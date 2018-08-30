// AngleSet.cpp : implementation file
//

#include "stdafx.h"

#include "AngleSettingDlg.h"


#include "IFRMView.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAngleSet dialog//spin


CAngleSettingGlg::CAngleSettingGlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAngleSettingGlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAngleSet)
	m_Sangle          =     30;
	m_SangleB         =     30; 
	m_SangleC         =     30;
	m_generatrixno    =      1;
	m_handno          =      0;
	m_handstationname = _T("");
	m_status          =   TRUE;
	m_radio           =      0;
	m_saveyears       =      0;
	//}}AFX_DATA_INIT
}


void CAngleSettingGlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAngleSet)
	DDX_Control(pDX, IDC_SPINHANDNO, m_spinhandno);
	DDX_Control(pDX, IDC_SPIN, m_SpinButton);
	DDX_Text(pDX, IDC_SANGLE, m_Sangle);
	DDX_Text(pDX, IDC_SANGLEB, m_SangleB);
	DDX_Text(pDX, IDC_SANGLEC, m_SangleC);
	DDX_Text(pDX, IDC_GENERATRIXNO, m_generatrixno);
	DDX_Text(pDX, IDC_HANDNO, m_handno);
	DDX_Text(pDX, IDC_HANDSTATIONNAME, m_handstationname);
	DDX_Check(pDX, IDC_STATUS, m_status);
	DDX_Control(pDX, IDC_SSTAB, m_SstabCtrl);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_SAVEYEARS, m_saveyears);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAngleSettingGlg, CDialog)
	//{{AFX_MSG_MAP(CAngleSet)
	ON_BN_CLICKED(IDC_ANGLESET, OnAngleset)
	ON_BN_CLICKED(IDC_READANGLE, OnReadangle)
	ON_BN_CLICKED(IDC_ANGLESETB, OnAnglesetb)
	ON_BN_CLICKED(IDC_ANGLESETC, OnAnglesetc)
	ON_BN_CLICKED(IDC_READANGLEB, OnReadangleb)
	ON_BN_CLICKED(IDC_READANGLEC, OnReadanglec)
	ON_BN_CLICKED(ID_SETPARAMETER, OnSetparameter)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_SETYEARS, OnSetyears)
	ON_BN_CLICKED(IDC_READYEARS, OnReadyears)
	ON_BN_CLICKED(ID_CANCELSET, OnCancelset)
	ON_BN_CLICKED(IDC_RADIO49, OnRadio49)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAngleSet message handlers

void CAngleSettingGlg::OnAngleset() 
{
	UpdateData(TRUE);
    //short generatrixno ĸ�߱��
	//short phase  ��� 0 A�� 1 B�� 2 C��
    //int   angles �Ƕ�
	SetThreePhaseAngle(m_generatrixno,0, m_Sangle,m_radio);
}


void CAngleSettingGlg::OnReadangle() 
{
	UpdateData(TRUE);
	
    CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//short phase  ��� 0 A�� 1 B�� 2 C��
    pview->ReadThreePhaseAngle(m_generatrixno,0,m_radio);
	
}

//short generatrixno ĸ�߱��
//short phase  ��� 0 A�� 1 B�� 2 C��
//int   angles �Ƕ�
//BYTE  kinds  ���� 0--�ź�ǿ�� 1���ӳٽǶ�
void CAngleSettingGlg::SetThreePhaseAngle(short generatrixno,short phase,int angles,BYTE kinds)
{
	
    CString str;
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	switch(phase)
	{
	case 0:
		{  
			if(kinds == 0)
			{
				str.Format("�����A���ź�ǿ�����ó�%d?",angles);
			}
			else
			{
				str.Format("�����A���ӳٽǶ����ó�%d?",angles);
			}
			break;
			
		}
	case 1:
		{
			if(kinds == 0)
			{
				str.Format("�����B���ź�ǿ�����ó�%d?",angles);
			}
			else
			{
				str.Format("�����B���ӳٽǶ����ó�%d?",angles);
			}
			break;
			
		}
	case 2:
		{
			
			if(kinds == 0)
			{
				str.Format("�����C���ź�ǿ�����ó�%d?",angles);
			}
			else
			{    
				str.Format("�����C���ӳٽǶ����ó�%d?",angles);
			}

			break;
			
		}
		
	}
	
	
	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		//short generatrixno ĸ�߱��
		//short phase        ��� 0 A�� 1 B�� 2 C��
		//int   angles       �Ƕ�
		pview->SetPhaseAngle(generatrixno,phase,angles,kinds);
	}
	
	
	
}

