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
#define NB_SCORE 4
#define SCORE_VALUE {10, 100, 1000, 10000}

// Valeurs des bonus associées aux broches BONUS (voir Pins.h)
// Les valeurs sont multipliées par 2 si le bnous est actif
#define NB_BONUS 4
#define BONUS_VALUE {150, 250, 750, 1500}

// Valeurs des cibles associées aux broches TARGETS (voir Pins.h)
// Les cibles remontent lors d'une nouvelle bille
#define NB_TARGET 4
#define TARGET_VALUE {1000, 1000, 1000, 1000}