#include "lvgl/lvgl.h"
#include "contacts_model.h"

ListNode *contactList = NULL;
int count = 0;


void addContact(const char *name, const char *number, const char *email) {

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    newNode->data.name = strdup(name);
    newNode->data.number = strdup(number);
    newNode->data.email = strdup(email);
    newNode->next = NULL; // Initialize next pointer as NULL

  // If the linked list is empty or the new node should be inserted at the beginning
    if (contactList == NULL || strcmp(name, contactList->data.name) < 0) {
            printf("inside if LL empty\r\n");

        newNode->next = contactList;
        contactList = newNode;
         count++; 
        return;
    }

    // Find the appropriate position to insert the new node
    ListNode *current = contactList;
    while (current->next != NULL && strcmp(name, current->next->data.name) > 0) {
            printf("inside while to find place\r\n");

        current = current->next;
    }

    // Insert the new node into the linked list
    newNode->next = current->next;
    current->next = newNode;
    count++;

}

// Function to free the memory used by the linked list
void freeContactList() {
    ListNode *current = contactList;
    ListNode *next;
    while (current != NULL) {
        next = current->next;
        free(current->data.name);
        free(current->data.number);
        free(current->data.email);
        free(current);
        current = next;
    }
    contactList = NULL;
}
