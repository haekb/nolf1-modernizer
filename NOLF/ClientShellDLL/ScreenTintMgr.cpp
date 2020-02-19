// ----------------------------------------------------------------------- //
//
// MODULE  : ScreenTintMgr.cpp
//
// PURPOSE : Implementation of ScreenTintMgr class
//
// CREATED : 02/02/00
//
// (c) 2000 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //

#include "stdafx.h"
#include "screentintmgr.h"
#include "GameClientShell.h"
extern CGameClientShell* g_pGameClientShell;
extern VarTrack g_vtEnableScreenTint;

CScreenTintMgr::CScreenTintMgr()
{
	for (int i = 0; i < NUM_TINT_EFFECTS; i++)
	{
		m_avTints[i].Init(0.0f,0.0f,0.0f);
	}
    m_bChanged = LTFALSE;
	m_hAltSurface = LTNULL;
	m_nAltSurfaceWidth = -1;
	m_nAltSurfaceHeight = -1;
}

CScreenTintMgr::~CScreenTintMgr()
{
}

void CScreenTintMgr::Update()
{
	if (!m_bChanged) {
		return;
	}

    LTVector vTemp;
	vTemp.Init(0.0f,0.0f,0.0f);
	for (int i = 0; i < NUM_TINT_EFFECTS; i++)
	{
		vTemp.x = Max(vTemp.x,m_avTints[i].x);
		vTemp.y = Max(vTemp.y,m_avTints[i].y);
		vTemp.z = Max(vTemp.z,m_avTints[i].z);
	}

	if (vTemp.x > 1.0f)
		vTemp.x = 1.0f;
	if (vTemp.y > 1.0f)
		vTemp.y = 1.0f;
	if (vTemp.z > 1.0f)
		vTemp.z = 1.0f;
    m_bChanged = LTFALSE;

	auto hScreen = g_pLTClient->GetScreenSurface();
	LTBOOL bEnableScreenTint = g_vtEnableScreenTint.GetFloat();

	// This can probably be rolled into optimized renderer...
	// But re-working the caching for OR would be annoying, so it's here.
	if (!bEnableScreenTint) {

		// Trash the old surface
		if (m_hAltSurface) {
			g_pLTClient->DeleteSurface(m_hAltSurface);
			m_hAltSurface = LTNULL;
		}

		uint32 nWidth, nHeight;

		g_pLTClient->GetSurfaceDims(hScreen, &nWidth, &nHeight);

		// Create a small surface so when the surface is optimized it won't drain our framerate!
		m_hAltSurface = g_pLTClient->CreateSurface(8, 8);

		LTRect rDest = { 0, 0, (int)nWidth, (int)nHeight };

		// Colours were normalized, un-normalize them...re-normalize?...255-ify them.
		HLTCOLOR hColour = SETRGB(vTemp.x * 255, vTemp.y * 255, vTemp.z * 255);

		g_pLTClient->FillRect(m_hAltSurface, &rDest, hColour);
		g_pLTClient->SetSurfaceAlpha(m_hAltSurface, 1.0f);

		m_nAltSurfaceWidth = nWidth;
		m_nAltSurfaceHeight = nHeight;

		return;
	}

	HLOCALOBJ hCamera = g_pGameClientShell->GetCamera();
    g_pLTClient->SetCameraLightAdd(hCamera, &vTemp);

}

void CScreenTintMgr::Set(eTintEffect eEffect, LTVector *pvColor)
{
    m_bChanged = LTTRUE;
	VEC_COPY(m_avTints[eEffect],*pvColor);
}

void CScreenTintMgr::Clear(eTintEffect eEffect)
{
    m_bChanged = LTTRUE;
	VEC_SET(m_avTints[eEffect],0.0f,0.0f,0.0f);
}

void CScreenTintMgr::ClearAll()
{
	for (int i = 0; i < NUM_TINT_EFFECTS; i++)
	{
		Clear((eTintEffect)i);
	}
}