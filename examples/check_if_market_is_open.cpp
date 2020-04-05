#include <iostream>

#include "alpaca/alpaca.h"

int main(int argc, char* argv[]) {
  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto client = alpaca::Client(env);

  // Check if the market is open now.
  auto clock_response = client.getClock();
  if (auto status = clock_response.first; !status.ok()) {
    std::cerr << "Error getting clock information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto clock = clock_response.second;

  if (clock.is_open) {
    std::cout << "The market is open." << std::endl;
  } else {
    std::cout << "The market is closed." << std::endl;
  }

  // Check when the market was open on Dec. 1, 2018
  auto date = "2018-12-01";
  auto calendar_response = client.getCalendar(date, date);
  if (auto status = calendar_response.first; !status.ok()) {
    std::cerr << "Error getting calendar information: " << status.getMessage() << std::endl;
    return status.getCode();
  }
  auto days = calendar_response.second;
  if (auto size = days.size(); size != 1) {
    std::cerr << "Expected to receive 1 day result but got " << size << "instead." << std::endl;
  }
  auto day = days.front();
  std::cout << "The market opened at " << day.open << " and closed at " << day.close << " on " << day.date << "."
            << std::endl;
  return 0;
}