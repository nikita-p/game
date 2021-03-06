#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

const int X_MAX=1280, Y_MAX=720, NUM_PLANETS = 3, NUM_TYPES=1, START_MONEY = 2000, MAX_PLAYERS = 3, font_size = Y_MAX/36; // =20
//Количество типов кораблей(NUM_TYPES) Размеры экрана(X_MAX,Y_MAX), число игроков
const float base_lenght = X_MAX/16, base_height = Y_MAX/20; // base-lenght=80 пикселей base-height=36 пикселя
const float base_ramka = 2;

struct players
{
	int number; // номер
    int gold;   //Счёт игрока
	int color[3]; //цвет

};
struct planets
{
    int index;
    int state;
    int type;
    int belong;
    int buildings[3];//Массив строений: 0 - экономическое, 1 - защитное, 2 - казарма. Значение - уровень
    int cost_buildings[3]; //Массив цен на улучшение построек
    int def;//Показатель защиты
    int add_ships;//Число доступных для постройки кораблей
    int res;  //Доходность
    int x; //Координаты
    int y;
    struct group_ships* defenders; //Корабли на этой планете
};

struct ships_type   //Тип корабля
{
    int attack;     // 0<атака_корабля<100
    int walking_ability;
    //Sprite sprite; //Для отрисовки кораблей
};

struct group_ships //Группы кораблей
{
    int number;
    int player;
    int amount_ships;
    int current_position[2];
    int next_position[2];
    int ships_types[NUM_TYPES];
    struct group_ships* next;
};
void return_graphics(struct planets* planets, struct players* players, struct group_ships* all_groups, ships_type *all_types, int activePlayer);

void draw_menu(RenderWindow* window, Texture* fon_block, Font font, struct planets planets, struct players players);
//Функция с простыми аргументами, которая рисует панель меню

void Draw_block(float X, float Y, float lenght, float height, float ramka, Color color, RenderWindow* window, Texture* fon_block);
/*в функцию дают высоту и длину блока, координаты верхнего левого угла и цвет в формате RGB
    для разных игроков(по цвету) будут использоваться комбинации (200,50,50) (50,200,50) (50,50,200); для нейтральных (100,100,100)
    *window - для того, что бы мы рисовали в нашем окне и не создавали кучу новых*/

void Draw_text(float X, float Y, float lenght, float height, Color color, char* string, int size, RenderWindow* window, Font font);
//string и size отвечают за текст и размер шрифта, font - за шрифт(в main загрузим из файла)

void Draw_panel(RenderWindow* window, Color color, Texture* fon_block, Font font, int Player_color[], int Buildings_level[], int Buildings_level_up_cost[], int Player_Money, struct planets* planets);
// из блоков и текста собирается панелька

bool Click_mouse(Event event, float x_left, float x_right, float y_up, float y_down);
// функция, возвращающая true, если курсор мыши находится в определенной области



int level_up(struct planets * list, struct players * list_p, int planet, int building, int ACTIVE_PLAYER);

void recount(struct planets * list);

int build_ship(struct planets * list, struct players * list_p, int planet, int count, int ACTIVE_PLAYER, int type);

void begining(struct planets *planets, players *players);

void add_planets(RenderWindow *window, Event event, Sprite *fn_sprite, Sprite *planets1_sprite, Sprite *planets2_sprite, struct planets  *planets, float *timescore, int N, group_ships* all_groups, ships_type* all_types, int activePlayer);

struct ships_type* create_list_types ();
//Здесь создаются типы кораблей. Нужно сделать один раз в начале игры.

struct group_ships* target(struct planets planets, struct group_ships* all_groups, struct planets* planetTwo, struct ships_type* all_types);
//Функция, задающая цель для кораблей.

struct group_ships *create_list_groups(struct planets* all_planets);
//Функция инициализирует список групп. Нужно сделать один раз в начале игры + идёт сопоставление планет и кораблей на них

void create_ship(planets creator, int type_index, int activePlayer);
//Создание корабля. Список планет, какой тип (int индекс этого типа)!, сколько может пройти, куда поставить, кто играет.

int amount_groups_ships(struct group_ships* l);
//Сколько групп кораблей существует

struct group_ships *add_new_group(group_ships *all_groups);
//Создание новой группы кораблей. Вывожу лист групп. Нулевое место в листе групп будет занимать новая группа.

struct group_ships* delete_one_group(struct group_ships* all, int trash_index);
//Функция позволяет удалить из списка групп одну с заданным индексом.

struct group_ships* delete_empty_groups(struct group_ships* l);
//Удаляю пустые группы кораблей. Вывожу лист групп.

void add_ship_in_group(struct group_ships* fromGroup, struct group_ships* inGroup, int typeAmount[], struct ships_type* allTypes);
struct group_ships* add_ship_in_group (struct group_ships* allGroups, int fromGroup, int toGroup, int typeAmount[NUM_TYPES], struct ships_type* allTypes);
//Функция добавляет корабли в существующую группу с индексом index_in из группы с индексом index_from

void step_group(group_ships *one, ships_type *all_types);
struct group_ships *step_one_ships(struct group_ships* allGroups, ships_type *all_types);
//Беспрепятственный шаг полёта группы кораблей

int check_index (int* index_active, int* index_passive, int array_active[NUM_TYPES], int array_passive[NUM_TYPES]);
//Ищем лучший тип кораблей, который есть у противников

struct group_ships* battle(struct group_ships* start_groups, int i_active, int  i_passive, struct ships_type* all_types);
//Это сам бой между группами кораблей. Выбираем самых сильных и сталкиваем между собой, убиваем проигравший корабль :(

struct planets* seize(struct group_ships* new_kings, struct planets* change_planet);
//Захват планеты. Необходимо сменить defenders у этой планеты

int Active_Planet(struct planets* Planets); //поиск активной планеты

char* int_to_string(int N); //функция перевода инта в строку

int walking(struct group_ships* one_group, struct ships_type* all_types);

#endif // HEADER_H
