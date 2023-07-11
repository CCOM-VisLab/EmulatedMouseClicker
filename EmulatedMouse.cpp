#include "EmulatedMouse.h"

int m_screenWidth;
int m_screenHeight;

EmulatedMouse::EmulatedMouse(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_Buffer = INPUT();
}


EmulatedMouse::~EmulatedMouse()
{
}


void EmulatedMouse::init()
{
	m_Buffer.type = INPUT_MOUSE;
	m_Buffer.mi.dx = 0;
	m_Buffer.mi.dy = 0;
	m_Buffer.mi.mouseData = 0;
	m_Buffer.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	m_Buffer.mi.time = 0;
	m_Buffer.mi.dwExtraInfo = 0;
}


void EmulatedMouse::moveAbsolute(int x, int y)
{
	m_Buffer.mi.dx = (x * ((0xFFFF + 1) / m_screenWidth));
	m_Buffer.mi.dy = (y * ((0xFFFF + 1) / m_screenHeight));
	m_Buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

	SendInput(1, &m_Buffer, sizeof(INPUT));
}


void EmulatedMouse::moveRelative(int x, int y)
{
	m_Buffer.mi.dx = x;
	m_Buffer.mi.dy = y;
	m_Buffer.mi.dwFlags = (MOUSEEVENTF_MOVE);

	SendInput(1, &m_Buffer, sizeof(INPUT));
}


void EmulatedMouse::click(DWORD msToHold)
{
	m_Buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, &m_Buffer, sizeof(INPUT));

	Sleep(msToHold);

	m_Buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &m_Buffer, sizeof(INPUT));
}
