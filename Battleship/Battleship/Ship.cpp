//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Ship.cpp
//	Description	:	Ship class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <algorithm>

// Local Includes
#include "generalmath.hpp"

// This Include
#include "Ship.hpp"

// Implementation

// Increments the active collider index by Step,
// wrapping around to stay inside the valid index range.
void CShip::CycleActiveColliderIndex(const int _ikStep)
{
	int iIndex = GetActiveColliderIndex() + _ikStep;
	iIndex = Cycle(iIndex, GetColliderCount());
	SetActiveColliderIndex(iIndex);
}
