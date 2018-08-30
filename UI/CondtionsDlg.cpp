// Condtions.cpp : implementation file
//

#include "stdafx.h"

#include "CondtionsDlg.h"
#include "EveryTimesDlg.h"

#include "IFRMView.h"
#include "ReadNoValueDlg.h"
#include "DataBaseInstance.h"
#include "RuntimeAccount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCondtions dialog


CCondtionsDlg::CCondtionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCondtionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCondtions)
	m_radio1      =      0;
	m_Check1      =  FALSE;
	m_ReadLabel   =  FALSE;
	m_radio2      =      0;
	m_radio3      =      0;
	m_readradiokinds =   0;
	m_shikedian   =      0;
	m_readRangle  =      1;
	m_readtimes   =     24;
	m_QuickReading = FALSE;
	//}}AFX_DATA_INIT
}


void CCondtionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCondtions)
	DDX_Control(pDX, IDC_SPIN35, m_spin35);
	DDX_Control(pDX, IDC_SPIN34, m_spin34);
	DDX_Control(pDX, IDC_SPIN32, m_spin32);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_READLABEL, m_ReadLabel);
	DDX_Radio(pDX, IDC_RADIO22, m_radio2);
	DDX_Radio(pDX, IDC_RADIO28, m_radio3);
	DDX_Radio(pDX, IDC_RADIO4, m_readradiokinds);
	DDX_Text(pDX, IDC_EDIT38, m_shikedian);
	DDX_Text(pDX, IDC_EDIT36, m_readRangle);
	DDX_Text(pDX, IDC_EDIT37, m_readtimes);
	DDX_Check(pDX, IDC_QUICKREAD, m_QuickReading);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCondtionsDlg, CDialog)
	//{{AFX_MSG_MAP(CCondtions)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(ID_HIGHSET, OnHighset)
	ON_BN_CLICKED(IDC_CHECK34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK109, OnCheck109)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO37, OnRadio37)
	ON_EN_CHANGE(IDC_EDIT36, OnChangeEdit36)
    ON_WM_CREATE()
	ON_BN_CLICKED(IDC_READLABEL, OnReadlabel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCondtions message handlers

BOOL CCondtionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_spin32.SetRange(1,3);   //ɨ����  Сʱ�ı���
	m_spin34.SetRange(1,24);  //�ܼ�ɨ����
	m_spin35.SetRange(0,59);  //��ʼʱ���

	m_spin32.SetPos(1);      //ɨ����
	m_spin34.SetPos(24);     //�ܼ�ɨ����
	m_spin35.SetPos(0);      //��ʼʱ���

	//��ʼ�ǳ������
    OnRadio4();
	
	m_NoReadingKinds  = 0;
	/*
	m_start.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_cancel.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
	m_search.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
    */
	// Create the Lamp 256 colors button
	//m_OthersButton.SubclassDlgItem(ID_HIGHSET, this);
    // Don't draw border for this button
	//m_OthersButton.DrawBorder(TRUE);

    CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	for(int i = 0; i < 15;i ++)
    {
	
		pview->m_SetLabel[i] = FALSE;
	
    }


	//���ھ���
	CenterWindow();

	//���ô��ڵ�ͼ��
	//HICON hIcon = AfxGetApp()->LoadIcon(IDI_RUN);
	//ASSERT(hIcon);
	//SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
 	
	//�õ�פ��ʱ��
//	initializeListInfo();

    OnCheck1();

	m_Check1  =  TRUE;
	
	//�û�Ȩ��
	CIFRMApp* Apppt = (CIFRMApp*)AfxGetApp();

	if(CRuntimeAccount::GetCurrentPrivilege() > 2)
	{
	    CWnd* ptt = GetDlgItem(IDOK);
		ptt->EnableWindow(FALSE);
	}

    m_QuickReading = pview->m_QuickReading;

	UpdateData(FALSE);

	return TRUE;  
}

void CCondtionsDlg::IsSelect(int index)
{
   
    CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	if(pview->m_SetLabel[index] == FALSE)
	{
		pview->m_SetLabel[index] = TRUE;
	}
	else
	{
		pview->m_SetLabel[index] = FALSE;
	}

}

void CCondtionsDlg::OnCheck1() 
{
    IsSelect(0);//�й����-�����ۼ�ֵ
	IsSelect(1);//�й����-����ֵ	
}

void CCondtionsDlg::OnCheck2() 
{ 
	IsSelect(2);//�޹����-�����ۼ�ֵ
	IsSelect(3);//�޹����-����ֵ	
}

void CCondtionsDlg::OnCheck7() 
{
    IsSelect(4);//A�����
	IsSelect(5);//B�����
	IsSelect(6);//C�����	
}

