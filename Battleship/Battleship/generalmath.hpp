//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	GeneralFunctions.hpp
//	Description	:	GeneralFunctions declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GENERAL_MATH_HPP__
#define __GENERAL_MATH_HPP__

// Declarations

// Clamps a value to the range [Min, Max].
template<class _T>
inline constexpr _T Clamp(const _T _tkValue, const _T _tkMin, const _T _tkMax);



// Cycles a value by wrapping around in the range [0, Length).
template<class _T>
inline constexpr _T Cycle(_T _tValue, const _T _tkLength);

// Cycles a value by wrapping around in the range [0, Length).
template<>
inline float Cycle<float>(float _fValue, const float _fkLength);

// Cycles a value by wrapping around in the range [0, Length).
template<>
inline double Cycle<double>(double _dValue, const double _dkLength);



// Cycles a value by wrapping around in the range [Min, Max).
template<class _T>
inline constexpr _T Cycle(_T _tValue, const _T _tkMin, const _T _tkMax);

// Cycles an integer value by wrapping around in the range [Min, Max].
template<class _T>
inline constexpr _T CycleIn(_T _tValue, const _T _tkMin, const _T _tkMax);



// Include implementation for inline and template functions.
#include "generalmath_imp.hpp"

#endif //~ __GENERAL_MATH_HPP__
