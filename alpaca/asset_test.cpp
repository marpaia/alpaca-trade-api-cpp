#include "alpaca/asset.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class AssetTest : public ::testing::Test {};

const std::string kAssetJSON =
    "{"
    "\"id\": \"904837e3-3b76-47ec-b432-046db621571b\","
    "\"class\": \"us_equity\","
    "\"exchange\": \"NASDAQ\","
    "\"symbol\": \"AAPL\","
    "\"status\": \"active\","
    "\"tradable\": true,"
    "\"marginable\": true,"
    "\"shortable\": true,"
    "\"easy_to_borrow\": true"
    "}";

TEST_F(AssetTest, testAssetFromJSON) {
  alpaca::Asset asset;
  EXPECT_OK(asset.fromJSON(kAssetJSON));
  EXPECT_EQ(asset.symbol, "AAPL");
}
