
// MFC_Christmas_TreeDoc.h : interface of the CMFC_Christmas_TreeDoc class
//


#pragma once


class CMFC_Christmas_TreeDoc : public CDocument
{
protected: // create from serialization only
	CMFC_Christmas_TreeDoc();
	DECLARE_DYNCREATE(CMFC_Christmas_TreeDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFC_Christmas_TreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
