// StationCommun.cpp : implementation file
//

#include "stdafx.h"

#include "StationCommunDlg.h"


#include "IFRMView.h"
#include "PhoneDlg.h"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationCommun dialog
//MultiByteToWideChar IsTextUnicode

CStationCommunDlg::CStationCommunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStationCommunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStationCommun)
	m_Port       =   2500;
	m_telephone  = _T("");
	m_AutoAnswer =  FALSE;
	m_IfVoice    =   TRUE;
	//}}AFX_DATA_INIT
}


void CStationCommunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStationCommun)
	DDX_Control(pDX, IDC_PHONESELECT, m_PhoneSelect);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_STOPCOMBO, m_comstop);
	DDX_Control(pDX, IDC_DATACOMBO, m_comdata);
	DDX_Control(pDX, IDC_CHECKCOMBOX, m_comcheck);
	DDX_Control(pDX, IDC_COMBOPORT, m_comboport);
	DDX_Control(pDX, IDC_COMBOBIT, m_combobit);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Control(pDX, IDC_SSTAB, m_maintab);
	DDX_CBString(pDX, IDC_PHONESELECT, m_telephone);
	DDX_Check(pDX, IDC_AUTODIAL, m_AutoAnswer);
	DDX_Check(pDX, IDC_NOVOICE, m_IfVoice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStationCommunDlg, CDialog)
	//{{AFX_MSG_MAP(CStationCommun)
	ON_NOTIFY(NM_DBLCLK, IDC_COMPUTERS, OnDblclkComputers)
	ON_BN_CLICKED(IDC_NETSEARCH, OnNetsearch)
	ON_BN_CLICKED(IDC_REFRESHS, OnRefreshs)
	ON_BN_CLICKED(IDC_NETDELETE, OnNetdelete)
	ON_BN_CLICKED(IDC_DELETEPHONE, OnDeletephone)
	ON_BN_CLICKED(IDC_ADDPHONE, OnAddphone)
	ON_BN_CLICKED(IDC_AUTODIAL, OnAutodial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationCommun message handlers

BOOL CStationCommunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString         portstr;

	//����ΪĬ��
	ShowButton(0);

	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_MODEM);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);

	//��ʼ�˿�
	CIFRMView* pview   = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
  	m_comboport.ResetContent();

	for(int i = 0 ; i < 10 ; i ++)
	{
	   //�ڶ�����Ϊ�����ܱ��վվ�ܱ�ר�� 485  
       if(pview->Ports[i] == TRUE )
	   {
		   
		    portstr.Format("COM%d",i + 1);   
		   	//TCP/IP
		 	//TRUE ���վ�汾  FALSE��ְ�
			if(m_WhichKind)
			{
				if( i != 1)
				{
			       m_comboport.AddString(portstr);
				}
			}
			else
			{
				//��ְ�
                m_comboport.AddString(portstr);
			}
	   }

	}

	//�õ���ǰ���õĲ���
	GetComInfoParameter();
    
	//�õ��绰�κ���Ϣ
	GetAllPhoneInfo();

	//�õ�������ַ
	GetLocalAddress();
	
	//��ʼ������
    GetAllIpAddress();
	//InitializeNet();

    CenterWindow();
	
	 //����ͼ��
	CBitmap *Computer = new    CBitmap;
	Computer->LoadBitmap(IDB_COMPUTER);
	m_imageList.Create(16, 16, ILC_COLOR16, 2, 2);
	m_imageList.Add(Computer, RGB(0, 0, 0,));
	delete Computer;

	UpdateData(FALSE);
	
	
	//TCP/IP
	if(m_PhoneSelect.GetCount() > 0)
	{
	
		m_PhoneSelect.SetCurSel(0);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStationCommunDlg::OnOK() 
{

	UpdateData(TRUE);
    CString    ComStr;
	int k      =    0;
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	//����������
    pview->m_sendkind = m_maintab.GetTab();
	
	//����Ǵ��ڻ�κ�
	if(m_maintab.GetTab() == 0 || m_maintab.GetTab() == 1)
	{
		
		if(m_comboport.GetCurSel() != CB_ERR)
		{
			//�����Ŵ�0��ʼ��
			m_comboport.GetLBText(m_comboport.GetCurSel(), ComStr);
		}
		else
		{
			MessageBox("����ѡ�����","����",MB_OK|MB_ICONWARNING);
			return;
		} 
		
		k = ComStr.Find("M");
		if(k != -1)
		{
			k = atoi(ComStr.Right(ComStr.GetLength()- k - 1));
		}
		else
		{
			MessageBox("����ѡ�����","����",MB_OK|MB_ICONWARNING);
			return;
		}

	}
	
	switch(m_maintab.GetTab())
	{
	case 0:	
		{
			//����
			//��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
			//���ø��ֲ���m_comboport.GetCurSel()
		   	pview->OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
    	  	
			//����ֲ���
			SaveComInfoParameter();
			break;
		}
	case 1:	
		{
	        //�绰����
			//TRUE ���վ�汾  FALSE��ְ�
			//���ø��ֲ���
			pview->OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
			
			if(m_WhichKind)
			{
				//�Զ�Ӧ��,���û�������򷵻�
				if(!pview->Connect(TRUE,m_IfVoice))
				{
					return;
				}
			}
			else
			{ 

				//�κ�
				if(!m_telephone.IsEmpty())
				{

					int k = m_telephone.Find("��");
        			m_telephone = m_telephone.Left(k);
					m_telephone.TrimLeft();
                    m_telephone.TrimRight();
					pview->Dial(m_telephone,m_IfVoice);
				  //pview->Dial(m_telephone,FALSE);
				}
				else
				{
					MessageBox("�κŵ绰���벻��Ϊ��!","����",MB_OK|MB_ICONWARNING);
					return;
				}
						
			}

			//����ֲ���
			SaveComInfoParameter();
			break;
		}
	case 2:	
		{
			//TCP/IP
		 	//TRUE ���վ�汾  FALSE��ְ�
			if(m_WhichKind)
			{
		       
				//���� TCP �����
				CString LocalHostAddress;	
				CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_LOCALADDRESS);
				IPAddr->GetWindowText(LocalHostAddress);
				LocalHostAddress.TrimLeft();
				LocalHostAddress.TrimRight();

				//��ַ��Ϊ�ջ�"0.0.0.0"
				if(!LocalHostAddress.IsEmpty() && LocalHostAddress != "0.0.0.0")
				{
					pview->SetLocalServer(LocalHostAddress, m_Port);
				}
				else
				{	
					MessageBox("�������ñ�����ַ!","����",MB_OK|MB_ICONWARNING);
					return;
				}

			}
			else
			{
				
				CString RemoteHostAddress;	
				CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
				IPAddr->GetWindowText(RemoteHostAddress);
				RemoteHostAddress.TrimLeft();
				RemoteHostAddress.TrimRight();

				//��ַ��Ϊ�ջ�"0.0.0.0"
				if(!RemoteHostAddress.IsEmpty() && RemoteHostAddress != "0.0.0.0")
				{
					//���� TCP �ͻ���
					RemoteHostAddress.TrimLeft();
					RemoteHostAddress.TrimRight();
			
					pview->SettcpClient(RemoteHostAddress, m_Port);
					
					//IP��ַ�����ַ
					AddAddressToTable();

				}
				else
				{
					MessageBox("����ѡ��������ַ!","����",MB_OK|MB_ICONWARNING);
					return;
				}
			
			}
			break;

		}

	}

	CDialog::OnOK();
}

