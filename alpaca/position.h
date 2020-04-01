#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing an Alpaca position.
 */
class Position {
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
  std::string avg_entry_price;
  std::string change_today;
  std::string cost_basis;
  std::string current_price;
  std::string exchange;
  std::string lastday_price;
  std::string market_value;
  std::string qty;
  std::string side;
  std::string symbol;
  std::string unrealized_intraday_pl;
  std::string unrealized_intraday_plpc;
  std::string unrealized_pl;
  std::string unrealized_plpc;
};
} // namespace alpaca