#include "header.h"

using namespace sf;

int main()
{
	float timescore = 0;
	int N = NUM_PLANETS;//////////////////////для изменение количества планет менять циферку здесь
	struct planets  list[NUM_PLANETS];///////////////////  и здесь (кроме того необходимо заполнить поля структуры)
	begining(list);
    Sprite fn_sprite;
	Sprite planets1_sprite[NUM_PLANETS];
	Sprite planets2_sprite[NUM_PLANETS];
	Texture fn_texture;
	fn_texture.loadFromFile("images\\fn.jpg");
	fn_sprite.setTexture(fn_texture);
	fn_sprite.setPosition(0, 0);
	Image _planets;
	_planets.loadFromFile("images\\planets.jpg");
	_planets.createMaskFromColor(Color(0, 0, 0));
	Texture planets_texture;
	planets_texture.loadFromImage(_planets);
	for (int i = 0; i < N; i++)
	{
		planets1_sprite[i].setTexture(planets_texture);
		planets1_sprite[i].setPosition(list[i].x, list[i].y);
		planets2_sprite[i].setTexture(planets_texture);
		planets2_sprite[i].setPosition(list[i].x, list[i].y);
		int y1 = (list[i].type - 1) * 200, y2 = y1 + 600;
		planets1_sprite[i].setTextureRect(IntRect(0, y1, 200, 200));
		planets2_sprite[i].setTextureRect(IntRect(0, y2, 200, 200));
		if (list[i].belong == 1)
		{
			planets1_sprite[i].setColor(Color(103, 183, 208));
			planets2_sprite[i].setColor(Color(103, 183, 208));
		}
		if (list[i].belong == 2)
		{
			planets1_sprite[i].setColor(Color(70, 163, 107));
			planets2_sprite[i].setColor(Color(70, 163, 107));
		}
		if (list[i].belong == 3)
		{
			planets1_sprite[i].setColor(Color(163, 93, 163));
			planets2_sprite[i].setColor(Color(163, 93, 163));
		}
	}
    RenderWindow window(VideoMode(X_MAX,Y_MAX),"OK, It is a start");
    struct planets* list = new struct planets[NUM_PLANETS];
    list = create();
    while(window.isOpen())
    {
        Clock clock;
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart();//перезагружает время
		time = time/3 ;//скорость игры
		timescore = timescore + time;
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear();
        for(int i=0; i<NUM_PLANETS;i++)
            window.draw(list[i].picture);
         add_planets(&window, event, &fn_sprite, planets1_sprite, planets2_sprite, list, &timescore, N);   
        window.display();
    }
    return 0;
}
