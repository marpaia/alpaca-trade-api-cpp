#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Get a list of all active assets.
  auto assets_response = client.getAssets();
  if (auto status = assets_response.first; !status.ok()) {
    std::cerr << "Error getting assets information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto assets = assets_response.second;

  // Filter the assets down to just those on NASDAQ.
  std::vector<alpaca::Asset> nasdaq_assets;
  for (const auto& asset : assets) {
    if (asset.exchange == "NASDAQ") {
      nasdaq_assets.push_back(asset);
    }
  }

  std::cout << "Found " << nasdaq_assets.size() << " assets being traded on the NASDAQ exchange" << std::endl;

  return 0;
}