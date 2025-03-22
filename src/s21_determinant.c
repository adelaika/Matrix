#include "s21_matrix.h"

int s21_get_minor(matrix_t *A, int col, matrix_t *minor) {
  int n = A->rows;
  if (s21_create_matrix(n - 1, n - 1, minor) != MATRIX_OK) {
    return MATRIX_INCORRECT;
  }
  for (int row = 1, minor_row = 0; row < n; row++, minor_row++) {
    int minor_col = 0;
    for (int j = 0; j < n; j++) {
      if (j != col) {
        minor->matrix[minor_row][minor_col] = A->matrix[row][j];
        minor_col++;
      }
    }
  }
  return MATRIX_OK;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = MATRIX_OK;
  *result = 0;
  if (!A || !result || !A->matrix || A->rows <= 0 || A->columns <= 0 ||
      A->rows != A->columns) {
    return MATRIX_INCORRECT;
  }
  int n = A->rows;
  if (n == 1) {
    *result = A->matrix[0][0];
  } else if (n == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    double det = 0.0;
    int sign = 1;
    for (int i = 0; i < n && status == MATRIX_OK; i++) {
      matrix_t minor;
      status = s21_get_minor(A, i, &minor);
      if (status == MATRIX_OK) {
        double minor_det;
        status = s21_determinant(&minor, &minor_det);
        if (status == MATRIX_OK) {
          det += sign * A->matrix[0][i] * minor_det;
          sign *= -1;
        }
        s21_remove_matrix(&minor);
      }
    }
    if (status == MATRIX_OK) {
      *result = det;
    }
  }
  return status;
}
