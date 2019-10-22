#include "raylib.h"

namespace Arkanoid
{
	extern const int screenWidth = 800;
	extern const int screenHeight = 450;
	extern const int maxEnemies = 30;

	int enemigosRestantes = 30;
	int playerLives = 3;
	int numRand = 0;
	int pUpRand = 0;
	int contadorFireball = 0;
	int contadorP1 = 0;
	int contadorNivel = 1;
	int nivelFinal = 5;
	int margenPantalla = 20;

	float directionx = 300.0f;
	float directiony = 420.0f;
	float radio = 20.0f;
	float radiopUp = 20.0f;
	float P1X = (float)(screenWidth / 2);
	float P1Y = 400;
	float speed = 500.0f;
	float playerWidth = 100.0f;
	float volume = 1.0f;

	bool PLAYlong = false;
	bool movIzq = false;
	bool movDer = false;
	bool fireball = false;
	bool game = false;

	Color colorBola = GREEN;

#pragma warning(disable:4204)
	Rectangle Player1 = { P1X, P1Y, playerWidth,30 };
#pragma warning(default:4204)
	Rectangle hitbox[30];

	Texture2D title = LoadTexture("Assets/Title.png");
	Texture2D inst = LoadTexture("Assets/Inst.png");
	Texture2D player = LoadTexture("Assets/P1.png");
	Texture2D backG = LoadTexture("Assets/fondo.jpg");
	Texture2D playerLONG = LoadTexture("Assets/P1long.png");
	Texture2D playerSHORT = LoadTexture("Assets/P1short.png");
	Texture2D credits = LoadTexture("Assets/Creditos.png");
	Texture2D ball = LoadTexture("Assets/ball.png");
	Texture2D fireB = LoadTexture("Assets/fireball.png");
	Texture2D longPUp = LoadTexture("Assets/long.png");
	Texture2D firePUp = LoadTexture("Assets/fire.png");
	Texture2D speedPUp = LoadTexture("Assets/speed.png");
	Texture2D lifePUp = LoadTexture("Assets/life.png");

	Music music = LoadMusicStream("Assets/Dirtygroove.ogg");
	Sound hitWav = LoadSound("Assets/hit.wav");
	Sound pickupWav = LoadSound("Assets/pickup.wav");

	Vector2 pUpPosition1 = { (int)0,(int)0 };
	Vector2 pUpPosition2 = { (int)0,(int)0 };
	Vector2 pUpPosition3 = { (int)0,(int)0 };
	Vector2 pUpPosition4 = { (int)0,(int)0 };
#pragma warning(disable:4204)
	Vector2 ballPosition = { P1X + radio , P1Y - radio };
#pragma warning(default:4204)

	int transformVolume(float volumen)
	{
		int vol = (int)(volumen * 100);
		return vol;
	}
	
	void initializeLevel(Rectangle level[], int nivel)
	{
		switch (nivel)
		{
		case 1:
			for (int i = 0; i < 30; i++)
			{
				if (i < 10)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
				else if (i >= 10 && i < 20)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
				if (i >= 20 && i < 30)
				{
					level[i].maxLives = 1;
					level[i].lives = 1;
				}
			}
			break;
		case 2:
			for (int i = 0; i < 30; i++)
			{
				if (i < 5)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
				else if (i >= 5 && i < 10)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
				else if (i >= 10 && i < 15)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
				else if (i >= 15 && i < 20)
				{
					level[i].maxLives = 1;
					level[i].lives = 1;
				}
				else if (i >= 20 && i < 25)
				{
					level[i].maxLives = 1;
					level[i].lives = 1;
				}
				else if (i >= 20 && i < 30)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
			}
			break;
		case 3:
			for (int i = 0; i < 30; i++)
			{
				if (i < 10)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
				else if (i >= 10 && i < 20)
				{
					level[i].maxLives = 1;
					level[i].lives = 1;
				}
				if (i >= 20 && i < 30)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
			}
			break;
		case 4:
			for (int i = 0; i < 30; i++)
			{
				if (i < 10)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
				else if (i >= 10 && i < 20)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
				if (i >= 20 && i < 30)
				{
					level[i].maxLives = 2;
					level[i].lives = 2;
				}
			}
			break;
		case 5:
			for (int i = 0; i < 30; i++)
			{
				if (i < 10)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
				else if (i >= 10 && i < 20)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
				if (i >= 20 && i < 30)
				{
					level[i].maxLives = 3;
					level[i].lives = 3;
				}
			}
			break;
		default:
			break;
		}
	}
	
