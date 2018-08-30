// ZHULIUTIMESELECT.cpp : implementation file
//

#include "stdafx.h"



#include "IFRMView.h"
#include "DataBaseInstance.h"
#include "ZHULIUTIMESELECTDlg.h"
#include "READRANGLE.h"
#include "FENGBEISETDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZHULIUTIMESELECT dialog


CZHULIUTIMESELECTDlg::CZHULIUTIMESELECTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZHULIUTIMESELECTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZHULIUTIMESELECT)
	m_check1  = FALSE;
	m_check2  = FALSE;
	m_check3  = FALSE;
	m_check4  = FALSE;
	m_check5  = FALSE;
	m_check6  = FALSE;
	m_check7  = FALSE;
	m_check8  = FALSE;
	m_check9  = FALSE;
	m_check10 = FALSE;
	m_check11 = FALSE;
	m_check12 = FALSE;
	m_check13 = FALSE;
	m_check14 = FALSE;
	m_check15 = FALSE;
	m_check16 = FALSE;
	m_check17 = FALSE;
	m_check18 = FALSE;
	m_check19 = FALSE;
	m_check20 = FALSE;
	m_check21 = FALSE;
	m_check22 = FALSE;
	m_check23 = FALSE;
	m_check24 = FALSE;
	m_check25 = FALSE;
	m_check26 = FALSE;
	m_check27 = FALSE;
	m_check28 = FALSE;
	m_check29 = FALSE;
	m_check30 = FALSE;
	m_check31 = FALSE;
	m_autorun = FALSE;
	//}}AFX_DATA_INIT
}


void CZHULIUTIMESELECTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZHULIUTIMESELECT)
	DDX_Control(pDX, IDC_SPINSCANTIMES, m_SpinScans);
	DDX_Control(pDX, IDC_SPINSCAN, m_SpinScan);
	DDX_Check(pDX, IDC_CHECK101, m_check1);
	DDX_Check(pDX, IDC_CHECK102, m_check2);
	DDX_Check(pDX, IDC_CHECK103, m_check3);
	DDX_Check(pDX, IDC_CHECK104, m_check4);
	DDX_Check(pDX, IDC_CHECK105, m_check5);
	DDX_Check(pDX, IDC_CHECK106, m_check6);
	DDX_Check(pDX, IDC_CHECK107, m_check7);
	DDX_Check(pDX, IDC_CHECK108, m_check8);
	DDX_Check(pDX, IDC_CHECK109, m_check9);
	DDX_Check(pDX, IDC_CHECK110, m_check10);
	DDX_Check(pDX, IDC_CHECK111, m_check11);
	DDX_Check(pDX, IDC_CHECK112, m_check12);
	DDX_Check(pDX, IDC_CHECK113, m_check13);
	DDX_Check(pDX, IDC_CHECK114, m_check14);
	DDX_Check(pDX, IDC_CHECK115, m_check15);
	DDX_Check(pDX, IDC_CHECK116, m_check16);
	DDX_Check(pDX, IDC_CHECK117, m_check17);
	DDX_Check(pDX, IDC_CHECK118, m_check18);
	DDX_Check(pDX, IDC_CHECK119, m_check19);
	DDX_Check(pDX, IDC_CHECK120, m_check20);
	DDX_Check(pDX, IDC_CHECK121, m_check21);
	DDX_Check(pDX, IDC_CHECK122, m_check22);
	DDX_Check(pDX, IDC_CHECK123, m_check23);
	DDX_Check(pDX, IDC_CHECK124, m_check24);
	DDX_Check(pDX, IDC_CHECK125, m_check25);
	DDX_Check(pDX, IDC_CHECK126, m_check26);
	DDX_Check(pDX, IDC_CHECK127, m_check27);
	DDX_Check(pDX, IDC_CHECK128, m_check28);
	DDX_Check(pDX, IDC_CHECK129, m_check29);
	DDX_Check(pDX, IDC_CHECK130, m_check30);
	DDX_Check(pDX, IDC_CHECK131, m_check31);
	DDX_Check(pDX, IDC_CHECK1, m_autorun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZHULIUTIMESELECTDlg, CDialog)
	//{{AFX_MSG_MAP(CZHULIUTIMESELECT)
	ON_BN_CLICKED(ID_ALLABANDON, OnAllabandon)
	ON_BN_CLICKED(ID_ALLSELECT, OnAllselect)
	ON_BN_CLICKED(IDC_TOTALSET, OnTotalset)
	ON_BN_CLICKED(IDC_FENGSET, OnFengset)
	ON_BN_CLICKED(IDC_CHECK101, OnCheck101)
	ON_BN_CLICKED(IDC_CHECK102, OnCheck102)
	ON_BN_CLICKED(IDC_CHECK103, OnCheck103)
	ON_BN_CLICKED(IDC_CHECK104, OnCheck104)
	ON_BN_CLICKED(IDC_CHECK105, OnCheck105)
	ON_BN_CLICKED(IDC_CHECK106, OnCheck106)
	ON_BN_CLICKED(IDC_CHECK107, OnCheck107)
	ON_BN_CLICKED(IDC_CHECK108, OnCheck108)
	ON_BN_CLICKED(IDC_CHECK109, OnCheck109)
	ON_BN_CLICKED(IDC_CHECK110, OnCheck110)
	ON_BN_CLICKED(IDC_CHECK111, OnCheck111)
	ON_BN_CLICKED(IDC_CHECK112, OnCheck112)
	ON_BN_CLICKED(IDC_CHECK113, OnCheck113)
	ON_BN_CLICKED(IDC_CHECK114, OnCheck114)
	ON_BN_CLICKED(IDC_CHECK115, OnCheck115)
	ON_BN_CLICKED(IDC_CHECK116, OnCheck116)
	ON_BN_CLICKED(IDC_CHECK117, OnCheck117)
	ON_BN_CLICKED(IDC_CHECK118, OnCheck118)
	ON_BN_CLICKED(IDC_CHECK119, OnCheck119)
	ON_BN_CLICKED(IDC_CHECK120, OnCheck120)
	ON_BN_CLICKED(IDC_CHECK121, OnCheck121)
	ON_BN_CLICKED(IDC_CHECK122, OnCheck122)
	ON_BN_CLICKED(IDC_CHECK123, OnCheck123)
	ON_BN_CLICKED(IDC_CHECK124, OnCheck124)
	ON_BN_CLICKED(IDC_CHECK125, OnCheck125)
	ON_BN_CLICKED(IDC_CHECK126, OnCheck126)
	ON_BN_CLICKED(IDC_CHECK127, OnCheck127)
	ON_BN_CLICKED(IDC_CHECK128, OnCheck128)
	ON_BN_CLICKED(IDC_CHECK129, OnCheck129)
	ON_BN_CLICKED(IDC_CHECK130, OnCheck130)
	ON_BN_CLICKED(IDC_CHECK131, OnCheck131)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZHULIUTIMESELECT message handlers

void CZHULIUTIMESELECTDlg::OnAllabandon() 
{
	m_check1  = FALSE;
	m_check2  = FALSE;
	m_check3  = FALSE;
	m_check4  = FALSE;
	m_check5  = FALSE;
	m_check6  = FALSE;
	m_check7  = FALSE;
	m_check8  = FALSE;
	m_check9  = FALSE;
	m_check10 = FALSE;
	m_check11 = FALSE;
	m_check12 = FALSE;
	m_check13 = FALSE;
	m_check14 = FALSE;
	m_check15 = FALSE;
	m_check16 = FALSE;
	m_check17 = FALSE;
	m_check18 = FALSE;
	m_check19 = FALSE;
	m_check20 = FALSE;
	m_check21 = FALSE;
	m_check22 = FALSE;
	m_check23 = FALSE;
	m_check24 = FALSE;
	m_check25 = FALSE;
	m_check26 = FALSE;
	m_check27 = FALSE;
	m_check28 = FALSE;
	m_check29 = FALSE;
	m_check30 = FALSE;
	m_check31 = FALSE;
	UpdateData(FALSE);
	CheckStatus(); 
}

