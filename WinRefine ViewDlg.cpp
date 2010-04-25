// WinRefine ViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinRefine View.h"
#include "WinRefine ViewDlg.h"
#include "GeneralDlg.h"
#include "SettingsDlg.h"
#include "EffectsDlg.h"
#include "ExtensionsDlg.h"
#include "Hyperlink.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MyKey CString(_T("Software\\CrystalSoft\\WinRefine"))
#define MyKeyCSID CString(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"))
#define MyCSID CString(_T("{3BE3D911-D0F6-4DBC-A9DB-E4ECA21C53A7}"))

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
	protected:
		DECLARE_MESSAGE_MAP()

	private:
		HICON hIcon;
		CStatic Icon;

		CHyperLink Link;
		CHyperLink ProdPage;
		CHyperLink LicenseDoc;
		CHyperLink SMS;

		afx_msg void OnClose();
		afx_msg void OnStnClickedLink();
		afx_msg void OnStnClickedLink2();
		afx_msg void OnStnClickedLink3();
		afx_msg void OnStnClickedSMS();

	protected:
		virtual void OnOK();
		virtual void OnCancel();
		virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINK, Link);
	DDX_Control(pDX, IDC_ICO, Icon);
	DDX_Control(pDX, IDC_LINK2, ProdPage);
	DDX_Control(pDX, IDC_LINK3, LicenseDoc);
	DDX_Control(pDX, IDC_SMS, SMS);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);
	Icon.SetIcon(hIcon);
	Icon.RedrawWindow();

	//Link.Set

	return TRUE;
}

void CAboutDlg::OnStnClickedLink()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("http://www.emuware.org/"), NULL, NULL, SW_SHOW);
}

void CAboutDlg::OnStnClickedLink2()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("http://www.emuware.org/?p=view&type=0&id=36"), NULL, NULL, SW_SHOW);
}

void CAboutDlg::OnStnClickedLink3()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("License.txt"), NULL, NULL, SW_SHOW);
}

void CAboutDlg::OnStnClickedSMS()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("http://www.fusionweb.it/"), NULL, NULL, SW_SHOW);
}

void CAboutDlg::OnClose()
{
	
}

void CAboutDlg::OnOK()
{
	
}

void CAboutDlg::OnCancel()
{
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_LINK, &CAboutDlg::OnStnClickedLink)
	ON_STN_CLICKED(IDC_LINK2, &CAboutDlg::OnStnClickedLink2)
	ON_STN_CLICKED(IDC_LINK3, &CAboutDlg::OnStnClickedLink3)
	ON_STN_CLICKED(IDC_SMS, &CAboutDlg::OnStnClickedSMS)
END_MESSAGE_MAP()

CWinRefineViewDlg::CWinRefineViewDlg(CWnd* pParent /*=NULL*/)
	: CTrayDialog(CWinRefineViewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinRefineViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, List);
	DDX_Control(pDX, IDC_CAPTION, Caption);
}

BEGIN_MESSAGE_MAP(CWinRefineViewDlg, CTrayDialog)
	ON_BN_CLICKED(IDC_APPLY, &CWinRefineViewDlg::OnBnClickedApply)
	ON_BN_CLICKED(IDCANCEL, &CWinRefineViewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_EXIT, &CWinRefineViewDlg::OnBnClickedExit)
	ON_COMMAND(IDC_CONFIGURE, &CWinRefineViewDlg::OnConfigure)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CWinRefineViewDlg::OnLvnItemchangedList)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

#include <afxinet.h>

