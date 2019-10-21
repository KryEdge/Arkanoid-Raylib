#include "raylib.h"

#include "game.h"
#include "gameplay.h"

using namespace Arkanoid;

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Bad Arkanoid");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		playGame();
	}
	CloseAudioDevice();
	CloseWindow();
	return 0;

}
