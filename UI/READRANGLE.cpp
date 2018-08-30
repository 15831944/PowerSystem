// READRANGLE.cpp : implementation file
//

#include "stdafx.h"
#include <cmath>



#include "IFRMView.h"
#include "READRANGLE.h"
#include "TRansformerdisppearDlg.h"
#include "DataBaseInstance.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CREADRANGLE dialog


CREADRANGLEDlg::CREADRANGLEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CREADRANGLEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CREADRANGLE)
	m_radio1       =    0;
	m_radio3       =    0;
	m_radio4       =    0;
	m_Isygdd       =  TRUE;
	m_Iswgdd       = FALSE;
	m_IsSanCurrent = FALSE;
	m_IsSanVoltage = FALSE;
	m_Isjfdd       = FALSE;
	m_Isfdd        = FALSE;
	m_Ispdd        = FALSE;
	m_Isgdd        = FALSE;
	m_Isglls       = FALSE;
	//}}AFX_DATA_INIT
}


void CREADRANGLEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREADRANGLE)
	DDX_Control(pDX, IDC_SPIN, m_spin);
	DDX_Radio(pDX, IDC_RADIO5, m_radio1);
	DDX_Radio(pDX, IDC_RADIO22, m_radio3);
	DDX_Radio(pDX, IDC_RADIO28, m_radio4);
	DDX_Check(pDX, IDC_CHECK101, m_Isygdd);
	DDX_Check(pDX, IDC_CHECK102, m_Iswgdd);
	DDX_Check(pDX, IDC_CHECK103, m_IsSanCurrent);
	DDX_Check(pDX, IDC_CHECK104, m_IsSanVoltage);
	DDX_Check(pDX, IDC_CHECK105, m_Isjfdd);
	DDX_Check(pDX, IDC_CHECK106, m_Isfdd);
	DDX_Check(pDX, IDC_CHECK107, m_Ispdd);
	DDX_Check(pDX, IDC_CHECK108, m_Isgdd);
	DDX_Check(pDX, IDC_CHECK109, m_Isglls);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CREADRANGLEDlg, CDialog)
	//{{AFX_MSG_MAP(CREADRANGLE)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREADRANGLE message handlers

void CREADRANGLEDlg::OnRadio5() 
{	
	CWnd* pt = GetDlgItem(IDOK);
	pt->EnableWindow(TRUE);
}

void CREADRANGLEDlg::OnRadio41() 
{	
	CWnd* pt = GetDlgItem(IDOK);
	pt->EnableWindow(FALSE);

	CTRansformerdisppearDlg  dlg;

	if(dlg.DoModal() == IDOK)
	{
		m_GetSubRangeStr = dlg.m_GetSubRangeStr;
		m_GetSubNameStr  = dlg.m_GetSubNameStr;
		pt->EnableWindow(TRUE);
	}

}



