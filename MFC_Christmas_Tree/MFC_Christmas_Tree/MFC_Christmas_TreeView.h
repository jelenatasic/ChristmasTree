
#pragma once
#include "ChristmasTree.h"
#include "Snow.h"
#include "Firework.h"
class CMFC_Christmas_TreeView : public CView
{
protected:
	CMFC_Christmas_TreeView();
	DECLARE_DYNCREATE(CMFC_Christmas_TreeView)

// Attributes
protected:
	ChristmasTree* christmas_tree;
	Snow* snow;
	Firework* firework1;
	Firework* firework2;
	Firework* firework3;
	Firework* firework4;
public:
	CMFC_Christmas_TreeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawSnowHill(CDC* pDC);
	void WishWell(CDC* pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFC_Christmas_TreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in MFC_Christmas_TreeView.cpp
inline CMFC_Christmas_TreeDoc* CMFC_Christmas_TreeView::GetDocument() const
   { return reinterpret_cast<CMFC_Christmas_TreeDoc*>(m_pDocument); }
#endif

