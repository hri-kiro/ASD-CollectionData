// VideoTag.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "VideoTag.h"
#include "afxdialogex.h"


// VideoTag 대화 상자

IMPLEMENT_DYNAMIC(VideoTag, CDialogEx)

VideoTag::VideoTag(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAGGING, pParent)
{

}

VideoTag::~VideoTag()
{
}

void VideoTag::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNUM, m_rnum);
}


BEGIN_MESSAGE_MAP(VideoTag, CDialogEx)
	ON_BN_CLICKED(IDC_VIDEO, &VideoTag::OnBnClickedVideo)
	ON_BN_CLICKED(IDC_CUT, &VideoTag::OnBnClickedCut)
	ON_BN_CLICKED(IDC_UPLOAD, &VideoTag::OnBnClickedUpload)
END_MESSAGE_MAP()


// VideoTag 메시지 처리기


void VideoTag::OnBnClickedVideo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef TEST
	::ShellExecute(NULL, "open", NULL, NULL, "./test", SW_SHOW);
#endif
#ifndef TEST
	CString cmdLine;
	cmdLine = "copy C:\\work\\sample\\ADOS2-m" + patient_info.Ados_Type + ".xlsx "+ patient_info.folder_path[0]+"ADOS2-m" + patient_info.Ados_Type+".xlsx";
	system(cmdLine);
	cmdLine = "copy C:\\work\\sample\\BEDEVEL-p-" + patient_info.Bedevel_Type + ".xlsx " + patient_info.folder_path[0] + "BEDEVEL-P-" + patient_info.Bedevel_Type + ".xlsx";
	system(cmdLine);
	::ShellExecute(NULL, "open", NULL, NULL, patient_info.folder_path[0], SW_SHOW);
#endif 
}


void VideoTag::OnBnClickedCut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 태깅에 원하는 경로를 설정해주세요.
	for (register int i = 0; i < 6; i++)
	{
		patient_info.folder_tagging_path[i] = "./test/tagging";
	}

	for (register int i = 0; i < 6; i++)
		DeleteAllFile(patient_info.folder_tagging_path[i]);

