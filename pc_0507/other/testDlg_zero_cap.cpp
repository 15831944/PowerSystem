// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "protocol.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "PCI8664.h"


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


 //stru_meter_read_protocol_Data  stru_meter_read_protocol ;

// stru_PC2MCU_Protocol     stru_pc2mcu_protocol ;


typedef unsigned long (CALLBACK *pfun_callback)(LPVOID pvUserParam) ;



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_LAB_PROTO, m_lab_ctrl_proto);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DECODE, OnBtnDecode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnBtnDecode() 
{
	// TODO: Add your control notification handler code here
  //////////////////init the wplc protocol
/*
  stru_meter_read_protocol->uc_phase_number = _PHASE_A ;

  stru_meter_read_protocol->uc_station_number = 0 ;

  stru_meter_read_protocol->uc_sub_meter_addr = 0x15A5A ;

  stru_meter_read_protocol->uc_sub_meter_addr = 12 ;

  stru_meter_read_protocol->uc_user_cmd = 0x02 ; //_READ_TRIG_DEGREE_A ;
  //////////////////init the pc2mcu protocol
  stru_pc2mcu_protocol->uc_line_number = 16 ;
  
  stru_pc2mcu_protocol->uc_mcu_cmd = 
*/	
  CComboBox  * p_combo ;

  int index = 0 ;

  CString  str1 , str2 ;

  int  i ;

  stru_Meter_Read     meter_read_proto ;

  stru_Meter_Congeal   meter_congeal_proto ;
//////////user cmd set 
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_USER_CMD ) ;

  index = p_combo->GetCurSel( ) ;

  switch( index )
  {
  case 0 :
	  {
         meter_read_proto.uc_user_cmd = 0x02 ;

		 break ;
	  }
  case 1 :
	  {
         meter_read_proto.uc_user_cmd = 0x06 ;

		 break ;
	  }
  case 2 :
	  {
         meter_read_proto.uc_user_cmd = 0xF2 ;

		 break ;
	  }
  default:
	  break;
  }
/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_MODULE_ADDR ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.un_module_addr.ldata = atoi( str1 ) ;


/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SUB_ADDR ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_sub_meter_addr = ( atoi( str1 ) - 1 ) ;

/////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_PHASE ) ;

  index = p_combo->GetCurSel( ) ;

  switch( index )
  {
  case 0 :
	  {
        meter_read_proto.uc_phase_number = 0x01 ;

		break ;
	  }
  case 1 :
	  {
        meter_read_proto.uc_phase_number = 0x02 ;

		break ;
	  }
  case 2 :
	  {
        meter_read_proto.uc_phase_number = 0x03 ;

		break ;
	  }
  case 3 :
	  {
        meter_read_proto.uc_phase_number = 0x00 ;

		break ;
	  }
  default:
	  break;
  }

  /////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_STATION_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_station_number= atoi( str1 ) ;
//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_CONGEAL_TIME ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_congeal_proto.un_congeal_time.idata = atoi( str1 ) ;
//////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_SECTION_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_section  = atoi( str1 ) ;
  //////////////////////
  p_combo = ( CComboBox  * ) GetDlgItem( IDC_COMBO_LINE_NUMBER ) ;

  p_combo->GetWindowText( str1 ) ;

  meter_read_proto.uc_line_number  = atoi( str1 ) ;



 // Fun_WPLC_Data_Set( meter_read_proto ) ;

  CMD_Buf_Init( ) ;

  Meter_Read_Single( & meter_read_proto ) ;
/*
  m_lab_ctrl_proto.SetWindowText( "" ) ;

  for( i = 0 ; i < 16 ; i ++ )
  {
    m_lab_ctrl_proto.GetWindowText( str2 ) ;
	
    str1.Format( "%x" , g_uc_cmd_buf[ i ] ) ;

	str1 = str2 + "0x" + str1 + " " ;

	m_lab_ctrl_proto.SetWindowText( str1 ) ;
  }
*/

}

HANDLE hDevice_AD ;  //�ɼ���������

PCI8664_STATUS_AD    AD_Status ;//ad�ɼ���״̬�ṹ��

int DeviceLgcID ;   

PCI8664_PARA_AD ADPara ;		// Initialization AD parameter structure

