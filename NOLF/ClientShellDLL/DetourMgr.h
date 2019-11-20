#pragma once

// Debug Output?
//#define CONSOLE_FUNCTION_PTR 0x496B1B;
// Formatting?
//#define CONSOLE_FUNCTION_PTR 0x49318E;
// Not it
//#define CONSOLE_FUNCTION_PTR 0x41d1c0;

// Console Print
#define CONSOLE_FUNCTION_PTR 0x41b880;
#define CONSOLE_FUNCTION_PTR_SIMPLE 0x41b8c0;
#define CONSOLE_FUNCTION_PTR_VA 0x41d380;

typedef void (*ConsoleFn)(HLTCOLOR iColour, int iLevel, const char* pMsg);

class DetourMgr
{
public:
	DetourMgr();
	~DetourMgr();

	void Init();
	void Term();

	void ConsolePrint(HLTCOLOR iColour, int iLevel, const char* pMsg);

protected:

private:

	int* m_pConsoleFunc;
	int* m_pConsoleFuncVa;
	int* m_pConsoleFuncSimple;

};

extern DetourMgr* g_pDetourMgr;

// Detour Functions
inline void df_Console(HLTCOLOR iColour, int iLevel, const char* pMsg) { if (!g_pDetourMgr) return; g_pDetourMgr->ConsolePrint(iColour, iLevel, pMsg); };

// The original function, there's only one reference that calls this, so I'm not sure it's correct...
// So it's not used!
inline void df_ConsoleVa(HLTCOLOR iColour, int iLevel, const char* pFormat, va_list vaList)
{
	if (!g_pConsoleMgr) {
		return;
	}

	char aMsgBuffer[2048];
	memset(aMsgBuffer, '\0', sizeof(aMsgBuffer));
	_vsnprintf(aMsgBuffer, sizeof(aMsgBuffer), pFormat, vaList);

	aMsgBuffer[strlen(aMsgBuffer)] = '\0';

	df_Console(iColour, iLevel, aMsgBuffer);
}

// Someone just wants to print a message, that's cool.
inline void df_ConsoleSimple(const char* pMsg)
{
	if (!g_pConsoleMgr) {
		return;
	}

	df_Console(SETRGB(255,255,255), 0, pMsg);
}