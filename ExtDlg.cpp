// ExtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "ExtDlg.h"


// CExtDlg dialog

IMPLEMENT_DYNAMIC(CExtDlg, CDialog)

CExtDlg::CExtDlg(CWinRefineViewDlg* pParent /*=NULL*/)
	: CDialog(CExtDlg::IDD, pParent)
	, AudioVideo(false)
	, Image(false)
{
	CExtDlg::Dlg = pParent;
}

CExtDlg::~CExtDlg()
{
}

void CExtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXTENSION, Extension);
}


BEGIN_MESSAGE_MAP(CExtDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CExtDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CExtDlg message handlers

BOOL CExtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Sel = 0;

	SetWindowText(Dlg->Lang[Dlg->GetLanguage()].GetAt(23));

	SetDlgItemText(IDC_EXTENSIONT, Dlg->Lang[Dlg->GetLanguage()].GetAt(20) + _T(":"));
	SetDlgItemText(IDC_TYPET, Dlg->Lang[Dlg->GetLanguage()].GetAt(19) + _T(":"));
	SetDlgItemText(IDC_AUDIOVIDEO, Dlg->Lang[Dlg->GetLanguage()].GetAt(21));
	SetDlgItemText(IDC_IMAGE, Dlg->Lang[Dlg->GetLanguage()].GetAt(22));
	SetDlgItemText(IDOK, Dlg->Lang[Dlg->GetLanguage()].GetAt(28));
	SetDlgItemText(IDCANCEL, Dlg->Lang[Dlg->GetLanguage()].GetAt(29));

	CheckDlgButton(IDC_AUDIOVIDEO, BST_CHECKED);

	return TRUE;
}

void CExtDlg::OnBnClickedOk()
{
	if (IsDlgButtonChecked(IDC_IMAGE))
	{
		Sel = 1;
	}

	GetDlgItemText(IDC_EXTENSION, Ext);

	OnOK();
}
