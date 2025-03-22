#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int miss = MATRIX_OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return MATRIX_INCORRECT;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return MATRIX_INCORRECT;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return MATRIX_CALCULATION;
  }
  if (s21_create_matrix(A->rows, A->columns, result) == MATRIX_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((isnan(A->matrix[i][j]) || isnan(B->matrix[i][j]) ||
             isinf(A->matrix[i][j]) || isinf(B->matrix[i][j])) &&
            miss == MATRIX_OK) {
          miss = MATRIX_CALCULATION;
        } else
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    if (miss != MATRIX_OK) {
      s21_remove_matrix(result);
    }
  }
  return miss;
}
