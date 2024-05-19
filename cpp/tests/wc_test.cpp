#include <gtest/gtest.h>
#include "wc.h"

TEST(WcTest, CountBytes) {
    std::istringstream stream("Hello, world!");
    WcConfig config;
    config.count_bytes = true;
    auto result = handle_queries(stream, config);
    ASSERT_EQ(result[0], 13);
}

TEST(WcTest, CountLines) {
    std::istringstream stream("Hello\nworld\n");
    WcConfig config;
    config.count_lines = true;
    auto result = handle_queries(stream, config);
    ASSERT_EQ(result[0], 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}