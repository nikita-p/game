#include "header.h"

void draw_menu(RenderWindow* window, Texture* fon_block, Font font, struct planets planets, struct players players)
//Функция с простыми аргументами, которая рисует панель меню
{
    Draw_panel(window, Color(players.color[0],players.color[1],players.color[2]),
                        fon_block, font, players.color, planets.buildings, planets.cost_buildings,
                        players.gold, &(planets));
    return;
}



char* int_to_string(int N) //функция перевода инта в строку
{
    int len = 1;
    int K = N; // вводим дополнительную переменную, чтобы не изменить исходное число(так как в цикле идет переобозначение)
    while(K >= 10) //подсчет длины числа (количества цифр)
    {
        len = len + 1;
        K = K / 10;
    }//после цикла len = количеству цифр
    char* str = new char[len + 1]; // объявляем и выделяем память под строку длиной len и еще одна позиция для '\0'
    for(int i = 0; i < len; i++)
    {
        str[len - 1 - i] = '0' + (N % 10); // N / 10 - цифра старшего разряда, записываем ее в строку(прибавив к символу '0' интовую цифру, получим символ той же цифры)
        N = (N / 10); // переобозначение N(рекурсия)
    }
    str[len] = '\0'; // спец. символ, завершающий строку
    return str;
}
void Draw_block(float X, float Y, float lenght, float height, float ramka, Color color, RenderWindow* window, Texture* fon_block)
//в функцию дают высоту и длину блока, координаты верхнего левого угла и цвет в формате RGB
//для разных игроков(по цвету) будут использоваться комбинации (200,50,50) (50,200,50) (50,50,200); для нейтральных (100,100,100)

//*window - для того, что бы мы рисовали в нашем окне и не создавали кучу новых
{
    RectangleShape block(Vector2f(lenght, height)); //рисует блок и рамку
    block.setPosition(X, Y);
    block.setFillColor(color);
    block.setOutlineThickness(-1 * ramka); // "-" - рамка рисуется внутрь прямоугольника
    block.setOutlineColor(color);
    block.setTexture(fon_block);
    block.setTextureRect(IntRect(0,0,1200,760)); //из файла вырезается прямоугольник и берется в качестве текстуры(размеры - почти вся картинка)

    window->draw(block);
}
void Draw_text(float X, float Y, float lenght, float height, Color color, char* string, int size, RenderWindow* window, Font font)
//string и size отвечают за текст и размер шрифта, font - за шрифт(в main загрузим из файла)
{
    Text text_block; //объявление текстового блока
    text_block.setPosition(X, Y); // рисуем текст внутри поля
    text_block.setCharacterSize(size); // устанавливаем размер шрифта и цвет
    text_block.setColor(color);
    text_block.setString(string);//загружаем строку
    text_block.setFont(font); // устанавливаем шрифт для этого текста

    window->draw(text_block);
}
void Draw_panel(RenderWindow* window, Color color, Texture* fon_block, Font font, int Player_color[], int Buildings_level[], int* Buildings_level_up_cost, int Player_Money, struct planets* planets)
// из блоков и текста собирается панелька
{
    for(int i = 0; i < 6; i++)
    {
        Draw_block(2 * base_lenght + i * 2 * base_lenght, Y_MAX - base_height, base_lenght, base_height, base_ramka, color, window, fon_block);
        Draw_block(2 * base_lenght + i * 2 * base_lenght + base_lenght, Y_MAX - base_height, base_lenght, base_height, base_ramka, color, window, fon_block);
        Draw_block(2 * base_lenght + i * 2 * base_lenght, Y_MAX - 2 * base_height, 2 * base_lenght, base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);
    }
    Draw_block(X_MAX - 2 * base_lenght, Y_MAX - 2 * base_height, 2 * base_lenght, 2 * base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);

    Draw_text(X_MAX - 2 * base_lenght + base_ramka, Y_MAX - 2 * base_height + base_ramka, 2 * base_lenght - 2 * base_ramka, 2 * base_height - 2 * base_ramka, Color::White, "\tNext\n\tPlayer" , 1.25 * font_size, window, font);
    Draw_text(2 * base_lenght + base_ramka, Y_MAX - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Economic", 0.9 * font_size, window, font);
    Draw_text(4 * base_lenght + base_ramka, Y_MAX - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Barracks", 0.9 * font_size, window, font);
    Draw_text(6 * base_lenght + base_ramka, Y_MAX - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Defense", 0.9 * font_size, window, font);

    for(int j = 0; j < 3; j++)
    {
        Draw_text(2 * (j + 1) * base_lenght + 1.6 * base_lenght, Y_MAX - 2 * base_height + base_ramka, 0.4 * base_lenght, base_height, Color::White, int_to_string(planets->buildings[j]), font_size, window, font); // всё отлично
        Draw_text(3 * base_lenght + 2 * j * base_lenght + base_ramka, Y_MAX - base_height + base_ramka, base_lenght - 2 * base_ramka, base_height, Color::White, "+", font_size, window, font);
        Draw_text(2 * base_lenght + 2 * j * base_lenght + base_ramka, Y_MAX - base_height + base_ramka, base_lenght - 2 * base_ramka, base_height, Color::White, int_to_string(Buildings_level_up_cost[j]), font_size, window, font);
    }
    /*--Вставленное руками количество кораблей на планете, нужно, чтобы было автоматически--*/
    int j=4;
    Draw_text(8 * base_lenght + base_ramka, Y_MAX - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::Black, "Ships", 0.9 * font_size, window, font);
    Draw_text(2 * j * base_lenght + 1.6 * base_lenght, Y_MAX - 2 * base_height + base_ramka, 0.4 * base_lenght, base_height, Color::Black, int_to_string(planets->defenders->amount_ships), font_size, window, font);
    Draw_text(3 * base_lenght + 2 * (j-1) * base_lenght + base_ramka, Y_MAX - base_height + base_ramka, base_lenght - 2 * base_ramka, base_height, Color::Black, int_to_string(planets[Active_Planet(planets)].add_ships), font_size, window, font);
    /*---*/
    Draw_block(0, Y_MAX - 2 * base_height, 2*base_lenght, 2 * base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);
    Draw_text(0 + base_ramka, Y_MAX - 2 * base_height + base_ramka, 2 * base_lenght - 2 * base_ramka, 2 * base_height - 2 * base_ramka, Color::White, int_to_string(Player_Money), 2*font_size, window, font); // как здесь сделана привязка к деньгам каждого игрока, так и нужно сделать в уровнях зданий и, впоследствии, с кораблями

}
bool Click_mouse(Event event, float x_left, float x_right, float y_up, float y_down) // функция, возвращающая true, если курсор мыши находится в определенной области
{
    return (event.mouseButton.x > x_left && event.mouseButton.x < x_right && event.mouseButton.y > y_down && event.mouseButton.y < y_up);
}
