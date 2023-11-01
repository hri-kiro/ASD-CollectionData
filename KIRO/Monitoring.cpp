// Monitoring.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "Monitoring.h"
#include "afxdialogex.h"
#include "defines.h"

// Monitoring 대화 상자
extern patient patient_info;

IMPLEMENT_DYNAMIC(Monitoring, CDialogEx)

Monitoring::Monitoring(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TABMASTER, pParent)
{
}

Monitoring::~Monitoring()
{
}

void Monitoring::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABCON, m_Tab);
	DDX_Control(pDX, IDC_ERNUM, m_hRnum);
}


BEGIN_MESSAGE_MAP(Monitoring, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &Monitoring::OnBnClickedAdd)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCON, &Monitoring::OnTcnSelchangeTabcon)
	ON_BN_CLICKED(IDC_MODIFY, &Monitoring::OnBnClickedModify)
END_MESSAGE_MAP()


// Monitoring 메시지 처리기


void Monitoring::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Monitoring::OnTcnSelchangeTabcon(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
		m_Tab1->ShowWindow(SW_SHOW);
		m_Tab2->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_Tab1->ShowWindow(SW_HIDE);
		m_Tab2->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}

	*pResult = 0;
}


BOOL Monitoring::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_Tab.InsertItem(0, _T("ADI_R"));
	m_Tab.InsertItem(1, _T("SURVEY"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	m_Tab1 = new TabDlg1;
	m_Tab2 = new TabDlg2;

	m_Tab1->Create(IDD_TAB1, &m_Tab);
	m_Tab1->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_Tab1->ShowWindow(SW_SHOW);

	m_Tab2->Create(IDD_TAB2, &m_Tab);
	m_Tab2->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_Tab2->ShowWindow(SW_HIDE);

	m_hRnum.SetWindowTextA(patient_info.Research_Number);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Monitoring::OnBnClickedModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
