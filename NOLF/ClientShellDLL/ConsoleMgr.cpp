#include "stdafx.h"
#include "ltbasedefs.h"
#include "InterfaceResMgr.h"
#include "ConsoleMgr.h"
#include "MsgIDs.h"
#include <algorithm>

#include "LTGUIMgr.h"


ConsoleMgr* g_pConsoleMgr = NULL;

extern CCheatMgr* g_pCheatMgr;
extern VarTrack g_vtConsoleBackdrop;
//extern CInterfaceResMgr* g_pInterfaceResMgr;

void ShowHelpListCommand(int argc, char** argv)
{
	if (!g_pConsoleMgr) {
		return;
	}

	g_pLTClient->CPrint("Available game commands:");
	for (auto item : g_pConsoleMgr->GetHelpList()) {
		g_pLTClient->CPrint((char*)item.c_str());
	}
}

void WriteToDebugLog(int argc, char** argv)
{
	if (!g_pConsoleMgr) {
		return;
	}

	g_pLTClient->CPrint("Writing to Debug.log...");

	SDL_Log("Writing Console History");
	SDL_Log("---------------------------------------");
	for (auto history : g_pConsoleMgr->GetHistory()) {
		SDL_Log("%s", history.sMessage.c_str());
	}
	SDL_Log("---------------------------------------");

	g_pLTClient->CPrint("Done!");
}

ConsoleMgr::ConsoleMgr()
{
	g_pConsoleMgr = this;

	m_bInitialized = false;
	m_bVisible = false;
	m_hConsoleSurface = NULL;
	memset(m_szEdit, 0, sizeof(m_szEdit));

	m_iWidth = 320;			// px
	m_iHeight = 240;		// Pixels
	m_iFontSize = 14;		// Pixels?
	m_iLineSpacing = 16;	// Pixels!

	// Position in History
	m_iCurrentPosition = 0;
	// Position in UI elements
	m_iCursorPosition = 0;

	m_iCommandHistoryPosition = 0;

	m_iOldGameState = -1;

	g_pLTClient->RegisterConsoleProgram("Help", ShowHelpListCommand);
	g_pLTClient->RegisterConsoleProgram("WriteToDebugLog", WriteToDebugLog);
}

ConsoleMgr::~ConsoleMgr()
{
	g_pLTClient->UnregisterConsoleProgram("Help");
	g_pLTClient->UnregisterConsoleProgram("WriteToDebugLog");

	Destroy();

	if (g_pConsoleMgr) {
		g_pConsoleMgr = NULL;
	}

	if (m_hConsoleSurface) {
		g_pInterfaceResMgr->FreeSharedSurface(m_hConsoleSurface);
		m_hConsoleSurface = NULL;
	}
}

void ConsoleMgr::Init()
{
	// If we're re-initializing, then destroy all the items
	if (m_bInitialized) {
		Destroy();
	}

	auto pFont = g_pInterfaceResMgr->GetSmallFont();

	if (!pFont) {
		return;
	}

	RMode currentMode;
	g_pLTClient->GetRenderMode(&currentMode);

	m_iHeight = (int)((float)currentMode.m_Height * 0.50f);
	m_iWidth = (int)currentMode.m_Width;

	// Calculate the amount of items we need to fill the space, and then minus one for our edit line.
	int iLineItemLength = (int)((float)m_iHeight / (float)m_iLineSpacing) - 1;

	// Create the lines for our console text
	// TODO: Maybe look into large text fields? Not sure if this will cause any performance concerns.
	for (int i = 0; i < iLineItemLength; i++) {

		CLTGUITextItemCtrl* pText = debug_new(CLTGUITextItemCtrl);
		if (!pText->Create(g_pLTClient, NULL, NULL, pFont, NULL, 0))
		{
			debug_delete(pText);
			pText = LTNULL;
		}

		m_pLineItems.push_back(pText);
	}

	// This is basically the little symbol, in our case it's `>` in front of the edit line
	m_pEditText = debug_new(CLTGUITextItemCtrl);
	if (!m_pEditText->Create(g_pLTClient, NULL, NULL, pFont, NULL, 0))
	{
		debug_delete(m_pEditText);
		m_pEditText = LTNULL;
	}

	HSTRING hString = g_pLTClient->CreateString(">");

	m_pEditText->AddString(hString);

	g_pLTClient->FreeString(hString);

	m_pEditText->SetColor(kWhite, kWhite, kWhite);
	
	m_pEdit = debug_new(CLTGUIEditCtrl);
	if (!m_pEdit->Create(g_pLTClient, 1, NULL, pFont, 0, 256, NULL, m_szEdit))
	{
		debug_delete(m_pEdit);
		m_pEdit = LTNULL;
	}

	m_pEdit->Enable(LTTRUE);
	m_pEdit->EnableCursor();
	m_pEdit->SetColor(kWhite, kWhite, kWhite);

	m_bInitialized = true;
}

