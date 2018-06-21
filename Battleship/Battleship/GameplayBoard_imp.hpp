//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GameplayBoard_imp.hpp
//	Description	:	GameplayBoard class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GAMEPLAY_BOARD_IMP_HPP__
#define __GAMEPLAY_BOARD_IMP_HPP__

// This Include
#include "GameplayBoard.hpp"

// Implementation

// Full Constructor.
inline CGameplayBoard::CGameplayBoard(
	CGameBoard& _rtGameBoard,
	EDisplayMode _eDisplayMode,
	CVector2i _vReticlePosition,
	int _iNavigateElementStep,
	const std::wstring& _rstrkLabel,
	CVector2i _vPosition,
	consolate::TColor _ulNormalColor,
	consolate::TColor _ulFocusedColor,
	const consolate::SPanelStyle& _rtkPanelStyle,
	bool _bIsInteractable,
	bool _bIsFocused
) :
	CDisplayBoard(
		_rtGameBoard,
		_eDisplayMode,
		_iNavigateElementStep,
		_rstrkLabel,
		_vPosition,
		_ulNormalColor,
		_ulFocusedColor,
		_rtkPanelStyle,
		_bIsInteractable,
		_bIsFocused
	)
{
	SetReticlePosition(_vReticlePosition);
}



// Sets the action to be invoked after the player fires a shot.
inline void CGameplayBoard::SetOnAfterFireHandler(TOnAfterFireEventHandler _fnOnAfterFireAction)
{
	m_fnOnAfterFireAction = _fnOnAfterFireAction;
}



// Gets the targeting reticle position.
inline CVector2i CGameplayBoard::GetReticlePosition() const
{
	return m_vReticlePosition;
}

// Sets the targeting reticle position, ensuring that it isn't outside the board.
inline void CGameplayBoard::SetReticlePosition(CVector2i _vReticlePosition)
{
	m_vReticlePosition = m_rtGameBoard.ClampSinglePosition(_vReticlePosition);
}

// Moves the targeting reticle, ensuring that it doesn't go outside the board.
inline void CGameplayBoard::MoveReticle(const CVector2i& _rvkTranslation)
{
	SetReticlePosition(GetReticlePosition() + _rvkTranslation);
}

#endif //~ __GAMEPLAY_BOARD_IMP_HPP__