CString DownloadTxtFile(CString url)
{
	wchar_t err[512];

	CString StrURL = url;
	CString StrMsg = _T("");

	CInternetFile* MyFile = NULL;
	CInternetSession* MySession = new CInternetSession(_T("WinRefine v0.3 by Emulator"), NULL);

	int isUTF8 = 0;
	int isConvert = 0;

	MySession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 6000);
	MySession->SetOption(INTERNET_OPTION_SEND_TIMEOUT, 60000);
	MySession->SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 60000);
	MySession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 500);
	MySession->SetOption(INTERNET_OPTION_CONNECT_RETRIES, 2);

	try
	{
		MyFile = (CInternetFile*)MySession->OpenURL(StrURL);
	}
				
	catch (CException* ex)
	{
		MyFile = NULL;

		ex->GetErrorMessage(err, 512, NULL);
		
		return err;
	}
				
	try 
	{
		if (MyFile)
		{
			if (MyFile->GetLength() < 1)
				return _T("Error: WinRefine#0x00000");

			CString Filesize;

			if (((CHttpFile*)MyFile)->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, Filesize))
			{
				int iTotolPos = _wtoi(Filesize);

				if (iTotolPos > 1048576)
				{
					return _T("Error: WinRefine#0x00001");
				}
			}
						
			DWORD dwStatusCode; 
						
			if (((CHttpFile*)MyFile)->QueryInfoStatusCode(dwStatusCode))
			{
				if (dwStatusCode == 400)
				{
					return _T("Error: WinRefine#0x00003");
				}
			}
						
			else
			{
				return _T("Error: WinRefine#0x00004");
			}
						
			CString StrLine;
						
			long Num_Line = 1;
						
			while (MyFile->ReadString(StrLine) != NULL)
			{
				Sleep(1);

				StrMsg += StrLine + _T("\r\n");

				Num_Line = Num_Line+1;
			}

			MyFile->Close();
			delete MyFile;
		}
	}

	catch (CException* ex)
	{
		delete MyFile;

		ex->GetErrorMessage(err, 512, NULL);
		
		return err;
	}

	MySession->Close();

	return StrMsg;
}

UINT CWinRefineViewDlg::UpdateChecker(LPVOID params)
{
	CWinRefineViewDlg* Dlg = (CWinRefineViewDlg*)params;

	Dlg->Threading = true;

	CString Domain = _T("http://www.emuware.org/");
	CString WinRefin = Domain + _T("winrefine/");

	CString Url = WinRefin + _T("update.php?ver=0.3");

	CString Esit = DownloadTxtFile(Url);
	Esit.Replace(_T("\n"), _T(""));
	Esit.Replace(_T("\r"), _T(""));

	if (Esit == "1") //Aggiornamento Disponibile
	{
		Dlg->Dialogs[0]->SetDlgItemTextW(IDC_VERSION, Dlg->Lang[Dlg->GetLanguage()].GetAt(10) + _T(" 0.3 - ") + Dlg->Lang[Dlg->GetLanguage()].GetAt(12));
	}

	else if (Esit == "0") //Nessun Aggiornamento
	{
		Dlg->Dialogs[0]->SetDlgItemTextW(IDC_VERSION, Dlg->Lang[Dlg->GetLanguage()].GetAt(10) + _T(" 0.3 - ") + Dlg->Lang[Dlg->GetLanguage()].GetAt(11));
	}

	else //Errore
	{
		
	}

	Dlg->Threading = false;

	return 0;
}

#define DIALOGS 5

