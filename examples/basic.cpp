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

  auto account_response = client.getAccount();
  if (auto status = account_response.first; !status.ok()) {
    LOG(ERROR) << "Error getting account information: " << status.getMessage();
    return status.getCode();
  }
  auto account = account_response.second;
  LOG(INFO) << "Alpaca account has the following buying power: " << account.buying_power;

  auto submit_order_response =
      client.submitOrder("NFLX", 10, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
  if (auto status = submit_order_response.first; !status.ok()) {
    LOG(ERROR) << "Error submitting order: " << status.getMessage();
    return status.getCode();
  }
  auto order = submit_order_response.second;
  LOG(INFO) << "Submitted order with client order ID: " << order.client_order_id;

  auto get_orders_response = client.getOrders(alpaca::OrderStatus::All);
  if (auto status = get_orders_response.first; !status.ok()) {
    LOG(ERROR) << "Error getting orders information: " << status.getMessage();
    return status.getCode();
  }
  auto orders = get_orders_response.second;
  LOG(INFO) << "Got info about " << orders.size() << " orders.";
  for (const auto& o : orders) {
    LOG(INFO) << "Fetching order by ID: " << o.id;
    auto single_order_response = client.getOrder(o.id);
    if (auto status = single_order_response.first; !status.ok()) {
      LOG(ERROR) << "Error getting order information: " << status.getMessage();
      return status.getCode();
    }
    LOG(INFO) << "Got order by ID: " << single_order_response.second.id;
  }

  return 0;
}