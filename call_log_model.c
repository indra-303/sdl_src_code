/*Imports*/

#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


/*Local Variables (Static)*/
static int count_calllog = 0;
static CallLogNode* callLogHead;
static lv_obj_t* currentButton = NULL;
static lv_obj_t* call_log_tab;

/*Functions*/
void set_call_log_tab(lv_obj_t* obj_tab)//Setter function for CALL LOG tab pointer ref
{
    call_log_tab = &(*obj_tab);   
}

lv_obj_t* get_call_log_tab()
{
    return call_log_tab;
}
void addToCallLog(const char *name, const char *time)
{

    CallLogNode *newNode = (CallLogNode*)create_node(CALL_LOG_NODE);
    newNode->data.name = strdup(name);
    newNode->data.time = strdup(time);
    newNode->next = NULL;

    // no_of_contacts(newNode, name);
    CallLogNode* head = (CallLogNode*)create_node(CALL_LOG_NODE);
    head = get_head();

    CallLogNode *curr = (CallLogNode*)create_node(CALL_LOG_NODE);
    curr = head;

    if (head == NULL || strcmp(name, head->data.name) < 0)
    {
        printf("List is empty\n");

        newNode->next = head;
        set_head(newNode);
        count_calllog++;
        // printf("Number of call logs :%d \n", count_calllog);
        return;
    }

    while (curr->next != NULL && (strcmp(name, curr->next->data.name) > 0))
    {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    count_calllog++;

    printf("Number of call logs :%d \n", count_calllog);
    // free(newNode);
    // free(head);
    // free(curr);

}

void freeCallLog()
{
    CallLogNode *current = (CallLogNode*)create_node(CALL_LOG_NODE);
    current = callLogHead;
    CallLogNode *next=(CallLogNode*)create_node(CALL_LOG_NODE);
    while (current != NULL)
    {
        next = current->next;
        free(current->data.name);
        // free(current->data.number);
        free(current->data.time);
        free(current);
        current = next;
    }
    callLogHead = NULL;// Reset the callLogHead pointer
    
    // free(current);
    // free(next); 
}

void no_of_call_logs(CallLogNode *newNode, const char *name)
{
    CallLogNode *curr = (CallLogNode*)create_node(CALL_LOG_NODE);
    curr = callLogHead;

    if (callLogHead == NULL || strcmp(name, callLogHead->data.name) < 0)
    {
        printf("List is empty\n");

        newNode->next = callLogHead;
        callLogHead = newNode;
        count_calllog++;
        return;
    }

    while (curr->next != NULL && (strcmp(name, curr->next->data.name) > 0))
    {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    count_calllog++;
    // free(curr);

    return;
}


CallLogNode* get_head()
{
    return callLogHead;
}

void set_head(CallLogNode* node)
{
    callLogHead = node;
}

int get_callLog_count()
{
    return count_calllog;
}

lv_obj_t* get_Current_Button()
{
        if(currentButton)
        {
            printf("inside get current button\n");
        }
    return currentButton;
}

void set_Current_Button(lv_obj_t* obj)
{
    currentButton = &(*obj);
}


void float_clear_cb(lv_event_t * e)
{
    const lv_event_code_t code = lv_event_get_code(e);
    if((code == LV_EVENT_CLICKED) ) {

        freeCallLog();

        lv_obj_t* call_log_tab = get_call_log_tab();
        call_log(call_log_tab);

    }
}





