#include "alpaca/streaming.h"

#include "alpaca/testing.h"
#include "gtest/gtest.h"

const std::string kAuthorizationReply =
    "{\"stream\":\"authorization\",\"data\":{\"action\":\"authenticate\",\"status\":\"authorized\"}}";
const std::string kListeningReply =
    "{\"stream\":\"listening\",\"data\":{\"streams\":[\"trade_updates\",\"account_updates\"]}}";

class StreamingTest : public ::testing::Test {};

TEST_F(StreamingTest, testReplyParser) {
  auto rp = alpaca::ReplyParser();

  auto authorization = rp.messageType(kAuthorizationReply);
  EXPECT_OK(authorization.first);
  EXPECT_EQ(authorization.second, alpaca::Authorization);

  auto listening = rp.messageType(kListeningReply);
  EXPECT_OK(listening.first);
  EXPECT_EQ(listening.second, alpaca::Listening);
}