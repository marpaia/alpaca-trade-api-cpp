#pragma once

#include <string>

#include "alpaca/account.h"
#include "alpaca/config.h"
#include "alpaca/status.h"

namespace alpaca {

/**
 * @brief The API client object for interacting with the Alpaca Trading API.
 *
 * @code{.cpp}
 *   auto env = alpaca::Environment();
 *   if (auto status = env.parse(); !status.ok()) {
 *     LOG(ERROR) << "Error parsing config from environment: " << status.getMessage();
 *     return status.getCode();
 *   }
 *   auto client = alpaca::Client(env);
 * @endcode
 */
class Client {
 public:
  /**
   * @brief The primary constructor.
   */
  explicit Client(Environment& environment);

  /**
   * @brief The default constructor of Client should never be used.
   */
  explicit Client() = delete;

  /**
   * @brief Fetch Alpaca account information.
   *
   * @code{.cpp}
   *   alpaca::Account account;
   *   if (auto status = client.getAccount(account); !status.ok()) {
   *     LOG(ERROR) << "Error getting account information: " << status.getMessage();
   *     return status.getCode();
   *   }
   *   LOG(INFO) << "ID: " << account.id;
   * @endcode
   *
   * @param account A reference to an initialized alpaca::Account object which
   * will be populated with the response content if the request is successful.
   *
   * @return a Status indicating the success or faliure of the operation.
   */
  Status getAccount(Account& account) const;

 private:
  Environment environment_;
};
} // namespace alpaca