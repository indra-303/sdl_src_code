// #include "lvgl/lvgl.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// const char *contacts_info[][3] = {
//     {"Thomas", "3683990000", "thomas@example.com"},
//     {"Robin", "8883780370", "robin@example.com"},
// 	{"Andrew", "1234567890", "andrew@example.com"},
// 	{"Brian", "9876543210", "brian@example.com"},
// 	{"George", "5551234567", "george@example.com"},
// 	{"Jerry", "8889990000", "jerry@example.com"},
// 	{"John", "4327990340", "john@example.com"},
// 	{"Kevin", "8585691100", "kevin@example.com"},
// 	{"Mary", "6780990330", "mary@example.com"},
// 	{"Micheal", "7639990000", "micheal@example.com"},
// 	{"Sarah", "6329990370", "sarah@example.com"},

// };

// // Structure for a contact
// typedef struct {
//     char *name;
//     char *number;
//     char *email;
// } Contact;

// // Structure for a linked list node
// typedef struct ListNode {
//     Contact data;
//     struct ListNode *next;
//     // lv_obj_t *subPage;
// } ListNode;

// ListNode *contactList = NULL;

// lv_obj_t * currentbtn = NULL;
// lv_obj_t * menu;
// lv_obj_t * main_page;
// uint32_t btn_cnt = 1;
// int flag = 0;
// lv_obj_t * base2;
// lv_obj_t * base3;
// lv_obj_t * base;

// lv_obj_t *name_ta;
// lv_obj_t *number_ta;
// lv_obj_t *email_ta;
// lv_obj_t *kb; // Global variable to hold the keyboard object
//  static lv_obj_t* cont2;
// lv_obj_t *add_contact_page;
// lv_obj_t * base4;
// lv_obj_t* tab1;
// int count = 0;

// void printContactList() {
//     ListNode *current = contactList;
//     printf("\n\n");
//     while (current != NULL) {
//         printf("Name: %s\n", current->data.name);
//         current = current->next;
//     }
// }



// void addContact(const char *name, const char *number, const char *email) {
//     printf("inside addContact\r\n");
//     printContactList();
//     ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
//     if (newNode == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         return;
//     }

//     newNode->data.name = strdup(name);
//     newNode->data.number = strdup(number);
//     newNode->data.email = strdup(email);
//     newNode->next = NULL; // Initialize next pointer as NULL

//   // If the linked list is empty or the new node should be inserted at the beginning
//     if (contactList == NULL || strcmp(name, contactList->data.name) < 0) {
//             printf("inside if LL empty\r\n");

//         newNode->next = contactList;
//         contactList = newNode;
//          count++; 
//         return;
//     }

//     // Find the appropriate position to insert the new node
//     ListNode *current = contactList;
//     while (current->next != NULL && strcmp(name, current->next->data.name) > 0) {
//             printf("inside while to find place\r\n");

//         current = current->next;
//     }

//     // Insert the new node into the linked list
//     newNode->next = current->next;
//     current->next = newNode;
//     count++;
// printContactList();
//         printf("outside addContact\r\n");

// }

// // Function to free the memory used by the linked list
// void freeContactList() {
//     ListNode *current = contactList;
//     ListNode *next;
//     while (current != NULL) {
//         next = current->next;
//         free(current->data.name);
//         free(current->data.number);
//         free(current->data.email);
//         free(current);
//         current = next;
//     }
//     contactList = NULL;
// }

// lv_obj_t* create_phone_keypad(lv_obj_t* parent) {
//     lv_obj_t* kb = lv_keyboard_create(parent);
//     lv_keyboard_mode_t mode = LV_KEYBOARD_MODE_NUMBER;
//     lv_keyboard_set_mode(kb, mode);
//     return kb;
// }

