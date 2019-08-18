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

typedef struct {
	LTRect dims;
	HLTCOLOR colour;
} CacheOption;

class COptimizedRenderer  
{
public:
	COptimizedRenderer();
	virtual ~COptimizedRenderer();

	void Init();
	void Term();
	
	// Faster FillRects
	void 	FillRect(HSURFACE hDestSurf, LTRect *rect, HLTCOLOR colour);
private:
	std::unordered_map<size_t, HSURFACE> m_CachedSurface;

	unsigned int GetHashValue(CacheOption);

	// Thanks SO: https://stackoverflow.com/a/27952689
	inline size_t HashCombine(size_t lhs, size_t rhs) {
		lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
		return lhs;
	}

	bool m_bInit;
};

#endif // !defined(AFX_OPTIMIZEDRENDERER_H__9487B0C0_46BD_445E_8298_032B29411A45__INCLUDED_)
