#pragma once

#include "WinRefine ViewDlg.h"
#include "afxcmn.h"
#include "afxwin.h"

// CEffectsDlg dialog

class CEffectsDlg : public CDialog
{
	DECLARE_DYNAMIC(CEffectsDlg)

	public:
		CEffectsDlg(CWinRefineViewDlg* pParent = NULL);   // standard constructor
		virtual ~CEffectsDlg();

	// Dialog Data
		enum { IDD = IDD_EFFECTS };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	private:
		CWinRefineViewDlg* Dlg;

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
private:
	CSliderCtrl Volume;
private:
	CSliderCtrl Transparency;
private:
	CButton Tooltip;
	afx_msg void OnBnClickedTooltip();
	afx_msg void OnNMReleasedcaptureVolume(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureTransparency(NMHDR *pNMHDR, LRESULT *pResult);
};
