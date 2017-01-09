
// MFC_Christmas_TreeDoc.cpp : implementation of the CMFC_Christmas_TreeDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Christmas_Tree.h"
#endif

#include "MFC_Christmas_TreeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC_Christmas_TreeDoc

IMPLEMENT_DYNCREATE(CMFC_Christmas_TreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFC_Christmas_TreeDoc, CDocument)
END_MESSAGE_MAP()


// CMFC_Christmas_TreeDoc construction/destruction

CMFC_Christmas_TreeDoc::CMFC_Christmas_TreeDoc()
{
	// TODO: add one-time construction code here

}

CMFC_Christmas_TreeDoc::~CMFC_Christmas_TreeDoc()
{
}

BOOL CMFC_Christmas_TreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFC_Christmas_TreeDoc serialization

void CMFC_Christmas_TreeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFC_Christmas_TreeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFC_Christmas_TreeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFC_Christmas_TreeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFC_Christmas_TreeDoc diagnostics

#ifdef _DEBUG
void CMFC_Christmas_TreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFC_Christmas_TreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFC_Christmas_TreeDoc commands
