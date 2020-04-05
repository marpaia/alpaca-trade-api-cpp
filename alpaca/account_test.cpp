#include "alpaca/account.h"

#include "alpaca/testing.h"
#include "glog/logging.h"
#include "gtest/gtest.h"

class AccountTest : public ::testing::Test {};

const std::string kAccountsJSON =
    "{"
    "\"account_blocked\": false,"
    "\"account_number\": \"010203ABCD\","
    "\"buying_power\": \"262113.632\","
    "\"cash\": \"-23140.2\","
    "\"created_at\": \"2019-06-12T22:47:07.99658Z\","
    "\"currency\": \"USD\","
    "\"daytrade_count\": 0,"
    "\"daytrading_buying_power\": \"262113.632\","
    "\"equity\": \"103820.56\","
    "\"id\": \"e6fe16f3-64a4-4921-8928-cadf02f92f98\","
    "\"initial_margin\": \"63480.38\","
    "\"last_equity\": \"103529.24\","
    "\"last_maintenance_margin\": \"38000.832\","
    "\"long_market_value\": \"126960.76\","
    "\"maintenance_margin\": \"38088.228\","
    "\"multiplier\": \"4\","
    "\"pattern_day_trader\": false,"
    "\"portfolio_value\": \"103820.56\","
    "\"regt_buying_power\": \"80680.36\","
    "\"short_market_value\": \"0\","
    "\"shorting_enabled\": true,"
    "\"sma\": \"0\","
    "\"status\": \"ACTIVE\","
    "\"trade_suspended_by_user\": false,"
    "\"trading_blocked\": false,"
    "\"transfers_blocked\": false"
    "}";

const std::string kAccountConfigurationsJSON =
    "{"
    "\"dtbp_check\": \"entry\","
    "\"no_shorting\": true,"
    "\"suspend_trade\": false,"
    "\"trade_confirm_email\": \"all\""
    "}";

TEST_F(AccountTest, testAccountConfigurationFromJSON) {
  alpaca::Account account;
  EXPECT_OK(account.fromJSON(kAccountsJSON));
  EXPECT_EQ(account.account_number, "010203ABCD");
}

TEST_F(AccountTest, testAccountConfigurationsFromJSON) {
    alpaca::AccountConfigurations account_configurations;
    EXPECT_OK(account_configurations.fromJSON(kAccountConfigurationsJSON));
    EXPECT_EQ(account_configurations.no_shorting, true);
}