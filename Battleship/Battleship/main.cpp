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
//					Game of Battleships.
//	Project		:	Battleship
//	Author		:	Elijah Shadbolt
//	Mail		:	elijah.sha7979@mediadesign.school.nz
//				-	elijah.shadbolt@mediadesignschool.com
//				-	cresspresso@gmail.com
//

// Library Includes
#include <conio.h>
#include <iostream>
#include <random>
#include <algorithm>	// all_of()

// Solution Library Includes
#include <consolate.hpp>

// Local Includes
#include "mymemory.hpp"
#include "generalmath.hpp"
#include "FixedArray2D.hpp"
#include "Input.hpp"
#include "ui_View.hpp"
#include "ui_Button.hpp"
#include "ui_Toggle.hpp"
#include "Ship.hpp"
#include "GameBoard.hpp"
#include "PlacementBoard.hpp"
#include "GameplayBoard.hpp"

#pragma region // Global Constants

constexpr int WINDOW_WIDTH = 900;
constexpr int WINDOW_HEIGHT = 540;

constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 10;

#pragma region // UI Constants

// Colors

const consolate::TColor g_ulkBackgroundColor	= consolate::colors::COLOR_DEFAULT;
const consolate::TColor g_ulkUnfocusedColor		= consolate::colors::COLOR_DARK_GRAY;
const consolate::TColor g_ulkFocusedColor		= consolate::colors::COLOR_YELLOW;
const consolate::TColor g_ulkDecorationColor	= consolate::colors::COLOR_GRAY;
const consolate::TColor g_ulkExitColor			= consolate::colors::COLOR_RED;

// Panel Styles
// Initialized at start of program.

consolate::SPanelStyle g_tkTextStyle;	
consolate::SPanelStyle g_tkButtonStyle;

// Sizes and Positions

// Buttons
const CVector2i g_vkButtonSize = { 30, 3 };
const int g_ikButtonYInc = g_vkButtonSize.m_tY + 1;
CVector2i g_vkButtonPosStart = { 8, 5 };

// Title
// TF: Constant
const int g_ikTitleSizeMargin = 2;
const CVector2i g_vkTitlePos = { g_vkButtonPosStart.m_tX + g_ikTitleSizeMargin, 1 };
const CVector2i g_vkTitleSize = g_vkButtonSize - CVector2i{ 2 * g_ikTitleSizeMargin, 0 };

// Info Text
const int g_ikInfoTextMarginX = 3;
const CVector2i g_vkInfoTextPos = { g_vkButtonPosStart.m_tX - g_ikInfoTextMarginX, g_vkButtonPosStart.m_tY + 4 * g_ikButtonYInc };
const CVector2i g_vkInfoTextSize = { g_vkButtonSize.m_tX + 2 * g_ikInfoTextMarginX, 9 };

// Placement Board
const CVector2i g_vkPlacementBoardPos = { g_vkButtonPosStart.m_tX + g_vkButtonSize.m_tX + 7, g_vkButtonPosStart.m_tY };

// Gameplay Boards
const CVector2i g_vkGameplayBoardPos_PlayerEnemy = { g_vkPlacementBoardPos.m_tX, 2 };
const CVector2i g_vkGameplayBoardPos_PlayerSelf = { g_vkGameplayBoardPos_PlayerEnemy.m_tX, 16 };
const CVector2i g_vkGameplayBoardPos_ComputerEnemy = { g_vkGameplayBoardPos_PlayerSelf.m_tX + 26, g_vkGameplayBoardPos_PlayerEnemy.m_tY };
const CVector2i g_vkGameplayBoardPos_ComputerSelf = { g_vkGameplayBoardPos_ComputerEnemy.m_tX, g_vkGameplayBoardPos_PlayerSelf.m_tY };

#pragma endregion //~ UI Constants

#pragma endregion //~ Global Constants

#pragma region // Global Variables

// UI Views
ui::CView g_tMainMenuView;
ui::CView g_tPlacementView;
ui::CView g_tGameplayView;
ui::CView g_tOutcomeView;



// Whether the game is in in debug mode.
// TF: Variable Type
bool g_bIsDebugMode;

// List of references to elements to set visiblity depending on IsDebugMode.
CFixedArray<ui::CElement*> g_aptDebugModeElements;



// The human player's board.
CGameBoard g_tPlayerBoard(BOARD_WIDTH, BOARD_HEIGHT);

// The computer player's board.
CGameBoard g_tComputerBoard(BOARD_WIDTH, BOARD_HEIGHT);

#pragma endregion //~ Global Variables



// Implementation

