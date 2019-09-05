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


protected:

	LTBOOL PlayScore(int scoreId);

	//uint32  OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2);

	int m_nIntensityLevel;

private:

};

