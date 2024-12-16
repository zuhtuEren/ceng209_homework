#include "room.h"
#include <stdio.h>

void print_room_info(struct room *inp_room)
{
    printf("\n====================================");
    printf("\nroom description : ");

    if (inp_room->is_unsafe == 0)
        printf("%s", inp_room->closed_description);
    else
        printf("%s", inp_room->opened_description);

    printf("\nroom item        : ");

    if (inp_room->room_item == NULL || inp_room->is_looted == 1)
        printf("none");
    else
        print_summary_item(inp_room->room_item);

    printf("\nroom creature    : ");

    if (inp_room->room_creature == NULL || inp_room->is_unsafe == 0)
        printf("none");
    else
        print_summary_creature(inp_room->room_creature);

    char u = inp_room->room_up != NULL ? 'U' : 'X';
    char r = inp_room->room_right != NULL ? 'R' : 'X';
    char d = inp_room->room_down != NULL ? 'D' : 'X';
    char l = inp_room->room_left != NULL ? 'L' : 'X';

    printf("\nroom navigates   : \n");
    printf("\n                  %c                ", u);
    printf("\n                  |                 ");
    printf("\n            %c -- you -- %c         ", l, r);
    printf("\n                  |                 ");
    printf("\n                  %c                \n", d);
    printf("\n====================================");
}

int is_available_direction(struct room *inp_room, char direction)
{
    if (direction == 'U' && inp_room->room_up != NULL)
        return 1;
    else if (direction == 'R' && inp_room->room_right != NULL)
        return 1;
    else if (direction == 'D' && inp_room->room_down != NULL)
        return 1;
    else if (direction == 'L' && inp_room->room_left != NULL)
        return 1;

    return 0;
}