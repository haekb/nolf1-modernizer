#include "stdafx.h"
#include "FolderJukebox.h"
#include "FolderMgr.h"
#include "FolderCommands.h"
#include "ClientRes.h"

#include "GameClientShell.h"
#include "GameSettings.h"
#include <string>
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

	const int APPLY_SETTINGS	= (FOLDER_CMD_CUSTOM + 7);

}

std::string m_sAmbushIntensity[12] = {
	"Silence", // 1
	"Sub Ambience",
	"Ambient Tension",
	"Sneaky",
	"Action", // Plays 1 time, then moves to Combat (6)
	"Combat",
	"Drive",
	"Low Earth Orbit",
	"Moracco",
	"Trains",
	"Bumper 1", // Plays 1 time, then moves to Sub Ambience (1)
	"Bumper 2" // 12 // Plays 1 time, then moves to Sub Ambience (1)
};

std::string m_sBaDeDumIntensity[26] = {
	"Silence", // 1
	"Sub Ambience",
	"Slow Ambience",
	"Slow Ambience (Drums)",
	"Medium Ambience",
	"Medium Ambience (Drums)",
	"Combat",
	"Fast Ambience",
	"Combat (Orchestral)", // Plays 2 times, then moves to Intro (18)
	"Medium Ambience (Orchestral)",
	"Tension (Orchestral)",
	"Bumper 1",
	"Bumper 2",
	"Bumper 3",
	"Bumper 4",
	"Bumper 5",
	"Medium Vibes",
	"Combat Intro (Orchestral)", // Plays 2 times, then moves to Break (19)
	"Combat Break (Orchestral)", // Plays 4 times then moves to Combat (9)
	"Sneaky", // 20
	"Slow Ambience (Mix)",
	"Slow Ambience (Mix 2)",
	"Medium Vibes (Mix)",
	"Medium Ambience (Mix)",
	"Combat (Mix)"
	"Oompaa!"
};

std::string m_sBadGuysIntensity[20] = {
	"Silence", // 1
	"Sub Ambience 1", // Plays 1 time, then moves to Sub Ambience 2 (3)
	"Sub Ambience 2",
	"Ambience 1", // Plays 1 time, then moves to Ambience 2 (5)
	"Ambience 2", // Plays 1 time, then moves to Ambience 1 (4)
	"Swing 1", // Plays 1 time, then moves to Swing 2 (7)
	"Swing 2", // Plays 1 time, then moves to Swing 3 (8)
	"Swing 3", // Plays 1 time, then moves to Swing 1 (6)
	"Rock & Bebop 1", // Plays 1 time, then moves to Rock & Bebop 2 (10)
	"Rock & Bebop 2", // Plays 1 time, then moves to Rock & Bebop 3 (11)
	"Rock & Bebop 3", // Plays 1 time, then moves to Rock & Bebop 4 (12)
	"Rock & Bebop 4", // Plays 1 time, then moves to Rock & Bebop 5 (13)
	"Rock & Bebop 5", // Plays 1 time, then moves to Rock & Bebop 1 (9)
	"Action 1", // Plays 1 time, then moves to Action 2 (15)
	"Action 2", // Plays 1 time, then moves to Action 3 (16)
	"Action 3", // Plays 1 time, then moves to Action 4 (17)
	"Action 5", // Plays 1 time, then moves to Action 5 (18)
	"Action 6", // Plays 1 time, then moves to Action 6 (20)
	"Action 7", // Plays 1 time, then moves to Action 1 (14)
};

std::string m_sOrchestralIntensity[8] = {
	"Silence", // 1
	"High Action 1", // Loops 1 time, then moves to High Action 2 (3)
	"High Action 2", // Loops 2 times, then moves to High Action Break (8)
	"Tension", 
	"Ambience",
	"Adventure" // Plays 1 time, then moves to Adventure Break (7)
	"Adventure Break" // Loops 4 times then, moves to Adventure (6)
};

std::string m_sMainThemeIntensity[14] = {
	"Silence" // 1,
	"Sub Ambience",
	"Ambience",
	"Slow Ambience",
	"Medium Ambience",
	"High Ambience (Main Theme)" // Plays 1 time, then moves to High Break (13)
	"Bumper 1", // Plays 1 time
	"Bumper 2", // Plays 1 time
	"Bumper 3", // Plays 1 time
	"Bumper 4", // Plays 1 time
	"Bumper 5", // Plays 1 time
	"Ambience Vibes",
	"High Break", // Plays 1 time, then moves to High Ambience (6)
	"Sneaky"
};

std::string m_sGOTYIntensity[8] = {
	"Normal",
	"Ambience",
	"Searching", // Plays 1 time, then moves to Routine (4)
	"Routine", // Plays 1 time, then moves to Searching (3)
	"Gumshoe 1", // Plays 1 time, then moves to Ambience (2)
	"Gumshoe 2", // Plays 1 time, then moves to Ambience (2)
	"Agressive", // Plays 1 time, then moves to Combat (8)
	"Combat" // Plays 1 time, then moves to Aggressive (7)
};

CFolderJukebox::CFolderJukebox()
{
	m_nIntensityLevel = 5;
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

	AddTextItem("Apply", APPLY_SETTINGS, 0);


	CCycleCtrl* intensityCtrl = AddCycleItem("Intensity", 0, kWidth, kGap, &m_nIntensityLevel);

	for (int i = 0; i < 30; i++) {

		std::string level = std::to_string(i);

		// Add the string to the control
		HSTRING hTemp = g_pLTClient->CreateString((char*)level.c_str());
		intensityCtrl->AddString(hTemp);

		// Free the strings
		g_pLTClient->FreeString(hTemp);
	}

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
	case APPLY_SETTINGS:
	{
		UpdateData(LTTRUE);
		g_pGameClientShell->GetMusic()->Play(m_nIntensityLevel);
		//std::string intensity = "MUSIC I " + std::to_string(m_nIntensityLevel) + " Immediately";
		//g_pLTClient->RunConsoleString((char*)intensity.c_str());
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

	UpdateData(LTTRUE);
	g_pGameClientShell->GetMusic()->Play(m_nIntensityLevel);

	return LTTRUE;
}
