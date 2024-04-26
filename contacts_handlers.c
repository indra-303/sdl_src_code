#include "contacts_controllers.h"
#include "contacts_model.h"
#include "contacts_view.h"
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static lv_obj_t* main_page;

// Event Callback Function Definitions
void confirm_btn_event_handler(lv_event_t *e) {
// Retrieve the filled information from the text areas
        printf(">>inside confirm_btn_event_handler\r\n");

    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *base4 = lv_obj_get_parent(lv_obj_get_parent(obj));
    TextareaInfo *info =(TextareaInfo*) lv_event_get_user_data(e);

    main_page = get_mainpage();
    
    const char *name = lv_textarea_get_text(info->name_ta);
    const char *number = lv_textarea_get_text(info->number_ta);
    const char *email = lv_textarea_get_text(info->email_ta);
    printf("name: %s\n", name);
    // Add the new contact to the linked list
    addContact(name, number, email);
    lv_obj_clean(main_page);
    createContactLabels(main_page);

    // Hide the add contact page
    lv_obj_add_flag(base4, LV_OBJ_FLAG_HIDDEN);
        printf(">>outside confirm_btn_event_handler\r\n");
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

void contact_delete_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(btn);

    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_t *label = lv_obj_get_child(parent, 0);
        const char *contactName = lv_label_get_text(label);

        popup_Box(parent, contactName);
    }
}

// Event Callback Function Definitions
void close_msgbox(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(btn);
    const char *name = lv_event_get_user_data(e);
    lv_obj_t *menu = get_menu();
    main_page = get_mainpage();
    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        const char *contactName = lv_label_get_text(label);
        lv_obj_t *tab1 = get_contacts_tab();

        if (strcmp(contactName, "YES") == 0)
        {
            freeContactList(name);
            lv_obj_clean(main_page);
            createContactLabels(main_page);
            lv_obj_del(parent);
            lv_obj_del(menu);
            contacts(tab1); // Re-create the menu

            // lv_menu_set_load_page_event(menu, cont,main_page);
        }
        else
        {
            lv_obj_del(parent);
        }

       
    }
}
