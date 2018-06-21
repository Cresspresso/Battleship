//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	DisplayBoard.hpp
//	Description	:	DisplayBoard class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __GAME_BOARD_HPP__
#define __GAME_BOARD_HPP__

// Local Includes
#include "FixedArray2D.hpp"
#include "Ship.hpp"
#include "Health.hpp"

// Declarations

// A single cell.
struct SGameBoardCell
{
	// A ship that is over this cell.
	CShip* m_ptShip = nullptr;

	// The health of this cell. (Whether or not it has been shot.)
	THealth m_iHealth = HEALTH_NORMAL;
};

// A grid of cells with several ships on them.
class CGameBoard
{
	// Methods
public:

	// Default Constructor.
	inline CGameBoard() = default;

	// Constructor with dimensions.
	inline CGameBoard(const int _ikWidth, const int _ikHeight);

	// Copy Constructor.
	inline CGameBoard(const CGameBoard& _rtkOther) = default;

	// Destructor.
	inline ~CGameBoard() = default;



	// Gets width of this board.
	inline int GetWidth() const;

	// Gets height of this board.
	inline int GetHeight() const;

	// Sets width and height of this board.
	inline void Resize(const int _ikWidth, const int _ikHeight);



	// Adds a ship to this board by copy.
	inline void AddShip(const CShip& _rtkShip);

	// Gets the number of ships on this board.
	inline int GetShipCount() const;

	// Gets a reference to a ship on this board.
	inline CShip& GetShipRefAt(const int _ikShipIndex);

	// Gets a const reference to a ship on this board.
	inline const CShip& GetShipRefAt(const int _ikShipIndex) const;

	// Gets a read-only reference to the the list of ships on this board.
	inline const CFixedArray<CShip>& GetShips() const;



	// Gets a reference to a cell in this board.
	inline SGameBoardCell& GetCellRefAt(const CVector2i& _rtkPosition);

	// Gets a const reference to a cell in this board.
	inline const SGameBoardCell& GetCellRefAt(const CVector2i& _rtkPosition) const;



	// Updates the cells of this board according to the states of the ships.
	void UpdateCells();

	// Clears the ships and resets the cells of this board.
	void Reset();



	// Returns true if the ship is overlapping any other ships on this board.
	bool IsShipOverlappingAny(const CShip& _rtkShip);

	// Returns true if two or more ships are overlapping each other.
	bool AreAnyShipsOverlapping();

	// Returns true if all ships on a board have zero health.
	bool AreAllShipsDestroyed();

	// Randomizes ship positions, ensuring none overlap.
	void RandomizePlacement();



	// Returns a new position vector for where the ship could be placed
	// so that it will be within the bounds of this board.
	// If the ship's bounds are larger than the size of this board,
	// it is clamped towards (0, 0).
	CVector2i ClampShipPosition(CVector2i _vPosition, const CShip& _rtkShip);

	// Ensures a position is within the bounds of this board.
	CVector2i ClampSinglePosition(CVector2i _vPosition);



	// Changes the health of a cell.
	void FireAt(const CVector2i& _rvkPosition);

	// Tries to fire at a cell.
	// If it was already hit, returns false. If firing succeeded, returns true.
	bool TryFireAt(const CVector2i& _rvkPosition);



private:

	// Resets the cells of this board.
	void ClearCells();

	// 'Prints' a ship to the board.
	void PlaceShip(CShip& _rtShip);



	// Member Variables
private:

	// List of ships on this board.
	CFixedArray<CShip> m_atShips;

	// 2D array of cells that form this board.
	CFixedArray2D<SGameBoardCell> m_atBoard;
};



// Include implementation for inline and template functions.
#include "GameBoard_imp.hpp"

#endif //~ __GAME_BOARD_HPP__
