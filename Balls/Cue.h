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

	// Скорость вращения Кия
	float CueAngleSpeed;

public:

	Cue();

	Cue(std::string CueTexturePath);

	~Cue();

	// Отрисовка Кия
	void Draw(sf::RenderWindow& window);

	// Изначальный угол равен 0 угол возрастает по часовой стрелке и ограничен от 0 до 360 градусов
	void SetAngle(float Angle);

	Vector2f GetAngle();

	float GetfloatAngle();

	// Установка Кия бойком к заданной точке
	void SetPosition(Vector2f Position);

	// Обновление позиции и силы удара Кия при ударе
	void Update(float distance);

	void SetIsHit(bool IsHit);

	bool GetIsHit();

	void SetHitPower(float HitPower);

	float GetHitPower();

	void Hit();

	// Делает спрайт невидимым
	void Hide();

	void Rotate(Direction dir);

	void CueAngleSpeedUp();

	void CueAngleSpeedDown();

	void SetSpeed(float speed);


};