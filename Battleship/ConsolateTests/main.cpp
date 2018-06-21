//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	main.cpp
//	Description	:	Main implementation file.
//					Manual tests for Consolate project.
//	Project		:	ConsolateTests
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <conio.h>
#include <iostream>
#include <sstream>

// Solution Library Includes
#include <consolate.hpp>

// Local Includes
#include "CTAssert.hpp"

// Usings
using namespace consolate;
using namespace consolate::colors;
using namespace consolate::colortable;

// Implementation

bool g_bWaitEnabled = true;

void Wait()
{
	if (g_bWaitEnabled)
	{
		_getch();
	}
}

// Prints all combinations of console foreground and
// background colors in a 15x15 grid.
void PrintAllColors()
{
	for (TColor i = COLOR_BG_0; i <= COLOR_BG_15; i += 0x10)
	{
		for (TColor j = COLOR_0; j <= COLOR_15; ++j)
		{
			g_tConsolate.SetColor(i | j);
			std::CWPREFIX(cout) << ((i + j) % 10);
		}
		std::CWPREFIX(cout) << std::endl;
	}
	Wait();
}

// Cycles through some color tables for the console.
void ChangeColorTables()
{
	// test TColorTable constants
	g_tConsolate.SetColorTable(COLORTABLE_GRAYSCALE);
	Wait();

	g_tConsolate.SetColorTable(COLORTABLE_BASIC);
	Wait();

	g_tConsolate.SetColorTable(COLORTABLE_PASTEL);
	Wait();

	// test custom ColorTable
	TColorTable tMyTable = COLORTABLE_BASIC;
	tMyTable.at(4) = RGB(255, 128, 64);
	tMyTable.at(15) = RGB(220, 110, 55);
	// test index out of range exceptions
	ASSERT_FAILS(tMyTable.at(16) = RGB(64, 255, 128));
	
	g_tConsolate.SetColorTable(tMyTable);
	Wait();

	// test restoring original ColorTable
	g_tConsolate.SetColorTable(g_tConsolate.GetOriginalColorTable());
	Wait();
}

// Demonstrates some DrawRect functions.
void DrawRects()
{
	g_tConsolate.ClearScreen();
	g_tConsolate.DrawRect({ 5, 5 }, { 10, 10 }, COLOR_BG_RED, TEXT('.'));
	g_tConsolate.DrawRectOutline({ 20, 3 }, { 40, 5 }, COLOR_BG_BLUE, TEXT('X'));
	g_tConsolate.DrawRectWithOutline({ 20, 8 }, { 40, 12 }, COLOR_BG_YELLOW, COLOR_BG_GREEN, TEXT('X'), TEXT('Y'));
	Wait();
}

// Demonstrates some DrawPanel functions.
void DrawPanels()
{
	g_tConsolate.ClearScreen();
	g_tConsolate.DrawPanel({ 5, 5 }, { 10, 10 });
	g_tConsolate.DrawPanel({ 15, 5 }, { 20, 10 }, SPanelStyle::PANELSTYLE_DOUBLE);

	SPanelStyle tMyStyle = SPanelStyle::PANELSTYLE_SINGLE;
	tMyStyle.m_cFill = TEXT('@');
	tMyStyle.m_ulFillColor = COLOR_BG_DARK_RED | COLOR_RED;
	tMyStyle.m_ulOutlineColor = COLOR_BG_DARK_GRAY | COLOR_WHITE;
	g_tConsolate.DrawPanel({ 25, 5 }, { 35, 10 }, tMyStyle);
	Wait();
}

// Demonstrates some DrawTextBox functions.
void DrawTextBoxes()
{
	g_tConsolate.ClearScreen();

	std::CWPREFIX(stringstream) iosTextStream;
	iosTextStream << TEXT("Hello World! These are fancy words, I hope you like them. ");
	iosTextStream << TEXT("Unfortunately, this is not the end for testing this text box. ");
	iosTextStream << TEXT("When we run out of space, then we will know the truth.");

	g_tConsolate.DrawTextRect({ 3, 3 }, { 45, 5 }, iosTextStream, COLOR_YELLOW);
	g_tConsolate.DrawRectOutline({ 2, 2 }, { 46, 6 }, COLOR_BG_DARK_GRAY);

	g_tConsolate.DrawTextRect({ 60, 3 }, { 85, 3 }, iosTextStream, COLOR_GREEN);
	g_tConsolate.DrawRectOutline({ 59, 2 }, { 86, 4 }, COLOR_BG_BLUE);

	// Clear stream so that it is empty.
	iosTextStream.str(std::CWPREFIX(string)());
	iosTextStream << TEXT("This is a single line.\nThis is also another second line.\nThird line for the win!");

	g_tConsolate.DrawTextRect({ 3, 12 }, { 45, 24 }, iosTextStream, COLOR_YELLOW);
	g_tConsolate.DrawRectOutline({ 2, 11 }, { 46, 25 }, COLOR_BG_DARK_GRAY);

	Wait();
}

// Main program entry.
int main()
{
	std::CWPREFIX(cout) << TEXT("Manual Tests for Consolate project.") << std::endl;
	_getch();

	PrintAllColors();
	ChangeColorTables();
	DrawRects();
	DrawPanels();
	DrawTextBoxes();

	g_tConsolate.Reset();
	std::CWPREFIX(cout) << TEXT("Tests have finished.") << std::endl;
	_getch();
	return 0;
}
