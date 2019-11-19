#pragma once

// Debug Output?
//#define CONSOLE_FUNCTION_PTR 0x496B1B;

#define CONSOLE_FUNCTION_PTR 0x49318E;


class DetourMgr
{
public:
	DetourMgr();
	~DetourMgr();

	void Init();
	void Term();

	void ConsolePrint(int iColour, int iLevel, const char* pFormat, va_list vaList);

protected:

private:

	int* m_pConsoleFunc;

};

extern DetourMgr* g_pDetourMgr;

// Detour Functions
inline void df_Console(int iColour, int iLevel, const char* pFormat, va_list vaList) { if (!g_pDetourMgr) return; g_pDetourMgr->ConsolePrint(iColour, iLevel, pFormat, vaList); };