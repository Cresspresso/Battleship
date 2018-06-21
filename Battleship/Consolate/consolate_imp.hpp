//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_imp.hpp
//	Description	:	Consolate class implementation file
//					for inline and template functions.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_IMP_HPP__
#define __CONSOLATE_IMP_HPP__

// Library Includes
#include <stdexcept>	// logic_error

// This Include
#include "consolate.hpp"

// Implementation

namespace consolate
{
#pragma region // Methods

#pragma region // Accessor Methods

#pragma region // Cursor Position

	// Gets the cursor position of the console.
	inline COORD CConsolate::GetCursorPosition() const
	{
		return GetBufferInfo().dwCursorPosition;
	}

	// Sets the cursor position of the console.
	inline void CConsolate::SetCursorPosition(const COORD _vkPosition)
	{
		SetConsoleCursorPosition(m_hkStdout, _vkPosition);
	}

#pragma endregion //~ Cursor Position

	// Gets the srWindow rect of the console.
	inline SMALL_RECT CConsolate::GetWindowRect() const
	{
		return GetBufferInfo().srWindow;
	}

	// Gets the size (width/height in number of characters) of the console window.
	inline COORD CConsolate::GetWindowSize() const
	{
		auto tBufferInfo = GetBufferInfo();
		return {
			tBufferInfo.srWindow.Right - tBufferInfo.srWindow.Left,
			tBufferInfo.srWindow.Bottom - tBufferInfo.srWindow.Top
		};
	}

#pragma region // Color

	// Gets the color for new console text (foreground and background).
	inline TColor CConsolate::GetColor() const
	{
		return m_ulDrawColor;
	}

	// Sets the color for new console text (foreground and background).
	inline void CConsolate::SetColor(const TColor _ulkColor)
	{
		m_ulDrawColor = _ulkColor;
		SetConsoleTextAttribute(m_hkStdout, m_ulDrawColor);
	}



	// Gets the original color for new console text (foreground and background).
	inline TColor CConsolate::GetOriginalColor() const
	{
		return m_tOriginalInfo.wAttributes;
	}

#pragma endregion //~ Color

#pragma region // ColorTable

	// Gets the color table of the console.
	inline TColorTable CConsolate::GetColorTable() const
	{
		return colortable::CreateColorTable(GetBufferInfo().ColorTable);
	}

	// Sets the color table of the console.
	inline void CConsolate::SetColorTable(const TColorTable& _rtkColorTable)
	{
		auto tBufferInfo = GetBufferInfo();
		colortable::CopyColorTable(_rtkColorTable, tBufferInfo.ColorTable);
		SetBufferInfo(tBufferInfo);
	}



	// Gets the original color table of the console.
	inline TColorTable CConsolate::GetOriginalColorTable() const
	{
		return colortable::CreateColorTable(m_tOriginalInfo.ColorTable);
	}

#pragma endregion //~ ColorTable

#pragma region // DrawChar

	// Gets the character used when drawing new shapes.
	inline TCHAR CConsolate::GetDrawChar() const
	{
		return m_cDrawChar;
	}

	// Sets the character used when drawing new shapes.
	inline void CConsolate::SetDrawChar(const TCHAR _ckDrawChar)
	{
		m_cDrawChar = _ckDrawChar;
	}

#pragma endregion //~ DrawChar

#pragma endregion //~ Accessor Methods

	// Returns true if the coord is a visible screen position.
	inline bool CConsolate::IsValidScreenCoord(const COORD _vkPosition)
	{
		const COORD vkSize = GetWindowSize();
		return _vkPosition.X >= 0 && _vkPosition.X <= vkSize.X
			&& _vkPosition.Y >= 0 && _vkPosition.Y <= vkSize.Y;
	}

#pragma region // Drawing

	// Clears the console screen.
	inline void CConsolate::ClearScreen(
		const COORD _vkCursorPos,
		const TColor _ulkFillColor,
		const TCHAR _ckFillChar
	)
	{
		SetColor(_ulkFillColor);
		SetDrawChar(_ckFillChar);
		ClearScreenRaw(_vkCursorPos);
	}



