//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Input.hpp
//	Description	:	Input class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <conio.h>

// This Include
#include "Input.hpp"

// Implementation

// Waits for a key press on the keyboard, then invokes a KeyCode-related event.
void CInput::WaitForKeyPress()
{
	using namespace keycodes;

	// get keycode
	int iKey = _getch();
	if (iKey == KEYCODE_EX)
	{
		// get extended keycode
		int iKeyEx = _getch();

		// invoke event
		if (m_fnOnKeyExPressed != nullptr)
		{
			m_fnOnKeyExPressed(static_cast<TKeyCodeEx>(iKeyEx));
		}
	}
	else if (iKey == KEYCODE_EX2)
	{
		// get secondary extended keycode
		int iKeyEx2 = _getch();

		// invoke event
		if (m_fnOnKeyEx2Pressed != nullptr)
		{
			m_fnOnKeyEx2Pressed(static_cast<TKeyCodeEx2>(iKeyEx2));
		}
	}
	else
	{
		// normal key

#ifdef NDEBUG
		_getch(); // Skip strange '\0' that appears.
#endif //~ NDEBUG

		// invoke event
		if (m_fnOnKeyPressed != nullptr)
		{
			m_fnOnKeyPressed(static_cast<TKeyCode>(iKey));
		}
	}
}

// Clears event handlers.
void CInput::ClearEventHandlers()
{
	m_fnOnKeyPressed = nullptr;
	m_fnOnKeyExPressed = nullptr;
	m_fnOnKeyEx2Pressed = nullptr;
}

// Singleton Instance.
CInput g_tInput;
