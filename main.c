#include <stdio.h>
#include <unistd.h>

#include "drawing.h"
#include "vmath.h"

typedef struct {
  Vector3 position, rotation;
} Camera;

void draw_char(Vector3 pos, char c) {
  set_cursor_pos(pos.y, pos.x * 2);
  printf("%c\n", c);
}

void draw_box(Vector3 pos, char c, int a) {
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < a; j++) {
       Vector3 v = pos;
       v.x += i;
       v.y += j;
      draw_char(v, c);
    }
  }
}

int main() {

  Matrix3x3 A = {{1,1,1}, {2, -1, 3}, {-1, 4, -1}};
  Vector3 b = {6, 14, -2};
  Vector3 x;

  printf("before:\n\n");
  print_matrix(&A);
  print_vector(b);
  printf("after:\n\n");

  solve_equation_system(&A, &x, b);
  print_matrix(&A);
  print_vector(x);

  /*
  hide_cursor();
  erase_screen();
  set_cursor_to_home();

  Vector3 start = {.x = 5, .y = 0, .z = 0};
  Vector3 offset = {.x = 10, .y = 10, .z = 0};
  Matrix3x3 rot = {0};

  Vector3 end;
  float phi = 0;
  while (1) {
    // draw_char(vector_add(offset, end), ' ');
    set_rotation_mat_z(&rot, phi);
    end = mat_mul_v(&rot, start);
    draw_char(vector_add(offset, end), 'X');
    fflush(stdout);
    phi += 0.005;
    usleep(1000);
  }
  */
}
