#pragma once
#include "defines.h"
#include "axismediacontrol.h"


// AKinect_Monitoring 대화 상자
using namespace Kinect;
class AKinect_Monitoring : public CDialogEx
{
	DECLARE_DYNAMIC(AKinect_Monitoring)

public:
	AKinect_Monitoring(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AKinect_Monitoring();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD_CAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//------------------------kinect thread
	HANDLE m_ThreadCAM1;
	bool m_Threadcam1;
	static UINT threadCAM1(LPVOID pParam);

	HANDLE m_ThreadCAM2;
	bool m_Threadcam2;
	static UINT threadCAM2(LPVOID pParam);

	HANDLE m_ThreadCAM3;
	bool m_Threadcam3;
	static UINT threadCAM3(LPVOID pParam);

	HANDLE m_ThreadCAM4;
	bool m_Threadcam4;
	static UINT threadCAM4(LPVOID pParam);

	HANDLE m_ThreadCAM5;
	bool m_Threadcam5;
	static UINT threadCAM5(LPVOID pParam);

	HANDLE m_ThreadCAM6;
	bool m_Threadcam6;
	static UINT threadCAM6(LPVOID pParam);

	HANDLE m_ThreadCAM7;
	bool m_Threadcam7;
	static UINT threadCAM7(LPVOID pParam);

	HANDLE m_ThreadCAM8;
	bool m_Threadcam8;
	static UINT threadCAM8(LPVOID pParam);
	//--------------------------------------

	Azure_Kinect kinect1;
	Azure_Kinect kinect2;
	Azure_Kinect kinect3;
	Azure_Kinect kinect4;
	Azure_Kinect kinect5;
	Azure_Kinect kinect6;
	Azure_Kinect kinect7;
	Azure_Kinect kinect8;
	void device_init();
//	CEdit m_Edit_Status;
	//---녹화시간관련
	int timer;

	//	CEdit m_Edit;
//	CEdit m_Edit_Timer;
	afx_msg void OnBnClickedCamon();
	afx_msg void OnBnClickedRecordstart();
	afx_msg void OnBnClickedRecordstop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CEdit m_Edit_Timer;
	CEdit m_Edit_Status;
	CEdit m_edit_ResearchNumber;
	CComboBox m_cADOS;
	CComboBox m_cBedevel;

	//--ip카메라 관련

	CString m_ipText_1;
	CString m_ipText_2;
	CString m_ipText_3;
	CString m_ipText_4;
	CString m_ipText_5;
	CString m_ipText_6;
	CString m_ipText_7;

	CString m_user;
	CString m_pass;
	CString m_type;

	CString m_File_1;
	CString m_File_2;
	CString m_File_3;
	CString m_File_4;
	CString m_File_5;
	CString m_File_6;
	CString m_File_7;

	afx_msg void OnBnClickedIpcamon();
	CAxisMediaControl m_AMC_1;
	CAxisMediaControl m_AMC_2;
	CAxisMediaControl m_AMC_3;
	CAxisMediaControl m_AMC_4;
	CAxisMediaControl m_AMC_5;
	CAxisMediaControl m_AMC_6;
	CAxisMediaControl m_AMC_7;

	afx_msg void OnBnClickedAudioon();

	afx_msg void OnBnClickedButton3();
};
