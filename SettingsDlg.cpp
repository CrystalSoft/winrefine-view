// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "SettingsDlg.h"


// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)

CSettingsDlg::CSettingsDlg(CWinRefineViewDlg* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	CSettingsDlg::Dlg = pParent;
}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_EN_CHANGE(IDC_LATENCY, &CSettingsDlg::OnEnChangeLatency)
	ON_EN_CHANGE(IDC_WIDTH, &CSettingsDlg::OnEnChangeWidth)
	ON_EN_CHANGE(IDC_HEIGHT, &CSettingsDlg::OnEnChangeHeight)
	ON_EN_CHANGE(IDC_THUMBSIZE, &CSettingsDlg::OnEnChangeThumbsize)
END_MESSAGE_MAP()


// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	return TRUE;
}

void CSettingsDlg::OnEnChangeLatency()
{
	Dlg->SetLatency(GetDlgItemInt(IDC_LATENCY, NULL, TRUE));
}

void CSettingsDlg::OnEnChangeWidth()
{
	Dlg->SetMinWidth(GetDlgItemInt(IDC_WIDTH, NULL, TRUE));
}

void CSettingsDlg::OnEnChangeHeight()
{
	Dlg->SetMinHeight(GetDlgItemInt(IDC_HEIGHT, NULL, TRUE));
}

void CSettingsDlg::OnEnChangeThumbsize()
{
	Dlg->SetThumbnailSize(GetDlgItemInt(IDC_THUMBSIZE, NULL, TRUE));
}
