//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_View.hpp
//	Description	:	View class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_VIEW_HPP__
#define __UI_VIEW_HPP__

// Library Includes
#include <sstream>

// Solution Library Includes
#include <consolate_colors.hpp>

// Local Includes
#include "FixedArray.hpp"

// Declarations

namespace ui
{
	// Forward Declarations
	class CElement;

	// Base class for a UI element such as a button or slider.
	class CView
	{
		// Methods
	public:

		// Basic Constructor.
		inline CView(
			int _iInitialFocusedIndex = 0,
			CView* _ptPreviousViewPtr = nullptr,
			consolate::TColor _ulClearColor = consolate::colors::COLOR_DEFAULT
		);

		// Full Constructor.
		// Takes control over an R-Value list of unique pointers to elements.
		// The elements are deleted upon destruction.
		CView(
			CFixedArray<CElement*>&& _rraptElements,
			int _iInitialFocusedIndex = 0,
			CView* _ptPreviousViewPtr = nullptr,
			consolate::TColor _ulClearColor = consolate::colors::COLOR_DEFAULT
		);

		// Destructor.
		~CView();


		inline CView* GetPreviousViewPtr() const;
		inline void SetPreviousViewPtr(CView* _ptPreviousViewPtr);

		inline consolate::TColor GetClearColor() const;
		inline void SetClearColor(consolate::TColor _ulClearColor);

		inline int GetElementCount() const;

		inline int GetInitialFocusedIndex() const;
		inline void SetInitialFocusedIndex(int _iInitialFocusedIndex);



		// Gets the index of the currently focused element.
		inline int GetFocusedIndex() const;

		// Gets a pointer to the currently focused element.
		// It could be null.
		CElement* GetFocusedElementPtr();

		// Sets which element is focused by its index.
		void SetFocusedIndex(int _iFocusedIndex);

		// Adds `Step` to the current focused index.
		// Until it lands on an interactable element, moves to the next one.
		void StepFocusedIndex(int _iStep = 1);



		// Tells an element that it is owned by this view.
		void TellElementItIsOwned(CElement* const _kptElementPtr);

		// Adds a new element to this view.
		// The element is deleted upon this view's destruction.
		void AddNewElement(CElement* const _kptElementPtr);

		// Gets a reference to an element in this view.
		inline CElement* GetElementPtrAt(const int _ikIndex);



		// Starts the rendering loop.
		void Display();

		// Stops the rendering loop.
		void Exit();

		// Exits this view and displays another view.
		inline void NavigateToView(CView& _rtOtherView);

		// Exits this view and displays the previous view (if it is not null).
		inline void NavigateBack();



	private:

		// Ensures an element index is in range by cycling it.
		inline int CycleElementIndex(const int _ikElementIndex);

		// Initializes input handlers for UI navigation.
		void SetupInputHandlers();

		// Draws a new frame of this view.
		void DrawView();



		// Member Variables
	private:

		// List of all elements in this view, in draw order.
		CFixedArray<CElement*> m_aptElements;

		// Index of the currently focused element.
		int m_iFocusedIndex;

		// Initial index of the focused element when navigating to this view.
		int m_iInitialFocusedIndex;

		// Background color for clearing the screen.
		consolate::TColor m_ulClearColor;

		// Whether the render loop should continue.
		bool m_bRenderLoopActive = false;

		// The view to navigate to when the NavigateBack method is called.
		CView* m_ptPreviousViewPtr;

	};

} //~ ui



// Include circular dependency.
#include "ui_Element.hpp"

// Include implementation for inline and template functions.
#include "ui_View_imp.hpp"

#endif //~ __UI_VIEW_HPP__
