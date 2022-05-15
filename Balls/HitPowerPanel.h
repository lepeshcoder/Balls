#pragma once
#include"include.h"
class HitPowerPanel
{
private:

	bool IsUpdate;

	Texture* HitPowerPanelTexture;

	Texture* HitPowerCueTexture;

	Sprite* HitPowerPanelSprite;

	Sprite* HitPowerCueSprite;



public: 

	HitPowerPanel();

	HitPowerPanel(std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath);

	~HitPowerPanel();

	void Update(float distance);

	void Draw(sf::RenderWindow& window);

	bool IsPanelActive(Vector2f Point);

	float GetTopPoint();

	float GetHeight();

	void SetIsUpdate(bool IsUpdate);

	void ResetCuePosition();


};

