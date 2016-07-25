//=============================================================================
// A C++ 11 style matrix

#ifndef Matrix_H
#define Matrix_H

#include "Capabilities.h"
#ifndef CAPABILITY_CONSTEXPR
#error "This needed constexpr."
#endif

#include <array>
#include <iostream>
#include <cassert>

#define UNUSED_VARIABLE 1
#define SELF_MOVE 1
#include "IgnoreDiagnostics.h"
#undef UNUSED_VARIABLE

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
class Matrix {
public:

  Matrix() = default;

  Matrix(std::initializer_list<std::initializer_list<T>> initializers);

  template <typename GENERATOR_FUNCTION>
  Matrix(GENERATOR_FUNCTION generator_function);
  // GENERATOR_FUNCTION is a function like
  // std::function<T(unsigned int, unsigned int)> which is used to assign
  // values to each cell in the Matrix.
  
  ~Matrix() = default;
  
  Matrix(Matrix<T, N, M>& other) = default;
  Matrix<T, N, M>& operator=(Matrix<T, N, M>& other) = default;
  
  Matrix(Matrix<T, N, M>&& other) = default;
  Matrix<T, N, M>& operator=(Matrix<T, N, M>&& other) = default;
  
  typedef typename std::array<std::array<T, M>, N>::iterator iterator;
  typedef typename std::array<std::array<T, M>, N>::const_iterator const_iterator;
  typedef typename std::array<T, M> row;

  //----- Random access
  row& operator[](unsigned int n);
  const row& operator[](unsigned int n) const;

  //----- Iterator access
  iterator begin();
  iterator end();
  
  const_iterator begin() const;
  const_iterator end() const;
  
  const_iterator cbegin() const;
  const_iterator cend() const;

  //----- constexpr dimension queries
  constexpr unsigned int columns() const {
    return M;
  }
  
  constexpr unsigned int rows() const {
    return N;
  }
  
  constexpr unsigned int elements() const {
    return N * M;
  }
  
  constexpr bool square() const {
    return N == M;
  }

  //----- Matrix operations
  Matrix<T, M, N> transpose() const;
  // Return this matrix, transposed.

private:

  Matrix(const Matrix<T, N, M>& other);
  Matrix<T, N, M>& operator=(const Matrix<T, N, M>& other);
  
  std::array<std::array<T, M>, N> m_matrix;
};

template <typename T, unsigned int N, unsigned int M>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& matrix);

//----- Matrix arithmatic operators
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b);

template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b);

template <typename T, unsigned int N, unsigned int M, unsigned int P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& a, const Matrix<T, M, P>& b);

//----- Scalar arithmatic operators
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator+(const T& scalar, const Matrix<T, N, M>& matrix);

template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& matrix, const T& scalar);

template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator*(const T& scalar, const Matrix<T, N, M>& matrix);

template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, const T& scalar);

//----- Comparison operators
template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator==(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b);

template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator!=(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b);

#endif
