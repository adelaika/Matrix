#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    return MATRIX_INCORRECT;
  }
  if (s21_create_matrix(A->columns, A->rows, result) == MATRIX_OK) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return MATRIX_OK;
}
