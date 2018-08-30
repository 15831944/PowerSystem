// AutoDateReadModule.cpp : implementation file
//

#include "stdafx.h"

#include "AutoDateReadModuleDlg.h"


#include "IFRMView.h"
#include "AMMETERRANGERDlg.h"
#include "DataBaseInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoDateReadModule dialog


CAutoDateReadModuleDlg::CAutoDateReadModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoDateReadModuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoDateReadModule)
	m_str    = _T("");
	m_radio  =      0;
	m_radio1 =      0;
	m_radio2 =      0;
	m_check1 =  FALSE;
	m_check2 =  FALSE;
	m_check3 =  FALSE;
	m_check4 =  FALSE;
	m_check5 =  FALSE;
	m_check6 =  FALSE;
	m_check7 =  FALSE;
	m_check8 =  FALSE;
	m_check9 =  FALSE;
	m_check10 = FALSE;
	//}}AFX_DATA_INIT
}


void CAutoDateReadModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoDateReadModule)
	DDX_Control(pDX, IDC_SPINSCANTIMES, m_SpinScans);
	DDX_Control(pDX, IDC_SPINSCAN, m_SpinScan);
	DDX_Control(pDX, IDC_SPIN, m_spin);
	DDX_Text(pDX, IDC_MESSAGE, m_str);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Radio(pDX, IDC_RADIO22, m_radio1);
	DDX_Radio(pDX, IDC_RADIO28, m_radio2);
	DDX_Check(pDX, IDC_CHECK101, m_check1);
	DDX_Check(pDX, IDC_CHECK102, m_check2);
	DDX_Check(pDX, IDC_CHECK103, m_check3);
	DDX_Check(pDX, IDC_CHECK104, m_check4);
	DDX_Check(pDX, IDC_CHECK105, m_check5);
	DDX_Check(pDX, IDC_CHECK106, m_check6);
	DDX_Check(pDX, IDC_CHECK107, m_check7);
	DDX_Check(pDX, IDC_CHECK108, m_check8);
	DDX_Check(pDX, IDC_CHECK109, m_check9);
	DDX_Check(pDX, IDC_CHECK1, m_check10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAutoDateReadModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoDateReadModule)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_CANCELSET, OnCancelset)
	ON_BN_CLICKED(IDC_ALLSET, OnAllset)
	ON_BN_CLICKED(IDC_ALLCLEAR, OnAllclear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoDateReadModule message handlers

BOOL CAutoDateReadModuleDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_TIMER);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	//פ��ʱ���(0-23��)
	m_spin.SetRange(0,23);
	//ɨ�����(4-7��)
	m_SpinScan.SetRange(4,8);//3

	//8Сʱ�ٶ�(0-10)��
	m_SpinScans.SetRange(0,10);

	//û�м�¼�򷵻�
	if( CDataBaseInstance::GetAllRecordsCount("TB_Auto","ALL") > 0)
	{   
		
		InitializeParameter();//��ʼ������
		
		//פ��ʱ���
		m_spin.SetPos(pview->m_parameter[104]);
		    
		//ɨ�����
		if(pview->m_parameter[106] > 0)
		{
			m_SpinScan.SetPos(pview->m_parameter[106]);
		}
 
	    //�����һ���������ٶ�(0-3��)
	    m_SpinScans.SetPos(pview->m_parameter[108]);

	}
	else
	{
		m_spin.SetPos(0);       //��ʱ0��
		m_SpinScan.SetPos(5);   //ɨ�����5��
		m_SpinScans.SetPos(3);  //�����һ���������ٶ�(0-3��)
	}

	UpdateData(FALSE);
    return TRUE;  
}


