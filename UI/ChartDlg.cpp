// OWEMONEY.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "ChartDlg.h"


#include "IFRMView.h"
#include "DIBAPI.H"
#include "DataBaseInstance.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COWEMONEY dialog

CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
   : CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COWEMONEY)
	m_radio1      =      0;
	m_title       = _T("");
	m_showlegend  =   TRUE;
	m_check1      =   TRUE;
	m_check3      =   FALSE;
	m_check4      =   FALSE;
	m_xtitle      = _T("");
	m_ytitle      = _T("");	
	m_showlabel   =  FALSE;
	m_showstasline = FALSE;
	m_showvalue   =   TRUE;
	m_showxlabel  =  FALSE;
	m_datakinds   =      0;
	m_multile = _T("");
	m_Ismultiple = FALSE;
	//}}AFX_DATA_INIT

	for(int i = 0; i < 13; i ++)
	{
		if(i == 0)
		{
			SELECT[i]  = TRUE;
		}
		else
		{
			SELECT[i]  = FALSE;
		}
	}

	BeginTime   = "";
	EndTime     = "";
}


void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COWEMONEY)
	DDX_Control(pDX, IDC_USERCOMBO, m_UserCombox);
	DDX_Control(pDX, IDC_ENDTIME, m_listend);
	DDX_Control(pDX, IDC_BEGINTIME, m_listbegin);
	DDX_Control(pDX, IDC_MSCHART, m_Chart);
	DDX_Control(pDX, IDC_DBGRIDS, m_dbgrids);
	DDX_Control(pDX, IDC_REMOTEDATACTLS, m_remotedatactrls);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Check(pDX, IDC_SHOWLEGEND, m_showlegend);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK7, m_check3);
	DDX_Check(pDX, IDC_CHECK8, m_check4);
	DDX_Text(pDX, IDC_XTITLE, m_xtitle);
	DDX_Text(pDX, IDC_YTITLE, m_ytitle);
	DDX_Check(pDX, IDC_SHOWLABEL, m_showlabel);
	DDX_Check(pDX, IDC_SHOWSTASLINE, m_showstasline);
	DDX_Check(pDX, IDC_SHOWVALUE, m_showvalue);
	DDX_Check(pDX, IDC_SHOWXLABEL, m_showxlabel);
	DDX_Radio(pDX, IDC_RADIO4, m_datakinds);
	DDX_Text(pDX, IDC_MULTIPLE, m_multile);
	DDX_Check(pDX, IDC_CHECK3, m_Ismultiple);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(COWEMONEY)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SAVEBMP, OnSavebmp)
	ON_BN_CLICKED(IDC_PRINTBMP, OnPrintbmp)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_SHOWLEGEND, OnShowlegend)
	ON_BN_CLICKED(IDC_SETTITLE, OnSettitle)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_SETXTITLE, OnSetxtitle)
	ON_BN_CLICKED(IDC_SETYTITLE, OnSetytitle)
	ON_BN_CLICKED(IDC_SHOWLABEL, OnShowlabel)
	ON_BN_CLICKED(IDC_SHOWSTASLINE, OnShowstasline)
	ON_CBN_SELCHANGE(IDC_BEGINTIME, OnSelchangeBegintime)
	ON_CBN_SELCHANGE(IDC_ENDTIME, OnSelchangeEndtime)
	ON_BN_CLICKED(IDC_SHOWVALUE, OnShowvalue)
	ON_BN_CLICKED(IDC_CHECK34, OnCheck34)
	ON_BN_CLICKED(IDC_CHECK39, OnCheck39)
	ON_BN_CLICKED(IDC_CHECK37, OnCheck37)
	ON_BN_CLICKED(IDC_CHECK38, OnCheck38)
	ON_BN_CLICKED(IDC_CHECK40, OnCheck40)
	ON_BN_CLICKED(IDC_CHECK41, OnCheck41)
	ON_BN_CLICKED(IDC_CHECK42, OnCheck42)
	ON_BN_CLICKED(IDC_CHECK43, OnCheck43)
	ON_BN_CLICKED(IDC_SHOWXLABEL, OnShowxlabel)
	ON_CBN_SELCHANGE(IDC_USERCOMBO, OnSelchangeUsercombo)
	ON_BN_CLICKED(IDC_CHECK45, OnCheck45)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COWEMONEY message handlers


void CChartDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}


void CChartDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CChartDlg::OnDestroy() 
{
	
	CDialog::OnDestroy();
   	
}


