#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing an Alpaca account.
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