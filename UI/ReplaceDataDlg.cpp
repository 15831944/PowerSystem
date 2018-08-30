// ReplaceData.cpp : implementation file
//

#include "stdafx.h"

#include "ReplaceDataDlg.h"


#include "IFRMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceData dialog


CReplaceDataDlg::CReplaceDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplaceData)
	m_value = _T("");
	m_index = 0;
	//}}AFX_DATA_INIT
}


void CReplaceDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceData)
	DDX_Control(pDX, IDC_COMBOFIELD, m_combofield);
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_CBIndex(pDX, IDC_COMBOFIELD, m_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceDataDlg, CDialog)
	//{{AFX_MSG_MAP(CReplaceData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceData message handlers
void CReplaceDataDlg::initializeFieldInfo(CString DataName)
{
	
	//�����ݿ�
	CDatabase db;
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		CString strSql;
		strSql.Format("SELECT DISTINCT * FROM %s",DataName);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount( );

		CODBCFieldInfo fieldinfo;
		
		m_combofield.ResetContent();
		DataName.TrimLeft();
		DataName.TrimRight();
		
		if(DataName ==  "TB_ELECTRICITY")
		{
            
			//�õ�����͵��
			for(int i = 0; i < 2*nFields;i ++)
			{
			
				if(i%2 != 0)
				{
     		        m_combofield.AddString(pview->TB_ELECTRICITYS[i]);
				}
			
			}
				
		}
		else if(DataName == "TB_TRANSFORMER")
		{

			//��̨��Ϣ���ݱ�
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
     		        m_combofield.AddString(pview->TB_TRANSFORMERS[i]);
				}

			}
			
		}
		else if(DataName == "TB_AMMETER")
		{
		
			//�����Ϣ���ݱ�
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
     		        m_combofield.AddString(pview->TB_AMMETERS[i]);
				}

			}
		
		}
		else if(DataName == "TB_USER")
		{
            
			//�û���Ϣ�����ݱ�
			for(int i = 0; i < 2*nFields; i ++)
			{

				if(i%2 != 0)
				{
     		        m_combofield.AddString(pview->TB_USERS[i]);
				}

			}
			
		}
		else if(DataName == "TB_GARRISON")
		{

			//פ�����ݱ�
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
     		      
					m_combofield.AddString(pview->TB_GARRISONS[i]);

				}

			}
		
		}
		else if(DataName == "TB_REALTIME")
		{
            
			//��ʽ�������ݱ�
			for(int i = 0; i < 2*nFields;i ++)
			{

				if(i%2 != 0)
				{
     		        m_combofield.AddString(pview->TB_REALTIMES[i]);
				}

			}
		
		}
		else
		{
		
			for(int i = 0;i < nFields; i++)
			{
				//�ֶ���
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_combofield.AddString(fieldinfo.m_strName);
			}

		}
		
		rs.Close( );
		db.Close( );
	}

}

BOOL CReplaceDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    initializeFieldInfo(m_dataname);

	//����ȱʡ�İ�ť
	SetDefID(IDCANCEL);
    UpdateData(FALSE);
	return TRUE;  
}

void CReplaceDataDlg::OnOK() 
{
    UpdateData(TRUE);	
	CDialog::OnOK();
}