BOOL CChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//���ô��ڵ�ͼ��
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_TOTAL);
	ASSERT(hIcon);
	SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);
	

	//�õ�DIALOGBAR�ϵı���
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	GetAllUSERInfo(pMainFrm->m_wndMyDialogBar.SelectCondition());

	//�ҳ�פ��ʱ���б�
	InitializeCombo(0);
	//��ʾ�б�����
	OnSelchangeUsercombo();
    //���ھ���
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartDlg::initialize(short m_kinds)
{

	CString    Sqlstr,str;
  
	//û��ѡ��
	if(BeginTime.IsEmpty() || EndTime.IsEmpty())
	{
		MessageBox("û���ҵ�����ʾ���ݣ�","����",MB_OK|MB_ICONWARNING);
		return;
	}

	switch(m_kinds)
	{
	case 0:
		{
			//�õ��û���������ֶ�
			str = "SELECT TB_USER.USER_STATIONNAME AS ���վ����,TB_USER.USER_LINENAME AS ��·����,TB_USER.USER_TRANSFORMERNO AS ��̨����,TB_USER.USER_NO AS �û����,TB_USER.USER_NAME AS �û���,TB_USER.USER_ADDRESS AS �û���ַ,TB_GARRISON.GARRISON_MODULENO AS ģ���";
			
			//�й����
			if(SELECT[0])
			{
				str = str + ",TB_GARRISON.GARRISON_WORKDEGREE AS �й����";
			}
			
			//�޹����
			if(SELECT[1])
			{
				str = str + ",TB_GARRISON.GARRISON_LOSEDEGREE AS �޹����";
			}
			
			//A�����
			if(SELECT[2])
			{
				str = str + ",TB_GARRISON.GARRISON_ACURRENT AS A�����";
			}	
			
			//B�����
			if(SELECT[3])
			{
				str = str + ",TB_GARRISON.GARRISON_BCURRENT AS B�����";
			}
			
			//C�����
			if(SELECT[4])
			{
				str = str + ",TB_GARRISON.GARRISON_CCURRENT AS C�����";
			}
			
			//A���ѹ
			if(SELECT[5])
			{
				str = str + ",TB_GARRISON.GARRISON_AVOLTAGE AS A���ѹ";
			}
			
			//B���ѹ
			if(SELECT[6])
			{
				str = str + ",TB_GARRISON.GARRISON_BVOLTAGE AS B���ѹ";
			}
			
			//C���ѹ
			if(SELECT[7])
			{
				str = str + ",TB_GARRISON.GARRISON_CVOLTAGE AS C���ѹ";
			}	
			
			//������
			if(SELECT[8])
			{
				str = str + ",TB_GARRISON.GARRISON_JFDL AS ������";
			}
			
			//������
			if(SELECT[9])
			{
				str = str + ",TB_GARRISON.GARRISON_FDL AS �����";
			}
			
			//ƽ����
			if(SELECT[10])
			{
				str = str + ",TB_GARRISON.GARRISON_PDL AS ƽ����";
			}	
			
			//�ȵ���
			if(SELECT[11])
			{
				str = str + ",TB_GARRISON.GARRISON_GDL AS �ȵ���";
			}	
			
			//��������
			if(SELECT[12])
			{
				str = str + ",TB_GARRISON.GARRISON_GLYS AS ��������";
			}
			
			str = str + ",TB_GARRISON.GARRISON_HALTTIME AS פ��ʱ�� FROM TB_USER,TB_GARRISON ";
			Sqlstr.Format("%s WHERE TB_USER.USER_MODULENO=TB_GARRISON.GARRISON_MODULENO AND %s AND TB_GARRISON.GARRISON_HALTTIME>='%s' AND TB_GARRISON.GARRISON_HALTTIME<='%s' ORDER BY TB_GARRISON.GARRISON_HALTTIME ASC",str,m_RangeStr,BeginTime,EndTime);
			break;
		}
	case 1:
		{
			
			//��ʾ��̬�������
			str = "SELECT TB_USER.USER_STATIONNAME AS ���վ����,TB_USER.USER_LINENAME AS ��·����,TB_USER.USER_TRANSFORMERNO AS ��̨����,TB_USER.USER_NO AS �û����,TB_USER.USER_NAME AS �û���,TB_USER.USER_ADDRESS AS �û���ַ,TB_REALTIME.REALTIME_MODULENO AS ģ���";
			
			//�й����
			if(SELECT[0])
			{
				str = str + ",TB_REALTIME.REALTIME_WORKDEGREE AS �й����";
			}
			
			//�޹����
			if(SELECT[1])
			{
				str = str + ",TB_REALTIME.REALTIME_LOSEDEGREE AS �޹����";
			}
			
			//A�����
			if(SELECT[2])
			{
				str = str + ",TB_REALTIME.REALTIME_ACURRENT AS A�����";
			}	
			
			//B�����
			if(SELECT[3])
			{
				str = str + ",TB_REALTIME.REALTIME_BCURRENT AS B�����";
			}
			
			//C�����
			if(SELECT[4])
			{
				str = str + ",TB_REALTIME.REALTIME_CCURRENT AS C�����";
			}
			
			//A���ѹ
			if(SELECT[5])
			{
				str = str + ",TB_REALTIME.REALTIME_AVOLTAGE AS A���ѹ";
			}
			
			//B���ѹ
			if(SELECT[6])
			{
				str = str + ",TB_REALTIME.REALTIME_BVOLTAGE AS B���ѹ";
			}
			
			//C���ѹ
			if(SELECT[7])
			{
				str = str + ",TB_REALTIME.REALTIME_CVOLTAGE AS C���ѹ";
			}	
			
			//������
			if(SELECT[8])
			{
				str = str + ",TB_REALTIME.REALTIME_JFDL AS ������";
			}
			
			//������
			if(SELECT[9])
			{
				str = str + ",TB_REALTIME.REALTIME_FDL AS �����";
			}
			
			//ƽ����
			if(SELECT[10])
			{
				str = str + ",TB_REALTIME.REALTIME_PDL AS ƽ����";
			}	
			
			//�ȵ���
			if(SELECT[11])
			{
				str = str + ",TB_REALTIME.REALTIME_GDL AS �ȵ���";
			}	
			
			//��������
			if(SELECT[12])
			{
				str = str + ",TB_REALTIME.REALTIME_GLYS AS ��������";
			}
			
			str = str + ",TB_REALTIME.REALTIME_TRANSCRIBETIME AS ����ʱ�� FROM TB_USER,TB_REALTIME ";
			Sqlstr.Format("%s WHERE TB_USER.USER_MODULENO=TB_REALTIME.REALTIME_MODULENO AND %s AND TB_REALTIME.REALTIME_TRANSCRIBETIME>='%s' AND TB_REALTIME.REALTIME_TRANSCRIBETIME<='%s' AND TB_REALTIME.REALTIME_PROTOCOL=100 ORDER BY TB_REALTIME.REALTIME_TRANSCRIBETIME ASC",str,m_RangeStr,BeginTime,EndTime);
			break;
		}
	}

	m_remotedatactrls.SetDataSourceName(_T("ifrm"));
    m_remotedatactrls.SetSql(Sqlstr);
	m_remotedatactrls.SetUserName(_T("admin"));
	m_remotedatactrls.SetPassword(_T(""));
	m_remotedatactrls.SetCursorDriver(2);
	m_remotedatactrls.SetReadOnly(TRUE);
	m_remotedatactrls.Refresh();

	//connect it to IDC_REMOTEDATACTL
	LPUNKNOWN pCursor=m_remotedatactrls.GetDSCCursor();
	ASSERT(pCursor!=NULL);
	m_dbgrids.SetDataSource(pCursor); //bind the grid
	m_dbgrids.BindProperty(0x9, &m_remotedatactrls);
	m_dbgrids.SetEditActive(FALSE);
	m_dbgrids.Scroll(2, 0);
}




