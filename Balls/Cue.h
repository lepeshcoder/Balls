#pragma once
#include"include.h"

class Cue {

private:

	// �������� ���
	Texture* CueTexture;

	// ������ ���
	Sprite* CueSprite;

	// ���� ����� �� ����
	float HitPower;

	// ������� ����� ���
	Vector2f Position;

	// ���� �����
	float angle;

	// ������� �� ���� �����
	bool IsHit = false;

	// �������� �������� ���
	float CueAngleSpeed;

public:

	Cue();

	Cue(std::string CueTexturePath);

	~Cue();

	// ��������� ���
	void Draw(sf::RenderWindow& window);

	// ����������� ���� ����� 0 ���� ���������� �� ������� ������� � ��������� �� 0 �� 360 ��������
	void SetAngle(float Angle);

	Vector2f GetAngle();

	float GetfloatAngle();

	// ��������� ��� ������ � �������� �����
	void SetPosition(Vector2f Position);

	// ���������� ������� � ���� ����� ��� ��� �����
	void Update(float distance);

	void SetIsHit(bool IsHit);

	bool GetIsHit();

	void SetHitPower(float HitPower);

	float GetHitPower();

	void Hit();

	// ������ ������ ���������
	void Hide();

	void Rotate(Direction dir);

	void CueAngleSpeedUp();

	void CueAngleSpeedDown();

	void SetSpeed(float speed);


};