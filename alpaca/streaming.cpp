#include "streaming.h"

#include "glog/logging.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "uWS.h"

namespace alpaca::stream {

/**
 * @brief The string representation of an authorization reply
 */
const std::string kAuthorizationStream = "authorization";

/**
 * @brief The string representation of a listening reply
 */
const std::string kListeningStream = "listening";

/**
 * @brief The string representation of a trade updates reply
 */
const std::string kTradeUpdatesStream = "trade_updates";

/**
 * @brief The string representation of an account updates reply
 */
const std::string kAccountUpdatesStream = "account_updates";

std::string streamToString(const StreamType stream) {
  switch (stream) {
  case TradeUpdates:
    return "trade_updates";
  case AccountUpdates:
    return "account_updates";
  case UnknownStreamType:
    return "unknown";
  }
}

std::string MessageGenerator::authentication(const std::string& key_id, const std::string& secret_key) const {
  rapidjson::StringBuffer s;
  s.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartObject();
  writer.Key("action");
  writer.String("authenticate");
  writer.Key("data");
  writer.StartObject();
  writer.Key("key_id");
  writer.String(key_id.c_str());
  writer.Key("secret_key");
  writer.String(secret_key.c_str());
  writer.EndObject();
  writer.EndObject();
  return s.GetString();
}

std::string MessageGenerator::listen(const std::set<StreamType>& streams) const {
  rapidjson::StringBuffer s;
  s.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartObject();
  writer.Key("action");
  writer.String("listen");
  writer.Key("data");
  writer.StartObject();
  writer.Key("streams");
  writer.StartArray();
  for (const auto& stream : streams) {
    writer.String(streamToString(stream).c_str());
  }
  writer.EndArray();
  writer.EndObject();
  writer.EndObject();
  return s.GetString();
}

std::pair<Status, Reply> parseReply(const std::string& text) {
  Reply r;

  rapidjson::Document d;
  if (d.Parse(text.c_str()).HasParseError()) {
    return std::make_pair(Status(1, "Received parse error when deserializing reply JSON"), r);
  }

  if (!d.IsObject()) {
    return std::make_pair(Status(1, "Deserialized valid JSON but it wasn't an object"), r);
  }

  if (d.HasMember("stream") && d["stream"].IsString()) {
    auto stream = d["stream"].GetString();
    if (*stream == *kAuthorizationStream.c_str()) {
      r.reply_type = Authorization;
      return std::make_pair(Status(), r);
    } else if (*stream == *kListeningStream.c_str()) {
      r.reply_type = Listening;
      return std::make_pair(Status(), r);
    } else if (*stream == *kTradeUpdatesStream.c_str()) {
      r.reply_type = Update;
      r.stream_type = TradeUpdates;
    } else if (*stream == *kAccountUpdatesStream.c_str()) {
      r.reply_type = Update;
      r.stream_type = AccountUpdates;
    } else {
      std::ostringstream ss;
      ss << "Unknown stream string: " << stream;
      return std::make_pair(Status(1, ss.str()), r);
    }
  } else {
    return std::make_pair(Status(1, "Reply did not contain stream key"), r);
  }

  if (d.HasMember("data") && d["data"].IsObject()) {
    rapidjson::StringBuffer s;
    s.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    d["data"].Accept(writer);
    r.data = s.GetString();
  }

  return std::make_pair(Status(), r);
}

Status Handler::run(Environment& env) {
  uWS::Hub hub;
  auto group = hub.createGroup<uWS::CLIENT>();

  if (!env.hasBeenParsed()) {
    if (auto status = env.parse(); !status.ok()) {
      return status;
    }
  }
  auto message_generator_ = MessageGenerator();
  auto authentication = message_generator_.authentication(env.getAPIKeyID(), env.getAPISecretKey());
  auto listen = message_generator_.listen({StreamType::TradeUpdates, StreamType::AccountUpdates});

  group->onConnection([authentication](uWS::WebSocket<uWS::CLIENT>* ws, uWS::HttpRequest req) {
    DLOG(INFO) << "Received connection event and sending authenticate message";
    ws->send(authentication.data(), authentication.size(), uWS::OpCode::TEXT);
  });

  group->onMessage([this, listen](uWS::WebSocket<uWS::CLIENT>* ws, char* message, size_t length, uWS::OpCode opCode) {
    auto text = std::string(message, length);

    auto parsed_reply = parseReply(text);
    if (auto status = parsed_reply.first; !status.ok()) {
      LOG(ERROR) << "Error parsing stream reply: " << status.getMessage();
      return;
    }
    auto reply = parsed_reply.second;

    if (reply.reply_type == ReplyType::Authorization) {
      DLOG(INFO) << "Sending listen message: " << listen;
      ws->send(listen.data(), listen.size(), uWS::OpCode::TEXT);
      return;
    } else if (reply.reply_type == ReplyType::Listening) {
      DLOG(INFO) << "Received listening confirmation";
      return;
    } else if (reply.reply_type == ReplyType::UnknownReplyType) {
      LOG(WARNING) << "Received unknown stream reply type";
      return;
    } else if (reply.reply_type == ReplyType::Update) {
      DLOG(INFO) << "Received update message";
    } else {
      LOG(ERROR) << "Unhandled stream reply type in router: " << reply.reply_type;
    }

    if (reply.stream_type == StreamType::UnknownStreamType) {
      LOG(WARNING) << "Received unknown stream type";
    } else if (reply.stream_type == StreamType::TradeUpdates) {
      DLOG(INFO) << "Received trade update";
      on_trade_update_(reply.data);
    } else if (reply.stream_type == StreamType::AccountUpdates) {
      DLOG(INFO) << "Received account update";
      on_account_update_(reply.data);
    } else {
      LOG(ERROR) << "Unhandled stream type in router: " << reply.stream_type;
    }
  });

  group->onDisconnection([](uWS::WebSocket<uWS::CLIENT>* ws, int code, char* message, size_t length) {
    DLOG(INFO) << "Received disconnection event: " << std::string(message, length);
  });

  group->onError([](void* e) { LOG(ERROR) << "Received error in stream handler."; });

  std::ostringstream ss;
  ss << "wss://" << env.getAPIBaseURL() << "/stream";
  hub.connect(ss.str(), nullptr, {}, 5000, group);
  hub.run();

  return Status(1, "unreachable");
}

} // namespace alpaca::stream