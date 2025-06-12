#ifndef DRAWING_H
#define DRAWING_H

#include <stdio.h>

void set_cursor_to_home();

void set_cursor_pos(int row, int col);
void hide_cursor();
void erase_screen();

void draw_char(int x, int y, char c);
void draw_str(int x, int y, const char *s);

void draw_line(int x1, int y1, int x2, int y2, float thiccness, char c);

#endif
