//
// Created by Xu Wenbo on 2020-07-11.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <string>

template<typename T>
class Vector;

template<typename T>
class Matrix {
public:
    Matrix(int row, int col) : m_data(row > 0 ? row : throw std::runtime_error("Row must be positive."),
                                      std::vector<T>(
                                              col > 0 ? col : throw std::runtime_error("Column must be positive."),
                                              0)) {
    }

    Matrix(const std::vector<std::vector<T>> &v) {
        //check sanity
        if (v.empty() || v[0].empty())
            throw std::runtime_error("Invalid matrix initialization.");
        auto cols = v[0].size();
        for (auto &r : v) {
            if (r.size() != cols)
                throw std::runtime_error("Invalid matrix initialization.");
        }
        m_data = v;
    }

    Matrix(const Matrix<T> &orig) = default;

    Matrix &operator=(const Matrix<T> &rhs) = default;

    ~Matrix() = default;

    std::string to_string() {
        std::string s;
        for (auto &row : m_data) {
            for (auto &d : row) {
                s += std::to_string(d) + ' ';
            }
            s.back() = '\n';
        }
        return s;
    }
    std::pair<size_t, size_t> size() const {
        return std::make_pair<size_t, size_t>(m_data.size(), m_data[0].size());
    }


    T &operator()(const size_t &i, const size_t &j) {
        if (i < 0 || i >= m_data.size() || j < 0 || j >= m_data[0].size())
            throw std::runtime_error("Index out of bound.");
        return m_data[i][j];
    }

    template<typename U1, typename U2>
    friend Matrix<typename std::common_type<U1, U2>::type> operator+(const Matrix<U1> &lhs, const Matrix<U2> &rhs);

    template<typename U1, typename U2>
    friend Matrix<U1> &operator+=(Matrix<U1> &lhs, const Matrix<U2> &rhs);

    template<typename U1, typename U2>
    friend Matrix<typename std::common_type<U1, U2>::type> operator*(const Matrix<U1> &lhs, const U2 &rhs);

    template<typename U1, typename U2>
    friend Matrix<typename std::common_type<U1, U2>::type> operator*(const U1 &lhs, const Matrix<U2> &rhs);

    template<typename U1, typename U2>
    friend Matrix<typename std::common_type<U1, U2>::type> operator*(const Matrix<U1> &lhs, const Matrix<U2> &rhs);

    template<typename U1, typename U2>
    friend Vector<typename std::common_type<U1, U2>::type> operator*(const Matrix<U1> &lhs, const Vector<U2> &rhs);

private:
    std::vector<std::vector<T>> m_data;
};


#endif //MATRIX_MATRIX_H