void CStationCommunDlg::GetComInfoParameter()
{
	CString      str;
	CDatabase     db;
	CString   strSql;
	CString strValue;
	str        =  "";
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
       	strSql = "SELECT count(*) FROM TB_COMINFORMATION";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();
		
		if(fields <= 0)
		{
			
			m_combobit.SetCurSel(9);
			m_comboport.SetCurSel(0);
			m_comstop.SetCurSel(0);
			m_comdata.SetCurSel(4);
			m_comcheck.SetCurSel(0);
			m_AutoAnswer =    FALSE;
			
		}
		else
		{
			strSql = "SELECT * FROM TB_COMINFORMATION";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//�õ��ֶθ���
			short nFields = rs.GetODBCFieldCount();
			
			for(int i = 0; i < nFields; i++)
			{
				rs.GetFieldValue((short)i,str);
				str.TrimLeft();
				str.TrimRight();
				
				switch(i)
				{
				case 0:
					{
						//����
						if(m_comboport.GetCount() > 0)
						{
							
							//���
							if(atoi(str) > m_comboport.GetCount())
							{
								m_comboport.SetCurSel(0);
							}
							else
							{
								m_comboport.SetCurSel(atoi(str));
							}
							
						}
						break;
					}
				case 1:
					{
						//������
						m_combobit.SetCurSel(atoi(str));
						break;
					}
				case 2:
					{
						//����λ
						m_comcheck.SetCurSel(atoi(str));
						break;
					}
				case 3:
					{
						//����λ
						m_comdata.SetCurSel(atoi(str));
						break;
					}
				case 4:
					{
						//ֹͣλ
						m_comstop.SetCurSel(atoi(str));
						break;
					}
				case 5:
					{
						//�Զ�Ӧ��
						m_AutoAnswer = atoi(str);
						break;
					}
					
				}
				
				
			}
			
			//�ر����ݿ�
			rs.Close( );
			db.Close( );
			
		}
	
	}

}

