#include "Window.h"
#include <SFML/Graphics.hpp>

Window::Window(int width, int height, std::string title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	window.create(sf::VideoMode(width, height), title);
}

Window::~Window()
{
	if (window.isOpen())
	{
		window.close();
	}
}

void Window::clear() {
	window.clear(sf::Color::Black);
}

void Window::close()
{
	window.close();
}

void Window::display()
{
	window.display();
}

bool Window::isOpen()
{
	return window.isOpen();
}

bool Window::pollEvent(sf::Event& event) {
	return window.pollEvent(event);
}

sf::Vector2u Window::getSize()
{
	return window.getSize();
}

sf::RenderWindow& Window::getRenderWindow() {
	return window;
}


