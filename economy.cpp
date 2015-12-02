#include "header.h"
#include "math.h"
int const SLUP_E = 600, //Start level-up price of economy (1 lvl->2 lvl)
            SLUP_D = 900, //--defense
            SLUP_A = 1200, //--add-ship building
            PRP_E = 1.6, //Показатель роста стоимости прокачки экономики
            PRP_D = 1.5, //--защиты
            PRP_A = 1.4, //--казармы
            SD = 5, //Показатель защиты 1-го уровня
            SA = 5, //Сколько можно построить за ход кораблей на 1-м уровне
            SR = 500, //Доходность планеты 1-го уровня
            PR_D = 1.3,//Показатель роста защиты при прокачке
            PR_A = 1.2,//--казармы
            PR_E = 1.5,//-доходности
            PS = 80;//Price of ship

int level_up(struct planets * list, struct players * list_p, int planet, int building)//Функция прокачки здания. Возвращает 0 - нужно больше золота, 1 - успешно. Должна вызываться при нажатии соотв. кнопки
{
    int cost;//Стоимость
    switch (building)
    {
    case 0:
        cost = (int)SLUP_E*pow(PRP_E, list[planet].buildings[building]-1);
        break;
    case 1:
        cost = (int)SLUP_D*pow(PRP_D, list[planet].buildings[building]-1);
        break;
    case 2:
        cost = (int)SLUP_A*pow(PRP_A, list[planet].buildings[building]-1);
        break;
    }

    if (list_p[ACTIVE_PLAYER].gold >= cost){
        list[planet].buildings[building]++;
        list_p[ACTIVE_PLAYER].gold = list_p[ACTIVE_PLAYER].gold - cost;
        return 1;
    }
    return 0;
}

void recount(struct planets * list)//Обновление показателей планет. Должна вызываться в начале нового круга - благодаря этому, эффект от прокачки почувствуется только на след. ходе
{
    for (int i = 0; i < NUM_PLANETS; i++){
        list[i].def = (int)SD*pow(PR_D, list[i].buildings[1]);
        list[i].add_ships = (int)SA*pow(PR_A, list[i].buildings[2]);
        list[i].res = (int)SE*pow(PR_E, list[i].buildings[0]);
    }
}

int build_ship(struct planets * list, struct players * list_p, int planet, int count)
{
    if ((list_p[ACTIVE_PLAYER].gold >= PS * count) && (list[planet].add_ships >= count))
    {
        list_p[ACTIVE_PLAYER].gold = list_p[ACTIVE_PLAYER].gold - count * PS;
        list[planet].add_ships = list[planet].add_ships - count;
        list[planet].attack_ships = list[planet].attack_ships + count;
        return 1;
    }
    return 0;
}
