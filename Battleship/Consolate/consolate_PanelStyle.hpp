//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Consolate_PanelStyle.hpp
//	Description	:	PanelStyle struct declaration file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_PANEL_STYLE_HPP__
#define __CONSOLATE_PANEL_STYLE_HPP__

// Library Includes
#include <windows.h>

// Local Includes
#include "consolate_colors.hpp"

// Declarations

namespace consolate
{
	// Character set for styling panels in consolate.
	struct SPanelStyle
	{
#pragma region // Methods
	public:

#pragma region // Constructors and Destructors

		// Default Constructor.
		inline SPanelStyle(
			TCHAR _cFill = TEXT(' '),
			TColor _ulOutlineColor = colors::COLOR_DEFAULT,
			TColor _ulFillColor = colors::COLOR_DEFAULT
		);

		// Partial Constructor.
		inline SPanelStyle(
			TCHAR _cTop,
			TCHAR _cBottom,
			TCHAR _cLeft,
			TCHAR _cRight,

			TCHAR _cTopLeft,
			TCHAR _cTopRight,
			TCHAR _cBottomLeft,
			TCHAR _cBottomRight,

			TCHAR _cFill = TEXT(' '),
			TColor _ulOutlineColor = colors::COLOR_DEFAULT,
			TColor _ulFillColor = colors::COLOR_DEFAULT
		);

		// Full Constructor.
		inline SPanelStyle(
			TCHAR _cTop,
			TCHAR _cBottom,
			TCHAR _cLeft,
			TCHAR _cRight,

			TCHAR _cTopLeft,
			TCHAR _cTopRight,
			TCHAR _cBottomLeft,
			TCHAR _cBottomRight,

			TCHAR _cTopT,
			TCHAR _cBottomT,
			TCHAR _cLeftT,
			TCHAR _cRightT,
			TCHAR _cCross,

			TCHAR _cFill = TEXT(' '),
			TColor _ulOutlineColor = colors::COLOR_DEFAULT,
			TColor _ulFillColor = colors::COLOR_DEFAULT
		);

		// Copy Constructor.
		inline SPanelStyle(const SPanelStyle& _rtkOther);

		// Destructor.
		inline ~SPanelStyle() = default;

#pragma endregion //~ Constructors and Destructors

#pragma endregion //~ Methods

#pragma region // Member Variables
	public:

		TCHAR m_cTop;
		TCHAR m_cBottom;
		TCHAR m_cLeft;
		TCHAR m_cRight;

		TCHAR m_cTopLeft;
		TCHAR m_cTopRight;
		TCHAR m_cBottomLeft;
		TCHAR m_cBottomRight;

		TCHAR m_cTopT;
		TCHAR m_cBottomT;
		TCHAR m_cLeftT;
		TCHAR m_cRightT;
		TCHAR m_cCross;

		TCHAR m_cFill;

		TColor m_ulOutlineColor;
		TColor m_ulFillColor;

#pragma endregion //~ Member Variables

#pragma region // Static Constant Instances

	public:

		// Panel style with single-lined border.
		static const SPanelStyle PANELSTYLE_SINGLE;

		// Panel style with double-lined border.
		static const SPanelStyle PANELSTYLE_DOUBLE;

#pragma endregion //~ Static Constant Instances
	};

} //~ consolate



// Include implementation for inline and template functions.
#include "consolate_PanelStyle_imp.hpp"

#endif //~ __CONSOLATE_PANEL_STYLE_HPP__
