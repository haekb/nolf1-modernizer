// ----------------------------------------------------------------------- //
//
// MODULE  : VersionMgr.h
//
// PURPOSE : Definition of versioning manager
//
// CREATED : 11/16/2000
//
// (c) 2000 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //

#ifndef __VERSION_MGR_H__
#define __VERSION_MGR_H__

class CVersionMgr;
extern CVersionMgr* g_pVersionMgr;

class CVersionMgr
{
	public :

		CVersionMgr();
		~CVersionMgr() {}

		static const char* GetVersion();
		static const char* GetBuild();
		static const uint32 GetSaveVersion();
		static const float GetLatestPatchVersion();

		const char* GetLanguage()	const { return m_szLanguage; }
		inline bool	IsLowViolence() const { return m_bLowViolence; }
		inline bool IsGOTY() const { return m_bIsGOTY; }


	private :

		char m_szLanguage[64];
		bool m_bLowViolence;
		bool m_bIsGOTY;
};

#endif __VERSION_MGR_H__