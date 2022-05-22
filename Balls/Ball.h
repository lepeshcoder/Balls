#pragma once
#include"include.h"

using namespace sf;

class Ball {

private:
	
	// Координаты центра
	Vector2f Centre;

	// Радиус
	float Radius;

	// Скорость шарика ( Величина )
	float Speed;

	// Угол движения шарика
	Vector2f SpeedVector;

	// Текстура шарика
	Texture* BallTexture;

	// Спрайт для отрисовки
	Sprite* BallSprite;


public:

	// Конструктор по умолчанию
	Ball();

	// Конструктор
	Ball(Vector2f Centre, float Radius, std::string TexturePath);

	// Конструктор копирования
	Ball(const Ball &other);

	// Деструктор
	~Ball();

	// Отрисовка шарика
	void Draw(sf::RenderWindow& window);

	// Обновление Характеристик Шарика
	void Update(float time, float friction);

	// Смена направления
	void ChangeDir(Vector2f SpeedVector);

	// Установка скорости
	void SetSpeed(float Speed);

	// Геттер Позиции центра
	Vector2f GetCentre();

	float GetSpeed();

	// Обработка статических коллизий двух шаров ( ПОФИКСИТЬ)
	void ProcessingStaticCollision(Ball& OtherBall);

	// Обработка коллизий с колайдером
	void ColiderCollisison(Rect<float> &Colider);

	// Обработка динамических коллизий
	void DynamicCollision(Ball& other);

	void NormalizeSpeedVector();

	// Выставляет спрайт в CENTRE
	void UpdateCentre();


};