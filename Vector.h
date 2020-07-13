//
// Created by Xu Wenbo on 2020-07-13.
//

#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H
template <typename T>
class Matrix;

template <typename T>
class Vector {
public:
    Vector(int size) : m_data(size > 0 ? std::vector<T>(size) : throw std::runtime_error("Vector size must be positive."))
    {}

    Vector(const std::vector<T>& v) : m_data(v.empty() ? throw std::runtime_error("Vector size must be positive.") : v)
    {}

    Vector(const Vector<T> &orig) = default;

    Vector &operator=(const Vector<T> &rhs) = default;

    ~Vector() = default;

    size_t size() const {
        return m_data.size();
    }

    T& operator()(const size_t& i) {
        if(i < 0 || i >= m_data.size())
            throw std::runtime_error("Index out of bound.");
        return m_data[i];
    }

    template<typename U1, typename U2>
    friend Vector<typename std::common_type<U1, U2>::type> operator+(const Vector<U1> &lhs, const Vector<U2> &rhs);

    template<typename U1, typename U2>
    friend Vector<U1>& operator+=(Vector<U1> &lhs, const Vector<U2> &rhs);

    template<typename U1, typename U2>
    friend Vector<typename std::common_type<U1, U2>::type> operator*(const Vector<U1> &lhs, const U2 &rhs);

    template<typename U1, typename U2>
    friend Vector<typename std::common_type<U1, U2>::type> operator*(const U1 &lhs, const Vector<U2> &rhs);

    template<typename U1, typename U2>
    friend Vector<typename std::common_type<U1, U2>::type> operator*(const Matrix<U1> &lhs, const Vector<U2> &rhs);

private:
    std::vector<T> m_data;
};
#endif //MATRIX_VECTOR_H
