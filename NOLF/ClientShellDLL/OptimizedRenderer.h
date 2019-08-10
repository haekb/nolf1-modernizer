// OptimizedRenderer.h: interface for the OptimizedRenderer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIMIZEDRENDERER_H__9487B0C0_46BD_445E_8298_032B29411A45__INCLUDED_)
#define AFX_OPTIMIZEDRENDERER_H__9487B0C0_46BD_445E_8298_032B29411A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL.h"
#include "iltclient.h"
#include "ltbasedefs.h"


class COptimizedRenderer;
extern COptimizedRenderer* g_pOptimizedRenderer;

class COptimizedRenderer  
{
public:
	COptimizedRenderer();
	virtual ~COptimizedRenderer();

	void Init();
	
	// Faster FillRects
	void 	FillRect(HSURFACE hDestSurf, LTRect *rect, HLTCOLOR colour);
	//void 	FillRectTrans(HSURFACE hDestSurf, LTRect *rect, HLTCOLOR colour);
private:
	// It could be anything!
	HSURFACE m_hQuantumWhite;

	// FIXME: VS6 won't let me use a map, so if you have a better way to handle an assoc array, PR it!
	CMoArray<HLTCOLOR>    m_CachedSurfaceKey;
	CMoArray<HSURFACE>	m_CachedSurfaceArray;
};

#endif // !defined(AFX_OPTIMIZEDRENDERER_H__9487B0C0_46BD_445E_8298_032B29411A45__INCLUDED_)
