// InterfaceResMgr.cpp: implementation of the CInterfaceResMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientRes.h"
#include "gameclientshell.h"
#include "InterfaceResMgr.h"
#include "ClientButeMgr.h"
#include "SDL.h"
#include "ConsoleMgr.h"
#include "FontMgr.h"

CInterfaceResMgr*   g_pInterfaceResMgr = LTNULL;
extern SDL_Window* g_SDLWindow;
extern ConsoleMgr* g_pConsoleMgr;
extern FontMgr* g_pFontMgr;

namespace
{
	char g_szFontName[128];
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterfaceResMgr::CInterfaceResMgr()
{
	g_pInterfaceResMgr = this;

	m_hSurfLoading	 = NULL;
	m_hSurfCursor = NULL;
	m_hTransColor = SETRGB(255,0,255);

    m_pTitleFont = LTNULL;
    m_pLargeFont = LTNULL;
    m_pMediumFont = LTNULL;
    m_pSmallFont = LTNULL;
    m_pHelpFont = LTNULL;

    m_pMsgForeFont = LTNULL;
    m_pHUDForeFont = LTNULL;
    m_pAirFont = LTNULL;
    m_pChooserFont = LTNULL;

	m_Offset.x =  -1;
	m_Offset.y =  -1;

	m_dwScreenWidth = -1;
	m_dwScreenHeight = -1;

	m_fXRatio = 1.0f;
	m_fYRatio = 1.0f;

	m_fUserScale = 0.50;

	m_bFontsSetup = LTFALSE;

}

CInterfaceResMgr::~CInterfaceResMgr()
{
    g_pInterfaceResMgr = LTNULL;
}

//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::Init
// Description	    :
// Return type      : LTBOOL
// Argument         : ILTClient* pClientDE
// Argument         : CGameClientShell* pClientShell
//////////////////////////////////////////////////////////////////////
LTBOOL CInterfaceResMgr::Init(ILTClient* pClientDE, CGameClientShell* pClientShell)
{
	if (!pClientDE)
	{
        return LTFALSE;
	}

    HSTRING hString;

	// Set the English flag
    hString = g_pLTClient->FormatString(IDS_GAME_LANGUAGE);
    if (hString && _mbsicmp((const unsigned char*)"english", (const unsigned char*)g_pLTClient->GetStringData(hString)) != 0)
    {
        m_bEnglish=LTFALSE;
	}
	else
    {
        m_bEnglish=LTTRUE;
	}
    g_pLTClient->FreeString(hString);
    hString=LTNULL;

	// Load the virtual key codes for yes responses
    hString=g_pLTClient->FormatString(IDS_MENU_VKEY_YES);
	if (hString)
	{
        m_nYesVKeyCode=atoi(g_pLTClient->GetStringData(hString));
        g_pLTClient->FreeString(hString);
        hString=LTNULL;
	}

	// Load the virtual key codes for no responses
    hString=g_pLTClient->FormatString(IDS_MENU_VKEY_NO);
	if (hString)
	{
        m_nNoVKeyCode=atoi(g_pLTClient->GetStringData(hString));
        g_pLTClient->FreeString(hString);
        hString=LTNULL;
	}

	// Init the InterfaceSurfMgr class
    m_InterfaceSurfMgr.Init(g_pLTClient);

	// set resolution dependant variables
	ScreenDimsChanged();

	// Init font stuff here!
	FontMgr* pFontMgr = new FontMgr();
	pFontMgr->Init();

	// This now includes InitFonts
	if (!SetupScaleFonts()) {
		return LTFALSE;
	}

	g_pConsoleMgr->Init();

	HandleBorderlessWindowed();

	m_fUserScale = GetConfigFloat("UIScale", 0.5f);

    return LTTRUE;
}

//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::Term
// Description	    :
// Return type		: void
//////////////////////////////////////////////////////////////////////

void CInterfaceResMgr::Term()
{
	Clean();

	// Terminate the InterfaceSurfMgr class
	m_InterfaceSurfMgr.Term();

	if (m_hSurfCursor)
	{
        g_pLTClient->DeleteSurface(m_hSurfCursor);
		m_hSurfCursor = NULL;
	}

	TermFonts();
}

//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::Setup
// Description	    :
// Return type      : LTBOOL
//////////////////////////////////////////////////////////////////////

LTBOOL CInterfaceResMgr::Setup()
{
	//preload common surfaces

    return LTTRUE;
}

//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::Clean
// Description	    :
// Return type		: void
//////////////////////////////////////////////////////////////////////

void CInterfaceResMgr::Clean()
{
    if (g_pLTClient)
	{
		if (m_hSurfLoading)
		{
            g_pLTClient->DeleteSurface(m_hSurfLoading);
			m_hSurfLoading = NULL;
		}

		// free shared surfaces
		m_InterfaceSurfMgr.FreeAllSurfaces();


	}
}

//
// Loads TTFs and exports the approiately scaled PCXs
//
LTBOOL CInterfaceResMgr::SetupScaleFonts()
{
	//TermFonts();

	// If we're not using scale fonts, we don't need to do this setup
	if (!g_pGameClientShell->UseScaleFonts()) {

		return InitFonts();
	}

	// Initialize some font magic here
	char szFontName[128];
	std::string sFileName = "";

	float nResolutionRatio = (GetYRatio() * 0.75f);
	int nLarge = (int) ((LTFLOAT)20 * nResolutionRatio);
	int nMedium = (int) ((LTFLOAT)14 * nResolutionRatio);
	int nSmall = (int)((LTFLOAT)10 * nResolutionRatio);

	// Cap the font size so we don't exceed 2000 pixels in width
	// Might need to pack my own d3dim700.dll to fix this...
	nLarge = min(30, nLarge);
	nMedium = min(30, nMedium);
	nSmall = min(30, nSmall);

#if 1
	g_pLayoutMgr->GetHelpFont(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nSmall, sFileName);

	g_pLayoutMgr->GetTitleFont(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721KN.TTF", nLarge, sFileName);

	g_pLayoutMgr->GetLargeFontBase(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nLarge, sFileName);

	g_pLayoutMgr->GetMediumFontBase(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nMedium, sFileName);

	g_pLayoutMgr->GetSmallFontBase(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nSmall, sFileName);

	g_pLayoutMgr->GetHUDForeFont(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nMedium, sFileName);

	g_pLayoutMgr->GetMsgForeFont(szFontName, sizeof(szFontName));
	sFileName = szFontName;
	sFileName = sFileName.substr(3, sFileName.length());
	g_pFontMgr->LoadAndExport("Fonts\\SQR721B.TTF", nLarge, sFileName);
#endif

	// Initialize the fonts
	return InitFonts();

}

//////////////////////////////////////////////////////////////////////
// Function name	: CInterfaceResMgr::DrawFolder
// Description	    :
// Return type		: void
//////////////////////////////////////////////////////////////////////
void CInterfaceResMgr::DrawFolder()
{
    _ASSERT(g_pLTClient);
    if (!g_pLTClient) return;

	if (m_Offset.x < 0)
		ScreenDimsChanged();

	// The screen surface
    HSURFACE hScreen = g_pLTClient->GetScreenSurface();

	// Render the current folder
	g_pInterfaceMgr->GetFolderMgr()->Render(hScreen);

	return;
}

void CInterfaceResMgr::DrawLoadScreen()
{
    _ASSERT(g_pLTClient);
    if (!g_pLTClient) return;

	// The screen surface
    HSURFACE hScreen = g_pLTClient->GetScreenSurface();
	HSURFACE hLoad   = GetSurfaceLoading();
    uint32 dwScreenWidth=0;
    uint32 dwScreenHeight=0;
    uint32 dwLoadWidth=0;
    uint32 dwLoadHeight=0;

	_ASSERT(hLoad && hScreen);
	if (!hLoad || !hScreen) return;

	// Get the dims of the screen and the working surface
    g_pLTClient->GetSurfaceDims(hScreen, &dwScreenWidth, &dwScreenHeight);
    g_pLTClient->GetSurfaceDims(hLoad, &dwLoadWidth, &dwLoadHeight);

	// Center the image and blit it to the screen
	int nLeft=(dwScreenWidth/2)-(dwLoadWidth/2);
	int nTop=(dwScreenHeight/2)-(dwLoadHeight/2);
    g_pLTClient->DrawSurfaceToSurfaceTransparent(hScreen, hLoad, NULL, nLeft, nTop,m_hTransColor);


	return;
}

void CInterfaceResMgr::DrawFolderBars()
{
	HLTCOLOR hShadeColor = g_pLayoutMgr->GetShadeColor();
	HSURFACE hScreen = g_pLTClient->GetScreenSurface();

	int nXOffset = g_pInterfaceResMgr->GetXOffset();

	LTRect rect(0, 0, 0, 0);

	if (nXOffset > 0)
	{
		rect.left = 0;
		rect.right = nXOffset;
		rect.top = 0;
		rect.bottom = g_pInterfaceResMgr->GetScreenHeight();

		g_pOptimizedRenderer->FillRect(hScreen, &rect, hShadeColor);

		rect.left = g_pInterfaceResMgr->GetScreenWidth() - nXOffset;
		rect.right = g_pInterfaceResMgr->GetScreenWidth();
		rect.top = 0;
		rect.bottom = g_pInterfaceResMgr->GetScreenHeight();

		g_pOptimizedRenderer->FillRect(hScreen, &rect, hShadeColor);
	}
}

int CInterfaceResMgr::Get4x3Offset()
{
	/* 
		Simple formula to calculate the edges of a 4x3 resolution.
		We calculate the equivalent 4x3 resolution from our whatever resolution,
		and then subtract it from our current width. 
		That leaves us over with both sides of the edges, 
		so we then divide by 2 to get only one side. 
	*/
	return (GetScreenWidth() - (GetScreenHeight() * Get4x3Ratio())) / 2;
}

void CInterfaceResMgr::DrawMessage(CLTGUIFont* pFont, int nMessageId)
{
    _ASSERT(g_pLTClient && pFont);
    if (!g_pLTClient || !pFont) return;

	// The screen surface
    HSURFACE hScreen = g_pLTClient->GetScreenSurface();
	HSURFACE hBlank  = CreateSurfaceBlank();
	uint32 dwScreenWidth=0;
    uint32 dwScreenHeight=0;
    uint32 dwWidth=0;
    uint32 dwHeight=0;

	_ASSERT(hBlank);
	if (!hBlank) return;

	// Get the string...
    HSTRING hStr = g_pLTClient->FormatString(nMessageId);

	_ASSERT(hStr);
	if (!hStr)
	{
        g_pLTClient->DeleteSurface(hBlank);
		return;
	}

	// Get the dims of the screen and the working surface
	g_pLTClient->GetSurfaceDims(hScreen, &dwScreenWidth, &dwScreenHeight);
    g_pLTClient->GetSurfaceDims(hBlank, &dwWidth, &dwHeight);


	// Center the image and blit it to the screen
	int nLeft=(dwScreenWidth/2)-(dwWidth/2);
	int nTop=(dwScreenHeight/2)-(dwHeight/2);
    g_pLTClient->DrawSurfaceToSurfaceTransparent(hScreen, hBlank, NULL, nLeft, nTop, m_hTransColor);

    g_pLTClient->DeleteSurface(hBlank);

	// Center the string on the surface...
    LTIntPt size = pFont->GetTextExtents(hStr);
	pFont->Draw(hStr, hScreen, dwScreenWidth/2, (dwScreenHeight - size.y)/2, LTF_JUSTIFY_CENTER,kWhite);
    g_pLTClient->FreeString(hStr);

	return;
}

//
// If we're in windowed mode, and the resolution is the same as our desktop,
// then borderless windowed mode it up!
//
void CInterfaceResMgr::HandleBorderlessWindowed()
{
	// Only do this in windowed mode!
	if (GetConsoleInt("windowed", 0) == 0) {
		return;
	}

	uint32 dwScreenWidth = 0;
	uint32 dwScreenHeight = 0;
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}

	g_pLTClient->GetSurfaceDims(g_pLTClient->GetScreenSurface(), &dwScreenWidth, &dwScreenHeight);

	// If res matches our desktop, borderless it!
	if (dm.w == dwScreenWidth && dm.h == dwScreenHeight)
	{
		SDL_SetWindowFullscreen(g_SDLWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		return;
	}

	// Otherwise reset to windowed.
	SDL_SetWindowFullscreen(g_SDLWindow, 0);
}

LTBOOL CInterfaceResMgr::InitFonts()
{
	m_pSmallFont = debug_new(CLTGUIFont);
	m_pMediumFont = debug_new(CLTGUIFont);
	m_pLargeFont = debug_new(CLTGUIFont);
	m_pHelpFont = debug_new(CLTGUIFont);
	m_pTitleFont = debug_new(CLTGUIFont);
	m_pMsgForeFont = debug_new(CLTGUIFont);
	m_pHUDForeFont = debug_new(CLTGUIFont);
	m_pAirFont = debug_new(CLTGUIFont);
	m_pChooserFont = debug_new(CLTGUIFont);

	// Initialize the bitmap fonts if we are in english
	if (IsEnglish())
	{
        // ************* help font
		g_pLayoutMgr->GetHelpFont(g_szFontName,sizeof(g_szFontName));
		if (!SetupFont(m_pHelpFont))
		{
			debug_delete(m_pHelpFont);
            m_pHelpFont=LTNULL;
            return LTFALSE;
		}
        // *********** small font
		g_pLayoutMgr->GetSmallFontBase(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pSmallFont))
		{
			debug_delete(m_pSmallFont);
            m_pSmallFont=LTNULL;
            return LTFALSE;
		}

        // *********** medium font
		g_pLayoutMgr->GetMediumFontBase(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pMediumFont))
		{
			debug_delete(m_pMediumFont);
            m_pMediumFont=LTNULL;
            return LTFALSE;
		}

        // *********** Large font
		g_pLayoutMgr->GetLargeFontBase(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pLargeFont))
		{
			debug_delete(m_pLargeFont);
            m_pLargeFont=LTNULL;
            return LTFALSE;
		}

