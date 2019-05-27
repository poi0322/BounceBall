
// BounceBallDlg.cpp: 구현 파일
//


#include "stdafx.h"
#include "BounceBall.h"
#include "BounceBallDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CBounceBallDlg 대화 상자

int Ax;
int Start;
int RGB = RGB(0, 0, 0);
int R;
int G;
int B;
void randRGB() {

	R = (BYTE)(rand() % 255);
	G = (BYTE)(rand() % 255);
	B = (BYTE)(rand() % 255);

	RGB = RGB(R, G, B);
}


CBounceBallDlg::CBounceBallDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BOUNCEBALL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBounceBallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRAME, mFrame);
	DDX_Control(pDX, cEdit_CirleNum, mEdit_CircleNum);
	DDX_Control(pDX, cScroll_Red, mScroll_Red);
	DDX_Control(pDX, cScroll_Green, mScroll_Green);
	DDX_Control(pDX, cScroll_Blue, mScroll_Blue);
	DDX_Control(pDX, cEdit_Red, mEdit_Red);
	DDX_Control(pDX, cEdit_Green, mEdit_Green);
	DDX_Control(pDX, cEdit_Blue, mEdit_Blue);
	DDX_Control(pDX, cSlider_dx, mSlider_Dx);
	DDX_Control(pDX, cButton_Start, mButton_Start);
}

BEGIN_MESSAGE_MAP(CBounceBallDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(cButton_CirDraw, &CBounceBallDlg::OnClickedCbuttonCirdraw)
	ON_BN_CLICKED(cButton_RandomCircle, &CBounceBallDlg::OnClickedCbuttonRandomcircle)
	ON_BN_CLICKED(cButton_RandomColor, &CBounceBallDlg::OnClickedCbuttonRandomcolor)
	ON_BN_CLICKED(cButton_Start, &CBounceBallDlg::OnClickedCbuttonStart)
	ON_NOTIFY(NM_RELEASEDCAPTURE, cSlider_dx, &CBounceBallDlg::OnReleasedcaptureCsliderDx)
	ON_WM_CREATE()
	ON_WM_TIMER()
//	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CBounceBallDlg 메시지 처리기

int CBounceBallDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}

BOOL CBounceBallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	mSlider_Dx.SetRange(0, 6);
	mSlider_Dx.SetPos(3);
	Ax = mSlider_Dx.GetPos()-3;



	mScroll_Red.SetScrollRange(0, 255);
	mScroll_Red.SetScrollPos(0);
	mScroll_Green.SetScrollRange(0, 255);
	mScroll_Green.SetScrollPos(0);
	mScroll_Blue.SetScrollRange(0, 255);
	mScroll_Blue.SetScrollPos(0);
	mScroll_Red.EnableScrollBar(ESB_ENABLE_BOTH);
	mScroll_Green.EnableScrollBar(ESB_ENABLE_BOTH);
	mScroll_Blue.EnableScrollBar(ESB_ENABLE_BOTH);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBounceBallDlg::OnPaint()
{
	//Invalidate();
	/*
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

	}*/
	CPaintDC dc(this);
	//int num = GetDlgItemInt(cEdit_CirleNum);
	CDC* p = mFrame.GetDC();
	CBrush brush, *oldbrush;

	brush.CreateSolidBrush(RGB);
	oldbrush = p->SelectObject(&brush);
	for (vector<Object>::iterator i = ball.begin(); i != ball.end(); i++) {
		p->SetDCBrushColor(RGB);
		p->Ellipse(GETXY(i));
	}
	p->SelectObject(oldbrush);
	brush.DeleteObject();

	setRGBText();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBounceBallDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBounceBallDlg::OnClickedCbuttonCirdraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
	CString str;
	int num = GetDlgItemInt(cEdit_CirleNum);
	CRect rect;
	mFrame.GetWindowRect(&rect);
	ScreenToClient(&rect);

	int nWidth = rect.Width();
	int nHeight = rect.Height();

	Object temp;

	ball.clear();
	for (int j = 0; j < num; j++) {
		temp.xy.x = rand() % (nWidth - DEFAULT_RAD-DEFAULT_RAD) + DEFAULT_RAD;
		temp.xy.y = rand() % (nHeight - DEFAULT_RAD - DEFAULT_RAD) + DEFAULT_RAD;
		ball.push_back(temp);
			for (int k = 0; k < j; k++) {
				if ((ball.at(j).xy.x - ball.at(k).xy.x)*(ball.at(j).xy.x - ball.at(k).xy.x) + (ball.at(j).xy.y - ball.at(k).xy.y)*(ball.at(j).xy.y - ball.at(k).xy.y) < 80 * 80) { // 겹침
					ball.pop_back();
					j--;
					break;
				}
			}
	}

}


