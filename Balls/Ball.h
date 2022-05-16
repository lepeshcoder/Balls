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
	float Angle;

	// Флаг движения
	bool IsMove;

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
	void ChangeDir(float angle);

	// Установка скорости
	void SetSpeed(float Speed);

	// Установка флага движения
	void SetIsMove(bool IsMove);

	// Геттер Позиции центра
	Vector2f GetCentre();

	// Обработка статических коллизий двух шаров
	void ProcessingStaticCollision(Ball& OtherBall);

	void ColiderCollisison(Rect<float> &Colider);



	
	

	
	








};