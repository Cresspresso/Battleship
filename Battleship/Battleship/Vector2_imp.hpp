//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Vector2_imp.hpp
//	Description	:	Vector2 class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __VECTOR_2_IMP_HPP__
#define __VECTOR_2_IMP_HPP__

// Library Includes
#include <sstream>

// This Include
#include "Vector2.hpp"

// Implementation

// Compares equality of this vector with another vector.
template<class _T>
inline bool CVector2<_T>::operator==(const CVector2<_T>& _rvkOther) const
{
	return m_tX == _rvkOther.m_tX
		&& m_tY == _rvkOther.m_tY;
}

// Compares inequality of this vector with another vector.
template<class _T>
inline bool CVector2<_T>::operator!=(const CVector2<_T>& _rvkOther) const
{
	return m_tX != _rvkOther.m_tX
		|| m_tY != _rvkOther.m_tY;
}



// Adds a vector to this vector.
template<class _T>
inline CVector2<_T>& CVector2<_T>::operator+=(const CVector2<_T>& _rvkOther)
{
	m_tX += _rvkOther.m_tX;
	m_tY += _rvkOther.m_tY;
	return *this;
}

// Subtracts a vector from this vector.
template<class _T>
inline CVector2<_T>& CVector2<_T>::operator-=(const CVector2<_T>& _rvkOther)
{
	m_tX -= _rvkOther.m_tX;
	m_tY -= _rvkOther.m_tY;
	return *this;
}



// Vector addition. Returns the sum of two vectors.
template<class _T>
inline CVector2<_T> operator+(CVector2<_T> _vLhs, const CVector2<_T>& _rvkRhs)
{
	_vLhs += _rvkRhs;
	return _vLhs;
}

// Vector subtraction. Returns the sum of one vector and the inverse of another.
template<class _T>
inline CVector2<_T> operator-(CVector2<_T> _vLhs, const CVector2<_T>& _rvkRhs)
{
	_vLhs -= _rvkRhs;
	return _vLhs;
}



// Creates a string representation of a vector.
// Format: "(X, Y)"
template<class _T>
std::wstring ToString(const CVector2<_T> _vVector)
{
	std::wstringstream iosStream;
	iosStream << TEXT('(') << _vVector.m_tX << TEXT(", ") << _vVector.m_tY << TEXT(')');
	return iosStream.str();
}



// Converts a vector to a COORD.
template<class _T>
inline COORD ToCoord(const CVector2<_T> _vVector)
{
	return {
		static_cast<short>(_vVector.m_tX),
		static_cast<short>(_vVector.m_tY)
	};
}

// Converts a COORD to a vector.
template<class _T>
inline CVector2<_T> ToVector(const COORD _vCoord)
{
	return {
		static_cast<_T>(_vCoord.X),
		static_cast<_T>(_vCoord.Y)
	};
}

#endif //~ __VECTOR_2_IMP_HPP__