        // ************* Title font
		g_pLayoutMgr->GetLargeFontBase(g_szFontName,sizeof(g_szFontName));
		if (!SetupFont(m_pTitleFont))
		{
			if (!SetupFont(m_pTitleFont,LTFALSE))
			{
				debug_delete(m_pTitleFont);
				m_pTitleFont=LTNULL;
				return LTFALSE;
			}
		}


        // ************* Foreground HUD (i.e. white) HUD font
		g_pLayoutMgr->GetMsgForeFont(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pMsgForeFont))
		{
			debug_delete(m_pMsgForeFont);
            m_pMsgForeFont=LTNULL;
            return LTFALSE;
		}


        uint32 dwFlags = LTF_INCLUDE_SYMBOLS_1 | LTF_INCLUDE_NUMBERS | LTF_INCLUDE_SYMBOLS_2;
        // ************* Foreground HUD (i.e. white) HUD font
		g_pLayoutMgr->GetHUDForeFont(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pHUDForeFont,LTTRUE,dwFlags))
		{
			debug_delete(m_pHUDForeFont);
            m_pHUDForeFont=LTNULL;
            return LTFALSE;
		}

        // ************* Air font
		g_pLayoutMgr->GetAirFont(g_szFontName,sizeof(g_szFontName));
        if (!SetupFont(m_pAirFont,LTTRUE,dwFlags)) // This is actually not used?
		{
			debug_delete(m_pAirFont);
            m_pAirFont=LTNULL;
            return LTFALSE;
		}

        // ************* Weapon Chooser font
		g_pLayoutMgr->GetChooserFont(g_szFontName,sizeof(g_szFontName));
		if (!SetupFont(m_pChooserFont))
		{
			debug_delete(m_pChooserFont);
            m_pChooserFont=LTNULL;
            return LTFALSE;
		}
	}
	else
	{
        // TODO: put these into string table for localization
		// Initialize the engine fonts for non-english resource files
		if (!InitEngineFont(m_pSmallFont, IDS_SMALL_FONT_NAME, IDS_SMALL_FONT_WIDTH, IDS_SMALL_FONT_HEIGHT, LTFALSE))
            return LTFALSE;
		if (!InitEngineFont(m_pHelpFont, IDS_SMALL_FONT_NAME, IDS_SMALL_FONT_WIDTH, IDS_SMALL_FONT_HEIGHT, LTFALSE))
            return LTFALSE;
		if (!InitEngineFont(m_pMediumFont, IDS_MEDIUM_FONT_NAME, IDS_MEDIUM_FONT_WIDTH, IDS_MEDIUM_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pLargeFont, IDS_LARGE_FONT_NAME, IDS_LARGE_FONT_WIDTH, IDS_LARGE_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pTitleFont, IDS_TITLE_FONT_NAME, IDS_TITLE_FONT_WIDTH, IDS_TITLE_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pMsgForeFont, IDS_MEDIUM_FONT_NAME, IDS_MEDIUM_FONT_WIDTH, IDS_MEDIUM_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pHUDForeFont, IDS_LARGE_FONT_NAME, IDS_LARGE_FONT_WIDTH, IDS_LARGE_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pAirFont, IDS_LARGE_FONT_NAME, IDS_LARGE_FONT_WIDTH, IDS_LARGE_FONT_HEIGHT, LTTRUE))
            return LTFALSE;
		if (!InitEngineFont(m_pChooserFont, IDS_SMALL_FONT_NAME, IDS_SMALL_FONT_WIDTH, IDS_SMALL_FONT_HEIGHT, LTFALSE))
            return LTFALSE;

	}

    // TODO: reimplement this stuff
	// Set the wrapping method
