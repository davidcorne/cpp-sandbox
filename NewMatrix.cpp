//=============================================================================
// A C++ 11 style matrix

#include <array>
#include <iostream>
#include <UnitCpp/Test.h>

#define UNUSED_VARIABLE 1
#include "IgnoreDiagnostics.h"
#undef UNUSED_VARIABLE

template <typename T, unsigned int N, unsigned int M>
class Matrix {
public:

  Matrix();

  template <typename GENERATOR_FUNCTION>
  Matrix(GENERATOR_FUNCTION generator_function);
  // GENERATOR_FUNCTION is a function like
  // std::function<T(unsigned int, unsigned int)> which is used to assign
  // values to each cell in the Matrix.
  
  ~Matrix();
  
  Matrix(Matrix<T, N, M>&& other);
  Matrix<T, N, M>& operator=(Matrix<T, N, M>&& other);
  
  typedef typename std::array<std::array<T, M>, N>::iterator iterator;
  typedef typename std::array<std::array<T, M>, N>::const_iterator const_iterator;
  typedef typename std::array<T, M> row;

  //----- Random access
  row& operator[](unsigned int n);
  const row& operator[](unsigned int n) const;

  //----- Iterator access
  iterator begin();
  iterator end();
  
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
Matrix<T, N, M> operator*(const T& scalar, const Matrix<T, N, M>& matrix);

template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, const T& scalar);

//----- Comparison operators
template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator==(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b);

template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator!=(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b);


//----- Tests

//=============================================================================
TEST(Matrix, dimensions)
{
  Matrix<int, 3, 3> square_matrix;
  TEST_EQUAL(square_matrix.rows(), 3);
  TEST_EQUAL(square_matrix.columns(), 3);
  TEST_EQUAL(square_matrix.elements(), 9);
  TEST_TRUE(square_matrix.square());

  Matrix<double, 1, 7> row_matrix;
  TEST_EQUAL(row_matrix.rows(), 1);
  TEST_EQUAL(row_matrix.columns(), 7);
  TEST_EQUAL(row_matrix.elements(), 7);
  TEST_FALSE(row_matrix.square());

  Matrix<std::string, 5, 1> column_matrix;
  TEST_EQUAL(column_matrix.rows(), 5);
  TEST_EQUAL(column_matrix.columns(), 1);
  TEST_EQUAL(column_matrix.elements(), 5);
  TEST_FALSE(column_matrix.square());
}

//=============================================================================
TEST(Matrix, foreach)
{
  Matrix<int, 4, 5> matrix;
  int count = 0;
  for (auto& rows: matrix) {
    for (auto& item: rows) {
      ++count;
    }
  }
  TEST_EQUAL(count, 20);
  count = 0;
  for (auto& rows: matrix) {
    for (auto& item: rows) {
      item = ++count;
    }
  }
  TEST_EQUAL(matrix[0][0], 1);
  TEST_EQUAL(matrix[0][1], 2);
  TEST_EQUAL(matrix[0][2], 3);
  TEST_EQUAL(matrix[0][3], 4);
  TEST_EQUAL(matrix[0][4], 5);
  TEST_EQUAL(matrix[1][0], 6);
  TEST_EQUAL(matrix[1][1], 7);
  TEST_EQUAL(matrix[1][2], 8);
  TEST_EQUAL(matrix[1][3], 9);
  TEST_EQUAL(matrix[1][4], 10);
  TEST_EQUAL(matrix[2][0], 11);
  TEST_EQUAL(matrix[2][1], 12);
  TEST_EQUAL(matrix[2][2], 13);
  TEST_EQUAL(matrix[2][3], 14);
  TEST_EQUAL(matrix[2][4], 15);
  TEST_EQUAL(matrix[3][0], 16);
  TEST_EQUAL(matrix[3][1], 17);
  TEST_EQUAL(matrix[3][2], 18);
  TEST_EQUAL(matrix[3][3], 19);
  TEST_EQUAL(matrix[3][4], 20);
}