//���������ھ�
void CStationCommunDlg::InitializeNet()
{
	
	CString      strTemp;	
	int    item    =   0;
	struct hostent *host;
	struct in_addr  *ptr;
	
	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);

	//���б���������
	List->DeleteAllItems( );       //ɾ���б�����������(��)
	while (List->DeleteColumn(0)); //ɾ���б���������

	// ����list�ؼ���ʽ	
    List->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	

	List->SetImageList(&m_imageList, LVSIL_SMALL);
	
	//д���б���
	List->InsertColumn(0, "IP��ַ", LVCFMT_LEFT, 170);
	List->InsertColumn(1, "���������", LVCFMT_LEFT, 170);

	//�ҳ���������Ƽ�IP��ַ
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);	
	DWORD dwScope = RESOURCE_CONTEXT;
	NETRESOURCE *NetResource = NULL;
	HANDLE hEnum; 
	WNetOpenEnum(dwScope, NULL, NULL, NULL, &hEnum);

	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1),&wsaData);

	if (hEnum)
	{
		DWORD Count = 0xFFFFFFFF;
		DWORD BufferSize = 2048;
		LPVOID Buffer  =  new   char[2048];
		WNetEnumResource(hEnum, &Count, Buffer, &BufferSize);
		NetResource = (NETRESOURCE*)Buffer;
		char               szHostName[200];
		for (unsigned int i = 0; i < BufferSize/sizeof(NETRESOURCE); i++, NetResource++)
		{

			if (NetResource->dwUsage == RESOURCEUSAGE_CONTAINER && NetResource->dwType == RESOURCETYPE_ANY)
			{

				if (NetResource->lpRemoteName)
				{
					CString strFullName = NetResource->lpRemoteName;
					char buf[512];
					if ( 0 == strFullName.Left(2).Compare("\\\\"))
					strFullName = strFullName.Right(strFullName.GetLength()-2);
					gethostname(szHostName, strlen( szHostName ));
					host = gethostbyname(strFullName);
					if (!host) continue;
					ptr = (struct in_addr *) host->h_addr_list[0];
					sprintf(buf, "%d.%d.%d.%d", ptr->S_un.S_un_b.s_b1, 
						ptr->S_un.S_un_b.s_b2, ptr->S_un.S_un_b.s_b3, ptr->S_un.S_un_b.s_b4);
					List->InsertItem(item++, buf, 0);
					List->SetItemText(item - 1, 1, strFullName);
				//	List->SetItemText(item - 1, 2, NetResource->lpComment);

				}

			}

		}
		delete Buffer;
		WNetCloseEnum(hEnum);
	}
	WSACleanup();
}