//  HSTRING hString=g_pLTClient->FormatString(IDS_FONT_WRAP_USE_SPACES);
//  if (_mbsicmp((const unsigned char*)g_pLTClient->GetStringData(hString), (const unsigned char*)"1") == 0)
//	{
        CLTGUIFont::SetWrapMethod(LTTRUE);
//	}
//	else
//	{
//      CLTGUIFont::SetWrapMethod(LTFALSE);
//	}

	m_bFontsSetup = LTTRUE;

    return LTTRUE;

}

LTBOOL CInterfaceResMgr::TermFonts()
{

	if (m_pHelpFont)
	{
		m_pHelpFont->Term();
		debug_delete(m_pHelpFont);
		m_pHelpFont = LTNULL;
	}
	if (m_pSmallFont)
	{
		m_pSmallFont->Term();
		debug_delete(m_pSmallFont);
		m_pSmallFont = LTNULL;
	}
	if (m_pMediumFont)
	{
		m_pMediumFont->Term();
		debug_delete(m_pMediumFont);
		m_pMediumFont = LTNULL;
	}
	if (m_pLargeFont)
	{
		m_pLargeFont->Term();
		debug_delete(m_pLargeFont);
		m_pLargeFont = LTNULL;
	}
	if (m_pTitleFont)
	{
		m_pTitleFont->Term();
		debug_delete(m_pTitleFont);
		m_pTitleFont = LTNULL;
	}
	if (m_pMsgForeFont)
	{
		m_pMsgForeFont->Term();
		debug_delete(m_pMsgForeFont);
		m_pMsgForeFont = LTNULL;
	}
	if (m_pHUDForeFont)
	{
		m_pHUDForeFont->Term();
		debug_delete(m_pHUDForeFont);
		m_pHUDForeFont = LTNULL;
	}
	if (m_pAirFont)
	{
		m_pAirFont->Term();
		debug_delete(m_pAirFont);
		m_pAirFont = LTNULL;
	}
	if (m_pChooserFont)
	{
		m_pChooserFont->Term();
		debug_delete(m_pChooserFont);
		m_pChooserFont = LTNULL;
	}

	m_bFontsSetup = LTFALSE;

	return LTTRUE;
}

