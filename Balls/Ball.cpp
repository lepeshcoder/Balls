#include"Ball.h"

Ball::Ball(Vector2f Centre, float Radius, std::string TexturePath)
{
	//std::cout << "Вызвался конструктор c параметрами обьекта " << this << std::endl;
	this->Centre = Centre;
	this->Radius = Radius;
	Speed = 0;
	SpeedVector = Vector2f(0, 0);
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
	Radius = 0;
	Speed = 0;
	SpeedVector = Vector2f(0, 0);
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
	Radius = other.Radius;
	SpeedVector = other.SpeedVector;
	Speed = other.Speed;
}

void Ball::Update(float time,float friction)
{
	Vector2f Delta = SpeedVector * Speed * time;
	Centre += Delta;																																														
	if (Speed > friction) Speed -= friction * time;
	else Speed = 0;
}

void Ball::SetSpeed(float Speed)
{
	this->Speed = Speed;
}

Vector2f Ball::GetCentre()
{
	return Centre;
}

void Ball::ProcessingStaticCollision(Ball& OtherBall)
{
	float distance = sqrt(pow(Centre.x - OtherBall.Centre.x, 2) + pow(Centre.y - OtherBall.Centre.y, 2)); // Расстояние между центрами шаров
	if (distance < Radius + OtherBall.Radius) // Если произошло наложение
	{
		float temp = (distance - Radius - OtherBall.Radius) / 2; // Расстояние наложения пополам
		Centre -= Vector2f(Centre.x - OtherBall.Centre.x, Centre.y - OtherBall.Centre.y) * temp / distance;
		OtherBall.Centre += Vector2f(Centre.x - OtherBall.Centre.x, Centre.y - OtherBall.Centre.y) * temp / distance;
		DynamicCollision(OtherBall);
	}
	else return;
}

void Ball::NormalizeSpeedVector()
{
	float modul = sqrt(pow(SpeedVector.x, 2) + pow(SpeedVector.y, 2));
	SpeedVector /= modul;
}

float Ball::GetSpeed()
{
	return Speed;
}

void Ball::UpdateCentre()
{
	BallSprite->setPosition(Centre);
}



void Ball::DynamicCollision(Ball& other) 
{
	float u1x = SpeedVector.x * Speed;
	float u1y = SpeedVector.y * Speed;
	float u2x = SpeedVector.x * Speed;
	float u2y = SpeedVector.x * Speed;
	float U1x = u1x * u2x / (u1x + u2x);
	float U1y = u1y * u2y / (u1y + u2y);
	float U2x = u1x + u2x - U1x;
	float U2y = u1y + u2y - U1y;
	ChangeDir(Vector2f(U1x, U1y));
	other.ChangeDir(Vector2f(U2x, U2y));
	Speed /= 2;
	other.Speed = Speed;
}






void Ball::ChangeDir(Vector2f SpeedVector)
{ 
	this->SpeedVector = SpeedVector;
	NormalizeSpeedVector();
}

void Ball::ColiderCollisison(Rect<float> &Colider)
{
	if (Centre.x - Radius < Colider.left)
	{
		Centre.x = Colider.left + Radius;
		SpeedVector.x *= -1;
		Speed *= 0.8;

	}
	else if (Centre.x + Radius > Colider.left + Colider.width)
	{
		Centre.x = Colider.left + Colider.width - Radius;
		SpeedVector.x *= -1;
		Speed *= 0.8;
	}
	else if (Centre.y - Radius < Colider.top)
	{
		Centre.y = Colider.top + Radius;
		SpeedVector.y *= -1;
		Speed *= 0.8;
	}
	else if (Centre.y + Radius > Colider.top + Colider.height)
	{
		Centre.y = Colider.top + Colider.height - Radius;
		SpeedVector.y *= -1;
		Speed *= 0.8;
	}

}












