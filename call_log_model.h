//For importing and defining once per call
#ifndef CALLOG_MODEL_H
#define CALLOG_MODEL_H

/*Includes*/
#include "lvgl/lvgl.h"
#include <stdlib.h>

/*Templates*/
// #define NODE(type, name) \
//     if(type==Call_log) { \
//             CallLogNode name;\
//     }

    // else if (type==Contact)



/*Variables*/

//Extern variables

//Global Variables for the module


/*Structs*/
typedef struct {
    char *name;           // Contact name
    char *time;           // Time of call
} CallLogEntry;

typedef struct CallLogNode {
    CallLogEntry data;             // Data of the node
    struct CallLogNode *next;      // Pointer to the next node
} CallLogNode;




/*Functions*/
void addToCallLog(const char *name, const char *time);//Adding to call log on dialing a number each instance
void freeCallLog();//Freeing the call log
int get_callLog_count();//Getting a total count of the number entries present in the call log
CallLogNode* get_head();//Gettter function to return the HEAD pointer of the Call log linked list
void set_head(CallLogNode* node);//Private settter function to set the HEAD pointer to the current node passed as an argument
lv_obj_t* get_Current_Button();//Gettter function to return the HEAD pointer of the Call log linked list
void set_Current_Button(lv_obj_t* obj);
void float_clear_cb(lv_event_t * e);
void set_call_log_tab(lv_obj_t* obj_tab);
lv_obj_t* get_call_log_tab();


#endif