void CAngleSettingGlg::OnAnglesetb() 
{
	UpdateData(TRUE);

	//short generatrixno ĸ�߱��
	//short phase  ��� 0 A�� 1 B�� 2 C��
    //int   angles �Ƕ�
	SetThreePhaseAngle(m_generatrixno,1, m_SangleB,m_radio);	
}

void CAngleSettingGlg::OnAnglesetc() 
{
    UpdateData(TRUE);

	//short generatrixno ĸ�߱��
	//short phase  ��� 0 A�� 1 B�� 2 C��
    //int   angles �Ƕ�
	SetThreePhaseAngle(m_generatrixno,2, m_SangleC,m_radio);	
}



void CAngleSettingGlg::OnReadangleb() 
{

   UpdateData(TRUE);

   CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
 
   //short phase  ��� 0 A�� 1 B�� 2 C��
   pview->ReadThreePhaseAngle(m_generatrixno,1,m_radio);
	
}

void CAngleSettingGlg::OnReadanglec() 
{

   UpdateData(TRUE);
  
   //short phase  ��� 0 A�� 1 B�� 2 C��
   CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
  
    //short phase  ��� 0 A�� 1 B�� 2 C��
   pview->ReadThreePhaseAngle(m_generatrixno,2,m_radio);
}

BOOL CAngleSettingGlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    EnableWindows(0);
	m_saveyears = pview->m_saveyears;
	
	//���ð�ť���
	
	/*
	m_ParameterSet.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_readanglecd.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_readanglec.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_readangleb.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_readangle.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_dangleset.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_anglesetc.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_anglesetb.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	m_angleseta.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
	*/

//	m_first.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
//	m_interval.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;

	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ANGLE);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	//ĸ�߷�Χ
	m_SpinButton.SetRange( 1, 4);
	m_SpinButton.SetPos(1);
   
	//������վ����
    m_spinhandno.SetRange( 0, 1);
	m_spinhandno.SetPos(0);
    
	//�õ������ֵ�վ��͵�վ����
	GetHandNoInformation();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAngleSettingGlg::OnSetparameter() 
{

	UpdateData(TRUE);
	CString      str;  
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    //pt->m_WhichKind-------TRUE ���վ�汾  FALSE��ְ�
	
	m_handstationname.TrimLeft();
	m_handstationname.TrimRight();
	str = "�������������ֹ��������Ϣ��?";
	
	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//���վ�汾
		if(m_WhichKind)
		{
			CDatabase dbs;
			CString StrSql;
			
			if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
			{	
				
				StrSql = "DELETE FROM TB_HAND";
				dbs.ExecuteSQL(StrSql);
				
				StrSql.Format("INSERT INTO TB_HAND(HAND_NO,HAND_STATIONNAME,HAND_STATUS) VALUES (%d,'%s',%d)",m_handno,m_handstationname,m_status);
				dbs.ExecuteSQL(StrSql);
				dbs.Close();

				//������վ����
				pview->m_handno        =  m_handno;
				//�Ƿ��͵����ź�
				pview->m_status        =  m_status;
				//���ö�ʱ��Ϣ
				pview->SetTimersign();
				MessageBox("�����ֹ��������Ϣ���óɹ���","��ʾ",MB_OK|MB_ICONWARNING);
				CDialog::OnOK();
				
			}
			
		}
		else
		{   
			
			//Զ�̶��������ֲ�����
			CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
			
			str.Format("BEGINS;COMMAND:20:%d:%s:%d;ENDS",m_handno,m_handstationname,m_status);
			
			if(pview->SelectSendString(pview->m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
			{				
				pview->m_StartRead = TRUE;
				
			}
			
		}
		
	}
	
}

//�õ������ֵ�վ��͵�վ����
void CAngleSettingGlg::GetHandNoInformation()
{
    CDatabase          db;
	CString        strSql;
	
	CString strValue = "";
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );

    	//�õ���¼����
		long fields = CDataBaseInstance::GetAllRecordsCount("TB_HAND","ALL"); 
		
		if(fields > 0)
		{
		
			strSql = "SELECT HAND_NO,HAND_STATIONNAME,HAND_STATUS FROM TB_HAND";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			rs.GetFieldValue((short)0,strValue);
			m_handno = atoi(strValue);
            rs.GetFieldValue((short)1,strValue);
			strValue.TrimLeft();
        	strValue.TrimRight();
            m_handstationname  = strValue;
           	rs.GetFieldValue((short)2,strValue);
			strValue.TrimLeft();
        	strValue.TrimRight();
            m_status  = atoi(strValue);
       
		}
		//�ر����ݿ�
	    rs.Close( );
		db.Close( );
	}

}


