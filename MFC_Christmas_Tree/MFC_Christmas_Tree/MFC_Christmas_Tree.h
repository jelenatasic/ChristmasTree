
// MFC_Christmas_Tree.h : main header file for the MFC_Christmas_Tree application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFC_Christmas_TreeApp:
// See MFC_Christmas_Tree.cpp for the implementation of this class
//

class CMFC_Christmas_TreeApp : public CWinAppEx
{
public:
	CMFC_Christmas_TreeApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_Christmas_TreeApp theApp;
