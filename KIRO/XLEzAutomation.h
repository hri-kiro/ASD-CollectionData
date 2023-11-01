// EzAutomation.h: interface for the CXLEzAutomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_)
#define AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XLAutomation.h"
#define xlNormal -4143

class CXLEzAutomation  
{
public:
	BOOL InsertPictureFromBuffer(BYTE* pImage, int Column, int Row, double dXScale, double dYScale);
	BOOL OpenExcelFile(CString szFileName);
	BOOL PlacePictureToClipboard(BYTE* pImage);
	BOOL InsertPictureFromClipboard(int Column, int Row);
	BOOL InsertPictureFromFile(CString szFileName, int Column, int Row);
	CString GetCellValue(int nColumn, int nRow);
	BOOL SaveFileAs(CString szFileName);
	BOOL DeleteRow(int nRow);
	BOOL ReleaseExcel();
	BOOL SetCellValue(int nColumn, int nRow, CString szValue);
	BOOL ExportCString(CString szDataCollection);
	BOOL UpdateXYChart(int nYColumn);
	BOOL CreateXYChart(int nYColumn);
	CXLEzAutomation();
	CXLEzAutomation(BOOL bVisible);
	virtual ~CXLEzAutomation();

protected:
	CXLAutomation* m_pXLServer;
};

#endif // !defined(AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_)
