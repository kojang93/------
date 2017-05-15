
// ����������ƮView.cpp : C����������ƮView Ŭ������ ����
//

#include "stdafx.h"

#include <mmsystem.h> 
#pragma comment(lib, "winmm")
#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"


// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "����������Ʈ.h"
#endif
#include "MyDialog.h"
#include "����������ƮDoc.h"
#include "����������ƮView.h"
#include "Ant.h"
#include "Hell.h"
#include <random>
#include <vector>
#include "BufferDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
bool AntClick=false;
bool ItemClick=false;
enum Click{none, Item1, Item2, Item3};
enum Title { menu, how, ready, gameon };
Click LClick=none;
Title title = menu;

int Record;
int CakeHP = 1000; //����ũ 
int CakeFHP = 1000; //����ũ Ǯ����ġ�� 
//int AntDamage = 100;
int ItemX = 1050;//������ ��ǥ
int ItemY = 0;
int Item2X = 1200;
int Item2Y = 0;
int Item3X = 1300;
int Item3Y = 0;
int cakeX = 650;//����ũ �⺻��ǥ
int cakeY = 325;//����ũ �⺻��ǥ


CString Text;
CString Text2;

int score; //���� �ʴ���
int second = 0;
int OnTimerSecond=10;

int cost;// ������ ��� �ڽ�Ʈ
int count = 0;
CList<Ant> AntList;//������ ���̵�
CList<Hell> HellList;//����Ʈ
Ant* ClickAnt;//Ŭ���� ���� ����Ű�� ������ 


// C����������ƮView

IMPLEMENT_DYNCREATE(C����������ƮView, CView)

