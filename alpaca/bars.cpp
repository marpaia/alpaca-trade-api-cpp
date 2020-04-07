#include "alpaca/bars.h"

#include "alpaca/json.h"
#include "glog/logging.h"
#include "rapidjson/document.h"

namespace alpaca {

Status Bar::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing bar JSON");
  }

  return fromDocument(d);
}

Status Bar::fromDocument(
    const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& d) {
  PARSE_UINT(time, "t")
  PARSE_DOUBLE(open_price, "o")
  PARSE_DOUBLE(high_price, "h")
  PARSE_DOUBLE(low_price, "l")
  PARSE_DOUBLE(close_price, "c")
  PARSE_UINT(volume, "v")

  return Status();
}

Status Bars::fromJSON(const std::string& json) {
  rapidjson::Document d;
  if (d.Parse(json.c_str()).HasParseError()) {
    return Status(1, "Received parse error when deserializing bars JSON");
  }

  if (!d.IsObject()) {
    return Status(1, "Deserialized valid JSON but it wasn't bars object");
  }

  for (auto symbol_bars = d.MemberBegin(); symbol_bars != d.MemberEnd(); symbol_bars++) {
    bars[symbol_bars->name.GetString()] = std::vector<Bar>{};
    for (auto& symbol_bar : symbol_bars->value.GetArray()) {
      Bar bar;
      if (auto status = bar.fromDocument(symbol_bar.GetObject()); !status.ok()) {
        return status;
      }
      bars[symbol_bars->name.GetString()].push_back(bar);
    }
  }

  return Status();
}
} // namespace alpaca