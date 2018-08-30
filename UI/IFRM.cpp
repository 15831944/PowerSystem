// IFRM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "IFRM.h"
#include "MainFrm.h"
#include "IFRMDoc.h"

#include "IFRMView.h"
#include "CreditsDlg.h"
#include "PassWordDlg.h"
#include "HyperLink.h" 
#include "RuntimeAccount.h"
#include "AppInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp

BEGIN_MESSAGE_MAP(CIFRMApp, CWinApp)
	//{{AFX_MSG_MAP(CIFRMApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp construction

CIFRMApp::CIFRMApp()
{
	AppInfo::Instance().m_WhichKind        =  FALSE; //TRUE  ���վ�汾   MessageBeep                   FALSE ��ְ�
	AppInfo::Instance().m_2000Users        =  FALSE; //TRUE 2000�û�   TRUE�û�����������
	AppInfo::Instance().m_AutoRunning      =  TRUE;  //TRUETRUE�Ƿ�һ�������Զ�����
	AppInfo::Instance().m_SingleBB         =  TRUE; //FALSE�Ƿ��ǵ�һ�汾
	AppInfo::Instance().m_YanShi           =  FALSE; //FALSETRUE; //�Ƿ�����ʾ�汾
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFRMApp object

CIFRMApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CIFRMApp initialization

BOOL CIFRMApp::InitInstance()
{

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    
//	AfxMessageBox(m_pszAppName);

	//�˳���ֻ������һ�Σ��û��������жϳ����Ƿ�������
    HANDLE m_hMutex = CreateMutex(NULL,TRUE, m_pszAppName); 
   
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{ 
		//::MessageBox("��������ͬ������Ѿ��������У�"," ",MB_OK|MB_ICONWARNING);
		//AfxMessageBox("��������ͬ������������У�",MB_OK, 0 );
		return FALSE; 
	}


	//���öԻ��򱳾����ı���ɫ
	//SetDialogBkColor(RGB(221,221,221),RGB(0,0,0));	//160,180,220
	
	//SetDialogBkColor(RGB(0xFF, 0xFF, 0xE0),RGB(0, 0,0));
	//SetDialogBkColor(RGB(0,255,255), RGB(0, 0,255));
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
    
	//�Ƿ�һ�������Զ�����
	
	if(!AppInfo::Instance().m_AutoRunning)
	{
		CPassWordDlg  password;

		password.m_SingleBB = AppInfo::Instance().m_SingleBB;

		if(password.DoModal() != IDOK)
		{
			return  FALSE;
		}
		
		//�汾���� 0 Զ��    1 ����
		AppInfo::Instance().m_WhichKind  = password.m_softkind; 
		//Ȩ���ȼ�����0 ---���� 1-�ճ� 2-���� 3-����
		//m_RightGrade = password.m_userkind;	

	}
	else
	{
		//�汾���� 0 Զ��    1 ����
		AppInfo::Instance().m_WhichKind  = 1; 
		//Ȩ���ȼ�����0 ---���� 1-�ճ� 2-���� 3-����
		//chh m_RightGrade = 0;	
	}

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views.
    

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIFRMDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CIFRMView));
	
	/*pDocTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));*/
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	CString   UseName,TitleName;
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);

	switch(CRuntimeAccount::GetCurrentPrivilege())
	{
	case 0:
		{
			UseName = "�߼�����Ա";
			break;
		}
	case 1:
		{
			UseName = "��ͨ����Ա";
			break;
		}
	case 2:
		{
			UseName = "�߼��û�";
			break;
		}
	case 3:
		{
			UseName = "��ͨ�û�";
			break;
		}
	}
	
	if(AppInfo::Instance().m_WhichKind)//ѡ�����ֱ� //TRUE ���վ�汾  FALSE��ְ�
	{
		
		//m_2000Users  TRUE 2000�û� FALSE �û�����������
		if(AppInfo::Instance().m_2000Users)
		{
		
			TitleName.Format("��Ƶ����Զ�̳���ϵͳ1.90f���ذ�-[2000�û�-%s]",UseName);
		
		}
		else
		{
			
			TitleName.Format("��Ƶ����Զ�̳���ϵͳ1.90f��-[%s]",UseName);//����
		
		}
		
	}
	else
	{	
		
		//m_2000Users  TRUE 2000�û� FALSE �û�����������
		if(AppInfo::Instance().m_2000Users)
		{  
			TitleName.Format("��Ƶ����Զ�̳���ϵͳ1.90fԶ�̰�-[2000�û�-%s]",UseName);
		}
		else
		{	
			TitleName.Format("��Ƶ����Զ�̳���ϵͳ1.90fԶ�̰�-[%s]",UseName);
		}
		
	}
	
	//�Ƿ�����ʾ�汾
	if(AppInfo::Instance().m_YanShi)
	{
		m_pMainWnd->SetWindowText(TitleName + "---��ʾ��");
	}
	else
	{
		m_pMainWnd->SetWindowText(TitleName);
	}
	
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	
	//Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_mail;
	CHyperLink	m_address;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddress();
	afx_msg void OnEmail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL, m_mail);
	DDX_Control(pDX, IDC_ADDRESS, m_address);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_ADDRESS, OnAddress)
	ON_BN_CLICKED(IDC_EMAIL, OnEmail)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// App command to run the dialog
void CIFRMApp::OnAppAbout()
{
	//��ʾ��ʼ����
    CCreditsDlg  dlg;
	dlg.DoModal();
	//CAboutDlg aboutDlg;
	//aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CIFRMApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_mail.SetURL(_T("mailto:market@incomep.com"));
	m_mail.SetUnderline(CHyperLink::ulAlways);

	m_address.SetURL(_T("http://www.incomep.com"));
	m_address.SetUnderline(CHyperLink::ulAlways);
	
	return TRUE;  
}

void CAboutDlg::OnAddress() 
{
	// TODO: Add your control notification handler code here
	
}

void CAboutDlg::OnEmail() 
{
	// TODO: Add your control notification handler code here
	
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
