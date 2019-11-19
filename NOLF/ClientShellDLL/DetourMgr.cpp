#include "stdafx.h"
#include "ltbasedefs.h"
#include <detours.h>
#include "DetourMgr.h"
#include "ConsoleMgr.h"

DetourMgr* g_pDetourMgr = NULL;
extern ConsoleMgr* g_pConsoleMgr;

DetourMgr::DetourMgr()
{
	g_pDetourMgr = this;
	m_pConsoleFunc = NULL;
}

DetourMgr::~DetourMgr()
{
}

void DetourMgr::Init()
{
	m_pConsoleFunc = (int*)CONSOLE_FUNCTION_PTR;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Attach some functions!
	DetourAttach(&(PVOID&)m_pConsoleFunc, df_Console);

	DetourTransactionCommit();

}

void DetourMgr::Term()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)m_pConsoleFunc, df_Console);
	DetourTransactionCommit();
}


void DetourMgr::ConsolePrint(int iColour, int iLevel, const char* pFormat, va_list vaList)
{
	if (!g_pConsoleMgr) {
		return;
	}

	char aMsgBuffer[2048];
	memset(aMsgBuffer, '\0', sizeof(aMsgBuffer));
	_vsnprintf(aMsgBuffer, sizeof(aMsgBuffer), pFormat, vaList);

	aMsgBuffer[sizeof(aMsgBuffer) - 1] = '\0';

	g_pConsoleMgr->Read(aMsgBuffer, iColour, iLevel);

	SDL_Log("CONSOLE: %s", aMsgBuffer);
}
