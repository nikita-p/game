#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "header.h"

struct ships_type* create_list_types ()
//Здесь создаются типы кораблей. Нужно сделать один раз в начале игры.
{
    struct ships_type* list = new struct ships_type [NUM_TYPES];
    for(int i=0;i<NUM_TYPES;i++)
    {
        list[i].attack=10*(i+1);
        list[i].walking_ability=200*(i+1);
    }
    return list;
}

struct group_ships* create_list_groups(struct planets* all_planets)
//Функция инициализирует список групп. Нужно сделать один раз в начале игры + идёт сопоставление планет и кораблей на них
{
    struct group_ships* head = new struct group_ships;
    head->next = NULL;
    for(int i=0;i<NUM_PLANETS;i++)
    {
        struct group_ships* plusShip = new struct group_ships;
        plusShip->next = head;
        all_planets[i].defenders= plusShip;
        plusShip->current_position[0]=all_planets[i].x;
        plusShip->current_position[1]=all_planets[i].y;
        plusShip->next_position[0]=all_planets[i].x;
        plusShip->next_position[1]=all_planets[i].y;
        plusShip->player=all_planets[i].belong;
        for(int j=0; j<NUM_TYPES;j++)
        {
            plusShip->ships_types[j]=15*(j+1);
            plusShip->amount_ships += plusShip->ships_types[j];
        }
        head = plusShip;
    }
    return head;
}

int walking(struct group_ships* one_group, struct ships_type* all_types)
{
    for (int i=0; i<NUM_TYPES;i++)
        if(one_group->ships_types[i] != 0)
            return all_types[i].walking_ability;
    return 0;
}

void create_ship(struct planets creator, int type_index, int activePlayer)
//Создание корабля. Список планет, какой тип (int индекс этого типа)!, сколько может пройти, куда поставить.
{
    if(creator.belong != activePlayer)
        return;
    creator.defenders->ships_types[type_index] ++;
    creator.defenders->amount_ships++;
}

int amount_groups_ships(struct group_ships* l)
//Сколько групп кораблей существует
{
    int len =0;
    for(;l->next!=NULL;l=l->next)
        len++;
    return len;
}

struct group_ships* add_new_group(struct group_ships* all_groups)
//Создаю новую группу кораблей. Вывожу лист групп. Нулевое место в листе групп будет занимать новая группа.
{
    struct group_ships* pasteGroup = new struct group_ships;
    pasteGroup->amount_ships = 0;
    for(int j=0;j<NUM_TYPES;j++)
        pasteGroup->ships_types[j] = 0;
    pasteGroup->next = all_groups;
    return pasteGroup;
}

struct group_ships* delete_one_group(struct group_ships* all, int trash_index)
//Функция позволяет удалить из списка групп одну с заданным индексом.
{
    struct group_ships* head = all;
    struct group_ships* prev = new struct group_ships;
    if(trash_index==0)
        head=head->next;
    for(int i=0; i<trash_index && all->next!=NULL; i++)
    {
        prev = all;
        all=all->next;
    }
    prev->next = all->next;
    delete all;
    return head;
}

struct group_ships* delete_empty_groups(struct group_ships* l) //Не очень
//Удаляю пустые группы кораблей. Вывожу лист групп.
{
    struct group_ships* head = l;
    for(int i=0; l->next!=NULL; i++)
        if(l->amount_ships==0)
        {
            head = delete_one_group(head, i);
            l = head;
            i=0;
        }
    return l;
}

void add_ship_in_group(struct group_ships* fromGroup, struct group_ships* inGroup, int typeAmount[], struct ships_type* allTypes)
{
    inGroup->player=fromGroup->player;
    for (int i=0; i<2; i++) //Проставляю координаты группе
    {
        inGroup->current_position[i] = fromGroup->current_position[i];
        inGroup->next_position[i] = fromGroup->next_position[i];
    }
    for (int i=0; i<NUM_TYPES; i++) //Перекидываю корабли в группу
    {
        if(typeAmount[i]<=fromGroup->ships_types[i])
        {
            inGroup->ships_types[i] += typeAmount[i];
            fromGroup->ships_types[i] -= typeAmount[i];
            inGroup->amount_ships += typeAmount[i];
            fromGroup->amount_ships -= typeAmount[i];
        }
        else{
            inGroup->ships_types[i] += fromGroup->ships_types[i];
            fromGroup->ships_types[i] = 0;
            inGroup->amount_ships += fromGroup->ships_types[i];
            fromGroup->amount_ships -= fromGroup->ships_types[i];
        }
    }
}

