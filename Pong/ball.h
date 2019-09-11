#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f position;
	RectangleShape ballShape;
	Color ballColour = Color::Black;

	float xVelocity = .2f;
	float yVelocity = .2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();
	RectangleShape getShape();
	float getXVelocity();

	void reboundSides();
	void reboundBatOrTop();
	void hitBottom();
	void update();
};