void CZHULIUTIMESELECTDlg::OnAllselect() 
{
	m_check1  = TRUE;
	m_check2  = TRUE;
	m_check3  = TRUE;
	m_check4  = TRUE;
	m_check5  = TRUE;
	m_check6  = TRUE;
	m_check7  = TRUE;
	m_check8  = TRUE;
	m_check9  = TRUE;
	m_check10 = TRUE;
	m_check11 = TRUE;
	m_check12 = TRUE;
	m_check13 = TRUE;
	m_check14 = TRUE;
	m_check15 = TRUE;
	m_check16 = TRUE;
	m_check17 = TRUE;
	m_check18 = TRUE;
	m_check19 = TRUE;
	m_check20 = TRUE;
	m_check21 = TRUE;
	m_check22 = TRUE;
	m_check23 = TRUE;
	m_check24 = TRUE;
	m_check25 = TRUE;
	m_check26 = TRUE;
	m_check27 = TRUE;
	m_check28 = TRUE;
	m_check29 = TRUE;
	m_check30 = TRUE;
	m_check31 = TRUE;
	UpdateData(FALSE);	
	CheckStatus(); 
}

BOOL CZHULIUTIMESELECTDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_TIMER);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	
	//ɨ�����(3-7��)
	m_SpinScan.SetRange(3,7);

	//�Ժ�ɨ�����(0-10��)
	m_SpinScans.SetRange(0,10);

	//û�м�¼�򷵻�
	if( CDataBaseInstance::GetAllRecordsCount("TB_DateAuto","ALL") > 0)
	{   
		
		InitializeParameter();//��ʼ������
		
		if(pview->m_DateReadParameter[0] > 0)
		{
			m_check1 =   TRUE;
		}
		
    	if(pview->m_DateReadParameter[2] > 0)
		{
			m_check2 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[4] > 0)
		{
			m_check3 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[6] > 0)
		{
			m_check4 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[8] > 0)
		{
			m_check5 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[10] > 0)
		{
			m_check6 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[12] > 0)
		{
			m_check7 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[14] > 0)
		{
			m_check8 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[16] > 0)
		{
			m_check9 =   TRUE;
		}
		
		if(pview->m_DateReadParameter[18] > 0)
		{
			m_check10 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[20] > 0)
		{
			m_check11 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[22] > 0)
		{
			m_check12 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[24] > 0)
		{
			m_check13 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[26] > 0)
		{
			m_check14 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[28] > 0)
		{
			m_check15 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[30] > 0)
		{
			m_check16 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[32] > 0)
		{
			m_check17 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[34] > 0)
		{
			m_check18 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[36] > 0)
		{
			m_check19 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[38] > 0)
		{
			m_check20 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[40] > 0)
		{
			m_check21 =   TRUE;
		}	
		
		
		if(pview->m_DateReadParameter[42] > 0)
		{
			m_check22 =   TRUE;
		}
		
		if(pview->m_DateReadParameter[44] > 0)
		{
			m_check23 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[46] > 0)
		{
			m_check24 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[48] > 0)
		{
			m_check25 =   TRUE;
		}
		
		
		if(pview->m_DateReadParameter[50] > 0)
		{
			m_check26 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[52] > 0)
		{
			m_check27 =   TRUE;
		}
		
	    if(pview->m_DateReadParameter[54] > 0)
		{
			m_check28 =   TRUE;
		}
		
		if(pview->m_DateReadParameter[56] > 0)
		{
			m_check29 =   TRUE;
		}
		
		if(pview->m_DateReadParameter[58] > 0)
		{
			m_check30 =   TRUE;
		}
		
		if(pview->m_DateReadParameter[60] > 0)
		{
			m_check31 =   TRUE;
		}

		//ɨ�����(3-7��)
		m_SpinScan.SetPos(pview->m_DateReadParameter[63]);
		//�Ժ���ɨ�����(0-10��)
		m_SpinScans.SetPos(pview->m_DateReadParameter[65]);
		//�Ƿ�һ�������Զ�פ��
		m_autorun = pview->m_DateReadParameter[66];
	}
	else
	{
		m_SpinScan.SetPos(5);   //ɨ�����5��
		m_SpinScans.SetPos(3);  //�Ժ�ɨ�����
	}


	UpdateData(FALSE);

    //���״̬
	CheckStatus();
	CenterWindow();
  	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//��ʼ������
