#include <check.h>

#include "../s21_matrix.h"

void mCreateTests(TCase *tc_core);
void mRemTests(TCase *tc_core);
void mEqTests(TCase *tc_core);
void mSumTests(TCase *tc_core);
void mSubTests(TCase *tc_core);
void mMatTests(TCase *tc_core);
void mNumTests(TCase *tc_core);
void cCompTests(TCase *tc_core);
void transTest(TCase *tc_core);
void invMatrTests(TCase *tc_core);
void dtrTests(TCase *tc_core);

int main(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_matrix");
  tc_core = tcase_create("s21_matrix");

  mCreateTests(tc_core);
  mRemTests(tc_core);
  mEqTests(tc_core);
  mSumTests(tc_core);
  mSubTests(tc_core);
  mMatTests(tc_core);
  mNumTests(tc_core);
  cCompTests(tc_core);
  transTest(tc_core);
  invMatrTests(tc_core);
  dtrTests(tc_core);

  suite_add_tcase(s, tc_core);
  SRunner *sr;
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);

  return 0;
}

START_TEST(test_matrix_create_1) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(4, 4, &A), MATRIX_OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_matrix_create_2) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(2, 3, &A), MATRIX_OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_matrix_create_3) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(4, 2, &A), MATRIX_OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_matrix_create_4) {
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), MATRIX_INCORRECT);
}
END_TEST

START_TEST(test_matrix_create_5) {
  matrix_t A = {};
  s21_create_matrix(0, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_matrix_create_6) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(-1, 0, &A), MATRIX_INCORRECT);
}
END_TEST

START_TEST(test_matrix_create_7) {
  int result = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(result, MATRIX_INCORRECT);
}
END_TEST

START_TEST(test_matrix_create_8) {
  int result = s21_create_matrix(0, 0, NULL);
  ck_assert_int_eq(result, MATRIX_INCORRECT);
}
END_TEST

START_TEST(test_remove_matrix_1) {
  matrix_t A = {};
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(test_remove_matrix_2) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_remove_matrix_3) {
  matrix_t A = {};
  ck_assert_int_eq(1, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_init_matrix(&A, 4, 1);
  s21_init_matrix(&B, 4, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_init_matrix(&A, 4, 4);
  s21_init_matrix(&A, 4, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_init_matrix(&A, 4, 1);
  s21_init_matrix(&A, 4, 8);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_4) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(1, 5, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(6, 6, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(5, 1, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), MATRIX_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(6, 6, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(5, 1, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(6, 6, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_null) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), MATRIX_INCORRECT);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), MATRIX_INCORRECT);
  ck_assert_int_eq(s21_sub_matrix(NULL, NULL, &result), MATRIX_INCORRECT);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_A_null_matrix) {
  matrix_t A = {0};
  A.rows = 3;
  A.columns = 3;
  A.matrix = NULL;
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_nan_inf) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = NAN;
  B.matrix[0][0] = 1.0;
  A.matrix[1][1] = INFINITY;
  B.matrix[1][1] = 2.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_CALCULATION);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_1x1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5.5;
  B.matrix[0][0] = 3.3;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.2, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_2x2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 10;
  A.matrix[0][1] = 20;
  A.matrix[1][0] = 30;
  A.matrix[1][1] = 40;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 10;
  B.matrix[1][0] = 15;
  B.matrix[1][1] = 20;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), MATRIX_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 10, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 15, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 20, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(1, 0, &A);
  s21_create_matrix(1, 1, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(1, 6, &A);
  s21_create_matrix(6, 1, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(6, 1, &A);
  s21_create_matrix(2, 6, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), MATRIX_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_1) {
  matrix_t A = {};
  matrix_t result = {};
  double number = 2;
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A = {};
  matrix_t result = {};
  double number = 2;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_3) {
  matrix_t A = {};
  matrix_t result = {};
  double number = -1;
  s21_create_matrix(4, 1, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_comp_1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 5, NULL);
  ck_assert_int_eq(s21_calc_complements(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_comp_2) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 5, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_comp_3) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 0, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_1) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_transpose(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_2) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(1, 4, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), MATRIX_OK);
  ck_assert_int_eq(result.rows, 4);
  ck_assert_int_eq(result.columns, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_3) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(4, 1, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), MATRIX_OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 4);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(1, 1, NULL);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(4, 2, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_4) {
  matrix_t A = {};
  matrix_t result = {};
  double num = 5.0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  ck_assert_int_eq(1.0 / num, result.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_5) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_6) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1234;
  A.matrix[0][1] = 5678;
  A.matrix[0][2] = 7645;
  A.matrix[1][0] = 91011;
  A.matrix[1][1] = 1213;
  A.matrix[1][2] = 8906;
  A.matrix[2][0] = 8731;
  A.matrix[2][1] = 4567;
  A.matrix[2][2] = 41423;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_null) {
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_A_null_matrix) {
  matrix_t A = {0};
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_non_square) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_zero_det) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_CALCULATION);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);
  ck_assert_ptr_null(result.matrix);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_1x1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), MATRIX_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_determinant_1) {
  matrix_t A = {};
  double result = 0;
  s21_create_matrix(4, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t A = {};
  double result = 0;
  s21_create_matrix(4, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), MATRIX_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 3, &A);
  s21_init_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_determinant(&A, &det), MATRIX_OK);
  ck_assert_double_eq(det, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(2, 2, &A);
  s21_init_matrix(&A, 3, 3);
  ck_assert_int_eq(s21_determinant(&A, &det), MATRIX_OK);
  ck_assert_double_eq(det, -18);
  s21_remove_matrix(&A);
}
END_TEST

void mCreateTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_matrix_create_1);
  tcase_add_test(tc_core, test_matrix_create_2);
  tcase_add_test(tc_core, test_matrix_create_3);
  tcase_add_test(tc_core, test_matrix_create_4);
  tcase_add_test(tc_core, test_matrix_create_5);
  tcase_add_test(tc_core, test_matrix_create_6);
  tcase_add_test(tc_core, test_matrix_create_7);
  tcase_add_test(tc_core, test_matrix_create_8);
}

void mRemTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_remove_matrix_1);
  tcase_add_test(tc_core, test_remove_matrix_2);
  tcase_add_test(tc_core, test_remove_matrix_3);
}

void mEqTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_eq_matrix_1);
  tcase_add_test(tc_core, test_eq_matrix_2);
  tcase_add_test(tc_core, test_eq_matrix_3);
  tcase_add_test(tc_core, test_eq_matrix_4);
  tcase_add_test(tc_core, test_eq_matrix_5);
}

void mSumTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_sum_matrix_1);
  tcase_add_test(tc_core, test_sum_matrix_2);
  tcase_add_test(tc_core, test_sum_matrix_3);
}

void mSubTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_sub_matrix_1);
  tcase_add_test(tc_core, test_sub_matrix_2);
  tcase_add_test(tc_core, test_sub_matrix_3);
  tcase_add_test(tc_core, test_sub_matrix_null);
  tcase_add_test(tc_core, test_sub_matrix_A_null_matrix);
  tcase_add_test(tc_core, test_sub_matrix_nan_inf);
  tcase_add_test(tc_core, test_sub_matrix_1x1);
  tcase_add_test(tc_core, test_sub_matrix_2x2);
}

void mMatTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_mult_matrix_1);
  tcase_add_test(tc_core, test_mult_matrix_2);
  tcase_add_test(tc_core, test_mult_matrix_3);
}

void mNumTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_mult_number_1);
  tcase_add_test(tc_core, test_mult_number_2);
  tcase_add_test(tc_core, test_mult_number_3);
}

void cCompTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_calc_comp_1);
  tcase_add_test(tc_core, test_calc_comp_2);
  tcase_add_test(tc_core, test_calc_comp_3);
}

void transTest(TCase *tc_core) {
  tcase_add_test(tc_core, test_transpose_1);
  tcase_add_test(tc_core, test_transpose_2);
  tcase_add_test(tc_core, test_transpose_3);
}

void invMatrTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_inverse_matrix_1);
  tcase_add_test(tc_core, test_inverse_matrix_2);
  tcase_add_test(tc_core, test_inverse_matrix_3);
  tcase_add_test(tc_core, test_inverse_matrix_4);
  tcase_add_test(tc_core, test_inverse_matrix_5);
  tcase_add_test(tc_core, test_inverse_matrix_6);
  tcase_add_test(tc_core, test_inverse_matrix_null);
  tcase_add_test(tc_core, test_inverse_matrix_A_null_matrix);
  tcase_add_test(tc_core, test_inverse_matrix_non_square);
  tcase_add_test(tc_core, test_inverse_matrix_zero_det);
  tcase_add_test(tc_core, test_inverse_matrix_1x1);
}

void dtrTests(TCase *tc_core) {
  tcase_add_test(tc_core, test_determinant_1);
  tcase_add_test(tc_core, test_determinant_2);
  tcase_add_test(tc_core, test_determinant_3);
  tcase_add_test(tc_core, test_determinant_4);
}
