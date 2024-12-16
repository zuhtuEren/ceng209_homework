#include "item.h"
#include <string.h>
#include <stdio.h>

void print_summary_item(struct item *inp_item)
{
    printf("(name : %s / heal : %d / attack : %d / armor : %d)", inp_item->name, inp_item->heal, inp_item->attack, inp_item->armor);
}

int is_null_item(struct item *inp_item)
{
    if (inp_item->heal == -1 && inp_item->attack == -1 && inp_item->armor == -1)
        return 1;

    return 0;
}