// *******************************************************************

// Initialize an engine font from string IDs that represent the name, width, and height
LTBOOL CInterfaceResMgr::InitEngineFont(CLTGUIFont *pFont, int nNameID, int nWidthID, int nHeightID, LTBOOL bBold)
{
	if (!pFont)
	{
        return LTFALSE;
	}

	// Get the font name, width, and height
    HSTRING hName=g_pLTClient->FormatString(nNameID);
    HSTRING hWidth=g_pLTClient->FormatString(nWidthID);
    HSTRING hHeight=g_pLTClient->FormatString(nHeightID);

	LITHFONTCREATESTRUCT lfCS;
	char szFontName[256] = "";
    strncpy(szFontName,g_pLTClient->GetStringData(hName),sizeof(szFontName));

	lfCS.szFontName	= szFontName;
    lfCS.nWidth     = atoi(g_pLTClient->GetStringData(hWidth));
    lfCS.nHeight    = atoi(g_pLTClient->GetStringData(hHeight));
    lfCS.bItalic    = LTFALSE;
    lfCS.bBold      = bBold;
    lfCS.bUnderline = LTFALSE;

	// Initialize the font
    LTBOOL bResult;

    bResult=pFont->Init(g_pLTClient, &lfCS);
	

	if (!bResult)
	{
		char szString[1024];
        sprintf(szString, "Cannot initialize font: %s", g_pLTClient->GetStringData(hName));
        g_pLTClient->CPrint(szString);
		SDL_Log(szString);
	} else {
		SDL_Log("Initialized Font %s",lfCS.szFontName);
	}


	// Free the strings
    g_pLTClient->FreeString(hName);
    g_pLTClient->FreeString(hWidth);
    g_pLTClient->FreeString(hHeight);

	return bResult;
}

