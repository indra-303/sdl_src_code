#include "lvgl/lvgl.h"
#include "contacts_model.h"
#include <time.h>

extern lv_obj_t* screen;
extern lv_obj_t *tab2;



static void modal_event_cb(lv_event_t *e)
{
	printf("Inside clearing call event!\r\n");

    lv_obj_t *ta = lv_event_get_user_data(e);
    lv_textarea_set_text(ta, "");  // Clear the textarea when the modal is closed
}

static void msgbox_event_handler(lv_event_t *e)
{
	printf("Inside message box close event!\r\n");
	lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * mbox = lv_obj_get_parent(btn);
    lv_msgbox_close(mbox);
}

void calling_display(lv_obj_t* parent, lv_obj_t* modal, lv_obj_t* ta, char *text) {
    

				static lv_style_t style_msgbox;
				lv_style_init(&style_msgbox);
				// lv_style_set_text_font(&style_msgbox, LV_STATE_DEFAULT, &lv_font_montserrat_20);
				lv_style_set_text_color(&style_msgbox,  lv_color_black());
				lv_style_set_bg_color(&style_msgbox,  lv_palette_main(LV_PALETTE_YELLOW));
				// lv_style_set_margin_left(&style_msgbox, 50);
			    lv_style_set_text_align(&style_msgbox,  LV_ALIGN_CENTER);

            	lv_obj_t* f_btn;
				static const char * btns[] = {LV_SYMBOL_CLOSE, LV_SYMBOL_MUTE, LV_SYMBOL_VOLUME_MAX, ""};
				if(strlen(text)==0){
					modal = lv_msgbox_create(parent, text, LV_SYMBOL_WARNING "Invalid Input!", btns, false);
					lv_obj_t * txt = lv_msgbox_get_text(modal);
					lv_obj_set_style_text_color(txt, lv_color_make(0xff,0x00,0x00),0);
					// lv_obj_set_style_margin_top(modal, 50,0);
				}
				else{
					const char* contact = text;

					ListNode *current = contactList;
					while (current != NULL) {
						if(strcmp(text, current->data.number)==0)
						{
							contact = current->data.name;
						}
							current = current->next;
					}
					
					time_t current_time;
    				time(&current_time);
					
					char time_str[20]; // Adjust the size as needed
    				strftime(time_str, sizeof(time_str), "%H:%M", localtime(&current_time)); 

					modal = lv_msgbox_create(parent, contact, "Calling ...", btns, false);
                   	addToCallLog(contact, time_str);
                    call_log(tab2);
                    // lv_textarea_set_text(ta, "Calling ...");
				}
	            lv_obj_set_size(modal, 300, 350);
	            lv_obj_align(modal, LV_ALIGN_CENTER, 0, 0);
	            lv_obj_set_style_text_align(modal, LV_ALIGN_CENTER,0);

	    		
	    		lv_obj_t* btn = lv_msgbox_get_btns(modal);
	    		// lv_obj_set_style_margin_top(btn, 100, NULL);
	    		// lv_obj_set_style_margin_left(btn, 60, NULL);
				lv_obj_add_event_cb(btn, msgbox_event_handler, LV_EVENT_CLICKED, NULL);
	    		lv_obj_add_event_cb(modal, modal_event_cb, LV_EVENT_DELETE, ta);


}


void btn_event_cb(lv_event_t * e)
{
	int count = 0;
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * btn = lv_event_get_target(e);
	lv_obj_t * ta = lv_event_get_user_data(e);

	lv_obj_set_size(ta, 450, 70);

	lv_obj_t *label;
	const char *btn_text;

	label = lv_obj_get_child(btn, 0); // Get the first child of the button, assuming it's the label
	btn_text = lv_label_get_text(label);
    // printf("Button '%s' clicked\r\n", btn_text);

	if(code == LV_EVENT_CLICKED) {
		static uint8_t cnt = 0;
		cnt++;

		if(strcmp(btn_text, LV_SYMBOL_BACKSPACE) == 0) lv_textarea_del_char(ta);
		else if(strcmp(btn_text, LV_SYMBOL_CALL) == 0) 
			{
				char * text = lv_textarea_get_text(ta);
				lv_obj_t *modal;
				calling_display(screen, modal, ta, text);
				lv_textarea_set_text(ta, "Calling ...");
	        }
		else 
		{
			char * text = lv_textarea_get_text(ta);
			if(strcmp(text, "Calling ...") == 0) 
			{
				lv_textarea_set_text(ta, btn_text);
			}

			else if(strlen(text) <= 10) 
			{ 
				lv_textarea_add_text(ta, btn_text);			
			} 
		}

	}
}
