#include "include.h"
#include "Ball.h"




int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bil'yard!");
   

    Ball ball(Vector2f(20, 400), 10, Color::Red);
    Clock clock;

    float FrictionCoeff = 0.0005;
    Vector2f Dir(1, 0);
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
            ball.SetIsMove(true);
            ball.ChangeDir(Dir);
            ball.SetSpeed(speed);   
        }
        ball.Update(time, FrictionCoeff);
 
        window.clear();
        ball.Draw(window);
        window.display();
    }

    return 0;
}