#include "lvgl/lvgl.h"
#include <stdlib.h>
#include "call_log_model.h"
#include "contacts_model.h"
#include "contacts_view.h"
#include "keypad_view.h"


void call_cancel_handler(lv_event_t *e) {
    int *flag = lv_event_get_user_data(e);
    if(flag == 1){
        call_log(get_call_log_tab());
    }
    else if(flag==2){
        lv_obj_t* tab1 = get_contacts_tab();
        contacts(tab1);
    }
    else if(flag==3){
        lv_obj_t* tab1 = get_keypad_tab();
        keypad(tab1);
    }
}


void dialer_screen(lv_obj_t *parent, char *name, int *flag)
{
    static lv_style_t dialer_style;
    lv_style_init(&dialer_style);
    lv_style_set_shadow_width(&dialer_style, 40);
	lv_style_set_shadow_color(&dialer_style, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_40));
	lv_style_set_shadow_opa(&dialer_style, LV_OPA_50);
	lv_style_set_shadow_ofs_x(&dialer_style, 10);

	
    lv_obj_t* container = lv_obj_create(parent);
	lv_obj_set_size(container, 350, 275);
	lv_obj_align(container, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_bg_color(container, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_10), NULL);

    lv_obj_t *name_label = lv_label_create(container);
	lv_label_set_text(name_label, "Calling...");
	lv_obj_align(name_label, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *contact_label = lv_label_create(container);

  
    lv_label_set_text_fmt(contact_label, "%s", name);
    
    lv_obj_align(contact_label, LV_ALIGN_TOP_MID, 0, 50);


    lv_obj_t *call_btn = lv_btn_create(container);
    lv_obj_t *call_label = lv_label_create(call_btn);
    lv_label_set_text(call_label, LV_SYMBOL_CLOSE);
    lv_obj_align(call_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(call_btn, call_cancel_handler,LV_EVENT_CLICKED, flag);

}

