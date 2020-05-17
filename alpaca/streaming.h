#pragma once

#include <functional>
#include <set>
#include <string>
#include <utility>
#include <variant>

#include "alpaca/config.h"
#include "alpaca/status.h"

namespace alpaca::stream {

typedef std::string DataType;
const DataType kDefaultData = "{}";

/**
 * @brief A type representing streams that may be subscribed too
 */
enum StreamType {
  UnknownStreamType,
  TradeUpdates,
  AccountUpdates,
};

/**
 * @brief A type represennting the different replies one might receive
 */
enum ReplyType {
  UnknownReplyType,
  Authorization,
  Listening,
  Update,
};

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
  std::string listen(const std::set<StreamType>& streams) const;
};

/**
 * @brief A class for handling stream messages
 */
class Handler {
 public:
  Handler() = delete;
  Handler(std::function<void(DataType)> on_trade_update, std::function<void(DataType)> on_account_update)
      : on_trade_update_(on_trade_update), on_account_update_(on_account_update) {}

 public:
  /**
   * @brief Run the stream handler and block.
   */
  Status run(Environment& env);

 private:
  std::function<void(DataType)> on_trade_update_;
  std::function<void(DataType)> on_account_update_;
};

class Reply {
 public:
  Reply(const ReplyType reply_type = UnknownReplyType,
        StreamType stream_type = UnknownStreamType,
        const DataType data = kDefaultData)
      : reply_type(reply_type), stream_type(stream_type), data(data) {}

 public:
  ReplyType reply_type;
  StreamType stream_type;
  std::string data;
};

/**
 * @brief Parse text from an Alpaca stream into a Reply object
 */
std::pair<Status, Reply> parseReply(const std::string& text);

} // namespace alpaca::stream