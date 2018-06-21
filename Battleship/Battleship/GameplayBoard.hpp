//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GameplayBoard.hpp
//	Description	:	GameplayBoard class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GAMEPLAY_BOARD_HPP__
#define __GAMEPLAY_BOARD_HPP__

// Library Includes
#include <functional>

// Local Includes
#include "DisplayBoard.hpp"

// Declarations

// UI Element that allows the player to shoot somewhere on the enemy board.
class CGameplayBoard : public CDisplayBoard
{
	// Types
public:

	// Event invoked after the player fires a shot.
	using TOnAfterFireEventHandler = std::function<void(CGameplayBoard& _rtViewElement)>;



	// Methods
public:

	// Full Constructor.
	inline CGameplayBoard(
		CGameBoard& _rtGameBoard,
		EDisplayMode _eDisplayMode = DISPLAY_MODE_ENEMY,
		CVector2i _vReticlePosition = { 0, 0 },
		int _iNavigateElementStep = 1,
		const std::wstring& _rstrkLabel = TEXT("Shots"),
		CVector2i _vPosition = { 0, 0 },
		consolate::TColor _ulNormalColor = consolate::colors::COLOR_DEFAULT,
		consolate::TColor _ulFocusedColor = consolate::colors::COLOR_DEFAULT,
		const consolate::SPanelStyle& _rtkPanelStyle = consolate::SPanelStyle::PANELSTYLE_SINGLE,
		bool _bIsInteractable = true,
		bool _bIsFocused = false
	);

	// Copy Constructor.
	inline CGameplayBoard(const CGameplayBoard& _rtkOther) = default;

	// Destructor.
	inline ~CGameplayBoard() = default;



	// Sets the action to be invoked after the player fires a shot.
	inline void SetOnAfterFireHandler(TOnAfterFireEventHandler _fnOnAfterFireAction);



	// Gets the targeting reticle position.
	inline CVector2i GetReticlePosition() const;

	// Sets the targeting reticle position, ensuring that it isn't outside the board.
	inline void SetReticlePosition(CVector2i _vReticlePosition);

	// Moves the targeting reticle, ensuring that it doesn't go outside the board.
	inline void MoveReticle(const CVector2i& _rvkTranslation);



	// Tries to fire at the targeting reticle position.
	void EventFire();



	// Generates color and symbol for the cell being drawn.
	SCellDisplayingData GenerateCellDisplayingData(
		const SGameBoardCell& _rtkCell,
		const CVector2i& _rvkCellBoardPos
	) const override
	{
		using namespace consolate::colors;

		// If it is the cell under the targeting reticle, draw differently.
		if (_rvkCellBoardPos == GetReticlePosition())
		{
			if (_rtkCell.m_iHealth == HEALTH_HIT)
			{
				return {
					COLOR_BG_DARK_RED,
					CDisplayBoard::GenerateCellDisplayingData(_rtkCell, _rvkCellBoardPos).m_strSymbol
				};
			}
			else //if (_rtkCell.m_iHealth == HEALTH_NORMAL)
			{
				return {
					COLOR_BG_YELLOW,
					CDisplayBoard::GenerateCellDisplayingData(_rtkCell, _rvkCellBoardPos).m_strSymbol
				};
			}
		}
		else
		{
			return CDisplayBoard::GenerateCellDisplayingData(_rtkCell, _rvkCellBoardPos);
		}
	}



	// Events

	void InputEventUp() override
	{
		MoveReticle({ 0, -1 });
	}

	void InputEventDown() override
	{
		MoveReticle({ 0, 1 });
	}

	void InputEventLeft() override
	{
		MoveReticle({ -1, 0 });
	}

	void InputEventRight() override
	{
		MoveReticle({ 1, 0 });
	}

	void InputEventEnter() override
	{
		EventFire();
	}

	void InputEventSpace() override
	{
		EventFire();
	}

	void InputEventEscape() override
	{
		GetViewRef().StepFocusedIndex(GetNavigateElementStep());
	}



	// Member Variables
private:

	// Position of the targeting reticle.
	CVector2i m_vReticlePosition;

	// Event invoked after the player fires a shot.
	TOnAfterFireEventHandler m_fnOnAfterFireAction = nullptr;

};



// Include implementation for inline and template functions.
#include "GameplayBoard_imp.hpp"

#endif //~ __GAMEPLAY_BOARD_HPP__