// Gets whether the game is in debug mode.
inline bool GetIsDebugMode()
{
	return g_bIsDebugMode;
}

// Sets whether the game is in debug mode.
inline void SetIsDebugMode(bool _bIsDebugMode)
{
	g_bIsDebugMode = _bIsDebugMode;

	// Update visibility of UI elements.
	for (ui::CElement* const pktElementPtr : g_aptDebugModeElements)
	{
		if (pktElementPtr != nullptr)
		{
			pktElementPtr->SetIsVisible(g_bIsDebugMode);
		}
	}
}



// Resets the game: ship placements, boards, etc.
void ResetGame();

// Lets the computer player take their turn.
void DoComputerTurn()
{
	// Purely random firing. No intelligence or strategy.

	static auto s_tRandomEngine = std::default_random_engine(std::random_device()());

	CGameBoard& rtEnemyBoard = g_tPlayerBoard;

	static const int MAX_TRIES = 1000;
	int iTries = MAX_TRIES;

	CVector2i vReticlePosition;
	do
	{
		// Generate random position to shoot at.
		vReticlePosition = {
			// Random number in the range [0, 9] (assuming board width is 10).
			// TF: Pseudo Random Number
			std::uniform_int_distribution<>(0, rtEnemyBoard.GetWidth() - 1)(s_tRandomEngine),
			std::uniform_int_distribution<>(0, rtEnemyBoard.GetHeight() - 1)(s_tRandomEngine)
		};
	}
	// While that spot has already been shot.
	while (!rtEnemyBoard.TryFireAt(vReticlePosition) && ((--iTries) > 0));

	// If random position failed to find an empty spot,
	if (iTries <= 0)
	{
		// Loop through all cells and fire at each one.
		bool bContinue = true;
		for (int iRow = 0; iRow < rtEnemyBoard.GetHeight() && bContinue; ++iRow)
		{
			for (int iColumn = 0; iColumn < rtEnemyBoard.GetWidth() && bContinue; ++iColumn)
			{
				vReticlePosition = { iColumn, iRow };
				bContinue = !rtEnemyBoard.TryFireAt(vReticlePosition);
			}
		}

		// If it still failed,
		if (bContinue)
		{
			throw std::exception("There are no more cells to shoot at!");
		}
	}
}

// Action to execute when the player has finished firing a shot.
void OnAfterPlayersTurn(CGameplayBoard& _rtViewElement)
{
	using namespace consolate::colors;

	// If player won,
	if (g_tComputerBoard.AreAllShipsDestroyed())
	{
		// Setup outcome view.
		ui::CTextRect* rtTitle = reinterpret_cast<ui::CTextRect*>(g_tOutcomeView.GetElementPtrAt(0));
		if (rtTitle != nullptr)
		{
			rtTitle->SetText(TEXT("VICTORY"));
			rtTitle->SetNormalColor(COLOR_GREEN);
			rtTitle->SetFocusedColor(COLOR_GREEN);
		}

		// Navigate to outcome view.
		_rtViewElement.GetViewRef().NavigateToView(g_tOutcomeView);
	}

	DoComputerTurn();

	// If computer won,
	if (g_tPlayerBoard.AreAllShipsDestroyed())
	{
		// Setup outcome view.
		ui::CTextRect* rtTitle = reinterpret_cast<ui::CTextRect*>(g_tOutcomeView.GetElementPtrAt(0));
		if (rtTitle != nullptr)
		{
			rtTitle->SetText(TEXT("DEFEAT"));
			rtTitle->SetNormalColor(COLOR_RED);
			rtTitle->SetFocusedColor(COLOR_RED);
		}

		// Navigate to outcome view.
		_rtViewElement.GetViewRef().NavigateToView(g_tOutcomeView);
	}
}



