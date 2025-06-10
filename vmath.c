#include "vmath.h"

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

Vector3 mat_get_row(const Matrix3x3 mat, int idx) {
  Vector3 v;
  v.x = mat[idx][0];
  v.y = mat[idx][1];
  v.z = mat[idx][2];

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

void solve_equation_system(Matrix3x3 *A, Vector3 *x, Vector3 b) {
  // TODO: Support row swapping to position a non-zero pivot element at the top

  // make the first column 0 for row 2 and 3
  Vector3 row = mat_get_row(*A, 0);

  float factor = (*A)[1][0] / (*A)[0][0];
  Vector3 to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 1);
  b.y -= b.x * factor;

  factor = (*A)[2][0] / (*A)[0][0];
  to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 2);
  b.z -= b.x * factor;

  // sub second row from thrid row
  row = mat_get_row(*A, 1);

  factor = (*A)[2][1] / (*A)[1][1];
  to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 2);
  b.z -= b.y * factor;

  // sub third row from first and second row
  row = mat_get_row(*A, 2);

  factor = (*A)[0][2] / (*A)[2][2];
  to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 0);
  b.x -= b.z * factor;

  factor = (*A)[1][2] / (*A)[2][2];
  to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 1);
  b.y -= b.z * factor;

  // sub second row from first row
  row = mat_get_row(*A, 1);

  factor = (*A)[0][1] / (*A)[1][1];
  to_sub = vector_scale(row, -factor);
  mat_add_to_row(A, to_sub, 0);
  b.x -= b.y * factor;

  x->x = b.x / (*A)[0][0];
  x->y = b.y / (*A)[1][1];
  x->z = b.z / (*A)[2][2];
}

void print_matrix(const Matrix3x3 *m) {
  for (int i = 0; i < 3; i++) {
    printf("| ");
    for (int j = 0; j < 3; j++) {
      printf("%6.2f ", (*m)[i][j]);
    }
    printf("|\n");
  }
  printf("\n");
}

void print_vector(Vector3 v) {
  printf("| %6.2f |\n", v.x);
  printf("| %6.2f |\n", v.y);
  printf("| %6.2f |\n", v.z);
}
