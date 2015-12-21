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

struct group_ships* create_list_groups(struct planets* all_planets) //Проверено, работает ++
//Функция инициализирует список групп. Нужно сделать один раз в начале игры + идёт сопоставление планет и кораблей на них
{
    struct group_ships* list_groups = new struct group_ships [NUM_PLANETS+1];
    for(int i=0;i<NUM_PLANETS;i++)
    {
        all_planets[i].defenders=&list_groups[i];
        list_groups[i].amount_ships = 0;
        for(int j=0; j<NUM_TYPES;j++)
            list_groups[i].ships_types[j]=0;
    }
    list_groups[NUM_PLANETS].amount_ships = -1;
    return list_groups;
}

void create_ship(struct planets* creator, int type_index, int walk_ab, int activePlayer) //Проверено, работает ++
//Создание корабля. Список планет, какой тип (int индекс этого типа)!, сколько может пройти, куда поставить.
{
    creator->defenders->player=activePlayer; // !!
    creator->defenders->current_position[0] = creator->x;
    creator->defenders->current_position[1] = creator->y;
    creator->defenders->next_position[0] = creator->defenders->current_position[0];
    creator->defenders->next_position[1] = creator->defenders->current_position[1];
    creator->defenders->ships_types[type_index] ++;
    creator->defenders->amount_ships++;
    if (walk_ab < creator->defenders->walking_ability || creator->defenders->walking_ability==0)
        creator->defenders->walking_ability=walk_ab;
}

int amount_groups_ships(struct group_ships* all_groups) //Работает, ++
//Сколько групп кораблей существует
{
    int len =0;
    while(all_groups[len].amount_ships!=-1)
        len++;
    len++; //Не забываем про завершающую строку
    return len;
}

struct group_ships* add_new_group(struct group_ships* all_groups) //Работает, ++
//Создаю новую группу кораблей. Вывожу лист групп. Нулевое место в листе групп будет занимать новая группа.
{
    int len = amount_groups_ships(all_groups); //Нужно проверить сколько групп есть.
    struct group_ships* new_all_groups = new struct group_ships [len+1];
    new_all_groups[0].amount_ships = 0;
    for(int j=0;j<NUM_TYPES;j++)
        new_all_groups[0].ships_types[j] = 0;
    for (int i=1; i<len+1;i++)
        new_all_groups[i]=all_groups[i-1];
    delete[] all_groups;
    return new_all_groups;
}

struct group_ships* delete_one_group(struct group_ships* all, int trash_index)
//Функция позволяет удалить из списка групп одну с заданным индексом.
{
    int len = amount_groups_ships(all);
    struct group_ships* new_groups = new struct group_ships [len-1];
    for (int i=0; i<trash_index; i++)
        new_groups[i]=all[i];
    for (int i=trash_index+1; i<len; i++)
        new_groups[i-1]=all[i];
    delete[] all;
    return new_groups;
}

struct group_ships* delete_empty_groups(struct group_ships* all_groups)
//Удаляю пустые группы кораблей. Вывожу лист групп.
{
    int len=amount_groups_ships(all_groups);
    int i = 0;
    while(i<len)
    {
        if(all_groups[i].amount_ships==0)
        {
            all_groups=delete_one_group(all_groups, i);
            i--;
            len--;
        }
        i++;
    }
    return all_groups;
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
    for(int i=0;i<NUM_TYPES;i++)
    {
        if(fromGroup->walking_ability == 0 || //Берём низкое движение у группы, из которой выходят
                (fromGroup->ships_types[i]!=0 && fromGroup->walking_ability>allTypes[i].walking_ability))
            fromGroup->walking_ability=allTypes[i].walking_ability;
        if(inGroup->walking_ability == 0 || //Движение берём самое низкое у группы, в которую заходят
                (inGroup->ships_types[i]!=0 && inGroup->walking_ability>allTypes[i].walking_ability))
            inGroup->walking_ability=allTypes[i].walking_ability;
    }
}

