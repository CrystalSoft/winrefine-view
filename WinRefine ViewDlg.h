// WinRefine ViewDlg.h : header file
//

#pragma once

#include "TrayDialog.h"
#include "ColorStatic.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <atlbase.h>

// CWinRefineViewDlg dialog
class CWinRefineViewDlg: public CTrayDialog
{
// Construction
public:
	CWinRefineViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINREFINEVIEW_DIALOG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		static UINT UpdateChecker(LPVOID params);

	// Implementation
	protected:
		HICON m_hIcon;
		CMenu* pSubMenu;

		// Generated message map functions
		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		DECLARE_MESSAGE_MAP()

	private:
		void OnApply();
		afx_msg void OnBnClickedApply();
		afx_msg void OnBnClickedCancel();
		afx_msg void OnBnClickedExit();
		afx_msg void OnConfigure();
		afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	public:
		void SwitchLang(int Language);

		//Settings
		void SetEnabled(bool Enabled);
		void SetLanguage(DWORD Lang);
		void SetLatency(DWORD Latency);
		void SetVolume(DWORD Volume);
		void SetThumbnailSize(DWORD ThumbnailSize);
		void SetMinWidth(DWORD MinWidth);
		void SetMinHeight(DWORD MinHeight);
		void SetTransparency(DWORD Transparency);
		void SetTooltip(DWORD Tooltip);
		void SetAudioVideo(CString AudioVideo);
		void SetImage(CString Image);

		bool GetEnabled();
		DWORD GetLanguage();
		DWORD GetLatency();
		DWORD GetVolume();
		DWORD GetThumbnailSize();
		DWORD GetMinWidth();
		DWORD GetMinHeight();
		DWORD GetTransparency();
		DWORD GetTooltip();
		CString GetAudioVideo();
		CString GetImage();

	private:
		bool Threading;
		int Selection;

		CString MyPath;
		CDialog* Dialogs[5];
		CListCtrl List;
		CColorStatic Caption;
		CFont TitleFont;

		CRegKey Reg;

		//Settings
		bool Enable;
		DWORD Language;
		DWORD Latency;
		DWORD Volume;
		DWORD ThumbnailSize;
		DWORD MinWidth;
		DWORD MinHeight;
		DWORD Transparency;
		DWORD Tooltip;
		CString AudioVideo;
		CString Image;

	public:
		CStringArray Lang[2];
};
