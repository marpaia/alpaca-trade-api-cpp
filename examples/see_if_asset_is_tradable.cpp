#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Check if AAPL is tradable on the Alpaca platform.
  auto asset_response = client.getAsset("AAPL");
  if (auto status = asset_response.first; !status.ok()) {
    std::cerr << "Error getting asset information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto asset = asset_response.second;

  if (asset.tradable) {
    std::cout << "We can trade AAPL." << std::endl;
  } else {
    std::cout << "We can not trade AAPL." << std::endl;
  }

  return 0;
}