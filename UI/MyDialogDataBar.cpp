// MyDialogDataBar.cpp : implementation file
//

#include "stdafx.h"

#include "MyDialogDataBar.h"


#include "IFRMView.h"
#include "ShowDataDlg.h"
#include "DataBaseInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDataBar dialog


CMyDialogDataBar::CMyDialogDataBar()
{
	//{{AFX_DATA_INIT(CMyDialogDataBar)

	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar message handlers
BOOL CMyDialogDataBar::OnInitDialogBar()
{
	// Support for DDX mechanism
	// If you do not want DDX then
	// do not call base class
	CInitDialogBar::OnInitDialogBar();
	m_MaxPosition.vt   =   VT_I4;
    m_MaxPosition.lVal =      0;
 	return TRUE;
}

void CMyDialogDataBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialogDataBar)
	DDX_Control(pDX, IDC_DBGRID, m_dbgrid);
	DDX_Control(pDX, IDC_REMOTEDATACTL, m_remotedatactrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialogDataBar, CInitDialogBar)
	//{{AFX_MSG_MAP(CMyDialogDataBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogDataBar message handlers

void CMyDialogDataBar::ChangeSize()
{
	CRect rect;
    GetClientRect(rect);
    m_dbgrid.SetWindowPos(NULL,20,3,rect.right-rect.left-20,rect.bottom-rect.top-8,SWP_SHOWWINDOW);
}


//��ʾ����
void CMyDialogDataBar::initializeFieldInfo(CString m_title,CString m_totalsql,int columns,VARIANT  position)
{
	CString        Sqlstr;
    m_remotedatactrl.SetDataSourceName(_T("ifrm"));
    m_totalsql.TrimLeft();
	m_totalsql.TrimRight();
	long    m_records =  0;
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(m_totalsql == "ALL")
	{
		//��˾����,��վ���,���վ����,��·���,��·����,��̨����,ģ���,��,����,�û����,ԭ�û���,סַ,�绰,�õ�����,�����,�������,��װʱ��,����ֵ,����,�õ�����
		Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNAME AS ���վ����,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_NAME AS ����,USER_NO AS �û����,USER_MOTHERLINE  AS ĸ�߱��,USER_LINENO AS ��·���,USER_BAKMOTHERLINE  AS ����ĸ��,USER_BAKLINENO AS ���ó���,USER_PHASE AS ��,USER_PROTOCOL AS ����Э��,USER_MODULENO AS ģ���,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_DOWNVALUE AS �±���������,USER_UPVALUE AS �±���������,USER_DESCRIBE AS �õ����� FROM %s ORDER BY USER_MODULENO","TB_USER");
	}
	else
	{  
		Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNAME AS ���վ����,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_NAME AS ����,USER_NO AS �û����,USER_MOTHERLINE  AS ĸ�߱��,USER_LINENO AS ��·���,USER_BAKMOTHERLINE  AS ����ĸ��,USER_BAKLINENO AS ���ó���,USER_PHASE AS ��,USER_PROTOCOL AS ����Э��,USER_MODULENO AS ģ���,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_DOWNVALUE AS �±���������,USER_UPVALUE AS �±���������,USER_DESCRIBE AS �õ����� FROM %s WHERE %s ORDER BY USER_MODULENO","TB_USER",m_totalsql);
	}
	
	m_remotedatactrl.SetSql(Sqlstr);
	m_remotedatactrl.SetUserName(_T("admin"));
	m_remotedatactrl.SetPassword(_T(""));
	m_remotedatactrl.SetCursorDriver(2);
	m_remotedatactrl.SetReadOnly(TRUE);
	m_remotedatactrl.Refresh();
	
	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor=m_remotedatactrl.GetDSCCursor();
	ASSERT(pCursor!=NULL);
	m_dbgrid.SetDataSource(pCursor); //bind the grid
	m_dbgrid.BindProperty(0x9, &m_remotedatactrl);
	m_dbgrid.Scroll(columns, 0);
	m_dbgrid.SetBackColor(RGB(255,255,255));
	m_dbgrid.SetEditActive(FALSE);
	
	VARIANT  VAR = m_dbgrid.GetFirstRow();
    m_dbgrid.SetFirstRow(VAR);
	m_dbgrid.SetBookmark(position);	/**/
	m_dbgrid.Refresh(); 

	m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", m_totalsql);

    m_MaxPosition.vt   =           VT_I4;
    m_MaxPosition.lVal =       m_records;

	Sqlstr.Format("%s����¼������%d�ݣ�ģ�������%d��",m_title,m_records,CDataBaseInstance::Getmoduls(m_totalsql));
    m_dbgrid.SetCaption(Sqlstr);
	
}

//�·����ݼ�¼
void CMyDialogDataBar::ScrollRecord(VARIANT  position)
{
	VARIANT  VAR = m_dbgrid.GetFirstRow();
    m_dbgrid.SetFirstRow(VAR);
	
	if(position.lVal <= m_MaxPosition.lVal)
	{
		m_dbgrid.SetBookmark(position);	
		m_dbgrid.Refresh(); 
	}

}