BEGIN_EVENTSINK_MAP(CAutoDateReadModuleDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CAutoDateReadModule)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CAutoDateReadModuleDlg::OnOK() 
{

	UpdateData(TRUE);

 	BOOL m_OK        = FALSE;
	CString     str,m_SqlStr,m_ReadStr;
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	int i;

	for(i = 0; i < 93; i ++)
	{

		if(pview->m_parameter[i] > 0)
		{
		
			m_OK = TRUE;
			break;
		
		}

	}
	if(i>=93)
	{
		if(!m_OK)//������ѡ���Ϊ��Ч
		{
            m_check1=FALSE;
			m_radio1=FALSE;
			m_check2=FALSE;
			m_radio2=FALSE;
			m_check3=FALSE;
			m_check4=FALSE;
			m_check5=FALSE;
			m_check6=FALSE;
			m_check7=FALSE;
			m_check8=FALSE;
			m_check9=FALSE;
			m_check10=FALSE;
		}
	
	}



/*	if(!m_OK)
	{
		MessageBox("����ѡ���������û����̨��ȱ�\r\n�Ķ������ڣ�","",MB_OK|MB_ICONWARNING);
		return;
	}
 */  
	m_OK = FALSE;

	if(m_check1 || m_check2 || m_check3 || m_check4 || m_check5 || m_check6 || m_check7 || m_check8 || m_check9)
	{
		m_OK = TRUE;
	}
	
/*	if(!m_OK)
	{
		MessageBox("��ѡ��ģ���Ķ������ݣ�","",MB_OK|MB_ICONWARNING);
		return;
	}
*/
	pview->m_parameter[93]  = m_check1;
	pview->m_parameter[94]  = m_radio1;
	pview->m_parameter[95]  = m_check2;
    pview->m_parameter[96]  = m_radio2;
    pview->m_parameter[97]  = m_check3;
	pview->m_parameter[98]  = m_check4;
	pview->m_parameter[99]  = m_check5;
	pview->m_parameter[100] = m_check6;
	pview->m_parameter[101] = m_check7;
    pview->m_parameter[102] = m_check8;
	pview->m_parameter[103] = m_check9;
    
   //15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
 	for( i = 0; i < 15; i++)
	{
		pview->m_TimeSetLabel[i]  = FALSE;  
	}
	
	//�й����
	if(pview->m_parameter[93] > 0)
	{
		
		if(pview->m_parameter[93] > 0  && pview->m_parameter[94] > 0)
		{
			pview->m_TimeSetLabel[0] = TRUE;
			pview->m_TimeSetLabel[1] = TRUE;    //0���й����-�����ۼ�ֵ
		}
		else
		{
			pview->m_TimeSetLabel[0] = TRUE;
		}

	}	
	
	//�޹����
	if(pview->m_parameter[95] > 0)
	{
		if(pview->m_parameter[95] > 0  && pview->m_parameter[96] > 0)
		{
			pview->m_TimeSetLabel[2] = TRUE;
			pview->m_TimeSetLabel[3] = TRUE;    //0���޹����-�����ۼ�ֵ
		}
		else
		{
			pview->m_TimeSetLabel[2] = TRUE;   
		}
	}	
		
	//4��A����� 5��B����� 6��C�����
	if(pview->m_parameter[97] > 0)
	{
		pview->m_TimeSetLabel[4] = TRUE;
		pview->m_TimeSetLabel[5] = TRUE;
		pview->m_TimeSetLabel[6] = TRUE;
	}

	//7��A���ѹ 8��B���ѹ 9��C���ѹ
	if(pview->m_parameter[98] > 0)
	{
		pview->m_TimeSetLabel[7] = TRUE;
		pview->m_TimeSetLabel[8] = TRUE;
		pview->m_TimeSetLabel[9] = TRUE;
	}

	//������
	if(pview->m_parameter[99] > 0)
	{
		pview->m_TimeSetLabel[10] = TRUE;
	}
	
	//�����
	if(pview->m_parameter[100] > 0)
	{
		pview->m_TimeSetLabel[11] = TRUE;
	}

    //ƽ����
	if(pview->m_parameter[101] > 0)
	{
		pview->m_TimeSetLabel[12] = TRUE;
	}
	
	//�ȵ���
	if(pview->m_parameter[102] > 0)
	{
		pview->m_TimeSetLabel[13] = TRUE;
	}
	
	//��������	
	if(pview->m_parameter[103] > 0)
	{
		pview->m_TimeSetLabel[14] = TRUE;
	}
	
	//פ��ʱ���
	pview->m_parameter[104] = m_spin.GetPos();
	//ɨ��ʱ����
	pview->m_parameter[105] =  30;//m_spinevery.GetPos();
	//ɨ�����
	pview->m_parameter[106] = m_SpinScan.GetPos();
	//�Ժ�ÿ���ʱ��ɨ
    pview->m_parameter[107] = 0;//����m_SpinAgain.GetPos();
	//�ܼ�ɨ������
	pview->m_parameter[108] = m_SpinScans.GetPos();
	//�Զ�����
	pview->m_parameter[109] = m_check10;

	
	if(MessageBox(pview->DecodeParameter(TRUE),"��ʱ�����������������",MB_OKCANCEL) == IDOK)
	{
		//д��פ�������
		pview->WriteToAllAmeterParameter();
		
		//����Զ�Ӧ��
		if(m_check10)
		{
			
			if(pview->IsCurveTableExist("TB_DateAuto"))
			{
				
				if(CDataBaseInstance::GetAllRecordsCount("TB_DateAuto","ALL") > 0)
				{
					
					m_SqlStr.Format("UPDATE TB_DateAuto SET Auto_Parameter67=%d",0);
					CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
					
				}
				
			}
			
			
		}
		if(!m_OK)
			CDialog::OnCancel();
		else
			CDialog::OnOK();
	}

}


