#ifndef VMATH_H
#define VMATH_H

#include <math.h>
#include <stdio.h>

typedef struct {
  float x, y, z;
} Vector3;

Vector3 vector_add(Vector3 a, Vector3 b);

Vector3 vector_sub(Vector3 a, Vector3 b);

Vector3 vector_scale(Vector3 v, float a);

typedef float Matrix3x3[3][3];

void set_mat_from_v(Matrix3x3 *mat, Vector3 v1, Vector3 v2, Vector3 v3);

Vector3 mat_get_row(const Matrix3x3 *mat, int idx);

void mat_add_to_row(Matrix3x3 *mat, Vector3 v, int idx);

Vector3 mat_mul_v(const Matrix3x3 *mat, Vector3 vec);

void set_rotation_mat_z(Matrix3x3 *mat, float phi);

/*
 * Solve an equation system in the form of: Ax = b.
 * The result will be written into the variable vector.
 *
 * @param float A[3][3] the coefficient matrix
 * @param Vector *x pointer to the variable vector
 * @param Vector b the constant vector
 */
void solve_equation_system(Matrix3x3 *A, Vector3 *x, Vector3 b);

void print_matrix(const Matrix3x3 *m);

void print_vector(Vector3 v);

#endif
