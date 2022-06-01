#include"Cue.h"


Cue::Cue()
{
	angle = 0;
	CueSprite = new Sprite();
	CueTexture = new Texture();
	HitPower = 0;
	IsHit = false;
	Position = Vector2f(0, 0);
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
	CueAngleSpeed = 0.1;
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
	this->angle = Angle;
	while (angle > 359) angle -= 360;
	while (angle < 0) angle += 360;
	CueSprite->setRotation(angle);
}

Vector2f Cue::GetAngle()
{
	return Vector2f(cos(angle * PI / 180), sin(angle * PI / 180));
}

float Cue::GetfloatAngle()
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
	SetAngle(angle);
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

void Cue::Hide()
{
	CueSprite->setPosition(10000, 10000);
}

void Cue::Rotate(Direction dir)
{
	angle += ((dir == CLOCKWISE) ? CueAngleSpeed : -CueAngleSpeed);
}

void Cue::CueAngleSpeedUp()
{
	this->CueAngleSpeed = 0.5;
}

void Cue::CueAngleSpeedDown()
{
	this->CueAngleSpeed = 0.1;
}

void Cue::SetSpeed(float speed)
{
	this->CueAngleSpeed = speed;
}