struct group_ships* add_ship_in_group (struct group_ships* allGroups, int fromGroup, int toGroup, int typeAmount[NUM_TYPES], struct ships_type* allTypes) //Вроде работает ++
//Добавить корабль в существующую группу.(все группы, индекс группы, из которой берём, индекс, в которую берём, массив количества кораблей, все типы кораблей)
{
    allGroups[fromGroup].player = allGroups[toGroup].player; //Игрок один и тот же
    for (int i=0; i<2; i++) //Проставляю координаты группе
    {
        allGroups[fromGroup].current_position[i] = allGroups[toGroup].current_position[i];
        allGroups[fromGroup].next_position[i] = allGroups[toGroup].next_position[i];
    }
    for (int i=0; i<NUM_TYPES; i++) //Перекидываю корабли в группу
    {
        if(typeAmount[i]<=allGroups[fromGroup].ships_types[i])
        {
            allGroups[toGroup].ships_types[i] += typeAmount[i];
            allGroups[fromGroup].ships_types[i] -= typeAmount[i];
            allGroups[toGroup].amount_ships += typeAmount[i];
            allGroups[fromGroup].amount_ships -= typeAmount[i];
        }
        else{
            allGroups[toGroup].ships_types[i] += allGroups[fromGroup].ships_types[i];
            allGroups[fromGroup].ships_types[i] = 0;
            allGroups[toGroup].amount_ships += allGroups[fromGroup].ships_types[i];
            allGroups[fromGroup].amount_ships -= allGroups[fromGroup].ships_types[i];
        }
    }
    for(int i=0;i<NUM_TYPES;i++)
    {
        if(allGroups[fromGroup].walking_ability == 0 || //Берём низкое движение у группы, из которой выходят
                (allGroups[fromGroup].ships_types[i]!=0 && allGroups[fromGroup].walking_ability>allTypes[i].walking_ability))
            allGroups[fromGroup].walking_ability=allTypes[i].walking_ability;
        if(allGroups[toGroup].walking_ability == 0 || //Движение берём самое низкое у группы, в которую заходят
                (allGroups[toGroup].ships_types[i]!=0 && allGroups[toGroup].walking_ability>allTypes[i].walking_ability))
            allGroups[toGroup].walking_ability=allTypes[i].walking_ability;
    }
    return allGroups;
}

struct group_ships* target(struct planets planets, struct group_ships* all_groups, int x, int y, struct ships_type* all_types)
{
    all_groups = add_new_group(all_groups);
    int* flighters = new int [NUM_TYPES];
    for(int i=0;i<NUM_TYPES;i++)
        flighters[i]=planets.defenders->ships_types[i]/2;
    add_ship_in_group(all_groups, planets.defenders, flighters, all_types);
    delete[] flighters;
    all_groups[0].next_position[0]=x;
    all_groups[0].next_position[0]=y;
    return all_groups;
}

void step_group(struct group_ships* one) //Вроде работает
//Беспрепятственный шаг полёта одной группы кораблей
{
    if(one->next_position[0] == one->current_position[0] &&
            one->next_position[1] == one->current_position[1]);
    int delta_x = (one->next_position[0]) - (one->current_position[0]);
    int delta_y = (one->next_position[1]) - (one->current_position[1]);
    double z = sqrt(delta_x*delta_x + delta_y*delta_y);
    if (z<=one->walking_ability)
        {
            one->current_position[0] = one->next_position[0];
            one->current_position[1] = one->next_position[1];
        }
    one->current_position[0] = one->current_position[0] + int(one->walking_ability*(delta_x/z));
    one->current_position[1] = one->current_position[1] + int(one->walking_ability*(delta_y/z));
}

struct group_ships* step_one_ships(struct group_ships* allGroups) //Вроде работает
//Беспрепятственный шаг полёта всех групп кораблей
{
    int len = amount_groups_ships(allGroups);
    for(int i=0; i<len; i++)
        step_group(&allGroups[i]);
    return allGroups;
}

int check_index (int* index_active, int* index_passive, int array_active[NUM_TYPES], int array_passive[NUM_TYPES])
//Ищем лучший тип кораблей, который есть у противников
{
    for(int i=0;i<NUM_TYPES;i++) //Всё хоккей
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

