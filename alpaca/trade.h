#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing a trade.
 */
class Trade {
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
  double price;
  int size;
  int exchange;
  int cond1;
  int cond2;
  int cond3;
  int cond4;
  uint64_t timestamp;
};

/**
 * @brief A type representing the last trade for a certain symbol.
 */
class LastTrade {
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
  std::string status;
  std::string symbol;
  Trade trade;
};
} // namespace alpaca