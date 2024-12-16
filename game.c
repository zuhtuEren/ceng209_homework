#include "game.h"
#include "room.h"
#include "player.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMBER_OF_ITEMS 10
#define NUMBER_OF_ROOMS 12
#define NUMBER_OF_CREATURES 5

struct room room1, room2, room3, room4, room5, room6, room7, room8, room9, room10, room11, room12;
struct room rooms[NUMBER_OF_ROOMS];

struct item item1, item2, item3, item4, item5, item6, item7, item8, item9, item10;
struct item items[NUMBER_OF_ITEMS];

struct creature creature1, creature2, creature3, creature4, creature5;
struct creature creatures[NUMBER_OF_CREATURES];

struct player crt_player;

struct room *crt_room = &room1;
struct room *prv_room = NULL;
struct room *tmp_room = NULL;

int escaped_room;

void play_game()
{
    escaped_room = 0;

    printf("\n====================================");
    printf("\nCommands");
    printf("\n====================================");
    printf("\n> move <direction (U, R, D, L)>");
    printf("\n> escape");
    printf("\n> look");
    printf("\n> inventory");
    printf("\n> pickup");
    printf("\n> attack");
    printf("\n> exit");
    printf("\n====================================\n");

    while (1)
    {
        print_player_info(&crt_player);
        printf("\n====================================");
        printf("\ncurrent room  : room%d", crt_room->id);
        printf("\nprevious room : ");

        if (prv_room == NULL)
            printf("none");
        else
            printf("room%d", prv_room->id);

        printf("\n====================================");

        char input[15];
        char destin[5];
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        strncpy(destin, input, 4);

        if (strcmp(destin, "move") == 0)
        {
            char direction = input[5];
            struct room *new_room;

            if (crt_room->is_unsafe == 0 && is_available_direction(crt_room, direction))
            {
                if (direction == 'U')
                    new_room = crt_room->room_up;
                else if (direction == 'R')
                    new_room = crt_room->room_right;
                else if (direction == 'D')
                    new_room = crt_room->room_down;
                else
                    new_room = crt_room->room_left;

                tmp_room = prv_room;
                prv_room = crt_room;
                crt_room = new_room;
                escaped_room = 0;

                printf("\n> moved the room in direction %c.\n", direction);
            }
            else
                printf("\n> can not move to direction %c.\n", direction);
        }
        else if (strcmp(input, "escape") == 0)
        {
            if (prv_room != NULL && escaped_room == 0)
            {
                crt_room = prv_room;
                prv_room = tmp_room;
                escaped_room = 1;
                printf("\n> escaped from the room.\n");
            }
            else
                printf("\n> could not escape from the room.\n");
        }
        else if (strcmp(input, "look") == 0)
            print_room_info(crt_room);
        else if (strcmp(input, "inventory") == 0)
            print_inventory(&crt_player);
        else if (strcmp(input, "pickup") == 0)
        {
            if (crt_room->is_unsafe == 0 && crt_room->is_looted == 0 && crt_room->room_item != NULL)
            {
                if (strcmp(crt_room->room_item->name, "treasure") == 0)
                {
                    printf("\n> treasure is collected. game is over.\n");
                    break;
                }

                pickup_item(&crt_player, crt_room->room_item);
                crt_room->is_looted = 1;
                printf("\n> %s is picked.\n", crt_room->room_item->name);
            }
            else
                printf("\n> there is no item to pickup.\n");
        }
        else if (strcmp(input, "attack") == 0)
        {
            if (crt_room->is_unsafe == 1 && crt_room->room_creature != NULL)
            {
                if (fight(&crt_player, crt_room->room_creature) == 1)
                {
                    printf("\n> %s is killed by player.\n", crt_room->room_creature->name);
                    crt_room->is_unsafe = 0;
                }
                else
                {
                    printf("\n> player is killed by %s. game is over.\n", crt_room->room_creature->name);
                    break;
                }
            }
            else
                printf("\n> there is no monster to attack.\n");
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("\n> exited from the game.\n");
            break;
        }
        else
            printf("\n> command not recognized.\n");
    }
}

