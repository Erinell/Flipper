# Flipper

## Sommaire
1. [Pins](#Pins)
2. [Schémas](#Schémas)
    - [Arduino Méga](#Arduino-Mega)
    - [Matrice LED](#Matrice-LED)
3. [Notes](#Notes)
4. [Todo](#Todo)

## Pins

Nom              | Mode | Pin
-----------------|------|----
reset            | OUT  | D8
target_1         | IN   | D30
target_2         | IN   | D31
target_3         | IN   | D32
target_4         | IN   | D33
target_5         | IN   | D34
bonus1500        | IN   | D36
led1500          | OUT  | D37
bonus750         | IN   | D38
led750           | OUT  | D39
bonus250         | IN   | D40
led250           | OUT  | D41
bonus150         | IN   | D42
led150           | OUT  | D43
trigg_solenoid_1 | IN   | D44
trigg_solenoid_2 | IN   | D45
start            | IN   | D48
ballDetection    | IN   | D49
points1000       | IN   | D50
points10000      | IN   | D51
points10         | IN   | D52
points100        | IN   | D53
ballEjection     | OUT  | A0
liftTarget       | OUT  | A1
solenoid_1       | OUT  | A2
solenoid_2       | OUT  | A3
credits          | IN   | -1

### Matrice LED
HUB75 brochage

1   | Pin | Pin | 2
----|-----|-----|----
R1  | D24 | D25 | G1
B1  | D26 | GND | GND
R2  | D27 | D28 | G2
B2  | D29 | GND | GND
A   | A7  | A8  | B
C   | A9  | A10 | D
CLK | D11 | D10 | LAT
OE  | D9  | GND | GND

## Hardware

- Afficheur LED 64x32 P5
<!-- [https://circuitdigest.com/microcontroller-projects/digital-notice-board-using-p10-led-matrix-display-and-arduino] -->
<!-- matrice pins standard : [https://www.hackster.io/Maddy/using-the-dfrobot-rgb-led-matrix-921141] -->
- Arduino mega 2560

## Schémas
### Arduino Mega
![Mega2560](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_ArduinoMega_2023-06-12.png?raw=true)

### Matrice LED
![Matrice LED](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_Matrix_2023-06-08.png?raw=true)

### Switch
![Switch](https://github.com/Erinell/Flipper/blob/master/docs/img/Schematic_Switchs_2023-06-08.png?raw=true)

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

### Todo
- [ ] Ajouter de l'audio
- [ ] Ajouter des chenillards (bonus et/ou score)