#pragma once

#include <string>
#include <utility>
#include <vector>

#include "alpaca/account.h"
#include "alpaca/asset.h"
#include "alpaca/config.h"
#include "alpaca/order.h"
#include "alpaca/position.h"
#include "alpaca/status.h"

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
  std::pair<Status, std::vector<Order>> getOrders(const OrderStatus status = OrderStatus::Open,
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
  std::pair<Status, std::vector<Asset>> getAssets() const;

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

 private:
  Environment environment_;
};
} // namespace alpaca