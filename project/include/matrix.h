#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>


typedef struct {
    size_t rows;
    size_t columns;
    double **matrix;
} Matrix;



// Init/release operations
Matrix* create_matrix_from_file(const char* file_path);
Matrix* create_matrix(size_t rows, size_t columns);
void free_matrix(Matrix* matrix_data);

// Basic operations
int get_rows(const Matrix* matrix_data, size_t* rows);
int get_cols(const Matrix* matrix_data, size_t* columns);
int get_elem(const Matrix* matrix_data, size_t row, size_t column, double* value);
int set_elem(Matrix* matrix_data, size_t row, size_t column, double value);

// Math operations
Matrix* mul_scalar(const Matrix* matrix_data, double value);
Matrix* transp(const Matrix* old_matrix);

Matrix* sum(const Matrix* left, const Matrix* right);
Matrix* sub(const Matrix* left, const Matrix* right);
Matrix* mul(const Matrix* left, const Matrix* right);

// Extra operations
int det(const Matrix* matrix_data, double* value);
Matrix* adj(const Matrix* matrix_data);
Matrix* inv(const Matrix* matrix_data);

#endif  // PROJECT_INCLUDE_MATRIX_H_
