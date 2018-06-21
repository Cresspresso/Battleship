//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Button_imp.hpp
//	Description	:	Button class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_BUTTON_IMP_HPP__
#define __UI_BUTTON_IMP_HPP__

// This Include
#include "ui_Button.hpp"

// Implementation

namespace ui
{
	// Full Constructor.
	inline CButton::CButton(
		TEventAction _fnOnInputEventEnter,
		TEventAction _fnOnInputEventSpace,
		CVector2i _vPosition,
		CVector2i _vSize,
		const std::wstring& _rstrkText,
		consolate::TColor _ulNormalColor,
		consolate::TColor _ulFocusedColor,
		const consolate::SPanelStyle& _rtkPanelStyle,
		bool _bIsInteractable,
		bool _bIsFocused
	) :
		m_fnOnInputEventEnter(_fnOnInputEventEnter),
		m_fnOnInputEventSpace(_fnOnInputEventSpace),
		CTextRect(
			_vPosition,
			_vSize,
			_rstrkText,
			_ulNormalColor,
			_ulFocusedColor,
			_rtkPanelStyle,
			_bIsInteractable,
			_bIsFocused
		)
	{
	}



	inline void CButton::SetOnInputEventEnter(TEventAction _fnOnInputEventEnter)
	{
		m_fnOnInputEventEnter = _fnOnInputEventEnter;
	}

	inline void CButton::SetOnInputEventSpace(TEventAction _fnOnInputEventSpace)
	{
		m_fnOnInputEventSpace = _fnOnInputEventSpace;
	}

} //~ ui

#endif //~ __UI_BUTTON_IMP_HPP__
