// BDV.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "BDV.h"
#include "afxdialogex.h"


// BDV 대화 상자

IMPLEMENT_DYNAMIC(BDV, CDialogEx)

BDV::BDV(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BDV, pParent)
{

	m_bdvType = 0;
}

BDV::~BDV()
{
}

void BDV::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_com);
	DDX_Control(pDX, IDC_EDIT1, m_score);
	DDX_Control(pDX, IDC_RNUM, m_rnum);
}


BEGIN_MESSAGE_MAP(BDV, CDialogEx)
END_MESSAGE_MAP()


// BDV 메시지 처리기


BOOL BDV::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_rnum.SetWindowTextA(patient_info.Research_Number);

	m_com.AddString(TEXT("Selected")); // 0
	m_com.AddString(TEXT("Diagnosis")); // 1
	m_com.AddString(TEXT("BD2")); // 2
	m_com.AddString(TEXT("BD3")); // 3
	m_com.AddString(TEXT("BD4")); // 4
	m_com.AddString(TEXT("BD5")); // 5
	m_com.AddString(TEXT("BD6")); // 6
	m_com.AddString(TEXT("BD7")); // 7
	m_com.AddString(TEXT("BD8")); // 8
	m_com.AddString(TEXT("BD9")); // 9
	m_com.AddString(TEXT("BD10")); // 10
	m_com.AddString(TEXT("BD11")); // 11
	m_com.AddString(TEXT("BD12")); // 12
	m_com.AddString(TEXT("BD13")); // 13
	m_com.AddString(TEXT("BD14")); // 14
	switch (m_bdvType)
	{
	case 2:
		m_com.AddString(TEXT("BD15")); // 15
		break;
	case 3:
		m_com.AddString(TEXT("BD15")); // 15
		m_com.AddString(TEXT("BD16")); // 16
		m_com.AddString(TEXT("BD17")); // 17
		m_com.AddString(TEXT("BD18")); // 18
		m_com.AddString(TEXT("BD19")); // 19
		break;
	case 4:
		m_com.AddString(TEXT("BD15")); // 15
		m_com.AddString(TEXT("BD16")); // 16
		m_com.AddString(TEXT("BD17")); // 17
		m_com.AddString(TEXT("BD18")); // 18
		m_com.AddString(TEXT("BD19")); // 19
		m_com.AddString(TEXT("BD20")); // 20
		break;
	default:
		break;
	}
	m_com.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
