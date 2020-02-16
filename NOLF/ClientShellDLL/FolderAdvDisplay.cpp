// FolderAdvDisplay.cpp: implementation of the CFolderAdvDisplay class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FolderAdvDisplay.h"
#include "FolderMgr.h"
#include "FolderCommands.h"
#include "ClientRes.h"

#include "GameClientShell.h"
#include "GameSettings.h"
extern CGameClientShell* g_pGameClientShell;

namespace
{
	enum eLocalCommands
	{
		CMD_TEXTURES = FOLDER_CMD_CUSTOM+1,
	};
	int kHeaderWidth = 300;
	int kSliderWidth = 200;
	int kSpacerWidth = 25;
	int kTotalWidth  = kHeaderWidth + kSpacerWidth;

	void AreYouSureCallBack(LTBOOL bReturn, void *pData)
	{
		CFolderAdvDisplay *pThisFolder = (CFolderAdvDisplay *)pData;
		if (pThisFolder)
		{
			pThisFolder->ConfirmSetting(bReturn);
		}
	}

	LTBOOL g_bFocus = LTFALSE;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolderAdvDisplay::CFolderAdvDisplay()
{
	m_bLightMap = LTFALSE;
	m_bMirrors = LTFALSE;
	m_nShadows = 0;
	m_bDetailTextures = LTFALSE;
	m_bEnvMapWorld = LTFALSE;
	m_bEnvMapEnable = LTFALSE;
	m_bTripleBuffer = LTFALSE;
	m_bFixSparkleys = LTFALSE;
	m_bTrilinear = LTFALSE;
	m_nTextureFiltering = 0;

	m_pTextureFiltering = LTNULL;
	m_pShadows = LTNULL;
//	m_pOverdraw = LTNULL;
	m_pLightMap = LTNULL;
	m_pMirrors = LTNULL;
}

CFolderAdvDisplay::~CFolderAdvDisplay()
{
	Term();
}

// Build the folder
LTBOOL CFolderAdvDisplay::Build()
{

	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_ADVDISPLAY,"ColumnWidth"))
	{
		kTotalWidth = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_ADVDISPLAY,"ColumnWidth");
		LTFLOAT yr = g_pInterfaceResMgr->GetYRatio();
		kTotalWidth *= yr;
		kHeaderWidth = kTotalWidth - kSpacerWidth;
	}
	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_ADVDISPLAY,"SliderWidth"))
		kSliderWidth = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_ADVDISPLAY,"SliderWidth");

	CreateTitle(IDS_TITLE_ADVDISPLAY);

	AddTextItem(IDS_TEXTURE_RES, CMD_TEXTURES,	IDS_HELP_TEXTURE_RES);

	m_pLightMap = AddToggle(IDS_LIGHTMAP, IDS_HELP_LIGHTMAP, kTotalWidth, &m_bLightMap );
	m_pLightMap->SetOnString(IDS_ON);
	m_pLightMap->SetOffString(IDS_OFF);

	m_pMirrors = AddToggle(IDS_MIRRORS, IDS_HELP_MIRRORS, kTotalWidth, &m_bMirrors );
	m_pMirrors->SetOnString(IDS_ON);
	m_pMirrors->SetOffString(IDS_OFF);

	m_pShadows = AddCycleItem(IDS_SHADOWS,IDS_HELP_SHADOWS,kHeaderWidth,kSpacerWidth,&m_nShadows);
	m_pShadows->AddString(IDS_NONE);
	m_pShadows->AddString(IDS_CIRCULAR);
//	m_pShadows->AddString(IDS_PROJECTED);
	
	CToggleCtrl* pToggle = AddToggle(IDS_DETAILTEXTURES, IDS_HELP_DETAILTEXTURES, kTotalWidth, &m_bDetailTextures );
	pToggle->SetOnString(IDS_ON);
	pToggle->SetOffString(IDS_OFF);

	pToggle = AddToggle(IDS_ENVIRONMENT_MAP, IDS_HELP_ENVIRONMENT_MAP, kTotalWidth, &m_bEnvMapWorld );
	pToggle->SetOnString(IDS_ON);
	pToggle->SetOffString(IDS_OFF);

	pToggle = AddToggle(IDS_CHROME, IDS_HELP_CHROME, kTotalWidth, &m_bEnvMapEnable );
	pToggle->SetOnString(IDS_ON);
	pToggle->SetOffString(IDS_OFF);