void CChartDlg::OnSavebmp() 
{

	char szFilter[]="ͼ��BMP�ļ�(*.BMP)|*.BMP||";
   	CFileDialog dlg(FALSE,"BMP","*.BMP",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	dlg.m_ofn.lpstrTitle="����Ϊ";
	
	if(dlg.DoModal() == IDOK)
	{
	
		EmptyClipboard();
		
		m_Chart.EditCopy();
		
		CloseClipboard();

		HBITMAP    m_bitmap;
		CDIBSectionLite bmp;
          
		//�򿪼�����
		if(OpenClipboard())
		{
			
			m_bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		
			bmp.SetBitmap(m_bitmap,NULL);
			bmp.Save(dlg.GetPathName());
			CloseClipboard(); 
			
		}
	
		//���BMP�ļ�
		//WndToBmpFile(pDC,dlg.GetPathName());
	}

}

void CChartDlg::WndToBmpFile(CDC* pDC,CString BmpFile)
{
	
	//it will capture a wnd image and save it into a bmp file
	CBitmap bmp,*pOldBmp;
	CRect           rect;
	CWnd*           pWnd;
	BOOL     flg  =    0;
	CPalette         pal;
	LOGPALETTE*      pLp;
	
	if(pDC == NULL)               //if pDC is NULL return
	{
		return ;
	}
	
	pWnd = pDC->GetWindow();      //Get Window of PDC
	
	pWnd->GetClientRect(&rect); //Get dimension of Window
	
	if(BmpFile.IsEmpty())
		return ;
	
	CDC memdc;
	
	memdc.CreateCompatibleDC(pDC);  //Make Compatible DC for memdc
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
    //Create Compatible DDB
	pOldBmp=memdc.SelectObject(&bmp);
	memdc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	
	//The following code will detect whether the BMP uses a Raster
	//palette or not.
	
	if(pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		int nSize;
		nSize = sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256;
		pLp   = (LOGPALETTE*) new BYTE[nSize];
		pLp->palVersion    = 0x300;
		pLp->palNumEntries = GetSystemPaletteEntries(pDC->m_hDC,0,255,pLp->palPalEntry);
		pal.CreatePalette(pLp);
		
		delete [] pLp;
	}
	memdc.SelectObject(pOldBmp);
	
	// will convert bitmap from DDB to DIB see DDBToDIB()
	HANDLE hDIB = DDBToDIB(bmp,BI_RGB,&pal);
	if(hDIB==NULL)
	{
		return ;
	}
	
	CFile        file;
	CFileException fe;
    // ���ļ�
	if (!file.Open(BmpFile, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		MessageBox("����ָ����ͼ���ļ�����!","���棺",MB_OK|MB_ICONWARNING);
		return;
	}
	
	// ���Ե���SaveDIB����ͼ��
	TRY
	{
		// ���Ա���ͼ��
		SaveDIB(HDIB(hDIB), file);
		// �ر��ļ�
		file.Close();
		if (hDIB != NULL)
		{
			// ���DIB����
			::GlobalFree((HGLOBAL) hDIB);
		}
	}
	CATCH (CException, eSave)
	{
		// ʧ��
		file.Abort();
		MessageBox("����ָ����ͼ���ļ�����!","���棺",MB_OK|MB_ICONWARNING);
	}
	END_CATCH
	
}


HANDLE CChartDlg::DDBToDIB(CBitmap &bitmap, DWORD dwCompression,CPalette *pPal)
{
	BITMAP              bm;
	BITMAPINFOHEADER    bi;
	LPBITMAPINFOHEADER  lpbi;
	DWORD               dwLen;
	HANDLE              hDIB;
	HANDLE              handle;
	HDC                 hDC;
	HPALETTE            hPal;
	
	
	ASSERT( bitmap.GetSafeHandle() );
	
	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;
	
	// If a palette has not been supplied, use default palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	
	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);
	
	// Initialize the bitmap infoheader
	bi.biSize          = sizeof(BITMAPINFOHEADER);
	bi.biWidth         = bm.bmWidth;
	bi.biHeight        = bm.bmHeight;
	bi.biPlanes        = 1;
	bi.biBitCount      = bm.bmPlanes * bm.bmBitsPixel;
    //bm.bmPlanes    * bm.bmBitsPixel;
	bi.biCompression   = dwCompression;
	bi.biSizeImage     = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed       = 0;
	bi.biClrImportant  = 0;
	
	// Compute the size of the infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);
	
	// We need a device context to get the DIB from
	hDC = ::GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	
	// Allocate enough memory to hold bitmap infoheader and
	// color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);
	
	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	
	*lpbi = bi;
	
	// Call GetDIBits with a NULL lpBits param, so the device
	// driver will calculate the biSizeImage field
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L,
		(DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);
	
	bi = *lpbi;
	
	// If the driver did not fill in the biSizeImage field, then
	// compute it
	// Each scan line of the image is aligned on a DWORD (32bit)
	// boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31)
			& ~31) / 8) * bi.biHeight;
		
		// If a compression scheme is used, the result may in fact
		// be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}
	
	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	
	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
        0L,                        // Start scan line
        (DWORD)bi.biHeight,        // # of scan lines
        (LPBYTE)lpbi               // address for bitmap bits
        + (bi.biSize + nColors * sizeof(RGBQUAD)),
        (LPBITMAPINFO)lpbi,        // address of bitmapinfo
        (DWORD)DIB_RGB_COLORS);    // Use RGB for color table
	
	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}
	
	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);
	
	return hDIB;
}



