#include "include.h"
#include "Ball.h"
#include "Game.h"




int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Bil'yard!");
   


    Game Game(window);

   
    Clock clock;

    float FrictionCoeff = 0.0002;
    Vector2f Dir(3, -2);
    float speed = 0.5;
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= GAME_SPEED;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
              
        }
       
       // window.clear();
        Game.Draw(window);
        window.display();
    }

    return 0;
}