BEGIN_MESSAGE_MAP(C����������ƮView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// C����������ƮView ����/�Ҹ�


int getRandomXY(int min, int max) //���� �ѹ� ����
{
	std::random_device rn; 
	std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<int> range(min, max);

	return range(rnd);
}

void CreateAnt()//���� ��ǥ ���� �����ϰ� ����Ʈ�� �߰�
{
	int random=getRandomXY(0, 3);
	
	if (random == 0)
	{
		Ant ant(getRandomXY(0, 1500), 0, 1);
		AntList.AddTail(ant);
	}
	else if (random == 1)
	{
		Ant ant(0, getRandomXY(0, 1000), 1);
		AntList.AddTail(ant);
	}
	else if (random == 2)
	{
		Ant ant(getRandomXY(0, 1500), 1000 ,1);
		AntList.AddTail(ant);
	}
	else {
		Ant ant(1500, getRandomXY(0, 1000), 1);
		AntList.AddTail(ant);
	}

	//Ant ant(getRandomXY(0,1000),getRandomXY(0,900));
	//AntList.AddTail(ant);
}


void C����������ƮView::DrawAnt(Ant* ant) //���� ��ü���Ѱ��ָ� ���� ��ü �ȿ� ��ǥ�ش��ϴ� ��Ʈ�� �׸�
{
	CBufferDC dc(this);
	CClientDC cdc(this);
	BITMAP bmpInfo4;
	CBitmap bmp4, *old4;

	bmp4.LoadBitmap(IDB_BITMAP2);
	bmp4.GetBitmap(&bmpInfo4);


	AntMemDC.CreateCompatibleDC(&dc);
	old4 = (CBitmap *)AntMemDC.SelectObject(bmp4);
	

	dc.TransparentBlt(ant->AntX, ant->AntY, bmpInfo4.bmWidth / 2, bmpInfo4.bmHeight / 2, &AntMemDC, 0, 0, bmpInfo4.bmWidth, bmpInfo4.bmHeight, RGB(255, 255, 255));
	//dc.BitBlt(ant->AntX, ant->AntY, bmpInfo.bmWidth / 2, bmpInfo.bmHeight / 2, &AntMemDC, 0, 0, SRCCOPY);
	//cdc.BitBlt(ant->AntX, ant->AntY, bmpInfo.bmWidth / 2, bmpInfo.bmHeight / 2, &AntMemDC, 0, 0, SRCCOPY);
	AntMemDC.SelectObject(old4);
	dc.DeleteDC();
	AntMemDC.DeleteDC();
	bmp4.DeleteObject();
}

void Reset()
{
	CakeHP = 1000;
		AntList.RemoveAll();
	cost = 0;
	score = 0;
	title = ready;
}

bool CheckCursor()
{
	POINT point;
	CWnd *pWnd = AfxGetMainWnd();

	HWND hWnd = pWnd->m_hWnd;
	GetCursorPos(&point);
	ScreenToClient(hWnd, &point);

	if (point.x > 200 && point.x < 500 && point.y >500 && point.y < 750)
	{
		return true;
	}
	else {
		return false;
	}
}
void DrawHp(CDC* pDC)
{
	
	CDC MemDC1;
	BITMAP bmpInfo1;
	CBitmap bmp1;

	bmp1.LoadBitmap(IDB_BITMAP18);
	bmp1.GetBitmap(&bmpInfo1);
	MemDC1.CreateCompatibleDC(pDC);
	MemDC1.SelectObject(&bmp1);

	CDC MemDC2;
	BITMAP bmpInfo2;
	CBitmap bmp2;

	bmp2.LoadBitmap(IDB_BITMAP19);
	bmp2.GetBitmap(&bmpInfo2);
	MemDC2.CreateCompatibleDC(pDC);
	MemDC2.SelectObject(&bmp2);

	pDC->TransparentBlt(660, 450, 120, 30, &MemDC1, 0, 0, bmpInfo1.bmWidth, bmpInfo1.bmHeight, RGB(255, 255, 255));



	pDC->TransparentBlt(670, 450, CakeHP/10, 30, &MemDC2, 0, 0, bmpInfo2.bmWidth, bmpInfo2.bmHeight, RGB(255, 255, 255));

}
void Drawtitle(CDC* pDC) ////////////
{

	CDC MemDC1;
	BITMAP bmpInfo1;
	CBitmap bmp1;

	bmp1.LoadBitmap(IDB_BITMAP17);
	bmp1.GetBitmap(&bmpInfo1);
	MemDC1.CreateCompatibleDC(pDC);
	MemDC1.SelectObject(&bmp1);

	CDC MemDC2;
	BITMAP bmpInfo2;
	CBitmap bmp2;

	bmp2.LoadBitmap(IDB_BITMAP14);
	bmp2.GetBitmap(&bmpInfo2);
	MemDC2.CreateCompatibleDC(pDC);
	MemDC2.SelectObject(&bmp2);

	CDC MemDC3;
	BITMAP bmpInfo3;
	CBitmap bmp3;

	bmp3.LoadBitmap(IDB_BITMAP15);
	bmp3.GetBitmap(&bmpInfo3);
	MemDC3.CreateCompatibleDC(pDC);
	MemDC3.SelectObject(&bmp3);

	CDC MemDC4;
	BITMAP bmpInfo4;
	CBitmap bmp4;


	bmp4.LoadBitmap(IDB_BITMAP16);
	bmp4.GetBitmap(&bmpInfo4);
	MemDC4.CreateCompatibleDC(pDC);
	MemDC4.SelectObject(&bmp4);

	if (title == menu) //���� �޴� ȭ��
	{
		pDC->TransparentBlt(200, 300, 300, 150, &MemDC2, 0, 0, bmpInfo2.bmWidth, bmpInfo2.bmHeight, RGB(255, 255, 255));


		pDC->TransparentBlt(200, 500, 300, 150, &MemDC3, 0, 0, bmpInfo3.bmWidth, bmpInfo3.bmHeight, RGB(255, 255, 255));

		if (CheckCursor())
		{
			pDC->TransparentBlt(900, 200, 500, 500, &MemDC4, 0, 0, bmpInfo4.bmWidth, bmpInfo4.bmHeight, RGB(255, 255, 255));
		}

	}
	else if (title == ready)
	{

		pDC->TransparentBlt(400, 200, 700, 500, &MemDC1, 0, 0, bmpInfo1.bmWidth, bmpInfo1.bmHeight, RGB(255, 255, 255));

	}
}
void C����������ƮView::RotateAntDraw()//����Ʈ ��ȸ�ϸ鼭 �ٱ׸�
{
	//GetClientRect(&rect);
	//CBufferDC dc(this);


	//POSITION pos = AntList.GetHeadPosition();
	//
	//	
	//while (pos != NULL) {
	//	MoveToCake(&AntList.GetAt(pos), cakeX, cakeY);//ȭ�� �߾����� �̵�
	//	//DrawAnt(&AntList.GetAt(pos));
	//	DrawCake(&dc);
	//	AntList.GetNext(pos);
	//}
}

void CheckHellcount()//���������� hpȮ���ϰ� 0�� �Ǹ� ���ش�. //////////////////////////////////////////////////////////////////////////////////////////////
{
	if (HellList.GetHead().count>0)
	{
		HellList.GetHead().count--;
	}
	else if (HellList.GetHead().count == 0)
	{
		HellList.RemoveAll();
	}
}
C����������ƮView::C����������ƮView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	m_StartToMove = false;
	//CreateAnt();
}

