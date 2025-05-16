
// LafManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LafManager.h"
#include "LafManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLafManagerDlg dialog



CLafManagerDlg::CLafManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LAFMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLafManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LAF, cbLaf);
	DDX_Control(pDX, IDC_LIST_LOG, lbLog);
}

BEGIN_MESSAGE_MAP(CLafManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UNLOCK, &CLafManagerDlg::OnBnClickedButtonUnlock)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLafManagerDlg message handlers

BOOL CLafManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	FLaf = new CwclLafManager();
	CString s;
	
	int Res = FLaf->Open();
	if (Res != WCL_E_SUCCESS)
	{
		s.Format(_T("%.8X"), Res);
		lbLog.AddString(_T("Open LAF Manager failed: 0x") + s);
	}
	else
	{
		lbLog.AddString(_T("LAF Manager opened"));

		tstring Pfn;
		tstring AppName;
		tstring Publisher;
		Res = FLaf->GetIdentity(Pfn, AppName, Publisher);
		if (Res != WCL_E_SUCCESS)
		{
			s.Format(_T("%.8X"), Res);
			lbLog.AddString(_T("Get identity failed: 0x") + s);
		}
		else
		{
			lbLog.AddString(tstring(_T("PFN: ") + Pfn).c_str());
			lbLog.AddString(tstring(_T("AppName: ") + AppName).c_str());
			lbLog.AddString(tstring(_T("Publisher: ") + Publisher).c_str());

			list<tstring> Laf;

			Res = FLaf->Enum(Laf);
			if (Res != WCL_E_SUCCESS)
			{
				s.Format(_T("%.8X"), Res);
				lbLog.AddString(_T("Enum LAF failed: 0x") + s);
			}
			else
			{
				if (Laf.size() > 0)
				{
					for (list<tstring>::iterator i = Laf.begin(); i != Laf.end(); i++)
						cbLaf.AddString(i->c_str());

					cbLaf.SetCurSel(0);
				}
			}
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLafManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLafManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLafManagerDlg::OnBnClickedButtonUnlock()
{
	if (cbLaf.GetCurSel() == -1)
		lbLog.AddString(_T("No LAF found"));
	else
	{
		CString Laf;
		cbLaf.GetWindowText(Laf);
		int Res = FLaf->Unlock(Laf.GetString());
		if (Res != WCL_E_SUCCESS)
		{
			CString s;
			s.Format(_T("%.8X"), Res);
			lbLog.AddString(_T("Unlock ") + Laf + _T(" failed: 0x") + s);
		}
		else
			lbLog.AddString(_T("LAF ") + Laf + _T(" unlocked"));
	}
}


void CLafManagerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete FLaf;
}
