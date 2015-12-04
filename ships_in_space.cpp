//#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int ACTIVE_PLAYER;
const int NUM_PLANETS=3, NUM_TYPES=2; //Количество типов кораблей

struct planets
{
    int x_place;
    int y_place;
    struct group_ships* defenders;
};

struct ships_type   //Тип корабля
{
    int attack;     // 0<атака_корабля<100
    int walking_ability;
    //sf::Sprite sprite; Для отрисовки кораблей
    //int hp; Если кто-то не может без этого, то можно добавить
};

struct group_ships //Группы кораблей
{
    int player;
    int amount_ships;
    int walking_ability;
    int current_position[2];
    int next_position[2];
    int ships_types[NUM_TYPES];
};

struct ships_type* create_list_types ()
//Здесь создаются типы кораблей. Нужно сделать один раз в начале игры.
{
    struct ships_type* list = new struct ships_type [NUM_TYPES];
    list[0].attack=10;
    list[0].walking_ability=200;
    list[1].attack=20;
    list[1].walking_ability=400;
    return list;
}

struct group_ships** create_list_groups(struct planets* all_planets)
//Функция инициализирует список групп. Нужно сделать один раз в начале игры + идёт сопоставление планет и кораблей на них
{
    struct group_ships** list_groups = new struct group_ships* [NUM_PLANETS+1];
    for(int i=0;i<NUM_PLANETS;i++)
    {
        list_groups[i] = new struct group_ships;
        all_planets[i].defenders=list_groups[i];
    }
    list_groups[NUM_PLANETS] == NULL;
    return list_groups;
}

struct planets create_ship(struct planets creator, int type_index, int walk_ab)
//Создание корабля. Список планет, какой тип (int индекс этого типа)!, сколько может пройти, куда поставить.
{
    creator.defenders->player=ACTIVE_PLAYER; // !!
    creator.defenders->current_position[0] = creator.x_place;
    creator.defenders->current_position[1] = creator.y_place;
    creator.defenders->next_position[0] = creator.defenders->current_position[0];
    creator.defenders->next_position[1] = creator.defenders->current_position[1];
    creator.defenders->ships_types[type_index] ++;
    creator.defenders->amount_ships ++;
    if (walk_ab < creator.defenders->walking_ability || creator.defenders->walking_ability==0)
        creator.defenders->walking_ability=walk_ab;
    return creator;
}

struct group_ships** add_new_group(struct group_ships** all_groups)
//Создаю новую группу кораблей. Вывожу лист групп. Нулевое место в листе групп будет занимать новая группа.
{
    int len=0; //Нужно проверить сколько элементов в группе. Сомнительно, но в create_list_groups всё проставил как надо :((
    while(all_groups[len]!=NULL)
        len++;
    //if(len==0)
    //    return all_groups;
    struct group_ships** new_all_groups = new struct group_ships* [len+1];
    new_all_groups[0]=new struct group_ships;
    for (int i=1; i<len+1;i++)
        new_all_groups[i]=all_groups[i-1];
    delete[] all_groups;
    return new_all_groups;
}

struct group_ships** delete_group(struct group_ships** all_groups, struct group_ships* trash)
//Удаляю группу кораблей. Вывожу лист групп.
{
    int len=0; //Нужно проверить сколько элементов в группе. Сомнительно, но в create_list_groups всё проставил как надо :((
    int index=0; //Номер удаляемой строки
    while(all_groups[len]!=NULL)
        len++;
    //if(len==0)
    //    return all_groups;
    struct group_ships** new_all_groups = new struct group_ships* [len-1];
    for (int i=1; i<len;i++)
        if(trash==all_groups[i])
            index = i; //Какая-то хрень с index. Говорит, что переменная не используется ((
    for (int i=1; i<index; i++)
        new_all_groups[i]=all_groups[i];
    for (int i=index+1; i<len; i++)
        new_all_groups[i-1]=all_groups[i];
    delete[] all_groups;
    return new_all_groups;
}

