#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// Composants de base
struct Position {
    float x, y; 
};

struct Velocity {
    float x, y;
};

struct Size {
    float width, height; 
};

struct Color {
    int red, green, blue, alpha; 
};

// Composants spécifiques
struct Ball {
    bool isMain; 
};

struct Brick {
    int health;
};

struct Bonus {
    std::string type; 
    bool active;      
};

struct Racket {
    float speed;
};

struct RenderShape {
    std::shared_ptr<sf::Shape> shape;
};
