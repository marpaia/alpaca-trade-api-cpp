#pragma once

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "alpaca/account.h"
#include "alpaca/asset.h"
#include "alpaca/bars.h"
#include "alpaca/calendar.h"
#include "alpaca/clock.h"
#include "alpaca/config.h"
#include "alpaca/order.h"
#include "alpaca/portfolio.h"
#include "alpaca/position.h"
#include "alpaca/quote.h"
#include "alpaca/status.h"
#include "alpaca/trade.h"
#include "alpaca/watchlist.h"

namespace alpaca {

/**
 * @brief The API client object for interacting with the Alpaca Trading API.
 *
 * @code{.cpp}
 *   auto env = alpaca::Environment();
 *   if (auto status = env.parse(); !status.ok()) {
 *     LOG(ERROR) << "Error parsing config from environment: "
 *                << status.getMessage();
 *     return status.getCode();
 *   }
 *   auto client = alpaca::Client(env);
 * @endcode
 */
class Client {
 public:
  /**
   * @brief The primary constructor.
   */
  explicit Client(Environment& environment);

  /**
   * @brief The default constructor of Client should never be used.
   */
  explicit Client() = delete;

  /**
   * @brief Fetch Alpaca account information.
   *
   * @code{.cpp}
   *   auto resp = client.getAccount();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting account information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto account = resp.second;
   *   LOG(INFO) << "ID: " << account.id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an
   * alpaca::Account object.
   */
  std::pair<Status, Account> getAccount() const;

  /**
   * @brief Fetch Alpaca account configuration information.
   *
   * @code{.cpp}
   *   auto resp = client.getAccountConfigurations();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting account information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto account_config = resp.second;
   *   if (accout_config.no_shorting) {
   *     LOG(WARNING) << "This account is not allowed to short!";
   *   }
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an
   * alpaca::AccountConfigurations object.
   */
  std::pair<Status, AccountConfigurations> getAccountConfigurations() const;

  /**
   * @brief Fetch Alpaca account activity.
   *
   * @code{.cpp}
   *   auto resp = client.getAccountActivity();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting account activity: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto account_activity = resp.second
   *   LOG(INFO) << "Found " << account_activity.size()
   *             << " elements of account activity.";
   * @endcode
   *
   * @param activity_types A list of string-based representations of activity
   * types. A full list of available activity types can be found on the docs:
   * https://alpaca.markets/docs/api-documentation/api-v2/account-activities/#activity-types
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is either an
   * alpaca::TradeActivity object or an alpaca::NonTradeActivity object.
   */
  std::pair<Status, std::vector<std::variant<TradeActivity, NonTradeActivity>>> getAccountActivity(
      const std::vector<std::string>& activity_types = {}) const;

  /**
   * @brief Update Alpaca account configuration information.
   *
   * @code{.cpp}
   *   auto resp = client.updateAccountConfigurations(true);
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error updating account information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an
   * alpaca::AccountConfigurations object.
   */
  std::pair<Status, AccountConfigurations> updateAccountConfigurations(const bool no_shorting,
                                                                       const std::string& dtbp_check,
                                                                       const std::string& trade_confirm_email,
                                                                       const bool suspend_trade) const;

  /**
   * @brief Fetch submitted Alpaca orders.
   *
   * @code{.cpp}
   *   auto resp = client.getOrders(alpaca::OrderStatus::All);
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting order information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto orders = resp.second;
   *   LOG(INFO) << "Number of orders: " << orders.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Order objects.
   */
  std::pair<Status, std::vector<Order>> getOrders(const ActionStatus status = ActionStatus::Open,
                                                  const int limit = 50,
                                                  const std::string& after = "",
                                                  const std::string& until = "",
                                                  const OrderDirection = OrderDirection::Descending,
                                                  const bool nested = false) const;

  /**
   * @brief Fetch a specific Alpaca order.
   *
   * @code{.cpp}
   *   auto resp = client.getOrder("6ad592c4-b3de-4517-a21c-13fdb184d65f");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting order information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto order = resp.second;
   *   LOG(INFO) << "Client order identifier: " << order.client_order_id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Order object.
   */
  std::pair<Status, Order> getOrder(const std::string& id, const bool nested = false) const;