BEGIN_EVENTSINK_MAP(CAngleSettingGlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CAngleSet)
	ON_EVENT(CAngleSettingGlg, IDC_SSTAB, -600 /* Click */, OnClickSstab, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CAngleSettingGlg::OnClickSstab(short PreviousTab) 
{
	EnableWindows(m_SstabCtrl.GetTab());
}

void CAngleSettingGlg::EnableWindows(int m_select)
{
	switch(m_select)
	{
	case 0:
		{
			CWnd* pt = GetDlgItem(IDC_STATIC1);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC2);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC3);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC4);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_GENERATRIXNO);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SPIN);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SANGLE);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_ANGLESET);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_READANGLE);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SANGLEB);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_ANGLESETB);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_READANGLEB);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SANGLEC);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_ANGLESETC);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_READANGLEC);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO1);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO2);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC15);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SAVEYEARS);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SETYEARS);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_READYEARS);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_RADIO49);
			pt->ShowWindow(SW_SHOW);


			pt = GetDlgItem(IDC_STATIC5);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_HANDSTATIONNAME);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC6);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_HANDNO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SPINHANDNO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATUS);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(ID_SETPARAMETER);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(ID_CANCELSET);
			pt->ShowWindow(SW_HIDE);
			break;
		}
	case 1:
		{	
			CWnd* pt = GetDlgItem(IDC_STATIC1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC3);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC4);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_GENERATRIXNO);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SPIN);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SANGLE);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_ANGLESET);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_READANGLE);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SANGLEB);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_ANGLESETB);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_READANGLEB);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SANGLEC);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_ANGLESETC);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_READANGLEC);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO1);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO2);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_STATIC15);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SAVEYEARS);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_SETYEARS);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_READYEARS);
			pt->ShowWindow(SW_HIDE);
			pt = GetDlgItem(IDC_RADIO49);
			pt->ShowWindow(SW_HIDE);

			pt = GetDlgItem(IDC_STATIC5);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_HANDSTATIONNAME);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATIC6);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_HANDNO);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_SPINHANDNO);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(IDC_STATUS);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(ID_SETPARAMETER);
			pt->ShowWindow(SW_SHOW);
			pt = GetDlgItem(ID_CANCELSET);
			pt->ShowWindow(SW_SHOW);
			break;
		}
	}

}

void CAngleSettingGlg::OnRadio1() 
{
	UpdateData(TRUE);
    m_radio  = 0;	
	CWnd* pt =  GetDlgItem(IDC_STATIC2);
	pt->SetWindowText("������A���ź�ǿ��");	
	pt =  GetDlgItem(IDC_STATIC3);
	pt->SetWindowText("������B���ź�ǿ��");
	pt =  GetDlgItem(IDC_STATIC4);
	pt->SetWindowText("������C���ź�ǿ��");
	CEdit * pp = (CEdit *)GetDlgItem(IDC_SANGLE);
	pp->SetWindowText("30");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEB);
	pp->SetWindowText("30");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEC);
	pp->SetWindowText("30");
	pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(TRUE);
	UpdateData(TRUE);
    UpdateData(FALSE);	
}

