#pragma once

#include <string>

#include "alpaca/status.h"

namespace alpaca {

/// The base URL for API calls to the live trading API
const std::string kAPIBaseURLLive = "api.alpaca.markets";

/// The base URL for API calls to the paper trading API
const std::string kAPIBaseURLPaper = "paper-api.alpaca.markets";

/// The base URL for API calls to the data API
const std::string kAPIDataURL = "data.alpaca.markets";

/**
 * @brief A class to help witth parsing required variables from the environment.
 * @code{.cpp}
 *   auto env = alpaca::Environment();
 *   if (auto status = env.parse(); !status.ok()) {
 *     LOG(ERROR) << "Error parsing config from environment: "
 *                << status.getMessage();
 *     return status.getCode();
 *   }
 * @endcode
 */
class Environment {
 public:
  /**
   * @brief Default constructor
   *
   * Use the default constructor with overrides if you'd like to parse the
   * required environment variables from non-standard names.
   */
  explicit Environment(std::string api_key_id_env_var = "APCA_API_KEY_ID",
                       std::string api_secret_key_env_var = "APCA_API_SECRET_KEY",
                       std::string api_base_url_env_var = "APCA_API_BASE_URL",
                       std::string api_data_url_env_var = "APCA_API_DATA_URL")
      : api_key_id_env_var_(api_key_id_env_var),
        api_secret_key_env_var_(api_secret_key_env_var),
        api_base_url_env_var_(api_base_url_env_var),
        api_data_url_env_var_(api_data_url_env_var) {}

  /**
   * @brief Parse the environment variables into local state.
   *
   * @return a Status indicating the success or faliure of the operation.
   */
  Status parse();

  /**
   * @brief Indicates wether or not the environment has been successfully
   * parsed.
   */
  bool hasBeenParsed() const;

  /**
   * @brief A getter for the API Key ID
   *
   * Note that this method should only be called after successfully calliing
   * the parse() method.
   */
  std::string getAPIKeyID() const;

  /**
   * @brief A getter for the API Secret Key
   *
   * Note that this method should only be called after successfully calliing
   * the parse() method.
   */
  std::string getAPISecretKey() const;

  /**
   * @brief A getter for the API Base URL
   *
   * Note that this method should only be called after successfully calliing
   * the parse() method.
   */
  std::string getAPIBaseURL() const;

  /**
   * @brief A getter for the API Data URL
   *
   * Note that this method should only be called after successfully calliing
   * the parse() method.
   */
  std::string getAPIDataURL() const;

 private:
  bool parsed_;

  std::string api_key_id_;
  std::string api_secret_key_;
  std::string api_base_url_;
  std::string api_data_url_;

  std::string api_key_id_env_var_;
  std::string api_secret_key_env_var_;
  std::string api_base_url_env_var_;
  std::string api_data_url_env_var_;
};
} // namespace alpaca