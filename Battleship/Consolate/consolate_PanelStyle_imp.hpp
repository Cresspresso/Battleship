//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_PanelStyle_imp.hpp
//	Description	:	PanelStyle struct implementation file
//					for inline and template functions.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_PANEL_STYLE_IMP_HPP__
#define __CONSOLATE_PANEL_STYLE_IMP_HPP__

// Header for this Implementation file.
#include "consolate_PanelStyle.hpp"

// Implementation

namespace consolate
{
#pragma region // Constructors

	// Default Constructor
	inline SPanelStyle::SPanelStyle(
		TCHAR _cFill,
		TColor _ulOutlineColor,
		TColor _ulFillColor
	) :
		m_cFill(_cFill),
		m_ulOutlineColor(_ulOutlineColor),
		m_ulFillColor(_ulFillColor)
	{
	}

	// Partial Constructor
	inline SPanelStyle::SPanelStyle(
		TCHAR _cTop,
		TCHAR _cBottom,
		TCHAR _cLeft,
		TCHAR _cRight,

		TCHAR _cTopLeft,
		TCHAR _cTopRight,
		TCHAR _cBottomLeft,
		TCHAR _cBottomRight,

		TCHAR _cFill,
		TColor _ulOutlineColor,
		TColor _ulFillColor
	) :
		m_cTop(_cTop),
		m_cBottom(_cBottom),
		m_cLeft(_cLeft),
		m_cRight(_cRight),

		m_cTopLeft(_cTopLeft),
		m_cTopRight(_cTopRight),
		m_cBottomLeft(_cBottomLeft),
		m_cBottomRight(_cBottomRight),

		m_cFill(_cFill),
		m_ulOutlineColor(_ulOutlineColor),
		m_ulFillColor(_ulFillColor)
	{
	}

	// Full Constructor
	inline SPanelStyle::SPanelStyle(
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

		TCHAR _cFill,
		TColor _ulOutlineColor,
		TColor _ulFillColor
	) :
		m_cTop(_cTop),
		m_cBottom(_cBottom),
		m_cLeft(_cLeft),
		m_cRight(_cRight),

		m_cTopLeft(_cTopLeft),
		m_cTopRight(_cTopRight),
		m_cBottomLeft(_cBottomLeft),
		m_cBottomRight(_cBottomRight),

		m_cTopT(_cTopT),
		m_cBottomT(_cBottomT),
		m_cLeftT(_cLeftT),
		m_cRightT(_cRightT),
		m_cCross(_cCross),

		m_cFill(_cFill),
		m_ulOutlineColor(_ulOutlineColor),
		m_ulFillColor(_ulFillColor)
	{
	}

	// Copy Constructor
	inline SPanelStyle::SPanelStyle(const SPanelStyle& _rtkOther)
		:
		m_cTop(_rtkOther.m_cTop),
		m_cBottom(_rtkOther.m_cBottom),
		m_cLeft(_rtkOther.m_cLeft),
		m_cRight(_rtkOther.m_cRight),

		m_cTopLeft(_rtkOther.m_cTopLeft),
		m_cTopRight(_rtkOther.m_cTopRight),
		m_cBottomLeft(_rtkOther.m_cBottomLeft),
		m_cBottomRight(_rtkOther.m_cBottomRight),

		m_cTopT(_rtkOther.m_cTopT),
		m_cBottomT(_rtkOther.m_cBottomT),
		m_cLeftT(_rtkOther.m_cLeftT),
		m_cRightT(_rtkOther.m_cRightT),
		m_cCross(_rtkOther.m_cCross),

		m_cFill(_rtkOther.m_cFill),
		m_ulOutlineColor(_rtkOther.m_ulOutlineColor),
		m_ulFillColor(_rtkOther.m_ulFillColor)
	{
	}

#pragma endregion //~ Constructors

} //~ consolate

#endif //~ __CONSOLATE_PANEL_STYLE_IMP_HPP__
