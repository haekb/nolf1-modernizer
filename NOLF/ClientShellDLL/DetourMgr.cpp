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
	m_pConsoleFuncVa = NULL;
	m_pConsoleFuncSimple = NULL;
}

DetourMgr::~DetourMgr()
{
	Term();
}

void DetourMgr::Init()
{
	m_pConsoleFunc = (int*)CONSOLE_FUNCTION_PTR;
	m_pConsoleFuncVa = (int*)CONSOLE_FUNCTION_PTR_VA;
	m_pConsoleFuncSimple = (int*)CONSOLE_FUNCTION_PTR_SIMPLE;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// Attach some functions!
	DetourAttach(&(PVOID&)m_pConsoleFunc, df_Console);
	DetourAttach(&(PVOID&)m_pConsoleFuncSimple, df_ConsoleSimple);

	DetourTransactionCommit();

}

void DetourMgr::Term()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)m_pConsoleFunc, df_Console);
	DetourDetach(&(PVOID&)m_pConsoleFuncSimple, df_ConsoleSimple);
	DetourTransactionCommit();
}

// Main console print method
// We can filter with iLevel, although I've only seen 0 and 1 be used, and I'm not sure either's context.
// Colour works, so that's neat.
void DetourMgr::ConsolePrint(HLTCOLOR iColour, int iLevel, const char* pMsg)
{
	if (!g_pConsoleMgr) {
		return;
	}

	std::string sString = pMsg;

	g_pConsoleMgr->Read(sString.c_str(), iColour, iLevel);

	// Run the original console print
	((ConsoleFn)m_pConsoleFunc)(iColour, iLevel, pMsg);
}

