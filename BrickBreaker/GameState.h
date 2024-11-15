#ifndef GAMESTATE_H
#define GAMESTATE_H

// Enum�ration repr�sentant les �tats du jeu
enum class GameState {
    Menu,      // Menu principal
    Playing,   // Jeu en cours
	Restart,   // Red�marrer le jeu
    Options,   // Options
    Quit       // Quitter le jeu
};

#endif // GAMESTATE_H