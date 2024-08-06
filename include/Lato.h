#ifndef LIBLATO_H
#define LIBLATO_H

#define LENGTH 400

#include "Character.h"
#include "Context.h"
#include "Error.h"
#include "GL/glext.h"
#include "Shaders.h"
#include "math.h"
#include <GL/gl.h>
#include <fontconfig/fontconfig.h>
#include <freetype/freetype.h>
#include <freetype/ftoutln.h>
#include <freetype/ftstroke.h>
#include <freetype/ftsynth.h>
#include <ft2build.h>
#include <string.h>

typedef enum {
  COLOR_SOLID,
  COLOR_GRADIENT,
  COLOR_TRIPLE_GRADIENT,
} ColorType;

typedef struct {
  ColorType type;
  float color1[4];
  float color2[4];
  float color3[4];
  float degrees;
} Color;

typedef struct {
  float letter_map[LENGTH];
  Mat4 transform[LENGTH];
  float color1[LENGTH][4];
  float color2[LENGTH][4];
  float color3[LENGTH][4];
  float degrees[LENGTH];
} InstanceData;

typedef struct {
  InstanceData instance_data;
  GLuint texture_array;
  int index;
  Character *char_info;
  GLuint shaders[3];
  Color color;
  GLuint UBO;
  GLint viewport[4];
} Lato;

LatoErrorCode lato_init(Lato *lato, LatoContext *lato_context);

void lato_destroy(Lato *lato, LatoContext *lato_context);

void lato_set_solid_color(Lato *lato, float color[4]);

void lato_set_gradient_color(Lato *lato, float start_color[4],
                             float end_color[4], float deg);

void lato_set_triple_gradient_color(Lato *lato, float start_color[4],
                                    float mid_color[4], float end_color[4],
                                    float deg);

void lato_text_place(Lato *lato, LatoContext *lato_context, char *text, float x,
                     float y);

void lato_text_render_call(Lato *lato);

LatoErrorCode get_font_path(char **buffer, const char *font_name);

#endif
