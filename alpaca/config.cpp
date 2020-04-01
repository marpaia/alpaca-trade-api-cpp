#include "alpaca/config.h"

#include "glog/logging.h"

namespace alpaca {

Status Environment::parse() {
  auto error_suffix = " environment variable not set";

  if (auto e = std::getenv(api_key_id_env_var_.c_str())) {
    api_key_id_ = std::string(e);
  } else {
    return Status(1, api_key_id_env_var_ + error_suffix);
  }

  if (auto e = std::getenv(api_secret_key_env_var_.c_str())) {
    api_secret_key_ = std::string(e);
  } else {
    return Status(1, api_secret_key_env_var_ + error_suffix);
  }

  if (auto e = std::getenv(api_base_url_env_var_.c_str())) {
    api_base_url_ = std::string(e);
  } else {
    LOG(WARNING) << api_base_url_env_var_ << " not set so defaulting to using the paper URL: " << kAPIBaseURLPaper;
    api_base_url_ = kAPIBaseURLPaper;
  }

  if (auto e = std::getenv(api_data_url_env_var_.c_str())) {
    api_data_url_ = std::string(e);
  } else {
    DLOG(WARNING) << api_data_url_env_var_ << " not set so defaulting to using the default data URL: " << kAPIDataURL;
    api_data_url_ = kAPIDataURL;
  }

  parsed_ = true;
  return Status();
}

bool Environment::hasBeenParsed() const {
  return parsed_;
}

std::string Environment::getAPIKeyID() const {
  return api_key_id_;
}

std::string Environment::getAPISecretKey() const {
  return api_secret_key_;
}

std::string Environment::getAPIBaseURL() const {
  return api_base_url_;
}

std::string Environment::getAPIDataURL() const {
  return api_data_url_;
}
} // namespace alpaca