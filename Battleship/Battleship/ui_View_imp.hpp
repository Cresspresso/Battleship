//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_View_imp.hpp
//	Description	:	View class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_VIEW_IMP_HPP__
#define __UI_VIEW_IMP_HPP__

// Local Includes
#include "generalmath.hpp"

// This Include
#include "ui_View.hpp"

// Implementation

namespace ui
{
	// Basic Constructor.
	inline CView::CView(
		int _iInitialFocusedIndex,
		CView* _ptPreviousViewPtr,
		consolate::TColor _ulClearColor
	)
		:
		m_aptElements(),
		m_iInitialFocusedIndex(_iInitialFocusedIndex),
		m_iFocusedIndex(m_iInitialFocusedIndex),
		m_ptPreviousViewPtr(_ptPreviousViewPtr),
		m_ulClearColor(_ulClearColor)
	{
	}



	inline CView* CView::GetPreviousViewPtr() const
	{
		return m_ptPreviousViewPtr;
	}

	inline void CView::SetPreviousViewPtr(CView* _ptPreviousViewPtr)
	{
		m_ptPreviousViewPtr = _ptPreviousViewPtr;
	}



	inline consolate::TColor CView::GetClearColor() const
	{
		return m_ulClearColor;
	}

	inline void CView::SetClearColor(consolate::TColor _ulClearColor)
	{
		m_ulClearColor = _ulClearColor;
	}



	inline int CView::GetElementCount() const
	{
		return m_aptElements.GetSize();
	}



	inline int CView::GetInitialFocusedIndex() const
	{
		return m_iInitialFocusedIndex;
	}

	inline void CView::SetInitialFocusedIndex(int _iInitialFocusedIndex)
	{
		m_iInitialFocusedIndex = CycleElementIndex(_iInitialFocusedIndex);
	}



	// Gets the index of the currently focused element.
	inline int CView::GetFocusedIndex() const
	{
		return m_iFocusedIndex;
	}



	// Gets a reference to an element in this view.
	inline CElement* CView::GetElementPtrAt(const int _ikIndex)
	{
		return m_aptElements.GetElementAt(_ikIndex);
	}



	// Exits this view and displays another view.
	inline void CView::NavigateToView(CView& _rtOtherView)
	{
		Exit();
		_rtOtherView.Display();
	}

	// Exits this view and displays the previous view (if it is not null).
	inline void CView::NavigateBack()
	{
		if (m_ptPreviousViewPtr != nullptr)
		{
			NavigateToView(*m_ptPreviousViewPtr);
		}
		else
		{
			Exit();
		}
	}



	// Ensures an element index is in range by cycling it.
	inline int CView::CycleElementIndex(const int _ikElementIndex)
	{
		return Cycle(_ikElementIndex, GetElementCount());
	}

} //~ ui

#endif //~ __UI_VIEW_IMP_HPP__
