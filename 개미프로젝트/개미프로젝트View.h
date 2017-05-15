
// 개미프로젝트View.h : C개미프로젝트View 클래스의 인터페이스
//

#pragma once
#include "Ant.h"
#include "BufferDC.h"

class C개미프로젝트View : public CView
{
protected: // serialization에서만 만들어집니다.
	C개미프로젝트View();
	DECLARE_DYNCREATE(C개미프로젝트View)

// 특성입니다.
public:
	CRect rect;








	C개미프로젝트Doc* GetDocument() const;
	
	CPoint m_StartPos, m_EndPos;
	CRect m_rect; 
	bool m_StartToMove;
	CDC AntMemDC;
	CDC FireAntMemDC;
	CDC BearAntMemDC;
	CDC BearAntMemDC2 ;
	
// 작업입니다.
public:
	void DrawCake(CBufferDC* dc/*, Ant* ant*/);
	void DrawAnt(Ant* ant);
	void MoveToCake(Ant* ant, int x2, int y2);
	void CakeDamage();
	void RotateAntDraw(/*CBufferDC* dc*/);
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
protected: 
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~C개미프로젝트View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // 개미프로젝트View.cpp의 디버그 버전
inline C개미프로젝트Doc* C개미프로젝트View::GetDocument() const
   { return reinterpret_cast<C개미프로젝트Doc*>(m_pDocument); }
#endif

