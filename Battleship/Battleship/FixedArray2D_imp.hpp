//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	FixedArray2D_imp.hpp
//	Description	:	FixedArray2D class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __FIXED_ARRAY_2D_IMP_HPP__
#define __FIXED_ARRAY_2D_IMP_HPP__

// Library Includes
#include <memory>
#include <stdexcept>	// exception, out_of_range

// This Include
#include "FixedArray2D.hpp"

// Implementation

#pragma region // Constructors and Destructor

// Default Constructor.
template<class _T>
inline CFixedArray2D<_T>::CFixedArray2D()
	:
	m_iWidth(0),
	m_iHeight(0),
	CFixedArray<_T>()
{
}

// Copy Constructor.
template<class _T>
inline CFixedArray2D<_T>::CFixedArray2D(const CFixedArray2D<_T>& _rtkOther)
	:
	m_iWidth(_rtkOther.m_iWidth),
	m_iHeight(_rtkOther.m_iHeight),
	CFixedArray<_T>(_rtkOther)
{
}

// Move Constructor.
template<class _T>
inline CFixedArray2D<_T>::CFixedArray2D(CFixedArray2D<_T>&& _rrtOther)
	:
	m_iWidth(_rrtOther.m_iWidth),
	m_iHeight(_rrtOther.m_iHeight),
	CFixedArray<_T>(std::forward(_rrtOther))
{
	// the array is now under this object's control, so
	// clear the other object.
	_rrtOther.m_iWidth = 0;
	_rrtOther.m_iHeight = 0;
}

// Constructor with width and height of the 2D array.
template<class _T>
inline CFixedArray2D<_T>::CFixedArray2D(
	const int _ikWidth,
	const int _ikHeight
) :
	m_iWidth(_ikWidth),
	m_iHeight(_ikHeight),
	CFixedArray<_T>(_ikWidth * _ikHeight)
{
}

// Constructor with default element value.
template<class _T>
inline CFixedArray2D<_T>::CFixedArray2D(
	const int _ikWidth,
	const int _ikHeight,
	const _T& _rtkDefaultValue
) :
	m_iWidth(_ikWidth),
	m_iHeight(_ikHeight),
	CFixedArray<_T>(_ikWidth * _ikHeight, _rtkDefaultValue)
{
}

// Constructor with nested initializer lists.
template<class _T>
CFixedArray2D<_T>::CFixedArray2D(std::initializer_list<std::initializer_list<_T>> _aaList)
	:
	m_iWidth(_aaList.size()),
	m_iHeight(m_iWidth > 0 ? _aaList[0].size() : 0),
	CFixedArray<_T>(m_iWidth * m_iHeight)
{
	using std::begin;
	using std::end;

	// Validate list lengths.
	// If not all of them are the same size, throw an error.
	if (std::any_of(begin(_aaList), end(_aaList), [](const std::initializer_list<_T>>& _rakList) {
		_rakList.size() != m_iWidth
	}))
	{
		throw exception("Nested initializer lists must have the same size.");
	}

	// Copy input across to internal array.
	for (int iRow = 0; iRow < m_iHeight; ++iRow)
	{
		for (int iColumn = 0; iColumn < m_iWidth; ++iColumn)
		{
			SetElementAt(iRow, iColumn, _aaList[iRow][iColumn]);
		}
	}
}

// Copy Assignment Operator.
template<class _T>
inline CFixedArray2D<_T>& CFixedArray2D<_T>::operator=(const CFixedArray2D<_T>& _rtkOther)
{
	m_iWidth = _rtkOther.m_iWidth;
	m_iHeight = _rtkOther.m_iHeight;
	CFixedArray<_T>::operator=(std::forward<CFixedArray2D<_T>>(_rtkOther));

	return *this;
}

// Move Assignment Operator.
template<class _T>
inline CFixedArray2D<_T>& CFixedArray2D<_T>::operator=(CFixedArray2D<_T>&& _rrtOther)
{
	m_iWidth = _rtkOther.m_iWidth;
	m_iHeight = _rtkOther.m_iHeight;
	CFixedArray<_T>::operator=(std::forward<CFixedArray2D<_T>>(_rrtOther));

	// the array is now under this object's control, so
	// clear the other object.
	_rrtOther.m_iWidth = 0;
	_rrtOther.m_iHeight = 0;

	return *this;
}

#pragma endregion //~ Constructors and Destructor

#pragma region // Size

