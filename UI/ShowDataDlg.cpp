// ShowData.cpp : implementation file
//

#include "stdafx.h"

#include "ShowDataDlg.h"

#include "MainFrm.h"
#include "IFRMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowData dialog


CShowDataDlg::CShowDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowData)
	m_radio3 = 0;
	m_radio  = 0;
	//}}AFX_DATA_INIT
}


void CShowDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowData)
	DDX_Radio(pDX, IDC_RADIO3, m_radio3);
	DDX_Control(pDX, IDC_REMOTEDATACTLS, m_remotedatactrl);
	DDX_Control(pDX, IDC_DBGRIDS, m_dbgrid);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowDataDlg, CDialog)
	//{{AFX_MSG_MAP(CShowData)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(ID_SAVEDATA, OnSavedata)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowData message handlers

//CString   m_SelectStr  �û�����ѡ��Χ 
//CString   m_DateRange  ����ʱ�䷶Χ
void CShowDataDlg::DataSort(CString m_SelectStr,CString m_DateRange)
{
	UpdateData(TRUE);
	CString     fieldname,strSql,sqlstr;
	CString     StrFields,m_RecordStr,m_modulestr;
	CString        StrTime,m_sequence;   
	CStringArray         m_FieldArray;
	
	if(m_radio3 == 0)
	{
		//����
        m_sequence = "ASC";
	}
	else
	{
		//����
		m_sequence = "DESC";
	}
	
	//����������
	if(whichsel < 4)
	{
		whichsel  =  4;
	}
	
	m_NameArray.RemoveAll(); 
	
	//�õ��û���������ֶ�
	m_FieldArray.Add("TB_USER.USER_COMPANY");       //��˾����
	m_NameArray.Add("��˾����");                    
	m_FieldArray.Add("TB_USER.USER_STATIONNAME");   //���վ����
    m_NameArray.Add("���վ����");
	m_FieldArray.Add("TB_USER.USER_LINENAME");      //��·����
	m_NameArray.Add("��·����");
	m_FieldArray.Add("TB_USER.USER_TRANSFORMERNO"); //��̨��
    m_NameArray.Add("��̨����");
	m_FieldArray.Add("TB_USER.USER_NO");            //�û����
	m_NameArray.Add("�û����");
	m_FieldArray.Add("TB_USER.USER_AMMETERNO");     //�����
	m_NameArray.Add("�����");

	if(m_Select[7])
	{
		m_FieldArray.Add("TB_USER.USER_NAME");     //�û���
		m_NameArray.Add("�û���");
		m_FieldArray.Add("TB_USER.USER_ADDRESS");  //�û���ַ
		m_NameArray.Add("�û���ַ");
	
	}

	switch(m_TableKinds)
	{
	case 0://��ʽ����
		{

			//�й���ʽ��
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREE");      
				m_NameArray.Add("�й����");
			}
			
			//�޹�
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREE");
				m_NameArray.Add("�޹����");
			}
			
			//����
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_ACURRENT");      
				m_NameArray.Add("A�����");
				m_FieldArray.Add("TB_REALTIME.REALTIME_BCURRENT");      
				m_NameArray.Add("B�����");
				m_FieldArray.Add("TB_REALTIME.REALTIME_CCURRENT");      
				m_NameArray.Add("C�����");
			}
			
			//��ѹ
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_AVOLTAGE");      
				m_NameArray.Add("A���ѹ");
				m_FieldArray.Add("TB_REALTIME.REALTIME_BVOLTAGE");      
				m_NameArray.Add("B���ѹ");
				m_FieldArray.Add("TB_REALTIME.REALTIME_CVOLTAGE");      
				m_NameArray.Add("C���ѹ");
			}		
			
			//�������й���
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREETOTAL");      
				m_NameArray.Add("�������й���");
			}
			
			//�������޹���
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREETOTAL");      
				m_NameArray.Add("�������޹���");
			}
			
			//������
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_JFDL");       
				m_NameArray.Add("������");	
			}
			
			//�����
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_FDL");       
				m_NameArray.Add("�����");	
			}
			
			//�ȵ���
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_GDL");       
				m_NameArray.Add("�ȵ���");	
			}
			
			//ƽ����
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_PDL");       
				m_NameArray.Add("ƽ����");	
			}
			
			//��������
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_REALTIME.REALTIME_GLYS");       
				m_NameArray.Add("��������");	
			}
			
			m_FieldArray.Add("TB_REALTIME.REALTIME_TRANSCRIBETIME");      
			m_NameArray.Add("����ʱ��");
			
			
			if(m_Select[6])
			{
				//ĸ�߱��
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("ĸ�߱��");
				//���߱��
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("���߱��");
				
				//ģ���
				m_FieldArray.Add("TB_REALTIME.REALTIME_MODULENO");       
				m_NameArray.Add("ģ���");
				//��ӦЭ��
				m_FieldArray.Add("TB_REALTIME.REALTIME_PROTOCOL"); 
				m_NameArray.Add("��ӦЭ��");
				//���
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("���");
			}
		
			break;
		}
	case 1://פ������
		{	
			
			//�й�פ����
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREE");     
				m_NameArray.Add("�й����");
			}
			
			//�޹�
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREE");     
				m_NameArray.Add("�޹����");
			}
			
			//����
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_ACURRENT");       
				m_NameArray.Add("A�����");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BCURRENT");       
				m_NameArray.Add("B�����");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CCURRENT");      
				m_NameArray.Add("C�����");
			}
			
			//��ѹ
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_AVOLTAGE");      
				m_NameArray.Add("A���ѹ");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BVOLTAGE");      
				m_NameArray.Add("B���ѹ");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CVOLTAGE");       
				m_NameArray.Add("C���ѹ");
			}
			
			//�������й���
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREETOTAL");
				m_NameArray.Add("�������й���");
			}	
			
			//�������޹���
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREETOTAL");
				m_NameArray.Add("�������޹���");
			}
			
			//������
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_JFDL");       
				m_NameArray.Add("������");	
			}
			
			//�����
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_FDL");       
				m_NameArray.Add("�����");	
			}
			
			//�ȵ���
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GDL");       
				m_NameArray.Add("�ȵ���");	
			}
			
			//ƽ����
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_PDL");       
				m_NameArray.Add("ƽ����");	
			}
			
			//��������
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GLYS");       
				m_NameArray.Add("��������");	
			}
			
			if(m_Select[6])
			{
				//ĸ�߱��
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("ĸ�߱��");
				//���߱��
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("���߱��");
				//ģ���
				m_FieldArray.Add("TB_GARRISON.GARRISON_MODULENO");       
				m_NameArray.Add("ģ���");
				//��ӦЭ��
				m_FieldArray.Add("TB_GARRISON.GARRISON_PROTOCOL"); 
				m_NameArray.Add("��ӦЭ��");
				//���
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("���"); 
				//����ʱ��
				m_FieldArray.Add("TB_GARRISON.GARRISON_TRANSCRIBETIME");      
				m_NameArray.Add("����ʱ��");
			}

			m_FieldArray.Add("TB_GARRISON.GARRISON_HALTTIME");      
			m_NameArray.Add("פ��ʱ��");
			break;
         }
	 case 2:
		 {

	
			 break;
		 }
    }
	
	//�ֶ�����
	for(int i = 0; i < m_FieldArray.GetSize(); i++)
	{
		
		if(i != m_FieldArray.GetSize() - 1)
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i] + ",";
		}
		else
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i];
		}
	
	}

	m_remotedatactrl.SetDataSourceName(_T("ifrm"));
	
	
	switch(m_TableKinds)
	{
	case 0:
		{
			//��ʽ��������,�û�ѡ��Χ
			if(m_DateRange == "ALL")
			{  
				sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
			}
			else
			{	
				sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_DateRange,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s)",m_SelectStr,m_DateRange);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND (%s)",m_SelectStr,m_DateRange);
			}
			
			break;

		}
	case 1:
		{
			//פ��ʱ��
			if(m_DateRange == "ALL")
			{ 		
				//����û�ѡ��Ϊ���֣�ʱ�䷶ΧΪȫ��
				sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_SelectStr);
				
			}
			else
			{	
				//����û�ѡ��Ϊ���֣�ʱ�䷶ΧΪ����
				sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_DateRange,m_SelectStr,m_FieldArray[whichsel],m_sequence);
				m_RecordStr.Format("SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_DateRange,m_SelectStr);
				m_modulestr.Format("SELECT COUNT(DISTINCT TB_USER.USER_MODULENO/100) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_DateRange,m_SelectStr);
			}

			break;
			
		}
	case 2:
		{


			break;
		}
	}

	m_remotedatactrl.SetSql(sqlstr);
	m_remotedatactrl.SetUserName(_T("admin"));
	m_remotedatactrl.SetPassword(_T(""));
	m_remotedatactrl.SetCursorDriver(2);
	m_remotedatactrl.SetReadOnly(TRUE);
	m_remotedatactrl.Refresh();
	
	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor = m_remotedatactrl.GetDSCCursor();
	ASSERT(pCursor != NULL);
	m_dbgrid.SetDataSource(pCursor); //bind the grid
	m_dbgrid.BindProperty(0x9, &m_remotedatactrl);
	m_dbgrid.Scroll(2, 0);
	m_dbgrid.SetEditActive(FALSE);
	
	//�����ݿ�
	CDatabase       dbs;	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset rs(&dbs);
		
		//�û�����
    	rs.Open(CRecordset::forwardOnly,m_RecordStr);
		rs.GetFieldValue((short)0,m_RecordStr);
		rs.Close();
	    
		//ģ�����
		rs.Open(CRecordset::forwardOnly,m_modulestr);
		rs.GetFieldValue((short)0,m_modulestr);
		rs.Close();

		dbs.Close();

		if(m_TableKinds == 0)
		{
			sqlstr.Format("��ʽ�������ݣ�ʱ�䷶Χ[%s]",m_TimeRangeStr);
		}
		else
		{	
			sqlstr.Format("פ���������ݣ�ʱ�䷶Χ[%s]",m_TimeRangeStr);
		}
		SetWindowText(sqlstr);
		
		sqlstr.Format("��������¼[%s]����ģ��[%s]��",m_RecordStr,m_modulestr);
	    m_remotedatactrl.SetCaption(sqlstr);

		//���û������
		if(atoi(m_RecordStr) < 1)
		{
			CWnd* pt = GetDlgItem(ID_SAVEDATA);
			pt->EnableWindow(FALSE);
			pt       = GetDlgItem(IDC_DELETE);
			pt->EnableWindow(FALSE);
		}
	
	}

}

