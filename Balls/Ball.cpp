#include"Ball.h"

Ball::Ball(Vector2f Centre, float Radius, std::string TexturePath)
{
	//std::cout << "�������� ����������� c ����������� ������� " << this << std::endl;
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
	//std::cout << "�������� ����������� �� ��������� ������� " << this << std::endl;
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
	//std::cout << "�������� ���������� ������� " << this << std::endl;
	delete BallTexture;
	delete BallSprite;
}

Ball::Ball(const Ball &other)
{
	//std::cout << "�������� ����������� ����������� � ������� " << this << " �� ������� " << &other << std::endl;
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

bool Ball::ProcessingStaticCollision(Ball& OtherBall)
{
	float distance = sqrt(pow(Centre.x - OtherBall.Centre.x, 2) + pow(Centre.y - OtherBall.Centre.y, 2)); // ���������� ����� �������� �����
	if (distance + 0.001 < Radius + OtherBall.Radius) // ���� ��������� ���������
	{
		float temp = (distance - Radius - OtherBall.Radius) / 2; // ���������� ��������� �������
		Centre -= Vector2f(Centre.x - OtherBall.Centre.x, Centre.y - OtherBall.Centre.y) * temp / distance;
		OtherBall.Centre += Vector2f(Centre.x - OtherBall.Centre.x, Centre.y - OtherBall.Centre.y) * temp / distance;
		//std::cout << "��������� ����������� �������� �������" << this << " : " << &OtherBall << std::endl;
		return true;
	}
	else return false;
}

void Ball::NormalizeSpeedVector()
{
	float modul = sqrt(pow(SpeedVector.x, 2) + pow(SpeedVector.y, 2));
	if (modul != 0) SpeedVector /= modul;
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
	float distance = 2 * BALL_RADIUS;
	Vector2f normal = (Centre - other.Centre) / distance;
	Vector2f tangent = Vector2f(-normal.y, normal.x);

	Speed *= 0.8;
	other.Speed *= 0.8;

	float v1x = SpeedVector.x * Speed, v1y = SpeedVector.y * Speed;
	float v2x = other.SpeedVector.x * other.Speed, v2y = other.SpeedVector.y * other.Speed;

	float dptan1 = v1x * tangent.x + v1y * tangent.y;
	float dptan2 = v2x * tangent.x + v2y * tangent.y;

	float dpnorm1 = v1x * normal.x + v1y * normal.y;
	float dpnorm2 = v2x * normal.x + v2y * normal.y;

	float V1x = tangent.x * dptan1 + normal.x * other.Speed;
	float V1y = tangent.y * dptan1 + normal.y * other.Speed;
	float V2x = tangent.x * dptan2 + normal.x * Speed;
	float V2y = tangent.y * dptan2 + normal.y * Speed;

	ChangeDir(Vector2f(V1x, V1y)); 
	other.ChangeDir(Vector2f(-V2x, -V2y));

	Speed = sqrt(V1x * V1x + V1y * V1y);
	other.Speed = sqrt(V2x * V2x + V2y * V2y);


   //std::cout << "��������� ������������ �������� �������" << this << " : " << &other << std::endl;
}

void Ball::SetPosition(Vector2f Position)
{
	Centre = Position;
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












