#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Get the last 100 of our closed orders
  auto list_orders_response = client.getOrders(alpaca::ActionStatus::Closed, 100);
  if (auto status = list_orders_response.first; !status.ok()) {
    std::cerr << "Error listing orders: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto orders = list_orders_response.second;

  // Get only the closed orders for a particular stock
  std::vector<alpaca::Order> aapl_orders;
  for (const auto& order : orders) {
    if (order.symbol == "AAPL") {
      aapl_orders.push_back(order);
    }
  }
  std::cout << "Found " << aapl_orders.size() << " closed orders for AAPL." << std::endl;

  return 0;
}