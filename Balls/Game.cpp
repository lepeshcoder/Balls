#include "Game.h"

Game::Game(sf::RenderWindow& window,std::string CueTexturePath, std::string TableTexturePath,std::string MainBallTexturePath, std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath)
{
	GameState = START;
	cue = new Cue(CueTexturePath);
	table = new Table(TableTexturePath, window, FRICTION);
	hitPowerPanel = new HitPowerPanel(HitPowerPanelTexturePath, HitPowerCueTexturePath);
	MainBall = nullptr;
	MyScore = OpponentScore = 0;
	Ballsleft = 15;
	TextFont.loadFromFile("..\\Fonts\\impact2.ttf");
	MyScoreText.setFont(TextFont);
	MyScoreText.setString("My Score: " + std::to_string(MyScore));
	MyScoreText.setPosition(400, 10);
	MyScoreText.setFillColor(Color::Red);
	OpponentScoreText.setFont(TextFont);
	OpponentScoreText.setString("Opponent Score: " + std::to_string(OpponentScore));
	OpponentScoreText.setPosition(1000, 10);
	OpponentScoreText.setFillColor(Color::Red);

}

Game::~Game()
{
	delete cue;
	delete MainBall;
	delete table;
	delete hitPowerPanel;
}


void Game::Draw(sf::RenderWindow& window)
{
	table->Draw(window);
	for (auto& i : Balls) i.Draw(window);
	cue->Draw(window);
	hitPowerPanel->Draw(window);
	window.draw(MyScoreText);
	window.draw(OpponentScoreText);
}

void Game::AddBall(Ball ball)
{
	Balls.push_back(ball);
}

void Game::SetFriction(float Friction)
{
	table->SetFriction(Friction);
}

void Game::SetCueAngle(float Angle)
{
	cue->SetAngle(Angle);
}

void Game::SetCueIsHit(bool IsHit)
{
	cue->SetIsHit(IsHit);
}

void Game::SetCueHitPower(float power)
{
	this->cue->SetHitPower(power);
}

bool Game::GetCueIsHit()
{
	return cue->GetIsHit();
}

void Game::SetCuePosition(Vector2f Position)
{
	cue->SetPosition(Position);
}

std::vector<Vector2f> Game::GetBallsCentres()
{
	std::vector<Vector2f> Centres;
	for (auto& i : Balls) Centres.push_back(i.GetCentre());
	return Centres;
}

void Game::Initialize(std::string BallTexturePath, std::string MainBallTexturePath)
{
	Vector2f Position(1000, 450);
	float deltaX, deltaY;
	deltaX = 2 * BALL_RADIUS * sin(PI/3); deltaY = 2 * BALL_RADIUS * cos(PI/3);

	AddBall(Ball(Vector2f(650, 450), BALL_RADIUS, MainBallTexturePath));				// Главный мяч
	for (int i = 1; i <= 5; i++)
	{
		Vector2f temp = Position + Vector2f((i - 1) * deltaX, (1 - i) * deltaY);
		for (int j = 1; j <= i; j++)
		{	
			AddBall(Ball(temp, BALL_RADIUS, BallTexturePath));
			temp.y += 2 * BALL_RADIUS;
		}
	}
	MainBall = &Balls[0];
	cue->SetPosition(MainBall->GetCentre());
}

void Game::Update(float time)
{
	switch (Hit)
	{
		case MY_HIT:
		{
			cue->Update(hitPowerPanel->GetCueHitDistance());				 // Обновление позиции кия
			for (auto& i : Balls) i.Update(time, FRICTION);					 // Обновление позиции шаров 
			CheckBallsInPockets();											 // Проверка на попадания мячиков в лузы
			PerformColiderCollision(table->GetColider());					 // Обработка коллизий с колайдером(столом)
			PerformStaticCollisisons();										 // Обработка статических коллизий между шариками
			PerformDynamicCollision();										 // Обработка динамических коллизий
			for (auto& i : Balls) i.UpdateCentre();							 // Обновляем позиции спрайтов
			hitPowerPanel->Update(hitPowerPanel->GetCueHitDistance());		 // Обновление позиции Кия на панели силы удара
			if (IsHitEnded())												 // Когда удар заканчивается 
			{
				cue->SetPosition(MainBall->GetCentre());					 // Устанавливаем кий к главному шару
				if (GameState == HIT_PHASE)
				{
					Hit = ((Hit == MY_HIT) ? OPPONENT_HIT : MY_HIT);		 // Передаем очередь хода		
					GameState = PREPARE;                                     // Устанавливаем подготовку
				}
			}
			break;
		}
		case OPPONENT_HIT:
		{
			Packet packet;
			IpAddress IP; unsigned short port;
			Socket.receive(packet, IP, port);
			
			float* begin = (float*) (((unsigned char*)packet.getData()) + sizeof(unsigned char));
			float angle = begin[0];
			float distance = begin[1];
			float speed = begin[2];

			cue->SetAngle(angle);
			cue->SetSpeed(speed);
			cue->Update(distance);				 // Обновление позиции кия
			for (auto& i : Balls) i.Update(time, FRICTION);					 // Обновление позиции шаров 
			CheckBallsInPockets();											 // Проверка на попадания мячиков в лузы
			PerformColiderCollision(table->GetColider());					 // Обработка коллизий с колайдером(столом)
			PerformStaticCollisisons();										 // Обработка статических коллизий между шариками
			PerformDynamicCollision();										 // Обработка динамических коллизий
			for (auto& i : Balls) i.UpdateCentre();							 // Обновляем позиции спрайтов
			hitPowerPanel->Update(distance);		 // Обновление позиции Кия на панели силы удара
			if (IsHitEnded())												 // Когда удар заканчивается 
			{
				cue->SetPosition(MainBall->GetCentre());					 // Устанавливаем кий к главному шару
				if (GameState == HIT_PHASE)
				{
					Hit = ((Hit == MY_HIT) ? OPPONENT_HIT : MY_HIT);		 // Передаем очередь хода		
					GameState = PREPARE;                                     // Устанавливаем подготовку
				}
			}
			
			break;
		}
	}
	

	std::cout << "Gamestate: " << GameState << "  Hit: " << Hit << "  score: " << MyScore << " : " << OpponentScore << std::endl;
}

