#include "alpaca/clock.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {
Status Clock::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing clock JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a clock object");
  }

  PARSE_BOOL(is_open, "is_open")
  PARSE_STRING(next_close, "next_close")
  PARSE_STRING(next_open, "next_open")
  PARSE_STRING(timestamp, "timestamp")

  return Status();
}
} // namespace alpaca