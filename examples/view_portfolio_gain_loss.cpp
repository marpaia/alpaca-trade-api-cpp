#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Get account info
  auto account_response = client.getAccount();
  if (auto status = account_response.first; !status.ok()) {
    std::cerr << "Error getting account information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto account = account_response.second;

  // Check our current balance vs. our balance at the last market close
  std::cout << "Equity (cash + long_market_value + short_market_value): " << account.equity;
  std::cout << "Equity as of previous trading day: " << account.last_equity;

  return 0;
}