#include "alpaca/client.h"

#include <utility>

#include "glog/logging.h"
#include "httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace alpaca {

const char* kJSONContentType = "application/json";

httplib::Headers headers(const Environment& environment) {
  return {
      {"APCA-API-KEY-ID", environment.getAPIKeyID()},
      {"APCA-API-SECRET-KEY", environment.getAPISecretKey()},
  };
}

Client::Client(Environment& environment) {
  if (!environment.hasBeenParsed()) {
    if (auto s = environment.parse(); !s.ok()) {
      LOG(ERROR) << "Error parsing the environment: " << s.getMessage();
    }
  }
  environment_ = environment;
}

std::pair<Status, Account> Client::getAccount() const {
  Account account;

  httplib::SSLClient client(environment_.getAPIBaseURL());
  auto resp = client.Get("/v2/account", headers(environment_));
  if (!resp) {
    return std::make_pair(Status(1, "Call to /v2/account returned an empty response"), account);
  }

  if (resp->status != 200) {
    std::ostringstream ss;
    ss << "Call to /v2/account returned an HTTP " << resp->status << ": " << resp->body;
    return std::make_pair(Status(1, ss.str()), account);
  }

  DLOG(INFO) << "Response from /v2/account: " << resp->body;
  return std::make_pair(account.fromJSON(resp->body), account);
}

std::pair<Status, std::vector<Order>> Client::getOrders(const OrderStatus status,
                                                        const int limit,
                                                        const std::string& after,
                                                        const std::string& until,
                                                        const OrderDirection direction,
                                                        const bool nested) const {
  std::vector<Order> orders;

  httplib::Params params{
      {"status", orderStatusToString(status)},
      {"limit", std::to_string(limit)},
      {"direction", orderDirectionToString(direction)},
  };
  if (after != "") {
    params.insert({"after", after});
  }
  if (until != "") {
    params.insert({"until", until});
  }
  if (nested) {
    params.insert({"nested", "true"});
  }
  auto query_string = httplib::detail::params_to_query_str(params);
  httplib::SSLClient client(environment_.getAPIBaseURL());
  auto url = "/v2/orders?" + query_string;
  DLOG(INFO) << "Making request to: " << url;
  auto resp = client.Get(url.c_str(), headers(environment_));
  if (!resp) {
    return std::make_pair(Status(1, "Call to /v2/orders returned an empty response"), orders);
  }

  if (resp->status != 200) {
    std::ostringstream ss;
    ss << "Call to /v2/orders returned an HTTP " << resp->status << ": " << resp->body;
    return std::make_pair(Status(1, ss.str()), orders);
  }

  DLOG(INFO) << "Response from /v2/orders: " << resp->body;

  rapidjson::Document d;
  if (d.Parse(resp->body.c_str()).HasParseError()) {
    return std::make_pair(Status(1, "Received parse error when deserializing orders JSON"), orders);
  }
  for (auto& o : d.GetArray()) {
    Order order;
    rapidjson::StringBuffer s;
    s.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    o.Accept(writer);
    if (auto status = order.fromJSON(s.GetString()); !status.ok()) {
      return std::make_pair(status, orders);
    }
    orders.push_back(order);
  }

  return std::make_pair(Status(), orders);
}

std::pair<Status, Order> Client::submitOrder(const std::string& symbol,
                                             const int quantity,
                                             const OrderSide side,
                                             const OrderType type,
                                             const OrderTimeInForce tif,
                                             const std::string& limit_price,
                                             const std::string& stop_price,
                                             const bool extended_hours,
                                             const std::string& client_order_id,
                                             const OrderClass order_class,
                                             TakeProfitParams* take_profit_params,
                                             StopLossParams* stop_loss_params) const {
  Order order;

  rapidjson::StringBuffer s;
  s.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartObject();

  writer.Key("symbol");
  writer.String(symbol.c_str());

  writer.Key("qty");
  writer.Int(quantity);

  writer.Key("side");
  writer.String(orderSideToString(side).c_str());

  writer.Key("type");
  writer.String(orderTypeToString(type).c_str());

  writer.Key("time_in_force");
  writer.String(orderTimeInForceToString(tif).c_str());

  if (limit_price != "") {
    writer.Key("limit_price");
    writer.String(limit_price.c_str());
  }

  if (stop_price != "") {
    writer.Key("stop_price");
    writer.String(stop_price.c_str());
  }

  if (extended_hours) {
    writer.Key("extended_hours");
    writer.Bool(extended_hours);
  }

  if (client_order_id != "") {
    writer.Key("client_order_id");
    writer.String(client_order_id.c_str());
  }

  if (order_class != OrderClass::Simple) {
    writer.Key("order_class");
    writer.String(orderClassToString(order_class).c_str());
  }

  if (take_profit_params != nullptr) {
    writer.Key("take_profit");
    writer.StartObject();
    if (take_profit_params->limitPrice != "") {
      writer.Key("limit_price");
      writer.String(take_profit_params->limitPrice.c_str());
    }
    writer.EndObject();
  }

  if (stop_loss_params != nullptr) {
    writer.Key("stop_loss");
    writer.StartObject();
    if (stop_loss_params->limitPrice != "") {
      writer.Key("limit_price");
      writer.String(stop_loss_params->limitPrice.c_str());
    }
    if (stop_loss_params->stopPrice != "") {
      writer.Key("stop_price");
      writer.String(stop_loss_params->stopPrice.c_str());
    }
    writer.EndObject();
  }

  writer.EndObject();
  auto body = s.GetString();

  DLOG(INFO) << "Sending request body to /v2/orders: " << body;

  httplib::SSLClient client(environment_.getAPIBaseURL());
  auto resp = client.Post("/v2/orders", headers(environment_), body, kJSONContentType);
  if (!resp) {
    return std::make_pair(Status(1, "Call to /v2/orders returned an empty response"), order);
  }

  if (resp->status != 200) {
    std::ostringstream ss;
    ss << "Call to /v2/orders returned an HTTP " << resp->status << ": " << resp->body;
    return std::make_pair(Status(1, ss.str()), order);
  }

  return std::make_pair(order.fromJSON(resp->body), order);
}

} // namespace alpaca