void Game::CueHit()
{
	cue->Hit();                                                // Возвращение кия к шару
	cue->Hide();											   // Делает кий невидимым до конца удара
	hitPowerPanel->ResetCuePosition();                         // Возвращения кия на Панели силы удара в исходное положение
	MainBall->SetSpeed(cue->GetHitPower());                    // Задание начальной скорости Шару
	MainBall->ChangeDir(cue->GetAngle());                      // Передача ему угла
}

bool Game::IsHitPanelActive(Vector2f Point)
{
	return hitPowerPanel->IsPanelActive(Point);
}

float Game::GetHitPowerPanelTopPoint()
{
	return hitPowerPanel->GetTopPoint();
}

float Game::GetHitPowerPanelHeight()
{
	return hitPowerPanel->GetHeight();
}

void Game::SetHitPowerPanelIsUpdate(bool IsUpdate)
{
	hitPowerPanel->SetIsUpdate(IsUpdate);
}

void Game::PerformStaticCollisisons()
{
	for (int i = 0; i < Balls.size(); i++)
		for (int j = i + 1; j < Balls.size(); j++)
			if (Balls[i].ProcessingStaticCollision(Balls[j]))
				CollissionPairs.push_back(std::make_pair(&Balls[i], &Balls[j]));
}

void Game::PerformColiderCollision(std::vector<LINE> &Colider)
{
	for (auto& i : Balls) i.ColiderCollisison(Colider);
}

void Game::SetCueHitDistance(float CueHitDistance)
{
	this->hitPowerPanel->SetCueHitDistance(CueHitDistance);
}

float Game::GetCueHitDistance()
{
	return hitPowerPanel->GetCueHitDistance();
}

bool Game::IsHitEnded()
{
	for (auto& i : Balls) if (i.GetSpeed()) return false;
	return true;
}

void Game::PerformDynamicCollision()
{
	for (auto& i : CollissionPairs) i.first->DynamicCollision(*(i.second));
	CollissionPairs.clear();
}

Ball* Game::GetMainBall()
{
	return MainBall;
}

bool Game::IsBallInPocket(Ball& ball)
{
	return table->IsBallInPockets(ball.GetCentre());
}

void Game::CheckBallsInPockets()
{
	for (auto& i : Balls) 
	{
		if (IsBallInPocket(i))
		{
			i.Hide();
			i.SetSpeed(0);
			if (&i != MainBall)
			{
				(GameState == MY_HIT) ? MyScore++ : OpponentScore++;
			}
			else
			{
				(GameState == MY_HIT) ? MyScore = 0 : OpponentScore = 0;
				GameState = MAINBALL_RESET;
				Ballsleft--;
			}
		}
	}
	MyScoreText.setString("My Score: " + std::to_string(MyScore));
	OpponentScoreText.setString("Opponent Score: " + std::to_string(OpponentScore));
	if (Ballsleft == 0) GameState = END;
}

void Game::Connect()
{

	GameState = CONNECT;
	
	unsigned short LocalPort;
	std::cout << "Enter IP Addres: "; std::cin >> RemoteIp;
	std::cout << "\nEnter Remote Port: "; std::cin >> RemotePort;
	std::cout << "\nEnter Local Port: "; std::cin >> LocalPort;
	Socket.bind(LocalPort);

	Packet SendData;
	unsigned char type = PACKET_TYPES::SERVER_CONNECT;
	SendData.append((void*)&type, 1);
	Socket.send(SendData, RemoteIp, RemotePort);

	Packet ReceiveData;
	IpAddress serverIp;
	unsigned short serverPort;
	Socket.receive(ReceiveData,serverIp,serverPort);
	if (((unsigned char*)ReceiveData.getData())[0] == 1)
	{
		Hit = MY_HIT;
		std::cout << "RECEIVE 1" << std::endl;
	}
	else 
	{
		Hit = OPPONENT_HIT;
		std::cout << "Receive 2" << std::endl;
	}

	GameState = PREPARE;
}

void Game::SendData(sf::Packet& packet)
{
	Socket.send(packet, RemoteIp, RemotePort);
}

Packet Game::ReceiveData()
{
	Packet packet;
	IpAddress addr; unsigned short port;
	Socket.receive(packet, addr, port);
	return packet;
}

void Game::RotateCue(Direction dir)
{
	cue->Rotate(dir);
}

void Game::CueSpeedUp()
{
	cue->CueAngleSpeedUp();
}

void Game::CueSpeedDown()
{
	cue->CueAngleSpeedDown();
}

float Game::GetCueAngle()
{
	return cue->GetfloatAngle();
}

void Game::SetCueAngleSpeed(float speed)
{
	cue->SetSpeed(speed);
}

UdpSocket& Game::GetSocket()
{
	return this->Socket;
}
