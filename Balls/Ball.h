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

	// ������ ����������� ������
	Vector2f SpeedVector;

	// ���� ��������
	bool IsMove;


	// ������ ��� ���������
	Sprite BallSprite;


public:

	// �����������
	Ball(Vector2f Centre, float Radius, sf::Texture& Texture);

	// ��������� ������
	void Draw(sf::RenderWindow& window);

	// ���������� ������������� ������
	void Update(float time, float friction);

	// ����� �����������
	void ChangeDir(Vector2f SpeedVector);

	// ��������� ��������
	void SetSpeed(float Speed);

	// ��������� ����� ��������
	void SetIsMove(bool IsMove);

	
	

	
	








};