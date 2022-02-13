#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0)) {}

    Matrix::Matrix(std::istream &is) {
//        std::cout << is.rdbuf()->in_avail() << std::endl;
        is >> rows >> cols;
        if (!is) { throw InvalidMatrixStream(); }
//        std::cout << rows << ' ' << cols << ' ' << is.fail() << std::endl;
        matrix = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                is >> matrix[i][j];
                if (!is) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const {
        return rows;
    }

    size_t Matrix::getCols() const {
        return cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i * j >= cols * rows) { throw OutOfRange(i, j, *this); }
        return matrix[i][j];
    }

    double &Matrix::operator()(size_t i, size_t j) {
        if (i * j >= cols * rows) { throw OutOfRange(i, j, *this); }
        return matrix[i][j];
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) { return false; }
        bool flag = true;
        for (size_t i = 0, j = 0; i < rows || j < rhs.rows; ++i, ++j) {
            for (size_t k = 0, l = 0; k < cols || l < rhs.cols; ++k, ++l) {
                if (std::fabs(matrix[i][k] - rhs.matrix[j][l]) > std::numeric_limits<double>::epsilon()) {
                    flag = false;
                }
            }
        }
        return flag;
    }

    bool Matrix::operator!=(const Matrix &rhs) const {
        return !operator==(rhs);
    }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.rows << ' ' << matrix.cols << std::endl;
        for (auto row: matrix.matrix) {
            for (auto col: row) {
                os << col << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) { throw DimensionMismatch(*this, rhs); }
        Matrix sum(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sum.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return sum;
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) { throw DimensionMismatch(*this, rhs); }
        Matrix sum(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sum.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return sum;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (cols != rhs.rows) { throw DimensionMismatch(*this, rhs); }
        Matrix multiplicate_matrix(rows, rhs.cols);
        for (size_t i = 0; i < multiplicate_matrix.rows; ++i) {
            size_t m = 0;
            for (size_t j = 0; j < multiplicate_matrix.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    multiplicate_matrix.matrix[i][j] += (matrix[i][k] * rhs.matrix[k][m]);
                }
                ++m;
            }
        }
        return multiplicate_matrix;
    }

    Matrix Matrix::transp() const {
        Matrix transposed(cols, rows);
        for (size_t i = 0; i < transposed.rows; ++i) {
            for (size_t j = 0; j < transposed.cols; ++j) {
                transposed.matrix[i][j] = matrix[j][i];
            }
        }
        return transposed;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix miltiplicated(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                miltiplicated.matrix[i][j] = val * matrix[i][j];
            }
        }
        return miltiplicated;
    }

    Matrix operator*(double val, const Matrix &matrix) {
        return matrix * val;
    }

    double Matrix::det() const {
        if (cols != rows) { throw DimensionMismatch(*this); }
        double determinant = 0;
        if (rows == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        }
        if (rows == 1) {
            return matrix[0][0];
        }
        for (size_t j = 0; j < cols; ++j) {
            Matrix minor(rows - 1, cols - 1);
            for (size_t k = 1; k < rows; ++k) {
                size_t m = 0;
                for (size_t l = 0; l < cols; ++l) {
                    if (l == j)
                        continue;
                    minor.matrix[k - 1][m++] = matrix[k][l];
                }
            }
            if (j % 2 == 0) {
                determinant += matrix[0][j] * minor.det();
            } else {
                determinant += -matrix[0][j] * minor.det();
            }
        }
        return determinant;
    }

    Matrix Matrix::adj() const {
        if (cols != rows) { throw DimensionMismatch(*this); }
        Matrix adjugated(rows, cols);
        if (rows == 1) {
            adjugated.matrix[0][0] = 1;
            return adjugated;
        }
        Matrix transposed = transp();
        for (size_t i = 0; i < adjugated.rows; ++i) {
            for (size_t j = 0; j < adjugated.cols; ++j) {
                Matrix minor(transposed.rows - 1, transposed.cols - 1);
                size_t m = 0;
                for (size_t k = 0; k < transposed.rows; ++k) {
                    size_t n = 0;
                    for (size_t l = 0; l < transposed.cols; ++l) {
                        if (k == i || l == j) {
                            continue;
                        }
                        minor.matrix[m][n++] = transposed.matrix[k][l];
                    }
                    if (k != i) {
                        ++m;
                    }
                }
                adjugated.matrix[i][j] = pow(-1, i + j) * minor.det();
            }
        }
        return adjugated;
    }

    Matrix Matrix::inv() const {
        double determinant = det();
        if (determinant == 0) { throw SingularMatrix(); }
        return adj() * (1 / determinant);
    }
}
