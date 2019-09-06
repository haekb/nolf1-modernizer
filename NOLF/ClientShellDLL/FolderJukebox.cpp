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
	LTRect rcSongListRect;
	int nListHeight = 0;
	int nListWidth = 0;
	int nArrowWidth = 0;
	int nIndent = 0;

	const int PLAY_AMBUSH = (FOLDER_CMD_CUSTOM + 1);
	const int PLAY_BADEDUM = (FOLDER_CMD_CUSTOM + 2);
	const int PLAY_BADGUY = (FOLDER_CMD_CUSTOM + 3);
	const int PLAY_NOLFORCH = (FOLDER_CMD_CUSTOM + 4);
	const int PLAY_NOLFTHEME = (FOLDER_CMD_CUSTOM + 5);
	const int PLAY_GOTY = (FOLDER_CMD_CUSTOM + 6);

	const int PLAY_SONG = (FOLDER_CMD_CUSTOM + 7);

}

// Just for reference, here's the intensities for each "Song"
// They're in order from 1 ... n
#if 0
// Individual Intensities
std::string m_sAmbushIntensity[12] = {
	"Silence", // 1
	"Sub Ambience",
	"Ambient Tension",
	"Sneak",
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
	"Sneak", // 20
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
	"Sneak"
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
#endif

CFolderJukebox::CFolderJukebox()
{
	m_sCurrentSong = "";

	m_PreviousMusicState.Clear();

	// Format: Song Title => Intensity Level
	m_AmbushSongs = {
		{"Ambience", 2},
		{"Tension", 3},
		{"Sneaking Around", 4},
		{"Action", 5},
		{"Drive", 7},
		{"Low Earth Orbit", 8},
		{"Moracco",	9},
		{"Trains", 10},
	};

	m_BaDeDumSongs = {
		{ "Ambience", 2 },
		{ "Slow Vibes 1", 3 },
		{ "Slow Vibes 2", 21 },
		{ "Slow Drums 1", 4 },
		{ "Slow Drums 2", 22 },
		{ "Exploring Vibes 1", 5 },
		{ "Exploring Vibes 2", 17 },
		{ "Exploring Vibes 3", 23 },
		{ "Exploring Drums 1", 6 },
		{ "Exploring Drums 2", 24 },
		{ "Sneaking Around", 20 },
		{ "Action 1", 7 },
		{ "Action 2", 25 },
		{ "Orchestral Exploring", 10 },
		{ "Orchestral Ambience", 11 },
		{ "Orchestral Action", 18 },
		{ "Oompaa", 26 }
	};

	m_BadGuysSongs = {
		{ "Sub Ambience", 2 },
		{ "Ambience", 4 },
		{ "Swing", 6 },
		{ "Rock & Bepop", 9 },
		{ "Action Cinema", 14 }
	};

	m_OrchestralSongs = {
		{ "Ambience",  5 },
		{ "Tension",  4 },
		{ "Exploring",  6 },
		{ "Action",  2 }
	};

	m_MainThemeSongs = {
		{ "Sub Ambience", 2 },
		{ "Slow Going", 4 },
		{ "Main Theme", 5 },
		{ "Action", 6 },
		{ "Exploring Vibes", 12 },
		{ "Sneaking Around", 14 }
	};

	m_GOTYSongs = {
		{ "Normal", 1 },
		{ "Ambience", 2 },
		{ "Searching", 3 },
		{ "Investigate", 5 },
		{ "Combat", 7 }
	};
}

CFolderJukebox::~CFolderJukebox()
{
	m_AmbushSongs.clear();
	m_BaDeDumSongs.clear();
	m_BadGuysSongs.clear();
	m_OrchestralSongs.clear();
	m_MainThemeSongs.clear();
	m_GOTYSongs.clear();
}

LTBOOL CFolderJukebox::Build()
{
	CreateTitle("Jukebox");

	rcSongListRect = g_pLayoutMgr->GetFolderCustomRect((eFolderID)m_nFolderID, "SongListRect");
	nArrowWidth = g_pLayoutMgr->GetFolderCustomInt((eFolderID)m_nFolderID, "ArrowWidth");
	nIndent = g_pLayoutMgr->GetFolderCustomInt((eFolderID)m_nFolderID, "TextIndent");

	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_JUKEBOX, "ColumnWidth"))
		kGap = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_JUKEBOX, "ColumnWidth");
	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_JUKEBOX, "SliderWidth"))
		kWidth = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_JUKEBOX, "SliderWidth");

	LTFLOAT yr = g_pInterfaceResMgr->GetYRatio();
	kGap *= yr;


	AddTextItem("Themes", 0, 0, 0, GetLargeFont());
	AddTextItem("Ambush", PLAY_AMBUSH, 0, 0, GetMediumFont());
	AddTextItem("Ba De Dum", PLAY_BADEDUM, 0, 0, GetMediumFont());
	AddTextItem("Bad Guys", PLAY_BADGUY, 0, 0, GetMediumFont());
	AddTextItem("Orchestra", PLAY_NOLFORCH, 0, 0, GetMediumFont());
	AddTextItem("Main Theme", PLAY_NOLFTHEME, 0, 0, GetMediumFont());
	AddTextItem("Game Of The Year", PLAY_GOTY, 0, 0, GetMediumFont());

