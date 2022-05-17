#include "include.h"
#include "Ball.h"
#include "Game.h"


/*
    1) Пофиксить ProcessingStaticCollision
    2) Сделать динамические коллизии
    3) Обработать попадание шаров в лунку
*/

int main()
{

    setlocale(LC_ALL, "RUS");
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Bil'yard!");


    std::string CueTexturePath = "..\\Graphics\\Cue.png";
    std::string TableTexturePath = "..\\Graphics\\Table.png";
    std::string BallTexturePath = "..\\Graphics\\Ball.png";
    std::string HitPowerPanelTexturePath = "..\\Graphics\\Panel.png";
    std::string HitPowerCueTexturePath = "..\\Graphics\\PanelCue.png";


    Game Game(window,CueTexturePath,TableTexturePath,BallTexturePath, HitPowerPanelTexturePath, HitPowerCueTexturePath);
    Game.Initialize(BallTexturePath);

    
    Clock clock;

    float speed = 0.5;
    float angle = 0;
    float CueHitDistance = 0;


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

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            Game.SetCueAngle(angle);
            angle += speed;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            Game.SetCueAngle(angle);
            angle -= speed;
        }
        
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            Vector2i MousePosition = Mouse::getPosition(window);
           // std::cout << MousePosition.x << " : " << MousePosition.y << std::endl;
            if (Game.IsHitPanelActive(Vector2f(MousePosition.x,MousePosition.y)))
            {
                Game.SetCueIsHit(true);
                Game.SetHitPowerPanelIsUpdate(true);
                Game.SetCueHitDistance(MousePosition.y - Game.GetHitPowerPanelTopPoint());
                Game.SetCueHitPower(Game.GetCueHitDistance() / Game.GetHitPowerPanelHeight() * MAX_CUE_POWER);
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            Game.CueHit();
        }


        window.clear();
        Game.Update(time);
        Game.Draw(window);
        window.display();

    }

    return 0;
}