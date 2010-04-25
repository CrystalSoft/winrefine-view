#pragma once

#include "hyperlink.h"
#include "WinRefine ViewDlg.h"
#include "afxwin.h"


// CGeneralDlg dialog

class CGeneralDlg : public CDialog
{
	DECLARE_DYNAMIC(CGeneralDlg)

public:
	CGeneralDlg(CWinRefineViewDlg* pParent = NULL);   // standard constructor
	virtual ~CGeneralDlg();

// Dialog Data
	enum { IDD = IDD_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CWinRefineViewDlg* Dlg;
	CHyperLink ProdPage;
	afx_msg void OnStnClickedProdlink();
private:
	CButton Enabled;
	afx_msg void OnBnClickedEnabled();
private:
	CComboBox Lang;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeLang();
};
