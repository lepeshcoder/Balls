#include <SFML/Graphics.hpp>
#include"include.h"
#include"Circle.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       
    }

    return 0;
}