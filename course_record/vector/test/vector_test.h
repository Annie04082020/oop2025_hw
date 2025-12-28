#include <gtest/gtest.h>
#include "../src/vector.h"

TEST(VectorSuite, InnerProductTest) {
    double u[] = { 1.0, 0.0 };
    double v[] = { 1.0, 1.0 };

    double result = innerProduct(u, 2, v, 2);

    ASSERT_EQ(1.0, result);
}

TEST(VectorSuite, ThreeDimInnerProductTest) {
    double u[] = { 1.0, 1.0, 0.0 };
    double v[] = { 0.0, 1.0, 1.0 };

    double result = innerProduct(u, 3, v, 3);

    ASSERT_EQ(1.0, result);
}

TEST(VectorSuite, DifferentSizeTest) {
    double u[] = { 1.0, 0.0 };
    double v[] = { 1.0, 1.0, 0.0 };

    ASSERT_ANY_THROW(innerProduct(u, 2, v, 3));
    // innerProduct(u, 2, v, 3);
}

TEST(VectorSuite, SizeOfTest) {
    double u[] = { 1, 1 };
    double v[] = { 1, 1, 1 };
    ASSERT_EQ(16, sizeof(u));
    ASSERT_EQ(24, sizeof(v));
    ASSERT_EQ(2, sizeof(u) / sizeof(double));
    ASSERT_EQ(3, sizeof(v) / sizeof(double));
}

TEST(VectorSuite, VectorObject) {
    double a[] = { 1, 1 };
    Vector u {a, 2}; // calling constructor Vector(double* data, int size);
    // u.~Vector() called by C++ runtime 
}

TEST(VectorSuite, VectorCallByValueWithCopyConstructor) {
    double a[] = { 1, 1 };
    Vector u {a, 2}; 
    call_by_value(u);
    call_by_value(u);
}

TEST(VectorSuite, VectorCopyAssignment) {
    double a[] = { 1, 1 };
    double b[] = { 2, 2 };
    double c[] = { 0, 8 };
    Vector u {a, 2}; 
    Vector v {b ,2};
    Vector w {c, 2};
    u = v = w;
    ASSERT_EQ(u.get(0), 0);
    ASSERT_EQ(u.get(1), 8);
    ASSERT_EQ(v.get(0), 0);
    ASSERT_EQ(v.get(1), 8);
    ASSERT_EQ(w.get(0), 0);
    ASSERT_EQ(w.get(1), 8);
}

TEST(VectorSuite, VectorCopyAssignmentWithParenthesis) {
    double a[] = { 1, 1 };
    double b[] = { 2, 2 };
    double c[] = { 0, 8 };
    Vector u {a, 2}; 
    Vector v {b ,2};
    Vector w {c, 2};
    (u = v) = w;
    ASSERT_EQ(u.get(0), 0);
    ASSERT_EQ(u.get(1), 8);
    ASSERT_EQ(v.get(0), 2);
    ASSERT_EQ(v.get(1), 2);
    ASSERT_EQ(w.get(0), 0);
    ASSERT_EQ(w.get(1), 8);
}
