#pragma once

#include <map>
#include <string>
#include <vector>

#include "alpaca/status.h"
#include "rapidjson/document.h"

namespace alpaca {

/**
 * @brief A type representing an Alpaca bar.
 */
class Bar {
 public:
  /**
   * @brief A method for deserializing JSON into the current object state.
   *
   * @param json The JSON string
   *
   * @return a Status indicating the success or faliure of the operation.
   */
  Status fromJSON(const std::string& json);

  /**
   * @brief A method for deserializing JSON into the current object state.
   *
   * @param json The JSON string
   *
   * @return a Status indicating the success or faliure of the operation.
   */
  Status fromDocument(
      const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& d);

 public:
  uint time;
  double open_price;
  double high_price;
  double low_price;
  double close_price;
  uint volume;
};

/**
 * @brief A type representing bars for multiple symbols
 */
class Bars {
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
  std::map<std::string, std::vector<Bar>> bars;
};
} // namespace alpaca
