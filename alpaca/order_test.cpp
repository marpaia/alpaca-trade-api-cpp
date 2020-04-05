#include "alpaca/order.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class OrderTest : public ::testing::Test {};

const std::string kOrderJSON =
    "{"
    "\"id\": \"904837e3-3b76-47ec-b432-046db621571b\","
    "\"client_order_id\": \"904837e3-3b76-47ec-b432-046db621571b\","
    "\"created_at\": \"2018-10-05T05:48:59Z\","
    "\"updated_at\": \"2018-10-05T05:48:59Z\","
    "\"submitted_at\": \"2018-10-05T05:48:59Z\","
    "\"filled_at\": \"2018-10-05T05:48:59Z\","
    "\"expired_at\": \"2018-10-05T05:48:59Z\","
    "\"canceled_at\": \"2018-10-05T05:48:59Z\","
    "\"failed_at\": \"2018-10-05T05:48:59Z\","
    "\"asset_id\": \"904837e3-3b76-47ec-b432-046db621571b\","
    "\"symbol\": \"AAPL\","
    "\"asset_class\": \"us_equity\","
    "\"qty\": \"15\","
    "\"filled_qty\": \"0\","
    "\"type\": \"market\","
    "\"side\": \"buy\","
    "\"time_in_force\": \"day\","
    "\"limit_price\": \"107.00\","
    "\"stop_price\": \"106.00\","
    "\"filled_avg_price\": \"106.00\","
    "\"status\": \"accepted\","
    "\"extended_hours\": false,"
    "\"legs\": null"
    "}";

TEST_F(OrderTest, testOrderFromJSON) {
  alpaca::Order order;
  EXPECT_OK(order.fromJSON(kOrderJSON));
  EXPECT_EQ(order.symbol, "AAPL");
}
