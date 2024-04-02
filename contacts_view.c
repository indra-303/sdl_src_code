// contacts_view.c
#include "lvgl/lvgl.h"
#include "contacts_view.h"
#include "contacts_controllers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *contacts_info[][3] = {
    {"Thomas", "3683990000", "thomas@example.com"},
    {"Robin", "8883780370", "robin@example.com"},
    {"Andrew", "1234567890", "andrew@example.com"},
    {"Brian", "9876543210", "brian@example.com"},
    {"George", "5551234567", "george@example.com"},
    {"Jerry", "8889990000", "jerry@example.com"},
    {"John", "4327990340", "john@example.com"},
    {"Kevin", "8585691100", "kevin@example.com"},
    {"Mary", "6780990330", "mary@example.com"},
    {"Micheal", "7639990000", "micheal@example.com"},
    {"Sarah", "6329990370", "sarah@example.com"},
};


lv_obj_t * currentbtn = NULL;
lv_obj_t * menu;
lv_obj_t * main_page;
uint32_t btn_cnt = 1;
int flag = 0;
lv_obj_t * base2;
lv_obj_t * base3;
lv_obj_t * base;
lv_obj_t *name_ta;
lv_obj_t *number_ta;
lv_obj_t *email_ta;
lv_obj_t *kb; // Global variable to hold the keyboard object
static lv_obj_t* cont2;
lv_obj_t *add_contact_page;
lv_obj_t * base4;
lv_obj_t* tab1;
extern lv_obj_t *tab2;

lv_obj_t *container;
extern void event_handler2(lv_event_t * e);
extern void event_handler_up2(lv_event_t * e);
extern void event_handler_dn2(lv_event_t * e);
lv_obj_t* cont;
extern void float_button_event_cb(lv_event_t * e); 

extern void confirm_btn_event_handler(lv_event_t *e);


// void calling_cb(lv_event_t *e)
// {
//     lv_obj_t *modal;
//     // lv_obj_t *obj = lv_obj_create(container);
//     // lv_obj_set_size(obj, 640, 300);
//     lv_obj_t* obj = lv_event_get_target(e);
//     lv_obj_t* oo = lv_obj_get_parent(obj);
//     lv_obj_t* gp = lv_obj_get_parent(oo);
//     calling_display(gp, modal, NULL, "Sneha");
// }

lv_obj_t* create_phone_keypad(lv_obj_t* parent) {
    lv_obj_t* kb = lv_keyboard_create(parent);
    lv_keyboard_mode_t mode = LV_KEYBOARD_MODE_NUMBER;
    lv_keyboard_set_mode(kb, mode);
    return kb;
}

