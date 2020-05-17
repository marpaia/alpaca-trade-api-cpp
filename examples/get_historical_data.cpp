#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  // Parse configuration from the environment
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }

  // Create an API client object
  auto client = alpaca::Client(env);

  auto bars_response = client.getBars({"AAPL"}, "2020-04-01T09:30:00-04:00", "2020-04-03T09:30:00-04:00");
  if (auto status = bars_response.first; !status.ok()) {
    std::cerr << "Error getting bars information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto bars = bars_response.second.bars["AAPL"];

  auto start_price = bars.front().open_price;
  auto end_price = bars.back().close_price;
  auto percent_change = (end_price - start_price) / start_price * 100;
  std::cout << "AAPL moved " << percent_change << "% over the time range." << std::endl;

  auto last_trade_response = client.getLastTrade("AAPL");
  if (auto status = last_trade_response.first; !status.ok()) {
    std::cerr << "Error getting last trade information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto last_trade = last_trade_response.second;
  std::cout << "The last traded price of AAPL was: $" << last_trade.trade.price << std::endl;

  auto last_quote_response = client.getLastQuote("AAPL");
  if (auto status = last_quote_response.first; !status.ok()) {
    std::cerr << "Error getting last quote information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto last_quote = last_quote_response.second;
  std::cout << "The last quoted ask price of AAPL was: $" << last_quote.quote.ask_price << std::endl;

  return 0;
}