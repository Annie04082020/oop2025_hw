#include <gtest/gtest.h>
#include <vector>
#include "../src/shared_ptr.h"

class SharedPtrTest : public ::testing::Test
{
};

TEST_F(SharedPtrTest, DefaultConstructor)
{
    SharedPtr<int> a(new int(100));
    EXPECT_EQ(a.reference_count(), 1);
    EXPECT_EQ(*a, 100);
}
TEST_F(SharedPtrTest, CopyConstructor)
{
    SharedPtr<int> a(new int(100));
    EXPECT_EQ(a.reference_count(), 1);
    SharedPtr<int> b = a;
    EXPECT_EQ(a.reference_count(), 2);
    EXPECT_EQ(b.reference_count(), 2);
    EXPECT_EQ(*b, *a);
    EXPECT_EQ(*b, 100);
}
TEST_F(SharedPtrTest, Destructor)
{
    SharedPtr<int> a(new int(100));
    EXPECT_EQ(a.reference_count(), 1);
    {
        SharedPtr<int> b = a;
        EXPECT_EQ(a.reference_count(), 2);
        EXPECT_EQ(b.reference_count(), 2);
        EXPECT_EQ(*b, *a);
        EXPECT_EQ(*b, 100);
    }
    EXPECT_EQ(a.reference_count(), 1);
}
TEST_F(SharedPtrTest, CopyAssignmentOperator)
{
    SharedPtr<int> a(new int(100));
    SharedPtr<int> b(new int(50));
    EXPECT_EQ(*a, 100);
    EXPECT_EQ(*b, 50);
    EXPECT_EQ(a.reference_count(), 1);
    EXPECT_EQ(b.reference_count(), 1);
    b = a;
    EXPECT_EQ(a.reference_count(), 2);
    EXPECT_EQ(b.reference_count(), 2);
    EXPECT_EQ(*b, *a);
    EXPECT_EQ(*b, 100);
}
TEST_F(SharedPtrTest, DereferenceNormalPointer)
{
    EXPECT_NO_THROW(
        {
            SharedPtr<int> a(new int(100));
            EXPECT_EQ(*a, 100);
        });
}
TEST_F(SharedPtrTest, DereferenceNullPtr)
{
    SharedPtr<int> sp(nullptr);
    EXPECT_THROW(*sp, std::bad_optional_access); // 測試會預期收到這個型別
}
TEST_F(SharedPtrTest, ReferenceCountGetter)
{
    int loopcount = 100;
    SharedPtr<int> root(new int(100));
    EXPECT_EQ(root.reference_count(), 1);
    std::vector<SharedPtr<int>> clones;
    for (int i = 0; i < loopcount; i++)
    {
        clones.push_back(root);
        EXPECT_EQ(root.reference_count(), i + 2);
    }
    EXPECT_EQ(root.reference_count(), loopcount + 1);
    clones.clear();
    EXPECT_EQ(root.reference_count(), 1);
    EXPECT_EQ(*root, 100);
}
TEST_F(SharedPtrTest, ResetSharedPointer)
{
    SharedPtr<int> a(new int(100));
    SharedPtr<int> b = a;
    EXPECT_EQ(*a, 100);
    EXPECT_EQ(a.reference_count(), 2);
    EXPECT_EQ(b.reference_count(), 2);
    a.reset();
    EXPECT_EQ(b.reference_count(), 1);
    EXPECT_EQ(a.reference_count(), 0);
    EXPECT_THROW(*a, std::bad_optional_access);
}