void CShowDataDlg::OnSavedata() 
{

	UpdateData(TRUE);

	CString        fieldname,strSql,sqlstr,str;
	CString        StrFields,m_RecordStr,DataStr;
	CString        StrTime,m_sequence,filename;   
	CStringArray   m_FieldArray;
	char szFilter[] = "EXCEL�ļ�(*.CSV)|||";

	if(m_radio3 == 0)
	{
		//����
        m_sequence = "ASC";
	}
	else
	{
		//����
		m_sequence = "DESC";
	}
		
	if(m_TableKinds == 0)
	{
		DataStr         = "TB_REALTIME";
	}
	else
	{
		DataStr         = "TB_GARRISON";
	}

	m_NameArray.RemoveAll();

	switch(m_Kinds)
	{
	case 0:
		{
			
			//��ʾû��������������
			m_FieldArray.Add("USER_COMPANY");          //��˾����
			m_NameArray.Add("��˾����");   
			m_FieldArray.Add("USER_STATIONNO");        //��վ���
			m_NameArray.Add("��վ���");  
			m_FieldArray.Add("USER_STATIONNAME");     //���վ����
			m_NameArray.Add("���վ����");
			m_FieldArray.Add("USER_MOTHERLINE");      //ĸ�߱��    
			m_NameArray.Add("ĸ�߱��");
			m_FieldArray.Add("USER_LINENO");          //��·���
			m_NameArray.Add("��·���");
			m_FieldArray.Add("USER_LINENAME");        //��·����
			m_NameArray.Add("��·����");
			m_FieldArray.Add("USER_TRANSFORMERNO");   //��̨����
			m_NameArray.Add("��̨����");
			m_FieldArray.Add("USER_MODULENO");        //ģ���
			m_NameArray.Add("ģ���");
			m_FieldArray.Add("USER_PHASE");           //��
			m_NameArray.Add("��");
			m_FieldArray.Add("USER_NAME");            //����
			m_NameArray.Add("����");
			m_FieldArray.Add("USER_NO");              //�û����
			m_NameArray.Add("�û����");
			m_FieldArray.Add("USER_OLDNO");           //ԭ�û���
			m_NameArray.Add("ԭ�û���");
			m_FieldArray.Add("USER_ADDRESS");         //סַ
			m_NameArray.Add("סַ");
			m_FieldArray.Add("USER_PHONE");           //�绰
			m_NameArray.Add("�绰");
			m_FieldArray.Add("USER_ELECTRICITYKIND"); //�õ�����
			m_NameArray.Add("�õ�����");
			m_FieldArray.Add("USER_AMMETERNO");       //�����
			m_NameArray.Add("�����");
			m_FieldArray.Add("USER_AMMETERKIND");     //�������
			m_NameArray.Add("�������");
			m_FieldArray.Add("USER_INSTALLTIME");     //��װʱ��
			m_NameArray.Add("��װʱ��");
			m_FieldArray.Add("USER_INITIALVALUE");    //����ֵ
			m_NameArray.Add("����ֵ");
			m_FieldArray.Add("USER_MULTIPLE");       //����
			m_NameArray.Add("����");
			m_FieldArray.Add("USER_PROTOCOL");       //����Э��
			m_NameArray.Add("����Э��");
			m_FieldArray.Add("USER_DESCRIBE");       //�õ�����
			m_NameArray.Add("�õ�����");
	        m_FieldArray.Add("USER_RUNSTATUS");      //����״̬
			m_NameArray.Add("����״̬");
			break;

		}
	case 1:
		{
			
			//�õ��û���������ֶ�
			m_FieldArray.Add("TB_USER.USER_COMPANY");       //��˾����
			m_NameArray.Add("��˾����");                    
			m_FieldArray.Add("TB_USER.USER_STATIONNAME");   //���վ����
			m_NameArray.Add("���վ����");
			m_FieldArray.Add("TB_USER.USER_LINENAME");      //��·����
			m_NameArray.Add("��·����");
			m_FieldArray.Add("TB_USER.USER_TRANSFORMERNO"); //��̨��
			m_NameArray.Add("��̨����");
			m_FieldArray.Add("TB_USER.USER_NO");            //�û����
			m_NameArray.Add("�û����");
			m_FieldArray.Add("TB_USER.USER_AMMETERNO");     //�����
			m_NameArray.Add("�����");
			
			if(m_Select[7])
			{
				m_FieldArray.Add("TB_USER.USER_NAME");     //�û���
				m_NameArray.Add("�û���");
				m_FieldArray.Add("TB_USER.USER_ADDRESS");  //�û���ַ
				m_NameArray.Add("�û���ַ");
			}
			
			if(m_TableKinds == 0)
			{
				//��ʽ��
				
				//�й�
				if(m_Select[0])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREE");      
					m_NameArray.Add("�й����");
				}
				
				//�޹�
				if(m_Select[1])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREE");
					m_NameArray.Add("�޹����");
				}
				
				//����
				if(m_Select[2])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_ACURRENT");      
					m_NameArray.Add("A�����");
					m_FieldArray.Add("TB_REALTIME.REALTIME_BCURRENT");      
					m_NameArray.Add("B�����");
					m_FieldArray.Add("TB_REALTIME.REALTIME_CCURRENT");      
					m_NameArray.Add("C�����");
				}
				
				//��ѹ
				if(m_Select[3])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_AVOLTAGE");      
					m_NameArray.Add("A���ѹ");
					m_FieldArray.Add("TB_REALTIME.REALTIME_BVOLTAGE");      
					m_NameArray.Add("B���ѹ");
					m_FieldArray.Add("TB_REALTIME.REALTIME_CVOLTAGE");      
					m_NameArray.Add("C���ѹ");
				}		
				
				//�������й���
				if(m_Select[4])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_WORKDEGREETOTAL");      
					m_NameArray.Add("�������й���");
				}
				
				//�������޹���
				if(m_Select[5])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_LOSEDEGREETOTAL");      
					m_NameArray.Add("�������޹���");
				}
				
				//������
				if(m_Select[8])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_JFDL");       
					m_NameArray.Add("������");	
				}
				
				//�����
				if(m_Select[9])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_FDL");       
					m_NameArray.Add("�����");	
				}
				
				//�ȵ���
				if(m_Select[10])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_GDL");       
					m_NameArray.Add("�ȵ���");	
				}
				
				//ƽ����
				if(m_Select[11])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_PDL");       
					m_NameArray.Add("ƽ����");	
				}
				
				//��������
				if(m_Select[12])
				{
					m_FieldArray.Add("TB_REALTIME.REALTIME_GLYS");       
					m_NameArray.Add("��������");	
				}
				
				m_FieldArray.Add("TB_REALTIME.REALTIME_TRANSCRIBETIME");      
				m_NameArray.Add("����ʱ��");
				
				if(m_Select[6])
				{ 	
					
					//ĸ�߱��
					m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
					m_NameArray.Add("ĸ�߱��");
					//���߱��
					m_FieldArray.Add("TB_USER.USER_LINENO");       
					m_NameArray.Add("���߱��");
					//ģ���
					m_FieldArray.Add("TB_REALTIME.REALTIME_MODULENO");       
					m_NameArray.Add("ģ���");
					//��ӦЭ��
					m_FieldArray.Add("TB_REALTIME.REALTIME_PROTOCOL"); 
					m_NameArray.Add("��ӦЭ��");
					//���
					m_FieldArray.Add("TB_USER.USER_PHASE");   
					m_NameArray.Add("���");	
				}
				
		}
		else
		{
			//פ����			
			//�й�
			if(m_Select[0])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREE");     
				m_NameArray.Add("�й����");
			}
			
			//�޹�
			if(m_Select[1])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREE");     
				m_NameArray.Add("�޹����");
			}
			
			//����
			if(m_Select[2])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_ACURRENT");       
				m_NameArray.Add("A�����");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BCURRENT");       
				m_NameArray.Add("B�����");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CCURRENT");      
				m_NameArray.Add("C�����");
			}
			
			//��ѹ
			if(m_Select[3])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_AVOLTAGE");      
				m_NameArray.Add("A���ѹ");
				m_FieldArray.Add("TB_GARRISON.GARRISON_BVOLTAGE");      
				m_NameArray.Add("B���ѹ");
				m_FieldArray.Add("TB_GARRISON.GARRISON_CVOLTAGE");       
				m_NameArray.Add("C���ѹ");
			}
			
			//�������й���
			if(m_Select[4])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_WORKDEGREETOTAL");
				m_NameArray.Add("�������й���");
			}	
			
			//�������޹���
			if(m_Select[5])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_LOSEDEGREETOTAL");
				m_NameArray.Add("�������޹���");
			}
			
			//������
			if(m_Select[8])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_JFDL");       
				m_NameArray.Add("������");	
			}
			
			//�����
			if(m_Select[9])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_FDL");       
				m_NameArray.Add("�����");	
			}
			
			//�ȵ���
			if(m_Select[10])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GDL");       
				m_NameArray.Add("�ȵ���");	
			}
			
			//ƽ����
			if(m_Select[11])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_PDL");       
				m_NameArray.Add("ƽ����");	
			}
			
			//��������
			if(m_Select[12])
			{
				m_FieldArray.Add("TB_GARRISON.GARRISON_GLYS");       
				m_NameArray.Add("��������");	
			}
			
			if(m_Select[6])
			{
				//ĸ�߱��
				m_FieldArray.Add("TB_USER.USER_MOTHERLINE");       
				m_NameArray.Add("ĸ�߱��");
				//���߱��
				m_FieldArray.Add("TB_USER.USER_LINENO");       
				m_NameArray.Add("���߱��");
				//ģ���
				m_FieldArray.Add("TB_GARRISON.GARRISON_MODULENO");       
				m_NameArray.Add("ģ���");
				//��ӦЭ��
				m_FieldArray.Add("TB_GARRISON.GARRISON_PROTOCOL"); 
				m_NameArray.Add("��ӦЭ��");
				//���
				m_FieldArray.Add("TB_USER.USER_PHASE");   
				m_NameArray.Add("���"); 
				//����ʱ��
				m_FieldArray.Add("TB_GARRISON.GARRISON_TRANSCRIBETIME");      
				m_NameArray.Add("����ʱ��");
			}
			
			m_FieldArray.Add("TB_GARRISON.GARRISON_HALTTIME");      
			m_NameArray.Add("פ��ʱ��");
			
		}

		break;
	  }
	
    }
	
	//�ֶ�����
	for(int i = 0; i < m_FieldArray.GetSize(); i++)
	{
		
		if(i != m_FieldArray.GetSize() - 1)
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i] + ",";
		}
		else
		{
			StrFields = StrFields + m_FieldArray[i] + " AS " + m_NameArray[i];
		}
	
	}

	
	switch(m_Kinds)
	{
	case 0:
		{
			
			//ֻ��ʾû�ж�������ģ��
			if(m_TableKinds == 0)
			{

				switch(m_radio)
				{
				case 0://ȫ��δ��
					{
						//��ʽ����
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ","REALTIME_MODULENO",DataStr,m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ","REALTIME_MODULENO",DataStr,m_Condtion); 
						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ","REALTIME_MODULENO",DataStr,m_TimeRange,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ","REALTIME_MODULENO",DataStr,m_TimeRange,m_Condtion); 
						}

						break;
					}
				case 1://����
					{

						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 

						}
						
						break;
					}
				case 2://��·����
					{

						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
						}
						else
						{	
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}

						DataStr = "LineConnectError";
						break;
					}
				}

			}
			else
			{	
				
				switch(m_radio)
				{
				case 0://ȫ��δ��
					{
						//פ������
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND (%s)","GARRISON_MODULENO",DataStr,m_Condtion); 
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND (%s)","GARRISON_MODULENO",DataStr,m_Condtion); 
						}
						else
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬ FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND (%s) ","GARRISON_MODULENO",DataStr,m_TimeRange,m_Condtion); //,m_TimeRange
							m_RecordStr.Format("SELECT count(*) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND (%s) ","GARRISON_MODULENO",DataStr,m_TimeRange,m_Condtion);//,m_TimeRange); 

						}

						break;
					}	
				case 1://����
					{
                        if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER WHERE USER_RUNSTATUS=3"); 

						}
						else
						{	
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND (%s) ",m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 

						}

						break;
					}
				case 2://��·����ģ��
					{	
						
						if(m_TimeRange == "ALL")
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND (%s)",m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND %s",m_Condtion); 
						}
						else
						{
							sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND (%s)",m_TimeRange,m_Condtion); 
							m_RecordStr.Format("SELECT count(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND (%s)",m_TimeRange,m_Condtion); 
						}

						DataStr = "LineConnectError";
						break;
					}
				}

			}
			
			break;
		}
	case 1:
		{
			//��ʾ��������ģ��
			if(m_TableKinds == 0)
			{
				
				//��ʽ��������,�û�ѡ��Χ
				if(m_TimeRange == "ALL")
				{  
					sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_Condtion);
				}
				else
				{	
					sqlstr.Format("SELECT %s FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND %s ORDER BY TB_USER.USER_STATIONNAME,TB_USER.USER_LINENAME,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_TimeRange,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_REALTIME,TB_USER WHERE TB_REALTIME.REALTIME_MODULENO=TB_USER.USER_MODULENO AND (%s) AND %s",m_Condtion,m_TimeRange);
				}
				
			}
			else
			{
				//פ��ʱ��
				if(m_TimeRange == "ALL")
				{ 		
					//����û�ѡ��Ϊ���֣�ʱ�䷶ΧΪȫ��
					sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND (%s)",m_Condtion);
				}
				else
				{	
					//����û�ѡ��Ϊ���֣�ʱ�䷶ΧΪ����
					sqlstr.Format("SELECT %s FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s) ORDER BY TB_USER.USER_STATIONNO,TB_USER.USER_LINENO,TB_USER.USER_TRANSFORMERNO,%s %s",StrFields,m_TimeRange,m_Condtion,m_FieldArray[whichsel],m_sequence);
					m_RecordStr.Format("SELECT count(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND GARRISON_HALTTIME='%s' AND (%s)",m_TimeRange,m_Condtion);
				}
				
			}
			
			break;
		}

	}

	//�����ݿ�
	CDatabase       dbs;	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset rs(&dbs);
	
		rs.Open(CRecordset::forwardOnly,m_RecordStr);
		CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
      //  pview->WriteToLog(m_RecordStr);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,m_RecordStr);
		
	//	AfxMessageBox(m_RecordStr);

		rs.Close();
		dbs.Close();
		
	

	}

}

