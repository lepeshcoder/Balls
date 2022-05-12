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

	// Вектор направления шарика
	Vector2f SpeedVector;

	// Флаг движения
	bool IsMove;

	// Текстура для Шарика
	Texture Texture;

	// Объект для отрисовки
	CircleShape GraphicBall;


public:

	// Конструктор
	Ball(Vector2f Centre, float Radius, Color color);

	// Загрузка Текстуры
	void SetTexture(sf::Texture Texture);
	
	// Отрисовка шарика
	void Draw(sf::RenderWindow& window);

	// Обновление Характеристик Шарика
	void Update(float time, float friction);

	// Смена направления
	void ChangeDir(Vector2f SpeedVector);

	// Установка скорости
	void SetSpeed(float Speed);

	// Установка флага движения
	void SetIsMove(bool IsMove);

	
	

	
	








};