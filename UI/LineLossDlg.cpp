// LineLoss.cpp : implementation file
//

#include "stdafx.h"

#include "LineLossDlg.h"


#include "IFRMView.h"
#include "ParameterDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineLoss dialog


CLineLossDlg::CLineLossDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLineLossDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineLoss)
	m_radios = 0;
	m_title = _T("");
	//}}AFX_DATA_INIT
	m_StrSql  = "";
	BeginTime = "";
	EndTime   = "";
}


void CLineLossDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineLoss)
	DDX_Control(pDX, IDC_ENDTIME, m_listend);
	DDX_Control(pDX, IDC_BEGINTIME, m_listbegin);
	DDX_Radio(pDX, IDC_RADIO1, m_radios);
	DDX_Text(pDX, IDC_TITLE, m_title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineLossDlg, CDialog)
//{{AFX_MSG_MAP(CLineLoss)
ON_BN_CLICKED(IDC_TOTAL, OnTotal)
ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_CBN_SELCHANGE(IDC_BEGINTIME, OnSelchangeBegintime)
	ON_CBN_SELCHANGE(IDC_ENDTIME, OnSelchangeEndtime)
	ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
	ON_BN_CLICKED(IDC_RADIO42, OnRadio42)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineLoss message handlers



BOOL CLineLossDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//��ʼ��Combo
	InitializeCombo();

	//�������
	CTime t       = CTime::GetCurrentTime();
	GetCompanyNames = GetCompanyName();
	GetCompanyNames.TrimLeft();
    GetCompanyNames.TrimRight();
    m_title.Format("%s%d��%d�³����嵥",GetCompanyNames,t.GetYear(),t.GetMonth());
    
	m_GetDataname = "TB_EXCERPTION";
	UpdateData(FALSE);	
	//���ھ���
	CenterWindow();

	return TRUE;  
}

void CLineLossDlg::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CLineLossDlg::InitializeCombo()
{   
	//�����ݿ�
	CDatabase   db;
	CString strSql;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//��˾����ʼ
		CDaoRecordset m_CompanySet(m_pDatabase);
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT GARRISON_HALTTIME from TB_GARRISON order by GARRISON_HALTTIME "));
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_listbegin.AddString(strSql);
			m_listend.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//��˾����
		
		delete m_pDatabase;
		m_pDatabase = NULL; 
	
		//û��ѡ��
		if(m_listbegin.GetCount() > 0  && m_listend.GetCount() > 0)
		{

			m_listbegin.SetCurSel(0);
		    m_listend.SetCurSel(m_listend.GetCount()-1);
			
			//�õ���ʼʱ��ͽ���ʱ��
			m_listbegin.GetLBText(0,BeginTime);
			m_listend.GetLBText(m_listend.GetCount() - 1,EndTime);

			BeginTime.TrimLeft();
			BeginTime.TrimRight();
			
			EndTime.TrimLeft();
			EndTime.TrimRight();
		}
		else
		{
			
			//û�з���פ�������û����ʼʱ��ͽ���ʱ��
			MessageBox("û����ʼʱ��ͽ���ʱ��!"," ",MB_OK|MB_ICONWARNING);
			CWnd* pt = GetDlgItem(IDC_TOTAL);
			pt->EnableWindow(FALSE);
		}
		
	}
	
}


