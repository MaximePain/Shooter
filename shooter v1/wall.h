#pragma once
#include <SFML/Graphics.hpp>

class wall : public sf::Drawable, public sf::Transformable
{
public:
	wall();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(sprite, states);
	}


	~wall();

	float posX;
	float posY;

private:

	sf::Sprite sprite;
	sf::Texture texture;
	sf::RenderTexture renderTexture;
};

