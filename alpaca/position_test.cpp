#include "alpaca/position.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class PositionTest : public ::testing::Test {};

const std::string kPositionJSON =
    "{"
    "\"asset_id\": \"904837e3-3b76-47ec-b432-046db621571b\","
    "\"symbol\": \"AAPL\","
    "\"exchange\": \"NASDAQ\","
    "\"asset_class\": \"us_equity\","
    "\"avg_entry_price\": \"100.0\","
    "\"qty\": \"5\","
    "\"side\": \"long\","
    "\"market_value\": \"600.0\","
    "\"cost_basis\": \"500.0\","
    "\"unrealized_pl\": \"100.0\","
    "\"unrealized_plpc\": \"0.20\","
    "\"unrealized_intraday_pl\": \"10.0\","
    "\"unrealized_intraday_plpc\": \"0.0084\","
    "\"current_price\": \"120.0\","
    "\"lastday_price\": \"119.0\","
    "\"change_today\": \"0.0084\""
    "}";

TEST_F(PositionTest, testAccountConfigurationFromJSON) {
  alpaca::Position position;
  EXPECT_OK(position.fromJSON(kPositionJSON));
  EXPECT_EQ(position.exchange, "NASDAQ");
}