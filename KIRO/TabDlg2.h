#pragma once
#include "defines.h"

// TabDlg2 대화 상자

class TabDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(TabDlg2)

public:
	TabDlg2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabDlg2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;
};
