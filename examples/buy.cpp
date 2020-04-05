#include "alpaca/alpaca.h"
#include "glog/logging.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    LOG(ERROR) << "Error parsing config from environment: " << status.getMessage();
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  auto submit_order_response =
      client.submitOrder("NFLX", 1, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
  if (auto status = submit_order_response.first; !status.ok()) {
    LOG(ERROR) << "Error submitting order: " << status.getMessage();
    return status.getCode();
  }
  auto order = submit_order_response.second;
  LOG(INFO) << "Submitted order (Order ID: " << order.id << ")";

  return 0;
}