C����������ƮView::~C����������ƮView()
{
}

BOOL C����������ƮView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
	
}

 void C����������ƮView::OnTimer(UINT_PTR nIDEvent)//�ֱ������� ȣ��Ǵ� �Լ��� ���⼭ ���̵� �̵���Ű�� ���� �׸�***********************************************8
{
	 CBufferDC dc(this);
	 CClientDC cdc(this);
	
	 if (CakeHP != 0) {
		 if (second != 1000)
		 {
			 second += OnTimerSecond;
		 }

		 else if (second == 1000)//1�ʰ� ������
		 {

			 Text.Format(_T("%d"), score);
			 dc.TextOut(rect.right / 2, 0, Text);//�ð����
			 Text.Format(_T("%d"), cost);
			 dc.TextOut(rect.right / 2 + 100, 0, Text);//������ �ڽ�Ʈ ���
			
			 if (title == gameon)
			 {
				 cost += 1;//�ڽ�Ʈ �÷���
				 score += 1;//���� �ð��� � 
				 second = 0;
				 //�� ǥ���ϱ� 
				 CreateAnt();//1�ʸ��� ���̸� �����

				 if (!HellList.IsEmpty())//���̲����� ī��Ʈ üũ�ϴ� �Լ� 
				 {
					 CheckHellcount();
				 }

				 POSITION  posi = AntList.GetTailPosition();
				 if (score < 10) {
					 AntList.GetAt(posi).x = 1;
				 }

				 else if (10 <= score && score < 20) {
					 int rand = getRandomXY(1, 2);
					 AntList.GetAt(posi).x = rand;
					 AntList.GetAt(posi).Velocity = rand;
				 }
				 else if (20 <= score) {
					 int rand2 = getRandomXY(1, 3);
					 AntList.GetAt(posi).x = rand2;
					 AntList.GetAt(posi).Velocity = rand2;
				 }
			 }
		 }

		
		 //����ũ�� �׸���.
		 DrawCake(&dc);
		 Drawtitle(&dc);
		 if (title == gameon)
		 {
			 DrawCake(&dc);//���̵� �׸���
		 }
		cdc.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);


		dc.DeleteDC();
		if (CakeHP == 0) {
				AntList.RemoveAll();
				 MyDialog dlg;
				 dlg.score = score;
				 if (dlg.DoModal() == IDOK)
				 {
					 Reset();
				 }
				 else
				 {
					 Reset();
					 Invalidate();
				 }
			 }

		 
	 }

		 
}

void C����������ƮView::OnDraw(CDC* pDC)
{
	C����������ƮDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
}

