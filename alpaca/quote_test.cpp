#include "alpaca/quote.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class LastQuoteTest : public ::testing::Test {};

const std::string kLastQuoteJSON =
    "{"
    "\"status\": \"success\","
    "\"symbol\": \"SPY\","
    "\"last\": {"
    "\"askprice\": 279.1,"
    "\"asksize\": 1,"
    "\"askexchange\": 15,"
    "\"bidprice\": 287.05,"
    "\"bidsize\": 10,"
    "\"bidexchange\": 17,"
    "\"timestamp\": 1588770424970329400"
    "}"
    "}";

TEST_F(LastQuoteTest, testLastQuoteFromJSON) {
  alpaca::LastQuote last_quote;
  EXPECT_OK(last_quote.fromJSON(kLastQuoteJSON));
  EXPECT_EQ(last_quote.status, "success");
  EXPECT_EQ(last_quote.symbol, "SPY");
  EXPECT_EQ(last_quote.quote.ask_price, 279.1);
  EXPECT_EQ(last_quote.quote.ask_size, 1);
  EXPECT_EQ(last_quote.quote.ask_exchange, 15);
  EXPECT_EQ(last_quote.quote.bid_price, 287.05);
  EXPECT_EQ(last_quote.quote.bid_size, 10);
  EXPECT_EQ(last_quote.quote.bid_exchange, 17);
  EXPECT_EQ(last_quote.quote.timestamp, 1588770424970329400);
}