//��ʼ������
void CAutoDateReadModuleDlg::InitializeParameter()
{
    CString   strSql,strValue;
	CDatabase              db;	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset   rs(&db );
		strSql = "SELECT * FROM TB_Auto";
		rs.Open(CRecordset::forwardOnly,strSql);	
		
		//���Զ�������Ϣ
		for(int i = 0; i < 110; i++)
		{
			rs.GetFieldValue((short)i,strValue);
		    pview->m_parameter[i] = atoi(strValue);
		}

		//�ر����ݿ�
		rs.Close( );
		db.Close( );

		m_check1 = pview->m_parameter[93];

		if(pview->m_parameter[94] > 0)
		{
			m_radio1 = 1;
		}
		
		m_check2 = pview->m_parameter[95];

		if(pview->m_parameter[96] > 0)
		{
			m_radio2 = 1;
		}

		m_check3  = pview->m_parameter[97];
		m_check4  = pview->m_parameter[98];
		m_check5  = pview->m_parameter[99];
		m_check6  = pview->m_parameter[100];
		m_check7  = pview->m_parameter[101];
		m_check8  = pview->m_parameter[102];
        m_check9  = pview->m_parameter[103];
        m_check10 = pview->m_parameter[109];
		m_str     = pview->DecodeParameter(FALSE);
		m_str.TrimRight();
	}	
		
}


