#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), matrix(rows, std::vector<double> (cols, 0)) {}

    Matrix::Matrix(std::istream& is) {
        if (is.eof()) {throw prep::InvalidMatrixStream();}
        is >> rows >> cols;
        int elements_count = 0;
        int row = 0;
        int col = 0;
        std::string number;
        while (is >> number) {
            for (auto digit: number) {
                if (!std::isdigit(digit)) {throw prep::InvalidMatrixStream();}
            }
            if (col == cols) {
                col = 0;
                ++row;
            }
            matrix[row].emplace_back(std::strtod(number.c_str(), nullptr));
            ++col;
            ++elements_count;
        }
        if (rows * cols != elements_count) {throw prep::InvalidMatrixStream();}
    }

    size_t Matrix::getRows() const{
        return rows;
    }

    size_t Matrix::getCols() const{
        return cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i * j >= cols * rows) {throw OutOfRange(i, j, *this); }
        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i * j >= cols * rows) {throw OutOfRange(i, j, *this); }
        return matrix[i][j];
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.rows << matrix.cols;
        for (row : matrix.matrix) {
            for (col : row) {

            }
        }
    }
}
