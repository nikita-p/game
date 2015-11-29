#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(600,600),"Test");
    CircleShape MyCircle1(30,170);
    CircleShape MyCircle2(50,50);
    MyCircle1.setFillColor(Color::Green);
    MyCircle2.setFillColor(Color::Blue);
    MyCircle1.move(70,100);
    Clock clock;

    while(window.isOpen())
    {
        float time =clock.getElapsedTime().asMicroseconds();
        clock.restart();
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            MyCircle1.move(-0.001*time,0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            MyCircle1.move(0.001*time,0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            MyCircle1.move(0,-0.001*time);
        }
        if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            MyCircle1.move(0,0.001*time);
        }
        window.clear();
        window.draw(MyCircle1);
        window.draw(MyCircle2);
        window.display();
    }
    return 0;
}
