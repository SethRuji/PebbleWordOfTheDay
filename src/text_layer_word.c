#include <pebble.h>
#include "text_layer_word.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_18_bold;
static TextLayer *s_textlayer_word;
static TextLayer *s_textlayer_description;
static ScrollLayer *s_scroll_layer;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_textlayer_word
  s_textlayer_word = text_layer_create(GRect(0, 0, 144, 40));
  text_layer_set_text(s_textlayer_word, "LongerWord");
  text_layer_set_text_alignment(s_textlayer_word, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_word, s_res_gothic_24_bold);
	text_layer_set_background_color(s_textlayer_word, GColorVividCerulean);
	//text_layer_set_text_color(s_textlayer_word, GColorWhite);
  //layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_word);
	
	// Initialize the scroll layer
  GRect bounds = layer_get_frame(window_get_root_layer(s_window));
  s_scroll_layer = scroll_layer_create(bounds);
	scroll_layer_set_click_config_onto_window(s_scroll_layer, s_window);
	
  // s_textlayer_description
  s_textlayer_description = text_layer_create(GRect(0, 40, 144, 3000));
  text_layer_set_text(s_textlayer_description, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras risus leo, congue tristique elit at, pretium euismod nulla. Cras maximus elementum metus, vel fringilla mi fermentum at. Maecenas sed quam aliquet, dignissim nunc ac, elementum eros. Vestibulum iaculis ipsum et nulla volutpat fermentum. Nulla malesuada quam congue lacus molestie, ut pulvinar felis tempus. Curabitur lacinia urna sed aliquam pretium. Maecenas lorem quam, placerat ac sodales a, venenatis ac libero. Sed ac lacus porta, placerat turpis vel, varius eros.");
  text_layer_set_font(s_textlayer_description, s_res_gothic_18_bold);
	// Trim text layer and scroll content to fit text box
  GSize max_size = text_layer_get_content_size(s_textlayer_description);
  text_layer_set_size(s_textlayer_description, max_size);
  scroll_layer_set_content_size(s_scroll_layer, GSize(bounds.size.w, max_size.h + 4));
	scroll_layer_add_child(s_scroll_layer, (Layer *)s_textlayer_word);
	scroll_layer_add_child(s_scroll_layer, (Layer *)s_textlayer_description);
	
	layer_add_child(window_get_root_layer(s_window), (Layer *)s_scroll_layer);
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
