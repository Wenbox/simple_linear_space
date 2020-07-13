//
// Created by Xu Wenbo on 2020-07-11.
//

#include "gtest/gtest.h"
#include "Matrix.h"
#include "Vector.h"
#include "Arithmetic.h"

TEST(MatrixConstructor, rowColumn) {
    EXPECT_THROW(Matrix<int>(0, 1), std::runtime_error);
    EXPECT_THROW(Matrix<int>(1, 0), std::runtime_error);
    Matrix<double> matD(1, 1);
    EXPECT_EQ(0, matD(0, 0));
    Matrix<int> mat(3, 4);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_EQ(0, mat(i, j));
}

TEST(MatrixConstructor, twoDimVector) {
    std::vector<std::vector<int>> v1 = {{1, 2, 3},
                                        {4, 5, 6}};
    Matrix<int> m1 = v1;
    for (int i = 0; i < v1.size(); ++i) {
        for (int j = 0; j < v1[i].size(); ++j)
            EXPECT_EQ(v1[i][j], m1(i, j));
    }
    std::vector<std::vector<int>> v2 = {{1, 2, 3},
                                        {4, 5, 6},
                                        {7}};
    EXPECT_THROW(Matrix<int>{v2}, std::runtime_error);

    EXPECT_THROW(Matrix<int>({}), std::runtime_error);

    std::vector<std::vector<int>> v3(1);
    EXPECT_THROW(Matrix<int>{v3}, std::runtime_error);
}

TEST(MatrixConstructor, copy) {
    Matrix<double> m1({{1, 2, 3},
                       {4, 5, 6}});
    Matrix<double> m2(m1);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(m1(i, j), m2(i, j));
        }
    }
    Matrix<double> m3(1, 1);
    m3 = m2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(m3(i, j), m2(i, j));
        }
    }
}

TEST(MatrixAccess, access) {
     Matrix<double> m1({{1, 2, 3},
                       {4, 5, 6}});
     EXPECT_EQ(3.0, m1(0,2));
     m1(0,2) = 99.0;
     EXPECT_EQ(99.0, m1(0, 2));
     EXPECT_THROW(m1(-1,2), std::runtime_error);
     EXPECT_THROW(m1(2,2), std::runtime_error);
}

TEST(MatrixScalarProduct, nonPromote) {
    Matrix<double> m1({{0, 1, 2, 3},
                       {4, 5, 6, 7}});
    auto p1 = m1 * 3;
    auto p2 = 3.0 * m1;
    EXPECT_TRUE((std::is_same<decltype(p1), Matrix<double>>::value));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(p1(i, j), 3 * (i * 4 + j));
            EXPECT_EQ(p2(i, j), 3 * (i * 4 + j));
        }
    }
}

TEST(MatrixScalarProduct, promote) {
    Matrix<int> m1({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    auto p1 = m1 * 3.0;
    auto p2 = 3.0 * m1;
    EXPECT_TRUE((std::is_same<decltype(p1), Matrix<double>>::value));
    EXPECT_TRUE((std::is_same<decltype(p2), Matrix<double>>::value));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(p1(i, j), 3 * (i * 4 + j));
            EXPECT_EQ(p2(i, j), 3 * (i * 4 + j));
        }
    }

}

TEST(MatrixAddition, sameType) {
    Matrix<int> m1({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    Matrix<int> m2({{0,  -1, -2, -3},
                    {-4, -5, -6, -7}});
    auto sum1 = m1 + m2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(sum1(i, j), 0);
        }
    }
}

TEST(MatrixAddition, differentType) {
    Matrix<int> m1({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    Matrix<double> m2({{1.0,  1.0, 1.0, 1.0},
                    {1.0, 1.0, 1.0, 1.0}});
    auto sum1 = m1 + m2;
    EXPECT_TRUE((std::is_same<decltype(sum1), Matrix<double>>::value));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(sum1(i, j), i*4 + j + 1.0);
        }
    }
}

