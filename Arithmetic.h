//
// Created by Xu Wenbo on 2020-07-12.
//

#ifndef MATRIX_ARITHMETIC_H
#define MATRIX_ARITHMETIC_H

#include <type_traits>
#include "Vector.h"
#include "Matrix.h"


template<typename T, typename U>
Vector<typename std::common_type<T, U>::type> operator+ (const Vector<T> &lhs, const Vector<U> &rhs) {
    using common_type_t = typename std::common_type<T, U>::type;
    if(lhs.size() != rhs.size())
        throw std::runtime_error("Vector dimensions mismatch, cannot add.");
    Vector<common_type_t> res(lhs.size());
    for(size_t i = 0; i < res.size(); ++i) {
        res(i) = lhs.m_data[i] + rhs.m_data[i];
    }
    return res;
}

template<typename T, typename U>
Vector<T>& operator+= (Vector<T> &lhs, const Vector<U> &rhs) {
    using common_type_t = typename std::common_type<T, U>::type;
    if(lhs.size() != rhs.size())
        throw std::runtime_error("Vector dimension mismatch, cannot add.");
    if(std::is_same<T, common_type_t >::value) {
        for(size_t i = 0; i < lhs.size(); ++i) {
            lhs.m_data[i] += rhs.m_data[i];
        }
        return lhs;
    } else {
        throw std::runtime_error("Type promoted after addition, cannot assign to left hand side.");
    }
}

template<typename T, typename U>
Vector<typename std::common_type<T, U>::type> operator* (const Vector<T> &v, const U &scalar) {
    using common_type_t = typename std::common_type<T, U>::type;
    Vector<common_type_t> res(v.size());
    for (size_t i = 0; i < res.m_data.size(); ++i) {
        res.m_data[i] = v.m_data[i] * scalar;
    }
    return res;
}

template<typename T, typename U>
Vector<typename std::common_type<T, U>::type> operator*(const T &scalar, const Vector<U> &v) {
    return v * scalar;
}

template<typename T, typename U>
Matrix<typename std::common_type<T, U>::type> operator+ (const Matrix<T> &lhs, const Matrix<U> &rhs) {
    using common_type_t = typename std::common_type<T, U>::type;
    if(lhs.m_data.size() != rhs.m_data.size() || lhs.m_data[0].size() != rhs.m_data[0].size())
        throw std::runtime_error("Matrices dimensions mismatch, cannot add.");
    Matrix<common_type_t> res(lhs.m_data.size(), lhs.m_data[0].size());
    for (size_t i = 0; i < res.m_data.size(); ++i) {
        for (size_t j = 0; j < res.m_data[i].size(); ++j)
            res.m_data[i][j] = lhs.m_data[i][j] + rhs.m_data[i][j];
    }
    return res;
}

template<typename T, typename U>
Matrix<T>& operator+= (Matrix<T>& lhs, const Matrix<U> &rhs) {
    using common_type_t = typename std::common_type<T, U>::type;
    if(lhs.m_data.size() != rhs.m_data.size() || lhs.m_data[0].size() != rhs.m_data[0].size())
        throw std::runtime_error("Matrices dimension mismatch, cannot add.");
    if(std::is_same<T, common_type_t >::value) {
        for(size_t i = 0; i < lhs.m_data.size(); ++i) {
            for(size_t j = 0; j < lhs.m_data[i].size(); ++j) {
                lhs.m_data[i][j] += rhs.m_data[i][j];
            }
        }
        return lhs;
    } else {
        throw std::runtime_error("Type promoted after addition, cannot assign to left hand side.");
    }
}

template<typename T, typename U>
Matrix<typename std::common_type<T, U>::type> operator* (const Matrix<T> &m, const U &scalar) {
    using common_type_t = typename std::common_type<T, U>::type;
    Matrix<common_type_t> res(m.m_data.size(), m.m_data[0].size());
    for (size_t i = 0; i < res.m_data.size(); ++i) {
        for (size_t j = 0; j < res.m_data[i].size(); ++j)
            res.m_data[i][j] = m.m_data[i][j] * scalar;
    }
    return res;
}

template<typename T, typename U>
Matrix<typename std::common_type<T, U>::type> operator*(const T &scalar, const Matrix<U> &m) {
    return m * scalar;
}

template<typename T, typename U>
Matrix<typename std::common_type<T, U>::type> operator*(const Matrix<T> &A, const Matrix<U> &B) {
    using common_type_t = typename std::common_type<T, U>::type;
    size_t m = A.m_data.size();
    size_t p = A.m_data[0].size();
    if(B.m_data.size() != p)
        throw std::runtime_error("Matrix multiplication dimension mismatch.");
    size_t n = B.m_data[0].size();
    Matrix<common_type_t> res(m, n);
    //ikj
    for(size_t i = 0; i < m; ++i) {
        for(size_t k = 0; k < p; ++k) {
            const auto& tmp = A.m_data[i][k];
            for(size_t j = 0; j < n; ++j) {
                res.m_data[i][j] += B.m_data[k][j] * tmp;
            }
        }
    }
    return res;
}

template<typename T, typename U>
Vector<typename std::common_type<T, U>::type> operator*(const Matrix<T> &M, const Vector<U> &V) {
    using common_type_t = typename std::common_type<T, U>::type;
    size_t m = M.m_data.size();
    size_t p = M.m_data[0].size();
    if(V.size() != p)
        throw std::runtime_error("Matrix * Vector dimension mismatch.");
    Vector<common_type_t> res(m);
    for(size_t i = 0; i < m; ++i) {
        for(size_t k = 0; k < p; ++k) {
            res.m_data[i] += M.m_data[i][k] * V.m_data[k];
        }
    }
    return res;
}

#endif //MATRIX_ARITHMETIC_H
