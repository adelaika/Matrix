#include "s21_matrix.h"

void minorMoreTwo(matrix_t *temp_minor, matrix_t *A, int n, int row, int col) {
  temp_minor->rows = n - 1;
  temp_minor->columns = n - 1;
  temp_minor->matrix = (double **)calloc(temp_minor->rows, sizeof(double *));
  for (int i = 0; i < temp_minor->rows; i++) {
    temp_minor->matrix[i] =
        (double *)calloc(temp_minor->columns, sizeof(double));
  }
  int minor_row = 0;
  for (int i = 0; i < n; i++) {
    if (i != row) {
      int minor_col = 0;
      for (int j = 0; j < n; j++) {
        if (j != col) {
          temp_minor->matrix[minor_row][minor_col] = A->matrix[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
}

double find_minor(matrix_t *A, int row, int col) {
  int n = A->rows;
  double minor = 0.0;
  if (n == 1) {
    minor = 1.0;
  } else if (n == 2) {
    int r = (row == 0) ? 1 : 0;
    int c = (col == 0) ? 1 : 0;
    minor = A->matrix[r][c];
  } else {
    matrix_t temp_minor;
    minorMoreTwo(&temp_minor, A, n, row, col);
    s21_determinant(&temp_minor, &minor);
    for (int i = 0; i < temp_minor.rows; i++) {
      free(temp_minor.matrix[i]);
    }
    free(temp_minor.matrix);
  }
  return minor;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || A->rows != A->columns) {
    return MATRIX_INCORRECT;
  }
  int n = A->rows;
  if (n == 1) {
    return MATRIX_CALCULATION;
  }
  int status = s21_create_matrix(n, n, result);
  if (status == MATRIX_OK) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        double minor = find_minor(A, i, j);
        result->matrix[i][j] = minor * pow(-1, i + j);
      }
    }
  }
  return status;
}
