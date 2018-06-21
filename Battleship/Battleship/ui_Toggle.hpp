//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_Toggle.hpp
//	Description	:	Toggle class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_TOGGLE_HPP__
#define __UI_TOGGLE_HPP__

// Library Includes
#include <functional>

// Local Includes
#include "ui_TextRect.hpp"

// Declarations

namespace ui
{
	// A button that toggles a boolean when clicked.
	class CToggle : public CTextRect
	{
		// Types
	public:
		using TEventToggle = std::function<void(CToggle&)>;


		// Methods
	public:

		// Full Constructor.
		inline CToggle(
			TEventToggle _fnOnToggle = nullptr,
			CVector2i _vPosition = { 0, 0 },
			CVector2i _vSize = { 10, 3 },
			const std::wstring& _rstrkText = TEXT("Button"),
			bool _bDefaultToggleValue = false,
			consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulNormalColorOn = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulFocusedColorOn = consolate::colors::COLOR_DEFAULT,
			const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
			bool _bIsInteractable = true,
			bool _bIsFocused = false
		);

		// Destructor.
		inline ~CToggle() = default;



		// Gets the text to display to the screen.
		std::wstring GetDisplayText() const override
		{
			std::wstringstream iosText;
			iosText << TEXT('[');

			if (GetToggleValue())
			{
				iosText << TEXT('X');
			}
			else
			{
				iosText << TEXT(' ');
			}

			iosText << TEXT("] ") << CTextRect::GetText();
			return iosText.str();
		}



		inline bool GetToggleValue() const;
		inline void SetToggleValue(bool _bToggleValue);

		inline bool GetDefaultToggleValue() const;
		inline void SetDefaultToggleValue(bool _bDefaultToggleValue);

		inline void SetOnToggle(TEventToggle _fnOnToggle);
		
		inline consolate::TColor GetNormalColorOn() const;
		inline void SetNormalColorOn(consolate::TColor _ulNormalColorOn);

		inline consolate::TColor GetFocusedColorOn() const;
		inline void SetFocusedColorOn(consolate::TColor _ulFocusedColorOn);



		// Get color depending on whether this element is focused or toggled.
		consolate::TColor GetDisplayColor() const override
		{
			if (GetToggleValue())
			{
				return GetIsFocused() ? m_ulFocusedColorOn : m_ulNormalColorOn;
			}
			else
			{
				return __super::GetDisplayColor();
			}
		}


		void InputEventEnter() override
		{
			SetToggleValue(!GetToggleValue());
		}

		/*void InputEventSpace() override
		{
			SetToggleValue(m_bDefaultToggleValue);
		}*/



		// Member Variables
	private:

		// The value being toggled.
		bool m_bToggleValue;

		// The default toggle value.
		bool m_bDefaultToggleValue;

		// Action to execute when the value is toggled.
		TEventToggle m_fnOnToggle;

		// Color when ToggleValue is true, and element is not focused.
		consolate::TColor m_ulNormalColorOn;

		// Color when ToggleValue is true, and element is focused.
		consolate::TColor m_ulFocusedColorOn;

	};

} //~ ui



// Include implementation for inline and template functions.
#include "ui_Toggle_imp.hpp"

#endif //~ __UI_TOGGLE_HPP__
