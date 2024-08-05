#include "../include/Lato.h"
#include <GLFW/glfw3.h>
#include <assert.h>
#include <string.h>

int test_font_path(const char *font_name) {
  char *font_path;
  if (get_font_path(&font_path, font_name) != LATO_OK) {
    return 0;
  }

  struct stat statbuf;
  int file_exists =
      (stat(font_path, &statbuf)) == 0 && S_ISREG(statbuf.st_mode);

  free(font_path);

  return file_exists;
}

void test_lato_init() {
  int keycode_arr[] = {'h', 'e', 'l', 'o', 'w', 'r', 'd', '\0'};
  int *keycodes = (int *)malloc(sizeof(keycode_arr));
  memcpy(keycodes, keycode_arr, sizeof(keycode_arr));

  LatoContext context = lato_context_init(0, 0, 1920, 1080);

  lato_context_set_characters(&context, keycodes);
  lato_context_set_font_size(&context, 40);
  lato_context_set_font_weight(&context, 16);
  lato_context_set_font_family(&context, "Monospace");

  Lato lato;
  lato_init(&lato, &context);

  float color[4] = {0, 0, 0, 0};
  lato_set_solid_color(&lato, color);

  assert(lato.char_info['h'].size[0] == 108);
  assert(lato.char_info['h'].size[1] == 188);
  assert(lato.char_info['e'].size[0] == 117);
  assert(lato.char_info['e'].size[1] == 139);
  assert(lato.char_info['l'].size[0] == 123);
  assert(lato.char_info['l'].size[1] == 191);
  assert(lato.char_info['o'].size[0] == 116);
  assert(lato.char_info['o'].size[1] == 139);
  assert(lato.char_info['w'].size[0] == 134);
  assert(lato.char_info['w'].size[1] == 133);
  assert(lato.char_info['r'].size[0] == 134);
  assert(lato.char_info['r'].size[1] == 136);
  assert(lato.char_info['d'].size[0] == 117);
  assert(lato.char_info['d'].size[1] == 191);

  lato_destroy(&lato, &context);
  lato_context_destroy(&context);
}

int main() {
  assert(test_font_path("Arial"));
  assert(test_font_path("Monospace"));

  glfwInit();
  GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  test_lato_init();

  int keycode_arr[] = {'h', 'e', 'l', 'o', 'w', 'r', 'd', '\0'};
  int *keycodes = (int *)malloc(sizeof(keycode_arr));
  memcpy(keycodes, keycode_arr, sizeof(keycode_arr));

  LatoContext context = lato_context_init(0, 0, 1920, 1080);

  lato_context_set_characters(&context, keycodes);
  lato_context_set_font_size(&context, 40);
  lato_context_set_font_weight(&context, 16);
  lato_context_set_font_family(&context, "Monospace");

  Lato lato;
  lato_init(&lato, &context);

  while (!glfwWindowShouldClose(window)) {
    lato_text_place(&lato, &context, "hello world", 10, 10);
    lato_text_render_call(&lato, &context);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
