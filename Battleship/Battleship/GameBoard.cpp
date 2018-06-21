//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GameBoard.cpp
//	Description	:	GameBoard class implementation file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#include "mydebug.hpp"

// Library Includes
#include <stdexcept>
#include <random>
#include <algorithm>	// any_of()

// This Include
#include "GameBoard.hpp"

// Implementation

// Updates the cells of this board according to the states of the ships.
void CGameBoard::UpdateCells()
{
	ClearCells();

	// Place Ships
	for (CShip& rtShip : m_atShips)
	{
		PlaceShip(rtShip);
	}
}



// Clears the ships and resets the cells of this board.
void CGameBoard::Reset()
{
	ClearCells();
	m_atShips.Clear();
}



// Returns true if the ship is overlapping any other ships on this board.
bool CGameBoard::IsShipOverlappingAny(const CShip& _rtkShip)
{
	using namespace std;
	return any_of(begin(m_atShips), end(m_atShips), [&](const CShip& _rtkOther)
	{
		return &_rtkShip != &_rtkOther // not the same ship
			&& _rtkShip.IsOverlapping(_rtkOther);
	});
}

// Returns true if two or more ships are overlapping each other.
bool CGameBoard::AreAnyShipsOverlapping()
{
	for (int i = 1; i < m_atShips.GetSize(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (GetShipRefAt(i).IsOverlapping(GetShipRefAt(j)))
			{
				return true;
			}
		}
	}
	return false;
}

// Returns true if all ships on a board have zero health.
bool CGameBoard::AreAllShipsDestroyed()
{
	using namespace std;
	return all_of(begin(m_atShips), end(m_atShips), [](const CShip& _rtkShip)
	{
		return _rtkShip.GetHealth() <= 0;
	});
}



// Randomizes ship positions, ensuring none overlap.
void CGameBoard::RandomizePlacement()
{
	static auto s_tRandomEngine = std::default_random_engine(std::random_device()());

	bool bFailed = false;
	for (CShip& rtShip : m_atShips)
	{
		static constexpr int MAX_TRIES = 1000;
		int iTries = MAX_TRIES;
		do
		{
			// Generate random collider index.
			rtShip.SetActiveColliderIndex(
				std::uniform_int_distribution<>(0, rtShip.GetColliderCount() - 1)(s_tRandomEngine)
			);

			const CVector2i vkBoundsMin = rtShip.GetActiveColliderRef().GetBoundsMin();
			const CVector2i vkBoundsMax = rtShip.GetActiveColliderRef().GetBoundsMax();

			// Generate random board position.
			CVector2i vNewPos = {
				std::uniform_int_distribution<>(-vkBoundsMin.m_tX, GetWidth() - 1 - vkBoundsMax.m_tX)(s_tRandomEngine),
				std::uniform_int_distribution<>(-vkBoundsMin.m_tY, GetHeight() - 1 - vkBoundsMax.m_tY)(s_tRandomEngine),
			};
			vNewPos = ClampShipPosition(vNewPos, rtShip);
			rtShip.SetPosition(vNewPos);
		}
		// while not overlapping any other ships.
		while (
			IsShipOverlappingAny(rtShip)
			&& ((--iTries) > 0)
		);

		if (iTries <= 0)
		{
			bFailed = true;
		}
	}

	// If we could not find a way to make the ships stop overlapping,
	if (bFailed)
	{
#ifdef _DEBUG
		// Intentional debug call (do not remove).
		OutputDebugString(TEXT("Failed to place ships randomly."));
#endif //~ _DEBUG


		// Assign default positions for ships, which should not overlap.
		// This default positioning assumes the ships' first collider has
		// height 1, starts at local position (0, 0), and extends to the right.
		// It also assumes there are fewer ships than rows.

		CVector2i vPosition = { 0, 0 };
		for (CShip& rtShip : m_atShips)
		{
			rtShip.SetActiveColliderIndex(0);

			rtShip.SetPosition(ClampShipPosition(vPosition, rtShip));

			++vPosition.m_tY;
		}
	}

	UpdateCells();
}



