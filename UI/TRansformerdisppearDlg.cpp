// TRansformerdisppear.cpp : implementation file
//

#include "stdafx.h"

#include "TRansformerdisppearDlg.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRansformerdisppear dialog


CTRansformerdisppearDlg::CTRansformerdisppearDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTRansformerdisppearDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTRansformerdisppear)
	m_IsDaYongFu = FALSE;
	m_IsBT     =  TRUE;
	m_IsJuMin  = FALSE;
	//}}AFX_DATA_INIT
}


void CTRansformerdisppearDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTRansformerdisppear)
	DDX_Control(pDX, IDC_DATATREE, m_datatree);
	DDX_Check(pDX, IDC_CHECK2, m_IsDaYongFu);
	DDX_Check(pDX, IDC_CHECK3, m_IsBT);
	DDX_Check(pDX, IDC_CHECK1, m_IsJuMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTRansformerdisppearDlg, CDialog)
	//{{AFX_MSG_MAP(CTRansformerdisppear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTRansformerdisppear message handlers
//��ʼ�����ؼ�
void CTRansformerdisppearDlg::Initialize()
{

	HICON             hicon[14];
	CDatabase                db;
	CString     str,strs,strSql; 
	CString    strtemp1,strtemp2;
 
    //ɾ�����е���
	m_datatree.DeleteAllItems();

	//ɾ��ͼ���б�
	m_imageList.DeleteImageList();
    m_imgState.DeleteImageList();
	
	m_imageList.Create(28,28,ILC_COLOR32,8,8);
 	m_imageList.SetBkColor(RGB(255,255,255));//RGB(128,128,128));//RGB(0xFF, 0xFF, 0xE0));//RGB(255,255,255));//

	//��ģ�Ի���
	CProgressDlg pDialog(ID_PROGRESSDLGTITLE);
	pDialog.Create(NULL);

    hicon[ 0]  = AfxGetApp()->LoadIcon(IDI_COMPANY);            //��˾
    hicon[ 1]  = AfxGetApp()->LoadIcon(IDI_SUB);                //���վ
	hicon[ 2]  = AfxGetApp()->LoadIcon(IDI_LINE);               //��·
    hicon[ 3]  = AfxGetApp()->LoadIcon(IDI_TRANS);              //��̨
    hicon[ 4]  = AfxGetApp()->LoadIcon(IDI_MODULE);             //ģ��
    hicon[ 5]  = AfxGetApp()->LoadIcon(IDI_BIGMODULE);          //���û�  
	hicon[ 6]  = AfxGetApp()->LoadIcon(IDI_SUBTOTALMODULE);     //̨�����ܱ�
    hicon[ 7]  = AfxGetApp()->LoadIcon(IDI_SUBSALEMODULE);      //��̨�ֱ�
  	hicon[ 8]  = AfxGetApp()->LoadIcon(IDI_ZSUBTOTALMODULE);    //̨ר���ܱ�
	hicon[ 9]  = AfxGetApp()->LoadIcon(IDI_COMPENSATEMODULE);   //�޹�������
    hicon[10]  = AfxGetApp()->LoadIcon(IDI_LSALEMODULE);        //��·�۵��
	hicon[11]  = AfxGetApp()->LoadIcon(IDI_LTOTALMODULE);       //��·�����
	hicon[12]  = AfxGetApp()->LoadIcon(IDI_ZSALEMODULE);        //��վ�����
	hicon[13]  = AfxGetApp()->LoadIcon(IDI_ZTOLTALMODULE);      //��վվ�ܱ�

	//����ͼ��
	for( int i = 0; i < 14;i ++)
	{
        m_imageList.Add(hicon[i]);
	}
	

	m_imgState.Create(IDB_BITMAP_STATE,13, 1, RGB(0xFF, 0xFF, 0xE0));//RGB(0xFF, 0xFF, 0xE0)RGB(255,255,255));

	m_datatree.SetImageList(&m_imageList,TVSIL_NORMAL);//TVSIL_SMALL
    
	//m_datatree.SetBkColor(RGB(128,128,128));
	m_datatree.SetBkColor(RGB(255,255,255));//RGB(128,128,128));//RGB(0xFF, 0xFF, 0xE0));

	m_datatree.SetImageList(&m_imgState,TVSIL_STATE);

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{

		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
      	db.Close( );
		
		//��˾����ʼ
	    CDaoRecordset m_CompanySet(m_pDatabase);
	   	m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT USER_COMPANY from TB_USER order by USER_COMPANY"));
      
		//Ѱ�����������ļ�¼
      	while (!m_CompanySet.IsEOF())
		{
	 		
			HTREEITEM hFirst = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0)),0,0,TVI_ROOT,TVI_LAST);
		//	m_datatree.SetItemState( hFirst, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK );
		    
			//���������ʼ 
    		 CDaoRecordset m_SubStaitonSet(m_pDatabase);
			
			 strSql.Format("SELECT DISTINCT USER_STATIONNAME from TB_USER WHERE USER_COMPANY='%s'",V_I4(&m_CompanySet.GetFieldValue(0)));

			 m_SubStaitonSet.Open(dbOpenSnapshot,strSql);
			 
			 while (!m_SubStaitonSet.IsEOF())
			 {
				 
				  HTREEITEM hSecond = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_SubStaitonSet.GetFieldValue(0)),1,1,hFirst,TVI_LAST);
				  {
                      
					  //�ӱ��վ�����
                      strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=9  AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
				 	  AddAllKindAmmeter(strSql,hSecond,13);
					  
					  //�ӱ��վ�۵��
					  strSql.Format("USER_COMPANY='%s' AND USER_AMMETERKIND=8  AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
					  AddAllKindAmmeter(strSql,hSecond,12); 
					  
										  
					  //��·����ʼ
					  CDaoRecordset m_LinesSet(m_pDatabase);
					  strSql.Format("Select DISTINCT USER_LINENAME from TB_USER WHERE USER_COMPANY='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
					  m_LinesSet.Open(dbOpenSnapshot,strSql);

					  while (!m_LinesSet.IsEOF())
					  {
						  
						  HTREEITEM hThird = m_datatree.InsertItem((LPTSTR)(LPCTSTR)V_I4(&m_LinesSet.GetFieldValue(0)),2,2,hSecond,TVI_LAST);
						  {
							  
								  //������·�ܱ�
								  strSql.Format("USER_AMMETERKIND=7  AND USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  AddAllKindAmmeter(strSql,hThird,11);
								  
								  //������·�۵��
								  strSql.Format("USER_AMMETERKIND=6  AND USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  AddAllKindAmmeter(strSql,hThird,10);

								  //��̨����ʼ
								  CDaoRecordset m_DeviceSet(m_pDatabase);
								  strSql.Format("Select DISTINCT USER_TRANSFORMERNO from TB_USER WHERE USER_COMPANY='%s' AND USER_LINENAME='%s' AND USER_STATIONNAME='%s'",V_I4(&m_CompanySet.GetFieldValue(0)),V_I4(&m_LinesSet.GetFieldValue(0)),V_I4(&m_SubStaitonSet.GetFieldValue(0)));
								  m_DeviceSet.Open(dbOpenSnapshot,strSql);

								  while (!m_DeviceSet.IsEOF())
								  {
									  
									  strSql.Format("TRANSFORMER_NO='%s'",V_I4(&m_DeviceSet.GetFieldValue(0)));
									  strSql = "";
									  str    = (LPTSTR)(LPCTSTR)V_I4(&m_DeviceSet.GetFieldValue(0));
									  str.TrimLeft();
									  str.TrimRight();
									  
									  if(str.GetLength() == 1)
									  {
										  str = " " +str;
									  }
									  
									  strSql = str  + strSql ;
									  
									  //��ģ��
									  HTREEITEM hFourth = m_datatree.InsertItem(strSql,3,3,hThird,TVI_LAST);
									  
									  m_DeviceSet.MoveNext();
									  //m_datatree.Expand(hFourth,TVE_EXPAND);
									  
								  }
								  m_DeviceSet.Close();
								  //��̨��
	 
							  }
							  m_LinesSet.MoveNext();
							//m_datatree.Expand(hThird,TVE_EXPAND);
								  
						 }
						 m_LinesSet.Close();
     					 //��·����

				  }
				  m_SubStaitonSet.MoveNext();
//				  m_datatree.Expand(hSecond,TVE_EXPAND); 

			 }
			 m_SubStaitonSet.Close();
			//��������� 


			m_CompanySet.MoveNext();
//			m_datatree.Expand(hFirst,TVE_EXPAND); 
		}
		m_CompanySet.Close();	
    	//��˾����

		delete m_pDatabase;
		m_pDatabase = NULL;

    }

}


