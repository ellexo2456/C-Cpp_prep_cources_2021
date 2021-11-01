#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>


typedef struct {
    size_t rows;
    size_t columns;
    double **values;
} Matrix;



// Init/release operations
Matrix* create_matrix_from_file(const char* file_path);
Matrix* create_matrix(size_t rows, size_t columns);
void free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* columns);
int get_elem(const Matrix* matrix, size_t row, size_t column, double* value);
int set_elem(Matrix* matrix, size_t row, size_t column, double value);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double multiplier);
Matrix* transp(const Matrix* old_matrix);

Matrix* sum(const Matrix* left_matrix, const Matrix* right_matrix);
Matrix* sub(const Matrix* left_matrix, const Matrix* right_matrix);
Matrix* mul(const Matrix* left_matrix, const Matrix* right_matrix);

// Extra operations
int det(const Matrix* matrix, double* determinant);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_
