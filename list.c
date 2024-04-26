/*Imports*/

#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
// #include "call_log_model.h"
// #include "contacts_model.h"

void* create_node(Node type)
{
    if (type == CALL_LOG_NODE)
    {
        CallLogNode *newNode = (CallLogNode *)malloc(sizeof(CallLogNode));

        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            // Handle memory allocation failure
            return;
        }
        else
            return newNode;
    }

    else if (type == CONTACT_LIST_NODE)
    {
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        if (newNode == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        else
            return newNode;
    }
}

void free_node(void* obj)
{
    free(obj);
}