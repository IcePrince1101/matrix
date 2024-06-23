#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  /*
  Создание матрицы.
  Args:
   - rows: кол-во строк
   - columns: кол-во столбцов
   - result: указатель на матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны (указатель на матрицу существует, строк
  и столбцы > 0)
  */
  int code = (rows <= 0 || columns <= 0 || result == NULL) ? UNCORR : OK;
  if (code == OK) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return code;
}

void s21_remove_matrix(matrix_t *A) {
  /*
  Удаление матрицы.
  Args:
   - A: указатель на матрицу
  */
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  /*
  Сравнение матриц.
  Args:
   - A: указатель на матрицу
   - B: указатель на матрицу
  Returns:
   - SUCCESS: если матрицы равны
   - FAILURE: если матрицы не равны или разные по размерам
  */
  int code = (s21_is_matrix_exist(A) || s21_is_matrix_exist(B) ||
              A->rows != B->rows || A->columns != B->columns)
                 ? FAILURE
                 : SUCCESS;
  if (code == SUCCESS) {
    for (int i = 0; i < A->rows && code == SUCCESS; ++i) {
      for (int j = 0; j < A->columns && code == SUCCESS; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > ACCURACY) code = FAILURE;
      }
    }
  }
  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /*
  Сложение матриц.
  Args:
   - A: указатель на матрицу
   - B: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрицы разного размера
  */
  int code = (s21_is_matrix_exist(A) || s21_is_matrix_exist(B) || !result)
                 ? UNCORR
                 : OK;
  if (code == OK)
    code = (A->rows != B->rows || A->columns != B->columns) ? CALC_ERR : code;
  if (code == OK) {
    result->rows = A->rows;
    result->columns = A->columns;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /*
  Вычитание матриц.
  Args:
   - A: указатель на матрицу
   - B: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрицы разного размера
  */
  int code = (s21_is_matrix_exist(A) || s21_is_matrix_exist(B) || !result)
                 ? UNCORR
                 : OK;
  if (code == OK)
    code = (A->rows != B->rows || A->columns != B->columns) ? CALC_ERR : code;
  if (code == OK) {
    result->rows = A->rows;
    result->columns = A->columns;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  /*
  Умножение матрицы на число.
  Args:
   - A: указатель на матрицу
   - number: число
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
  */
  int code = (s21_is_matrix_exist(A) || !result) ? UNCORR : OK;
  if (code == OK) {
    result->rows = A->rows;
    result->columns = A->columns;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /*
  Умножение матриц.
  Args:
   - A: указатель на матрицу
   - B: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрицы неправильного размера (строки первой не равны
  столбцам второй)
  */
  int code = (s21_is_matrix_exist(A) || s21_is_matrix_exist(B) || !result)
                 ? UNCORR
                 : OK;
  if (code == OK) code = (A->columns != B->rows) ? CALC_ERR : code;
  if (code == OK) {
    result->rows = A->rows;
    result->columns = B->columns;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  /*
  Транспонирование матрицы.
  Args:
   - A: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
  */
  int code = (s21_is_matrix_exist(A) || !result) ? UNCORR : OK;
  if (code == OK) {
    result->rows = A->columns;
    result->columns = A->rows;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  /*
  Вычисление обратной матрицы.
  Args:
   - A: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрица неправильного размера (не квадратная)
  */
  int code = (s21_is_matrix_exist(A) || !result) ? UNCORR : OK;
  if (code == OK) code = A->rows != A->columns ? CALC_ERR : code;
  if (code == OK) {
    result->rows = A->rows;
    result->columns = A->columns;
    s21_create_matrix(result->rows, result->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        matrix_t tmp;
        double det = 0;
        s21_build_minor_matrix(*A, i, j, &tmp);
        s21_determinant(&tmp, &det);
        result->matrix[i][j] = pow(-1, i + j) * det;
        s21_remove_matrix(&tmp);
      }
    }
  }
  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  /*
  Вычисление определителя матрицы.
  Args:
   - A: указатель на матрицу
   - result: указатель на результирующее число
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрица неправильного размера (не квадратная)
  */
  int code = (s21_is_matrix_exist(A) || !result) ? UNCORR : OK;
  if (code == OK) code = A->rows != A->columns ? CALC_ERR : code;
  if (code == OK) {
    *result = 0;
    if (A->rows == 1)
      *result = A->matrix[0][0];
    else if (A->rows == 2)
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    else {
      for (int j = 0; j < A->columns; ++j) {
        matrix_t tmp;
        double det = 0;
        s21_build_minor_matrix(*A, 0, j, &tmp);
        s21_determinant(&tmp, &det);
        *result += (((j) << 31) >> 31 ? -1 : 1) * A->matrix[0][j] * det;
        s21_remove_matrix(&tmp);
      }
    }
  }
  return code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  /*
  Вычисление обратной матрицы.
  Args:
   - A: указатель на матрицу
   - result: указатель на результирующую матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
   - CALC_ERR: если матрица неправильного размера (не квадратная)
  */
  int code = (s21_is_matrix_exist(A) || !result) ? UNCORR : OK;
  if (code == OK) {
    code = A->rows != A->columns ? CALC_ERR : OK;
    double det;
    s21_determinant(A, &det);
    code = fabs(det) < ACCURACY ? CALC_ERR : code;
    if (code == OK) {
      matrix_t tmp;
      s21_create_matrix(A->rows, A->columns, &tmp);
      s21_calc_complements(A, &tmp);
      s21_transpose(&tmp, result);
      for (int i = 0; i < result->rows; ++i) {
        for (int j = 0; j < result->columns; ++j) {
          result->matrix[i][j] /= det;
        }
      }
      s21_remove_matrix(&tmp);
    }
  }
  return code;
}

void s21_build_minor_matrix(matrix_t A, int row, int column, matrix_t *result) {
  /*
  Вычисление определителя матрицы.
  Args:
   - A: указатель на матрицу
   - result: указатель на результирующую матрицу
  */
  s21_create_matrix(A.rows - 1, A.columns - 1, result);
  for (int i = 0, i_new = 0; i < A.rows; ++i) {
    if (i == row) continue;
    for (int j = 0, j_new = 0; j < A.columns; ++j) {
      if (j == column) continue;
      result->matrix[i_new][j_new++] = A.matrix[i][j];
    }
    i_new++;
  }
}

int s21_is_matrix_exist(matrix_t *A) {
  /*
  Проверка существования матрицы.
  Args:
   - A: указатель на матрицу
  Returns:
   - OK: если все нормально
   - UNCORR: если аргументы некорректны
  */
  return (!A || A->rows < 1 || A->columns < 1) ? UNCORR : OK;
}