BOOL CWinRefineViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	Threading = false;
	Selection = 0;

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//Language Definitions
	Lang[0].Add(_T("General")); //0
	Lang[0].Add(_T("Settings")); //1
	Lang[0].Add(_T("Extensions")); //2
	Lang[0].Add(_T("About")); //3
	Lang[0].Add(_T("Exit")); //4
	Lang[0].Add(_T("Apply")); //5
	Lang[0].Add(_T("Main WinRefine set-up")); //6
	Lang[0].Add(_T("Enable WinRefine")); //7
	Lang[0].Add(_T("Language")); //8
	Lang[0].Add(_T("Current Version")); //9
	Lang[0].Add(_T("Version")); //10
	Lang[0].Add(_T("No Updates available")); //11
	Lang[0].Add(_T("New version found!")); //12
	Lang[0].Add(_T("Go to Product Page")); //13
	Lang[0].Add(_T("Milliseconds to wait before Preview incoming")); //14
	Lang[0].Add(_T("Least Image Width/Height for preview show")); //15
	Lang[0].Add(_T("Thumbnail Dimensions")); //16
	Lang[0].Add(_T("Proportional Image stretch width")); //17
	Lang[0].Add(_T("Enabled Extensions list")); //18
	Lang[0].Add(_T("Type")); //19
	Lang[0].Add(_T("Extension")); //20
	Lang[0].Add(_T("Audio/Video")); //21
	Lang[0].Add(_T("Image")); //22
	Lang[0].Add(_T("Add Extension")); //23
	Lang[0].Add(_T("Main Site")); //24
	Lang[0].Add(_T("Product Page")); //25
	Lang[0].Add(_T("License")); //26
	Lang[0].Add(_T("Open License Document")); //27
	Lang[0].Add(_T("OK")); //28
	Lang[0].Add(_T("Cancel")); //29
	Lang[0].Add(_T("Effects")); //30
	Lang[0].Add(_T("Volume for Audio/Video files")); //31
	Lang[0].Add(_T("Transparency level for Image preview Tip")); //32
	Lang[0].Add(_T("Show default Windows Tooltip for Images")); //33
	Lang[0].Add(_T("Enable")); //34

	Lang[1].Add(_T("Generale")); //0
	Lang[1].Add(_T("Impostazioni")); //1
	Lang[1].Add(_T("Estensioni File")); //2
	Lang[1].Add(_T("About")); //3
	Lang[1].Add(_T("Esci")); //4
	Lang[1].Add(_T("Applica")); //5
	Lang[1].Add(_T("Impostazioni globali WinRefine")); //6
	Lang[1].Add(_T("Abilita WinRefine")); //7
	Lang[1].Add(_T("Linguaggio")); //8
	Lang[1].Add(_T("Versione Corrente")); //9
	Lang[1].Add(_T("Versione")); //10
	Lang[1].Add(_T("Nessun aggiornamento disponibile")); //11
	Lang[1].Add(_T("Trovata nuova versione!")); //12
	Lang[1].Add(_T("Vai alla Pagina Prodotto")); //13
	Lang[1].Add(_T("Attesa millisecondi prima dell'Anteprima")); //14
	Lang[1].Add(_T("Dimensioni Immagine minime per l'Anteprima")); //15
	Lang[1].Add(_T("Anteprima")); //16
	Lang[1].Add(_T("Dimensione in larghezza")); //17
	Lang[1].Add(_T("Estensioni file abilitate")); //18
	Lang[1].Add(_T("Tipo")); //19
	Lang[1].Add(_T("Estensione")); //20
	Lang[1].Add(_T("Audio/Video")); //21
	Lang[1].Add(_T("Immagine")); //22
	Lang[1].Add(_T("Aggiungi Estensione")); //23
	Lang[1].Add(_T("Sito Principale")); //24
	Lang[1].Add(_T("Pagina Prodotto")); //25
	Lang[1].Add(_T("Licenza")); //26
	Lang[1].Add(_T("Apri Documento di Licenza")); //27
	Lang[1].Add(_T("OK")); //28
	Lang[1].Add(_T("Annulla")); //29
	Lang[1].Add(_T("Effetti")); //30
	Lang[1].Add(_T("Impostazione Volume per i file Audio/Video")); //31
	Lang[1].Add(_T("Livello Trasparenza anteprima Immagine")); //32
	Lang[1].Add(_T("Visualizza il Tooltip per i file Immagine")); //33
	Lang[1].Add(_T("Abilita")); //34
	/////////////////

	TraySetIcon(IDR_MAINFRAME);
	TraySetToolTip(_T("WinRefine v0.3"));
	TraySetMinimizeToTray(FALSE);
	TrayShow();

	TitleFont.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, L"MS Shell Dlg");

	CImageList* ImgHeaders = new CImageList;

	//ImgHeaders->Create(32, 32, ILC_COLOR32, 0, 0);
	ImgHeaders->Create(16, 16, ILC_COLOR32, 0, 0);
	ImgHeaders->Add(AfxGetApp()->LoadIcon(IDR_GENERAL));
	ImgHeaders->Add(AfxGetApp()->LoadIcon(IDR_SETTINGS));
	ImgHeaders->Add(AfxGetApp()->LoadIcon(IDR_EFFECTS));
	ImgHeaders->Add(AfxGetApp()->LoadIcon(IDR_EXTENSIONS));
	ImgHeaders->Add(AfxGetApp()->LoadIcon(IDR_ABOUT));

	List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	List.InsertColumn(0, _T(""), LVCFMT_CENTER, 120);
	List.SetImageList(ImgHeaders, LVSIL_SMALL);

	Caption.SetFont(&TitleFont);
	Caption.SetBkColor(RGB(200, 200, 200));
	Caption.SetTextColor(RGB(0, 0, 0));

	DWORD Need = 1024;
	wchar_t Str[1024];

	MyPath = GetCommandLine();
	MyPath = MyPath.Left(MyPath.ReverseFind('\\') + 1);

	if (MyPath[0] == '\"')
	{
		MyPath = MyPath.Right(MyPath.GetLength()-1);
	}

	Enable = false;
	Language = 0;
	Latency = 0;
	Volume = 1000;
	ThumbnailSize = 300;
	MinWidth = 100;
	MinHeight = 100;
	Transparency = 240;
	Tooltip = 0;
	AudioVideo = _T("mp3|wav|avi|mpg|mpeg|wma|mpa|vob|wmv|asf");
	Image = _T("png|gif|bmp|jpg|jpeg|tiff|tif|psd|tga");

	if (Reg.Open(HKEY_CURRENT_USER, MyKey, KEY_READ) == ERROR_SUCCESS)
	{
		Reg.QueryDWORDValue(_T("Language"), Language);

		if (Language > 1)
		{
			Language = 0;
		}

		Reg.QueryDWORDValue(_T("Latency"), Latency);
		Reg.QueryDWORDValue(_T("Volume"), Volume);
		Reg.QueryDWORDValue(_T("ThumbnailSize"), ThumbnailSize);
		Reg.QueryDWORDValue(_T("MinWidth"), MinWidth);
		Reg.QueryDWORDValue(_T("MinHeight"), MinHeight);
		Reg.QueryDWORDValue(_T("Transparency"), Transparency);
		Reg.QueryDWORDValue(_T("Tooltip"), Tooltip);

		Need = 1024;
		*Str = 0;

		Reg.QueryStringValue(_T("AudioVideo"), Str, &Need);
		AudioVideo = Str;

		Need = 1024;
		*Str = 0;

		Reg.QueryStringValue(_T("Image"), Str, &Need);
		Image = Str;

		Reg.Close();
	}

	else
	{
		if (Reg.Create(HKEY_CURRENT_USER, MyKey) == ERROR_SUCCESS)
		{
			OnApply();
		}
	}

	//Menu
	pSubMenu = new CMenu;

	//Dialogs
	Dialogs[0] = new CGeneralDlg(this);
	Dialogs[0]->Create(IDD_GENERAL, CWnd::FromHandle(this->m_hWnd));

	Dialogs[1] = new CSettingsDlg(this);
	Dialogs[1]->Create(IDD_SETTINGS, CWnd::FromHandle(this->m_hWnd));

	Dialogs[2] = new CEffectsDlg(this);
	Dialogs[2]->Create(IDD_EFFECTS, CWnd::FromHandle(this->m_hWnd));

	Dialogs[3] = new CExtensionsDlg(this);
	Dialogs[3]->Create(IDD_EXTENSIONS, CWnd::FromHandle(this->m_hWnd));

	Dialogs[4] = new CAboutDlg();
	Dialogs[4]->Create(IDD_ABOUTBOX, CWnd::FromHandle(this->m_hWnd));

	for (int i = 0; i < DIALOGS; i++)
	{
		Dialogs[i]->ShowWindow(SW_HIDE);
		Dialogs[i]->SetWindowPos(NULL, 142, 35, 0, 0, SWP_NOSIZE);
	}

	Dialogs[0]->ShowWindow(SW_SHOW);
	Dialogs[0]->RedrawWindow();

	if (Reg.Open(HKEY_LOCAL_MACHINE, MyKeyCSID, KEY_READ) == ERROR_SUCCESS)
	{
		if (Reg.QueryStringValue(MyCSID, Str, &Need) == ERROR_SUCCESS)
		{
			SetEnabled(true);

			Dialogs[0]->CheckDlgButton(IDC_ENABLED, BST_CHECKED);
		}

		Reg.Close();
	}

	Dialogs[1]->SetDlgItemInt(IDC_LATENCY, GetLatency(), TRUE);
	Dialogs[1]->SetDlgItemInt(IDC_WIDTH, GetMinWidth(), TRUE);
	Dialogs[1]->SetDlgItemInt(IDC_HEIGHT, GetMinHeight(), TRUE);
	Dialogs[1]->SetDlgItemInt(IDC_THUMBSIZE, GetThumbnailSize(), TRUE);

	((CSliderCtrl*)Dialogs[2]->GetDlgItem(IDC_VOLUME))->SetPos(Volume);
	((CSliderCtrl*)Dialogs[2]->GetDlgItem(IDC_TRANSPARENCY))->SetPos(Transparency);

	if (GetTooltip())
	{
		Dialogs[2]->CheckDlgButton(IDC_TOOLTIP, BST_CHECKED);
	}

	SwitchLang(GetLanguage());

	if (!Threading)
	{
		AfxBeginThread(UpdateChecker, this);
	}

	return TRUE;
}

void CWinRefineViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CWinRefineViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}

	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CWinRefineViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWinRefineViewDlg::SwitchLang(int Language)
{
	SetDlgItemTextW(IDC_EXIT, Lang[Language].GetAt(4));
	SetDlgItemTextW(IDC_APPLY, Lang[Language].GetAt(5));

	Dialogs[0]->SetWindowTextW(Lang[Language].GetAt(0));
	Dialogs[1]->SetWindowTextW(Lang[Language].GetAt(1));
	Dialogs[2]->SetWindowTextW(Lang[Language].GetAt(30));
	Dialogs[3]->SetWindowTextW(Lang[Language].GetAt(2));
	Dialogs[4]->SetWindowTextW(Lang[Language].GetAt(3));

	Dialogs[0]->SetDlgItemTextW(IDC_MAINT, Lang[Language].GetAt(6) + _T(":"));
	Dialogs[0]->SetDlgItemTextW(IDC_ENABLED, Lang[Language].GetAt(7));
	Dialogs[0]->SetDlgItemTextW(IDC_LANGT, Lang[Language].GetAt(8) + _T(":"));
	Dialogs[0]->SetDlgItemTextW(IDC_CURRT, Lang[Language].GetAt(9) + _T(":"));
	Dialogs[0]->SetDlgItemTextW(IDC_VERSION, Lang[Language].GetAt(10) + _T(" 0.3 - ") + Lang[Language].GetAt(11));
	Dialogs[0]->SetDlgItemTextW(IDC_PRODLINK, Lang[Language].GetAt(13));
	Dialogs[0]->RedrawWindow();

	Dialogs[1]->SetDlgItemTextW(IDC_MILLT, Lang[Language].GetAt(14) + _T(":"));
	Dialogs[1]->SetDlgItemTextW(IDC_MINT, Lang[Language].GetAt(15) + _T(":"));
	Dialogs[1]->SetDlgItemTextW(IDC_THUMBT, Lang[Language].GetAt(16) + _T(":"));
	Dialogs[1]->SetDlgItemTextW(IDC_STRETCHT, Lang[Language].GetAt(17) + _T(":"));

	Dialogs[2]->SetDlgItemTextW(IDC_VOLT, Lang[Language].GetAt(31) + _T(":"));
	Dialogs[2]->SetDlgItemTextW(IDC_TRANT, Lang[Language].GetAt(32) + _T(":"));
	Dialogs[2]->SetDlgItemTextW(IDC_TOOLT, Lang[Language].GetAt(33) + _T(":"));
	Dialogs[2]->SetDlgItemTextW(IDC_TOOLTIP, Lang[Language].GetAt(34));

	Dialogs[3]->SetDlgItemTextW(IDC_EXTT, Lang[Language].GetAt(18) + _T(":"));
	Dialogs[3]->SetDlgItemTextW(IDC_ADD, Lang[Language].GetAt(23));

	Dialogs[4]->SetDlgItemTextW(IDC_MAINT, Lang[Language].GetAt(24) + _T(":"));
	Dialogs[4]->SetDlgItemTextW(IDC_PRODT, Lang[Language].GetAt(25) + _T(":"));
	Dialogs[4]->SetDlgItemTextW(IDC_LINK2, Lang[Language].GetAt(13));
	Dialogs[4]->SetDlgItemTextW(IDC_LICT, Lang[Language].GetAt(26) + _T(":"));
	Dialogs[4]->SetDlgItemTextW(IDC_LINK3, Lang[Language].GetAt(27));

	List.DeleteAllItems();

	List.InsertItem(0, Lang[Language].GetAt(0), 0);
	List.InsertItem(1, Lang[Language].GetAt(1), 1);
	List.InsertItem(2, Lang[Language].GetAt(30), 2);
	List.InsertItem(3, Lang[Language].GetAt(2), 3);
	List.InsertItem(4, Lang[Language].GetAt(3), 4);
	List.SetItemState(Selection, LVIS_SELECTED, LVIS_SELECTED);

	OnLvnItemchangedList(NULL, NULL);

	int Menu = Language == 0 ? IDR_MENU : IDR_MENU_IT;

	pSubMenu->DestroyMenu();
	pSubMenu->LoadMenuW(Menu);

	if (pSubMenu)
	{
		pSubMenu->GetSubMenu(0)->SetDefaultItem(0, TRUE);

		TraySetMenu(pSubMenu->GetSubMenu(0)->GetSafeHmenu(), 0);
	}
}

