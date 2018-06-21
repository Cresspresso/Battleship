//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_colors.hpp
//	Description	:	Color namespace declaration file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_COLORS_HPP__
#define __CONSOLATE_COLORS_HPP__

// Library Includes
#include <windows.h>

// Declarations

namespace consolate
{
	// Value type representing a foreground and background color for console text.
	using TColor = WORD;


	namespace colors
	{
		// Some useful values for specifying console text colors.
		// Implicitly convertable to TColor.
		// Combine foreground and background like so:
		//		(COLOR_White | COLOR_BG_Blue)
		// COLOR_... values have a Black background on their own.
		// COLOR_BG_... values have a Black foreground on their own.
		// 
		// NOTE: disregards coding standard for enum definition because
		// it is a collection of constant integers, not an enumeration.
		enum EColor
		{
#pragma region // Indexed Colors

			COLOR_0 = 0x00,
			COLOR_1 = 0x01,
			COLOR_2 = 0x02,
			COLOR_3 = 0x03,
			COLOR_4 = 0x04,
			COLOR_5 = 0x05,
			COLOR_6 = 0x06,
			COLOR_7 = 0x07,
			COLOR_8 = 0x08,
			COLOR_9 = 0x09,
			COLOR_10 = 0x0A,
			COLOR_11 = 0x0B,
			COLOR_12 = 0x0C,
			COLOR_13 = 0x0D,
			COLOR_14 = 0x0E,
			COLOR_15 = 0x0F,

			COLOR_BG_0 = 0x00,
			COLOR_BG_1 = 0x10,
			COLOR_BG_2 = 0x20,
			COLOR_BG_3 = 0x30,
			COLOR_BG_4 = 0x40,
			COLOR_BG_5 = 0x50,
			COLOR_BG_6 = 0x60,
			COLOR_BG_7 = 0x70,
			COLOR_BG_8 = 0x80,
			COLOR_BG_9 = 0x90,
			COLOR_BG_10 = 0xA0,
			COLOR_BG_11 = 0xB0,
			COLOR_BG_12 = 0xC0,
			COLOR_BG_13 = 0xD0,
			COLOR_BG_14 = 0xE0,
			COLOR_BG_15 = 0xF0,

#pragma endregion //~ Indexed Colors

#pragma region // Named Colors
			// Corresponding Color Names when using the default Windows ColorTable.

			COLOR_BLACK = 0x00,				// Black (Foreground)
			COLOR_DARK_BLUE = 0x01,			// Dark Blue (Foreground)
			COLOR_DARK_GREEN = 0x02,		// Dark Green (Foreground)
			COLOR_DARK_CYAN = 0x03,			// Dark Cyan (Foreground)
			COLOR_DARK_RED = 0x04,			// Dark Red (Foreground)
			COLOR_DARK_MAGENTA = 0x05,		// Dark Magenta (Foreground)
			COLOR_DARK_YELLOW = 0x06,		// Dark Yellow (Foreground)
			COLOR_GRAY = 0x07,				// Light Gray (Foreground)
			COLOR_DARK_GRAY = 0x08,			// Dark Gray (Foreground)
			COLOR_BLUE = 0x09,				// Light Blue (Foreground)
			COLOR_GREEN = 0x0A,				// Light Green (Foreground)
			COLOR_CYAN = 0x0B,				// Light Cyan (Foreground)
			COLOR_RED = 0x0C,				// Light Red (Foreground)
			COLOR_MAGENTA = 0x0D,			// Light Magenta (Foreground)
			COLOR_YELLOW = 0x0E,			// Light Yellow (Foreground)
			COLOR_WHITE = 0x0F,				// White (Foreground)

			COLOR_BG_BLACK = 0x00,			// Black (Background)
			COLOR_BG_DARK_BLUE = 0x10,		// Dark Blue (Background)
			COLOR_BG_DARK_GREEN = 0x20,		// Dark Green (Background)
			COLOR_BG_DARK_CYAN = 0x30,		// Dark Cyan (Background)
			COLOR_BG_DARK_RED = 0x40,		// Dark Red (Background)
			COLOR_BG_DARK_MAGENTA = 0x50,	// Dark Magenta (Background)
			COLOR_BG_DARK_YELLOW = 0x60,	// Dark Yellow (Background)
			COLOR_BG_GRAY = 0x70,			// Light Gray (Background)
			COLOR_BG_DARK_GRAY = 0x80,		// Dark Gray (Background)
			COLOR_BG_BLUE = 0x90,			// Light Blue (Background)
			COLOR_BG_GREEN = 0xA0,			// Light Green (Background)
			COLOR_BG_CYAN = 0xB0,			// Light Cyan (Background)
			COLOR_BG_RED = 0xC0,			// Light Red (Background)
			COLOR_BG_MAGENTA = 0xD0,		// Light Magenta (Background)
			COLOR_BG_YELLOW = 0xE0,			// Light Yellow (Background)
			COLOR_BG_WHITE = 0xF0,			// White (Background)

#pragma endregion //~ Named Colors

			// Default Color of Windows Console.
			COLOR_DEFAULT = COLOR_GRAY | COLOR_BG_BLACK,

		};

#pragma region // Inline Functions

		// Converts a foreground color to a background color.
		// For example, COLOR_Red => COLOR_BG_Red
		inline TColor ForeToBack(const TColor _ulkForeground);

		// Converts a background color to a foreground color.
		// For example, COLOR_BG_Red => COLOR_Red
		inline TColor BackToFore(const TColor _ulkBackground);

		// Replaces the foreground of a color but keeps the background color.
		// NewForegroundColor must be a `COLOR_...` value.
		inline TColor ReplaceFore(
			const TColor _ulkOriginalColor,
			const TColor _ulkNewForegroundColor
		);

		// Replaces the background of a color but keeps the foreground color.
		// NewBackgroundColor must be a `COLOR_BG_...` value.
		inline TColor ReplaceBack(
			const TColor _ulkOriginalColor,
			const TColor _ulkNewBackgroundColor
		);

#pragma endregion //~ Inline Functions

	} //~ colors

} //~ consolate



// Include implementation for inline and template functions.
#include "consolate_colors_imp.hpp"

#endif //~ __CONSOLATE_COLORS_HPP__