void CAngleSettingGlg::OnRadio2() 
{
	UpdateData(TRUE);
    m_radio  = 1;	
	CWnd* pt =  GetDlgItem(IDC_STATIC2);
	pt->SetWindowText("������A���ӳٽǶ�");	
	pt =  GetDlgItem(IDC_STATIC3);
	pt->SetWindowText("������B���ӳٽǶ�");
	pt =  GetDlgItem(IDC_STATIC4);
	pt->SetWindowText("������C���ӳٽǶ�");
	CEdit * pp = (CEdit *)GetDlgItem(IDC_SANGLE);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEB);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_SANGLEC);
	pp->SetWindowText("0");
	pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(TRUE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(TRUE);
	UpdateData(TRUE);
    UpdateData(FALSE);		
}

void CAngleSettingGlg::OnSetyears() 
{	
	UpdateData(TRUE);
	CString      str;

    CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(m_saveyears < 1 || m_saveyears > 10)
	{
		MessageBox("���ж������ݱ���ʱ��ӦΪ��1��10���꣡","���棺",MB_OK|MB_ICONWARNING);
		return;
	}

	str.Format("פ���������ݺ���ʽ�������ݶ�ֻ����Ϊ%d�ꣿ��\r\nע��������ʱ�䷶Χ��פ�����ݽ������ļ����棬\r\n������ʱ�䷶Χ��ʵʱ���ݽ���ɾ�����ٱ��棡��",m_saveyears);
	
	pview->m_saveyears = m_saveyears;

	if(MessageBox(str,"  ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		//0 ���ñ���ʱ�� 1 ��ѯ����ʱ��
		pview->DealOverTime(0);
	}
}

void CAngleSettingGlg::OnReadyears() 
{
	//0 ���ñ���ʱ�� 1 ��ѯ����ʱ��
	CString           str;  
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	pview->DealOverTime(1);	
	m_saveyears = pview->m_saveyears;
	UpdateData(FALSE);
}

void CAngleSettingGlg::OnCancelset() 
{
	UpdateData(TRUE);
	CString      str;  
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    //pt->m_WhichKind-------TRUE ���վ�汾  FALSE��ְ�
	
	m_handstationname.TrimLeft();
	m_handstationname.TrimRight();
	str = "����ȡ�������ֹ��������Ϣ��?";
	
	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//���վ�汾
		if(m_WhichKind)
		{
			
			CDatabase dbs;
			CString StrSql;
			
			if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
			{	
				
				StrSql = "DELETE FROM TB_HAND";
				dbs.ExecuteSQL(StrSql);
				StrSql.Format("INSERT INTO TB_HAND(HAND_NO,HAND_STATIONNAME,HAND_STATUS) VALUES (%d,'%s',%d)",m_handno,m_handstationname,0);
				dbs.ExecuteSQL(StrSql);
				dbs.Close();
				//������վ����
				pview->m_handno        =  m_handno;
				//�Ƿ��͵����ź�
				pview->m_status        =      FALSE;
				//���ö�ʱ��Ϣ
				pview->SetTimersign();
				MessageBox("ȡ�����������óɹ���","��ʾ",MB_OK|MB_ICONWARNING);
				CDialog::OnOK();
				
			}

		}
		else
		{   
			
			//Զ�̶��������ֲ�����
			CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
			
			str.Format("BEGINS;COMMAND:20:%d:%s:%d;ENDS",m_handno,m_handstationname,0);
			
			if(pview->SelectSendString(pview->m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
			{				
				pview->m_StartRead = TRUE;
				
			}
			
		}
		
	}	
}

void CAngleSettingGlg::OnRadio49() 
{
	CWnd* pp = (CEdit *)GetDlgItem(IDC_ANGLESET);
	pp->EnableWindow(FALSE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETB);
	pp->EnableWindow(FALSE);
	pp = (CEdit *)GetDlgItem(IDC_ANGLESETC);
	pp->EnableWindow(FALSE);	
}
