#include "header.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(X_MAX,Y_MAX),"OK, It is a start");
    struct planets* list = new struct planets[2];
    list = create();
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }
        window.clear();
        for(int i=0; i<NUM_PLANETS;i++)
            window.draw(list[i].picture);
        window.display();
    }
    return 0;
}