// static void phone_ta_event_cb(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * ta = lv_event_get_target(e);
//     lv_obj_t * kb = lv_event_get_user_data(e);
//     if(code == LV_EVENT_FOCUSED) {
//         lv_keyboard_set_textarea(kb, ta);
//         lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }

//     if(code == LV_EVENT_DEFOCUSED) {
//         lv_keyboard_set_textarea(kb, NULL);
//         lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }
// }

// static void ta_event_cb(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * ta = lv_event_get_target(e);
//     lv_obj_t * kb = lv_event_get_user_data(e);
    
//     if(code == LV_EVENT_FOCUSED) {
//         lv_keyboard_set_textarea(kb, ta);
//         lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }

//     if(code == LV_EVENT_DEFOCUSED) {
//         lv_keyboard_set_textarea(kb, NULL);
//         lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }

//     if(code == LV_EVENT_INSERT) {
//         const char *current_text = lv_textarea_get_text(ta);
//         // Check if the inserted character is the first character and is lowercase
//         if (strlen(current_text) == 1 && islower(current_text[0])) {
//             // Capitalize the first character
//             char *modified_text = strdup(current_text);
//             modified_text[0] = toupper(modified_text[0]);
//             lv_textarea_set_text(ta, modified_text);
//             free(modified_text);
//         }
//     }
// }

// static void screen_click_cb(lv_event_t * e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t * ta = lv_event_get_target(e);
//     lv_obj_t * kb = lv_event_get_user_data(e);
//     if(code == LV_EVENT_CLICKED) {
//         // lv_keyboard_set_textarea(kb, ta);
//         lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     }

// }

// static void confirm_btn_event_handler(lv_event_t *e) {
//     // Retrieve the filled information from the text areas
//         printf("inside confirm_btn_event_handler\r\n");

//     const char *name = lv_textarea_get_text(name_ta);
//     const char *number = lv_textarea_get_text(number_ta);
//     const char *email = lv_textarea_get_text(email_ta);

//     // Add the new contact to the linked list
//     addContact(name, number, email);
//     lv_obj_clean(main_page);
//     createContactLabels(main_page);

//     // Hide the add contact page
//     lv_obj_add_flag(base4, LV_OBJ_FLAG_HIDDEN);
//         printf("outside confirm_btn_event_handler\r\n");

// }
// void add_contact_ui(lv_obj_t *parent) {
//     // Create a new page for adding a contact
//         printf("inside add_contact_ui\r\n");

//     add_contact_page = lv_obj_create(parent);
//     lv_obj_set_size(add_contact_page, 500, 405 );
    
// 	lv_obj_align(add_contact_page, LV_ALIGN_TOP_MID, 0, -25);
// 	lv_obj_clear_flag(add_contact_page, LV_OBJ_FLAG_SCROLLABLE); 
//      lv_obj_t * kb = lv_keyboard_create(parent);
//     lv_obj_add_flag(add_contact_page, LV_OBJ_FLAG_CLICKABLE);
//     lv_obj_add_event_cb(parent, screen_click_cb, LV_EVENT_CLICKED, kb);
// 	//text area to display digits of pressed key
//     name_ta = lv_textarea_create(add_contact_page);
// 	lv_obj_set_style_border_color(add_contact_page, lv_color_white(), LV_PART_MAIN);
// 	lv_obj_set_size(name_ta, 450, 70);
// 	lv_textarea_set_one_line(name_ta, true);
// 	lv_obj_align(name_ta, LV_ALIGN_TOP_MID, 0, 0);
//     // lv_obj_add_state(name_ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
//     lv_textarea_set_placeholder_text(name_ta, "Name");
//     lv_obj_add_event_cb(name_ta, ta_event_cb, LV_EVENT_ALL, kb); // Assign event handler for text area

