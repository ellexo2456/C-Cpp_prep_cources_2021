#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

Matrix* create_matrix_from_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        puts("\nError: no such file\n");
        return NULL;
    }
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix_data) {
        puts("\nError: memory`s run out\n");
        fclose(file);
        return NULL;
    }
    fscanf(file, "%zu%zu", &matrix_data->rows, &matrix_data->columns);
    if (!matrix_data->rows || !matrix_data->columns) {  // Чтобы не выделить 0 через malloc
        puts("\nError: zero count of rows or columns\n");
        free(matrix_data);
        fclose(file);
        return NULL;
    }
    matrix_data->matrix = (double**)malloc(matrix_data->rows*sizeof(double*));
    if (!matrix_data->matrix) {
        puts("\nError: memory`s run out\n");
        free(matrix_data);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < matrix_data->rows; i++) {
        matrix_data->matrix[i] = (double*)malloc(matrix_data->columns*sizeof(double));
        if (!matrix_data->matrix[i]) {
            puts("\nError: memory`s run out\n");
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
    if (!rows || !columns) {
        puts("\nError: zero count of rows or columns\n");
        return NULL;
    }
    Matrix* matrix_data = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    matrix_data->rows = rows;
    matrix_data->columns = columns;
    matrix_data->matrix = (double**)malloc(matrix_data->rows * sizeof(double*));
    if (!matrix_data->matrix) {
            puts("\nError: memory`s run out\n");
            free(matrix_data);
            return NULL;
    }
    for (size_t i = 0; i < matrix_data->rows; i++) {
        matrix_data->matrix[i] = (double*)calloc(matrix_data->columns, sizeof(double));
        if (!matrix_data->matrix[i]) {
            puts("\nError: memory`s run out\n");
            matrix_data->rows = i;
            free_matrix(matrix_data);
            return NULL;
        }
    }
    return matrix_data;
}

void free_matrix(Matrix* matrix_data) {
    if (!matrix_data) {
        puts("\nError: can`t free memory because of NULL pointer\n");
        return;
    }
    for (size_t i = 0; i < matrix_data->rows; i++)
        free(matrix_data->matrix[i]);
    free(matrix_data->matrix);
    free(matrix_data);
}

int get_rows(const Matrix* matrix_data, size_t* rows) {
    if (rows && matrix_data) {
        *rows = matrix_data->rows;
        return 0;
    }
    return -1;
}

int get_cols(const Matrix* matrix_data, size_t* columns) {
    if (columns && matrix_data) {
        *columns = matrix_data->columns;
        return 0;
    }
    return -1;
}

int get_elem(const Matrix* matrix_data, size_t row, size_t column, double* value) {
    if (value && matrix_data && row <= matrix_data->rows && column <= matrix_data->columns) {
        *value = matrix_data->matrix[row][column];
        return 0;
    }
    return -1;
}

int set_elem(Matrix* matrix_data, size_t row, size_t column, double value) {
    if (matrix_data && row <= matrix_data->rows && column <= matrix_data->columns) {
        matrix_data->matrix[row][column] = value;
        return 0;
    }
    return -1;
}

Matrix* mul_scalar(const Matrix* matrix_data, double multiplier) {
    if (!matrix_data) {
        puts("\nError: null pointer\n");
        return NULL;
    }
    Matrix* calculated_matrix_data = create_matrix(matrix_data->rows, matrix_data->columns);
    if (!calculated_matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix_data->rows; i++) {
        for (size_t j = 0; j < calculated_matrix_data->columns; j++) {
            calculated_matrix_data->matrix[i][j] = matrix_data->matrix[i][j] * multiplier;
        }
    }
        return calculated_matrix_data;
}

Matrix* transp(const Matrix* old_matrix_data) {
    if (!old_matrix_data) {
        puts("\nError: null pointer\n");
        return NULL;
    }
    Matrix* transposed_matrix_data = create_matrix(old_matrix_data->columns, old_matrix_data->rows);
    if (!transposed_matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < transposed_matrix_data->rows; i++) {
        for (size_t j = 0; j < transposed_matrix_data->columns; j++) {
                transposed_matrix_data->matrix[i][j] = old_matrix_data->matrix[j][i];
        }
    }
    return transposed_matrix_data;
}

Matrix* sum(const Matrix* left_matrix_data, const Matrix* right_matrix_data) {
    if (!left_matrix_data || !right_matrix_data || left_matrix_data->rows != right_matrix_data->rows \
    || left_matrix_data->columns != right_matrix_data->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix_data = create_matrix(left_matrix_data->rows, left_matrix_data->columns);
    if (!calculated_matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix_data->rows; i++) {
        for (size_t j = 0; j < calculated_matrix_data->columns; j++) {
            calculated_matrix_data->matrix[i][j] = left_matrix_data->matrix[i][j] \
            + right_matrix_data->matrix[i][j];
        }
    }
    return calculated_matrix_data;
}

Matrix* sub(const Matrix* left_matrix_data, const Matrix* right_matrix_data) {
    if (!left_matrix_data || !right_matrix_data || left_matrix_data->rows != right_matrix_data->rows \
    || left_matrix_data->columns != right_matrix_data->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix_data = create_matrix(left_matrix_data->rows, left_matrix_data->columns);
    if (!calculated_matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix_data->rows; i++) {
        for (size_t j = 0; j < calculated_matrix_data->columns; j++) {
            calculated_matrix_data->matrix[i][j] = \
            left_matrix_data->matrix[i][j] - right_matrix_data->matrix[i][j];
        }
    }
    return calculated_matrix_data;
}

Matrix* mul(const Matrix* left_matrix_data, const Matrix* right_matrix_data) {
    if (!left_matrix_data || !right_matrix_data || left_matrix_data->columns != right_matrix_data->rows) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix_data = create_matrix(left_matrix_data->rows, \
    right_matrix_data->columns);  // Размер матрицы B[2][4]*C[4][5]
    if (!calculated_matrix_data) {                                 // равен [2][5]
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix_data->rows; i++) {  // Последующая система циклов
        size_t m = 0;                  // позволяет вычислить каждый элемент произведения
        for (size_t j = 0; j < calculated_matrix_data->columns; j++) {  // матриц и заполнить
            for (size_t k = 0; k < left_matrix_data->columns; k++)      // ими новую матрицу
                calculated_matrix_data->matrix[i][j] += \
                (left_matrix_data->matrix[i][k] * right_matrix_data->matrix[k][m]);
            ++m;
        }
    }
    return calculated_matrix_data;
}

int det(const Matrix* matrix_data, double* determinant) {
    if (!determinant || !matrix_data || matrix_data->rows != matrix_data->columns) {
        puts("\nError: incorrect data\n");
        return -1;
    }
    if (matrix_data->rows == 2) {
        *determinant = matrix_data->matrix[0][0]*matrix_data->matrix[1][1] \
        - matrix_data->matrix[1][0]*matrix_data->matrix[0][1];
        return 0;
    }
    if (matrix_data->rows == 1) {
        *determinant = matrix_data->matrix[0][0];
        return 0;
    }
    double current_determinant = 0;
    for (size_t j = 0; j < matrix_data->columns; j++) {
        Matrix* minor_matrix_data = create_matrix(matrix_data->rows - 1, matrix_data->columns - 1);
        if (!minor_matrix_data) {
            puts("\nError: memory`s run out\n");
            return -1;
        }
        minor_matrix_data->rows = matrix_data->rows - 1;
        minor_matrix_data->columns = matrix_data->columns - 1;
        for (size_t k = 1; k < matrix_data->rows; k++) {  // Создание матрицы для
            size_t m = 0;                               // рекурсии (алгебраическое дополнение)
            for (size_t l = 0; l < matrix_data->columns; l++) {
                if (l == j)
                    continue;
                minor_matrix_data->matrix[k-1][m++] = matrix_data->matrix[k][l];
            }
        }
        if (det(minor_matrix_data, determinant) != 0) {
            puts("\nError: can`t compute determinant\n");
            free_matrix(minor_matrix_data);
            return -1;
        }
        if (j % 2 == 0)
            current_determinant += matrix_data->matrix[0][j] * *determinant;
        else
            current_determinant += -matrix_data->matrix[0][j] * *determinant;
        free_matrix(minor_matrix_data);
    }
    *determinant = current_determinant;
    return 0;
}

Matrix* adj(const Matrix* matrix_data) {
    if (!matrix_data || matrix_data->rows != matrix_data->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    if (matrix_data->rows == 1)
        return (Matrix*)matrix_data;
    Matrix* transposed_matrix_data = transp(matrix_data);
    if (!transposed_matrix_data) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    Matrix* adjugate_matrix_data = create_matrix(matrix_data->rows, matrix_data->columns);
    if (!adjugate_matrix_data) {
        puts("\nError: memory`s run out\n");
        free_matrix(transposed_matrix_data);
        return NULL;
    }
    for (size_t i = 0; i < adjugate_matrix_data->rows; i++) {  // Два цикла для заполнения
        for (size_t j = 0; j < adjugate_matrix_data->columns; j++) {  // дополнительной матрицы
            Matrix* minor_matrix_data = create_matrix(transposed_matrix_data->rows - 1,
            transposed_matrix_data->columns - 1);
            if (!minor_matrix_data) {
                puts("\nError: memory`s run out\n");
                free_matrix(adjugate_matrix_data);
                free_matrix(transposed_matrix_data);
                return NULL;
            }
            size_t m = 0;  // Счётчик для заполнения минора
            for (size_t k = 0; k < transposed_matrix_data->rows; k++) {  // Два цикла для перебора
                size_t n = 0;  // Счётчик для заполнения минора
                for (size_t l = 0; l < transposed_matrix_data->columns; l++) {  // транспонированной матрицы
                    if (k == i || l == j) {
                        continue;
                    }
                    minor_matrix_data->matrix[m][n++] = transposed_matrix_data->matrix[k][l];
                }
                if (k != i)
                    m++;
            }
            double minor = 0;
            if (det(minor_matrix_data, &minor) != 0) {
                puts("\nError: can`t compute determinant\n");
                free_matrix(minor_matrix_data);
                free_matrix(adjugate_matrix_data);
                free_matrix(transposed_matrix_data);
                return NULL;
            }
            adjugate_matrix_data->matrix[i][j] = pow(-1, i + j)*minor;
            free_matrix(minor_matrix_data);
        }
    }
    free_matrix(transposed_matrix_data);
    return (Matrix*)adjugate_matrix_data;
}

Matrix* inv(const Matrix* matrix_data) {
    double determinant = 0;
    if (det(matrix_data, &determinant))
        return NULL;
    return mul_scalar(adj(matrix_data), 1 / (determinant*determinant));
}
