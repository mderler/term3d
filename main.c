#include <math.h>
#include <stdio.h>
#include <unistd.h>

void set_cursor_to_home() { printf("\033[H"); }
void set_cursor_pos(int row, int col) { printf("\033[%d;%dH", row, col); };
void hide_cursor() { printf("\033[?25l\n"); }
void erase_screen() { printf("\033[2J"); }

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

typedef struct {
  Vector3 position, rotation;
} Camera;

void draw_char(Vector3 pos, char c) {
  set_cursor_pos(pos.y, pos.x * 2);
  printf("%c\n", c);
}

int main() {
  // hide_cursor();
  erase_screen();
  set_cursor_to_home();

  Vector3 start = {.x = 5, .y = 0, .z = 0};
  Vector3 offset = {.x = 10, .y = 10, .z = 0};
  Matrix3x3 rot = {0};

  Vector3 end;
  float phi = 0;
  while (1) {
    draw_char(vector_add(offset, end), ' ');
    set_rotation_mat_z(&rot, phi);
    end = mat_mul_v(rot, start);
    draw_char(vector_add(offset, end), 'X');
    phi += 0.01;
    usleep(1000);
  }

  printf("\n");
}
