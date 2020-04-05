#include "alpaca/alpaca.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  LOG(INFO) << "Basic Alpaca C++ API Client Example";

  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    LOG(ERROR) << "Error parsing config from environment: " << status.getMessage();
    return status.getCode();
  }

  auto client = alpaca::Client(env);
  auto get_configs_resp = client.getAccountConfigurations();
  if (auto status = get_configs_resp.first; !status.ok()) {
    LOG(ERROR) << "Error getting account configs: " << status.getMessage();
    return status.getCode();
  }
  auto account_config = get_configs_resp.second;

  auto set_configs_resp = client.updateAccountConfigurations(!account_config.no_shorting,
                                                             account_config.dtbp_check,
                                                             account_config.trade_confirm_email,
                                                             account_config.suspend_trade);
  if (auto status = set_configs_resp.first; !status.ok()) {
    LOG(ERROR) << "Error setting account configs: " << status.getMessage();
    return status.getCode();
  }

  return 0;
}