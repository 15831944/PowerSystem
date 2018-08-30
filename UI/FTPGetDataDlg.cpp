// FTPGetData.cpp : implementation file
//

#include "stdafx.h"
#include "ifrm.h"
#include "FTPGetDataDlg.h"
#include "MainFrm.h"
#include "IFRMDoc.h"
#include "IFRMView.h"
#include "ChildStationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPGetData dialog


CFTPGetDataDlg::CFTPGetDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFTPGetDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTPGetData)
	m_anomymous   =  FALSE;
	m_everytimes  =     15;
	m_description = _T("");
	//}}AFX_DATA_INIT
}


void CFTPGetDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTPGetData)
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Text(pDX, IDC_LOGIN, m_loginname);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Check(pDX, IDC_ANONYMOUS, m_anomymous);
	DDX_Text(pDX, IDC_TIMES, m_everytimes);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFTPGetDataDlg, CDialog)
	//{{AFX_MSG_MAP(CFTPGetData)
	ON_BN_CLICKED(IDC_ANONYMOUS, OnAnonymous)
	ON_BN_CLICKED(IDC_CONNECTTEST, OnConnecttest)
	ON_BN_CLICKED(ID_SET, OnSet)
	ON_BN_CLICKED(ID_DATARANGE, OnDatarange)
	ON_BN_CLICKED(ID_HANDSET, OnHandset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPGetData message handlers

void CFTPGetDataDlg::OnAnonymous() 
{
	UpdateData(TRUE);

	if(m_anomymous)
	{
		CWnd* pt = GetDlgItem(IDC_LOGIN);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_PASSWORD);
		pt->EnableWindow(FALSE);
	}
	else
	{
		CWnd* pt = GetDlgItem(IDC_LOGIN);
		pt->EnableWindow(TRUE);
		pt = GetDlgItem(IDC_PASSWORD);
		pt->EnableWindow(TRUE);
	}
}

