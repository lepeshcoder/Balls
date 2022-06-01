#include "include.h"
#include "Ball.h"
#include "Game.h"


/*
    ToDo LIST:
    1) Обработать попадание шаров в лунку (Немного поправить)
    2) Сеть
    3) Прицел 
*/


int main()
{
    setlocale(LC_ALL, "RUS");
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Bil'yard!");

   

    sf::Music music;
    music.openFromFile("..\\Music\\music.ogg");
    music.setPitch(0.5);
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

    
    

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
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


        if (Game.Hit == MY_HIT)
        {

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                Game.RotateCue(CLOCKWISE);
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                Game.RotateCue(COUNTERCLOCKWISE);
            }

            if (event.type == Event::EventType::KeyPressed && event.key.code == Keyboard::LShift)
            {
                Game.CueSpeedUp();
            }

            if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::LShift)
            {
                Game.CueSpeedDown();
            }





            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                Vector2i MousePosition = Mouse::getPosition(window);
                if (Game.IsHitPanelActive(Vector2f(MousePosition.x, MousePosition.y)) && Game.GameState == PREPARE)
                {
                    Game.SetCueIsHit(true);
                    Game.SetHitPowerPanelIsUpdate(true);
                    Game.SetCueHitDistance(MousePosition.y - Game.GetHitPowerPanelTopPoint());
                    Game.SetCueHitPower(Game.GetCueHitDistance() / Game.GetHitPowerPanelHeight() * MAX_CUE_POWER);
                }
                else if (Game.GameState == MAINBALL_RESET)
                {
                    Game.GetMainBall()->SetPosition(Vector2f(MousePosition.x, MousePosition.y));
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

            Packet data;
            unsigned char type = PACKET_TYPES::SERVER_PREPARE;
            data.append((void*)&type, sizeof(unsigned char));
            float angle = Game.GetCueAngle();
            data.append((void*)&angle, sizeof(float));
            float Tempdistance = Game.GetCueHitDistance();
            data.append((void*)&Tempdistance, sizeof(float));
            float Tempspeed = Game.GetMainBall()->GetSpeed();
            data.append((void*)&Tempspeed, sizeof(float));
            Game.Socket.send(data, Game.RemoteIp, Game.RemotePort);
            



        }
        else if (Game.Hit == OPPONENT_HIT)
        {

        }


        window.clear();
        Game.Update(time);
        Game.Draw(window);
        window.display();
    }

    return 0;
}