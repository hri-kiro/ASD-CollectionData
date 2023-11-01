// TabDlg2.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "TabDlg2.h"
#include "afxdialogex.h"


// TabDlg2 대화 상자

IMPLEMENT_DYNAMIC(TabDlg2, CDialogEx)

TabDlg2::TabDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB2, pParent)
{

}

TabDlg2::~TabDlg2()
{
}

void TabDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabDlg2, CDialogEx)
END_MESSAGE_MAP()


// TabDlg2 메시지 처리기


BOOL TabDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	if (bOpen)
		m_pRs = new CRecordset(&m_db);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