struct group_ships* target(struct planets planets, struct group_ships* all_groups, int x, int y, struct ships_type* all_types)
{
    all_groups = add_new_group(all_groups);
    int* flighters = new int [NUM_TYPES];
    for(int i=0;i<NUM_TYPES;i++)
        flighters[i]=planets.defenders->ships_types[i]/2;
    add_ship_in_group(planets.defenders, all_groups, flighters, all_types);
    delete[] flighters;
    all_groups[0].next_position[0]=x;
    all_groups[0].next_position[1]=y;
    return all_groups;
}

void step_group(struct group_ships* one, struct ships_type* all_types) //Вроде работает
//Беспрепятственный шаг полёта одной группы кораблей
{
    if(one->next_position[0] == one->current_position[0] &&
            one->next_position[1] == one->current_position[1]);
    int delta_x = (one->next_position[0]) - (one->current_position[0]);
    int delta_y = (one->next_position[1]) - (one->current_position[1]);
    double z = sqrt(delta_x*delta_x + delta_y*delta_y);
    if (z<=walking(one, all_types))
        {
            one->current_position[0] = one->next_position[0];
            one->current_position[1] = one->next_position[1];
        }
    one->current_position[0] = one->current_position[0] + int(walking(one, all_types)*(delta_x/z));
    one->current_position[1] = one->current_position[1] + int(walking(one, all_types)*(delta_y/z));
}

struct group_ships* step_one_ships(struct group_ships* allGroups, struct ships_type* all_types) //Вроде работает
//Беспрепятственный шаг полёта всех групп кораблей
{
    int len = amount_groups_ships(allGroups);
    for(int i=0; i<len; i++)
        step_group(&allGroups[i], all_types);
    return allGroups;
}

int check_index (int* index_active, int* index_passive, int array_active[NUM_TYPES], int array_passive[NUM_TYPES])
//Ищем лучший тип кораблей, который есть у противников
{
    for(int i=0;i<NUM_TYPES;i++)
    {
        if(array_active[i] != 0)
            *index_active = i;
        if(array_passive[i] != 0)
            *index_passive = i;
    }
    return 0;
}


struct group_ships* battle(struct group_ships* start_groups, int i_active, int  i_passive, struct ships_type* all_types)
//Это сам бой между группами кораблей. Выбираем самых сильных и сталкиваем между собой, убиваем проигравший корабль :(
{
    int index_active = 0, index_passive = 0, delta_attack = 0;
    srand(time(NULL));
    check_index(&index_active, &index_passive, start_groups[i_active].ships_types, start_groups[i_passive].ships_types);
    while(start_groups[i_active].amount_ships!=0 && start_groups[i_passive].amount_ships != 0)
    {

       delta_attack = all_types[index_active].attack - all_types[index_passive].attack;
       int P_win_attack = int(100*(delta_attack/100 + 1)/2); //Вероятность (в %) победы атакующего
       int p = rand()%101; //А теперь бросаем кость.
       if (p<P_win_attack)
       {
           start_groups[i_active].ships_types[index_passive] --;
           start_groups[i_active].amount_ships --;
       }
       if (p>=P_win_attack)
       {
           start_groups[i_passive].ships_types[index_active] --;
           start_groups[i_passive].amount_ships --;
       }
       if(start_groups[i_active].ships_types[index_active]==0 || start_groups[i_passive].ships_types[index_passive]==0)
            check_index(&index_active, &index_passive, start_groups[i_active].ships_types, start_groups[i_passive].ships_types);
    }
    //Расформировать
    if(start_groups[i_active].amount_ships==0)
        start_groups = delete_one_group(start_groups,i_active);
    if(start_groups[i_passive].amount_ships==0)
        start_groups = delete_one_group(start_groups,i_passive);
    return start_groups;
}


struct planets* seize(struct group_ships* new_kings, struct planets* change_planet)
//Захват планеты. Необходимо сменить defenders у этой планеты
{
    change_planet->defenders=new_kings;
    return change_planet;
}

