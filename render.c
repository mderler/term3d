#include <math.h>

#include "render.h"
#include "drawing.h"

Camera init_camera(float fov, float plane_distance, float aspect_ratio) {
  Camera cam = {0};

  float half_fov_rad = (fov * M_PI / 180.0) / 2.0;
  float half_plane_width = plane_distance * tanf(half_fov_rad);

  Vector3 offset;
  offset.x = plane_distance;
  offset.y = half_plane_width;

  Vector3 pw = {0};
  pw.y = -2 * half_plane_width;

  Vector3 ph = {0};
  ph.z = (1 / aspect_ratio) * pw.y;

  cam.plane_offset = offset;
  cam.pw = pw;
  cam.ph = ph;

  return cam;
}

void draw_vertecies(Screen screen, const Camera *cam, const Vertex *vertecies,
                    int vertex_count) {

  Matrix3x3 rot;
  set_rotation_mat_z(&rot, cam->z_angle); // TODO: Support x angle

  for (int i = 0; i < vertex_count; i++) {
    // transform vertex
    Vertex vertex = vertecies[i];
    vertex = mat_mul_v(&rot, vertex);

    // to screen space coords (u,v,t)
    Vector3 uvt = to_screen_space(cam, vertex);
    draw_char(screen.w * uvt.x, screen.h * uvt.y, 'X');
  }
}

Vector3 to_screen_space(const Camera *cam, Vertex vertex) {
  Vector3 cam_vert = vector_sub(vertex, cam->position);

  Vector3 uvt;
  Matrix3x3 A;
  set_mat_from_v(&A, cam->pw, cam->ph, vector_scale(cam_vert, -1));
  solve_equation_system(&A, &uvt, vector_scale(cam->plane_offset, -1));

  return uvt;
}