#ifdef TEST
	// 절대경로만 엑셀이 열립니다.
	CString str1, str2;
	patient_info.Ados_Type.Format(_T("1"));
	patient_info.Bedevel_Type.Format(_T("1"));
	if (_ttoi(patient_info.Ados_Type) == 1)
		str1.Format("C:\\Users\\PC\\Downloads\\2020.05\\KIRO0506\\KIRO\\test\\ADOS2-m1.xlsx");
	if (_ttoi(patient_info.Ados_Type) == 2)
		str1.Format("C:\\Users\\PC\\Downloads\\2020.04\\KIRO0427\\KIRO\\test\\ADOS2-m2.xlsx");
	if (_ttoi(patient_info.Ados_Type) == 3)
		str1.Format("C:\\Users\\PC\\Downloads\\2020.04\\KIRO0427\\KIRO\\test\\ADOS2-mT.xlsx");

	if (_ttoi(patient_info.Bedevel_Type) == 1)
		str2.Format("C:\\Users\\PC\\Downloads\\2020.05\\KIRO0506\\KIRO\\test\\BEDEVEL-P-1.xlsx");
	if (_ttoi(patient_info.Bedevel_Type) == 2)
		str2.Format("C:\\Users\\PC\\Downloads\\2020.04\\KIRO0427\\KIRO\\test\\BEDEVEL-P-2.xlsx");
	if (_ttoi(patient_info.Bedevel_Type) == 3)
		str2.Format("C:\\Users\\PC\\Downloads\\2020.04\\KIRO0427\\KIRO\\test\\BEDEVEL-P-3.xlsx");
	if (_ttoi(patient_info.Bedevel_Type) == 4)
		str2.Format("C:\\Users\\PC\\Downloads\\2020.04\\KIRO0427\\KIRO\\test\\BEDEVEL-P-4.xlsx");

	CXLEzAutomation exc(false);
	exc.OpenExcelFile(str1);

	// 데이터는 1,1 부터 시작합니다. 0,0 아님. 형식 (x,y) 로 데이터 가져옴. 반환형 CString
	// example) exc.GetCellValue(1, 1);
	bool tag = true;
	vector<xlContainer> dataSet1, dataSet2;
	xlContainer tempdata;
	int y = 5;
	while (tag)
	{
		tempdata.contents = exc.GetCellValue(1, y);
		tempdata.time = exc.GetCellValue(2, y);
		tempdata.score = exc.GetCellValue(3, y++);

		if (tempdata.contents == L"")
			tag = false;

		if (tempdata.time == L"" || tempdata.score == L"")
			continue;

		dataSet1.push_back(tempdata);
	}
	exc.ReleaseExcel();

	exc.OpenExcelFile(str2);
	y = 5;
	while (tag)
	{
		tempdata.contents = exc.GetCellValue(1, y);
		tempdata.time = exc.GetCellValue(2, y);
		tempdata.score = exc.GetCellValue(3, y++);

		if (tempdata.contents == L"")
			tag = false;

		if (tempdata.time == L"" || tempdata.score == L"")
			continue;

		dataSet2.push_back(tempdata);
	}
	exc.ReleaseExcel();

	CString fileName = "test_result", temp;
	CString cmdLine = "mkvmerge -o " + fileName + " test.mkv" + " --split parts:" + dataSet1[0].time;

	if (!dataSet1.empty())
	{
		for (register int i = 0; i < dataSet1.size(); i++)
		{
			temp.Format("%d", i);
			cmdLine = "mkvmerge -o " + fileName + temp + ".mkv test.mkv" + " --split parts:" + dataSet1[i].time;
			threadV.push_back(thread(&systemCall, cmdLine));
		}
	}
	if (!dataSet2.empty())
	{
		for (register int i = 0; i < dataSet2.size(); i++)
		{
			temp.Format("%d", i);
			cmdLine = "mkvmerge -o " + fileName + temp + ".mkv test.mkv" + " --split parts:" + dataSet2[i].time;
			threadV.push_back(thread(&systemCall, cmdLine));
		}
	}

	for (register int i = 0; i < threadV.size(); i++)
	{
		threadV[i].detach();
	}

	// 쿼리문 작성
	CString sql1, sql2, deletesql1("DELETE FROM Autism_db."), deletesql2("DELETE FROM Autism_db.");
	string tempsql1 = "INSERT INTO Autism_db.", tempsql2 = "INSERT INTO Autism_db.", tempstring1, tempstring2;
	if (_ttoi(patient_info.Ados_Type) == 1)
		tempstring1 = "ados_1", deletesql1 += "ados_1\n";
	if (_ttoi(patient_info.Ados_Type) == 2)
		tempstring1 = "ados_2", deletesql1 += "ados_2\n";;
	if (_ttoi(patient_info.Ados_Type) == 3)
		tempstring1 = "ados_t", deletesql1 += "ados_t\n";;

	if (_ttoi(patient_info.Bedevel_Type) == 1)
		tempstring2 = "bedevel-1", deletesql2 += "bedevel-1\n";
	if (_ttoi(patient_info.Bedevel_Type) == 2)
		tempstring2 = "bedevel-2", deletesql2 += "bedevel-2\n";
	if (_ttoi(patient_info.Bedevel_Type) == 3)
		tempstring2 = "bedevel-3", deletesql2 += "bedevel-3\n";
	if (_ttoi(patient_info.Bedevel_Type) == 4)
		tempstring2 = "bedevel-4", deletesql2 += "bedevel-4\n";

	tempsql1 = tempsql1 + tempstring1 + "(Readsearch_Number,";
	tempsql2 = tempsql2 + tempstring2 + "(Readsearch_Number,";

	for (register int i = 0; i < dataSet1.size(); i++)
	{
		tempsql1 = tempsql1 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet1.size())
			tempsql1 += ",";
		else
			tempsql1 += ")";
	}
	tempsql1 = tempsql1 + " VALUES (" + (LPCSTR)patient_info.Research_Number;
	for (register int i = 0; i < dataSet1.size(); i++)
	{
		tempsql1 = tempsql1 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet1.size())
			tempsql1 += ",";
		else
			tempsql1 += ");";
	}

	for (register int i = 0; i < dataSet2.size(); i++)
	{
		tempsql2 = tempsql2 + LPCTSTR(dataSet2[i].contents);
		if (i + 1 != dataSet2.size())
			tempsql2 += ",";
		else
			tempsql2 += ")";
	}
	tempsql2 = tempsql2 + " VALUES (" + (LPCSTR)patient_info.Research_Number;
	for (register int i = 0; i < dataSet2.size(); i++)
	{
		tempsql2 = tempsql2 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet2.size())
			tempsql2 += ",";
		else
			tempsql2 += ");";
	}

	// -- 쿼리문 전송 ---
	try
	{
		if (bOpen)
		{
			m_db.BeginTrans();
			if (!dataSet1.empty())
			{
				deletesql1 = deletesql1 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql1);
				m_db.ExecuteSQL(sql1);
			}
			if (!dataSet2.empty())
			{
				deletesql2 = deletesql2 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql2);
				m_db.ExecuteSQL(sql2);
			}
			MessageBox(_T("추가에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		}
		else
		{
			bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
			if (bOpen)
				m_pRs = new CRecordset(&m_db);

			m_db.BeginTrans();
			if (!dataSet1.empty())
			{
				deletesql1 = deletesql1 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql1);
				m_db.ExecuteSQL(sql1);
			}
			if (!dataSet2.empty())
			{
				deletesql2 = deletesql2 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql2);
				m_db.ExecuteSQL(sql2);
			}
			MessageBox(_T("추가에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		}

	}
	catch (CException * e)
	{
		e->ReportError();
		MessageBox(_T("DB연결을 확인해주세요"), _T("경고"), MB_ICONWARNING);
	}

	m_pRs->Close();
	m_db.CommitTrans();
	m_db.Close();
	bOpen = false;

#endif
#ifndef TEST
	// 절대경로만 엑셀이 열립니다.
	CString str1, str2;
	CString ads1 = "ADOS2-m1.xlsx";
	CString ads2 = "ADOS2-m2.xlsx";
	CString adst = "ADOS2-mt.xlsx";
	CString bdv1 = "BEDEVEL-P-1.xlsx";
	CString bdv2 = "BEDEVEL-P-2.xlsx";
	CString bdv3 = "BEDEVEL-P-3.xlsx";
	CString bdv4 = "BEDEVEL-P-4.xlsx";
	//patient_info.Ados_Type.Format(_T("1"));
	//patient_info.Bedevel_Type.Format(_T("1"));
	if (_ttoi(patient_info.Ados_Type) == 1)
		//str1.Format("C:\\work\\sample\\ADOS2-m1.xlsx");
		str1 = patient_info.folder_path[0] + ads1;
	if (_ttoi(patient_info.Ados_Type) == 2)
		//str1.Format("C:\\work\\sample\\ADOS2-m2.xlsx");
		str1 = patient_info.folder_path[0] + ads2;
	if (_ttoi(patient_info.Ados_Type) == 3)
		//str1.Format("C:\\work\\sample\\ADOS2-mT.xlsx");
		str1 = patient_info.folder_path[0] + adst;

	if (_ttoi(patient_info.Bedevel_Type) == 1)
		//str2.Format("C:\\work\\sample\\BEDEVEL-P-1.xlsx");
		str2 = patient_info.folder_path[0] + bdv1;
	if (_ttoi(patient_info.Bedevel_Type) == 2)
		//str2.Format("C:\\work\\sample\\BEDEVEL-P-2.xlsx");
		str2 = patient_info.folder_path[0] + bdv2;
	if (_ttoi(patient_info.Bedevel_Type) == 3)
		//str2.Format("C:\\work\\sample\\BEDEVEL-P-3.xlsx");
		str2 = patient_info.folder_path[0] + bdv3;
	if (_ttoi(patient_info.Bedevel_Type) == 4)
		//str2.Format("C:\\work\\sample\\BEDEVEL-P-4.xlsx");
		str2 = patient_info.folder_path[0] + bdv4;

	CXLEzAutomation exc_ads(false);
	
	exc_ads.OpenExcelFile(str1);
	//exc.SetCellValue(2, 1, patient_info.Research_Number);
	// 데이터는 1,1 부터 시작합니다. 0,0 아님. 형식 (x,y) 로 데이터 가져옴. 반환형 CString
	// example) exc.GetCellValue(1, 1);
	bool tag = true;
	vector<xlContainer> dataSet1, dataSet2;
	xlContainer tempdata;
	int y = 5;
	while (tag)
	{
		tempdata.contents = exc_ads.GetCellValue(1, y);
		tempdata.time = exc_ads.GetCellValue(2, y);
		//tempdata.score = exc.GetCellValue(3, y++);
		tempdata.score.Format("%d", _ttoi(exc_ads.GetCellValue(3, y++)));
		if (tempdata.contents == L"")
			tag = false;

		if (tempdata.time == L"" || tempdata.score == L"")
			continue;

		dataSet1.push_back(tempdata);
	}
	exc_ads.ReleaseExcel();
	tag = true;
	CXLEzAutomation exc_bdv(false);
	exc_bdv.OpenExcelFile(str2);
	//exc.SetCellValue(2, 1, patient_info.Research_Number);
	y = 5;
	while (tag)
	{
		tempdata.contents = exc_bdv.GetCellValue(1, y);
		//tempdata.contents.Format("%d", _ttoi(exc_bdv.GetCellValue(1, y)));
		tempdata.time = exc_bdv.GetCellValue(2, y);
		//tempdata.score = exc.GetCellValue(3, y++);
		tempdata.score.Format("%d", _ttoi(exc_bdv.GetCellValue(3, y++)));

		if (tempdata.contents == L"" )
			tag = false;

		if (tempdata.time == L"" || tempdata.score == L"")
			continue;

		dataSet2.push_back(tempdata);
	}
	exc_bdv.ReleaseExcel();

	CString fileName = "test_result.mkv";
	CString cmdLine;// = "mkvmerge -o " + patient_info.folder_path[0] + fileName + " " + patient_info.video_full_path[0] + " --split parts:" + dataSet1[i].time;

	if (!dataSet1.empty())
	{
		for (register int i = 0; i < dataSet1.size(); i++)
		{
			//filneName = 규칙
			CString id;
			id.Format(_T("%d"), i);
			fileName = "test_result";
			for (int j = 0; j < 6; j++)
			{
				cmdLine = "mkvmerge -o " + patient_info.video_path[j] + "_" + dataSet1[i].contents + "_" + dataSet1[i].score + "-ads-" + id + ".mkv" + " " + patient_info.video_full_path[j] + " --split parts:" + dataSet1[i].time;
				threadV.push_back(thread(&systemCall, cmdLine));
			}
		}
	}
	cout << "ados tagging 완료" << endl;
	if (!dataSet2.empty())
	{
		for (register int i = 0; i < dataSet2.size(); i++)
		{
			CString id;
			id.Format(_T("%d"), i);
			//filneName = 규칙
			fileName = "test_result.mkv";
			for (int j = 0; j < 6; j++)
			{
				cmdLine = "mkvmerge -o " + patient_info.video_path[j] + "_" + dataSet2[i].contents + "_" + dataSet2[i].score + "-bdv-" + id + ".mkv" + " " + patient_info.video_full_path[j] + " --split parts:" + dataSet2[i].time;
				threadV.push_back(thread(&systemCall, cmdLine));
			}
		}
	}

	for (register int i = 0; i < threadV.size(); i++)
	{
		threadV[i].detach();
	}

	cout << "bedevel tagging 완료" << endl;

	// 쿼리문 작성
	CString sql1, sql2, deletesql1("DELETE FROM Autism_db."), deletesql2("DELETE FROM Autism_db.");
	string tempsql1 = "INSERT INTO Autism_db.", tempsql2 = "INSERT INTO Autism_db.", tempstring1, tempstring2;
	if (_ttoi(patient_info.Ados_Type) == 1)
		tempstring1 = "ados_1", deletesql1 += "ados_1\n";
	if (_ttoi(patient_info.Ados_Type) == 2)
		tempstring1 = "ados_2", deletesql1 += "ados_2\n";;
	if (_ttoi(patient_info.Ados_Type) == 3)
		tempstring1 = "ados_t", deletesql1 += "ados_t\n";;

	if (_ttoi(patient_info.Bedevel_Type) == 1)
		tempstring2 = "bedevel-1", deletesql2 += "bedevel-1\n";
	if (_ttoi(patient_info.Bedevel_Type) == 2)
		tempstring2 = "bedevel-2", deletesql2 += "bedevel-2\n";
	if (_ttoi(patient_info.Bedevel_Type) == 3)
		tempstring2 = "bedevel-3", deletesql2 += "bedevel-3\n";
	if (_ttoi(patient_info.Bedevel_Type) == 4)
		tempstring2 = "bedevel-4", deletesql2 += "bedevel-4\n";

	tempsql1 = tempsql1 + tempstring1 + "(Readsearch_Number,";
	tempsql2 = tempsql2 + tempstring2 + "(Readsearch_Number,";

	for (register int i = 0; i < dataSet1.size(); i++)
	{
		tempsql1 = tempsql1 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet1.size())
			tempsql1 += ",";
		else
			tempsql1 += ")";
	}
	tempsql1 = tempsql1 + " VALUES (" + (LPCSTR)patient_info.Research_Number;
	for (register int i = 0; i < dataSet1.size(); i++)
	{
		tempsql1 = tempsql1 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet1.size())
			tempsql1 += ",";
		else
			tempsql1 += ");";
	}

	for (register int i = 0; i < dataSet2.size(); i++)
	{
		tempsql2 = tempsql2 + LPCTSTR(dataSet2[i].contents);
		if (i + 1 != dataSet2.size())
			tempsql2 += ",";
		else
			tempsql2 += ")";
	}
	tempsql2 = tempsql2 + " VALUES (" + (LPCSTR)patient_info.Research_Number;
	for (register int i = 0; i < dataSet2.size(); i++)
	{
		tempsql2 = tempsql2 + LPCTSTR(dataSet1[i].contents);
		if (i + 1 != dataSet2.size())
			tempsql2 += ",";
		else
			tempsql2 += ");";
	}

	// -- 쿼리문 전송 ---
	try
	{
		if (bOpen)
		{
			m_db.BeginTrans();
			if (!dataSet1.empty())
			{
				deletesql1 = deletesql1 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql1);
				m_db.ExecuteSQL(sql1);
			}
			if (!dataSet2.empty())
			{
				deletesql2 = deletesql2 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql2);
				m_db.ExecuteSQL(sql2);
			}
			MessageBox(_T("추가에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		}
		else
		{
			bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
			if (bOpen)
				m_pRs = new CRecordset(&m_db);

			m_db.BeginTrans();
			if (!dataSet1.empty())
			{
				deletesql1 = deletesql1 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql1);
				m_db.ExecuteSQL(sql1);
			}
			if (!dataSet2.empty())
			{
				deletesql2 = deletesql2 + "WHERE Research_Number = '" + (LPCSTR)patient_info.Research_Number + "'";
				m_db.ExecuteSQL(deletesql2);
				m_db.ExecuteSQL(sql2);
			}
			MessageBox(_T("추가에 성공하였습니다."), _T("알림"), MB_ICONWARNING);
		}

	}
	catch (CException * e)
	{
		e->ReportError();
		MessageBox(_T("DB연결을 확인해주세요"), _T("경고"), MB_ICONWARNING);
	}

	m_pRs->Close();
	m_db.CommitTrans();
	m_db.Close();
	bOpen = false;