void CLineLossDlg::OnTotal() 
{
	
	UpdateData(TRUE);

	CString TableName,StrSql;
	
	m_title.TrimLeft();
    m_title.TrimRight();
	
	//������ȴ���100�Ļ�
	if(m_title.GetLength() >  100)
	{
        MessageBox("�������̫����ӦΪ1��50������(�����ֻ�Ӣ����ĸ)��"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	//�������Ϊ0�Ļ�
	if(m_title.GetLength() ==  0)
	{
        MessageBox("�����뱨����⣬ӦΪ1��50������(�����ֻ�Ӣ����ĸ)��"," ",MB_OK|MB_ICONWARNING);
		return;
	}
	
	//���ⳤ��
	BOOL m_GetChanged  = FALSE;

	for(int i = 0;i < m_title.GetLength();i ++)
	{
		char c = m_title.GetAt(i);
		
		//30  - 39  61-7A  41-5A
		if(!((c < 0x00 || c > 0xFF) || (c >= 0x30 && c <= 0x39) || (c >= 0x61 && c <= 0x7a) || (c >= 0x41 && c <= 0x5a)))
		{
		    m_GetChanged  = TRUE;
			break;
		}
	}
	
	if(m_GetChanged)
	{
	   MessageBox("Ϊ�˷�����EXCEL�ļ����������\r\nֻ������Ӣ�ġ����ֻ����ַ���"," ",MB_OK|MB_ICONWARNING);
	   return;   
	}

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CWnd* pt = GetDlgItem(IDCANCEL);
	pt->EnableWindow(FALSE);

	//���û�е�۱�
	if(m_radios == 0 || m_radios == 1)
	{

		if(CDataBaseInstance::GetAllRecordsCount("TB_ELECTRICITY","ALL") < 1)
		{
		
			CWnd* pt = GetDlgItem(IDCANCEL);
			pt->EnableWindow(TRUE);
           	MessageBox("�˱���Ҫ�õ���۱���Ϣ�������ڵ�۱���������Ϣ\r\n�Һ��û���Ϣ�����õ������Ӧ��ͳ�ƣ�"," ",MB_OK|MB_ICONWARNING);
			return;
		
		}

	}
	
	//������
	if(pview->IsCurveTableExist("TB_GARRISONBAK"))
	{
		//ɾ��ԭ���Ŀ��
		StrSql.Format("DROP TABLE TB_GARRISONBAK");
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}

	//����ʱ����ȡ����
	StrSql.Format("SELECT * INTO TB_GARRISONBAK FROM TB_GARRISON  WHERE GARRISON_HALTTIME='%s' OR GARRISON_HALTTIME='%s'",BeginTime,EndTime);
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	//��ԭ����ģ��Ż����ڵĺ�
	StrSql.Format("UPDATE TB_GARRISONBAK SET  GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENOOLD");
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

    //�й����,����ֵ
	StrSql.Format("UPDATE TB_GARRISONBAK SET GARRISON_WORKDEGREE = GARRISON_WORKDEGREE - b.CHANGEAMMETER_WORKDEGREE FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_HALTTIME>b.CHANGEAMMETER_UPDATETIME AND a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO");
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	//ͳ�Ƹ��ֲ���
	if(m_radios == 1)
	{
		//�������й���
	    StrSql.Format("UPDATE TB_GARRISONBAK SET GARRISON_WORKDEGREETOTAL = GARRISON_WORKDEGREETOTAL-b.CHANGEAMMETER_WORKDEGREETOTAL,\
		                                         GARRISON_LOSEDEGREE      = GARRISON_LOSEDEGREE-b.CHANGEAMMETER_LOSEDEGREE,\
											     GARRISON_LOSEDEGREETOTAL = GARRISON_LOSEDEGREETOTAL-b.CHANGEAMMETER_LOSEDEGREETOTAL,\
												 GARRISON_JFDL            = GARRISON_JFDL-b.CHANGEAMMETER_JFDL,\
												 GARRISON_FDL             = GARRISON_FDL -b.CHANGEAMMETER_FDL,\
												 GARRISON_PDL             = GARRISON_PDL -b.CHANGEAMMETER_PDL,\
												 GARRISON_GDL             = GARRISON_GDL -b.CHANGEAMMETER_GDL \
												 FROM TB_GARRISONBAK a,TB_CHANGEAMMETER b WHERE a.GARRISON_HALTTIME>b.CHANGEAMMETER_UPDATETIME AND a.GARRISON_MODULENO=b.CHANGEAMMETER_MODULENO");
	    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	 
	}

    switch(m_radios)
	{
	case 0:
		{
			//���ɳ����嵥
			pview->FormChaoBiaoData(m_AppearCondtion,BeginTime,EndTime);
			TableName = "TB_EXCERPTION";
			break;
		}
	case 1:
		{	
			//���ɸ��ֲ���ͳ�Ʊ�
			TableName = "TB_TOTAL";	
			CParameterDlg  dlg;
			if(dlg.DoModal() != IDOK)
			{
				pt->EnableWindow(TRUE);
				return;
			}	
			pview->ComingIntoBeing(m_AppearCondtion,BeginTime,EndTime,dlg.m_parameter1,dlg.m_parameter2,dlg.m_parameter3,dlg.m_parameter4,dlg.m_parameter5,dlg.m_parameter6,dlg.m_parameter7,dlg.m_parameter8);
			break;
		}
	case 2:
		{
			//��̨������ͳ�Ʊ�
			TableName = "TB_ELECTRICITYTOTAL";
			SubSupply(m_AppearCondtion);
			break;
		}
	case 3:
		{	
			//��ʼ����ͳ��
			pview->BeginTotalLoss(m_AppearCondtion,BeginTime,EndTime);
			TableName = "TB_ELECTRICITYLOSS";
			break;
		}
	case 4:
		{	
			TableName = "TB_WARN";	
			//���ɱ�������
			pview->ElectricityWarning(m_AppearCondtion,BeginTime,EndTime);
			break;
		}	
	} 
	
	if(CDataBaseInstance::GetAllRecordsCount(TableName,"ALL") == 0)
	{
        pt->EnableWindow(TRUE);
		pview->status("");
		MessageBox("û���ҵ��������������ݣ�"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	//���ɱ����б�
	pview->InitGrid(TableName,BeginTime,EndTime);
	
	//�������
	pview->m_Grid.m_title = m_title;
	pview->m_Grid.AutoSize();

	//ɾ���������ԭ���ļ�¼
	StrSql.Format("DELETE FROM %s",TableName);
    CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	
	//������
	if(pview->IsCurveTableExist("TB_GARRISONBAK"))
	{
		//ɾ��ԭ���Ŀ��
		StrSql.Format("DROP TABLE TB_GARRISONBAK");
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}

	CDialog::OnOK();
}


//�õ���˾���ڵ���
//CString Order    �����ֶ��� TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName  ��˾��
double CLineLossDlg::GetCompanyElc(CString Order,CString CompanyName)
{
    //�����ݿ�
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db);
		CString     strSql;
		//ͳ���ܹ�˾�µ����б��վ���ܱ��
		strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=5",Order,CompanyName,BeginTime,EndTime);
		rs.Open(CRecordset::forwardOnly,strSql);
		//��
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));	
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
	
}

//�õ�ĳ���վ������ܱ�ֵ�����������ܱ�ĺ�
//CString FieldName       �����ֶ������� TB_GARRISON.�й����
//CString CompanyName     ��˾��
//CString SubstationName  ���վ��
//short   kinds           ���� 0����������ı�ֵ 1��������������·�ı��
double CLineLossDlg::GetSubStaitonElc(CString Order,CString CompanyName, CString SubstationName,short kinds)
{
    //�����ݿ�
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db);
		CString     strSql;
		if(kinds == 0)
		{
			//ĳ���վ�����
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=4",Order,CompanyName,SubstationName,BeginTime,EndTime);
			
		}
		else
		{
			//ͳ��ĳ���վ���������ܱ�ĺ�
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=3",Order,CompanyName,SubstationName,BeginTime,EndTime);
		}
		rs.Open(CRecordset::forwardOnly,strSql);
		//��
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
}

