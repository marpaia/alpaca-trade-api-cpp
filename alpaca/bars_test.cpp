#include "alpaca/bars.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class BarTest : public ::testing::Test {};

const std::string kBarJSON =
    "{"
    "\"t\": 1544129220,"
    "\"o\": 172.26,"
    "\"h\": 172.3,"
    "\"l\": 172.16,"
    "\"c\": 172.18,"
    "\"v\": 3892"
    "}";

const std::string kBarsJSON =
    "{"
    "\"AAPL\": ["
    "{"
    "\"t\": 1544129220,"
    "\"o\": 172.26,"
    "\"h\": 172.3,"
    "\"l\": 172.16,"
    "\"c\": 172.18,"
    "\"v\": 3892"
    "}"
    "]"
    "}";

TEST_F(BarTest, testBarFromJSON) {
  alpaca::Bar bar;
  EXPECT_OK(bar.fromJSON(kBarJSON));
  EXPECT_EQ(bar.time, 1544129220);
  EXPECT_EQ(bar.open_price, 172.26);
  EXPECT_EQ(bar.high_price, 172.3);
  EXPECT_EQ(bar.low_price, 172.16);
  EXPECT_EQ(bar.close_price, 172.18);
  EXPECT_EQ(bar.volume, 3892);
}

TEST_F(BarTest, testBarsFromJSON) {
  alpaca::Bars bars;
  EXPECT_OK(bars.fromJSON(kBarsJSON));
  EXPECT_NE(bars.bars.find("AAPL"), bars.bars.end());
  auto bar = bars.bars["AAPL"][0];
  EXPECT_EQ(bar.time, 1544129220);
  EXPECT_EQ(bar.open_price, 172.26);
  EXPECT_EQ(bar.high_price, 172.3);
  EXPECT_EQ(bar.low_price, 172.16);
  EXPECT_EQ(bar.close_price, 172.18);
  EXPECT_EQ(bar.volume, 3892);
}