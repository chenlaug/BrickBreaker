#pragma once
#include <SFML/Graphics.hpp>

class Window
{
private:
	int width;
	int height;
	sf::RenderWindow window;
	std::string title;
	bool isfullscreen = false;

public:

	Window(int width, int height, std::string title);
	~Window();

	void clear();
	void display();
	void close();
	void toggleFullscreen();
	void reCreateWindow();
	void setFullscreen();
	void draw(const sf::Drawable& drawable);
	bool isOpen();
	bool isFullscreen();
	bool pollEvent(sf::Event&);
	sf::Vector2u getSize();
	sf::RenderWindow& getRenderWindow();
};
