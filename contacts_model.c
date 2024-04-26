#include "lvgl/lvgl.h"
// #include "contacts_model.h"
#include "list.h"

static int count_contacts = 0;
static lv_obj_t *currentBtn = NULL;

static ListNode *contactList;

void set_contacts_head(ListNode *node)
{
    contactList = node;
}

void addContact(const char *name, const char *number, const char *email)
{

    ListNode *newNode = (ListNode *)create_node(CONTACT_LIST_NODE);

    newNode->data.name = strdup(name);
    newNode->data.number = strdup(number);
    newNode->data.email = strdup(email);
    newNode->next = NULL; // Initialize next pointer as NULL

    // If the linked list is empty or the new node should be inserted at the beginning
    if (contactList == NULL || strcmp(name, contactList->data.name) < 0)
    {
        printf("inside if LL empty\r\n");

        newNode->next = contactList;
        contactList = newNode;
        count_contacts++;
        return;
    }

    // Find the appropriate position to insert the new node
    ListNode *current = (ListNode *)create_node(CONTACT_LIST_NODE);
    current = contactList;
    while (current->next != NULL && strcmp(name, current->next->data.name) > 0)
    {
        printf("inside while to find place\r\n");

        current = current->next;
    }

    // Insert the new node into the linked list
    newNode->next = current->next;
    current->next = newNode;
    count_contacts++;
    ListNode *iter = get_contacts_head();
    while (iter != NULL)
    {
        printf("NAME: %s\n", iter->data.name);

        iter = iter->next;
    }
}

// Function to free the memory used by the linked list
void freeContactList(const char *name)
{
    ListNode *current = (ListNode *)create_node(CONTACT_LIST_NODE);
    current = contactList;
    ListNode *prev = (ListNode *)create_node(CONTACT_LIST_NODE);
    prev = NULL;
    ListNode *next = (ListNode *)create_node(CONTACT_LIST_NODE);

    if (name != NULL)
    {
        while (current != NULL)
        {

            if (strcmp(current->data.name, name) == 0)
            {
                if (prev == NULL)
                {
                    contactList = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                next = current->next;
                free(current->data.name);
                free(current->data.number);
                free(current->data.email);
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    free(current);
    free(prev);
    free(next);
}

void no_of_contacts(ListNode *newNode, const char *name)
{
    ListNode *current = (ListNode *)create_node(CONTACT_LIST_NODE);
    current = contactList;

    if (contactList == NULL || strcmp(name, contactList->data.name) < 0)
    {
        printf("List is empty\n");

        newNode->next = contactList;
        contactList = newNode;
        count_contacts++;
        return;
    }

    while (current->next != NULL && (strcmp(name, current->next->data.name) > 0))
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    count_contacts++;
    return;
}

ListNode *get_contacts_head()
{
    // CallLogNode* callLogHead= get_head();
    return contactList;
}

int get_contacts_count()
{
    return count_contacts;
}

lv_obj_t *get_Current_Btn()
{
    return currentBtn;
}

void set_Current_Btn(lv_obj_t *obj)
{
    currentBtn = &(*obj);
}