//	m_pOverdraw = AddToggle(IDS_OVERDRAW, IDS_HELP_OVERDRAW, kTotalWidth, &m_bFixSparkleys );
//	m_pOverdraw->SetOnString(IDS_ON);
//	m_pOverdraw->SetOffString(IDS_OFF);


	//pToggle = AddToggle(IDS_TRILINEAR, IDS_HELP_TRILINEAR, kTotalWidth, &m_bTrilinear );
	//pToggle->SetOnString(IDS_ON);
	//pToggle->SetOffString(IDS_OFF);

	m_pTextureFiltering = AddCycleItem(IDS_TEXTURE_FILTERING, IDS_HELP_TEXTURE_FILTERING, kHeaderWidth, kSpacerWidth, &m_nTextureFiltering);
	m_pTextureFiltering->AddString(IDS_NO_TF);
	m_pTextureFiltering->AddString(IDS_TRILINEAR_TF);
	m_pTextureFiltering->AddString(IDS_AF_2X_TF);
	m_pTextureFiltering->AddString(IDS_AF_4X_TF);
	m_pTextureFiltering->AddString(IDS_AF_8X_TF);
	m_pTextureFiltering->AddString(IDS_AF_16X_TF);


	pToggle = AddToggle(IDS_TRIPLE_BUFF, IDS_HELP_TRIPLE_BUFF, kTotalWidth, &m_bTripleBuffer );
	pToggle->SetOnString(IDS_ON);
	pToggle->SetOffString(IDS_OFF);    
	
	uint32 dwAdvancedOptions = g_pInterfaceMgr->GetAdvancedOptions();
	pToggle->Enable( (dwAdvancedOptions & AO_TRIPLEBUFFER) );


 	// Make sure to call the base class
	if (!CBaseFolder::Build()) return LTFALSE;

	UseBack(LTTRUE,LTTRUE);

	return LTTRUE;

}

void CFolderAdvDisplay::Term()
{
	// Make sure to call the base class
	CBaseFolder::Term();
}

uint32 CFolderAdvDisplay::OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2)
{
	switch (dwCommand)
	{
	case CMD_TEXTURES:
	{
		m_pFolderMgr->SetCurrentFolder(FOLDER_ID_TEXTURE);
	} break;

	default:
		return CBaseFolder::OnCommand(dwCommand,dwParam1,dwParam2);
	};

	return 1;
};


void CFolderAdvDisplay::OnFocus(LTBOOL bFocus)
{
	uint32 dwAdvancedOptions = g_pInterfaceMgr->GetAdvancedOptions();
	g_bFocus = LTFALSE;
	LTBOOL bAllowMirrors = (GetConsoleInt("BitDepth",16) == 32);
	if (bFocus)
	{
		

		m_pMirrors->Enable(bAllowMirrors);

        m_bLightMap = (GetConsoleInt("LightMap",0) > 0);
		if (bAllowMirrors)
	        m_bMirrors = (GetConsoleInt("DrawPortals",0) > 0);
		else
			m_bMirrors = LTFALSE;
        m_bDetailTextures = (GetConsoleInt("DetailTextures",0) > 0);
        m_bEnvMapWorld = (GetConsoleInt("EnvMapWorld",0) > 0);
        m_bEnvMapEnable = (GetConsoleInt("EnvMapEnable",0) > 0);
        m_bTripleBuffer = (GetConsoleInt("TripleBuffer",0) > 0) && (dwAdvancedOptions & AO_TRIPLEBUFFER);
        m_bFixSparkleys = (GetConsoleInt("FixSparkleys",0) > 0);
        m_bTrilinear = (GetConsoleInt("Trilinear",0) > 0);
		
		if (m_bTrilinear == 1) {
			m_nTextureFiltering = 1;
		}

		int af = GetConsoleInt("anisotropic", 0);

		// Lazy but it works!
		switch (af) {
		case 2:
			m_nTextureFiltering = 2;
			break;
		case 4:
			m_nTextureFiltering = 3;
			break;
		case 8:
			m_nTextureFiltering = 4;
		case 16:
			m_nTextureFiltering = 5;
		}

		m_nShadows = 0;
		if (GetConsoleInt("DrawShadows",0) > 0)
		{
			m_nShadows++;
			if (GetConsoleInt("ModelShadowProj",0) > 0) m_nShadows++;
		}

        UpdateData(LTFALSE);
		g_bFocus = LTTRUE;

	}
	else
	{
        UpdateData(LTTRUE);

		int af = 0;
		int bilinear = 0;

		// Texture filtering time!
		
		// Honestly this could probably be a table, but we only need it here so...
		switch (m_nTextureFiltering) {
		case 0:
		case 1:
			m_bTrilinear = m_nTextureFiltering;
			break;
		case 2:
			af = 2;
			m_bTrilinear = 1;
			break;
		case 3:
			af = 4;
			m_bTrilinear = 1;
			break;
		case 4:
			af = 8;
			m_bTrilinear = 1;
			break;
		case 5:
			af = 16;
			m_bTrilinear = 1;
			break;
		}

		// Sooo with no texture filtering on...we also need to turn off bilinear. 
		// OH god is it ever ugly, but gotta be true to the option name!
		bilinear = m_bTrilinear;

		// End texture filtering mess


		LTBOOL bOldTB = (GetConsoleInt("TripleBuffer",0) > 0);

		WriteConsoleInt("LightMap",m_bLightMap);
		if (bAllowMirrors)
			WriteConsoleInt("DrawPortals",m_bMirrors);
		WriteConsoleInt("DetailTextures",m_bDetailTextures);
		WriteConsoleInt("EnvMapWorld",m_bEnvMapWorld);
		WriteConsoleInt("EnvMapEnable",m_bEnvMapEnable);
		WriteConsoleInt("TripleBuffer",m_bTripleBuffer && (dwAdvancedOptions & AO_TRIPLEBUFFER));
		WriteConsoleInt("FixSparkleys",m_bFixSparkleys);

		WriteConsoleInt("Bilinear", bilinear);
		WriteConsoleInt("Trilinear",m_bTrilinear);
		WriteConsoleInt("Anisotropic", af);


		WriteConsoleInt("DrawShadows",(m_nShadows > 0) );
		WriteConsoleInt("MaxModelShadows",(m_nShadows > 0) );
		WriteConsoleInt("ModelShadowProj",(m_nShadows > 1) );

		if (bOldTB != m_bTripleBuffer)
		{
			// Set the renderer mode
			g_pInterfaceMgr->SetSwitchingRenderModes(LTTRUE);
			g_pLTClient->RunConsoleString("RestartRender");
			g_pInterfaceMgr->SetSwitchingRenderModes(LTFALSE);

		}

        g_pLTClient->WriteConfigFile("autoexec.cfg");

	}
	CBaseFolder::OnFocus(bFocus);
}