void CChartDlg::OnPrintbmp() 
{
	
	CFileFind    finder;
	HBITMAP    m_bitmap;
	CDIBSectionLite bmp;

	EmptyClipboard();
	m_Chart.EditCopy();
	CloseClipboard();

	//�򿪼�����
	if(OpenClipboard())
	{
		
		m_bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
		
		bmp.SetBitmap(m_bitmap,NULL);
		bmp.Save("C:\\temp000.bmp");
		
		EmptyClipboard();
		CloseClipboard(); 
		
	}

  
	//�Ҳ������ļ�
	if(!finder.FindFile("C:\\temp000.bmp"))
	{
        MessageBox("λͼ��������BMP�ļ�!","  ",MB_OK|MB_ICONWARNING);
		return ;
	}

    //�򿪴�BMP�ļ�
	WinExec( "mspaint.exe C:\\temp000.BMP",SW_SHOWMAXIMIZED);
   
	/*
	PROCESS_INFORMATION procinfo; //���̵���Ϣ
	char* chPar="MSPAINT.EXE C:\\temp000.BMP";

	STARTUPINFO stinfo;	
	memset(&stinfo, 0, sizeof(STARTUPINFO));
	stinfo.cb = sizeof(STARTUPINFO);
	stinfo.dwFlags = STARTF_USESHOWWINDOW;
	stinfo.wShowWindow = SW_SHOWMAXIMIZED;//SW_SHOWDEFAULT;//"MSPAINT.EXE C:\\temp000.BMP"
	
	BOOL isOK;
	isOK = CreateProcess(NULL,chPar,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&stinfo,&procinfo);
	if(isOK)
	{
		DWORD result = WaitForSingleObject(procinfo.hThread,INFINITE);//10000);
	}
	else
	{
		MessageBox("��ͼ��������ʧ��!","����",MB_OK|MB_ICONWARNING);
	}
	*/
	


}

