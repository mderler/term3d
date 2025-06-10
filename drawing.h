#ifndef DRAWING_H
#define DRAWING_H

#include <stdio.h>

void set_cursor_to_home();

void set_cursor_pos(int row, int col);
void hide_cursor();
void erase_screen();

void draw_char(int x, int y, char c);

#endif
