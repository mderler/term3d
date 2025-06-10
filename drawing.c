#include "drawing.h"

void set_cursor_to_home() {
  const char str[] = "\033[H";
  fwrite(str, sizeof(str), 1, stdout);
}

void set_cursor_pos(int row, int col) { printf("\033[%d;%dH", row, col); };
void hide_cursor() { printf("\033[?25l"); }
void erase_screen() { printf("\033[2J"); }

void draw_char(int x, int y, char c) {
  set_cursor_pos(y, x * 2);
  printf("[]\n", c);
}