//�õ�ĳ��·������ܱ�ֵ�������б�̨�ܱ�ĺ�
//CString FieldName       �����ֶ��� TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName     ��˾��
//CString SubstationName  ���վ��
//CString LineName        ��·����
//short   kinds           ���� 0����������ı�ֵ 1�����������б�̨�ı��
double CLineLossDlg::GetLineElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,short kinds)
{
	
    //�����ݿ�
	CString   strValue;
	CDatabase       db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db);
		CString     strSql;	
		
		if(kinds == 0)
		{
			//ĳ��·�����ֵ
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=3",Order,CompanyName,SubstationName,LineName,BeginTime,EndTime);
		}
		else
		{
			//ͳ��ĳ���վ���������ܱ�ĺ�
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISON WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (TB_GARRISON.GARRISON_HALTTIME='%s' OR TB_GARRISON.GARRISON_HALTTIME='%s')  AND TB_USER.USER_AMMETERKIND=2",Order,CompanyName,SubstationName,LineName,BeginTime,EndTime);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		//��
		rs.GetFieldValue((short)0,strValue);
		strValue.Format("%.2f",atof(strValue));
		rs.Close( );
		db.Close( );
		return atof(strValue);
	}
	return 0;
}




long CLineLossDlg::GetRecords(CString SqlStr)
{
	
	CDatabase         dbs;
	CString           sql;
	CString strValue = ""; 

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	{  
		//��CRecordset����
		CRecordset rss(&dbs );
		SqlStr.TrimLeft();
		SqlStr.TrimRight();
        
		rss.Open(CRecordset::forwardOnly,SqlStr);
		
		//�õ���¼����
	
		rss.GetFieldValue((short)0,strValue);
		//��¼���� atol(strValue); 
		rss.Close();
		dbs.Close();
		return atol(strValue);
	}
	return 0;
}

