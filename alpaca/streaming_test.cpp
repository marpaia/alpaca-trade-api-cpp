#include "alpaca/streaming.h"

#include "alpaca/testing.h"
#include "gtest/gtest.h"

const std::string kAuthorizationReply =
    "{\"stream\":\"authorization\",\"data\":{\"action\":\"authenticate\",\"status\":\"authorized\"}}";
const std::string kListeningReply =
    "{\"stream\":\"listening\",\"data\":{\"streams\":[\"trade_updates\",\"account_updates\"]}}";
const std::string kTradeUpdatsReply =
    "{"
    "\"stream\": \"trade_updates\","
    "\"data\": {"
    "\"event\": \"fill\","
    "\"order\": {"
    "\"asset_class\": \"us_equity\","
    "\"asset_id\": \"b0b6dd9d-8b9b-48a9-ba46-b9d54906e415\","
    "\"canceled_at\": null,"
    "\"client_order_id\": \"53b52c15-b7f7-4940-9292-d3e3857cfb97\","
    "\"created_at\": \"2020-04-06T14:03:18.089295Z\","
    "\"expired_at\": null,"
    "\"extended_hours\": false,"
    "\"failed_at\": null,"
    "\"filled_at\": \"2020-04-06T14:03:18.143277Z\","
    "\"filled_avg_price\": \"253.02\","
    "\"filled_qty\": \"1\","
    "\"id\": \"caf0cc4b-1601-4a37-acc1-ad27b8175a47\","
    "\"legs\": null,"
    "\"limit_price\": null,"
    "\"order_class\": \"\","
    "\"order_type\": \"market\","
    "\"qty\": \"1\","
    "\"replaced_at\": null,"
    "\"replaced_by\": null,"
    "\"replaces\": null,"
    "\"side\": \"buy\","
    "\"status\": \"filled\","
    "\"stop_price\": null,"
    "\"submitted_at\": \"2020-04-06T14:03:18.075743Z\","
    "\"symbol\": \"AAPL\","
    "\"time_in_force\": \"day\","
    "\"type\": \"market\","
    "\"updated_at\": \"2020-04-06T14:03:18.15874Z\""
    "},"
    "\"position_qty\": \"1\","
    "\"price\": \"253.02\","
    "\"qty\": \"1\","
    "\"timestamp\": \"2020-04-06T14:03:18.143276612Z\""
    "}"
    "}";

class StreamingTest : public ::testing::Test {};

TEST_F(StreamingTest, testReplyParser) {}