void C����������ƮView::CakeDamage()//������ ��ġ�� cake�� �����ϰԵǸ� cake������ ���̰� �ǰ� ���̴� ��������. 
{
	//
	//CBufferDC dc(this);
	//POSITION pos = AntList.GetHeadPosition();
	//while (pos != NULL) {
	//	
	//	if (cakeX-5<=AntList.GetAt(pos).AntX<=cakeX+5&& AntList.GetAt(pos).AntY==cakeY)//����ũ ��ǥ�� ��������  �������� ���Ѵ�. 
	//	{
	//		
	//		CakeHP -= AntDamage;
	//		AntList.RemoveAt(pos);
	//		Invalidate(false);
	//		Text.Format(_T("%d"), CakeHP);
	//		dc.TextOut(100, 100, Text);
	//		///0�̵Ǹ� if�� �ְ� ���� ����Ǵ� ��ƾ �߰� �Ѵ�.
	//		if (CakeHP == 0)
	//		{
	//			CDialog dlg(IDD_DIALOG1);
	//			if (dlg.DoModal() == IDOK)
	//			{
	//				Reset();
	//			}
	//			else
	//			{
	//				Reset();
	//				Invalidate();
	//			}
	//		
	//		}
	//		
	//		break;
	//		
	//	}
	//	else {
	//		AntList.GetNext(pos);
	//		
	//	}
	//	
	//	
 //}
}



