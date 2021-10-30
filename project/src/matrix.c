#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"

Matrix* create_matrix_from_file(const char* file_path) {
    // printf("\n************************%s************************\n", file_path);
    FILE* file = fopen(file_path, "r+");
    if (file == NULL)
        return NULL;
    size_t rows;
    size_t columns;
    fscanf(file, "%zu%zu", &rows, &columns);
    if (columns == 0 || rows == 0) {
        fclose(file);
        return NULL;
    }
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    if (matrix_data == NULL) {
        fclose(file);
        return NULL;
    }
        matrix_data->rows = rows;
    matrix_data->columns = columns;
    // if ((strcmp(file_path, "./project/tests/data/test_scalar_mul/case_0/in.txt") == 0))
    //    printf("\n****%zu %zu****\n", matrix_data->rows, matrix_data->columns);
    matrix_data->matrix = (double**)malloc(rows*sizeof(double*));
    if (matrix_data->matrix == NULL) {
        free(matrix_data);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix_data->matrix[i] = (double*)malloc(columns*sizeof(double));
        if (matrix_data->matrix[i] == NULL) {
            free(matrix_data);
            fclose(file);
            return NULL;
        }
        for (size_t j = 0; j < columns; j++)
            fscanf(file, "%lf", &matrix_data->matrix[i][j]);
    }
    fclose(file);
    // if ((strcmp(file_path, "./project/tests/data/test_scalar_mul/case_0/in.txt") == 0))
    //    printf("%p\n", matrix_data);
    return matrix_data;
}

Matrix* create_matrix(size_t rows, size_t columns) {
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    matrix_data->rows = rows;
    matrix_data->columns = columns;
    if (matrix_data->rows == 0 || matrix_data->columns == 0) {
        free(matrix_data);
        return NULL;
    }
    matrix_data->matrix = (double**)malloc(matrix_data->rows * sizeof(double*));
    for (size_t i = 0; i < matrix_data->rows; i++) {
        matrix_data->matrix[i] = (double*)calloc(matrix_data->columns, sizeof(double));
        if (matrix_data->matrix == NULL)
            return NULL;
    }
    return matrix_data;
}

void free_matrix(Matrix* matrix_data) {
    for (size_t i = 0; i < matrix_data->rows; i++)
        free(matrix_data->matrix[i]);
    free(matrix_data->matrix);
    free(matrix_data);
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
    Matrix* calculated_matrix = (Matrix*)malloc(sizeof(Matrix));
    calculated_matrix->rows = matrix_data->rows;
    calculated_matrix->columns = matrix_data->columns;
    if (calculated_matrix->rows == 0 || calculated_matrix->columns == 0) {
        free(calculated_matrix);
        return NULL;
    }
    calculated_matrix->matrix = (double**)malloc(calculated_matrix->rows*sizeof(double*));
    if (calculated_matrix->matrix == NULL) {
        free(calculated_matrix);
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        calculated_matrix->matrix[i] = (double*)malloc(calculated_matrix->columns*sizeof(double));
        if (calculated_matrix->matrix[i] == NULL) {
            free(calculated_matrix);
            return NULL;
        }
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = matrix_data->matrix[i][j] * val;
        }
    }
    return calculated_matrix;
}

Matrix* transp(const Matrix* old_matrix) {
    if (old_matrix == NULL)
        return NULL;
    Matrix* transposed_matrix = (Matrix*)malloc(sizeof(Matrix));
    transposed_matrix->rows = old_matrix->columns;
    transposed_matrix->columns = old_matrix->rows;
    if (transposed_matrix->rows == 0 || transposed_matrix->columns == 0) {
        free(transposed_matrix);
        return NULL;
    }
    transposed_matrix->matrix = (double**)malloc(transposed_matrix->rows*sizeof(double*));
    if (transposed_matrix->matrix == NULL) {
        free(transposed_matrix);
        return NULL;
    }
    for (size_t i = 0; i < transposed_matrix->rows; i++) {
        transposed_matrix->matrix[i] = (double*)malloc(transposed_matrix->columns*sizeof(double));
        if (transposed_matrix->matrix[i] == NULL) {
            free(transposed_matrix);
            return NULL;
        }
        for (size_t j = 0; j < transposed_matrix->columns; j++) {
            transposed_matrix->matrix[i][j] = old_matrix->matrix[j][i];
        }
    }
    return transposed_matrix;
}

