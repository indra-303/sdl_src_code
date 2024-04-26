#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "list_operations.h"
// #include "call_log_model.c"
// #include "contacts_model.c"

static int total_call_log = 0;
static int total_contacts = 0;

int get_call_log_count()
{
    return total_call_log;
}

int get_contact_count()
{
    return total_contacts;
}


void add_to_list(void *obj, Node type)
{

    if (type == CALL_LOG_NODE)
    {
        call_log_info *object = (call_log_info *)obj;
        CallLogNode *newNode = (CallLogNode *)create_node(CALL_LOG_NODE);
        newNode->data.name = strdup(object->contact);
        newNode->data.time = strdup(object->time);
        newNode->next = NULL;

        // no_of_contacts(newNode, name);
        CallLogNode *head = (CallLogNode *)create_node(CALL_LOG_NODE);
        head = get_head();

        CallLogNode *curr = (CallLogNode *)create_node(CALL_LOG_NODE);
        curr = head;

        if (head == NULL || strcmp(object->contact, head->data.name) < 0)
        {
            printf("List is empty\n");

            newNode->next = head;
            set_head(newNode);
            total_call_log++;
            // printf("Number of call logs :%d \n", total_call_log);
            return;
        }

        while (curr->next != NULL && (strcmp(object->contact, curr->next->data.name) > 0))
        {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
        total_call_log++;

        printf("Number of call logs :%d \n", total_call_log);
    }

    if (type == CONTACT_LIST_NODE)
    {
        contact_info* object = (contact_info*)obj;
        ListNode *newNode = (ListNode *)create_node(CONTACT_LIST_NODE);

        newNode->data.name = strdup(object->name);
        newNode->data.number = strdup(object->number);
        newNode->data.email = strdup(object->email);
        newNode->next = NULL; // Initialize next pointer as NULL

        ListNode *contactList = (ListNode*)create_node(CONTACT_LIST_NODE);
        contactList = get_contacts_head();
        // If the linked list is empty or the new node should be inserted at the beginning
        if (contactList == NULL || strcmp(object->name, contactList->data.name) < 0)
        {
            printf("inside if LL empty\r\n");

            newNode->next = contactList;
            set_contacts_head(newNode);
            total_contacts++;

            
 
            return;
        }

        // Find the appropriate position to insert the new node
        ListNode *current = (ListNode *)create_node(CONTACT_LIST_NODE);
        contactList = get_contacts_head();
        current = contactList;
        while (current->next != NULL && strcmp(object->name, current->next->data.name) > 0)
        {
            printf("inside while to find place\r\n");

            current = current->next;
        }

        // Insert the new node into the linked list
        newNode->next = current->next;
        current->next = newNode;
        total_contacts++;
        ListNode *iter = get_contacts_head();

            while(iter != NULL)
            {
                printf("NAME: %s\n", iter->data.name);

                iter = iter->next;
            }
    }
}