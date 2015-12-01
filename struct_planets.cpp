#include "header.h"

using namespace sf;

const int x[2]={40,630}, y[2] = {50,480}, Rad=50; //Координаты планет и их радиус

struct planets* create() //Здесь происходит создание планет
{
    CircleShape* Planet = new CircleShape [NUM_PLANETS];
    struct planets* list = new struct planets [NUM_PLANETS]; //Данные хранятся в структуре
    for(int i=0;i<NUM_PLANETS;i++)
    {
        Planet[i].setFillColor(sf::Color(i*55, 200-50*i, 50+10*i)); //Цвет планетки
        Planet[i].setPosition(x[i],y[i]); //Позиция планеты, радиус
        Planet[i].setRadius(Rad);
        list[i].index = i;          //Индекс, вместо названия(пока)
        list[i].attack_ships = 5*i; //Количество кораблей на ней.
        list[i].picture=Planet[i]; //Связываю планету с её рисунком

    }
    return list; //Возвращаю структуру с данными о планетах
}
