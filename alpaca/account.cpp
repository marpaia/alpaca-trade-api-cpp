#include "alpaca/account.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {
Status Account::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing account JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't an account object");
  }

  PARSE_BOOL(account_blocked, "account_blocked")
  PARSE_STRING(account_number, "account_number")
  PARSE_STRING(buying_power, "buying_power")
  PARSE_STRING(cash, "cash")
  PARSE_STRING(created_at, "created_at")
  PARSE_STRING(currency, "currency")
  PARSE_INT(daytrade_count, "daytrade_count")
  PARSE_STRING(daytrading_buying_power, "daytrading_buying_power")
  PARSE_STRING(equity, "equity")
  PARSE_STRING(id, "id")
  PARSE_STRING(initial_margin, "initial_margin")
  PARSE_STRING(last_equity, "last_equity")
  PARSE_STRING(last_maintenance_margin, "last_maintenance_margin")
  PARSE_STRING(long_market_value, "long_market_value")
  PARSE_STRING(maintenance_margin, "maintenance_margin")
  PARSE_STRING(multiplier, "multiplier")
  PARSE_BOOL(pattern_day_trader, "pattern_day_trader")
  PARSE_STRING(portfolio_value, "portfolio_value")
  PARSE_STRING(regt_buying_power, "regt_buying_power")
  PARSE_STRING(short_market_value, "short_market_value")
  PARSE_BOOL(shorting_enabled, "shorting_enabled")
  PARSE_STRING(sma, "sma")
  PARSE_STRING(status, "status")
  PARSE_BOOL(trade_suspended_by_user, "trade_suspended_by_user")
  PARSE_BOOL(trading_blocked, "trading_blocked")
  PARSE_BOOL(transfers_blocked, "transfers_blocked")

  return Status();
}

Status AccountConfigurations::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing account configurations JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't an account configurations object");
  }

  PARSE_STRING(dtbp_check, "dtbp_check")
  PARSE_BOOL(no_shorting, "no_shorting")
  PARSE_BOOL(suspend_trade, "suspend_trade")
  PARSE_STRING(trade_confirm_email, "trade_confirm_email")

  return Status();
}

Status TradeActivity::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing trade activity JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a trade activity object");
  }

  PARSE_STRING(activity_type, "activity_type")
  PARSE_STRING(cum_qty, "cum_qty")
  PARSE_STRING(id, "id")
  PARSE_STRING(leaves_qty, "leaves_qty")
  PARSE_STRING(order_id, "order_id")
  PARSE_STRING(price, "price")
  PARSE_STRING(qty, "qty")
  PARSE_STRING(side, "side")
  PARSE_STRING(symbol, "symbol")
  PARSE_STRING(transaction_time, "transaction_time")
  PARSE_STRING(type, "type")

  return Status();
}

Status NonTradeActivity::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing non-trade activity JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a non-trade activity object");
  }

  PARSE_STRING(activity_type, "activity_type")
  PARSE_STRING(date, "date")
  PARSE_STRING(id, "id")
  PARSE_STRING(net_amount, "net_amount")
  PARSE_STRING(per_share_amount, "per_share_amount")
  PARSE_STRING(qty, "qty")
  PARSE_STRING(symbol, "symbol")

  return Status();
}
} // namespace alpaca