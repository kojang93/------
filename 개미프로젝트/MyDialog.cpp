// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "개미프로젝트.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_score, m_score);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	
END_MESSAGE_MAP()


// MyDialog message handlers


BOOL MyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString Text;
	Text.Format(_T("%d점"), score);

	m_score.SetWindowTextW(Text);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void MyDialog::OnStnClickedscore()
{
	// TODO: Add your control notification handler code here
}
