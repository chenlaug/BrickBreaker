#pragma once
#include <SFML/Graphics.hpp>

class FPSConter
{
private:
    sf::Clock clock;         
    sf::Time elapsedTime;    
    sf::Text text;           
    sf::Font font;           
	sf::Text textLife;

    float fps = 0.0f;        
    float deltaTime = 0.0f;  
    int frameCount = 0;     

public:
    void init(const std::string& fontPath = "../Resource/Font/Roboto-Medium.ttf");
    void update();
    void updateLife(int life);
    float getFps() const;
    float getDeltaTime() const;
    const sf::Text& getText() const;
    const sf::Text& getTextLife() const;
};