  /**
   * @brief Fetch a specific Alpaca order by client order ID.
   *
   * @code{.cpp}
   *   auto resp = client.getOrderByClientOrderID("13901840-34e2-4175-9f42-e3d0302ab0ad");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting order information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto order = resp.second;
   *   LOG(INFO) << "Client order identifier: " << order.client_order_id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Order object.
   */
  std::pair<Status, Order> getOrderByClientOrderID(const std::string& client_order_id) const;

  /**
   * @brief Submit an Alpaca order.
   *
   * @code{.cpp}
   *   auto resp = client.submitOrder(
   *     "NFLX",
   *     10,
   *     alpaca::OrderSide::Buy,
   *     alpaca::OrderType::Market,
   *     alpaca::OrderTimeInForce::Day
   *   );
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error submitting order: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto order = resp.second;
   *   LOG(INFO) << "Client Order Identifier: " << order.client_order_id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is the newly
   * created alpaca::Order object.
   */
  std::pair<Status, Order> submitOrder(const std::string& symbol,
                                       const int quantity,
                                       const OrderSide side,
                                       const OrderType type,
                                       const OrderTimeInForce tif,
                                       const std::string& limit_price = "",
                                       const std::string& stop_price = "",
                                       const bool extended_hours = false,
                                       const std::string& client_order_id = "",
                                       const OrderClass order_class = OrderClass::Simple,
                                       TakeProfitParams* take_profit_params = nullptr,
                                       StopLossParams* stop_loss_params = nullptr) const;

  /**
   * @brief Replace an Alpaca order.
   *
   * @code{.cpp}
   *   auto resp = client.ReplaceOrder(
   *     "560fbbe6-16ce-41c6-b5b4-31a84646443a",
   *     10,
   *     alpaca::OrderTimeInForce::Day
   *   );
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error submitting order: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto order = resp.second;
   *   LOG(INFO) << "Client Order Identifier: " << order.client_order_id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is the newly
   * created alpaca::Order object.
   */
  std::pair<Status, Order> replaceOrder(const std::string& id,
                                        const int quantity,
                                        const OrderTimeInForce tif,
                                        const std::string& limit_price = "",
                                        const std::string& stop_price = "",
                                        const std::string& client_order_id = "") const;

  /**
   * @brief Cancel all Alpaca orders.
   *
   * @code{.cpp}
   *   auto resp = client.cancelOrders();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error cancelling orders: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto orders = resp.second;
   *   LOG(INFO) << "Number of orders: " << orders.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Order objects.
   */
  std::pair<Status, std::vector<Order>> cancelOrders() const;

  /**
   * @brief Cancel a specific Alpaca order.
   *
   * @code{.cpp}
   *   auto resp = client.cancelOrder("6ad592c4-b3de-4517-a21c-13fdb184d65f");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error cancelling order: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto order = resp.second;
   *   LOG(INFO) << "Order identifier: " << order.id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Order object.
   */
  std::pair<Status, Order> cancelOrder(const std::string& id) const;

  /**
   * @brief Fetch all open Alpaca positions.
   *
   * @code{.cpp}
   *   auto resp = client.getPositions();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting position information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto positions = resp.second;
   *   LOG(INFO) << "Number of positions: " << positions.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Position objects.
   */
  std::pair<Status, std::vector<Position>> getPositions() const;

  /**
   * @brief Fetch a position for a given symbol.
   *
   * @code{.cpp}
   *   auto resp = client.getPosition("NFLX");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting position information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto position = resp.second;
   *   LOG(INFO) << "Asset class: " << position.asset_class;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Position object.
   */
  std::pair<Status, Position> getPosition(const std::string& symbol) const;

  /**
   * @brief Close (liquidate) all Alpaca positions.
   *
   * @code{.cpp}
   *   auto resp = client.closePositions();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error closing positions: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto positions = resp.second;
   *   LOG(INFO) << "Number of positions: " << positions.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Position objects.
   */
  std::pair<Status, std::vector<Position>> closePositions() const;

