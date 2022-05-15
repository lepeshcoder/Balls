#pragma once
#include"include.h"

class Cue {

private:

	// Текстура Кия
	Texture* CueTexture;

	// Спрайт Кия
	Sprite* CueSprite;

	// Сила удара по шару
	float HitPower;

	// Позиция удара кия
	Vector2f Position;

	// Угол удара
	float angle;

	// Активна ли фаза удара
	bool IsHit = false;

public:

	Cue();

	Cue(std::string CueTexturePath);

	~Cue();

	// Отрисовка Кия
	void Draw(sf::RenderWindow& window);


	void SetAngle(float Angle);

	float GetAngle();

	// Установка Кия бойком к заданной точке
	void SetPosition(Vector2f Position);

	// Обновление позиции и силы удара Кия при ударе
	void Update(float distance);

	void SetIsHit(bool IsHit);

	bool GetIsHit();

	void SetHitPower(float HitPower);

	float GetHitPower();

	void Hit();

};