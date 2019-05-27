
// BounceBallDlg.h: 헤더 파일
//
#include <iostream>
#include <vector>

using namespace std;
#pragma once

#define CIRCLE 0
#define SQUARE 1

#define GRAVITY 1
#define BALL_ELASTICITY (0.9)
#define DEFAULT_RAD 40
#define WALL_ELASTICITY (0.7)

#define ACTION_MOVE 0
#define ACTION_STOP 1
#define ACTION_IDLE 2
#define LEFT_WALL	3
#define RIGHT_WALL	4

#define BALL_TIMER 1
#define COLOR_TIMER 2

#define ABS(D) ((D) >= 0 ? (D) : -(D))
#define TO_POS(D) ((D)=(D)>=0 ? (D) : -(D))
#define TO_NEG(D) ((D)=(D)>=0 ? -(D) : (D))
#define GETXY(i) i->xy.x - i->radius, i->xy.y - i->radius, i->xy.x + i->radius, i->xy.y + i->radius

class Object {
public:
	CPoint xy;	//xy좌표
	int dx, dy;	//xy속도
	int radius;	//반지름
	double elasticity;	//탄성
	int action;	//공의 상태
	int shape;
public:
	Object() {
		CPoint point;
		this->xy = point;
		this->dx = 0;
		this->dy = 0;
		this->radius = DEFAULT_RAD;
		this->elasticity = BALL_ELASTICITY;
		this->action = ACTION_IDLE;
	}
	void IDLE() { this->action = ACTION_IDLE; }
	void MOVE() { this->action = ACTION_MOVE; }
	void STOP() { this->action = ACTION_STOP; }
	void LEFT() { this->action = LEFT_WALL; }
	void RIGHT() { this->action = RIGHT_WALL; }

	void move();
	void collision(int nWidth, int nHeight);
	void gravity();

};

// CBounceBallDlg 대화 상자
class CBounceBallDlg : public CDialog
{
// 생성입니다.
public:
	CBounceBallDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOUNCEBALL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClickedCbuttonCirdraw();
	afx_msg void OnClickedCbuttonRandomcircle();
	afx_msg void OnClickedCbuttonRandomcolor();
	afx_msg void OnClickedCbuttonStart();
	CStatic mFrame;
	CEdit mEdit_CircleNum;
	CScrollBar mScroll_Red;
	CScrollBar mScroll_Green;
	CScrollBar mScroll_Blue;
	CEdit mEdit_Red;
	CEdit mEdit_Green;
	CEdit mEdit_Blue;
	CSliderCtrl mSlider_Dx;
	CButton mButton_Start;

public:
	vector<Object> ball;
	
	afx_msg void OnReleasedcaptureCsliderDx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	void setRGBText();
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