	// Draws a horizontal row of characters, with color, extending from position to the right.
	inline void CConsolate::DrawRow(
		const COORD _vkPosition,
		const DWORD _ulkLength,
		const TColor _ulkDrawColor,
		const TCHAR _ckDrawChar
	)
	{
		SetColor(_ulkDrawColor);
		SetDrawChar(_ckDrawChar);
		DrawRowRaw(_vkPosition, _ulkLength);
	}

	// Draws a single character at the position.
	inline void CConsolate::DrawPointRaw(const COORD _vkPosition)
	{
		DrawRowRaw(_vkPosition, 1);
	}

	// Draws a single character at the position, with color.
	inline void CConsolate::DrawPoint(
		const COORD _vkPosition,
		const TColor _ulkDrawColor,
		const TCHAR _ckDrawChar
	)
	{
		SetColor(_ulkDrawColor);
		SetDrawChar(_ckDrawChar);
		DrawPointRaw(_vkPosition);
	}



	// Draws a rectangle.
	inline void CConsolate::DrawRect(
		const COORD _vkMin,
		const COORD _vkMax,
		const TColor _ulkFillColor,
		const TCHAR _ckFillChar
	)
	{
		SetColor(_ulkFillColor);
		SetDrawChar(_ckFillChar);
		DrawRectRaw(_vkMin, _vkMax);
	}

	// Draws the outline of a rectangle.
	inline void CConsolate::DrawRectOutline(
		const COORD _vkMin,
		const COORD _vkMax,
		const TColor _ulkOutlineColor,
		const TCHAR _ckOutlineChar
	)
	{
		SetColor(_ulkOutlineColor);
		SetDrawChar(_ckOutlineChar);
		DrawRectOutlineRaw(_vkMin, _vkMax);
	}



	// Draws a styled outline of a rectangle, with color.
	inline void CConsolate::DrawPanelOutline(
		const COORD _vkMin,
		const COORD _vkMax,
		const SPanelStyle& _rtkStyle
	)
	{
		SetColor(_rtkStyle.m_ulOutlineColor);
		DrawPanelOutlineRaw(_vkMin, _vkMax, _rtkStyle);
	}



	// Prints text from a stream to a rect on the screen.
	inline std::CWPREFIX(istream)& CConsolate::DrawTextRect(
		const COORD _vkMin,
		const COORD _vkMax,
		std::CWPREFIX(istream)& _risTextStream,
		const TColor _ulkDrawColor
	)
	{
		SetColor(_ulkDrawColor);
		SetDrawChar(TEXT(' '));
		DrawRectRaw(_vkMin, _vkMax);
		return DrawTextRectRaw(_vkMin, _vkMax, _risTextStream);
	}

	// Prints text from a stream to a styled rectangle on the screen.
	inline std::CWPREFIX(istream)& CConsolate::DrawTextPanel(
		const COORD _vkMin,
		const COORD _vkMax,
		std::CWPREFIX(istream)& _risTextStream,
		const SPanelStyle& _rtkStyle
	)
	{
		DrawPanelOutline(_vkMin, _vkMax, _rtkStyle);
		return DrawTextRect(
			{ _vkMin.X + 1, _vkMin.Y + 1 },
			{ _vkMax.X - 1, _vkMax.Y - 1 },
			_risTextStream,
			_rtkStyle.m_ulFillColor
		);
	}

#pragma endregion //~ Drawing

#pragma endregion //~ Methods

#pragma region // Static Functions

	// Throws a logic_error when a component of the
	// Min point is greater than that of the Max point.
	inline void CConsolate::AssertMinMaxValid(
		const COORD _vkMin,
		const COORD _vkMax
	)
	{
		if (_vkMin.X > _vkMax.X)
			throw std::logic_error("Min X > Max X");

		if (_vkMin.Y > _vkMax.Y)
			throw std::logic_error("Min Y > Max Y");
	}

#pragma endregion //~ Static Functions

} //~ consolate

#endif //~ __CONSOLATE_IMP_HPP__
