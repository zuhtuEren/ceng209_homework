#ifndef ROOM_H_
#define ROOM_H_

#include "item.h"
#include "creature.h"

struct room
{
    int id;
    char *opened_description;
    char *closed_description;
    int is_unsafe;
    int is_looted;
    struct item *room_item;
    struct creature *room_creature;
    struct room *room_up;
    struct room *room_right;
    struct room *room_down;
    struct room *room_left;
};

void print_room_info(struct room *inp_room);

int is_available_direction(struct room *inp_room, char direction);

#endif
