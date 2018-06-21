//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	FixedArray.hpp
//	Description	:	FixedArray class declaration file.
//					Dynamic memory for an array.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __FIXED_ARRAY_HPP__
#define __FIXED_ARRAY_HPP__

// Library Includes
#include <functional>		// function<>
#include <initializer_list>

// Declarations

// An array of elements of a single type.
template<class _T>
class CFixedArray
{
	// Methods
public:

	// Default Constructor.
	inline CFixedArray();

	// Copy Constructor.
	inline CFixedArray(const CFixedArray<_T>& _rtkOther);

	// Move Constructor.
	inline CFixedArray(CFixedArray<_T>&& _rrtOther);

	// Constructor with size of the array.
	inline CFixedArray(const int _ikSize);

	// Constructor with default element value.
	inline CFixedArray(const int _ikSize, const _T& _rtkDefaultValue);

	// Constructor with initializer list.
	inline CFixedArray(std::initializer_list<_T> _aList);

	// Destructor.
	inline ~CFixedArray();

	// Copy Assignment Operator.
	inline CFixedArray<_T>& operator=(const CFixedArray<_T>& _rtkOther);

	// Move Assignment Operator.
	inline CFixedArray<_T>& operator=(CFixedArray<_T>&& _rrtOther);



	// Get the size of this array (the number of elements).
	inline int GetSize() const;

	// Resize this array to hold a different number of elements.
	void Resize(const int _ikNewSize);

	// Removes all elements from this array.
	void Clear();



	// Get element at index by value.
	inline _T GetElementAt(const int _ikIndex) const;

	// Set element at index to a different value.
	inline void SetElementAt(const int _ikIndex, _T _tValue);

	// Get element at index by reference.
	inline _T& GetElementRefAt(const int _ikIndex);

	// Get const element at index by reference.
	inline const _T& GetElementRefAt(const int _ikIndex) const;



	// Adds an element by copy to the end of this list.
	void AddElement(const _T& _rtkValue);



	// Replicates the begin() method of a std library collection class.
	// Disobeying naming convention in order to work with std::begin template functions.
	inline _T* begin();

	// Replicates the begin() method of a std library collection class.
	// Disobeying naming convention in order to work with std::begin template functions.
	inline const _T* begin() const;

	// Replicates the end() method of a std library collection class.
	// Disobeying naming convention in order to work with std::end template functions.
	inline _T* end();

	// Replicates the end() method of a std library collection class.
	// Disobeying naming convention in order to work with std::end template functions.
	inline const _T* end() const;



protected:

	// Resize this array to hold a different number of elements.
	// The OldArrayCopier takes parameters:
	//		ptr to old array,
	//		ptr to new array
	// and modifies the elements of the new array.
	// If SkipIfSameSize is true, and the new size is identical
	// to the old size, no change will occur.
	void Resize(
		const int _ikNewSize,
		const std::function<void(_T* const, _T* const)> _fnkOldArrayCopier,
		const bool _bkSkipIfSameSize = true
	);



private:

	// Throws an exception if the index is out of range,
	// or the array is null.
	inline void AssertIndexInRange(const int _ikIndex) const;



	// Member Variables
private:

	// Size of the internal array.
	int m_iSize;

	// The internal array.
	// Pointer to an array on the free store.
	_T* m_paArray;

};



// Global Functions

// Alternative to std::copy.
template<class _T>
inline void CopyArray(const _T* _ptkBegin, const _T* const _kptkEnd, _T* _ptDest);



// Include implementation for inline and template functions.
#include "FixedArray_imp.hpp"

#endif //~ __FIXED_ARRAY_HPP__