void CZHULIUTIMESELECTDlg::InitializeParameter()
{
	CString               str;
	CDatabase              db;	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset   rs(&db );
		str = "SELECT * FROM TB_DateAuto";
		rs.Open(CRecordset::dynaset,str);
		
		if(rs.IsEOF())
		{
			//�ر����ݿ�
		    rs.Close( );
		    db.Close( );
			return;
		}
		
		//���Զ�������Ϣ
		for(int i = 0; i < 67; i++)
		{
			rs.GetFieldValue((short)i,str);
			pview->m_DateReadParameter[i] = atoi(str);
		}

		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}

}

void CZHULIUTIMESELECTDlg::OnTotalset() 
{	
	UpdateData(TRUE);

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString  str,strsql,strtemp,strs,strm;
 

	CREADRANGLEDlg          dlg;
	dlg.m_days   =         0;

	m_Result[0 ] = m_check1;
	m_Result[1 ] = m_check2;
	m_Result[2 ] = m_check3;
	m_Result[3 ] = m_check4;
	m_Result[4 ] = m_check5;
	m_Result[5 ] = m_check6;
	m_Result[6 ] = m_check7;
	m_Result[7 ] = m_check8;
	m_Result[8 ] = m_check9;
	m_Result[9 ] = m_check10;
	m_Result[10] = m_check11;
	m_Result[11] = m_check12;
	m_Result[12] = m_check13;
	m_Result[13] = m_check14;
	m_Result[14] = m_check15;
	m_Result[15] = m_check16;
	m_Result[16] = m_check17;
	m_Result[17] = m_check18;
	m_Result[18] = m_check19;
	m_Result[19] = m_check20;
	m_Result[20] = m_check21;
	m_Result[21] = m_check22;
	m_Result[22] = m_check23;
	m_Result[23] = m_check24;
	m_Result[24] = m_check25;
	m_Result[25] = m_check26;
	m_Result[26] = m_check27;
	m_Result[27] = m_check28;
	m_Result[28] = m_check29;
	m_Result[29] = m_check30;
	m_Result[30] = m_check31;

	int i=0,tmpselectmark=0;//�ж��Ƿ��������ھ�δѡ���־

    for(i=0;i<31;i++)//�Ƿ�ѡ��������
		if(m_Result[i]!=0)
		{
			tmpselectmark=1;//ѡ����פ������
			break;
		}
	if(tmpselectmark)//פ�����ڴ���,�����·�פ��
	{
		CREADRANGLEDlg          dlg;
		dlg.m_days   =         0;

	if(dlg.DoModal()==IDOK)
	{
		
		str  =  "";
		
		for(i = 0; i < 93; i ++)
		{
			str = str + "0";
		}
		
		strsql.Format("UPDATE TB_USER SET USER_ZHULABEL='%s'",str);
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);

		str    =    "";
	    strs   =    "";

		//���б�
		for( i = 0; i < 31; i ++)
		{
			
			if(m_Result[i])
			{
				//��������ж���
				strtemp.Format("%s",dlg.m_ReadRangeStr);

				if(strs.IsEmpty())
				{
					strm.Format("%2d",i + 1);
				}
				else
				{
					strm.Format("��%2d",i + 1);
				}
				
				strs = strs + strm;

			}
			else
			{
				//�������˱�־,3����־ ���������ѹռ��һλ,�����Ʊ�ʾ ÿ������11λ,ʮ���ƴ�0~FFF֮��
				strtemp = "000";
			}
			
			str = str + strtemp;
			
		}
		
		//���Ϊ����Ϊȫ
        if(dlg.m_radio1 == 0)
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL='%s'",str);
		}
		else
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL='%s' WHERE %s",str,dlg.m_GetSubRangeStr);
		}	

		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
		
		m_AppearStr = dlg.m_AppearStr;
        m_AppearStr.TrimLeft();
		m_AppearStr.TrimRight();
        m_AppearStr = " ͳһ���ò������£�\r\n���������ڡ�\r\n" +  strs + "\r\n" + m_AppearStr + "\r\n";

		strm.Format("��ɨ�������\r\n �ȼ����Сʱ��%2d��\r\n",m_SpinScan.GetPos());
		m_AppearStr = m_AppearStr  + strm;
		strm.Format("����ɨ������\r\n ������Сʱ��%2d��\r\n",m_SpinScans.GetPos());
		m_AppearStr = m_AppearStr  + strm;
		
		if(m_autorun)
		{
			strm.Format("���Զ����С�\r\n �������ʱ�Զ���������פ������");
		}
		else
		{
			strm.Format("���Զ����С�\r\n �������ʱ���Զ���������פ������");
		}

		m_AppearStr = m_AppearStr  + strm;

		//ѯ���Ƿ��Ƕ����������
        AskOk();

	}
	}
	else //פ������Ϊ��
	{
        
		for(i=0;i<67;i++)//��ȫ�ֱ���
		   pview->m_DateReadParameter[i]=0;
	   m_AppearStr = " ͳһ���ò������£�\r\n���������ڡ�\r\n������\r\n ��հ���������פ���������ݿ� \r\n"; 
	   //ѯ�� 
	    

		if(MessageBox(m_AppearStr,"��ʱ�����������������",MB_OKCANCEL) == IDOK)
		{
			CTime timet = CTime::GetCurrentTime();//ʱ��
			str.Format("��%4d-%02d-%02d %02d:%02d:%02d����������פ��:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_AppearStr);
			pview->WriteToLog(str);
			//д��פ�������
			pview->WriteToParameterByDate();
			CDialog::OnOK();
		}
	}

}

