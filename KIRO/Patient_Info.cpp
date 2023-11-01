// Patient_Info.cpp: 구현 파일
//
#pragma once
#include "pch.h"
#include "KIRO.h"
#include "Patient_Info.h"
#include "afxdialogex.h"
#include "defines.h"
// Patient_Info 대화 상자
patient patient_info;
IMPLEMENT_DYNAMIC(Patient_Info, CDialogEx)

Patient_Info::Patient_Info(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PATIENTINFO, pParent)
{

}

Patient_Info::~Patient_Info()
{
}

void Patient_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GENDER, m_cGender);
	DDX_Control(pDX, IDC_Diagnosis, m_cDiagnosis);
	DDX_Control(pDX, IDC_RESEARCHNUMBER, m_eResearchNumber);
	DDX_Control(pDX, IDC_SUBJECTNUMBER, m_eSubjectNumber);
	DDX_Control(pDX, IDC_AGE, m_eAge);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_RDate);
	DDX_Control(pDX, IDC_ADOSTYPE, m_adostype);
	DDX_Control(pDX, IDC_BEDEVELTYPE, m_bedeveltype);
}


BEGIN_MESSAGE_MAP(Patient_Info, CDialogEx)
	
	ON_BN_CLICKED(IDC_INSERT, &Patient_Info::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_SEARCH, &Patient_Info::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_MODIFY, &Patient_Info::OnBnClickedModify)
END_MESSAGE_MAP()

BOOL Patient_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_cGender.AddString(TEXT("1"));
	m_cGender.AddString(TEXT("2"));
	m_cDiagnosis.AddString(TEXT("1"));
	m_cDiagnosis.AddString(TEXT("2"));
	m_cDiagnosis.AddString(TEXT("3"));
	m_adostype.AddString(TEXT("1"));
	m_adostype.AddString(TEXT("2"));
	m_adostype.AddString(TEXT("T"));
	m_bedeveltype.AddString(TEXT("1"));
	m_bedeveltype.AddString(TEXT("2"));
	m_bedeveltype.AddString(TEXT("3"));
	m_bedeveltype.AddString(TEXT("4"));

	m_cGender.SetCurSel(0);
	bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	if (bOpen)
		m_pRs = new CRecordset(&m_db);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
// Patient_Info 메시지 처리기

BOOL CreateDir(CString dir) //--- 폴더 생성
{
	CFileFind file;
	CString strFile = _T("*.*");
	BOOL bResult = file.FindFile(dir + strFile);

	if (!bResult)
	{
		bResult = CreateDirectory(dir, NULL);
	}

	return bResult;
}

