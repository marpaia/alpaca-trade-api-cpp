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

TEST_F(ClientTest, testGetAccountConfigurations) {
  auto client = testClient();
  auto get_account_configurations_resp = client.getAccountConfigurations();
  EXPECT_OK(get_account_configurations_resp.first);
  auto account_configurations = get_account_configurations_resp.second;

  auto update_account_configurations_resp =
      client.updateAccountConfigurations(false,
                                         account_configurations.dtbp_check,
                                         account_configurations.trade_confirm_email,
                                         account_configurations.suspend_trade);
  EXPECT_OK(update_account_configurations_resp.first);
  auto updated_account_configurations = update_account_configurations_resp.second;
  EXPECT_FALSE(updated_account_configurations.no_shorting);
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
  auto get_orders_response = client.getOrders(alpaca::ActionStatus::All, number_of_orders);
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

TEST_F(ClientTest, testPositions) {
  auto client = testClient();
  auto symbol = "NFLX";
  auto number_of_orders = 3;

  // liquidate all existing positions
  auto close_positions_response = client.closePositions();
  EXPECT_OK(close_positions_response.first);

  // submit orders
  for (int i = 0; i < number_of_orders; i++) {
    // submit a market order to buy 10 shares of NFLX
    auto submit_order_response = client.submitOrder(
        symbol, 10, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
    EXPECT_OK(submit_order_response.first);
  }

  // get all open positions
  auto get_positions_response = client.getPositions();
  EXPECT_OK(get_positions_response.first);
  auto positions = get_positions_response.second;
  EXPECT_GE(positions.size(), 1);

  // ensure there is an open position for the stock we just purchased
  auto found_symbol = false;
  alpaca::Position found_position;
  for (const auto& position : positions) {
    if (position.symbol == symbol) {
      found_symbol = true;
      found_position = position;
      break;
    }
  }
  EXPECT_TRUE(found_symbol);

  // directly retrieve the position for the stock we just purchased
  auto get_position_response = client.getPosition(symbol);
  EXPECT_OK(get_position_response.first);
  EXPECT_EQ(found_position.asset_id, get_position_response.second.asset_id);
}

TEST_F(ClientTest, testAssets) {
  auto client = testClient();
  auto symbol = "NFLX";
  auto number_of_orders = 3;

  // submit orders
  for (int i = 0; i < number_of_orders; i++) {
    // submit a market order to buy 10 shares of NFLX
    auto submit_order_response = client.submitOrder(
        symbol, 10, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
    EXPECT_OK(submit_order_response.first);
  }

  // get all open assets
  auto get_assets_response = client.getAssets();
  EXPECT_OK(get_assets_response.first);
  auto assets = get_assets_response.second;
  EXPECT_GE(assets.size(), 1);

  // ensure there is an asset for the stock we just purchased
  auto found_symbol = false;
  alpaca::Asset found_asset;
  for (const auto& asset : assets) {
    if (asset.symbol == symbol) {
      found_symbol = true;
      found_asset = asset;
      break;
    }
  }
  EXPECT_TRUE(found_symbol);

  // directly retrieve the asset for the stock we just purchased
  auto get_asset_response = client.getAsset(symbol);
  EXPECT_OK(get_asset_response.first);
  EXPECT_EQ(found_asset.id, get_asset_response.second.id);
}

TEST_F(ClientTest, testClock) {
  auto client = testClient();
  auto get_clock_response = client.getClock();
  EXPECT_OK(get_clock_response.first);
  auto clock = get_clock_response.second;
  EXPECT_NE(clock.next_open, "");
  EXPECT_NE(clock.next_close, "");
}