Matrix* sum(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL)
        return NULL;
    Matrix* calculated_matrix = (Matrix*)malloc(sizeof(Matrix));
    calculated_matrix->rows = left->rows;
    calculated_matrix->columns = left->columns;
    if (calculated_matrix->rows == 0 || calculated_matrix->columns == 0) {
        free(calculated_matrix);
        return NULL;
    }
    calculated_matrix->matrix = (double**)malloc(calculated_matrix->rows*sizeof(double*));
    if (calculated_matrix->matrix == NULL) {
        free(calculated_matrix);
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        calculated_matrix->matrix[i] = (double*)malloc(calculated_matrix->columns*sizeof(double));
        if (calculated_matrix->matrix[i] == NULL) {
            free(calculated_matrix);
            return NULL;
        }
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = left->matrix[i][j] + right->matrix[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* sub(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL) {
        return NULL;
    }
    Matrix* calculated_matrix = (Matrix*)malloc(sizeof(Matrix));
    calculated_matrix->rows = left->rows;
    calculated_matrix->columns = left->columns;
    if (calculated_matrix->rows == 0 || calculated_matrix->columns == 0) {
        free(calculated_matrix);
        return NULL;
    }
    calculated_matrix->matrix = (double**)malloc(calculated_matrix->rows*sizeof(double*));
    if (calculated_matrix->matrix == NULL) {
        free(calculated_matrix);
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        calculated_matrix->matrix[i] = (double*)malloc(calculated_matrix->columns*sizeof(double));
        if (calculated_matrix->matrix[i] == NULL) {
            free(calculated_matrix);
            return NULL;
        }
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = left->matrix[i][j] - right->matrix[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* mul(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL) {
        return NULL;
    }
    Matrix* calculated_matrix = (Matrix*)malloc(sizeof(Matrix));
    calculated_matrix->rows = left->rows;
    calculated_matrix->columns = right->columns;
    /*printf("\nLEFT\n");
    printf("Rows: %zu Cols: %zu\n", left->rows, left->columns);
    for (size_t i = 0; i < left->rows; i++) {
        for (size_t j = 0; j < left->columns; j++)
            printf("%lf ", left->matrix[i][j]);
        printf("\n");
    }
    printf("\nRIGHT\n");
    printf("Rows: %zu Cols: %zu\n", right->rows, right->columns);
    for (size_t i = 0; i < right->rows; i++) {
        for (size_t j = 0; j < right->columns; j++)
            printf("%lf ", right->matrix[i][j]);
        printf("\n");
    }*/
    if (calculated_matrix->rows == 0 || calculated_matrix->columns == 0) {
        free(calculated_matrix);
        return NULL;
    }
    calculated_matrix->matrix = (double**)malloc(calculated_matrix->rows*sizeof(double*));
    if (calculated_matrix->matrix == NULL) {
        free(calculated_matrix);
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        calculated_matrix->matrix[i] = (double*)calloc(calculated_matrix->columns, sizeof(double));
        if (calculated_matrix->matrix[i] == NULL) {
            free(calculated_matrix);
            return NULL;
        }
        size_t m = 0;
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            for (size_t k = 0; k < left->columns; k++)
                calculated_matrix->matrix[i][j] += (left->matrix[i][k] * right->matrix[k][m]);
            ++m;
        }
    }
    return calculated_matrix;
}

int det(const Matrix* matrix, double* val) {
    *val = matrix->rows;
    double a =*val;
    return a;
    }

Matrix* adj(const Matrix* matrix) {return (Matrix*)matrix;}

Matrix* inv(const Matrix* matrix) {return (Matrix*)matrix;}
