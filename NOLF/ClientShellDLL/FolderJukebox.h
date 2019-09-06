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
	std::unordered_map<std::string, int>* m_CurrentSongList;

	// I'm just going to hardcode these to make it easier for myself
	std::unordered_map<std::string, int> m_AmbushSongs;
	std::unordered_map<std::string, int> m_BaDeDumSongs;
	std::unordered_map<std::string, int> m_BadGuysSongs;
	std::unordered_map<std::string, int> m_OrchestralSongs;
	std::unordered_map<std::string, int> m_MainThemeSongs;
	std::unordered_map<std::string, int> m_GOTYSongs;

private:

};

