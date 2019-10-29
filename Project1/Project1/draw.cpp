#include "raylib.h"

#include "gameplay.h"

namespace Arkanoid
{
	float posxactual = 10.0f;
	float pUpY = (float)GetRandomValue(130, screenHeight - 80);
	float pUpX = (float)GetRandomValue(30, screenWidth - 30);
	int color1 = 0;
	int numberPUP = 0;
	bool PLAYshort = false;

	void drawUI()
	{
		DrawRectangle(0, 0, screenWidth, 20, BLACK);
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

		DrawText(FormatText("Volumen: %i", transformVolume(volume)), screenWidth / 2, 5, 15, WHITE);
		DrawText("SCORE: ", screenWidth - 110, 5, 15, WHITE);
		DrawText(FormatText(" %i", contadorP1), screenWidth - 60, 5, 15, WHITE);
	}

	void drawLevel(int i)
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
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, YELLOW);
				break;
			case 2:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, RED);
				break;
			case 3:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, BLUE);
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
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, YELLOW);
				break;
			case 2:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, RED);
				break;
			case 3:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, BLUE);
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
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, YELLOW);
				break;
			case 2:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, RED);
				break;
			case 3:
				DrawRectangle((int)posxactual, (int)hitbox[i].y, 70, 20, BLUE);
				break;
			default:
				break;
			}
			DrawRectangleRec(hitbox[i], YELLOW);
		}

		posxactual += 80;
	}

	void drawPowUps()
	{
		if (numRand == 200)
		{
			if (pUpRand == 0)
			{
				pUpX = (float)GetRandomValue(30, screenWidth - 30);
				pUpY = (float)GetRandomValue(130, screenHeight - 80);
				pUpRand = GetRandomValue(1, 4);
			}
			switch (pUpRand)
			{
			case 1:
				pUpPosition1.x = pUpX;
				pUpPosition1.y = pUpY;
				DrawCircleV(pUpPosition1, radiopUp, PINK);
				DrawTexture(longPUp, (int)(pUpPosition1.x - radiopUp), (int)(pUpPosition1.y - radiopUp), WHITE);
				break;
			case 2:
				pUpPosition2.x = pUpX;
				pUpPosition2.y = pUpY;
				DrawCircleV(pUpPosition2, radiopUp, GOLD);
				DrawTexture(speedPUp, (int)(pUpPosition2.x - radiopUp), (int)(pUpPosition2.y - radiopUp), WHITE);
				break;
			case 3:
				pUpPosition3.x = pUpX;
				pUpPosition3.y = pUpY;
				DrawCircleV(pUpPosition3, radiopUp, VIOLET);
				DrawTexture(lifePUp, (int)(pUpPosition3.x - radiopUp), (int)(pUpPosition3.y - radiopUp), WHITE);

				break;
			case 4:
				pUpPosition4.x = pUpX;
				pUpPosition4.y = pUpY;
				DrawCircleV(pUpPosition4, radiopUp, RED);
				DrawTexture(firePUp, (int)(pUpPosition4.x - radiopUp), (int)(pUpPosition4.y - radiopUp), WHITE);
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

	void drawPlayer()
	{
		switch (color1)
		{
		case 0:
			DrawRectangleRec(Player1, MAROON);
			DrawRectangle((int)Player1.x, (int)Player1.y, (int)Player1.width, 30, MAROON);
			break;
		case 1:
			DrawRectangleRec(Player1, BLUE);
			DrawRectangle((int)Player1.x, (int)Player1.y, (int)Player1.width, 30, BLUE);
			break;
		case 2:
			DrawRectangleRec(Player1, DARKGREEN);
			DrawRectangle((int)Player1.x, (int)Player1.y, (int)Player1.width, 30, DARKGREEN);
			break;
		case 3:
			DrawRectangleRec(Player1, DARKPURPLE);
			DrawRectangle((int)Player1.x, (int)Player1.y, (int)Player1.width, 30, DARKPURPLE);
			break;
		default:
			break;
		}

		if (!PLAYlong && !PLAYshort)
		{
			DrawTexture(player, (int)Player1.x, (int)Player1.y - 35, WHITE);
		}
		else if (PLAYlong)
		{
			DrawTexture(playerLONG, (int)Player1.x, (int)Player1.y - 35, WHITE);
		}
		else if (PLAYshort)
		{
			DrawTexture(playerSHORT, (int)Player1.x, (int)Player1.y - 35, WHITE);
		}
		DrawCircleV(ballPosition, radio, colorBola);

		if (!fireball)
		{
			DrawTexture(ball, (int)(ballPosition.x - radio), (int)(ballPosition.y - radio), WHITE);
		}
		else if (fireball)
		{
			DrawTexture(fireB, (int)(ballPosition.x - radio), (int)(ballPosition.y - radio), WHITE);
		}

	}

	void drawMenu()
	{

		ClearBackground(DARKGRAY);

		if (IsKeyUp(KEY_C) && IsKeyUp(KEY_X))
		{
			DrawTexture(title, screenWidth / 2 - 80, 0, WHITE);
			DrawText("C - Creditos", 10, 10, 30, WHITE);
			DrawText("X - Instrucciones", 10, 50, 30, WHITE);
			DrawText("P - Pausa (In Game)", 10, 90, 30, WHITE);
			DrawText("Puede subir y bajar el volumen con las teclas + y -", 160, 370, 20, WHITE);
			DrawText("Elija su color", 210, screenHeight / 2, 60, WHITE);
			DrawText("Presione Enter para jugar", 210, 400, 30, WHITE);
			DrawText("A             D", 270, 300, 40, WHITE);

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

		if (IsKeyDown(KEY_C))
		{
			DrawTexture(credits, 0, 0, WHITE);
		}
		if (IsKeyDown(KEY_X))
		{
			DrawTexture(inst, 0, 0, WHITE);
		}

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
			if (enemigosRestantes == maxEnemies)
			{
				initializeLevel(hitbox, contadorNivel);
			}
			UnloadTexture(title);
			UnloadTexture(credits);
			UnloadTexture(inst);
			game = true;
		}

	}

	void drawWinScreen()
	{

		ClearBackground(BLACK);
		DrawText("Felicidades!", 200, screenHeight / 4, 50, WHITE);
		DrawText(FormatText(" %i", contadorP1), 260, 300, 30, WHITE);
		DrawText(FormatText("Puntaje:"), 100, 300, 30, WHITE);

	}

	void drawGameOver()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("YOU DIED", 250, 100, 50, RED);
		DrawText(FormatText("Puntaje:"), 300, 200, 30, WHITE);
		DrawText(FormatText(" %i", contadorP1), 300, 250, 50, WHITE);
		DrawText("Press Enter", 230, 350, 50, RED);

		if (IsKeyPressed(KEY_ENTER))
		{
			playerLives = 3;
			contadorNivel = 1;
			enemigosRestantes = 30;
			title = LoadTexture("Assets/Title.png");
			credits = LoadTexture("Assets/PUP.png");
		}

		EndDrawing();
	}

	void draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(backG, 0, 0, WHITE);

		if (!game && contadorNivel == 1)
		{
			drawMenu();
		}

		if (game)
		{
			drawPlayer();
			for (int i = 0; i < maxEnemies; i++)
			{
				drawLevel(i);
			}
			if (playerLives > 0)
			{
				drawUI();
			}
			if (numberPUP < 1)
			{
				drawPowUps();
			}
		}

		if (!game && contadorNivel == 5 && playerLives > 0)
		{
			drawWinScreen();
		}

		if (!game && playerLives <= 0)
		{
			drawGameOver();
		}
		EndDrawing();

	}
}
