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

	Init();
}

COptimizedRenderer::~COptimizedRenderer()
{
	// The game will clean the surfaces up.
	// Not the best solution, but there's not too many FillRects, 
	// and this class dies with the game.
	g_pOptimizedRenderer = LTNULL;

	Term();
}

void COptimizedRenderer::Init()
{
	//
}

void COptimizedRenderer::Term()
{
	std::unordered_map<size_t, HSURFACE>::iterator it = m_CachedSurface.begin();
	while (it != m_CachedSurface.end()) {
		g_pLTClient->DeleteSurface(it->second);
		it = m_CachedSurface.erase(it);
	}
}

// Faster FillRect, we do basically a FillRect once, and then cache that result.
void COptimizedRenderer::FillRect(HSURFACE hDestSurf, LTRect *rect, HLTCOLOR colour)
{
	HSURFACE hSurf = LTNULL;
	CacheOption options = {
		*rect,
		colour
	};

	size_t result = GetHashValue(options);
	
	auto item = m_CachedSurface.find(result);

	// Not found
	if (item == m_CachedSurface.end())
	{
		SDL_Log("Cache Miss for <%u>", result);
		int width = rect->right - rect->left;
		int height = rect->bottom - rect->top;

		// Create our (to be) cached surface, and FillRect on that.
		hSurf = g_pLTClient->CreateSurface(width, height);
			
		LTRect dims = { 0, 0, width, height };

		g_pLTClient->FillRect(hSurf, &dims, colour);

		// Cache our result
		m_CachedSurface.insert({ result, hSurf });
	}
	else {
		// Grab the surface
		hSurf = item->second;
	}

	if (!hDestSurf || !hSurf) {
		return;
	}

	g_pLTClient->DrawSurfaceToSurface(hDestSurf, hSurf, NULL, rect->left, rect->top);
}

// TODO: Make this better...
unsigned int COptimizedRenderer::GetHashValue(CacheOption options)
{
	std::hash<uint32> hasher;
	size_t hash;
	hash = HashCombine(hasher(options.dims.top), hasher(options.dims.left));
	hash = HashCombine(hash, hasher(options.dims.bottom));
	hash = HashCombine(hash, hasher(options.dims.right));
	return HashCombine(hash, hasher(options.colour));

}

