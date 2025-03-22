#include "s21_matrix.h"
#define EPSILON 1e-7

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int miss = SUCCESS;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    miss = FAILURE;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    miss = FAILURE;
  }
  if (miss == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON && miss)
          miss = FAILURE;
      }
    }
  }
  return miss;
}