// Get the width of this 2D array (the number of columns).
template<class _T>
inline int CFixedArray2D<_T>::GetWidth() const
{
	return m_iWidth;
}

// Get the height of this 2D array (the number of rows).
template<class _T>
inline int CFixedArray2D<_T>::GetHeight() const
{
	return m_iHeight;
}

// Resize this array to hold a different number of elements.
template<class _T>
void CFixedArray2D<_T>::Resize(
	const int _ikWidth,
	const int _ikHeight
)
{
	if (_ikWidth < 0 || _ikHeight < 0)
	{
		throw std::exception("Array size must be >= 0.");
	}
	else if (_ikWidth == 0 || _ikHeight == 0)
	{
		m_iWidth = 0;
		m_iHeight = 0;
		Clear();
	}
	else if (_ikWidth == m_iWidth && _ikHeight == m_iHeight)
	{
		return;
	}
	else // _ikWidth > 0 && _ikHeight > 0
	{
		const int ikEndWidth = _ikWidth < m_iWidth ? _ikWidth : m_iWidth;
		const int ikEndHeight = _ikHeight < m_iHeight ? _ikHeight : m_iHeight;
		const int ikOldWidth = m_iWidth;

		// Call Resize with a function to copy old values across.
		// Old 2D array is copied to top-left corner,
		// i.e. index (0,0) stays at index (0,0).
		CFixedArray<_T>::Resize(_ikWidth * _ikHeight,
			[_ikWidth, ikOldWidth, ikEndWidth, ikEndHeight](
				_T* const _kpaOldArray,
				_T* const _kpaNewArray
			)
			{
				// For each row that exists in both arrays,
				for (int iRow = 0; iRow < ikEndHeight; ++iRow)
				{
					// For each column that exists in both arrays,
					for (int iColumn = 0; iColumn < ikEndWidth; ++iColumn)
					{
						// Copy element from old array to new array.
						_kpaNewArray[iRow * _ikWidth + iColumn] = _kpaOldArray[iRow * ikOldWidth + iColumn];
					}
				}
			},
			false // force copy, in case width/height have just been flipped.
		);

		m_iWidth = _ikWidth;
		m_iHeight = _ikHeight;
	}
}

#pragma endregion //~ Size

#pragma region // Elements

// Get element at position by value.
template<class _T>
inline _T CFixedArray2D<_T>::GetElementAt(
	const int _ikColumn,
	const int _ikRow
) const
{
	AssertRowInRange(_ikRow);
	AssertColumnInRange(_ikColumn);
	return CFixedArray<_T>::GetElementAt(_ikRow * m_iWidth + _ikColumn);
}

// Set element at position to a different value.
template<class _T>
inline void CFixedArray2D<_T>::SetElementAt(
	const int _ikColumn,
	const int _ikRow,
	_T _tValue
)
{
	AssertRowInRange(_ikRow);
	AssertColumnInRange(_ikColumn);
	CFixedArray<_T>::SetElementAt(_ikRow * m_iWidth + _ikColumn, _tValue);
}

// Get element at position by reference.
template<class _T>
inline _T& CFixedArray2D<_T>::GetElementRefAt(
	const int _ikColumn,
	const int _ikRow
)
{
	AssertRowInRange(_ikRow);
	AssertColumnInRange(_ikColumn);
	return CFixedArray<_T>::GetElementRefAt(_ikRow * m_iWidth + _ikColumn);
}

// Get const element at position by reference.
template<class _T>
inline const _T& CFixedArray2D<_T>::GetElementRefAt(
	const int _ikColumn,
	const int _ikRow
) const
{
	AssertRowInRange(_ikRow);
	AssertColumnInRange(_ikColumn);
	return CFixedArray<_T>::GetElementRefAt(_ikRow * m_iWidth + _ikColumn);
}

#pragma endregion //~ Elements

// Throws an exception if the row index is out of range.
template<class _T>
inline void CFixedArray2D<_T>::AssertRowInRange(const int _ikRow) const
{
	if (_ikRow < 0 || _ikRow >= m_iHeight)
	{
		throw std::out_of_range("Row index out of range.");
	}
}

// Throws an exception if the column index is out of range.
template<class _T>
inline void CFixedArray2D<_T>::AssertColumnInRange(const int _ikColumn) const
{
	if (_ikColumn < 0 || _ikColumn >= m_iWidth)
	{
		throw std::out_of_range("Column index out of range.");
	}
}

#endif //~ __FIXED_ARRAY_2D_IMP_HPP__
