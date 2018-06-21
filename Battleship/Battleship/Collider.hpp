//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Collider.hpp
//	Description	:	Collider class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __COLLIDER_HPP__
#define __COLLIDER_HPP__

// Library Includes
#include <initializer_list>

// Local Includes
#include "FixedArray.hpp"
#include "Vector2.hpp"

// Declarations

// A list of local cell positions,
// for detecting overlapping geometry and bounds checking.
class CCollider : private CFixedArray<CVector2i>
{
	// Methods
public:

	// Default Constructor.
	inline CCollider();

	// Copy Constructor.
	inline CCollider(const CCollider& _rtkOther);

	// Move Constructor.
	inline CCollider(CCollider&& _rrtOther);

	// Constructor with initializer list.
	inline CCollider(std::initializer_list<CVector2i> _aList);

	// Destructor.
	inline ~CCollider() = default;

	// Copy Assignment Operator.
	inline CCollider& operator=(const CCollider& _rtkOther);

	// Move Assignment Operator.
	inline CCollider& operator=(CCollider&& _rrtOther);



	// Get local cell position at array index by value.
	using CFixedArray<CVector2i>::GetElementAt;

	// Get local cell position at array index by reference.
	using CFixedArray<CVector2i>::GetElementRefAt;

	// Get the number of cells in this collider.
	using CFixedArray<CVector2i>::GetSize;

	using CFixedArray<CVector2i>::begin;
	using CFixedArray<CVector2i>::end;



	// Get minimum local position of any cell.
	inline CVector2i GetBoundsMin() const;

	// Get maximum local position of any cell.
	inline CVector2i GetBoundsMax() const;



	// Returns true if the two colliders are overlapping in board space.
	bool IsOverlapping(
		const CCollider& _rtkOther,
		const CVector2i& _rvkPosition,
		const CVector2i& _rvkPositionOther
	) const;



private:

	// Recalculates the local bounds of this collider.
	void RecalculateBounds();



	// Member Variables
private:

	// Minimum local position of any cell.
	CVector2i m_vBoundsMin;

	// Maximum local position of any cell.
	CVector2i m_vBoundsMax;

};




// Include implementation for inline and template functions.
#include "Collider_imp.hpp"

#endif //~ __COLLIDER_HPP__
