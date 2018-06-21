//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	main.cpp
//	Description	:	Main implementation file.
//					Manual tests for Battleship project.
//	Project		:	BattleshipTests
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <iostream>
#include <conio.h>
#include <stdexcept>
#include <string>

// Solution Library Includes
#include <consolate.hpp>
#include <FixedArray.hpp>
#include <FixedArray2D.hpp>
#include <generalmath.hpp>
#include <Input.hpp>

// Usings
using namespace std;
using namespace consolate;

// Macros

#define ASSERT(_X) {\
	if (!static_cast<bool>(_X))\
		throw std::exception(("Assert Failed: Expression is false. :" + std::to_string(__LINE__)).c_str());\
}

#define ASSERT_FAILS(_X) {\
	try {\
		(_X);\
		throw std::exception(("Assert Failed: Expression did not throw. :" + std::to_string(__LINE__)).c_str());\
	} catch (...) {}\
}

// Implementation

#pragma region // Input

// Echoes all raw keycodes from the keyboard.
void TestBasicInput()
{
	using namespace std;
	while (true)
	{
		int iKey = _getch();
		wcout << iKey << endl;
	}
}

// Echoes the keycode of a key when it is pressed.
/*void TestInput()
{
	using namespace keycodes;

	bool bRunning = true;

	CInput tInput;

	tInput.m_fnOnKeyPressed = [&bRunning](const TKeyCode _ekKey)
	{
		std::wcout << TEXT("Key ") << _ekKey << std::endl;

		bRunning = _ekKey != KEYCODE_ESCAPE;
	};
	tInput.m_fnOnKeyExPressed = [](const TKeyCodeEx _ekKeyEx)
	{
		std::wcout << TEXT("Ex  ") << _ekKeyEx << std::endl;
	};
	tInput.m_fnOnKeyEx2Pressed = [](const TKeyCodeEx2 _ekKeyEx2)
	{
		std::wcout << TEXT("Ex2 ") << _ekKeyEx2 << std::endl;
	};

	do
	{
		tInput.WaitForKeyPress();
	} while (bRunning);
}*/

#pragma endregion //~ Input

#pragma region // generalmath

void TestGeneralMath()
{
	g_tConsolate.ClearScreen();
	wcout << "Testing generalmath..." << endl << endl;


	int i;
	i = Cycle(3, 4); ASSERT(i == 3);
	i = Cycle(4, 4); ASSERT(i == 0);
	i = Cycle(0, 4); ASSERT(i == 0);
	i = Cycle(5, 4); ASSERT(i == 1);

	double d;
	d = Cycle(3.0, 1.0, 4.0); ASSERT(d == 3.0);
	d = Cycle(0.0, 1.0, 4.0); ASSERT(d == 3.0);
	d = Cycle(3.0, -2.0, 2.0); ASSERT(d == -1.0);
	d = Cycle(0.0, -5.0, 0.0); ASSERT(d == -5.0);
	d = Cycle(0.0, -2.0); ASSERT(d == 0.0);
	d = Cycle(-3.0, -2.0, 0.0); ASSERT(d == -1.0);

	long l;
	l = CycleIn(8, 7, 10); ASSERT(l == 8);
	l = CycleIn(6, 7, 10); ASSERT(l == 10);


	wcout << endl;
}

#pragma endregion //~ generalmath

#pragma region // FixedArray

void PrintArray(const CFixedArray<int>& _rakArray)
{
	const int ikSize = _rakArray.GetSize();
	if (ikSize > 0)
	{
		wcout << "[ ";
		wcout << _rakArray.GetElementAt(0);
		for (int i = 1; i < ikSize; ++i)
		{
			wcout << ", " << _rakArray.GetElementAt(i);
		}
		wcout << " ]";
	}
	else
	{
		wcout << "[]";
	}
}

void PrintNestedArray(const CFixedArray<CFixedArray<int>>& _rakArray)
{
	const int ikSize = _rakArray.GetSize();
	if (ikSize > 0)
	{
		wcout << "[\n";
		PrintArray(_rakArray.GetElementRefAt(0));
		for (int i = 1; i < ikSize; ++i)
		{
			wcout << ",\n";
			PrintArray(_rakArray.GetElementRefAt(i));
		}
		wcout << "\n]";
	}
	else
	{
		wcout << "[]";
	}
}

