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
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) {
        puts("\nError: memory`s run out\n");
        fclose(file);
        return NULL;
    }
    if (fscanf(file, "%zu%zu", &matrix->rows, &matrix->columns) != 2) {
        puts("\nError: incorrect count of arguments\n");
        free(matrix);
        fclose(file);
        return NULL;
    }
    if (!matrix->rows || !matrix->columns) {  // Чтобы не выделить 0 через malloc
        puts("\nError: zero count of rows or columns\n");
        free(matrix);
        fclose(file);
        return NULL;
    }
    matrix->values = (double**)malloc(matrix->rows*sizeof(double*));
    if (!matrix->values) {
        puts("\nError: memory`s run out\n");
        free(matrix);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; ++i) {
        matrix->values[i] = (double*)malloc(matrix->columns*sizeof(double));
        if (!matrix->values[i]) {
            puts("\nError: memory`s run out\n");
            matrix->rows = i;
            free_matrix(matrix);  // Удаление всего выделенного до массива matrix->values[i]
            fclose(file);
            return NULL;
        }
        for (size_t j = 0; j < matrix->columns; ++j)
            if (fscanf(file, "%lf", &matrix->values[i][j]) != 1) {
                puts("\nError: incorrect count of arguments\n");
                free_matrix(matrix);
                fclose(file);
                return NULL;
            }
    }
    fclose(file);
    return matrix;
}

