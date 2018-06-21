//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_View.cpp
//	Description	:	View class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <stdexcept>

// Solution Library Includes
#include <consolate.hpp>

// Local Includes
#include "generalmath.hpp"
#include "Input.hpp"

// This Include
#include "ui_View.hpp"

// Implementation

namespace ui
{
	// Full Constructor.
	// Takes control over an R-Value list of unique pointers to elements.
	// The elements are deleted upon destruction.
	CView::CView(
		CFixedArray<CElement*>&& _rraptElements,
		int _iInitialFocusedIndex,
		CView* _ptPreviousViewPtr,
		consolate::TColor _ulClearColor
	) :
		m_aptElements(_rraptElements),
		m_iInitialFocusedIndex(CycleElementIndex(_iInitialFocusedIndex)),
		m_iFocusedIndex(m_iInitialFocusedIndex),
		m_ptPreviousViewPtr(_ptPreviousViewPtr),
		m_ulClearColor(_ulClearColor)
	{
		// Ensure all elements exist.
		for (CElement* ptElementPtr : m_aptElements)
		{
			if (ptElementPtr == nullptr)
			{
				throw std::exception("Some elements are null!");
			}
		}

		// Set up elements.
		for (CElement* ptElementPtr : m_aptElements)
		{
			TellElementItIsOwned(ptElementPtr);

			// Ensure element is not focused.
			ptElementPtr->SetIsFocused(false);
		}

		// Focus the initial focused element.
		GetFocusedElementPtr()->SetIsFocused(true);
	}

	// Destructor.
	// TF: Destructor
	CView::~CView()
	{
		// Delete all UI elements of this view.
		for (CElement*& rptElementPtr : m_aptElements)
		{
			if (rptElementPtr != nullptr)
			{
				delete rptElementPtr;
				rptElementPtr = nullptr;
			}
		}
	}



	// Gets a pointer to the currently focused element.
	// It could be null.
	CElement* CView::GetFocusedElementPtr()
	{
		if (GetElementCount() == 0)
		{
			throw std::exception("There are no elements in this view!");
		}

		CElement* ptElement = m_aptElements.GetElementAt(m_iFocusedIndex);

		if (ptElement == nullptr)
		{
			throw std::exception("Focused Element is null!");
		}

		return ptElement;
	}

	// Sets which element is focused by its index.
	void CView::SetFocusedIndex(int _iFocusedIndex)
	{
		// Unfocus old element.
		if (GetFocusedIndex() >= 0 && GetFocusedIndex() < GetElementCount())
		{
			GetFocusedElementPtr()->SetIsFocused(false);
		}

		if (GetElementCount() > 0)
		{
			// Ensure new index is in range.
			m_iFocusedIndex = CycleElementIndex(_iFocusedIndex);

			// Focus new element.
			GetFocusedElementPtr()->SetIsFocused(true);
		}
		else
		{
			m_iFocusedIndex = 0;
		}
	}

	// Adds `Step` to the current focused index.
	// Until it lands on an interactable element, moves to the next one.
	void CView::StepFocusedIndex(int _iStep)
	{
		SetFocusedIndex(GetFocusedIndex() + _iStep);

		if (!(GetFocusedElementPtr()->GetIsInteractable()))
		{
			// step by 1 or -1 until reached an interactable element.

			if (_iStep >= 0)
				_iStep = 1;
			else
				_iStep = -1;

			int iAttempts = GetElementCount();

			while (!(GetFocusedElementPtr()->GetIsInteractable()) && iAttempts > 0)
			{
				SetFocusedIndex(GetFocusedIndex() + _iStep);
				--iAttempts;
			}

			if (iAttempts == 0)
			{
				throw std::exception("All elements are not interactable!");
			}
		}
	}



	// Adds a new element to this view.
	// The element is deleted upon this view's destruction.
	void CView::AddNewElement(CElement* const _kptElementPtr)
	{
		TellElementItIsOwned(_kptElementPtr);
		m_aptElements.AddElement(_kptElementPtr);
	}

	// Tells an element that it is owned by this view.
	void CView::TellElementItIsOwned(CElement* const _kptElementPtr)
	{
		if (_kptElementPtr == nullptr)
		{
			throw std::exception("Element is null!");
		}

		CView* pView = _kptElementPtr->GetViewPtr();
		if (pView == nullptr)
		{
			_kptElementPtr->SetViewPtr(this);
		}
		else if (pView != this)
		{
			throw std::exception("Elements cannot be shared between views!");
		}
	}



	// Starts the rendering loop.
	void CView::Display()
	{
		if (GetElementCount() == 0)
		{
			throw std::exception("There are no elements in this view!");
		}

		SetFocusedIndex(GetInitialFocusedIndex());

		SetupInputHandlers();

		m_bRenderLoopActive = true;
		do
		{
			DrawView();

			g_tInput.WaitForKeyPress();
		} while (m_bRenderLoopActive);
	}

	// Stops the rendering loop.
	void CView::Exit()
	{
		m_bRenderLoopActive = false;
	}



	// Initializes input handlers for UI navigation.
	void CView::SetupInputHandlers()
	{
		using namespace keycodes;

		g_tInput.m_fnOnKeyPressed = [this](TKeyCode _iKey)
		{
			switch (_iKey)
			{
			case 'w':
			{
				GetFocusedElementPtr()->InputEventUp();
				break;
			}
			case 's':
			{
				GetFocusedElementPtr()->InputEventDown();
				break;
			}
			case 'a':
			{
				GetFocusedElementPtr()->InputEventLeft();
				break;
			}
			case 'd':
			{
				GetFocusedElementPtr()->InputEventRight();
				break;
			}
			case KEYCODE_ESCAPE:
			{
				GetFocusedElementPtr()->InputEventEscape();
				break;
			}
			case KEYCODE_ENTER:
			{
				GetFocusedElementPtr()->InputEventEnter();
				break;
			}
			case KEYCODE_SPACE:
			{
				GetFocusedElementPtr()->InputEventSpace();
				break;
			}
			case 'q':
			{
				GetFocusedElementPtr()->InputEventQ();
				break;
			}
			case 'e':
			{
				GetFocusedElementPtr()->InputEventE();
				break;
			}
			}
		};

		g_tInput.m_fnOnKeyExPressed = [this](TKeyCodeEx _iKeyEx)
		{
			switch (_iKeyEx)
			{
			case KEYCODE_EX_ARROW_UP:
			{
				GetFocusedElementPtr()->InputEventUp();
				break;
			}
			case KEYCODE_EX_ARROW_DOWN:
			{
				GetFocusedElementPtr()->InputEventDown();
				break;
			}
			case KEYCODE_EX_ARROW_LEFT:
			{
				GetFocusedElementPtr()->InputEventLeft();
				break;
			}
			case KEYCODE_EX_ARROW_RIGHT:
			{
				GetFocusedElementPtr()->InputEventRight();
				break;
			}
			}
		};

		g_tInput.m_fnOnKeyEx2Pressed = nullptr;
	}



	// Draws a new frame of this view.
	void CView::DrawView()
	{
		using namespace consolate;
		using namespace consolate::colors;

		g_tConsolate.ClearScreen({ 0, 0 }, m_ulClearColor);

		for (CElement* ptElementPtr : m_aptElements)
		{
			if (ptElementPtr != nullptr && ptElementPtr->GetIsVisible())
			{
				ptElementPtr->Draw();
			}
		}

		g_tConsolate.SetCursorPosition({ 0, 0 });
	}

} //~ ui