//     number_ta = lv_textarea_create(add_contact_page);
//     lv_textarea_set_placeholder_text(number_ta, "Phone Number");
//     lv_obj_set_size(number_ta, 450, 70);
// 	lv_textarea_set_one_line(number_ta, true);
// 	lv_obj_align(number_ta, LV_ALIGN_CENTER, 0, -100);
//     // lv_obj_add_state(number_ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
//     lv_obj_t* phone_kb = create_phone_keypad(parent);
//     lv_obj_add_event_cb(number_ta, phone_ta_event_cb, LV_EVENT_ALL, phone_kb); // Assign event handler for text area

//     email_ta = lv_textarea_create(add_contact_page);
//     lv_textarea_set_placeholder_text(email_ta, "Email");
//     lv_obj_set_size(email_ta, 450, 70);
// 	lv_textarea_set_one_line(email_ta, true);
// 	lv_obj_align(email_ta, LV_ALIGN_CENTER, 0, -50);
//     lv_obj_add_event_cb(email_ta, ta_event_cb, LV_EVENT_ALL, kb); // Assign event handler for text area
    
//     // Create a button to confirm the addition
//     lv_obj_t *confirm_btn = lv_btn_create(add_contact_page);
//     lv_obj_t *confirm_label = lv_label_create(confirm_btn);
//     lv_label_set_text(confirm_label, "Confirm");
//     lv_obj_align(confirm_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
//     lv_obj_add_event_cb(confirm_btn, confirm_btn_event_handler, LV_EVENT_CLICKED, NULL); // Assign event handler for confirmation button

//     lv_keyboard_set_textarea(kb, name_ta);
//     lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
//     lv_obj_add_flag(phone_kb, LV_OBJ_FLAG_HIDDEN);

//         printf("outside add_contact_ui\r\n");


// }


// void float_button_event_cb(lv_event_t *e) {
//     printf("inside floatbutton\r\n");
//     LV_UNUSED(e);
//     printf("inside btn\r\n");
//     base4 = lv_obj_create(base);
//     lv_obj_set_size(base4, 789, 405 );
//     lv_obj_align(base4, LV_ALIGN_CENTER, 0, 0);
//     lv_obj_set_style_border_color(base4, lv_color_white(),0);
//     lv_obj_clear_flag(base4, LV_OBJ_FLAG_SCROLLABLE);
    
//     // Open the UI for adding a new contact
//     add_contact_ui(base4);
//     printf("outside floatbutton\r\n");

// }

// extern void event_handler2(lv_event_t * e);
// extern void event_handler_up2(lv_event_t * e);
// extern void event_handler_dn2(lv_event_t * e);
// void float_button_event_cb(lv_event_t * e);
//  lv_obj_t* cont;
 
// void createContactLabels(lv_obj_t *parent) {
//     printf("inside createContactLabels\r\n");
//     printContactList();
//     // bubbleSort();

//     ListNode *current = contactList;
//     int index = 0;
//     lv_obj_t * label;
//     lv_obj_t * sub_page[count];
        
//     while (current != NULL && index <= count) {

//         sub_page[index] = lv_menu_page_create(menu, current->data.name);
//         cont = lv_menu_cont_create(sub_page[index]);
//         lv_obj_set_size(cont, 744,310);
//         create_contact_profile(cont, current);
        

//         cont = lv_menu_cont_create(parent);
//         // Create an LVGL label for each contact name
//         lv_obj_t *label = lv_label_create(cont);
//         lv_label_set_text(label, current->data.name);
//         lv_obj_set_user_data(label, current);
//         lv_menu_set_load_page_event(menu, cont, sub_page[index]);
        
//         lv_obj_add_event_cb(cont, event_handler2, LV_EVENT_CLICKED, NULL);


//         current = current->next;
//         if(index==0)
//         {
//             currentbtn = cont;
//             lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
//         }
//         index++;
//     }
//         printf("outside createContactLabels\r\n");

// }

// void contacts(lv_obj_t* parent)
// {
//    printf("inside contacts\r\n");
//     ListNode *head = NULL;

