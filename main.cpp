#include "header.h"


//Настоящие игроки начинаются с 1.
int main()
{
        /*Блок инициализации*/
    int activePlayer = 1;
    struct players* players = new struct players [MAX_PLAYERS + 1]; //Игроки, +1 для пустых планет
    struct planets* planets = new struct planets [NUM_PLANETS];     //Планеты
    begining(planets, players); //Лежит в data.cpp
    struct ships_type* all_types = create_list_types();             //Типы кораблей с характеристиками
    struct group_ships* all_groups = create_list_groups(planets); //Группы кораблей

    return_graphics(planets,players, all_groups, all_types, activePlayer);
}
