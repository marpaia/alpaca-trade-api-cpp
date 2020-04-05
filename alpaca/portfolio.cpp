#include "alpaca/portfolio.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {
Status PortfolioHistory::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing portfolio JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a portfolio object");
  }

  PARSE_DOUBLE(base_value, "base_value")
  PARSE_VECTOR_DOUBLES(equity, "equity")
  PARSE_VECTOR_DOUBLES(profit_loss, "profit_loss")
  PARSE_VECTOR_DOUBLES(profit_loss_pct, "profit_loss_pct")
  PARSE_STRING(timeframe, "timeframe")
  PARSE_VECTOR_UINT64(timestamp, "timestamp")

  return Status();
}
} // namespace alpaca
