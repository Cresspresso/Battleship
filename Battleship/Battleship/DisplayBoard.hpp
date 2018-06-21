//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	DisplayBoard.hpp
//	Description	:	DisplayBoard class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __DISPLAY_BOARD_HPP__
#define __DISPLAY_BOARD_HPP__

// Library Includes
#include <iostream>
#include <string>

// Solution Library Includes
#include <consolate.hpp>

// Local Includes
#include "ui_TextRect.hpp"
#include "GameBoard.hpp"

// Declarations

enum EDisplayMode
{
	// Indicates the board is owned by the player. Displays everything.
	DISPLAY_MODE_SELF,

	// The enemy board. Hide cells that have not been fired at.
	DISPLAY_MODE_ENEMY,
};

struct SCellDisplayingData
{
	consolate::TColor m_ulColor;
	std::wstring m_strSymbol;
};

// UI element for drawing a GameBoard.
class CDisplayBoard : public ui::CTextRect
{
	// Constants
private:

	// Screen size of a cell, in characters.
	static const CVector2i CELL_SIZE;


	// Methods
public:

	// Full Constructor.
	inline CDisplayBoard(
		CGameBoard& _rtGameBoard,
		EDisplayMode _eDisplayMode = DISPLAY_MODE_SELF,
		int _iNavigateElementStep = 1,
		const std::wstring& _rstrkLabel = TEXT("Board"),
		CVector2i _vPosition = { 0, 0 },
		consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
		consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
		const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
		bool _bIsInteractable = false,
		bool _bIsFocused = false
	);

	// Copy Constructor.
	inline CDisplayBoard(const CDisplayBoard& _rtkOther) = default;

	// Destructor.
	inline ~CDisplayBoard() = default;



	inline EDisplayMode GetDisplayMode() const;
	inline void SetDisplayMode(EDisplayMode _eDisplayMode);

	inline int GetNavigateElementStep() const;
	inline void SetNavigateElementStep(int _iStep);

	inline const std::wstring& GetLabel() const;
	inline void SetLabel(const std::wstring& _rstrkLabel);



	// Recalculates the size of this UI element based on the board size.
	inline void RecalculateSize();

	// Converts a position from board space to screen space.
	inline CVector2i ConvertBoardPosToScreenPos(const CVector2i _vkBoardPos);



	// Generates color and symbol for the cell being drawn.
	virtual SCellDisplayingData GenerateCellDisplayingData(
		const SGameBoardCell& _rtkCell,
		const CVector2i& /*_rvkCellBoardPos*/
	) const
	{
		using namespace consolate::colors;

		if (_rtkCell.m_ptShip == nullptr)
		{
			if (_rtkCell.m_iHealth == HEALTH_HIT)
			{
				return { COLOR_DARK_BLUE, TEXT("-") };
			}
			else //if (_rtkCell.m_iHealth == HEALTH_NORMAL)
			{
				return { COLOR_BLUE, TEXT("~") };
			}
		}
		else
		{
			if (m_eDisplayMode == DISPLAY_MODE_SELF)
			{
				if (_rtkCell.m_iHealth == HEALTH_HIT)
				{
					return { COLOR_RED, _rtkCell.m_ptShip->GetSymbol() };
				}
				else //if (_rtkCell.m_iHealth == HEALTH_NORMAL)
				{
					return { COLOR_WHITE, _rtkCell.m_ptShip->GetSymbol() };
				}
			}
			else //if (m_eDisplayMode == DISPLAY_MODE_ENEMY)
			{
				if (_rtkCell.m_iHealth == HEALTH_HIT)
				{
					if (_rtkCell.m_ptShip->GetHealth() == 0)
					{
						return { COLOR_RED, _rtkCell.m_ptShip->GetSymbol() };
					}
					else
					{
						return { COLOR_RED, TEXT("X") };
					}
				}
				else //if (_rtkCell.m_iHealth == HEALTH_NORMAL)
				{
					return { COLOR_BLUE, TEXT("~") };
				}
			}
		}
	}

	// Draws this UI element.
	void Draw() override
	{
		using namespace std;
		using namespace consolate;
		using namespace consolate::colors;

		RecalculateSize();

		// Get positions.

		const CVector2i vkPos = GetPosition();
		const CVector2i vkMax = vkPos + GetSize() - CVector2i{ 1, 1 };

		// Draw Label.
		const CVector2i vkLabelPos = vkPos + CVector2i{ 1, -1 };
		g_tConsolate.SetCursorPosition(ToCoord(vkLabelPos));
		g_tConsolate.SetColor(GetDisplayColor());
		std::wcout << GetLabel();

		// Draw border box.
		ui::CTextRect::Draw();

		// For each cell,
		for (int iRow = 0; iRow < m_rtGameBoard.GetHeight(); ++iRow)
		{
			for (int iColumn = 0; iColumn < m_rtGameBoard.GetWidth(); ++iColumn)
			{
				// Get cell position in board and screen space.
				const CVector2i vkCellBoardPos = { iRow, iColumn };
				const CVector2i vkCellScreenPos = ConvertBoardPosToScreenPos(vkCellBoardPos);

				// Get the game board cell.
				const SGameBoardCell& rtkGameCell = m_rtGameBoard.GetCellRefAt(vkCellBoardPos);

				// Get cell symbol and color.
				SCellDisplayingData tData = GenerateCellDisplayingData(rtkGameCell, vkCellBoardPos);
				tData.m_strSymbol = tData.m_strSymbol.substr(0, CELL_SIZE.m_tX);

				// Draw the cell.
				g_tConsolate.SetCursorPosition(ToCoord(vkCellScreenPos));
				g_tConsolate.SetColor(tData.m_ulColor);
				wcout << tData.m_strSymbol;
			}
		}
	}



	// Member Variables
protected:

	// The game board to draw.
	CGameBoard& m_rtGameBoard;



private:

	// How to draw the board.
	EDisplayMode m_eDisplayMode;

	// Label to appear above this DisplayBoard element.
	std::wstring m_strLabel;

	// Amount of steps when navigating away from this element.
	// (Used by daughter classes, not this class.)
	int m_iNavigateElementStep;

};



// Include implementation for inline and template functions.
#include "DisplayBoard_imp.hpp"

#endif //~ __DISPLAY_BOARD_HPP__
