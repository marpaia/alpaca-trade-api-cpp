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

  alpaca::Account account;
  if (auto status = client.getAccount(account); !status.ok()) {
    LOG(ERROR) << "Error getting account information: " << status.getMessage();
    return status.getCode();
  }
  LOG(INFO) << "Alpaca account has the following buying power: " << account.buying_power;

  return 0;
}