#pragma once

#include <string>
#include <vector>

#include "alpaca/status.h"

namespace alpaca {
class PortfolioHistory {
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
  double base_value;
  std::vector<double> equity;
  std::vector<double> profit_loss;
  std::vector<double> profit_loss_pct;
  std::string timeframe;
  std::vector<uint64_t> timestamp;
};
} // namespace alpaca