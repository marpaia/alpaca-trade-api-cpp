#pragma once

#include "alpaca/client.h"
#include "gtest/gtest.h"

#define EXPECT_OK(status)                                                                                              \
  EXPECT_TRUE(status.ok());                                                                                            \
  EXPECT_EQ(status.getMessage(), "OK");                                                                                \
  EXPECT_EQ(status.getCode(), 0)

alpaca::Client testClient() {
  auto env = alpaca::Environment();
  auto parse_status = env.parse();
  EXPECT_OK(parse_status);
  return alpaca::Client(env);
}