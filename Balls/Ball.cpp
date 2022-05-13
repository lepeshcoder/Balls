#include"Ball.h"

Ball::Ball(Vector2f Centre, float Radius, sf::Texture& Texture)
{
	this->Centre = Centre;
	this->Radius = Radius;
	this->Speed = 0;
	this->SpeedVector = Vector2f(0, 0);
	IsMove = false;
	BallSprite.setTexture(Texture);
	BallSprite.setPosition(Centre - Vector2f(Radius,Radius));
	BallSprite.setScale(40 / 561.0, 40 / 561.0);
}



void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(BallSprite);
}

void Ball::Update(float time,float friction)
{
	if (IsMove)
	{
		float dx = SpeedVector.x * Speed * time;
		float dy = SpeedVector.y * Speed * time;
		Centre += Vector2f(dx, dy);
		BallSprite.move(Vector2f(dx, dy));
		std::cout << Speed << std::endl;
		if (Speed > friction) Speed -= friction * time;
		else
		{
			Speed = 0;
			IsMove = false;
		}
	}
}

void Ball::SetSpeed(float Speed)
{
	this->Speed = Speed;
}

void Ball::SetIsMove(bool IsMove)
{
	this->IsMove = IsMove;
}

void Ball::ChangeDir(Vector2f SpeedVector)
{ 
	float modul = sqrt(SpeedVector.x * SpeedVector.x + SpeedVector.y * SpeedVector.y);
	this->SpeedVector = Vector2f(SpeedVector.x / modul, SpeedVector.y / modul);
}












