#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"

Matrix* create_matrix_from_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL)
        return NULL;
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    if (matrix_data == NULL) {
        fclose(file);
        return NULL;
    }
    fscanf(file, "%zu%zu", &matrix_data->rows, &matrix_data->columns);
    if (matrix_data->rows == 0 || matrix_data->columns == 0) {  // Чтобы не выделить 0 через malloc
        free(matrix_data);
        fclose(file);
        return NULL;
    }
    matrix_data->matrix = (double**)malloc(matrix_data->rows*sizeof(double*));
    if (matrix_data->matrix == NULL) {
        free(matrix_data);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < matrix_data->rows; i++) {
        matrix_data->matrix[i] = (double*)malloc(matrix_data->columns*sizeof(double));
        if (matrix_data->matrix[i] == NULL) {
            matrix_data->rows = i;
            free_matrix(matrix_data);  // Удаление всего выделенного до массива matrix_data->matrix[i]
            fclose(file);
            return NULL;
        }
        for (size_t j = 0; j < matrix_data->columns; j++)
            fscanf(file, "%lf", &matrix_data->matrix[i][j]);
    }
    fclose(file);
    return matrix_data;
}

Matrix* create_matrix(size_t rows, size_t columns) {
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    if (matrix_data == NULL)
        return NULL;
    matrix_data->rows = rows;
    matrix_data->columns = columns;
    if (matrix_data->rows == 0 || matrix_data->columns == 0) {
        free(matrix_data);
        return NULL;
    }
    matrix_data->matrix = (double**)malloc(matrix_data->rows * sizeof(double*));
    if (matrix_data->matrix == NULL) {
            free(matrix_data);
            return NULL;
    }
    for (size_t i = 0; i < matrix_data->rows; i++) {
        matrix_data->matrix[i] = (double*)calloc(matrix_data->columns, sizeof(double));
        if (matrix_data->matrix[i] == NULL) {
            matrix_data->rows = i;
            free_matrix(matrix_data);
            return NULL;
        }
    }
    return matrix_data;
}

void free_matrix(Matrix* matrix_data) {
    if (matrix_data == NULL) {
        puts("Can`t free memory because of NULL pointer");
        return;
    }
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

int get_elem(const Matrix* matrix_data, size_t row, size_t column, double* value) {
    if ((value != NULL) && (matrix_data != NULL) && \
    (row <= matrix_data->rows) && (column <= matrix_data->columns)) {
        *value = matrix_data->matrix[row][column];
        return 0;
    }
    return -1;
}

int set_elem(Matrix* matrix_data, size_t row, size_t column, double value) {
    if ((matrix_data != NULL) && (row <= matrix_data->rows) && (column <= matrix_data->columns)) {
        matrix_data->matrix[row][column] = value;
        return 0;
    }
    return -1;
}

Matrix* mul_scalar(const Matrix* matrix_data, double value) {
    if (matrix_data == NULL)
        return NULL;
    Matrix* calculated_matrix = create_matrix(matrix_data->rows, matrix_data->columns);
    if (calculated_matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = matrix_data->matrix[i][j] * value;
        }
    }
    return calculated_matrix;
}

Matrix* transp(const Matrix* old_matrix) {
    if (old_matrix == NULL)
        return NULL;
    Matrix* transposed_matrix = create_matrix(old_matrix->columns, old_matrix->rows);
    if (transposed_matrix == NULL)
        return NULL;
    for (size_t i = 0; i < transposed_matrix->rows; i++) {
        for (size_t j = 0; j < transposed_matrix->columns; j++) {
                transposed_matrix->matrix[i][j] = old_matrix->matrix[j][i];
        }
    }
    return transposed_matrix;
}

Matrix* sum(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL)
        return NULL;
    Matrix* calculated_matrix = create_matrix(left->rows, left->columns);
    if (calculated_matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = left->matrix[i][j] + right->matrix[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* sub(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL)
        return NULL;
    Matrix* calculated_matrix = create_matrix(left->rows, left->columns);
    if (calculated_matrix == NULL)
        return NULL;
    for (size_t i = 0; i < calculated_matrix->rows; i++) {
        for (size_t j = 0; j < calculated_matrix->columns; j++) {
            calculated_matrix->matrix[i][j] = left->matrix[i][j] - right->matrix[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* mul(const Matrix* left, const Matrix* right) {
    if (left == NULL || right == NULL)
        return NULL;
    Matrix* calculated_matrix = create_matrix(left->rows, right->columns);  // Размер матрицы B[2][4]*C[4][5]
    if (calculated_matrix == NULL)                                     // равен [2][5]
        return NULL;
    for (size_t i = 0; i < calculated_matrix->rows; i++) {  // Последующая система циклов
        size_t m = 0;                  // позволяет вычислить каждый элемент произведения
        for (size_t j = 0; j < calculated_matrix->columns; j++) {  // матриц и заполнить ими новую матрицу
            for (size_t k = 0; k < left->columns; k++)
                calculated_matrix->matrix[i][j] += (left->matrix[i][k] * right->matrix[k][m]);
            ++m;
        }
    }
    return calculated_matrix;
}

int det(const Matrix* matrix, double* value) {  // Заглушки для пока не используемых функций
    *value = matrix->rows;
    double a =*value;
    return a;
    }

Matrix* adj(const Matrix* matrix) {return (Matrix*)matrix;}

Matrix* inv(const Matrix* matrix) {return (Matrix*)matrix;}
