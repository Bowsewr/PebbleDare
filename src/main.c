/*
                 
                                  ------------------------------------------
                                  | LUDUM DARE 32 - Unconventional Weapons |
                                  ------------------------------------------ 
                 
                          ~My first pebble app and first solo programming adventure~
                      
                      
                                          -Bowsewr   04/18/2015


          **Special Thanks to those who helped me in stream and joined me in this learning process**
                  --DemonicEgg
                  --Willx71
                  --Pythe314
                  --
                  --
*/


#include <pebble.h>

#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 6
#define NUM_SECOND_MENU_ITEMS 0
#define NUM_MENU_ICONS 6
  
static Window *main_window;
static MenuLayer *my_menu_layer;

static int current_icon = 0;  
  
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1: 
      return NUM_SECOND_MENU_ITEMS;
    default:
      return 0;
  }
}


// Special Props to DemonicEgg for solving the uint16 vs int16 riddle. thanks!  //
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 16;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer, "  It's Unconventional...");
      break;

//    case 1: 
//      menu_cell_basic_header_draw(ctx, cell_layer, "Header 2");
//      break;
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->section) {
    case 0: 
      switch (cell_index->row) {
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 1", "OF DEATH", NULL);
          break;
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 2", "UNSTOPPABLE", NULL);
          break;
        case 2: 
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 3", "GOD-LIKE", NULL);
          break;
        case 3: 
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 4", "NOOB", NULL);
          break;
        case 4: 
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 5", "hope this works", NULL);
          break;
        case 5: 
          menu_cell_basic_draw(ctx, cell_layer, "WEAPON 6", "PLEASE", NULL);
          break;
          
      }
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  switch (cell_index->row) {
    case 1:
      current_icon = (current_icon + 1) % NUM_MENU_ICONS;
      layer_mark_dirty(menu_layer_get_layer(menu_layer));
     break;
  }
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
    
  my_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(my_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  menu_layer_set_click_config_onto_window(my_menu_layer, window);
  
  layer_add_child(window_layer, menu_layer_get_layer(my_menu_layer));
  
}

static void main_window_unload(Window *window) {
  menu_layer_destroy(my_menu_layer);
  
}

static void init() {
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(main_window, true);
}

static void deinit() {
  window_destroy(main_window);
  
}

int main(void) {
  init();
  app_event_loop();
  deinit();
  
}