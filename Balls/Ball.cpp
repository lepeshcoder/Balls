#include"Ball.h"

Ball::Ball(Vector2f Centre = Vector2f(0, 0), float Radius = 0, Color color = Color::Red)
{
	this->Centre = Centre;
	this->Radius = Radius;
	this->Speed = 0;
	this->SpeedVector = Vector2f(0, 0);
	IsMove = false;
	GraphicBall.setPosition(Centre - Vector2f(Radius,Radius));
	GraphicBall.setRadius(Radius);
	GraphicBall.setFillColor(color);
}

void Ball::SetTexture(sf::Texture Texture)
{
	this->Texture = Texture;
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(GraphicBall);
}

void Ball::Update(float time,float friction)
{
	if (IsMove)
	{
		float dx = SpeedVector.x * Speed * time;
		float dy = SpeedVector.y * Speed * time;
		Centre += Vector2f(dx, dy);
		GraphicBall.move(Vector2f(dx, dy));
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
	this->SpeedVector = SpeedVector;
}












