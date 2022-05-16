#pragma once
#include "include.h"
class Table
{

private:

	Texture* TableTexture;

	Sprite* TableSprite;

	float Friction;

	Rect<float> Colider;


public:

	Table();

	Table(std::string TableTexturePath, sf::RenderWindow& window, float Friction = 0);

	void Draw(sf::RenderWindow& window);

	void SetFriction(float Friction);

	 Rect<float>& GetColider();
	
	~Table();


	
	

};

