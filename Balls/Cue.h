#pragma once
#include"include.h"

class Cue {

private:

	// ������ ���
	Sprite CueSprite;

	// ���� ����� �� ����
	float HitPower;

	// ������� ����� ���
	Vector2f Position;

	// ���� �����
	float angle;

public:

	Cue();

	// �����������
	Cue(sf::Texture& Texture);
	
	// ��������� ���
	void Draw(sf::RenderWindow& window);

};