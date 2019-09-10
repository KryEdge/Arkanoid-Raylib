#include "raylib.h"

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
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	const int maxEnemies = 30;
	int enemigosRestantes = 30;
	Rectangle hitbox[30];

	int playerLives = 3;
	int color1 = 0;
	int numberPUP = 0;
	int numRand = 0;
	int pUpRand = 0;
	Color colorBola = GREEN;
	bool game = false;
	bool win = false;
	int directionx = 4;
	int directiony = 4;
	const float incremento = 0.3;
	int contadorP1 = 0;
	int speed = 7;
	int playerWidth = 100;
	bool PLAYlong = false;
	bool PLAYshort = false;
	float P1X = screenWidth / 2;
	float P1Y = 400;
	Rectangle Player1 = { P1X, P1Y, playerWidth,30 };
	int contadorNivel = 1;

	InitWindow(screenWidth, screenHeight, "Bad Arkanoid");
	InitAudioDevice();

	Texture2D title = LoadTexture("Assets/Title.png");
	Texture2D player = LoadTexture("Assets/P1.png");
	Texture2D backG = LoadTexture("Assets/fondo.jpg");
	Texture2D playerLONG = LoadTexture("Assets/P1long.png");
	Texture2D playerSHORT = LoadTexture("Assets/P1short.png");

	Music music = LoadMusicStream("Assets/Hydrogen.ogg");
	Sound hitWav = LoadSound("Assets/hit.wav");
	Sound pickupWav = LoadSound("Assets/pickup.wav");

	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	Vector2 pUpPosition1 = { (int)0,(int)0 };
	Vector2 pUpPosition2 = { (int)0,(int)0 };
	Vector2 pUpPosition3 = { (int)0,(int)0 };
	Vector2 pUpPosition4 = { (int)0,(int)0 };
	bool fireball = false;
	int contadorFireball = 0;
	int pUpY;
	int pUpX;
	int radio = 20;
	int radiopUp = 20;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	initializeLevel(hitbox, contadorNivel);
	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateMusicStream(music);
		if (game)
		{
			PlayMusicStream(music);

			if (ballPosition.y > screenHeight)
			{
				ballPosition.x = Player1.x + playerWidth / 2;
				ballPosition.y = Player1.y - 10;
				playerLives--;
				speed = 7;
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
			if(enemigosRestantes == 0)
			{
				enemigosRestantes = 30;
				contadorNivel++;
				initializeLevel(hitbox, contadorNivel);
			}

			if (IsKeyDown(KEY_A))
			{
				if (Player1.x > 0)
				{
					Player1.x -= speed;
				}
			}

			if (IsKeyDown(KEY_D))
			{
				if (Player1.x + Player1.width < screenWidth)
				{
					Player1.x += speed;
				}
			}

			ballPosition.x += directionx;
			ballPosition.y += directiony;

			if (ballPosition.x + radio > screenWidth || ballPosition.x - radio < 20)
			{
				directionx *= -1.1;
				if (!IsSoundPlaying(hitWav))
				{
					PlaySound(hitWav);
				}
			}
			if (CheckCollisionCircleRec(ballPosition, radio, Player1))
			{
				switch (GetRandomValue(1, 2))
				{
				case 1:
					directionx *= -1;
					break;
				case 2:
					break;
				}
				if (!IsSoundPlaying(hitWav))
				{
					PlaySound(hitWav);
				}
			}
			if (ballPosition.y - radio < 20 || CheckCollisionCircleRec(ballPosition, radio, Player1))
			{

				directiony *= -1.1;

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
				Player1.width = 200;
				PLAYlong = true;
				Player1.x += 42;
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
				radio = 40;
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
				speed = 10;
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

			if ((contadorNivel == 5 && enemigosRestantes == 0) || playerLives <= 0)
			{
				game = false;
			}
			//----------------------------------------------------------------------------------

			// Draw
			//----------------------------------------------------------------------------------

			BeginDrawing();
			ClearBackground(BLACK);
			int posxactual = 10;
			DrawTexture(backG, 0, 0, WHITE);

			DrawRectangle(0, 0, screenWidth, 20, BLACK);//DIBUJO "UI"
			if(playerLives > 0)
			{
				DrawText("LIVES: ", 5, 5, 15, WHITE);
				switch (playerLives)
				{
				case 1:
					DrawRectangle(60, 5, 30, 10, WHITE);
					break;
				case 2:
					DrawRectangle(60, 5, 30, 10, WHITE);
					DrawRectangle(95, 5, 30, 10, WHITE);
					break;
				case 3:
					DrawRectangle(60, 5, 30, 10, WHITE);
					DrawRectangle(95, 5, 30, 10, WHITE);
					DrawRectangle(130, 5, 30, 10, WHITE);
					break;
				default:
					break;
				}
			}
			DrawText(FormatText(" %i", contadorP1), screenWidth-60, 5, 15, WHITE);
			DrawText("SCORE: ", screenWidth-110, 5, 15, WHITE);


			for (int i = 0; i < maxEnemies; i++)//DIBUJO NIVEL
			{
				if (i == 10) posxactual = 10;
				if (i == 20) posxactual = 10;

				if (i < 10)
				{
					hitbox[i].x = posxactual;
					hitbox[i].y = 30;
					hitbox[i].width = 70;
					hitbox[i].height = 20;
					switch (hitbox[i].lives)
					{
					case 1:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, YELLOW);
						break;
					case 2:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, RED);
						break;
					case 3:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, BLUE);
						break;
					default:
						break;
					}
					DrawRectangleRec(hitbox[i], RED);

				}

				if (i >= 10 && i < 20)
				{
					hitbox[i].x = posxactual;
					hitbox[i].y = 70;
					hitbox[i].width = 70;
					hitbox[i].height = 20;
					switch (hitbox[i].lives)
					{
					case 1:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, YELLOW);
						break;
					case 2:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, RED);
						break;
					case 3:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, BLUE);
						break;
					default:
						break;
					}
					DrawRectangleRec(hitbox[i], BLUE);
				}
				
				if (i >= 20) 
				{
					hitbox[i].x = posxactual;
					hitbox[i].y = 110;
					hitbox[i].width = 70;
					hitbox[i].height = 20;
					DrawRectangleRec(hitbox[i], YELLOW);
					switch (hitbox[i].lives)
					{
					case 1:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, YELLOW);
						break;
					case 2:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, RED);
						break;
					case 3:
						DrawRectangle(posxactual, hitbox[i].y, 70, 20, BLUE);
						break;
					default:
						break;
					}
					DrawRectangleRec(hitbox[i], YELLOW);
				}

				posxactual += 80;
			}

			if (numberPUP < 1)//DIBUJO POWERUPS
			{
				if (numRand == 200)
				{
					if (pUpRand == 0)
					{
						pUpX = GetRandomValue(30, screenWidth - 40);
						pUpY = GetRandomValue(130, screenHeight - 40);
						pUpRand = GetRandomValue(1, 4);
					}
					switch (pUpRand)
					{
					case 1:
						pUpPosition1.x = pUpX;
						pUpPosition1.y = pUpY;
						DrawCircleV(pUpPosition1, radiopUp, PINK);
						break;
					case 2:
						pUpPosition2.x = pUpX;
						pUpPosition2.y = pUpY;
						DrawCircleV(pUpPosition2, radiopUp, GOLD);
						break;
					case 3:
						pUpPosition3.x = pUpX;
						pUpPosition3.y = pUpY;
						DrawCircleV(pUpPosition3, radiopUp, VIOLET);
						break;
					case 4:
						pUpPosition4.x = pUpX;
						pUpPosition4.y = pUpY;
						DrawCircleV(pUpPosition4, radiopUp, RED);
						break;
					default:
						break;
					}
				}
				else
				{
					numRand = GetRandomValue(0, 200);
				}
			}

			switch (color1)
			{
			case 0:
				DrawRectangleRec(Player1, MAROON);
				DrawRectangle(Player1.x, Player1.y, Player1.width, 30, MAROON);
				break;
			case 1:
				DrawRectangleRec(Player1, BLUE);
				DrawRectangle(Player1.x, Player1.y, Player1.width, 30, BLUE);
				break;
			case 2:
				DrawRectangleRec(Player1, DARKGREEN);
				DrawRectangle(Player1.x, Player1.y, Player1.width, 30, DARKGREEN);
				break;
			case 3:
				DrawRectangleRec(Player1, DARKPURPLE);
				DrawRectangle(Player1.x, Player1.y, Player1.width, 30, DARKPURPLE);
				break;
			default:
				break;
			}


			if (!PLAYlong && !PLAYshort)
			{
				DrawTexture(player, Player1.x, Player1.y - 35, WHITE);
			}
			else if (PLAYlong)
			{
				DrawTexture(playerLONG, Player1.x, Player1.y - 35, WHITE);
			}
			else if (PLAYshort)
			{
				DrawTexture(playerSHORT, Player1.x, Player1.y - 35, WHITE);
			}

			DrawCircleV(ballPosition, radio, colorBola);

			EndDrawing();
		}
		else if (!game && contadorNivel == 1 && enemigosRestantes == 30)
		{
			BeginDrawing();
			ClearBackground(DARKGRAY);

			DrawTexture(title, screenWidth / 2 - 80, 0, WHITE);

			DrawText("Elija su color", 210, screenHeight / 2, 60, WHITE);
			DrawText("Presione Enter para jugar", 210, 400, 30, WHITE);
			DrawText("A             D", 270, 300, 40, WHITE);
			EndDrawing();

			if (IsKeyPressed(KEY_A))
			{
				if (color1 > 0)
				{
					color1--;
				}
			}
			if (IsKeyPressed(KEY_D))
			{
				if (color1 < 3)
				{
					color1++;
				}
			}

			if (IsKeyPressed(KEY_ENTER))
			{
				UnloadTexture(title);
				game = true;
			}
			switch (color1)
			{
			case 0:
				DrawRectangle(300, 300, 200, 40, MAROON);
				break;
			case 1:
				DrawRectangle(300, 300, 200, 40, BLUE);
				break;
			case 2:
				DrawRectangle(300, 300, 200, 40, DARKGREEN);
				break;
			case 3:
				DrawRectangle(300, 300, 200, 40, DARKPURPLE);
				break;
			default:
				break;
			}

		}
		if (!game && contadorNivel == 5 && playerLives > 0)
		{
			StopMusicStream(music);
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Felicidades!", 200, screenHeight / 4, 50, WHITE);			
			DrawText(FormatText(" %i", contadorP1), 260, 300, 30, WHITE);
			DrawText(FormatText("Puntaje:"), 100, 300, 30, WHITE);

			EndDrawing();
		}
		if (!game && playerLives <= 0)
		{
			StopMusicStream(music);
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("YOU DIED", 200, screenHeight / 2, 50, RED);
			DrawText(FormatText(" %i", contadorP1), 340, 300, 50, WHITE);
			DrawText(FormatText("Puntaje:"), 200, 300, 30, WHITE);
			if (IsKeyPressed(KEY_ENTER))
			{
				playerLives = 3;
				contadorNivel = 1;
				enemigosRestantes = 30;
				LoadTexture("Assets/Title.png");
			}
			EndDrawing();
		}
		//----------------------------------------------------------------------------------
	}
	// De-Initialization
	//--------------------------------------------------------------------------------------

	CloseAudioDevice();

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
