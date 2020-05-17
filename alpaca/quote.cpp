#include "alpaca/quote.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace alpaca {
Status Quote::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing quote JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a quote object");
  }

  PARSE_DOUBLE(ask_price, "askprice")
  PARSE_INT(ask_size, "asksize")
  PARSE_INT(ask_exchange, "askexchange")
  PARSE_DOUBLE(bid_price, "bidprice")
  PARSE_INT(bid_size, "bidsize")
  PARSE_INT(bid_exchange, "bidexchange")
  PARSE_UINT64(timestamp, "timestamp")

  return Status();
}

Status LastQuote::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing last quote JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a last quote object");
  }

  PARSE_STRING(status, "status")
  PARSE_STRING(symbol, "symbol")

  if (d.HasMember("last") && d["last"].IsObject()) {
    rapidjson::StringBuffer s;
    s.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    d["last"].Accept(writer);
    if (auto status = quote.fromJSON(s.GetString()); !status.ok()) {
      return status;
    }
  }

  return Status();
};
} // namespace alpaca