// Returns a new position vector for where the ship could be placed
// so that it will be within the bounds of this board.
// If the ship's bounds are larger than the size of this board,
// it is clamped towards (0, 0).
CVector2i CGameBoard::ClampShipPosition(CVector2i _vPosition, const CShip& _rtkShip)
{
	const CCollider& rtkCollider = _rtkShip.GetActiveColliderRef();
	CVector2i vMin = _vPosition + rtkCollider.GetBoundsMin();
	CVector2i vMax = _vPosition + rtkCollider.GetBoundsMax();
	
	// TF: Arithmetic Operator
	int iBoardMaxX = GetWidth() - 1;
	int iBoardMaxY = GetHeight() - 1;

	// TF: Relational Operator
	if (vMax.m_tX > iBoardMaxX)
	{
		_vPosition.m_tX += iBoardMaxX - vMax.m_tX;
	}

	if (vMax.m_tY > iBoardMaxY)
	{
		_vPosition.m_tY += iBoardMaxY - vMax.m_tY;
	}

	if (vMin.m_tX < 0)
	{
		_vPosition.m_tX -= vMin.m_tX;
	}

	if (vMin.m_tY < 0)
	{
		_vPosition.m_tY -= vMin.m_tY;
	}

	return _vPosition;
}

// Ensures a position is within the bounds of this board.
CVector2i CGameBoard::ClampSinglePosition(CVector2i _vPosition)
{
	int iBoardMaxX = GetWidth() - 1;
	int iBoardMaxY = GetHeight() - 1;

	if (_vPosition.m_tX > iBoardMaxX)
		_vPosition.m_tX = iBoardMaxX;

	if (_vPosition.m_tY > iBoardMaxY)
		_vPosition.m_tY = iBoardMaxY;

	if (_vPosition.m_tX < 0)
		_vPosition.m_tX = 0;

	if (_vPosition.m_tY < 0)
		_vPosition.m_tY = 0;

	return _vPosition;
}



// Changes the health of a cell.
void CGameBoard::FireAt(const CVector2i& _rvkPosition)
{
	SGameBoardCell& rtCell = GetCellRefAt(_rvkPosition);

	if (rtCell.m_iHealth == HEALTH_NORMAL)
	{
		rtCell.m_iHealth = HEALTH_HIT;

		if (rtCell.m_ptShip != nullptr)
		{
			rtCell.m_ptShip->SetHealth(rtCell.m_ptShip->GetHealth() - 1);
		}
	}
	else //if (rtCell.m_iHealth == HEALTH_HIT)
	{
		throw std::exception("That cell has already been fired at!");
	}
}

// Tries to fire at a cell.
// If it was already hit, returns false. If firing succeeded, returns true.
bool CGameBoard::TryFireAt(const CVector2i& _rvkPosition)
{
	const SGameBoardCell& rtkCell = GetCellRefAt(_rvkPosition);
	if (rtkCell.m_iHealth == HEALTH_NORMAL)
	{
		FireAt(_rvkPosition);
		return true;
	}
	else //if (rtkCell.m_iHealth == HEALTH_HIT)
	{
		return false;
	}
}



// Resets the cells of this board.
void CGameBoard::ClearCells()
{
	for (SGameBoardCell& rtCell : m_atBoard)
	{
		rtCell.m_ptShip = nullptr;
		rtCell.m_iHealth = HEALTH_NORMAL;
	}
}

// 'Prints' a ship to the board.
void CGameBoard::PlaceShip(CShip& _rtShip)
{
	// For each cell local position,
	for (const CVector2i& rtkShipCellPos : _rtShip.GetActiveColliderRef())
	{
		// Get board position.
		CVector2i vBoardCellPos = rtkShipCellPos + _rtShip.GetPosition();

		// Get board cell by reference at that position.
		SGameBoardCell& rtBoardCell = GetCellRefAt(vBoardCellPos);

		// Update cell with ship data.
		rtBoardCell.m_ptShip = &_rtShip;
	}
}
