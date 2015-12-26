#include "header.h"
#include "math.h"
double const SLUP_E = 600, //Start level-up price of economy (1 lvl->2 lvl)
            SLUP_D = 900, //--defense
            SLUP_A = 1200, //--add-ship building
            PRP_E = 1.6,
            PRP_D = 1.5,
            PRP_A = 1.4,
            SD = 5,
            SA = 300,
            SR = 500,
            PR_D = 1.3,
            PR_A = 1.05,
            PR_E = 1.5,
            PS = 80;//Price of ship

int level_up(struct planets * list, struct players * list_p, int planet, int building, int ACTIVE_PLAYER)
{
    int cost;
    switch (building)
    {
    case 0:
        cost = (int)SLUP_E*pow(PRP_E, list[planet].buildings[building]-1);

        break;
    case 2:
        cost = (int)SLUP_D*pow(PRP_D, list[planet].buildings[building]-1);

        break;
    case 1:
        cost = (int)SLUP_A*pow(PRP_A, list[planet].buildings[building]-1);

        break;
    }

    if (list_p[ACTIVE_PLAYER].gold >= cost){
        list[planet].buildings[building]++;
        list_p[ACTIVE_PLAYER].gold = list_p[ACTIVE_PLAYER].gold - cost;
        switch (building)
        {
        case 0:
            list[Active_Planet(list)].cost_buildings[building] = (int)SLUP_E*pow(PRP_E, list[planet].buildings[building]-1);
            break;
        case 2:
            list[Active_Planet(list)].cost_buildings[building] = (int)SLUP_D*pow(PRP_D, list[planet].buildings[building]-1);
            break;
        case 1:
            list[Active_Planet(list)].cost_buildings[building] = (int)SLUP_A*pow(PRP_A, list[planet].buildings[building]-1);
            break;
        }
        return cost;
    }
    return cost;
}

void recount(struct planets * list)
{
    for (int i = 0; i < NUM_PLANETS; i++){
        list[i].def = (int)SD*pow(PR_D, list[i].buildings[2]);//сделать в битве: OK
        list[i].add_ships = (int)(SA/pow(PR_A, list[i].buildings[1]));// !!
        list[i].res = (int)SR*pow(PR_E, list[i].buildings[0]);
    }
}

void add_money(struct planets * planets, struct players* players, int activePlayer)
{
    for (int i = 0; i < NUM_PLANETS; i++)
        if (planets[i].belong == activePlayer)
            players[activePlayer].gold+=planets[i].res;
}

int build_ship(struct planets * list, struct players * list_p, int planet, int count, int ACTIVE_PLAYER, int type)//!!!
{
    if ((list_p[ACTIVE_PLAYER].gold >= PS * count) && (list[planet].add_ships >= count))
    {
        list_p[ACTIVE_PLAYER].gold = list_p[ACTIVE_PLAYER].gold - count * PS;
        list[planet].add_ships = list[planet].add_ships - count;
        list[planet].defenders->amount_ships += count;
        list[planet].defenders->ships_types[type]+=count;
        return 1;
    }
    return 0;
}
