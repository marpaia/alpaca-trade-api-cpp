#include <variant>

#include "alpaca/client.h"
#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class ClientTest : public ::testing::Test {};

TEST_F(ClientTest, testGetAccount) {
  auto client = alpaca::testClient();
  auto resp = client.getAccount();
  EXPECT_OK(resp.first);
  auto account = resp.second;
  EXPECT_EQ(account.status, "ACTIVE");
}

TEST_F(ClientTest, testGetAccountConfigurations) {
  auto client = alpaca::testClient();
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

TEST_F(ClientTest, testGetAccountActivity) {
  auto client = alpaca::testClient();
  auto get_account_activity_resp = client.getAccountActivity();
  EXPECT_OK(get_account_activity_resp.first);
  auto activities = get_account_activity_resp.second;
  for (const auto& activity : activities) {
    auto found = false;
    try {
      auto typed_activity = std::get<alpaca::TradeActivity>(activity);
      found = true;
    } catch (const std::bad_variant_access&) {
    }
    try {
      auto typed_activity = std::get<alpaca::NonTradeActivity>(activity);
      found = true;
    } catch (const std::bad_variant_access&) {
    }
    EXPECT_TRUE(found);
  }
}

TEST_F(ClientTest, testOrders) {
  auto client = alpaca::testClient();
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
  auto client = alpaca::testClient();
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
  auto client = alpaca::testClient();
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
  auto client = alpaca::testClient();
  auto get_clock_response = client.getClock();
  EXPECT_OK(get_clock_response.first);
  auto clock = get_clock_response.second;
  EXPECT_NE(clock.next_open, "");
  EXPECT_NE(clock.next_close, "");
}

TEST_F(ClientTest, testCalendar) {
  auto client = alpaca::testClient();
  auto get_calendar_response = client.getCalendar("2018-01-02", "2018-01-09");
  EXPECT_OK(get_calendar_response.first);
  auto dates = get_calendar_response.second;
  for (const auto& date : dates) {
    EXPECT_NE(date.date, "");
    EXPECT_NE(date.open, "");
    EXPECT_NE(date.close, "");
  }
}

TEST_F(ClientTest, testWatchlists) {
  auto client = alpaca::testClient();

  // create a test watchlist
  auto create_watchlist_response = client.createWatchlist(
      "My Test Watchlist - " + alpaca::randomString(24),
      std::vector<std::string>{"GOOG", "WORK", "MSFT", "AAPL", "FB", "NFLX", "TSLA", "TWTR", "NOW", "DIS"});
  EXPECT_OK(create_watchlist_response.first);
  auto watchlist = create_watchlist_response.second;
  EXPECT_NE(watchlist.id, "");
  EXPECT_GT(watchlist.assets.size(), 0);

  // update the symbols in the test watchlist
  auto update_watchlist_response = client.updateWatchlist(watchlist.id, watchlist.name, std::vector<std::string>{"FB"});
  EXPECT_OK(update_watchlist_response.first);
  watchlist = update_watchlist_response.second;
  EXPECT_NE(watchlist.id, "");
  EXPECT_EQ(watchlist.assets.size(), 1);

  // add a symbol to the watchlist
  auto add_symbol_response = client.addSymbolToWatchlist(watchlist.id, "GOOG");
  EXPECT_OK(add_symbol_response.first);
  watchlist = add_symbol_response.second;
  EXPECT_NE(watchlist.id, "");
  EXPECT_EQ(watchlist.assets.size(), 2);

  // remove a symbol from the watchliist
  auto remove_symbol_response = client.removeSymbolFromWatchlist(watchlist.id, "GOOG");
  EXPECT_OK(remove_symbol_response.first);
  watchlist = remove_symbol_response.second;
  EXPECT_NE(watchlist.id, "");
  EXPECT_EQ(watchlist.assets.size(), 1);

  // delete the watchlist
  auto delete_watchlist_response = client.deleteWatchlist(watchlist.id);
  EXPECT_OK(delete_watchlist_response);
}

TEST_F(ClientTest, testPortfolioHistory) {
  auto client = alpaca::testClient();
  auto get_portfolio_history_response = client.getPortfolioHistory();
  EXPECT_OK(get_portfolio_history_response.first);
  auto portfolio_history = get_portfolio_history_response.second;
  EXPECT_GT(portfolio_history.base_value, 0.0);
  EXPECT_GT(portfolio_history.equity.size(), 0);
  EXPECT_GT(portfolio_history.profit_loss.size(), 0);
  EXPECT_GT(portfolio_history.profit_loss_pct.size(), 0);
  EXPECT_NE(portfolio_history.timeframe, "");
  EXPECT_GT(portfolio_history.timestamp.size(), 0);
}

TEST_F(ClientTest, testBars) {
  auto client = alpaca::testClient();
  auto bars_resp = client.getBars({"AAPL", "GOOG"}, "2020-04-01T09:30:00-04:00", "2020-04-03T09:30:00-04:00");
  EXPECT_OK(bars_resp.first);
  auto bars = bars_resp.second;
  for (auto it = bars.bars.begin(); it != bars.bars.end(); ++it) {
    EXPECT_NE(it->first, "");
    EXPECT_EQ(it->second.size(), 3);
  }
}

TEST_F(ClientTest, testLastTrade) {
  auto client = alpaca::testClient();
  auto last_trade_resp = client.getLastTrade("SPY");
  EXPECT_OK(last_trade_resp.first);
  auto last_trade = last_trade_resp.second;
  EXPECT_EQ(last_trade.symbol, "SPY");
}

TEST_F(ClientTest, testLastQuote) {
  auto client = alpaca::testClient();
  auto last_quote_resp = client.getLastQuote("SPY");
  EXPECT_OK(last_quote_resp.first);
  auto last_quote = last_quote_resp.second;
  EXPECT_EQ(last_quote.symbol, "SPY");
}