#pragma once
#include "include.h"
#include "Ball.h"
#include "Table.h"
#include "Cue.h"
class Game
{

private:

	std::vector<Ball> Balls;

	Table table;

	Cue cue;

	GameStates GameState;

	


public:

	Game(sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window);
	
	void AddBall(Ball ball);



};

