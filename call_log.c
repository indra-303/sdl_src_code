#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "contacts_view.h"
#include "call_log_model.h"
#include "contacts_controllers.h"
#include "scrolling_handler.h"
#include "Dialer.h"
#include "list_operations.h"
static lv_obj_t *call_log_menu;



void call_log(lv_obj_t *parent)
{

    set_call_log_tab(parent);


    int *flag = 0;
    printf("flag = %d\n",flag);
    int call_log_count = get_call_log_count();
    printf("No. of call logs:%d\n", call_log_count);
    static lv_style_t style2;
    lv_obj_t *main_page;
    lv_style_init(&style2);
    lv_style_set_border_color(&style2, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_border_width(&style2, 2);
    lv_style_set_border_opa(&style2, LV_OPA_40);
    lv_style_set_border_side(&style2, LV_BORDER_SIDE_FULL);
    lv_obj_t *base = lv_obj_create(parent);
    lv_obj_set_size(base, 798, 405);
    lv_obj_align(base, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE);
    int inx = 0;
    call_log_menu = lv_menu_create(base);
    lv_obj_set_size(call_log_menu, 798, 405);
    lv_obj_center(call_log_menu);
    lv_obj_clear_flag(call_log_menu, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *cont;
    lv_obj_t *label;

    lv_obj_t *sub_page[call_log_count];

    
    CallLogNode *currentNode = (CallLogNode*)create_node(CALL_LOG_NODE);
    currentNode = get_head();
    main_page = lv_menu_page_create(call_log_menu, NULL);

    while (currentNode != NULL && inx<=call_log_count)
    {

        sub_page[inx] = lv_menu_page_create(call_log_menu, currentNode->data.name);
        cont = lv_menu_cont_create(sub_page[inx]);
        lv_obj_set_size(cont, 744, 310);

        lv_obj_t *profile_cont = lv_obj_create(cont);
	    lv_obj_set_size(profile_cont, 700, 480);
	    lv_obj_set_style_border_color(profile_cont, lv_color_white(), LV_PART_MAIN);
	
        dialer_screen(profile_cont, currentNode->data.name, 1);

        printf("Profile successfully created\n");

        cont = lv_menu_cont_create(parent);
        cont = lv_menu_cont_create(main_page);
        lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);

        label = lv_label_create(cont);
        lv_label_set_text(label, currentNode->data.name);
        // printf("CALL LOG INFO:%d\n", currentNode->data.name);

        lv_obj_t *label2 = lv_label_create(cont);
        lv_label_set_text(label2, currentNode->data.time);
        lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
        lv_menu_set_load_page_event(call_log_menu, cont, sub_page[inx]);

        CallLogNode* head = (CallLogNode*)create_node(CALL_LOG_NODE);
        head = get_head();

        // printf("Before highlighting node in call log entry\n");

        lv_obj_t* current;

        if (head != NULL && currentNode == head)
        {
            
            // currentButton = cont;

            // if(cont==NULL)
            // {
            //     printf("NULL OBJECT IS BEING ASSIGNED\n");
            // }
            set_Current_Button(cont);

            current = get_Current_Button();
            
            lv_obj_add_state(current, LV_STATE_CHECKED);
            // printf("State of particular call log entry is highlighted\n");

            
        }

        inx++;
        currentNode = currentNode->next;
        // free(head);
    }

    lv_menu_set_page(call_log_menu, main_page);

    lv_obj_t *base2 = lv_obj_create(base);
    lv_obj_set_size(base2, 50, 50);
    lv_obj_align(base2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base2, lv_color_white(), 0);
    lv_obj_clear_flag(base2, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    lv_obj_t *btn = lv_btn_create(base2);
    lv_obj_t *label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_UP);
    lv_obj_set_size(btn, 50, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, event_handler_up, LV_EVENT_ALL, flag);

    lv_group_remove_obj(btn);

    lv_obj_t *base3 = lv_obj_create(base);
    lv_obj_set_size(base3, 50, 50);
    lv_obj_align(base3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base3, lv_color_white(), 0);
    lv_obj_clear_flag(base3, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    btn = lv_btn_create(base3);
    label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_DOWN);
    lv_obj_set_size(btn, 50, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, event_handler_dn, LV_EVENT_ALL, flag);
    lv_group_remove_obj(btn);

    /*Create floating btn*/
    lv_obj_t *float_btn2 = lv_btn_create(base);
    lv_obj_set_size(float_btn2, 50, 50);
    lv_obj_add_flag(float_btn2, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn2, LV_ALIGN_BOTTOM_RIGHT, -50, -12);
    lv_obj_add_event_cb(float_btn2, float_clear_cb, LV_EVENT_CLICKED, call_log_menu);
    lv_obj_set_style_radius(float_btn2, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(float_btn2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_img_src(float_btn2, LV_SYMBOL_TRASH, 0);
    lv_obj_set_style_text_font(float_btn2, lv_theme_get_font_large(float_btn2), 0);

    // free(currentNode);


}


