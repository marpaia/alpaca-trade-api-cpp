#include "alpaca/trade.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace alpaca {
Status Trade::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing trade JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a trade object");
  }

  PARSE_DOUBLE(price, "price")
  PARSE_INT(size, "size")
  PARSE_INT(exchange, "exchange")
  PARSE_INT(cond1, "cond1")
  PARSE_INT(cond2, "cond2")
  PARSE_INT(cond3, "cond3")
  PARSE_INT(cond4, "cond4")
  PARSE_UINT64(timestamp, "timestamp")

  return Status();
}

Status LastTrade::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing last trade JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a last trade object");
  }

  PARSE_STRING(status, "status")
  PARSE_STRING(symbol, "symbol")

  if (d.HasMember("last") && d["last"].IsObject()) {
    rapidjson::StringBuffer s;
    s.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    d["last"].Accept(writer);
    if (auto status = trade.fromJSON(s.GetString()); !status.ok()) {
      return status;
    }
  }

  return Status();
}
} // namespace alpaca