void CLineLossDlg::CheckNumbers()
{
	
	long begins = 0;
	long Ends   = 0;
	long Equals = 0; 
	CString  strSql;
	
	m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
	
	//ͳ�ƿ�ʼʱ��ĸ���
	strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s'",BeginTime);
	begins = GetRecords(strSql);
    
	//ͳ�ƽ���ʱ��ĸ���
	m_listend.GetLBText(m_listend.GetCurSel(),EndTime); 
    strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s'",EndTime);
	Ends   = GetRecords(strSql);
		
	strSql.Format("Select  COUNT(DISTINCT GARRISON_MODULENO) from TB_GARRISON WHERE GARRISON_HALTTIME='%s' OR GARRISON_HALTTIME='%s'",BeginTime,EndTime);
    Equals = GetRecords(strSql);


}

//�õ���̨�ĵ�ַ����
CString CLineLossDlg::GetSubName(CString Sql)
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
		
		Sql.TrimLeft();
		Sql.TrimRight();
		
		if(Sql.IsEmpty())
		{
       	    strSql = "SELECT count(*) FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT count(*) FROM TB_TRANSFORMER WHERE %s",Sql);
			
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		CString strValue;
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();
		
		if(Sql.IsEmpty())
		{
       	    strSql = "SELECT TRANSFORMER_POSITION FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT TRANSFORMER_POSITION FROM TB_TRANSFORMER WHERE %s",Sql);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j++)
		{
			rs.GetFieldValue((short)0,strValue);
			strValue.TrimLeft();
			strValue.TrimRight();
			
			fieldname = fieldname + strValue;
			
			//���»�һ����¼
			rs.MoveNext();
		}
		
		
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}
	
	if(!fieldname.IsEmpty())
	{
        fieldname = "��" + fieldname + "��";
	}
	return fieldname;
	
}


//�����嵥
void CLineLossDlg::OnRadio1() 
{
	m_radios  =   0;
	CTime t = CTime::GetCurrentTime();
	m_title.Format("%s%d��%d���û������嵥�����̨��",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname = "TB_EXCERPTION";
	UpdateData(FALSE);
	
}

//̨������ͳ�Ʊ���
void CLineLossDlg::OnRadio10() 
{
	m_radios  =   3;
	CTime t = CTime::GetCurrentTime();
	m_title.Format("%s%d��%d��̨������ͳ�Ʊ���",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname = "TB_ELECTRICITYLOSS";
	UpdateData(FALSE);
	
}


//��̨������ͳ�Ʊ�
void CLineLossDlg::OnRadio5() 
{
	m_radios  =   2;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d��%d�±�̨������ͳ�Ʊ�",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname =  "TB_ELECTRICITYTOTAL";
	UpdateData(FALSE);
}


//ͳ�Ʊ�̨������ 
void CLineLossDlg::SubSupply(CString m_Condtion)
{
		
	CDatabase                db;
	CString  m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,strsql;
	int    doors       =       0;//����
	int    m_records   =       0;//��¼��

   	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();


	//�жϱ��Ƿ����
	if(pview->IsCurveTableExist("TB_TOTLE"))
	{
		//ɾ��ԭ���ı�
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
	}
	
	//������ʱ��
    strsql.Format("SELECT * INTO TB_TOTLE FROM TB_USER WHERE %s",m_Condtion);
    CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//��˾����ʼ
		CDaoRecordset m_CompanySet(m_pDatabase);
		strsql = "SELECT count(*)  FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
		m_CompanySet.Open(dbOpenSnapshot,strsql);
		
		m_records = V_I4(&m_CompanySet.GetFieldValue(0));
        m_CompanySet.Close();
	
		strsql = "SELECT USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
        m_CompanySet.Open(dbOpenSnapshot,strsql);

	    pview->ShowProgressCtrl(TRUE);
        pview->SetProgressCtrlRange(0, m_records,1);
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
            m_STATIONNAME    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1));
            m_LINENAME       = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2));
            m_TRANSFORMERNO  = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(3));
			
	        pview->status("���ڼ����̨:" + m_TRANSFORMERNO);
		
			//�����̨�ĸ���ֵ
			GetSubSupply(m_CompanyName, m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,m_TRANSFORMERNO,BeginTime,EndTime);

			m_CompanySet.MoveNext();
            pview->SetProgressCtrlSetIt();

		}

		m_CompanySet.Close();
		delete m_pDatabase;	
		
		//ɾ��ԭ���ı�
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
		pview->ShowProgressCtrl(FALSE);
	}


}

