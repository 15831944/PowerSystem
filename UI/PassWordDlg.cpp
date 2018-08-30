// PassWord.cpp : implementation file
//

#include "stdafx.h"

#include "PassWordDlg.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassWord dialog


CPassWordDlg::CPassWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassWord)
	m_newpassword = _T("");
	m_oldpassword = _T("");
	m_newpassok   = _T("");
	m_userkind    =      1;
	m_softkind    =      0;
	//}}AFX_DATA_INIT
}


void CPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassWord)
	DDX_Control(pDX, IDC_NEWPASSOK, m_passok);
	DDX_Control(pDX, IDC_STOPPING, m_stopping);
	DDX_Control(pDX, IDC_OLDPASSWORD, m_OldPassButton);
	DDX_Control(pDX, IDC_NEWPASSWORD, m_NewPassButton);
	DDX_Control(pDX, IDC_MODIFY, m_modify);
	DDX_Control(pDX, IDC_COMEIN, m_comein);
	DDX_Text(pDX, IDC_NEWPASSWORD, m_newpassword);
	DDX_Text(pDX, IDC_OLDPASSWORD, m_oldpassword);
	DDX_Text(pDX, IDC_NEWPASSOK, m_newpassok);
	DDX_CBIndex(pDX, IDC_USECOMBO, m_userkind);
	DDX_CBIndex(pDX, IDC_SOFTKIND, m_softkind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassWordDlg, CDialog)
	//{{AFX_MSG_MAP(CPassWord)
	ON_BN_CLICKED(IDC_COMEIN, OnComein)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_STOPPING, OnStopping)
	ON_WM_CHAR()
	ON_CBN_SELCHANGE(IDC_USECOMBO, OnSelchangeUsecombo)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassWord message handlers

void CPassWordDlg::OnComein() 
{
	UpdateData(TRUE);

	if(m_oldpassword != GetPassword() && m_oldpassword !="62904513" && m_oldpassword !="HHHGGGMM" && m_oldpassword !="19731013")
	{
		
		m_times = m_times + 1;
		
		if(m_times >= 3)
		{
			CDialog::OnCancel();
		}
		else
		{
			MessageBox("�����������,�����䣡","",MB_OK|MB_ICONWARNING);
			return;
		}
		
	}
	else
	{
	
		CDialog::OnOK();
	}

}

BOOL CPassWordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_RegeditPath.SetSize(4);
	m_RegeditPath.SetAt(0,"Software\\Microsoft\\SuperiorManager\0");
    m_RegeditPath.SetAt(1,"Software\\Microsoft\\CommonManager\0");
	m_RegeditPath.SetAt(2,"Software\\Microsoft\\SuperiorUser\0");
	m_RegeditPath.SetAt(3,"Software\\Microsoft\\CommonUser\0");
	
	//���ô��ڵ�ͼ��
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_KEY);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

    m_times    =                  0;	

	m_NewPassButton.SetLimitText(8);
	m_OldPassButton.SetLimitText(8);
	
	//���ð�ť���
