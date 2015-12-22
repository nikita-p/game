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

    /*-------------------------------------------------------------------------------------------------*/

/*int main()
{
    int activePlayer = 1;
    struct planets* list_planets = new struct planets[NUM_PLANETS];
    for(int i=0;i<NUM_PLANETS;i++)
    {
        list_planets[i].index=i;
        list_planets[i].x_place=X_MAX*(i+1)/(NUM_PLANETS+1);
        list_planets[i].y_place=Y_MAX*(i+1)/(NUM_PLANETS+1);
    }
    struct ships_type* all_types = create_list_types();
    struct group_ships* all_groups = create_list_groups(list_planets);
    for(int i = 0; i<72; i++)
    {
        list_planets[i%3]=create_ship(list_planets[i%3],i%2,200, activePlayer);
    }
    all_groups = add_new_group(all_groups); //Добавил пустую группу
    all_groups = delete_empty_groups(all_groups); //Удалил пустые группы
    int a[2] = {3, 0}; //Типичный массив кораблей
    all_groups = add_ship_in_group(all_groups, 0, 2, a, all_types); //Добавил корабли a из группы 0 в группу 2
    all_groups[1].next_position[0] = 1; //Задаю цель некоторой группе.
    all_groups[1].next_position[1] = 1;
    all_groups = step_one_ships(all_groups); //Поменял текущую позицию.
    int len = amount_groups_ships(all_groups);
    all_groups = battle(all_groups,1,2,all_types); //Битва
    return 0;
}
*/
