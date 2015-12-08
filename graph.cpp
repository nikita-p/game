#include "header.h"

void begining(struct planets *planets)
{
    planets[0].state = 0;
    planets[0].x = 100;
    planets[0].y = 400;
    planets[0].belong = 1;
    planets[0].type = 1;
    planets[1].state = 0;
    planets[1].x = 700;
    planets[1].y = 100;
    planets[1].belong = 2;
    planets[1].type = 2;
    planets[2].state = 0;
    planets[2].x = 1000;
    planets[2].y = 450;
    planets[2].belong = 0;
    planets[2].type = 3;
    planets[3].state = 0;
    planets[3].x = 300;
    planets[3].y = 50;
    planets[3].belong = 3;
    planets[3].type = 1;
}

void add_planets(RenderWindow *window, Event event, Sprite *fn_sprite, Sprite *planets1_sprite, Sprite *planets2_sprite, struct planets  *planets, float *timescore, int N)
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
                    if (planets[i].state == 1)
                        planets[i].state = 0;
    }

    window->draw(*fn_sprite);
    for (int i = 0; i < N; i++)
    {
        if (planets[i].state == 0)
            window->draw(planets1_sprite[i]);
        else
            window->draw(planets2_sprite[i]);
    }
}

