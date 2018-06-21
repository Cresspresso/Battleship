//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_ColorTable_imp.hpp
//	Description	:	colortable namespace implementation file
//					for inline and template functions.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//
#pragma once
#ifndef __CONSOLATE_COLOR_TABLE_IMP_HPP__
#define __CONSOLATE_COLOR_TABLE_IMP_HPP__

// Header for this Implementation file.
#include "consolate_ColorTable.hpp"

// Implementation

namespace consolate
{
	namespace colortable
	{
		// Creates a ColorTable from a raw array.
		TColorTable CreateColorTable(const TRawColorTable& _rakSource)
		{
			TColorTable tTable;
			for (std::size_t i = 0; i < COLORTABLE_LENGTH; ++i)
			{
				tTable[i] = _rakSource[i];
			}
			return tTable;
		}

		// Copies a ColorTable's values to a raw array.
		void CopyColorTable(
			const TColorTable& _rtkSource,
			TRawColorTable& _raDest
		)
		{
			for (std::size_t i = 0; i < COLORTABLE_LENGTH; ++i)
			{
				_raDest[i] = _rtkSource[i];
			}
		}

		// Copies the color table values from one raw array to another.
		void CopyColorTable(
			const TRawColorTable& _rakSource,
			TRawColorTable& _raDest
		)
		{
			for (std::size_t i = 0; i < COLORTABLE_LENGTH; ++i)
			{
				_raDest[i] = _rakSource[i];
			}
		}

	} //~ colortable

} //~ consolate

#endif //~ __CONSOLATE_COLOR_TABLE_IMP_HPP__
