#include "drawing.h"
#include "render.h"

int main() {
  erase_screen();
  set_cursor_to_home();

  Vertex vertecies[] = {{4, 0, 10}, {2, 5, -1}};
  Screen screen = {.w = 16, .h = 9 };
  Camera cam = init_camera(90, 1, 16.0/9.0);

  draw_vertecies(screen, &cam, vertecies, 2);

  while (1) ;
}
