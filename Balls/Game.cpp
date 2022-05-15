#include "Game.h"

Game::Game(sf::RenderWindow& window,std::string CueTexturePath, std::string TableTexturePath,std::string MainBallTexturePath, std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath)
{
	GameState = START;
	cue = new Cue(CueTexturePath);
	MainBall = new Ball(Vector2f(650, 450), BALL_RADIUS, MainBallTexturePath);
	table = new Table(TableTexturePath, window, FRICTION);
	hitPowerPanel = new HitPowerPanel(HitPowerPanelTexturePath, HitPowerCueTexturePath);
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
	MainBall->Draw(window);
	for (int i = 0; i < Balls.size(); i++) Balls[i].Draw(window);
	cue->Draw(window);
	hitPowerPanel->Draw(window);
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

void Game::Initialize(std::string BallTexturePath)
{
	Vector2f Position(1000, 450);
	float deltaX, deltaY;
	deltaX = 2 * BALL_RADIUS * sin(PI/3); deltaY = 2 * BALL_RADIUS * cos(PI/3);
	
	for (int i = 1; i <= 5 ; i++)
	{
		Vector2f temp = Position + Vector2f((i - 1) * deltaX, (1 - i) * deltaY);
		for (int j = 1; j <= i; j++)
		{	
			AddBall(Ball(temp, BALL_RADIUS, BallTexturePath));
			temp.y += 2 * BALL_RADIUS;
		}
	}
	cue->SetPosition(MainBall->GetCentre());
}

void Game::Update(float time, float CueHitDistance)
{
	std::cout << cue->GetAngle() << std::endl;
	cue->Update(CueHitDistance);
	MainBall->Update(time, FRICTION);
	for (auto& i : Balls) i.Update(time, FRICTION);
	hitPowerPanel->Update(CueHitDistance);
}

void Game::CueHit()
{
	cue->Hit();
	hitPowerPanel->ResetCuePosition();
	MainBall->SetSpeed(cue->GetHitPower());
	MainBall->ChangeDir(cue->GetAngle());
	MainBall->SetIsMove(true);
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
