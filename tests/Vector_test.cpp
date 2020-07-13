//
// Created by Xu Wenbo on 2020-07-13.
//

#include "gtest/gtest.h"
#include "Vector.h"
#include "Arithmetic.h"

TEST(VectorConstructor, size) {
    Vector<int> v(10);
    EXPECT_EQ(10, v.size());
    for(size_t i = 0; i < v.size(); ++i)
        EXPECT_EQ(0, v(i));
    EXPECT_THROW(Vector<int>(0), std::runtime_error);
}

TEST(VectorConstructor, stlVector) {
    std::vector<double> base = {3.14, 6.28};
    Vector<double> v = base;
    EXPECT_EQ(base.size(), v.size());
    for(size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(base[i], v(i));
    }
}

TEST(VectorConstructor, copy) {
    std::vector<int> base = {0, 1, 2, 3};
    Vector<int> v1(base);
    Vector<int> v2 = v1;
    EXPECT_EQ(v1.size(), v2.size());
    for(size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v2(i), v1(i));
    }
    Vector<int> v3(5);
    v3 = v1;
    EXPECT_EQ(v1.size(), v3.size());
    for(size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v3(i), v1(i));
    }
}

TEST(VectorAdd, mismatch) {
    Vector<int> v1(1);
    Vector<int> v2(2);
    EXPECT_THROW(v1 + v2, std::runtime_error);
    EXPECT_THROW(v1 += v2, std::runtime_error);
}

TEST(VectorAdd, sameType) {
    Vector<int> v1 = {{1,3,5,7}};
    Vector<int> v2 = {{8, 6, 4, 2}};
    auto v3 = v1 + v2;
    EXPECT_EQ(v1.size(), v3.size());
    for(size_t i = 0; i < v3.size(); ++i) {
        EXPECT_EQ(9, v3(i));
    }
}

TEST(VectorAdd, differentType) {
    Vector<double> v1 = {{0.1,0.3,0.5,0.7}};
    Vector<int> v2 = {{8, 8, 8, 8}};
    auto v3 = v1 + v2;
    EXPECT_TRUE((std::is_same<decltype(v3), Vector<double>>::value));
    EXPECT_EQ(v1.size(), v3.size());
    for(size_t i = 0; i < v3.size(); ++i) {
        EXPECT_NEAR(8 + i/5.0 + 0.1, v3(i), 1e-5);
    }
    auto v4 = v1 + v2;
    EXPECT_TRUE((std::is_same<decltype(v4), Vector<double>>::value));
    EXPECT_EQ(v1.size(), v4.size());
    for(size_t i = 0; i < v4.size(); ++i) {
        EXPECT_NEAR(8 + i/5.0 + 0.1, v4(i), 1e-5);
    }
}

TEST(VectorScalarProduct, nonPromote) {
    Vector<double> v = {{1,2,3,4}};
    auto v2 = 0.1 * v;
    EXPECT_TRUE((std::is_same<decltype(v2), Vector<double>>::value));
    for(size_t i = 0; i < v2.size(); ++i) {
        EXPECT_NEAR((i+1)/10.0, v2(i), 1e-5);
    }
    auto v3 = v2 * 10;
    EXPECT_TRUE((std::is_same<decltype(v3), Vector<double>>::value));
    for(size_t i = 0; i < v3.size(); ++i) {
        EXPECT_NEAR((i+1), v3(i), 1e-5);
    }
}

TEST(VectorScalarProduct, promote) {
    Vector<int> v = {{1,2,3,4}};
    auto v2 = 0.1 * v;
    EXPECT_TRUE((std::is_same<decltype(v2), Vector<double>>::value));
    for(size_t i = 0; i < v2.size(); ++i) {
        EXPECT_NEAR((i+1)/10.0, v2(i), 1e-5);
    }
    auto v3 = v * 10.0;
    EXPECT_TRUE((std::is_same<decltype(v3), Vector<double>>::value));
    for(size_t i = 0; i < v3.size(); ++i) {
        EXPECT_NEAR((i+1)*10, v3(i), 1e-5);
    }
}
