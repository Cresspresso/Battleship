//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_ColorTable.cpp
//	Description	:	ColorTable class implementation file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// This Include
#include "consolate_ColorTable.hpp"

// Implementation

namespace consolate
{
	namespace colortable
	{
#pragma region // Constant Instances

		// Basic color table.
		const TColorTable COLORTABLE_BASIC = {
			RGB(0, 0, 0),

			RGB(0, 0, 128),
			RGB(0, 128, 0),
			RGB(0, 128, 128),
			RGB(128, 0, 0),
			RGB(128, 0, 128),
			RGB(128, 128, 0),

			RGB(192, 192, 192),
			RGB(128, 128, 128),

			RGB(0, 0, 255),
			RGB(0, 255, 0),
			RGB(0, 255, 255),
			RGB(255, 0, 0),
			RGB(255, 0, 255),
			RGB(255, 255, 0),

			RGB(255, 255, 255),
		};

		// Grayscale color table, from COLOR_0 = black to COLOR_15 = white.
		const TColorTable COLORTABLE_GRAYSCALE = {
			RGB(0, 0, 0),
			RGB(0x11, 0x11, 0x11),
			RGB(0x22, 0x22, 0x22),
			RGB(0x33, 0x33, 0x33),
			RGB(0x44, 0x44, 0x44),
			RGB(0x55, 0x55, 0x55),
			RGB(0x66, 0x66, 0x66),
			RGB(0x77, 0x77, 0x77),
			RGB(0x88, 0x88, 0x88),
			RGB(0x99, 0x99, 0x99),
			RGB(0xAA, 0xAA, 0xAA),
			RGB(0xBB, 0xBB, 0xBB),
			RGB(0xCC, 0xCC, 0xCC),
			RGB(0xDD, 0xDD, 0xDD),
			RGB(0xEE, 0xEE, 0xEE),
			RGB(0xFF, 0xFF, 0xFF),
		};

		// Vibrant color table. Intense colors like blue are easier to see.
		const TColorTable COLORTABLE_PASTEL = {
			RGB(0, 0, 0),

			RGB(0, 0, 160),
			RGB(0, 160, 0),
			RGB(0, 110, 110),
			RGB(160, 0, 0),
			RGB(110, 0, 110),
			RGB(110, 110, 0),

			RGB(200, 200, 200),
			RGB(128, 128, 128),

			RGB(110, 110, 255),
			RGB(110, 255, 110),
			RGB(70, 255, 255),
			RGB(255, 110, 110),
			RGB(255, 70, 255),
			RGB(255, 255, 70),

			RGB(255, 255, 255),
		};

#pragma endregion //~ Constant Instances

	} //~ colortable

} //~ consolate
