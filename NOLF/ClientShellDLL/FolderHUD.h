#pragma once
#include "BaseFolder.h"

class CFolderHUD : public CBaseFolder
{
public:
	CFolderHUD();
	virtual ~CFolderHUD();

	// Build the folder
	LTBOOL   Build();
	void    OnFocus(LTBOOL bFocus);


protected:

	//uint32  OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2);

protected:
	// 1.0 based - For the actual command
	float							m_fUIScale;
	// 100 based - For the silly UI slider
	int								m_nUIScale;
	LTBOOL							m_bUseGOTYMenu;
	LTBOOL							m_bLockFramerate;
	LTBOOL							m_bShowFramerate;
	LTBOOL							m_bRestrictAspectRatio;
};

