#ifndef PLAYER_H_
#define PLAYER_H_

#include "item.h"
#include "creature.h"

#define INVENTORY_CAPACITY 5

struct player
{
    char *name;
    int health;
    int damage;
    int block;
    struct item inventory[INVENTORY_CAPACITY];
};

void print_player_info(struct player *inp_player);

void print_inventory(struct player *inp_player);

void pickup_item(struct player *inp_player, struct item *inp_item);

int fight(struct player *inp_player, struct creature *inp_creature);

#endif