// PhaseTest.cpp : implementation file
//

#include "stdafx.h"

#include "PhaseTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhaseTest dialog


CPhaseTestDlg::CPhaseTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhaseTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhaseTest)
	m_times  = 3;
	m_nook   = FALSE;
	m_radio  = 0;
	//}}AFX_DATA_INIT
}


void CPhaseTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhaseTest)
	DDX_Text(pDX, IDC_TIMES, m_times);
	DDX_Check(pDX, IDC_NOOk, m_nook);
	DDX_Radio(pDX, IDC_RADIO25, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhaseTestDlg, CDialog)
	//{{AFX_MSG_MAP(CPhaseTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhaseTest message handlers

BOOL CPhaseTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//���ھ���
	CenterWindow();

	//���ô��ڵ�ͼ��
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_PARAMETER);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPhaseTestDlg::OnOK() 
{

	UpdateData(TRUE);  
	//�жϲ�����öԲ��� 
	
	//�������
   	if(m_times > 6 || m_times < 1)
	{
		MessageBox("���������ΧӦ��[1-6]֮��,������!","����",MB_OK|MB_ICONWARNING);
		return;
		
	}

	CDialog::OnOK();
}



void CPhaseTestDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}



BEGIN_EVENTSINK_MAP(CPhaseTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPhaseTest)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


