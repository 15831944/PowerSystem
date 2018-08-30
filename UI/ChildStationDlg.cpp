// ChildStation.cpp : implementation file
//

#include "stdafx.h"

#include "ChildStationDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildStation dialog


CChildStationDlg::CChildStationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChildStationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChildStation)
	m_AddStation = _T("");
	//}}AFX_DATA_INIT
}


void CChildStationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChildStation)
	DDX_Control(pDX, IDC_LIST, m_ListBox);
	DDX_Text(pDX, IDC_ADDSTATION, m_AddStation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChildStationDlg, CDialog)
	//{{AFX_MSG_MAP(CChildStation)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildStation message handlers

//�õ����վ��Ϣ
void CChildStationDlg::GetAllStationInfo()
{
	//�����ݿ�
	CDatabase           db;
	CString         strSql;
	CString       strValue;
	CString fieldname = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//��CRecordset����
		CRecordset rs(&db );
	    strSql = "SELECT count(*) FROM TB_MANAGERANGE";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();
		
		//ɾ��ԭ�����б�����
		m_ListBox.ResetContent();

		if(fields  > 0)	
		{
      	    strSql = "SELECT USER_MANAGENO FROM TB_MANAGERANGE";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//���û���Ϣ
			for(int j = 0;j < fields; j++)
			{
				
				//�õ����վ�����Ϣ
				rs.GetFieldValue((short)0,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
							
				//�����б��
				m_ListBox.AddString(strValue);
						
				//���»�һ����¼
				rs.MoveNext();

			}
		
			//�ر����ݿ�
		    rs.Close( );
		
		}
		
		db.Close( );
	}

}



BOOL CChildStationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//�õ����վ�����Ϣ
    GetAllStationInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//���ӷ־�����段�վ
void CChildStationDlg::OnAdd() 
{
    UpdateData(TRUE);
	CString   StrSql;

	m_AddStation.TrimLeft();
	m_AddStation.TrimRight();
		
	if(m_AddStation.IsEmpty())
	{
		MessageBox("�����������������Ų���Ϊ��!"," ",MB_OK|MB_ICONWARNING);
		return;
	}
	else
	{	
		
		
        
		StrSql.Format("RTRIM(USER_MANAGENO)='%s'",m_AddStation);

		if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE",StrSql) < 1)
		{
			//û�д˵绰����,�򱣴�˵绰
	    	StrSql.Format("INSERT INTO TB_MANAGERANGE(USER_MANAGENO) VALUES ('%s')",m_AddStation);
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
			m_AddStation =  "";
			UpdateData(FALSE);
			
			//�õ����վ��Ϣ
            GetAllStationInfo();

		}
		else
		{
	     	MessageBox("�˷־ֹ����������Ѿ��Ѿ����ڣ�"," ",MB_OK|MB_ICONWARNING);
		}

	}
	
}

//ɾ���־�����段�վ
void CChildStationDlg::OnDelete() 
{
	
	CString     StrSql;
	CString   StrValue;
	
	if(m_ListBox.GetCurSel() != LB_ERR)
	{
		
		if(MessageBox("����ɾ������־ֹ�����������"," ",MB_YESNO|MB_ICONQUESTION)== IDYES)
		{
			
			//CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
			
			m_ListBox.GetText(m_ListBox.GetCurSel(),StrValue);
			
			StrSql.Format("RTRIM(USER_MANAGENO)='%s'",StrValue);
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE",StrSql) > 0)
			{
				//�������������ĺ���ɾ��
				StrValue.Format("DELETE FROM TB_MANAGERANGE WHERE %s",StrSql);
				CDataBaseInstance::ExecuteDataBaseSQL(StrValue);
				
				//�õ����վ��Ϣ
                GetAllStationInfo();
			}
			
		}
		
	}
	
}
