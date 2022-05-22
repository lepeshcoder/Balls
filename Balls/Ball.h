#pragma once
#include"include.h"

using namespace sf;

class Ball {

private:
	
	// ���������� ������
	Vector2f Centre;

	// ������
	float Radius;

	// �������� ������ ( �������� )
	float Speed;

	// ���� �������� ������
	Vector2f SpeedVector;

	// �������� ������
	Texture* BallTexture;

	// ������ ��� ���������
	Sprite* BallSprite;


public:

	// ����������� �� ���������
	Ball();

	// �����������
	Ball(Vector2f Centre, float Radius, std::string TexturePath);

	// ����������� �����������
	Ball(const Ball &other);

	// ����������
	~Ball();

	// ��������� ������
	void Draw(sf::RenderWindow& window);

	// ���������� ������������� ������
	void Update(float time, float friction);

	// ����� �����������
	void ChangeDir(Vector2f SpeedVector);

	// ��������� ��������
	void SetSpeed(float Speed);

	// ������ ������� ������
	Vector2f GetCentre();

	float GetSpeed();

	// ��������� ����������� �������� ���� ����� ( ���������)
	void ProcessingStaticCollision(Ball& OtherBall);

	// ��������� �������� � ����������
	void ColiderCollisison(Rect<float> &Colider);

	// ��������� ������������ ��������
	void DynamicCollision(Ball& other);

	void NormalizeSpeedVector();

	// ���������� ������ � CENTRE
	void UpdateCentre();


};