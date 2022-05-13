#include "Table.h"

Table::Table()
{
}

Table::Table(Texture& Texture, sf::RenderWindow& window)
{
	
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(TableSprite);
}

void Table::SetTexture(Texture& Texture, sf::RenderWindow& window)
{
	TableSprite.setTexture(Texture);
	TableSprite.setScale(float(window.getSize().x) / Texture.getSize().x, float(window.getSize().y) / Texture.getSize().y);
}
