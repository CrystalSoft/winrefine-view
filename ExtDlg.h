#pragma once

#include "afxwin.h"
#include "WinRefine ViewDlg.h"

// CExtDlg dialog

class CExtDlg : public CDialog
{
	DECLARE_DYNAMIC(CExtDlg)

	public:
		CExtDlg(CWinRefineViewDlg* pParent = NULL);   // standard constructor
		virtual ~CExtDlg();

	// Dialog Data
		enum { IDD = IDD_EXTDIALOG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual BOOL OnInitDialog();

		DECLARE_MESSAGE_MAP()

	private:
		CWinRefineViewDlg* Dlg;

		CEdit Extension;
		bool AudioVideo;
		bool Image;

	public:
		CString Ext;
		bool Sel;
public:
	afx_msg void OnBnClickedOk();
};