void TestFixedArray()
{
	g_tConsolate.ClearScreen();
	wcout << "Testing CFixedArray<_T>..." << endl << endl;

	// Default Constructor.
	CFixedArray<int> a0;
	wcout << "a0 = ";
	PrintArray(a0);
	wcout << endl;

	// Constructor(int).
	CFixedArray<int> a1(5);
	wcout << "a1 = ";
	PrintArray(a1);
	wcout << endl;

	// Constructor(int, _T).
	CFixedArray<int> a2(5, 0);
	wcout << "a2 = ";
	PrintArray(a2);
	wcout << endl;

	// SetElementAt().
	a2.SetElementAt(3, -54);
	wcout << "a2 = ";
	PrintArray(a2);
	wcout << endl;

	// Copy Constructor.
	CFixedArray<int> a3(a2);
	wcout << "a3 = ";
	PrintArray(a3);
	wcout << endl;

	// Resize().
	a0.Resize(12);
	wcout << "a0 = ";
	PrintArray(a0);
	wcout << endl;

	// Constructor(initializer_list).
	CFixedArray<int> a4{ 3, 4, 5 };
	wcout << "a4:" << endl;
	PrintArray(a4);
	wcout << endl;

	// Nested arrays.
	CFixedArray<CFixedArray<int>> nestedArray{
		CFixedArray<int>(10, 0),
		{ 5, 8, 2 },
	};
	wcout << "nestedArray:" << endl;
	PrintNestedArray(nestedArray);
	wcout << endl;

	wcout << endl;
}

#pragma endregion //~ FixedArray

#pragma region // FixedArray2D

void PrintArray2D(const CFixedArray2D<int>& _rtkArray)
{
	const int ikWidth = _rtkArray.GetWidth();
	const int ikHeight = _rtkArray.GetHeight();
	for (int iRow = 0; iRow < ikHeight; ++iRow)
	{
		for (int iColumn = 0; iColumn < ikWidth; ++iColumn)
		{
			wcout << _rtkArray.GetElementAt(iColumn, iRow) << " ";
		}
		wcout << endl;
	}
}

void TestFixedArray2D()
{
	g_tConsolate.ClearScreen();
	wcout << "Testing CFixedArray2D<_T>..." << endl << endl;

	CFixedArray2D<int> t0;
	wcout << "t0:" << endl;
	PrintArray2D(t0);
	wcout << endl;

	CFixedArray2D<int> t1(3, 5);
	wcout << "t1:" << endl;
	PrintArray2D(t1);
	wcout << endl;

	CFixedArray2D<int> t2(3, 5, 0);
	wcout << "t2:" << endl;
	PrintArray2D(t2);
	wcout << endl;

	wcout << "[2,4] = 3" << endl;
	t2.SetElementAt(2, 4, 3);
	wcout << "[0,0] = 9" << endl;
	t2.SetElementAt(0, 0, 9);
	wcout << "[1,1] = 2" << endl;
	t2.SetElementAt(1, 1, 2);
	wcout << "t2:" << endl;
	PrintArray2D(t2);
	wcout << endl;

	CFixedArray2D<int> t3(t2);
	wcout << "t3:" << endl;
	PrintArray2D(t3);
	wcout << endl;

	wcout << "t0:" << endl;
	t0.Resize(5, 3);
	wcout << "[4,2] = 9" << endl;
	t0.SetElementAt(4, 2, 9);
	wcout << "[1,0] = 3" << endl;
	t0.SetElementAt(1, 0, 3);

	wcout << "t0:" << endl;
	PrintArray2D(t0);
	wcout << endl;

	t0.Resize(3, 5);
	wcout << "t0:" << endl;
	PrintArray2D(t0);
	wcout << endl;

	wcout << endl;
}

#pragma endregion //~ FixedArray2D

int main()
{
	wcout << "Manual Tests for Battleship project." << endl;
	_getch();



#ifdef _DEBUG
	try
#endif //~ _DEBUG

	{
		TestGeneralMath();
		_getch();

		TestFixedArray();
		_getch();

		TestFixedArray2D();
		_getch();
	}

#ifdef _DEBUG
	catch (const std::exception& e)
	{
		wcout << "Exception: " << e.what() << endl;
		throw;
	}
	catch (const char* const kpckMessage)
	{
		wcout << "CString Exception: " << kpckMessage << endl;
		throw;
	}
	catch (...)
	{
		wcout << "Unknown Exception." << endl;
		throw;
	}
#endif //~ _DEBUG



	g_tConsolate.Reset();
	wcout << "Tests have finished." << endl;
	_getch();
	return 0;
}
