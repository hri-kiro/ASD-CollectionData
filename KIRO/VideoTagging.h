#pragma once
#include "resource.h"
#include "defines.h"
#include "mkv_controller.h"
#include "BDV.h"
#include "ADOS.h"

// VideoTagging 대화 상자
class BDV;
class ADOS;
struct VideoIndex;
extern patient patient_info;

class VideoTagging : public CDialogEx
{
	DECLARE_DYNAMIC(VideoTagging)

public:
	VideoTagging(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~VideoTagging();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedEnd();
	afx_msg void OnBnClickedCut();
	afx_msg void OnBnClickedPlay();
	CSliderCtrl m_slider;
	CStatic m_pcc;
	CListBox m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	mkv_controller videoController1;
	mkv_controller videoController2;
	mkv_controller videoController3;
	mkv_controller videoController4;
	mkv_controller videoController5;
	mkv_controller videoController6;

	BDV* m_bdv;
	ADOS* m_ados;

	int nowIndex;
	int startIndex;
	int endIndex;
	int height;
	int width;
	std::vector<VideoIndex> videoSet;
	k4a::image colorImage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	BITMAPINFO m_bitmapInfo;

	bool m_bPlay;
	CButton m_hPlay;
	CTabCtrl m_Tab;

	CDatabase m_db;
	CRecordset* m_pRs;
	BOOL bOpen;

	vector<pair<int, int>> m_bdvData;
	vector<pair<int, int>> m_adosData;
};