void CAutoDateReadModuleDlg::OnSet() 
{
	UpdateData(TRUE);

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CAMMETERRANGERDlg dlg;

	switch(m_radio)
	{
	case 0:
		{	
			dlg.m_title   = "���񳭱�����";
			break;
		}
	case 1:
		{	
			dlg.m_title   = "���û���������";
			break;
		}
	case 2:
		{
			dlg.m_title   = "��̨�ȱ�������";
			break;
		}
	}

	dlg.m_check1  = pview->m_parameter[m_radio*31 +  0];
	dlg.m_check2  = pview->m_parameter[m_radio*31 +  1];
	dlg.m_check3  = pview->m_parameter[m_radio*31 +  2];
	dlg.m_check4  = pview->m_parameter[m_radio*31 +  3];
	dlg.m_check5  = pview->m_parameter[m_radio*31 +  4];
	dlg.m_check6  = pview->m_parameter[m_radio*31 +  5];
	dlg.m_check7  = pview->m_parameter[m_radio*31 +  6];
	dlg.m_check8  = pview->m_parameter[m_radio*31 +  7];
	dlg.m_check9  = pview->m_parameter[m_radio*31 +  8];
	dlg.m_check10 = pview->m_parameter[m_radio*31 +  9];
	dlg.m_check11 = pview->m_parameter[m_radio*31 + 10];
	dlg.m_check12 = pview->m_parameter[m_radio*31 + 11];
	dlg.m_check13 = pview->m_parameter[m_radio*31 + 12];
	dlg.m_check14 = pview->m_parameter[m_radio*31 + 13];
	dlg.m_check15 = pview->m_parameter[m_radio*31 + 14];
	dlg.m_check16 = pview->m_parameter[m_radio*31 + 15];
	dlg.m_check17 = pview->m_parameter[m_radio*31 + 16];
	dlg.m_check18 = pview->m_parameter[m_radio*31 + 17];
	dlg.m_check19 = pview->m_parameter[m_radio*31 + 18];
	dlg.m_check20 = pview->m_parameter[m_radio*31 + 19];
	dlg.m_check21 = pview->m_parameter[m_radio*31 + 20];
	dlg.m_check22 = pview->m_parameter[m_radio*31 + 21];
	dlg.m_check23 = pview->m_parameter[m_radio*31 + 22];
	dlg.m_check24 = pview->m_parameter[m_radio*31 + 23];
	dlg.m_check25 = pview->m_parameter[m_radio*31 + 24];
	dlg.m_check26 = pview->m_parameter[m_radio*31 + 25];
	dlg.m_check27 = pview->m_parameter[m_radio*31 + 26];
	dlg.m_check28 = pview->m_parameter[m_radio*31 + 27];
	dlg.m_check29 = pview->m_parameter[m_radio*31 + 28];
	dlg.m_check30 = pview->m_parameter[m_radio*31 + 29];
	dlg.m_check31 = pview->m_parameter[m_radio*31 + 30];
	
	if(dlg.DoModal() == IDOK)
	{
		pview->m_parameter[m_radio*31 +  0] = dlg.m_check1;
		pview->m_parameter[m_radio*31 +  1] = dlg.m_check2;
	    pview->m_parameter[m_radio*31 +  2] = dlg.m_check3;
		pview->m_parameter[m_radio*31 +  3] = dlg.m_check4;
		pview->m_parameter[m_radio*31 +  4] = dlg.m_check5;
		pview->m_parameter[m_radio*31 +  5] = dlg.m_check6;
		pview->m_parameter[m_radio*31 +  6] = dlg.m_check7;
		pview->m_parameter[m_radio*31 +  7] = dlg.m_check8;
	    pview->m_parameter[m_radio*31 +  8] = dlg.m_check9;
		pview->m_parameter[m_radio*31 +  9] = dlg.m_check10;
		pview->m_parameter[m_radio*31 + 10] = dlg.m_check11;
		pview->m_parameter[m_radio*31 + 11] = dlg.m_check12;
		pview->m_parameter[m_radio*31 + 12] = dlg.m_check13;
		pview->m_parameter[m_radio*31 + 13] = dlg.m_check14;
	    pview->m_parameter[m_radio*31 + 14] = dlg.m_check15;
		pview->m_parameter[m_radio*31 + 15] = dlg.m_check16;
		pview->m_parameter[m_radio*31 + 16] = dlg.m_check17;
		pview->m_parameter[m_radio*31 + 17] = dlg.m_check18;
		pview->m_parameter[m_radio*31 + 18] = dlg.m_check19;
		pview->m_parameter[m_radio*31 + 19] = dlg.m_check20;
	    pview->m_parameter[m_radio*31 + 20] = dlg.m_check21;
		pview->m_parameter[m_radio*31 + 21] = dlg.m_check22;
		pview->m_parameter[m_radio*31 + 22] = dlg.m_check23;
		pview->m_parameter[m_radio*31 + 23] = dlg.m_check24;
		pview->m_parameter[m_radio*31 + 24] = dlg.m_check25;
		pview->m_parameter[m_radio*31 + 25] = dlg.m_check26;
		pview->m_parameter[m_radio*31 + 26] = dlg.m_check27;
		pview->m_parameter[m_radio*31 + 27] = dlg.m_check28;
		pview->m_parameter[m_radio*31 + 28] = dlg.m_check29;
		pview->m_parameter[m_radio*31 + 29] = dlg.m_check30;
		pview->m_parameter[m_radio*31 + 30] = dlg.m_check31;
		
		//���Ͳ���������
		m_str    =  pview->DecodeParameter(FALSE);
		m_str.TrimRight();

		UpdateData(FALSE);
	}

}


