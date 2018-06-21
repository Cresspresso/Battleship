//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	FixedArray_imp.hpp
//	Description	:	FixedArray class implementation file
//					for inline and template functions.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __FIXED_ARRAY_IMP_HPP__
#define __FIXED_ARRAY_IMP_HPP__

// Library Includes
#include <stdexcept>	// exception, out_of_range
#include <algorithm>	// copy(), generate()

// This Include
#include "FixedArray.hpp"

// Implementation

#pragma region // Constructors and Destructor

// Default Constructor.
template<class _T>
inline CFixedArray<_T>::CFixedArray()
	:
	m_iSize(0),
	m_paArray(nullptr)
{
}

// Copy Constructor.
template<class _T>
inline CFixedArray<_T>::CFixedArray(const CFixedArray<_T>& _rtkOther)
	:
	m_iSize(_rtkOther.m_iSize),
	// If size is not zero, allocate space on the free store.
	m_paArray(m_iSize > 0 ? new _T[m_iSize] : nullptr)
{
	using std::begin;
	using std::end;
	// Copy elements from other array to this new one.
	CopyArray(begin(_rtkOther), end(_rtkOther), this->begin());
}

// Move Constructor.
template<class _T>
inline CFixedArray<_T>::CFixedArray(CFixedArray<_T>&& _rrtOther)
	:
	m_iSize(_rrtOther.m_iSize),
	m_paArray(_rrtOther.m_paArray)
{
	// the array is now under this object's control, so
	// do not let the other object modify it further.
	_rrtOther.m_iSize = 0;
	_rrtOther.m_paArray = nullptr;
}

// Constructor with size of the array.
template<class _T>
inline CFixedArray<_T>::CFixedArray(const int _ikSize)
	:
	m_iSize(_ikSize > 0 ? _ikSize : 0),
	m_paArray(m_iSize > 0 ? new _T[m_iSize] : nullptr)
{
}

// Constructor with default element value.
template<class _T>
inline CFixedArray<_T>::CFixedArray(const int _ikSize, const _T& _rtkDefaultValue)
	:
	m_iSize(_ikSize > 0 ? _ikSize : 0),
	m_paArray(m_iSize > 0 ? new _T[m_iSize] : nullptr)
{
	using std::begin;
	using std::end;
	// Set elements of new array to the default value.
	std::generate(this->begin(), this->end(), [&]() { return _rtkDefaultValue; });
}

// Constructor with initializer list.
template<class _T>
inline CFixedArray<_T>::CFixedArray(std::initializer_list<_T> _aList)
	:
	m_iSize(static_cast<int>(_aList.size())),
	m_paArray(m_iSize > 0 ? new _T[m_iSize] : nullptr)
{
	using std::begin;
	using std::end;
	// Set elements of new array to the default value.
	CopyArray(begin(_aList), end(_aList), this->begin());
}



// Destructor.
template<class _T>
inline CFixedArray<_T>::~CFixedArray()
{
	Clear();
}



// Copy Assignment Operator.
template<class _T>
inline CFixedArray<_T>& CFixedArray<_T>::operator=(const CFixedArray<_T>& _rtkOther)
{
	if (&_rtkOther == this)
		return *this;

	Clear();

	m_iSize = _rtkOther.m_iSize;
	m_paArray = m_iSize > 0 ? new _T[m_iSize] : nullptr;

	using std::begin;
	using std::end;
	// Copy elements from other array to this new one.
	CopyArray(begin(_rtkOther), end(_rtkOther), this->begin());

	return *this;
}

// Move Assignment Operator.
template<class _T>
inline CFixedArray<_T>& CFixedArray<_T>::operator=(CFixedArray<_T>&& _rrtOther)
{
	if (&_rrtOther == this)
		return *this;

	Clear();

	m_iSize = _rrtOther.m_iSize;
	m_paArray = _rrtOther.m_paArray;

	// the array is now under this object's control, so
	// do not let the other object modify it further.
	_rrtOther.m_iSize = 0;
	_rrtOther.m_paArray = nullptr;

	return *this;
}

#pragma endregion //~ Constructors and Destructor

#pragma region // Size

// Get the size of this array (the number of elements).
template<class _T>
inline int CFixedArray<_T>::GetSize() const
{
	return m_iSize;
}

// Resize this array to hold a different number of elements.
template<class _T>
void CFixedArray<_T>::Resize(const int _ikNewSize)
{
	// iEnd = minimum of old size and new size.
	const int ikEnd = _ikNewSize < m_iSize ? _ikNewSize : m_iSize;

	// Call Resize with a function to copy old values across.
	Resize(_ikNewSize,
		[ikEnd](
			_T* const _kpaOldArray,
			_T* const _kpaNewArray
		)
		{
			// Copy elements from old array to new array.
			for (int i = 0; i < ikEnd; ++i)
			{
				_kpaNewArray[i] = _kpaOldArray[i];
			}
		}
	);
}

