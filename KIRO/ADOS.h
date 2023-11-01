#pragma once
#include "defines.h"
extern patient patient_info;

// ADOS 대화 상자

class ADOS : public CDialogEx
{
	DECLARE_DYNAMIC(ADOS)

public:
	ADOS(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ADOS();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADOS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_adosType;
	CComboBox m_com;
	CEdit m_score;
	CEdit m_rnum;
	virtual BOOL OnInitDialog();
};
