#include "alpaca/calendar.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class CalendarTest : public ::testing::Test {};

const std::string kDateJSON =
    "{"
    "\"date\": \"2018-01-03\","
    "\"open\": \"09:30\","
    "\"close\": \"16:00\""
    "}";

TEST_F(CalendarTest, testDateFromJSON) {
  alpaca::Date date;
  EXPECT_OK(date.fromJSON(kDateJSON));
  EXPECT_EQ(date.open, "09:30");
  EXPECT_EQ(date.close, "16:00");
  EXPECT_EQ(date.date, "2018-01-03");
}
