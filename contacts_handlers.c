#include "contacts_controllers.h"
#include "contacts_model.h"
#include "contacts_view.h"
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Event Callback Function Definitions
void confirm_btn_event_handler(lv_event_t *e) {
// Retrieve the filled information from the text areas
        printf("inside confirm_btn_event_handler\r\n");

    const char *name = lv_textarea_get_text(name_ta);
    const char *number = lv_textarea_get_text(number_ta);
    const char *email = lv_textarea_get_text(email_ta);

    // Add the new contact to the linked list
    addContact(name, number, email);
    lv_obj_clean(main_page);
    createContactLabels(main_page);

    // Hide the add contact page
    lv_obj_add_flag(base4, LV_OBJ_FLAG_HIDDEN);
        printf("outside confirm_btn_event_handler\r\n");
}

void screen_click_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED) {
        // lv_keyboard_set_textarea(kb, ta);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void phone_ta_event_cb(lv_event_t *e) {
    
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void ta_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_INSERT) {
        const char *current_text = lv_textarea_get_text(ta);
        // Check if the inserted character is the first character and is lowercase
        if (strlen(current_text) == 1 && islower(current_text[0])) {
            // Capitalize the first character
            char *modified_text = strdup(current_text);
            modified_text[0] = toupper(modified_text[0]);
            lv_textarea_set_text(ta, modified_text);
            free(modified_text);
        }
    }
}

void float_button_event_cb(lv_event_t *e) {
    printf("inside floatbutton\r\n");
    LV_UNUSED(e);
    printf("inside btn\r\n");
    base4 = lv_obj_create(base);
    lv_obj_set_size(base4, 789, 405 );
    lv_obj_align(base4, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_border_color(base4, lv_color_white(),0);
    lv_obj_clear_flag(base4, LV_OBJ_FLAG_SCROLLABLE);
    
    // Open the UI for adding a new contact
    add_contact_ui(base4);
    printf("outside floatbutton\r\n");
}

void event_handler2(lv_event_t *e) {
     lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        // LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));
           
        if(currentbtn == obj) {
            currentbtn = NULL;
        }
        else {
            currentbtn = obj;
        }
        lv_obj_t * parent = lv_obj_get_parent(obj);
        uint32_t i;
        for(i = 0; i < lv_obj_get_child_cnt(parent); i++) {
            lv_obj_t * child = lv_obj_get_child(parent, i);
            if(child == currentbtn) {
                lv_obj_add_state(child, LV_STATE_CHECKED);
                
            }
            
            else {
                lv_obj_clear_state(child, LV_STATE_CHECKED);
            }
        }
    }
}

void event_handler_up2(lv_event_t *e) {
 lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentbtn == NULL) 
        	return;

        lv_obj_clear_state(currentbtn, LV_STATE_CHECKED);
 		lv_obj_t *parent = lv_obj_get_parent(currentbtn);
        uint32_t index = lv_obj_get_index(currentbtn);
        
        // Move to the previous button
        if (index > 0)
        {
            currentbtn = lv_obj_get_child(parent, index - 1);
        }
        else
        {
            // Handle wrap-around if needed
            currentbtn = lv_obj_get_child(parent, index);
        }

        lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentbtn, LV_ANIM_ON);
    }	
}

void event_handler_dn2(lv_event_t *e) {
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
        if(currentbtn == NULL) return;

        lv_obj_clear_state(currentbtn, LV_STATE_CHECKED);
 		lv_obj_t *parent = lv_obj_get_parent(currentbtn);

        const uint32_t index = lv_obj_get_index(currentbtn);
        uint32_t child_count = lv_obj_get_child_cnt(parent);

     
        // Move to the next button
        if (index < (child_count - 1))
        {
            currentbtn = lv_obj_get_child(parent, index + 1);
        }
        else
        {
            // Handle wrap-around if needed
            currentbtn = lv_obj_get_child(parent, index);
        }

        lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentbtn, LV_ANIM_ON);
    }
}
