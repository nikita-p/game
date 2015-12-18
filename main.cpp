#include "header.h"

int main()
{
        /*Блок инициализации*/
    float timescore = 0;
    int activePlayer = 1;
    struct players* players = new struct players [MAX_PLAYERS + 1]; //Игроки, +1 для пустых планет
    struct planets* planets = new struct planets [NUM_PLANETS];     //Планеты
    struct ships_type* all_types = create_list_types();             //Типы кораблей с характеристиками
    struct group_ships* all_groups = create_list_groups(planets); //Группы кораблей
    int Buildings_level_up_cost[3] = {100, 50, 20};
    begining(planets, players); //Лежит в data.cpp

        /*Блок загрузки всех вещей*/ //Ещё нужно сделать графику для кораблей
    Texture fon_block;
    fon_block.loadFromFile("Textures/fon_block.jpg");
    Font font;
    font.loadFromFile("Fonts/font_block.ttf");    //загрузка шрифта из файла
    Texture fn_texture;
    fn_texture.loadFromFile("files/background_image.jpg");
    Sprite fn_sprite;
    fn_sprite.setTexture(fn_texture);
    fn_sprite.setPosition(0, 0);
    Texture planets_texture;
    planets_texture.loadFromFile("files/planets_image.png");
    Sprite planets1_sprite[NUM_PLANETS];
    Sprite planets2_sprite[NUM_PLANETS];
    for (int i = 0; i < NUM_PLANETS; i++)
    {
        planets1_sprite[i].setTexture(planets_texture);
        planets1_sprite[i].setPosition(planets[i].x, planets[i].y);
        planets2_sprite[i].setTexture(planets_texture);
        planets2_sprite[i].setPosition(planets[i].x, planets[i].y);
        int y1 = (planets[i].type - 1) * 200, y2 = y1 + 600;
        planets1_sprite[i].setTextureRect(IntRect(0, y1, 200, 200));
        planets2_sprite[i].setTextureRect(IntRect(0, y2, 200, 200));
        int j =planets[i].belong; //Делаем цвета для каждой планеты
        planets1_sprite[i].setColor(Color(players[j].color[0],players[j].color[1],players[j].color[2]));
        planets2_sprite[i].setColor(Color(players[j].color[0],players[j].color[1],players[j].color[2]));
    }

    /*-------------------------------------------------------------------------------------------------*/







    //это нужно убрать, т.к. уже есть, но я не успел
    int Player_Money[7] = {0, 10000, 1500, 3600, 3400, 2200, 1100}; // массив на 7(!!!) элементов, потому что Now_Player начинается с 1




        RenderWindow window(VideoMode(X_MAX,Y_MAX), "Beta", Style::Fullscreen);

        window.setKeyRepeatEnabled(false); // устанавливаем, чтобы по одиночному нажиманию клавиши запускалось одно событие, а не череда событий

        while (window.isOpen())
        {
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
                                activePlayer =1;
                            }
                            }
                            for(int j = 0; j < 3; j++) //j - индексы зданий
                            {
                                if(Click_mouse(event, (2*j+3) * base_lenght, (2*j+4) * base_lenght, Y_MAX, Y_MAX - base_height))
                                {
                                    if(activePlayer == planets[Active_Planet(planets)].belong)
                                        Buildings_level_up_cost[j] = level_up(planets, players, Active_Planet(planets), j, activePlayer);
                                }
                            }
                            break;
                        }
                    break;
                default:
                    break;
                }
            }
            window.clear(Color::Black);
            add_planets(&window, event, &fn_sprite, planets1_sprite, planets2_sprite, planets, &timescore, NUM_PLANETS);
            Draw_panel(&window, Color(players[activePlayer].color[0],players[activePlayer].color[1],players[activePlayer].color[2]),
                    &fon_block, font, activePlayer, players[activePlayer].color, planets[Active_Planet(planets)].buildings, Buildings_level_up_cost,
                    Player_Money, &(planets[activePlayer]));
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
