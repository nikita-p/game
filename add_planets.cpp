void add_planets(RenderWindow *window, Event event, Sprite *fn_sprite, Sprite *planets1_sprite, Sprite *planets2_sprite, struct planets  *list, float *timescore, int N)
{
	float time = *timescore;
	int k = 8, T = 100, Lenght = 200;
	for (int j = 0; j < k; j++)
	{
		if (time > T*j)
			for (int i = 0; i < N; i++)
			{
				int y1 = (list[i].type - 1) *Lenght, y2 = y1 + 3 * Lenght, x = j * Lenght;
				planets1_sprite[i].setTextureRect(IntRect(x, y1, 200, 200));
				planets2_sprite[i].setTextureRect(IntRect(x, y2, 200, 200));
				if ((time > T*k) && (i == N - 1))
					*timescore = 0;
			}
	}
	if (event.type == Event::MouseButtonPressed)
	{
		bool check_position = 0;
		if (event.key.code == Mouse::Left)
		{
			for (int i = 0; i < N; i++)
				if (event.mouseButton.x > list[i].x && event.mouseButton.x < (list[i].x + Lenght) && event.mouseButton.y > list[i].y && event.mouseButton.y < (list[i].y + Lenght))
				{
					for (int j = 0; j < N; j++)
						list[j].state = 0;
					list[i].state = 1;
					check_position = true;
				}
			if (check_position == false)
				for (int i = 0; i < N; i++)
					list[i].state = 0;
		}
	}
	window->draw(*fn_sprite);
	for (int i = 0; i < N; i++)
	{
		if (list[i].state == 0)
			window->draw(planets1_sprite[i]);
		else
			window->draw(planets2_sprite[i]);
	}
}