LTBOOL CInterfaceResMgr::InitEngineFont(CLTGUIFont *pFont, char *lpszName, int nWidth, int nHeight, LTBOOL bBold)
{
	if (!pFont)
	{
        return LTFALSE;
	}

	LITHFONTCREATESTRUCT lfCS;
	char szFontName[256] = "";
	strncpy(szFontName,lpszName,sizeof(szFontName));

	lfCS.szFontName	= szFontName;
	lfCS.nWidth		= nWidth;
	lfCS.nHeight	= nHeight;
    lfCS.bItalic    = LTFALSE;
    lfCS.bBold      = bBold;
    lfCS.bUnderline = LTFALSE;

	// Initialize the font
    LTBOOL bResult;
    bResult=pFont->Init(g_pLTClient, &lfCS);

	if (!bResult)
	{
        g_pLTClient->CPrint("Cannot initialize font: %s", lpszName);
	}


	return bResult;
}

#define USABLE_HEIGHT_I 480
#define USABLE_HEIGHT_F 480.0f

void CInterfaceResMgr::ScreenDimsChanged()
{
    if (!g_pLTClient) return;

	RMode currentMode;
    g_pLTClient->GetRenderMode(&currentMode);

	m_Offset.x = (int)(currentMode.m_Width - 640) / 2;
	m_Offset.y = (int)(currentMode.m_Height - USABLE_HEIGHT_I) / 2;

	m_fXRatio = (float)currentMode.m_Width / 640.0f;
	m_fYRatio = (float)currentMode.m_Height / USABLE_HEIGHT_F;

	m_dwScreenWidth = currentMode.m_Width;
	m_dwScreenHeight = currentMode.m_Height;

	// Adjust scale fonts
	SetupScaleFonts();

	// Re-init the console
	g_pConsoleMgr->Init();
}


