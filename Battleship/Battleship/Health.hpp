//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	Health.hpp
//	Description	:	Health type declaration file.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __HEALTH_HPP__
#define __HEALTH_HPP__

// Types

// The health of one collider cell or board cell.
using THealth = int;



// Constants

constexpr THealth HEALTH_HIT = 0; // Indicates the cell has been shot at.
constexpr THealth HEALTH_NORMAL = 1; // Indicates the cell has not been shot at.

#endif //~ __HEALTH_HPP__
