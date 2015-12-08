#include "header.h"

int main()
{
    int activePlayer = 1;


    int Player_color[3] = {100, 100, 100}; //задаем массив цветов (для каждого игрока будут свои значения)
    int Buildings_level[3] = {15, 23, 6};
    int Buildings_level_up_cost[3] = {100, 50, 20};
    int Player_Money[7] = {0, 10000, 1500, 3600, 3400, 2200, 1100}; // массив на 7(!!!) элементов, потому что Now_Player начинается с 1

    float timescore = 0;
    int N = 4;
    struct planets planets[4]; //Создание структуры планет
    begining(planets);

        Texture fon_block;
        fon_block.loadFromFile("files/menu_texture.png"); //объявляем и загружаем текстуру из файла
        //block.setTextureRect(IntRect(0,0,1200,760)); //из файла вырезается прямоугольник и берется в качестве текстуры(размеры - почти вся картинка)

        Font font;
        font.loadFromFile("files/menu_font.ttf"); //загрузка шрифта из файла

        //Image fn;
        //fn.loadFromFile("files/background_image.jpg");

        Texture fn_texture;
        fn_texture.loadFromFile("files/background_image.jpg");

        Sprite fn_sprite;
        fn_sprite.setTexture(fn_texture);
        fn_sprite.setPosition(0, 0);

        //Image _planets;
        //_planets.loadFromFile("/home/nikitap/projects/game/images/planets.jpg");
        //_planets.createMaskFromColor(Color(0, 0, 0));

        Texture planets_texture;
        planets_texture.loadFromFile("files/planets_image.png");

        Sprite planets1_sprite[4];
        Sprite planets2_sprite[4];

        for (int i = 0; i < N; i++)
        {
            planets1_sprite[i].setTexture(planets_texture);
            planets1_sprite[i].setPosition(planets[i].x, planets[i].y);

            planets2_sprite[i].setTexture(planets_texture);
            planets2_sprite[i].setPosition(planets[i].x, planets[i].y);

            int y1 = (planets[i].type - 1) * 200, y2 = y1 + 600;
            planets1_sprite[i].setTextureRect(IntRect(0, y1, 200, 200));
            planets2_sprite[i].setTextureRect(IntRect(0, y2, 200, 200));

            if (planets[i].belong == 1)
            {
                planets1_sprite[i].setColor(Color::Cyan);
                planets2_sprite[i].setColor(Color::Cyan);
            }
            if (planets[i].belong == 2)
            {
                planets1_sprite[i].setColor(Color::Green);
                planets2_sprite[i].setColor(Color::Green);
            }
            if (planets[i].belong == 3)
            {
                planets1_sprite[i].setColor(Color::Red);
                planets2_sprite[i].setColor(Color::Red);
            }
        }

        RenderWindow window(VideoMode(X_MAX,Y_MAX), "Planets", Style::Fullscreen);

        window.setKeyRepeatEnabled(false); // устанавливаем, чтобы по одиночному нажиманию клавиши запускалось одно событие, а не череда событий

        while (window.isOpen())
        {
            /*
            Clock clock;
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time/400 ;
            timescore = timescore + time;
            */
            timescore++;

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                switch(event.type)
                {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    switch(event.key.code)
                    {
                    case Keyboard::Escape:
                        window.close();
                        break;
                    }
                    break;
                case Event::MouseButtonPressed:
                    switch(event.mouseButton.button)
                    {
                    case Mouse::Left:
                        if(Click_mouse(event, X_MAX - 2 * base_lenght, X_MAX, Y_MAX, Y_MAX - 2 * base_height))
                        { //если курсор попадает в пределы кнопки и нажата клавиша, то меняется игрок
                            activePlayer++;
                            if(activePlayer > MAX_PLAYERS)
                            {
                                activePlayer= 1;
                            }
                        }
                        for(int j = 0; j < 3; j++)
                        {
                            if(Click_mouse(event, (2*j+3) * base_lenght, (2*j+4) * base_lenght, Y_MAX, Y_MAX - base_height))
                            {
                                Buildings_level[j] = Buildings_level[j] + 1; // уровень повышается на один
                                Player_Money[activePlayer] -= Buildings_level_up_cost[j]; //Никита играется (наверное, это нужно оставить) :)
                                Buildings_level_up_cost[j] = Buildings_level_up_cost[j] * 2; // цена поднятия уровня увеличивается в 2 раза(если будет массив параметров, то можно умножать на j элемент)
                            }
                        }
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            switch(activePlayer) // в зависимости от текущего игрока выбирается цвет
            {
            case 1:
                Player_color[0] = 200; //красный
                Player_color[1] = 50;
                Player_color[2] = 50;
                break;
            case 2:
                Player_color[0] = 50; //зеленый
                Player_color[1] = 200;
                Player_color[2] = 50;
                break;
            case 3:
                Player_color[0] = 50; //синий
                Player_color[1] = 50;
                Player_color[2] = 200;
                break;
            case 4:
                Player_color[0] = 200; //желтый
                Player_color[1] = 200;
                Player_color[2] = 50;
                break;
            case 5:
                Player_color[0] = 200; //фиолетовый
                Player_color[1] = 50;
                Player_color[2] = 200;
                break;
            case 6:
                Player_color[0] = 50; //голубой
                Player_color[1] = 200;
                Player_color[2] = 200;
                break;
            default:
                break;
            }
            window.clear(Color::Black);
            add_planets(&window, event, &fn_sprite, planets1_sprite, planets2_sprite, planets, &timescore, N);
            Draw_panel(&window, Color(Player_color[0],Player_color[1],Player_color[2]), &fon_block, font, activePlayer, Player_color, Buildings_level, Buildings_level_up_cost,Player_Money);
            window.display();
        }
}



/*int main()
{
    int activePlayer = 1;
    struct planets* list_planets = new struct planets[NUM_PLANETS];
    for(int i=0;i<NUM_PLANETS;i++)
    {
        list_planets[i].index=i;
        list_planets[i].x_place=X_MAX*(i+1)/(NUM_PLANETS+1);
        list_planets[i].y_place=Y_MAX*(i+1)/(NUM_PLANETS+1);
    }
    struct ships_type* all_types = create_list_types();
    struct group_ships* all_groups = create_list_groups(list_planets);
    for(int i = 0; i<72; i++)
    {
        list_planets[i%3]=create_ship(list_planets[i%3],i%2,200, activePlayer);
    }
    all_groups = add_new_group(all_groups); //Добавил пустую группу
    all_groups = delete_empty_groups(all_groups); //Удалил пустые группы
    int a[2] = {3, 0}; //Типичный массив кораблей
    all_groups = add_ship_in_group(all_groups, 0, 2, a, all_types); //Добавил корабли a из группы 0 в группу 2
    all_groups[1].next_position[0] = 1; //Задаю цель некоторой группе.
    all_groups[1].next_position[1] = 1;
    all_groups = step_one_ships(all_groups); //Поменял текущую позицию.
    int len = amount_groups_ships(all_groups);
    all_groups = battle(all_groups,1,2,all_types); //Битва
    return 0;
}
*/
