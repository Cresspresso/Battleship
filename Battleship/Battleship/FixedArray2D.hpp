//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	FixedArray2D.hpp
//	Description	:	FixedArray2D class declaration file.
//					Dynamic memory for a 2D array.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __FIXED_ARRAY_2D_HPP__
#define __FIXED_ARRAY_2D_HPP__

// Library Includes
#include <functional>	// function<>
#include <memory>		// move(), forward()

// Local Includes
#include "FixedArray.hpp"

// Declarations

// A two-dimensional array of elements of a single type.
template<class _T>
class CFixedArray2D : private CFixedArray<_T>
{
	// Methods
public:

	// Default Constructor.
	inline CFixedArray2D();

	// Copy Constructor.
	inline CFixedArray2D(const CFixedArray2D<_T>& _rtkOther);

	// Move Constructor.
	inline CFixedArray2D(CFixedArray2D<_T>&& _rrtOther);

	// Constructor with width and height of the 2D array.
	inline CFixedArray2D(
		const int _ikWidth,
		const int _ikHeight
	);

	// Constructor with default element value.
	inline CFixedArray2D(
		const int _ikWidth,
		const int _ikHeight,
		const _T& _rtkDefaultValue
	);

	// Constructor with nested initializer lists.
	CFixedArray2D(std::initializer_list<std::initializer_list<_T>> _aaList);

	// Destructor.
	inline ~CFixedArray2D() = default;

	// Copy Assignment Operator.
	inline CFixedArray2D<_T>& operator=(const CFixedArray2D<_T>& _rtkOther);

	// Move Assignment Operator.
	inline CFixedArray2D<_T>& operator=(CFixedArray2D<_T>&& _rrtOther);



	// Get the width of this 2D array (the number of columns).
	inline int GetWidth() const;

	// Get the height of this 2D array (the number of rows).
	inline int GetHeight() const;

	// Get the total number of elements in this 2D array (rows * columns).
	using CFixedArray<_T>::GetSize;

	// Resize this array to hold a different number of elements.
	void Resize(const int _ikWidth, const int _ikHeight);

	// Removes all elements from this array.
	using CFixedArray<_T>::Clear;



	// Get element at position by value.
	inline _T GetElementAt(
		const int _ikColumn,
		const int _ikRow
	) const;

	// Set element at position to a different value.
	inline void SetElementAt(
		const int _ikColumn,
		const int _ikRow,
		_T _tValue
	);

	// Get element at position by reference.
	inline _T& GetElementRefAt(
		const int _ikColumn,
		const int _ikRow
	);

	// Get const element at position by reference.
	inline const _T& GetElementRefAt(
		const int _ikColumn,
		const int _ikRow
	) const;



	using CFixedArray<_T>::begin;
	using CFixedArray<_T>::end;



private:

	// Throws an exception if the row index is out of range.
	inline void AssertRowInRange(const int _ikRow) const;

	// Throws an exception if the column index is out of range.
	inline void AssertColumnInRange(const int _ikRow) const;



	// Member Variables
private:

	// Width of the 2D array.
	int m_iWidth;

	// Height of the 2D array.
	int m_iHeight;

};



// Include implementation for inline and template functions.
#include "FixedArray2D_imp.hpp"

#endif //~ __FIXED_ARRAY_2D_HPP__
