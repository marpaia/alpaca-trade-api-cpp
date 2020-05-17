#include "alpaca/trade.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class LastTradeTest : public ::testing::Test {};

const std::string kLastTradeJSON =
    "{"
    "\"status\": \"success\","
    "\"symbol\": \"SPY\","
    "\"last\": {"
    "\"price\": 286.84,"
    "\"size\": 100,"
    "\"exchange\": 2,"
    "\"cond1\": 12,"
    "\"cond2\": 0,"
    "\"cond3\": 0,"
    "\"cond4\": 0,"
    "\"timestamp\": 1588770424970329400"
    "}"
    "}";

TEST_F(LastTradeTest, testLastTradeFromJSON) {
  alpaca::LastTrade last_trade;
  EXPECT_OK(last_trade.fromJSON(kLastTradeJSON));
  EXPECT_EQ(last_trade.status, "success");
  EXPECT_EQ(last_trade.symbol, "SPY");
  EXPECT_EQ(last_trade.trade.price, 286.84);
  EXPECT_EQ(last_trade.trade.size, 100);
  EXPECT_EQ(last_trade.trade.exchange, 2);
  EXPECT_EQ(last_trade.trade.cond1, 12);
  EXPECT_EQ(last_trade.trade.cond2, 0);
  EXPECT_EQ(last_trade.trade.cond3, 0);
  EXPECT_EQ(last_trade.trade.cond4, 0);
  EXPECT_EQ(last_trade.trade.timestamp, 1588770424970329400);
}
