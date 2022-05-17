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
	if (distance + 0.01 < Radius + OtherBall.Radius) // Если произошло наложение
	{
		float temp = Radius + OtherBall.Radius - distance; // Расстояние наложения
		Centre += Vector2f(-temp / 2 * abs(cos(Angle * PI / 180)), 0);// temp / 2 * sin(Angle * PI / 180));
		BallSprite->setPosition(Centre);
		OtherBall.Centre += Vector2f(temp / 2 * abs(cos(OtherBall.Angle * PI / 180)), 0); // temp / 2 * sin(OtherBall.Angle * PI / 180));
		OtherBall.BallSprite->setPosition(OtherBall.Centre);	
	}
	else return;
}


void Ball::ChangeDir(float angle)
{ 
	this->Angle = angle;
	if (Angle > 359) Angle -= 360;
	if (Angle < 0) Angle += 360;
	std::cout << "Переданый угол шару от Кия: " << Angle << std::endl;
}

void Ball::ColiderCollisison(Rect<float> &Colider)
{
	if (Centre.x - Radius < Colider.left)
	{
		float distance = abs(Colider.left - (Centre.x - Radius));
		Centre += Vector2f(distance * abs(cos(Angle * PI / 180)), distance * sin(Angle * PI / 180));
		BallSprite->move(Vector2f(distance * abs(cos(Angle * PI / 180)), distance * sin(Angle * PI / 180)));
		ChangeDir(180 - Angle);

	}
	else if (Centre.x + Radius > Colider.left + Colider.width)
	{
		float distance = abs((Colider.left + Colider.width) - (Centre.x + Radius));
		Centre += Vector2f(-distance * abs(cos(Angle * PI / 180)), distance * sin(Angle * PI / 180));
		BallSprite->move(Vector2f(-distance * abs(cos(Angle * PI / 180)), distance * sin(Angle * PI / 180)));
		ChangeDir(180 - Angle);
	}
	else if (Centre.y - Radius < Colider.top)
	{
		float distance = abs(Colider.top - (Centre.y - Radius));
		Centre += Vector2f(distance * cos(Angle * PI / 180), distance * abs(sin(Angle * PI / 180)));
		BallSprite->move(Vector2f(distance * cos(Angle * PI / 180), distance * abs(sin(Angle * PI / 180))));
		ChangeDir(360 - Angle);

	}
	else if (Centre.y + Radius > Colider.top + Colider.height)
	{
		float distance = abs((Centre.y + Radius) - (Colider.top + Colider.height));
		Centre += Vector2f(distance * cos(Angle * PI / 180), -distance * abs(sin(Angle * PI / 180)));
		BallSprite->move(Vector2f(distance * cos(Angle * PI / 180), -distance * abs(sin(Angle * PI / 180))));
		ChangeDir(360 - Angle);
	}
}












