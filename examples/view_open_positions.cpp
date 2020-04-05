#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Get our position in AAPL.
  auto get_position_response = client.getPosition("AAPL");
  if (auto status = get_position_response.first; status.ok()) {
    auto position = get_position_response.second;
    std::cout << "Apple position: " << position.qty << " shares." << std::endl;
  } else {
    std::cout << "No AAPL position.";
  }

  // Get a list of all of our positions.
  auto get_positions_response = client.getPositions();
  if (auto status = get_positions_response.first; !status.ok()) {
    std::cerr << "Error getting positions information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto positions = get_positions_response.second;
  for (const auto& position : positions) {
    std::cout << position.qty << " shares in " << position.symbol << std::endl;
  }

  return 0;
}