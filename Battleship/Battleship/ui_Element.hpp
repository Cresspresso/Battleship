//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Element.hpp
//	Description	:	Element class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_ELEMENT_HPP__
#define __UI_ELEMENT_HPP__

// Library Includes
#include <sstream>

// Solution Library Includes
//#include <consolate_colors.hpp>
#include <consolate.hpp>

// Local Includes
#include "ui_View.hpp"
#include "Vector2.hpp"

// Declarations

namespace ui
{
	// Forward Declarations
	class CView;

	// Base class for a UI element such as a button or slider.
	class CElement
	{
	public:

		// Full Constructor.
		inline CElement(
			CVector2i _vPosition = { 0, 0 },
			consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
			bool _bIsInteractable = false,
			bool _bIsFocused = false,
			bool _bIsVisible = true
		);

		// Copy Constructor.
		inline CElement(const CElement& _rtkOther) = default;

		// Destructor.
		inline ~CElement() = default;



		// Gets a pointer to the view that owns this element.
		inline CView* GetViewPtr() const;
		// Sets the pointer to the view that owns this element.
		inline void SetViewPtr(CView* _ptView);
		// Gets a reference to the view that owns this element.
		inline CView& GetViewRef() const;

		inline CVector2i GetPosition() const;
		inline void SetPosition(CVector2i _vPosition);

		inline bool GetIsVisible() const;
		inline void SetIsVisible(bool _bIsVisible);

		inline bool GetIsInteractable() const;
		inline void SetIsInteractable(bool _bIsInteractable);

		inline bool GetIsFocused() const;
		inline void SetIsFocused(bool _bIsFocused);

		inline consolate::TColor GetNormalColor() const;
		inline void SetNormalColor(consolate::TColor _ulNormalColor);

		inline consolate::TColor GetFocusedColor() const;
		inline void SetFocusedColor(consolate::TColor _ulFocusedColor);

		// Get color depending on whether this element is focused.
		virtual consolate::TColor GetDisplayColor() const
		{
			return GetIsFocused() ? m_ulFocusedColor : m_ulNormalColor;
		}



		// Draws this UI element.
		virtual void Draw()
		{
			// This is a placeholder drawing
			// for the base class CElement.

			using namespace consolate;

			std::wstringstream iosTextStream;
			iosTextStream << TEXT("Abstract UI Element");

			CVector2i vMax = m_vPosition + CVector2i{ 21, 2 };

			SPanelStyle tStyle = SPanelStyle::PANELSTYLE_SINGLE;
			tStyle.m_ulOutlineColor = GetDisplayColor();
			tStyle.m_ulFillColor = tStyle.m_ulOutlineColor;

			g_tConsolate.DrawPanelOutline(
				ToCoord(m_vPosition),
				ToCoord(vMax),
				tStyle
			);
			g_tConsolate.DrawTextRect(
				ToCoord(m_vPosition + CVector2i{ 1, 1 }),
				ToCoord(vMax - CVector2i{ 1, 1 }),
				iosTextStream,
				tStyle.m_ulOutlineColor
			);
		}



		// Input Event handlers for when a key is pressed while this is focused.

		virtual void InputEventUp()
		{
			GetViewRef().StepFocusedIndex(-1);
		}

		virtual void InputEventDown()
		{
			GetViewRef().StepFocusedIndex(1);
		}

		virtual void InputEventLeft()
		{
			GetViewRef().StepFocusedIndex(-1);
		}

		virtual void InputEventRight()
		{
			GetViewRef().StepFocusedIndex(1);
		}

		virtual void InputEventEscape()
		{
			GetViewRef().NavigateBack();
		}

		virtual void InputEventEnter() {}

		virtual void InputEventSpace()
		{
			InputEventEnter();
		}

		virtual void InputEventQ() {}

		virtual void InputEventE() {}



		// Member Variables
	private:

		// The view which owns this element.
		CView* m_ptView = nullptr;

		// Position in screen space.
		CVector2i m_vPosition;

		// Whether this element is visible.
		// Does not affect navigation; it can still be selected.
		bool m_bIsVisible;

		// Whether this element should be skipped during navigation (skip if false).
		bool m_bIsInteractable;

		// Whether this element is currently focused.
		bool m_bIsFocused;

		// Color when not focused.
		consolate::TColor m_ulNormalColor;

		// Color when focused.
		consolate::TColor m_ulFocusedColor;

	};

} //~ ui



// Include implementation for inline and template functions.
#include "ui_Element_imp.hpp"

#endif //~ __UI_ELEMENT_HPP__