void ConsoleMgr::Destroy()
{
	if (!m_bInitialized) {
		return;
	}

	m_pEdit->Destroy();
	m_pEditText->Destroy();

	for (auto item : m_pLineItems) {
		item->Destroy();
	}

	m_pLineItems.clear();
}

LTBOOL ConsoleMgr::HandleChar(unsigned char c)
{
	if (!m_bVisible) return LTFALSE;

	// Ignore console key
	if (c == VK_OEM_3) {
		return LTFALSE;
	}

	return m_pEdit->HandleChar(c);
}


LTBOOL ConsoleMgr::HandleKeyDown(int key, int rep)
{
	if (!m_bVisible) {
		if (key == VK_OEM_3) {
			Show(true);
			return LTTRUE;
		}

		return LTFALSE;
	}

	switch (key) {
	case VK_OEM_3:
	case VK_ESCAPE:
	{
		Show(false);
		return LTTRUE;
	} break;

	case VK_RETURN:
	{
		Send();
		return LTTRUE;
	} break;
	case VK_UP:
		RecallHistoryUp();
		break;
	case VK_DOWN:
		RecallHistoryDown();
		break;
	case VK_PRIOR: // Page Up
		MoveUp(false);
		break;
	case VK_NEXT: // Page Down
		MoveDown(false);
		break;
	}

	m_pEdit->HandleKeyDown(key, rep);
	return LTTRUE;
}

void ConsoleMgr::Read(std::string sMessage, unsigned int iColour, int iLevel)
{
	HistoryData data;

	data.iColour = iColour;
	data.sMessage = sMessage;
	data.iLevel = iLevel;
	
	m_History.push_back(data);

	// Ok we can't actually adjust our position if we're not init'd.
	// This happens when the game is launching and setting stuff up before consolemgr is init'd.
	if (!m_bInitialized) {
		m_iCurrentPosition++;
		return;
	}

	MoveDown(false);
}

void ConsoleMgr::Send()
{
	MoveDown(true);

	// Throw it in our history!
	m_CommandHistory.push_back(m_szEdit);
	m_iCommandHistoryPosition = m_CommandHistory.size();

	// Echo it back
	g_pLTClient->CPrint(m_szEdit);

	// Jake: Small hack, in case they disable OldMouseLook through the console, we also need to disable CursorCenter!
	if (stricmp(m_szEdit, "OldMouseLook 0") == 0) {
		g_pLTClient->RunConsoleString("CursorCenter 0");
	}

	// If it's a cheat we can just run that instead!
	if (g_pCheatMgr->Check(m_szEdit)) {
		g_pClientSoundMgr->PlayInterfaceSound("Menu\\Snd\\Cheat.wav");
		// Clear our command string
		m_pEdit->SetText("");
		memset(m_szEdit, 0, sizeof(m_szEdit));
		return;
	}

	// Always run it on client, just in case it's not a server command or we can't run server commands.
	g_pLTClient->RunConsoleString(m_szEdit);

	// If we're hosting or in singleplayer, we can run server commands!
	if(g_pGameClientShell->IsHosting() || !g_pGameClientShell->IsMultiplayerGame())
	{
		// Are we running in a server? If so, send it to the server so they can send it off!
		HSTRING hstrCmd = g_pLTClient->CreateString(m_szEdit);

		HMESSAGEWRITE hMessage = g_pLTClient->StartMessage(MID_CONSOLE_COMMAND_CLIENT);
		g_pLTClient->WriteToMessageHString(hMessage, hstrCmd);
		g_pLTClient->EndMessage(hMessage);

		g_pLTClient->FreeString(hstrCmd);
	}

	// Clear our command string
	m_pEdit->SetText("");
	memset(m_szEdit, 0, sizeof(m_szEdit));
}

