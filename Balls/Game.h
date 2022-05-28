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

	HitPowerPanel* hitPowerPanel;

	std::vector<std::pair<Ball*, Ball*>> CollissionPairs;

	
public:

	GameStates GameState;

	Game(sf::RenderWindow& window, std::string CueTexturePath, std::string TableTexturePath, std::string MainBallTexturePath, std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath);

	~Game();

	void Draw(sf::RenderWindow& window);
	
	void AddBall(Ball ball);

	void SetFriction(float Friction);

	void SetCueAngle(float Angle);

	void SetCueIsHit(bool IsHit);

	void SetCueHitPower(float power);

	bool GetCueIsHit();
	
	// Устанавливает кий бойком к шару с центров в заданной точке
	void SetCuePosition(Vector2f Position);

	// Возвращает список центров шаров 
	std::vector<Vector2f> GetBallsCentres();

	// Инициализция Игры
	void Initialize(std::string BallTexturePath);

	// Обновление Игры
	void Update(float time);

	void CueHit();

	bool IsHitPanelActive(Vector2f Point);
	
	float GetHitPowerPanelTopPoint();

	float GetHitPowerPanelHeight();

	void SetHitPowerPanelIsUpdate(bool IsUpdate);

	void PerformStaticCollisisons();

	void PerformColiderCollision(Rect<float> &Colider);

	void SetCueHitDistance(float CueHitDistance);

	float GetCueHitDistance();

	bool IsHitEnded();

	void PerformDynamicCollision();

	Ball* GetMainBall();

};

