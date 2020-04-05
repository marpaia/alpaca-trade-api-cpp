#include "alpaca/watchlist.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class WatchlistTest : public ::testing::Test {};

const std::string kWatchlistJSON =
    "{"
    "\"account_id\": \"1d5493c9-ea39-4377-aa94-340734c368ae\","
    "\"assets\": ["
    "{"
    "\"class\": \"us_equity\","
    "\"easy_to_borrow\": true,"
    "\"exchange\": \"ARCA\","
    "\"id\": \"b28f4066-5c6d-479b-a2af-85dc1a8f16fb\","
    "\"marginable\": true,"
    "\"shortable\": true,"
    "\"status\": \"active\","
    "\"symbol\": \"SPY\","
    "\"tradable\": true"
    "},"
    "{"
    "\"class\": \"us_equity\","
    "\"easy_to_borrow\": false,"
    "\"exchange\": \"NASDAQ\","
    "\"id\": \"f801f835-bfe6-4a9d-a6b1-ccbb84bfd75f\","
    "\"marginable\": true,"
    "\"shortable\": false,"
    "\"status\": \"active\","
    "\"symbol\": \"AMZN\","
    "\"tradable\": true"
    "}"
    "],"
    "\"created_at\": \"2019-10-30T07:54:42.981322Z\","
    "\"id\": \"fb306e55-16d3-4118-8c3d-c1615fcd4c03\","
    "\"name\": \"Monday List\","
    "\"updated_at\": \"2019-10-30T07:54:42.981322Z\""
    "}";

TEST_F(WatchlistTest, testWatchlistJSON) {
  alpaca::Watchlist watchlist;
  EXPECT_OK(watchlist.fromJSON(kWatchlistJSON));
  EXPECT_EQ(watchlist.assets.size(), 2);
}
