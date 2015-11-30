#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(600,600),"click_moving");
    CircleShape Circle(300,70);
    Circle.setFillColor(Color::Red);
    Circle.setPosition(40,50);
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            if(event.type==Event::MouseButtonPressed)
                Circle.move(10,0);
        }
        window.clear();
        window.draw(Circle);
        window.display();
    }
    return 0;
}
