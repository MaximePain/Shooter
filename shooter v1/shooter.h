#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "balle.h"
#include <vector>


class Shooter : public sf::Drawable, public sf::Transformable
{
public:
	Shooter(sf::Color color = sf::Color::Green);

	Balle *balle = 0;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(line1);
		target.draw(line2);

		target.draw(sprite, states);
		if (alreadyShoot)
		{
			target.draw(*balle);
		}
	}
	void setPos(float x, float y);

	void update();

	void avancer(int work);
	void turnRight(int work);
	void turnLeft(int work);
	void tirer(int work);
	void fieldOfView(int set);
	void rollBack();

	void reculer();
	void addDataPos(sf::FloatRect data, int type);
	void addEntityLs(Shooter* entity);
	void aie();
	void hit(int points);

	void reset() {
		vies = 3;
		points = 0;
		isDead = false;
		firstShoot = true;
		firstMove = true;
		firstRot = true;
	}

	~Shooter();

	float posX;
	float posY;
	int see = 0;

	float rotation;
	float coeffRotate = 4;
	float isDead = false;
	sf::FloatRect box;
	bool isShooting() { return alreadyShoot; }

	bool touchBullet = false;
	int points = 0;

private:
	void addPos(float x, float y, float coeff = 6);
	void seePoint();

	sf::RenderTexture renderTexture;
	sf::Texture texture;
	sf::Sprite sprite;
	double PI = 3.14159265358979323846;
	int vies = 3;
	bool alreadyShoot = false;
	float largeur = 40;
	float hauteur = 40;
	float backPosX;
	float backPosY;
	std::vector<sf::FloatRect> dataPos;
	std::vector<int> dataPosType;
	std::vector<Shooter*> entityList;
	
	float fov = 5;
	int fovl = 1200;
	sf::RectangleShape line1, line2;
	bool firstShoot = true;
	bool firstMove = true;
	bool firstRot = true;
};

