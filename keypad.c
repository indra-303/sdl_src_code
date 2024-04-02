#include "lvgl/lvgl.h"

lv_obj_t* screen;
lv_obj_t *tab2;

extern char *contacts_info[][3];

static void modal_event_cb(lv_event_t *e);

static void msgbox_event_handler(lv_event_t *e);

void btn_event_cb(lv_event_t * e);

/*Keypad UI*/
void keypad(lv_obj_t *parent)
{

	//base screen, common for text area as well as keypad
	screen = lv_obj_create(parent);
	lv_obj_set_size(screen, 798, 405);
	lv_obj_align(screen, LV_ALIGN_TOP_MID, 0, -25);
	lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE); 

	//text area to display digits of pressed key
	lv_obj_t * ta = lv_textarea_create(screen);
	lv_obj_set_style_border_color(screen, lv_color_white(), LV_PART_MAIN);
	lv_obj_set_size(ta, 450, 70);
	lv_textarea_set_one_line(ta, true);
	lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, -25);
    lv_obj_add_state(ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
    // lv_obj_set_style_transform_angle(ta, 2700, 0);
    // lv_obj_set_style_margin_left(ta, 50, 0);

	  uint32_t i;
	  const int num_rows = 4 ;
	  const int num_cols = 3;
    const int btn_width = 100; // Adjust button size as needed
    const int btn_height = 55;
    int count = 0;
    //creating a container for all the keys
    lv_obj_t * cont = lv_obj_create(screen);
    lv_obj_set_size(cont, 450, 320);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, 25);

    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE); 
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE); 


    /* This loop creates buttons, add labels to each button
    	and aligns buttons
    */
    for (int row = 0; row < num_rows; ++row) {
    	for (int col = 0; col < num_cols; ++col) {
    		lv_obj_t * btn = lv_btn_create(cont);

    		lv_obj_set_size(btn, btn_width, btn_height);

    		if(row==0)
    		{
            	lv_obj_align(btn, LV_ALIGN_TOP_LEFT, col * (btn_width + 50), -22); // Adjust spacing as needed

            }

            else
            {
            	lv_obj_align(btn, LV_ALIGN_TOP_LEFT, col * (btn_width + 48), row * (btn_height + 25) - 22); // Adjust spacing as needed
            }

            // Set a unique identifier for each button
            lv_obj_set_tile_id(btn, row+1, col+1, LV_ANIM_OFF);


            lv_obj_t * label = lv_label_create(btn);
            
            if(row==3)
            {
            	if(col==2)
            		lv_label_set_text_fmt(label, "%s", LV_SYMBOL_CALL);
            	else if(col==1)
            		lv_label_set_text(label, "0");
            	else if(col==0)
            		lv_label_set_text_fmt(label, "%s", LV_SYMBOL_BACKSPACE);
            }
            else{
            	lv_label_set_text_fmt(label, "%d",  row * num_cols + col + 1);
            }
            lv_obj_align(label,  LV_ALIGN_CENTER, 0, 0);

            //event handler for clicking buttons
		    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, ta);

        }
    }

}