LONG nReadSizeWords;		// Each time the number of read  AD data

LONG nRetSizeWords;

int nADChannel = 0;

SHORT ADData;

int  Fun_AD_Device_Init( )
{
  DeviceLgcID = 0;

  hDevice_AD = PCI8664_CreateDevice(DeviceLgcID); // create device object

  if(hDevice_AD == INVALID_HANDLE_VALUE)
  {
		AfxMessageBox( "PCI�ɼ�����ʼ��ʧ�ܣ�" ) ;

		return 0; 
  }
			

memset(&ADPara, sizeof(ADPara), 0x00);	// reset the parameters to certainty value 0 (strongly recommended) 

// Preset hardware parameters
ADPara.ADMode		= PCI8664_ADMODE_SEQUENCE;		// continuous sampling

ADPara.FirstChannel = 0;							// first channel

ADPara.LastChannel	= 31;							// last channel

ADPara.Frequency	= 1000000;						// sampling frequency(Hz)

ADPara.GroupInterval= 1;							// group interval(uS)

ADPara.LoopsOfGroup = 1;							// loops of group

ADPara.Gains		= PCI8664_GAINS_1MULT;

ADPara.InputRange	= PCI8664_INPUT_N5000_P5000 ;	// ���뷶Χ�� + - 5V // Analog Input Range range

ADPara.TriggerMode	= PCI8664_TRIGMODE_SOFT;		// software trigger

ADPara.TriggerType	= PCI8664_TRIGTYPE_EDGE;		// edge trigger 

ADPara.TriggerDir   = PCI8664_TRIGDIR_NEGATIVE;		// negative trigger	

ADPara.ClockSource	= PCI8664_CLOCKSRC_IN;			// internal clock

ADPara.bClockOutput = PCI8664_CLOCKOUT_DISABLE;

if(!PCI8664_InitDeviceProAD( hDevice_AD ,  &ADPara ) )		// Initial AD
{
    AfxMessageBox( "PCI�ɼ���AD��������ʧ�ܣ�" ) ;

	return 0;  
}


}
/*
nReadSizeWords = 1024*4; 

if(!PCI8664_StartDeviceProAD(hDevice)) // Start AD
{
    MessageBox( "PCI�ɼ���AD�������ʧ��" ) ��

	return 0; 
}
*/





#define    _100K_CLK       0.00001 

volatile bool  g_flag_pc_io_clk =  false ;

HANDLE     hEvent_RW_Trig_Angle_Enable ;

//unsigned char  g_uc

#define     _BIT8_CLK_HIGH      0x0100   //���

#define    _BIT8_CLK_LOW        0xF7FF  //����

unsigned char   g_uc_PC_RX_Buf[ 16 ] ; //pc����дָ��������Ŷ�д������ָ��ķ�������

#define    RW_TRIG_ANGLE_READBACK_LEN    16 

