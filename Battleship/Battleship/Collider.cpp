//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Collider.cpp
//	Description	:	Collider class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// This Include
#include "Collider.hpp"

// Implementation

// Returns true if the two colliders are overlapping in board space.
bool CCollider::IsOverlapping(
	const CCollider& _rtkOther,
	const CVector2i& _rvkPosition,
	const CVector2i& _rvkPositionOther
) const
{
	const int iEnd = GetSize();
	// for each cell in this collider
	// TF: Iteration Structure
	for (int i = 0; i < iEnd; ++i)
	{
		CVector2i tA = GetElementRefAt(i) + _rvkPosition;

		// for each cell in the other collider
		const int jEnd = _rtkOther.GetSize();
		for (int j = 0; j < jEnd; ++j)
		{
			CVector2i tB = _rtkOther.GetElementRefAt(j) + _rvkPositionOther;

			// if they have the same position in board space
			// TF: Conditional Statement
			if (tA == tB)
			{
				return true;
			}
		}
	}
	return false;
}



// Recalculates the local bounds of this collider.
void CCollider::RecalculateBounds()
{
	m_vBoundsMin = { 0, 0 };
	m_vBoundsMax = { 0, 0 };

	for (int i = 0; i < GetSize(); ++i)
	{
		const CVector2i& rvkCell = GetElementRefAt(i);

		if (m_vBoundsMin.m_tX > rvkCell.m_tX)
			m_vBoundsMin.m_tX = rvkCell.m_tX;

		if (m_vBoundsMin.m_tY > rvkCell.m_tY)
			m_vBoundsMin.m_tY = rvkCell.m_tY;

		if (m_vBoundsMax.m_tX < rvkCell.m_tX)
			m_vBoundsMax.m_tX = rvkCell.m_tX;

		if (m_vBoundsMax.m_tY < rvkCell.m_tY)
			m_vBoundsMax.m_tY = rvkCell.m_tY;
	}
}