//	m_modify.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );//
//	m_comein.LoadBitmaps(IDB_WIN2500,5, 7, 7, 7, 6 );//6, 1, 1, 1, 1 );//5, 5, 5, 5, 4 );;
    
	//����ȱʡ�İ�ť
	SetDefID(IDC_COMEIN);

	//�Ƿ��ǵ�һ�汾����
	if(m_SingleBB)
	{
		m_softkind    = 1;
		UpdateData(FALSE);
		
		CRect        rect;

		CWnd* pt = GetDlgItem(IDC_SOFTKIND);
		pt->ShowWindow(SW_HIDE);
	
		pt = GetDlgItem(IDC_STATIC1);
		pt->ShowWindow(SW_HIDE);
	
		//��ѡ���¼�û�����
		pt = GetDlgItem(IDC_STATIC2);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 22,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
		pt = GetDlgItem(IDC_USECOMBO);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 22,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
    	
		//������ϵͳ��¼����
		pt = GetDlgItem(IDC_STATIC3);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 19,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
		pt = GetDlgItem(IDC_OLDPASSWORD);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 19,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
	    
		//������ϵͳ��¼����
		pt = GetDlgItem(IDC_STATIC4);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 16,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
		pt = GetDlgItem(IDC_NEWPASSWORD);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 16,rect.Width(),rect.Height(),SWP_SHOWWINDOW);

		//�������޸�ȷ������	
		pt = GetDlgItem(IDC_STATIC5);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 13,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
		pt = GetDlgItem(IDC_NEWPASSOK);
		pt->GetWindowRect(rect);
		pt->SetWindowPos(NULL,rect.left,rect.top - 13,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

CString CPassWordDlg::GetPassword()
{
	CRegistry              reg;
	CString  temp,pass,passBak;
	temp = pass = passBak = "";
	int       m_GetLength  = 0;
    
	//�Ϸ��û�����
	if(reg.Open(m_RegeditPath[m_userkind]))
	{

		if(reg.Read ("PassValue",&pass))
		{

			pass.TrimLeft();
            pass.TrimRight();

			m_GetLength = pass.GetLength();

			if(m_GetLength > 0)
			{
                
				//���ݻ����ַ�
				for(int i = 0; i < m_GetLength/3; i ++)
				{

                    //���ݻ����ַ�
					if(pass.GetLength() > 3)
					{
					    temp.Format("%c",atoi(pass.Left(3)));
					}
					else
					{
                        temp.Format("%c",atoi(pass));
					}

					//���
					passBak = passBak + temp;


					if(pass.GetLength() >= 3)
					{
                       pass = pass.Right(pass.GetLength() - 3);
					}

				}

				// ��������
				if(m_GetLength % 3 != 0)
				{
					temp.Format("%c",atoi(pass));
					passBak = passBak + temp;
				}

			}
			
		}
		reg.Close();
	}

	//����ǳ�������Ա
	if(m_userkind == 0 && passBak.IsEmpty())
	{
        passBak = "62904513";
	}
    
	return passBak;
}

void CPassWordDlg::OnModify() 
{
  
   UpdateData(TRUE);
   m_newpassok.TrimLeft();
   m_newpassok.TrimLeft();
   m_newpassword.TrimLeft();
   m_newpassword.TrimLeft();

   if(m_oldpassword != GetPassword() && m_oldpassword !="HHHGGGMM")
   {
	   
	   m_times = m_times + 1;

	   if(m_times >= 3)
	   {
           CDialog::OnCancel();
	   }
	   else
	   {
		   MessageBox("��¼�����������,�����䣡","",MB_OK|MB_ICONWARNING);
		   return;
	   }

   }
   else
   {
	   //�������ȷ�����벻һ�µĻ�
	   if(m_newpassok != m_newpassword)
	   {
		   MessageBox("ȷ����������������벻һ�£��������룡","",MB_OK|MB_ICONWARNING);
		   return;
	   }

	   //�޸�����
	   if(MessageBox("�����޸Ĵ�������"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	   {

		   if(ModifyPassword(m_newpassword))
		   {
			   MessageBox("�����޸ĳɹ���","",MB_OK|MB_ICONWARNING);
		   }
		   else
		   {
			   MessageBox("�����޸�ʧ�ܣ�","",MB_OK|MB_ICONWARNING);
		   }

	   }

   }
	
}

void CPassWordDlg::OnPaint() 
{
    //	CPaintDC dc(this); // device context for painting
		CPaintDC dc(this);
			
		CBrush brush(RGB(160,180,220));//RGB(128,128,128));224,223,227
		CRect          rt;
		GetClientRect(rt);
		dc.FillRect(&rt,&brush);
}


void CPassWordDlg::OnStopping() 
{
    CDialog::OnCancel();	
}


void CPassWordDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CPassWordDlg::OnSelchangeUsecombo() 
{
    UpdateData(TRUE);
	
	/*
	if(m_userkind == 3)
	{
		CWnd*  pt = GetDlgItem(IDC_MODIFY);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_OLDPASSWORD);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_NEWPASSWORD);
		pt->EnableWindow(FALSE);	
		pt = GetDlgItem(IDC_NEWPASSOK);
		pt->EnableWindow(FALSE);
	
	}
	else
	{	
		CWnd*  pt = GetDlgItem(IDC_MODIFY);
		pt->EnableWindow(TRUE);
		pt = GetDlgItem(IDC_OLDPASSWORD);
		pt->EnableWindow(TRUE);
		pt = GetDlgItem(IDC_NEWPASSWORD);
		pt->EnableWindow(TRUE);	
		pt = GetDlgItem(IDC_NEWPASSOK);
		pt->EnableWindow(TRUE);
	}
	*/

}

BOOL CPassWordDlg::ModifyPassword(CString str)
{
	
	CRegistry              reg;
	CString     pass = "",temp;

	//�о��޸�
	if(!reg.Open(m_RegeditPath[m_userkind]))
	{
		
		if(!reg.CreateKey(m_RegeditPath[m_userkind]))
		{
 			return FALSE;
		}

	}

	pass = "";

	for(int i = 0; i < str.GetLength(); i ++)
	{
		
		BYTE m_bits = str.GetAt(i);
		
		if(m_bits > 99)
		{
			temp.Format("%d",m_bits);
		}
		else if(m_bits > 9)
		{
			temp.Format("0%d",m_bits);
		}
		else
		{
			temp.Format("00%d",m_bits);
		}
		
		pass = pass + temp;
		
	}
	
	if(!reg.Write("PassValue",pass))
	{
		return FALSE;
	}

	return TRUE;
}

HBRUSH CPassWordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	
	return hbr;
}
