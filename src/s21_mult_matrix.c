#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || !result || !A->matrix || !B->matrix) {
    return MATRIX_INCORRECT;
  }
  if (A->columns != B->rows) {
    return MATRIX_CALCULATION;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return MATRIX_INCORRECT;
  }
  int miss = s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows && !miss; i++) {
    for (int j = 0; j < B->columns && !miss; j++) {
      double sum = 0.0;
      for (int f = 0; f < A->columns && !miss; f++) {
        double a = A->matrix[i][f];
        double b = B->matrix[f][j];
        if (isnan(a) || isnan(b) || isinf(a) || isinf(b)) {
          s21_remove_matrix(result);
          miss = MATRIX_CALCULATION;
        }
        sum += a * b;
      }
      result->matrix[i][j] = sum;
    }
  }
  return miss;
}
