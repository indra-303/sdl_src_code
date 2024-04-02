#include "lvgl/lvgl.h"
#include <stdlib.h>

extern lv_obj_t * currentButton;
extern lv_obj_t *tab2;


void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        // LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));

        if(currentButton == obj) {
            currentButton = NULL;
        }
        else {
            currentButton = obj;
        }
        lv_obj_t * parent = lv_obj_get_parent(obj);
        uint32_t i;
        for(i = 0; i < lv_obj_get_child_cnt(parent); i++) {
            lv_obj_t * child = lv_obj_get_child(parent, i);
            if(child == currentButton) {
                lv_obj_add_state(child, LV_STATE_CHECKED);
            }
           
            else {
                lv_obj_clear_state(child, LV_STATE_CHECKED);
            }
        }
    }
}


void event_handler_up(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) 
        	return;

        lv_obj_clear_state(currentButton, LV_STATE_CHECKED);
 		lv_obj_t *parent = lv_obj_get_parent(currentButton);
        uint32_t index = lv_obj_get_index(currentButton);
        
        // Move to the previous button
        if (index > 0)
        {
            currentButton = lv_obj_get_child(parent, index - 1);
        }
        else
        {
            // Handle wrap-around if needed
            currentButton = lv_obj_get_child(parent, index);
        }

        lv_obj_add_state(currentButton, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }	
    
}

void event_handler_dn(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentButton == NULL) return;

        lv_obj_clear_state(currentButton, LV_STATE_CHECKED);
 		lv_obj_t *parent = lv_obj_get_parent(currentButton);

        const uint32_t index = lv_obj_get_index(currentButton);
        uint32_t child_count = lv_obj_get_child_cnt(parent);

     
        // Move to the next button
        if (index < (child_count - 1))
        {
            currentButton = lv_obj_get_child(parent, index + 1);
        }
        else
        {
            // Handle wrap-around if needed
            currentButton = lv_obj_get_child(parent, index);
        }

        lv_obj_add_state(currentButton, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentButton, LV_ANIM_ON);
    }
}

void float_clear_cb(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) ) {

        freeCallLog();
        call_log(tab2);

    }
}
