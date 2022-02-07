#include "matrix.h"
#include "exceptions.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), matrix(rows, std::vector<double> (cols, 0)) {}
}
