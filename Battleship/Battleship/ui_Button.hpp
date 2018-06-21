//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Button.hpp
//	Description	:	Button class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_BUTTON_HPP__
#define __UI_BUTTON_HPP__

// Library Includes
#include <functional>

// Local Includes
#include "ui_TextRect.hpp"

// Declarations

namespace ui
{
	// A button which does an action when it is pressed (ENTER or SPACE keys).
	class CButton : public CTextRect
	{
		// Types
	public:
		using TEventAction = std::function<void(CButton&)>;



		// Methods
	public:

		// Full Constructor.
		inline CButton(
			TEventAction _fnOnInputEventEnter = nullptr,
			TEventAction _fnOnInputEventSpace = nullptr,
			CVector2i _vPosition = { 0, 0 },
			CVector2i _vSize = { 10, 3 },
			const std::wstring& _rstrkText = TEXT("Button"),
			consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
			const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
			bool _bIsInteractable = true,
			bool _bIsFocused = false
		);

		// Copy Constructor.
		inline CButton(const CButton& _rtkOther) = default;

		// Destructor.
		inline ~CButton() = default;



		inline void SetOnInputEventEnter(TEventAction _fnOnInputEventEnter);
		inline void SetOnInputEventSpace(TEventAction _fnOnInputEventSpace);



		// Input Event handlers for when a key is pressed while this is focused.

		void InputEventEnter() override
		{
			if (m_fnOnInputEventEnter != nullptr)
			{
				m_fnOnInputEventEnter(*this);
			}
		}

		void InputEventSpace() override
		{
			if (m_fnOnInputEventSpace != nullptr)
			{
				m_fnOnInputEventSpace(*this);
			}
			else
			{
				InputEventEnter();
			}
		}



		// Member Variables
	private:

		// Actions to execute when the events happen.

		TEventAction m_fnOnInputEventEnter;
		TEventAction m_fnOnInputEventSpace;

	};

} //~ ui



// Include implementation for inline and template functions.
#include "ui_Button_imp.hpp"

#endif //~ __UI_BUTTON_HPP__
