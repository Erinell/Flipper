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

// Valeurs de score associées aux broches SCORE (voir Pins.h)
#define SCORE_VALUE {10, 100, 1000, 10000, 1000}

/*
 Valeurs des bonus associées aux broches BONUS (voir Pins.h)
 Les valeurs sont multipliées par 2 si le bonus est actif
*/
#define BONUS_VALUE {150, 250, 750, 1500}

/*
 Valeur des cibles associées à la broche TARGETS (voir Pins.h)
 Les cibles remontent lors d'une nouvelle bille
*/
#define TARGET_VALUE 1000