void CStationCommunDlg::OnDblclkComputers(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CEdit *Host = (CEdit *)GetDlgItem(IDC_HOST);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	int mark = List->GetSelectionMark();
	if(mark < 0)
	{
		return;
	}

	char buf[512];
	List->GetItemText(mark, 0, buf, sizeof(buf));
	IPAddr->SetWindowText(buf);
	List->GetItemText(mark, 1, buf, sizeof(buf));
	Host->SetWindowText(buf);	
	*pResult = 0;
}



void CStationCommunDlg::GetLocalAddress()
{
	
	struct hostent *host;
	struct  in_addr *ptr;
	char        buf[512];
	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_LOCALADDRESS);


	GetDlgItem(IDC_HOST)->GetWindowText(buf, sizeof(buf));
	host = gethostbyname(buf);
	
	if (!host) 
	{
		IPAddr->SetWindowText("0.0.0.0");
		return;
	}
	else
	{
		ptr = (struct in_addr *) host->h_addr_list[0];
		sprintf(buf, "%d.%d.%d.%d", ptr->S_un.S_un_b.s_b1, 
			ptr->S_un.S_un_b.s_b2, ptr->S_un.S_un_b.s_b3, ptr->S_un.S_un_b.s_b4);
		IPAddr->SetWindowText(buf);	
	}

}

BEGIN_EVENTSINK_MAP(CStationCommunDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CStationCommun)
	ON_EVENT(CStationCommunDlg, IDC_SSTAB, -600 /* Click */, OnClickSstab, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CStationCommunDlg::OnClickSstab(short PreviousTab) 
{
   //����ΪĬ��
   ShowButton(m_maintab.GetTab());
}


//��κź���Ͷ˿ڲ���
void CStationCommunDlg::SaveComInfoParameter()
{
	CDatabase  dbs;
	CString StrSql;

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	{	
	
		StrSql = "DELETE FROM TB_COMINFORMATION";
		dbs.ExecuteSQL(StrSql);
		StrSql.Format("INSERT INTO TB_COMINFORMATION(COMINFORMATION_COM,COMINFORMATION_BITS,COMINFORMATION_CHECKBIT,COMINFORMATION_DATABIT,COMINFORMATION_STOPBIT,COMINFORMATION_AUTOREPLY) VALUES (%d,%d,%d,%d,%d,%d)",m_comboport.GetCurSel(),m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel(),m_AutoAnswer);
		dbs.ExecuteSQL(StrSql);
		dbs.Close();
	}
	   
}


void CStationCommunDlg::OnNetsearch() 
{
	//���������ھ�
	InitializeNet();
	CWnd* pt = GetDlgItem(IDC_NETDELETE);
	pt->EnableWindow(FALSE);
}

//�õ����ļ��д��IP��ַ
void CStationCommunDlg::GetAllIpAddress()
{

	CDatabase                        db;
	CString                      strSql;
	CString strValue,HostName,IPAddrStr;
	int  item             =           0;

	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);

	//���б���������
	List->DeleteAllItems( );       //ɾ���б�����������(��)
	while (List->DeleteColumn(0)); //ɾ���б���������

	List->SetImageList(&m_imageList, LVSIL_SMALL);
	
	//д���б���
	List->InsertColumn(0, "IP��ַ", LVCFMT_LEFT, 170);
	List->InsertColumn(1, "���������", LVCFMT_LEFT, 170);

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
       	strSql = "SELECT count(*) FROM TB_IP";
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();

	    if(fields > 0)
		{

			strSql = "SELECT * FROM TB_IP";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//���û���Ϣ
			for(int j = 0;j < fields; j++)
			{
                
				//��ַȥ�ո�
				rs.GetFieldValue((short)0,IPAddrStr);
                
				IPAddrStr.TrimLeft();
				IPAddrStr.TrimRight();
                
				//����ȥ�ո�
				rs.GetFieldValue((short)1,HostName);
               	HostName.TrimLeft();
				HostName.TrimRight();
					
				List->InsertItem(item++, IPAddrStr, 0);
				List->SetItemText(item-1, 1, HostName);		

				//���»�һ����¼
				rs.MoveNext();

			}
			
			//�ر����ݿ�
		    rs.Close( );

		}
		db.Close( );
	}

}

