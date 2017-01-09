#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_Christmas_Tree.h"
#endif

#include "MFC_Christmas_TreeDoc.h"
#include "MFC_Christmas_TreeView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SNOW_FLAKE_COUNT 300

// CMFC_Christmas_TreeView

IMPLEMENT_DYNCREATE(CMFC_Christmas_TreeView, CView)

BEGIN_MESSAGE_MAP(CMFC_Christmas_TreeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFC_Christmas_TreeView construction/destruction

CMFC_Christmas_TreeView::CMFC_Christmas_TreeView()
{
	christmas_tree = new ChristmasTree();
	snow = new Snow(SNOW_FLAKE_COUNT);
	firework1 = new Firework(5, 9, true, 25);
	firework2 = new Firework(4, 15, false, 70);
	firework3 = new Firework(4, 20, false, 100);
	firework4 = new Firework(5, 8, true, 25);
}

CMFC_Christmas_TreeView::~CMFC_Christmas_TreeView()
{
	delete christmas_tree;
	delete snow;
	delete firework1;
	delete firework2;
	delete firework3;
	delete firework4;
}

BOOL CMFC_Christmas_TreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CMFC_Christmas_TreeView drawing

void CMFC_Christmas_TreeView::OnDraw(CDC* pDC)
{
	CMFC_Christmas_TreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportExt(rect.Width(), rect.Height());
	pDC->SetWindowExt(rect.Width(), rect.Height());

	//all drawing is done in memory DC, for elimination of flicker
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	//creating bitmap that is compatibile with pDC, and selecting it into memoryDC, so that it contains the drawing
	CBitmap screen;
	screen.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	memDC->SelectObject(&screen);

	CBrush* brush = new CBrush(RGB(40,40,40));//(80,150,190));
	memDC->FillRect(rect, brush);
	DrawSnowHill(memDC);
	WishWell(memDC);

	firework1->PrepareFirework(CPoint(rect.right* 0.125, rect.bottom*0.225), RGB(112,146,190));  //(206,199,225));
	firework1->DrawFirework(memDC);

	firework2->PrepareFirework(CPoint(rect.right* 0.2, rect.bottom*0.35), RGB(163,73,164));
	firework2->DrawFirework(memDC);

	firework3->PrepareFirework(CPoint(rect.right* 0.8, rect.bottom*0.3), RGB	(206,0,103));
	firework3->DrawFirework(memDC);

	firework4->PrepareFirework(CPoint(rect.right* 0.875, rect.bottom*0.225), RGB	(255,153,204));
	firework4->DrawFirework(memDC);

	christmas_tree->SetDC(memDC);
	christmas_tree->DrawChristmasTree(rect.Width(), rect.Height());
	
	snow->Show(memDC);
	//setting timer, that when triggered, couses positon change for snowflakes
	SetTimer(1, 50, NULL); // 8 frame per second

	//copying bitmap from memoryDC into pDC
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	//deleting used objects
	memDC->DeleteDC();
	brush->DeleteObject();
}

void CMFC_Christmas_TreeView::DrawSnowHill(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	//creating new brush and pen with colors for snow hill
	CBrush* brush = new CBrush(RGB(230,230,230));
	CBrush* old_brush = pDC->SelectObject(brush);

	CPen* pen = new CPen(PS_SOLID, 2, RGB(230,230,230));
	CPen* old_pen = pDC->SelectObject(pen);

	//path containing hill on the bottom of screen
	pDC->BeginPath();
	pDC->MoveTo(0.0, 0.93*rect.bottom);

	CPoint points[] =
	{
		CPoint(0.2*rect.right, 0.90*rect.bottom),
		CPoint(0.4*rect.right, 0.90*rect.bottom),
		CPoint(0.5*rect.right, 0.93*rect.bottom),
		CPoint(0.6*rect.right, 0.96*rect.bottom),
		CPoint(0.8*rect.right, 0.96*rect.bottom),
		CPoint(rect.right, 0.93*rect.bottom)
	};
	//Bezier line for curve
	pDC->PolyBezierTo(points, 6);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(0.0, rect.bottom);
	pDC->LineTo(0.0, 0.93*rect.bottom);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(old_brush);
	brush->DeleteObject();
	pDC->SelectObject(old_pen);
	pen->DeleteObject();
}

void CMFC_Christmas_TreeView::WishWell(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CFont font;
	LPCTSTR fontStyle = (LPCTSTR)"Courier";
	font.CreateFont(26, 15, 0, 0, FW_BOLD, 2, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	CFont *oldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(104, 176, 34));

	CString string = (CString)"Happy 15th birthday Troxo!";
	pDC->SetTextAlign(TA_BOTTOM);
	pDC->TextOut(rect.right - pDC->GetTextExtent(string).cx, rect.bottom, string);

	pDC->SelectObject(oldFont);
	font.DeleteObject();
}


// CMFC_Christmas_TreeView printing

BOOL CMFC_Christmas_TreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CMFC_Christmas_TreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFC_Christmas_TreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFC_Christmas_TreeView diagnostics

#ifdef _DEBUG
void CMFC_Christmas_TreeView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_Christmas_TreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_Christmas_TreeDoc* CMFC_Christmas_TreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_Christmas_TreeDoc)));
	return (CMFC_Christmas_TreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_Christmas_TreeView message handlers


void CMFC_Christmas_TreeView::OnTimer(UINT_PTR nIDEvent)
{
	//when timer goes off, snowflakes should move on screen and take new positions
	snow->Move();
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CMFC_Christmas_TreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}


BOOL CMFC_Christmas_TreeView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CMFC_Christmas_TreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	//when screen resize occures, positions of snowflakes should be calculated for new dimensions of screen
	if(cx!=0 && cy!=0)
	{
		snow->Initial(cx, cy);
		firework1->ResetPositions();
		firework2->ResetPositions();
		firework3->ResetPositions();
		firework4->ResetPositions();
	}
}
