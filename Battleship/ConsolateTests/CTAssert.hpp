//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	CTAssert.hpp
//	Description	:	Declaration file for Assert related macros.
//	Project		:	ConsolateTests
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CTASSERT__
#define __CTASSERT__

// Library Includes
#include <cassert>

// Asserts that an expression evaluates to true.
// Throws an exception if it is false.
#define ASSERT(expression) assert(expression)

// Asserts that an expression throws an exception during evaluation.
// Throws an exception if it does not.
#define ASSERT_FAILS(expression) {\
	bool b = false;\
	try { expression; } catch(...) {\
		b = true;\
	}\
	ASSERT(b);\
}

#endif //~ __CTASSERT__
