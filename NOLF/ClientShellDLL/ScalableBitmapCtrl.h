#pragma once

#include "LTGUIMgr.h"
#include "stdlith.h"
#include "BitmapCtrl.h"

#define SCALABLE_BITMAP_ID 1337

class CScalableBitmapCtrl :
	public CBitmapCtrl
{
public:
	CScalableBitmapCtrl();
	~CScalableBitmapCtrl();

	LTBOOL   Create(ILTClient* pClientDE, char* lpszNormalBmp, char* lpszSelectedBmp = NULL, char* lpszDisabledBmp = NULL,
		CLTGUICommandHandler* pCommandHandler = LTNULL, uint32 dwCommandID = LTNULL, uint32 dwParam1 = 0, uint32 dwParam2 = 0);

	virtual void Render(HSURFACE hDestSurf);

	void SetScale(int x, int y) { m_iScaleX = x; m_iScaleY = y; };
	
	// Width/Height calculations
	virtual int		GetWidth();
	virtual int		GetHeight();

protected:
	int m_iScaleX;
	int m_iScaleY;
};

