//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Vector2.hpp
//	Description	:	Vector2 class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __VECTOR_2_HPP__
#define __VECTOR_2_HPP__

// Library Includes
#include <Windows.h>	// COORD
#include <string>

// Vector of two components.
template<class _T>
class CVector2
{
	// Methods
public:

#pragma region // Operators

	// Compares equality of this vector with another vector.
	inline bool operator==(const CVector2<_T>& _rvkOther) const;

	// Compares inequality of this vector with another vector.
	inline bool operator!=(const CVector2<_T>& _rvkOther) const;



	// Adds a vector to this vector.
	inline CVector2<_T>& operator+=(const CVector2<_T>& _rvkOther);

	// Subtracts a vector from this vector.
	inline CVector2<_T>& operator-=(const CVector2<_T>& _rvkOther);



	// Vector addition. Returns the sum of two vectors.
	template<class _T0>
	friend inline CVector2<_T0> operator+(CVector2<_T0> _vLhs, const CVector2<_T0>& _rvkRhs);

	// Vector subtraction. Returns the sum of one vector and the inverse of another.
	template<class _T0>
	friend inline CVector2<_T0> operator-(CVector2<_T0> _vLhs, const CVector2<_T0>& _rvkRhs);

#pragma endregion //~ Operators



	// Member Variables
public:

	// X component.
	_T m_tX;

	// Y component.
	_T m_tY;

};

// Types

// Vector of two int components.
using CVector2i = CVector2<int>;

#pragma region // Functions

// Vector addition. Returns the sum of two vectors.
template<class _T>
inline CVector2<_T> operator+(CVector2<_T> _vLhs, const CVector2<_T>& _rvkRhs);

// Vector subtraction. Returns the sum of one vector and the inverse of another.
template<class _T>
inline CVector2<_T> operator-(CVector2<_T> _vLhs, const CVector2<_T>& _rvkRhs);



// Creates a string representation of a vector.
// Format: "(X, Y)"
template<class _T>
std::wstring ToString(const CVector2<_T> _vVector);



// Converts a vector to a COORD.
template<class _T>
inline COORD ToCoord(const CVector2<_T> _vVector);

// Converts a COORD to a vector.
template<class _T>
inline CVector2<_T> ToVector(const COORD _vCoord);

#pragma endregion //~ Functions



// Include implementation for inline and template functions.
#include "Vector2_imp.hpp"

#endif //~ __VECTOR_2_HPP__