void CShowDataDlg::OnDelete() 
{

	CString    StrTime,str;
	CString         Sqlstr;
    CString   LineErrorStr;
	CString      Str1,Str2;
	int k     =          0;
	short     m_kinds = -1;

	if(m_TimeRangeStr.Find("����")!= -1)
	{
		StrTime = "";
		m_kinds =  0;
	}
	else
	{
		k = m_TimeRangeStr.Find("��");
		
		if(k != -1)
		{
			Str1    = m_TimeRangeStr.Left(m_TimeRangeStr.GetLength() - k - 2);
			Str2    = m_TimeRangeStr.Right(m_TimeRangeStr.GetLength()- k - 2);
			m_kinds = 1;
		}
		else
		{
            StrTime = m_TimeRangeStr;
			StrTime.TrimLeft();
            StrTime.TrimRight();
			m_kinds =  2;
		}
		
	}
    
	if(m_TableKinds  == 0)
	{	
		//��ʽ����
		switch(m_kinds)
		{
		case  0:
			{	
				str = "����ɾ������������������ʽ����������\r\n���棺����ɾ�����ָܻ�!!";
				break;
			}
		case 1:
			{
				str.Format("����ɾ������������ʱ�䷶ΧΪ[%s,%s]\r\n����ʽ���������𣿾��棺����ɾ�����ָܻ�!!",Str1,Str2);
				break;
			}
		case 2:
			{		
				str.Format("����ɾ�����������Ҷ���ʱ��Ϊ[%s]\r\n����ʽ���������𣿾��棺����ɾ�����ָܻ�!!",StrTime);
				break;
			}
		}

	}
	else
	{
		//פ����
		switch(m_kinds)
		{
		case  0:
			{	
				str = "����ɾ����������������פ������������\r\n���棺����ɾ�����ָܻ�!!";
				break;
			}
		case 1:
			{
				str.Format("����ɾ������������ʱ�䷶ΧΪ[%s,%s]\r\n��פ�����������𣿾��棺����ɾ�����ָܻ�!!",Str1,Str2);
				break;
			}
		case 2:
			{		
				str.Format("����ɾ�����������Ҷ���ʱ��Ϊ[%s]\r\n��פ�����������𣿾��棺����ɾ�����ָܻ�!!",StrTime);
				break;
			}
		}
	}
	

	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
    

		str.Format("�������ɾ������������?���ȷ��Ҫɾ��,��ѡ���ǰ�ť,\r\n����ɾ����ѡ���ť!���棺����ɾ�����ָܻ�!!");
		
		if(MessageBox(str,"����:",MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			//�����ݿ�
			CDatabase  db;

			if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
			{
			
				//SQl���
				if(m_TableKinds  == 0)
				{
					
					//��ʽ����
					switch(m_kinds)
					{
					case  0:
						{	
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							break;
						}
					case 1:
						{
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s')",m_Condtion,Str1,Str2);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s')  AND LINEERROR_READTIME>='%s' AND LINEERROR_READTIME<='%s'  AND LINEERROR_KINDS=1",m_Condtion,Str1,Str2,Str1,Str2);
							break;
						}
					case 2:
						{	
							Sqlstr.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME='%s')",m_Condtion,StrTime);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s AND REALTIME_TRANSCRIBETIME='%s') AND LINEERROR_KINDS=1",m_Condtion,StrTime);
    						break;
						}
					}
					
				}
				else
				{	
				
					//פ����
					switch(m_kinds)
					{
					case  0:
						{	//�������������м�¼
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)  AND LINEERROR_KINDS=2",m_Condtion);
    						break;
						}
					case 1:
						{	
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_HALTTIME>='%s' AND GARRISON_HALTTIME<='%s' AND GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",Str1,Str2,m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME>='%s' AND LINEERROR_HALTTIME<='%s' AND LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s) AND LINEERROR_KINDS=2",Str1,Str2,m_Condtion);
							break;
						}
					case 2:
						{	
							Sqlstr.Format("DELETE FROM TB_GARRISON WHERE GARRISON_HALTTIME='%s' AND GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",StrTime,m_Condtion);
							LineErrorStr.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)  AND LINEERROR_KINDS=2",StrTime,m_Condtion);
    						break;
						}
					}

				}
			
				db.ExecuteSQL(Sqlstr);
				//ɾ�����е���·����ģ���¼
				db.ExecuteSQL(LineErrorStr);
				
				db.Close();
				
				//����ˢ���б�
				if(m_TableKinds == 1)
				{
					CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
					pMainFrm->m_wndMyDialogBar.InitializeCombo();
				}

				//��ʾ����
		        DataSort(m_Condtion,m_TimeRange);

			}  

		}

	} 

}

