#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief The class of an asset.
 */
enum AssetClass {
  USEquity,
};

/**
 * @brief A helper to convert an AssetClass to a string
 */
std::string assetClassToString(const AssetClass asset_class);

/**
 * @brief A type representing an Alpaca asset.
 */
class Asset {
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
  bool easy_to_borrow;
  std::string exchange;
  std::string id;
  bool marginable;
  bool shortable;
  std::string status;
  std::string symbol;
  bool tradable;
};
} // namespace alpaca