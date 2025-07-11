#ifndef RENDER_H
#define RENDER_H
#include "vmath.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef Vector3 Vertex;

typedef struct {
  Vector3 position;
  float z_angle, y_angle;

  Vector3 plane_offset, pw, ph;
} Camera;

typedef struct {
  int w, h;
} Screen;

Camera init_camera(float fov, float plane_distance, float aspect_ratio);

void draw_vertex(Screen screen, const Camera *cam, Vertex vertex, const char* str);
void draw_vertecies(Screen screen, const Camera *cam, const Vertex *vertecies,
                    int vertex_count);

Vector3 to_screen_space(const Camera *cam, Vertex vertex);

#endif