void set_game(char *plyr_name, int plyr_health)
{
    set_creatures();
    set_items();
    set_rooms();

    crt_player.name = plyr_name;
    crt_player.health = plyr_health;

    for (int i = 0; i < INVENTORY_CAPACITY; i++)
    {
        crt_player.inventory[i].heal = -1;
        crt_player.inventory[i].attack = -1;
        crt_player.inventory[i].armor = -1;
    }
}

void set_rooms()
{
    room1.id = 1;
    room1.closed_description = "this place is the entry of dungeon. i need to go forward.";
    room1.opened_description = room1.closed_description;
    room1.is_unsafe = 0;
    room1.is_looted = 1;
    room1.room_item = NULL;
    room1.room_creature = NULL;
    room1.room_up = &room2;
    rooms[0] = room1;

    room2.id = 2;
    room2.closed_description = "it is a dark place. i think there is an old blade on the ground.";
    room2.opened_description = "it is a dark place. nothing else here.";
    room2.is_unsafe = 0;
    room2.is_looted = 0;
    room2.room_item = &item1;
    room2.room_creature = NULL;
    room2.room_right = &room8;
    room2.room_down = &room1;
    room2.room_left = &room3;
    rooms[1] = room2;

    room3.id = 3;
    room3.closed_description = "it is a very big room. there is a skeleton cavalry. it has a spear.";
    room3.opened_description = "it is a very big room. nothing else here.";
    room3.is_unsafe = 1;
    room3.is_looted = 0;
    room3.room_item = &item2;
    room3.room_creature = &creature1;
    room3.room_up = &room4;
    room3.room_right = &room2;
    rooms[2] = room3;

    room4.id = 4;
    room4.closed_description = "it is an old medic room. there is a bandage on the desk.";
    room4.opened_description = "it is an old medic room. nothing else here.";
    room4.is_unsafe = 0;
    room4.is_looted = 0;
    room4.room_item = &item3;
    room4.room_creature = NULL;
    room4.room_up = &room5;
    room4.room_down = &room3;
    rooms[3] = room4;

    room5.id = 5;
    room5.closed_description = "it is an empty room. nothing else here.";
    room5.opened_description = room5.opened_description;
    room5.is_unsafe = 0;
    room5.is_looted = 1;
    room5.room_item = NULL;
    room5.room_creature = NULL;
    room5.room_left = &room6;
    room5.room_down = &room4;
    rooms[4] = room5;

    room6.id = 6;
    room6.closed_description = "there is a tomb of a king inside. a zombie knight protecting it. it is wearing a golden armor.";
    room6.opened_description = "there is a tomb of a king inside. nothing else here.";
    room6.is_unsafe = 1;
    room6.is_looted = 0;
    room6.room_item = &item4;
    room6.room_creature = &creature2;
    room6.room_right = &room5;
    room6.room_down = &room7;
    rooms[5] = room6;

    room7.id = 7;
    room7.closed_description = "there is a magician inside. he says he can give you a free health elixir.";
    room7.opened_description = "there is a magician inside. nothing else here.";
    room7.is_unsafe = 0;
    room7.is_looted = 0;
    room7.room_item = &item5;
    room7.room_creature = NULL;
    room7.room_up = &room6;
    rooms[6] = room7;

    room8.id = 8;
    room8.closed_description = "there is a mutant gorilla inside. it has a very powerful stell hammer.";
    room8.opened_description = "it is an long hall. nothing else here.";
    room8.is_unsafe = 1;
    room8.is_looted = 0;
    room8.room_item = &item6;
    room8.room_creature = &creature3;
    room8.room_left = &room2;
    room8.room_up = &room9;
    rooms[7] = room8;

    room9.id = 9;
    room9.closed_description = "it is an empty dark room. there is a book on the ground. there is a heal magic in it.";
    room9.opened_description = "it is an empty dark room. nothing else here.";
    room9.is_unsafe = 0;
    room9.is_looted = 0;
    room9.room_item = &item7;
    room9.room_creature = NULL;
    room9.room_right = &room10;
    room9.room_down = &room8;
    rooms[8] = room9;

    room10.id = 10;
    room10.closed_description = "there is a samurai inside. he is wearing a samurai armor that very durable and protected against spells.";
    room10.opened_description = "it is an old room of samurai. nothing else here.";
    room10.is_unsafe = 1;
    room10.is_looted = 0;
    room10.room_item = &item8;
    room10.room_creature = &creature4;
    room10.room_left = &room9;
    room10.room_up = &room11;
    rooms[9] = room10;

    room11.id = 11;
    room11.closed_description = "there is a medallion of a old god. it will increase the health of who ever wears it.";
    room11.opened_description = "it is an old temple. nothing else here.";
    room11.is_unsafe = 0;
    room11.is_looted = 0;
    room11.room_item = &item9;
    room11.room_creature = NULL;
    room11.room_down = &room10;
    room11.room_left = &room12;
    rooms[10] = room11;

    room12.id = 12;
    room12.closed_description = "there is an ancient snake. it is protecting a treasure.";
    room12.opened_description = "it is an old cave. nothing else here.";
    room12.is_unsafe = 1;
    room12.is_looted = 0;
    room12.room_item = &item10;
    room12.room_creature = &creature5;
    room12.room_right = &room11;
    rooms[11] = room12;
}

