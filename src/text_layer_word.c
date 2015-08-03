#include <pebble.h>
#include "text_layer_word.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18_bold;
static TextLayer *s_textlayer_word;
static TextLayer *s_textlayer_description;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_textlayer_word
  s_textlayer_word = text_layer_create(GRect(0, 0, 144, 40));
  text_layer_set_text(s_textlayer_word, "LongerWord");
  text_layer_set_text_alignment(s_textlayer_word, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_word, s_res_gothic_28_bold);
	text_layer_set_background_color(s_textlayer_word, GColorVividCerulean);
	//text_layer_set_text_color(s_textlayer_word, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_word);
  
  // s_textlayer_description
  s_textlayer_description = text_layer_create(GRect(0, 40, 144, 128));
  text_layer_set_text(s_textlayer_description, "Text layer");
  text_layer_set_font(s_textlayer_description, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_description);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_word);
  text_layer_destroy(s_textlayer_description);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_text_layer_word(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_text_layer_word(void) {
  window_stack_remove(s_window, true);
}