	void gameplay()
	{
		InitAudioDevice();
		UpdateMusicStream(music);

		if (game)
		{
			initializeLevel(hitbox, contadorNivel);

			PlayMusicStream(music);
			SetMusicVolume(music, volume);
			SetSoundVolume(hitWav, volume);
			SetSoundVolume(pickupWav, volume);
			if (IsKeyPressed(KEY_KP_ADD))
			{
				if (volume < 1.0f)
				{
					volume += 0.10f;
				}
			}
			else if (IsKeyPressed(KEY_KP_SUBTRACT))
			{
				if (volume > 0.0f)
				{
					volume -= 0.10f;
				}
			}

			if (IsKeyPressed(KEY_P) && game)
			{
				game = false;
				title = LoadTexture("Assets/Title.png");
				inst = LoadTexture("Assets/Inst.png");
				credits = LoadTexture("Assets/Creditos.png");
			}

			if (ballPosition.y > screenHeight)
			{
				ballPosition.x = Player1.x + playerWidth / 2;
				ballPosition.y = Player1.y - 10;
				playerLives--;
				speed = 360;
				Player1.width = 100;
				radio = 20;
				PLAYlong = false;
				fireball = false;
				contadorFireball = 0;
			}
			if (contadorFireball >= 10)
			{
				fireball = false;
				colorBola = GREEN;
				contadorFireball = 0;
			}
			if (enemigosRestantes < 1)
			{
				enemigosRestantes = 30;
				contadorNivel++;
				initializeLevel(hitbox, contadorNivel);
			}

			if (IsKeyDown(KEY_A))
			{
				if (Player1.x > 0)
				{
					Player1.x -= speed * GetFrameTime();
				}
				movIzq = true;
				movDer = false;
			}

			if (IsKeyDown(KEY_D))
			{
				if (Player1.x + Player1.width < screenWidth)
				{
					Player1.x += speed * GetFrameTime();
				}
				movIzq = false;
				movDer = true;
			}


			ballPosition.x += directionx * GetFrameTime();
			ballPosition.y += directiony * GetFrameTime();

			if (ballPosition.x + radio > screenWidth || ballPosition.x - radio < 0)
			{
				directionx *= -1;
				ballPosition.x += directionx / 300;
				if (!IsSoundPlaying(hitWav))
				{
					PlaySound(hitWav);
				}
			}
			if (CheckCollisionCircleRec(ballPosition, radio, Player1))
			{
				if (movIzq)
				{
					if (directionx > 0)
					{
						directionx *= -1;
					}
				}
				else if (movDer)
				{
					if (directionx < 0)
					{
						directionx *= -1;
					}
				}
				if (!IsSoundPlaying(hitWav))
				{
					PlaySound(hitWav);
				}
			}
			if (ballPosition.y - radio < margenPantalla || CheckCollisionCircleRec(ballPosition, radio, Player1))
			{

				directiony *= -1;

				if (!IsSoundPlaying(hitWav))
				{
					PlaySound(hitWav);
				}
				if (CheckCollisionCircleRec(ballPosition, radio, Player1))
				{
					ballPosition.y -= radio / 2;
				}
			}
			for (int i = 0; i < 30; i++)
			{
				if (CheckCollisionCircleRec(ballPosition, radio, hitbox[i]))
				{
					if (hitbox[i].lives > 0)
					{
						hitbox[i].lives--;
						if (hitbox[i].lives == 0)
						{
							enemigosRestantes--;
						}
						if (!fireball)
						{
							directiony *= -1;
						}
						else
						{
							contadorFireball++;
						}
						ballPosition.y += radio / 2;

						contadorP1 += 42;
					}
				}
			}
			if (CheckCollisionCircles(ballPosition, radio, pUpPosition1, radiopUp))
			{
				if (!PLAYlong)
				{
					Player1.width = 200;
					PLAYlong = true;
					Player1.x += 42;
				}
				pUpPosition1.x = 0;
				pUpPosition1.y = 0;
				numRand = 0;
				pUpRand = 0;
				contadorP1 += 25;
				if (!IsSoundPlaying(pickupWav))
				{
					PlaySound(pickupWav);
				}
			}
			if (CheckCollisionCircles(ballPosition, radio, pUpPosition3, radiopUp))
			{
				if (playerLives < 3)
				{
					playerLives++;
				}
				pUpPosition3.x = 0;
				pUpPosition3.y = 0;
				numRand = 0;
				pUpRand = 0;
				contadorP1 += 25;
				if (!IsSoundPlaying(pickupWav))
				{
					PlaySound(pickupWav);
				}
			}
			if (CheckCollisionCircles(ballPosition, radio, pUpPosition2, radiopUp))
			{
				speed *= 1.5;
				pUpPosition2.x = 0;
				pUpPosition2.y = 0;
				numRand = 0;
				pUpRand = 0;
				contadorP1 += 25;
				if (!IsSoundPlaying(pickupWav))
				{
					PlaySound(pickupWav);
				}
			}

			if (CheckCollisionCircles(ballPosition, radio, pUpPosition4, radiopUp))
			{
				fireball = true;
				colorBola = RED;
				pUpPosition4.x = 0;
				pUpPosition4.y = 0;
				numRand = 0;
				pUpRand = 0;
				contadorP1 += 25;
				if (!IsSoundPlaying(pickupWav))
				{
					PlaySound(pickupWav);
				}
			}

			if ((contadorNivel == nivelFinal && enemigosRestantes == 0) || playerLives <= 0)
			{
				game = false;
			}
		}
	}
}