void CCondtionsDlg::OnCheck8() 
{
    IsSelect(7);//A���ѹ
	IsSelect(8);//B���ѹ
	IsSelect(9);//C���ѹ	
}

void CCondtionsDlg::OnOK() 
{
    UpdateData(TRUE);	
    CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

    BOOL m_select = FALSE;
	
	for(int i = 0;i < 15; i++)
	{
        
		//ֻ���й���ȵ����ۼ�ֵIsSelect(1);//�й����-����ֵ
		if(m_radio2 == 0)
		{
			pview->m_SetLabel[1] = FALSE;
		}

        //ֻ���޹���ȵ����ۼ�ֵIsSelect(3); //�޹����-����ֵ
		if(m_radio3 == 0)
		{
			pview->m_SetLabel[3] = FALSE;
		}

		//�Ƿ�Ҫ��Ҫ��������
		if(pview->m_SetLabel[i] == TRUE)
		{
			m_select =  TRUE;
		}

	}

	//���û��ѡ��
	if(m_select == FALSE)
	{
		MessageBox("���ܶ���û��ѡ����ѡ�������!"," ",MB_OK|MB_ICONWARNING);
		return;
	}	

	CDialog::OnOK();
}

void CCondtionsDlg::initializeListInfo()
{	

	CString fieldname;
	//�����ݿ�
	CDatabase       db;
	CString     strSql;
	CString   strValue;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
      
		CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
   		//�õ���¼����
		long fields = CDataBaseInstance::GetAllRecordsCount("TB_HALTTIME","ALL"); 

		strSql = "SELECT * FROM TB_HALTTIME";
	
    	rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j++)
		{
				rs.GetFieldValue((short)0,m_GetTimeStr);
				m_GetTimeStr.TrimRight();
		
				//���»�һ����¼
			    rs.MoveNext();
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}

}


//
void CCondtionsDlg::OnHighset() 
{
	UpdateData(TRUE);
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	CEveryTimesDlg  dlg;
	dlg.m_times  = pview->m_Recycles;
	dlg.m_every  = pview->m_SetRecycleTime;
	
	if(dlg.DoModal() == IDOK)
	{
		//ѭ������,Ĭ����1 ��
	    pview->m_Recycles       =     dlg.m_times;
	    //��֮��ʱ����,Ĭ����30����
	    pview->m_SetRecycleTime =     dlg.m_every;
	}

}

void CCondtionsDlg::OnCheck34() 
{
	IsSelect(10);//������	
}

void CCondtionsDlg::OnCheck37() 
{
	IsSelect(11);//�����	
}

void CCondtionsDlg::OnCheck39() 
{
	IsSelect(13);//ƽ����	
}

void CCondtionsDlg::OnCheck38() 
{
	IsSelect(12);//�ȵ���	
}

void CCondtionsDlg::OnCheck109() 
{
    IsSelect(14);//��������	
}

void CCondtionsDlg::OnRadio4() 
{
	CWnd * pt = GetDlgItem(IDC_SPIN32);
	pt->EnableWindow(FALSE);	
	pt = GetDlgItem(IDC_SPIN34);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SPIN35);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_EDIT36);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_EDIT37);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_EDIT38);
	pt->EnableWindow(FALSE);

 	pt = GetDlgItem(IDC_RADIO1);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_RADIO2);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_RADIO3);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(ID_HIGHSET);
	pt->EnableWindow(TRUE);	
	pt = GetDlgItem(IDC_READLABEL);
	pt->EnableWindow(TRUE);
}

void CCondtionsDlg::OnRadio37() 
{
	CWnd * pt = GetDlgItem(IDC_SPIN32);
	pt->EnableWindow(TRUE);	
	pt = GetDlgItem(IDC_SPIN34);
	pt->EnableWindow(TRUE);	
	pt = GetDlgItem(IDC_SPIN35);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_EDIT36);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_EDIT37);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_EDIT38);
	pt->EnableWindow(TRUE);

    pt = GetDlgItem(IDC_RADIO1);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO2);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO3);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(ID_HIGHSET);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_READLABEL);
	pt->EnableWindow(FALSE);

}


void CCondtionsDlg::OnChangeEdit36() 
{
	
}

void CCondtionsDlg::OnReadlabel() 
{
     UpdateData(TRUE);	

	 if(m_ReadLabel)
	 {
		 m_NoReadingKinds  = 0;
		 
		 CReadNoValueDlg  dlg;
		 
		 if(dlg.DoModal() != IDOK)
		 {
			 m_ReadLabel  = FALSE;
			 UpdateData(FALSE);
		 }
		 else
		 {
			 m_NoReadingKinds  = dlg.m_radio;
			 m_PhaseNoKnown    = dlg.m_PhaseNoKnown;
		 }
		 
	 }

}
