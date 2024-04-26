// contacts_view.h
#ifndef CONTACTS_VIEW_H
#define CONTACTS_VIEW_H

#include "lvgl/lvgl.h"
#include "contacts_model.h"

typedef struct 
{
    lv_obj_t *name_ta; //
    lv_obj_t *number_ta;//
    lv_obj_t *email_ta;//
}TextareaInfo;

typedef struct {
    lv_obj_t *tab1;
    const char *name;
}Tabs1;

void contacts(lv_obj_t* parent);
void add_contact_ui(lv_obj_t *parent);
void createContactLabels(lv_obj_t *parent);
void create_contact_profile(lv_obj_t *parent, char *name[]);
lv_obj_t* create_phone_keypad(lv_obj_t* parent); 
void popup_Box(lv_obj_t *parent, const char *name);
lv_obj_t *get_menu();
lv_obj_t *get_mainpage();
lv_obj_t *get_contacts_tab();


#endif // CONTACTS_VIEW_H