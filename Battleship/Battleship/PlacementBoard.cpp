//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	PlacementBoard.cpp
//	Description	:	PlacementBoard class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// This Include
#include "PlacementBoard.hpp"

// Implementation

// Clamps the selected ship so that it isn't outside the board.
void CPlacementBoard::ClampShip()
{
	CShip& rtShip = GetSelectedShipRef();
	CVector2i vNewPos = rtShip.GetPosition();
	vNewPos = m_rtGameBoard.ClampShipPosition(vNewPos, rtShip);
	rtShip.SetPosition(vNewPos);
}

// Moves the selected ship, ensuring that it doesn't go outside the board.
void CPlacementBoard::MoveShip(const CVector2i& rvkTranslation)
{
	CShip& rtShip = GetSelectedShipRef();
	CVector2i vNewPos = rtShip.GetPosition() + rvkTranslation;
	vNewPos = m_rtGameBoard.ClampShipPosition(vNewPos, rtShip);
	rtShip.SetPosition(vNewPos);
}
