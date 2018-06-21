//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	PlacementBoard_imp.hpp
//	Description	:	PlacementBoard class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __PLACEMENT_BOARD_IMP_HPP__
#define __PLACEMENT_BOARD_IMP_HPP__

// This Include
#include "PlacementBoard.hpp"

// Implementation

// Full Constructor.
inline CPlacementBoard::CPlacementBoard(
	CGameBoard& _rtGameBoard,
	int _iSelectedShipIndex,
	EDisplayMode _eDisplayMode,
	int _iNavigateElementStep,
	const std::wstring& _rstrkLabel,
	CVector2i _vPosition,
	consolate::TColor _ulNormalColor,
	consolate::TColor _ulFocusedColor,
	const consolate::SPanelStyle& _rtkPanelStyle,
	bool _bIsInteractable,
	bool _bIsFocused
) :
	m_iSelectedShipIndex(_iSelectedShipIndex),
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
}



inline int CPlacementBoard::GetSelectedShipIndex() const
{
	return m_iSelectedShipIndex;
}

inline void CPlacementBoard::SetSelectedShipIndex(int _iIndex)
{
	m_iSelectedShipIndex = Cycle(_iIndex, m_rtGameBoard.GetShipCount());
}

inline void CPlacementBoard::StepSelectedShipIndex(const int _ikStep)
{
	SetSelectedShipIndex(GetSelectedShipIndex() + _ikStep);
}

inline CShip& CPlacementBoard::GetSelectedShipRef()
{
	return m_rtGameBoard.GetShipRefAt(GetSelectedShipIndex());
}

inline const CShip& CPlacementBoard::GetSelectedShipRef() const
{
	return m_rtGameBoard.GetShipRefAt(GetSelectedShipIndex());
}

#endif //~ __PLACEMENT_BOARD_IMP_HPP__
