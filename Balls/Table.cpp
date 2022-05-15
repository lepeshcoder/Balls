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
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(*TableSprite);
}


void Table::SetFriction(float Friction)
{
	this->Friction = Friction;
}

Table::~Table()
{
	delete TableTexture;
	delete TableSprite;
}