void CALLBACK CTestDlg:: Thread_RW_Trig_Angle( CTestDlg *pDlg )
{

   LARGE_INTEGER    time1 ;

   double   db_freq ,  db_space ;

   LONGLONG db_start , db_end ; 

   int  out_data = 0 ;

   int i ;

   unsigned char  send_data ;

   unsigned char  recv_data ;

   //get frequence 
   QueryPerformanceFrequency( &time1 ) ;

   db_freq = ( double ) time1.QuadPart ;
do 
{//thread do while
   
if( WaitForSingleObject( hEvent_RW_Trig_Angle_Enable , 0 ) == WAIT_OBJECT_0 ) //hEvent_RW_Trig_Angle_Enable 
 {   
//����ָ�� 
   for( i = 0 ; i < 16 ; i ++ )
   {     
	   send_data = g_uc_cmd_buf[ i ] | _BIT8_CLK_HIGH  ;  //ʹCLK��������ߵ�ƽ��ͬʱ������ݷ��õ��Ͱ�λ

	   PCI8664_SetDeviceDO( hDevice_AD , &send_data ) ;  //������ݺ�clk�ź�

	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
		  
       db_start = time1.QuadPart ;
       ////////��ʱ100k , ���ָߵ�ƽ
       do
	   {    
          QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��

	      db_end = time1.QuadPart ;

	      db_space = ( double ) ( db_end- db_start ) ; //ʱ���
   
	      db_space = db_space / db_freq ;

	   }   while( db_space < _100K_CLK ) ;  //ʱ���С��100K

	   send_data = g_uc_cmd_buf[ i ] & _BIT8_CLK_LOW  ;  //ʹCLK��������ߵ�ƽ��ͬʱ������ݷ��õ��Ͱ�λ
	   
	   PCI8664_SetDeviceDO( hDevice_AD , &send_data ) ;
       ////////��ʱ100k �����ֵ͵�ƽ
	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	   
       db_start = time1.QuadPart ;
	   
       do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		   
		   db_space = db_space / db_freq ;
		   
	   }   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
   }//for

//��ȡָ��ظ���16�ֽڳ���
   bool bflag_recv_start = false ;
   
   
   unsigned char recv_data_index = 0 ;

   do 
   {     
	   send_data = send_data | _BIT8_CLK_HIGH  ;  //ʹCLK��������ߵ�ƽ
	   
	   PCI8664_SetDeviceDO( hDevice_AD , &send_data ) ;  //���clk�ź�
	   
	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	   
       db_start = time1.QuadPart ;
	   
       do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		   
		   db_space = db_space / db_freq ;
		   
	   }   
	   while( db_space < _100K_CLK ) ;  //ʱ���С��100K
	   
	   send_data = send_data & _BIT8_CLK_LOW  ;  //ʹCLK�������di��ƽ
	   
	   PCI8664_SetDeviceDO( hDevice_AD , &send_data ) ;

       //��ʱ100K�����ֵ͵�ƽ
	   QueryPerformanceCounter( &time1 ) ;  //�õ���ʼʱ��
	   
       db_start = time1.QuadPart ;
	   
       do
	   {    
		   QueryPerformanceCounter( &time1 ) ;  //�õ���ǰʱ��
		   
		   db_end = time1.QuadPart ;
		   
		   db_space = ( double ) ( db_end- db_start ) ; //ʱ���
		   
		   db_space = db_space / db_freq ;
		   
	   }   while( db_space < _100K_CLK ) ;  //ʱ���С��100K

	   //�͵�ƽʱ�䵽,��ȡ����

	   PCI8664_GetDeviceDI( hDevice_AD , &recv_data ) ;

	   if( recv_data == 0x68 && bflag_recv_start ==  false ) //the start of readback data
	   {
          bflag_recv_start = true ;

		  g_uc_PC_RX_Buf[ 0 ] = recv_data ;

		  recv_data_index ++ ; 
	   }
	   else if( bflag_recv_start == true )
	   {
		  g_uc_PC_RX_Buf[ recv_data_index ] = recv_data ;
		   
		  recv_data_index ++ ;
	   }
   } 
   while( recv_data_index < RW_TRIG_ANGLE_READBACK_LEN  ) ;//�ж϶�ȡ���ݵĸ�����
                          //�Ƿ�ﵽЭ��涨�����ݳ��ȣ����򷵻ؼ�����ȡ��һ���ֽ�

   ResetEvent( hEvent_RW_Trig_Angle_Enable ) ;

 //  SuspendThread( hThread_RW_Trig_Angle ) ;

}//hEvent_RW_Trig_Angle_Enable

} while( 1 ) ;//thread do while

}






HANDLE   hThread_RW_Trig_Angle ;

DWORD   dwThreadID1 ;



void CTestDlg:: Fun_RW_Trig_Angle_Init( )//�����䴥��������ȡ�������߳�
{
  /////////////create a thread
  hThread_RW_Trig_Angle = CreateThread( 0, 0, ( pfun_callback )Thread_RW_Trig_Angle, this , 
											  CREATE_SUSPENDED , &dwThreadID1 ) ;

  SetThreadPriority( hThread_RW_Trig_Angle , THREAD_PRIORITY_NORMAL ) ; 

  hEvent_RW_Trig_Angle_Enable = CreateEvent( NULL , true , false , NULL) ; 

}



#define    _AC_SHAKE_OK     0x53

#define    _TIME_MS_10      0.010

volatile   double     g_db_zero_delta_second = 0 ;