void CAutoDateReadModuleDlg::OnCancelset() 
{
	UpdateData(TRUE);

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString    str,mstr;
	
	switch(m_radio)
	{
	case 0:
		{
			str   =  "ȡ������������������";
			mstr  =  "���������������ѱ�ȡ����";
			break;
		}
	case 1:
		{
			str   =  "ȡ�����û��������������";
			mstr  =  "���û�������������ѱ�ȡ����";
			break;
		}
	case 2:
		{
			str   = "ȡ��̨��ȱ������������";	
			mstr  =  "̨��ȱ�����������ѱ�ȡ����";
			break;
		}
	}


	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
        for(int i = 0; i < 31; i ++)
		{
			pview->m_parameter[m_radio*31 + i] = 0;	
		}
				
		//���Ͳ���������
		m_str    =  pview->DecodeParameter(FALSE);
		m_str.TrimRight();

		UpdateData(FALSE);
		
		MessageBox(mstr," ",MB_OK|MB_ICONWARNING);
	}

}

void CAutoDateReadModuleDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CAutoDateReadModuleDlg::OnAllset() 
{
	UpdateData(TRUE);

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CAMMETERRANGERDlg dlg;

	//m_check1
	if(pview->m_parameter[0 * 31 +  0] > 0 || pview->m_parameter[1 * 31 +  0] > 0 || pview->m_parameter[2 * 31 +  0] > 0)
	{
		dlg.m_check1  = TRUE;
	}
	else
	{
		dlg.m_check1  = FALSE;
	}

	//m_check2
	if(pview->m_parameter[0 * 31 +  1] > 0 || pview->m_parameter[1 * 31 +  1] > 0 || pview->m_parameter[2 * 31 +  1] > 0)
	{
		dlg.m_check2  = TRUE;
	}
	else
	{
		dlg.m_check2  = FALSE;
	}

	//m_check3
	if(pview->m_parameter[0 * 31 +  2] > 0 || pview->m_parameter[1 * 31 +  2] > 0 || pview->m_parameter[2 * 31 +  2] > 0)
	{
		dlg.m_check3  = TRUE;
	}
	else
	{
		dlg.m_check3  = FALSE;
	}

    //m_check4
	if(pview->m_parameter[0 * 31 +  3] > 0 || pview->m_parameter[1 * 31 +  3] > 0 || pview->m_parameter[2 * 31 +  3] > 0)
	{
		dlg.m_check4  = TRUE;
	}
	else
	{
		dlg.m_check4  = FALSE;
	} 
	
	//m_check5
	if(pview->m_parameter[0 * 31 +  4] > 0 || pview->m_parameter[1 * 31 +  4] > 0 || pview->m_parameter[2 * 31 +  4] > 0)
	{
		dlg.m_check5  = TRUE;
	}
	else
	{
		dlg.m_check5  = FALSE;
	}

	//m_check6
	if(pview->m_parameter[0 * 31 +  5] > 0 || pview->m_parameter[1 * 31 +  5] > 0 || pview->m_parameter[2 * 31 +  5] > 0)
	{
		dlg.m_check6  = TRUE;
	}
	else
	{
		dlg.m_check6  = FALSE;
	}

	//m_check7
	if(pview->m_parameter[0 * 31 +  6] > 0 || pview->m_parameter[1 * 31 +  6] > 0 || pview->m_parameter[2 * 31 +  6] > 0)
	{
		dlg.m_check7  = TRUE;
	}
	else
	{
		dlg.m_check7  = FALSE;
	}

	//m_check8
	if(pview->m_parameter[0 * 31 +  7] > 0 || pview->m_parameter[1 * 31 +  7] > 0 || pview->m_parameter[2 * 31 +  7] > 0)
	{
		dlg.m_check8  = TRUE;
	}
	else
	{
		dlg.m_check8  = FALSE;
	}

    //m_check9
	if(pview->m_parameter[0 * 31 +  8] > 0 || pview->m_parameter[1 * 31 +  8] > 0 || pview->m_parameter[2 * 31 +  8] > 0)
	{
		dlg.m_check9  = TRUE;
	}
	else
	{
		dlg.m_check9  = FALSE;
	} 
	
	//m_check10
	if(pview->m_parameter[0 * 31 +  9] > 0 || pview->m_parameter[1 * 31 +  9] > 0 || pview->m_parameter[2 * 31 +  9] > 0)
	{
		dlg.m_check10  = TRUE;
	}
	else
	{
		dlg.m_check10  = FALSE;
	}
	
	//m_check11
	if(pview->m_parameter[0 * 31 +  10] > 0 || pview->m_parameter[1 * 31 +  10] > 0 || pview->m_parameter[2 * 31 +  10] > 0)
	{
		dlg.m_check11  = TRUE;
	}
	else
	{
		dlg.m_check11  = FALSE;
	}

	//m_check12
	if(pview->m_parameter[0 * 31 +  11] > 0 || pview->m_parameter[1 * 31 +  11] > 0 || pview->m_parameter[2 * 31 +  11] > 0)
	{
		dlg.m_check12  = TRUE;
	}
	else
	{
		dlg.m_check12  = FALSE;
	}

	//m_check13
	if(pview->m_parameter[0 * 31 +  12] > 0 || pview->m_parameter[1 * 31 +  12] > 0 || pview->m_parameter[2 * 31 +  12] > 0)
	{
		dlg.m_check13  = TRUE;
	}
	else
	{
		dlg.m_check13  = FALSE;
	}

    //m_check14
	if(pview->m_parameter[0 * 31 +  13] > 0 || pview->m_parameter[1 * 31 +  13] > 0 || pview->m_parameter[2 * 31 +  13] > 0)
	{
		dlg.m_check14  = TRUE;
	}
	else
	{
		dlg.m_check14  = FALSE;
	} 
	
	//m_check15
	if(pview->m_parameter[0 * 31 +  14] > 0 || pview->m_parameter[1 * 31 +  14] > 0 || pview->m_parameter[2 * 31 +  14] > 0)
	{
		dlg.m_check15  = TRUE;
	}
	else
	{
		dlg.m_check15  = FALSE;
	}

	//m_check16
	if(pview->m_parameter[0 * 31 +  15] > 0 || pview->m_parameter[1 * 31 +  15] > 0 || pview->m_parameter[2 * 31 +  15] > 0)
	{
		dlg.m_check16  = TRUE;
	}
	else
	{
		dlg.m_check16  = FALSE;
	}

	//m_check17
	if(pview->m_parameter[0 * 31 +  16] > 0 || pview->m_parameter[1 * 31 +  16] > 0 || pview->m_parameter[2 * 31 +  16] > 0)
	{
		dlg.m_check17  = TRUE;
	}
	else
	{
		dlg.m_check17  = FALSE;
	}

	//m_check18
	if(pview->m_parameter[0 * 31 +  17] > 0 || pview->m_parameter[1 * 31 +  17] > 0 || pview->m_parameter[2 * 31 +  17] > 0)
	{
		dlg.m_check18  = TRUE;
	}
	else
	{
		dlg.m_check18  = FALSE;
	}

    //m_check19
	if(pview->m_parameter[0 * 31 +  18] > 0 || pview->m_parameter[1 * 31 +  18] > 0 || pview->m_parameter[2 * 31 +  18] > 0)
	{
		dlg.m_check19  = TRUE;
	}
	else
	{
		dlg.m_check19  = FALSE;
	} 
	
	//m_check20
	if(pview->m_parameter[0 * 31 +  19] > 0 || pview->m_parameter[1 * 31 +  19] > 0 || pview->m_parameter[2 * 31 +  19] > 0)
	{
		dlg.m_check20  = TRUE;
	}
	else
	{
		dlg.m_check20  = FALSE;
	}

	//m_check21
	if(pview->m_parameter[0 * 31 +  20] > 0 || pview->m_parameter[1 * 31 +  20] > 0 || pview->m_parameter[2 * 31 +  20] > 0)
	{
		dlg.m_check21  = TRUE;
	}
	else
	{
		dlg.m_check21  = FALSE;
	}

	//m_check22
	if(pview->m_parameter[0 * 31 +  21] > 0 || pview->m_parameter[1 * 31 +  21] > 0 || pview->m_parameter[2 * 31 +  21] > 0)
	{
		dlg.m_check22  = TRUE;
	}
	else
	{
		dlg.m_check22  = FALSE;
	}

	//m_check23
	if(pview->m_parameter[0 * 31 +  22] > 0 || pview->m_parameter[1 * 31 +  22] > 0 || pview->m_parameter[2 * 31 +  22] > 0)
	{
		dlg.m_check23  = TRUE;
	}
	else
	{
		dlg.m_check23  = FALSE;
	}

    //m_check24
	if(pview->m_parameter[0 * 31 +  23] > 0 || pview->m_parameter[1 * 31 +  23] > 0 || pview->m_parameter[2 * 31 +  23] > 0)
	{
		dlg.m_check24  = TRUE;
	}
	else
	{
		dlg.m_check24  = FALSE;
	} 
	
	//m_check25
	if(pview->m_parameter[0 * 31 +  24] > 0 || pview->m_parameter[1 * 31 +  24] > 0 || pview->m_parameter[2 * 31 +  24] > 0)
	{
		dlg.m_check25  = TRUE;
	}
	else
	{
		dlg.m_check25  = FALSE;
	}

	//m_check26
	if(pview->m_parameter[0 * 31 +  25] > 0 || pview->m_parameter[1 * 31 +  25] > 0 || pview->m_parameter[2 * 31 +  25] > 0)
	{
		dlg.m_check26  = TRUE;
	}
	else
	{
		dlg.m_check26  = FALSE;
	}

	//m_check27
	if(pview->m_parameter[0 * 31 +  26] > 0 || pview->m_parameter[1 * 31 +  26] > 0 || pview->m_parameter[2 * 31 +  26] > 0)
	{
		dlg.m_check27  = TRUE;
	}
	else
	{
		dlg.m_check27  = FALSE;
	}

	//m_check28
	if(pview->m_parameter[0 * 31 +  27] > 0 || pview->m_parameter[1 * 31 +  27] > 0 || pview->m_parameter[2 * 31 +  27] > 0)
	{
		dlg.m_check28  = TRUE;
	}
	else
	{
		dlg.m_check28  = FALSE;
	}

    //m_check29
	if(pview->m_parameter[0 * 31 +  28] > 0 || pview->m_parameter[1 * 31 +  28] > 0 || pview->m_parameter[2 * 31 +  28] > 0)
	{
		dlg.m_check29  = TRUE;
	}
	else
	{
		dlg.m_check29  = FALSE;
	} 
	
	//m_check30
	if(pview->m_parameter[0 * 31 +  29] > 0 || pview->m_parameter[1 * 31 +  29] > 0 || pview->m_parameter[2 * 31 +  29] > 0)
	{
		dlg.m_check30  = TRUE;
	}
	else
	{
		dlg.m_check30  = FALSE;
	}
	
	//m_check31
	if(pview->m_parameter[0 * 31 +  30] > 0 || pview->m_parameter[1 * 31 +  30] > 0 || pview->m_parameter[2 * 31 +  30] > 0)
	{
		dlg.m_check31  = TRUE;
	}
	else
	{
		dlg.m_check31  = FALSE;
	}


	dlg.m_title   = "���񡢴��û�����̨�����б�������";


	if(dlg.DoModal() == IDOK)
	{
		int i=0;
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  0] = dlg.m_check1;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  1] = dlg.m_check2;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  2] = dlg.m_check3;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  3] = dlg.m_check4;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  4] = dlg.m_check5;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  5] = dlg.m_check6;
		}

	    for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  6] = dlg.m_check7;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  7] = dlg.m_check8;
		}

		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  8] = dlg.m_check9;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  9] = dlg.m_check10;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  10] = dlg.m_check11;
		}

		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  11] = dlg.m_check12;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  12] = dlg.m_check13;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  13] = dlg.m_check14;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  14] = dlg.m_check15;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  15] = dlg.m_check16;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  16] = dlg.m_check17;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  17] = dlg.m_check18;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  18] = dlg.m_check19;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  19] = dlg.m_check20;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  20] = dlg.m_check21;
		}

		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  21] = dlg.m_check22;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  22] = dlg.m_check23;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  23] = dlg.m_check24;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  24] = dlg.m_check25;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  25] = dlg.m_check26;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  26] = dlg.m_check27;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  27] = dlg.m_check28;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  28] = dlg.m_check29;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  29] = dlg.m_check30;
		}
		
		for( i = 0;i < 3; i ++)
		{
			pview->m_parameter[i*31 +  30] = dlg.m_check31;
		}
	
	    //��������
        m_str = pview->DecodeParameter(FALSE);
		
		UpdateData(FALSE);
	}
	
}

