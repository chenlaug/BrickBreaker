#ifndef GAMESTATE_H
#define GAMESTATE_H

// Enumération représentant les états du jeu
enum class GameState {
    Menu,      // Menu principal
    Playing,   // Jeu en cours
	Restart,   // Redémarrer le jeu
    Options,   // Options
    Quit       // Quitter le jeu
};

#endif // GAMESTATE_H