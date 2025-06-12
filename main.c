#include <unistd.h>

#include "drawing.h"
#include "render.h"
#include "vmath.h"

int main() {
    erase_screen();
    hide_cursor();

    float r = 1;
    Vector3 cube_pos = {.x = 4, .y = 0, .z = 0};

    Vertex vertecies[] = {
        {-r, r, r}, {-r, r, -r}, {-r, -r, r}, {-r, -r, -r},
        {r, r, r},  {r, r, -r},  {r, -r, r},  {r, -r, -r},
    };

    int vertex_count = sizeof(vertecies) / sizeof(Vertex);

    Screen screen = {.w = 16 * 4, .h = 9 * 4};
    Camera cam = init_camera(90, 1, (float)4 / 3);

    float phi = 0.02f;
    Matrix3x3 rotz;
    set_rotation_mat_z(&rotz, phi);
    char str[] = " ";
    while (1) {
        erase_screen();
        draw_char(0, 0, '+');
        draw_char(screen.w - 1, 0, '+');
        draw_char(0, screen.h - 1, '+');
        draw_char(screen.w - 1, screen.h - 1, '+');

        for (int i = 0; i < vertex_count; i++) {
            vertecies[i] = mat_mul_v(&rotz, vertecies[i]);
            str[0] = i + '0';
            draw_vertex(screen, &cam, vector_add(vertecies[i], cube_pos), str);
        }

        // draw_vertecies(screen, &cam, vertecies, vertex_count);

        usleep(1000 * 30);
    }
}
