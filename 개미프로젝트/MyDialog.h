#pragma once
#include "afxwin.h"


// MyDialog dialog

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)
	int score;
public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnStnClickedscore();
	CStatic m_score;
};
