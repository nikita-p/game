#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

float X_max = 1280, Y_max = 720;
float base_ramka = 2;
int Player_color[3] = {100, 100, 100}; //задаем массив цветов (для каждого игрока будут свои значения)

float base_lenght = X_max/16; // =80 пикселей
float base_height = Y_max/20; // =36 пикселя
int font_size = Y_max/36; // =20
int Now_Player = 1; // 1 - red, 2 - green, 3 - blue, 4 - yellow;
int Max_Players = 6; //число игроков
int Buildings_level[3] = {15, 23, 6};
int Buildings_level_up_cost[3] = {100, 50, 20};
int Player_Money[7] = {0, 10000, 1500, 3600, 3400, 2200, 1100}; // массив на 7(!!!) элементов, потому что Now_Player начинается с 1

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
void Draw_panel(RenderWindow* window, Color color, Texture* fon_block, Font font, int Now_Player)
// из блоков и текста собирается панелька
{
	for(int i = 0; i < 6; i++)
	{
		Draw_block(2 * base_lenght + i * 2 * base_lenght, Y_max - base_height, base_lenght, base_height, base_ramka, color, window, fon_block);
		Draw_block(2 * base_lenght + i * 2 * base_lenght + base_lenght, Y_max - base_height, base_lenght, base_height, base_ramka, color, window, fon_block);
		Draw_block(2 * base_lenght + i * 2 * base_lenght, Y_max - 2 * base_height, 2 * base_lenght, base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);
	}
	Draw_block(X_max - 2 * base_lenght, Y_max - 2 * base_height, 2 * base_lenght, 2 * base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);

	Draw_text(X_max - 2 * base_lenght + base_ramka, Y_max - 2 * base_height + base_ramka, 2 * base_lenght - 2 * base_ramka, 2 * base_height - 2 * base_ramka, Color::White, "\tNext\n\tPlayer" , 1.25 * font_size, window, font);
	Draw_text(2 * base_lenght + base_ramka, Y_max - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Economic's level", 0.9 * font_size, window, font);
	Draw_text(4 * base_lenght + base_ramka, Y_max - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Barrack's level", 0.9 * font_size, window, font);	
	Draw_text(6 * base_lenght + base_ramka, Y_max - 2 * base_height + base_ramka, 4 * base_lenght - 2 * base_ramka, 4 * base_height - 2 * base_ramka, Color::White, "Defense's level", 0.9 * font_size, window, font);	

	for(int j = 0; j < 3; j++)
	{
		Draw_text(2 * (j + 1) * base_lenght + 1.6 * base_lenght, Y_max - 2 * base_height + base_ramka, 0.4 * base_lenght, base_height, Color::White, int_to_string(Buildings_level[j]), font_size, window, font); // в аргументе int_to_string стоит уровень здания, надо сделать еще привязку к игроку и планете
		Draw_text(3 * base_lenght + 2 * j * base_lenght + base_ramka, Y_max - base_height + base_ramka, base_lenght - 2 * base_ramka, base_height, Color::White, "Level up", font_size, window, font);
		Draw_text(2 * base_lenght + 2 * j * base_lenght + base_ramka, Y_max - base_height + base_ramka, base_lenght - 2 * base_ramka, base_height, Color::White, int_to_string(Buildings_level_up_cost[j]), font_size, window, font);
	}
	Draw_block(0, Y_max - 2 * base_height, 2*base_lenght, 2 * base_height, base_ramka, Color(Player_color[0],Player_color[1],Player_color[2]), window, fon_block);
	Draw_text(0 + base_ramka, Y_max - 2 * base_height + base_ramka, 2 * base_lenght - 2 * base_ramka, 2 * base_height - 2 * base_ramka, Color::White, int_to_string(Player_Money[Now_Player]), 2*font_size, window, font); // как здесь сделана привязка к деньгам каждого игрока, так и нужно сделать в уровнях зданий и, впоследствии, с кораблями

}
bool Click_mouse(Event event, float x_left, float x_right, float y_up, float y_down) // функция, возвращающая true, если курсор мыши находится в определенной области
{
	return (event.mouseButton.x > x_left && event.mouseButton.x < x_right && event.mouseButton.y > y_down && event.mouseButton.y < y_up);
}
int main()
{

	// это все, наверное, следует перекинуть в наш main
	Texture fon_block;
	fon_block.loadFromFile("Textures\\fon_block.jpg"); //объявляем и загружаем текстуру из файла
	//block.setTextureRect(IntRect(0,0,1200,760)); //из файла вырезается прямоугольник и берется в качестве текстуры(размеры - почти вся картинка)

	Font font;
	font.loadFromFile("Fonts\\font_block.ttf"); //загрузка шрифта из файла

	RenderWindow window(VideoMode(X_max,Y_max), "Planets", Style::Fullscreen);

	window.setKeyRepeatEnabled(false); // устанавливаем, чтобы по одиночному нажиманию клавиши запускалось одно событие, а не череда событий

	while(window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
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
					if(Click_mouse(event, X_max - 2 * base_lenght, X_max, Y_max, Y_max - 2 * base_height))
					{ //если курсор попадает в пределы кнопки и нажата клавиша, то меняется игрок
						Now_Player = Now_Player + 1;					
						if(Now_Player > Max_Players)
						{
							Now_Player = 1;
						}
					}
					for(int j = 0; j < 3; j++)
					{
						if(Click_mouse(event, (2*j+3) * base_lenght, (2*j+4) * base_lenght, Y_max, Y_max - base_height))
						{
							Buildings_level[j] = Buildings_level[j] + 1; // уровень повышается на один
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
		switch(Now_Player) // в зависимости от текущего игрока выбирается цвет
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

	// все проверки условий можно позже выделить в отдельную функцию, и запускать ее внутри цикла, но это фигово, т.к в нее придется передавать каждый из параметров и возвращать она должна тоже все(хотя, может, я не так представляю)
	window.clear(Color::Black);
	Draw_panel(&window, Color(Player_color[0],Player_color[1],Player_color[2]), &fon_block, font, Now_Player);
	window.display();
	}
	return 0;
}