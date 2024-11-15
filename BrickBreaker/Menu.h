#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Window.h"
#include "Systeme.h"

class Menu {
private:
    Window& window;
	Systeme& systeme;
    sf::Font font;
    sf::Text title;
    sf::Text startOption;
    sf::Text optionsOption;
    sf::Text exitOption;
    sf::Clock inputDelayClock; // Pour limiter la vitesse des changements
    sf::Time delayTime = sf::milliseconds(200); // Temps minimum entre deux changements

    int selectedOption = 0;

public:
    Menu(Window& win, Systeme& sys);
    ~Menu() = default;

    void init();
    void handleInput();
    int getSelectedOption() const;
    void display();
};

