// VideoTagging.cpp: 구현 파일
//

#include "pch.h"
#include "KIRO.h"
#include "VideoTagging.h"
#include "afxdialogex.h"


// VideoTagging 대화 상자

IMPLEMENT_DYNAMIC(VideoTagging, CDialogEx)

VideoTagging::VideoTagging(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

VideoTagging::~VideoTagging()
{
}

void VideoTagging::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_PCC, m_pcc);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PLAY, m_hPlay);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(VideoTagging, CDialogEx)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &VideoTagging::OnNMCustomdrawSlider1)
	ON_LBN_SELCHANGE(IDC_LIST1, &VideoTagging::OnLbnSelchangeList1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &VideoTagging::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_SAVE, &VideoTagging::OnBnClickedSave)
	ON_BN_CLICKED(IDC_START, &VideoTagging::OnBnClickedStart)
	ON_BN_CLICKED(IDC_END, &VideoTagging::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_CUT, &VideoTagging::OnBnClickedCut)
	ON_BN_CLICKED(IDC_PLAY, &VideoTagging::OnBnClickedPlay)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// VideoTagging 메시지 처리기


//void VideoTagging::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}


void VideoTagging::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void VideoTagging::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_Tab.GetCurSel();

	switch (sel)
	{
	case 0:
		m_bdv->ShowWindow(SW_SHOW);
		m_ados->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_bdv->ShowWindow(SW_HIDE);
		m_ados->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	
	*pResult = 0;
}

