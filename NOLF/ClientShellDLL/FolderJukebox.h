#pragma once
#include "BaseFolder.h"

class CFolderJukebox : public CBaseFolder
{
public:
	CFolderJukebox();
	virtual ~CFolderJukebox();

	// Build the folder
	LTBOOL   Build();
	uint32 OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2);
	void    OnFocus(LTBOOL bFocus);
	virtual void	UpdateHelpText();

protected:

	LTBOOL PlayScore(int scoreId);

	CMusicState m_PreviousMusicState;

	CListCtrl* m_SongListCtrl;

	std::string m_sCurrentSong;
	std::map<std::string, int>* m_CurrentSongList;

	// I'm just going to hardcode these to make it easier for myself
	std::map<std::string, int> m_AmbushSongs;
	std::map<std::string, int> m_BaDeDumSongs;
	std::map<std::string, int> m_BadGuysSongs;
	std::map<std::string, int> m_OrchestralSongs;
	std::map<std::string, int> m_MainThemeSongs;
	std::map<std::string, int> m_GOTYSongs;

	std::vector<int> m_ThemeIDsToSkip;

	std::vector< std::map<std::string, int> > m_Songs;

private:

};