//SqlStr       ��    ��
//BeginTime    ��ʼʱ��
//EndTime      ����ʱ��
void CChartDlg::ShowChart(CString SqlStr, CString BeginTimes, CString EndTimes,short m_kinds)
{
	long      ModuleNo;
	CString        str;
	
	//���ݸ���
	long m_DataRecords;
    
	UpdateData(TRUE);
	
	//�����ݿ�,�ҳ�ģ���
	CDatabase      dbs;	
	
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset rs(&dbs);
		
		/*************�ҳ�����������ģ���****************/
		SqlStr = "SELECT USER_MODULENO,USER_MULTIPLE,USER_NAME FROM TB_USER WHERE " + SqlStr;
		
		rs.Open(CRecordset::forwardOnly,SqlStr);
		
		rs.GetFieldValue((short)0,str);
		ModuleNo = atol(str);
		m_title = "[" + str + "]"; 
		//����
		rs.GetFieldValue((short)1,str);
		str.TrimLeft();
        str.TrimRight();

		if(atoi(str) == 0)
		{
			m_multile = "1";
		}
		else
		{
			m_multile = str;
		}

		rs.GetFieldValue((short)2,str);
		rs.Close();
		
		
		str.TrimLeft();
        str.TrimRight();
        
		switch(m_kinds)
		{
		case 0:
			{
		       m_title = str + "�õ����߷�����" + m_title;
			   break;
			}
		case 1:
			{
				m_title = str + "��̬�����������" + m_title;
				break;
			}
		}
		
		m_Chart.SetTitleText(" " + m_title + " ");
		UpdateData(FALSE);
		
		/*************�ҳ�����������ģ��Ž���****************/
		switch(m_kinds)
		{
		case 0:
			{
				//��ʾפ������
				SqlStr.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME>='%s' AND GARRISON_HALTTIME<='%s'",ModuleNo,BeginTime,EndTime);
				m_DataRecords = CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", SqlStr);
				break;
			}
		case 1:
			{
				//��ʾ��̬��������
				SqlStr.Format("REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME>='%s' AND REALTIME_TRANSCRIBETIME<='%s' AND REALTIME_PROTOCOL=100",ModuleNo,BeginTime,EndTime);
				m_DataRecords = CDataBaseInstance::GetAllRecordsCount("TB_REALTIME", SqlStr);
				break;
			}
		}
			
		//������ݸ�������0
		if(m_DataRecords > 0)
		{
			m_StrArray.SetSize(m_DataRecords);
			
			CMakeArray<float> m_pMakeArray;
			
			//���ɶ�ά����
			float **data = m_pMakeArray.MakeTwoArray(m_DataRecords,13);
			data[0][0]     =                            0;
			
			switch(m_kinds)
			{
			case 0:
				{
			       SqlStr =  "SELECT  GARRISON_WORKDEGREE,GARRISON_LOSEDEGREE,GARRISON_ACURRENT,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_JFDL,GARRISON_FDL,GARRISON_PDL,GARRISON_GDL,GARRISON_GLYS,GARRISON_HALTTIME FROM TB_GARRISON WHERE " + SqlStr + " order by GARRISON_HALTTIME";
				   break;
				}
			case 1:
				{
   			        SqlStr =  "SELECT  REALTIME_WORKDEGREE,REALTIME_LOSEDEGREE,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_JFDL,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL,REALTIME_GLYS,REALTIME_TRANSCRIBETIME FROM TB_REALTIME WHERE " + SqlStr + " AND REALTIME_PROTOCOL=100 order by REALTIME_TRANSCRIBETIME";
					break;
				}
			}

			rs.Open(CRecordset::forwardOnly,SqlStr);
			
			//���û���Ϣ���ҳ�ģ���
			for(int k = 0;k < m_DataRecords; k++)
			{
				
				//�õ�����ֵ
				rs.GetFieldValue((short)0,str);

				//�й�
				if(m_Ismultiple)
				{
					//�б���
					data[k][0] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					
					data[k][0] = float(atof(str));
				}

				//�޹�
				rs.GetFieldValue((short)1,str);
			
				if(m_Ismultiple)
				{
					//�б���
					data[k][1] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][1] = float(atof(str));
				}
				
				//A�����
				rs.GetFieldValue((short)2,str);
				
				if(m_Ismultiple)
				{
					data[k][2] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][2] = float(atof(str));
				}

				//B�����
				rs.GetFieldValue((short)3,str);
                
				if(m_Ismultiple)
				{
					data[k][3] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][3] = float(atof(str));
				}

				//C�����
				rs.GetFieldValue((short)4,str);
				
				if(m_Ismultiple)
				{
					data[k][4] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][4] = float(atof(str));
				}
				
				//5,6,7�ֱ�ΪABC�����ѹ
				rs.GetFieldValue((short)5,str);
				data[k][5] = float(atof(str));
				
				rs.GetFieldValue((short)6,str);
				data[k][6] = float(atof(str));
				
				rs.GetFieldValue((short)7,str);
				data[k][7] = float(atof(str));
				
			    //������
				rs.GetFieldValue((short)8,str);
				
				if(m_Ismultiple)
				{
					data[k][8] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][8] = float(atof(str));
				}
				
				rs.GetFieldValue((short)9,str);
				
				//�����
				if(m_Ismultiple)
				{
					data[k][9] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][9] = float(atof(str));
				}
				
				rs.GetFieldValue((short)10,str);
	           
				//ƽ����
				if(m_Ismultiple)
				{
					data[k][10] = float(atof(str))*float(atof(m_multile));	
				}
				else
				{
					data[k][10] = float(atof(str));	
				}
				
				rs.GetFieldValue((short)11,str);
	           
				//�ȵ���
				if(m_Ismultiple)
				{
					data[k][11] = float(atof(str))*float(atof(m_multile));
				}
				else
				{
					data[k][11] = float(atof(str));
				}
				
				rs.GetFieldValue((short)12,str);
				//��������
				data[k][12] = float(atof(str));

				rs.GetFieldValue((short)13,str);
				
				m_StrArray[k] = str;
				//���»�һ����¼
				rs.MoveNext();
				
			}
			rs.Close();
			
			SetChartDataValue(data,m_DataRecords,13);
			
			//ɾ����ά����
			m_pMakeArray.DelTwoArray(data,m_DataRecords);
			
		}
		else
		{
		
			m_StrArray.SetSize(1);
			
			CMakeArray<float> m_pMakeArray;
			
			//���ɶ�ά����
			float **data = m_pMakeArray.MakeTwoArray(1,13);
			data[0][0]     =        0;
			data[0][1]     =        0;
			data[0][2]     =        0;
			data[0][3]     =        0;
			data[0][4]     =        0;
			data[0][5]     =        0;
			data[0][6]     =        0;
			data[0][7]     =        0;
			data[0][8]     =        0;
			data[0][9]     =        0;
			data[0][10]    =        0;
			data[0][11]    =        0;
			data[0][12]    =        0;
            
			m_StrArray[0] = "��";
			SetChartDataValue(data,1,13);

			//ɾ����ά����
			m_pMakeArray.DelTwoArray(data,m_DataRecords);

		}
			
		//�ر����ݿ�
		dbs.Close();
	}

}



