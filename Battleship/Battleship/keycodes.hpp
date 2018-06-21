//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	KeyCodeEnums.hpp
//	Description	:	Declaration file for enums: KeyCode, KeyCodeEx, KeyCodeEx2.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __KEYCODES_HPP__
#define __KEYCODES_HPP__

// Declarations

namespace keycodes
{
	using TKeyCode = int;
	using TKeyCodeEx = int;
	using TKeyCodeEx2 = int;

	// Key codes for the keyboard.
	// This enum does not contain all possible keys.
	enum EKeyCode
	{
		KEYCODE_EX = 0xE0,
		KEYCODE_EX2 = 0,

		// Normal Keys
		KEYCODE_BACKSPACE = 8,
		KEYCODE_ENTER = 13,
		KEYCODE_ESCAPE = 27,
		KEYCODE_SPACE = 32,
		KEYCODE_TAB = 9,

		// CTRL Modified Keys
		KEYCODE_CTRL_ENTER = 10,
	};

	// Key codes for extended keys.
	// This enum does not contain all possible keys.
	enum EKeyCodeEx
	{
		// Normal 
		KEYCODE_EX_ARROW_DOWN = 80,
		KEYCODE_EX_ARROW_LEFT = 75,
		KEYCODE_EX_ARROW_RIGHT = 77,
		KEYCODE_EX_ARROW_UP = 72,
		KEYCODE_EX_DELETE = 83,
		KEYCODE_EX_END = 79,
		KEYCODE_EX_HOME = 71,
		KEYCODE_EX_INSERT = 82,
		KEYCODE_EX_PAGE_DOWN = 81,
		KEYCODE_EX_PAGE_UP = 73,

		// CTRL Modified Keys
		KEYCODE_EX_CTRL_DELETE = 147,
		KEYCODE_EX_CTRL_END = 117,
		KEYCODE_EX_CTRL_HOME = 119,
		KEYCODE_EX_CTRL_INSERT = 146,
		KEYCODE_EX_CTRL_TAB = 143,
		KEYCODE_EX_CTRL_PAGE_DOWN = 118,
		KEYCODE_EX_CTRL_PAGE_UP = 134,
	};

	// Key codes for secondary extended keys.
	// This enum does not contain all possible keys.
	enum EKeyCodeEx2
	{
		// ALT Modified Keys
		KEYCODE_EX2_ALT_ARROW_DOWN = 160,
		KEYCODE_EX2_ALT_ARROW_LEFT = 155,
		KEYCODE_EX2_ALT_ARROW_RIGHT = 157,
		KEYCODE_EX2_ALT_ARROW_UP = 152,
		KEYCODE_EX2_ALT_DELETE = 163,
		KEYCODE_EX2_ALT_END = 159,
		KEYCODE_EX2_ALT_HOME = 151,
		KEYCODE_EX2_ALT_PAGE_DOWN = 161,
		KEYCODE_EX2_ALT_PAGE_UP = 153,
	};

} //~ input

#endif //~ __KEYCODES_HPP__