void CWinRefineViewDlg::OnApply()
{
	if (Enable)
	{
		WinExec("regsvr32 \"" + CStringA(MyPath) + "WinRefine.dll\" /s", SW_HIDE);
	}

	else
	{
		WinExec("regsvr32 \"" + CStringA(MyPath) + "WinRefine.dll\" /u /s", SW_HIDE);
	}

	if (Reg.Open(HKEY_CURRENT_USER, MyKey, KEY_WRITE) == ERROR_SUCCESS)
	{
		Reg.SetDWORDValue(_T("Language"), GetLanguage());
		Reg.SetDWORDValue(_T("Latency"), GetLatency());
		Reg.SetDWORDValue(_T("Volume"), GetVolume());
		Reg.SetDWORDValue(_T("ThumbnailSize"), GetThumbnailSize());
		Reg.SetDWORDValue(_T("MinWidth"), GetMinWidth());
		Reg.SetDWORDValue(_T("MinHeight"), GetMinHeight());
		Reg.SetDWORDValue(_T("Transparency"), GetTransparency());
		Reg.SetDWORDValue(_T("Tooltip"), GetTooltip());
		Reg.SetStringValue(_T("AudioVideo"), GetAudioVideo());
		Reg.SetStringValue(_T("Image"), GetImage());

		Reg.Close();
	}
}

