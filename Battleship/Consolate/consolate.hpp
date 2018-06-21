//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate.hpp
//	Description	:	Consolate class declaration file.
//					Main header file for Consolate library.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_HPP__
#define __CONSOLATE_HPP__

// Library Includes
#include <windows.h>
#include <iostream>

// Local Includes
#include "consolate_colors.hpp"
#include "consolate_colortable.hpp"
#include "consolate_PanelStyle.hpp"

// Macros

#ifdef _UNICODE

// Prefixes an identifier with 'w' if _UNICODE is defined.
#define CWPREFIX(_X) w ## _X

#else //! _UNICODE

// Prefixes an identifier with 'w' if _UNICODE is defined.
#define CWPREFIX(_X) _X

#endif //~ _UNICODE



// Declarations

// A namespace acting as an interface between the program and the Windows Console.
namespace consolate
{
	// Singleton class.
	class CConsolate
	{
#pragma region // Methods
	public:

#pragma region // Constructors and Destructors

		// Default Constructor.
		CConsolate(
			const HANDLE _hkStdout = GetStdHandle(STD_OUTPUT_HANDLE),
			const HANDLE _hkStdin = GetStdHandle(STD_INPUT_HANDLE)
		);

		// Copy Constructor (disallowed).
		CConsolate(const CConsolate&) = delete;

		// Destructor.
		~CConsolate();

		// Restores the original settings of the console.
		void Reset();

#pragma endregion //~ Constructors and Destructors

#pragma region // Accessor Methods

		// Gets the console's buffer info.
		CONSOLE_SCREEN_BUFFER_INFOEX GetBufferInfo() const;

		// Sets the console's buffer info.
		void SetBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX _tBufferInfo);



		// Gets the cursor position of the console.
		inline COORD GetCursorPosition() const;

		// Sets the cursor position of the console.
		inline void SetCursorPosition(const COORD _vPosition);



		// Gets the srWindow rect of the console.
		inline SMALL_RECT GetWindowRect() const;

		// Gets the size (width/height in number of characters) of the console window.
		inline COORD GetWindowSize() const;



		// Sets the position (in pixels) of the actual Windows window of the console.
		void SetContainerWindowPosition(int _iX, int _iY);

		// Sets the size (in pixels) of the actual Windows window of the console.
		void SetContainerWindowSize(int _iWidth, int _iHeight);



		// Gets the color for new console text (foreground and background).
		inline TColor GetColor() const;

		// Sets the color for new console text (foreground and background).
		inline void SetColor(const TColor _ulkColor);

		// Gets the original color for new console text (foreground and background).
		inline TColor GetOriginalColor() const;



		// Gets the color table of the console.
		inline TColorTable GetColorTable() const;

		// Sets the color table of the console.
		inline void SetColorTable(const TColorTable& _rtkColorTable);

		// Gets the original color table of the console.
		inline TColorTable GetOriginalColorTable() const;



		// Gets the character used when drawing new shapes.
		inline TCHAR GetDrawChar() const;

		// Sets the character used when drawing new shapes.
		inline void SetDrawChar(const TCHAR _ckDrawChar);

#pragma endregion //~ Accessor Methods

		// Returns true if the coord is a visible screen position.
		inline bool IsValidScreenCoord(const COORD _vkPosition);

#pragma region // Drawing

		// Draws a horizontal row of characters, extending from position to the right.
		void DrawRowRaw(const COORD _vkPosition, const DWORD _ulkLength);

		// Clears the console screen, using Draw Char and Color.
		void ClearScreenRaw(const COORD _vkCursorPos = { 0, 0 });



		// Draws a rectangle.
		void DrawRectRaw(COORD _vMin, const COORD _vkMax);

		// Draws the filled inside of an outlined rectangle.
		// If min > max, draws nothing.
		void DrawRectInnerRaw(COORD _vMin, COORD _vMax);

		// Draws the outline of a rectangle.
		void DrawRectOutlineRaw(const COORD _vkMin, const COORD _vkMax);

		// Draws a rectangle with an outline.
		void DrawRectWithOutline(
			const COORD _vkMin,
			const COORD _vkMax,
			const TColor _ulkFillColor = colors::COLOR_DEFAULT,
			const TColor _ulkOutlineColor = colors::COLOR_DEFAULT,
			const TCHAR _ckFillChar = TEXT(' '),
			const TCHAR _ckOutlineChar = TEXT('X')
		);



