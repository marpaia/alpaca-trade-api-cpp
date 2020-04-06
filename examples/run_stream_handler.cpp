#include "alpaca/config.h"
#include "alpaca/streaming.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  LOG(INFO) << "Starting streaming example";

  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    LOG(ERROR) << "Error parsing environment: " << status.getMessage();
    return status.getCode();
  }

  auto handler = alpaca::StreamHandler();
  if (auto status = handler.run(env); !status.ok()) {
    LOG(ERROR) << "Error running stream handler: " << status.getMessage();
    return status.getCode();
  }

  return 0;
}