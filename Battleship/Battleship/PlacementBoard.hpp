//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	PlacementBoard.hpp
//	Description	:	PlacementBoard class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __PLACEMENT_BOARD_HPP__
#define __PLACEMENT_BOARD_HPP__

// Local Includes
#include "generalmath.hpp"
#include "DisplayBoard.hpp"

// Declarations

class CPlacementBoard : public CDisplayBoard
{
	// Methods
public:

	// Full Constructor.
	inline CPlacementBoard(
		CGameBoard& _rtGameBoard,
		int _iSelectedShipIndex = 0,
		EDisplayMode _eDisplayMode = DISPLAY_MODE_SELF,
		int _iNavigateElementStep = 1,
		const std::wstring& _rstrkLabel = TEXT("Ships"),
		CVector2i _vPosition = { 0, 0 },
		consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
		consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
		const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
		bool _bIsInteractable = true,
		bool _bIsFocused = false
	);

	// Copy Constructor.
	inline CPlacementBoard(const CPlacementBoard& _rtkOther) = default;

	// Destructor.
	inline ~CPlacementBoard() = default;



	// Selected Ship

	inline int GetSelectedShipIndex() const;
	inline void SetSelectedShipIndex(int _iIndex);

	inline void StepSelectedShipIndex(const int _ikStep = 1);

	inline CShip& GetSelectedShipRef();
	inline const CShip& GetSelectedShipRef() const;

	// Clamps the selected ship so that it isn't outside the board.
	void ClampShip();

	// Moves the selected ship, ensuring that it doesn't go outside the board.
	void MoveShip(const CVector2i& rvkTranslation);



	// Generates color and symbol for the cell being drawn.
	SCellDisplayingData GenerateCellDisplayingData(
		const SGameBoardCell& _rtkCell,
		const CVector2i& _rvkCellBoardPos
	) const override
	{
		using namespace consolate::colors;

		// If it is the selected ship, print differently.
		if (
			GetIsFocused()
			&& _rtkCell.m_ptShip != nullptr
			&& _rtkCell.m_ptShip == &GetSelectedShipRef()
		)
		{
			const CShip& rtkShip = *_rtkCell.m_ptShip;
			if (m_rtGameBoard.IsShipOverlappingAny(rtkShip))
			{
				return { COLOR_RED, _rtkCell.m_ptShip->GetSymbol() };
			}
			else
			{
				return { COLOR_YELLOW, _rtkCell.m_ptShip->GetSymbol() };
			}
		}
		else
		{
			return CDisplayBoard::GenerateCellDisplayingData(_rtkCell, _rvkCellBoardPos);
		}
	}

	// Draws this UI element.
	void Draw() override
	{
		m_rtGameBoard.UpdateCells();
		CDisplayBoard::Draw();
	}


	// Events

	void InputEventUp() override
	{
		MoveShip({ 0, -1 });
	}

	void InputEventDown() override
	{
		MoveShip({ 0, 1 });
	}

	void InputEventLeft() override
	{
		MoveShip({ -1, 0 });
	}

	void InputEventRight() override
	{
		MoveShip({ 1, 0 });
	}

	void InputEventEnter() override
	{
		// If placement is valid,
		if (m_rtGameBoard.AreAnyShipsOverlapping() == false)
		{
			// Exit editing placement.
			GetViewRef().StepFocusedIndex(GetNavigateElementStep());
		}
	}

	void InputEventSpace() override
	{
		GetSelectedShipRef().CycleActiveColliderIndex();
		ClampShip();
	}

	void InputEventQ() override
	{
		StepSelectedShipIndex(-1);
	}

	void InputEventE() override
	{
		StepSelectedShipIndex(1);
	}



	// Member Variables
private:

	// Index of selected ship.
	int m_iSelectedShipIndex;

};



// Include implementation for inline and template functions.
#include "PlacementBoard_imp.hpp"

#endif //~ __PLACEMENT_BOARD_HPP__
