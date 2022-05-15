#include"Cue.h"


Cue::Cue()
{
	this->angle = 0;
	this->CueSprite = new Sprite();
	this->CueTexture = new Texture();
	this->HitPower = 0;
	this->IsHit = false;
	this->Position = Vector2f(0, 0);
}

Cue::Cue(std::string CueTexturePath)
{
	CueTexture = new Texture();
	CueTexture->loadFromFile(CueTexturePath);
	CueSprite = new Sprite();
	CueSprite->setTexture(*CueTexture);
	CueSprite->setOrigin(CueTexture->getSize().x + BALL_RADIUS + 1, CueTexture->getSize().y / 2.0);
	angle = 0;
	HitPower = 0;
	angle = 0;
}

Cue::~Cue()
{
	delete CueTexture;
	delete CueSprite;
}

void Cue::Draw(sf::RenderWindow& window)
{
	window.draw(*CueSprite);
}


void Cue::SetAngle(float Angle)
{
	this->angle = (int(Angle) % 360 < 0) ? (360 + Angle) : (int(Angle) % 360);
	CueSprite->setRotation(angle);
}

float Cue::GetAngle()
{
	return angle;
}

void Cue::SetPosition(Vector2f Position)
{
	CueSprite->setPosition(Position);	
	this->Position = Position;
}

void Cue::Update(float distance)
{
	if (IsHit)
	{
		CueSprite->setOrigin(CueTexture->getSize().x + BALL_RADIUS + distance / 2, CueTexture->getSize().y / 2.0);
		IsHit = false;
	}
}

void Cue::SetIsHit(bool IsHit)
{
	this->IsHit = IsHit;
}

bool Cue::GetIsHit()
{
	return IsHit;
}

void Cue::SetHitPower(float HitPower)
{
	this->HitPower = HitPower;
}

float Cue::GetHitPower()
{
	return HitPower;
}

void Cue::Hit()
{
	CueSprite->setOrigin(CueTexture->getSize().x + BALL_RADIUS + 1, CueTexture->getSize().y / 2.0);
}
