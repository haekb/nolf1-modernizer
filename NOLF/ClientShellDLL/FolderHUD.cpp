#include "stdafx.h"
#include "FolderHUD.h"
#include "FolderMgr.h"
#include "FolderCommands.h"
#include "ClientRes.h"

#include "GameClientShell.h"
#include "GameSettings.h"

namespace
{
	int kGap = 0;
	int kWidth = 0;
}

// CFolderInterface
// For those looking for it, HUD was renamed to Interface :)
CFolderHUD::CFolderHUD()
{
	m_fUIScale = 1.0f;
	m_nUIScale = 100;
	m_bUseGOTYMenu = LTFALSE;
}

CFolderHUD::~CFolderHUD()
{
}

LTBOOL CFolderHUD::Build()
{
	CreateTitle(IDS_TITLE_HUD_OPTIONS);

	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_HUD, "ColumnWidth"))
		kGap = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_HUD, "ColumnWidth");
	if (g_pLayoutMgr->HasCustomValue(FOLDER_ID_HUD, "SliderWidth"))
		kWidth = g_pLayoutMgr->GetFolderCustomInt(FOLDER_ID_HUD, "SliderWidth");

	LTFLOAT yr = g_pInterfaceResMgr->GetYRatio();
	kGap *= yr;


	CSliderCtrl* pSlider = AddSlider(IDS_UI_SCALE, IDS_HELP_UI_SCALE, 200 * yr, 200, &m_nUIScale);
	pSlider->SetSliderRange(50, 100);
	pSlider->SetSliderIncrement(10);
	pSlider->SetNumericDisplay(LTTRUE);

	if (g_pVersionMgr->IsGOTY())
	{
		CToggleCtrl* pToggle = AddToggle(IDS_USE_GOTY_MENU, IDS_HELP_USE_GOTY_MENU, kGap, &m_bUseGOTYMenu);
		pToggle->SetOnString(IDS_GOTY_MENU);
		pToggle->SetOffString(IDS_NORMAL_MENU);
	}
	
	// Make sure to call the base class
	if (!CBaseFolder::Build()) return LTFALSE;

	UseBack(LTTRUE, LTTRUE);

	return LTTRUE;
}

void CFolderHUD::OnFocus(LTBOOL bFocus)
{
	// Enter
	if (bFocus) {

		m_fUIScale = GetConfigFloat("UIScale", 0.5f);
		m_nUIScale = m_fUIScale * 100;

		m_bUseGOTYMenu = GetConfigInt("UseGotyMenu", 0);

		UpdateData(LTFALSE);
		CBaseFolder::OnFocus(bFocus);
		return;
	}

	// Leave
	UpdateData(LTTRUE);

	m_fUIScale = (float)m_nUIScale / 100.0f;

	WriteConsoleFloat("UIScale", m_fUIScale);
	g_pInterfaceResMgr->SetUserScale(m_fUIScale);

	WriteConsoleInt("UseGotyMenu", m_bUseGOTYMenu);

	g_pLTClient->WriteConfigFile("autoexec.cfg");
	GetConfigFile("autoexec.cfg");
	g_pGameClientShell->UpdateConfigSettings(); // Might not be needed here.

	CBaseFolder::OnFocus(bFocus);
}
