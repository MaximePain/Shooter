#include "stdafx.h"
#include "balle.h"


/*balle::balle()
{
}*/

void Balle::addPos(float x, float y, float coeff)
{
	posX += (x * coeffPos * coeff);
	posY += (y * coeffPos * coeff);
}

void Balle::setData(std::vector<sf::FloatRect> dataPos, std::vector<int> dataPosType) {
	this->dataPos = dataPos;
	this->dataPosType = dataPosType;
	//this->entityList = entityLs;
}

void Balle::move()
{
	box.left = posX - (10 / 2);
	box.top = posY - (10 / 2);
	box.height = 10;
	box.width = 10;

	addPos(ceil(cos(rotation * PI / 180) * 10000) / 10000, ceil(sin(rotation * PI / 180) * 10000) / 10000);
	timeToLive--;
	if (timeToLive < 0)
		isDead = true;
	this->setPosition(posX, posY);

	/*for (int i = 0; i < entityList.size(); i++)
	{
		if (box.intersects(entityList[i]->box))
		{
			entityList[i]->aie();
			int points = 2;
			if (entityList[i]->isDead)
				points = 4;
			owner->hit(points);
			isDead = true;
			break;
		}
	}*/
}

void Balle::init(float x, float y, float r/*, Shooter *entity**/)
{
	//owner = entity;
	posX = x; posY = y; rotation = r;
}

Balle::~Balle()
{
}