void CZHULIUTIMESELECTDlg::OnFengset() 
{
	UpdateData(TRUE);
	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	CString         strm,strsql;
	CFENGBEISETDlg             dlg;
	dlg.m_Result[0 ] = m_check1;
	dlg.m_Result[1 ] = m_check2;
	dlg.m_Result[2 ] = m_check3;
	dlg.m_Result[3 ] = m_check4;
	dlg.m_Result[4 ] = m_check5;
	dlg.m_Result[5 ] = m_check6;
	dlg.m_Result[6 ] = m_check7;
	dlg.m_Result[7 ] = m_check8;
	dlg.m_Result[8 ] = m_check9;
	dlg.m_Result[9 ] = m_check10;
	dlg.m_Result[10] = m_check11;
	dlg.m_Result[11] = m_check12;
	dlg.m_Result[12] = m_check13;
	dlg.m_Result[13] = m_check14;
	dlg.m_Result[14] = m_check15;
	dlg.m_Result[15] = m_check16;
	dlg.m_Result[16] = m_check17;
	dlg.m_Result[17] = m_check18;
	dlg.m_Result[18] = m_check19;
	dlg.m_Result[19] = m_check20;
	dlg.m_Result[20] = m_check21;
	dlg.m_Result[21] = m_check22;
	dlg.m_Result[22] = m_check23;
	dlg.m_Result[23] = m_check24;
	dlg.m_Result[24] = m_check25;
	dlg.m_Result[25] = m_check26;
	dlg.m_Result[26] = m_check27;
	dlg.m_Result[27] = m_check28;
	dlg.m_Result[28] = m_check29;
	dlg.m_Result[29] = m_check30;
	dlg.m_Result[30] = m_check31;
	
	//��פ����������פ������
	for(int ii = 0; ii < 67; ii ++)
	{
		 pview->m_DateReadParameter[ii] = 0;
	}	
	
	strm  =  "";
	
	for(int i = 0; i < 93; i ++)
	{
		strm = strm + "0";
	}
	
	strsql.Format("UPDATE TB_USER SET USER_ZHULABEL='%s'",strm);
	CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	if(dlg.DoModal()==IDOK)
	{
	
		m_AppearStr = dlg.m_AppearStrs;
        m_AppearStr.TrimLeft();
		m_AppearStr.TrimRight();
        m_AppearStr = "�ֱ����ò������£�\r\n" + m_AppearStr + "\r\n";

    	strm.Format("��ɨ�������\r\n �ȼ����Сʱ��%2d��\r\n",m_SpinScan.GetPos());
		m_AppearStr = m_AppearStr  + strm;
		strm.Format("����ɨ������\r\n ������Сʱ��%2d��\r\n",m_SpinScans.GetPos());
		m_AppearStr = m_AppearStr  + strm;
		
		if(m_autorun)
		{
			strm.Format("���Զ����С�\r\n �Զ�����");
		}
		else
		{
			strm.Format("���Զ����С�\r\n ���Զ�����");
		}

		m_AppearStr = m_AppearStr  + strm;

		//���Ƿ�ȷ��
		AskOk();	
	}

}

void CZHULIUTIMESELECTDlg::OnCheck101() 
{
	//���״̬
	CheckStatus(); 
}

