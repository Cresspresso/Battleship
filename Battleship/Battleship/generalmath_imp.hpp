//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	generalmath_imp.hpp
//	Description	:	generalmath implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GENERAL_MATH_IMP_HPP__
#define __GENERAL_MATH_IMP_HPP__

// Library Includes
#include <cmath>

// This Include
#include "generalmath.hpp"

// Clamps a value to the range [Min, Max].
template<class _T>
inline constexpr _T Clamp(const _T _tkValue, const _T _tkMin, const _T _tkMax)
{
	return (_tkValue > _tkMax ? _tkMax : (_tkValue < _tkMin ? _tkMin : _tkValue));
}



// Cycles a value by wrapping around in the range [0, Length).
template<class _T>
inline constexpr _T Cycle(_T _tValue, const _T _tkLength)
{
	_tValue %= _tkLength;
	return _tValue < 0 ? _tValue + _tkLength : _tValue;
}

// Cycles a value by wrapping around in the range [0, Length).
template<>
inline float Cycle<float>(float _fValue, const float _fkLength)
{
	_fValue = std::fmodf(_fValue, _fkLength);
	return _fValue < 0.0f ? _fValue + _fkLength : _fValue;
}

// Cycles a value by wrapping around in the range [0, Length).
template<>
inline double Cycle<double>(double _dValue, const double _dkLength)
{
	_dValue = std::fmod(_dValue, _dkLength);
	return _dValue < 0.0 ? _dValue + _dkLength : _dValue;
}



// Cycles a value by wrapping around in the range [Min, Max).
template<class _T>
inline constexpr _T Cycle(_T _tValue, const _T _tkMin, const _T _tkMax)
{
	return Cycle<_T>(_tValue - _tkMin, _tkMax - _tkMin) + _tkMin;
}

// Cycles an integer value by wrapping around in the range [Min, Max].
template<class _T>
inline constexpr _T CycleIn(_T _tValue, const _T _tkMin, const _T _tkMax)
{
	return Cycle<_T>(_tValue, _tkMin, _tkMax + 1);
}



// Throws an exception if the pointer is nullptr.
template<class _T>
inline void AssertMemoryAllocated(const _T* const _kptkPointer)
{
	if (_kptkPointer == nullptr)
		throw std::exception("Memory allocation failed.");
}



#endif //~ __GENERAL_MATH_IMP_HPP__
