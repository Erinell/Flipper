/*
 Matrice LED type HUB75
*/
#define HUB75

// Nombre de joueurs maximum dans la partie
#define MAX_PLAYERS 4

// Nombre de coups par joueurs
#define MAX_TRY 3

// Compte à rebours lors de la sélection u nombre de joueurs
#define START_DELAY 5000

// Temporisation avant réinitialisation du flipper
#define END_DELAY 10000

/*
 reset software.
 Si désactivé, la broche RESET de la carte doit être connectée à la broche reset définie dans Pins.h
*/
#define SOFT_RESET false