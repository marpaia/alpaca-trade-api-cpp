#include "streaming.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace alpaca {

std::string streamToString(const Stream stream) {
  switch (stream) {
      case TradeUpdates:
        return "trade_updates";
      case AccountUpdates:
        return "account_updates";
      }
}

std::string MessageHelper::authentication(const std::string& key_id, const std::string& secret_key) const {
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

std::string MessageHelper::listen(const std::set<Stream>& streams) const {
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

} // namespace alpaca