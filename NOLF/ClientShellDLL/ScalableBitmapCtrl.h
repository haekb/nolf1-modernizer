#pragma once

#include "LTGUIMgr.h"
#include "stdlith.h"
#include "BitmapCtrl.h"

class CScalableBitmapCtrl :
	public CBitmapCtrl
{
public:
	CScalableBitmapCtrl();
	~CScalableBitmapCtrl();

	virtual void Render(HSURFACE hDestSurf);

	void SetScale(int x, int y) { m_iScaleX = x; m_iScaleY = y; };
	
	// Width/Height calculations
	virtual int		GetWidth();
	virtual int		GetHeight();

protected:
	int m_iScaleX;
	int m_iScaleY;
};

