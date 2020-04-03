#include "alpaca/order.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {

std::string orderDirectionToString(const OrderDirection direction) {
  switch (direction) {
  case OrderDirection::Ascending:
    return "asc";
  case OrderDirection::Descending:
    return "desc";
  }
}

std::string orderSideToString(const OrderSide side) {
  switch (side) {
  case OrderSide::Buy:
    return "buy";
  case OrderSide::Sell:
    return "sell";
  }
}

std::string orderTypeToString(const OrderType type) {
  switch (type) {
  case OrderType::Market:
    return "market";
  case OrderType::Limit:
    return "limit";
  case OrderType::Stop:
    return "stop";
  case OrderType::StopLimit:
    return "stop_limit";
  }
}

std::string orderTimeInForceToString(const OrderTimeInForce tif) {
  switch (tif) {
  case OrderTimeInForce::Day:
    return "day";
  case OrderTimeInForce::GoodUntilCanceled:
    return "gtc";
  case OrderTimeInForce::OPG:
    return "opg";
  case OrderTimeInForce::CLS:
    return "cls";
  case OrderTimeInForce::ImmediateOrCancel:
    return "ioc";
  case OrderTimeInForce::FillOrKill:
    return "fok";
  }
}

std::string orderClassToString(const OrderClass order_class) {
  switch (order_class) {
  case OrderClass::Simple:
    return "simple";
  case OrderClass::Bracket:
    return "bracket";
  case OrderClass::OneCancelsOther:
    return "oco";
  case OrderClass::OneTriggersOther:
    return "oto";
  }
}

Status Order::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing order JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't an order object");
  }

  PARSE_STRING(asset_class, "asset_class")
  PARSE_STRING(asset_id, "asset_id")
  PARSE_STRING(canceled_at, "canceled_at")
  PARSE_STRING(client_order_id, "client_order_id")
  PARSE_STRING(created_at, "created_at")
  PARSE_STRING(expired_at, "expired_at")
  PARSE_BOOL(extended_hours, "extended_hours")
  PARSE_STRING(failed_at, "failed_at")
  PARSE_STRING(filled_at, "filled_at")
  PARSE_STRING(filled_avg_price, "filled_avg_price")
  PARSE_STRING(filled_qty, "filled_qty")
  PARSE_STRING(id, "id")
  PARSE_BOOL(legs, "legs")
  PARSE_STRING(limit_price, "limit_price")
  PARSE_STRING(qty, "qty")
  PARSE_STRING(side, "side")
  PARSE_STRING(status, "status")
  PARSE_STRING(stop_price, "stop_price")
  PARSE_STRING(submitted_at, "submitted_at")
  PARSE_STRING(symbol, "symbol")
  PARSE_STRING(time_in_force, "time_in_force")
  PARSE_STRING(type, "type")
  PARSE_STRING(updated_at, "updated_at")

  return Status();
}
} // namespace alpaca