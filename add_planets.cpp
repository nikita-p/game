#include "header.h"
void add_planets(RenderWindow *window, Event event, Sprite *fn_sprite, Sprite *planets1_sprite, Sprite *planets2_sprite, struct planet  *planets, float *timescore, int N)
{
	float time = *timescore;

		
		
		int k = 4, T = 150;//T-интервал между кадрами, k-число кадров
		
		
		for (int j = 0; j<k; j++)
		{
			if (time > T*j)
				for (int i = 0; i < N; i++)
				{
					int y1 = (planets[i].type - 1) * 200, y2 = y1 + 600, x = j * 200;
					planets1_sprite[i].setTextureRect(IntRect(x, y1, 200, 200));
					planets2_sprite[i].setTextureRect(IntRect(x, y2, 200, 200));
					if ((time > T*k) && (i == N - 1))
						*timescore = 0;
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
	
		window->draw(*fn_sprite);
		for (int i = 0; i < N; i++)
		{
			if (planets[i].state == 0)
				window->draw(planets1_sprite[i]);
			else
				window->draw(planets2_sprite[i]);
		}
		
	
}
