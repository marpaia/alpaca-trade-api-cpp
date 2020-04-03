#pragma once

#include <string>

#include "alpaca/client.h"
#include "gtest/gtest.h"

#define EXPECT_OK(status)                                                                                              \
  EXPECT_TRUE(status.ok());                                                                                            \
  EXPECT_EQ(status.getMessage(), "OK");                                                                                \
  EXPECT_EQ(status.getCode(), 0)

#define EXPECT_NOT_OK(status)                                                                                          \
  EXPECT_FALSE(status.ok());                                                                                           \
  EXPECT_NE(status.getMessage(), "OK");                                                                                \
  EXPECT_NE(status.getCode(), 0)

namespace alpaca {

Client testClient();

std::string randomString(size_t length);

} // namespace alpaca