void CWinRefineViewDlg::OnBnClickedApply()
{
	OnApply();

	SwitchLang(GetLanguage());

	if (!Threading)
	{
		AfxBeginThread(UpdateChecker, this);
	}
}

void CWinRefineViewDlg::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
}

void CWinRefineViewDlg::OnBnClickedExit()
{
	CDialog::OnCancel();
}

void CWinRefineViewDlg::OnConfigure()
{
	ShowWindow(SW_SHOW);
}

void CWinRefineViewDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int Sel = -1;

	POSITION p = List.GetFirstSelectedItemPosition();

	while (p)
	{
		Sel = List.GetNextSelectedItem(p);
	}

	if ((Sel >= 0) && List.GetItemCount() > 0 && Sel <= List.GetItemCount())
	{
		if (Sel != Selection)
		{
			for (int i = 0; i < DIALOGS; i++)
			{
				Dialogs[i]->ShowWindow(SW_HIDE);
			}

			Dialogs[Sel]->ShowWindow(SW_SHOW);

			CString Title;
			Dialogs[Sel]->GetWindowTextW(Title);
			Dialogs[Sel]->RedrawWindow();

			Caption.SetWindowTextW(Title);

			Selection = Sel;
		}
	}

	if (pResult)
	{
		*pResult = 0;
	}
}

