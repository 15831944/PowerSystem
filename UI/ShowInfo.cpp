// ShowInfo.cpp : implementation file
//

#include "stdafx.h"

#include "ShowInfoDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowInfo dialog


CShowInfoDlg::CShowInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowInfo)
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CShowInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowInfo)
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CShowInfo)
	ON_BN_CLICKED(ID_SAVEFILE, OnSavefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowInfo message handlers

//������Ϣ
void CShowInfoDlg::OnSavefile() 
{	

	char szFilter[]="�ı��ļ�(*.TXT)|||";
	CFileDialog dlg(FALSE,"TXT","*.TXT",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	dlg.m_ofn.lpstrTitle = "�����ı��ļ�Ϊ";
		  
	if(dlg.DoModal() == IDOK)
	{	
		m_info.TrimLeft();
        m_info.TrimRight();
	
		//д���ı��ļ�
		FILE *text;
	
		if((text = fopen(dlg.GetPathName(),"wb")) != NULL)
		{
			
			fputs(m_info + "\r\n",text);
			fclose(text);
			MessageBox("�ı��ļ�����ɹ���"," ",MB_OK);
			
		}

	}

}

//�����µ����
void CShowInfoDlg::CheckUseData()
{
	//�����ݿ�
	CDatabase            db;
	CString strSql,strValue,strValue1,strValue2,strValue3,strValue4,strValue5;
	long       fields =   0;
	m_info            =  "";
	int           j   =   0;

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//���ʱ�䲻ͬ�Ļ�
	strValue = pview->GetRefreshTime();
    strValue.TrimLeft();
    strValue.TrimRight();

	if(!strValue.IsEmpty())
	{   
		m_info = m_info + "�������û������ļ�����ʱ�䣺" + strValue + "\r\n";
	
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//��CRecordset����
			CRecordset rs(&db );
		/*	strSql = "SELECT  count(*) FROM TB_USER  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USERBAK)";
			rs.Open(CRecordset::forwardOnly,strSql);
			//�õ���¼����
			rs.GetFieldValue((short)0,strValue);
			//��¼����
			fields = atol(strValue); 
			rs.Close();

			if(fields > 0)
			{
				
				strSql = "SELECT  USER_STATIONNAME,USER_STATIONNO,USER_MODULENO,USER_IDNO FROM TB_USER  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USERBAK) ORDER BY USER_STATIONNO,USER_MODULENO";
				
				m_info = m_info + "������ģ�����±�\r\n";
				
				strValue.Format("%20.20s   %s   %s   %s","���վ��","���վ��","ģ���","ģ��������");;
				m_info = m_info  +  strValue + "\r\n";
				
				rs.Open(CRecordset::forwardOnly,strSql);
				
				//���û���Ϣ
				for( j = 0;j < fields; j++)
				{
					rs.GetFieldValue((short)0,strValue1);
					strValue1.TrimRight();
					rs.GetFieldValue((short)1,strValue2);
					strValue2.TrimRight();
					rs.GetFieldValue((short)2,strValue3);
					strValue3.TrimRight();
					rs.GetFieldValue((short)3,strValue4);
					strValue4.TrimRight();  
					strValue.Format("%20.20s      %5.5s       %8.8s        %4.4s",strValue1,strValue2,strValue3,strValue4);
					m_info = m_info  +  strValue + "\r\n";
					
					//���»�һ����¼
					rs.MoveNext();
				}
				
				//�ر����ݿ�
				rs.Close( );
			}
			
			strSql = "SELECT count(*) FROM TB_USERBAK  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USER)";
			rs.Open(CRecordset::forwardOnly,strSql);
			//�õ���¼����
			rs.GetFieldValue((short)0,strValue);
			//��¼����
			fields = atol(strValue); 
			rs.Close();
			
			if(fields > 0)
			{
				//ɾ����ģ���
				strSql = "SELECT USER_STATIONNAME,USER_STATIONNO,USER_MODULENO,USER_IDNO FROM TB_USERBAK  WHERE USER_AMMETERNO NOT IN (SELECT USER_AMMETERNO FROM TB_USER) ORDER BY USER_STATIONNO,USER_MODULENO";
				
				m_info = m_info + "\r\n\r\nɾ����ģ�����±�\r\n ";
				
				strValue.Format("%20.20s   %s   %s   %s","���վ��","���վ��","ģ���","ģ��������");;
				m_info = m_info  +  strValue + "\r\n";
				
				rs.Open(CRecordset::forwardOnly,strSql);
				
				//���û���Ϣ
				for( j = 0;j < fields; j++)
				{
					rs.GetFieldValue((short)0,strValue1);
					strValue1.TrimRight();
					rs.GetFieldValue((short)1,strValue2);
					strValue2.TrimRight();
					rs.GetFieldValue((short)2,strValue3);
					strValue3.TrimRight();
					rs.GetFieldValue((short)3,strValue4);
					strValue4.TrimRight();  
					strValue.Format("%20.20s      %5.5s       %8.8s        %4.4s",strValue1,strValue2,strValue3,strValue4);
					m_info = m_info  +  strValue + "\r\n";
					
					//���»�һ����¼
					rs.MoveNext();
				}
				
				//�ر����ݿ�
				rs.Close( ); 
			}
            */
	
			strValue = "USER_MODULENO IS NULL OR USER_MODULENO<101 OR USER_MODULENO>13107115 OR USER_MODULENO%100 > 15 OR USER_LINENO IS NULL OR USER_LINENO> 16 OR USER_LINENO<1 OR USER_MOTHERLINE IS NULL OR USER_MOTHERLINE<1 OR USER_MOTHERLINE>4";
			fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",strValue);
			
			if(fields > 0)
			{
				strValue.Format("\r\nģ�����������飺   \r\n     ��%d����¼������Ĳ���������ģ��ɼ�Ҫ��ģ���\r\n��ΧΪ��101��13107115�ݣ�����λӦС��15��ĸ�߱��\r\nӦΪ��1��4�ݣ����߱��ӦΪ��1��16��",fields);
			}
			else
			{	
				strValue.Format("ģ�����������飺   \r\n     ��ʱû���ҵ��д���ļ�¼��");
				m_info = m_info + strValue;
				UpdateData(FALSE);
				return;
			}
			m_info = m_info + strValue;
			
			//�������ϸ��ģ���
			strValue = "USER_MODULENO IS NULL OR USER_MODULENO<101 OR USER_MODULENO>13107115 OR USER_MODULENO%100 > 15 OR USER_LINENO IS NULL OR USER_LINENO> 16 OR USER_LINENO<1 OR USER_MOTHERLINE IS NULL OR USER_MOTHERLINE<1 OR USER_MOTHERLINE>4";
			strSql.Format("SELECT USER_STATIONNAME,USER_STATIONNO,USER_MOTHERLINE,USER_LINENO,USER_MODULENO FROM TB_USER  WHERE  %s",strValue);
			
			m_info = m_info + "\r\n\r\n�������ϸ�ģ�����£�\r\n";
			
			strValue.Format("%20.20s   %s   %s   %s    %s","���վ��","���վ��","ĸ�߱��","���߱��","ģ���");
			m_info = m_info  +  strValue + "\r\n";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//���û���Ϣ
			for( j = 0;j < fields; j++)
			{
				rs.GetFieldValue((short)0,strValue1);
				strValue1.TrimRight();
				rs.GetFieldValue((short)1,strValue2);
				strValue2.TrimRight();
				rs.GetFieldValue((short)2,strValue3);
				strValue3.TrimRight();
				rs.GetFieldValue((short)3,strValue4);
				strValue4.TrimRight();
				rs.GetFieldValue((short)4,strValue5);
				strValue5.TrimRight();  
				strValue.Format("%20.20s      %5.5s       %14.14s        %4.4s   %18.18s",strValue1,strValue2,strValue3,strValue4,strValue5);
				m_info = m_info  +  strValue + "\r\n";
				
				//���»�һ����¼
				rs.MoveNext();
			}
			
			//�ر����ݿ�
			rs.Close( ); 
			
			db.Close( );
		 }
		 
	}

	UpdateData(FALSE);

}

BOOL CShowInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//�������
    CheckUseData();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
