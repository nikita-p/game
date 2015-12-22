#include "header.h"


void return_graphics(struct planets* planets,struct players* players,struct group_ships* all_groups, struct ships_type* all_types
                     ,int activePlayer)
{
    float timescore =0;
    /*Блок загрузки всех вещей*/ //Ещё нужно сделать графику для кораблей
    Texture fon_block;
    fon_block.loadFromFile("Textures/fon_block.png");
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

    RenderWindow window(VideoMode(X_MAX,Y_MAX), "Beta", Style::Close);

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
                            players[activePlayer].gold+=500; //Нужна функция начисления денег
                            activePlayer++;
                            if(activePlayer > MAX_PLAYERS)
                                activePlayer =1;
                        }
                        for(int j = 0; j < 3; j++) //j - индексы зданий
                        {
                            if(Click_mouse(event, (2*j+3) * base_lenght, (2*j+4) * base_lenght, Y_MAX, Y_MAX - base_height))
                            {
                                if(activePlayer == planets[Active_Planet(planets)].belong) //Строим здания и выводим на экран
                                {
                                    level_up(planets, players, Active_Planet(planets), j, activePlayer);
                                    //Использем level_up для получения цены следующего улучшения, вставляя в качестве активного пустого игрока - 0.
                                    planets[Active_Planet(planets)].cost_buildings[j] = level_up(planets, players, Active_Planet(planets), j, 0);
                                }

                            }
                        }
                        if(Click_mouse(event, (2*3+3) * base_lenght, (2*3+4) * base_lenght, Y_MAX- base_height, Y_MAX - 2*base_height)
                                && activePlayer==planets[Active_Planet(planets)].belong)
                        { //Здесь происходит создание кораблей, 1 штука - 300$
                            if(players[activePlayer].gold-300>=0)
                            {
                                players[activePlayer].gold-=300;
                                create_ship(planets[Active_Planet(planets)], 0, activePlayer);
                            }
                        }
                        break;
                    }
                break;
            default:
                break;
            }
        }
        int activePlanet=Active_Planet(planets);
        if(activePlanet==-1) activePlanet=0;
        window.clear(Color::Black);
        add_planets(&window, event, &fn_sprite, planets1_sprite, planets2_sprite, planets,
                    &timescore, NUM_PLANETS, all_groups, all_types, activePlayer);
        draw_menu(&window, &fon_block, font, planets[activePlanet], players[activePlayer]); //лежит в data.cpp
        window.display();
    }
}
