//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Element_imp.hpp
//	Description	:	Element class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_ELEMENT_IMP_HPP__
#define __UI_ELEMENT_IMP_HPP__

// Library Includes
#include <stdexcept>

// This Include
#include "ui_Element.hpp"

// Implementation

namespace ui
{
	// Full Constructor.
	inline CElement::CElement(
		CVector2i _vPosition,
		consolate::TColor _ulNormalColor,
		consolate::TColor _ulFocusedColor,
		bool _bIsInteractable,
		bool _bIsFocused,
		bool _bIsVisible
	) :
		m_vPosition(_vPosition),
		m_ulNormalColor(_ulNormalColor),
		m_ulFocusedColor(_ulFocusedColor),
		m_bIsInteractable(_bIsInteractable),
		m_bIsFocused(_bIsFocused),
		m_bIsVisible(_bIsVisible),
		m_ptView(nullptr)
	{
	}



	// Gets a pointer to the view that owns this element.
	inline CView* CElement::GetViewPtr() const
	{
		return m_ptView;
	}

	// Sets the pointer to the view that owns this element.
	inline void CElement::SetViewPtr(CView* _ptView)
	{
		m_ptView = _ptView;
	}

	// Gets a reference to the view that owns this element.
	inline CView& CElement::GetViewRef() const
	{
		if (m_ptView == nullptr)
		{
			throw std::exception("View reference of an element is null!");
		}

		return *m_ptView;
	}



	inline CVector2i CElement::GetPosition() const
	{
		return m_vPosition;
	}

	inline void CElement::SetPosition(CVector2i _vPosition)
	{
		m_vPosition = _vPosition;
	}



	inline bool CElement::GetIsVisible() const
	{
		return m_bIsVisible;
	}

	inline void CElement::SetIsVisible(bool _bIsVisible)
	{
		m_bIsVisible = _bIsVisible;
	}



	inline bool CElement::GetIsInteractable() const
	{
		return m_bIsInteractable;
	}

	inline void CElement::SetIsInteractable(bool _bIsInteractable)
	{
		m_bIsInteractable = _bIsInteractable;
	}



	inline bool CElement::GetIsFocused() const
	{
		return m_bIsFocused;
	}

	inline void CElement::SetIsFocused(bool _bIsFocused)
	{
		m_bIsFocused = _bIsFocused;
	}



	inline consolate::TColor CElement::GetNormalColor() const
	{
		return m_ulNormalColor;
	}

	inline void CElement::SetNormalColor(consolate::TColor _ulNormalColor)
	{
		m_ulNormalColor = _ulNormalColor;
	}



	inline consolate::TColor CElement::GetFocusedColor() const
	{
		return m_ulFocusedColor;
	}

	inline void CElement::SetFocusedColor(consolate::TColor _ulFocusedColor)
	{
		m_ulFocusedColor = _ulFocusedColor;
	}

} //~ ui

#endif //~ __UI_ELEMENT_IMP_HPP__
