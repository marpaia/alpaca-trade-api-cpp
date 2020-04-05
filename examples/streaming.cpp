#include <chrono>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include "Group.h"
#include "alpaca/config.h"
#include "alpaca/streaming.h"
#include "glog/logging.h"
#include "uWS.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  LOG(INFO) << "Starting streaming example";

  auto env = alpaca::Environment();
  if (auto status = env.parse(); !status.ok()) {
    LOG(ERROR) << "Error parsing environment: " << status.getMessage();
    return status.getCode();
  }
  auto m = alpaca::MessageHelper();
  std::string authentication = m.authentication(env.getAPIKeyID(), env.getAPISecretKey());

  uWS::Hub hub;
  auto group = hub.createGroup<uWS::CLIENT>();

  group->onConnection([authentication](uWS::WebSocket<uWS::CLIENT>* ws, uWS::HttpRequest req) {
    LOG(INFO) << "Received connection event";

    LOG(INFO) << "Sending authenticate message";
    ws->send(authentication.data(), authentication.size(), uWS::OpCode::TEXT);
  });

  group->onMessage([m](uWS::WebSocket<uWS::CLIENT>* ws, char* message, size_t length, uWS::OpCode opCode) {
    auto text = std::string(message, length);
    LOG(INFO) << "Got reply: " << text;

    if (text.find("authorized") != std::string::npos) {
      auto listen = m.listen({alpaca::TradeUpdates, alpaca::AccountUpdates});
      LOG(INFO) << "Sending listen message: " << listen;
      ws->send(listen.data(), listen.size(), uWS::OpCode::TEXT);
    }
  });

  group->onDisconnection([](uWS::WebSocket<uWS::CLIENT>* ws, int code, char* message, size_t length) {
    LOG(INFO) << "Received disconnection event: " << std::string(message, length);
  });

  group->onError([](void* e) { LOG(ERROR) << "Received error."; });

  hub.connect("wss://paper-api.alpaca.markets/stream", nullptr, {}, 5000, group);
  hub.run();

  return 0;
}