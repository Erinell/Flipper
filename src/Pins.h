#include "Settings.h"
// ------------ Boutons ------------

#define points10        52
#define points100       53
#define points1000      50
#define points10000     51
#define credits         -1
#define start           48
#define tilt            34  // input 1 si flipper basculé
#define ballDetection   49  // input 1 si bille dans rail prêt à tirer
#define reset           8

#define bonus150        42
#define bonus250        40
#define bonus750        38
#define bonus1500       36
#define led150          43
#define led250          41
#define led750          39
#define led1500         37


// ------------ Solenoides ------------

#define ballEjection    A0  // Output 1 pour tirer

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