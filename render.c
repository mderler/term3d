#include <math.h>
#include <stdio.h>

#include "drawing.h"
#include "render.h"
#include "vmath.h"

Camera init_camera(float fov, float plane_distance, float aspect_ratio) {
    Camera cam = {0};

    float half_fov_rad = (fov * M_PI / 180.0) / 2.0;
    float half_plane_width = plane_distance * tanf(half_fov_rad);
    float plane_width = 2 * half_plane_width;

    float plane_height = (1 / aspect_ratio) * plane_width;

    Vector3 offset;
    offset.x = plane_distance;
    offset.y = half_plane_width;
    offset.z = -plane_height / 2;

    Vector3 pw = {0};
    pw.y = -plane_width;

    Vector3 ph = {0};
    ph.z = plane_height;

    cam.plane_offset = offset;
    cam.pw = pw;
    cam.ph = ph;

    return cam;
}

void draw_vertex(Screen screen, const Camera *cam, Vertex vertex, const char *str) {
    Matrix3x3 rotx;
    set_rotation_mat_z(&rotx, cam->x_angle);
    Matrix3x3 rotz;
    set_rotation_mat_z(&rotz, cam->z_angle);

    vertex = vector_sub(vertex, cam->position);
    vertex = mat_mul_v(
        &rotx, vertex); // INFO: Ineffecient, use matrix multiplication to combine rotx and rotz
    vertex = mat_mul_v(&rotz, vertex);

    // to screen space coords (u,v,t)
    Vector3 uvt = to_screen_space(cam, vertex);

#ifdef DEBUG
    printf("uvt:\n");
    print_vector(uvt);
#endif

#ifndef DEBUG
    if (0 <= uvt.x && uvt.x <= 1 && 0 <= uvt.y && uvt.y <= 1) {
        draw_str(screen.w * uvt.x, screen.h * uvt.y, str);
    }
#endif
}

void draw_vertecies(Screen screen, const Camera *cam, const Vertex *vertecies, int vertex_count) {

    Matrix3x3 rotx;
    set_rotation_mat_z(&rotx, cam->x_angle);
    Matrix3x3 rotz;
    set_rotation_mat_z(&rotz, cam->z_angle);

    for (int i = 0; i < vertex_count; i++) {
        // transform vertex
        Vertex vertex = vertecies[i];
        vertex = vector_sub(vertex, cam->position);
        vertex = mat_mul_v(
            &rotx, vertex); // INFO: Ineffecient, use matrix multiplication to combine rotx and rotz
        vertex = mat_mul_v(&rotz, vertex);

        // to screen space coords (u,v,t)
        Vector3 uvt = to_screen_space(cam, vertex);

#ifdef DEBUG
        printf("uvt:\n");
        print_vector(uvt);
#endif

#ifndef DEBUG
        if (0 <= uvt.x && uvt.x <= 1 && 0 <= uvt.y && uvt.y <= 1) {
            draw_str(screen.w * uvt.x, screen.h * uvt.y, "[]");
        }
#endif
    }
}

Vector3 to_screen_space(const Camera *cam, Vertex vertex) {
    Matrix3x3 A;
    set_mat_from_v(&A, cam->pw, cam->ph, vector_scale(vertex, -1));

    Vector3 uvt;
    solve_equation_system(&A, &uvt, vector_scale(cam->plane_offset, -1));

    return uvt;
}
