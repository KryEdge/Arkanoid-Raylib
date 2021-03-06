#include "raylib.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace Arkanoid
{
extern int transformVolume(float volume);
extern void initializeLevel(Rectangle level[], int nivel);
extern void gameplay();

extern int const screenWidth;
extern int const screenHeight;
extern int const maxEnemies;
extern int playerLives;
extern int puntaje;
extern int enemigosRestantes;
extern int playerLives;
extern int numRand;
extern int pUpRand;
extern int contadorFireball;
extern int contadorNivel;

extern float volume;
extern float radio;
extern float radiopUp;

extern bool PLAYlong;
extern bool fireball;
extern bool game;
extern bool pause;


extern Color colorBola;

extern Rectangle Player1;
extern Rectangle hitbox[30];

extern Texture2D title;
extern Texture2D inst;
extern Texture2D player;
extern Texture2D backG;
extern Texture2D playerLONG;
extern Texture2D playerSHORT;
extern Texture2D credits;
extern Texture2D ball;
extern Texture2D fireB;
extern Texture2D longPUp;
extern Texture2D firePUp;
extern Texture2D speedPUp;
extern Texture2D lifePUp;
extern Texture2D backG;

extern Vector2 pUpPosition1;
extern Vector2 pUpPosition2;
extern Vector2 pUpPosition3;
extern Vector2 pUpPosition4;
extern Vector2 ballPosition;
}

#endif GAMEPLAY_H