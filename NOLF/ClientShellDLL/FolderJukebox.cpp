#include "stdafx.h"
#include "FolderJukebox.h"
#include "FolderMgr.h"
#include "FolderCommands.h"
#include "ClientRes.h"

#include "GameClientShell.h"
#include "GameSettings.h"
#include "VersionMgr.h"
#include <string>

#include "JukeboxButeMgr.h"
namespace
{
	int kGap = 0;
	int kWidth = 0;
	LTRect rcSongListRect;
	int nListHeight = 0;
	int nListWidth = 0;
	int nArrowWidth = 0;
	int nIndent = 0;

	// FOLDER_CMD_CUSTOM ... FOLDER_CMD_CUSTOM + 500
	// are dedicated for themes

	// Just bump this up to not conflict with the attribute file
	const int PLAY_SONG = (FOLDER_CMD_CUSTOM + 500);
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

	// FIXME: Localize meeeee
	AddTextItem("Themes", 0, 0, 0, GetLargeFont());

	int nThemeCount = g_pJukeboxButeMgr->GetNumThemes();

	for (int i = 0; i < nThemeCount; i++)
	{
		auto sName = g_pJukeboxButeMgr->GetThemeName(i);
		auto bRequiresGOTY = g_pJukeboxButeMgr->GetThemeRequiresGOTY(i);

		// If this theme requires GOTY, and we don't have the GOTY files...don't include it.
		// Would just crash the game!
		if (bRequiresGOTY && !g_pVersionMgr->IsGOTY())
		{
			// We'll need this info later..
			m_ThemeIDsToSkip.push_back(i);
			continue;
		}

		AddTextItem(sName.GetBuffer(), FOLDER_CMD_CUSTOM + i, 0, 0, GetMediumFont());

		// Let's start off a map, 
		// because everything here is pretty static we can safely assume the position in the vector relates to the theme id.
		// Sorry for anyone who has to change this...(But also like why?)
		std::map<std::string, int> SongMap;
		m_Songs.push_back(SongMap);
	}

	int nSongCount = g_pJukeboxButeMgr->GetNumSongs();

	for (int i = 0; i < nSongCount; i++)
	{
		auto sName = g_pJukeboxButeMgr->GetSongName(i);
		auto nIntensityLevel = g_pJukeboxButeMgr->GetSongIntensityLevel(i);
		auto nThemeID = g_pJukeboxButeMgr->GetSongThemeID(i);

		// If the ID is in the "to skip" list, then skip this song!
		// This is needed if the player doesn't have the required files installed.
		if (std::find(m_ThemeIDsToSkip.begin(), m_ThemeIDsToSkip.end(), nThemeID) != m_ThemeIDsToSkip.end())
		{
			continue;
		}

		// Insert the song into its proper theme map.
		m_Songs[nThemeID].insert( std::pair<std::string, int>(sName, nIntensityLevel) );
	}

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

	// Make sure to call the base class
	if (!CBaseFolder::Build()) return LTFALSE;

	UseBack(LTTRUE, LTTRUE);

	return LTTRUE;
}


uint32 CFolderJukebox::OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2)
{
	if (dwCommand >= FOLDER_CMD_CUSTOM && dwCommand < (FOLDER_CMD_CUSTOM + m_Songs.size()) )
	{
		return PlayScore(dwCommand);
	}
	else if (dwCommand == PLAY_SONG)
	{
		UpdateData(LTTRUE);

		CStaticTextCtrl* pCtrl = (CStaticTextCtrl*)m_SongListCtrl->GetSelectedControl();
		std::string key = g_pLTClient->GetStringData(pCtrl->GetString());

		m_sCurrentSong = key;

		int intensity = (*m_CurrentSongList).at(key);
		g_pGameClientShell->GetMusic()->Play(intensity);

		UpdateHelpText();

		return 1;
	}

	return CBaseFolder::OnCommand(dwCommand, dwParam1, dwParam2);
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
	// excuse my mixed naming convetion here...
	std::string directory = "Music\\";
	std::string controlFile;

	int nThemeID = scoreId - FOLDER_CMD_CUSTOM;

	// Make doubly sure we're not trying to access a theme we don't have the files for!
	if (std::find(m_ThemeIDsToSkip.begin(), m_ThemeIDsToSkip.end(), nThemeID) != m_ThemeIDsToSkip.end())
	{
		return LTFALSE;
	}

	auto sDirectory = g_pJukeboxButeMgr->GetThemeDirectory(nThemeID);
	auto sControlFile = g_pJukeboxButeMgr->GetThemeControlFile(nThemeID);

	m_CurrentSongList = &m_Songs[nThemeID];
	directory += sDirectory.GetBuffer();
	controlFile = sControlFile.GetBuffer();

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
