#pragma once
#include "include.h"
class Table
{

private:

	Texture* TableTexture;

	Sprite* TableSprite;

	float Friction;

	std::vector<Vector2f> pockets;

	std::vector<LINE> colider;

public:

	Table();

	Table(std::string TableTexturePath, sf::RenderWindow& window, float Friction = 0);

	void Draw(sf::RenderWindow& window);

	void SetFriction(float Friction);

	std::vector<LINE>& GetColider();

	bool IsBallInPockets(Vector2f BallCentre);
	
	~Table();


	
	

};

