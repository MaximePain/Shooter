// shooter v1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include "shooter.h"
#include <cmath>
#include <vector>
#include "balle.h"
#ifdef PORTABLE
#include "../../Lia/Lia v1/Lia.h"
#else
#include "../../&AI/Lia/Lia v1/Lia v1/Lia.h"
#endif // PORTABLE



Shooter entity1;

Shooter entity2(sf::Color::Red);

void avancer(int work) {
	entity1.avancer(work);
}
void turnRight(int work) {
	entity1.turnRight(work);
}
void turnLeft(int work) {
	entity1.turnLeft(work);
}
void tirer(int work) {
	entity1.tirer(work);
}
void fieldOfView(int work) {
	entity1.fieldOfView(work);
}

void avancer2(int work) {
	entity2.avancer(work);
}
void turnRight2(int work) {
	entity2.turnRight(work);
}
void turnLeft2(int work) {
	entity2.turnLeft(work);
}
void tirer2(int work) {
	entity2.tirer(work);
}
void fieldOfView2(int work) {
	entity2.fieldOfView(work);
}

int main()
{
	std::cout << "neuronBase (enter = default): ";
	std::string neuronBase;
	std::getline(std::cin, neuronBase);
	if (neuronBase.size() < 3)
		neuronBase = "0:0!0|0:0!0|0:0!0|0:0!0|1:0!0|1:0!0|1:0!0|1:0!0|"; //0:0!0|1:0!0|2:10!0|2:10!0|2:10!0|2:10!0|2:10!0|
	Lia LIA(neuronBase);
	Lia LIA2(neuronBase);

	bool gameActive = true;
	bool loop = true;
	int windowX = 800;
	int windowY = 600;
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "v2");
	window.setVerticalSyncEnabled(true);

	entity1.setPos(100, 100);
	entity2.setPos(500, 150);
	entity2.rotation = 180;

	sf::RectangleShape mur;
	mur.setFillColor(sf::Color::Black);
	mur.setPosition(500, 400);
	mur.setSize(sf::Vector2f(20, 20));

	LIA.addInput(&entity1.see);
	LIA.addInput(&entity1.points);
	LIA.addInput(&entity1.vies);
	LIA.addInput(&(int&)entity1.fov);
	LIA.addOutput(&avancer);
	LIA.addOutput(&turnRight);
	LIA.addOutput(&turnLeft);
	LIA.addOutput(&tirer);
	LIA.addOutput(&fieldOfView);
	
	LIA2.addInput(&entity2.see);
	LIA2.addInput(&entity2.points);
	LIA2.addInput(&entity2.vies);
	LIA2.addInput(&(int&)entity2.fov);
	LIA2.addOutput(&avancer2);
	LIA2.addOutput(&turnRight2);
	LIA2.addOutput(&turnLeft2);
	LIA2.addOutput(&tirer2);
	LIA2.addOutput(&fieldOfView2);

	int time = 0;
	int timeMax = 60;
	bool speed = false;

	entity1.reset();
	entity2.reset();

	while (loop)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				loop = false;
			}
			if (event.type == sf::Event::LostFocus)
				gameActive = false;
			if (event.type == sf::Event::GainedFocus)
				gameActive = true;
		}
		if (gameActive || speed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				entity1.avancer(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				entity1.turnRight(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				entity1.turnLeft(1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				entity1.tirer(1);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				entity1.fieldOfView(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				entity1.fieldOfView(3);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				if (speed) {
					window.setVerticalSyncEnabled(true);
					speed = false;
				}
				else {
					window.setVerticalSyncEnabled(false);
					speed = true;
				}
				std::cout << speed << std::endl;
				sf::sleep(sf::milliseconds(1000));
			}

			//std::cout << "posX: " << entity1.posX << std::endl << "posY: " << entity1.posY << std::endl;

			//LIA.firstGen();
			LIA2.firstGen();
			entity1.update();
			entity2.update();
			//LIA.update();
			LIA2.update();

			if (entity1.isShooting())
				if (entity1.balle->box.intersects(entity2.box))
				{
					entity2.aie();
					int points = 2;
					if (entity2.isDead)
						points = 4;
					entity1.hit(points);
					entity1.balle->isDead = true;
				}
			if (entity2.isShooting())
				if (entity2.balle->box.intersects(entity1.box))
				{
					entity1.aie();
					int points = 2;
					if (entity1.isDead)
						points = 4;
					entity2.hit(points);
					entity2.balle->isDead = true;
				}

			/*
			########################
				AFFICHAGE
			########################
			*/
			//entity1.addDataPos(mur.getGlobalBounds(), 1);
			entity1.addDataPos(entity2.box, 2);

			//entity2.addDataPos(mur.getGlobalBounds(), 1);
			entity2.addDataPos(entity1.box, 2);

			if (entity1.box.intersects(mur.getGlobalBounds()))
				entity1.rollBack();
			if (entity1.box.intersects(entity2.box))
				entity1.rollBack();
			if (entity2.box.intersects(mur.getGlobalBounds()))
				entity2.rollBack();
			if (entity2.box.intersects(entity1.box))
				entity2.rollBack();

			//std::cout << entity1.see << std::endl;

			if (!speed || 1) {
				window.clear(sf::Color::White);
				window.draw(entity1);
				window.draw(entity2);
				window.draw(mur);
				window.display();
			}
			//std::cout << entity1.points << std::endl;
			if (entity1.points > 0 || entity2.points > 0)
				timeMax = 1000;
			else if (entity1.points > 3 || entity2.points > 3)
				timeMax = 3000;
			else
				timeMax = 60;
			if (entity1.isDead || entity2.isDead || time > timeMax)
			{
				//LIA.addScore(entity1.points);
				LIA2.addScore(entity2.points);
				//std::cout << LIA.debug() << std::endl << entity2.points << std::endl;
				entity2.rotation = 180;
				entity2.setPos(500, 150);
				entity1.setPos(100, 100);
				entity1.rotation = 0;
				time = 0;
				/*if (!LIA.newGenom()) {
					std::cout << LIA.debug() << " - ";
					std::cout << entity1.points << std::endl;
					LIA.newGeneration();
				}*/

				if (!LIA2.newGenom()) {
					std::cout << LIA2.debug() << " - ";
					std::cout << entity2.points << std::endl << std::endl;
					LIA2.newGeneration();
				}
				entity1.reset();
				entity2.reset();
			}
			time++;
		}
		//else
			//sf::sleep(sf::milliseconds(10));
	}

	return 0;
}

