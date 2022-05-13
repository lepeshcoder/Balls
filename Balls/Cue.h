#pragma once
#include"include.h"

class Cue {

private:

	// Спрайт Кия
	Sprite CueSprite;

	// Сила удара по шару
	float HitPower;

	// Позиция удара кия
	Vector2f Position;

	// Угол удара
	float angle;

public:

	Cue();

	// Конструктор
	Cue(sf::Texture& Texture);
	
	// Отрисовка Кия
	void Draw(sf::RenderWindow& window);

};