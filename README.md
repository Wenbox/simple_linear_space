# simple_linear_space

This demo implements the basics of linear algebra.
It defines a Vector template and a Matrix template.
A Vector corresponds to a column vector in linear algebra.
Moreover, the following operations are supported:

* Vector + Vector
* Vector * scalar and scalar * Vector
* Matrix + Matrix
* Matrix * scalar and scalar * Matrix
* Matrix * Matrix
* Matrix * Vector, the result is a Vector

## Implementation notes

1. I use stl vector, instead of raw array, to store internal data of Vector and Matrix.
The consideration is the ease of maintenance and debugging.
However, for high performance computing, some benchmarks are necessary to find out the best solution to store data.

   Also note that a Matrix is a vector of vectors, whilst a Vector is just a stl vector, so an n * 1 Matrix is NOT a vector.

2. Type promotion is taken into account.
For example, a Matrix<int> * double scalar should result in a Matrix<double>.
Similarly, a Vector<double> + Vector<int> also results in a Vector<double>.
  
3. Matrix multiplication is implemented in a naïve way with O(n^3) time complexity.
The only optimisation I made is to use a "ikj" loop for better locality and cache behaviour, according to the book *Computer Systems: A Programmer's Perspective*.
For very large matrices, better algorithms may be required, such as Strassen's algorithm and distributed algorithm.

4. Empty Vector or Matrix is not allowed. Trying to initialise empty Vectors or Matrices will throw runtime error.

## Build and test

Requiremtns:
* A modern CMake (tested with V3.14).
* A modern c++ compliler supportint c++17 (tested with Apple clang-1103.0.32.62).

This is a CMake project.
After cloning the project, do the following under the root folder of this project:

`mkdir build && cd build`  
`cmake ..`   
`make`   

This will automatically download google test framework and build the unit tests.
Then run `make test` will run the unit tests.
