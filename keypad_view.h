#ifndef KEYPAD_VIEW_H
#define KEYPAD_VIEW_H

#include "lvgl/lvgl.h"

void keypad(lv_obj_t *parent);

void set_keypad_tab(lv_obj_t* obj_tab);
lv_obj_t* get_keypad_tab();

#endif 