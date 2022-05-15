#pragma once
#include "include.h"
#include "Ball.h"
#include "Table.h"
#include "Cue.h"
#include "HitPowerPanel.h"
class Game
{

private:

	Ball* MainBall;

	std::vector<Ball> Balls;

	Table* table;

	Cue* cue;

	GameStates GameState;

	HitPowerPanel* hitPowerPanel;

	
public:

	Game(sf::RenderWindow& window, std::string CueTexturePath, std::string TableTexturePath, std::string MainBallTexturePath, std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath);

	~Game();

	void Draw(sf::RenderWindow& window);
	
	void AddBall(Ball ball);

	void SetFriction(float Friction);

	void SetCueAngle(float Angle);

	void SetCueIsHit(bool IsHit);

	void SetCueHitPower(float power);

	bool GetCueIsHit();
	
	// ������������� ��� ������ � ���� � ������� � �������� �����
	void SetCuePosition(Vector2f Position);

	// ���������� ������ ������� ����� 
	std::vector<Vector2f> GetBallsCentres();

	// ������������ ����
	void Initialize(std::string BallTexturePath);

	// ���������� ����
	void Update(float time,float CueHitDistance);

	void CueHit();

	bool IsHitPanelActive(Vector2f Point);
	
	float GetHitPowerPanelTopPoint();

	float GetHitPowerPanelHeight();

	void SetHitPowerPanelIsUpdate(bool IsUpdate);

};