#if 1
	LTIntPt pos;
	int nBarHeight = GetMediumFont()->GetHeight();

	//Add PlayerList Here
	pos.x = rcSongListRect.left + nIndent;
	pos.y = rcSongListRect.top + nBarHeight;
	nListHeight = (rcSongListRect.bottom - rcSongListRect.top) - nBarHeight;
	nListHeight += 24;	// [blg] tweak
	nListWidth = (rcSongListRect.right - rcSongListRect.left) - nArrowWidth;

	int nListHeight = 400;
	int nListWidth = 200;
	m_SongListCtrl = debug_new(CListCtrl);
	m_SongListCtrl->Create(nListHeight, LTTRUE, nListWidth);
	m_SongListCtrl->SetParam1(nListWidth);
	m_SongListCtrl->SetItemSpacing(2);
	m_SongListCtrl->EnableMouseMoveSelect(LTTRUE);
	m_SongListCtrl->SetHelpID(0);
	AddFixedControl(m_SongListCtrl, pos, LTTRUE);
#endif

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
	case PLAY_SONG:
	{
		UpdateData(LTTRUE);

		CStaticTextCtrl* pCtrl = (CStaticTextCtrl*)m_SongListCtrl->GetSelectedControl();
		std::string key = g_pLTClient->GetStringData(pCtrl->GetString());

		m_sCurrentSong = key;

		int intensity = (*m_CurrentSongList).at(key);
		g_pGameClientShell->GetMusic()->Play(intensity);

		UpdateHelpText();

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

		m_sCurrentSong = "";

		// Store the current music state, so we can restore when they leave!
		m_PreviousMusicState = *g_pGameClientShell->GetMusic()->GetMusicState();
		
		CBaseFolder::OnFocus(bFocus);
		return;
	}

	// Leave
	UpdateData(LTTRUE);

	// Restore the music that was playing before they entered this menu.
	g_pGameClientShell->GetMusic()->RestoreMusicState(m_PreviousMusicState);


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
		m_CurrentSongList = &m_AmbushSongs;
		break;
	case PLAY_BADEDUM:
		directory += "BADEDUM";
		controlFile = "BADEDUM.txt";
		m_CurrentSongList = &m_BaDeDumSongs;
		break;
	case PLAY_BADGUY:
		directory += "BADGUY";
		controlFile = "BADGUY.txt";
		m_CurrentSongList = &m_BadGuysSongs;
		break;
	case PLAY_NOLFORCH:
		directory += "NOLFORCH";
		controlFile = "NOLFORCH.txt";
		m_CurrentSongList = &m_OrchestralSongs;
		break;
	case PLAY_NOLFTHEME:
		directory += "NOLFTHEME";
		controlFile = "NOLFTHEME.txt";
		m_CurrentSongList = &m_MainThemeSongs;
		break;
	case PLAY_GOTY:
		directory += "GOTY";
		controlFile = "GOTY.txt";
		m_CurrentSongList = &m_GOTYSongs;
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

	// Update the song list based on the newly selected theme!
	m_SongListCtrl->RemoveAllControls();
	std::map<std::string, int>::iterator it = (*m_CurrentSongList).begin();
	while (it != (*m_CurrentSongList).end()) {

		// Add the string to the control
		HSTRING hTemp = g_pLTClient->CreateString((char*)it->first.c_str());

		CStaticTextCtrl* pCtrl = CreateStaticTextItem((char*)(LPCTSTR)(it->first.c_str()), PLAY_SONG, LTNULL, 200, GetMediumFont()->GetHeight(), LTFALSE, GetMediumFont());
		
		m_SongListCtrl->AddControl(pCtrl);

		// Free the strings
		g_pLTClient->FreeString(hTemp);
		it++;
	}

	return LTTRUE;
}

void CFolderJukebox::UpdateHelpText()
{
	// Force Help Text to render!
	m_dwCurrHelpID = 1;

	// Build out string
	std::string nowPlaying = "Now Playing: " + m_sCurrentSong;
	HSTRING hHelpTxt = g_pLTClient->CreateString((char*)nowPlaying.c_str());

	int nWidth = m_HelpRect.right - m_HelpRect.left;
	int nHeight = m_HelpRect.bottom - m_HelpRect.top;

	// Setup the rect!
	LTRect rect(0, 0, nWidth, nHeight);
	g_pLTClient->FillRect(m_hHelpSurf, &rect, kBlack);

	GetHelpFont()->DrawFormat(hHelpTxt, m_hHelpSurf, 0, 0, (uint32)nWidth, kWhite);
	g_pLTClient->OptimizeSurface(m_hHelpSurf, kBlack);
	g_pLTClient->FreeString(hHelpTxt);
}
