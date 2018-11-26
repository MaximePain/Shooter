#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include <math.h>

class Balle : public sf::Drawable, public sf::Transformable
{
public:
	Balle()
	{
		renderTexture.create(10, 10);
		sf::CircleShape shape1(5);
		shape1.setFillColor(sf::Color::Black);
		renderTexture.draw(shape1);
		renderTexture.display();

		texture = renderTexture.getTexture();
		sprite.setTexture(texture);
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (!isDead) {
			states.transform *= getTransform();
			target.draw(sprite, states);
		}
	}

	void init(float x, float y, float r/*, Shooter *entity*/);
	
	void move();
	void addPos(float x, float y, float coeff = 1);
	void setData(std::vector<sf::FloatRect> dataPos, std::vector<int> dataPosType);
	
	bool isDead = false;
	int info = 0;
	float rotation;
	float posX;
	float posY;
	float coeffPos = 5;
	~Balle();
	sf::FloatRect box;
private:
	sf::RenderTexture renderTexture;
	sf::Texture texture;
	sf::Sprite sprite;
	double PI = 3.14159265358979323846;

	int timeToLive = 200;
	
	//Shooter* owner;
	//std::vector<Shooter*> entityList;
	std::vector<sf::FloatRect> dataPos;
	std::vector<int> dataPosType;

};