unsigned char         g_uc_trig_angle  ; //ȫ�� �������Ƕ� ������

HANDLE   hThread_Zero_Cap ;

HANDLE   hEvent_Thread_Zero_Cap_Enable ;


#define    _ZERO   0 


//���������ֳɹ��󣬶�ȡ������ִ�е������ݷ�������Ĺ�������
#define   _TIME_TRIG_CMD_READBACK_ZERO_NUMBER    ( 64 + 2 )   

void CALLBACK CTestDlg:: Thread_Zero_Cap( CTestDlg *pDlg )
{
   int   idata ;

   LARGE_INTEGER    time1 ;

   double  db_freq ;

   LONGLONG   shake_point ,  zero_point ;

   double     db_space , db_set_time ; 

   //get frequence 
   QueryPerformanceFrequency( &time1 ) ;

   db_freq = ( double ) time1.QuadPart ;
   
if( WaitForSingleObject( hEvent_Thread_Zero_Cap_Enable , 0 ) == WAIT_OBJECT_0 )
 { 
	//read the io level
  //  idata = read_io(  ) ;//�����ֵ��io�ĸ�λ��������io�ĵ�λ�����߻���Ӱ�졣
	                     //read io����һ���ַ����͵����ݺ�һ���ַ����͵�falg������Ϊ��λ�������͵�����
	                     //falg����a��b��c�����Ƿ��ǹ����

	if( idata == _AC_SHAKE_OK ) //handshake  ok
	{
       QueryPerformanceCounter( &time1 ) ;

	   shake_point = time1.QuadPart ;

       db_space = ( double ) ( shake_point - zero_point ) ;
       //�Ե����������Ϊ�ж����ݣ�����������ʱ��ʼ�մ��ڷ��������ʱ�̣������߲�ֵ���ڰ������ʱ��˵������������ڵ����������֮��
	   //�����߲�ֵС�ڰ������ʱ��˵������������ڵ��������ֵ�֮��
	   if(  db_space >= _TIME_MS_10  )//���������֮�������Ƿ�������㣬���ߵ�����֮ǰһ�������ڵķ��������
	   {
	     //�����������ڵ��������
         g_db_zero_delta_second =  ( double ) db_space / db_freq ;
         /*
         db_set_time = _TIME_TRIG_CMD_READBACK_ZERO_NUMBER * _TIME_MS_20 
			             - g_db_zero_delta_second       //130 �ܲ���ʱ���
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//��һ�������������㿪ʼ������
		                        //����ܲ���ʼ����������ܲ�180 - �����Ƕȣ�Ȼ��ת���ɶ�Ӧ��ʱ�䡣         
	     */
		  db_set_time =  0 - g_db_zero_delta_second   +    //130 �ܲ���ʱ���
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//��һ�������������㿪ʼ������
		                        //����ܲ���ʼ����������ܲ�180 - �����Ƕȣ�Ȼ��ת���ɶ�Ӧ��ʱ�䡣         
	     
		 //��ʼ����������

	//	 break ;
	   }
	   else
	   {
	     //���������С�ڵ��������
         g_db_zero_delta_second =  ( double ) db_space / db_freq ;

         db_set_time = _TIME_TRIG_CMD_READBACK_ZERO_NUMBER * _TIME_MS_10 
			             + g_db_zero_delta_second +      //130 �ܲ���ʱ���
						 ( 180 - g_uc_trig_angle ) * 1 / 18.0 ;//��һ�������������㿪ʼ������
		
	   }
	   
	 }
	//failing edge of io , ���������
	if( idata == _ZERO )
	{
	  QueryPerformanceCounter( &time1 ) ;

	  zero_point = time1.QuadPart ;
	}




}

}






void CTestDlg:: Fun_PC_Zero_Cap_init( )
{
  /////////////create a thread
  hThread_Zero_Cap = CreateThread( 0, 0, ( pfun_callback)Thread_Zero_Cap, this , 
											  CREATE_SUSPENDED , &dwThreadID1 ) ;

  SetThreadPriority( hThread_Zero_Cap , THREAD_PRIORITY_ABOVE_NORMAL ) ; 

  hEvent_Thread_Zero_Cap_Enable = CreateEvent( NULL , true , false , NULL) ; 
}
