#include "creature.h"
#include <stdio.h>

void print_summary_creature(struct creature *inp_creature)
{
    printf("(name : %s / health : %d / damage : %d)", inp_creature->name, inp_creature->health, inp_creature->damage);
}