#pragma once
#include "defines.h"
#include "XLEzAutomation.h"
extern patient patient_info;

// VideoTag 대화 상자

class VideoTag : public CDialogEx
{
	DECLARE_DYNAMIC(VideoTag)

public:
	VideoTag(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~VideoTag();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAGGING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedVideo();
	afx_msg void OnBnClickedCut();
	virtual BOOL OnInitDialog();
	CEdit m_rnum;
	afx_msg void OnBnClickedUpload(); 
	void DeleteAllFile(CString path);
	vector<thread> threadV;
	static void systemCall(CString cmd);
	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;
};