Matrix* create_matrix(size_t rows, size_t columns) {
    if (!rows || !columns) {
        puts("\nError: zero count of rows or columns\n");
        return NULL;
    }
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->values = (double**)malloc(matrix->rows * sizeof(double*));
    if (!matrix->values) {
            puts("\nError: memory`s run out\n");
            free(matrix);
            return NULL;
    }
    for (size_t i = 0; i < matrix->rows; ++i) {
        matrix->values[i] = (double*)calloc(matrix->columns, sizeof(double));
        if (!matrix->values[i]) {
            puts("\nError: memory`s run out\n");
            matrix->rows = i;
            free_matrix(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(Matrix* matrix) {
    if (!matrix) {
        puts("\nError: can`t free memory because of NULL pointer\n");
        return;
    }
    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

int get_rows(const Matrix* matrix, size_t* rows) {
    if (rows && matrix) {
        *rows = matrix->rows;
        return 0;
    }
    return -1;
}

int get_cols(const Matrix* matrix, size_t* columns) {
    if (columns && matrix) {
        *columns = matrix->columns;
        return 0;
    }
    return -1;
}

int get_elem(const Matrix* matrix, size_t row, size_t column, double* value) {
    if (value && matrix && row <= matrix->rows && column <= matrix->columns) {
        *value = matrix->values[row][column];
        return 0;
    }
    return -1;
}

int set_elem(Matrix* matrix, size_t row, size_t column, double value) {
    if (matrix && row <= matrix->rows && column <= matrix->columns) {
        matrix->values[row][column] = value;
        return 0;
    }
    return -1;
}

Matrix* mul_scalar(const Matrix* matrix, double multiplier) {
    if (!matrix) {
        puts("\nError: null pointer\n");
        return NULL;
    }
    Matrix* calculated_matrix = create_matrix(matrix->rows, matrix->columns);
    if (!calculated_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; ++i) {
        for (size_t j = 0; j < calculated_matrix->columns; ++j) {
            calculated_matrix->values[i][j] = matrix->values[i][j] * multiplier;
        }
    }
    return calculated_matrix;
}

Matrix* transp(const Matrix* old_matrix) {
    if (!old_matrix) {
        puts("\nError: null pointer\n");
        return NULL;
    }
    Matrix* transposed_matrix = create_matrix(old_matrix->columns, old_matrix->rows);
    if (!transposed_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < transposed_matrix->rows; ++i) {
        for (size_t j = 0; j < transposed_matrix->columns; ++j) {
                transposed_matrix->values[i][j] = old_matrix->values[j][i];
        }
    }
    return transposed_matrix;
}

Matrix* sum(const Matrix* left_matrix, const Matrix* right_matrix) {
    if (!left_matrix || !right_matrix || left_matrix->rows != right_matrix->rows \
    || left_matrix->columns != right_matrix->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix = create_matrix(left_matrix->rows, left_matrix->columns);
    if (!calculated_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; ++i) {
        for (size_t j = 0; j < calculated_matrix->columns; ++j) {
            calculated_matrix->values[i][j] = left_matrix->values[i][j] \
            + right_matrix->values[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* sub(const Matrix* left_matrix, const Matrix* right_matrix) {
    if (!left_matrix || !right_matrix) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    if (left_matrix->rows != right_matrix->rows || left_matrix->columns != right_matrix->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix = create_matrix(left_matrix->rows, left_matrix->columns);
    if (!calculated_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; ++i) {
        for (size_t j = 0; j < calculated_matrix->columns; ++j) {
            calculated_matrix->values[i][j] = \
            left_matrix->values[i][j] - right_matrix->values[i][j];
        }
    }
    return calculated_matrix;
}

Matrix* mul(const Matrix* left_matrix, const Matrix* right_matrix) {
    if (!left_matrix || !right_matrix || left_matrix->columns != right_matrix->rows) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* calculated_matrix = create_matrix(left_matrix->rows, \
    right_matrix->columns);
    if (!calculated_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    for (size_t i = 0; i < calculated_matrix->rows; ++i) {  // Последующая система циклов
        size_t m = 0;                  // позволяет вычислить каждый элемент произведения
        for (size_t j = 0; j < calculated_matrix->columns; ++j) {  // матриц и заполнить
            for (size_t k = 0; k < left_matrix->columns; ++k) {    // ими новую матрицу
                calculated_matrix->values[i][j] += \
                (left_matrix->values[i][k] * right_matrix->values[k][m]);
            }
            ++m;
        }
    }
    return calculated_matrix;
}

int det(const Matrix* matrix, double* determinant) {
    if (!determinant || !matrix || matrix->rows != matrix->columns) {
        puts("\nError: incorrect data\n");
        return -1;
    }
    if (matrix->rows == 2) {
        *determinant = matrix->values[0][0]*matrix->values[1][1] \
        - matrix->values[1][0]*matrix->values[0][1];
        return 0;
    }
    if (matrix->rows == 1) {
        *determinant = matrix->values[0][0];
        return 0;
    }
    double current_determinant = 0;
    for (size_t j = 0; j < matrix->columns; ++j) {
        Matrix* minor_matrix = create_matrix(matrix->rows - 1, matrix->columns - 1);
        if (!minor_matrix) {
            puts("\nError: memory`s run out\n");
            return -1;
        }
        minor_matrix->rows = matrix->rows - 1;
        minor_matrix->columns = matrix->columns - 1;
        for (size_t k = 1; k < matrix->rows; ++k) {  // Создание матрицы для
            size_t m = 0;                               // рекурсии (алгебраическое дополнение)
            for (size_t l = 0; l < matrix->columns; ++l) {
                if (l == j)
                    continue;
                minor_matrix->values[k-1][m++] = matrix->values[k][l];
            }
        }
        if (det(minor_matrix, determinant) != 0) {
            puts("\nError: can`t compute determinant\n");
            free_matrix(minor_matrix);
            return -1;
        }
        if (j % 2 == 0) {
            current_determinant += matrix->values[0][j] * *determinant;
        } else {
            current_determinant += -matrix->values[0][j] * *determinant;
        }
        free_matrix(minor_matrix);
    }
    *determinant = current_determinant;
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (!matrix || matrix->rows != matrix->columns) {
        puts("\nError: incorrect data\n");
        return NULL;
    }
    Matrix* transposed_matrix = transp(matrix);
    if (!transposed_matrix) {
        puts("\nError: memory`s run out\n");
        return NULL;
    }
    Matrix* adjugate_matrix = create_matrix(matrix->rows, matrix->columns);
    if (!adjugate_matrix) {
        puts("\nError: memory`s run out\n");
        free_matrix(transposed_matrix);
        return NULL;
    }
    if (matrix->rows == 1) {
        adjugate_matrix->values[0][0] = 1;
        free_matrix(transposed_matrix);
        return adjugate_matrix;
    }
    for (size_t i = 0; i < adjugate_matrix->rows; ++i) {  // Два цикла для заполнения
        for (size_t j = 0; j < adjugate_matrix->columns; ++j) {  // дополнительной матрицы
            Matrix* minor_matrix = create_matrix(transposed_matrix->rows - 1,
            transposed_matrix->columns - 1);
            if (!minor_matrix) {
                puts("\nError: memory`s run out\n");
                free_matrix(adjugate_matrix);
                free_matrix(transposed_matrix);
                return NULL;
            }
            size_t m = 0;  // Счётчик для заполнения минора
            for (size_t k = 0; k < transposed_matrix->rows; ++k) {  // Два цикла для перебора
                size_t n = 0;  // Счётчик для заполнения минора
                for (size_t l = 0; l < transposed_matrix->columns; ++l) {  // транспонированной матрицы
                    if (k == i || l == j) {
                        continue;
                    }
                    minor_matrix->values[m][n++] = transposed_matrix->values[k][l];
                }
                if (k != i) {
                    ++m;
                }
            }
            double minor = 0;
            if (det(minor_matrix, &minor) || double_equality(minor, 0.)) {
                puts("\nError: can`t compute determinant\n");
                free_matrix(minor_matrix);
                free_matrix(adjugate_matrix);
                free_matrix(transposed_matrix);
                return NULL;
            }
            adjugate_matrix->values[i][j] = pow(-1, i + j)*minor;
            free_matrix(minor_matrix);
        }
    }
    free_matrix(transposed_matrix);
    return (Matrix*)adjugate_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        puts("\nError: null pointer\n");
        return NULL;
    }
    double determinant = 0;
    if (det(matrix, &determinant) || double_equality(determinant, 0.)) {  // Проверка
        puts("\nError: can`t compute inverse matrix\n");  // на квадратность пройдёт внутри det()
        return NULL;
    }
    Matrix* adjugate_matrix = adj(matrix);
    if (!adjugate_matrix) {
        puts("\nError: can`t compute inverse matrix\n");
        return NULL;
    }
    Matrix* inverse_matrix = mul_scalar(adjugate_matrix, 1 / determinant);
    free_matrix(adjugate_matrix);
    if (!inverse_matrix) {
        puts("\nError: can`t compute inverse matrix\n");
        return NULL;
    }
    return inverse_matrix;
}

int double_equality(double left, double right) {
    return fabs(left - right) < 1e-15;
}
