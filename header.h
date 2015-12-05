#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "economy.cpp"

const int X_MAX=800, Y_MAX=640, NUM_PLANETS = 3, NUM_TYPES=2; //Количество типов кораблей(NUM_TYPES) Размеры экрана(X_MAX,Y_MAX)
//int ACTIVE_PLAYER=1;//Ходящий игрок

struct players
{
    int gold;//Счёт игрока
};
struct planets
{
    int index;
    int buildings[3];//Массив строений: 0 - экономическое, 1 - защитное, 2 - казарма. Значение - уровень
    //int def;//Показатель защиты
    int add_ships;//Число доступных для постройки кораблей
    int res;  //Доходность
    int x_place; //Координаты
    int y_place;    
    struct group_ships* defenders; //Корабли на этой планете
};

struct ships_type   //Тип корабля
{
    int attack;     // 0<атака_корабля<100
    int walking_ability;
    //sf::Sprite sprite; //Для отрисовки кораблей
};

struct group_ships //Группы кораблей
{
    int player;
    int amount_ships;
    int walking_ability;
    int current_position[2];
    int next_position[2];
    int ships_types[NUM_TYPES];
    sf::CircleShape picture;
};

struct ships_type* create_list_types ();
//Здесь создаются типы кораблей. Нужно сделать один раз в начале игры.

group_ships *create_list_groups(struct planets* all_planets);
//Функция инициализирует список групп. Нужно сделать один раз в начале игры + идёт сопоставление планет и кораблей на них

planets create_ship(planets creator, int type_index, int walk_ab);
//Создание корабля. Список планет, какой тип (int индекс этого типа)!, сколько может пройти, куда поставить.

int amount_groups_ships(struct group_ships** all_groups);
//Сколько групп кораблей существует

group_ships **add_new_group(group_ships **all_groups);
//Создание новой группы кораблей. Вывожу лист групп. Нулевое место в листе групп будет занимать новая группа.

group_ships **delete_group(group_ships **all_groups, struct group_ships* trash);
//Удаляю группу кораблей. Вывожу лист групп.

struct group_ships* add_ship_in_group (struct group_ships* all_groups, int position, struct group_ships* old_group, int type_and_amount[NUM_TYPES], struct ships_type* all_types);
//Функция добавляет корабли в существующую группу на позицию position из списка групп

struct group_ships* step_one_ships(struct group_ships* one);
//Беспрепятственный шаг полёта группы кораблей

int check_index (int* index_active, int* index_passive, int array_active[NUM_TYPES], int array_passive[NUM_TYPES]);
//Ищем лучший тип кораблей, который есть у противников

struct group_ships* battle(struct group_ships* start_groups, struct group_ships* active, struct group_ships* passive, struct ships_type* all_types);
//Это сам бой между группами кораблей. Выбираем самых сильных и сталкиваем между собой, убиваем проигравший корабль :(

struct planets* seize(struct group_ships* new_kings, struct planets* change_planet);
//Захват планеты. Необходимо сменить defenders у этой планеты


#endif // HEADER_H
