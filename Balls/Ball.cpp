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

Ball::Ball(const Ball &other)
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
	Angle = other.Angle;
	Speed = other.Speed;
}

void Ball::Update(float time,float friction)
{
	if (IsMove)
	{
		float dx = cos(Angle * PI / 180) * Speed * time;
		float dy = -sin(Angle * PI / 180) * Speed * time;
		Centre += Vector2f(dx, dy);
		BallSprite->move(Vector2f(dx,dy));
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

void Ball::ProcessingStaticCollision(Ball& OtherBall)
{
	// Расстояние между центрами шаров
	float distance = sqrt(pow(Centre.x - OtherBall.Centre.x, 2) + pow(Centre.y - OtherBall.Centre.y, 2)); 
	if (distance + 0.001 < Radius + OtherBall.Radius) // Если произошло наложение
	{
		float temp = (Radius + OtherBall.Radius - distance); // Расстояние наложения
		float DeltaX = temp * abs(Centre.x - OtherBall.Centre.x) / (2 * distance);
		float DeltaY = temp * abs(Centre.y - OtherBall.Centre.y) / (2 * distance);
		Vector2f Delta;
		if (Centre.x < OtherBall.Centre.x)
		{
			Delta.x = -DeltaX;
			if (Centre.y < OtherBall.Centre.y)Delta.y = -DeltaY;
			else Delta.y = DeltaY;
		}
		else
		{
			Delta.x = DeltaX;
			if (Centre.y < OtherBall.Centre.y) Delta.y = -DeltaY;
			else Delta.y = DeltaY;
		}
		Centre += Delta;
		OtherBall.Centre -= Delta;
		BallSprite->setPosition(Centre);
		OtherBall.BallSprite->setPosition(OtherBall.Centre);
	}
	else return;
}


void Ball::ChangeDir(float angle)
{ 
	this->Angle = angle;
	if (Angle > 359) Angle -= 360;
	if (Angle < 0) Angle += 360;
	//std::cout << "Переданый угол шару от Кия: " << Angle << std::endl;
}

void Ball::ColiderCollisison(Rect<float> &Colider)
{
	if (Centre.x - Radius < Colider.left)
	{
		Centre.x = Colider.left + Radius;
		BallSprite->setPosition(Centre);
		ChangeDir(180 - Angle);
		Speed *= 0.8;
	}
	else if (Centre.x + Radius > Colider.left + Colider.width)
	{
		Centre.x = Colider.left + Colider.width - Radius;
		BallSprite->setPosition(Centre);
		ChangeDir(180 - Angle);
		Speed *= 0.8;
	}
	else if (Centre.y - Radius < Colider.top)
	{
		Centre.y = Colider.top + Radius;
		BallSprite->setPosition(Centre);
		ChangeDir(360 - Angle);
		Speed *= 0.8;
	}
	else if (Centre.y + Radius > Colider.top + Colider.height)
	{
		Centre.y = Colider.top + Colider.height - Radius;
		BallSprite->setPosition(Centre);
		ChangeDir(360 - Angle);
		Speed *= 0.8;
	}
}












