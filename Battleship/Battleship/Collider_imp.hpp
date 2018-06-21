//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Collider_imp.hpp
//	Description	:	Collider class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __COLLIDER_IMP_HPP__
#define __COLLIDER_IMP_HPP__

// Library Includes
#include <memory>	// move(), forward()

// This Include
#include "Collider.hpp"

// Implementation

// Default Constructor.
inline CCollider::CCollider()
	:
	CFixedArray<CVector2i>(),
	m_vBoundsMin{ 0, 0 },
	m_vBoundsMax{ 0, 0 }
{
}

// Copy Constructor.
inline CCollider::CCollider(const CCollider& _rtkOther)
	:
	CFixedArray<CVector2i>(_rtkOther),
	m_vBoundsMin(_rtkOther.m_vBoundsMin),
	m_vBoundsMax(_rtkOther.m_vBoundsMax)
{
}

// Move Constructor.
inline CCollider::CCollider(CCollider&& _rrtOther)
	:
	CFixedArray<CVector2i>(std::forward<CCollider>(_rrtOther)),
	m_vBoundsMin(std::move(_rrtOther.m_vBoundsMin)),
	m_vBoundsMax(std::move(_rrtOther.m_vBoundsMax))
{
}

// Constructor with initializer list.
inline CCollider::CCollider(std::initializer_list<CVector2i> _aList)
	:
	CFixedArray<CVector2i>(_aList)
{
	RecalculateBounds();
}

// Copy Assignment Operator.
inline CCollider& CCollider::operator=(const CCollider& _rtkOther)
{
	CFixedArray<CVector2i>::operator=(_rtkOther);
	m_vBoundsMin = _rtkOther.m_vBoundsMin;
	m_vBoundsMax = _rtkOther.m_vBoundsMax;
	return *this;
}

// Move Assignment Operator.
inline CCollider& CCollider::operator=(CCollider&& _rrtOther)
{
	CFixedArray<CVector2i>::operator=(std::forward<CCollider>(_rrtOther));
	m_vBoundsMin = std::move(_rrtOther.m_vBoundsMin);
	m_vBoundsMax = std::move(_rrtOther.m_vBoundsMax);
	return *this;
}



// Get minimum local position of any cell.
inline CVector2i CCollider::GetBoundsMin() const
{
	return m_vBoundsMin;
}

// Get maximum local position of any cell.
inline CVector2i CCollider::GetBoundsMax() const
{
	return m_vBoundsMax;
}

#endif //~ __COLLIDER_IMP_HPP__