bool CheckHell(Ant* ant)//���̰� ���̲����̾ȿ� ������ Ʈ���ȯ
{
	if (HellList.IsEmpty())
	{
		return false;
	}
	else if (HellList.GetHead().HellX > ant->AntX-150  && HellList.GetHead().HellX < ant->AntX  && HellList.GetHead().HellY> ant->AntY-200  && HellList.GetHead().HellY  < ant->AntY-25)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void C����������ƮView::DrawCake(CBufferDC* dc) //����ũ �׸��°� �� ó���� ondrawȣ��Ǵ°����� ȣ���
{
	CDC MemDC, MemDC2, MemDC3,MemDC4, MemDC5, MemDC6;
	BITMAP bmpInfo, bmpInfo2, bmpInfo3,bmpInfo4,bmpInfo5, bmpInfo6;
	CBitmap bmp, bmp2, bmp3,bmp4, bmp5, bmp6, *old, *old2, *old3,*old4, *old5, *old6;

	GetClientRect(&rect);

	MemDC3.CreateCompatibleDC(dc);
	bmp3.LoadBitmap(IDB_BITMAP7);
	bmp3.GetObject(sizeof(bmpInfo3), &bmpInfo3);
	old3 = (CBitmap*)MemDC3.SelectObject(&bmp3);


	dc->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC3, 0, 0, bmpInfo3.bmWidth, bmpInfo3.bmHeight, SRCCOPY);//���
	MemDC3.SelectObject(old3);
	MemDC3.DeleteDC();
	bmp3.DeleteObject();
	
	//cake �׸���

	bmp2.LoadBitmap(IDB_BITMAP4);
	bmp2.GetBitmap(&bmpInfo2);

	MemDC2.CreateCompatibleDC(dc);
	old2 = (CBitmap*)MemDC2.SelectObject(&bmp2);

	bmp4.LoadBitmap(IDB_BITMAP3);
	bmp4.GetBitmap(&bmpInfo4);

	MemDC4.CreateCompatibleDC(dc);
	old4 = (CBitmap*)MemDC4.SelectObject(&bmp4);

	bmp5.LoadBitmap(IDB_BITMAP12);
	bmp5.GetBitmap(&bmpInfo5);

	MemDC5.CreateCompatibleDC(dc);
	old5 = (CBitmap*)MemDC5.SelectObject(&bmp5);

	bmp6.LoadBitmap(IDB_BITMAP13);
	bmp6.GetBitmap(&bmpInfo6);

	MemDC6.CreateCompatibleDC(dc);
	old6 = (CBitmap*)MemDC6.SelectObject(&bmp6);

	if (CakeHP > CakeFHP / 4 * 3)//Ǯ�� ����ũ �׸���
	{
		bmp.LoadBitmap(IDB_BITMAP1);
		bmp.GetBitmap(&bmpInfo);

		MemDC.CreateCompatibleDC(dc);
		old = (CBitmap*)MemDC.SelectObject(&bmp);
		dc->TransparentBlt(cakeX, cakeY, bmpInfo.bmWidth / 3, bmpInfo.bmHeight / 3, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));//����ũ


	}
	else if (CakeHP > CakeFHP / 4 * 2 &&CakeHP <= CakeFHP/4 * 3) //ù��° ������ ���� ����ũ
	{
		bmp.LoadBitmap(IDB_BITMAP5);
		bmp.GetBitmap(&bmpInfo);

		MemDC.CreateCompatibleDC(dc);
		old = (CBitmap*)MemDC.SelectObject(&bmp);
		dc->TransparentBlt(cakeX, cakeY, bmpInfo.bmWidth / 3, bmpInfo.bmHeight / 3, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));//����ũ

	}
	else if (CakeHP > CakeFHP / 4 && CakeHP <=  CakeFHP/ 4 * 2) // �ι�° ������ ���� ����ũ 
	{
		bmp.LoadBitmap(IDB_BITMAP6);
		bmp.GetBitmap(&bmpInfo);

		MemDC.CreateCompatibleDC(dc);
		old = (CBitmap*)MemDC.SelectObject(&bmp);
		dc->TransparentBlt(cakeX, cakeY, bmpInfo.bmWidth / 3, bmpInfo.bmHeight / 3, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));//����ũ

	}
	else if(CakeHP<= CakeFHP/4)
	{
		bmp.LoadBitmap(IDB_BITMAP8);
		bmp.GetBitmap(&bmpInfo);

		MemDC.CreateCompatibleDC(dc);
		old = (CBitmap*)MemDC.SelectObject(&bmp);
		dc->TransparentBlt(cakeX, cakeY, bmpInfo.bmWidth / 3, bmpInfo.bmHeight / 3, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));//����ũ

	}

	DrawHp(dc);

	if (HellList.IsEmpty()) {

	}
	else if (HellList.GetHead().count <=10&&HellList.GetHead().count>=0) 
		dc->TransparentBlt(HellList.GetHead().HellX, HellList.GetHead().HellY, bmpInfo6.bmWidth/2, bmpInfo6.bmHeight/2, &MemDC6, 0, 0, bmpInfo6.bmWidth, bmpInfo6.bmHeight, RGB(255, 255, 255));//������
	
	dc->TransparentBlt(ItemX, ItemY, bmpInfo2.bmWidth/2, bmpInfo2.bmHeight/2, &MemDC2, 0, 0, bmpInfo2.bmWidth, bmpInfo2.bmHeight, RGB(255, 255, 255));//�ĸ�ä
	dc->TransparentBlt(Item2X, Item2Y, bmpInfo4.bmWidth/4, bmpInfo4.bmHeight/4 , &MemDC4, 0, 0, bmpInfo4.bmWidth, bmpInfo4.bmHeight, RGB(255, 255, 255));//��������
	dc->TransparentBlt(Item3X, Item3Y, bmpInfo5.bmWidth / 4, bmpInfo5.bmHeight / 4, &MemDC5, 0, 0, bmpInfo5.bmWidth, bmpInfo5.bmHeight, RGB(255, 255, 255));//����
	


	MemDC.SelectObject(&old);
	MemDC2.SelectObject(&old2);
	MemDC3.SelectObject(&old3);
	MemDC4.SelectObject(&old4);
	MemDC5.SelectObject(&old5);
	MemDC6.SelectObject(&old6);

	MemDC.DeleteDC();
	MemDC2.DeleteDC();
	MemDC3.DeleteDC();
	MemDC4.DeleteDC();
	MemDC5.DeleteDC();
	MemDC6.DeleteDC();

	bmp.DeleteObject();
	bmp2.DeleteObject();
	bmp3.DeleteObject();
	bmp4.DeleteObject();
	bmp5.DeleteObject();
	bmp6.DeleteObject();


	


	POSITION pos = AntList.GetHeadPosition();
	while (pos != NULL) {
		Ant ant = AntList.GetAt(pos);
		BITMAP bmpInfo4, bmpInfo5, bmpInfo6, bmpInfo61;
		CBitmap bmp4, *old4, bmp5, *old5, bmp6, *old6, bmp61, *old61;

		bmp4.LoadBitmap(IDB_BITMAP2);
		bmp4.GetBitmap(&bmpInfo4);
		bmp5.LoadBitmap(IDB_BITMAP9);
		bmp5.GetBitmap(&bmpInfo5);
		bmp6.LoadBitmap(IDB_BITMAP11);
		bmp6.GetBitmap(&bmpInfo6);


		bmp61.LoadBitmap(IDB_BITMAP10);
		bmp61.GetBitmap(&bmpInfo61);

		AntMemDC.CreateCompatibleDC(dc);
		FireAntMemDC.CreateCompatibleDC(dc);
		BearAntMemDC.CreateCompatibleDC(dc);
		BearAntMemDC2.CreateCompatibleDC(dc);
		old4 = (CBitmap *)AntMemDC.SelectObject(&bmp4);
		old5 = (CBitmap *)FireAntMemDC.SelectObject(&bmp5);
		old6 = (CBitmap *)BearAntMemDC.SelectObject(&bmp6);
		old61 = (CBitmap *)BearAntMemDC2.SelectObject(&bmp61);

			if (AntList.GetAt(pos).x == 1) {
				dc->TransparentBlt(ant.AntX, ant.AntY, bmpInfo4.bmWidth / 2, bmpInfo4.bmHeight / 2, &AntMemDC, 0, 0, bmpInfo4.bmWidth, bmpInfo4.bmHeight, RGB(255, 255, 255));
			}
			else if (AntList.GetAt(pos).x == 2) {
				dc->TransparentBlt(ant.AntX, ant.AntY, bmpInfo5.bmWidth / 2, bmpInfo5.bmHeight / 2, &FireAntMemDC, 0, 0, bmpInfo5.bmWidth, bmpInfo5.bmHeight, RGB(255, 255, 255));
			}
			else if (AntList.GetAt(pos).x == 3) {
				if (AntList.GetAt(pos).AntX < rect.right / 2) {
					AntList.GetAt(pos).Velocity = 1;
					AntList.GetAt(pos).AntDamage= 200;
					dc->TransparentBlt(ant.AntX, ant.AntY, bmpInfo6.bmWidth / 3*2, bmpInfo6.bmHeight /3* 2, &BearAntMemDC, 0, 0, bmpInfo6.bmWidth, bmpInfo6.bmHeight, RGB(255, 255, 255));
				}
				else if (AntList.GetAt(pos).AntX >= rect.right / 2) {
					AntList.GetAt(pos).Velocity = 1;
					AntList.GetAt(pos).AntDamage = 200;
					dc->TransparentBlt(ant.AntX, ant.AntY, bmpInfo61.bmWidth / 3*2, bmpInfo61.bmHeight / 3*2, &BearAntMemDC2, 0, 0, bmpInfo61.bmWidth, bmpInfo61.bmHeight, RGB(255, 255, 255));
				}
			}
			AntMemDC.SelectObject(old4);
			FireAntMemDC.SelectObject(old5);
			BearAntMemDC.SelectObject(old6);
			BearAntMemDC2.SelectObject(old61);
			AntMemDC.DeleteDC();
			bmp4.DeleteObject();
			FireAntMemDC.DeleteDC();
			bmp5.DeleteObject();
			BearAntMemDC.DeleteDC();
			BearAntMemDC2.DeleteDC();
			bmp6.DeleteObject();
			bmp61.DeleteObject();


			if (CheckHell(&AntList.GetAt(pos)))//�������� �������� ������ ������������ ����. 
			{

			}
			else {
				MoveToCake(&AntList.GetAt(pos), cakeX + 50, cakeY + 50);
			}

			if ( AntList.GetAt(pos).AntX < cakeX+100 && AntList.GetAt(pos).AntX > cakeX&& AntList.GetAt(pos).AntY < cakeY+100&& AntList.GetAt(pos).AntY>cakeY) {//����ũ ��ǥ�� ��������  �������� ���Ѵ�. 
					CakeHP -= AntList.GetAt(pos).AntDamage;
					AntList.RemoveAt(pos);
					Invalidate(false);

					///0�̵Ǹ� if�� �ְ� ���� ����Ǵ� ��ƾ �߰� �Ѵ�.

					break;	
			}
			else
				AntList.GetNext(pos);
		}

	
	
	Text.Format(_T("%d"), score);
	dc->TextOut(rect.right / 2, 0, Text);//�ð����
	Text.Format(_T("%d"), cost);
	dc->TextOut(rect.right / 2 + 100, 0, Text);//������ �ڽ�Ʈ ���
	
}



