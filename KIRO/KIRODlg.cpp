
// KIRODlg.cpp: 구현 파일
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "KIRO.h"
#include "KIRODlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKIRODlg 대화 상자



CKIRODlg::CKIRODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KIRO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKIRODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAG, m_bTag);
	DDX_Control(pDX, IDC_MONITOR2, m_bMonitor);
	DDX_Control(pDX, IDC_ID, m_hID);
	DDX_Control(pDX, IDC_PW, m_hPW);
	DDX_Control(pDX, IDC_PAITENTINFO, m_bPatient);
	DDX_Control(pDX, IDC_SURVEY, m_bSurv);
	DDX_Control(pDX, IDC_TAGG, m_TaggingN);
}

BEGIN_MESSAGE_MAP(CKIRODlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MONITOR2, &CKIRODlg::OnBnClickedMonitor2)
	ON_BN_CLICKED(IDC_LOGIN, &CKIRODlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_TAG, &CKIRODlg::OnBnClickedTag)
	ON_BN_CLICKED(IDC_PAITENTINFO, &CKIRODlg::OnBnClickedPaitentinfo)
	ON_BN_CLICKED(IDC_SURVEY, &CKIRODlg::OnBnClickedSurvey)
	ON_BN_CLICKED(IDC_TAGG, &CKIRODlg::OnBnClickedTagg)
END_MESSAGE_MAP()


// CKIRODlg 메시지 처리기

BOOL CKIRODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	try
	{
		BOOL bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	
		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (const CException* e)
	{
		MessageBox(_T("DB연결을 확인해주세요."), _T("경고"), MB_ICONWARNING);
	}

#ifdef TEST
	this->m_bMonitor.EnableWindow(true);
	//this->m_bTag.EnableWindow(true);
	this->m_TaggingN.EnableWindow(true);
	this->m_bPatient.EnableWindow(true);
	this->m_bSurv.EnableWindow(true);
#endif

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKIRODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKIRODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKIRODlg::OnBnClickedMonitor2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_pMonitorDlg == nullptr)
		this->m_pAKinect_MonitoringDlg = new AKinect_Monitoring;
	m_pAKinect_MonitoringDlg->DoModal();
}


void CKIRODlg::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	bool bLogin = false;
	CString str_id, str_pw;
	vector<CString> stdvec_input;

	m_hID.GetWindowTextA(str_id);
	stdvec_input.push_back(str_id);
	m_hPW.GetWindowTextA(str_pw);
	stdvec_input.push_back(str_pw);
		
	try
	{
		CString sql = _T("select * from Admin_User;");
		BOOL bOpen = m_pRs->Open(CRecordset::snapshot, sql);
		if (bOpen)
		{
			int row = 1;
			bool bisEof = m_pRs->IsEOF();
			DWORD dwSize = m_pRs->GetRowsetSize();
			vector<CString> stdvec_item;
			if (!bisEof)
			{
				for (m_pRs->MoveFirst(); !m_pRs->IsEOF(); m_pRs->MoveNext())
				{
					int cnt = m_pRs->GetODBCFieldCount();
					for (int col = 0; col < cnt; col++)
					{
						CString item;
						m_pRs->SetAbsolutePosition(row);
						m_pRs->GetFieldValue(col, item);
						stdvec_item.push_back(item);
					}
					row++;
				}
			}
			if (stdvec_input == stdvec_item)
			{
				bLogin = true;
				
			}
				
			else
				MessageBox(_T("id/pw를 확인해주세요."), _T("경고"),MB_ICONWARNING);
			m_pRs->Close();
			m_db.Close();
		}


	}
	catch (const CException* e)
	{

	}

	if (bLogin)
	{
		this->m_bMonitor.EnableWindow(true);
		//this->m_bTag.EnableWindow(true);
		this->m_TaggingN.EnableWindow(true);
		this->m_bPatient.EnableWindow(true);
		this->m_bSurv.EnableWindow(true);
	}
}


void CKIRODlg::OnBnClickedTag()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 현재 다른 프로젝트에서 구현 테스트 중
	if (m_videoTag == nullptr)
		this->m_videoTag = new VideoTagging;
	m_videoTag->DoModal();
}


BOOL CKIRODlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
		{
			if (GetDlgItem(IDC_PW) == GetFocus() || GetDlgItem(IDC_ID) == GetFocus())
			{//에디트 컨트롤 엔터 누를시 개행.
				OnBnClickedLogin();
			}
			return TRUE;
		}
			
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKIRODlg::OnBnClickedPaitentinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pPatient_InfoDlg == nullptr)
		this->m_pPatient_InfoDlg = new Patient_Info;
	m_pPatient_InfoDlg->DoModal();
}


void CKIRODlg::OnBnClickedSurvey()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pMonitorDlg == nullptr)
		this->m_pMonitorDlg = new Monitoring;
	m_pMonitorDlg->DoModal();
}


void CKIRODlg::OnBnClickedTagg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_videoTagging == nullptr)
		this->m_videoTagging = new VideoTag;
	m_videoTagging->DoModal();
}