//�õ�ĳ��̨������
//CString CompanyName     ��˾��
//CString SubstationName  ���վ��
//int     SubNo           ��̨��  
//CString LineName        ��·����
//CString SubNo           ��̨��
//CString SubName         ��̨��
//CString BeginTime       ��ʼʱ��
//CString EndTime         ����ʱ��
void  CLineLossDlg::GetSubSupply(CString CompanyName, CString SubstationName, CString LineName, CString SubNo,CString SubName,CString BeginTime,CString EndTime)
{
	
	CString           strValue;
	CString             strSql;  
	long            fields = 0;
	CDatabase               db;	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		
		//��CRecordset����
		CRecordset rs(&db);
		CString     str[5];
		
		//��¼����
		strSql.Format("SELECT COUNT(*) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",BeginTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,strSql);
		rs.Close();
		
		if(atoi(strSql) < 1)
		{	
			db.Close( );
			return;
		}
		
		//���¶���
		strSql.Format("SELECT SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",BeginTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,str[3]);
		rs.Close();	
		
		//���¶���
		strSql.Format("SELECT SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE) FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4))",EndTime,CompanyName,LineName,SubNo);//SubstationName,
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,str[4]);
		rs.Close();
		
		//ĳ��̨����ı�ֵ
		strSql.Format("SELECT TB_USER.USER_AMMETERNO,TB_USER.USER_MULTIPLE FROM TB_USER,TB_GARRISONBAK WHERE TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s' AND (TB_USER.USER_COMPANY='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s')",BeginTime,CompanyName,LineName,SubNo);
		
		rs.Open(CRecordset::forwardOnly,strSql);
		//��̨����
		str[0]      =          SubName;
		//�����
		rs.GetFieldValue((short)0,str[1]);
		//����
		rs.GetFieldValue((short)1,str[2]);

		//������ݣ���д�����
		strSql.Format("INSERT INTO TB_ELECTRICITYTOTAL(��̨����,���ܱ���,���¶���,���¶���,����) VALUES ('%s','%s',%.2f,%.2f,%d)",SubName,str[1],atof(str[3]),atof(str[4]),atoi(str[2]));
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		//�������
		strSql = "UPDATE  TB_ELECTRICITYTOTAL SET ���� = ROUND((���¶���-���¶���)*����,2)";
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		rs.Close( );
		db.Close( );
		
	}
	
	
}

//�õ���˾����
CString CLineLossDlg::GetCompanyName()
{	
	
	CDatabase                db;
	CString  m_CompanyName = "";
	CString              strsql;

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//��˾����ʼ
		CDaoRecordset m_CompanySet(m_pDatabase);
		m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT USER_COMPANY from TB_USER order by USER_COMPANY "));
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();

		delete m_pDatabase;
		
	}
	return m_CompanyName;
}

//��ʼʱ��
void CLineLossDlg::OnSelchangeBegintime() 
{	
	m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
    BeginTime.TrimLeft();
	BeginTime.TrimRight();
}

//����ʱ��
void CLineLossDlg::OnSelchangeEndtime() 
{
    m_listend.GetLBText(m_listend.GetCurSel(),EndTime);
    EndTime.TrimLeft();
	EndTime.TrimRight();	
}

BOOL CLineLossDlg::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

void CLineLossDlg::OnRadio41() 
{
	m_radios  =   1;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d��%d���й��޹���ѹ����ͳ�Ʊ�",GetCompanyNames,t.GetYear(),t.GetMonth());
	m_GetDataname =  "TB_ELECTRICITYTOTAL";
	UpdateData(FALSE);
}



void CLineLossDlg::OnRadio42() 
{
	m_radios  =   4;
	CTime t = CTime::GetCurrentTime();	
	m_title.Format("%s%d��%d�µ�������ͳ�Ʊ�",GetCompanyNames,t.GetYear(),t.GetMonth());
	UpdateData(FALSE);
}