//=============================================================================
TEST(Matrix, generator_constructor)
{
  Matrix<double, 3, 3> identity(
    [](unsigned int i, unsigned int j){return i == j ? 1.0 : 0.0;}
  );
  TEST_EQUAL(identity[0][0], 1);
  TEST_EQUAL(identity[0][1], 0);
  TEST_EQUAL(identity[0][2], 0);
  TEST_EQUAL(identity[1][0], 0);
  TEST_EQUAL(identity[1][1], 1);
  TEST_EQUAL(identity[1][2], 0);
  TEST_EQUAL(identity[2][0], 0);
  TEST_EQUAL(identity[2][1], 0);
  TEST_EQUAL(identity[2][2], 1);

  Matrix<double, 2, 3> additive(
    [](unsigned int i, unsigned int j){return i + j;}
  );
  TEST_EQUAL(additive[0][0], 0);
  TEST_EQUAL(additive[0][1], 1);
  TEST_EQUAL(additive[0][2], 2);
  TEST_EQUAL(additive[1][0], 1);
  TEST_EQUAL(additive[1][1], 2);
  TEST_EQUAL(additive[1][2], 3);
}

//=============================================================================
TEST(Matrix, ostream)
{
  Matrix<int, 1, 2> matrix_1;
  matrix_1[0][0] = 0;
  matrix_1[0][1] = 2;
  std::stringstream ss;
  ss << matrix_1;
  TEST_EQUAL(ss.str(), "0 2 \n");
  ss.str("");

  Matrix<double, 3, 2> matrix_2(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  ss << matrix_2;
  TEST_EQUAL(ss.str(), "0 1 \n1 2 \n2 3 \n");
  ss.str("");
  
}

//=============================================================================
TEST(Matrix, move)
{
  Matrix<int, 2, 3> matrix_1(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  auto matrix_2 = std::move(matrix_1);
  TEST_EQUAL(matrix_2[0][0], 0);
  TEST_EQUAL(matrix_2[0][1], 1);
  TEST_EQUAL(matrix_2[0][2], 2);
  TEST_EQUAL(matrix_2[1][0], 1);
  TEST_EQUAL(matrix_2[1][1], 2);
  TEST_EQUAL(matrix_2[1][2], 3);

  for (auto& rows: matrix_2) {
    for (auto& item: rows) {
      item = 5;
    }
  }
  matrix_1 = std::move(matrix_2);
  TEST_EQUAL(matrix_1[0][0], 5);
  TEST_EQUAL(matrix_1[0][1], 5);
  TEST_EQUAL(matrix_1[0][2], 5);
  TEST_EQUAL(matrix_1[1][0], 5);
  TEST_EQUAL(matrix_1[1][1], 5);
  TEST_EQUAL(matrix_1[1][2], 5);

  matrix_1 = std::move(matrix_1);
  TEST_EQUAL(matrix_1[0][0], 5);
  TEST_EQUAL(matrix_1[0][1], 5);
  TEST_EQUAL(matrix_1[0][2], 5);
  TEST_EQUAL(matrix_1[1][0], 5);
  TEST_EQUAL(matrix_1[1][1], 5);
  TEST_EQUAL(matrix_1[1][2], 5);
}

//=============================================================================
TEST(Matrix, add)
{
  Matrix<int, 2, 3> a(
    [](unsigned int, unsigned int){return 1;}
  );
  Matrix<int, 2, 3> b(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  Matrix<int, 2, 3> result = a + b;
  TEST_EQUAL(result[0][0], 1);
  TEST_EQUAL(result[0][1], 2);
  TEST_EQUAL(result[0][2], 3);
  TEST_EQUAL(result[1][0], 2);
  TEST_EQUAL(result[1][1], 3);
  TEST_EQUAL(result[1][2], 4);
}

//=============================================================================
TEST(Matrix, subtract)
{
  Matrix<int, 3, 2> a(
    [](unsigned int, unsigned int){return 5;}
  );
  Matrix<int, 3, 2> b(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  Matrix<int, 3, 2> result = a - b;
  TEST_EQUAL(result[0][0], 5);
  TEST_EQUAL(result[0][1], 4);
  TEST_EQUAL(result[1][0], 4);
  TEST_EQUAL(result[1][1], 3);
  TEST_EQUAL(result[2][0], 3);
  TEST_EQUAL(result[2][1], 2);
}

//=============================================================================
TEST(Matrix, scalar_multiplication)
{
  Matrix<int, 3, 2> a(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  Matrix<int, 3, 2> result = 2 * a;
  TEST_EQUAL(result[0][0], 0);
  TEST_EQUAL(result[0][1], 2);
  TEST_EQUAL(result[1][0], 2);
  TEST_EQUAL(result[1][1], 4);
  TEST_EQUAL(result[2][0], 4);
  TEST_EQUAL(result[2][1], 6);

  result = result * 2;
  TEST_EQUAL(result[0][0], 0);
  TEST_EQUAL(result[0][1], 4);
  TEST_EQUAL(result[1][0], 4);
  TEST_EQUAL(result[1][1], 8);
  TEST_EQUAL(result[2][0], 8);
  TEST_EQUAL(result[2][1], 12);
}

//=============================================================================
TEST(Matrix, matrix_multiplication)
{
  Matrix<int, 3, 2> a(
    [](unsigned int i, unsigned int j){return i+j;}
  );
  Matrix<int, 2, 4> b(
    [](unsigned int i, unsigned int j){return i-j;}
  );
  Matrix<int, 3, 4> result = a * b;

  // (0 1)   (0 -1 -2 -3)   (1  0 -1  -2) 
  // (1 2) * (1  0 -1 -2) = (2 -1 -4  -7)
  // (2 3)                  (3 -2 -7 -12)

  // these tests are probably unnecessary, as I assign it to the right class.
  TEST_EQUAL(result.rows(), 3);
  TEST_EQUAL(result.columns(), 4);
  TEST_EQUAL(result.elements(), 12);

  TEST_EQUAL(result[0][0],   1);
  TEST_EQUAL(result[0][1],   0);
  TEST_EQUAL(result[0][2],  -1);
  TEST_EQUAL(result[0][3],  -2);
  TEST_EQUAL(result[1][0],   2);
  TEST_EQUAL(result[1][1],  -1);
  TEST_EQUAL(result[1][2],  -4);
  TEST_EQUAL(result[1][3],  -7);
  TEST_EQUAL(result[2][0],   3);
  TEST_EQUAL(result[2][1],  -2);
  TEST_EQUAL(result[2][2],  -7);
  TEST_EQUAL(result[2][3], -12);

  double counter = 0.0;
  Matrix<double, 7, 7> square(
    [&counter](unsigned int i, unsigned int j){counter += 0.33;return counter;}
  );
  Matrix<double, 7, 7> identity(
    [](unsigned int i, unsigned int j){return i == j ? 1 : 0;}
  );
  Matrix<double, 7, 7> new_result = square * identity;
  TEST_EQUAL(new_result, square);
  new_result = identity * square;
  TEST_EQUAL(new_result, square);
}

//=============================================================================
TEST(Matrix, equality)
{
  auto ones = [](unsigned int i, unsigned int j) {return 1.0;};
  Matrix<double, 3, 2> a(ones);
  Matrix<double, 3, 3> b(ones);
  Matrix<double, 3, 2> c(ones);
  //     1 1     1 1 1     1 1
  // a = 1 1 b = 1 1 1 c = 1 1 
  //     1 1     1 1 1     1 1
  
  TEST_TRUE(a == a);
  TEST_FALSE(a == b);
  TEST_TRUE(a == c);

  TEST_FALSE(b == a);
  TEST_TRUE(b == b);
  TEST_FALSE(b == c);

  TEST_TRUE(c == a);
  TEST_FALSE(c == b);
  TEST_TRUE(c == c);

  c[2][1] = 2;
  //     1 1     1 1 1     1 1
  // a = 1 1 b = 1 1 1 c = 1 1 
  //     1 1     1 1 1     1 2
  TEST_TRUE(a == a);
  TEST_FALSE(a == b);
  TEST_FALSE(a == c);

  TEST_FALSE(b == a);
  TEST_TRUE(b == b);
  TEST_FALSE(b == c);

  TEST_FALSE(c == a);
  TEST_FALSE(c == b);
  TEST_TRUE(c == c);
}

//=============================================================================
TEST(Matrix, inequality)
{
  auto ones = [](unsigned int i, unsigned int j) {return 1.0;};
  Matrix<double, 3, 2> a(ones);
  Matrix<double, 3, 3> b(ones);
  Matrix<double, 3, 2> c(ones);
  //     1 1     1 1 1     1 1
  // a = 1 1 b = 1 1 1 c = 1 1 
  //     1 1     1 1 1     1 1
  
  TEST_FALSE(a != a);
  TEST_TRUE(a != b);
  TEST_FALSE(a != c);

  TEST_TRUE(b != a);
  TEST_FALSE(b != b);
  TEST_TRUE(b != c);

  TEST_FALSE(c != a);
  TEST_TRUE(c != b);
  TEST_FALSE(c != c);

  c[2][1] = 2;
  //     1 1     1 1 1     1 1
  // a = 1 1 b = 1 1 1 c = 1 1 
  //     1 1     1 1 1     1 2
  TEST_FALSE(a != a);
  TEST_TRUE(a != b);
  TEST_TRUE(a != c);

  TEST_TRUE(b != a);
  TEST_FALSE(b != b);
  TEST_TRUE(b != c);

  TEST_TRUE(c != a);
  TEST_TRUE(c != b);
  TEST_FALSE(c != c);
}

//=============================================================================
TEST(Matrix, transpose)
{
  Matrix<int, 2, 3> matrix(
    [](unsigned int i, unsigned int j){return i + j;}
  );
  // 0 1 2
  // 1 2 3
  Matrix<int, 3, 2> transpose = matrix.transpose();
  // 0 1
  // 1 2
  // 2 3
  Matrix<int, 3, 2> expected(
    [](unsigned int i, unsigned int j){return i + j;}
  );
  TEST_EQUAL(transpose, expected);
}

//----- Test harness

//=============================================================================
int main(int argc, char** argv)
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//----- Source

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M>::Matrix()
{
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
template <typename GENERATOR_FUNCTION>
Matrix<T, N, M>::Matrix(GENERATOR_FUNCTION generator_function)
{
  for (unsigned int i = 0; i < rows(); ++i) {
    auto& row = operator[](i);
    for (unsigned int j = 0; j < columns(); ++j) {
      row[j] = generator_function(i, j);
    }
  }
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M>::~Matrix()
{
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
typename Matrix<T, N, M>::iterator Matrix<T, N, M>::begin()
{
  return std::begin(m_matrix);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
typename Matrix<T, N, M>::iterator Matrix<T, N, M>::end()
{
  return std::end(m_matrix);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
typename Matrix<T, N, M>::const_iterator Matrix<T, N, M>::cbegin() const
{
  return m_matrix.cbegin();
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
typename Matrix<T, N, M>::const_iterator Matrix<T, N, M>::cend() const
{
  return m_matrix.cend();
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
typename Matrix<T, N, M>::row& Matrix<T, N, M>::operator[](unsigned int n)
{
  return m_matrix[n];
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
const typename Matrix<T, N, M>::row& Matrix<T, N, M>::operator[](unsigned int n) const
{
  return m_matrix[n];
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M>::Matrix(Matrix<T, N, M>&& other)
  : m_matrix(std::move(other.m_matrix))
{
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M>& Matrix<T, N, M>::operator=(Matrix<T, N, M>&& other)
{
  if (&other != this) {
    m_matrix = std::move(other.m_matrix);
  }
  return *this;
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, M, N> Matrix<T, N, M>::transpose() const
{
  auto& self = *this;
  auto transpose_function = [&self](unsigned int i, unsigned int j){
    return self[j][i];
  };
  return Matrix<T, M, N>(transpose_function);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& matrix)
{
  for (auto row_it = matrix.cbegin(); row_it != matrix.cend(); ++row_it) {
    for (auto it = row_it->cbegin(); it != row_it->cend(); ++it) {
      os << *it << " ";
    }
    os << "\n";
  }
  return os;
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b)
{
  Matrix<T, N, M> result(
    [&a, &b](unsigned int i, unsigned int j){return a[i][j] + b[i][j];}
  );
  return std::move(result);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b)
{
  Matrix<T, N, M> result(
    [&a, &b](unsigned int i, unsigned int j){return a[i][j] - b[i][j];}
  );
  return std::move(result);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& matrix, const T& scalar)
{
  Matrix<T, N, M> result(
    [&matrix, &scalar](unsigned int i, unsigned int j){return matrix[i][j] * scalar;}
  );
  return std::move(result);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M>
Matrix<T, N, M> operator*(const T& scalar, const Matrix<T, N, M>& matrix)
{
  Matrix<T, N, M> result(
    [&matrix, &scalar](unsigned int i, unsigned int j){return scalar * matrix[i][j];}
  );
  return std::move(result);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M, unsigned int P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& a, const Matrix<T, M, P>& b)
{
  auto summation = [&](unsigned int x, unsigned int y) {
    // don't want to default construct this e.g. default int is not 0,
    // dont want to initialise with 
    T sum = a[x][0] * b[0][y];
    for (unsigned int i = 1; i < M; ++i) {
      sum = sum + (a[x][i] * b[i][y]);
    }
    return sum;
  };
  return Matrix<T, N, P>(summation);
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator==(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b)
{
  if (N == P && M == Q) {
    for (unsigned int i = 0; i < N; ++i) {
      for (unsigned int j = 0; j < M; ++j) {
        if (!(a[i][j] == b[i][j])) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

//=============================================================================
template <typename T, unsigned int N, unsigned int M, unsigned int P, unsigned int Q>
bool operator!=(const Matrix<T, N, M>& a, const Matrix<T, P, Q>& b)
{
  return !(a == b);
}