BOOL CREADRANGLEDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString         Str;
	
	OnRadio5();

	//פ��ʱ���(0-23��)
	m_spin.SetRange(0,23);

	if(m_days == 0)
	{
		Str.Format("�������ڶ���Χ�����ݼ�פ��ʱ�̵�����");
	}
	else
	{
		Str.Format("��%d���Ŷ���Χ�����ݼ�פ��ʱ�̵�����",m_days);
	}
	
	SetWindowText(Str);
    CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CREADRANGLEDlg::OnOK() 
{
    UpdateData(TRUE);	
	CString          str,strsql;
	int          m_BitValue = 0;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//�й����޹�����������������ѹ�����������������ƽ�������ȵ�������������
	if(!(m_Isygdd || m_Iswgdd || m_IsSanCurrent || m_IsSanVoltage || m_Isjfdd || m_Isfdd || m_Ispdd || m_Isgdd || m_Isglls))
	{
		MessageBox("��ѡ��פ���������ݣ�","����",MB_OK|MB_ICONWARNING);
		return;
	}

	//���ʱ����Ч��
	if(m_days  == 1)
	{
		
		//�����31��������
		if(pview->m_DateReadParameter[60] > 0)
		{
			
			//�����һ��ʱ���������һ��ʱ���
			if(m_spin.GetPos() < (pview->m_DateReadParameter[61]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n31�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n��ʱ����С��24Сʱ�������裡",m_spin.GetPos(),pview->m_DateReadParameter[61]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//�����С��ʱ��30��
		if(pview->m_DateReadParameter[58] > 0)
		{
			
			//�����һ��ʱ���������һ��ʱ���
			if(m_spin.GetPos() < (pview->m_DateReadParameter[59]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n30�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�������裡",m_spin.GetPos(),pview->m_DateReadParameter[59]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//�����С��ʱ��29��
		if(pview->m_DateReadParameter[56] > 0)
		{
			
			//�����һ��ʱ���������һ��ʱ���
			if(m_spin.GetPos() < (pview->m_DateReadParameter[57]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n29�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�������裡",m_spin.GetPos(),pview->m_DateReadParameter[57]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}

		//�����С��ʱ��28��
		if(pview->m_DateReadParameter[54] > 0)
		{
			
			//�����һ��ʱ���������һ��ʱ���
			if(m_spin.GetPos() < (pview->m_DateReadParameter[55]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n28�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�������裡",m_spin.GetPos(),pview->m_DateReadParameter[55]);
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}
		
	}
	else if(m_days == 31)
	{
		
		//�����һ��������
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//���һ��,������һ��ʱ���������ڵ�һ��ʱ���
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n31�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n��ʱ����С��24Сʱ�����裡",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}
	else if(m_days == 30)
	{
		
		//�����һ��������
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//���һ��,������һ��ʱ���������ڵ�һ��ʱ���
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n30�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�����裡",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}
	else if(m_days == 29)
	{
		
		//�����һ��������
		if(pview->m_DateReadParameter[0] > 0)
		{

			//���һ��,������һ��ʱ���������ڵ�һ��ʱ���
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n29�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�����裡",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}	
	else if(m_days == 28)
	{
		
		//�����һ��������
		if(pview->m_DateReadParameter[0] > 0)
		{
			
			//���һ��,������һ��ʱ���������ڵ�һ��ʱ���
			if(m_spin.GetPos() > (pview->m_DateReadParameter[1]))
			{
				str.Format("  1�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\n28�ŵ�פ��ʱ���Ϊ:%2d�㣬\r\nС��ʱ��ʱ����С��24Сʱ�����裡",pview->m_DateReadParameter[1],m_spin.GetPos());
				MessageBox(str," ",MB_OK|MB_ICONWARNING);
				return;
			}
			
		}	
		
	}


	//���С��ǰһ��
	if(pview->m_DateReadParameter[2*(m_days-2)] > 0)
	{
		
		if(m_spin.GetPos() < (pview->m_DateReadParameter[2*(m_days-2)+1]))
		{
			str.Format("%2d�ŵ�פ��ʱ�������Ϊ:%2d�㣬\r\n%2d�ŵ�פ��ʱ�������Ϊ:%2d�㣬\r\n��ʱ����С��24Сʱ�����裡",m_days-1,pview->m_DateReadParameter[2*(m_days-2) + 1],m_days,m_spin.GetPos());
			MessageBox(str," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
	}
	
	//������ں�һ��
	if(pview->m_DateReadParameter[2*m_days] > 0)
	{
		
		if(m_spin.GetPos() > pview->m_DateReadParameter[2*m_days+1])
		{
			str.Format("%2d�ŵ�פ��ʱ�������Ϊ:%2d�㣬\r\n%2d�ŵ�פ��ʱ�������Ϊ:%2d�㣬\r\n��ʱ����С��24Сʱ�����裡",m_days+1,pview->m_DateReadParameter[2*m_days+1],m_days,m_spin.GetPos());
			MessageBox(str," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
	}
	

	str    =      "���������\r\n";
 
	//�������
	if(m_radio1 ==1)
	{
		str = str + m_GetSubNameStr;
	}
	else
	{
		str = str + "������·���б�";
	}
	
	m_AppearStr = m_AppearStr + str + "\r\n";
	
	str    =      "���������ݡ�\r\n";
	
	//��������

	
	m_ReadRangeStr = "";

	//�й�
	if(m_Isygdd)
	{
		
		if(m_radio3 == 0)
		{
			m_BitValue = m_BitValue + int(pow((double)2,10));
			str        = str + "�й����  ";
		}
		else
		{	
			m_BitValue = m_BitValue + int(pow((double)2,10)) + int(pow((double)2,(int)9));
			str        = str + "�й������й����  ";
		}

	}


	//�޹�
	if(m_Iswgdd)
	{
		
		if(m_radio4 == 0)
		{	
			m_BitValue = m_BitValue + int(pow((double)2,8));
			str        = str + "�޹����  ";
		}
		else
		{	
			m_BitValue = m_BitValue + int(pow((double)2,8))+ int(pow((double)(int)2,(int)7));
			str        = str + "�޹������޹����  ";
		}

	}

    
	//ABC�������
	if(m_IsSanCurrent)
	{
		m_BitValue = m_BitValue + int(pow((double)2,6));
		str        = str + "ABC�������  ";
	}

	
	//ABC�����ѹ
	if(m_IsSanVoltage)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,5));
		str        = str + "ABC�����ѹ  ";
	}
	
	
	//������
	if(m_Isjfdd)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,4));
		str        = str + "������  ";
	}


	//�����
	if(m_Isfdd)
	{
		m_BitValue = m_BitValue + int(pow((double)2,3));
		str        = str + "�����  ";
	}


    //ƽ����
	if(m_Ispdd)
	{
		m_BitValue = m_BitValue + int(pow((double)2,2));
		str        = str     + "ƽ����  ";
	}


    //�ȵ���
	if(m_Isgdd)
	{	
		m_BitValue = m_BitValue + int(pow((double)(int)2,(int)1));
		str        = str  +    "�ȵ���  ";
	}  
	
	
	//��������
	if(m_Isglls)
	{	
		m_BitValue = m_BitValue + int(pow((double)2,0));
		str            = str + "��������  ";
	} 

    m_ReadRangeStr.Format("%03x",m_BitValue);

	m_AppearStr = m_AppearStr + str + "\r\n";

	str.Format("��פ��ʱ�̡� \r\n%2d��",m_spin.GetPos());
	m_AppearStr = m_AppearStr + str + "\r\n";
	
    
	if(m_days == 0)
	{
		//�������ڶ���Χ�����ݼ�פ��ʱ�̵�����
		for(int i = 0; i < 31; i ++)
		{
			pview->m_DateReadParameter[2*i + 1]     = m_spin.GetPos();
		}

	}
	else
	{
	  	//�Ŷ���Χ�����ݼ�פ��ʱ�̵�����
		pview->m_DateReadParameter[2*(m_days-1)    ] =               1;
		pview->m_DateReadParameter[2*(m_days-1) + 1] = m_spin.GetPos();

		//��ʼ����ʱ״̬Ϊ��
		strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')",(m_days-1)*3+1,"000");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);

		//���Ϊ����Ϊȫ
        if(m_radio1 == 0)
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')",(m_days-1)*3+1,m_ReadRangeStr);
		}
		else
		{
			strsql.Format("UPDATE TB_USER SET USER_ZHULABEL=STUFF(USER_ZHULABEL,%d,3,'%s')  WHERE %s",(m_days-1)*3+1,m_ReadRangeStr,m_GetSubRangeStr);
		}	
        
    	CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	}

	CDialog::OnOK();
}
