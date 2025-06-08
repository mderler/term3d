#ifndef VMATH_H
#define VMATH_H
#include <math.h>

typedef struct {
  float x, y, z;
} Vector3;

Vector3 vector_add(Vector3 a, Vector3 b) {
  Vector3 v = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
  return v;
}

typedef float Matrix3x3[3][3];

Vector3 mat_mul_v(Matrix3x3 mat, Vector3 vec) {
  Vector3 v;
  v.x = vec.x * mat[0][0] + vec.y * mat[0][1] + vec.z * mat[0][2];
  v.y = vec.x * mat[1][0] + vec.y * mat[1][1] + vec.z * mat[1][2];
  v.z = vec.x * mat[2][0] + vec.y * mat[2][1] + vec.z * mat[2][2];

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

#endif
