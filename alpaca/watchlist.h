#pragma once

#include <string>
#include <vector>

#include "alpaca/asset.h"
#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing an Alpacaa watchlist
 */
class Watchlist {
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
  std::string account_id;
  std::vector<Asset> assets;
  std::string created_at;
  std::string id;
  std::string name;
  std::string updated_at;
};
} // namespace alpaca