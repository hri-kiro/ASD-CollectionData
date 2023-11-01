// TabDlg1.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "TabDlg1.h"
#include "afxdialogex.h"


// TabDlg1 대화 상자

IMPLEMENT_DYNAMIC(TabDlg1, CDialogEx)

TabDlg1::TabDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB1, pParent)
{

}

TabDlg1::~TabDlg1()
{
}

void TabDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_A, m_ea);
	DDX_Control(pDX, IDC_EDIT_BV, m_ebv);
	DDX_Control(pDX, IDC_EDIT_BNV, m_bnv);
	DDX_Control(pDX, IDC_EDIT_NV, m_env);
	DDX_Control(pDX, IDC_EDIT_C, m_c);
	DDX_Control(pDX, IDC_EDIT_D, m_d);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_eR);
}


BEGIN_MESSAGE_MAP(TabDlg1, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &TabDlg1::OnBnClickedSave)
END_MESSAGE_MAP()


// TabDlg1 메시지 처리기


BOOL TabDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	if (bOpen)
		m_pRs = new CRecordset(&m_db);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabDlg1::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
