#pragma once

#include "WinRefine ViewDlg.h"
#include "ExtDlg.h"

#include "afxcmn.h"

// CExtensionsDlg dialog

class CExtensionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CExtensionsDlg)

	public:
		CExtensionsDlg(CWinRefineViewDlg* pParent = NULL);   // standard constructor
		virtual ~CExtensionsDlg();

		CString GetAudioVideoExt();
		CString GetImageExt();

	// Dialog Data
		enum { IDD = IDD_EXTENSIONS };

	protected:
		CMenu* pSubMenu;

		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	private:
		CWinRefineViewDlg* Dlg;

	DECLARE_MESSAGE_MAP()

	private:
		CStringArray AudioVideoExtensions;
		CStringArray ImageExtensions;

		CListCtrl ExtList;
		afx_msg void OnBnClickedAdd();
		virtual BOOL OnInitDialog();
		afx_msg void OnNMRclickExtlist(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnRemoveext();
};
