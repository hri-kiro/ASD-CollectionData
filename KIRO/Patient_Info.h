#pragma once

#include "defines.h"
// Patient_Info 대화 상자
struct patient;
extern patient patient_info;

class Patient_Info : public CDialogEx
{
	DECLARE_DYNAMIC(Patient_Info)

public:
	Patient_Info(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Patient_Info();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATIENTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cGender;
	CComboBox m_cDiagnosis;
	CEdit m_eResearchNumber;
	CEdit m_eSubjectNumber;
	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedModify();
	CEdit m_eAge;
	CDateTimeCtrl m_RDate;
	CComboBox m_adostype;
	CComboBox m_bedeveltype;
};
