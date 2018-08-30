// WuGongDlg.cpp : implementation file
//

#include "stdafx.h"

#include "WuGongDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWuGongDlg dialog


CWuGongDlg::CWuGongDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWuGongDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWuGongDlg)
	m_up             =    80;
	m_down           =    50;
	m_EveryTimeKinds =    -1;
	//}}AFX_DATA_INIT
}


void CWuGongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWuGongDlg)
	DDX_Text(pDX, IDC_UP, m_up);
	DDX_Text(pDX, IDC_DOWN, m_down);
	DDX_CBIndex(pDX, IDC_COMBO1, m_EveryTimeKinds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWuGongDlg, CDialog)
	//{{AFX_MSG_MAP(CWuGongDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWuGongDlg message handlers

void CWuGongDlg::OnOK() 
{
	UpdateData(TRUE);
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString       SqlStr;
	
	UpdateData(TRUE);
	SqlStr.Format("DELETE FROM TB_WGUPDOWN");
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	SqlStr.Format("INSERT INTO TB_WGUPDOWN(WGUPDOWN_UP,WGUPDOWN_DOWN,WGUPDOWN_EVERYTIME) VALUES (%d,%d,%d)",m_up,m_down,m_EveryTimeKinds);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
    
	//�޹���ʱ�������� 0---10����  1---20����  2---30����
	pview->m_WgLess  = m_EveryTimeKinds;

	CDialog::OnOK();
}


//��Ӧģ�����������
void CWuGongDlg::GetWuGongUpDown()
{
	CString strValue,StrSql;
	CDatabase                   db;	
	m_up              =         80;
    m_down            =         50;
    m_EveryTimeKinds  =          0;
    //�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset    rs(&db );
		StrSql.Format("SELECT WGUPDOWN_UP,WGUPDOWN_DOWN,WGUPDOWN_EVERYTIME FROM TB_WGUPDOWN");
		rs.Open(CRecordset::dynaset,StrSql);	
		
		if(rs.IsEOF())
		{
			//�ر����ݿ�
			rs.Close( );
			db.Close( );
			return;
		}
		
		rs.GetFieldValue((short)0,strValue);
        m_up             = atoi(strValue);	
		rs.GetFieldValue((short)1,strValue);
        m_down           = atoi(strValue);
		rs.GetFieldValue((short)2,strValue);
        m_EveryTimeKinds = atoi(strValue);

    	//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}

}

BOOL CWuGongDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//��Ӧģ�����������
	GetWuGongUpDown();	

    UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
