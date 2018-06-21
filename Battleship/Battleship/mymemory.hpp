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
#ifndef __MYMEMORY_HPP__
#define __MYMEMORY_HPP__

// Library Includes
#include <exception>

// Declarations

// Allocates new memory on the free store.
// Throws an exception if memory allocation failed.
// _VariableName is the identifier of the pointer variable.
// _Type is the type of the object being created.
// __VA_ARGS__ are the arguments passed to the constructor of the new object.
// Example:
//		int* pInt;
//		ALLOCATE_NEW_MEMORY(pInt, int, 3)
// is trying to achieve
//		int* pInt;
//		pInt = new int(3);
//
#define ALLOCATE_NEW_MEMORY(_VariableName, _Type, ...)\
{\
	_VariableName = nullptr;\
	_VariableName = reinterpret_cast<_Type*>(new _Type(__VA_ARGS__));\
	if (_VariableName == nullptr)\
		throw std::exception("Memory allocation failed.");\
}

// Allocates new array memory on the free store.
// Throws an exception if memory allocation failed.
// _VariableName is the identifier of the pointer variable.
// _Type is the type of the elements of the array.
// _Size is the size of the array.
// __VA_ARGS__ are the elements of the newly created array.
// Example:
//		int* pInt;
//		ALLOCATE_NEW_ARRAY_MEMORY(pInt, int, 2, 3, 4)
// is trying to achieve
//		int* pInt;
//		pInt = new int[2]{3,4};
//
#define ALLOCATE_NEW_ARRAY_MEMORY(_VariableName, _Type, _Size, ...)\
{\
	_VariableName = nullptr;\
	_VariableName = reinterpret_cast<_Type*>(new _Type[_Size]{__VA_ARGS__});\
	if (_VariableName == nullptr)\
		throw std::exception("Memory allocation failed.");\
}



#endif //~ __MYMEMORY_HPP__
