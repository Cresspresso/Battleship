//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Ship.hpp
//	Description	:	Ship class declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __SHIP_HPP__
#define __SHIP_HPP__

// Library Includes
#include <initializer_list>
#include <string>

// Local Includes
#include "FixedArray.hpp"
#include "Collider.hpp"

// Declarations

// A ship for the game Battleships.
// TF: Class
class CShip
{
	// Methods
	// TF: Access Specifier
public:

	// Full Constructor.
	inline CShip(
		const CFixedArray<CCollider>& _rakColliders = { CCollider{ {0, 0} } },
		// TF: Default Parameter
		const int _ikActiveColliderIndex = 0,
		const std::wstring& _rstrkName = TEXT("Ship"),
		const std::wstring& _rstrkSymbol = TEXT("X"),
		const CVector2i _vkPosition = { 0, 0 }
	);

	// Copy Constructor.
	inline CShip(const CShip& _rtkOther);

	// Destructor.
	inline ~CShip() = default;



	// Gets the name of this ship.
	inline const std::wstring& GetName() const;

	// Sets the name of this ship.
	inline void SetName(const std::wstring& _rstrkName);



	// Gets the symbol of this ship.
	inline const std::wstring& GetSymbol() const;

	// Sets the symbol of this ship.
	inline void SetSymbol(const std::wstring& _rstrkSymbol);



	// Gets the number of colliders in this ship.
	inline int GetColliderCount() const;



	// Gets the index of this ship's active collider.
	inline int GetActiveColliderIndex() const;

	// Sets the active collider of this ship via its index.
	inline void SetActiveColliderIndex(int _iActiveColliderIndex);

	// Increments the active collider index by Step,
	// wrapping around to stay inside the valid index range.
	void CycleActiveColliderIndex(const int _ikStep = 1);



	// Gets the active collider of this ship.
	inline const CCollider& GetActiveColliderRef() const;



	// Gets position of this ship in board space.
	inline CVector2i GetPosition() const;

	// Sets position of this ship in board space.
	inline void SetPosition(CVector2i _vPosition);



	// Returns true if this ship's collider overlaps the
	// other ship's collider in board space.
	inline bool IsOverlapping(const CShip& _rtkOther) const;



	// Gets the number of cells that have not yet been hit.
	inline int GetHealth() const;

	// Tells this ship how many cells have not yet been hit.
	inline void SetHealth(int _iHealth);

	// Resets the health of this ship based on the current collider.
	inline void ResetHealth();



	// Member Variables
private:

	// Name of this ship.
	std::wstring m_strName;

	// Symbol of this ship, for displaying on a board.
	std::wstring m_strSymbol;

	// All possible colliders of this ship type.
	CFixedArray<CCollider> m_aColliders;

	// Index of the active collider in the Colliders array.
	int m_iActiveColliderIndex;
	
	// Position of this ship in board space.
	CVector2i m_vPosition;

	// Number of cells that have not yet been hit.
	int m_iHealth;
};



// Include implementation for inline and template functions.
#include "Ship_imp.hpp"

#endif //~ __SHIP_HPP__
