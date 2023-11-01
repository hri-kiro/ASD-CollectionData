#pragma once

#include "defines.h"

class TabDlg1;
class TabDlg2; 
struct patient;
extern patient patient_info;

// Monitoring 대화 상자

class Monitoring : public CDialogEx
{
	DECLARE_DYNAMIC(Monitoring)

public:
	Monitoring(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Monitoring();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABMASTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnTcnSelchangeTabcon(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_Tab;
	TabDlg1* m_Tab1;
	TabDlg2* m_Tab2;
	virtual BOOL OnInitDialog();
	CEdit m_hRnum;
	afx_msg void OnBnClickedModify();
	CEdit m_eRNum;

	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;
};
