#include "Table.h"



Table::Table()
{
	TableTexture = new Texture();
	TableSprite = new Sprite();
	Friction = 0;
}

Table::Table(std::string TableTexturePath, sf::RenderWindow& window, float Friction)
{
	TableTexture = new Texture();
	TableTexture->loadFromFile(TableTexturePath);
	TableSprite = new Sprite(*TableTexture);
	TableSprite->setTexture(*TableTexture);
	TableSprite->setPosition(Vector2f(0, 0));
	TableSprite->setScale(float(window.getSize().x) / TableTexture->getSize().x, float(window.getSize().y) / TableTexture->getSize().y);
	this->Friction = Friction;
	/*
	*  . - . - .
 	* |        |
	*  . - . - .
 	*/
	colider.push_back(LINE(std::make_pair(Vector2f(168,130), Vector2f(775,130))));
	colider.push_back(LINE(std::make_pair(Vector2f(823,130), Vector2f(1432,130))));
	colider.push_back(LINE(std::make_pair(Vector2f(1465,163), Vector2f(1465,742))));
	colider.push_back(LINE(std::make_pair(Vector2f(168,770), Vector2f(775,770))));
	colider.push_back(LINE(std::make_pair(Vector2f(823,770), Vector2f(1432,770))));
	colider.push_back(LINE(std::make_pair(Vector2f(135,163), Vector2f(135,742))));
	
	pockets.push_back(Vector2f(129,120));
	pockets.push_back(Vector2f(129,776));
	pockets.push_back(Vector2f(799,105));
	pockets.push_back(Vector2f(799,793));
	pockets.push_back(Vector2f(1470,122));
	pockets.push_back(Vector2f(1470,778));
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(*TableSprite);
}


void Table::SetFriction(float Friction)
{
	this->Friction = Friction;
}

std::vector<LINE>& Table::GetColider()
{
	return colider;
}

bool Table::IsBallInPockets(Vector2f BallCentre)
{
	for (auto& i : pockets)
	{
		float distance = sqrt(pow(BallCentre.x - i.x, 2) + pow(BallCentre.y - i.y, 2));
		if (distance < BALL_RADIUS + 0.1) return true;
	}
	return false;	
}

Table::~Table()
{
	delete TableTexture;
	delete TableSprite;
}
