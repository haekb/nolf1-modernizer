// OptimizedRenderer.cpp: implementation of the OptimizedRenderer class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "OptimizedRenderer.h"

COptimizedRenderer* g_pOptimizedRenderer = LTNULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptimizedRenderer::COptimizedRenderer()
{
	g_pOptimizedRenderer = this;
	m_hQuantumWhite = LTNULL;
}

COptimizedRenderer::~COptimizedRenderer()
{
	// The game will clean the surfaces up.
	// Not the best solution, but there's not too many FillRects, 
	// and this class dies with the game.
	if (m_hQuantumWhite)
	{
		g_pInterfaceResMgr->FreeSharedSurface(m_hQuantumWhite);
		m_hQuantumWhite = LTNULL;
	}

	g_pOptimizedRenderer = LTNULL;
}

void COptimizedRenderer::Init()
{
	m_hQuantumWhite = g_pInterfaceResMgr->GetSharedSurface("interface\\QuantumWhite.pcx");
	SDL_Log("Optimized Renderer Intialized");
}

// Faster FillRect, we do basically a FillRect once, and then cache that result.
void COptimizedRenderer::FillRect(HSURFACE hDestSurf, LTRect *rect, HLTCOLOR colour)
{
	HSURFACE hSurf = LTNULL;
	int index = m_CachedSurfaceKey.FindElement(colour);

	if(index == BAD_INDEX) {
		SDL_Log("Cache Miss for <%d>", colour);

		hSurf = g_pLTClient->CreateSurface(32,32);
		g_pLTClient->FillRect(hSurf, LTNULL, colour);

		m_CachedSurfaceKey.Add(colour);
		m_CachedSurfaceArray.Add(hSurf);
	} else {
		hSurf = m_CachedSurfaceArray.GetAt(index);
	}

	g_pLTClient->ScaleSurfaceToSurface(hDestSurf, hSurf, rect, LTNULL);
}
