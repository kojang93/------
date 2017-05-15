
// ����������ƮView.h : C����������ƮView Ŭ������ �������̽�
//

#pragma once
#include "Ant.h"
#include "BufferDC.h"

class C����������ƮView : public CView
{
protected: // serialization������ ��������ϴ�.
	C����������ƮView();
	DECLARE_DYNCREATE(C����������ƮView)

// Ư���Դϴ�.
public:
	CRect rect;








	C����������ƮDoc* GetDocument() const;
	
	CPoint m_StartPos, m_EndPos;
	CRect m_rect; 
	bool m_StartToMove;
	CDC AntMemDC;
	CDC FireAntMemDC;
	CDC BearAntMemDC;
	CDC BearAntMemDC2 ;
	
// �۾��Դϴ�.
public:
	void DrawCake(CBufferDC* dc/*, Ant* ant*/);
	void DrawAnt(Ant* ant);
	void MoveToCake(Ant* ant, int x2, int y2);
	void CakeDamage();
	void RotateAntDraw(/*CBufferDC* dc*/);
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected: 
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~C����������ƮView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void PlayWAVEFile();
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};

#ifndef _DEBUG  // ����������ƮView.cpp�� ����� ����
inline C����������ƮDoc* C����������ƮView::GetDocument() const
   { return reinterpret_cast<C����������ƮDoc*>(m_pDocument); }
#endif

