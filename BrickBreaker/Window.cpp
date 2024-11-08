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
	close();
}

void Window::clear()
{
	window.clear();
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

sf::Vector2u Window::getSize()
{
	return window.getSize();
}

bool Window::pollEvent()
{
	return window.pollEvent(event);
}


