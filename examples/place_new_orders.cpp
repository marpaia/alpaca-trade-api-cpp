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
  auto buy_response =
      client.submitOrder("AAPL", 1, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
  if (auto status = buy_response.first; !status.ok()) {
    std::cerr << "Error submitting purchase order: " << status.getMessage() << std::endl;
    return status.getCode();
  }

  // Submit a limit order to attempt to sell 1 share of AMD at a particular
  // price ($20.50) when the market opens
  auto sell_response = client.submitOrder(
      "AMD", 1, alpaca::OrderSide::Sell, alpaca::OrderType::Limit, alpaca::OrderTimeInForce::OPG, "20.50");
  if (auto status = sell_response.first; !status.ok()) {
    std::cerr << "Error submitting sell order: " << status.getMessage() << std::endl;
    return status.getCode();
  }

  return 0;
}