void CTRansformerdisppearDlg::AddAllKindAmmeter(CString condtion,HTREEITEM Item,int n)
{

	//�����ݿ�
	CDatabase            db;
	CString      str,strSql;
	
	//��¼����
	long    fields    = 0;
	
	switch(n)
	{
	case 5:
		{
			str = "�����û���";
			break;
		}
	case 6:
		{   
			str = "��̨�����ܱ�";
			break;
		}
	case 7:
		{   
			str = "��̨��ֱ�";
			break;
		}
	case 8:
		{   
			str = "��̨ר���ܱ�";
			break;
		}
	case 9:
		{   
			str = "���޹�������";
			break;
		}
	case 10:
		{
			str = "�����۵��";
			break;
		}	
	case 11:
		{
			str = "���߹����";
			break;
		}
	case 12:
		{
			str = "��վ�۵��";
			break;
		}
	case 13:
		{
			str = "��վ�����";
			break;
		}
	}

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		strSql.Format("SELECT USER_MODULENO FROM TB_USER WHERE %s",condtion);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		while(!rs.IsEOF())
		{
			
			rs.GetFieldValue((short)0,strSql);
			
			strSql.TrimLeft();
			strSql.TrimRight();
			
			if(!strSql.IsEmpty())
			{
				strSql = strSql + str;
			}
			
			//�������б�
			m_datatree.InsertItem(strSql,n,n,Item,TVI_LAST);
			
			//���»�һ����¼
			rs.MoveNext();
		}
	
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}
	
}