void VideoTagging::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
#ifdef TEST
	int serial = 1, size = videoSet.size();
	string str;
	for (register int i = 0;i<size;i++)
	{
		patient_info.video_path[0] = patient_info.folder_path[0] + patient_info.Research_Number + _T("_ADOS_") + patient_info.Ados_Type + _T("_BEDEVEL") + patient_info.Bedevel_Type;
		str = patient_info.video_path[0] + "_Ads_";
		switch (m_bdvData[i].first)
		{
		case 2:
			str += "BD2_";
			break;
		case 3:
			str += "BD3_";
			break;
		case 4:
			str += "BD4_";
			break;
		case 5:
			str += "BD5_";
			break;
		case 6:
			str += "BD6_";
			break;
		case 7:
			str += "BD7_";
			break;
		case 8:
			str += "BD8_";
			break;
		case 9:
			str += "BD9_";
			break;
		case 10:
			str += "BD10_";
			break;
		case 11:
			str += "BD11_";
			break;
		case 12:
			str += "BD12_";
			break;
		case 13:
			str += "BD13_";
			break;
		case 14:
			str += "BD14_";
			break;
		case 15:
			str += "BD15_";
			break;
		case 16:
			str += "BD16_";
			break;
		case 17:
			str += "BD17_";
			break;
		case 18:
			str += "BD18_";
			break;
		case 19:
			str += "BD19_";
			break;
		case 20:
			str += "BD20_";
			break;
		default:
			break;
		}
		str += to_string(m_bdvData[i].second);
		str += "_Bdv_";

		if (patient_info.Ados_Type == _T("1"))
		{
			switch (m_adosData[i].first)
			{
			case 5:
				str += "A1_";
				break;
			case 6:
				str += "A2_";
				break;
			case 7:
				str += "A3_";
				break;
			case 8:
				str += "A4_";
				break;
			case 9:
				str += "A5_";
				break;
			case 10:
				str += "A6_";
				break;
			case 11:
				str += "A7_";
				break;
			case 12:
				str += "A8_";
				break;
			case 13:
				str += "B1_";
				break;
			case 14:
				str += "B2_";
				break;
			case 15:
				str += "B3_";
				break;
			case 16:
				str += "B4_";
				break;
			case 17:
				str += "B5_";
				break;
			case 18:
				str += "B6_";
				break;
			case 19:
				str += "B7_";
				break;
			case 20:
				str += "B8_";
				break;
			case 21:
				str += "B9_";
				break;
			case 22:
				str += "B10_";
				break;
			case 23:
				str += "B11_";
				break;
			case 24:
				str += "B12_";
				break;
			case 25:
				str += "B13a_";
				break;
			case 26:
				str += "B13b_";
				break;
			case 27:
				str += "B14_";
				break;
			case 28:
				str += "B15_";
				break;
			case 29:
				str += "B16_";
				break;
			case 30:
				str += "C1_";
				break;
			case 31:
				str += "C2_";
				break;
			case 32:
				str += "D1_";
				break;
			case 33:
				str += "D2_";
				break;
			case 34:
				str += "D3_";
				break;
			case 35:
				str += "D4_";
				break;
			case 36:
				str += "E1_";
				break;
			case 37:
				str += "E2_";
				break;
			case 38:
				str += "E3_";
				break;
			default:
				break;
			}
		}
		else if (patient_info.Ados_Type == _T("2"))
		{
			switch (m_adosData[i].first)
			{
			case 5:
				str += "A1_";
				break;
			case 6:
				str += "A2_";
				break;
			case 7:
				str += "A3_";
				break;
			case 8:
				str += "A4_";
				break;
			case 9:
				str += "A5_";
				break;
			case 10:
				str += "A6_";
				break;
			case 11:
				str += "A7_";
				break;
			case 12:
				str += "B1_";
				break;
			case 13:
				str += "B2_";
				break;
			case 14:
				str += "B3_";
				break;
			case 15:
				str += "B4_";
				break;
			case 16:
				str += "B5_";
				break;
			case 17:
				str += "B6_";
				break;
			case 18:
				str += "B7_";
				break;
			case 19:
				str += "B8_";
				break;
			case 20:
				str += "B9a_";
				break;
			case 21:
				str += "B9b_";
				break;
			case 22:
				str += "B10_";
				break;
			case 23:
				str += "B11_";
				break;
			case 24:
				str += "B12_";
				break;
			case 25:
				str += "C1_";
				break;
			case 26:
				str += "C2_";
				break;
			case 27:
				str += "D1_";
				break;
			case 28:
				str += "D2_";
				break;
			case 29:
				str += "D3_";
				break;
			case 30:
				str += "D4_";
				break;
			case 31:
				str += "E1_";
				break;
			case 32:
				str += "E2_";
				break;
			case 33:
				str += "E3_";
				break;
			default:
				break;
			}
		}
		else if (patient_info.Ados_Type == _T("T"))
		{
			switch (m_adosData[i].first)
			{
			case 5:
				str += "A1_";
				break;
			case 6:
				str += "A1a_";
				break;
			case 7:
				str += "A2_";
				break;
			case 8:
				str += "A3_";
				break;
			case 9:
				str += "A4_";
				break;
			case 10:
				str += "A5_";
				break;
			case 11:
				str += "A6_";
				break;
			case 12:
				str += "A7_";
				break;
			case 13:
				str += "A8_";
				break;
			case 14:
				str += "A9_";
				break;
			case 15:
				str += "B1_";
				break;
			case 16:
				str += "B2_";
				break;
			case 17:
				str += "B3_";
				break;
			case 18:
				str += "B4_";
				break;
			case 19:
				str += "B5_";
				break;
			case 20:
				str += "B6_";
				break;
			case 21:
				str += "B7_";
				break;
			case 22:
				str += "B8_";
				break;
			case 23:
				str += "B9_";
				break;
			case 24:
				str += "B10_";
				break;
			case 25:
				str += "B11_";
				break;
			case 26:
				str += "B12_";
				break;
			case 27:
				str += "B13_";
				break;
			case 28:
				str += "B14_";
				break;
			case 29:
				str += "B15_";
				break;
			case 30:
				str += "B16a_";
				break;
			case 31:
				str += "B16b_";
				break;
			case 32:
				str += "B17_";
				break;
			case 33:
				str += "B18_";
				break;
			case 34:
				str += "C1_";
				break;
			case 35:
				str += "C2_";
				break;
			case 36:
				str += "C3_";
				break;
			case 37:
				str += "D1_";
				break;
			case 38:
				str += "D2_";
				break;
			case 39:
				str += "D3_";
				break;
			case 40:
				str += "D4_";
				break;
			case 41:
				str += "D5_";
				break;
			case 42:
				str += "E1_";
				break;
			case 43:
				str += "E2_";
				break;
			case 44:
				str += "E3_";
				break;
			default:
				break;
			}
		}
		str += to_string(m_adosData[i].second);
		str += "_";
		str += to_string(serial++);
		str += ".mkv";
		videoController1.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
	}
