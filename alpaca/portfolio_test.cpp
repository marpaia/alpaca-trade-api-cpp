#include "alpaca/portfolio.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class PortfolioTest : public ::testing::Test {};

const std::string kPortfolioHistoryJSON =
    "{"
    "\"timestamp\": [1580826600000, 1580827500000, 1580828400000],"
    "\"equity\": [27423.73, 27408.19, 27515.97],"
    "\"profit_loss\": [11.8, -3.74, 104.04],"
    "\"profit_loss_pct\": [0.000430469507254688, -0.0001364369455197062, 0.0037954277571845543],"
    "\"base_value\": 27411.93,"
    "\"timeframe\": \"15Min\""
    "}";

TEST_F(PortfolioTest, testPortfolioHistoryFromJSON) {
  alpaca::PortfolioHistory portfolio_history;
  EXPECT_OK(portfolio_history.fromJSON(kPortfolioHistoryJSON));
  EXPECT_EQ(portfolio_history.equity.size(), 3);
  EXPECT_EQ(portfolio_history.timestamp.size(), 3);
  EXPECT_EQ(portfolio_history.profit_loss.size(), 3);
  EXPECT_EQ(portfolio_history.profit_loss_pct.size(), 3);
  EXPECT_EQ(portfolio_history.timeframe, "15Min");
  EXPECT_EQ(portfolio_history.base_value, 27411.93);
}