void add_contact_ui(lv_obj_t *parent) {
    // Create a new page for adding a contact
        printf("inside add_contact_ui\r\n");

    add_contact_page = lv_obj_create(parent);
    lv_obj_set_size(add_contact_page, 500, 405 );
    
	lv_obj_align(add_contact_page, LV_ALIGN_TOP_MID, 0, -25);
	lv_obj_clear_flag(add_contact_page, LV_OBJ_FLAG_SCROLLABLE); 
     lv_obj_t * kb = lv_keyboard_create(parent);
    lv_obj_add_flag(add_contact_page, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(parent, screen_click_cb, LV_EVENT_CLICKED, kb);
	//text area to display digits of pressed key
    name_ta = lv_textarea_create(add_contact_page);
	lv_obj_set_style_border_color(add_contact_page, lv_color_white(), LV_PART_MAIN);
	lv_obj_set_size(name_ta, 450, 70);
	lv_textarea_set_one_line(name_ta, true);
	lv_obj_align(name_ta, LV_ALIGN_TOP_MID, 0, 0);
    // lv_obj_add_state(name_ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
    lv_textarea_set_placeholder_text(name_ta, "Name");
    lv_obj_add_event_cb(name_ta, ta_event_cb, LV_EVENT_ALL, kb); // Assign event handler for text area

    number_ta = lv_textarea_create(add_contact_page);
    lv_textarea_set_placeholder_text(number_ta, "Phone Number");
    lv_obj_set_size(number_ta, 450, 70);
	lv_textarea_set_one_line(number_ta, true);
	lv_obj_align(number_ta, LV_ALIGN_CENTER, 0, -100);
    // lv_obj_add_state(number_ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
    lv_obj_t* phone_kb = create_phone_keypad(parent);
    lv_obj_add_event_cb(number_ta, phone_ta_event_cb, LV_EVENT_ALL, phone_kb); // Assign event handler for text area

    email_ta = lv_textarea_create(add_contact_page);
    lv_textarea_set_placeholder_text(email_ta, "Email");
    lv_obj_set_size(email_ta, 450, 70);
	lv_textarea_set_one_line(email_ta, true);
	lv_obj_align(email_ta, LV_ALIGN_CENTER, 0, -50);
    lv_obj_add_event_cb(email_ta, ta_event_cb, LV_EVENT_ALL, kb); // Assign event handler for text area
    
    // Create a button to confirm the addition
    lv_obj_t *confirm_btn = lv_btn_create(add_contact_page);
    lv_obj_t *confirm_label = lv_label_create(confirm_btn);
    lv_label_set_text(confirm_label, "Confirm");
    lv_obj_align(confirm_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(confirm_btn, confirm_btn_event_handler, LV_EVENT_CLICKED, NULL); // Assign event handler for confirmation button

    lv_keyboard_set_textarea(kb, name_ta);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(phone_kb, LV_OBJ_FLAG_HIDDEN);

        printf("outside add_contact_ui\r\n");


}

void createContactLabels(lv_obj_t *parent) {
    printf("inside createContactLabels\r\n");
    // printContactList();
    // bubbleSort();

    ListNode *current = contactList;
    int index = 0;
    lv_obj_t * label;
    lv_obj_t * sub_page[count];
        
    while (current != NULL && index <= count) {

        sub_page[index] = lv_menu_page_create(menu, current->data.name);
        cont = lv_menu_cont_create(sub_page[index]);
        lv_obj_set_size(cont, 744,310);
        create_contact_profile(cont, current);
        

        cont = lv_menu_cont_create(parent);
        // Create an LVGL label for each contact name
        lv_obj_t *label = lv_label_create(cont);
        lv_label_set_text(label, current->data.name);
        lv_obj_set_user_data(label, current);
        lv_menu_set_load_page_event(menu, cont, sub_page[index]);
        
        lv_obj_add_event_cb(cont, event_handler2, LV_EVENT_CLICKED, NULL);


        current = current->next;
        if(index==0)
        {
            currentbtn = cont;
            lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
        }
        index++;
    }
        printf("outside createContactLabels\r\n");

}

int create_contact_profile(lv_obj_t *parent, char *name[])
{
    printf("Inside profile creation\n");

    static lv_style_t style;

    lv_style_init(&style);
	lv_style_set_shadow_width(&style, 40);
	lv_style_set_shadow_color(&style, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_40));
	lv_style_set_shadow_opa(&style, LV_OPA_50);
	lv_style_set_shadow_ofs_x(&style, 10);

	lv_obj_t *profile_cont = lv_obj_create(parent);
	lv_obj_set_size(profile_cont, 700, 275);
	lv_obj_set_style_border_color(profile_cont, lv_color_white(), LV_PART_MAIN);
	
    container = lv_obj_create(profile_cont);
	lv_obj_set_size(container, 640, 205);
	lv_obj_align(container, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_bg_color(container, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_10), NULL);
	
	// Create a label for the name
	lv_obj_t *name_label = lv_label_create(container);
	lv_label_set_text(name_label, name[0]);
	lv_obj_align(name_label, LV_ALIGN_TOP_MID, 0, 0);
	// lv_obj_set_style_text_font(name_label, );
	// Create a label for contact number
	lv_obj_t *contact_label = lv_label_create(container);
	// lv_obj_add_style(contact_label, &style, 0);
	lv_label_set_text_fmt(contact_label, "Phone: %s", name[1]);
	lv_obj_align(contact_label, LV_ALIGN_LEFT_MID, 50, 50);

	lv_obj_t *email_label = lv_label_create(container);
	lv_label_set_text_fmt(email_label, "Email: %s",name[2]);
	lv_obj_align(email_label, LV_ALIGN_LEFT_MID, 50, 0);

    lv_obj_t *call_btn = lv_btn_create(container);
    lv_obj_t *call_label = lv_label_create(call_btn);
    lv_label_set_text(call_label, LV_SYMBOL_CALL);
    lv_obj_align(call_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
    // lv_obj_add_event_cb(call_btn, calling_cb, LV_EVENT_CLICKED, NULL);

    return 1;
}

void contacts(lv_obj_t* parent)
{
   printf("inside contacts\r\n");
    ListNode *head = NULL;

    lv_obj_t * float_btn;
    lv_obj_t* btn1;
    lv_obj_t* btn2;
      /*Create a menu object*/
    base = lv_obj_create(parent);
    lv_obj_set_size(base, 798, 405);
    lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE); 
    lv_obj_align(base, LV_ALIGN_TOP_MID,0,-25);

    menu = lv_menu_create(base);
    lv_obj_set_size(menu, 798, 405);
    lv_obj_center(menu);
    lv_obj_clear_flag(menu, LV_OBJ_FLAG_SCROLLABLE);

    static lv_style_t style2;
    lv_style_init(&style2);
    lv_style_set_border_color(&style2, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_border_width(&style2, 2);
    lv_style_set_border_opa(&style2, LV_OPA_40);
    lv_style_set_border_side(&style2, LV_BORDER_SIDE_FULL);
    // lv_style_set_height(&style2, 70);
    // lv_style_set_width(&style2, 120);

    /*Modify the header*/
    lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
    lv_obj_t * back_button_label = lv_label_create(back_btn);
    lv_obj_align(back_button_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_style(back_btn, &style2, 0);

    lv_label_set_text(back_button_label, "Back");
    
    for (int i = 0; i < sizeof(contacts_info) / sizeof(contacts_info[0]); i++) {
        addContact(contacts_info[i][0], contacts_info[i][1], contacts_info[i][2]);
    }
 
     /*Create a main page*/
    main_page = lv_menu_page_create(menu, NULL);

    createContactLabels(main_page);

  	base2 = lv_obj_create(base);
    lv_obj_set_size(base2, 50, 50 );
    lv_obj_align(base2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base2, lv_color_white(),0);
    lv_obj_clear_flag(base2, LV_OBJ_FLAG_SCROLLABLE);

    btn1 = lv_btn_create(base2);
    lv_obj_t* label2 = lv_label_create(btn1);
    lv_label_set_text(label2, LV_SYMBOL_UP);
    lv_obj_set_size(btn1, 50,50);
    lv_obj_align(btn1, LV_ALIGN_CENTER,0,0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

    lv_obj_add_event_cb(btn1, event_handler_up2, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn1);


	base3 = lv_obj_create(base);
    lv_obj_set_size(base3, 50, 50 );
    lv_obj_align(base3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base3, lv_color_white(),0);
    lv_obj_clear_flag(base3, LV_OBJ_FLAG_SCROLLABLE);
    
    btn2 = lv_btn_create(base3);
    label2 = lv_label_create(btn2);
    lv_label_set_text(label2, LV_SYMBOL_DOWN);
    lv_obj_set_size(btn2, 50,50);
    lv_obj_align(btn2, LV_ALIGN_CENTER,0,0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

    lv_obj_add_event_cb(btn2, event_handler_dn2, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn2);

    lv_menu_set_page(menu, main_page);

     /*Create floating btn*/
    float_btn = lv_btn_create(base);
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -50, -12);
    lv_obj_add_event_cb(float_btn, float_button_event_cb, LV_EVENT_CLICKED, menu);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_PLUS, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);

 
}