BOOL CTRansformerdisppearDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//��ʼ�����ؼ�
	Initialize();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//�õ�ѡ������
CString CTRansformerdisppearDlg::SelectCondition()
{  

	//��һ����˾��
	HTREEITEM               hBootItem,hFirstItem; 
	HTREEITEM hSecondItem,hThirdItem,hFourthItem;
	
	//��һ����
    CString         str1,str2,str3,str4;
	CString str5,str6,str7,str8,strtemp;
    CString                          tr;
	int                      temp,temp1;
	
	hBootItem  = m_datatree.GetRootItem();
	
	if(hBootItem == NULL)
	{
		return "";
	}
	
	//�ڶ������վ
	if(m_datatree.ItemHasChildren(hBootItem))
	{	
		hFirstItem = m_datatree.GetChildItem(hBootItem);
		
		str1 = "";
		str6 = ""; 
		
		do
		{ 
			
			//����������·��
			if(m_datatree.ItemHasChildren(hFirstItem) && (m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
			{	
				str2 = "";
				str5 = "";
				hSecondItem = m_datatree.GetChildItem(hFirstItem);
				do
				{
					
					//���ļ�����̨�ż�
					if(m_datatree.ItemHasChildren(hSecondItem) && (m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					{	
						
						str3 = "";
						str4 = "";

						hThirdItem = m_datatree.GetChildItem(hSecondItem);

					
						do
						{
							
							//���弶��ģ��ż�
							if(m_datatree.ItemHasChildren(hThirdItem) && (m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{	
								str7 = str8 = "";
								hFourthItem = m_datatree.GetChildItem(hThirdItem);
								do
								{
									if((m_datatree.GetItemState(hFourthItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
									{
										
										tr = m_datatree.GetItemText(hFourthItem);
										tr.TrimLeft();
										tr.TrimRight();
										int k = tr.Find("��"); 
										if(k != -1)
										{
											tr = tr.Left(k);
										}
										
										str8 = str8 + "USER_MODULENO="  + tr;
										
										//str8 = str8 + "USER_MODULENO="  + m_datatree.GetItemText(hFourthItem);
										
										str8.TrimRight();
										str7 = str7 + str8;
										str8 = " OR ";
										
									}
									
								}while( (hFourthItem = m_datatree.GetNextSiblingItem(hFourthItem)) != NULL );
								
							}	
							//���弶��
							
							//nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��  ��̨
							if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{
								
								tr = m_datatree.GetItemText(hThirdItem);
								tr.TrimLeft();
								tr.TrimRight();
								int k = tr.Find("��"); 
								if(k != -1)
								{
									tr = tr.Left(k);
								}
								
								/////////////
								//�õ�ͼ��������
								m_datatree.GetItemImage(hThirdItem,temp,temp1);
								
								//���������
								if(temp1 > 3)
								{
									
									//����·�Ĺ������۵��,�����Ǳ�̨����
									str4 = str4 + "(USER_MODULENO="  +  tr;
								}
								else
								{
									//�Ǳ�̨����
									str4 = str4 + "(USER_TRANSFORMERNO="  + "'" + tr + "'";
								}
								
								
								str4.TrimRight();
								str3 = str3 + str4;
								str4 = " OR ";
								
								if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
								{
									str3 =  str3 + " AND (" + str7 + "))";
								}
								else
								{
									//�õ�ͼ��������
									m_datatree.GetItemImage(hThirdItem,temp,temp1);
									
									//���������
								//	if(temp1 > 3)
									{
										str3 =  str3 + ")";
									}
								//	else
									{
								//		str3 =  str3 + " AND USER_AMMETERKIND<3)";
									}
									
								}
								
							}
							
							
						}while( (hThirdItem = m_datatree.GetNextSiblingItem(hThirdItem)) != NULL );

					
						
					 }	
					 //���ļ���
					 
					 //nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��  ��·
					 if((m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					 {
						 //�õ�ͼ��������
						 m_datatree.GetItemImage(hSecondItem,temp,temp1);
						 
						 //���������
						 if(temp1 > 3)
						 {
							 
							 //�Ǳ��վ�Ĺ������۵��,��������·����
							 strtemp.Format("%d",atol(m_datatree.GetItemText(hSecondItem)));
							 //str5 = str5 + "(USER_MODULENO="  +  strtemp;
							 str5 = str5 + "USER_MODULENO="  +  strtemp;
							 
						 }
						 else
						 {
							 //����·����
							 str5 = str5 + "(USER_LINENAME="  +  "'" + m_datatree.GetItemText(hSecondItem) + "'" ;
							 
						 }
						 
						 str5.TrimRight();
						 str2 = str2 + str5;
						 str5 = " OR "; 
						 
						 str3.TrimLeft();
						 str3.TrimRight();
						 
						 if(!str3.IsEmpty())
						 {
							 
							 if((m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
							 {
								 str2 =  str2 + " AND (" + str3 + "))";
							 }
							 else
							 {
								 str2 =  str2 + ")";
							 }
							 
							 
						 }
						 
					 }
					 
					 
				   }while( (hSecondItem = m_datatree.GetNextSiblingItem(hSecondItem)) != NULL );
						
						
				  }
				  
				  //nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��  ���վ
				  if((m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
				  {
					  
					  str6 = str6 + "(USER_STATIONNAME="  + "'" + m_datatree.GetItemText(hFirstItem) + "'";
					  str6.TrimRight();
					  str1 = str1 + str6;
					  str6 = " OR ";
					  
					  str2.TrimLeft();
					  str2.TrimRight();
					  
					  if(!str2.IsEmpty())
					  {
						  
						  if((m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) == 2)
						  {
							  str1 =  str1 + " AND (" + str2 + "))";
						  }
						  else
						  {
							  str1 = str1 + ")";
						  }
						  
					  }
					  
				  }
				  
				  //��������
				  
				  
			}while( (hFirstItem = m_datatree.GetNextSiblingItem(hFirstItem)) != NULL );
			
			
		}	
		//�ڶ�����
		
		return str1;
		
}

void CTRansformerdisppearDlg::OnOK() 
{

	UpdateData(TRUE);
	CString  strtemp;

    m_GetSubRangeStr = SelectCondition();
    m_GetSubRangeStr.TrimLeft();
	m_GetSubRangeStr.TrimRight();

	if(m_GetSubRangeStr.IsEmpty())
	{
		MessageBox("��ѡ��Ҫפ������ı�̨��"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	strtemp = "";

	if(!(m_IsBT || m_IsJuMin || m_IsDaYongFu))
	{
		MessageBox("��ѡ��פ������Ķ���"," ",MB_OK|MB_ICONWARNING);
		return;
	}

	m_GetSubNameStr = GetSelectSubName();

	
//	m_GetSubNameStr = "������Χ��\r\n" + GetSelectSubName();

//	m_GetSubNameStr = m_GetSubNameStr + "���������\r\n";

	//�����
	if(m_IsJuMin)
	{
		
		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND = 0";
		}
		else
		{
			
			strtemp = strtemp + " OR USER_AMMETERKIND = 0";
		}
		
	//	m_GetSubNameStr = m_GetSubNameStr + "�����  ";
		
	}
	
	
	//���û���
	if(m_IsDaYongFu)
	{
		
		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND = 1";
		}
		else
		{
			strtemp = strtemp + " OR USER_AMMETERKIND = 1";
		}

	//	m_GetSubNameStr = m_GetSubNameStr + "���û���  ";
		
	}
	
	//��̨
    if(m_IsBT)
	{

		if(strtemp.IsEmpty())
		{
			strtemp = "USER_AMMETERKIND > 1";
		}
		else
		{
			strtemp = strtemp + " OR USER_AMMETERKIND > 1";
		}
		
//		m_GetSubNameStr = m_GetSubNameStr + "��̨��  ";

	}

	m_GetSubRangeStr = "(" + m_GetSubRangeStr  + ") AND (" + strtemp + ")";
	CDialog::OnOK();

}



//�õ�ѡ���̨����
CString CTRansformerdisppearDlg::GetSelectSubName()
{  

	//��һ����˾��
	HTREEITEM               hBootItem,hFirstItem; 
	HTREEITEM               hSecondItem,hThirdItem;
	
	//��һ����
    CString                m_SubNameStr,tr,str,tr1,tr2;
	str                =                    "";

	hBootItem  = m_datatree.GetRootItem();
	
	if(hBootItem == NULL)
	{
		return "";
	}

	m_SubNameStr = "��·����          ��̨����               �������";

	//�����
	if(m_IsJuMin)
	{
		str = str + "�����";
	}
	
	
	//���û���
	if(m_IsDaYongFu)
	{

		if(str.IsEmpty())
		{
			str = str + "���û���";
		}
		else
		{
			str = str + "�����û���";
		}

	}
	
	//��̨
    if(m_IsBT)
	{	
		if(str.IsEmpty())
		{
			str = str + "��̨��";
		}
		else
		{	
			str = str + "����̨��";
		}
	}
	
	//�ڶ������վ
	if(m_datatree.ItemHasChildren(hBootItem))
	{	
		hFirstItem = m_datatree.GetChildItem(hBootItem);
		
		do
		{ 
			
			//����������·��
			if(m_datatree.ItemHasChildren(hFirstItem) && (m_datatree.GetItemState(hFirstItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
			{	
			
				hSecondItem = m_datatree.GetChildItem(hFirstItem);
				do
				{
					
					//���ļ�����̨�ż�
					if(m_datatree.ItemHasChildren(hSecondItem) && (m_datatree.GetItemState(hSecondItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
					{	
						
						hThirdItem = m_datatree.GetChildItem(hSecondItem);

						/*
						if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
						{
							tr  = m_datatree.GetItemText(hSecondItem)  + m_datatree.GetItemText(hThirdItem);
							AfxMessageBox(tr);

							m_SubNameStr = m_SubNameStr + tr  + "\r\n";
						}
						*/

						do
						{
							
							
							//���弶��ģ��ż�
							/*
							if(m_datatree.ItemHasChildren(hThirdItem) && (m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) >= 2)
							{	
							
								hFourthItem = m_datatree.GetChildItem(hThirdItem);
								do
								{
									
									if((m_datatree.GetItemState(hFourthItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
									{
										
										tr = m_datatree.GetItemText(hFourthItem);
										
										tr.TrimLeft();
										tr.TrimRight();

									
										int k = tr.Find("��");
										
										if(k != -1)
										{
											tr = tr.Left(k);
										}
										
										
										tr  = m_datatree.GetItemText(hThirdItem)  + tr ;
										m_SubNameStr = m_SubNameStr + tr;
										//str8 = str8 + "USER_MODULENO="  + m_datatree.GetItemText(hThirdItem);
										
									
										
									}
								
									
								}while( (hFourthItem = m_datatree.GetNextSiblingItem(hFourthItem)) != NULL );
								
							}	
							//���弶��
							*/
							
							//nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��  ��̨
						
							if((m_datatree.GetItemState(hThirdItem, TVIS_STATEIMAGEMASK ) >> 12) == 3)
							{
								tr1  = m_datatree.GetItemText(hSecondItem);
								tr2 = m_datatree.GetItemText(hThirdItem);

								tr1.TrimLeft();
								tr1.TrimRight();
								
								tr2.TrimLeft();
								tr2.TrimRight();

								tr.Format("%20s    %20s    %16s",tr1,tr2,str);
								tr.TrimLeft();
						    	tr.TrimRight();
								
								/*
								int k = tr.Find("��"); 
								if(k != -1)
								{
									tr = tr.Left(k);
								}
								*/
								
								/////////////
								//�õ�ͼ��������
								//m_datatree.GetItemImage(hThirdItem,temp,temp1);
								
								//���������
								//if(temp1 > 3)
								{
									
									//����·�Ĺ������۵��,�����Ǳ�̨����
									//str4 = str4 + "(USER_MODULENO="  +  tr;
								}
								//else
								{
									//�Ǳ�̨����
								//	str4 = str4 + "(USER_TRANSFORMERNO="  + "'" + tr + "'";
								}

							//	tr  =   + tr ;
								m_SubNameStr = m_SubNameStr + "\r\n" + tr ;
								
															
							}
							
							
							
						}while( (hThirdItem = m_datatree.GetNextSiblingItem(hThirdItem)) != NULL );

					
						
					 }	
					 //���ļ���
					 
							 
				   }while( (hSecondItem = m_datatree.GetNextSiblingItem(hSecondItem)) != NULL );
						
						
				  }
				  
				 //��������
				  
				  
			}while( (hFirstItem = m_datatree.GetNextSiblingItem(hFirstItem)) != NULL );
			
			
		}	
		//�ڶ�����
		
		return m_SubNameStr;
		
}