#pragma once
#include <SFML/Graphics.hpp>
class Window
{
private:
	int width;
	int height;
	sf::RenderWindow window;
	std::string title;

public:

	Window(int width, int height, std::string title);
	~Window();

	void clear();
	void display();
	void close();
	bool isOpen();
	bool pollEvent(sf::Event&);
	sf::Vector2u getSize();
	sf::RenderWindow& getRenderWindow();
};