void CChartDlg::InitializeCombo(short m_kinds)
{   
	//�����ݿ�
	CDatabase     db;
	CString   strSql;

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//��˾����ʼ
		CDaoRecordset m_CompanySet(m_pDatabase);

		switch(m_kinds)
		{
		case 0:
			{
				m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT GARRISON_HALTTIME from TB_GARRISON order by GARRISON_HALTTIME "));
				break;
			}
		case 1:
			{		
				m_CompanySet.Open(dbOpenSnapshot,_T("Select DISTINCT REALTIME_TRANSCRIBETIME from TB_REALTIME WHERE REALTIME_PROTOCOL=100 order by REALTIME_TRANSCRIBETIME"));
				break;
			}
		}

		m_listbegin.ResetContent();
		m_listend.ResetContent();
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			strSql = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
			m_listbegin.AddString(strSql);
			m_listend.AddString(strSql);
			m_CompanySet.MoveNext();
		}
		m_CompanySet.Close();	
		//��˾����
		
		delete m_pDatabase;
		m_pDatabase = NULL; 

		//û��ѡ��
		if(m_listbegin.GetCount() > 0  && m_listend.GetCount() > 0)
		{

			m_listbegin.SetCurSel(0);
		    m_listend.SetCurSel(m_listend.GetCount()-1);
			
			//�õ���ʼʱ��ͽ���ʱ��
			m_listbegin.GetLBText(0,BeginTime);
			m_listend.GetLBText(m_listend.GetCount() - 1,EndTime);

			BeginTime.TrimLeft();
			BeginTime.TrimRight();
			
			EndTime.TrimLeft();
			EndTime.TrimRight();
		}
		
	}
	
}

void CChartDlg::SetChartDataValue(float** data,int Rows,int Cols)
{

	short LineNo[13];
   
	int   j  =    0;
	int   l  =    0;
	
	LineNo[0]  =  0;
	
	//��13�����������ļ���
	for(int i = 0; i < 13; i++)
	{

		if(SELECT[i])
		{
			//������������
			LineNo[j] = i;
			j++;
		}
		
	}



    //������������j������
	m_Chart.SetColumnCount(j); 
	
	//��13�����������ļ���
	for( int i = 0; i < 13; i++)
	{

		if(SELECT[i])
		{
		
			l++;

			m_Chart.SetColumn(l);
			
			//�����б���
			switch(i+1)
			{
			case 1:
				{
					m_Chart.SetColumnLabel("�й����");
					break;
				}
			case 2:
				{
					m_Chart.SetColumnLabel("�޹����");
					break;
				}
			case 3:
				{
					m_Chart.SetColumnLabel("A�����");
					break;
				}
			case 4:
				{
					m_Chart.SetColumnLabel("B�����");
					break;
				}
			case 5:
				{
					m_Chart.SetColumnLabel("C�����");
					break;
				}
			case 6:
				{
					m_Chart.SetColumnLabel("A���ѹ");
					break;
				}
			case 7:
				{
					m_Chart.SetColumnLabel("B���ѹ");
					break;
				}
			case 8:
				{
					m_Chart.SetColumnLabel("C���ѹ");
					break;
				}
			case 9:
				{
					m_Chart.SetColumnLabel("������");
					break;
				}
			case 10:
				{
					m_Chart.SetColumnLabel("�����");
					break;
				}
			case 11:
				{
					m_Chart.SetColumnLabel("ƽ����");
					break;
				}
			case 12:
				{
					m_Chart.SetColumnLabel("�ȵ���");
					break;
				}
			case 13:
				{
					m_Chart.SetColumnLabel("��������");
					break;
				}
				
			}
			
		}
		
	}


	//ÿ���ߵĵ���
	m_Chart.SetRowCount(Rows);

	for(int k = 0; k < j; k++)
	{

		//��������ֱ�ߣ���Ŵ�1��ʼ
		m_Chart.SetColumn(k + 1);

		// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
		// 0: ����ʾ	1: ��ʾ����״ͼ��
		// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
		m_Chart.GetPlot().GetSeriesCollection().GetItem(k+1).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(m_showvalue);
		
		//��ʾ����
		m_Chart.GetPlot().GetSeriesCollection().GetItem(k+1).GetDataPoints().GetItem(-1).GetMarker().SetVisible(m_showlabel);
		
		//�������ߵĵ�ֵ
		for(int i = 0; i < Rows; i++)
		{
            
			//����X���б���
			m_Chart.SetRow(i + 1);
		    m_Chart.SetRowLabel(m_StrArray[i]);
			//������ֵ
			m_Chart.GetDataGrid().SetData(i + 1, k + 1,data[i][LineNo[k]], 0);

			if(!m_showxlabel)
			{
				m_Chart.SetRowLabel("");
			}
		
		}

	}

	m_Chart.SetShowLegend(m_showlegend);
	

	m_StrArray.FreeExtra();
	m_StrArray.RemoveAll();
 	
	m_Chart.Refresh();
}


