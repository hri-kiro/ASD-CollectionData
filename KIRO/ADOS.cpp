// ADOS.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "ADOS.h"
#include "afxdialogex.h"


// ADOS 대화 상자

IMPLEMENT_DYNAMIC(ADOS, CDialogEx)

ADOS::ADOS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADOS, pParent)
{

}

ADOS::~ADOS()
{
}

void ADOS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_com);
	DDX_Control(pDX, IDC_EDIT1, m_score);
	DDX_Control(pDX, IDC_RNUM, m_rnum);
}


BEGIN_MESSAGE_MAP(ADOS, CDialogEx)
END_MESSAGE_MAP()


// ADOS 메시지 처리기


BOOL ADOS::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_rnum.SetWindowTextA(patient_info.Research_Number);

	m_com.AddString(TEXT("Affection")); // 0
	m_com.AddString(TEXT("Behavior")); // 1
	m_com.AddString(TEXT("Total_Score")); // 2
	m_com.AddString(TEXT("Relative_Score")); // 3
	m_com.AddString(TEXT("Diagnosis")); // 4
	switch (m_adosType)
	{
	case 1: // ados 1
		m_com.AddString(TEXT("A1")); // 5
		m_com.AddString(TEXT("A2")); // 6
		m_com.AddString(TEXT("A3")); // 7
		m_com.AddString(TEXT("A4")); // 8
		m_com.AddString(TEXT("A5")); // 9
		m_com.AddString(TEXT("A6")); // 10
		m_com.AddString(TEXT("A7")); // 11
		m_com.AddString(TEXT("A8")); // 12
		m_com.AddString(TEXT("B1")); // 13
		m_com.AddString(TEXT("B2")); // 14
		m_com.AddString(TEXT("B3")); // 15
		m_com.AddString(TEXT("B4")); // 16
		m_com.AddString(TEXT("B5")); // 17
		m_com.AddString(TEXT("B6")); // 18
		m_com.AddString(TEXT("B7")); // 19
		m_com.AddString(TEXT("B8")); // 20
		m_com.AddString(TEXT("B9")); // 21
		m_com.AddString(TEXT("B10")); // 22
		m_com.AddString(TEXT("B11")); // 23
		m_com.AddString(TEXT("B12")); // 24
		m_com.AddString(TEXT("B13a")); // 25
		m_com.AddString(TEXT("B13b")); // 26
		m_com.AddString(TEXT("B14")); // 27
		m_com.AddString(TEXT("B15")); // 28
		m_com.AddString(TEXT("B16")); // 29
		m_com.AddString(TEXT("C1")); // 30
		m_com.AddString(TEXT("C2")); // 31
		m_com.AddString(TEXT("D1")); // 32
		m_com.AddString(TEXT("D2")); // 33
		m_com.AddString(TEXT("D3")); // 34
		m_com.AddString(TEXT("D4")); // 35
		m_com.AddString(TEXT("E1")); // 36
		m_com.AddString(TEXT("E2")); // 37
		m_com.AddString(TEXT("E3")); // 38
		break;
	case 2: // ados2
		m_com.AddString(TEXT("A1")); // 5
		m_com.AddString(TEXT("A2")); // 6
		m_com.AddString(TEXT("A3")); // 7
		m_com.AddString(TEXT("A4")); // 8
		m_com.AddString(TEXT("A5")); // 9
		m_com.AddString(TEXT("A6")); // 10
		m_com.AddString(TEXT("A7")); // 11
		m_com.AddString(TEXT("B1")); // 12
		m_com.AddString(TEXT("B2")); // 13
		m_com.AddString(TEXT("B3")); // 14
		m_com.AddString(TEXT("B4")); // 15
		m_com.AddString(TEXT("B5")); // 16
		m_com.AddString(TEXT("B6")); // 17
		m_com.AddString(TEXT("B7")); // 18
		m_com.AddString(TEXT("B8")); // 19
		m_com.AddString(TEXT("B9a")); // 20
		m_com.AddString(TEXT("B9b")); // 21
		m_com.AddString(TEXT("B10")); // 22
		m_com.AddString(TEXT("B11")); // 23
		m_com.AddString(TEXT("B12")); // 24
		m_com.AddString(TEXT("C1")); // 25
		m_com.AddString(TEXT("C2")); // 26
		m_com.AddString(TEXT("D1")); // 27
		m_com.AddString(TEXT("D2")); // 28
		m_com.AddString(TEXT("D3")); // 29
		m_com.AddString(TEXT("D4")); // 30
		m_com.AddString(TEXT("E1")); // 31
		m_com.AddString(TEXT("E2")); // 32
		m_com.AddString(TEXT("E3")); // 33
		break;
	case 3: // ados t
		m_com.AddString(TEXT("A1")); // 5
		m_com.AddString(TEXT("A1a")); // 6
		m_com.AddString(TEXT("A2")); // 7
		m_com.AddString(TEXT("A3")); // 8
		m_com.AddString(TEXT("A4")); // 9
		m_com.AddString(TEXT("A5")); // 10
		m_com.AddString(TEXT("A6")); // 11
		m_com.AddString(TEXT("A7")); // 12
		m_com.AddString(TEXT("A8")); // 13
		m_com.AddString(TEXT("A9")); // 14
		m_com.AddString(TEXT("B1")); // 15
		m_com.AddString(TEXT("B2")); // 16
		m_com.AddString(TEXT("B3")); // 17
		m_com.AddString(TEXT("B4")); // 18
		m_com.AddString(TEXT("B5")); // 19
		m_com.AddString(TEXT("B6")); // 20
		m_com.AddString(TEXT("B7")); // 21
		m_com.AddString(TEXT("B8")); // 22
		m_com.AddString(TEXT("B9")); // 23
		m_com.AddString(TEXT("B10")); // 24
		m_com.AddString(TEXT("B11")); // 25
		m_com.AddString(TEXT("B12")); // 26
		m_com.AddString(TEXT("B13")); // 27
		m_com.AddString(TEXT("B14")); // 28
		m_com.AddString(TEXT("B15")); // 29
		m_com.AddString(TEXT("B16a")); // 30
		m_com.AddString(TEXT("B16b")); // 31
		m_com.AddString(TEXT("B17")); // 32
		m_com.AddString(TEXT("B18")); // 33
		m_com.AddString(TEXT("C1")); // 34
		m_com.AddString(TEXT("C2")); // 35
		m_com.AddString(TEXT("C3")); // 36
		m_com.AddString(TEXT("D1")); // 37
		m_com.AddString(TEXT("D2")); // 38
		m_com.AddString(TEXT("D3")); // 39
		m_com.AddString(TEXT("D4")); // 40
		m_com.AddString(TEXT("D5")); // 41
		m_com.AddString(TEXT("E1")); // 42
		m_com.AddString(TEXT("E2")); // 43
		m_com.AddString(TEXT("E3")); // 44
		break;
	default:
		break;
	}
	m_com.SetCurSel(5);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
