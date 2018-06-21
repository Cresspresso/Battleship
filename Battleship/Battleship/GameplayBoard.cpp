//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GameplayBoard.cpp
//	Description	:	GameplayBoard class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// This Include
#include "GameplayBoard.hpp"

// Implementation

// Tries to fire at the targeting reticle position.
void CGameplayBoard::EventFire()
{
	// If player successfully fired at the cell,
	if (m_rtGameBoard.TryFireAt(m_vReticlePosition))
	{
		// Invoke OnFire event.
		if (m_fnOnAfterFireAction != nullptr)
		{
			m_fnOnAfterFireAction(*this);
		}
	}
}
