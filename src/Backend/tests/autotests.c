#include <check.h>

#include "../back.h"

START_TEST(amount_vert_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  ck_assert_int_eq(3618, syst.vert.amountVert);
  res_free(&syst);
}
END_TEST

START_TEST(amount_face_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  ck_assert_int_eq(3442, syst.amountFacets);
  res_free(&syst);
}
END_TEST

START_TEST(vert_fill_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.571387, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(face_fill_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  ck_assert_int_eq(4, syst.face[5].count);
  ck_assert_int_eq(93, syst.face[5].f[0]);
  ck_assert_int_eq(94, syst.face[5].f[1]);
  ck_assert_int_eq(88, syst.face[5].f[2]);
  ck_assert_int_eq(89, syst.face[5].f[3]);
  res_free(&syst);
}
END_TEST

START_TEST(minmax_ranges_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  ck_assert_double_eq_tol(-2.712309, *syst.vert.rangeX[0], 1e-6);
  ck_assert_double_eq_tol(2.712309, *syst.vert.rangeX[1], 1e-6);
  ck_assert_double_eq_tol(-3.294219, *syst.vert.rangeY[0], 1e-6);
  ck_assert_double_eq_tol(2.597942, *syst.vert.rangeY[1], 1e-6);
  ck_assert_double_eq_tol(-1.111950, *syst.vert.rangeZ[0], 1e-6);
  ck_assert_double_eq_tol(1.111950, *syst.vert.rangeZ[1], 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(move_x_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  movement(&syst, 1.5, 'x');
  ck_assert_double_eq_tol(1.907673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.571387, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(move_y_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  movement(&syst, 1.5, 'y');
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(0.928613, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(move_z_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  movement(&syst, 1.5, 'z');
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.571387, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(1.705197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(rot_x_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  rot(&syst, 90, 'x');
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.205197, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(-0.571387, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(rot_y_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  rot(&syst, 90, 'y');
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.571387, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(-0.407673, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(rot_z_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  rot(&syst, 90, 'z');
  ck_assert_double_eq_tol(0.571387, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(mult_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  mult(&syst, 10);
  ck_assert_double_eq_tol(4.07673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-5.71387, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(2.05197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(frames_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  resize_frames(&syst, 5);
  ck_assert_double_eq_tol(0.69189, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.969741, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.348254, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(central_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(0, matrix_fill(filename, &syst));
  center_frames(&syst);
  ck_assert_double_eq_tol(0.407673, syst.vert.coord[3610].x, 1e-6);
  ck_assert_double_eq_tol(-0.223248, syst.vert.coord[3610].y, 1e-6);
  ck_assert_double_eq_tol(0.205197, syst.vert.coord[3610].z, 1e-6);
  res_free(&syst);
}
END_TEST

START_TEST(file_err_test) {
  res syst = {0};
  const char *filename = "Backend/tests/normalin.obj";
  ck_assert_int_eq(-1, obj_counter(filename, &syst));
  ck_assert_int_eq(-1, matrix_fill(filename, &syst));
}
END_TEST

START_TEST(face_err_test) {
  res syst = {0};
  const char *filename = "Backend/tests/nenormal.obj";
  ck_assert_int_eq(0, obj_counter(filename, &syst));
  ck_assert_int_eq(-2, matrix_fill(filename, &syst));
}
END_TEST

START_TEST(empty_file_test) {
  res syst = {0};
  const char *filename = "Backend/tests/empty.obj";
  ck_assert_int_eq(-1, obj_counter(filename, &syst));
}
END_TEST

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s);
  int nf;
  suite_add_tcase(s, tc);

  tcase_add_test(tc, amount_vert_test);
  tcase_add_test(tc, amount_face_test);
  tcase_add_test(tc, vert_fill_test);
  tcase_add_test(tc, face_fill_test);
  tcase_add_test(tc, minmax_ranges_test);
  tcase_add_test(tc, move_x_test);
  tcase_add_test(tc, move_y_test);
  tcase_add_test(tc, move_z_test);
  tcase_add_test(tc, rot_x_test);
  tcase_add_test(tc, rot_y_test);
  tcase_add_test(tc, rot_z_test);
  tcase_add_test(tc, mult_test);
  tcase_add_test(tc, frames_test);
  tcase_add_test(tc, central_test);
  tcase_add_test(tc, file_err_test);
  tcase_add_test(tc, face_err_test);
  tcase_add_test(tc, empty_file_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
