#include "s21_matrix.h"

void s21_init_matrix(matrix_t *A, double start, double step) {
  if (A != NULL && A->matrix != NULL) {
    double sym = start;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = sym;
        sym += step;
      }
    }
  }
}
