//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Ship_imp.hpp
//	Description	:	Ship class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __SHIP_IMP_HPP__
#define __SHIP_IMP_HPP__

// Library Includes
#include <windows.h>	// TEXT()
#include <stdexcept>	// out_of_range
#include <functional>

// Local Includes
#include "generalmath.hpp"

// This Include
#include "Ship.hpp"

// Implementation

// Full Constructor.
// TF: Constructor
inline CShip::CShip(
	const CFixedArray<CCollider>& _rakColliders,
	const int _ikActiveColliderIndex,
	const std::wstring& _rstrkName,
	const std::wstring& _rstrkSymbol,
	const CVector2i _vkPosition
) :
	m_strName(_rstrkName),
	m_aColliders(_rakColliders),
	m_vPosition(_vkPosition),
	m_strSymbol(_rstrkSymbol)
{
	SetActiveColliderIndex(_ikActiveColliderIndex);
}

// Copy Constructor.
// TF: Copy Constructor
inline CShip::CShip(const CShip& _rtkOther)
	:
	m_strName(_rtkOther.m_strName),
	m_aColliders(_rtkOther.m_aColliders),
	m_iActiveColliderIndex(_rtkOther.m_iActiveColliderIndex),
	m_vPosition(_rtkOther.m_vPosition),
	m_strSymbol(_rtkOther.m_strSymbol)
{
}



// Gets the name of this ship.
inline const std::wstring& CShip::GetName() const
{
	return m_strName;
}

// Sets the name of this ship.
inline void CShip::SetName(const std::wstring& _rstrkName)
{
	m_strName = _rstrkName;
}



// Gets the symbol of this ship.
inline const std::wstring& CShip::GetSymbol() const
{
	return m_strSymbol;
}

// Sets the symbol of this ship.
inline void CShip::SetSymbol(const std::wstring& _rstrSymbol)
{
	m_strSymbol = _rstrSymbol;
}



// Gets the number of colliders in this ship.
inline int CShip::GetColliderCount() const
{
	return m_aColliders.GetSize();
}



// Gets the index of this ship's active collider.
inline int CShip::GetActiveColliderIndex() const
{
	return m_iActiveColliderIndex;
}

// Sets the active collider of this ship via its index.
inline void CShip::SetActiveColliderIndex(int _iActiveColliderIndex)
{
	m_iActiveColliderIndex = Clamp(_iActiveColliderIndex, 0, GetColliderCount() - 1);
	ResetHealth();
}



// Gets the active collider of this ship.
inline const CCollider& CShip::GetActiveColliderRef() const
{
	return m_aColliders.GetElementRefAt(m_iActiveColliderIndex);
}



// Gets position of this ship in board space.
inline CVector2i CShip::GetPosition() const
{
	return m_vPosition;
}

// Sets position of this ship in board space.
inline void CShip::SetPosition(CVector2i _vPosition)
{
	m_vPosition = _vPosition;
}



// Returns true if this ship's collider overlaps the
// other ship's collider in board space.
inline bool CShip::IsOverlapping(const CShip& _rtkOther) const
{
	return GetActiveColliderRef().IsOverlapping(
		_rtkOther.GetActiveColliderRef(),
		m_vPosition,
		_rtkOther.m_vPosition
	);
}



// Gets the number of cells that have not yet been hit.
inline int CShip::GetHealth() const
{
	return m_iHealth;
}

// Tells this ship how many cells have not yet been hit.
inline void CShip::SetHealth(int _iHealth)
{
	m_iHealth = Clamp(_iHealth, 0, GetActiveColliderRef().GetSize());
}

// Resets the health of this ship based on the current collider.
inline void CShip::ResetHealth()
{
	m_iHealth = GetActiveColliderRef().GetSize();
}

#endif //~ __SHIP_IMP_HPP__
