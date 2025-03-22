#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int miss = MATRIX_OK;
  if (A->rows <= 0 || A->columns <= 0) {
    return MATRIX_INCORRECT;
  }
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return MATRIX_INCORRECT;
  }
  if (isinf(number) || isnan(number)) {
    return MATRIX_CALCULATION;
  }
  miss = s21_create_matrix(A->rows, A->columns, result);
  if (miss != MATRIX_OK) {
    s21_remove_matrix(result);
  }
  for (int i = 0; i < A->rows && !miss; i++) {
    for (int j = 0; j < A->columns && !miss; j++) {
      if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
        s21_remove_matrix(result);
        miss = MATRIX_CALCULATION;
      }
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return miss;
}
