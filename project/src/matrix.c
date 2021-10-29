#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix* create_matrix_from_file(const char* file_path) {
    static Matrix matrix_data;
    FILE* file = fopen(file_path, "r+");
    if (file == NULL)
        return NULL;
    fscanf(file, "%zu%zu", &matrix_data.rows, &matrix_data.columns);
    matrix_data.matrix = (double**)malloc(matrix_data.rows*sizeof(double*));
    if (matrix_data.matrix == NULL) {
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < matrix_data.rows; i++) {
        matrix_data.matrix[i] = (double*)malloc(matrix_data.columns*sizeof(double));
        if (matrix_data.matrix == NULL) {
            fclose(file);
            return NULL;
        }
        for (size_t j = 0; j < matrix_data.columns; j++)
            fscanf(file, "%lf", &matrix_data.matrix[i][j]);
    }
    fclose(file);
    return &matrix_data;
}

Matrix* create_matrix(size_t rows, size_t columns) {
    static Matrix matrix_data;
    matrix_data.rows = rows;
    matrix_data.columns = columns;
    matrix_data.matrix = (double**)calloc(matrix_data.rows, sizeof(double*));
    if (matrix_data.matrix == NULL)
        return NULL;
    for (size_t i = 0; i < matrix_data.rows; i++) {
        matrix_data.matrix[i] = (double*)calloc(matrix_data.columns, sizeof(double));
        if (matrix_data.matrix == NULL)
            return NULL;
    }
    return &matrix_data;
}

void free_matrix(Matrix* matrix_data) {
    for (size_t i = 0; i < matrix_data->rows; i++)
        free(matrix_data->matrix[i]);
    free(matrix_data->matrix);
}

int get_rows(const Matrix* matrix_data, size_t* rows) {
    if ((rows != NULL) && (matrix_data != NULL)) {
        *rows = matrix_data->rows;
        return 0;
    }
    return -1;
}

int get_cols(const Matrix* matrix_data, size_t* columns) {
    if ((columns != NULL) && (matrix_data != NULL)) {
        *columns = matrix_data->columns;
        return 0;
    }
    return -1;
}

int get_elem(const Matrix* matrix_data, size_t row, size_t column, double* val) {
    if ((val != NULL) && (matrix_data != NULL)) {
        *val = matrix_data->matrix[row][column];
        return 0;
    }
    return -1;
}

int set_elem(Matrix* matrix_data, size_t row, size_t column, double val) {
    matrix_data->matrix[row][column] = val;
    if (matrix_data->matrix[row][column] == val)
        return 0;
    return -1;
}

Matrix* mul_scalar(const Matrix* matrix_data, double val) {
    if (matrix_data == NULL)
        return NULL;
    for (size_t i = 0; i < matrix_data->rows; i++) {
        for (size_t j = 0; j < matrix_data->columns; j++)
            matrix_data->matrix[i][j] *= val;
    }
    return (Matrix*)matrix_data;
}

Matrix* transp(const Matrix* old_matrix) {
    if (old_matrix == NULL)
        return NULL;
    static Matrix transposed_matrix;
    transposed_matrix.rows = old_matrix->columns;
    transposed_matrix.columns = old_matrix->rows;
    transposed_matrix.matrix = (double**)malloc(transposed_matrix.rows*sizeof(double*));
    if (transposed_matrix.matrix == NULL)
        return NULL;
    for (size_t i = 0; i < transposed_matrix.rows; i++) {
        transposed_matrix.matrix[i] = (double*)malloc(transposed_matrix.columns*sizeof(double));
        if (transposed_matrix.matrix == NULL)
            return NULL;
        for (size_t j = 0; j < transposed_matrix.columns; j++)
            transposed_matrix.matrix[i][j] = old_matrix->matrix[j][i];
    }
    return &transposed_matrix;
}

Matrix* sum(const Matrix* left, const Matrix* right) {
if ((left == NULL) || (right == NULL))
        return NULL;
    static Matrix calculated_matrix;
    calculated_matrix.rows = left->rows;
    calculated_matrix.columns = left->columns;
    printf("\nLEFT\n");
    printf("%zu %zu\n", left->rows, left->columns);
    for (size_t i = 0; i < left->rows; i++) {
        for (size_t j = 0; j < left->columns; j++)
            printf("%lf ", left->matrix[i][j]);
        printf("\n");
    }
    printf("\nRIGHT\n");
    for (size_t i = 0; i < right->rows; i++) {
        for (size_t j = 0; j < right->columns; j++)
            printf("%lf ", right->matrix[i][j]);
        printf("\n");
    }
    calculated_matrix.matrix = (double**)malloc(calculated_matrix.rows*sizeof(double*));
    if (calculated_matrix.matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix.rows; i++) {
        calculated_matrix.matrix[i] = (double*)malloc(calculated_matrix.columns*sizeof(double));
        if (calculated_matrix.matrix == NULL)
            return NULL;
        for (size_t j = 0; j < calculated_matrix.columns; j++) {
            calculated_matrix.matrix[i][j] = (left->matrix[i][j] + right->matrix[i][j]);
        }
    }
    return &calculated_matrix;
}

Matrix* sub(const Matrix* left, const Matrix* right) {
if ((left == NULL) || (right == NULL))
        return NULL;
    static Matrix calculated_matrix;
    calculated_matrix.rows = left->rows;
    calculated_matrix.columns = left->columns;
    calculated_matrix.matrix = (double**)malloc(calculated_matrix.rows*sizeof(double*));
    if (calculated_matrix.matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix.rows; i++) {
        calculated_matrix.matrix[i] = (double*)malloc(calculated_matrix.columns*sizeof(double));
        if (calculated_matrix.matrix == NULL)
            return NULL;
        for (size_t j = 0; j < calculated_matrix.columns; j++) 
            calculated_matrix.matrix[i][j] = 0;
    }
    return &calculated_matrix;
}

Matrix* mul(const Matrix* left, const Matrix* right) {
if ((left == NULL) || (right == NULL))
        return NULL;
    static Matrix calculated_matrix;
    calculated_matrix.rows = left->rows;
    calculated_matrix.columns = left->columns;
    calculated_matrix.matrix = (double**)malloc(calculated_matrix.rows*sizeof(double*));
    if (calculated_matrix.matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix.rows; i++) {
        calculated_matrix.matrix[i] = (double*)malloc(calculated_matrix.columns*sizeof(double));
        if (calculated_matrix.matrix == NULL)
            return NULL;
        for (size_t j = 0; j < calculated_matrix.columns; j++)
            calculated_matrix.matrix[i][j] = 0;
    }
    return &calculated_matrix;
}

int det(const Matrix* matrix, double* val) {
    *val = matrix->rows;
    double a =*val;
    return a;
    }

Matrix* adj(const Matrix* matrix) {return (Matrix*)matrix;}

Matrix* inv(const Matrix* matrix) {return (Matrix*)matrix;}