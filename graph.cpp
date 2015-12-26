#include "header.h"
#include <math.h>

void add_planets(RenderWindow *window, Event event, Sprite *fn_sprite, Sprite *planets1_sprite, Sprite *planets2_sprite, struct planets  *planets, float *timescore, int N, group_ships* all_groups, ships_type* all_types, int activePlayer)
{
    float time = *timescore;
    Clock clock;

    int k = 4, T = 1, Lenght = 200;

    for (int j = 0; j < k; j++)
    {
        if (time > T*j)
            for (int i = 0; i < N; i++)
            {
                int y1 = (planets[i].type - 1) *Lenght, y2 = y1 + 3 * Lenght, x = j * Lenght;
                planets1_sprite[i].setTextureRect(IntRect(x, y1, 200, 200));
                planets2_sprite[i].setTextureRect(IntRect(x, y2, 200, 200));
                if ((time > T*k) && (i == N - 1))
                    *timescore = 0;
            }
    }
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.key.code == Mouse::Left)
            for (int i = 0; i < N; i++)
                if (event.mouseButton.x > planets[i].x && event.mouseButton.x < (planets[i].x + Lenght) && event.mouseButton.y > planets[i].y && event.mouseButton.y < (planets[i].y + Lenght))
                {
                    for (int j = 0; j < N; j++)
                        planets[j].state = 0;
                    planets[i].state = 1;
                }
        if (event.key.code == Mouse::Right)
            for (int i = 0; i < N; i++)
                if (event.mouseButton.x > planets[i].x && event.mouseButton.x < (planets[i].x + Lenght) && event.mouseButton.y > planets[i].y && event.mouseButton.y < (planets[i].y + Lenght))
                {
                    if (planets[Active_Planet(planets)].belong == activePlayer)
                    {
                        //Корабли получают цель, проблема: прожимается много раз! работает функция target
                        all_groups = target(planets[(Active_Planet(planets))], all_groups, &planets[i], all_types, window);
                    }
                }
    }

    window->draw(*fn_sprite);
    for (int i = 0; i < N; i++)
    {
        if (planets[i].state == 0)
            window->draw(planets1_sprite[i]);
        else
            window->draw(planets2_sprite[i]);
    }
    bool t= true;
}

void motion_ship(RenderWindow *window, Sprite *ship_sprite, int x0, int y0, int x, int y, bool* k, float speed)
{
    int Lenght = 200, L = 70, l = 25;//  некоторые геометрические параметры
    float dx = x - x0;
    float dy = y - y0;
    if (*k == true)
    {
        ship_sprite[0].setPosition(x0 + 75, y0 + 75);// установка начального положения
        ship_sprite[0].setRotation(0);// установка начального угла
    }
    *k = false;

    float DX = speed* dx / (10*sqrt(dx*dx + dy*dy)); // нормировка векторов и умножение на скорость
    float DY = speed* dy / (10*sqrt(dx*dx + dy*dy));

    ship_sprite[0].rotate(0.03); // изящный поворотик во время движения

    if (!(ship_sprite[0].getPosition().x + l > x + L && ship_sprite[0].getPosition().x + l < x + Lenght - L && ship_sprite[0].getPosition().y + l > y + L && ship_sprite[0].getPosition().y + l < y + Lenght - L))
    {
        ship_sprite[0].move(DX, DY);  // движение и отрисовка в условии ненахождения
        window->draw(ship_sprite[0]);
    }
    else
        *k = true;
}
