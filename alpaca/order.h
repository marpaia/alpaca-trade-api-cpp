#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief The direction to display orders in when enumerating them.
 */
enum OrderDirection {
  Ascending,
  Descending,
};

/**
 * @brief A helper to convert an OrderDirection to a string
 */
std::string orderDirectionToString(const OrderDirection direction);

/**
 * @brief When you submit an order, you may be buying or selling.
 */
enum OrderSide {
  Buy,
  Sell,
};

/**
 * @brief A helper to convert an OrderSide to a string
 */
std::string orderSideToString(const OrderSide side);

/**
 * @brief When you submit an order, you can choose a supported order type.
 *
 * For more information on supported order types, see:
 * https://alpaca.markets/docs/trading-on-alpaca/orders/#order-types
 */
enum OrderType {
  Market,
  Limit,
  Stop,
  StopLimit,
};

/**
 * @brief A helper to convert an OrderType to a string
 */
std::string orderTypeToString(const OrderType side);

/**
 * @brief Alpaca supports several Time-In-Force designations
 *
 * For more information on the supported designations, see:
 * https://alpaca.markets/docs/trading-on-alpaca/orders/#time-in-force
 */
enum OrderTimeInForce {
  Day,
  GoodUntilCanceled,
  OPG,
  CLS,
  ImmediateOrCancel,
  FillOrKill,
};

/**
 * @brief A helper to convert an OrderTimeInForce to a string
 */
std::string orderTimeInForceToString(const OrderTimeInForce tif);

/**
 * @brief The class of the order
 *
 * For details of non-simple order classes, please see:
 * https://alpaca.markets/docs/trading-on-alpaca/orders/#bracket-orders
 */
enum OrderClass {
  Simple,
  Bracket,
  OneCancelsOther,
  OneTriggersOther,
};

/**
 * @brief A helper to convert an OrderClass to a string
 */
std::string orderClassToString(const OrderClass order_class);

/**
 * @brief Additional parameters for take-profit leg of advanced orders
 */
struct TakeProfitParams {
  /// Required for bracket orders
  std::string limitPrice;
};

/**
 * @brief Additional parameters for stop-loss leg of advanced orders
 */
struct StopLossParams {
  /// Required for bracket orders
  std::string stopPrice;
  /// The stop-loss order becomes a stop-limit order if specified
  std::string limitPrice;
};

/**
 * @brief A type representing an Alpaca order.
 */
class Order {
 public:
  /**
   * @brief A method for deserializing JSON into the current object state.
   *
   * @param json The JSON string
   *
   * @return a Status indicating the success or faliure of the operation.
   */
  Status fromJSON(const std::string& json);

 public:
  std::string asset_class;
  std::string asset_id;
  std::string canceled_at;
  std::string client_order_id;
  std::string created_at;
  std::string expired_at;
  bool extended_hours;
  std::string failed_at;
  std::string filled_at;
  std::string filled_avg_price;
  std::string filled_qty;
  std::string id;
  bool legs;
  std::string limit_price;
  std::string qty;
  std::string side;
  std::string status;
  std::string stop_price;
  std::string submitted_at;
  std::string symbol;
  std::string time_in_force;
  std::string type;
  std::string updated_at;
};
} // namespace alpaca