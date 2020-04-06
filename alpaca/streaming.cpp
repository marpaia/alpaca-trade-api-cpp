#include "streaming.h"

#include "glog/logging.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "uWS.h"

namespace alpaca {

std::string streamToString(const Stream stream) {
  switch (stream) {
  case TradeUpdates:
    return "trade_updates";
  case AccountUpdates:
    return "account_updates";
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

std::string MessageGenerator::listen(const std::set<Stream>& streams) const {
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

std::pair<Status, std::variant<Reply, Stream>> ReplyParser::messageType(const std::string& text) const {
  rapidjson::Document d;
  if (d.Parse(text.c_str()).HasParseError()) {
    return std::make_pair(Status(1, "Received parse error when deserializing reply JSON"), Unknown);
  }

  if (!d.IsObject()) {
    return std::make_pair(Status(1, "Deserialized valid JSON but it wasn't an object"), Unknown);
  }

  if (d.HasMember("stream") && d["stream"].IsString()) {
    auto stream = d["stream"].GetString();
    if (*stream == *kAuthorizationStream.c_str()) {
      return std::make_pair(Status(), Authorization);
    } else if (*stream == *kListeningStream.c_str()) {
      return std::make_pair(Status(), Listening);
    } else if (*stream == *kTradeUpdatesStream.c_str()) {
      return std::make_pair(Status(), TradeUpdates);
    } else if (*stream == *kAccountUpdatesStream.c_str()) {
      return std::make_pair(Status(), AccountUpdates);
    } else {
      std::ostringstream ss;
      ss << "Unknown stream string: " << stream;
      return std::make_pair(Status(1, ss.str()), Unknown);
    }
  }

  return std::make_pair(Status(1, "Reply did not contain stream key"), Unknown);
}

Status StreamHandler::run(Environment& env) {
  uWS::Hub hub;
  auto group = hub.createGroup<uWS::CLIENT>();

  if (!env.hasBeenParsed()) {
    if (auto status = env.parse(); !status.ok()) {
      return status;
    }
  }
  auto m = MessageGenerator();
  auto r = ReplyParser();
  auto authentication = m.authentication(env.getAPIKeyID(), env.getAPISecretKey());

  group->onConnection([authentication](uWS::WebSocket<uWS::CLIENT>* ws, uWS::HttpRequest req) {
    DLOG(INFO) << "Received connection event and sending authenticate message";
    ws->send(authentication.data(), authentication.size(), uWS::OpCode::TEXT);
  });

  group->onMessage([m, r](uWS::WebSocket<uWS::CLIENT>* ws, char* message, size_t length, uWS::OpCode opCode) {
    auto text = std::string(message, length);
    DLOG(INFO) << "Got reply: " << text;

    auto message_type = r.messageType(text);
    if (auto status = message_type.first; !status.ok()) {
      LOG(ERROR) << "Error parsing stream reply: " << status.getMessage();
      return;
    }

    try {
      auto stream_type = std::get<Stream>(message_type.second);
      if (stream_type == TradeUpdates) {
        DLOG(INFO) << "Received trade update";
      } else if (stream_type == AccountUpdates) {
        DLOG(INFO) << "Received account update";
      } else {
        LOG(ERROR) << "Unhandled stream type in router: " << stream_type;
      }

      return;
    } catch (const std::bad_variant_access&) {
    }

    try {
      auto reply_type = std::get<Reply>(message_type.second);
      if (reply_type == Authorization) {
        auto listen = m.listen({TradeUpdates, AccountUpdates});
        DLOG(INFO) << "Sending listen message: " << listen;
        ws->send(listen.data(), listen.size(), uWS::OpCode::TEXT);
      } else if (reply_type == Listening) {
        DLOG(INFO) << "Received listening confirmation";
      } else if (reply_type == Unknown) {
        LOG(WARNING) << "Received unknown stream reply type";
      } else {
        LOG(ERROR) << "Unhandled stream reply type in router: " << reply_type;
      }

      return;
    } catch (const std::bad_variant_access&) {
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

} // namespace alpaca