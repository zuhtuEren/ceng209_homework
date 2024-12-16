#ifndef ITEM_H_
#define ITEM_H_

struct item
{
    int id;
    char *name;
    char *description;
    int heal;
    int attack;
    int armor;
};

void print_summary_item(struct item *inp_item);

int is_null_item(struct item *inp_item);

#endif