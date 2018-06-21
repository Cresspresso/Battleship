//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Toggle_imp.hpp
//	Description	:	Toggle class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_TOGGLE_IMP_HPP__
#define __UI_TOGGLE_IMP_HPP__

// This Include
#include "ui_Toggle.hpp"

// Implementation

namespace ui
{
	// Full Constructor.
	inline CToggle::CToggle(
		TEventToggle _fnOnToggle,
		CVector2i _vPosition,
		CVector2i _vSize,
		const std::wstring& _rstrkText,
		bool _bDefaultToggleValue,
		consolate::TColor _ulNormalColor,
		consolate::TColor _ulFocusedColor,
		consolate::TColor _ulNormalColorOn,
		consolate::TColor _ulFocusedColorOn,
		const consolate::SPanelStyle& _rtkPanelStyle,
		bool _bIsInteractable,
		bool _bIsFocused
	) :
		m_fnOnToggle(_fnOnToggle),
		m_bDefaultToggleValue(_bDefaultToggleValue),
		m_bToggleValue(_bDefaultToggleValue),
		m_ulNormalColorOn(_ulNormalColorOn),
		m_ulFocusedColorOn(_ulFocusedColorOn),
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



	inline bool CToggle::GetToggleValue() const
	{
		return m_bToggleValue;
	}

	inline void CToggle::SetToggleValue(bool _bToggleValue)
	{
		m_bToggleValue = _bToggleValue;

		if (m_fnOnToggle != nullptr)
		{
			m_fnOnToggle(*this);
		}
	}



	inline bool CToggle::GetDefaultToggleValue() const
	{
		return m_bDefaultToggleValue;
	}

	inline void CToggle::SetDefaultToggleValue(bool _bDefaultToggleValue)
	{
		m_bDefaultToggleValue = _bDefaultToggleValue;
	}



	inline void CToggle::SetOnToggle(TEventToggle _fnOnToggle)
	{
		m_fnOnToggle = _fnOnToggle;
	}



	inline consolate::TColor CToggle::GetNormalColorOn() const
	{
		return m_ulNormalColorOn;
	}

	inline void CToggle::SetNormalColorOn(consolate::TColor _ulNormalColorOn)
	{
		m_ulNormalColorOn = _ulNormalColorOn;
	}



	inline consolate::TColor CToggle::GetFocusedColorOn() const
	{
		return m_ulFocusedColorOn;
	}

	inline void CToggle::SetFocusedColorOn(consolate::TColor _ulFocusedColorOn)
	{
		m_ulFocusedColorOn = _ulFocusedColorOn;
	}

} //~ ui

#endif //~ __UI_TOGGLE_IMP_HPP__