//�õ����ļ��д��IP��ַ
void CStationCommunDlg::OnRefreshs() 
{
    GetAllIpAddress();
	CWnd* pt = GetDlgItem(IDC_NETDELETE);
	pt->EnableWindow(TRUE);
}

void CStationCommunDlg::OnNetdelete() 
{   
    char buf[20];
   	CString      IPAddrStr,SqlStr;
	
	

	CListCtrl *List = (CListCtrl *)GetDlgItem(IDC_COMPUTERS);
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	int mark = List->GetSelectionMark();
	if(mark < 0 )
	{
		return;
	}

	List->GetItemText(mark, 0, buf, sizeof(buf));
	IPAddrStr = buf;

	IPAddrStr.TrimLeft();
	IPAddrStr.TrimRight();

    if(MessageBox("����ɾ���б��е�" + IPAddrStr + "IP��ַ��","ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		//�д�IP��ַ,��ɾ���˼�¼
		SqlStr.Format("DELETE FROM TB_IP WHERE IP_ADDRESS='%s'",IPAddrStr);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
		
		//�õ����ļ��д��IP��ַ
		GetAllIpAddress();  
	}

}

//�õ��绰�κ���Ϣ
void CStationCommunDlg::GetAllPhoneInfo()
{
	//�����ݿ�
	CDatabase           db;
	CString         strSql;
	CString       strValue;
	CString fieldname = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//��CRecordset����
		CRecordset rs(&db );
	    strSql = "SELECT count(*) FROM TB_PHONE";
			
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();
		
		//ɾ��ԭ�����б�����
		m_PhoneSelect.ResetContent();

		if(fields  > 0)
		{
      	    strSql = "SELECT PHONE_NO,PHONE_NAME FROM TB_PHONE";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//���û���Ϣ
			for(int j = 0;j < fields; j++)
			{
				
				//�绰����
				rs.GetFieldValue((short)0,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
				strSql = strValue;	
				rs.GetFieldValue((short)1,strValue);
				strValue.TrimLeft();
				strValue.TrimRight();
				strSql = strSql + "��" + strValue;
				
				//�����б��
				m_PhoneSelect.AddString(strSql);
						
				//���»�һ����¼
				rs.MoveNext();

			}
		
			//�ر����ݿ�
		    rs.Close( );
		
		}
		
		//�����������0
		if(m_PhoneSelect.GetCount() > 0)
		{
			m_PhoneSelect.SetCurSel(0);
		}

		db.Close( );
	}

}


//ɾ���绰��¼
void CStationCommunDlg::OnDeletephone() 
{
	CString m_Phones,SqlStr;
	int                   k;
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(m_PhoneSelect.GetCurSel() != CB_ERR)
	{
		m_PhoneSelect.GetLBText(m_PhoneSelect.GetCurSel(),m_Phones); 
        k = m_Phones.Find("��");
        
		m_Phones = m_Phones.Left(k);
		
		if(MessageBox("����ɾ���б��е绰�Ż�[" + m_Phones + "]��","ѯ��",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
		   return;
		}

		//�д˵绰����,��ɾ���˼�¼
		SqlStr.Format("DELETE FROM TB_PHONE WHERE RTRIM(PHONE_NO)='%s'",m_Phones);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr); 

		//�õ��绰�κ���Ϣ
        GetAllPhoneInfo();
	}
	
}

void CStationCommunDlg::ShowButton(short kinds)
{	
	
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
    switch(kinds)
	{
	case 0:	
		{
			//����
		    CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
						
			//�绰
			pwnd = GetDlgItem(IDC_TELEPHONETXT);
			pwnd->ShowWindow(SW_HIDE);
            pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOST);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOSTTXT);
			pwnd->ShowWindow(SW_HIDE);
			
			pwnd = GetDlgItem(IDC_NETSEARCH);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_NETDELETE);
			pwnd->ShowWindow(SW_HIDE);
         	pwnd = GetDlgItem(IDC_REFRESHS);
			pwnd->ShowWindow(SW_HIDE);

	        pwnd = GetDlgItem(IDC_PHONESELECT);
			pwnd->ShowWindow(SW_HIDE); 
			pwnd = GetDlgItem(IDC_DELETEPHONE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_ADDPHONE);
			pwnd->ShowWindow(SW_HIDE);
			//�Զ�Ӧ�����
			pwnd = GetDlgItem(IDC_AUTODIAL);
			pwnd->ShowWindow(SW_HIDE);

	        pwnd = GetDlgItem(IDOK);
			pwnd->SetWindowText("����");
	       	break;
		}
	case 1:	
		{
			//�绰�κ�
			CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_SHOW); 
			pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_SHOW);
			
            //TRUE ���վ�汾  FALSE��ְ�
	        //�绰����
	        if(!m_WhichKind)
			{
				pwnd = GetDlgItem(IDC_TELEPHONETXT);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_PHONESELECT);
				pwnd->ShowWindow(SW_SHOW); 
				pwnd = GetDlgItem(IDC_DELETEPHONE);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_ADDPHONE);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("�κ�");
				//�Զ�Ӧ�����
				pwnd = GetDlgItem(IDC_AUTODIAL);
			    pwnd->ShowWindow(SW_HIDE);
               
			}
			else
			{ 
				pwnd = GetDlgItem(IDC_TELEPHONETXT);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_PHONESELECT);
				pwnd->ShowWindow(SW_HIDE); 
				pwnd = GetDlgItem(IDC_DELETEPHONE);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_ADDPHONE);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("�Զ�Ӧ��");
				//�Զ�Ӧ�����
				pwnd = GetDlgItem(IDC_AUTODIAL);
			    pwnd->ShowWindow(SW_SHOW);	
			}
	        
			//�κ�
		    if(!pview->m_Com.GetCDHolding())
			{
				pwnd = GetDlgItem(IDOK);
				pwnd->EnableWindow(TRUE);
			}
			else
			{
				pwnd = GetDlgItem(IDOK);
				pwnd->EnableWindow(FALSE);
			}

			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESS);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_IPADDRESSTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOST);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_HOSTTXT);
			pwnd->ShowWindow(SW_HIDE);

			pwnd = GetDlgItem(IDC_NETSEARCH);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_NETDELETE);
			pwnd->ShowWindow(SW_HIDE);
         	pwnd = GetDlgItem(IDC_REFRESHS);
			pwnd->ShowWindow(SW_HIDE);
			break;
		}
	case 2:	
		{
			//TCP/IP
		 	CWnd* pwnd = GetDlgItem(IDC_COMBOPORT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOPORTTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOBIT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMBOBITTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_CHECKCOMBOX);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_CHECKCOMBOXTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_DATACOMBO);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_DATACOMBOTXT);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_STOPCOMBO);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_STOPCOMBOTXT);
			pwnd->ShowWindow(SW_HIDE);
						
			//�绰
			pwnd = GetDlgItem(IDC_TELEPHONETXT);
			pwnd->ShowWindow(SW_HIDE);
            pwnd = GetDlgItem(IDC_NOVOICE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_COMPUTERS);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_LOCALADDRESSTXT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_LOCALADDRESS);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_PORT);
			pwnd->ShowWindow(SW_SHOW);
			pwnd = GetDlgItem(IDC_PORTTXT);
			pwnd->ShowWindow(SW_SHOW);
		
			pwnd = GetDlgItem(IDC_PHONESELECT);
			pwnd->ShowWindow(SW_HIDE); 

			pwnd = GetDlgItem(IDC_DELETEPHONE);
			pwnd->ShowWindow(SW_HIDE);
			pwnd = GetDlgItem(IDC_ADDPHONE);
			pwnd->ShowWindow(SW_HIDE);	
			
			//�Զ�Ӧ�����
			pwnd = GetDlgItem(IDC_AUTODIAL);
			pwnd->ShowWindow(SW_HIDE);
		
			//TRUE ���վ�汾  FALSE��ְ�
	      	if(!m_WhichKind)
			{	
				pwnd = GetDlgItem(IDC_IPADDRESS);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_IPADDRESSTXT);
				pwnd->ShowWindow(SW_SHOW);

				pwnd = GetDlgItem(IDC_HOST);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_HOSTTXT);
				pwnd->ShowWindow(SW_SHOW);

				pwnd = GetDlgItem(IDC_NETSEARCH);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_NETDELETE);
				pwnd->ShowWindow(SW_SHOW);
         		pwnd = GetDlgItem(IDC_REFRESHS);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("����");
						
			}
			else
			{	
				pwnd = GetDlgItem(IDC_IPADDRESS);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_IPADDRESSTXT);
				pwnd->ShowWindow(SW_HIDE);

				pwnd = GetDlgItem(IDC_HOST);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_HOSTTXT);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDC_NETSEARCH);
				pwnd->ShowWindow(SW_SHOW);
				pwnd = GetDlgItem(IDC_NETDELETE);
				pwnd->ShowWindow(SW_HIDE);
         		pwnd = GetDlgItem(IDC_REFRESHS);
				pwnd->ShowWindow(SW_HIDE);
				pwnd = GetDlgItem(IDOK);
			    pwnd->SetWindowText("����");
		
			}
			break;
		}

	}
}



