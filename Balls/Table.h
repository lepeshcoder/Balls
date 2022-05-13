#pragma once
#include "include.h"
class Table
{

private:

	Sprite TableSprite;


public:

	Table();

	Table(Texture& Texture,sf::RenderWindow& window);

	void Draw(sf::RenderWindow& window);

	void SetTexture(Texture& Texture, sf::RenderWindow& window);

};

