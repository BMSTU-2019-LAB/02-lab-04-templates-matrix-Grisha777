// Copyright 2018 Your Name <your_email>

#include <type_traits>
#include <limits>
#include <iostream>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_
template <class T>
class Matrix 
{
  static_assert(std::is_arithmetic<T>::value, "Non-arithmetic type");
  int rows;
  int columns;
  T** M;

 public: 
  Matrix() 
  {
    rows = 0;
    columns = 0;
    M = nullptr;
  }
  Matrix(int rows, int columns) 
  {
    this->rows = rows;
    this->columns = columns;
    M = new T*[rows];
    for (int i = 0; i < rows; i++) 
    {
      M[i] = new T[columns];
    }
    for (int i = 0; i < rows; i++) 
    {
      for (int j = 0; j < columns; j++) 
      {
        M[i][j] = 0;
      }
    }
  }

  Matrix(const Matrix& Copy) 
  {
    rows = Copy.rows;
    columns = Copy.columns;
    M = new T*[rows];
    for (int i = 0; i < rows; i++) 
    {
      M[i] = new T[columns];
    }
    for (int i = 0; i < rows; i++) 
    {
      for (int j = 0; j < columns; j++) 
      {
        M[i][j] = Copy.M[i][j];
      }
    }
  }
  Matrix& operator=(const Matrix& m) 
  {
    rows = m.rows;
    columns = m.columns;
    M = new T*[rows];
    for (int i = 0; i < rows; i++) 
    {
      M[i] = new T[columns];
    }
    for (int i = 0; i < m.rows; i++) 
    {
      for (int j = 0; j < m.columns; j++) 
      {
        M[i][j] = m.M[i][j];
      }
    }
    return *this;
  }
  Matrix operator+(const Matrix& m1) const
  {
    if (columns != m1.columns || rows != m1.rows) 
    {
      Matrix<T> error;
      return error;
    }
    Matrix<T> add(rows, columns);
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++) 
      {
        add.M[i][j] = M[i][j] + m1.M[i][j];
      }
    }
    return add;
  }

  Matrix operator-(Matrix& m2) const 
  {
    if (rows != m2.rows || columns != m2.columns) 
    {
      Matrix<T> error;
      return error;
    }
    
    Matrix<T> sub(rows, columns);
    for (int i = 0; i < rows; i++) 
    {
      for (int j = 0; j < columns; j++)
      {
        sub.M[i][j] = M[i][j] - m2.M[i][j];
      }
    }
    return sub;
  }

  Matrix operator*(Matrix& m3) const 
  {
    if (columns != m3.rows) 
    {
      Matrix<T> error;
      return error;
    }
   
    Matrix<T> Mult(rows, m3.columns);
    for (int i = 0; i < Mult.rows; i++)
    {
      for (int j = 0; j < Mult.columns; j++) 
      {
        for (int k = 0; k < columns; k++) 
        {
          Mult.M[i][j] += M[i][k] * m3.M[k][j];
        }
      }
    }
    return Mult;
  }

 
  T* operator[](int index) const 
  {
      return M[index]; 
  }
  int get_rows() const 
  {
      return rows; 
  }

  int get_columns() const 
  { 
      return columns; 
  }

  bool operator==(const Matrix& G) const 
  {
    for (int i = 0; i < rows; i++) 
    {
      for (int j = 0; j < columns; j++) 
      {
        if (M[i][j] == G[i][j]);
        else
          return false;
      }
    }
    return true;
  }

  bool operator!=(const Matrix<T>& G) const 
  {
    for (int i = 0; i < rows; i++) 
    {
      for (int j = 0; j < columns; j++) 
      {
        if (M[i][j] == G.M[i][j])
        {
          return false;
        }
      }
    }
    return true;
  }
  ~Matrix() 
  { 
      
      for (int i = 0; i < rows; i++)
      {
        delete[] M[i];
      }
      delete[] M;
      
  }
};

#endif  // INCLUDE_MATRIX_HPP_
