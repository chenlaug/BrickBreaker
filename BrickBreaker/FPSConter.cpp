#include "FPSConter.h"
#include <iostream>
 
// Cette fonction permet d'initialiser la police de caractères
void FPSConter::init()
{
    if (!font.loadFromFile("../Resource/Font/Roboto-Medium.ttf")) {
        throw std::runtime_error("Impossible de charger la police de caractères.");
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(10, 10);
}

// Cette fonction permet de calculer le nombre d'images par seconde
float FPSConter::getFps()
{
    frame++;
    time += clock.restart();
    if (time.asSeconds() >= 1.0f)
    {
        fps = frame / time.asSeconds();
        frame = 0;
        time = sf::Time::Zero;
    }
    return fps;
}

// Cette fonction permet d'afficher le nombre d'images par seconde
void FPSConter::display()
{
    text.setString("FPS: " + std::to_string(static_cast<int>(getFps())));
}

// Cette fonction permet de retourner le texte
const sf::Text& FPSConter::getText() const
{
    return text;
}