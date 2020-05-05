#pragma once
#include "GameButeMgr.h"
#include "ltbasetypes.h"
#include "iltcsbase.h"
#include <string>

//
// Contains all the jukebox songs!
//

class CJukeboxButeMgr;
extern CJukeboxButeMgr* g_pJukeboxButeMgr;

class CJukeboxButeMgr :
	public CGameButeMgr
{
public:
	CJukeboxButeMgr();
	~CJukeboxButeMgr();

	LTBOOL       Init(ILTCSBase* pInterface, const char* szAttributeFile = "Attributes\\Jukebox.txt");
	void		Term();

	int			GetNumThemes() { return m_nThemeIDCount; }

	// Themes
	CString		GetThemeName(int nThemeID);
	CString		GetThemeDirectory(int nThemeID);
	CString		GetThemeControlFile(int nThemeID);
	bool		GetThemeRequiresGOTY(int nThemeID);

	// Songs
	CString		GetSongName(int nSongID);
	int			GetSongIntensityLevel(int nSongID);
	int			GetThemeID(int nSongID);

private:

	int m_nThemeIDCount;
	int m_nSongIDCount;

};

