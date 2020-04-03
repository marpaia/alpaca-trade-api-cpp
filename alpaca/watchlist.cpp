#include "alpaca/watchlist.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace alpaca {

Status Watchlist::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing watchlist JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a watchlist object");
  }

  PARSE_STRING(account_id, "account_id")
  PARSE_STRING(created_at, "created_at")
  PARSE_STRING(id, "id")
  PARSE_STRING(name, "name")
  PARSE_STRING(updated_at, "updated_at")

  assets.clear();
  for (auto& a : d["assets"].GetArray()) {
    Asset asset;
    rapidjson::StringBuffer s;
    s.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    a.Accept(writer);
    if (auto status = asset.fromJSON(s.GetString()); !status.ok()) {
      return status;
    }
    assets.push_back(asset);
  }

  return Status();
}
} // namespace alpaca