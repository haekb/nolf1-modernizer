#include "stdafx.h"
#include "ScalableBitmapCtrl.h"
#include "OptimizedRenderer.h"
#include "SDL.h"
namespace
{
	const int kHighlightWidth = 2;
}
CScalableBitmapCtrl::CScalableBitmapCtrl()
{
	m_iScaleX = 1;
	m_iScaleY = 1;
	
}


CScalableBitmapCtrl::~CScalableBitmapCtrl()
{
	Destroy();
}

/*
LTBOOL CScalableBitmapCtrl::OnMouseMove(int x, int y)
{
	LTIntPt scaled = { m_pos.x + (m_nNormalWidth * m_iScaleX), m_pos.y + (m_nNormalHeight * m_iScaleY) };
	LTRect destRect = { m_pos.x, m_pos.y, scaled.x, scaled.y };
	LTBOOL inRect = x >= destRect.left
		&& x <= destRect.right
		&& y >= destRect.top
		&& y <= destRect.bottom;
	
	return inRect;
}
*/
// Render the control
void CScalableBitmapCtrl::Render(HSURFACE hDestSurf)
{
	// Hack Alert: 
	// Right now we only use scalable bitmaps for arrow/resolution purposes, so this is okaaay.
	SetScale(g_pInterfaceResMgr->GetYRatio(), g_pInterfaceResMgr->GetYRatio());

	m_hTrans = SETRGB(255, 0, 255);
	int state = GetState();
	LTIntPt scaled = { m_pos.x + GetWidth(), m_pos.y + GetHeight() };
	LTRect destRect = { m_pos.x, m_pos.y, scaled.x, scaled.y };

	//g_pOptimizedRenderer->FillRect(hDestSurf, &destRect, kWhite);
	//return;
	if ((state == LGCS_DISABLED || !m_bEnabled) && m_sDisabledSurface[0])
	{
		m_pClientDE->ScaleSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sDisabledSurface), &destRect, LTNULL, m_hTrans);
	}
	else if (state == LGCS_SELECTED && m_sSelectedSurface[0])
	{
		m_pClientDE->ScaleSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sSelectedSurface), &destRect, LTNULL, m_hTrans);
	}

	else
	{
		//		if (state == LGCS_SELECTED)
		//		{
		//          LTRect rect = {m_pos.x-2,m_pos.y-2,m_pos.x+m_nNormalWidth+2,m_pos.y+m_nNormalHeight+2};
		//          g_pLTClient->FillRect(hDestSurf,&rect,SETRGB(255,255,255));
		//		}
		m_pClientDE->ScaleSurfaceToSurfaceTransparent(hDestSurf, g_pInterfaceResMgr->GetSharedSurface(m_sNormalSurface), &destRect, LTNULL, m_hTrans);

#if 0 // TODO: Not sure what this does?
		if (state == LGCS_SELECTED)
		{
			//left
			LTRect rectL(m_pos.x, m_pos.y, m_pos.x + kHighlightWidth, m_pos.y + m_nNormalHeight);

			//top
			LTRect rectT(m_pos.x, m_pos.y, m_pos.x + m_nNormalWidth, m_pos.y + kHighlightWidth);

			//right
			LTRect rectR(m_pos.x + m_nNormalWidth - kHighlightWidth, m_pos.y, m_pos.x + m_nNormalWidth, m_pos.y + m_nNormalHeight);

			//bottom
			LTRect rectB(m_pos.x, m_pos.y + m_nNormalHeight - kHighlightWidth, m_pos.x + m_nNormalWidth, m_pos.y + m_nNormalHeight);

			g_pOptimizedRenderer->FillRect(hDestSurf, &rectL, kWhite);
			g_pOptimizedRenderer->FillRect(hDestSurf, &rectT, kWhite);
			g_pOptimizedRenderer->FillRect(hDestSurf, &rectR, kWhite);
			g_pOptimizedRenderer->FillRect(hDestSurf, &rectB, kWhite);
		}
#endif
	}

}


// Width/Height calculations
int CScalableBitmapCtrl::GetWidth()
{
	int state = GetState();
	if (state == LGCS_SELECTED && m_sSelectedSurface[0])
	{
		return m_nSelectedWidth * m_iScaleX;
	}
	else if (state == LGCS_DISABLED && m_sDisabledSurface[0])
	{
		return m_nDisabledWidth * m_iScaleX;
	}
	else
	{
		return m_nNormalWidth * m_iScaleX;
	}

}

int CScalableBitmapCtrl::GetHeight()
{
	int state = GetState();
	if (state == LGCS_SELECTED && m_sSelectedSurface[0])
	{
		return m_nSelectedHeight * m_iScaleY;
	}
	else if (state == LGCS_DISABLED && m_sDisabledSurface[0])
	{
		return m_nDisabledHeight * m_iScaleY;
	}
	else
	{
		return m_nNormalHeight * m_iScaleY;
	}

}