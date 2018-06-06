#include "stdafx.h"
#include "UsingSDK.h"
#include "UsingSDKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()




CUsingSDKDlg::CUsingSDKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsingSDKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsingSDKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CUsingSDKDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD_POLICY, &CUsingSDKDlg::OnBnClickedButtonLoadPolicy)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD_POLICY, &CUsingSDKDlg::OnBnClickedButtonUnloadPolicy)

END_MESSAGE_MAP()



BOOL CUsingSDKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		


	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(FALSE);


	LONG lStyle,dwStyle;
	lStyle = GetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE, lStyle); 

	dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_ListCtrl.SetExtendedStyle(dwStyle);

	m_ListCtrl.InsertColumn(0, _T("Event name"),   LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(1, _T("Data"),       LVCFMT_LEFT, 280);



	return TRUE;  
}

void CUsingSDKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUsingSDKDlg::OnPaint()
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


HCURSOR CUsingSDKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define  TEST_KEY "0123456789012345"

void CUsingSDKDlg::OnBnClickedButtonLoadPolicy()
{
	DWORD  CihperID = CIPHER_ID_XTEA ;
	int    bRandomKey = FALSE;
	DWORD  dwRet;

	//start engine
	dwRet = efsApi_SetStartFiltering(TRUE);

	//set cipher config
	efsApi_SetCryptConfig(CIPHER_ID_XTEA, bRandomKey, "0123456789012345",16);
	//efsApi_SetCryptConfig(CIPHER_ID_AES, bRandomKey, "01234567890123450123456789012345",32);

	//load built in application policy
	LoadNotepadPolicy();
	LoadWordpadPolicy();
	LoadWordPolicy();
	LoadExcelPolicy();
	LoadPPTPolicy();
	LoadAdobePDFPolicy();

	
	//load a custom policy
	//dwRet =  efsApi_AddPolicy(L"TEST.EXE",L".TXT|.TMP|", PROC_FLAG_ENCRYPT_ON_OPEN);

	//ENABLE  binding custom data
	//efsApi_SetCustomDataResident(1);

	//ENABLE manually encryption
	//efsApi_SetManualEncryptFile(1);

	//create event server
	CreateFileEventServer(&m_FileEventServer);
	m_FileEventServer->Startup( this);

	//start control module and efskrnl
	efsCtrl_Start();
	
	//ENABLE Eevent report
	//SetEventReportValue(1);
	
	//ENABLE  Access control 
	//SetPrivilegeControlValue(1);
	
	//ENABLE Faked Exe Checking
	//SetFakedExeCheckValue(1);

	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow( FALSE );
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_FILTER)->EnableWindow(FALSE);

	m_bStarted = TRUE;
}

void CUsingSDKDlg::OnBnClickedButtonUnloadPolicy()
{
	UnloadNotepadPolicy();
	UnloadWordpadPolicy();
	UnloadWordPolicy();
	UnloadExcelPolicy();
	UnloadPPTPolicy();
	UnloadAdobePDFPolicy();
	
	efsCtrl_Stop();

	delete m_FileEventServer;
	m_FileEventServer = NULL;

	efsApi_SetStartFiltering(FALSE);
	
	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow( TRUE );
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(FALSE);

	m_bStarted = FALSE;
}

void CUsingSDKDlg::OnCancel()
{
	if( m_bStarted )
	{
		return;
	}

	__super::OnCancel();
}

DWORD  CUsingSDKDlg::OnFileEvent(PFILE_EVENT_PACKET  pFileEventPacket) 
{
	int nItemCount = m_ListCtrl.GetItemCount();
	DWORD  dwRet = FE_SUCCESS;

	switch(pFileEventPacket->dwEventID )
	{
	case EVENT_ID_FILE_QUERY_PRIVILEGE:
		{
			DWORD dwRet;;
			CHAR  szCustomData[CUSTOM_DATA_SIZE]={0};

			m_ListCtrl.InsertItem(nItemCount, L"QUERY_PRIVILEGE");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->QueryPrivilege.wszSrcFileName);

			dwRet = efsApi_GetCustomData(pFileEventPacket->QueryPrivilege.wszSrcFileName, szCustomData , CUSTOM_DATA_SIZE);
			if( dwRet != EFSAPI_SUCCESS )
			{
				if(dwRet == EFSAPI_NOT_ENCRYPTED)
				{

				}
				else
				{
					pFileEventPacket->dwStatusCode = FE_NO_PRIVILEGE;
				}
				break;
			}

			CopyMemory(&pFileEventPacket->QueryPrivilege.Privilege, &szCustomData[256], sizeof(FILE_PRIVILEGE));
			pFileEventPacket->dwStatusCode = FE_SUCCESS;
		}
		break;


	case EVENT_ID_FILE_OPEN_FROM_API:
		{
			m_ListCtrl.InsertItem(nItemCount, L"OPEN_FROM_API");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FileOpenFromApi.wszSrcFileName);
		}
		break;


	case EVENT_ID_FILE_CLOSE_FROM_WND:
		{
			m_ListCtrl.InsertItem(nItemCount, L"CLOSE_FROM_WND");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FileCloseFromWnd.wszSrcFileName);
		}
		break;

	case EVENT_ID_FILE_PRINT:
		{
			m_ListCtrl.InsertItem(nItemCount, L"PRINT");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FilePrint.wszSrcFileName);
		}
		break;

	case EVENT_ID_FILE_SAVE_AS:
		{
			WCHAR   wszMsg[512]={0};

			m_ListCtrl.InsertItem(nItemCount, L"SAVEAS");

			wsprintf(wszMsg, L"%ws-->%ws",
				pFileEventPacket->FileSaveAs.wszSrcFileName, pFileEventPacket->FileSaveAs.wszDestFileName);

			m_ListCtrl.SetItemText(nItemCount, 1, wszMsg);
		}
		break;

	case EVENT_ID_FILE_QUERY_SIG_INFO:
		{
			if( _wcsicmp(pFileEventPacket->FileQuerySigInfo.SigInfo.wszExeName, L"WINWORD.EXE" ) == 0 )
			{
				pFileEventPacket->FileQuerySigInfo.SigInfo.Flags = VERIFY_SUBJECT_NAME_FIRST;
				wcscpy( pFileEventPacket->FileQuerySigInfo.SigInfo.wszSubjectName, L"Microsoft Corporation");
				wcscpy( pFileEventPacket->FileQuerySigInfo.SigInfo.wszMD5List,L"1EEA7DD2F1EA6EFEF380B99A90228D2F;");

				pFileEventPacket->dwStatusCode = FE_SUCCESS;
			}
			else
			{
				pFileEventPacket->dwStatusCode = FE_OBJECT_NOT_FOUND;
			}
		}
		break;

	case EVENT_ID_FILE_FAKED_DETECTED:
		{
			m_ListCtrl.InsertItem(nItemCount, L"FAKED_FILE");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FileFakedDected.wszSrcFileName);
		}
		break;

	case EVENT_ID_ENCRYPT_FILE_FORCE:
		{
			dwRet = efsApi_EncryptFile(pFileEventPacket->EncryptFileForce.wszSrcFileName);
			if(dwRet == EFSAPI_SUCCESS) 
			{
				pFileEventPacket->dwStatusCode = FE_SUCCESS;
			}
			else
			{
				pFileEventPacket->dwStatusCode = FE_NO_PRIVILEGE;
			}
		}
		break;

	default:
		{

		}
		break;

	}
	return dwRet;
}
