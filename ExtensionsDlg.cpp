// ExtensionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "ExtensionsDlg.h"


// CExtensionsDlg dialog

IMPLEMENT_DYNAMIC(CExtensionsDlg, CDialog)

CExtensionsDlg::CExtensionsDlg(CWinRefineViewDlg* pParent /*=NULL*/)
	: CDialog(CExtensionsDlg::IDD, pParent)
{
	CExtensionsDlg::Dlg = pParent;
}

CExtensionsDlg::~CExtensionsDlg()
{
}

void CExtensionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXTLIST, ExtList);
}


BEGIN_MESSAGE_MAP(CExtensionsDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, &CExtensionsDlg::OnBnClickedAdd)
	ON_NOTIFY(NM_RCLICK, IDC_EXTLIST, &CExtensionsDlg::OnNMRclickExtlist)
	ON_COMMAND(IDC_REMOVEEXT, &CExtensionsDlg::OnRemoveext)
END_MESSAGE_MAP()

void SplitString(CStringArray& StrArr, CString szString, CString szTokens)
{
	int iCurrPos = 0;
	CString subString;

	while ((iCurrPos = szString.FindOneOf(szTokens)) != -1)
	{
		StrArr.Add(szString.Left(iCurrPos));

		szString = szString.Right(szString.GetLength() - iCurrPos - 1);
	}

	if (szString.GetLength() > 0)
	{
		StrArr.Add(szString);
	}
}

int FindString(CStringArray& Array, CString String)
{
	int ret = -1;

	for (int i = 0; i < Array.GetCount(); i++)
	{
		if (Array.GetAt(i).Find(String) >= 0)
		{
			ret = i;

			break;
		}
	}

	return ret;
}

// CExtensionsDlg message handlers

BOOL CExtensionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	pSubMenu = new CMenu;

	CImageList* ImgHeaders = new CImageList;

	SHFILEINFO shfi;
	SHGetFileInfo(_T(".mp3"), FILE_ATTRIBUTE_NORMAL, &shfi, sizeof(SHFILEINFO), SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_SHELLICONSIZE | SHGFI_SMALLICON);

	ImgHeaders->Create(16, 16, ILC_COLOR32, 0, 0);
	ImgHeaders->Add(shfi.hIcon);

	SHGetFileInfo(_T(".png"), FILE_ATTRIBUTE_NORMAL, &shfi, sizeof(SHFILEINFO), SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_SHELLICONSIZE | SHGFI_SMALLICON);

	ImgHeaders->Add(shfi.hIcon);

	ExtList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	ExtList.InsertColumn(0, Dlg->Lang[Dlg->GetLanguage()].GetAt(19), LVCFMT_LEFT, 95);
	ExtList.InsertColumn(1, Dlg->Lang[Dlg->GetLanguage()].GetAt(20), LVCFMT_LEFT, 150);
	ExtList.SetImageList(ImgHeaders, LVSIL_SMALL);

	CString AudioVideoExt = Dlg->GetAudioVideo();
	CString ImageExt = Dlg->GetImage();

	SplitString(AudioVideoExtensions, AudioVideoExt, _T("|"));

	for (int i = 0; i < AudioVideoExtensions.GetCount(); i++)
	{
		int Item = ExtList.InsertItem(0, Dlg->Lang[Dlg->GetLanguage()].GetAt(21), 0);
		ExtList.SetItemText(Item, 1, AudioVideoExtensions.GetAt(i));
	}

	SplitString(ImageExtensions, ImageExt, _T("|"));

	for (int i = 0; i < ImageExtensions.GetCount(); i++)
	{
		int Item = ExtList.InsertItem(0, Dlg->Lang[Dlg->GetLanguage()].GetAt(22), 1);
		ExtList.SetItemText(Item, 1, ImageExtensions.GetAt(i));
	}

	return TRUE;
}

void CExtensionsDlg::OnBnClickedAdd()
{
	CExtDlg Dialog(Dlg);

	if (Dialog.DoModal() == IDOK)
	{
		CString Ext = Dialog.Ext;

		if (!Ext.IsEmpty())
		{
			Ext.MakeLower();

			int pos = -1;

			if (Dialog.Sel == 0)
			{
				pos = FindString(AudioVideoExtensions, Ext);

				if (pos < 0)
				{
					AudioVideoExtensions.Add(Ext);

					int Item = ExtList.InsertItem(0, Dlg->Lang[Dlg->GetLanguage()].GetAt(21), 0);
					ExtList.SetItemText(Item, 1, Ext);
				}
			}

			else
			{
				pos = FindString(ImageExtensions, Ext);

				if (pos < 0)
				{
					ImageExtensions.Add(Ext);

					int Item = ExtList.InsertItem(0, Dlg->Lang[Dlg->GetLanguage()].GetAt(22), 1);
					ExtList.SetItemText(Item, 1, Ext);
				}
			}

			if (pos < 0)
			{
				Dlg->SetAudioVideo(GetAudioVideoExt());
				Dlg->SetImage(GetImageExt());
			}
		}
	}
}

CString CExtensionsDlg::GetAudioVideoExt()
{
	CString Ret;
	Ret.Empty();

	INT_PTR len = AudioVideoExtensions.GetCount();

	for (int i = 0; i < len; i++)
	{
		Ret += AudioVideoExtensions.GetAt(i);

		if (i < (len-1))
		{
			Ret += "|";
		}
	}

	return Ret;
}

CString CExtensionsDlg::GetImageExt()
{
	CString Ret;
	Ret.Empty();

	INT_PTR len = ImageExtensions.GetCount();

	for (int i = 0; i < len; i++)
	{
		Ret += ImageExtensions.GetAt(i);

		if (i < (len-1))
		{
			Ret += "|";
		}
	}

	return Ret;
}

void CExtensionsDlg::OnNMRclickExtlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	int Sel = -1;

	POSITION p = ExtList.GetFirstSelectedItemPosition();

	while (p)
	{
		Sel = ExtList.GetNextSelectedItem(p);
	}

	if ((Sel >= 0) && ExtList.GetItemCount() > 0 && Sel <= ExtList.GetItemCount())
	{
		int Menu = Dlg->GetLanguage() == 0 ? IDR_EXTMENU : IDR_EXTMENU_IT;

		pSubMenu->DestroyMenu();
		pSubMenu->LoadMenuW(Menu);

		POINT point;
		GetCursorPos(&point);

		if (pSubMenu)
		{
			pSubMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
		}
	}

	*pResult = 0;
}

void CExtensionsDlg::OnRemoveext()
{
	int Sel = -1;

	POSITION p = ExtList.GetFirstSelectedItemPosition();

	while (p)
	{
		Sel = ExtList.GetNextSelectedItem(p);
	}

	if ((Sel >= 0) && ExtList.GetItemCount() > 0 && Sel <= ExtList.GetItemCount())
	{
		int pos = FindString(AudioVideoExtensions, ExtList.GetItemText(Sel, 1));

		if (pos >= 0)
		{
			AudioVideoExtensions.RemoveAt(pos);
			ExtList.DeleteItem(Sel);
		}

		else
		{
			pos = FindString(ImageExtensions, ExtList.GetItemText(Sel, 1));

			if (pos >= 0)
			{
				ImageExtensions.RemoveAt(pos);
				ExtList.DeleteItem(Sel);
			}
		}

		if (pos >= 0)
		{
			Dlg->SetAudioVideo(GetAudioVideoExt());
			Dlg->SetImage(GetImageExt());
		}
	}
}