BOOL CFTPGetDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    //���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_FTP);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);	
   	CIFRMView* pview = (CIFRMView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
 	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	IPAddr->SetWindowText(pview->m_address);	
    
	CWnd* pt  = GetDlgItem(ID_SET);
	pt->EnableWindow(FALSE);
    pt  = GetDlgItem(ID_HANDSET);
	pt->EnableWindow(FALSE);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFTPGetDataDlg::OnConnecttest() 
{
	UpdateData(TRUE);
    CString         m_address;	
	CInternetSession      ses;	
	CString               str;
	FILETIME  RemoteLastWrite;
    SYSTEMTIME     systemTime;
	
	//�û���
	m_loginname.TrimLeft();
    m_loginname.TrimRight();
    
	//����
	m_password.TrimLeft();
    m_password.TrimRight();

	CIFRMView* pview = (CIFRMView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	//��������ַ
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	IPAddr->GetWindowText(m_address);
    m_address.TrimLeft();
    m_address.TrimRight();

	//�ļ���
	m_FileName.TrimLeft();
    m_FileName.TrimRight();

	if(m_FileName.IsEmpty())
	{
		MessageBox("�ļ�������Ϊ�գ�"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	CFtpConnection* pFTP;
	try
	{
	
       
		if(m_anomymous)
		{
			//��������
			pFTP = ses.GetFtpConnection(m_address,"anonymous","",m_port,FALSE);
		}
		else
		{
			//���û���������
			pFTP = ses.GetFtpConnection(m_address,m_loginname,m_password,m_port,FALSE);
		}

		if (pFTP) 
		{	
			m_description = m_description  + "���������ӳɹ�...\r\n";

			CFtpFileFind pFileFind(pFTP);
		
			//�����ļ�
			if(pFileFind.FindFile("/data/pub/" + m_FileName))//ykdocs.csv"))
			{	
			 
				pFileFind.FindNextFile();
				
				//����GetLastWriteTimeǰ�ȵ���FindNextFile()һ��
				pFileFind.GetLastWriteTime(&RemoteLastWrite);
				
				//ת�ļ�ʱ��Ϊϵͳʱ��
				::FileTimeToSystemTime(&RemoteLastWrite,&systemTime);
				
				str.Format("%d-%d-%d %d:%d:%d",systemTime.wYear,systemTime.wMonth,systemTime.wDay,systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
			
				m_description = m_description + "�ɹ��ҵ�" + m_FileName + "�ļ�������:" + str + "\r\n";//ykdocs.csv

				pFileFind.Close();
                delete pFTP;
				
				pview->m_address = m_address;
				CWnd* pt  = GetDlgItem(ID_SET);
				pt->EnableWindow(TRUE); 
				pt  = GetDlgItem(ID_HANDSET);
				pt->EnableWindow(TRUE);
				

			}
			else
			{
				m_description =  m_description + "FTP���������Ҳ���" + m_FileName + "�ļ�..." + "\r\n";//ykdocs.csv
			}

		}
	}
	catch(CInternetException *pEx)
	{
		char m_szStatus[1024];
		pEx->GetErrorMessage(m_szStatus, sizeof(m_szStatus));
		str           =  m_szStatus;
        m_description =  m_description  + str;
		pEx->Delete();
	}

	UpdateData(FALSE);
}

void CFTPGetDataDlg::OnSet() 
{

	UpdateData(TRUE);

	
	CString  m_address;
	CIFRMView* pview = (CIFRMView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
    
	
	if(m_everytimes < 15)
	{
        MessageBox("ʱ����Ӧ����15����!"," ",MB_OK|MB_ICONWARNING);
		return;
	}
		
	m_address.Format("ÿ��%d���Ӵӷ�������ȡ������һ���û����ݣ�",m_everytimes);

	if(MessageBox(m_address,"ѯ��",MB_YESNO|MB_ICONQUESTION) != IDYES)
	{
		return;
	}

	//��������ַ
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	IPAddr->GetWindowText(m_address);

    m_address.TrimLeft();
    m_address.TrimRight();
	
	if(m_anomymous)
	{
		//�û���
		m_loginname = "anonymous";
		//��  ��
		m_password  = "";
	}
	else
	{
		//�û���
		m_loginname.TrimLeft();
		m_loginname.TrimRight();
		//����
		m_password.TrimLeft();
		m_password.TrimRight();
	}

	//��������ַ
	pview->m_address     =   m_address;
	//�û���
    pview->m_loginname   = m_loginname;
	//����
	pview->m_password    =  m_password;
	//�˿ں�
    pview->m_port        =      m_port;
    
	//FTP�ļ���
	pview->m_FtpFileName = m_FileName;

    pview->KillTimer(2);
    pview->SetTimer(2,m_everytimes*60000,NULL);	
	m_address.Format("ÿ��%d���Ӵӷ�������ȡ������һ���û��������óɹ���",m_everytimes);
	MessageBox(m_address," ",MB_OK|MB_ICONASTERISK);

    CDialog::OnOK();
}

void CFTPGetDataDlg::OnDatarange() 
{
	CChildStationDlg dlg;
	dlg.DoModal();	
}

void CFTPGetDataDlg::OnHandset() 
{
	UpdateData(TRUE);
    CString   SqlStr;
	CIFRMView* pview = (CIFRMView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
   	
	//�ж��Ƿ��г���������
	if(pview->CheckRunning())
	{
		return;
	}

	if(MessageBox("����ǿ�ƴӷ������ϸ����û�������","ѯ��",MB_YESNO|MB_ICONQUESTION) != IDYES)
	{
	   return;
	}
	
	//ɾ��ԭ�����µ�ʱ��
	SqlStr.Format("DELETE FROM TB_REFRESHTIME");
    pview->ExecuteDataBaseSQL(SqlStr);

    pview->GetDataFormMarketServer(pview->m_address,pview->m_loginname,pview->m_password,pview->m_FtpFileName,pview->m_port);
    CDialog::OnOK(); 
}
