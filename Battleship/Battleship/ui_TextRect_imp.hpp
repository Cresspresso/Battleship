//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_TextRect_imp.hpp
//	Description	:	TextRect class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_TEXT_RECT_IMP_HPP__
#define __UI_TEXT_RECT_IMP_HPP__

// This Include
#include "ui_TextRect.hpp"

// Implementation

namespace ui
{
	// Full Constructor.
	inline CTextRect::CTextRect(
		CVector2i _vPosition,
		CVector2i _vSize,
		const std::wstring& _rstrkText,
		consolate::TColor _ulNormalColor,
		consolate::TColor _ulFocusedColor,
		const consolate::SPanelStyle& _rtkPanelStyle,
		bool _bIsInteractable,
		bool _bIsFocused
	) :
		m_vSize(_vSize),
		m_strText(_rstrkText),
		m_tPanelStyle(_rtkPanelStyle),
		CElement(
			_vPosition,
			_ulNormalColor,
			_ulFocusedColor,
			_bIsInteractable,
			_bIsFocused
		)
	{
	}



	inline const std::wstring & CTextRect::GetText() const
	{
		return m_strText;
	}

	inline void CTextRect::SetText(const std::wstring& _rstrkText)
	{
		m_strText = _rstrkText;
	}



	inline CVector2i CTextRect::GetSize() const
	{
		return m_vSize;
	}

	inline void CTextRect::SetSize(CVector2i _vSize)
	{
		if (_vSize.m_tX < 3)
			_vSize.m_tX = 3;
		if (_vSize.m_tY < 3)
			_vSize.m_tY = 3;
		m_vSize = _vSize;
	}



	inline const consolate::SPanelStyle& CTextRect::GetPanelStyle() const
	{
		return m_tPanelStyle;
	}

	inline void CTextRect::SetPanelStyle(const consolate::SPanelStyle& _rtkPanelStyle)
	{
		m_tPanelStyle = _rtkPanelStyle;
	}

} //~ ui

#endif //~ __UI_TEXT_RECT_IMP_HPP__
