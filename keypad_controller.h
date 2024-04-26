#ifndef KEYPAD_CONTROLLER_H
#define KEYPAD_CONTROLLER_H

#include "lvgl/lvgl.h"

static void modal_event_cb(lv_event_t *e);
static void msgbox_event_handler(lv_event_t *e);

void calling_display(lv_obj_t* parent, lv_obj_t* modal, lv_obj_t* ta, char *text);
void btn_event_cb(lv_event_t * e);

#endif 