void set_items()
{
    item1.id = 1;
    item1.name = "old_blade";
    item1.description = "an old blade. not very good but it will work.";
    item1.heal = 0;
    item1.attack = 1;
    item1.armor = 0;
    items[0] = item1;

    item2.id = 2;
    item2.name = "spear";
    item2.description = "a spear. it is in good state.";
    item2.heal = 0;
    item2.attack = 2;
    item2.armor = 0;
    items[1] = item2;

    item3.id = 3;
    item3.name = "bandage";
    item3.description = "a bandage. it can be used for wrapping the wounds.";
    item3.heal = 2;
    item3.attack = 0;
    item3.armor = 0;
    items[2] = item3;

    item4.id = 4;
    item4.name = "golden_armor";
    item4.description = "a golden armor. very glittering and durable.";
    item4.heal = 0;
    item4.attack = 0;
    item4.armor = 2;
    items[3] = item4;

    item5.id = 5;
    item5.name = "health_elixir";
    item5.description = "a health elixir. it can be used for healing the body.";
    item5.heal = 6;
    item5.attack = 0;
    item5.armor = 0;
    items[4] = item5;

    item6.id = 6;
    item6.name = "steel_hammer";
    item6.description = "a steel hammer. it is very heavy and covered in blood.";
    item6.heal = 0;
    item6.attack = 4;
    item6.armor = 0;
    items[5] = item6;

    item7.id = 7;
    item7.name = "magic_book";
    item7.description = "a magic book. there is a heal magic in it.";
    item7.heal = 8;
    item7.attack = 0;
    item7.armor = 0;
    items[6] = item7;

    item8.id = 8;
    item8.name = "samurai_armor";
    item8.description = "a samurai armor. very durable and protected against spells.";
    item8.heal = 0;
    item8.attack = 0;
    item8.armor = 6;
    items[7] = item8;

    item9.id = 9;
    item9.name = "medallion_of_god";
    item9.description = "a medallion of god. it has a magic that increase health of whoever use it.";
    item9.heal = 12;
    item9.attack = 0;
    item9.armor = 0;
    items[8] = item9;

    item10.id = 10;
    item10.name = "treasure";
    item10.description = "a lost treasure. there are golds, diamonds and emeralds in it.";
    item10.heal = 0;
    item10.attack = 0;
    item10.armor = 0;
    items[9] = item10;
}

void set_creatures()
{
    creature1.id = 1;
    creature1.name = "skeleton cavalry";
    creature1.health = 3;
    creature1.damage = 2;
    creatures[0] = creature1;

    creature2.id = 2;
    creature2.name = "zombie knight";
    creature2.health = 6;
    creature2.damage = 2;
    creatures[1] = creature2;

    creature3.id = 3;
    creature3.name = "mutant_gorilla";
    creature3.health = 8;
    creature3.damage = 4;
    creatures[2] = creature3;

    creature4.id = 4;
    creature4.name = "samurai";
    creature4.health = 16;
    creature4.damage = 4;
    creatures[3] = creature4;

    creature5.id = 5;
    creature5.name = "ancient_snake";
    creature5.health = 20;
    creature5.damage = 7;
    creatures[4] = creature5;
}
