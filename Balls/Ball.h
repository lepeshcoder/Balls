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
	float Angle;

	// ���� ��������
	bool IsMove;

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
	void ChangeDir(float angle);

	// ��������� ��������
	void SetSpeed(float Speed);

	// ��������� ����� ��������
	void SetIsMove(bool IsMove);

	// ������ ������� ������
	Vector2f GetCentre();

	// ��������� ����������� �������� ���� �����
	void ProcessingStaticCollision(Ball& OtherBall);

	void ColiderCollisison(Rect<float> &Colider);



	
	

	
	








};