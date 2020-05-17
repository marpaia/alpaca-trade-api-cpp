#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing a quote.
 */
class Quote {
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
  double ask_price;
  int ask_size;
  int ask_exchange;
  double bid_price;
  int bid_size;
  int bid_exchange;
  uint64_t timestamp;
};

/**
 * @brief A type representing the last quote for a certain symbol.
 */
class LastQuote {
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
  Quote quote;
};
} // namespace alpaca