//���״̬
void CZHULIUTIMESELECTDlg::CheckStatus() 
{

	UpdateData(TRUE);

	//��פ����������
	BYTE  m_ZhuDays =     0;

	if(m_check1)
	{
		m_ZhuDays ++;
	}

	if(m_check2)
	{
		m_ZhuDays ++;
	}	
	
	if(m_check3)
	{
		m_ZhuDays ++;
	}	
	
	if(m_check4)
	{
		m_ZhuDays ++;
	}
	
	if(m_check5)
	{
		m_ZhuDays ++;
	}

    if(m_check6)
	{
		m_ZhuDays ++;
	}
	
	if(m_check7)
	{
		m_ZhuDays ++;
	}

	if(m_check8)
	{
		m_ZhuDays ++;
	}

	if(m_check9)
	{
		m_ZhuDays ++;
	}
	
	if(m_check10)
	{
		m_ZhuDays ++;
	}	
	
	if(m_check11)
	{
		m_ZhuDays ++;
	}

	if(m_check12)
	{
		m_ZhuDays ++;
	}

	if(m_check13)
	{
		m_ZhuDays ++;
	}
	
	if(m_check14)
	{
		m_ZhuDays ++;
	}

	if(m_check15)
	{
		m_ZhuDays ++;
	}

	if(m_check16)
	{
		m_ZhuDays ++;
	}

	if(m_check17)
	{
		m_ZhuDays ++;
	}

	if(m_check18)
	{
		m_ZhuDays ++;
	}
	
	if(m_check19)
	{
		m_ZhuDays ++;
	}

	if(m_check20)
	{
		m_ZhuDays ++;
	}
	
	if(m_check21)
	{
		m_ZhuDays ++;
	}	
	
	
	if(m_check22)
	{
		m_ZhuDays ++;
	}
	
	if(m_check23)
	{
		m_ZhuDays ++;
	}

	if(m_check24)
	{
		m_ZhuDays ++;
	}
	
	if(m_check25)
	{
		m_ZhuDays ++;
	}	
	
	
	if(m_check26)
	{
		m_ZhuDays ++;
	}
	
	if(m_check27)
	{
		m_ZhuDays ++;
	}

	if(m_check28)
	{
		m_ZhuDays ++;
	}

	if(m_check29)
	{
		m_ZhuDays ++;
	}
	
	if(m_check30)
	{
		m_ZhuDays ++;
	}
	
	if(m_check31)
	{
		m_ZhuDays ++;
	}

	CWnd*         pt ;

	if(m_ZhuDays <= 0)
	{
		pt = GetDlgItem(IDC_FENGSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_TOTALSET);
		pt->EnableWindow(TRUE);
	}
	else
	{
		pt = GetDlgItem(IDC_TOTALSET);
		pt->EnableWindow(TRUE);	
	
		pt = GetDlgItem(IDC_FENGSET);
		
		//��2�����ϲ��з�ʱפ��
		if(m_ZhuDays > 1)
		{
			pt->EnableWindow(TRUE);
		}
		else
		{
			pt->EnableWindow(FALSE);
		}

	}

}

void CZHULIUTIMESELECTDlg::OnCheck102() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck103() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck104() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck105() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck106() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck107() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck108() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck109() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck110() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck111() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck112() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck113() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck114() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck115() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck116() 
{
	//���״̬
	CheckStatus(); 
	
}

void CZHULIUTIMESELECTDlg::OnCheck117() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck118() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck119() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck120() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck121() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck122() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck123() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck124() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck125() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck126() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck127() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck128() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck129() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck130() 
{
	//���״̬
	CheckStatus(); 	
}

void CZHULIUTIMESELECTDlg::OnCheck131() 
{
	//���״̬
	CheckStatus(); 	
}



