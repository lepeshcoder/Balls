#include"Cue.h"

Cue::Cue()
{
}

Cue::Cue(sf::Texture& Texture)
{
	CueSprite.setTexture(Texture);
	CueSprite.setScale(0.5,0.5);
	CueSprite.setPosition(450,450);
	CueSprite.setRotation(0);
	Position = Vector2f(450, 450);
	HitPower = 0;
	angle = 0;
}

void Cue::Draw(sf::RenderWindow& window)
{
	window.draw(CueSprite);
}
