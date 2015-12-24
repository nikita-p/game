#include <header.h>
#include <fstream>

void begining(struct planets *planets, struct players* players) //Инициализация всего
{
    /*Начинаем с планет*/
    planets[0].x = 100;
    planets[0].y = 400;
    planets[1].x = 700;
    planets[1].y = 100;
    planets[2].x = 1000;
    planets[2].y = 450;
    planets[3].x = 300;
    planets[3].y = 50;
    for(int i=0; i<NUM_PLANETS;i++)
    {
        planets[i].state = 0;
        planets[i].belong = 1+i%MAX_PLAYERS; //+1 из-за пустого
        planets[i].type = i%3+1; //Коля, не помню, поправь пожалуйста
        for(int j=0; j<3; j++)
        {
            planets[i].buildings[j]=0;
            /*Начальные цены построек*/
            planets[i].cost_buildings[j]=level_up(planets,players,i,j,0);
            recount(planets);
        }
    }
    /*Теперь игроки*/
    ifstream in("files/color_table.txt"); //В этом файле лежат цвета в формате RGB
    for(int k = 0; k < MAX_PLAYERS + 1; k++)
    {
        players[0].gold=0; //Количество денег у "пустого" игрока
        players[k].death = false;
        if(k!=0)
            players[k].gold = START_MONEY;
        for(int i=0;i<3;i++)
        {
            int t;
            in >> t;
            players[k].color[i] = t;
        }
    }
    in.close();
}

int Active_Planet(struct planets* Planets) //поиск активной планеты
{
    for(int i = 0; i < NUM_PLANETS; i++)
    {
        if(Planets[i].state == 1)
        {
            return i; // вернет индекс активной(выделенной) планеты
        }
    }
    return -1; //не найдено
}
