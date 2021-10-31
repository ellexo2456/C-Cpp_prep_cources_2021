#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

Matrix* create_matrix_from_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL)
        return NULL;
    // printf("\n***********%s***********\n", file_path);
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

int det(const Matrix* matrix_data, double* value) {
    if (value == NULL || matrix_data == NULL)
        return -1;
    /*for (size_t i = 0; i < matrix_data->rows; i++) {
        for (size_t j = 0; j < matrix_data->columns; j++) {
            printf("%lf ", matrix_data->matrix[i][j]);
        }
        puts("\n");
    }
    puts("\n"); */
    if (matrix_data->rows == 2) {
        *value = matrix_data->matrix[0][0]*matrix_data->matrix[1][1] \
        - matrix_data->matrix[1][0]*matrix_data->matrix[0][1];
        return 0;
    }
    if (matrix_data->rows == 1) {
        *value = matrix_data->matrix[0][0];
        return 0;
    }
    double current_value = 0;
    for (size_t j = 0; j < matrix_data->columns; j++) {
        Matrix* decomposition_matrix = create_matrix(matrix_data->rows - 1, matrix_data->columns - 1);
        if (decomposition_matrix == NULL)
            return -1;
        decomposition_matrix->rows = matrix_data->rows - 1;
        decomposition_matrix->columns = matrix_data->columns - 1;
        for (size_t k = 1; k < matrix_data->rows; k++) {  // Создание матрицы для рекурсии
            size_t m = 0;
            for (size_t l = 0; l < matrix_data->columns; l++) {
                if (l == j)
                    continue;
                decomposition_matrix->matrix[k-1][m++] = matrix_data->matrix[k][l];
                // printf("%lf ", decomposition_matrix->matrix[k-1][m++]);
            }
           // puts("\n\n");
        }
        if (det(decomposition_matrix, value) != 0)
            return -1;
        current_value += pow(-1, j) * matrix_data->matrix[0][j] * *value;
        free_matrix(decomposition_matrix);
        // printf("\n%lf\n%lf\n", matrix_data->matrix[0][j], *value);
    }
    *value = current_value;
    return 0;
}

Matrix* adj(const Matrix* matrix_data) {
    if (matrix_data == NULL)
        return NULL;
    Matrix* transposed_matrix = transp(matrix_data);
    if (transposed_matrix == NULL)
        return NULL;
    Matrix* adjugate_matrix = create_matrix(matrix_data->rows, matrix_data->columns);
    if (adjugate_matrix == NULL) {
        free_matrix(transposed_matrix);
        return NULL;
    }
    for (size_t i = 0; i < adjugate_matrix->rows; i++) {  // Два цикла для заполнения
        for (size_t j = 0; j < adjugate_matrix->columns; j++) {  // дополнительной матрицы
            Matrix* cofactor_matrix = create_matrix(transposed_matrix->rows - 1, \
            transposed_matrix->columns - 1);
            if (cofactor_matrix == NULL) {
                free_matrix(adjugate_matrix);
                free_matrix(transposed_matrix);
                return NULL;
            }
            size_t m = 0;
            for (size_t k = 0; k < transposed_matrix->rows; k++) {  // Два цикла для перебора
                size_t n = 0;
                for (size_t l = 0; l < transposed_matrix->columns; l++) {  // транспонированной матрицы
                    if (k == i || l == j) {
                        continue;
                    }
                    cofactor_matrix->matrix[m][n++] = transposed_matrix->matrix[k][l];
                    // printf("%lf ", cofactor_matrix->matrix[m][n]);
                    // n++;
                    /*printf("%lf\n", cofactor_matrix->matrix[m][n]);
                    for (size_t i = 0; i < cofactor_matrix->rows; i++) {
                        for (size_t j = 0; j < cofactor_matrix->columns; j++) {
                            printf("%lf ", cofactor_matrix->matrix[i][j]);
                            printf(" %zu %zu   ", i, j);
                        }
                        puts("\n");
                    }
                    puts("\n");*/
                }
                // puts("\n");
                if (k != i)
                    m++;
            }
            double minor = 0;
            if (det(cofactor_matrix, &minor) != 0) {
                free_matrix(adjugate_matrix);
                free_matrix(transposed_matrix);
                free_matrix(cofactor_matrix);
                return NULL;
            }
            adjugate_matrix->matrix[i][j] = pow(-1, i + j)*minor;
            free_matrix(cofactor_matrix);
        }
    }
    free_matrix(transposed_matrix);
    return (Matrix*)adjugate_matrix;
}


Matrix* inv(const Matrix* matrix_data) {
    double determinant = 0;
    return mul_scalar(adj(matrix_data), pow(determinant, -1));
}
