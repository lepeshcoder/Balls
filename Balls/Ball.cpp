#include"Ball.h"

Ball::Ball(Vector2f Centre, float Radius, std::string TexturePath)
{
	//std::cout << "Вызвался конструктор c параметрами обьекта " << this << std::endl;
	this->Centre = Centre;
	this->Radius = Radius;
	Speed = 0;
	Angle = 0;
	IsMove = false;
	BallTexture = new Texture();
	BallTexture->loadFromFile(TexturePath);
	BallSprite = new Sprite();
	BallSprite->setTexture(*BallTexture);
	BallSprite->setPosition(Centre - Vector2f(Radius,Radius));
	BallSprite->setScale(40 / 561.0, 40 / 561.0);
}



Ball::Ball()
{
	//std::cout << "Вызвался конструктор по умолчанию обьекта " << this << std::endl;
	BallTexture = new Texture();
	BallSprite = new Sprite();
	Centre = Vector2f(0, 0);
	IsMove = false;
	Radius = 0;
	Speed = 0;
	Angle = 0;
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(*BallSprite);
}

Ball::~Ball()
{
	//std::cout << "Вызвался деструктор обьекта " << this << std::endl;
	delete BallTexture;
	delete BallSprite;
}

Ball::Ball(const Ball& other)
{
	//std::cout << "Вызвался конструктор копирования у обьекта " << this << " по обьекту " << &other << std::endl;
	BallTexture = new Texture(*other.BallTexture);
	BallSprite = new Sprite();
	BallSprite->setTexture(*BallTexture);
	BallSprite->setPosition(other.Centre - Vector2f(other.Radius, other.Radius));
	BallSprite->setScale(40 / 561.0, 40 / 561.0);
	Centre = other.Centre;
	IsMove = other.IsMove;
	Radius = other.Radius;
}

void Ball::Update(float time,float friction)
{
	if (IsMove)
	{
		std::cout << "FUNC MAIN BALL UPDATE: ANGLE = " << Angle << std::endl;
		float dx = cos(Angle * PI / 180) * Speed * time;
		float dy = sin(Angle * PI / 180) * Speed * time;
		Centre += Vector2f(dx, dy);
		BallSprite->move(Vector2f(dx, dy));
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

Vector2f Ball::GetCentre()
{
	return Centre;
}

void Ball::ChangeDir(float angle)
{ 
	
	this->Angle = angle;
}