void CChartDlg::OnRadio1() 
{
    m_Chart.SetChartType(3);
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio2() 
{
    m_Chart.SetChartType(2);
//	m_Chart.GetPlot().GetView3d().Set(365,0);//float Rotation, float Elevation) 10,100
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio3() 
{
    m_Chart.SetChartType(1);
	m_Chart.Refresh();	
}

void CChartDlg::OnRadio8() 
{
    m_Chart.SetChartType(0);
	m_Chart.Refresh();		
}

//��ʾͼ�� 
void CChartDlg::OnShowlegend() 
{

	if(m_Chart.GetShowLegend())
	{
		m_Chart.SetShowLegend(FALSE);
	}
	else
	{
		m_Chart.SetShowLegend(TRUE);
		
	}
	m_Chart.Refresh();

}

//���ñ���
void CChartDlg::OnSettitle() 
{
    UpdateData(TRUE);
	m_title.TrimLeft();
	m_title.TrimRight();
	m_Chart.SetTitleText(" " + m_title + " ");
	m_Chart.Refresh();
}

void CChartDlg::OnCheck1() 
{
   
   //�й����
   SELECT[0] = !SELECT[0];

   //������ˢ��һ��
   MsChartAppear();
   
}

void CChartDlg::OnCheck2() 
{
	//�޹����
   SELECT[1] = !SELECT[1];
   //������ˢ��һ��
   MsChartAppear();
	
}

void CChartDlg::OnCheck7() 
{
   //A�����
   SELECT[2] = !SELECT[2];
   //������ˢ��һ��
   MsChartAppear();
}

void CChartDlg::OnCheck8() 
{
   //A���ѹ
   SELECT[5] = !SELECT[5];
   //������ˢ��һ��
   MsChartAppear();
}

//X�����
void CChartDlg::OnSetxtitle() 
{
    UpdateData(TRUE);
	m_xtitle.TrimLeft();
	m_xtitle.TrimRight();
	VARIANT var;
	m_Chart.GetPlot().GetAxis(0,var).GetAxisTitle().SetText(m_xtitle);			// X������
	m_Chart.Refresh();	
}

//Y�����
void CChartDlg::OnSetytitle() 
{
    UpdateData(TRUE);
	VARIANT         var;
	m_ytitle.TrimLeft();
	m_ytitle.TrimRight();
	m_Chart.GetPlot().GetAxis(1,var).GetAxisTitle().SetText(m_ytitle);			// y������
	m_Chart.Refresh();	
	
}

//���Ǵ���
void CChartDlg::OnShowlabel() 
{

	UpdateData(TRUE);

	for(int j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		for(int i = 1; i <= m_Chart.GetPlot().GetSeriesCollection().Count();i ++)
		{
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetMarker().SetVisible(m_showlabel);
		
		}

	}
  	
}

//��ʾͳ����
void CChartDlg::OnShowstasline() 
{
	
    UpdateData(TRUE);
	
	for(int  j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		if(m_showstasline)
		{	  
			//��ʾ����ͳ������
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetStatLine().SetFlag(31);
			
		}
		else
		{	
			//���ظ���ͳ������
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetStatLine().SetFlag(0);
		}
		
	}
      	
}

void CChartDlg::MsChartAppear()
{

	int   j     =       0;
	CString           str;
	CString        StrSql;
	
	//û��ʱ�䷶Χ
	if(BeginTime.IsEmpty() || EndTime.IsEmpty())
	{
		return;
	}

	//��8�����������ļ���
	for(int i = 0; i < 13; i++)
	{
		
		if(SELECT[i] == TRUE)
		{
			j++;
		}
		
	}
	
	//û��ѡ����
	if( j  <= 0)
	{
		
		return;
		
	}
	else
	{
		//��ʾͼ��
		ShowChart(m_RangeStr, BeginTime,EndTime,m_datakinds);
		initialize(m_datakinds);
	}
	
}


void CChartDlg::OnSelchangeBegintime() 
{
   if(m_listbegin.GetCurSel() != CB_ERR)
   {
	   //�õ���ʼ��ʱ��
	   m_listbegin.GetLBText(m_listbegin.GetCurSel(),BeginTime);
	   BeginTime.TrimLeft();
	   BeginTime.TrimRight();
	   MsChartAppear();	  
	   initialize(m_datakinds);
   }
	   
}

void CChartDlg::OnSelchangeEndtime() 
{
   if(m_listend.GetCurSel() != CB_ERR)
   {
	   
	   //�õ�������ʱ��
	   m_listend.GetLBText(m_listend.GetCurSel(),EndTime);
	   EndTime.TrimLeft();
	   EndTime.TrimRight();
	   MsChartAppear();
	   initialize(m_datakinds);
   }

}

void CChartDlg::OnShowvalue() 
{
    UpdateData(TRUE);
	
	for(int  j = 1;j <= m_Chart.GetColumnCount();j ++)
	{
		
		//��������ֱ�ߣ���Ŵ�1��ʼ
		m_Chart.SetColumn(j);
		
		if(m_showvalue)
		{	  
			
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(1);
			
			
		}
		else
		{	
			// ���ݵ�������ʾ����ֵ��ģʽ(������״ͼ�͵���ͼ��Ч)
			// 0: ����ʾ	1: ��ʾ����״ͼ��
			// 2: ��ʾ����״ͼ���Ϸ�	3: ��ʾ����״ͼ���м�	4: ��ʾ����״ͼ���·�
			m_Chart.GetPlot().GetSeriesCollection().GetItem(j).GetDataPoints().GetItem(-1).GetDataPointLabel().SetLocationType(0);
		}
		
	}
	
}

void CChartDlg::OnCheck34() 
{
   //B�����
   SELECT[3] = !SELECT[3];
   //������ˢ��һ��
   MsChartAppear();	

}

void CChartDlg::OnCheck39() 
{
   //C�����
   SELECT[4] = !SELECT[4];
   //������ˢ��һ��
   MsChartAppear();	
}

void CChartDlg::OnCheck37() 
{
   //B���ѹ
   SELECT[6] = !SELECT[6];
   //������ˢ��һ��
   MsChartAppear();	
}

void CChartDlg::OnCheck38() 
{
   //C���ѹ
   SELECT[7] = !SELECT[7];
   //������ˢ��һ��
   MsChartAppear();	
}

void CChartDlg::OnCheck40() 
{
	//������
	SELECT[8] = !SELECT[8];
	//������ˢ��һ��
	MsChartAppear();		
}

void CChartDlg::OnCheck41() 
{
	//�����
	SELECT[9] = !SELECT[9];
	//������ˢ��һ��
	MsChartAppear();		
}

void CChartDlg::OnCheck42() 
{
	//ƽ����
	SELECT[10] = !SELECT[10];
	//������ˢ��һ��
	MsChartAppear();		
}

void CChartDlg::OnCheck43() 
{
	//�ȵ��� 
	SELECT[11] = !SELECT[11];
	//������ˢ��һ��
	MsChartAppear();		
}

void CChartDlg::OnShowxlabel() 
{
	UpdateData(TRUE);
	//������ˢ��һ��
	MsChartAppear();		
}

//�õ���ѡ����û���Ϣ
void CChartDlg::GetAllUSERInfo(CString StrSql)
{
	//�����ݿ�
	CDatabase           db;
	CString            Str,InsertStr;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		//��CRecordset����
		CRecordset rs(&db );
	    Str.Format("SELECT count(*) FROM TB_USER WHERE %s",StrSql);
			
		rs.Open(CRecordset::forwardOnly,Str);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,Str);
		
		//��¼����
		long fields = atol(Str); 
		rs.Close();
		
		//ɾ��ԭ�����б�����
		m_UserCombox.ResetContent();

		if(fields  > 0)
		{
      	    Str.Format("SELECT USER_MODULENO,USER_NAME FROM TB_USER WHERE %s",StrSql);
			
			rs.Open(CRecordset::forwardOnly,Str);
			
			//���û���Ϣ
			for(int j = 0;j < fields; j++)
			{
				InsertStr = "";
				rs.GetFieldValue((short)0,Str);//ģ���
				Str.TrimLeft();
				Str.TrimRight();
				InsertStr = Str;
				
				rs.GetFieldValue((short)1,Str);//�û���
				Str.TrimLeft();
				Str.TrimRight();
				InsertStr = InsertStr + "��" + Str;
				
				//�����б��
				m_UserCombox.AddString(InsertStr);
						
				//���»�һ����¼
				rs.MoveNext();

			}
		
			//�ر����ݿ�
		    rs.Close( );
		
		}
		
		//�����������0
		if(m_UserCombox.GetCount() > 0)
		{
			m_UserCombox.SetCurSel(0);
		}

		db.Close( );
	}

}