HSURFACE CInterfaceResMgr::GetSurfaceLoading()
{
	// The loading image
	if (!m_hSurfLoading)
        m_hSurfLoading = g_pLTClient->CreateSurfaceFromBitmap("menu\\art\\loading.pcx");
	_ASSERT(m_hSurfLoading);
	return m_hSurfLoading;
};

HSURFACE CInterfaceResMgr::CreateSurfaceBlank()
{
    return g_pLTClient->CreateSurfaceFromBitmap("menu\\art\\blanktag.pcx");
};


HSURFACE CInterfaceResMgr::GetSurfaceCursor()
{
	if (!m_hSurfCursor)
        m_hSurfCursor = g_pLTClient->CreateSurfaceFromBitmap("interface\\cursor0.pcx");
	_ASSERT(m_hSurfCursor);
	return m_hSurfCursor;
};


const char *CInterfaceResMgr::GetSoundSelect()
{
	if (m_csSoundSelect.IsEmpty())
	{
		m_csSoundSelect = g_pClientButeMgr->GetInterfaceAttributeString("SelectSound");
	}
	_ASSERT(!m_csSoundSelect.IsEmpty());
	return m_csSoundSelect;
};

const char *CInterfaceResMgr::GetSoundUnselectable()
{
	if (m_csSoundUnselectable.IsEmpty())
	{
		m_csSoundUnselectable = g_pClientButeMgr->GetInterfaceAttributeString("UnselectableSound");
	}
	_ASSERT(!m_csSoundUnselectable.IsEmpty());
	return m_csSoundUnselectable;
};