#endif
#ifndef TEST
	//videoController1.openPlayback(LPCTSTR(patient_info.video_full_path[0]));
	videoController2.openPlayback(LPCTSTR(patient_info.video_full_path[1]));
	videoController3.openPlayback(LPCTSTR(patient_info.video_full_path[2]));
	videoController4.openPlayback(LPCTSTR(patient_info.video_full_path[3]));
	videoController5.openPlayback(LPCTSTR(patient_info.video_full_path[4]));
	videoController6.openPlayback(LPCTSTR(patient_info.video_full_path[5]));

	for (int j = 0; j < 6; j++)
	{
		int serial = 1, size = videoSet.size();
		string str;
		for (register int i = 0; i < size; i++)
		{
			patient_info.video_path[j] = patient_info.folder_path[j] + patient_info.Research_Number + _T("_ADOS") + patient_info.Ados_Type + _T("_BEDEVEL_") + patient_info.Bedevel_Type;
			str = patient_info.video_path[j] + "_Ads_";
			switch (m_bdvData[i].first)
			{
			case 2:
				str += "BD2_";
				break;
			case 3:
				str += "BD3_";
				break;
			case 4:
				str += "BD4_";
				break;
			case 5:
				str += "BD5_";
				break;
			case 6:
				str += "BD6_";
				break;
			case 7:
				str += "BD7_";
				break;
			case 8:
				str += "BD8_";
				break;
			case 9:
				str += "BD9_";
				break;
			case 10:
				str += "BD10_";
				break;
			case 11:
				str += "BD11_";
				break;
			case 12:
				str += "BD12_";
				break;
			case 13:
				str += "BD13_";
				break;
			case 14:
				str += "BD14_";
				break;
			case 15:
				str += "BD15_";
				break;
			case 16:
				str += "BD16_";
				break;
			case 17:
				str += "BD17_";
				break;
			case 18:
				str += "BD18_";
				break;
			case 19:
				str += "BD19_";
				break;
			case 20:
				str += "BD20_";
				break;
			default:
				break;
	}
			str += to_string(m_bdvData[i].second);
			str += "_Bdv_";

			if (patient_info.Ados_Type == 1)
			{
				switch (m_adosData[i].first)
				{
				case 5:
					str += "A1_";
					break;
				case 6:
					str += "A2_";
					break;
				case 7:
					str += "A3_";
					break;
				case 8:
					str += "A4_";
					break;
				case 9:
					str += "A5_";
					break;
				case 10:
					str += "A6_";
					break;
				case 11:
					str += "A7_";
					break;
				case 12:
					str += "A8_";
					break;
				case 13:
					str += "B1_";
					break;
				case 14:
					str += "B2_";
					break;
				case 15:
					str += "B3_";
					break;
				case 16:
					str += "B4_";
					break;
				case 17:
					str += "B5_";
					break;
				case 18:
					str += "B6_";
					break;
				case 19:
					str += "B7_";
					break;
				case 20:
					str += "B8_";
					break;
				case 21:
					str += "B9_";
					break;
				case 22:
					str += "B10_";
					break;
				case 23:
					str += "B11_";
					break;
				case 24:
					str += "B12_";
					break;
				case 25:
					str += "B13a_";
					break;
				case 26:
					str += "B13b_";
					break;
				case 27:
					str += "B14_";
					break;
				case 28:
					str += "B15_";
					break;
				case 29:
					str += "B16_";
					break;
				case 30:
					str += "C1_";
					break;
				case 31:
					str += "C2_";
					break;
				case 32:
					str += "D1_";
					break;
				case 33:
					str += "D2_";
					break;
				case 34:
					str += "D3_";
					break;
				case 35:
					str += "D4_";
					break;
				case 36:
					str += "E1_";
					break;
				case 37:
					str += "E2_";
					break;
				case 38:
					str += "E3_";
					break;
				default:
					break;
				}
			}
			else if (patient_info.Ados_Type == 2)
			{
				switch (m_adosData[i].first)
				{
				case 5:
					str += "A1_";
					break;
				case 6:
					str += "A2_";
					break;
				case 7:
					str += "A3_";
					break;
				case 8:
					str += "A4_";
					break;
				case 9:
					str += "A5_";
					break;
				case 10:
					str += "A6_";
					break;
				case 11:
					str += "A7_";
					break;
				case 12:
					str += "B1_";
					break;
				case 13:
					str += "B2_";
					break;
				case 14:
					str += "B3_";
					break;
				case 15:
					str += "B4_";
					break;
				case 16:
					str += "B5_";
					break;
				case 17:
					str += "B6_";
					break;
				case 18:
					str += "B7_";
					break;
				case 19:
					str += "B8_";
					break;
				case 20:
					str += "B9a_";
					break;
				case 21:
					str += "B9b_";
					break;
				case 22:
					str += "B10_";
					break;
				case 23:
					str += "B11_";
					break;
				case 24:
					str += "B12_";
					break;
				case 25:
					str += "C1_";
					break;
				case 26:
					str += "C2_";
					break;
				case 27:
					str += "D1_";
					break;
				case 28:
					str += "D2_";
					break;
				case 29:
					str += "D3_";
					break;
				case 30:
					str += "D4_";
					break;
				case 31:
					str += "E1_";
					break;
				case 32:
					str += "E2_";
					break;
				case 33:
					str += "E3_";
					break;
				default:
					break;
				}
			}
			else if (patient_info.Ados_Type == 3)
			{
				switch (m_adosData[i].first)
				{
				case 5:
					str += "A1_";
					break;
				case 6:
					str += "A1a_";
					break;
				case 7:
					str += "A2_";
					break;
				case 8:
					str += "A3_";
					break;
				case 9:
					str += "A4_";
					break;
				case 10:
					str += "A5_";
					break;
				case 11:
					str += "A6_";
					break;
				case 12:
					str += "A7_";
					break;
				case 13:
					str += "A8_";
					break;
				case 14:
					str += "A9_";
					break;
				case 15:
					str += "B1_";
					break;
				case 16:
					str += "B2_";
					break;
				case 17:
					str += "B3_";
					break;
				case 18:
					str += "B4_";
					break;
				case 19:
					str += "B5_";
					break;
				case 20:
					str += "B6_";
					break;
				case 21:
					str += "B7_";
					break;
				case 22:
					str += "B8_";
					break;
				case 23:
					str += "B9_";
					break;
				case 24:
					str += "B10_";
					break;
				case 25:
					str += "B11_";
					break;
				case 26:
					str += "B12_";
					break;
				case 27:
					str += "B13_";
					break;
				case 28:
					str += "B14_";
					break;
				case 29:
					str += "B15_";
					break;
				case 30:
					str += "B16a_";
					break;
				case 31:
					str += "B16b_";
					break;
				case 32:
					str += "B17_";
					break;
				case 33:
					str += "B18_";
					break;
				case 34:
					str += "C1_";
					break;
				case 35:
					str += "C2_";
					break;
				case 36:
					str += "C3_";
					break;
				case 37:
					str += "D1_";
					break;
				case 38:
					str += "D2_";
					break;
				case 39:
					str += "D3_";
					break;
				case 40:
					str += "D4_";
					break;
				case 41:
					str += "D5_";
					break;
				case 42:
					str += "E1_";
					break;
				case 43:
					str += "E2_";
					break;
				case 44:
					str += "E3_";
					break;
				default:
					break;
				}
			}

			str += to_string(m_adosData[i].second);
			str += "_";
			str += to_string(serial++);
			str += ".mkv";

			if(j == 0)
				videoController1.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
			else if(j == 1)
				videoController2.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
			else if (j == 2)
				videoController3.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
			else if (j == 3)
				videoController4.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
			else if (j == 4)
				videoController5.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
			else if (j == 5)
				videoController6.saveBetweenFrame(videoSet[i].StartIndex, videoSet[i].EndIndex, str);
	}
	}
