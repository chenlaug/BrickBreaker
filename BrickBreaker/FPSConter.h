#pragma once
#include <SFML/Graphics.hpp>
class FPSConter
{
private:
	sf::Clock clock;
	sf::Time time;
	sf::Text text;
	sf::Font font;

	float fps = 0;
	int frame = 0;

public:
	void init();
	float getFps();
	void display();
	const sf::Text& getText() const;
};

