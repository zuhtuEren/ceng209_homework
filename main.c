#include "game.h"
#include "room.h"
#include "player.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("\n====================================");
    printf("\nCommands");
    printf("\n====================================");
    printf("\n> play");
    printf("\n> exit");
    printf("\n====================================\n");

    while (1)
    {
        char input[50];
        char destin[5];
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        strncpy(destin, input, 4);

        if (strcmp(input, "play") == 0)
        {
            char name[10];
            printf("\n> name : ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            set_game(name, 10);
            play_game();
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("\n> exited from the game.\n");
            break;
        }
        else
            printf("\n> command not recognized.\n");
    }

    return 0;
}