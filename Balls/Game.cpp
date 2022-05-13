#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
	GameState = START;
	Texture TableTexture;
	TableTexture.loadFromFile("..\\Graphics\\Table.png");
	table.SetTexture(TableTexture,window);
	//this->table = Table(TableTexture, window);
	Texture CueTexture;
	CueTexture.loadFromFile("..\\Graphics\\Cue.jpg");
	this->cue = Cue(CueTexture);
	Texture BallTexture;
	BallTexture.loadFromFile("..\\Graphics\\Ball.png");
	//this->Balls.push_back(Ball(Vector2f(800, 450), 20, BallTexture));
	
}


void Game::Draw(sf::RenderWindow& window)
{
	table.Draw(window);
	for (auto i : Balls) i.Draw(window);
	cue.Draw(window);
}


