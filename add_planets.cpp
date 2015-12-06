#include "header.h"
void add_planets(RenderWindow *window, Event event, struct planet  *planets, float *timescore, int N)
{
	int L = 200;//размеры текстур
	int k = 4, T = 100;//k-количество кадров, T-время между;



	Image fn; //создаем объект Image (Фон)
	fn.loadFromFile("images\\fn.jpg");//загружаем в него файл

	Texture fn_texture;//создаем объект Texture (текстура для фона)
	fn_texture.loadFromImage(fn);//передаем в него объект Image 

	Sprite fn_sprite;//создаем объект Sprite
	fn_sprite.setTexture(fn_texture);//передаём в него объект Texture
	fn_sprite.setPosition(0, 0);//задаем начальные координаты появления спрайта

	Image _planets;
	_planets.loadFromFile("images\\planets.jpg");
	_planets.createMaskFromColor(Color(0, 0, 0));

	Texture planets_texture;
	planets_texture.loadFromImage(_planets);

	Sprite planets1_sprite[3];//массивы спрайтов(один для обычных планет, другой для выделенных)
	Sprite planets2_sprite[3];//

	for (int i = 0; i < N; i++)
	{
		planets1_sprite[i].setTexture(planets_texture);
		planets1_sprite[i].setPosition(planets[i].x, planets[i].y);

		planets2_sprite[i].setTexture(planets_texture);
		planets2_sprite[i].setPosition(planets[i].x, planets[i].y);

		int y1 = (planets[i].type - 1) * 200, y2 = y1 + 600;
		planets1_sprite[i].setTextureRect(IntRect(0, y1, L, L));
		planets2_sprite[i].setTextureRect(IntRect(0, y2, L, L));
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
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Left)
				for (int i = 0; i < N; i++)
					if (event.mouseButton.x > planets[i].x && event.mouseButton.x < (planets[i].x + 200) && event.mouseButton.y > planets[i].y && event.mouseButton.y < (planets[i].y + 200))
					{
						for (int j = 0; j < N; j++)
							planets[j].state = 0;
						planets[i].state = 1;
					}
		if (event.type == Event::MouseButtonPressed)
			if (event.key.code == Mouse::Right)
				for (int i = 0; i < N; i++)
					if (event.mouseButton.x > planets[i].x && event.mouseButton.x < (planets[i].x + 200) && event.mouseButton.y > planets[i].y && event.mouseButton.y < (planets[i].y + 200))
						if (planets[i].state == 1)
							planets[i].state = 0;
		
		
		window->draw(fn_sprite);
		for (int i = 0; i < N; i++)
		{
			if (planets[i].state == 0)
				window->draw(planets1_sprite[i]);
			else
				window->draw(planets2_sprite[i]);
		}
		
	
}
