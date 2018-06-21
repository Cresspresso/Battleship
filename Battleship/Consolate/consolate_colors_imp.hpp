//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_colors_imp.hpp
//	Description	:	Color namespace implementation file
//					for inline and template functions.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_COLORS_IMP_HPP__
#define __CONSOLATE_COLORS_IMP_HPP__

// Header for this Implementation file.
#include "consolate_colors.hpp"

// Implementation

namespace consolate
{
	namespace colors
	{
#pragma region // Inline Functions

		// Converts a foreground color to a background color.
		// For example, COLOR_Red => COLOR_BG_Red
		inline TColor ForeToBack(const TColor _ulkForegroundColor)
		{
			return (_ulkForegroundColor << 4) & 0xF0;
		}

		// Converts a background color to a foreground color.
		// For example, COLOR_BG_Red => COLOR_Red
		inline TColor BackToFore(const TColor _ulkBackgroundColor)
		{
			return (_ulkBackgroundColor >> 4) & 0x0F;
		}

		// Replaces the foreground of a color but keeps the background color.
		// NewForegroundColor must be a `COLOR_...` value.
		inline TColor ReplaceFore(
			const TColor _ulkOriginalColor,
			const TColor _ulkNewForegroundColor
		)
		{
			return (_ulkOriginalColor & 0xF0) | (_ulkNewForegroundColor & 0x0F);
		}

		// Replaces the background of a color but keeps the foreground color.
		// NewBackgroundColor must be a `COLOR_BG_...` value.
		inline TColor ReplaceBack(
			const TColor _ulkOriginalColor,
			const TColor _ulkNewBackgroundColor
		)
		{
			return (_ulkOriginalColor & 0x0F) | (_ulkNewBackgroundColor & 0xF0);
		}

#pragma endregion //~ Inline Functions

	} //~ colors

} //~ consolate

#endif //~ __CONSOLATE_COLORS_IMP_HPP__
