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

    if (!loadBackground("../Resource/image/test.jpg")) {
        std::cerr << "Warning: Background not loaded. Using default clear color." << std::endl;
    }
}

// destructeur de la classe Window
Window::~Window()
{
	if (window.isOpen())
	{
		window.close();
	}
}

// Cette fonction permet de vider la fen�tre
void Window::clear() {
	window.clear(sf::Color::Black);
}

// Cette fonction permet de fermer la fen�tre
void Window::close()
{
	window.close();
}


// Cette fonction permet de recr�er la fen�tre
void Window::reCreateWindow(std::function<void(int, int)> resizeCallback) {
    close();

    this->isfullscreen = !isfullscreen;

    if (this->isfullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(width, height), title, sf::Style::Default);
    }

    // Appeler le callback pour redimensionner les entit�s
    if (resizeCallback) {
        int newWidth = window.getSize().x;
        int newHeight = window.getSize().y;
        resizeCallback(newWidth, newHeight);
    }
}


// Cette fonction permet d'afficher la fen�tre
void Window::display()
{
	window.display();
}

// Cette fonction permet de savoir si la fen�tre est ouverte
bool Window::isOpen()
{
	return window.isOpen();
}

// Cette fonction permet de savoir si la fen�tre est en plein �cran
bool Window::isFullscreen()
{
	return this->isfullscreen;
}

// Cette fonction permet de g�rer les �v�nements de la fen�tre
bool Window::pollEvent(sf::Event& event) {
	return window.pollEvent(event);
}

// Cette fonction permet de r�cup�rer la taille de la fen�tre
sf::Vector2u Window::getSize()
{
	return window.getSize();
}


// Cette fonction permet de r�cup�rer la fen�tre
sf::RenderWindow& Window::getRenderWindow() {
	return window;
}

void Window::drawBackground() {
    window.draw(backgroundSprite);
}

// Cette fonction permet de charger l'image d'arri�re-plan
bool Window::loadBackground(const std::string& filePath) {
    if (!backgroundTexture.loadFromFile(filePath)) {
        std::cerr << "�chec du chargement de l'image d'arri�re-plan: " << filePath << std::endl;
        return false;
    }

    backgroundSprite.setTexture(backgroundTexture);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);

    return true;
}



// Cette fonction permet de dessiner un objet
void Window::draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}


