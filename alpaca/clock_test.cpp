#include "alpaca/clock.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class ClockTest : public ::testing::Test {};

const std::string kClockJSON =
    "{"
    "\"timestamp\": \"2018-04-01T12:00:00.000Z\","
    "\"is_open\": true,"
    "\"next_open\": \"2018-04-01T12:00:00.000Z\","
    "\"next_close\": \"2018-04-01T12:00:00.000Z\""
    "}";

TEST_F(ClockTest, testClockFromJSON) {
  alpaca::Clock clock;
  EXPECT_OK(clock.fromJSON(kClockJSON));
  EXPECT_TRUE(clock.is_open);
  EXPECT_EQ(clock.timestamp, "2018-04-01T12:00:00.000Z");
  EXPECT_EQ(clock.next_close, "2018-04-01T12:00:00.000Z");
  EXPECT_EQ(clock.next_open, "2018-04-01T12:00:00.000Z");
}
