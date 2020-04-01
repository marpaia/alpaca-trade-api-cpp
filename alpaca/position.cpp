#include "alpaca/position.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {
Status Position::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing position JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a position object");
  }

  PARSE_STRING(asset_class, "asset_class")
  PARSE_STRING(asset_id, "asset_id")
  PARSE_STRING(avg_entry_price, "avg_entry_price")
  PARSE_STRING(change_today, "change_today")
  PARSE_STRING(cost_basis, "cost_basis")
  PARSE_STRING(current_price, "current_price")
  PARSE_STRING(exchange, "exchange")
  PARSE_STRING(lastday_price, "lastday_price")
  PARSE_STRING(market_value, "market_value")
  PARSE_STRING(qty, "qty")
  PARSE_STRING(side, "side")
  PARSE_STRING(symbol, "symbol")
  PARSE_STRING(unrealized_intraday_pl, "unrealized_intraday_pl")
  PARSE_STRING(unrealized_intraday_plpc, "unrealized_intraday_plpc")
  PARSE_STRING(unrealized_pl, "unrealized_pl")
  PARSE_STRING(unrealized_plpc, "unrealized_plpc")

  return Status();
}
} // namespace alpaca