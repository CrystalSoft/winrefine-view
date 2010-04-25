#pragma once

#include "WinRefine ViewDlg.h"

// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

	public:
		CSettingsDlg(CWinRefineViewDlg* pParent = NULL);   // standard constructor
		virtual ~CSettingsDlg();

	// Dialog Data
		enum { IDD = IDD_SETTINGS };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()

	private:
		CWinRefineViewDlg* Dlg;
		virtual BOOL OnInitDialog();
		afx_msg void OnEnChangeLatency();
		afx_msg void OnEnChangeWidth();
		afx_msg void OnEnChangeHeight();
		afx_msg void OnEnChangeThumbsize();
};
