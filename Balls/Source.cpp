#include "include.h"
#include "Ball.h"
#include "Game.h"





/*
    1) Обработать попадание шаров в лунку ( Немного поправить)
    2) Сеть
    3) Переделать все под GameStates
    4) Сделать   
*/

int main()
{
    setlocale(LC_ALL, "RUS");
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Bil'yard!");

    sf::Music music;
    music.openFromFile("..\\Music\\Badabum.ogg");
    music.setPitch(1.5);
    music.setLoop(true);
    music.play();

    std::string CueTexturePath = "..\\Graphics\\Cue.png";
    std::string TableTexturePath = "..\\Graphics\\Table.png";
    std::string BallTexturePath = "..\\Graphics\\Ball.png";
    std::string MainBallTexturePath = "..\\Graphics\\MainBall.png";
    std::string HitPowerPanelTexturePath = "..\\Graphics\\Panel.png";
    std::string HitPowerCueTexturePath = "..\\Graphics\\PanelCue.png";


    Game Game(window,CueTexturePath,TableTexturePath,BallTexturePath, HitPowerPanelTexturePath, HitPowerCueTexturePath);
    Game.Initialize(BallTexturePath,MainBallTexturePath);
    

    Game.Connect();

    Clock clock;

    float speed = 0.1;
    float angle = 0;
    float CueHitDistance = 0;


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
       // std::cout << time << "mks" << std::endl;
        clock.restart();
        time /= GAME_SPEED;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }        
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

        if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::LShift)
        {
            speed = 0.5;
        }

        if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::LShift)
        {
            speed = 0.1;
        }


        

        
        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            Vector2i MousePosition = Mouse::getPosition(window);
            if (Game.IsHitPanelActive(Vector2f(MousePosition.x,MousePosition.y)) && Game.GameState == PREPARE)
            {
                Game.SetCueIsHit(true);
                Game.SetHitPowerPanelIsUpdate(true);
                Game.SetCueHitDistance(MousePosition.y - Game.GetHitPowerPanelTopPoint());
                Game.SetCueHitPower(Game.GetCueHitDistance() / Game.GetHitPowerPanelHeight() * MAX_CUE_POWER);
            }
            else if( Game.GameState == MAINBALL_RESET)
            {
                Game.GetMainBall()->SetPosition(Vector2f(MousePosition.x,MousePosition.y));
            }
        }

        if (Mouse::isButtonPressed(Mouse::Button::Right) && Game.GameState == MAINBALL_RESET)
        {
             Game.GameState = PREPARE;
        }


        if (Keyboard::isKeyPressed(Keyboard::Space) && Game.GameState == PREPARE)
        {
            Game.GameState = HIT_PHASE;
            Game.CueHit();
        }


        window.clear();
        Game.Update(time);
        Game.Draw(window);
        window.display();
    }

    return 0;
}