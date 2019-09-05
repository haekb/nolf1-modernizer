#include "stdafx.h"
#include "FolderJukebox.h"
#include "FolderMgr.h"
#include "FolderCommands.h"
#include "ClientRes.h"

#include "GameClientShell.h"
#include "GameSettings.h"

namespace
{
	int kGap = 0;
	int kWidth = 0;

	const int PLAY_AMBUSH		= (FOLDER_CMD_CUSTOM + 1);
	const int PLAY_BADEDUM		= (FOLDER_CMD_CUSTOM + 2);
	const int PLAY_BADGUY		= (FOLDER_CMD_CUSTOM + 3);
	const int PLAY_NOLFORCH		= (FOLDER_CMD_CUSTOM + 4);
	const int PLAY_NOLFTHEME	= (FOLDER_CMD_CUSTOM + 5);
	const int PLAY_GOTY			= (FOLDER_CMD_CUSTOM + 6);

}

CFolderJukebox::CFolderJukebox()
{

}

CFolderJukebox::~CFolderJukebox()
{
}

LTBOOL CFolderJukebox::Build()
{
	CreateTitle("Jukebox");

	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_JUKEBOX, "ColumnWidth"))
		kGap = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_JUKEBOX, "ColumnWidth");
	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_JUKEBOX, "SliderWidth"))
		kWidth = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_JUKEBOX, "SliderWidth");

	LTFLOAT yr = g_pInterfaceResMgr->GetYRatio();
	kGap *= yr;

	AddTextItem("Ambush", PLAY_AMBUSH, 0);
	AddTextItem("Ba De Dum", PLAY_BADEDUM, 0);
	AddTextItem("Bad Guys", PLAY_BADGUY, 0);
	AddTextItem("Orchestra", PLAY_NOLFORCH, 0);
	AddTextItem("Main Theme", PLAY_NOLFTHEME, 0);
	AddTextItem("Game Of The Year", PLAY_GOTY, 0);

	// Make sure to call the base class
	if (!CBaseFolder::Build()) return LTFALSE;

	UseBack(LTTRUE, LTTRUE);

	return LTTRUE;
}


uint32 CFolderJukebox::OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2)
{
	switch (dwCommand)
	{
	case PLAY_AMBUSH:
	case PLAY_BADEDUM:
	case PLAY_BADGUY:
	case PLAY_NOLFORCH:
	case PLAY_NOLFTHEME:
	case PLAY_GOTY:
	{
		PlayScore(dwCommand);
		break;
	}
	default:
		return CBaseFolder::OnCommand(dwCommand, dwParam1, dwParam2);
	}
	return 1;
};



void CFolderJukebox::OnFocus(LTBOOL bFocus)
{
	// Enter
	if (bFocus) {
		UpdateData(LTFALSE);
		CBaseFolder::OnFocus(bFocus);
		return;
	}

	// Leave
	UpdateData(LTTRUE);

	CBaseFolder::OnFocus(bFocus);
}

LTBOOL CFolderJukebox::PlayScore(int scoreId)
{
	std::string directory = "Music\\";
	std::string controlFile;

	switch (scoreId)
	{
	case PLAY_AMBUSH:
		directory += "AMBUSH";
		controlFile = "AMBUSH.txt";
		break;
	case PLAY_BADEDUM:
		directory += "BADEDUM";
		controlFile = "BADEDUM.txt";
		break;
	case PLAY_BADGUY:
		directory += "BADGUY";
		controlFile = "BADGUY.txt";
		break;
	case PLAY_NOLFORCH:
		directory += "NOLFORCH";
		controlFile = "NOLFORCH.txt";
		break;
	case PLAY_NOLFTHEME:
		directory += "NOLFTHEME";
		controlFile = "NOLFTHEME.txt";
		break;
	case PLAY_GOTY:
		directory += "GOTY";
		controlFile = "GOTY.txt";
		break;
	default:
		return LTFALSE;
	}

	CMusicState MusicState;
	strcpy(MusicState.szDirectory, (char*)(LPCSTR)directory.c_str());
	strcpy(MusicState.szControlFile, (char*)(LPCSTR)controlFile.c_str());

	if (!g_pGameClientShell->GetMusic()->RestoreMusicState(MusicState))
	{
		return LTFALSE;
	}

	g_pLTClient->RunConsoleString("MUSIC I 5 Immediately");

	return LTTRUE;
}
