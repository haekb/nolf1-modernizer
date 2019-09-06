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

CFolderHUD::CFolderHUD()
{
	m_fUIScale = 1.0f;
	m_nUIScale = 100;
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

		SDL_Log("UI Scale (F)<%f> (I)<%d>", m_fUIScale, m_nUIScale);
		UpdateData(LTFALSE);
		CBaseFolder::OnFocus(bFocus);
		return;
	}

	// Leave
	UpdateData(LTTRUE);


	m_fUIScale = (float)m_nUIScale / 100.0f;
	SDL_Log("UI Scale (F)<%f> (I)<%d>", m_fUIScale, m_nUIScale);


	WriteConsoleFloat("UIScale", m_fUIScale);
	g_pInterfaceResMgr->SetUserScale(m_fUIScale);

	g_pLTClient->WriteConfigFile("autoexec.cfg");
	GetConfigFile("autoexec.cfg");
	g_pGameClientShell->UpdateConfigSettings(); // Might not be needed here.

	CBaseFolder::OnFocus(bFocus);
}
