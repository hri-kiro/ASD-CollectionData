#pragma once
#include "defines.h"
extern patient patient_info;
// BDV 대화 상자

class BDV : public CDialogEx
{
	DECLARE_DYNAMIC(BDV)

public:
	BDV(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~BDV();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BDV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_bdvType;
	CComboBox m_com;
	CEdit m_score;
	CEdit m_rnum;
	virtual BOOL OnInitDialog();
};
