#include "alpaca/client.h"

#include <utility>

#include "glog/logging.h"
#include "httplib.h"

namespace alpaca {

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

Status Client::getAccount(Account& account) const {
  httplib::SSLClient client(environment_.getAPIBaseURL());
  auto resp = client.Get("/v2/account", headers(environment_));
  if (!resp) {
    return Status(1, "Call to /v2/account returned an empty response");
  }
  if (resp->status != 200) {
    std::ostringstream ss;
    ss << "Call to /v2/account returned an HTTP " << resp->status << ": " << resp->body;
    return Status(1, ss.str());
  }

  DLOG(INFO) << "Response from /v2/account: " << resp->body;
  return account.fromJSON(resp->body);
}

} // namespace alpaca