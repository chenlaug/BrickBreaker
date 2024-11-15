#include "Menu.h"
#include <iostream>

Menu::Menu(Window& win, Systeme& sys) : window(win), systeme(sys) {}

void Menu::init() {
    if (!font.loadFromFile("../Resource/Font/Roboto-Medium.ttf")) {
        throw std::runtime_error("Impossible de charger la police de caract�res.");
    }

	std::cout << "Life Point: " << systeme.getLifePoint() << std::endl;
	if (systeme.getLifePoint() == 0) {
        // Option Game Over
        title.setString("Game Over");

        // Option Restart
        startOption.setString("Restart");
	}
	else {
        // Option Menu
        title.setString("Brick Breaker");

        // Option Start
        startOption.setString("Start");
	}

    // Titre
    title.setFont(font);
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

	// Option Start ou Restart
    startOption.setFont(font);
    startOption.setCharacterSize(32);
    startOption.setFillColor(sf::Color::Red);
    startOption.setPosition(window.getSize().x / 2 - startOption.getGlobalBounds().width / 2, 200);

    // Option Options
    optionsOption.setFont(font);
    optionsOption.setString("Options");
    optionsOption.setCharacterSize(32);
    optionsOption.setFillColor(sf::Color::White);
    optionsOption.setPosition(window.getSize().x / 2 - optionsOption.getGlobalBounds().width / 2, 300);

    // Option Exit
    exitOption.setFont(font);
    exitOption.setString("Exit");
    exitOption.setCharacterSize(32);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setPosition(window.getSize().x / 2 - exitOption.getGlobalBounds().width / 2, 400);
}

void Menu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            // R�agir aux fl�ches haut et bas
            if (event.key.code == sf::Keyboard::Up) {
                selectedOption = (selectedOption + 2) % 3; // Naviguer vers le haut
            }
            else if (event.key.code == sf::Keyboard::Down) {
                selectedOption = (selectedOption + 1) % 3; // Naviguer vers le bas
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                // Action de s�lection (g�r�e dans `Game::run()`)
            }
        }
    }

    // Changer la couleur selon l'option s�lectionn�e
    startOption.setFillColor(selectedOption == 0 ? sf::Color::Red : sf::Color::White);
    optionsOption.setFillColor(selectedOption == 1 ? sf::Color::Red : sf::Color::White);
    exitOption.setFillColor(selectedOption == 2 ? sf::Color::Red : sf::Color::White);
}


int Menu::getSelectedOption() const {
    return selectedOption;
}

void Menu::display() {
    window.clear();

    // Affiche les �l�ments du menu
    window.draw(title);
    window.draw(startOption);
    window.draw(optionsOption);
    window.draw(exitOption);

    window.display();
}