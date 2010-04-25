// GeneralDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "GeneralDlg.h"


// CGeneralDlg dialog

IMPLEMENT_DYNAMIC(CGeneralDlg, CDialog)

CGeneralDlg::CGeneralDlg(CWinRefineViewDlg* pParent /*=NULL*/)
	: CDialog(CGeneralDlg::IDD, pParent)
{
	CGeneralDlg::Dlg = pParent;
}

CGeneralDlg::~CGeneralDlg()
{
}

void CGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRODLINK, ProdPage);
	DDX_Control(pDX, IDC_ENABLED, Enabled);
	DDX_Control(pDX, IDC_LANG, Lang);
}


BEGIN_MESSAGE_MAP(CGeneralDlg, CDialog)
	ON_STN_CLICKED(IDC_PRODLINK, &CGeneralDlg::OnStnClickedProdlink)
	ON_BN_CLICKED(IDC_ENABLED, &CGeneralDlg::OnBnClickedEnabled)
	ON_CBN_SELCHANGE(IDC_LANG, &CGeneralDlg::OnCbnSelchangeLang)
END_MESSAGE_MAP()


// CGeneralDlg message handlers

BOOL CGeneralDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Lang.SetCurSel(Dlg->GetLanguage());

	return TRUE;
}

void CGeneralDlg::OnStnClickedProdlink()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("http://www.emuware.org/?p=view&type=0&id=36"), NULL, NULL, SW_SHOW);
}

void CGeneralDlg::OnBnClickedEnabled()
{
	Dlg->SetEnabled(IsDlgButtonChecked(IDC_ENABLED) == TRUE ? true : false);
}

void CGeneralDlg::OnCbnSelchangeLang()
{
	Dlg->SetLanguage(Lang.GetCurSel());
}
