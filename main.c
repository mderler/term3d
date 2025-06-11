#include <unistd.h>

#include "drawing.h"
#include "render.h"
#include "vmath.h"

int main() {
  erase_screen();
  hide_cursor();

  Vertex vertecies[] = {{2, 0, 0}, {10, 0, 4}};
  int vertex_count = sizeof(vertecies) / sizeof(Vertex);

  Screen screen = {.w = 16, .h = 9};
  Camera cam = init_camera(90, 1, (float)4 / 3);

  while (1) {
    erase_screen();
    draw_char(0, 0, '+');
    draw_char(screen.w - 1, 0, '+');
    draw_char(0, screen.h - 1, '+');
    draw_char(screen.w - 1, screen.h - 1, '+');

    draw_vertex(screen, &cam, vertecies[0], "[]");
    draw_vertex(screen, &cam, vertecies[1], "()");
    usleep(1000 * 30);

    for (int i = 0; i < vertex_count; i++) {
      vertecies[i].y += 0.04;
      if (vertecies[i].y > 1.8) {
        vertecies[i].y = -1.8;
      }
    }
  }
}
