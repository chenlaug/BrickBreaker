#include "Window.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// constructeur de la classe Window
Window::Window(int width, int height, std::string title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	window.create(sf::VideoMode(width, height), title, sf::Style::Default);
}

// destructeur de la classe Window
Window::~Window()
{
	if (window.isOpen())
	{
		window.close();
	}
}

// Cette fonction permet de vider la fenêtre
void Window::clear() {
	window.clear(sf::Color::Black);
}

// Cette fonction permet de fermer la fenêtre
void Window::close()
{
	window.close();
}

// Cette fonction permet de mettre la fenêtre en plein écran ou en fenêtré
void Window::toggleFullscreen()
{
	setFullscreen();
	reCreateWindow();
}

// Cette fonction permet de recréer la fenêtre
void Window::reCreateWindow()
{
	close();

	if (this->fullscreen)
	{
		window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
	}
	else
	{
		window.create(sf::VideoMode(width, height), title, sf::Style::Default);
	}
}

// Cette fonction permet d'afficher la fenêtre
void Window::display()
{
	window.display();
}

// Cette fonction permet de savoir si la fenêtre est ouverte
bool Window::isOpen()
{
	return window.isOpen();
}

// Cette fonction permet de savoir si la fenêtre est en plein écran
bool Window::isFullscreen()
{
	return this->fullscreen;
}

// Cette fonction permet de gérer les événements de la fenêtre
bool Window::pollEvent(sf::Event& event) {
	return window.pollEvent(event);
}

// Cette fonction permet de récupérer la taille de la fenêtre
sf::Vector2u Window::getSize()
{
	return window.getSize();
}


// Cette fonction permet de récupérer la fenêtre
sf::RenderWindow& Window::getRenderWindow() {
	return window;
}

// Cette fonction permet de mettre la fenêtre en plein écran
void Window::setFullscreen()
{
	this->fullscreen = !fullscreen;
}

// Cette fonction permet de dessiner un objet
void Window::draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}