void ConsoleMgr::Draw()
{
	if (!m_bVisible) {
		return;
	}

	g_pLTClient->Start3D();
	g_pLTClient->StartOptimized2D();

	HSURFACE hBlank;

	int iConsoleBackdrop = g_vtConsoleBackdrop.GetFloat();
	
	switch (iConsoleBackdrop) {
	case 1: 
		hBlank = g_pLTClient->CreateSurfaceFromBitmap("menu\\art\\blanktag.pcx");
		break;
	case 2:
		hBlank = g_pLTClient->CreateSurface(64, 64);
		g_pLTClient->ScaleSurfaceToSurfaceSolidColor(hBlank, hBlank, LTNULL, LTNULL, LTNULL, SETRGB(0, 0, 0));
		break;
	case 0:
	default:
		hBlank = g_pLTClient->CreateSurfaceFromBitmap("interface\\console.pcx");
	}

	HSURFACE hScreen = g_pLTClient->GetScreenSurface();

	LTRect dest = { 0, 0, m_iWidth, m_iHeight };

	g_pLTClient->ScaleSurfaceToSurface(hScreen, hBlank, &dest, LTNULL);

	m_pEdit->UpdateData(LTTRUE);

	LTIntPt pos = { 8, 0 };

	for (auto item : m_pLineItems) {
		item->RemoveAll();
	}
	
	auto selectionColour = SETRGB(255, 128, 255);

	int index = 0;
	for (auto item : m_HistorySlice) {
		if (index >= m_pLineItems.size()) {
			break;
		}

		auto pText = m_pLineItems.at(index);

		HSTRING hString = g_pLTClient->CreateString((char*)item.sMessage.c_str());

		pText->SetPos(pos);
		pText->AddString(hString);
		pText->SetColor(selectionColour, item.iColour, item.iColour);

		g_pLTClient->FreeString(hString);

		pText->Render(hScreen);

		index++;
		pos.y += m_iLineSpacing;
	}

	// Make sure our edit input is always at the bottom!
	pos.y = m_iLineSpacing * m_pLineItems.size();

	m_pEditText->SetPos(pos);
	pos.x += m_iLineSpacing / 2;
	m_pEdit->SetPos(pos);

	m_pEditText->Render(hScreen);
	m_pEdit->Render(hScreen);

	g_pLTClient->DeleteSurface(hBlank);

	g_pLTClient->EndOptimized2D();
	g_pLTClient->End3D();
}

void ConsoleMgr::Show(bool bShow)
{
	if (!m_bInitialized) {
		return;
	}

	// For now let's disable it in multiplayer!
	if (IsMultiplayerGame()) {
		m_bVisible = false;
		return;
	}

	// Pause the game
	g_pGameClientShell->PauseGame(bShow, LTTRUE);

	
	// Clear our command string
	m_pEdit->SetText("");

	m_bVisible = bShow;

	MoveDown(true);
}

void ConsoleMgr::MoveUp(bool bTop)
{
	if (bTop) {
		m_iCurrentPosition = m_pLineItems.size();
		m_iCursorPosition = 0;
	}
	else {
		if (m_iCurrentPosition > m_pLineItems.size()) {
			m_iCurrentPosition--;
		}
		if (m_iCursorPosition > 0) {
			m_iCursorPosition--;
		}
	}

	AdjustView();
}

void ConsoleMgr::MoveDown(bool bBottom)
{
	if (bBottom) {
		m_iCurrentPosition = m_History.size();
		m_iCursorPosition = m_pLineItems.size() - 1;
	}
	else {
		if (m_iCurrentPosition < m_History.size()) {
			m_iCurrentPosition++;
		}
		if (m_iCursorPosition < m_pLineItems.size() - 1) {
			m_iCursorPosition++;
		}
	}

	AdjustView();
}

void ConsoleMgr::RecallHistoryUp()
{
	if (m_CommandHistory.size() == 0) {
		return;
	}

	if (m_iCommandHistoryPosition > 0) {
		m_iCommandHistoryPosition--;
	}

	m_pEdit->SetText((char*)m_CommandHistory[m_iCommandHistoryPosition].c_str());
}

void ConsoleMgr::RecallHistoryDown()
{
	if (m_CommandHistory.size() == 0) {
		return;
	}

	if (m_iCommandHistoryPosition < m_CommandHistory.size() - 1) {
		m_iCommandHistoryPosition++;
	}

	m_pEdit->SetText((char*)m_CommandHistory[m_iCommandHistoryPosition].c_str());
}

void ConsoleMgr::AdjustView()
{
	if (!m_bVisible) {
		return;
	}

	m_HistorySlice.clear();

	int iBegin = m_iCurrentPosition - m_pLineItems.size();
	int iEnd = m_iCurrentPosition + m_pLineItems.size();

	// Clamp our being/end to -> 0 - Max Size
	if (iBegin < 0) {
		iBegin = 0;
	}
	if (iEnd > m_History.size()) {
		iEnd = m_History.size();
	}

	// Special case:
	// If we haven't filled the screen with commands, don't allow them to move up!
	if (m_History.size() < m_pLineItems.size()) {
		iBegin = 0;
	}

	// Remake the vector with the new slice
	std::vector<HistoryData> historySlice(m_History.begin() + iBegin, m_History.begin() + iEnd);

	for (auto item : historySlice) {
		m_HistorySlice.push_back(item);
	}

	historySlice.clear();
}

void ConsoleMgr::AddToHelp(std::string command)
{
	std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c) { return std::tolower(c); });

	m_HelpList.push_back(command);
}

void ConsoleMgr::RemoveFromHelp(std::string command)
{
	int index = 0;
	for (auto item : m_HelpList) {
		if (command.compare(item) == 0) {
			item.erase(item.begin() + index);
		}
		index++;
	}
}
