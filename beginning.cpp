#include "header.h"
void beginning(struct planets *list)
{
	list[0].state = 0;
	list[0].ships = 5;
	list[0].x = 100;
	list[0].y = 400;
	list[0].belong = 1;// Пренадлежность к игроку(1-синий,2-красный,0-свободна)
	list[0].type = 1;//Один из трех типов планет(различия только визульные)
	
	list[1].state = 0;
	list[1].ships = 0;
	list[1].x = 700;
	list[1].y = 100;
	list[1].belong = 2;
	list[1].type = 2;
	
	list[2].state = 0;
	list[2].ships = 0;
	list[2].x = 1000;
	list[2].y = 450;
	list[2].belong = 3;
	list[2].type = 3;
	
	list[3].state = 0;
	list[3].ships = 0;
	list[3].x = 300;
	list[3].y = 50;
	list[3].belong = 0;
	list[3].type = 1;
}
