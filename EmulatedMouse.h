#pragma once

#include <windows.h>

class EmulatedMouse
{
public:
	EmulatedMouse(int screenWidth, int screenHeight);
	~EmulatedMouse();

	void init();

	void moveAbsolute(int x, int y);

	void moveRelative(int x, int y);

	void click(DWORD msToHold = 10ul);

private:
	INPUT m_Buffer;
};
