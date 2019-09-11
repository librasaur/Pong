#include <iostream>
#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	int windowWidth = 1024;
	int windowHeight = 768;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int score = 0;
	int livesLeft = 3;

	Color bgColours[6] = {Color(255, 153, 153, 255), Color(255, 204, 153, 255), Color(255, 255, 153, 255),
							Color(153, 255, 153, 255), Color(153, 255, 255, 255), Color(204, 153, 225, 255)};
	int colourIndex = 0;

	Bat bat(windowWidth / 2, windowHeight - 20);
	Ball ball(windowWidth / 2, 1);

	Text hud;
	Font font;
	font.loadFromFile("game_over.ttf");

	hud.setFont(font);
	hud.setFillColor(Color::Black);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// If ball hits bottom
		if (ball.getPosition().top > windowHeight)
		{
			ball.hitBottom();
			livesLeft--;
		}

		// If ball hits top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			score++;

			colourIndex++;
			if (colourIndex > 5)
				colourIndex = 0;
		}

		// If ball hits side
		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
		{
			ball.reboundSides();
		}

		// If ball hits bat
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.reboundBatOrTop();
		}


		if (livesLeft < 1) // Player loses
		{
			std::stringstream endGameText;
			endGameText << "Game Over!";

			hud.setString(endGameText.str());
			hud.setCharacterSize(200);
			hud.setPosition(windowWidth, windowHeight);

			window.clear(bgColours[colourIndex]);
			window.draw(hud);
			window.display();

			// Reset game
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				score = 0;
				livesLeft = 3;
				colourIndex = 0;
			}
		}
		else // Player still has lives
		{
			ball.update();
			bat.update();

			std::stringstream gamePlayText;
			gamePlayText << "Score: " << score << "	Lives: " << livesLeft;

			hud.setString(gamePlayText.str());
			hud.setCharacterSize(100);
			hud.setPosition(50, 0);

			window.clear(bgColours[colourIndex]);
			window.draw(ball.getShape());
			window.draw(bat.getShape());
			window.draw(hud);
			window.display();
		}
	}

	return 0;
}