//ȷ����Ϣ
void CZHULIUTIMESELECTDlg::AskOk()
{
	CString  str;

	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    
	if(m_check1)
	{
		//1��
		pview->m_DateReadParameter[0] = 1;
	}
	else
	{
		pview->m_DateReadParameter[0] = 0;
		pview->m_DateReadParameter[1] = 0;
	}

	if(m_check2)
	{
		//2��
		pview->m_DateReadParameter[2] = 1;
	}
	else
	{
		pview->m_DateReadParameter[2] = 0;
		pview->m_DateReadParameter[3] = 0;
	}
	
	if(m_check3)
	{
		//3��
		pview->m_DateReadParameter[4] = 1;
	}
	else
	{
		pview->m_DateReadParameter[4] = 0;
		pview->m_DateReadParameter[5] = 0;
	}
	
	if(m_check4)
	{
		//4��
		pview->m_DateReadParameter[6] = 1;
	}
	else
	{
		pview->m_DateReadParameter[6] = 0;
		pview->m_DateReadParameter[7] = 0;
	}
	
	if(m_check5)
	{
		//5��
		pview->m_DateReadParameter[8] = 1;
	}	
	else
	{
		pview->m_DateReadParameter[8] = 0;
		pview->m_DateReadParameter[9] = 0;
	}


    if(m_check6)
	{
		//6��
		pview->m_DateReadParameter[10] = 1;
	}
	else
	{
		pview->m_DateReadParameter[10] = 0;
		pview->m_DateReadParameter[11] = 0;
	}
	
	if(m_check7)
	{
		//7��
		pview->m_DateReadParameter[12] = 1;
	}
	else
	{
		pview->m_DateReadParameter[12] = 0;
		pview->m_DateReadParameter[13] = 0;
	}

	if(m_check8)
	{
		//8��
		pview->m_DateReadParameter[14] = 1;
	}
	else
	{
		pview->m_DateReadParameter[14] = 0;
		pview->m_DateReadParameter[15] = 0;
	}

	if(m_check9)
	{
		//9��
		pview->m_DateReadParameter[16] = 1;
	}
	else
	{
		pview->m_DateReadParameter[16] = 0;
		pview->m_DateReadParameter[17] = 0;
	}
	
	if(m_check10)
	{
		//10��
		pview->m_DateReadParameter[18] = 1;
	}
	else
	{
		pview->m_DateReadParameter[18] = 0;
		pview->m_DateReadParameter[19] = 0;
	}	
	
	if(m_check11)
	{
		//11��
		pview->m_DateReadParameter[20] = 1;
	}
	else
	{
		pview->m_DateReadParameter[20] = 0;
		pview->m_DateReadParameter[21] = 0;
	}	

	if(m_check12)
	{
		//12��
		pview->m_DateReadParameter[22] = 1;
	}
	else
	{
		pview->m_DateReadParameter[22] = 0;
		pview->m_DateReadParameter[23] = 0;
	}	

	if(m_check13)
	{
		//13��
		pview->m_DateReadParameter[24] = 1;
	}
	else
	{
		pview->m_DateReadParameter[24] = 0;
		pview->m_DateReadParameter[25] = 0;
	}	
	
	if(m_check14)
	{
		//14��
		pview->m_DateReadParameter[26] = 1;
	}
	else
	{
		pview->m_DateReadParameter[26] = 0;
		pview->m_DateReadParameter[27] = 0;
	}	

	if(m_check15)
	{
		//15��
		pview->m_DateReadParameter[28] = 1;
	}
	else
	{
		pview->m_DateReadParameter[28] = 0;
		pview->m_DateReadParameter[29] = 0;
	}	

	if(m_check16)
	{
		//16��
		pview->m_DateReadParameter[30] = 1;
	}
	else
	{
		pview->m_DateReadParameter[30] = 0;
		pview->m_DateReadParameter[31] = 0;
	}	

	if(m_check17)
	{
		//17��
		pview->m_DateReadParameter[32] = 1;
	}
	else
	{
		pview->m_DateReadParameter[32] = 0;
		pview->m_DateReadParameter[33] = 0;
	}	

	if(m_check18)
	{
		//18��
		pview->m_DateReadParameter[34] = 1;
	}
	else
	{
		pview->m_DateReadParameter[35] = 0;
		pview->m_DateReadParameter[35] = 0;
	}	
	
	if(m_check19)
	{
		//19��
		pview->m_DateReadParameter[36] = 1;
	}
	else
	{
		pview->m_DateReadParameter[36] = 0;
		pview->m_DateReadParameter[37] = 0;
	}	

	if(m_check20)
	{
		//20��
		pview->m_DateReadParameter[38] = 1;
	}
	else
	{
		pview->m_DateReadParameter[38] = 0;
		pview->m_DateReadParameter[39] = 0;
	}	
	
	if(m_check21)
	{
		//21��
		pview->m_DateReadParameter[40] = 1;
	}
	else
	{
		pview->m_DateReadParameter[40] = 0;
		pview->m_DateReadParameter[41] = 0;
	}		
	
	
	if(m_check22)
	{
		//22��
		pview->m_DateReadParameter[42] = 1;
	}
	else
	{
		pview->m_DateReadParameter[42] = 0;
		pview->m_DateReadParameter[43] = 0;
	}	
	
	if(m_check23)
	{
		//23��
		pview->m_DateReadParameter[44] = 1;
	}
	else
	{
		pview->m_DateReadParameter[44] = 0;
		pview->m_DateReadParameter[45] = 0;
	}	

	if(m_check24)
	{
		//24��
		pview->m_DateReadParameter[46] = 1;
	}
	else
	{
		pview->m_DateReadParameter[46] = 0;
		pview->m_DateReadParameter[47] = 0;
	}	
	
	if(m_check25)
	{
		//25��
		pview->m_DateReadParameter[48] = 1;
	}
	else
	{
		pview->m_DateReadParameter[48] = 0;
		pview->m_DateReadParameter[49] = 0;
	}	
	
	
	if(m_check26)
	{
		//26��
		pview->m_DateReadParameter[50] = 1;
	}
	else
	{
		pview->m_DateReadParameter[50] = 0;
		pview->m_DateReadParameter[51] = 0;
	}
	
	if(m_check27)
	{
		//27��
		pview->m_DateReadParameter[52] = 1;
	}
	else
	{
		pview->m_DateReadParameter[52] = 0;
		pview->m_DateReadParameter[53] = 0;
	}

	if(m_check28)
	{
		//28��
		pview->m_DateReadParameter[54] = 1;
	}
	else
	{
		pview->m_DateReadParameter[54] = 0;
		pview->m_DateReadParameter[55] = 0;
	}

	if(m_check29)
	{
		//29��
		pview->m_DateReadParameter[56] = 1;
	}
	else
	{
		pview->m_DateReadParameter[56] = 0;
		pview->m_DateReadParameter[57] = 0;
	}
	
	if(m_check30)
	{
		//30��
		pview->m_DateReadParameter[58] = 1;
	}
	else
	{
		pview->m_DateReadParameter[58] = 0;
		pview->m_DateReadParameter[59] = 0;
	}
	
	if(m_check31)
	{
		//31��
		pview->m_DateReadParameter[60] = 1;
	}
	else
	{
		pview->m_DateReadParameter[60] = 0;
		pview->m_DateReadParameter[61] = 0;
	}


   //ɨ����(30-60����)
	pview->m_DateReadParameter[62] = 30;
	//ɨ�����(3-7��)
	pview->m_DateReadParameter[63] = m_SpinScan.GetPos();
	//�Ժ�ÿ���ʱ��ɨ(0-23��)
    pview->m_DateReadParameter[64] = 0;
	//�Ժ�ɨ�����(0-3��)
	pview->m_DateReadParameter[65] = m_SpinScans.GetPos();
    //�Ƿ�һ�������Զ�פ��
	pview->m_DateReadParameter[66] = m_autorun;

	
	if(MessageBox(m_AppearStr,"��ʱ�����������������",MB_OKCANCEL) == IDOK)
	{
		CTime timet = CTime::GetCurrentTime();//ʱ��
	    str.Format("��%4d-%02d-%02d %02d:%02d:%02d����������פ��:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_AppearStr);
		pview->WriteToLog(str);
		//д��פ�������
		pview->WriteToParameterByDate();

		//����Զ��������޸İ����������Զ�פ��
		if(m_autorun)
		{
			
			if(pview->IsCurveTableExist("TB_Auto"))
			{
				
				if(CDataBaseInstance::GetAllRecordsCount("TB_Auto","ALL") > 0)
				{
					
					str.Format("UPDATE TB_Auto SET Auto_Parameter110=%d",0);
					CDataBaseInstance::ExecuteDataBaseSQL(str);
					
				}

			}
			
		}

		//����פ��
		pview->StartZhuLiu();
		CDialog::OnOK();
	}

}