void CBounceBallDlg::OnClickedCbuttonRandomcircle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	SetDlgItemInt(cEdit_CirleNum, rand() % 10 + 1,1);
	OnClickedCbuttonCirdraw();
}


void CBounceBallDlg::OnClickedCbuttonRandomcolor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	randRGB();
	mScroll_Red.SetScrollPos(R);
	mScroll_Green.SetScrollPos(G);
	mScroll_Blue.SetScrollPos(B);

	OnPaint();
	//Invalidate();
}


void CBounceBallDlg::OnClickedCbuttonStart()
{
	CString str;
	mButton_Start.GetWindowTextW(str);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (str == "Start!") {
		for (int i = 0; i < ball.size(); i++) {
			ball.at(i).move();
		}

		SetTimer(BALL_TIMER, 10, NULL);
		mButton_Start.SetWindowTextW(_T("Stop!"));
	}
	else {
		KillTimer(BALL_TIMER);
		mButton_Start.SetWindowTextW(_T("Start!"));
	}
	//Invalidate();
}


void CBounceBallDlg::OnReleasedcaptureCsliderDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Ax = mSlider_Dx.GetPos() - 3;
	*pResult = 0;
}



void CBounceBallDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	mFrame.GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	
	/*
	int nWidth = rect.right - rect.left;
	int nHeight = rect.top - rect.bottom;
	*/
	if (nIDEvent == BALL_TIMER) {
		for (int i = 0; i < ball.size(); i++) {
			ball.at(i).move();
			ball.at(i).collision(nWidth, nHeight);
			ball.at(i).gravity();
		}
		Invalidate();

	}
	
	CDialog::OnTimer(nIDEvent);
}

void CBounceBallDlg::setRGBText()
{
	CString Red;
	Red.Format(_T("%d"), R);
	CString Green;
	Green.Format(_T("%d"), G);
	CString Blue;
	Blue.Format(_T("%d"), B);
	mEdit_Red.SetWindowTextW(Red);
	mEdit_Green.SetWindowTextW(Green);
	mEdit_Blue.SetWindowTextW(Blue);
}


void Object::move()
{
	xy.x += dx;
	xy.y += dy;
	action = ACTION_MOVE;
}

void Object::collision(int nWidth, int nHeight)
{
	if (xy.x - radius <= 0) { //왼쪽벽
		LEFT();
		if (xy.x + radius  <= -10)
		{
			xy.x = 0 + radius;
		}
	}
	if (xy.x + radius >= nWidth) { //오른쪽 벽
		RIGHT();
		if (xy.x + radius + 10 >= nWidth)
		{
			xy.x = nWidth - radius;
		}
	}
	if (xy.y + radius >= nHeight) { //바닥
		STOP();
	}

}

void Object::gravity()
{
	if (action==ACTION_MOVE) {
		dy += GRAVITY;
		dx += Ax;
	}
	if (action == ACTION_STOP) {
		TO_NEG(dy);
		dy *= elasticity; //탄성계수
	}
	if (action == LEFT_WALL) {
		TO_POS(dx);
		dx *= WALL_ELASTICITY;
		dy += 1;
	}
	if (action == RIGHT_WALL) {
		TO_NEG(dx);
		dx *= WALL_ELASTICITY;
		dy += 1;
	}
}





void CBounceBallDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nSBCode)
	{
	case SB_LINELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 1);
		break;
	case SB_LINERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 1);
		break;
	case SB_PAGELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 30);
		break;
	case SB_PAGERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 30);
		break;
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
		break;
	}
	R = mScroll_Red.GetScrollPos();
	G = mScroll_Green.GetScrollPos();
	B = mScroll_Blue.GetScrollPos();
	RGB = RGB(R, G, B);
	OnPaint();


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