		// Draws a styled outline of a rectangle,
		// without changing the draw color.
		void DrawPanelOutlineRaw(
			const COORD _vkMin,
			const COORD _vkMax,
			const SPanelStyle& _rtkStyle = SPanelStyle::PANELSTYLE_SINGLE
		);

		// Draws a styled rectangle.
		void DrawPanel(
			const COORD _vkMin,
			const COORD _vkMax,
			const SPanelStyle& _rtkStyle = SPanelStyle::PANELSTYLE_SINGLE
		);



		// Prints text from a stream to a rect on the screen.
		std::CWPREFIX(istream)& DrawTextRectRaw(
			const COORD _vkMin,
			const COORD _vkMax,
			std::CWPREFIX(istream)& _risTextStream
		);

#pragma region // Inline Methods

		// Clears the console screen.
		inline void ClearScreen(
			const COORD _vkCursorPos = { 0, 0 },
			const TColor _ulkColor = colors::COLOR_DEFAULT,
			const TCHAR _ckFillChar = TEXT(' ')
		);



		// Draws a horizontal row of characters, with color, extending from position to the right.
		inline void DrawRow(
			const COORD _vkPosition,
			const DWORD _ulkLength,
			const TColor _ulkDrawColor = colors::COLOR_DEFAULT,
			const TCHAR _ckDrawChar = TEXT('X')
		);

		// Draws a single character at the position.
		inline void DrawPointRaw(const COORD _vkPosition);

		// Draws a single character at the position, with color.
		inline void DrawPoint(
			const COORD _vkPosition,
			const TColor _ulkDrawColor = colors::COLOR_DEFAULT,
			const TCHAR _ckDrawChar = TEXT('X')
		);



		// Draws a rectangle.
		inline void DrawRect(
			const COORD _vkMin,
			const COORD _vkMax,
			const TColor _ulkFillColor = colors::COLOR_DEFAULT,
			const TCHAR _ckFillChar = TEXT(' ')
		);

		// Draws the outline of a rectangle.
		inline void DrawRectOutline(
			const COORD _vkMin,
			const COORD _vkMax,
			const TColor _ulkOutlineColor = colors::COLOR_DEFAULT,
			const TCHAR _ckOutlineChar = TEXT(' ')
		);



		// Draws a styled outline of a rectangle, with color.
		inline void DrawPanelOutline(
			const COORD _vkMin,
			const COORD _vkMax,
			const SPanelStyle& _rtkStyle = SPanelStyle::PANELSTYLE_SINGLE
		);



		// Prints text from a stream to a rect on the screen.
		inline std::CWPREFIX(istream)& DrawTextRect(
			const COORD _vkMin,
			const COORD _vkMax,
			std::CWPREFIX(istream)& _risTextStream,
			const TColor _ulkDrawColor = colors::COLOR_DEFAULT
		);

		// Prints text from a stream to a styled rectangle on the screen.
		inline std::CWPREFIX(istream)& DrawTextPanel(
			const COORD _vkMin,
			const COORD _vkMax,
			std::CWPREFIX(istream)& _risTextStream,
			const SPanelStyle& _rtkStyle = SPanelStyle::PANELSTYLE_SINGLE
		);

#pragma endregion //~ Inline Methods

#pragma endregion //~ Drawing

#pragma endregion //~ Methods

#pragma region // Static Functions
	private:

		// Throws a logic_error when a component of the
		// Min point is greater than that of the Max point.
		static inline void AssertMinMaxValid(
			const COORD _vkMin,
			const COORD _vkMax
		);

#pragma endregion //~ Static Functions

#pragma region // Member Variables
	private:

		// Standard output handle (Windows Console).
		const HANDLE m_hkStdout;

		// Standard input handle.
		const HANDLE m_hkStdin;

		// Original state of the console before Consolate took over.
		CONSOLE_SCREEN_BUFFER_INFOEX m_tOriginalInfo;



		// Color used when printing new text or shapes.
		TColor m_ulDrawColor;

		// Character used when painting new shapes.
		TCHAR m_cDrawChar = TEXT(' ');

#pragma endregion //~ Member Variables

	};

	// Singleton instance.
	extern CConsolate g_tConsolate;

} //~ consolate



// Include implementation for inline and template functions.
#include "consolate_imp.hpp"

#endif // __CONSOLATE_HPP__
