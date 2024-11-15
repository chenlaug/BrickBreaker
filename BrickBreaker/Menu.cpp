#include "Menu.h"
#include <iostream>

Menu::Menu(Window& win) : window(win) {}

void Menu::init() {
    if (!font.loadFromFile("../Resource/Font/Roboto-Medium.ttf")) {
        throw std::runtime_error("Impossible de charger la police de caractères.");
    }

    // Titre
    title.setFont(font);
    title.setString("Brick Breaker");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

    // Option Start
    startOption.setFont(font);
    startOption.setString("Start");
    startOption.setCharacterSize(32);
    startOption.setFillColor(sf::Color::Red); // Option sélectionnée par défaut
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
            // Réagir aux flèches haut et bas
            if (event.key.code == sf::Keyboard::Up) {
                selectedOption = (selectedOption + 2) % 3; // Naviguer vers le haut
            }
            else if (event.key.code == sf::Keyboard::Down) {
                selectedOption = (selectedOption + 1) % 3; // Naviguer vers le bas
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                // Action de sélection (gérée dans `Game::run()`)
            }
        }
    }

    // Changer la couleur selon l'option sélectionnée
    startOption.setFillColor(selectedOption == 0 ? sf::Color::Red : sf::Color::White);
    optionsOption.setFillColor(selectedOption == 1 ? sf::Color::Red : sf::Color::White);
    exitOption.setFillColor(selectedOption == 2 ? sf::Color::Red : sf::Color::White);
}


int Menu::getSelectedOption() const {
    return selectedOption; // 0: Start, 1: Options, 2: Exit
}

void Menu::display() {
    window.clear();

    // Affiche les éléments du menu
    window.draw(title);
    window.draw(startOption);
    window.draw(optionsOption);
    window.draw(exitOption);

    window.display();
}