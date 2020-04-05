#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Submit a market order to buy 1 share of Apple at market price
  auto buy_response = client.submitOrder("AAPL",
                                         1,
                                         alpaca::OrderSide::Buy,
                                         alpaca::OrderType::Market,
                                         alpaca::OrderTimeInForce::Day,
                                         "",
                                         "",
                                         false,
                                         "my_first_order");
  if (auto status = buy_response.first; !status.ok()) {
    std::cerr << "Error submitting purchase order: " << status.getMessage() << std::endl;
    return status.getCode();
  }

  // Get order by it's client order ID
  auto get_order_response = client.getOrderByClientOrderID("my_first_order");
  if (auto status = get_order_response.first; !status.ok()) {
    std::cerr << "Error getting order: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto order = get_order_response.second;

  std::cout << "Got order by client order ID: " << order.id;

  return 0;
}