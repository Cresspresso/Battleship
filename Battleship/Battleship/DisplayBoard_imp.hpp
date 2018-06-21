//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	DisplayBoard_imp.hpp
//	Description	:	DisplayBoard class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __DISPLAY_BOARD_IMP_HPP__
#define __DISPLAY_BOARD_IMP_HPP__

// This Include
#include "DisplayBoard.hpp"

// Implementation

// Full Constructor.
inline CDisplayBoard::CDisplayBoard(
	CGameBoard& _rtGameBoard,
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
	m_rtGameBoard(_rtGameBoard),
	m_eDisplayMode(_eDisplayMode),
	m_strLabel(_rstrkLabel),
	m_iNavigateElementStep(_iNavigateElementStep),
	CTextRect(
		_vPosition,
		{ 10, 3 }, // placeholder
		TEXT(""),
		_ulNormalColor,
		_ulFocusedColor,
		_rtkPanelStyle,
		_bIsInteractable,
		_bIsFocused
	)
{
	RecalculateSize();
}



inline EDisplayMode CDisplayBoard::GetDisplayMode() const
{
	return m_eDisplayMode;
}

inline void CDisplayBoard::SetDisplayMode(EDisplayMode _eDisplayMode)
{
	m_eDisplayMode = _eDisplayMode;
}



inline int CDisplayBoard::GetNavigateElementStep() const
{
	return m_iNavigateElementStep;
}

inline void CDisplayBoard::SetNavigateElementStep(int _iStep)
{
	m_iNavigateElementStep = _iStep;
}



inline const std::wstring& CDisplayBoard::GetLabel() const
{
	return m_strLabel;
}

inline void CDisplayBoard::SetLabel(const std::wstring& _rstrkLabel)
{
	m_strLabel = _rstrkLabel;
}



// Recalculates the size of this UI element based on the board size.
inline void CDisplayBoard::RecalculateSize()
{
	SetSize({
		2 + m_rtGameBoard.GetWidth() * CELL_SIZE.m_tX,
		2 + m_rtGameBoard.GetHeight() * CELL_SIZE.m_tY
	});
}

// Converts a position from board space to screen space.
inline CVector2i CDisplayBoard::ConvertBoardPosToScreenPos(const CVector2i _vkBoardPos)
{
	return CVector2i{
		1 + _vkBoardPos.m_tX * CELL_SIZE.m_tX,
		1 + _vkBoardPos.m_tY * CELL_SIZE.m_tY,
	} + GetPosition();
}

#endif //~ __DISPLAY_BOARD_IMP_HPP__