void CAutoDateReadModuleDlg::OnAllclear() 
{
	UpdateData(TRUE);

	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString    str,mstr;
	str   =  "ȡ����������û���̨����·��վ�������������";
	mstr  =  "��������û���̨����·��վ������������ѱ�ȡ����";
	
	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		for(int j = 0; j < 3; j ++)
		{
			for(int i = 0; i < 31; i ++)
			{
				pview->m_parameter[j*31 + i] = 0;	
			}
		}
		
	    m_String[0] = "���� �� �� \r\n  �������ڣ�<��> \r\n";
		m_String[1] = "�����û��� \r\n  �������ڣ�<��> \r\n";
	    m_String[2] = "��̨��ȱ� \r\n  �������ڣ�<��> \r\n";
	
	    m_str = m_String[0] + m_String[1] + m_String[2];
		m_str.TrimRight();

		UpdateData(FALSE);
		MessageBox(mstr," ",MB_OK|MB_ICONWARNING);

        //���ζ������ݵ�����
		CWnd* pt = GetDlgItem(IDC_CHECK101);
         pt->EnableWindow(FALSE);
         pt = GetDlgItem(IDC_CHECK102);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK103);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK104);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK105);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK106);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK107);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK108);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_CHECK109);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_RADIO22);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_RADIO23);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_RADIO28);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_RADIO29);
         pt->EnableWindow(FALSE);
         pt = GetDlgItem(IDC_CHECK1);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_EDIT35);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_EDIT37);
         pt->EnableWindow(FALSE);
		 pt = GetDlgItem(IDC_EDIT1);
         pt->EnableWindow(FALSE);
         UpdateData(TRUE);
	}
	
}