BOOL CShowDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_DATAAPPEAR);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	switch(m_Kinds)
	{
	case 0:
		{
			CWnd* pt = GetDlgItem(IDC_DELETE);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO3);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO4);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO1);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO5);
			pt->EnableWindow(TRUE);

			//����û�ж�������ģ��
			Findnoreadmodule(0);
			break;
		}
	case 1:
		{	
			whichsel  =   0;
			CWnd* pt  = GetDlgItem(IDC_RADIO1);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->EnableWindow(FALSE);
			pt = GetDlgItem(IDC_RADIO5);
			pt->EnableWindow(FALSE);
			//��ʾ����
			DataSort(m_Condtion,m_TimeRange);
			break;
		}

	}
	return TRUE;  
}



void CShowDataDlg::Findnoreadmodule(short kinds)
{	

	CString                str,filename;
   	CString  Sqlstr,DataStr,ModuleFieldName,m_modulestr;
    long      m_Records      =  0,m_ModuleRecords  =  0;
   
	CStringArray  m_NameArrays;
	CDatabase              dbs;
	
	switch(m_TableKinds)
	{
	case  0:
		{
			//��ʾ��ʽ����û��������
			DataStr         = "TB_REALTIME";
			ModuleFieldName = "REALTIME_MODULENO";
			break;
		}
	case 1:
		{
			//��ʾפ������û��������
			DataStr         = "TB_GARRISON";
			ModuleFieldName = "GARRISON_MODULENO";
			break;
		}

	}

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset rs(&dbs);

		switch(m_TableKinds)
		{
		case 0:
			{
				switch(kinds)
				{
				case 0://ȫ��δ��
					{
						//��ʽ����
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							
						}
						else
						{	
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}

						break;
					}
				case 1://����
					{
						
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
						}
						break;
					}
				case 2://��·����
					{

						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
							
						}
						else
						{
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");

							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}
						
						break;
					}

				}
				
				break;
			}
		case 1://פ����
			{
				
				switch(kinds)
				{
				case 0://ȫ��δ��
					{
						
						//פ������
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}
						
						break;
					}
				case 1://����
					{
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_RUNSTATUS=3"); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER WHERE USER_RUNSTATUS=3 AND %s",m_Condtion); 
						}
						
						break;
					}
				case 2://��·����
					{
							
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR) AND %s",m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100) FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR) AND %s",m_Condtion); 
							
						}
						else
						{
							Sqlstr.Format("SELECT COUNT(*)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s') AND %s",m_TimeRange,m_Condtion); 
							m_modulestr.Format("SELECT COUNT(DISTINCT USER_MODULENO/100)  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s') AND %s",m_TimeRange,m_Condtion); 
						}

						break;
					}
					
				}
				
				break;
			}
		}

	    //�õ��û���¼����
	  	rs.Open(CRecordset::forwardOnly,Sqlstr);
		rs.GetFieldValue((short)0,Sqlstr);
		rs.Close();
        m_Records = atoi(Sqlstr);
        
		//�õ�ģ����
	  	rs.Open(CRecordset::forwardOnly,m_modulestr);
		rs.GetFieldValue((short)0,m_modulestr);
		rs.Close();

		m_ModuleRecords = atoi(m_modulestr);
		
		//��ʾû�ж�����������
		switch(m_TableKinds)
		{
		case 0:
			{
				switch(kinds)
				{
				case 0://ȫ��δ��
					{
						//��ʽ����
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s ",ModuleFieldName,DataStr,m_Condtion); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s  WHERE %s) AND %s ",ModuleFieldName,DataStr,m_TimeRange,m_Condtion); 
						}
						break;
					}
				case 1://����
					{

	                    if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
						}
						
						break;
					}
				case 2://��·����
					{

						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=1) AND %s",m_Condtion); 
						}
						else
						{	
							str = m_TimeRange;
							str.Replace("TB_REALTIME", "TB_LINEERROR");
						    str.Replace("REALTIME_TRANSCRIBETIME", "LINEERROR_READTIME");
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE %s AND LINEERROR_KINDS=1) AND %s",str,m_Condtion); 
						}

						break;
					}
				}
				
				break;
				
			}
		case 1:
			{	
				
				switch(kinds)
				{
				case 0://ȫ��δ��
					{
						//פ������
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s) AND %s",ModuleFieldName,DataStr,m_Condtion); 
						}
						else
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬ FROM TB_USER  WHERE USER_MODULENO NOT IN (SELECT %s FROM %s WHERE GARRISON_HALTTIME='%s') AND %s ",ModuleFieldName,DataStr,m_TimeRange,m_Condtion,m_TimeRange); 
						}
						break;
					}	
				case 1://����
					{
                        if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER WHERE USER_RUNSTATUS=3"); 
						}
						else
						{	
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����  FROM TB_USER  WHERE USER_RUNSTATUS=3 AND %s ",m_Condtion); 
						}
						break;
					}
				case 2://��·����ģ��
					{	
						
						if(m_TimeRange == "ALL")
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_KINDS=2) AND %s",m_Condtion); 
						}
						else
						{
							Sqlstr.Format("SELECT USER_COMPANY AS ��˾����,USER_STATIONNO AS ��վ���,USER_STATIONNAME AS ���վ����,USER_MOTHERLINE AS ĸ�߱��,USER_LINENO AS ��·���,USER_LINENAME AS ��·����,USER_TRANSFORMERNO AS ��̨����,USER_MODULENO AS ģ���,USER_PHASE AS ��,USER_NAME AS ����,USER_NO AS �û����,USER_OLDNO AS ԭ�û���,USER_ADDRESS AS סַ,USER_PHONE AS �绰,USER_ELECTRICITYKIND AS �õ�����,USER_AMMETERNO AS �����,USER_AMMETERKIND AS �������,USER_INSTALLTIME AS ��װʱ��,USER_INITIALVALUE  AS ����ֵ,USER_MULTIPLE AS ����,USER_PROTOCOL AS ����Э��,USER_DESCRIBE AS �õ�����,USER_RUNSTATUS AS ����״̬  FROM TB_USER  WHERE USER_MODULENO IN (SELECT LINEERROR_MODULE FROM TB_LINEERROR WHERE LINEERROR_HALTTIME='%s' AND LINEERROR_KINDS=2) AND %s",m_TimeRange,m_Condtion); 
						}

						break;
					}
				}
	
				break;
			}
		}

		
		rs.Open(CRecordset::forwardOnly,Sqlstr);
		
		//�õ��ֶθ���
		short m_fileds = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
	
		for(int i = 0;i < m_fileds; i++)
		{
			//�ֶ���
			rs.GetODBCFieldInfo(i,fieldinfo);
			fieldinfo.m_strName.TrimLeft();
			fieldinfo.m_strName.TrimRight();
			m_NameArrays.Add(fieldinfo.m_strName);
		}
		
		rs.Close();
		dbs.Close();
	}

	m_remotedatactrl.SetDataSourceName(_T("ifrm"));
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
	m_dbgrid.SetEditActive(FALSE);	//�����ݿ�
    m_dbgrid.Scroll(4,0);
	
	switch(m_TableKinds)
	{
	   case 0:
		   {	
			   switch(kinds)
			   {
			   case 0:
				   { 
					   Sqlstr.Format("��ʽ����ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("δ������¼(��Ƿ��ͣ�硢������ģ������ͨѶ����)%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 1:
				   { 
					   Sqlstr.Format("��ʽ����ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("����ģ������δ������¼%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 2:
				   { 
					   Sqlstr.Format("��ʽ����ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("����ģ������ͨѶ����δ������¼%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   }
			  
			   break;
		   }
	   case 1:
		   {
			   
			   switch(kinds)
			   {
			   case 0:
				   {
					   Sqlstr.Format("פ������ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("δ������¼(��Ƿ��ͣ�硢������ģ������ͨѶ����)%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 1:
				   {
					   Sqlstr.Format("פ������ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("����ģ������δ������¼%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   case 2:
				   {
					   Sqlstr.Format("פ������ʱ�䷶Χ[%s]",m_TimeRangeStr);
					   m_modulestr.Format("����ģ������ͨѶ����δ������¼%d����ģ��%d��",m_Records,m_ModuleRecords);
					   break;
				   }
			   }

			   break;
		   } 
	}

	SetWindowText(Sqlstr);
	m_remotedatactrl.SetCaption(m_modulestr);

	
	CWnd* pt = GetDlgItem(ID_SAVEDATA);
	
	//���û������
	if(m_Records <= 0)
	{
		pt->EnableWindow(FALSE);
	}
	else
	{
		pt->EnableWindow(TRUE);
	}	

	pt = GetDlgItem(IDC_DELETE);
	pt->EnableWindow(FALSE);
	
}

BEGIN_EVENTSINK_MAP(CShowDataDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CShowData)
	ON_EVENT(CShowDataDlg, IDC_DBGRIDS, 10 /* HeadClick */, OnHeadClickDbgrids, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CShowDataDlg::OnHeadClickDbgrids(short ColIndex) 
{
	// TODO: Add your control notification handler code here
	whichsel = ColIndex;
	UpdateData(TRUE);
	
	if(m_Kinds > 0)
	{
		//��ʾ����
		DataSort(m_Condtion,m_TimeRange);
	}
	
}

void CShowDataDlg::OnRadio3() 
{
	UpdateData(TRUE);
	
	//��ʾ����
	DataSort(m_Condtion,m_TimeRange);
}

void CShowDataDlg::OnRadio4() 
{
	UpdateData(TRUE);
	
	//��ʾ����
	DataSort(m_Condtion,m_TimeRange);	
}


//��ʾ����������δ������ģ��
void CShowDataDlg::OnRadio1() 
{
	Findnoreadmodule(0);	
}

//��ʾ���������������û�
void CShowDataDlg::OnRadio2() 
{
	Findnoreadmodule(1);
}

//��ʾ���������Ľ��ߴ���ģ��
void CShowDataDlg::OnRadio5() 
{
	Findnoreadmodule(2);

}
