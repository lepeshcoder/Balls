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

public:

	Cue();

	Cue(std::string CueTexturePath);

	~Cue();

	// ��������� ���
	void Draw(sf::RenderWindow& window);


	void SetAngle(float Angle);

	float GetAngle();

	// ��������� ��� ������ � �������� �����
	void SetPosition(Vector2f Position);

	// ���������� ������� � ���� ����� ��� ��� �����
	void Update(float distance);

	void SetIsHit(bool IsHit);

	bool GetIsHit();

	void SetHitPower(float HitPower);

	float GetHitPower();

	void Hit();

};