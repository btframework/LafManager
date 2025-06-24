
// LafManagerDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "wclErrors.h"
#include "wclLaf.h"

using namespace wclCommon;
using namespace wclLaf;


// CLafManagerDlg dialog
class CLafManagerDlg : public CDialogEx
{
// Construction
public:
	CLafManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAFMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox cbLaf;
	CListBox lbLog;
	CwclLafManager* FLaf;
public:
	afx_msg void OnBnClickedButtonUnlock();
	afx_msg void OnDestroy();
};