void Patient_Info::OnBnClickedInsert()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_db.IsOpen())
		m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);

	CString Research_Number=NULL; // 연구번호는 계속 사용하므로 나중에 전역변수로 설정
	CString subject_number=NULL, gender = NULL, diagnosis = NULL;
	CString date = NULL, age=NULL;
	CString ados_type = NULL, bedevel_type = NULL;
	GetDlgItemText(IDC_RESEARCHNUMBER, Research_Number);
	GetDlgItemText(IDC_SUBJECTNUMBER, subject_number);
	GetDlgItemText(IDC_AGE, age);
	GetDlgItemText(IDC_ADOSTYPE, ados_type);
	GetDlgItemText(IDC_BEDEVELTYPE, bedevel_type);
	m_cGender.GetLBText(m_cGender.GetCurSel(), gender);
	GetDlgItemText(IDC_DATETIMEPICKER, date);
	m_cDiagnosis.GetLBText(m_cDiagnosis.GetCurSel(), diagnosis);
	CString sql;
	sql.Format(_T("INSERT INTO Autism_db.Patient_Information(Research_Number, Subject_Number, Gender,Age,Date,Final_Diagnosis,Ados_Type,Bedevel_Type) VALUES ('%s','%s' ,'%s' ,%d,'%s', '%s', '%s', '%s');"),  // -------------------수정해야되는 부분
		Research_Number, subject_number, gender, _ttoi(age),date, diagnosis, ados_type, bedevel_type);
	//patient patient_info;
	patient_info.Date = date;
	patient_info.Research_Number = Research_Number;
	patient_info.Age = age;
	patient_info.folder_path[0] = _T("E:\\") + Research_Number + _T("\\");
	patient_info.folder_path[1] = _T("F:\\") + Research_Number + _T("\\");
	patient_info.folder_path[2] = _T("G:\\") + Research_Number + _T("\\");
	patient_info.folder_path[3] = _T("H:\\") + Research_Number + _T("\\");
	patient_info.folder_path[4] = _T("I:\\") + Research_Number + _T("\\");
	patient_info.folder_path[5] = _T("J:\\") + Research_Number + _T("\\");
	patient_info.folder_path[6] = _T("K:\\") + Research_Number + _T("\\");
	patient_info.folder_path[7] = _T("L:\\") + Research_Number + _T("\\");
	patient_info.folder_path[8] = _T("D:\\") + Research_Number + _T("\\");

	for (int i = 0; i < 9; i++)
	{
		bool result;
		CString str;
		str.Format(_T("%d"), i); //int 를 CStirng으로 변환
		result = CreateDir(patient_info.folder_path[i]);
	}

	int iage = _ttoi(age);
	patient_info.Ados_Type = ados_type;
	patient_info.Bedevel_Type = bedevel_type;
	
	// -- 쿼리문 전송 ---
	try 
	{
		if (bOpen)
		{
			m_db.BeginTrans();
			m_db.ExecuteSQL(sql);
			MessageBox(_T("추가에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		}
		
	}
	catch (CException* e)
	{
		e->ReportError();
		MessageBox(_T("DB연결을 확인해주세요"), _T("경고"), MB_ICONWARNING);
	}
	m_pRs->Close();
	m_db.CommitTrans();
	m_db.Close();
}


void Patient_Info::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_db.IsOpen())
		m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);

	CString str;

	m_eResearchNumber.GetWindowTextA(str);
	str += "';";
	bool bOpen = m_pRs->Open(CRecordset::snapshot, _T("select * from Autism_db.Patient_Information where research_number='") + str);

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

		m_eResearchNumber.SetWindowTextA(stdvec_item[0]);
		m_eSubjectNumber.SetWindowTextA(stdvec_item[1]);
		m_eAge.SetWindowTextA(stdvec_item[3]);
		m_cGender.SetWindowTextA(stdvec_item[2]);
		m_cDiagnosis.SetCurSel(_ttoi(stdvec_item[5]) - 1);
		patient_info.Research_Number = stdvec_item[0];
		patient_info.Age = stdvec_item[3];
		int iage = _ttoi(stdvec_item[3]);
		/*if (iage < 18)
			patient_info.Bedevel_Type = _T("1");
		else if (iage < 24)
			patient_info.Bedevel_Type = _T("2"); 
		else if (iage < 36)
			patient_info.Bedevel_Type = _T("3"); 
		else if (iage < 43)
			patient_info.Bedevel_Type = _T("4");
		if (iage < 31)
			patient_info.Ados_Type = _T("T");
		else if (iage > 30)
			patient_info.Ados_Type = _T("1");
		else
			patient_info.Ados_Type = _T("2");*/
	}
	else
	{
		MessageBox(_T("Data 없음"), _T("경고"), MB_ICONWARNING);
	}

	m_pRs->Close();
	m_db.Close();
}


void Patient_Info::OnBnClickedModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (!m_db.IsOpen())
		bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);

	CString sql, date, age, subjectnum, gender, rnum, fd;
	m_RDate.GetWindowTextA(date);
	m_eAge.GetWindowTextA(age);
	m_eSubjectNumber.GetWindowTextA(subjectnum);
	m_cGender.GetLBText(m_cGender.GetCurSel(), gender);
	m_eResearchNumber.GetWindowTextA(rnum);
	m_cDiagnosis.GetLBText(m_cDiagnosis.GetCurSel(), fd);
	sql.Format(_T("update patient_information set subject_number = '%s', gender = '%s' , age = %d, date = '%s' , final_diagnosis = '%s' where Research_Number = '%s';"),
		subjectnum, gender, _ttoi(age), date, fd, rnum);
	patient_info.Age = age;
	int iage = _ttoi(age);
	if (iage < 18)
		patient_info.Bedevel_Type = _T("1");
	else if (iage < 24)
		patient_info.Bedevel_Type = _T("2");
	else if (iage < 36)
		patient_info.Bedevel_Type = _T("3");
	else if (iage < 43)
		patient_info.Bedevel_Type = _T("4");
	if (iage < 31)
		patient_info.Ados_Type = _T("T");
	else if (iage > 30)
		patient_info.Ados_Type = _T("1");
	else
		patient_info.Ados_Type = _T("2");
	if (bOpen)
	{
		m_db.BeginTrans();
		m_db.ExecuteSQL(sql);
		MessageBox(_T("수정에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		patient_info.Research_Number = rnum;
	}
	else
	{
		MessageBox(_T("수정에 실패하였습니다."), _T("경고"), MB_ICONWARNING);
	}
	m_db.CommitTrans();
	m_db.Close();
}
