#include <thread>

#include "alpaca/status.h"
#include "alpaca/testing.h"
#include "gtest/gtest.h"

class StatusTest : public ::testing::Test {};

TEST_F(StatusTest, testStatusConstructor) {
  auto status = alpaca::Status();
  EXPECT_OK(status);
}
