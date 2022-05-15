#include "HitPowerPanel.h"

HitPowerPanel::HitPowerPanel()
{
	HitPowerPanelTexture = new Texture();
	HitPowerPanelSprite = new Sprite();
	HitPowerCueTexture = new Texture();
	HitPowerCueSprite = new Sprite();
	IsUpdate = false;
}

HitPowerPanel::HitPowerPanel(std::string HitPowerPanelTexturePath, std::string HitPowerCueTexturePath)
{
	HitPowerPanelTexture = new Texture();
	HitPowerPanelTexture->loadFromFile(HitPowerPanelTexturePath);
	HitPowerPanelSprite = new Sprite();
	HitPowerPanelSprite->setTexture(*HitPowerPanelTexture);
	HitPowerPanelSprite->setScale(0.5, 0.9);
	HitPowerPanelSprite->setPosition(Vector2f(0, 180));

	Image HitPowerCueImage;
	HitPowerCueImage.loadFromFile(HitPowerCueTexturePath);
	HitPowerCueImage.createMaskFromColor(Color::White);
	HitPowerCueTexture = new Texture();
	HitPowerCueTexture->loadFromImage(HitPowerCueImage);
	HitPowerCueSprite = new Sprite();
	HitPowerCueSprite->setTexture(*HitPowerCueTexture);
	HitPowerCueSprite->setPosition(5, 200);
	HitPowerCueSprite->setScale(0.5, 0.9);
	IsUpdate = false;

}

HitPowerPanel::~HitPowerPanel()
{
	delete HitPowerCueTexture;
	delete HitPowerCueSprite;
	delete HitPowerPanelTexture;
	delete HitPowerPanelSprite;
}

void HitPowerPanel::Update(float distance)
{
	if (IsUpdate)
	{
		HitPowerCueSprite->setPosition(HitPowerCueSprite->getPosition().x, HitPowerPanelSprite->getPosition().y + distance);
		std::cout << HitPowerCueSprite->getPosition().y << std::endl;
		IsUpdate = false;
	}
}

void HitPowerPanel::Draw(sf::RenderWindow& window)
{
	window.draw(*HitPowerPanelSprite);
	window.draw(*HitPowerCueSprite);
}

bool HitPowerPanel::IsPanelActive(Vector2f Point)
{
	return HitPowerPanelSprite->getGlobalBounds().contains(Point);
}

float HitPowerPanel::GetTopPoint()
{
	return HitPowerPanelSprite->getPosition().y + 12;
}

float HitPowerPanel::GetHeight()
{
	return HitPowerPanelSprite->getGlobalBounds().height;
}

void HitPowerPanel::SetIsUpdate(bool IsUpdate)
{
	this->IsUpdate = IsUpdate;
}

void HitPowerPanel::ResetCuePosition()
{
	HitPowerCueSprite->setPosition(5, 200);
}
