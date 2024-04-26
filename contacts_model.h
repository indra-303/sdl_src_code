#ifndef CONTACTS_MODEL_H
#define CONTACTS_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a contact
typedef struct {
    char *name;
    char *number;
    char *email;
} Contact;

// Structure for a linked list node
typedef struct ListNode {
    Contact data;
    struct ListNode *next;
} ListNode;

void addContact(const char *name, const char *number, const char *email);
void freeContactList(const char *names);

int get_contacts_count();

ListNode* get_contacts_head();
lv_obj_t* get_Current_Btn();//Gettter function to return the HEAD pointer of the Call log linked list
void set_Current_Btn(lv_obj_t* obj);
void set_contacts_head(ListNode* node);

#endif // CONTACTS_MODEL_H