#pragma once

#include "defines.h"

// TabDlg1 대화 상자

class TabDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(TabDlg1)

public:
	TabDlg1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabDlg1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;
	afx_msg void OnBnClickedSave();
	CEdit m_ea;
	CEdit m_ebv;
	CEdit m_bnv;
	CEdit m_env;
	CEdit m_c;
	CEdit m_d;
	CEdit m_eR;
};
