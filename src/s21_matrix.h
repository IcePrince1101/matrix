#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define ACCURACY 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum { OK = 0, UNCORR = 1, CALC_ERR = 2 } errors;

/* Создание и удаление */
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

/* Сравнение матриц */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/* Алгабраические операции*/
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Операции над матрицами */
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/* Вспомогательные функции */
void s21_build_minor_matrix(matrix_t A, int row, int column, matrix_t *result);
int s21_is_matrix_exist(matrix_t *A);

#endif