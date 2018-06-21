//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_ColorTable.hpp
//	Description	:	ColorTable type declaration file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_COLOR_TABLE_HPP__
#define __CONSOLATE_COLOR_TABLE_HPP__

// Library Includes
#include <windows.h>
#include <initializer_list>
#include <array>

// Declarations

namespace consolate
{
	// Number of elements in a ColorTable array.
	constexpr std::size_t COLORTABLE_LENGTH = 16;

#pragma region // Types

	// Palette of console text colors.
	using TColorTable = std::array<COLORREF, COLORTABLE_LENGTH>;

	// Raw array of 16 COLORREFs.
	using TRawColorTable = COLORREF[COLORTABLE_LENGTH];

#pragma endregion //~ Types

	namespace colortable
	{
#pragma region // Functions

		// Creates a ColorTable from a raw array.
		inline TColorTable CreateColorTable(const TRawColorTable& _rakSource);

		// Copies a ColorTable's values to a raw array.
		inline void CopyColorTable(
			const TColorTable& _rtkSource,
			TRawColorTable& _raDest
		);

		// Copies the color table values from one raw array to another.
		inline void CopyColorTable(
			const TRawColorTable& _rakSource,
			TRawColorTable& _raDest
		);

#pragma endregion //~ Functions

#pragma region // Constant Instances

		// Basic color table.
		extern const TColorTable COLORTABLE_BASIC;

		// Grayscale color table, from COLOR_0 = black to COLOR_15 = white.
		extern const TColorTable COLORTABLE_GRAYSCALE;

		// Vibrant color table. Intense colors like blue are easier to see.
		extern const TColorTable COLORTABLE_PASTEL;

#pragma endregion //~ Constant Instances

	} //~ colortable

} //~ consolate



// Include implementation for inline and template functions.
#include "consolate_ColorTable_imp.hpp"

#endif //~ __CONSOLATE_COLOR_TABLE_HPP__