void C����������ƮView::MoveToCake(Ant* ant, int x2, int y2) //���� �˰��� �Ἥ ���� ��ǥ �̵���Ű�°���
{
	/*AntX += 1;
	AntY += 1;*/
	int addX, addY;
	int dx, dy;

	dx = x2 - ant->AntX;
	dy = y2 - ant->AntY;


	if (dx < 0)
	{
		addX = -1;
		dx = -dx;
	}
	else
	{
		addX = 1;
	}
	if (dy < 0)
	{
		addY = -1;
		dy = -dy;
	}
	else
	{
		addY = 1;
	}

	int x = ant->AntX;
	int y = ant->AntY;

	if (dx >= dy)
	{
		/*for (int i = 0; i < dx; i++)
		{*/
		ant->AntX += addX * ant->Velocity;
		ant->count += dy;
		if (ant->count >= dx)
		{
			ant->AntY += addY * ant->Velocity;
			ant->count -= dx;
		}
	}
	else
	{
		/*for (int i = 0; i < dy; i++)
		{*/
		ant->AntY += addY * ant->Velocity;
		ant->count += dx;
		if (count >= dy)
		{
			ant->AntX += addX * ant->Velocity;
			ant->count -= dy;
		}

	}
	
}

// C����������ƮView �μ�

BOOL C����������ƮView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void C����������ƮView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void C����������ƮView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// C����������ƮView ����

#ifdef _DEBUG
void C����������ƮView::AssertValid() const
{
	CView::AssertValid();
}

void C����������ƮView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C����������ƮDoc* C����������ƮView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C����������ƮDoc)));
	return (C����������ƮDoc*)m_pDocument;
}
#endif //_DEBUG


// C����������ƮView �޽��� ó����

int C����������ƮView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	
	// TODO:  Add your specialized creation code here
	if (CakeHP != 0)
		SetTimer(1, OnTimerSecond, NULL);
	else
		SetTimer(0, 0, NULL);

	PlayWAVEFile();
	return 0;
}


bool ItemOn = false;

void C����������ƮView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (title == menu)
	{

		if (point.x > 200 && point.x < 500 && point.y > 300 && point.y < 450)
		{
			title = ready;
		}
	}
	else if (title == ready) //��ŸƮ ȭ�鿡�� 
	{
		title = gameon;
	}
	else if (title == gameon)
	{
		if (point.x > ItemX && point.x < ItemX + 300 && point.y>0 && point.y < 0 + 100 && ItemOn == false && cost >= 2) // �������� �������� //�ڽ�Ʈ�� 3�̻��϶�
		{
			ItemOn = true;
			LClick = Item1;
			m_StartPos = point;

		}

		/*else if (point.x > Item2X && point.x < Item2X + 300 && point.y>0 && point.y < 0 + 100 && ItemOn == false )
		{
		ItemOn = true;
		LClick = Item2;
		m_StartPos = point;
		}*/
		else if (point.x > Item2X && point.x < Item2X + 300 && point.y>0 && point.y < 0 + 100 && ItemOn == false && HellList.IsEmpty())//���������� ���� 
		{
			ItemOn = true;
			LClick = Item3;
			m_StartPos = point;
		}

		else if (ItemOn == false)
		{ // �������� ������ �ʾ�����
			POSITION pos = AntList.GetHeadPosition();

			while (pos != NULL) {

				if (point.x > AntList.GetAt(pos).AntX&&point.x<AntList.GetAt(pos).AntX + 60 && point.y>AntList.GetAt(pos).AntY&&point.y < AntList.GetAt(pos).AntY + 80)//Ŭ�������� ���콺 ��ǥ�� �ش��ϴ� ���̸� ����Ʈ���� ã��
				{

					ClickAnt = &AntList.GetAt(pos);
					m_StartPos = point;
					m_StartToMove = true;//���콺 �����̱� ������
					break;
				}
				else {
					AntList.GetNext(pos);
				}
			}
			SetCapture();
		}


		else if (ItemOn)
		{
			if (LClick == Item1) { // ������1�� ��µǾ�����!!!!!!!
				POSITION pos = AntList.GetHeadPosition();

				while (pos != NULL) {

					if (point.x > AntList.GetAt(pos).AntX && point.x<AntList.GetAt(pos).AntX + 60 && point.y>AntList.GetAt(pos).AntY&&point.y < AntList.GetAt(pos).AntY + 80 )//Ŭ�������� ���콺 ��ǥ�� �ش��ϴ� ���̸� ����Ʈ���� ã��
					{

						AntList.RemoveAt(pos);

						ItemOn = false;
						LClick = none;

						Invalidate();
						cost -= 2;
						break;
					}
					else {
						AntList.GetNext(pos);
					}
				}
			}

			else if (LClick == Item2) //������ �� Ŭ�������� 
			{
				POSITION pos = AntList.GetHeadPosition();
				int killcount = 5;/////���� �ִ�ų ī��Ʈ
				bool check = false;
				while (pos != NULL) {
					score += 1;
					if (point.x > AntList.GetAt(pos).AntX && point.x<AntList.GetAt(pos).AntX + 300 && point.y>AntList.GetAt(pos).AntY && point.y < AntList.GetAt(pos).AntY + 300)//Ŭ�������� ���콺 ��ǥ�� �ش��ϴ� ���̸� ����Ʈ���� ã��
					{
						check = true;
						POSITION remove_pos = pos;
						/*AntList.RemoveAt(pos);*/

						killcount -= 1;
						AntList.GetNext(pos);
						AntList.RemoveAt(remove_pos);

						if (killcount == 0)
						{
							break;
						}
					}
					else {
						AntList.GetNext(pos);
					}
				}
				if (check == true) {
					LClick = none;
					cost -= 4;
					Invalidate();
					ItemOn = false;
				}
			}


			else if (LClick == Item3)//���� ������ �����. 
			{
				Hell hell(point.x, point.y, 10);
				HellList.AddTail(hell);
				//AntHell = new Hell(point.x, point.y,10);
				LClick = none;
				cost -= 6;
				ItemOn = false;//������ ���

			}
		}

	}

	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}


void C����������ƮView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	
		// TODO: Add your message handler code here and/or call default
		if (m_StartToMove) {
			m_EndPos = point;
			CPoint pos = m_EndPos - m_StartPos;
			m_StartPos = point;

			ClickAnt->AntX = point.x;//�����϶����� ������ ��ǥ�� ���콺 ������ ��ǥ�� ������
			ClickAnt->AntY = point.y;

		}
		
	
		CView::OnMouseMove(nFlags, point);
}


void C����������ƮView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

   
		if (m_StartToMove == true) {

			m_EndPos = point;
			Invalidate();
		}
		ReleaseCapture();
		//ant.Setdxdy(point.x, point.y);
	m_StartToMove = false;
	ClickAnt = NULL;
	


	CView::OnLButtonUp(nFlags, point);
}


BOOL C����������ƮView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return true;
}
void C����������ƮView::PlayWAVEFile()
{
	MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS ����ü ���� 
	mciOpen.lpstrDeviceType = TEXT("mpegvideo");  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	mciOpen.lpstrElementName = TEXT("Oh!MyCake!���.mp3"); // �����̸�
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)&mciOpen);

	MCI_PLAY_PARMS mciPlay;
	UINT dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)&mciPlay);
}
