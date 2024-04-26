//For importing and defining once per call
#ifndef LIST_H
#define LIST_H

/*Includes*/
#include "lvgl/lvgl.h"
#include <stdlib.h>
#include "call_log_model.h"
#include "contacts_model.h"


typedef struct
{
    char* contact;
    char* time;


}call_log_info;

typedef struct
{
    char* name;
    char* number;
    char* email;
}contact_info;

typedef enum
{
    CALL_LOG_NODE,
    CONTACT_LIST_NODE
}Node;

void* create_node(Node type);

void free_node(void* obj);


#endif