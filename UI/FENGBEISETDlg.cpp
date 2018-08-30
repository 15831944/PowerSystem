// FENGBEISET.cpp : implementation file
//

#include "stdafx.h"



#include "IFRMView.h"
#include "FENGBEISETDlg.h"
#include "READRANGLE.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFENGBEISET dialog


CFENGBEISETDlg::CFENGBEISETDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFENGBEISETDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFENGBEISET)
	m_AppearStrs = _T("");
	//}}AFX_DATA_INIT
}


void CFENGBEISETDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFENGBEISET)
	DDX_Text(pDX, IDC_APPEARSTR, m_AppearStrs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFENGBEISETDlg, CDialog)
	//{{AFX_MSG_MAP(CFENGBEISET)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON24, OnButton24)
	ON_BN_CLICKED(IDC_BUTTON29, OnButton29)
	ON_BN_CLICKED(IDC_BUTTON34, OnButton34)
	ON_BN_CLICKED(IDC_BUTTON39, OnButton39)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON25, OnButton25)
	ON_BN_CLICKED(IDC_BUTTON30, OnButton30)
	ON_BN_CLICKED(IDC_BUTTON35, OnButton35)
	ON_BN_CLICKED(IDC_BUTTON40, OnButton40)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON36, OnButton36)
	ON_BN_CLICKED(IDC_BUTTON41, OnButton41)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON27, OnButton27)
	ON_BN_CLICKED(IDC_BUTTON32, OnButton32)
	ON_BN_CLICKED(IDC_BUTTON37, OnButton37)
	ON_BN_CLICKED(IDC_BUTTON42, OnButton42)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON23, OnButton23)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFENGBEISET message handlers

BOOL CFENGBEISETDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd*        pt;

	if(!m_Result[0])
	{
		pt = GetDlgItem(IDC_BUTTON1);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[1])
	{
		pt = GetDlgItem(IDC_BUTTON14);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[2])
	{
		pt = GetDlgItem(IDC_BUTTON19);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[3])
	{
		pt = GetDlgItem(IDC_BUTTON24);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[4])
	{
		pt = GetDlgItem(IDC_BUTTON29);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[5])
	{
		pt = GetDlgItem(IDC_BUTTON34);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[6])
	{
		pt = GetDlgItem(IDC_BUTTON39);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[7])
	{
		pt = GetDlgItem(IDC_BUTTON10);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[8])
	{
		pt = GetDlgItem(IDC_BUTTON15);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[9])
	{
		pt = GetDlgItem(IDC_BUTTON20);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[10])
	{
		pt = GetDlgItem(IDC_BUTTON25);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[11])
	{
		pt = GetDlgItem(IDC_BUTTON30);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[12])
	{
		pt = GetDlgItem(IDC_BUTTON35);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[13])
	{
		pt = GetDlgItem(IDC_BUTTON40);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[14])
	{
		pt = GetDlgItem(IDC_BUTTON11);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[15])
	{
		pt = GetDlgItem(IDC_BUTTON16);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[16])
	{
		pt = GetDlgItem(IDC_BUTTON21);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[17])
	{
		pt = GetDlgItem(IDC_BUTTON26);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[18])
	{
		pt = GetDlgItem(IDC_BUTTON31);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[19])
	{
		pt = GetDlgItem(IDC_BUTTON36);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[20])
	{
		pt = GetDlgItem(IDC_BUTTON41);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[21])
	{
		pt = GetDlgItem(IDC_BUTTON12);
		pt->EnableWindow(FALSE);
	}	
	
	if(!m_Result[22])
	{
		pt = GetDlgItem(IDC_BUTTON17);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[23])
	{
		pt = GetDlgItem(IDC_BUTTON22);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[24])
	{
		pt = GetDlgItem(IDC_BUTTON27);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[25])
	{
		pt = GetDlgItem(IDC_BUTTON32);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[26])
	{
		pt = GetDlgItem(IDC_BUTTON37);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[27])
	{
		pt = GetDlgItem(IDC_BUTTON42);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[28])
	{
		pt = GetDlgItem(IDC_BUTTON13);
		pt->EnableWindow(FALSE);
	}

	if(!m_Result[29])
	{
		pt = GetDlgItem(IDC_BUTTON18);
		pt->EnableWindow(FALSE);
	}
	
	if(!m_Result[30])
	{
		pt = GetDlgItem(IDC_BUTTON23);
		pt->EnableWindow(FALSE);
	}	m_AppearStrs   = "";
	CString         str,str1;
	str = str1 =   "";

	for(int i = 0 ; i < 31; i ++)
	{
		
		if(m_Result[i])
		{

			str1.Format("%2d",i + 1);
			
			if(str.IsEmpty())
			{
				str = str + str1;
			}
			else
			{
				str = str + "��" + str1 ;
			}
			
		}
		
	}

	m_AppearStrs = "��Ӧ��פ�����ڡ�" + str ;

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFENGBEISETDlg::OnButton1() 
{
	//������1��
	CREADRANGLEDlg dlg;
	dlg.m_days     =   1;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[0]            = " 1��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
	}
	
}

void CFENGBEISETDlg::OnButton14() 
{
	//������2��
	CREADRANGLEDlg dlg;
	dlg.m_days     =  2;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[1]            = " 2��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}		
}

