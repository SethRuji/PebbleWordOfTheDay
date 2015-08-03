#include <pebble.h>
static Window *window;
static SimpleMenuLayer *menu_layer_main;


#define PEBBLE_WIDTH 144
#define PEBBLE_HEIGHT 168
static SimpleMenuSection s_menu_sections[2];

static char text[256];

enum {
  APP_KEY_READY,
  APP_KEY_TEXT,
  APP_KEY_MINUTES,
  APP_KEY_QUIT,
};

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
	menu_layer_main = simple_menu_layer_create(GRect(0, 0, PEBBLE_WIDTH, PEBBLE_HEIGHT));
	
  layer_add_child(window_layer, simple_menu_layer_get_layer(menu_layer_main));
}

static void window_unload(Window *window) {
  simple_menu_layer_destroy(menu_layer_main);
}

static void request_pin(uint32_t minutes) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint32(iter, APP_KEY_MINUTES, minutes);
  dict_write_end(iter);
  app_message_outbox_send();
}

static void check_launch_args() {
/*
	// store launch_arg locally so we can change it later
  uint32_t launch_arg = launch_get_args();

  // make launch_arg 5 so we send a pin that's in future
  if (launch_arg == 0) launch_arg = 5;

  // request a pin in `launch_arg` minutes
  request_pin(launch_arg);

  snprintf(text, sizeof(text), "Requesting a pin to be sent in %d minutes...", (int)launch_arg);
  text_layer_set_text(text_layer, text);
	*/
}

void process_tuple(Tuple *t){
  int key = t->key;
  switch(key){
    case APP_KEY_READY:
      APP_LOG(APP_LOG_LEVEL_INFO, "Got 'app key ready' message!");
			check_launch_args();
			request_word();
      break;
    /*case APP_KEY_TEXT:
		 	APP_LOG(APP_LOG_LEVEL_INFO, "Got 'app key text' message!");
			snprintf(text, sizeof(text), "%s", t->value->cstring);
    	text_layer_set_text(text_layer, text);
      break;
		case APP_KEY_MINUTES:
		 	APP_LOG(APP_LOG_LEVEL_INFO, "Got 'app key minutes' message!");
			snprintf(text, sizeof(text), "%s", t->value->cstring);
    	text_layer_set_text(text_layer, text);
      break;*/
		case APP_KEY_QUIT:
		 	APP_LOG(APP_LOG_LEVEL_INFO, "Got 'quit' message!");
		 	window_stack_pop_all(false);
      break;
  }
}

void inbox(DictionaryIterator *iter, void *context){
	//For all received tuples from the phone, send to process_tuple
  Tuple *t = dict_read_first(iter);
  if(t){
    process_tuple(t);
  }
  while(t != NULL){
    t = dict_read_next(iter);
    if(t){
      process_tuple(t);
    }
  }
}


static void init(void) {
	window = window_create();
  window_set_background_color(window, GColorCobaltBlue);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, false);

  app_message_register_inbox_received(inbox);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}