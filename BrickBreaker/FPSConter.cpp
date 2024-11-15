#include "FPSConter.h"
#include <iostream>
#include <iomanip>

// Initialisation de la police et des param�tres du texte
void FPSConter::init(const std::string& fontPath)
{
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Impossible de charger la police de caract�res : " + fontPath);
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

	textLife.setFont(font);
	textLife.setCharacterSize(20);
	textLife.setFillColor(sf::Color::White);
	textLife.setPosition(10, 40);
}

// Mise � jour des FPS et du deltaTime
void FPSConter::update()
{
    deltaTime = clock.restart().asSeconds();

    frameCount++;
    elapsedTime += sf::seconds(deltaTime);

    if (elapsedTime.asSeconds() >= 1.0f)
    {
        fps = frameCount / elapsedTime.asSeconds(); 
        frameCount = 0;                           
        elapsedTime = sf::Time::Zero;             
    }

    text.setString("FPS: " + std::to_string(static_cast<int>(fps)));
}

// Mise � jour de la vie
void FPSConter::updateLife(int life)
{
    textLife.setString("Life: " + std::to_string(life));
}



// Retourne les FPS actuels
float FPSConter::getFps() const
{
    return fps;
}

// Retourne le deltaTime actuel
float FPSConter::getDeltaTime() const
{
    return deltaTime;
}

// Retourne l'objet texte pour l'affichage
const sf::Text& FPSConter::getText() const
{
    return text;
}
// Retourne l'objet texte pour l'affichagep
const sf::Text& FPSConter::getTextLife() const
{
    return textLife;
}