const char *CInterfaceResMgr::GetSoundChange()
{
	if (m_csSoundChange.IsEmpty())
	{
		m_csSoundChange = g_pClientButeMgr->GetInterfaceAttributeString("SelectChangeSound");
	}
	_ASSERT(!m_csSoundChange.IsEmpty());
	return m_csSoundChange;
};

const char *CInterfaceResMgr::GetSoundPageChange()
{
	if (m_csSoundPageChange.IsEmpty())
	{
		m_csSoundPageChange = g_pClientButeMgr->GetInterfaceAttributeString("PageChangeSound");
	}
	_ASSERT(!m_csSoundPageChange.IsEmpty());
	return m_csSoundPageChange;
};

const char *CInterfaceResMgr::GetSoundArrowUp()
{
	if (m_csSoundArrowUp.IsEmpty())
	{
		m_csSoundArrowUp = g_pClientButeMgr->GetInterfaceAttributeString("ArrowUpSound");
	}
	_ASSERT(!m_csSoundArrowUp.IsEmpty());
	return m_csSoundArrowUp;
};

const char *CInterfaceResMgr::GetSoundArrowDown()
{
	if (m_csSoundArrowDown.IsEmpty())
	{
		m_csSoundArrowDown = g_pClientButeMgr->GetInterfaceAttributeString("ArrowDownSound");
	}
	_ASSERT(!m_csSoundArrowDown.IsEmpty());
	return m_csSoundArrowDown;
};

const char *CInterfaceResMgr::GetSoundArrowLeft()
{
	if (m_csSoundArrowLeft.IsEmpty())
	{
		m_csSoundArrowLeft = g_pClientButeMgr->GetInterfaceAttributeString("ArrowLeftSound");
	}
	_ASSERT(!m_csSoundArrowLeft.IsEmpty());
	return m_csSoundArrowLeft;
};

const char *CInterfaceResMgr::GetSoundArrowRight()
{
	if (m_csSoundArrowRight.IsEmpty())
	{
		m_csSoundArrowRight = g_pClientButeMgr->GetInterfaceAttributeString("ArrowRightSound");
	}
	_ASSERT(!m_csSoundArrowRight.IsEmpty());
	return m_csSoundArrowRight;
};



const char *CInterfaceResMgr::GetObjectiveAddedSound()
{
	if (m_csSoundObjAdd.IsEmpty())
	{
		m_csSoundObjAdd = g_pClientButeMgr->GetInterfaceAttributeString("ObjAddSound");
	}
	_ASSERT(!m_csSoundObjAdd.IsEmpty());
	return m_csSoundObjAdd;
};

const char *CInterfaceResMgr::GetObjectiveRemovedSound()
{
	if (m_csSoundObjRemove.IsEmpty())
	{
		m_csSoundObjRemove = g_pClientButeMgr->GetInterfaceAttributeString("ObjRemoveSound");
	}
	_ASSERT(!m_csSoundObjRemove.IsEmpty());
	return m_csSoundObjRemove;
};

