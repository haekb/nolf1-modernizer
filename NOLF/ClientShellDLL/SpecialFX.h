// ----------------------------------------------------------------------- //
//
// MODULE  : SpecialFX.h
//
// PURPOSE : Generic client-side Special FX wrapper class - Definition
//
// CREATED : 10/13/97
//
// (c) 1997-1999 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //

#ifndef __SPECIAL_FX_H__
#define __SPECIAL_FX_H__

#include "ltbasedefs.h"
#include "iltclient.h"
#include "SharedBaseFXStructs.h"
#include "SFXMsgIds.h"
#include "ClientUtilities.h"

LTFLOAT GetConsoleFloat(char* sKey, LTFLOAT fDefault);

class CSpecialFX
{
	public :

		CSpecialFX()
		{
            m_bWantRemove       = LTFALSE;
            m_pClientDE         = LTNULL;
            m_hObject           = LTNULL;
            m_hServerObject     = LTNULL;
			m_fUpdateDelta		= 0.001f;
			m_fNextUpdateTime	= 0.0f;
			m_vLastServPos.Init();
			m_vVel.Init();

			m_nHeadNode = -1;
		}

		virtual ~CSpecialFX()
		{
			CSpecialFX::Term();
		}

		virtual void Term()
		{
			if (m_pClientDE && m_hObject)
			{
				m_pClientDE->DeleteObject(m_hObject);
                m_hObject = LTNULL;
			}
		}

        virtual LTBOOL CreateObject(ILTClient* pClientDE)
		{
            if (!pClientDE) return LTFALSE;
			m_pClientDE = pClientDE;

			if (m_hServerObject)
			{
				m_pClientDE->GetObjectPos(m_hServerObject, &m_vLastServPos);
			}

            return LTTRUE;
		}

		virtual void FindHeadNode()
		{
			// Just incase constructor is never called...
			m_nHeadNode = INVALID_MODEL_NODE;

			HOBJECT hObject = m_hServerObject;

			// FIXME: This might be slow for objects that don't need big head mode...
			// Find the head node, this is later used for big head mode.
			HMODELNODE hCurNode = INVALID_MODEL_NODE;
			while (g_pLTClient->GetNextModelNode(hObject, hCurNode, &hCurNode) == LT_OK)
			{
				char szName[64] = "";
				g_pLTClient->GetModelNodeName(hObject, hCurNode, szName, 64);

				if (stricmp(szName, "head_node") == 0) {
					m_nHeadNode = hCurNode;
				}
			}
		}

        virtual LTBOOL Init(HLOCALOBJ hServObj, HMESSAGEREAD hRead)
		{
            if (!hRead) return LTFALSE;

			m_hServerObject = hServObj;

			FindHeadNode();

            return LTTRUE;
		}

        virtual LTBOOL Init(SFXCREATESTRUCT* psfxCreateStruct)
		{
            if (!psfxCreateStruct) return LTFALSE;

			m_hServerObject = psfxCreateStruct->hServerObj;

			FindHeadNode();

            return LTTRUE;
		}

        // Return of LTFALSE indicates special fx is done and can be removed.

        virtual LTBOOL Update()
		{
			// Calculate our server-object's velocity...

			if (m_hServerObject && m_pClientDE)
			{
                LTVector vPos;
				m_pClientDE->GetObjectPos(m_hServerObject, &vPos);

				m_vVel = vPos - m_vLastServPos;
				m_vVel /= m_pClientDE->GetFrameTime();

				m_vLastServPos = vPos;
			}

            return LTTRUE;
		}

		// Call this to tell special fx to finish up so we can remove it...

        virtual void WantRemove(LTBOOL bRemove=LTTRUE)
		{
			m_bWantRemove = bRemove;
            if (m_bWantRemove) m_hServerObject = LTNULL;
		}
        LTBOOL IsWaitingForRemove() const { return m_bWantRemove; }

		HLOCALOBJ	GetObject()		const { return m_hObject; }
		HLOCALOBJ	GetServerObj()	const { return m_hServerObject; }

        LTFLOAT  GetUpdateDelta()    const { return m_fUpdateDelta; }

		virtual void HandleTouch(CollisionInfo *pInfo, float forceMag) {}
		virtual void OnModelKey(HLOCALOBJ hObj, ArgList *pArgs) {}
        virtual LTBOOL OnServerMessage(HMESSAGEREAD hMessage) { return (!!hMessage); }

        LTFLOAT  m_fNextUpdateTime;  // When do we update next

		// Function for returning a special effect ID from a derived class
		virtual uint32 GetSFXID() { return SFX_TOTAL_NUMBER + 1; }

		HMODELNODE GetHeadNode() { return m_nHeadNode; }

		// Static

		//
		// Handle BigHeadMode here, so we can rely on this function from BodyFX and CharacterFX (via NodeController)
		//
		static void HandleBigHeadModeFn(HOBJECT hObj, HMODELNODE hNode, LTMatrix* pGlobalMat, void* pUserData)
		{
			LTFLOAT fBigHeadMode = GetConsoleFloat("BigHeadMode", 0.0f);

			if (!fBigHeadMode) {
				return;
			}
			
			CSpecialFX* pSFX = (CSpecialFX*)pUserData;

			// If big head mode enabled? If so, apply the scale!
			// It now scales based on the amount specified.
			if (hNode == pSFX->m_nHeadNode) {
				LTFLOAT fBigHeadedness = 1.8f * fBigHeadMode;
				pGlobalMat->Scale(fBigHeadedness, fBigHeadedness, fBigHeadedness);
			}
		}

	protected :

        ILTClient*  m_pClientDE;
		HOBJECT		m_hObject;			// Special FX object
		HOBJECT		m_hServerObject;	// Local handle to Server-side object
        LTVector     m_vLastServPos;     // Last position of the server object
        LTVector     m_vVel;             // Our server object's velocity
        LTBOOL       m_bWantRemove;
        LTFLOAT      m_fUpdateDelta;     // Time between updates

		HMODELNODE	m_nHeadNode;
};

#endif // __SPECIAL_FX_H__