// Initializes the MainMenu view and its elements.
void SetupMainMenuView()
{
	using namespace ui;
	using namespace consolate;
	using namespace consolate::colors;

	// TF: Reference
	CView& rtView = g_tMainMenuView;

	CVector2i vButtonPos = g_vkButtonPosStart;

	// Title Text
	{
		// TF: Pointer Initialised
		CTextRect* ptElement = nullptr;
		ptElement = new CTextRect;
		if (ptElement == nullptr)
		{
			throw std::exception("Memory allocation failed!");
		}

		// TF: Pointer Dereferenced
		(*ptElement).SetText(TEXT("BATTLESHIPS"));

		ptElement->SetPosition(g_vkTitlePos);
		ptElement->SetSize(g_vkTitleSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		// Pointed object is taken over by the view,
		// which will `delete` it when the view is destroyed.
		rtView.AddNewElement(ptElement);
	}

	// Instructions Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT(R"###(
W/S or UP/DOWN: Navigate buttons.
ENTER or SPACE: Select.
ESCAPE: Exit to Desktop.
)###"));

		ptElement->SetPosition(g_vkInfoTextPos);
		ptElement->SetSize(g_vkInfoTextSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Play Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Play"));
		ptElement->SetOnInputEventEnter([](CButton& _rtButton)
		{
			ResetGame();
			_rtButton.GetViewRef().NavigateToView(g_tPlacementView);
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// DebugMode Toggle
	{
		CToggle* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CToggle);
		ptElement->SetText(TEXT("Debug Mode"));
		ptElement->SetDefaultToggleValue(false);
		ptElement->SetOnToggle([](CToggle& _rtToggle)
		{
			SetIsDebugMode(_rtToggle.GetToggleValue());
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetNormalColorOn(COLOR_DARK_GREEN);
		ptElement->SetFocusedColorOn(COLOR_GREEN);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Exit Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Exit to Desktop"));
		ptElement->SetOnInputEventEnter([&](CButton& _rtButton)
		{
			_rtButton.GetViewRef().Exit();
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkExitColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Finish initializing the view.

	rtView.SetClearColor(g_ulkBackgroundColor);
	rtView.SetInitialFocusedIndex(2);
	rtView.SetPreviousViewPtr(nullptr);
}



// Initializes the Placement view and its elements.
void SetupPlacementView()
{
	using namespace ui;
	using namespace consolate;
	using namespace consolate::colors;

	CView& rtView = g_tPlacementView;
	CGameBoard& rtGameBoard = g_tPlayerBoard;

	CVector2i vButtonPos = g_vkButtonPosStart;

	// Title Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT("PLACEMENT"));

		ptElement->SetPosition(g_vkTitlePos);
		ptElement->SetSize(g_vkTitleSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Instructions Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT(R"###(
When Editing...
W/S/A/D or UP/DOWN/LEFT/RIGHT: Move ship.
SPACE: Rotate ship.
Q/E: Change selected ship.
ENTER: Confirm placement (must be valid).
ESCAPE: Exit to Main Menu.
)###"));

		ptElement->SetPosition(g_vkInfoTextPos);
		ptElement->SetSize(g_vkInfoTextSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Exit Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Exit"));
		ptElement->SetOnInputEventEnter([](CButton& _rtButton)
		{
			_rtButton.GetViewRef().NavigateToView(g_tMainMenuView);
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkExitColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Randomize Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Randomise"));
		ptElement->SetOnInputEventEnter([&](CButton&)
		{
			rtGameBoard.RandomizePlacement();
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Confirm Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Confirm"));
		ptElement->SetOnInputEventEnter([&](CButton& _rtButton)
		{
			_rtButton.GetViewRef().NavigateToView(g_tGameplayView);
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Edit Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT("Edit"));

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// PlacementBoard Element
	{
		CPlacementBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CPlacementBoard, rtGameBoard, DISPLAY_MODE_SELF);

		ptElement->SetPosition(g_vkPlacementBoardPos);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		ptElement->SetNavigateElementStep(-2);

		rtView.AddNewElement(ptElement);
	}

	// Finish initializing the view.

	rtView.SetClearColor(g_ulkBackgroundColor);
	rtView.SetInitialFocusedIndex(3);
	rtView.SetPreviousViewPtr(&g_tMainMenuView);
}



// Initializes the Gameplay view and its elements.
void SetupGameplayView()
{
	using namespace ui;
	using namespace consolate;
	using namespace consolate::colors;

	CView& rtView = g_tGameplayView;

	CVector2i vButtonPos = g_vkButtonPosStart;

	// Title Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT("BATTLESHIPS"));

		ptElement->SetPosition(g_vkTitlePos);
		ptElement->SetSize(g_vkTitleSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Instructions Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT(R"###(
W/S/A/D or UP/DOWN/LEFT/RIGHT: Move reticle.
SPACE or ENTER: Fire.
ESCAPE: Exit to Main Menu.
The enemy fires immediately after you.
Destroy all enemy ships.
)###"));

		ptElement->SetPosition(g_vkInfoTextPos);
		ptElement->SetSize(g_vkInfoTextSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Exit Button
	{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CButton);
		ptElement->SetText(TEXT("Exit"));
		ptElement->SetOnInputEventEnter([](CButton& _rtButton)
		{
			_rtButton.GetViewRef().NavigateToView(g_tMainMenuView);
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkExitColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}

	// Resume Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT("Resume"));

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// GameplayBoard Player-Enemy
	{
		CGameplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CGameplayBoard, g_tComputerBoard, DISPLAY_MODE_ENEMY);
		ptElement->SetLabel(TEXT("Player Shots"));
		ptElement->SetOnAfterFireHandler(OnAfterPlayersTurn);

		ptElement->SetReticlePosition({
			BOARD_WIDTH / 2,
			BOARD_HEIGHT / 2
		});

		ptElement->SetPosition(g_vkGameplayBoardPos_PlayerEnemy);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		ptElement->SetNavigateElementStep(-1);

		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Player-Self
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tPlayerBoard, DISPLAY_MODE_SELF);
		ptElement->SetLabel(TEXT("Player Ships"));

		ptElement->SetPosition(g_vkGameplayBoardPos_PlayerSelf);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Computer-Enemy
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tPlayerBoard, DISPLAY_MODE_ENEMY);
		ptElement->SetLabel(TEXT("Computer Shots"));

		ptElement->SetPosition(g_vkGameplayBoardPos_ComputerEnemy);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		g_aptDebugModeElements.AddElement(ptElement);
		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Computer-Self
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tComputerBoard, DISPLAY_MODE_SELF);
		ptElement->SetLabel(TEXT("Computer Ships"));

		ptElement->SetPosition(g_vkGameplayBoardPos_ComputerSelf);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		g_aptDebugModeElements.AddElement(ptElement);
		rtView.AddNewElement(ptElement);
	}

	// Finish initializing the view.

	rtView.SetClearColor(g_ulkBackgroundColor);
	rtView.SetInitialFocusedIndex(4);
	rtView.SetPreviousViewPtr(&g_tMainMenuView);
}



// Initializes an Outcome view and its elements.
void SetupOutcomeView()
{
	using namespace ui;
	using namespace consolate;
	using namespace consolate::colors;

	CView& rtView = g_tOutcomeView;

	CVector2i vButtonPos = g_vkButtonPosStart;

	// Title Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetIsInteractable(true);

		ptElement->SetPosition(g_vkTitlePos);
		ptElement->SetSize(g_vkTitleSize);

		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Instructions Text
	{
		CTextRect* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT(R"###(
ESCAPE: Exit to Main Menu.
)###"));

		ptElement->SetPosition(g_vkInfoTextPos);
		ptElement->SetSize(g_vkInfoTextSize);

		ptElement->SetNormalColor(g_ulkDecorationColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Exit Button
	/*{
		CButton* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CTextRect);
		ptElement->SetText(TEXT("Exit"));
		ptElement->SetOnInputEventEnter([](CButton& _rtButton)
		{
			_rtButton.GetViewRef().NavigateToView(g_tMainMenuView);
		});

		vButtonPos.m_tY += g_ikButtonYInc;
		ptElement->SetPosition(vButtonPos);
		ptElement->SetSize(g_vkButtonSize);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkExitColor);
		ptElement->SetPanelStyle(g_tkButtonStyle);

		rtView.AddNewElement(ptElement);
	}*/

	// GameplayBoard Player-Enemy
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tComputerBoard, DISPLAY_MODE_ENEMY);
		ptElement->SetLabel(TEXT("Player Shots"));

		ptElement->SetPosition(g_vkGameplayBoardPos_PlayerEnemy);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		ptElement->SetNavigateElementStep(-1);

		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Player-Self
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tPlayerBoard, DISPLAY_MODE_SELF);
		ptElement->SetLabel(TEXT("Player Ships"));

		ptElement->SetPosition(g_vkGameplayBoardPos_PlayerSelf);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Computer-Enemy
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tPlayerBoard, DISPLAY_MODE_ENEMY);
		ptElement->SetLabel(TEXT("Computer Shots"));

		ptElement->SetPosition(g_vkGameplayBoardPos_ComputerEnemy);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// DisplayBoard Computer-Self
	{
		CDisplayBoard* ptElement; ALLOCATE_NEW_MEMORY(ptElement, CDisplayBoard, g_tComputerBoard, DISPLAY_MODE_SELF);
		ptElement->SetLabel(TEXT("Computer Ships"));

		ptElement->SetPosition(g_vkGameplayBoardPos_ComputerSelf);

		ptElement->SetNormalColor(g_ulkUnfocusedColor);
		ptElement->SetFocusedColor(g_ulkFocusedColor);
		ptElement->SetPanelStyle(g_tkTextStyle);

		rtView.AddNewElement(ptElement);
	}

	// Finish initializing the views.

	rtView.SetClearColor(g_ulkBackgroundColor);
	rtView.SetInitialFocusedIndex(0);
	rtView.SetPreviousViewPtr(&g_tMainMenuView);
}

// Initializes ships for each board.
void SetupShipTypes()
{
	// Clear the boards.
	g_tPlayerBoard.Reset();
	g_tComputerBoard.Reset();

	// Aircraft Carrier
	{
		// TF: Class Instance
		CShip tShip({
			CCollider({ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, }),
			CCollider({ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, }),
		});
		tShip.SetName(TEXT("Aircraft Carrier"));
		tShip.SetSymbol(TEXT("A"));

		g_tPlayerBoard.AddShip(tShip);
		g_tComputerBoard.AddShip(tShip);
	}

	// Battleship
	{
		CShip tShip({
			CCollider({ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, }),
			CCollider({ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, }),
		});
		tShip.SetName(TEXT("Battleship"));
		tShip.SetSymbol(TEXT("B"));

		g_tPlayerBoard.AddShip(tShip);
		g_tComputerBoard.AddShip(tShip);
	}

	// Cruiser
	{
		CShip tShip({
			CCollider({ { 0, 0 }, { 1, 0 }, { 2, 0 }, }),
			CCollider({ { 0, 0 }, { 0, 1 }, { 0, 2 }, }),
		});
		tShip.SetName(TEXT("Cruiser"));
		tShip.SetSymbol(TEXT("C"));

		g_tPlayerBoard.AddShip(tShip);
		g_tComputerBoard.AddShip(tShip);
	}

	// Submarine
	{
		CShip tShip({
			CCollider({ { 0, 0 }, { 1, 0 }, { 2, 0 }, }),
			CCollider({ { 0, 0 }, { 0, 1 }, { 0, 2 }, }),
		});
		tShip.SetName(TEXT("Submarine"));
		tShip.SetSymbol(TEXT("S"));

		g_tPlayerBoard.AddShip(tShip);
		g_tComputerBoard.AddShip(tShip);
	}

	// Destroyer
	{
		CShip tShip({
			CCollider({ { 0, 0 }, { 1, 0 }, }),
			CCollider({ { 0, 0 }, { 0, 1 }, }),
		});
		tShip.SetName(TEXT("Destroyer"));
		tShip.SetSymbol(TEXT("D"));

		g_tPlayerBoard.AddShip(tShip);
		g_tComputerBoard.AddShip(tShip);
	}

	// Finish initializing boards.
	g_tPlayerBoard.RandomizePlacement();
	g_tComputerBoard.RandomizePlacement();
}



// Resets the game: ship placements, boards, etc.
void ResetGame()
{
	SetupShipTypes();
}



// Starts the program.
void Program()
{
	using namespace consolate;
	using namespace consolate::colors;

	// Check configuration.

#ifndef UNICODE
	throw std::exception("The program must be built with UNICODE defined.");
#endif //~ UNICODE

#if not defined(_DEBUG) and defined __MYDEBUG_HPP__
	throw std::exception("The release build should not #include \"mydebug.hpp\".");
#endif //~ not defined(_DEBUG) and defined __MYDEBUG_HPP__



	// Setup Global Constants
	// which could not be defined at declaration.

	g_tkTextStyle = SPanelStyle::PANELSTYLE_SINGLE;
	g_tkButtonStyle = SPanelStyle::PANELSTYLE_DOUBLE;

	g_vkButtonPosStart.m_tY -= g_ikButtonYInc;



	// Initialize window size.
	g_tConsolate.SetContainerWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Setup Views
	SetupMainMenuView();
	SetupPlacementView();
	SetupGameplayView();
	SetupOutcomeView();

	SetIsDebugMode(false);

	// Setup Boards
	SetupShipTypes();

	// Start the game (UI rendering loop).
	g_tMainMenuView.Display();
}



// Application entry point.
int main()
{
	using namespace std;

#ifdef _DEBUG
	try
#endif //~ _DEBUG
	{
		Program();
	}
#ifdef _DEBUG
	catch (const exception& e)
	{
		wcout << "Exception: " << e.what() << endl;
		throw;
	}
	catch (const char* const kpckMessage)
	{
		wcout << "CString Execption: " << kpckMessage << endl;
		throw;
	}
	catch (...)
	{
		wcout << "Unknown Exception." << endl;
		throw;
	}
#endif //~ _DEBUG



	// Cleaning up.

	consolate::g_tConsolate.Reset();
	consolate::g_tConsolate.ClearScreen();

#ifdef _DEBUG

	wcout << "Program has terminated." << endl;
	_getch();

#endif //~ _DEBUG

	return 0;
}
