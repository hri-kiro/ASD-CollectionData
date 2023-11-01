
// KIRODlg.h: 헤더 파일
//

#pragma once
#include "defines.h"
#include "VideoTag.h"

// CKIRODlg 대화 상자

class CKIRODlg : public CDialogEx
{
// 생성입니다.
public:
	CKIRODlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KIRO_DIALOG };
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
	afx_msg void OnBnClickedMonitor2();
	afx_msg void OnBnClickedLogin();
	CButton m_bTag;
	CButton m_bMonitor;
	CEdit m_hID;
	CEdit m_hPW;
	CDatabase m_db;
	CRecordset* m_pRs;
	Monitoring* m_pMonitorDlg;
	AKinect_Monitoring* m_pAKinect_MonitoringDlg;
	Patient_Info* m_pPatient_InfoDlg;
	VideoTagging* m_videoTag;
	VideoTag* m_videoTagging;

	afx_msg void OnBnClickedTag();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedPaitentinfo();
	CButton m_bPatient;
	afx_msg void OnBnClickedSurvey();
	CButton m_bSurv;
	CButton m_TaggingN;
	afx_msg void OnBnClickedTagg();
};
