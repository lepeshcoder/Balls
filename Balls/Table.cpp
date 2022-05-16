#include "Table.h"



Table::Table()
{
	TableTexture = new Texture();
	TableSprite = new Sprite();
	Friction = 0;
	Colider = Rect<float>(0, 0, 0, 0);
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
	Colider = Rect<float>(136, 128, 1461 - 136, 770 - 128);
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(*TableSprite);
}


void Table::SetFriction(float Friction)
{
	this->Friction = Friction;
}

Rect<float>& Table::GetColider()
{
	return Colider;
}

Table::~Table()
{
	delete TableTexture;
	delete TableSprite;
}
