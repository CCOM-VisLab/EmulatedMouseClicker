#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <chrono>
#include "EmulatedMouse.h"

EmulatedMouse* g_pMouse;

double g_accumulatedSeconds;

double g_secondsBetweenClicks = 60.0;

int g_mousePosX = 1900;
int g_mousePosY = 20;

int main(int argc, char* argv[])
{
	g_pMouse = new EmulatedMouse(1920, 1080);
	g_pMouse->init();

	auto start = std::chrono::high_resolution_clock::now();

	g_accumulatedSeconds = 0.f;

	while (true)
	{
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		g_accumulatedSeconds += elapsed_seconds.count();

		if (g_accumulatedSeconds > g_secondsBetweenClicks)
		{
			g_accumulatedSeconds -= g_secondsBetweenClicks;

			g_pMouse->moveAbsolute(g_mousePosX, g_mousePosY);
			g_pMouse->click();

			std::cout << "Click!" << std::endl;
		}

		start = end;
	}

	return 0;
}