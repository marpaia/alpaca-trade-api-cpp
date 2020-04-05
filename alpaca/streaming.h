#pragma once

#include <string>
#include <set>

#include "alpaca/config.h"

namespace alpaca {

enum Stream {
  TradeUpdates,
  AccountUpdates,
};

class MessageHelper {
 public:
  /**
   * @brief Create an authentication message for the Alpaca stream API
   */
  std::string authentication(const std::string& key_id, const std::string& secret_key) const;

  /**
   * @brief Create message for which stream to listen to for the Alpaca stream API
   */
  std::string listen(const std::set<Stream>& streams) const;
};

} // namespace alpaca