#endif
}


BOOL VideoTag::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_rnum.SetWindowTextA(patient_info.Research_Number);

	bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	if (bOpen)
		m_pRs = new CRecordset(&m_db);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void VideoTag::OnBnClickedUpload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cmdLine;
	cmdLine = "xcopy D:\\" + patient_info.Research_Number + " J:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cmdLine = "xcopy E:\\" + patient_info.Research_Number + " K:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cmdLine = "xcopy F:\\" + patient_info.Research_Number + " L:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cmdLine = "xcopy G:\\" + patient_info.Research_Number + " M:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cmdLine = "xcopy H:\\" + patient_info.Research_Number + " N:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cmdLine = "xcopy I:\\" + patient_info.Research_Number + " O:\\" + patient_info.Research_Number + " /E /H /K /I";
	system(cmdLine);
	cout << "nas 업로드 완료" << endl;
}

void VideoTag::DeleteAllFile(CString path)
{
	CString strName;
	strName.Format("%s\\*.*", path);
	CFileFind ff;
	BOOL bFind = ff.FindFile(strName);

	while (bFind)
	{
		bFind = ff.FindNextFileA();
		if(ff.IsDots() == TRUE || ff.IsDirectory() == TRUE) continue;
		DeleteFileA(ff.GetFilePath());
	}
	ff.Close();
}

void VideoTag::systemCall(CString cmd)
{
	system(cmd);
}
