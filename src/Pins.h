#include "Settings.h"
// ------------ Boutons ------------
#define SCORE {52, 53, 50, 51}

#define credits         -1
#define start           48
#define tilt            34  // input 1 si flipper basculé
#define ballDetection   49  // input 1 si bille dans rail prêt à tirer
#define reset           8   // Hardware reset
#define batteurs        7   // contrôle relai pour 24V des batteurs

#define BONUS {42, 40, 38, 36}
#define LEDS_BONUS {43, 41, 39, 37}

#define TARGETS 46 // contact pour score des cibles

#define TRIGGER_SOLENOID {44, 45} // contacts pour SOLENOIDS

// ------------ Solenoides ------------

#define ballEjection    A0
#define liftTargets     A1 // remontée des cibles
#define SOLENOIDS {A2, A5}

// ------------ Matrice LED HUB75 ------------
#ifdef HUB75
#define CLK 11
#define OE   9
#define LAT 10
#define A   A7
#define B   A8
#define C   A9
#define D   A10
// R1 -> 24
// G1 -> 25
// B1 -> 26
// R2 -> 27
// G2 -> 28
// B2 -> 29
#endif