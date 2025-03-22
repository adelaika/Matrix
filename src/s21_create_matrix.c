#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = MATRIX_OK;
  if (!result || rows < 1 || columns < 1) {
    return MATRIX_INCORRECT;
  }
  result->rows = rows;
  result->columns = columns;
  result->matrix = calloc(rows, sizeof(double *));
  if (!result->matrix) {
    return MATRIX_INCORRECT;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    if (!result->matrix[i] && status == MATRIX_OK) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      status = MATRIX_INCORRECT;
    }
  }
  return status;
}
