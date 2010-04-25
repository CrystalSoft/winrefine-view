// EffectsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "EffectsDlg.h"


// CEffectsDlg dialog

IMPLEMENT_DYNAMIC(CEffectsDlg, CDialog)

CEffectsDlg::CEffectsDlg(CWinRefineViewDlg* pParent /*=NULL*/)
	: CDialog(CEffectsDlg::IDD, pParent)
{
	CEffectsDlg::Dlg = pParent;
}

CEffectsDlg::~CEffectsDlg()
{
}

void CEffectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VOLUME, Volume);
	DDX_Control(pDX, IDC_TRANSPARENCY, Transparency);
	DDX_Control(pDX, IDC_TOOLTIP, Tooltip);
}


BEGIN_MESSAGE_MAP(CEffectsDlg, CDialog)
	ON_BN_CLICKED(IDC_TOOLTIP, &CEffectsDlg::OnBnClickedTooltip)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_VOLUME, &CEffectsDlg::OnNMReleasedcaptureVolume)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_TRANSPARENCY, &CEffectsDlg::OnNMReleasedcaptureTransparency)
END_MESSAGE_MAP()


// CEffectsDlg message handlers

BOOL CEffectsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	Volume.SetRange(0, 1000);
	Transparency.SetRange(0, 255);

	return TRUE;
}

void CEffectsDlg::OnBnClickedTooltip()
{
	Dlg->SetTooltip(IsDlgButtonChecked(IDC_TOOLTIP));
}

void CEffectsDlg::OnNMReleasedcaptureVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	Dlg->SetVolume(Volume.GetPos());

	*pResult = 0;
}

void CEffectsDlg::OnNMReleasedcaptureTransparency(NMHDR *pNMHDR, LRESULT *pResult)
{
	Dlg->SetTransparency(Transparency.GetPos());

	*pResult = 0;
}
