// EveryTimes.cpp : implementation file
//

#include "stdafx.h"

#include "EveryTimesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEveryTimes dialog


CEveryTimesDlg::CEveryTimesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEveryTimesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEveryTimes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEveryTimesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEveryTimes)
	DDX_Control(pDX, IDC_SPINEVERY, m_SpinEvery);
	DDX_Control(pDX, IDC_SPINTIME, m_SpinTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEveryTimesDlg, CDialog)
	//{{AFX_MSG_MAP(CEveryTimes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEveryTimes message handlers
BOOL CEveryTimesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_RESCYCLE);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	//ʱ����
	m_SpinEvery.SetRange(10,60);
    m_SpinEvery.SetPos(m_every);

	//����
	m_SpinTime.SetRange(1,100);
    m_SpinTime.SetPos(m_times);

	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEveryTimesDlg::OnOK() 
{
	//ѭ������,Ĭ����1 ��
	m_times =  m_SpinTime.GetPos();
	//��֮��ʱ����,Ĭ����30����
	m_every =  m_SpinEvery.GetPos();
	CDialog::OnOK();
}
