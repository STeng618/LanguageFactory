#include <gtest/gtest.h>
#include <iostream>
#include <value/cellReference.hpp>

using namespace Langfact;

TEST(CellReferenceTest, ValidSimpleReference) {
    std::string test_expr {"A1"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 1);
    EXPECT_EQ(ref->m_b, 1);
    EXPECT_EQ(ref->m_l, 1);
    EXPECT_EQ(ref->m_r, 1);
}

TEST(CellReferenceTest, ValidRangeReference) {
    std::string test_expr {"A1:C7"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 1);
    EXPECT_EQ(ref->m_b, 7);
    EXPECT_EQ(ref->m_l, 1);
    EXPECT_EQ(ref->m_r, 3);
}

TEST(CellReferenceTest, ValidOneColReference) {
    std::string test_expr {"A:A"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 0);
    EXPECT_EQ(ref->m_b, 0);
    EXPECT_EQ(ref->m_l, 1);
    EXPECT_EQ(ref->m_r, 1);
}

TEST(CellReferenceTest, ValidOneRowReference) {
    std::string test_expr {"3:3"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 3);
    EXPECT_EQ(ref->m_b, 3);
    EXPECT_EQ(ref->m_l, 0);
    EXPECT_EQ(ref->m_r, 0);
}

TEST(CellReferenceTest, ValidMultiRowReference) {
    std::string test_expr {"3:6"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 3);
    EXPECT_EQ(ref->m_b, 6);
    EXPECT_EQ(ref->m_l, 0);
    EXPECT_EQ(ref->m_r, 0);
}

TEST(CellReferenceTest, ValidMultiColReference) {
    std::string test_expr {"B:E"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 0);
    EXPECT_EQ(ref->m_b, 0);
    EXPECT_EQ(ref->m_l, 2);
    EXPECT_EQ(ref->m_r, 5);
}

TEST(CellReferenceTest, ValidWithConstReference) {
    std::string test_expr {"B$2:$AA7"};
    auto ref = CellReference::create(test_expr);
    ASSERT_NE(ref, nullptr);
    EXPECT_EQ(ref->m_t, 2);
    EXPECT_EQ(ref->m_b, 7);
    EXPECT_EQ(ref->m_l, 2);
    EXPECT_EQ(ref->m_r, 27);
}

TEST(CellReferenceTest, InvalidReferenceReturnsNull) {
    std::string test_expr {"1A"};
    auto ref = CellReference::create(test_expr);
    EXPECT_EQ(ref, nullptr);
}

TEST(CellReferenceTest, AwkwardReferenceReturnsNull) {
    std::string test_expr {"A:C7"};
    auto ref = CellReference::create(test_expr);
    EXPECT_EQ(ref, nullptr);
}

