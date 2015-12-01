#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

const int X_MAX=800, Y_MAX=640, NUM_PLANETS = 2; //Размеры экрана

struct planets
{
    int index;
    int attack_ships;
    sf::CircleShape picture;
    //int x_place; От координат центра планеты нужно отказаться, т.к. эту информацию
    //int y_place; можно получить из поля picture: picture[i].getPosition();
    //int radius;  то же самое и с радиусом: picture[i].getRadius();
};
struct planets* create();


#endif // HEADER_H
