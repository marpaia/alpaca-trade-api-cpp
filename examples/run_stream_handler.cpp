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

  std::function<void(alpaca::stream::DataType data)> on_trade_update = [=](alpaca::stream::DataType data) {
    LOG(INFO) << "Got trade update: " << data;
  };

  std::function<void(alpaca::stream::DataType data)> on_account_update = [=](alpaca::stream::DataType data) {
    LOG(INFO) << "Got account update: " << data;
  };

  auto handler = alpaca::stream::Handler(on_trade_update, on_account_update);
  if (auto status = handler.run(env); !status.ok()) {
    LOG(ERROR) << "Error running stream handler: " << status.getMessage();
    return status.getCode();
  }

  return 0;
}