void CFENGBEISETDlg::OnButton19() 
{
	//������3��
	CREADRANGLEDlg dlg;
	dlg.m_days     =   3;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[2]            = " 3��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton24() 
{
	//������4��
	CREADRANGLEDlg     dlg;
	dlg.m_days     =  4;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[3]            = " 4��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton29() 
{
	//������5��
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   5;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[4]            = " 5��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton34() 
{
	//������6��
	CREADRANGLEDlg     dlg;
	dlg.m_days     =  6;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[5]            = " 6��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton39() 
{
	//������7��
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   7;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[6]            = " 7��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton10() 
{
	//������8��
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   8;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[7]            = " 8��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton15() 
{
	//������9��
	CREADRANGLEDlg      dlg;
	dlg.m_days     =   9;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[8]            = " 9��פ��������������:\r\n" + dlg.m_AppearStr;
		
	   	//ˢ����ʾ
		Refresh();
		
	}
				
}

void CFENGBEISETDlg::OnButton20() 
{
	//������10��
	CREADRANGLEDlg      dlg;
	dlg.m_days     =  10;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[9] = "10��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton25() 
{
	//������11��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  11;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[10] = "11��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton30() 
{
	//������12��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  12;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[11] = "12��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton35() 
{
	//������13��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  13;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[12] = "13��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}			
}

void CFENGBEISETDlg::OnButton40() 
{
	//������14��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  14;	
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[13] = "14��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton11() 
{
	//������15��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  15;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[14] = "15��פ��������������:\r\n" + dlg.m_AppearStr;
		
	    //ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton16() 
{
	//������16��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  16;	

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[15] = "16��פ��������������:\r\n" + dlg.m_AppearStr;
		
	    //ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton21() 
{
	//������17��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  17;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[16] = "17��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton26() 
{
	//������18��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  18;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[17] = "18��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton31() 
{
	//������19��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  19;	
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[18] = "19��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton36() 
{
	//������20��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  20;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[19] = "20��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton41() 
{
	//������21��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  21;

	if(dlg.DoModal() == IDOK)
	{
		
	    m_AppearStr[20] = "21��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton12() 
{
	//������22��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  22;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[21] = "22��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton17() 
{
	//������23��
	CREADRANGLEDlg  dlg;
	dlg.m_days      =  23;	

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[22] = "23��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton22() 
{
	//������24��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  24;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[23] = "24��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton27() 
{
	//������25��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  25;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[24] = "25��פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}
	
}

void CFENGBEISETDlg::OnButton32() 
{
	//������26��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  26;
	
	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[25] = "26פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton37() 
{
	//������27��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  27;	

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[26] = "27פ��������������:\r\n" + dlg.m_AppearStr;
		
	  	//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton42() 
{
	//������28��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  28;

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[27] = "28פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}					
}

void CFENGBEISETDlg::OnButton13() 
{
	//������29��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  29;

	if(dlg.DoModal() == IDOK)
	{
		
		m_AppearStr[28]= "29פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton18() 
{
	//������30��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  30;	

	if(dlg.DoModal() == IDOK)
	{
		m_AppearStr[29]= "30פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}				
}

void CFENGBEISETDlg::OnButton23() 
{
	//������31��
	CREADRANGLEDlg       dlg;
	dlg.m_days      =  31;	

	if(dlg.DoModal() == IDOK)
	{	
		m_AppearStr[30]= "31פ��������������:\r\n" + dlg.m_AppearStr;
		
		//ˢ����ʾ
		Refresh();
		
	}	
}

//ˢ����ʾ
void CFENGBEISETDlg::Refresh()
{
	m_AppearStrs   = "";
	CString         str,str1,str3,strsql;
    str = str1 =   "";
	
	int j  =        1;

	for(int i = 0 ; i < 31; i ++)
	{
		
		//��ʾҪ���õ�����
		if(m_Result[i])
		{

			str1.Format("%2d",i + 1);
			
			if(str3.IsEmpty())
			{
				str3 = str3 + str1;
			}
			else
			{
				str3 = str3 + "��" + str1 ;
			}
			
		}

		//��ʾ�����õ�����
		if(!m_AppearStr[i].IsEmpty())
		{

			str1.Format("%2d",i + 1);

			if(str.IsEmpty())
			{
				str = str + str1;
			}
			else
			{
				str = str + "��" + str1 ;
			}

			str1.Format("%2d��%s",j,m_AppearStr[i] + "\r\n");

			m_AppearStrs = m_AppearStrs + str1;
			
			j ++;

		}
		
	}

	m_AppearStrs = "��Ӧ��פ�����ڡ�" + str3 + "\r\n" + "������פ�����ڡ�" +  str + "\r\n\r\n��ϸ�������£�\r\n" + m_AppearStrs;

	UpdateData(FALSE);
}

void CFENGBEISETDlg::OnOK() 
{
    BOOL m_Passing  =  TRUE;
	CString             str;
	int i = 0;
	for( i = 0 ; i < 31; i ++)
	{
		
		//��ʾҪ���õ�����
		if(m_Result[i])
		{
			//��ʾ�����õ�����
			if(m_AppearStr[i].IsEmpty())
			{
				m_Passing = FALSE;
				break;
			}
			
		}
		
	}

	//����Ƿ�ͨ��
	if(!m_Passing)
	{
		str.Format("��%d����פ������û�����úã���",i + 1);
		MessageBox(str,"����",MB_OK|MB_ICONWARNING);
		return;
	}

	
	CDialog::OnOK();
}
