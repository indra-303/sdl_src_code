#include "lvgl/lvgl.h"
#include <stdlib.h>
#include "call_log_model.h"
#include "contacts_model.h"

void event_handler_up(lv_event_t * e)
{
    int flag = lv_event_get_user_data(e);
    lv_obj_t* currentbtn;
    if(flag == 1)
    {
        currentbtn = get_Current_Btn();
    }
    else if(flag == 0)
        {
            currentbtn = get_Current_Button();
        }

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
            // set_Current_Btn(lv_obj_get_child(parent, index - 1));
            // currentbtn = get_Current_Btn();

            if(flag == 1)
            {
                set_Current_Btn(lv_obj_get_child(parent, index - 1));
                 currentbtn = get_Current_Btn();
            }
            else if (flag == 0)
            {
                set_Current_Button(lv_obj_get_child(parent, index - 1));
                currentbtn = get_Current_Button();
            }
        }
        else
        {
            // Handle wrap-around if needed
        //    set_Current_Btn(lv_obj_get_child(parent, index));
        //    currentbtn = get_Current_Btn();

         if(flag == 1){
                set_Current_Btn(lv_obj_get_child(parent, index));
                currentbtn = get_Current_Btn();
            }
            else if(flag == 0){
                set_Current_Button(lv_obj_get_child(parent, index));
                currentbtn = get_Current_Button();
            }
        }

        lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentbtn, LV_ANIM_ON);
    }	
    
}

void event_handler_dn(lv_event_t * e)
{
    int *flag = lv_event_get_user_data(e);
    lv_obj_t* currentbtn = NULL;
    if(flag==1)
    {
        currentbtn = get_Current_Btn();
    } else if(flag == 0)
    {
        currentbtn = get_Current_Button();

    }
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
            // set_Current_Btn(lv_obj_get_child(parent, index + 1));
            // currentbtn = get_Current_Btn();
             if(flag == 1)
            {
                set_Current_Btn(lv_obj_get_child(parent, index + 1));
                currentbtn = get_Current_Btn();  
            }
            else if(flag == 0)
            {
                set_Current_Button(lv_obj_get_child(parent, index + 1));
                currentbtn = get_Current_Button();
            }
        }
        else
        {
            // Handle wrap-around if needed
            // set_Current_Button(lv_obj_get_child(parent, index));
            // currentbtn = get_Current_Btn();

              if(flag == 1)
            {
                set_Current_Btn(lv_obj_get_child(parent, index));
                currentbtn = get_Current_Btn(); 
            }
            else if(flag == 0)
            {
                set_Current_Button(lv_obj_get_child(parent, index));
                currentbtn = get_Current_Button();
            }
        }

        lv_obj_add_state(currentbtn, LV_STATE_CHECKED);
        lv_obj_scroll_to_view(currentbtn, LV_ANIM_ON);
    }
}