  /**
   * @brief Close (liquidate) the position for a given symbol.
   *
   * @code{.cpp}
   *   auto resp = client.closePosition("NFLX");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error closing position: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto position = resp.second;
   *   LOG(INFO) << "Asset identifier: " << position.asset_id;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Position object.
   */
  std::pair<Status, Position> closePosition(const std::string& symbol) const;

  /**
   * @brief Fetch all open Alpaca assets.
   *
   * @code{.cpp}
   *   auto resp = client.getAssets();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting asset information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto assets = resp.second;
   *   LOG(INFO) << "Number of assets: " << assets.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Asset objects.
   */
  std::pair<Status, std::vector<Asset>> getAssets(const ActionStatus asset_status = ActionStatus::Active,
                                                  const AssetClass asset_class = AssetClass::USEquity) const;

  /**
   * @brief Fetch an asset for a given symbol.
   *
   * @code{.cpp}
   *   auto resp = client.getAsset("NFLX");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting asset information: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto asset = resp.second;
   *   LOG(INFO) << "Asset class: " << asset.asset_class;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Asset object.
   */
  std::pair<Status, Asset> getAsset(const std::string& symbol) const;

  /**
   * @brief Fetch the market clock.
   *
   * @code{.cpp}
   *   auto resp = client.getClock();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting the market clock: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto clock = resp.second;
   *   LOG(INFO) << "Next open: " << clock.next_open;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Clock object.
   */
  std::pair<Status, Clock> getClock() const;

  /**
   * @brief Fetch calendar data.
   *
   * @code{.cpp}
   *   auto resp = client.getCalendar("2018-01-02", "2018-01-09");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting the market calendar data: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto dates = resp.second;
   *   for (const auto& date : dates) {
   *     LOG(INFO) << "Market opened at " << date.open
   *               << " and closed at " << date.close
   *               << " on " << date.date;
   *   }
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is vector of
   * alpaca::Calendar objects.
   */
  std::pair<Status, std::vector<Date>> getCalendar(const std::string& start, const std::string& end) const;

  /**
   * @brief Fetch watchlists.
   *
   * @code{.cpp}
   *   auto resp = client.getWatchlists();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting watchlists: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlists = resp.second;
   *   LOG(INFO) << "Number of watchlists: " << watchlists.size();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is a vector of
   * alpaca::Watchlist objects.
   */
  std::pair<Status, std::vector<Watchlist>> getWatchlists() const;

  /**
   * @brief Fetch a watchlist by ID.
   *
   * @code{.cpp}
   *   auto resp = client.getWatchlist("6ad592c4-b3de-4517-a21c-13fdb184d65f");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlist = resp.second;
   *   LOG(INFO) << "Watchlist name: " << watchlist.name;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Watchlist object.
   */
  std::pair<Status, Watchlist> getWatchlist(const std::string& id) const;

  /**
   * @brief Create a watchlist.
   *
   * @code{.cpp}
   *   auto resp = client.createWatchlist("Stocks To Watch", std::vector<std::string>{"AAPL", "GOOG"});
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error creating watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlist = resp.second;
   *   LOG(INFO) << "Watchlist name: " << watchlist.name;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Watchlist object.
   */
  std::pair<Status, Watchlist> createWatchlist(const std::string& name, const std::vector<std::string>& symbols) const;

  /**
   * @brief Update a watchlist.
   *
   * @code{.cpp}
   *   auto resp = client.updateWatchlist("6ad592c4-b3de-4517-a21c-13fdb184d65f",
   *                                      "Stocks To Watch",
   *                                      std::vector<std::string>{"FB", "GOOG"});
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error updating watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlist = resp.second;
   *   LOG(INFO) << "Watchlist name: " << watchlist.name;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Watchlist object.
   */
  std::pair<Status, Watchlist> updateWatchlist(const std::string& id,
                                               const std::string& name,
                                               const std::vector<std::string>& symbols) const;