const char *CInterfaceResMgr::GetObjectiveCompletedSound()
{
	if (m_csSoundObjComplete.IsEmpty())
	{
		m_csSoundObjComplete = g_pClientButeMgr->GetInterfaceAttributeString("ObjCompleteSound");
	}
	_ASSERT(!m_csSoundObjComplete.IsEmpty());
	return m_csSoundObjComplete;
};


// Creates a surface just large enough for the string.
// You can make the surface a little larger with extraPixelsX and extraPixelsY.
HSURFACE CInterfaceResMgr::CreateSurfaceFromString(CLTGUIFont *pFont, HSTRING hString, HLTCOLOR hBackColor,
												int extraPixelsX, int extraPixelsY, int nWidth)
{
    LTIntPt sz;
	if (nWidth > 0)
		sz = pFont->GetTextExtentsFormat(hString,nWidth);
	else
		sz = pFont->GetTextExtents(hString);

    LTRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = sz.x+extraPixelsX;
	rect.bottom = sz.y+extraPixelsY;

    HSURFACE hSurf  = g_pLTClient->CreateSurface(sz.x+extraPixelsX,sz.y+extraPixelsY);
    g_pOptimizedRenderer->FillRect(hSurf,&rect,hBackColor);
	if (nWidth > 0)
		pFont->DrawFormat(hString, hSurf,extraPixelsX/2,extraPixelsY/2,nWidth,kWhite);
	else
		pFont->Draw(hString, hSurf,extraPixelsX/2,extraPixelsY/2,LTF_JUSTIFY_LEFT,kWhite);

	return hSurf;

}

HSURFACE CInterfaceResMgr::CreateSurfaceFromString(CLTGUIFont *pFont, int nStringId, HLTCOLOR hBackColor,
												int extraPixelsX, int extraPixelsY, int nWidth)
{
    HSTRING hString = g_pLTClient->FormatString(nStringId);
	return CreateSurfaceFromString(pFont, hString, hBackColor, extraPixelsX, extraPixelsY, nWidth);
    g_pLTClient->FreeString(hString);
}

HSURFACE CInterfaceResMgr::CreateSurfaceFromString(CLTGUIFont *pFont, char *lpszString, HLTCOLOR hBackColor,
												int extraPixelsX, int extraPixelsY, int nWidth)
{
    HSTRING hString = g_pLTClient->CreateString(lpszString);
	return CreateSurfaceFromString(pFont, hString, hBackColor, extraPixelsX, extraPixelsY, nWidth);
    g_pLTClient->FreeString(hString);
}

LTBOOL CInterfaceResMgr::SetupFont(CLTGUIFont *pFont, LTBOOL bBlend, uint32 dwFlags)
{

	LITHFONTCREATESTRUCT lithFont;
	lithFont.szFontBitmap = g_szFontName;
	lithFont.nGroupFlags = dwFlags;
	if (bBlend)
	{
		lithFont.bChromaKey = LTFALSE;
		lithFont.hTransColor = kBlack;
	}
	else
	{
		lithFont.bChromaKey = LTTRUE;
		lithFont.hTransColor = SETRGB(255,0,255);
	}

    if ( !pFont->Init(g_pLTClient, &lithFont) )
	{
		char szString[512];
		sprintf(szString, "Cannot load font: %s", lithFont.szFontBitmap);
        g_pLTClient->CPrint(szString);
		SDL_Log(szString);
        return LTFALSE;
	}

	
	SDL_Log("Initialized %s",lithFont.szFontBitmap);

    return LTTRUE;
}

CLTGUIFont* CInterfaceResMgr::GetLargeFont()
{
	// Until I can get some time to fix up other fonts, we'll just use the default one.
#if 1
	return m_pLargeFont;
#else
	if(m_pLargeHDFont != LTNULL && GetScreenHeight() > 900) {
		return m_pLargeHDFont;
	}

	return m_pLargeFont;
#endif
}