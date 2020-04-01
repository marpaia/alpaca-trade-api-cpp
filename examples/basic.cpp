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

  return 0;
}