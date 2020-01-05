#pragma once
#include <string>
#include <vector>
#include "iclientshell.h"

// Disabled for now, has a bug where it moves two positions, and I just wanna push this forward.
//#define CONSOLE_CURSOR

struct HistoryData {
	std::string sMessage;
	unsigned int iColour;
	int iLevel;
};

class ConsoleMgr
{
public:

	ConsoleMgr();
	~ConsoleMgr();

	void Init();
	void Destroy();
	LTBOOL HandleChar(unsigned char c);
	LTBOOL HandleKeyDown(int key, int rep);
	void Read(std::string sMessage, unsigned int iColour, int iLevel);
	void Send();
	void Draw();
	void Show(bool bShow);

	void MoveUp(bool bTop);
	void MoveDown(bool bBottom);

	void RecallHistoryUp();
	void RecallHistoryDown();

	void AdjustView();

	void AddToHelp(std::string command);
	void RemoveFromHelp(std::string command);

	LTBOOL  IsVisible() { return m_bVisible; }

	std::vector<std::string> GetHelpList() { return m_HelpList; };
	std::vector<HistoryData> GetHistory() { return m_History; };

protected:
	std::vector<HistoryData> m_History;
	std::vector<HistoryData> m_HistorySlice;
	HSURFACE m_hConsoleSurface;

	std::vector<std::string> m_HelpList;
	std::vector<std::string> m_CommandHistory;

	std::vector<CLTGUITextItemCtrl*> m_pLineItems;
	CLTGUITextItemCtrl* m_pEditText;
	char m_szEdit[256];
	CLTGUIEditCtrl* m_pEdit;

	// Console dims
	int m_iWidth;
	int m_iHeight;
	int m_iFontSize;
	int m_iLineSpacing;

	// 
	int m_iCurrentPosition;
	int m_iCursorPosition;
	int m_iCommandHistoryPosition;

	bool m_bInitialized;
	bool m_bVisible;

	int m_iOldGameState;
};