#endif
	// 규칙에 맞게 쿼리문 보내면 됨 + bedevel 결과

#ifndef TEST
	/*CString sql;
	try
	{
		if (bOpen)
		{
			m_db.BeginTrans();
			m_db.ExecuteSQL(sql);
			MessageBox(_T("태깅 완료"), _T("알림"), MB_ICONWARNING);
		}
		m_db.CommitTrans();
	}
	catch (CException * e)
	{
		e->ReportError();
		MessageBox(_T("DB연결을 확인해주세요"), _T("경고"), MB_ICONWARNING);
	}
	m_db.Close();*/
#endif
}


void VideoTagging::OnBnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	startIndex = nowIndex;
}


void VideoTagging::OnBnClickedEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	endIndex = nowIndex;
}


void VideoTagging::OnBnClickedCut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	VideoIndex temp;
	temp.StartIndex = startIndex;
	temp.EndIndex = endIndex;
	videoSet.push_back(temp);
	string str("Start : ");
	str += to_string((float)startIndex / 30);
	str += " sec  End : ";
	str += to_string((float)endIndex / 30);
	str += " sec";
	m_list.AddString(str.c_str());

	pair<int, int> tempPair;
	CString cstr;
	m_bdv->m_score.GetWindowTextA(cstr);
	int f = m_bdv->m_com.GetCurSel(), s = _ttoi(cstr);
	tempPair = make_pair(f,s);
	m_bdvData.push_back(tempPair);
	m_ados->m_score.GetWindowTextA(cstr);
	f = m_ados->m_com.GetCurSel(), s = _ttoi(cstr);
	tempPair = make_pair(f, s);
	m_adosData.push_back(tempPair);
}


