# Flipper

## Pins

Nom           | Mode | Pin
--------------|------|----
points10      | IN   | D40
points100     | IN   | D41
points1000    | IN   | D42
points10000   | IN   | D43
credits       | IN   | D44
start         | IN   | D45
ballDetection | IN   | D46
ballEjection  | OUT  | ?

### Matrice LED

<!-- HUB12 brochage
Nom  | Mode | Pin
-----|------|------
OE   | OUT  | D9
SCLK | OUT  | D8
CLK  | OUT  | D13
R    | OUT  | D10
A    | OUT  | D6
B    | OUT  | D7
C    | OUT  | - -->

HUB75 brochage
Nom | Mode | Pin
----|------|----
G1  | OUT  | D25
G2  | OUT  | D28
R1  | OUT  | D24
R2  | OUT  | D27
B1  | OUT  | D26
B2  | OUT  | D29
A   | OUT  | A7
B   | OUT  | A8
C   | OUT  | A9
D   | OUT  | A10
LAT | SPI  | D10
CLK | SPI  | D11
OE  | OUT  | D9
GND | -    | GND

## Hardware

- Afficheur LED 64x32 P5
<!-- [https://circuitdigest.com/microcontroller-projects/digital-notice-board-using-p10-led-matrix-display-and-arduino] -->
<!-- matrice pins standard : [https://www.hackster.io/Maddy/using-the-dfrobot-rgb-led-matrix-921141] -->
- Arduino mega 2560

## Notes

#### Sélection joueurs
Pour Sélectionner le nombre de joueur(s), x appui sur start = x joueur. Maximum 4 joueurs.\
Tant que le délai est pas dépassé, appuyer sur start augmente le nombre de joueur et réinitialise le délai.\
Si > 4 reviens à 1 joueur.\
Si le délai est dépassé, démarrage de la partie. (afficher décompte sur afficheur ?)\
Le délai est configurable, par défaut 5 secondes.

Après 5 secondes, un appui sur start commence la partie seulement si la balle est détectée.
Si la balle pas détectée sur ballDetection, afficher un message bille absente.

#### En jeu
Si la balle est détectée sur ballDetection, on éjecte avec la sortie ballEjection.\

Des boutons incrémentent le score du joueur en cours (10, 100, 1000, 10000).\
(Possibilité de mettre plusieurs boutons sur un même score / entrée)

#### Fin de partie
Si la balle est détectée sur ballDetection, on passe au joueur suivant.\
Fin de partie quand 3 balles ont été détéctées sur tout les joueurs.

## Docs
### Arduino Mega
![Switch](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_ArduinoMega_2022-11-05.png?raw=true)

### Matrice LED
![Matrice LED](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_Matrix_2022-11-05.png?raw=true)

### Switch
![Switch](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_Switchs_2022-11-05.png?raw=true)