  /**
   * @brief Delete a watchlist.
   *
   * @code{.cpp}
   *   auto status = client.deleteWatchlist("6ad592c4-b3de-4517-a21c-13fdb184d65f")
   *   if (!status.ok()) {
   *     LOG(ERROR) << "Error deleting watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   * @endcode
   *
   * @return a Status indicating the success or faliure of the operation
   */
  Status deleteWatchlist(const std::string& id) const;

  /**
   * @brief Add an asset to a watchlist.
   *
   * @code{.cpp}
   *   auto resp = client.addSymbolToWatchlist("6ad592c4-b3de-4517-a21c-13fdb184d65f", "NFLX")
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error adding asset to watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlist = resp.second;
   *   LOG(INFO) << "Watchlist name: " << watchlist.name;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Watchlist object.
   */
  std::pair<Status, Watchlist> addSymbolToWatchlist(const std::string& id, const std::string& symbol) const;

  /**
   * @brief Remove an asset from a watchlist.
   *
   * @code{.cpp}
   *   auto resp = client.removeAssetFromWatchlist("6ad592c4-b3de-4517-a21c-13fdb184d65f", "NFLX")
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error removing asset from watchlist: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto watchlist = resp.second;
   *   LOG(INFO) << "Watchlist name: " << watchlist.name;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Watchlist object.
   */
  std::pair<Status, Watchlist> removeSymbolFromWatchlist(const std::string& id, const std::string& symbol) const;

  /**
   * @brief Fetch portfolio history data.
   *
   * @code{.cpp}
   *   auto resp = client.getPortfolioHistory();
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting portfolio history: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto portfolio_history = resp.second;
   *   LOG(INFO) << "Latest equity value: " << portfolio_history.equity.back();
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::PortfolioHistory object.
   */
  std::pair<Status, PortfolioHistory> getPortfolioHistory(const std::string& period = "",
                                                          const std::string& timeframe = "",
                                                          const std::string& date_end = "",
                                                          const bool extended_hours = false) const;

  /**
   * @brief Fetch historical performance data.
   *
   * @code{.cpp}
   *   auto resp = client.getBars({"AAPL", "GOOG"}, "2020-04-01T09:30:00-04:00", "2020-04-07T09:30:00-04:00");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting bars: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto bars = resp.second;
   *   for (auto iter = bars.bars.begin(); iter != bars.bars.end(); ++iter) {
   *     LOG(INFO) << "Got " << iter->second.size() << " bars for " << iter->first << ".";
   *   }
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::Bars object.
   */
  std::pair<Status, Bars> getBars(const std::vector<std::string>& symbols,
                                  const std::string& start,
                                  const std::string& end,
                                  const std::string& after = "",
                                  const std::string& until = "",
                                  const std::string& timeframe = "1D",
                                  const uint limit = 100) const;

  /**
   * @brief Fetch last trade details for a symbol.
   *
   * @code{.cpp}
   *   auto resp = client.getLastTrade("SPY");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting last trade: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto last_trade = resp.second;
   *   LOG(INFO) << "Latest price: " << last_trade.trade.price;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::LastTrade object.
   */
  std::pair<Status, LastTrade> getLastTrade(const std::string& symbol) const;

  /**
   * @brief Fetch last quote details for a symbol.
   *
   * @code{.cpp}
   *   auto resp = client.getLastQuote("SPY");
   *   if (auto status = resp.first; !status.ok()) {
   *     LOG(ERROR) << "Error getting last quote: "
   *                << status.getMessage();
   *     return status.getCode();
   *   }
   *   auto last_quote = resp.second;
   *   LOG(INFO) << "Latest ask price: " << last_quote.quote.ask_price;
   * @endcode
   *
   * @return a std::pair where the first elemennt is a Status indicating the
   * success or faliure of the operation and the second element is an instance
   * of an alpaca::LastQuote object.
   */
  std::pair<Status, LastQuote> getLastQuote(const std::string& symbol) const;

 private:
  Environment environment_;
};
} // namespace alpaca