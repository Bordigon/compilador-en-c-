#include <gtest/gtest.h>
#include "AttributeValue.h"

using namespace TS_CPP;

class TestAttributeValue : public ::testing::Test {
protected:
    // Test setup can go here
};

TEST_F(TestAttributeValue, TestStringConstructor) {
    AttributeValue av("test");
    auto value = av.getValue();
    ASSERT_EQ(AttributeValue::STRING, value.first);
    ASSERT_STREQ("test", value.second.strPtr);
}

TEST_F(TestAttributeValue, TestIntegerConstructor) {
    AttributeValue av(123);
    auto value = av.getValue();
    ASSERT_EQ(AttributeValue::INT, value.first);
    ASSERT_EQ(123, value.second.integer);
}

TEST_F(TestAttributeValue, TestEqualityOperator) {
    AttributeValue av1("test");
    AttributeValue av2("test");
    ASSERT_TRUE(av1 == av2);

    AttributeValue av3(123);
    AttributeValue av4(123);
    ASSERT_TRUE(av3 == av4);

    AttributeValue av5("test");
    AttributeValue av6(123);
    ASSERT_FALSE(av5 == av6);
}

TEST_F(TestAttributeValue, TestIsValidAttributeValue) {
    AttributeValue av1(nullptr);
    ASSERT_FALSE(av1.isAValidAttributeValue());

    AttributeValue av2("test");
    ASSERT_TRUE(av2.isAValidAttributeValue());

    AttributeValue av3(123);
    ASSERT_TRUE(av3.isAValidAttributeValue());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}