void VideoTagging::OnBnClickedPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bPlay)
	{
		m_bPlay = false;
		m_hPlay.SetWindowTextA("Play");
	}
	else
	{
		m_bPlay = true;
		m_hPlay.SetWindowTextA("Pause");
	}
}


BOOL VideoTagging::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//// video 경로 받아서 넣어주면 됨 (현재 test용 비디오 하나만 받음)
#ifdef TEST
	string str("test.mkv");
	videoController1.openPlayback(str);
#endif
#ifndef TEST
	videoController1.openPlayback(LPCTSTR(patient_info.video_full_path[0]));
#endif

#ifndef TEST
	/*bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);
	if (bOpen)
		m_pRs = new CRecordset(&m_db);*/
#endif

	int length = videoController1.getTotalFrameCount();
	m_slider.SetRange(0, length);
	m_slider.SetPos(0);
	m_slider.SetLineSize(30);
	
	height = 1920;
	width = 1080;

	SetTimer(0, 1, NULL);

	m_bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bitmapInfo.bmiHeader.biPlanes = 1;
	m_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	m_bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
	m_bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	m_bitmapInfo.bmiHeader.biClrUsed = 0;
	m_bitmapInfo.bmiHeader.biClrImportant = 0;
	m_bitmapInfo.bmiHeader.biSizeImage = 0;
	m_bitmapInfo.bmiHeader.biWidth = 1920;
	m_bitmapInfo.bmiHeader.biHeight = -1080;
	m_bitmapInfo.bmiHeader.biBitCount = 32;

	nowIndex = 0;
	m_bPlay = false;

	m_Tab.InsertItem(0, _T("BDV"));
	m_Tab.InsertItem(1, _T("ADOS"));
	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	m_bdv = new BDV;
	if (_ttoi(patient_info.Age) < 18)
		m_bdv->m_bdvType = 1;
	else if (_ttoi(patient_info.Age) < 24)
		m_bdv->m_bdvType = 2;
	else if (_ttoi(patient_info.Age) < 36)
		m_bdv->m_bdvType = 3;
	else if (_ttoi(patient_info.Age) < 43)
		m_bdv->m_bdvType = 4;

	m_ados = new ADOS;
	if (_ttoi(patient_info.Age) < 31)
		m_ados->m_adosType = 3;
	else if (_ttoi(patient_info.Age) > 30)
		m_ados->m_adosType = 1;
	else
		m_ados->m_adosType = 2;
	
	m_bdv->Create(IDD_BDV, &m_Tab);
	m_bdv->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_ados->Create(IDD_ADOS, &m_Tab);
	m_ados->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_bdv->ShowWindow(SW_SHOW);
	
	try
	{
		bOpen = m_db.OpenEx(_T(DBOPEN), CDatabase::noOdbcDialog);

		if (bOpen)
			m_pRs = new CRecordset(&m_db);
	}
	catch (const CException * e)
	{
		MessageBox(_T("DB연결을 확인해주세요."), _T("경고"), MB_ICONWARNING);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void VideoTagging::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER1)
	{
		nowIndex = m_slider.GetPos();
		videoController1.getColorFrame(nowIndex, colorImage);
	}

	CDC* pDC;
	CRect rect;
	pDC = m_pcc.GetDC();
	m_pcc.GetClientRect(&rect);

	pDC->SetStretchBltMode(HALFTONE);
	CImage image;
	image.Create(1920, 1080,32);
	StretchDIBits(image.GetDC(), 0, 0, rect.Width() * 2, rect.Height() * 2,
		0, 0, 1920, 1080, colorImage.get_buffer(), &m_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	image.Draw(pDC->GetSafeHdc(), rect);

	ReleaseDC(pDC);
	image.ReleaseDC();
	image.Destroy();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void VideoTagging::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bPlay)
	{
		videoController1.getColorFrame(nowIndex, colorImage);
		m_slider.SetPos(nowIndex++);
		auto temp = colorImage.get_buffer();
		if (temp != nullptr)
		{
			CDC* pDC = m_pcc.GetDC();
			CRect rect;
			m_pcc.GetClientRect(&rect);
			pDC->SetStretchBltMode(HALFTONE);

			CImage image;
			image.Create(1920, 1080, 32);
			StretchDIBits(image.GetDC(), 0, 0, rect.Width() * 2, rect.Height() * 2,
				0, 0, 1920, 1080, (void*)temp, &m_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
			image.Draw(pDC->m_hDC, rect);
			ReleaseDC(pDC);
			image.ReleaseDC();
			image.Destroy();
		}
		
	}	

	CDialogEx::OnTimer(nIDEvent);
}
