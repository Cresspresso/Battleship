//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Input.hpp
//	Description	:	Input class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __INPUT_HPP__
#define __INPUT_HPP__

// Library Includes
#include <functional>	// function<>

// Local Includes
#include "keycodes.hpp"

// Declarations

class CInput
{
	// Types
public:

	// Event handler for a key press.
	using TKeyPressedEvent = std::function<void(const keycodes::TKeyCode)>;

	// Event handler for a key press of an extended keycode.
	using TKeyExPressedEvent = std::function<void(const keycodes::TKeyCodeEx)>;

	// Event handler for a key press of a secondary extended keycode.
	using TKeyEx2PressedEvent = std::function<void(const keycodes::TKeyCodeEx2)>;



	// Methods
public:

	// Waits for a key press on the keyboard, then invokes a KeyCode-related event.
	void WaitForKeyPress();

	// Clears event handlers.
	void ClearEventHandlers();



	// Member Variables
public:

	// Event handler for a key press.
	TKeyPressedEvent m_fnOnKeyPressed = nullptr;

	// Event handler for a key press of an extended keycode.
	TKeyExPressedEvent m_fnOnKeyExPressed = nullptr;

	// Event handler for a key press of a secondary extended keycode.
	TKeyEx2PressedEvent m_fnOnKeyEx2Pressed = nullptr;

};

// Singleton Instance.
extern CInput g_tInput;

#endif //~ __INPUT_HPP__