TEST(MatrixAddition, dimensionMismatch) {
    Matrix<int> m1({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    Matrix<double> m2({{1.0,  1.0, 1.0, 1.0}});
    EXPECT_THROW(m1 + m2, std::runtime_error);
    Matrix<int> m3({{0, 1, 2},
                    {4, 5, 6}});
    EXPECT_THROW(m1 + m3, std::runtime_error);
}

TEST(MatrixAdditionAsign, additionAsign) {
    Matrix<int> m1({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    Matrix<int> m2({{0,  -1, -2, -3},
                    {-4, -5, -6, -7}});
    m1 += m2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(m1(i, j), 0);
        }
    }
    Matrix<double> m3({{0, 1, 2, 3},
                    {4, 5, 6, 7}});
    m3 += m3;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(m3(i, j), 2*(i*4+j));
        }
    }
    m3 += m2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(m3(i, j), (i*4+j));
        }
    }

    EXPECT_THROW(m2 += m3, std::runtime_error);
}

TEST(MatrixMultiplication, dimensionMismatch) {
    Matrix<int> m1(3,4);
    Matrix<int> m2(3,1);
    EXPECT_THROW(m1 * m2, std::runtime_error);
}

TEST(MatrixMultiplication, zeroMatrix) {
    Matrix<int> m1(3,4);
    Matrix<int> m2(4,2);
    auto res1 = m1 * m2;
    for(size_t i = 0; i < 3; ++i) {
        for(size_t j = 0; j < 2; ++j) {
            EXPECT_EQ(0, res1(i, j));
        }
    }
}

TEST(MatrixMultiplication, anyMatrix) {
    std::vector<std::vector<double>> v1 = {{0,1,2}, {3,4,5}, {6,7,8}};
    std::vector<std::vector<double>> v2 = {{3,1,2}, {8,5,5}, {4,3,1}};
    std::vector<std::vector<double>> v3 = {{16,11,7}, {61,38,31}, {106,65,55}};

    Matrix<double> m1(v1);
    Matrix<double> m2(v2);
    auto m3 = m1 * m2;
    for(size_t i = 0; i < 3; ++i) {
        for(size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(v3[i][j], m3(i, j));
        }
    }
    std::vector<std::vector<double>> v4 = {{3.1}, {7.4}, {10}, {-6.5}};
    std::vector<std::vector<int>> v5 = {{-8, -2, 1}};
    std::vector<std::vector<double>> v6 = {{-24.8, -6.2, 3.1}, {-59.2, -14.8, 7.4}, {-80, -20, 10}, {52, 13, -6.5}};
    Matrix<double> m4(v4);
    Matrix<int> m5(v5);
    auto m6 = m4 * m5;
    EXPECT_EQ(4, m6.size().first);
    EXPECT_EQ(3, m6.size().second);
    EXPECT_TRUE((std::is_same<decltype(m6), Matrix<double>>::value));
    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(v6[i][j], m6(i, j), 1e-5);
        }
    }
}

TEST(MatrixVectorMultiplication, mismatch) {
    Matrix<int> m = {{{1,2}, {3,4}}};
    Vector<int> v1(1);
    Vector<int> v2 = {{1, 2, 3}};
    EXPECT_THROW(m * v1, std::runtime_error);
    EXPECT_THROW(m * v2, std::runtime_error);
}

TEST(MatrixVectorMultiplication, sameType) {
    Matrix<int> m = {{{1,2}, {3,4}}};
    Vector<int> v1({-7, -8});
    auto res = m * v1;
    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res(0), -23);
    EXPECT_EQ(res(1), -53);
}

TEST(MatrixVectorMultiplication, differentType) {
    Matrix<int> m = {{{8, -8, 10}, {-2, 100, -65535}}};
    Vector<double> v1({9.9, 0, -3.14});
    auto res = m * v1;
    EXPECT_TRUE((std::is_same<decltype(res), Vector<double>>::value));
    EXPECT_EQ(res.size(), 2);
    EXPECT_NEAR(res(0), 47.8, 1e-5);
    EXPECT_NEAR(res(1), 205760.1, 1e-5);
}