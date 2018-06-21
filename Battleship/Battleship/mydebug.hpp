//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	mydebug.hpp
//	Description	:	A header file for quick debugging tools.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __MYDEBUG_HPP__
#define __MYDEBUG_HPP__

#ifdef _DEBUG

// Library Includes
#include <iostream>
#include <string>
#include <sstream>

// Declarations

// Alias for std namespace.
// Easy to remember and search for in files when cleaning up debugging code.
namespace deb
{
	using namespace std;
}

// Macros

//#ifdef UNICODE
//
//#define dout deb::wcout
//
//#else //! UNICODE
//
//#define dout deb::cout
//
//#endif //~ UNICODE
//
//
//#define dendl deb::endl


#endif //~ _DEBUG

#endif //~ __MYDEBUG_HPP__