void CChartDlg::OnSelchangeUsercombo() 
{	
	
	CString          StrSql;
	int                   k;
	
	
	if(m_UserCombox.GetCurSel() != CB_ERR)
	{

		m_UserCombox.GetLBText(m_UserCombox.GetCurSel(),StrSql);
	    k = StrSql.Find("��");

		if( k != -1)
		{
			m_RangeStr.Format("TB_USER.USER_MODULENO=%d",atoi(StrSql.Left(k)));
			//���б�����ʾ������
			initialize(m_datakinds);
			//��ʾͼ��
			ShowChart(m_RangeStr,BeginTime,EndTime,m_datakinds);
			OnShowstasline();
		}
        
		StrSql = StrSql.Left(k);
	}

}

void CChartDlg::OnCheck45() 
{
	//�ȵ��� 
	SELECT[12] = !SELECT[12];
	//������ˢ��һ��
	MsChartAppear();		
}

void CChartDlg::OnRadio4() 
{
	UpdateData(TRUE);
	//�ҳ�פ��ʱ���б�
	InitializeCombo(0);
	//��ʾ�б�����
	OnSelchangeUsercombo();	
}

void CChartDlg::OnRadio6() 
{
	UpdateData(TRUE);
	//�ҳ�פ��ʱ���б�
	InitializeCombo(1);
	//��ʾ�б�����
	OnSelchangeUsercombo();		
}

void CChartDlg::OnCheck3() 
{
	UpdateData(TRUE);
	OnSelchangeUsercombo();

}