// Removes all elements from this array.
template<class _T>
void CFixedArray<_T>::Clear()
{
	m_iSize = 0;

	// Delete old array.
	if (m_paArray != nullptr)
	{
		delete[] m_paArray;
		m_paArray = nullptr;
	}
}

#pragma endregion //~ Size

#pragma region // Elements

// Get element at index by value.
template<class _T>
inline _T CFixedArray<_T>::GetElementAt(const int _ikIndex) const
{
	AssertIndexInRange(_ikIndex);
	return m_paArray[_ikIndex];
}

// Set element at index to a different value.
template<class _T>
inline void CFixedArray<_T>::SetElementAt(const int _ikIndex, _T _tValue)
{
	AssertIndexInRange(_ikIndex);
	m_paArray[_ikIndex] = _tValue;
}

// Get element at index by reference.
template<class _T>
inline _T& CFixedArray<_T>::GetElementRefAt(const int _ikIndex)
{
	AssertIndexInRange(_ikIndex);
	return m_paArray[_ikIndex];
}

// Get const element at index by reference.
template<class _T>
inline const _T& CFixedArray<_T>::GetElementRefAt(const int _ikIndex) const
{
	AssertIndexInRange(_ikIndex);
	return m_paArray[_ikIndex];
}



// Adds an element by copy to the end of this list.
template<class _T>
inline void CFixedArray<_T>::AddElement(const _T& _rtkValue)
{
	int i = GetSize();
	Resize(i + 1);
	SetElementAt(i, _rtkValue);
}



#pragma endregion //~ Elements

// Resize this array to hold a different number of elements.
// The OldArrayCopier takes parameters:
//		ptr to old array,
//		ptr to new array
// and modifies the elements of the new array.
// If SkipIfSameSize is true, and the new size is identical
// to the old size, no change will occur.
template<class _T>
inline void CFixedArray<_T>::Resize(
	const int _ikNewSize,
	const std::function<void(_T* const, _T* const)> _fnkOldArrayCopier,
	const bool _bkSkipIfSameSize
)
{
	// TF: Dynamic Memory
	// This function will resize this class's `m_paArray` array member variable.

	if (_ikNewSize < 0)
	{
		throw std::exception("Array size must be >= 0.");
	}
	else if (_ikNewSize == m_iSize && _bkSkipIfSameSize)
	{
		return;
	}
	else if (_ikNewSize == 0)
	{
		Clear();
	}
	else // _ikNewSize > 0
	{
		// If old array was nonexistent
		if (m_paArray == nullptr)
		{
			// Just allocate new memory.
			m_paArray = new _T[_ikNewSize];
			if (m_paArray == nullptr)
				throw std::exception("Memory allocation failed!");

			m_iSize = _ikNewSize;
		}
		else
		{
			// Allocate memory for new array.
			// TF: Array
			_T* paNewArray = nullptr;
			paNewArray = new _T[_ikNewSize];
			if (m_paArray == nullptr)
				throw std::exception("Memory allocation failed!");

			// Call copy function.
			if (_fnkOldArrayCopier != nullptr)
			{
				_fnkOldArrayCopier(m_paArray, paNewArray);
			}

			// Free memory from old array.
			delete[] m_paArray;
			m_paArray = nullptr; // not needed, as line below overwrites it anyway.

			// Keep pointer to new array.
			m_paArray = paNewArray;

			m_iSize = _ikNewSize;
		}
	}
}



// Replicates the begin() method of a std library collection class.
// Disobeying naming convention in order to work with std::begin template functions.
template<class _T>
inline _T* CFixedArray<_T>::begin()
{
	return m_paArray;
}

// Replicates the begin() method of a std library collection class.
// Disobeying naming convention in order to work with std::begin template functions.
template<class _T>
inline const _T* CFixedArray<_T>::begin() const
{
	return m_paArray;
}

// Replicates the end() method of a std library collection class.
// Disobeying naming convention in order to work with std::end template functions.
template<class _T>
inline _T* CFixedArray<_T>::end()
{
	return m_paArray + m_iSize;
}

// Replicates the end() method of a std library collection class.
// Disobeying naming convention in order to work with std::end template functions.
template<class _T>
inline const _T* CFixedArray<_T>::end() const
{
	return m_paArray + m_iSize;
}



// Throws an exception if the index is out of range,
// or the array is null.
template<class _T>
inline void CFixedArray<_T>::AssertIndexInRange(const int _ikIndex) const
{
	// TF: Logical Operator
	if (_ikIndex < 0 || _ikIndex >= m_iSize)
	{
		throw std::out_of_range("Index out of range.");
	}
	if (m_paArray == nullptr && m_iSize > 0)
	{
		throw std::exception("Size indicates internal array should exist, but it is null!");
	}
}



#pragma region // Global Functions

// Alternative to std::copy.
template<class _T>
inline void CopyArray(const _T* _ptkBegin, const _T* const _kptkEnd, _T* _ptDest)
{
	while (_ptkBegin != _kptkEnd)
	{
		*(_ptDest++) = *(_ptkBegin++);
	}
}

#pragma endregion //~ Global Functions

#endif //~ __FIXED_ARRAY_IMP_HPP__
