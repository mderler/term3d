#include "vmath.h"
#include <assert.h>
#include <stdio.h>

Vector3 vector_add(Vector3 a, Vector3 b) {
  Vector3 v = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
  return v;
}

Vector3 vector_sub(Vector3 a, Vector3 b) {
  Vector3 v = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
  return v;
}

Vector3 vector_scale(Vector3 v, float a) {
  v.x *= a;
  v.y *= a;
  v.z *= a;
  return v;
}

void set_mat_from_v(Matrix3x3 *mat, Vector3 v1, Vector3 v2, Vector3 v3) {
  (*mat)[0][0] = v1.x;
  (*mat)[1][0] = v1.y;
  (*mat)[2][0] = v1.z;

  (*mat)[0][1] = v2.x;
  (*mat)[1][1] = v2.y;
  (*mat)[2][1] = v2.z;

  (*mat)[0][2] = v3.x;
  (*mat)[1][2] = v3.y;
  (*mat)[2][2] = v3.z;
}

Vector3 mat_get_row(const Matrix3x3 *mat, int idx) {
  Vector3 v;
  v.x = (*mat)[idx][0];
  v.y = (*mat)[idx][1];
  v.z = (*mat)[idx][2];

  return v;
}

void mat_add_to_row(Matrix3x3 *mat, Vector3 v, int idx) {
  (*mat)[idx][0] += v.x;
  (*mat)[idx][1] += v.y;
  (*mat)[idx][2] += v.z;
}

Vector3 mat_mul_v(const Matrix3x3 *mat, Vector3 vec) {
  Vector3 v;
  v.x = vec.x * (*mat)[0][0] + vec.y * (*mat)[0][1] + vec.z * (*mat)[0][2];
  v.y = vec.x * (*mat)[1][0] + vec.y * (*mat)[1][1] + vec.z * (*mat)[1][2];
  v.z = vec.x * (*mat)[2][0] + vec.y * (*mat)[2][1] + vec.z * (*mat)[2][2];

  return v;
}

void set_rotation_mat_z(Matrix3x3 *mat, float phi) {
  float sin_phi = sinf(phi);
  float cos_phi = cosf(phi);

  (*mat)[0][0] = cos_phi;
  (*mat)[0][1] = -sin_phi;
  (*mat)[0][2] = 0;

  (*mat)[1][0] = sin_phi;
  (*mat)[1][1] = cos_phi;
  (*mat)[1][2] = 0;

  (*mat)[2][0] = 0;
  (*mat)[2][1] = 0;
  (*mat)[2][2] = 1;
}

static float v_at(Vector3 v, int idx) {
  switch (idx) {
  case 0:
    return v.x;
  case 1:
    return v.y;
  case 2:
    return v.z;
  }

  assert(0 && "unreachable");
}

static int is_in_range(float x, float epsilon) {
  if (-epsilon <= x && x <= epsilon)
    return 1;
  return 0;
}

static void v_set_at(Vector3 *v, int idx, float value) {
  switch (idx) {
  case 0:
    v->x = value;
    return;
  case 1:
    v->y = value;
    return;
  case 2:
    v->z = value;
    return;
  }

  assert(0 && "unreachable");
}

static void print_mat_row_swapped(const Matrix3x3 *m, int rows[]) {
  for (int i = 0; i < 3; i++) {
    int idx = rows[i];
    printf("| ");
    for (int j = 0; j < 3; j++) {
      printf("%7.4f ", (*m)[idx][j]);
    }
    printf("|\n");
  }
  printf("\n");
}

static void print_vec_swapped(Vector3 v, int rows[]) {
  for (int i = 0; i < 3; i++) {
    printf("| %7.4f |\n", v_at(v, rows[i]));
  }
}

void solve_equation_system(Matrix3x3 *A, Vector3 *x, Vector3 b) {
  const float EPSILON = 0.00001f;

#ifdef DEBUG
  printf("\n================= EQSYSTEM =================\n");
  printf("A:\n");
  print_matrix(A);
  printf("b:\n");
  print_vector(b);
#endif

  int row_order[3] = {0, 1, 2};
  for (int i = 0; i < 3; i++) {
    int pivot_row = i;
    while (row_order[pivot_row] < 3 &&
           is_in_range((*A)[row_order[pivot_row]][i], EPSILON)) {
      pivot_row++;
    }

    if (pivot_row != i) {
      int tmp = row_order[i];
      row_order[i] = row_order[pivot_row];
      row_order[pivot_row] = tmp;
    }

    for (int j = i + 1; j < 3; j++) {
      int i_row = row_order[i];
      int j_row = row_order[j];

      float factor = (*A)[j_row][i] / (*A)[i_row][i];

#ifdef DEBUG
      printf("\n================= BEFORE =================\n");
      printf("i=%d, j=%d, i_row=%d, j_row=%d, factor=%f\n", i, j, i_row, j_row,
             factor);
      printf("A:\n");
      print_mat_row_swapped(A, row_order);
      printf("b:\n");
      print_vec_swapped(b, row_order);
#endif

      if (is_in_range(factor, EPSILON))
        continue;

      Vector3 pivot = mat_get_row(A, i_row);
      Vector3 to_sub = vector_scale(pivot, -factor);
      mat_add_to_row(A, to_sub, j_row);
      v_set_at(&b, j_row, v_at(b, j_row) - factor * v_at(b, i_row));

#ifdef DEBUG
      printf("\n================= AFTER =================\n");
      printf("A:\n");
      print_mat_row_swapped(A, row_order);
      printf("b:\n");
      print_vec_swapped(b, row_order);
#endif
    }
  }

  for (int i = 2; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--) {
      int i_row = row_order[i];
      int j_row = row_order[j];

      float factor = (*A)[j_row][i] / (*A)[i_row][i];

#ifdef DEBUG
      printf("\n================= BEFORE =================\n");
      printf("i=%d, j=%d, i_row=%d, j_row=%d, factor=%f\n", i, j, i_row, j_row,
             factor);
      printf("A:\n");
      print_mat_row_swapped(A, row_order);
      printf("b:\n");
      print_vec_swapped(b, row_order);
#endif

      if (is_in_range(factor, EPSILON))
        continue;

      Vector3 pivot = mat_get_row(A, i_row);
      Vector3 to_sub = vector_scale(pivot, -factor);
      mat_add_to_row(A, to_sub, j_row);
      v_set_at(&b, j_row, v_at(b, j_row) - factor * v_at(b, i_row));

#ifdef DEBUG
      printf("\n================= AFTER =================\n");
      printf("A:\n");
      print_mat_row_swapped(A, row_order);
      printf("b:\n");
      print_vec_swapped(b, row_order);
#endif
    }
  }

#ifdef DEBUG
  printf("\n================= SOLUTION =================\n");
  print_mat_row_swapped(A, row_order);
  print_vec_swapped(b, row_order);
#endif

  x->x = v_at(b, row_order[0]) / (*A)[row_order[0]][0];
  x->y = v_at(b, row_order[1]) / (*A)[row_order[1]][1];
  x->z = v_at(b, row_order[2]) / (*A)[row_order[2]][2];
}

void print_matrix(const Matrix3x3 *m) {
  for (int i = 0; i < 3; i++) {
    printf("| ");
    for (int j = 0; j < 3; j++) {
      printf("%7.4f ", (*m)[i][j]);
    }
    printf("|\n");
  }
  printf("\n");
}

void print_vector(Vector3 v) {
  printf("| %7.4f |\n", v.x);
  printf("| %7.4f |\n", v.y);
  printf("| %7.4f |\n", v.z);
}