//     lv_obj_t * float_btn;
//     lv_obj_t* btn1;
//     lv_obj_t* btn2;
//       /*Create a menu object*/
//     base = lv_obj_create(parent);
//     lv_obj_set_size(base, 798, 405);
//     lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE); 
//     lv_obj_align(base, LV_ALIGN_TOP_MID,0,-25);

//     menu = lv_menu_create(base);
//     lv_obj_set_size(menu, 798, 405);
//     lv_obj_center(menu);
//     lv_obj_clear_flag(menu, LV_OBJ_FLAG_SCROLLABLE);

//     static lv_style_t style2;
//     lv_style_init(&style2);
//     lv_style_set_border_color(&style2, lv_palette_main(LV_PALETTE_GREY));
//     lv_style_set_border_width(&style2, 2);
//     lv_style_set_border_opa(&style2, LV_OPA_40);
//     lv_style_set_border_side(&style2, LV_BORDER_SIDE_FULL);
//     // lv_style_set_height(&style2, 70);
//     // lv_style_set_width(&style2, 120);

//     /*Modify the header*/
//     lv_obj_t * back_btn = lv_menu_get_main_header_back_btn(menu);
//     lv_obj_t * back_button_label = lv_label_create(back_btn);
//     lv_obj_align(back_button_label, LV_ALIGN_CENTER, 0, 0);
// 	lv_obj_add_style(back_btn, &style2, 0);

//     lv_label_set_text(back_button_label, "Back");
    
//     for (int i = 0; i < sizeof(contacts_info) / sizeof(contacts_info[0]); i++) {
//         addContact(contacts_info[i][0], contacts_info[i][1], contacts_info[i][2]);
//     }
 
//      /*Create a main page*/
//     main_page = lv_menu_page_create(menu, NULL);

//     createContactLabels(main_page);

//   	base2 = lv_obj_create(base);
//     lv_obj_set_size(base2, 50, 50 );
//     lv_obj_align(base2, LV_ALIGN_TOP_RIGHT, 0, 0);
//     lv_obj_set_style_border_color(base2, lv_color_white(),0);
//     lv_obj_clear_flag(base2, LV_OBJ_FLAG_SCROLLABLE);

//     btn1 = lv_btn_create(base2);
//     lv_obj_t* label2 = lv_label_create(btn1);
//     lv_label_set_text(label2, LV_SYMBOL_UP);
//     lv_obj_set_size(btn1, 50,50);
//     lv_obj_align(btn1, LV_ALIGN_CENTER,0,0);
//     lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

//     lv_obj_add_event_cb(btn1, event_handler_up2, LV_EVENT_ALL, NULL);
//     lv_group_remove_obj(btn1);


// 	base3 = lv_obj_create(base);
//     lv_obj_set_size(base3, 50, 50 );
//     lv_obj_align(base3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
//     lv_obj_set_style_border_color(base3, lv_color_white(),0);
//     lv_obj_clear_flag(base3, LV_OBJ_FLAG_SCROLLABLE);
    
//     btn2 = lv_btn_create(base3);
//     label2 = lv_label_create(btn2);
//     lv_label_set_text(label2, LV_SYMBOL_DOWN);
//     lv_obj_set_size(btn2, 50,50);
//     lv_obj_align(btn2, LV_ALIGN_CENTER,0,0);
//     lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

//     lv_obj_add_event_cb(btn2, event_handler_dn2, LV_EVENT_ALL, NULL);
//     lv_group_remove_obj(btn2);

//     lv_menu_set_page(menu, main_page);

//      /*Create floating btn*/
//     float_btn = lv_btn_create(base);
//     lv_obj_set_size(float_btn, 50, 50);
//     lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
//     lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -50, -12);
//     lv_obj_add_event_cb(float_btn, float_button_event_cb, LV_EVENT_CLICKED, menu);
//     lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
//     lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_PLUS, 0);
//     lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);

 
// }
