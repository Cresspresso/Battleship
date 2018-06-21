//
//	Bachelor of Software Engineering
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2018	Media Design School
//
//	File Name	:	consolate_PanelStyle.cpp
//	Description	:	PanelStyle struct implementation file.
//	Project		:	Consolate
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <memory>	// move()

// This Include
#include "consolate_PanelStyle.hpp"

namespace consolate
{
#pragma region // Constant Instances

#ifdef UNICODE

	const SPanelStyle SPanelStyle::PANELSTYLE_SINGLE(L'─', L'─', L'│', L'│', L'┌', L'┐', L'└', L'┘', L'┬', L'┴', L'├', L'┤', L'┼');
	const SPanelStyle SPanelStyle::PANELSTYLE_DOUBLE(L'═', L'═', L'║', L'║', L'╔', L'╗', L'╚', L'╝', L'╦', L'╩', L'╠', L'╣', L'╬');

#else //! UNICODE

	const SPanelStyle SPanelStyle::PANELSTYLE_SINGLE(-60, -60, -77, -77, -38, -65, -64, -39, -62, -63, -61, -76, -59);
	const SPanelStyle SPanelStyle::PANELSTYLE_DOUBLE(-51, -51, -70, -70, -55, -69, -56, -68, -53, -54, -52, -71, -50);

#endif //~ UNICODE

#pragma endregion //~ Constant Instances

} //~ consolate
