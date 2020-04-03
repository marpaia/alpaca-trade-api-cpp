#include <thread>

#include "alpaca/client.h"
#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class ClientTest : public ::testing::Test {};

TEST_F(ClientTest, testGetAccount) {
  auto client = testClient();
  auto resp = client.getAccount();
  EXPECT_OK(resp.first);
  auto account = resp.second;
  EXPECT_EQ(account.status, "ACTIVE");
}

TEST_F(ClientTest, testOrders) {
  auto client = testClient();
  auto number_of_orders = 3;

  // cancel any existing orders
  auto cancel_orders_response = client.cancelOrders();
  EXPECT_OK(cancel_orders_response.first);

  // submit orders and validate each can be individually retrieved
  for (int i = 0; i < number_of_orders; i++) {
    // submit a market order to buy 10 shares of NFLX
    auto submit_order_response = client.submitOrder(
        "NFLX", 10, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
    EXPECT_OK(submit_order_response.first);
    auto order = submit_order_response.second;
    EXPECT_NE(order.id, "");

    // use the Alpaca API to retrieve the order we just submitted
    auto get_order_response = client.getOrder(order.id);
    EXPECT_OK(get_order_response.first);
    auto order_alt = get_order_response.second;

    // validate the response from the order creation and the response from
    // order retrieval have the same id and client order id
    EXPECT_EQ(order.client_order_id, order_alt.client_order_id);
    EXPECT_EQ(order.id, order_alt.id);
  }

  // enumerate all orders and make sure we have at least ten
  auto get_orders_response = client.getOrders(alpaca::OrderStatus::All, number_of_orders);
  EXPECT_OK(get_orders_response.first);
  auto orders = get_orders_response.second;
  EXPECT_EQ(orders.size(), number_of_orders);

  for (const auto& order : orders) {
    // validate that all orders in the response have required fields
    EXPECT_NE(order.id, "");
    EXPECT_NE(order.client_order_id, "");

    // cancel the order by id
    auto cancel_order_response = client.cancelOrder(order.id);
    EXPECT_OK(cancel_order_response.first);
    EXPECT_EQ(cancel_order_response.second.id, order.id);
  }
}