#include "alpaca/client.h"

#include <utility>

#include "absl/strings/str_format.h"
#include "glog/logging.h"
#include "httplib.h"

namespace alpaca {
Client::Client(Environment& environment) {
  if (!environment.hasBeenParsed()) {
    if (auto s = environment.parse(); !s.ok()) {
      LOG(ERROR) << "error parsing the environment: " << s.getMessage();
    }
  }
  environment_ = environment;
}

httplib::Headers Client::headers() const {
  return {
      {"APCA-API-KEY-ID", environment_.getAPIKeyID()},
      {"APCA-API-SECRET-KEY", environment_.getAPISecretKey()},
  };
}

Status Client::getAccount(Account& account) const {
  httplib::SSLClient client(environment_.getAPIBaseURL());
  std::string body;
  auto resp = client.Get("/v2/account", headers());
  if (!resp) {
    return Status(1, "Call to /v2/account returned an empty response");
  }
  if (resp->status != 200) {
    return Status(1, absl::StrFormat("Call to /v2/account returned an HTTP %d: %s", resp->status, resp->body));
  }

  DLOG(INFO) << "Response from /v2/account: " << resp->body;
  return account.fromJSON(resp->body);
}
} // namespace alpaca