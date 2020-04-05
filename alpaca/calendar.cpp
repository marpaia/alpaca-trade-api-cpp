#include "alpaca/calendar.h"

#include "alpaca/json.h"
#include "rapidjson/document.h"

namespace alpaca {
Status Date::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing calendar JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't a calendar object");
  }

  PARSE_STRING(close, "close")
  PARSE_STRING(date, "date")
  PARSE_STRING(open, "open")

  return Status();
}
} // namespace alpaca