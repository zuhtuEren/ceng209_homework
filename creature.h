#ifndef CREATURE_H_
#define CREATURE_H_

struct creature
{   
    int id;
    char *name;
    int health;
    int damage;
};

void print_summary_creature(struct creature *inp_creature);

#endif