struct group_ships** add_ship_in_group (struct group_ships** all_groups, int position, struct group_ships* old_group, int type_and_amount[NUM_TYPES], struct ships_type* all_types)
//Функция добавляет корабли в существующую группу на позицию position из списка групп
{
    all_groups[position]->player = old_group->player;
    for(int i=0; i<2; i++)
    {
        all_groups[position]->current_position[i]= old_group->current_position[i];
        all_groups[position]->next_position[i] = old_group->next_position[i];
    }
    for(int i=0; i<NUM_TYPES;i++)
    {
        if(type_and_amount[i]<=old_group->ships_types[i])
        {
            all_groups[position]->ships_types[i]=type_and_amount[i];
            old_group->ships_types[i]=old_group->ships_types[i]-type_and_amount[i];
            old_group->amount_ships -= type_and_amount[i]; // !
            all_groups[position]->amount_ships += type_and_amount[i];
        }
        else
        {
            all_groups[position]->ships_types[i]=old_group->ships_types[i];
            old_group->ships_types[i]=0;
            old_group->amount_ships -= old_group->ships_types[i]; // !Работает или нет?
            all_groups[position]->amount_ships += old_group->ships_types[i];
        }
    }
    for(int i=0;i<NUM_TYPES;i++)
        if(all_groups[position]->ships_types[i]!=0)
        {
            all_groups[position]->walking_ability=all_types[i].walking_ability;
            break;
        }
    return all_groups;
}

struct group_ships step_one_ships(struct group_ships one)
//Беспрепятственный шаг полёта группы кораблей
{
    if(one.next_position == one.current_position)
        return one;
    int delta_x = (one.next_position[0]) - (one.current_position[0]);
    int delta_y = (one.next_position[1]) - (one.current_position[1]);
    int z = sqrt(delta_x*delta_x + delta_y*delta_y);
    if (z<=one.walking_ability)
        {
            one.current_position[0] = one.next_position[0];
            one.current_position[1] = one.next_position[1];
            return one;
        }
    one.current_position[0] = one.current_position[0] + one.walking_ability*(delta_y/z);
    one.current_position[1] = one.current_position[1] + one.walking_ability*(delta_y/z);
    return one;
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

struct group_ships** battle(struct group_ships** start_groups, struct group_ships* active, struct group_ships* passive, struct ships_type* all_types)
//Это сам бой между группами кораблей. Выбираем самых сильных и сталкиваем между собой, убиваем проигравший корабль :(
{
    int index_active = 0, index_passive = 0, delta_attack = 0;
    srand(time(NULL));
    check_index(&index_active, &index_passive, active->ships_types, passive->ships_types);
    while(active->amount_ships!=0 && passive->amount_ships != 0)
    {

       delta_attack = all_types[index_active].attack - all_types[index_passive].attack;
       int P_win_attack = int(100*(delta_attack/100 + 1)/2); //Вероятность (в %) победы атакующего
       int p = rand()%101; //А теперь бросаем кость.
       if (p<P_win_attack)
       {
           passive->ships_types[index_passive] --;
           active->amount_ships --;
       }
       if (p>=P_win_attack)
       {
           active->ships_types[index_active] --;
           active->amount_ships --;
       }
       if(active->ships_types[index_active]==0 || passive->ships_types[index_passive]==0)
            check_index(&index_active, &index_passive, active->ships_types, passive->ships_types);
    }
    //Расформировать
    if(active->amount_ships==0)
        start_groups = delete_group(start_groups,active);
    if(passive->amount_ships==0)
        start_groups = delete_group(start_groups,passive);
    return start_groups;
}

struct planets seize(struct group_ships* new_kings, struct planets change_planet)
//Захват планеты. Необходимо сменить defenders у этой планеты
{
    change_planet.defenders=new_kings;
    return change_planet;
}





int main() //Давайте проверять.
{
    struct planets* all_planets =new struct planets [NUM_PLANETS];
    struct ships_type* all_types = create_list_types();
    struct group_ships** all_groups = create_list_groups(all_planets);
    all_planets[2] = create_ship(all_planets[2], 1, 200);
    //...
    return 0;
}
