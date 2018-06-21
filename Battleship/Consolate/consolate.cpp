//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate.cpp
//	Description	:	Consolate namespace and class implementation file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <iostream>
#include <io.h>		// _setmode(), _fileno()
#include <fcntl.h>	// _O_U16TEXT
#include <string>

// This Include
#include "consolate.hpp"

// Implementation

namespace consolate
{
#pragma region // CConsolate Methods

#pragma region // Constructors and Destructors

	// Default Constructor.
	CConsolate::CConsolate(
		const HANDLE _hkStdout,
		const HANDLE _hkStdin
	) :
		m_hkStdout(_hkStdout),
		m_hkStdin(_hkStdin)
	{
		// Cache original console settings.
		CONSOLE_SCREEN_BUFFER_INFOEX tBufferInfo = { sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
		if (GetConsoleScreenBufferInfoEx(m_hkStdout, &tBufferInfo))
		{
			m_tOriginalInfo = tBufferInfo;

			// Initialize Draw color from console's original settings.
			m_ulDrawColor = m_tOriginalInfo.wAttributes;
		}
		else // error was encountered...
		{
			// Initialize Draw color to an arbitrary color.
			m_ulDrawColor = colors::COLOR_DEFAULT;
		}

		// Tell console to use unicode charset.
		// NOTE: this is not undone when the program exits.
#ifdef UNICODE
		_setmode(_fileno(stdout), _O_U16TEXT);
#endif //~ UNICODE

	}

	// Destructor.
	CConsolate::~CConsolate()
	{
		Reset();
	}

	// Restores the original settings of the console.
	void CConsolate::Reset()
	{
		// Get final state of the console.
		auto tBufferInfo = GetBufferInfo();

		// --- Restore Original Settings ---

		// Restore Color Table
		colortable::CopyColorTable(m_tOriginalInfo.ColorTable, tBufferInfo.ColorTable);
		SetBufferInfo(tBufferInfo);

		// Restore Text Color
		SetColor(m_tOriginalInfo.wAttributes);
	}

#pragma endregion //~ Constructors and Destructors

#pragma region // Accessor Methods

	// Gets the console's buffer info.
	CONSOLE_SCREEN_BUFFER_INFOEX CConsolate::GetBufferInfo() const
	{
		CONSOLE_SCREEN_BUFFER_INFOEX tBufferInfo = { sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
		if (!GetConsoleScreenBufferInfoEx(m_hkStdout, &tBufferInfo))
		{
			std::CWPREFIX(cout) << "Error calling GetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
		}
		return tBufferInfo;
	}

	// Sets the console's buffer info.
	void CConsolate::SetBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX _tBufferInfo)
	{
		// Fix the bug of window getting smaller.
		_tBufferInfo.srWindow.Bottom += 1;

		if (!SetConsoleScreenBufferInfoEx(m_hkStdout, &_tBufferInfo))
		{
			std::CWPREFIX(cout) << "Error calling SetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
		}
	}



	// Sets the position (in pixels) of the actual Windows window of the console.
	void CConsolate::SetContainerWindowPosition(int _iX, int _iY)
	{
		HWND hWindow = GetConsoleWindow();
		RECT r;
		::GetWindowRect(hWindow, &r);
		MoveWindow(hWindow, _iX, _iY, r.right - r.left, r.bottom - r.top, TRUE);
	}

	// Sets the size (in pixels) of the actual Windows window of the console.
	void CConsolate::SetContainerWindowSize(int _iWidth, int _iHeight)
	{
		HWND hWindow = GetConsoleWindow();
		RECT r;
		::GetWindowRect(hWindow, &r);
		MoveWindow(hWindow, r.left, r.top, _iWidth, _iHeight, TRUE);
	}

#pragma endregion //~ Accessor Methods

#pragma region // Drawing

	// Draws a horizontal row of characters, extending from position to the right.
	void CConsolate::DrawRowRaw(const COORD _vkPosition, const DWORD _ulkLength)
	{
		if (_ulkLength <= 0)
			return;

		DWORD ulWritten;
		FillConsoleOutputCharacter(m_hkStdout, m_cDrawChar, _ulkLength, _vkPosition, &ulWritten);
		FillConsoleOutputAttribute(m_hkStdout, m_ulDrawColor, _ulkLength, _vkPosition, &ulWritten);
	}

	// Clears the console screen, using Draw Char and Color.
	void CConsolate::ClearScreenRaw(const COORD _vkCursorPos)
	{
		auto tBufferInfo = GetBufferInfo();
		DrawRowRaw({ 0, 0 }, tBufferInfo.dwSize.X * tBufferInfo.dwSize.Y);
		SetCursorPosition(_vkCursorPos);
	}

#pragma region // Draw Rect

	// Draws a filled rectangle shape.
	void CConsolate::DrawRectRaw(COORD _vkMin, const COORD _vkMax)
	{
		AssertMinMaxValid(_vkMin, _vkMax);

		DWORD length = _vkMax.X - _vkMin.X + 1;
		for (; _vkMin.Y <= _vkMax.Y; ++_vkMin.Y)
		{
			DrawRowRaw(_vkMin, length);
		}
	}

	// Draws the filled inside of an outlined rectangle.
	// If min > max, draws nothing.
	void CConsolate::DrawRectInnerRaw(COORD _vMin, COORD _vMax)
	{
		_vMin = { _vMin.X + 1, _vMin.Y + 1 };
		_vMax = { _vMax.X - 1, _vMax.Y - 1 };
		if (_vMin.X <= _vMax.X && _vMin.Y <= _vMax.Y)
		{
			DrawRectRaw(_vMin, _vMax);
		}
	}

	// Draws the outline of a rectangle.
	void CConsolate::DrawRectOutlineRaw(const COORD _vkMin, const COORD _vkMax)
	{
		AssertMinMaxValid(_vkMin, _vkMax);

		DWORD length = _vkMax.X - _vkMin.X + 1;
		DrawRowRaw(_vkMin, length);
		DrawRowRaw({ _vkMin.X, _vkMax.Y }, length);
		for (short y = _vkMin.Y; y < _vkMax.Y; ++y)
		{
			DrawPointRaw({ _vkMin.X, y });
			DrawPointRaw({ _vkMax.X, y });
		}
	}

	// Draws a rectangle with an outline.
	void CConsolate::DrawRectWithOutline(
		const COORD _vkMin,
		const COORD _vkMax,
		const TColor _ulFillColor,
		const TColor _ulOutlineColor,
		const TCHAR _cFillChar,
		const TCHAR _cOutlineChar)
	{
		AssertMinMaxValid(_vkMin, _vkMax);

		// Draw fill
		SetColor(_ulFillColor);
		SetDrawChar(_cFillChar);
		DrawRectInnerRaw(_vkMin, _vkMax);

		// Draw outline
		SetColor(_ulOutlineColor);
		SetDrawChar(_cOutlineChar);
		DrawRectOutlineRaw(_vkMin, _vkMax);
	}

#pragma endregion //~ Draw Rect

#pragma region // Draw Panel

	// Draws a styled outline of a rectangle,
	// without changing the draw color.
	void CConsolate::DrawPanelOutlineRaw(
		const COORD _vkMin,
		const COORD _vkMax,
		const SPanelStyle& _rtkStyle
	)
	{
		AssertMinMaxValid(_vkMin, _vkMax);

		// Corners

		SetDrawChar(_rtkStyle.m_cTopLeft);
		DrawPointRaw(_vkMin);

		SetDrawChar(_rtkStyle.m_cBottomLeft);
		DrawPointRaw({ _vkMin.X, _vkMax.Y });

		SetDrawChar(_rtkStyle.m_cTopRight);
		DrawPointRaw({ _vkMax.X, _vkMin.Y });

		SetDrawChar(_rtkStyle.m_cBottomRight);
		DrawPointRaw(_vkMax);

		// Horizontal Edges

		DWORD ulLength = _vkMax.X - _vkMin.X + 1 - 2;

		SetDrawChar(_rtkStyle.m_cTop);
		DrawRowRaw({ _vkMin.X + 1, _vkMin.Y }, ulLength);

		SetDrawChar(_rtkStyle.m_cBottom);
		DrawRowRaw({ _vkMin.X + 1, _vkMax.Y }, ulLength);

		// Vertical Edges

		for (short y = _vkMin.Y + 1; y < _vkMax.Y; ++y)
		{
			SetDrawChar(_rtkStyle.m_cLeft);
			DrawPointRaw({ _vkMin.X, y });

			SetDrawChar(_rtkStyle.m_cRight);
			DrawPointRaw({ _vkMax.X, y });
		}
	}

	// Draws a styled rectangle.
	void CConsolate::DrawPanel(
		const COORD _vkMin,
		const COORD _vkMax,
		const SPanelStyle& _rtkStyle
	)
	{
		AssertMinMaxValid(_vkMin, _vkMax);

		// Draw outline
		SetColor(_rtkStyle.m_ulOutlineColor);
		DrawPanelOutlineRaw(_vkMin, _vkMax, _rtkStyle);

		// Draw fill
		SetColor(_rtkStyle.m_ulFillColor);
		SetDrawChar(_rtkStyle.m_cFill);
		DrawRectInnerRaw(_vkMin, _vkMax);
	}

#pragma endregion //~ Draw Panel

	// Prints text from a stream to a rect on the screen.
	std::CWPREFIX(istream)& CConsolate::DrawTextRectRaw(
		const COORD _vkMin,
		const COORD _vkMax,
		std::CWPREFIX(istream)& _risTextStream
	)
	{
		// TODO make newlines work.

		const std::CWPREFIX(string) strkSpace = TEXT(" ");

		// Buffered string.
		std::CWPREFIX(string) strBuffered;
		// Position of buffered string.
		std::streampos tOldPos = _risTextStream.tellg();
		// Read the first word.
		bool bNextExists = !!(_risTextStream >> strBuffered) && !strBuffered.empty();

		// For each line (row),
		for (short sY = _vkMin.Y; sY <= _vkMax.Y && bNextExists; ++sY)
		{
			// Screen X position of start of buffered string.
			short sX = _vkMin.X;
			// Move to new line.
			SetCursorPosition({ sX, sY });

			// Screen X position of end of buffered string.
			short sEndX = sX + static_cast<short>(strBuffered.length());

			// While the word can be printed without overflow,
			while ((sEndX <= _vkMax.X) && bNextExists)
			{
				// Print the word.
				std::CWPREFIX(cout) << strBuffered;
				if (sEndX != _vkMax.X)
				{
					std::CWPREFIX(cout) << strkSpace;
				}

				// Read the next word.
				tOldPos = _risTextStream.tellg();
				bNextExists = !!(_risTextStream >> strBuffered) && !strBuffered.empty();
				sX = sEndX + static_cast<short>(strkSpace.length());
				sEndX = sX + static_cast<short>(strBuffered.length());
			}

			// ensure line is printed.
			std::CWPREFIX(cout) << std::flush;
		}

		if (bNextExists)
		{
			// do not absorb last buffered word.
			_risTextStream.seekg(tOldPos);
		}

		return _risTextStream;
	}

#pragma endregion //~ Drawing

#pragma endregion //~ CConsolate Methods

	// Singleton instance.
	CConsolate g_tConsolate;

} //~ consolate
