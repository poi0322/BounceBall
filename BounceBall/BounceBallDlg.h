
// BounceBallDlg.h: 헤더 파일
//

#pragma once


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
	afx_msg void OnClickedCbuttonSqudraw();
	afx_msg void OnClickedCbuttonStart();
	CStatic mFrame;
	CEdit mEdit_CircleNum;
	CScrollBar mScroll_Red;
	CScrollBar mScroll_Green;
	CScrollBar mScroll_Blue;
	CEdit mEdit_Red;
	CEdit mEdit_Green;
	CEdit mEdit_Blue;
	CEdit mEdit_SquareNum;
};
