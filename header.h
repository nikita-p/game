#ifndef HEADER_H
#define HEADER_H

//#include <SFML/Graphics.hpp>
#include <iostream>
#include "economy.cpp"
#include "field.cpp"

const int X_MAX=800, Y_MAX=640, NUM_PLANETS = 2; //Размеры экрана
int ACTIVE_PLAYER;//Ходящий игрок

struct players
{
    int gold;//Счёт игрока
};
struct planets
{
    int index;
    int attack_ships;
    //sf::CircleShape picture;

    int buildings[3];//Массив строений: 0 - экономическое, 1 - защитное, 2 - казарма. Значение - уровень
    int def;//Показатель защиты
    int add_ships;//Число доступных для постройки кораблей
    int res;//Доходность
    //int x_place; От координат центра планеты нужно отказаться, т.к. эту информацию
    //int y_place; можно получить из поля picture: picture[i].getPosition();
    //int radius;  то же самое и с радиусом: picture[i].getRadius();
};
//struct planets* create();


#endif // HEADER_H
