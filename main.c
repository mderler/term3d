#define _XOPEN_SOURCE 500

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "drawing.h"
#include "render.h"
#include "vmath.h"

int main() {
    erase_screen();
    hide_cursor();

    struct termios newt;

    tcgetattr(STDIN_FILENO, &newt);

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

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

    const float CAM_SPEED = 0.1;
    const float CAM_ROT_SPEED = 0.01;

    char c = 'c';
    long frame_time_ms = 30;
    while (1) {
        char input = -1;
        int result = read(STDIN_FILENO, &input, 1);
        if ('a' <= input && input <= 'z') {
            switch (input) {
            case 'w':
                cam.position.x += CAM_SPEED;
                break;
            case 'a':
                cam.position.y += CAM_SPEED;
                break;
            case 's':
                cam.position.x -= CAM_SPEED;
                break;
            case 'd':
                cam.position.y -= CAM_SPEED;
                break;
            case 'j':
                cam.position.z += CAM_SPEED;
                break;
            case 'k':
                cam.position.z -= CAM_SPEED;
                break;
            case 'h':
                cam.z_angle -= CAM_SPEED;
                break;
            case 'l':
                cam.z_angle += CAM_SPEED;
                break;
            case 'u':
                cam.y_angle -= CAM_SPEED;
                break;
            case 'n':
                cam.y_angle += CAM_SPEED;
                break;
            }
            input = -1;
        }

        erase_screen();
        draw_char(0, 0, '+');
        draw_char(screen.w - 1, 0, '+');
        draw_char(0, screen.h - 1, '+');
        draw_char(screen.w - 1, screen.h - 1, '+');

        for (int i = 0; i < vertex_count; i++) {
            vertecies[i] = mat_mul_v(&rotz, vertecies[i]);
            str[0] = i + '1';
            draw_vertex(screen, &cam, vector_add(vertecies[i], cube_pos), str);
        }

        // draw_vertecies(screen, &cam, vertecies, vertex_count);

        usleep(1000 * 30);
    }
}