void CWinRefineViewDlg::SetEnabled(bool Enabled)
{
	CWinRefineViewDlg::Enable = Enabled;
}

void CWinRefineViewDlg::SetLanguage(DWORD Lang)
{
	CWinRefineViewDlg::Language = Lang;
}

void CWinRefineViewDlg::SetLatency(DWORD Latency)
{
	CWinRefineViewDlg::Latency = Latency;
}

void CWinRefineViewDlg::SetVolume(DWORD Volume)
{
	CWinRefineViewDlg::Volume = Volume;
}

void CWinRefineViewDlg::SetThumbnailSize(DWORD ThumbnailSize)
{
	CWinRefineViewDlg::ThumbnailSize = ThumbnailSize;
}

void CWinRefineViewDlg::SetMinWidth(DWORD MinWidth)
{
	CWinRefineViewDlg::MinWidth = MinWidth;
}

void CWinRefineViewDlg::SetMinHeight(DWORD MinHeight)
{
	CWinRefineViewDlg::MinHeight = MinHeight;
}

void CWinRefineViewDlg::SetTransparency(DWORD Transparency)
{
	CWinRefineViewDlg::Transparency = Transparency;
}

void CWinRefineViewDlg::SetTooltip(DWORD Tooltip)
{
	CWinRefineViewDlg::Tooltip = Tooltip;
}

void CWinRefineViewDlg::SetAudioVideo(CString AudioVideo)
{
	CWinRefineViewDlg::AudioVideo = AudioVideo;
}

void CWinRefineViewDlg::SetImage(CString Image)
{
	CWinRefineViewDlg::Image = Image;
}

bool CWinRefineViewDlg::GetEnabled()
{
	return Enable;
}

DWORD CWinRefineViewDlg::GetLanguage()
{
	return Language;
}

DWORD CWinRefineViewDlg::GetLatency()
{
	return Latency;
}

DWORD CWinRefineViewDlg::GetVolume()
{
	return Volume;
}

DWORD CWinRefineViewDlg::GetThumbnailSize()
{
	return ThumbnailSize;
}

DWORD CWinRefineViewDlg::GetMinWidth()
{
	return MinWidth;
}

DWORD CWinRefineViewDlg::GetMinHeight()
{
	return MinHeight;
}

DWORD CWinRefineViewDlg::GetTransparency()
{
	return Transparency;
}

DWORD CWinRefineViewDlg::GetTooltip()
{
	return Tooltip;
}

CString CWinRefineViewDlg::GetAudioVideo()
{
	return AudioVideo;
}

CString CWinRefineViewDlg::GetImage()
{
	return Image;
}