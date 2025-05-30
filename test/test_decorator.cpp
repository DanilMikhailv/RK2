#include <gtest/gtest.h>
#include "message.hpp"

TEST(MessageDecoratorTest, TextMessageBasic) {
    TextMessage msg("Hello");
    EXPECT_EQ(msg.Serialize(), "Hello");
}

TEST(MessageDecoratorTest, ImageMessageBasic) {
    ImageMessage msg("image.png");
    EXPECT_EQ(msg.Serialize(), "Binary Data Of image.png");
}

TEST(MessageDecoratorTest, CompressedTextMessage) {
    CompressionMessageDecorator cmp(std::make_unique<TextMessage>("aaabbbccc"));
    std::string result = cmp.Serialize();
    EXPECT_EQ(result, "abc");
}

TEST(MessageDecoratorTest, EncryptedTextMessage) {
    EncryptionMessageDecorator enc(std::make_unique<TextMessage>("abcd1234"));
    std::string result = enc.Serialize();
    EXPECT_EQ(result, "1234abcd");
}
/*
TEST(MessageDecoratorTest, FullChain) {
    EncryptionMessageDecorator enc(
        std::make_unique<CompressionMessageDecorator>(
            std::make_unique<TextMessage>("aaabbbcccaaa")));

    std::string result = enc.Serialize();
    EXPECT_EQ(result, "bcaaaaabbb");
}*/
