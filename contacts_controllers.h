#ifndef CONTACTS_HANDLERS_H
#define CONTACTS_HANDLERS_H

#include "lvgl/lvgl.h"

// Event Callback Function Declarations
void confirm_btn_event_handler(lv_event_t *e);
void screen_click_cb(lv_event_t *e);
void phone_ta_event_cb(lv_event_t *e);
void ta_event_cb(lv_event_t *e);
void float_button_event_cb(lv_event_t *e);
void event_handler2(lv_event_t *e);

void contact_delete_cb(lv_event_t *e);

void close_msgbox(lv_event_t *e);

#endif /* CONTACTS_HANDLERS_H */
