//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	ui_TextRect.hpp
//	Description	:	TextRect class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __UI_TEXT_RECT_HPP__
#define __UI_TEXT_RECT_HPP__

// Library Includes
#include <string>
#include <sstream>

// Solution Library Includes
#include <consolate.hpp>

// Local Includes
#include "ui_Element.hpp"

// Declarations

namespace ui
{
	class CTextRect : public CElement
	{
	public:

		// Full Constructor.
		inline CTextRect(
			CVector2i _vPosition = { 0, 0 },
			CVector2i _vSize = { 10, 3 },
			const std::wstring& _rstrkText = TEXT("Text"),
			consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
			consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
			const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
			bool _bIsInteractable = false,
			bool _bIsFocused = false
		);

		// Copy Constructor.
		inline CTextRect(const CTextRect& _rtkOther) = default;

		// Destructor.
		inline ~CTextRect() = default;



		inline const std::wstring& GetText() const;
		inline void SetText(const std::wstring& _rstrkText);

		inline CVector2i GetSize() const;
		inline void SetSize(CVector2i _vSize);

		inline const consolate::SPanelStyle& GetPanelStyle() const;
		inline void SetPanelStyle(const consolate::SPanelStyle& _rtkPanelStyle);

		virtual std::wstring GetDisplayText() const
		{
			return GetText();
		}



		// Draws this UI element.
		void Draw() override
		{
			using namespace consolate;

			const TColor ulkColor = GetDisplayColor();

			m_tPanelStyle.m_ulOutlineColor = ulkColor;
			m_tPanelStyle.m_ulFillColor = ulkColor;

			CVector2i vPos = GetPosition();
			CVector2i vMax = vPos + GetSize() - CVector2i{ 1, 1 };

			std::wstringstream iosText;
			iosText << GetDisplayText();

			g_tConsolate.DrawTextPanel(
				ToCoord(vPos),
				ToCoord(vMax),
				iosText,
				m_tPanelStyle
			);
		}



	private:

		// Content of this text rect.
		std::wstring m_strText;

		// Size of this rect.
		// Y component must be >= 2.
		CVector2i m_vSize;
		
		// Style of this text rect.
		consolate::SPanelStyle m_tPanelStyle;
	};

} //~ ui



// Include implementation for inline and template functions.
#include "ui_TextRect_imp.hpp"

#endif //~ __UI_TEXT_RECT_HPP__
