//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GameBoard_imp.hpp
//	Description	:	GameBoard class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GAME_BOARD_IMP_HPP__
#define __GAME_BOARD_IMP_HPP__

// This Include
#include "GameBoard.hpp"

// Implementation

// Constructor with dimensions.
inline CGameBoard::CGameBoard(const int _ikWidth, const int _ikHeight)
	:
	m_atBoard(_ikWidth, _ikHeight),
	m_atShips()
{
}



// Gets width of this board.
inline int CGameBoard::GetWidth() const
{
	return m_atBoard.GetWidth();
}

// Gets height of this board.
inline int CGameBoard::GetHeight() const
{
	return m_atBoard.GetHeight();
}

// Sets width and height of this board.
inline void CGameBoard::Resize(const int _ikWidth, const int _ikHeight)
{
	m_atBoard.Resize(_ikWidth, _ikHeight);
}



// Adds a ship to this board by copy.
inline void CGameBoard::AddShip(const CShip& _rtkShip)
{
	m_atShips.AddElement(_rtkShip);
}

// Gets the number of ships on this board.
inline int CGameBoard::GetShipCount() const
{
	return m_atShips.GetSize();
}

// Gets a reference to a ship on this board.
inline CShip& CGameBoard::GetShipRefAt(const int _ikShipIndex)
{
	return m_atShips.GetElementRefAt(_ikShipIndex);
}

// Gets a const reference to a ship on this board.
inline const CShip& CGameBoard::GetShipRefAt(const int _ikShipIndex) const
{
	return m_atShips.GetElementRefAt(_ikShipIndex);
}

// Gets a read-only reference to the the list of ships on this board.
inline const CFixedArray<CShip>& CGameBoard::GetShips() const
{
	return m_atShips;
}



// Gets a reference to a cell in this board.
inline SGameBoardCell& CGameBoard::GetCellRefAt(const CVector2i& _rtkPosition)
{
	return m_atBoard.GetElementRefAt(_rtkPosition.m_tX, _rtkPosition.m_tY);
}

// Gets a const reference to a cell in this board.
inline const SGameBoardCell& CGameBoard::GetCellRefAt(const CVector2i& _rtkPosition) const
{
	return m_atBoard.GetElementRefAt(_rtkPosition.m_tX, _rtkPosition.m_tY);
}

#endif //~ __GAME_BOARD_IMP_HPP__