void CStationCommunDlg::AddAddressToTable()
{
	CString HostName,IPAddrStr,	SqlStr;
    
	CIFRMView* pview = (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//������
	CEdit *Host = (CEdit *)GetDlgItem(IDC_HOST);
	Host->GetWindowText(HostName);

	//Զ�̵�ַ
	CIPAddressCtrl *IPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
    IPAddr->GetWindowText(IPAddrStr);
   
	//ȥ�ո�
	IPAddrStr.TrimLeft();
	IPAddrStr.TrimRight();
    HostName.TrimLeft();
	HostName.TrimRight();

    //��ѯ����,�Ƿ��д˼�¼	
	SqlStr.Format("IP_ADDRESS='%s'",IPAddrStr);

	if(CDataBaseInstance::GetAllRecordsCount("TB_IP", SqlStr) < 1)
	{
		//û�д�IP��ַ,������¼								
		SqlStr.Format("INSERT INTO TB_IP(IP_ADDRESS,IP_COMPUTER) VALUES ('%s','%s')",IPAddrStr,HostName);

	}
	else
	{	
		//�д�IP��ַ,�򸲸Ǽ�¼
		SqlStr.Format("UPDATE TB_IP SET IP_ADDRESS = '%s',IP_COMPUTER='%s' WHERE IP_ADDRESS='%s'",IPAddrStr,HostName,IPAddrStr);
	}
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	
}

void CStationCommunDlg::OnAddphone() 
{
	CPhoneDlg  DLG;
	DLG.DoModal();
	//�õ��绰��Ϣ
	GetAllPhoneInfo();	
}

void CStationCommunDlg::OnAutodial() 
{
	CString    StrSql;
	m_AutoAnswer = !m_AutoAnswer;
	UpdateData(FALSE);
	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_COMINFORMATION","ALL") > 0)
	{
		StrSql.Format("UPDATE TB_COMINFORMATION SET COMINFORMATION_AUTOREPLY=%d",m_AutoAnswer);
		CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	}
}
