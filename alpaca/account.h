#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing an Alpaca account.
 */
class Account {
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
  bool account_blocked;
  std::string account_number;
  std::string buying_power;
  std::string cash;
  std::string created_at;
  std::string currency;
  int daytrade_count;
  std::string daytrading_buying_power;
  std::string equity;
  std::string id;
  std::string initial_margin;
  std::string last_equity;
  std::string last_maintenance_margin;
  std::string long_market_value;
  std::string maintenance_margin;
  std::string multiplier;
  bool pattern_day_trader;
  std::string portfolio_value;
  std::string regt_buying_power;
  std::string short_market_value;
  bool shorting_enabled;
  std::string sma;
  std::string status;
  bool trade_suspended_by_user;
  bool trading_blocked;
  bool transfers_blocked;
};

/**
 * @brief A type representing Alpaca account configuration.
 */
class AccountConfiguration {
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
  std:: string dtbp_check;
  bool no_shorting;
  bool suspend_trade;
  std::string trade_confirm_email;
};
} // namespace alpaca