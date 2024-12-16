#include "player.h"
#include <stdio.h>

void print_player_info(struct player *inp_player)
{
    printf("\n====================================");
    printf("\nplayer name      : %s", inp_player->name);
    printf("\nplayer health    : %d", inp_player->health);
    printf("\nplayer damage    : %d", inp_player->damage);
    printf("\nplayer block     : %d", inp_player->block);
    printf("\n====================================");
}

void print_inventory(struct player *inp_player)
{
    printf("\n====================================");
    printf("\ninventory : ");

    for (int i = 0; i < INVENTORY_CAPACITY; i++)
    {
        if (is_null_item(&inp_player->inventory[i]) == 0)
            printf("%s,", inp_player->inventory[i].name);
    }

    printf("\n====================================");
}

void pickup_item(struct player *inp_player, struct item *inp_item)
{
    if (inp_item->heal > 0)
    {
        inp_player->health += inp_item->heal;
        return;
    }

    if (inp_item->attack > 0 && inp_item->attack > inp_player->damage)
        inp_player->damage = inp_item->attack;

    if (inp_item->armor > 0 && inp_item->armor > inp_player->block)
        inp_player->block = inp_item->armor;

    for (int i = 0; i < INVENTORY_CAPACITY; i++)
    {
        if (is_null_item(&inp_player->inventory[i]) == 1)
        {
            inp_player->inventory[i] = *inp_item;
            return;
        }
    }
}

int fight(struct player *inp_player, struct creature *inp_creature)
{
    int player_health = inp_player->health;
    int player_damage = inp_player->damage;
    int creature_health = inp_creature->health;
    int creature_damage = inp_creature->damage - inp_player->block;

    while (1)
    {
        creature_health -= player_damage;

        if (creature_health <= 0)
        {
            inp_player->health = player_health;
            return 1;
        }

        player_health -= creature_damage;

        if (player_health <= 0)
        {
            inp_player->health = 0;
            return 0;
        }
    }
}