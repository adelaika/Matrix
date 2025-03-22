#include <math.h>

#include "s21_matrix.h"

void copyMatrix(matrix_t *result, matrix_t *transpose, int det, int *status) {
  int n = transpose->columns;
  *status = s21_create_matrix(n, n, result);
  if (*status == MATRIX_OK) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result->matrix[i][j] = transpose->matrix[i][j] / det;
      }
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0) {
    return MATRIX_INCORRECT;
  }
  if (A->rows != A->columns) {
    return MATRIX_CALCULATION;
  }
  int status = MATRIX_OK;
  double det = 0.0;
  int n = A->rows;
  matrix_t complements = {0}, transpose = {0};

  if (n == 1) {
    if (fabs(A->matrix[0][0]) < 1e-7) {
      status = MATRIX_CALCULATION;
    } else {
      status = s21_create_matrix(1, 1, result);
      if (status == MATRIX_OK) {
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      }
    }

  } else {
    status = s21_determinant(A, &det);
    if (status == MATRIX_OK && fabs(det) >= 1e-7) {
      status = s21_calc_complements(A, &complements);
      if (status == MATRIX_OK) {
        status = s21_transpose(&complements, &transpose);
      }
      s21_remove_matrix(&complements);
      if (status == MATRIX_OK) {
        copyMatrix(result, &transpose, det, &status);
      }
      s21_remove_matrix(&transpose);
    } else {
      status = MATRIX_CALCULATION;
    }
  }
  return status;
}