void CFolderAdvDisplay::ConfirmSetting(LTBOOL bConfirm)
{
	if (bConfirm) return;
	switch (m_nSettingToConfirm)
	{
	case IDS_CONFIRM_SHADOWS:
		m_nShadows = 1;
		UpdateData(LTFALSE);
		break;
//	case IDS_CONFIRM_OVERDRAW:
//		m_bFixSparkleys = LTFALSE;
//		UpdateData(LTFALSE);
//		break;
	case IDS_CONFIRM_LIGHTMAP:
		m_bLightMap = LTTRUE;
		UpdateData(LTFALSE);
		break;

	}

}


LTBOOL CFolderAdvDisplay::OnLeft()
{
	if (!CBaseFolder::OnLeft()) return LTFALSE;
	if (GetSelectedControl() == m_pLightMap)
	{
		if (m_pLightMap->GetSelIndex())
		{
			m_nSettingToConfirm = IDS_CONFIRM_LIGHTMAP;
			HSTRING hString = g_pLTClient->FormatString(IDS_CONFIRM_LIGHTMAP);
			g_pInterfaceMgr->ShowMessageBox(hString,LTMB_YESNO,AreYouSureCallBack,this,LTFALSE,LTFALSE);
			g_pLTClient->FreeString(hString);
		}
	}
	return LTTRUE;
}

LTBOOL CFolderAdvDisplay::OnRight()
{
	if (!CBaseFolder::OnRight()) return LTFALSE;
	if (GetSelectedControl() == m_pLightMap)
	{
		if (m_pLightMap->GetSelIndex())
		{
			m_nSettingToConfirm = IDS_CONFIRM_LIGHTMAP;
			HSTRING hString = g_pLTClient->FormatString(IDS_CONFIRM_LIGHTMAP);
			g_pInterfaceMgr->ShowMessageBox(hString,LTMB_YESNO,AreYouSureCallBack,this,LTFALSE,LTFALSE);
			g_pLTClient->FreeString(hString);
		}
	}
	return LTTRUE;
}


LTBOOL CFolderAdvDisplay::OnLButtonUp(int x, int y)
{
	int nControlIndex=0;
	if (GetControlUnderPoint(x, y, &nControlIndex))
	{
		CLTGUICtrl* pCtrl = GetControl(nControlIndex);
		if (pCtrl == m_pLightMap)
		{
			return OnRight();
		}
	}
	return CBaseFolder::OnLButtonUp(x, y);
}

LTBOOL CFolderAdvDisplay::OnRButtonUp(int x, int y)
{
	int nControlIndex=0;
	if (GetControlUnderPoint(x, y, &nControlIndex))
	{
		CLTGUICtrl* pCtrl = GetControl(nControlIndex);
		if (pCtrl == m_pLightMap)
		{
			return OnLeft();
		}
	}
	return CBaseFolder::OnRButtonUp(x, y);
}
