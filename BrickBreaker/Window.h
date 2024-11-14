#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Window
{
private:
	int width;
	int height;
	sf::RenderWindow window;
	std::string title;
	bool isfullscreen = false;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:

	Window(int width, int height, std::string title);
	~Window();

	void clear();
	void display();
	void close();
	void reCreateWindow(std::function<void(int, int)> resizeCallback);
	void draw(const sf::Drawable& drawable);
	bool isOpen();
	bool isFullscreen();
	bool pollEvent(sf::Event&);
	sf::Vector2u getSize();
	sf::RenderWindow& getRenderWindow();

	void drawBackground();
	bool loadBackground(const std::string& filePath);
};
