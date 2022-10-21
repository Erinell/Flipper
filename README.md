# Flipper

## Pins

Name          | Mode | pin
--------------|------|----
points10      | IN   | D22
points100     | IN   | D23
points1000    | IN   | D24
points10000   | IN   | D25
credits       | IN   | D26
start         | IN   | D27
ballDetection | IN   | D28
ballEjection  | OUT  | A0

Pins à venir :
- leds ?
- Afficheur
- Solenoïdes
<!-- BallIndex     | OUT  | A1 -->

## Hardware

- Afficheur LED 32*16 P10
<!-- [https://circuitdigest.com/microcontroller-projects/digital-notice-board-using-p10-led-matrix-display-and-arduino] -->
- Arduino mega 2560

## Notes

#### Sélection joueurs
Pour Sélectionner le nombre de joueur(s), x appui sur start = x joueur. Maximum 4 joueurs.\
Tant que le délai est pas dépassé, appuyer sur start augmente le nombre de joueur et réinitialise le délai.\
Si > 4 reviens à 1 joueur.\
Si le délai est dépassé, démarrage de la partie. (afficher décompte sur afficheur ?)\
Le délai est configurable, par défaut 5 secondes.\

#### En jeu
Si la balle est détectée sur ballDetection, on éjecte avec la sortie ballEjection.\
Si la balle pas détectée sur ballDetection, afficher un message bille absente.\

Des boutons incrémentent le score du joueur en cours (10, 100, 1000, 10000).\
(Possibilité de mettre plusieurs boutons sur un même score / entrée)\

#### Fin de partie
Si la balle est détectée sur ballDetection, on passe au joueur suivant.\
Fin de partie quand 3 balles ont été détécté sur tout les joueurs.\

fin de la partie quand 3 balles par joueur sont detectées

## Classes

### Joueur
```c++
unsigned short id;              // id du joueur entre 1 et maxPlayers
unsigned short ballsDetected;   // nombre de balles jouées
unsigned long score;            // Le score
```

### Flipper
```c++
unsigned short maxPlayers;    // Nombre de joueurs maximum dans la config
unsigned short maxTry;        // Nombre de balle jouée avant fin de partie
unsigned short startDelay;    // Délai avant le démarrage de la partie (reset à chaque appui sur start)

short currentMaxPlayers;  // Nombre de joueurs maximum pour la partie (incrémente à chaque appui start)
short playerTurn;         // id du joueur qui joue
```