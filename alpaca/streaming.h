#pragma once

#include <set>
#include <string>
#include <utility>
#include <variant>

#include "alpaca/config.h"
#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief A type representing streams that may be subscribed too
 */
enum Stream {
  TradeUpdates,
  AccountUpdates,
};

/**
 * @brief A type represennting the different replies one might receive
 */
enum Reply {
  Unknown,
  Authorization,
  Listening,
};

/**
 * @brief The string representation of an authorization reply
 */
const std::string kAuthorizationStream = "authorization";

/**
 * @brief The string representation of a listening reply
 */
const std::string kListeningStream = "listening";

/**
 * @brief The string representation of a trade updates reply
 */
const std::string kTradeUpdatesStream = "trade_updates";

/**
 * @brief The string representation of an account updates reply
 */
const std::string kAccountUpdatesStream = "account_updates";

/**
 * @brief A helper class for generating messages for the stream API
 */
class MessageGenerator {
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

/**
 * @brief A helper class for parsing replies from the stream API
 */
class ReplyParser {
 public:
  /**
   * @brief A function for determining which type of message a reply is
   */
  std::pair<Status, std::variant<Reply, Stream>> messageType(const std::string& text) const;
};

/**
 * @brief A class for handling stream messages
 */
class StreamHandler {
 public:
  /**
   * @brief Run the stream handler and block.
   */
  Status run(Environment& env);
};

} // namespace alpaca