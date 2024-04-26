#include "lvgl/lvgl.h"
#include "contacts_model.h"
#include "keypad_controller.h"
#include "Dialer.h"
#include "call_log_model.h"
#include "list_operations.h"
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
        uint32_t tick_count = lv_tick_get();
		// Convert milliseconds to hours, minutes, and seconds
		uint32_t seconds = tick_count * 5 / 1000;
		uint32_t hours = seconds / 3600;
		uint32_t minutes = (seconds % 3600) / 60;
		uint32_t secs = seconds % 60;

		// Format time string in 12-hour format
		uint32_t hour_12 = hours % 12;
		char am_pm = (hours < 12) ? 'A' : 'P';
		if (hour_12 == 0) hour_12 = 12; // Handle midnight (12 AM)

				

            	lv_obj_t* f_btn;
				static const char * btns[] = {""};
				if(strlen(text)==0){
					modal = lv_msgbox_create(parent, text, LV_SYMBOL_WARNING "Invalid Input!", btns, true);
					lv_obj_t * txt = lv_msgbox_get_text(modal);
					lv_obj_set_style_text_color(txt, lv_color_make(0xff,0x00,0x00),0);
					// lv_obj_set_style_margin_top(modal, 50,0);
				}
				else{
					const char* contact = text;

					ListNode *current = get_contacts_head();
					while (current != NULL) {
						if(strcmp(text, current->data.number)==0)
						{
							contact = current->data.name;
						}
							current = current->next;
					}
					

					char time_str[20]; // Adjust the size as needed
    			    sprintf(time_str, "%02d:%02d %cM", hour_12, minutes, am_pm);
					lv_obj_t *child_ta = lv_obj_get_child(parent, 0);
					lv_obj_t *child_keypad = lv_obj_get_child(parent, 1);
					// modal = lv_msgbox_create(parent, contact, "Calling ...", btns, false);
					lv_obj_add_flag(child_ta, LV_OBJ_FLAG_HIDDEN);					
					lv_obj_add_flag(child_keypad, LV_OBJ_FLAG_HIDDEN);

					dialer_screen(parent, contact, 3);
                   	addToCallLog(contact, time_str);
					// call_log_info str;
					// str.contact = contact;
					// str.time = &time_str;
					// add_to_list(&str, CALL_LOG_NODE);
                    call_log(get_call_log_tab());
                    // lv_textarea_set_text(ta, "Calling ...");
				}
	            lv_obj_set_size(modal, 300, 350);
	            lv_obj_align(modal, LV_ALIGN_CENTER, 0, 0);
	            lv_obj_set_style_text_align(modal, LV_ALIGN_CENTER,0);

	    		
	    		// lv_obj_t* btn = lv_msgbox_get_btns(modal);
	    		// lv_obj_set_style_margin_top(btn, 100, NULL);
	    		// lv_obj_set_style_margin_left(btn, 60, NULL);
				// lv_obj_add_event_cb(btn, msgbox_event_handler, LV_EVENT_CLICKED, NULL);
	    		// lv_obj_add_event_cb(modal, modal_event_cb, LV_EVENT_DELETE, ta);


}


void btn_event_cb(lv_event_t * e)
{
	int count = 0;
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t * btn = lv_event_get_target(e);
	lv_obj_t* screen = lv_obj_get_parent(lv_obj_get_parent(btn));
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
