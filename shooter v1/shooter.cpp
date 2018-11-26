#include "stdafx.h"
#include "shooter.h"

#include "MathsMax.h"


Shooter::Shooter(sf::Color color)
{
	posX = 200;
	posY = 50;
	rotation = 0;
	renderTexture.create(largeur, hauteur);
	sf::CircleShape shape1(20);
	sf::CircleShape shape2(7);
	shape1.setFillColor(color);
	shape2.setFillColor(sf::Color::Black);
	shape2.setPosition(sf::Vector2f(23, 12));
	renderTexture.draw(shape1);
	renderTexture.draw(shape2);
	renderTexture.display();

	texture = renderTexture.getTexture();
	sprite.setTexture(texture);

	line1.setSize(sf::Vector2f(fovl, 1));
	line2.setSize(sf::Vector2f(fovl, 1));
	line1.setOrigin(sf::Vector2f(0, 0));
	line2.setOrigin(sf::Vector2f(0, 0));
	line1.setFillColor(sf::Color::Black);
	line2.setFillColor(sf::Color::Black);

	this->setOrigin(sf::Vector2f(20, 20));

}

void Shooter::setPos(float x, float y) {
	backPosX = x;
	backPosY = y;
	posX = x;
	posY = y;
}

void Shooter::addPos(float x, float y, float coeff) {
	backPosX = posX;
	backPosY = posY;
	posX += (x * coeff);
	posY += (y * coeff);
	if (firstMove) {
		points++;
		firstMove = false;
	}
}

void Shooter::addEntityLs(Shooter* entity)
{
	entityList.push_back(entity);
}

void Shooter::avancer(int work) {
	if (work > 0)
		addPos(ceil(cos(rotation * PI / 180) * 10000) / 10000, ceil(sin(rotation * PI / 180) * 10000) / 10000, 3);
}

void Shooter::reculer() {
	//if(work > 0)
	addPos(-(ceil(cos(rotation * PI / 180) * 10000) / 10000), -(ceil(sin(rotation * PI / 180) * 10000) / 10000), 3);
}

void Shooter::turnRight(int work) {
	if (work > 0) {
		rotation += coeffRotate;
		if (firstRot) {
			points++;
			firstRot = false;
		}
	}
}

void Shooter::turnLeft(int work) {
	if (work > 0) {
		rotation -= coeffRotate;
		if (firstRot) {
			points++;
			firstRot = false;
		}
	}
}

void Shooter::fieldOfView(int set) {
	if (set < 1)
		fov--;
	if (set > 2)
		fov++;

	if (fov > 30)
		fov = 30;
	if (fov < 1)
		fov = 1;
}

void Shooter::tirer(int work) {
	if (work > 0)
		if (!alreadyShoot)
		{
			balle = new Balle;
			balle->init(posX, posY, rotation/*, this*/);
			balle->setOrigin(5, 5);
			balle->addPos(ceil(cos(rotation * PI / 180) * 10000) / 10000, ceil(sin(rotation * PI / 180) * 10000) / 10000, 5);
			alreadyShoot = true;
		}
}

void Shooter::update() {
	if (vies <= 0) {
		isDead = true;
		return;
	}

	see = 0;
	box.left = posX - (largeur / 2);
	box.top = posY - (hauteur / 2);
	box.height = hauteur;
	box.width = largeur;

	this->setPosition(posX, posY);
	this->setRotation(rotation);

	if (alreadyShoot)
	{
		if (firstShoot) {
			points += 1;
			firstShoot = false;
		}
		if (balle->isDead)
		{
			if (balle->info == 1) //touché
				points++;
			if (balle->info == 2) //tué
				points += 4;
			delete balle;
			balle = 0;
			alreadyShoot = false;
		}
		else
		{
			balle->setData(dataPos, dataPosType/*, entityList*/);
			balle->move();
		}
	}

	if (rotation > 360)
		rotation -= 360;
	if (rotation < -360)
		rotation += 360;
	if (rotation <= 0)
		rotation = 360 - rotation;

	line1.setPosition(this->getPosition());
	line1.setRotation(this->getRotation() + (fov));

	line2.setPosition(this->getPosition());
	line2.setRotation(this->getRotation() - (fov));

	int rot = line1.getRotation();
	if (rot > 360)
		rot -= 360;
	if (rot < -360)
		rot += 360;
	if (rot <= 0)
		rot = 360 - rot;
	line1.setRotation(rot);
	rot = line2.getRotation();
	if (rot > 360)
		rot -= 360;
	if (rot < -360)
		rot += 360;
	if (rot <= 0)
		rot = 360 - rot;
	line2.setRotation(rot);

	seePoint();
	dataPos.clear();
}

void Shooter::rollBack() {

	posX = backPosX;
	posY = backPosY;

	box.left = posX - (largeur / 2);
	box.top = posY - (hauteur / 2);
	box.height = hauteur;
	box.width = largeur;


	this->setPosition(posX, posY);
	this->setRotation(rotation);
}

void Shooter::addDataPos(sf::FloatRect data, int type) {
	dataPos.push_back(data);
	dataPosType.push_back(type);
}

void Shooter::seePoint() {

	bool right1 = true;
	bool right2 = true;
	bool down1 = true;
	bool down2 = true;

	int rot1 = line1.getRotation();
	int rot2 = line2.getRotation();
	if (rot1 >= 270 || rot1 <= 90)
		right1 = true;
	else
		right1 = false;
	if (rot1 <= 180)
		down1 = true;
	else
		down1 = false;
	if (rot2 >= 270 || rot2 <= 90)
		right2 = true;
	else
		right2 = false;
	if (rot2 <= 180)
		down2 = true;
	else
		down2 = false;


	float l1x, l1y, l2x, l2y;

	Point A(this->getPosition().x, this->getPosition().y);

	l1x = line1.getGlobalBounds().left + line1.getGlobalBounds().width;
	l1y = line1.getPosition().y + line1.getGlobalBounds().height;

	l2x = line2.getGlobalBounds().left + line2.getGlobalBounds().width;
	l2y = line2.getPosition().y + line2.getGlobalBounds().height;

	line1.rotate(180);
	line2.rotate(180);

	if (!right1)
		l1x = this->getPosition().x + (this->getPosition().x - (line1.getGlobalBounds().left + line1.getGlobalBounds().width));
	if (!right2)
		l2x = this->getPosition().x + (this->getPosition().x - (line2.getGlobalBounds().left + line2.getGlobalBounds().width));
	if (!down1)
		l1y = this->getPosition().y + (this->getPosition().y - (line1.getPosition().y + line1.getGlobalBounds().height));
	if (!down2)
		l2y = this->getPosition().y + (this->getPosition().y - (line2.getPosition().y + line2.getGlobalBounds().height));
	line1.rotate(180);
	line2.rotate(180);

	Point B(l1x, l1y);
	Point C(l2x, l2y);
	//std::cout << l1x << "  " << l1y << "  :  " << l2x << "  " << l2y << std::endl;
	for (int i = 0; i < dataPos.size(); i++)
	{
		Point P(dataPos[i].left, dataPos[i].top);
		//std::cout << dataPos[i].left << "  " << dataPos[i].top << std::endl;
		if (PointInTriangle(A, B, C, P))
		{
			see += dataPosType[i];
		}
	}

}


void Shooter::aie() {
	vies--;
	points -= 1;
	if (vies <= 0) {
		isDead = true;
		points /= 2;
	}
}
void Shooter::hit(int points) {
	this->points += points;
}

Shooter::~Shooter()
{
}
