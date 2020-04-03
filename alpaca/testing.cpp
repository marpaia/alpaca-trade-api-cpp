#include "alpaca/testing.h"

#include <random>

namespace alpaca {

alpaca::Client testClient() {
  auto env = alpaca::Environment();
  auto parse_status = env.parse();
  EXPECT_OK(parse_status);
  return alpaca::Client(env);
}

std::string randomString(size_t length) {
  static auto& chrs =
      "0123456789"
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  thread_local static std::mt19937 rg{std::random_device{}()};
  thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

  std::string s;
  s.reserve(length);

  while (length--) {
    s += chrs[pick(rg)];
  }

  return s;
}
} // namespace alpaca