// TTTView.cpp : implementation of the CTTTView class
//

#include "stdafx.h"
#include "TTT.h"
#include "stdlib.h"
#include "math.h"
#include "TTTView.h"
#include "MainFrm.h"
#include "DisplayAnalyzeWin.h"
#include "TTTDoc.h"
#include "Dask.h"
#include "SwitchLineDlg.h"
#include "AngleSet.h"
#include "ras.h."
#include "bch63457.h"
#include "TestDlg.h"
#include "ChangeFileDlg.h"
#include "SendEveryTime.h"
#include "TIMEDLG.h"
#include "Afxmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
POINT input_pos[16]= {{470, 280},  {440, 280},
                       {410, 280},  {380, 280},
                       {350, 280},  {320, 280},
                       { 290, 280},  {260, 280},
                       {230, 280},  {200, 280},
                       {170, 280},  {140, 280},
                       {110, 280},  {80, 280},
                       { 50, 280},  { 20, 280},
                      };
POINT output_pos[16] ={
                       {470, 340},  {440, 340},
                       {410, 340},  {380, 340},
                       {350, 340},  {320, 340},
                       { 290, 340},  {260, 340},
                       {230, 340},  {200, 340},
                       {170, 340},  {140, 340},
                       {110, 340},  {80, 340},
                       { 50, 340},  { 20, 340},
                      };

POINT io_pos[16] ={
                       {395, 40},  {370, 40},
                       {345, 40},  {320, 40},
                       {295, 40},  {270, 40},
                       { 245, 40},  {220, 40},
                       {195, 40},  {170, 40},
                       {145, 40},  {120, 40},
                       {95, 40},  {70, 40},
                       { 45, 40},  { 20, 40},
                      };

//��ؼ������ݱ� 20��
short Correlation_Table20[256] = 
{
  -6,  -6,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -7,  -5,  -5,  -6,  -6,
  -5,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -6,  -5,  -6,  -6,  -6,  -6,
  -5,  -7,  -6,  -6,  -5,  -6,  -7,  -7,  -6,  -6,  -5,  -6,  -6,  -6,  -5,  -5,
  -5,  -4,  -5,  -6,  -5,  -4,  -5,  -6,  -6,  -5,  -6,  -5,  -5,  -5,  -5,  -5,
  -5,  -6,  -6,  -6,  -6,  -6,  -7,  -7,  -6,  -5,  -6,  -6,  -6,  -5,  -5,  -4,
  -4,  -4,  -4,  -5,  -4,  -5,  -5,  -5,  -4,  -5,  -5,  -5,  -5,  -5,  -6,  -6,
  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -5,  -5,  -4,  -6,
  -5,  -6,  -4,  -4,  -5,  -5,  -6,  -5,  -5,  -5,  -6,  -5,  -6,  -6,  -6,  -6,
  -6,  -7,  -6,  -7,  -6,  -4,  -7,  -7,  -5,  -5,  -5,  -5,  -5,  -4,  -5,  -4,
  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -5,  -4,  -5,  -4,  -4,  -5,  -4,  -5,  -5,
  -4,  -5,  -5,  -3,  -5,  -4,  -4,  -4,  -5,  -4,  -4,  -4,  -4,  -4,  -3,  -4,
   4,   9,  15,  47,  84, 125, 190, 281, 414, 586, 790,1005,1212,1395,1543,1656,
1733,1783,1807,1812,1804,1786,1765,1743,1719,1699,1678,1661,1646,1631,1618,1605,
1592,1576,1559,1537,1514,1485,1454,1417,1376,1330,1281,1228,1171,1111,1051, 988,
 920, 858, 792, 727, 664, 600, 538, 480, 423, 368, 315, 269, 228, 187, 153, 121,
  96,  69,  49,  31,  14,  -2, -16, -29, -40, -51, -59, -60, -55, -52, -47, -49
};

//��ؼ������ݱ� 10��
short Correlation_Table10[256] = 
{
	  -3,  -3,  -3,  -2,  -3,  -2,  -3,  -2,  -4,  -2,  -4,  -2,  -3,  -3,  -3,  -3,
	  -3,  -2,  -2,  -3,  -2,  -3,  -2,  -3,  -2,  -3,  -3,  -2,  -3,  -3,  -3,  -2,
	  -3,  -1,  -4,  -1,  -4,  -2,  -4,  -2,  -4,  -3,  -3,  -3,  -4,  -3,  -5,  -3,
	  -3,  -2,  -3,  -3,  -3,  -4,  -4,  -3,  -2,  -3,  -2,  -2,  -3,  -2,  -1,  -3,
	  -2,  -2,  -2,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -4,  -2,  -3,  -3,  -4,
	  -3,  -4,  -4,  -3,  -3,  -4,  -3,  -3,  -2,  -3,  -2,  -2,  -3,  -3,  -2,  -2,
	  -3,  -2,  -3,  -3,  -2,  -1,  -3,  -2,  -2,  -3,  -2,  -1,  -1,  -2,  -2,  -2,
	  -3,  -2,  -1,  -1,  -2,  -2,  -2,  -2,  -2,  -3,  -3,  -3,  -3,  -3,  -4,  -4,
	  -3,  -3,  -4,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -1,
	  -1,  -1,  -2,  -1,  -2,  -1,  -1,  -2,  -2,  -1,  -1,  -1,  -2,  -1,  -1,  -1,
	  -2,   0,  -1,  -1,  -1,  -1,  -2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -2,
	  -3,  -2,  -2,  -1,  -1,   0,  -1,   0,   1,   6,  14,  20,  26,  32,  37,  45,
	  54,  61,  72,  85,  98, 113, 130, 148, 170, 192, 216, 242, 267, 292, 316, 339,
	 362, 383, 398, 415, 425, 433, 440, 442, 440, 440, 433, 426, 414, 403, 389, 376,
	 362, 346, 330, 314, 296, 281, 265, 250, 233, 217, 201, 184, 168, 153, 140, 126,
	 113, 101,  89,  79,  69,  57,  51,  42,  36,  28,  21,  15,  11,   6,   0,  -3
};

//��ؼ������ݱ� 5��
short Correlation_Table05[256] = 
{
   -3,   -3,   -3,   -2,   -3,   -2,   -3,   -2,   -4,   -2,   -4,   -2,   -3,   -3,   -3,   -3,
   -3,   -2,   -2,   -3,   -2,   -3,   -2,   -3,   -2,   -3,   -3,   -2,   -3,   -3,   -3,   -2,
   -2,   -2,   -3,   -2,   -3,   -3,   -3,   -3,   -4,   -3,   -3,   -3,   -4,   -3,   -5,   -3,
   -2,   -3,   -3,   -3,   -3,   -4,   -3,   -3,   -3,   -3,   -2,   -3,   -2,   -2,   -2,   -2,
   -2,   -2,   -2,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -3,   -4,   -2,   -3,   -3,   -4,
   -3,   -4,   -4,   -3,   -3,   -4,   -3,   -3,   -2,   -3,   -2,   -2,   -3,   -3,   -2,   -2,
   -3,   -2,   -3,   -3,   -1,   -2,   -3,   -2,   -2,   -2,   -3,    0,   -3,    0,   -3,   -2,
   -3,   -1,   -1,   -2,   -2,   -2,   -2,   -2,   -2,   -3,   -3,   -3,   -3,   -3,   -4,   -4,
   -3,   -3,   -4,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -1,   -2,
   -1,   -1,   -2,   -1,   -2,   -1,   -1,   -2,   -2,   -1,   -1,   -1,   -2,   -1,    0,   -2,
   -1,   -1,   -1,   -1,   -1,   -1,   -2,   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -2,
   -3,   -2,   -2,   -1,    0,   -1,   -1,   -1,   -2,   -2,   -1,    0,    0,   -1,    0,    0,
   -1,   -1,    0,   -1,   -2,   -1,   -1,    0,    0,    0,    0,    1,    4,    9,   16,   22,
   27,   35,   39,   47,   56,   64,   77,   88,  101,  118,  135,  155,  174,  196,  221,  248,
  271,  297,  320,  334,  334,  284,  269,  254,  237,  222,  203,  188,  172,  157,  143,  130,
  116,  104,   92,   82,   70,   60,   53,   44,   37,   30,   22,   17,   12,    8,    0,   -1,
};

//��ؼ������ݱ� 20��
short  SourceArrays[256] = 
	{ 
	  -6,  -6,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -7,  -5,  -5,  -6,  -6,
	  -5,  -6,  -6,  -5,  -6,  -5,  -6,  -5,  -5,  -6,  -6,  -5,  -6,  -6,  -6,  -6,
	  -5,  -7,  -6,  -6,  -5,  -6,  -7,  -7,  -6,  -6,  -5,  -6,  -6,  -6,  -5,  -5,
	  -5,  -4,  -5,  -6,  -5,  -4,  -5,  -6,  -6,  -5,  -6,  -5,  -5,  -5,  -5,  -5,
	  -5,  -6,  -6,  -6,  -6,  -6,  -7,  -7,  -6,  -5,  -6,  -6,  -6,  -5,  -5,  -4,
	  -4,  -4,  -4,  -5,  -4,  -5,  -5,  -5,  -4,  -5,  -5,  -5,  -5,  -5,  -6,  -6,
	  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -6,  -5,  -5,  -4,  -6,
	  -5,  -6,  -4,  -4,  -5,  -5,  -6,  -5,  -5,  -5,  -6,  -5,  -6,  -6,  -6,  -6,
	  -6,  -7,  -6,  -7,  -6,  -4,  -7,  -7,  -5,  -5,  -5,  -5,  -5,  -4,  -5,  -4,
	  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -5,  -4,  -5,  -4,  -4,  -5,  -4,  -5,  -5,
	  -4,  -5,  -5,  -3,  -5,  -4,  -4,  -4,  -5,  -4,  -4,  -4,  -4,  -4,  -3,  -4,
	   4,   9,  15,  47,  84, 125, 190, 281, 414, 586, 790,1005,1212,1395,1543,1656,
	1733,1783,1807,1812,1804,1786,1765,1743,1719,1699,1678,1661,1646,1631,1618,1605,
	1592,1576,1559,1537,1514,1485,1454,1417,1376,1330,1281,1228,1171,1111,1051, 988,
	 920, 858, 792, 727, 664, 600, 538, 480, 423, 368, 315, 269, 228, 187, 153, 121,
	  96,  69,  49,  31,  14,  -2, -16, -29, -40, -51, -59, -60, -55, -52, -47, -49
	};

//��ؼ������ݱ� 5��
long CorrelationSix_Table05[25] =
{ 
   0,     0,    0,     0,    9,
   28,   47,   76,   118,  175, 
  246,  317,  295,   237,   187, 
  143,  104,   70,    44,    23,
    6,    1,    0,     0,     0  
};

//��ؼ������ݱ� 10��
long CorrelationSix_Table10[25] =
{ 
  -3,   2,   20,   38,   62, 
  98, 149,  216,  291,  361,
 412, 438,  437,  414,  375,
 330,  280, 233,  184,  139,
 101,   68,  43,   21,    5
};

//��ؼ������ݱ� 20��
long CorrelationSix_Table20[25] =
{ 
   -1,   23,  133,  427, 1002,
 1531, 1774, 1800, 1742, 1679,
 1631, 1591, 1536, 1452, 1329,
 1170,  986,  792,  600,  423,
  270,  153,   71,   14,   -4
};

/////////////////////////////////////////////////////////////////////////////
// CTTTView 117 248
short DataBuf[1000000];//135000 ȫ�ɵĻ���512*4*4*63 = 516096
short TempDataBuf[1000000];
int   DiffAll[200000],SumAll[20000];
int   DataLen,RecCount;
unsigned  short  Value;
float  g_GainSampleWin;
float g_CurrentGainSampleWin;
BOOL     m_TestPhase = FALSE;
short       	m_TestCurrent[140000];//����
short           m_TestVoltage[140000];//��ѹ
int             m_TestParameter[6];

U32   nReadCount = 2048;
I16   card;
UINT  SampleRate;
BOOL  bClearOp, bClearOp1, bParity, bClearRecv;
CDisplayWaveWin    m_wndWaveWin;
CDisplayAnalyzeWin m_wndAnalyzeWin;
I16                       err;
unsigned short ReadBuff[1024];
int               m_DivideVal;    //�ɵ���Ҫ����ֵ1��PCI-9111DR   16     2��PCI-9111HR     1 
CEvent            eventWriteD;


#define LASTCHANNEL   15//15//;//
#define DISPWINWIDTH 640

IMPLEMENT_DYNCREATE(CTTTView, CFormView)

BEGIN_MESSAGE_MAP(CTTTView, CFormView)
//{{AFX_MSG_MAP(CTTTView)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
ON_CBN_SELCHANGE(IDC_COMBO_SMPRATE, OnSelchangeComboSmprate)
ON_BN_CLICKED(IDC_CHECK_CH3, OnCheckCh3)
ON_BN_CLICKED(IDC_CHECK_CH0, OnCheckCh0)
ON_BN_CLICKED(IDC_CHECK_CH1, OnCheckCh1)
ON_BN_CLICKED(IDC_CHECK_CH2, OnCheckCh2)
ON_BN_CLICKED(IDC_CHECK_CH4, OnCheckCh4)
ON_BN_CLICKED(IDC_CHECK_CH5, OnCheckCh5)
ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
ON_EN_CHANGE(IDC_EDIT_STARTPOINT, OnChangeEditStartpoint)
ON_CBN_SELCHANGE(IDC_COMBO_CYCLENUM, OnSelchangeComboCyclenum)
ON_EN_CHANGE(IDC_EDIT_GAIN, OnChangeEditGain)
ON_BN_CLICKED(IDC_RADIO_REALTIME, OnRadioRealtime)
ON_BN_CLICKED(IDC_RADIO_ANALYZE, OnRadioAnalyze)
ON_BN_CLICKED(IDC_BUTTON_SHIFTLEFT, OnButtonShiftleft)
ON_BN_CLICKED(IDC_BUTTON_SHIFTRIGHT, OnButtonShiftright)
ON_BN_CLICKED(IDC_BUTTON_ASHIFTLEFT, OnButtonAshiftleft)
ON_BN_CLICKED(IDC_BUTTON_ASHIFTRIGHT, OnButtonAshiftright)
ON_EN_CHANGE(IDC_EDIT_GAINSMPWIN, OnChangeEditGainsmpwin)
ON_CBN_SELCHANGE(IDC_COMBO_CHSELECT, OnSelchangeComboChselect)
ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
ON_BN_CLICKED(IDC_CHECK_AVER4, OnCheckAver4)
ON_BN_CLICKED(IDC_CHECK_DIFFI, OnCheckDiffi)
ON_EN_CHANGE(IDC_EDIT_ANGLE, OnChangeEditAngle)
ON_EN_CHANGE(IDC_EDIT_THRESHOLD, OnChangeEditThreshold)
ON_EN_CHANGE(IDC_EDIT_SENDCODE, OnChangeEditSendcode)
ON_BN_CLICKED(IDC_CHECK_CH10, OnCheckCh10)
ON_BN_CLICKED(IDC_CHECK_CH9, OnCheckCh9)
ON_BN_CLICKED(IDC_CHECK_CH8, OnCheckCh8)
ON_BN_CLICKED(IDC_CHECK7, OnCheckBandPass)
ON_EN_CHANGE(IDC_EDIT_BANDPASSANGLE, OnChangeEditBandpassangle)
ON_BN_CLICKED(IDC_CHECK_DVDT, OnCheckDvdt)
ON_BN_CLICKED(IDC_REAL_START, OnRealStart)
ON_BN_CLICKED(IDC_REALSTOP, OnRealstop)
ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
ON_BN_CLICKED(IDC_BUTTON_ANGLE, OnButtonAngle)
ON_BN_CLICKED(IDC_REAL_RECORD, OnRealRecord)
ON_BN_CLICKED(IDC_REAL_SEND, OnRealSend)
ON_BN_CLICKED(IDC_BUTTON_STOPREC, OnButtonStoprec)
ON_BN_CLICKED(IDC_READLINE, OnReadline)
	ON_CBN_SELCHANGE(IDC_PROTOCOLS, OnSelchangeProtocols)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_SETTIMER, OnSettimer)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_ZHONGZHI, OnZhongzhi)
	ON_BN_CLICKED(IDC_DECODE, OnDecode)
	ON_BN_CLICKED(IDC_FFT, OnFft)
	ON_BN_CLICKED(IDC_READFILTER, OnReadfilter)
	ON_BN_CLICKED(IDC_DELETEFILE, OnDeletefile)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_BCHTEST, OnBchtest)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK_DIFFI2, OnCheckDiffi2)
	ON_BN_CLICKED(IDC_CHECK_DIFFI3, OnCheckDiffi3)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_TESTDATA, OnTestdata)
	ON_EN_CHANGE(IDC_STARTPOINT, OnChangeStartpoint)
	ON_EN_CHANGE(IDC_WAVEPOINTS, OnChangeWavepoints)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPINSTART, OnOutofmemorySpinstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINSTART, OnDeltaposSpinstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINAVERAGE, OnDeltaposSpinaverage)
	ON_BN_CLICKED(IDC_FINDZERO, OnFindzero)
	ON_BN_CLICKED(IDC_ALLADD, OnAlladd)
	ON_EN_CHANGE(IDC_ALLTIMES, OnChangeAlltimes)
	ON_BN_CLICKED(IDC_INITIALIZE, OnInitialize)
	ON_BN_CLICKED(IDC_COMSET, OnComset)
	ON_EN_CHANGE(IDC_ANGLE, OnChangeAngle)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHANGEUSEDATA, OnChangeusedata)
	ON_BN_CLICKED(IDC_SENDALLONE, OnSendallone)
	ON_BN_CLICKED(IDC_BUTTON_TESTPHASE, OnButtonTestphase)
	ON_EN_CHANGE(IDC_EDIT_CURRENTGAINSMPWIN, OnChangeEditCurrentgainsmpwin)
	ON_CBN_SELCHANGE(IDC_ORDERCOMBO, OnSelchangeOrdercombo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP

// Standard printing commands
ON_MESSAGE(WM_EVENT, OnEvent)
ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTTView construction/destruction
//
CTTTView::CTTTView()
: CFormView(CTTTView::IDD)
{
	//{{AFX_DATA_INIT(CTTTView)
	m_iSampleRate =     9;
	m_bCh0        = FALSE;
	m_bCh1        = FALSE;
	m_bCh2        = FALSE;
	m_bCh3        = FALSE;
	m_bCh4        = FALSE;
	m_bCh5        = FALSE;
	m_bCh8        = FALSE;
	m_bCh9        = FALSE;
	m_bCh10       = FALSE;
	m_nStartPoint = 0;
	m_nCycleNum   = 0;
	m_iCycleNum   = -1;
	m_iModeSel    = 0;
	m_fGain       = 0.0f;
	m_fGainSampleWin = 0.0f;
	m_iChSelect   = 0;
	m_bDiff2      = FALSE;
	m_bAver4      = FALSE;
	m_bDiffI      = TRUE;
	m_bBandPass   = FALSE;
	m_generatrix  =     0;
	m_phase       =     0;
	m_module      = 13107101;
	m_data        = _T("");
	m_tong789     =  FALSE;
	m_SendOrder   = _T("");
	m_ReceiveStr  = _T("");
	m_addone      =  FALSE;
	m_IfWriteToLog = FALSE;
	m_qzhikiu      = FALSE;
	m_bDiff3       = FALSE;
	m_findpipeimax =  TRUE;
	m_radio        =     1;
	m_quancai      = FALSE;
	m_AllAdd       = FALSE;
	m_alltimes     =     1;
	m_delay        =  1000;
	m_angle        =    20;
	m_derrors      =    31;
	m_check4bit    = FALSE;
	m_xinjiaobian  = FALSE;
	m_Is0Station   =  TRUE;
	m_fCurrentGainSampleWin = 1.0f;
	m_equal = FALSE;
	m_wavepoints   =   512;
	m_millondseconds = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_fGain           =  1.0;
	m_iCycleNum       =    2;
	m_fGainSampleWin  =  1.0;
	m_iChSelect       =    0;
	Line              =    0;
	m_angles          =    0;
	m_iBandPassPoints =   62;//128;

	m_startpoint      = 1024;
	m_wavepoints      =  512;

	//ͨ�� 
	m_Channels        =   1;
	m_Stopping        = FALSE;

	m_SuccessTimes    =   0;
   	m_TotalTimes      =   0;
	m_CollectErrors   =   0;//�ɼ�����
	
	CTTTApp * pt = (CTTTApp*)AfxGetApp();
    
	if(pt->m_ifcardis9111dr)
	{	
		m_maxDecimalVal = 4096;//���ֵ        1��PCI-9111DR 4096     2��PCI-9111HR 65536 
		m_DivideVal     =   16;//�ɵ���Ҫ����ֵ1��PCI-9111DR   16     2��PCI-9111HR     1 
	}
	else
	{
		m_maxDecimalVal = 65536;//���ֵ        1��PCI-9111DR 4096     2��PCI-9111HR 65536 
		m_DivideVal     =     1;//�ɵ���Ҫ����ֵ1��PCI-9111DR   16     2��PCI-9111HR     1 
	} 

	m_StatusStr      =      "";
	
	m_TestPhase      =   FALSE;
	m_TimeSeconds    =       0;

}

CTTTView::~CTTTView()
{

	bClearOp  = TRUE;
	Sleep(200);

}

void CTTTView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTTView)
	DDX_Control(pDX, IDC_ORDERCOMBO, m_ordercombo);
	DDX_Control(pDX, IDC_COMBO_SMPRATE, m_SmprateComb);
	DDX_Control(pDX, IDC_PROTOCOLS, m_ProtocolControl);
	DDX_Control(pDX, IDC_CHECKCOMBOX, m_comcheck);
	DDX_Control(pDX, IDC_DATACOMBO, m_comdata);
	DDX_Control(pDX, IDC_STOPCOMBO, m_comstop);
	DDX_Control(pDX, IDC_COMBOBIT, m_combobit);
	DDX_Control(pDX, IDC_COMBOPORT, m_comboport);
	DDX_Control(pDX, IDC_SPINAVERAGE, m_SpinAverage);
	DDX_Control(pDX, IDC_SPINSTART, m_Spinstart);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_CBIndex(pDX, IDC_COMBO_SMPRATE, m_iSampleRate);
	DDX_Check(pDX, IDC_CHECK_CH0, m_bCh0);
	DDX_Check(pDX, IDC_CHECK_CH1, m_bCh1);
	DDX_Check(pDX, IDC_CHECK_CH2, m_bCh2);
	DDX_Check(pDX, IDC_CHECK_CH3, m_bCh3);
	DDX_Check(pDX, IDC_CHECK_CH4, m_bCh4);
	DDX_Check(pDX, IDC_CHECK_CH5, m_bCh5);
	DDX_Check(pDX, IDC_CHECK_CH8, m_bCh8);
	DDX_Check(pDX, IDC_CHECK_CH9, m_bCh9);
	DDX_Check(pDX, IDC_CHECK_CH10, m_bCh10);
	DDX_Text(pDX, IDC_EDIT_STARTPOINT, m_nStartPoint);
	DDX_CBIndex(pDX, IDC_COMBO_CYCLENUM, m_iCycleNum);
	DDX_Radio(pDX, IDC_RADIO_REALTIME, m_iModeSel);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_fGain);
	DDX_Text(pDX, IDC_EDIT_GAINSMPWIN, m_fGainSampleWin);
	DDX_CBIndex(pDX, IDC_COMBO_CHSELECT, m_iChSelect);
	DDX_Check(pDX, IDC_CHECK_DIFFI2, m_bDiff2);
	DDX_Check(pDX, IDC_CHECK_AVER4, m_bAver4);
	DDX_Check(pDX, IDC_CHECK_DIFFI, m_bDiffI);
	DDX_Check(pDX, IDC_CHECK7, m_bBandPass);
	DDX_Text(pDX, IDC_GENERATRIX, m_generatrix);
	DDX_Text(pDX, IDC_PHASE, m_phase);
	DDX_Text(pDX, IDC_MODULE, m_module);
	DDX_Text(pDX, IDC_DATAVALUE, m_data);
	DDX_Check(pDX, IDC_CHECK5, m_tong789);
	DDX_Text(pDX, IDC_SENDORDER, m_SendOrder);
	DDX_Text(pDX, IDC_RECEIVE, m_ReceiveStr);
	DDX_Check(pDX, IDC_ADDONE, m_addone);
	DDX_Check(pDX, IDC_CHECK9, m_IfWriteToLog);
	DDX_Check(pDX, IDC_CHECK10, m_qzhikiu);
	DDX_Check(pDX, IDC_CHECK_DIFFI3, m_bDiff3);
	DDX_Check(pDX, IDC_FINDPIPEVALUE, m_findpipeimax);
	DDX_Radio(pDX, IDC_RADIO3, m_radio);
	DDX_Check(pDX, IDC_CHECK11, m_quancai);
	DDX_Check(pDX, IDC_ALLADD, m_AllAdd);
	DDX_Text(pDX, IDC_ALLTIMES, m_alltimes);
	DDX_Control(pDX, IDC_MSCOMM, m_Com);
	DDX_Text(pDX, IDC_DELAY, m_delay);
	DDX_Text(pDX, IDC_ANGLE, m_angle);
	DDX_Text(pDX, IDC_EDITT, m_derrors);
	DDX_Check(pDX, IDC_CHECK4BIT, m_check4bit);
	DDX_Check(pDX, IDC_CHECK12, m_xinjiaobian);
	DDX_Check(pDX, IDC_IS0STATION, m_Is0Station);
	DDX_Text(pDX, IDC_EDIT_CURRENTGAINSMPWIN, m_fCurrentGainSampleWin);
	DDX_Check(pDX, IDC_CHECK13, m_equal);
	DDX_Text(pDX, IDC_DELAYHAOMIAO, m_millondseconds);
	//}}AFX_DATA_MAP
}

BOOL CTTTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}



void CTTTView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	CString                    str;
    SampleRate             =     9;
    g_Gain                 =     1;
	g_GainSampleWin        =     1;
	g_CurrentGainSampleWin =     1;
    g_Extend               =     10;
	CycleNum               =     1;
	PointsNum              =   512;//1/4��
    bParity                = FALSE;
	bFlash                 = FALSE;
	bClearRecv             = FALSE;
	MinSum                 =  1000;
	BandPassAngle          =    45;
	m_protocol             =    71;

    CTTTApp * pt = (CTTTApp*)AfxGetApp();

    if(pt->m_ifcardis9111dr)
	{
		
		if((card = Register_Card(PCI_9111DG, 0)) <0 ) 
		{
			 
			MessageBox("�ɼ�����ʼ��ʱ���󣬼��ɼ����Ƿ�װ���ɶ���\r\n�������ɼ��ȹ��ܲ���ʱ�������","����",MB_OK|MB_ICONWARNING);
		
		}

	}
	else
	{
		
		if((card = Register_Card(PCI_9111HR, 0)) <0 ) 
		{
		
			MessageBox("�ɼ�����ʼ��ʱ���󣬼��ɼ����Ƿ�װ���ɶ���\r\n�������ɼ��ȹ��ܲ���ʱ�������","����",MB_OK|MB_ICONWARNING);
		
		}

	}
	
  //err = AI_9111_Config(card, TRIG_EXT_STROBE, 0, 1024);
	err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    //Beep(300,400);
		
    }
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
    if (err!=0)
	{
    	//Beep(300,400);
		
    }
	
	/*
	
	*/
	////////////////////////////////////////
	
	m_wndWaveWin.SubclassDlgItem(IDC_WAVE, this);
    m_wndAnalyzeWin.SubclassDlgItem(IDC_ANALYZE, this);

	//��λ
	m_spin3.SetRange(0, 2);
	m_spin3.SetPos(0);
	//ĸ�߱��
	m_spin4.SetRange(1, 4);
	m_spin4.SetPos(1);

	
	m_Spinstart.SetRange(0,2500);
	m_Spinstart.SetPos(1024);
	
	m_SpinAverage.SetRange(400,5000);
	m_SpinAverage.SetPos(512);

    OnRadio1();

	CEdit* pyy = (CEdit*)GetDlgItem(IDC_ORDER);
    pyy->SetLimitText(2);
	pyy = (CEdit*)GetDlgItem(IDC_ORDER);
    pyy->SetWindowText("02");

	m_SmprateComb.ResetContent();

	for(int i = 10; i <= 100; i = i + 10)
	{
		str.Format("%3d",i);
		m_SmprateComb.AddString(str);

	}

    m_SmprateComb.SetCurSel(9);

	OnRadioRealtime();

	m_ProtocolControl.ResetContent();
	m_ProtocolControl.AddString("21");
    m_ProtocolControl.AddString("22");
    m_ProtocolControl.AddString("31");
    m_ProtocolControl.AddString("32");
	m_ProtocolControl.AddString("61");
    m_ProtocolControl.AddString("62");
	m_ProtocolControl.AddString("71");
    m_ProtocolControl.AddString("72");
    m_ProtocolControl.AddString("73");

    m_ProtocolControl.SetCurSel(6);
	
	InitOrderCombo(71);

	OnSelchangeProtocols();
	
	GetDlgItem(IDC_CHECK13)->EnableWindow(FALSE);

	//��ʼ���˿�
	GetComPorts();
	
}


UINT WriteD(LPVOID pParam)
{	
	Beep(5000,400);
	int type =(int)pParam;
	CMainFrame* pts   = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pts->GetActiveView());
	WaitForSingleObject(eventWriteD.m_hObject,INFINITE);
	Beep(5000,400);
	//������
   	pview->SendOrderToSCM(115/*ģ���*/,0/*�����ֵ�վ��*/,1/*ĸ��*/,1 + 1/*�ߺ�*/,0/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,0x02/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);
	return 0;

}

/////////////////////////////////////////////////////////////////////////////
// CTTTView printing

BOOL CTTTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTTTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTTTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTTTView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTTTView diagnostics

#ifdef _DEBUG
void CTTTView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTTTView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTTTDoc* CTTTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTTTDoc)));
	return (CTTTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTTView message handlers

BOOL CTTTView::DestroyWindow() 
{
	Release_Card(card);
    KillTimer(1);  
	KillTimer(2); 
	return CFormView::DestroyWindow();
}

void CTTTView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:
		{
			KillTimer(1);
			//��鴮�����
			CheckComData();
			break;
		}
	case 2:
		{
			//ȫ��1
			SendAllOne();
			break;
		}
	}

	CFormView::OnTimer(nIDEvent);
}

UINT  ScanChannels(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	CString                  str;
	unsigned short ReadBuf[1024];
    BOOLEAN    bHalfReady, bStop;
	float                  m_kkk;

    U32  count1,count2 =     0;
    do{
		do {
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStop);
		} while (!bHalfReady);

		AI_AsyncDblBufferTransfer(card, ReadBuf);

		//��789ͨ������������
		m_wndWaveWin.NewDataIn(ReadBuf,nReadCount/2); 

	}while(!bClearOp);

    AI_AsyncClear(card, &count1);
	
    return 0;
}

void CTTTView::OnButtonStart() 
{
	//��ʾ���ι���
	m_ShowWave     =   FALSE;
  	g_Extend       =      10;
	UpdateData(FALSE);
	m_TestPhase    =   FALSE;

	unsigned short *ai_buf=NULL;
    I16 err;
	
    err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    Beep(300,400);
		return;
    }
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
  
	err = AI_ContScanChannels(card,LASTCHANNEL, AD_B_10_V, ai_buf, nReadCount,(SampleRate+1)*1000, ASYNCH_OP);
  	
	AfxBeginThread(ScanChannels,this);
	bClearOp = 0;
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMSET)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);
}

void CTTTView::OnButtonStop() 
{
	bClearOp   =      1;	
//	m_TestPhase = FALSE;

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMSET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(TRUE);
}


void CTTTView::OnSelchangeComboSmprate() 
{
	UpdateData();
	SampleRate = m_iSampleRate;
}

void CTTTView::OnCheckCh3() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        = 3;
}

void CTTTView::OnCheckCh0() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  0;
}

void CTTTView::OnCheckCh1() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  1;
}

void CTTTView::OnCheckCh2() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  2;
}

void CTTTView::OnCheckCh4() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  4;
}

void CTTTView::OnCheckCh5() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  5;
}

void CTTTView::OnCheckCh8() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  8;
}

void CTTTView::OnCheckCh9() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  9;
}

void CTTTView::OnCheckCh10() 
{
	UpdateData();
	//ͨ�� 
	m_Channels        =  10;
}


void CTTTView::OnChangeEditStartpoint() 
{
	UpdateData();
	OnButtonUpdate();
}

void CTTTView::OnSelchangeComboCyclenum() 
{
	UpdateData();
	

	switch(m_iCycleNum)
	{
	case 0:
		{
			CycleNum = 1; 
			g_Extend = DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 1:
		{
			CycleNum = 2; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 2:
		{
			CycleNum = 4;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 3:
		{
			CycleNum = 8;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/8;
		    break;
		}
	case 4: 
		{	
			CycleNum = 16; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/16;
		    break;
		}
	}
    OnButtonUpdate();
	
}


int CTTTView::FindZeroPointCao(UINT WaveNum)
{
    UINT CntPoint=0,CntCycle  =     0;
	UINT temp,CurZeroPoint    =     0;
	BOOL bReady               = FALSE;
	
    do{
       	temp = DataBuf[CntPoint++];

		if(temp > m_maxDecimalVal/2 - 1)
		{ 
			
			if(CntPoint > CurZeroPoint+10)
			{
				
				bReady = TRUE; 

			}

		}
		else
		{			
			if(bReady)
			{

				if( DataBuf[CntPoint + 10 ]< m_maxDecimalVal/2)
				{  
					CurZeroPoint = CntPoint;
					bReady       = FALSE; 
					CntCycle++;
				}

			}
			
		}
		
	}while(CntCycle<WaveNum+1);
	
	return CntPoint-1;
}

int CTTTView::FindCyclePointsNum(int WaveNum)
{
	UINT cnt=0, cnt1=0;
	int iPointsNum=0;
	char buf[6];
	double temp;
	BOOL bOverZero=false,bReady=false, bExit=false;
	
	do{
		file.Seek(36+WaveNum*2000*8+cnt*8,CFile::begin);
		file.Read(buf,6);
		temp=atof(buf);
		
		if(!bReady)
		{
			if(temp<0)
				bReady=true;   
		}
		else
		{
			if(temp>=0)
			{ 
				bReady   = false; 
				bOverZero=  true;
				cnt1          ++;
			}

		}

		if(bOverZero)
			iPointsNum++;
		if(cnt1==5)
			bExit=true; 
		cnt++;
	}while(!bExit);
	
	return iPointsNum/4;
}

void CTTTView::OnChangeEditGain() 
{
	CString str;
	UpdateData();
	g_Gain = m_fGain;
    str.Format("   +%3.3fV -",10/m_fGain);
	GetDlgItem(IDC_STATIC_ANALYZESCALEP)->SetWindowText(str);
    str.Format("   -%3.3fV -",10/m_fGain);
	GetDlgItem(IDC_STATIC_ANALYZESCALEN)->SetWindowText(str);
	OnButtonUpdate();
}

void CTTTView::OnChangeEditGainsmpwin() 
{
	CString str;
	UpdateData();

	Invalidate();

	g_GainSampleWin        = m_fGainSampleWin;
	g_CurrentGainSampleWin = m_fCurrentGainSampleWin;	

	str.Format("+%3.2fV(+%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEP)->SetWindowText(str);
    str.Format("-%3.2fV(-%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEN)->SetWindowText(str);

	if(m_iModeSel > 0)
	{
	    OnButtonUpdate();
	}
}

void CTTTView::OnRadioRealtime() 
{
	m_TestPhase = FALSE;
	UpdateData();	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE); 
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE); 
	GetDlgItem(IDC_REAL_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	GetDlgItem(IDC_READLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_SETTIMER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(TRUE);

 //   GetDlgItem(IDC_CHECK11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_HIDE);
}   

void CTTTView::OnRadioAnalyze() 
{
	m_TestPhase = FALSE;

	UpdateData();
	
	if(!m_ShowWave)
	{
		Invalidate();
	}

	m_ShowWave     =   TRUE;
    
	switch(CycleNum)
	{
	case 1: 
		{
			g_Extend=DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 2:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 4:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 8:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/8;
			break;
		}
	case 16:
		{
			g_Extend=(DISPWINWIDTH/(float)PointsNum)/16;
			break;
		}
	}
	
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(TRUE);
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_REAL_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_REAL_START)->SetWindowText("����");
	GetDlgItem(IDC_REALSTOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
    GetDlgItem(IDC_SETTIMER)->EnableWindow(TRUE);
	GetDlgItem(IDC_DECODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);


//	GetDlgItem(IDC_CHECK11)->EnableWindow(FALSE);//TRUE
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_HIDE);
  
	OnSelchangeProtocols();
}

void CTTTView::OnButtonUpdate() 
{
	CString                str;
   	int        iWaveAll[80000];	
	UpdateData(TRUE);

  	m_startpoint = m_Spinstart.GetPos();
	m_wavepoints = m_SpinAverage.GetPos();

	if(m_wavepoints > 5000)
	{
		MessageBox("���Ӽ��̫��[400,5000]��","",MB_OK|MB_ICONWARNING);
		return;
	}

	PointsNum         =   m_wavepoints;          //ÿ�����ɵĵ���
	MaxCycleNum       =   (DataLen-m_startpoint)/PointsNum;     //�ɵ������
	
	switch(m_iCycleNum)
	{
	case 0:
		{
			CycleNum = 1; 
			g_Extend = DISPWINWIDTH/(float)PointsNum;
			break;
		}
	case 1:
		{
			CycleNum = 2; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/2;
			break;
		}
	case 2:
		{
			CycleNum = 4;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/4;
			break;
		}
	case 3:
		{
			CycleNum = 8;
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/8;
		    break;
		}
	case 4: 
		{	
			CycleNum = 16; 
			g_Extend = (DISPWINWIDTH/(float)PointsNum)/16;
		    break;
		}
	}

	BandPassAngle     =   int(m_iBandPassPoints*180.00/PointsNum + 0.5);

	for(int j = 0; j < CycleNum; j++)
	{

		//�����ԭ���Ĵ�Ļ�
		if(m_nStartPoint + j > MaxCycleNum - 1)
		{ 

			if(DataLen > 0)
			{
				MessageBox("�����ѵ���ͷ��"," ",MB_OK|MB_ICONWARNING);
			}
			else
			{
			//	Beep(300,400);
			}

			break;
		}    
	
		//��ʾֵ
		for(int  i = 0; i < PointsNum; i ++)
		{
		
			iWaveAll[j*PointsNum+i] = DataBuf[(m_nStartPoint+j)*PointsNum + m_startpoint + i];
		
		}

	}
	
	//���в�����
	if(m_AllAdd)
	{
		//��1�Ĳ�������һ��,��0�Ĳ�������һ��
		AllWaveAdd();
	}

	m_wndAnalyzeWin.NewDataIn(iWaveAll,CycleNum*PointsNum);
	m_wndWaveWin.NewDataInAnalyze(iWaveAll,CycleNum*PointsNum);

}

void CTTTView::OnButtonShiftleft() 
{		
	UpdateData(TRUE);
	m_nStartPoint ++;

	PointsNum   = m_wavepoints;                         //ÿ�����ɵĵ���
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //�ɵ������
	
	if(m_nStartPoint + CycleNum > MaxCycleNum - 1)
	{
		m_nStartPoint = MaxCycleNum - CycleNum;
		Beep(300,400);
		//MessageBox("�����ѵ���ͷ��"," ",MB_OK|MB_ICONWARNING);
	}
	
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
	}

	UpdateData(FALSE);
	
	//�������ݱ�
	OnButtonUpdate();
}

void CTTTView::OnButtonAshiftleft() 
{	
	UpdateData(TRUE);
	
	m_nStartPoint += CycleNum;
	PointsNum      = m_wavepoints;                         //ÿ�����ɵĵ���
	MaxCycleNum    = (DataLen-m_startpoint)/PointsNum;     //�ɵ������

	//�����ͷ��
	if(m_nStartPoint + CycleNum > MaxCycleNum - 1)
	{

		m_nStartPoint = MaxCycleNum - CycleNum;
	
		//add
		if(m_nStartPoint%4 != 0)
		{
			m_nStartPoint = m_nStartPoint - m_nStartPoint%4;
		}
		
		if(m_nStartPoint < 0)
		{
			m_nStartPoint = 0;
		}

        Beep(300,400);
	
	}

	UpdateData(FALSE);
	
	//�������ݱ�
	OnButtonUpdate();
}

void CTTTView::OnButtonShiftright() 
{
	UpdateData(TRUE);
	m_nStartPoint--;

	PointsNum   = m_wavepoints;                         //ÿ�����ɵĵ���
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //�ɵ������
	
	//�����ǰ����
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
		Beep(300,400);
	}
	
	UpdateData(FALSE);
	
	//�������ݱ�
	OnButtonUpdate();
}


void CTTTView::OnButtonAshiftright() 
{	
	UpdateData(TRUE);

	m_nStartPoint -= CycleNum;

	PointsNum   = m_wavepoints;                         //ÿ�����ɵĵ���
	MaxCycleNum = (DataLen-m_startpoint)/PointsNum;     //�ɵ������
	
	//�����ǰ����
	if(m_nStartPoint < 0)
	{
		m_nStartPoint = 0;
		Beep(300,400);
	  //MessageBox("�����ѵ���ǰͷ��"," ",MB_OK|MB_ICONWARNING);
	}

	UpdateData(FALSE);
    
	//�������ݱ�
	OnButtonUpdate();
}


void CTTTView::OnSelchangeComboChselect() 
{
	UpdateData(TRUE);
	BYTE   ORDER[15];
	//��ORDER[0]��ORDER[4]��Ƭ����
	//������
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x5B; //��������
	ORDER[3]  = (m_generatrix - 1) * 64 + (m_iChSelect + 1) * 4 + 01;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	
	ORDER[4]  =  3;// ��ʱ��0����   
	
	//����ģ����
	ORDER[5]  = 0xf2; //�����֣�Ҫʲô����
	ORDER[6]  = 0;    //ģ��ߵ�ַ
	ORDER[7]  = 0;    //ģ���е�ַ
	ORDER[8]  = 0;//AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4��Ϊפ��ʱ��,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
	ORDER[9]  = 0;//StatusL;//פ��ʱ��
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��
	
	//��ʱ����
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//��Ƭ��������
	PcSendToSCM(ORDER);
}


void CTTTView::OnButtonLoad() 
{
	//���ļ��Ի���
	char szFilter[]="�ı��ļ�(*.TXT)|*.TXT||";
	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{

		CString            str;
		char            buf[8];
		short    length    =   0;
		long     m_sums    =   0;
		int        kkkk    =   0;
		int   m_postion    =   0;
		int   abstempvalue =   100;
	        
		//�õ����������ļ��ĵ������ݳ���
	    length = GetFileEveryDataLength(dlg.GetPathName());
	
		if(!file.Open(dlg.GetPathName( ),CFile::modeRead))
		{
			MessageBox("�ļ��򿪴���!","ȷ��",MB_OK); 
			return;
		}

		CWnd* ptt = GetDlgItem(IDC_STATICFILE);
		ptt->SetWindowText("�����ļ���" + dlg.GetPathName());
	
		if(length != 4 && length != 5 && length != 6)
		{
			file.Close();
			MessageBox("�������ļ�����TTT���������ļ���","ȷ��",MB_OK|MB_ICONWARNING);
			return;
		}
	    
		MaxPointsNum = (file.GetLength())/(length + 2);	//12λ�ɼ������ݳ���Ϊ6��16λ�ɼ������ݳ���Ϊ8
		DataLen      = MaxPointsNum;

		file.Seek(0,CFile::begin);

		for(UINT j = 0; j < MaxPointsNum; j++)
		{	
			file.Read(buf,length + 2);
			str   =  buf;
			str= str.Left(6);
			str.TrimLeft();
			str.TrimRight();
			
			DataBuf[j] = atoi(str);
			file.Seek(0,CFile::current);

		}
		file.Close();
        
    	UpdateData(TRUE);

		m_iCycleNum   =          2;
		m_bDiffI      =       TRUE;
		m_nStartPoint =          0;
		UpdateData(FALSE);
    	
		//��ʾ����
		OnButtonUpdate();
		
		OnSelchangeComboCyclenum();
	
     }

}

//��ѹ��
void CTTTView::OnCheckDiff() 
{
	UpdateData();
}

//ǰ��
void CTTTView::OnCheckAver4() 
{
	UpdateData();
	OnButtonUpdate();
}

//��ͨ
void CTTTView::OnCheckBandPass() 
{
	UpdateData();
	OnButtonUpdate();
}

//΢��
void CTTTView::OnCheckDvdt() 
{
	UpdateData();
}

//����
void CTTTView::OnCheckDiffi() 
{
	UpdateData();
	OnButtonUpdate();
}


void CTTTView::OnChangeEditAngle() 
{
	UpdateData();
}

void CTTTView::OnChangeEditBandpassangle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData();
}




void CTTTView::OnChangeEditThreshold() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}

void CTTTView::Delay()
{
	for(int i=0; i< 2000; i++);
	
}

void CTTTView::OnChangeEditSendcode() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
}


//˫��ͨѶ
BOOL CTTTView::PcSendToSCM(BYTE ORDER[])
{

	SendMessage(WM_EVENT,1,0);

	CString        str;	
	CString       str1;
	U32      output[5];
	BYTE    Receive[5];
	ORDER[14]     =  0;

	if(ORDER[2] == 0x53)
	{
		//add
		//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
		ORDER[2] = m_protocol/10*16 + m_protocol%10;
		
		if(m_protocol == 22)
		{
			//22Э�鵱71Э����
			ORDER[2] = 0x71;
		}
		else if(m_protocol == 31)
		{
			ORDER[2] = 0x53;
		}
	
		//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
		if(m_protocol >= 71 && m_protocol <= 73)
		{
			//�����ֽ�,BCHУ��
			BYTE            g[64];
			BYTE         data[45];
			//CString   str,strtemp;
			//g[63] =             0;
			BYTE         TempVale;
			
			for(int i = 5; i < 10; i ++)
			{
				
				//	str.Format("ORDER[%d]=0x%0x",i,ORDER[i]);
				//	WriteToLog(str);
				TempVale = ORDER[i];
		//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

				
				for(int j = 1; j <= 8; j ++)
				{
					//ssgg 7-5
					//	strtemp.Format("%d",TempVale%2);
					//data[6 + (i-5)*8+j-1] = TempVale%2;//add 2004.12.28
					//TempVale              = TempVale/2;
					data[6 + (i - 5) * 8 + j - 1] = (TempVale & 0x80) == 0 ? 0 : 1;//add 2004.12.28
					TempVale                      = TempVale << 1;
					//end ssgg 7-5
				}
				
			}
			
			//  40-45��Ϊ0
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;
			
//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<46; i++) {
				CString mystr;
				if(data[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
//end ssgg debug

			//ת��BCH��
			Encode_Bch_63_45_3(g,data);
			
			//�����ָ���
			for( i = 5; i < 13; i ++)
			{
				
				ORDER[i] = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					//ssgg 7-5
					//ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,j));
					ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow(2,j*(-1) + 7));
					//end ssgg 7-5
				}

		//ssgg debug
		ORDER[12] = 0x67;
		//		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug
				
			}

			ORDER[13] = 0;

		}
		else if(m_protocol == 22)
		{
			//22Э��,�����ֽ�,BCHУ��
			BYTE             g[31];
			BYTE            gg[62];
			BYTE          data[21];
			//	CString    str,strtemp;
			//��21λ����ȡ��
			long         TempVale = (ORDER[5]<<13) + (ORDER[6]<<5) + (ORDER[7]>>3);
			
			//21����
			for(int j = 0; j < 21; j ++)
			{
				//21λ����
				data[20-j]   = TempVale%2;
				TempVale     = TempVale/2;     
			}
			
			//ת��BCH��
			Encode_Bch_31_21_2(g,data);
			
			//22��˫��Э��,1��10,0����01
			for(int i = 0; i < 31; i ++)
			{
				
				//�����1��0,��0��1
				if(g[i] == 1)
				{
					gg[2*i  ] = 1;
					gg[2*i+1] = 0;
				}
				else
				{
					gg[2*i  ] = 0;
					gg[2*i+1] = 1;
				}
				
			}
			
			WriteToLog("\r\n");
			
			//�����ָ��� 5-----13
			for( i = 5; i < 13; i ++)
			{
				ORDER[i]  = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if((i-5)*8+j < 62)
					{
						ORDER[i] = ORDER[i] + BYTE(gg[(i-5)*8+j]<<(7-j));
						str.Format("gg[%d]=%d",(i-5)*8+j,gg[(i-5)*8+j]);
					}
					else
					{	
						if((i-5)*8+j == 62)
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
							str.Format("gg[%d]=%d",(i-5)*8+j,0);
						}
						else
						{
							ORDER[i] = ORDER[i] + BYTE(1<<(7-j));
							str.Format("gg[%d]=%d",(i-5)*8+j,1);
						}
						
					}
					
					WriteToLog(str);
					
				}
				
				//22Э�鹲��62λ�����һ��ֻ�в�2λ������2λ
				str.Format("ORDER[%d]=%0x\r\n",i,ORDER[i]);
				WriteToLog(str);
			}
			
			ORDER[13] = 0;
			
		}
		else if(m_protocol == 61 || m_protocol == 62)
		{

			//61,62,Э��,�����ֽ�,BCHУ�� 45_27_3
			BYTE             g[45];
			BYTE          data[27];

			//��21λ����ȡ��
			long         TempVale = (ORDER[5]<<19) + (ORDER[6]<<11) + (ORDER[7]<<3) +  (ORDER[8]>>5);
			
			//21λ����
			for(int j = 0; j < 27; j ++)
			{
				data[26-j]  = TempVale%2;
				TempVale    = TempVale/2;     
			}

			//ת��BCH��45_27_3
			Encode_Bch_45_27_3(g,data);

			//�����ָ���
			for(int i = 5; i < 13; i ++)
			{
				
				ORDER[i]     =   0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if(((i-5)*8 + j ) > 44)
					{
						ORDER[i] = ORDER[i] + 0;
					}
					else
					{
						ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,7-j));
					}
					
				}	
				
				//22Э�鹲��62λ�����һ��ֻ�в�2λ������2λ
				str.Format("ORDER[%d]=%0x\r\n",i,ORDER[i]);
				WriteToLog(str);
				
			}

			ORDER[13] = 0;
			
		}
		
		//������ǽǱ�
		if(m_xinjiaobian)
		{
			ORDER[13]  = 0x06;
		}

	}


    str= "";

	//��ǰ14λ
	for(int j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//�����
			ORDER[14] = ORDER[14] + ORDER[j];
			
		}
		
		if(ORDER[j] > 15)
		{
		  //str1.Format(" 0x%0x \r\n",ORDER[j]);
            str1.Format(" 0x%0x  ",ORDER[j]);
		}
		else
		{
          //str1.Format(" 0x0%0x \r\n",ORDER[j]);
			str1.Format(" 0x0%0x  ",ORDER[j]);
		}

        str = str + str1;
		
	}
	
	
	str1.Format(" 0x%0x ",ORDER[14]);
	str = str + str1;
    
	m_SendOrder = str;

	SendMessage(WM_EVENT,2,0);
	//ORDER[14] = ORDER[14]%256;
	
	//���ͼ����
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//��һ����
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//�߷�����
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//ʱ��
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//ʱ��
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		//	MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
		}


		Receive[j] = BYTE(output[j] & 0xff);

		Sleep(1);
		
		
	}
	
	/**/
	str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//���λ��λȥ��
	//AfxMessageBox(str1);
    
	CTime time = CTime::GetCurrentTime();
	CString s;
	s.Format("%4d-%2d-%2d %2d:%2d:%2d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //ת��ʱ���ʽ
	//WriteToLog("˫��ͨѶ���\r\n" + str + "\r\n" + str1 + s);
	
	
	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		WriteToLog("˫��ͨѶʱ����Ͳ���!\r\n" + str + "\r\n" + str1);
		Beep(300,400);
		return FALSE;
	}

    switch(ORDER[2])
	{
	case 0x53://pc������
		{
			//Receive[1]������ĸ��  Receive[2]������ ��· Receive[3]������ ���
			if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
			{
				WriteToLog("˫��ͨѶʱ��������� 0x53!\r\n" + str + "\r\n" + str1);
				Beep(300,400); 
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5c://����A�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5C!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5d://����B�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5d!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5e://����C�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5e!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x58://��ȡA�ഥ���Ƕ�
		{
			if(Receive[0] != 0x68)
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x58!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0x59://��ȡB�ഥ���Ƕ�
		{
			if(Receive[0] != 0x69)
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x59!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0x5a://��ȡC�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6a)
			{
				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5a!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0x9c://��ȡֱ�ߺ�
		{
			if(Receive[0] != 0xac)
			{
				WriteToLog("˫��ͨѶʱ��ȡֱ�߱�Ų��� 0x5a!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0xC0://����A���ӳٽǶ�
		{
			if(Receive[0] != 0xD0)
			{
				WriteToLog("˫��ͨѶʱ����A���ӳٽǶȲ��� 0xD0!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC1://����B���ӳٽǶ�
		{
			if(Receive[0] != 0xD1)
			{
				WriteToLog("˫��ͨѶʱ����B���ӳٽǶȲ��� 0xD1!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC2://����C���ӳٽǶ�
		{
			if(Receive[0] != 0xD2)
			{
				WriteToLog("˫��ͨѶʱ����C���ӳٽǶȲ��� 0xD2!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC3://��ȡA���ӳٽǶ�
		{
			if(Receive[0] != 0xD3)
			{
				WriteToLog("˫��ͨѶʱ��ȡA���ӳٽǶȲ��� 0xD3!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}
			break;
		}
	case 0xC4://��ȡB���ӳٽǶ�
		{
			if(Receive[0] != 0xD4)
			{
				WriteToLog("˫��ͨѶʱ��ȡB���ӳٽǶȲ��� 0xD4!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xC5://��ȡC���ӳٽǶ�
		{
			if(Receive[0] != 0xD5)
			{
				WriteToLog("˫��ͨѶʱ��ȡC���ӳٽǶȲ��� 0xD5!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xC6://������ģ���A�������ѹ
		{
			if(Receive[0] != 0xD6)
			{
			//	WriteToLog("˫��ͨѶʱ������ģ���A�������ѹ���� 0xD6!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			break;
		}
	case 0xC7://������ģ���B�������ѹ
		{
			if(Receive[0] != 0xD7)
			{
			//	WriteToLog("˫��ͨѶʱ������ģ���B�������ѹ���� 0xD7!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}

			break;
		}
	case 0xC8://������ģ���C�������ѹ
		{
			if(Receive[0] != 0xD8)
			{
			//	WriteToLog("˫��ͨѶʱ������ģ���C�������ѹ���� 0xD7!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
			}
			
			break;
		}

    /*
	case 0xC6://����A�෢�����
		{
			if(Receive[0] != 0xD6)
			{
				WriteToLog("˫��ͨѶʱ���÷���������� 0xD6!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC7://����B�෢�����
		{
			if(Receive[0] != 0xD7)
			{
				WriteToLog("˫��ͨѶʱ���÷���������� 0xD7!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC8://����C�෢�����
		{
			if(Receive[0] != 0xD8)
			{
				WriteToLog("˫��ͨѶʱ���÷���������� 0xD8!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	*/

	case 0xC9://��ȡA�෢�����
		{
			if(Receive[0] != 0xD9)
			{
				WriteToLog("˫��ͨѶʱ��ȡA�෢��������� 0xD9!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}

	case 0xCA://��ȡB�෢�����
		{
			if(Receive[0] != 0xDA)
			{
				WriteToLog("˫��ͨѶʱ��ȡB�෢��������� 0xDA!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}
	case 0xCB://��ȡC�෢�����
		{
			if(Receive[0] != 0xDB)
			{
				WriteToLog("˫��ͨѶʱ��ȡC�෢��������� 0xDB!\r\n" + str + "\r\n" + str1);
				Beep(300,400);
				WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];//Receive[1];
			}

			break;
		}


	}
	return TRUE;
}

void CTTTView::WriteP9111_CHANNEL_DOPort(int value)
{
	I16     err;
	err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100 + value);//ʱ��
	if(err != 0)
	{
		//Beep(300,400);
		//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
		//return;
	}

	Sleep(1);

	err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000 + value);
	if(err != 0)
	{
		//Beep(300,400);
		//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
	}

	Sleep(1);
}


void CTTTView::WriteToTxtFile(CString FileName,unsigned short DataBuf[],int length)
{
	//д���ı��ļ�
	FILE  *text;
	CString Str;
	if((text = fopen(FileName,"a")) != NULL)
	{
		for(int i = 0; i < length; i++)
		{
			Str.Format("%5d",DataBuf[i]);
			//Str.Format("%4d",DataBuf[i]);
			fputs(Str + "\r\n",text);
		}
		fclose(text);
	}
}



UINT  ReadChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	
	if(!pview->m_xinjiaobian)
	{
		//����
		pview->ReadMeter();
	}
	else
	{
		//ͬ��ɼ�ͬ����
		if(pview->m_equal)
		{
			pview->ReadMeter();
		}
		else
		{
			//�ǽ�
			pview->ReadSixChannelMeter();
		}
	}

	return 0;
}

void CTTTView::OnRealStart() 
{

	UpdateData(TRUE);

//	m_nStartPoint = 0;
//  UpdateData(FALSE);

    if(m_derrors > 31 )
	{
        MessageBox("��λ����ӦС��31��","����",MB_OK|MB_ICONWARNING);
		return;
	}


	//��ɼ�������
	if(m_iModeSel == 1)
	{
		CWnd* pt  = GetDlgItem(IDC_RECEIVE);
		pt->SetWindowText(" ");
		pt  = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText(" ");	
		pt  = GetDlgItem(IDC_STATICFILE);
		pt->SetWindowText(" ");
		m_ReceiveStr     =  "";
		
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_BUTTON_ANGLE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);

		for(int i = 0; i < 270000; i++)//135000*2 131584
		{
			DataBuf[i] = 0;
		}
		
		AfxBeginThread(ReadChannel,this); 
	//	eventWriteD.ResetEvent(); 
	//	AfxBeginThread(WriteD,this);
		m_ShowWave  = TRUE;	
	}
	else
	{	
		//�򴮿ڷ�������
		int         m_order    = 0;
		CString                str;
		UpdateData(TRUE);
		
		if(m_angle  < 5 || m_angle  > 50)
		{
			MessageBox("�Ƕȳ���[5,50]��","����",MB_OK|MB_ICONWARNING);
			return;
		}
		
		GetDlgItem(IDC_RECEIVE)->SetWindowText("");
		GetDlgItem(IDC_SENDORDER)->SetWindowText("");
		
		CWnd* pt    =    GetDlgItem(IDC_ORDER);
		pt->GetWindowText(str);	
	
		str.TrimLeft();
		str.TrimRight();
		
		if(str.IsEmpty())
		{
			pt    =    GetDlgItem(IDC_REAL_START);
			pt->EnableWindow(TRUE);
			MessageBox("�����ֲ���Ϊ�գ�","",MB_OK|MB_ICONWARNING);
			return;
		}
		
		if(str.GetLength() > 1)
		{
			m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
		}
		else
		{
			m_order = GetHexValue(str.GetAt(0));
		}
		
		SendByteArray.RemoveAll();
		BYTE             TempByte;

        //��ʼ�ֽ�
        SendByteArray.Add(0x68);    
		//�㲥
        SendByteArray.Add(0xff);            
        
		//�ϳ��ֽ�,������(2)+��λ(2)+����Э��(4)     
		switch(m_protocol)
		{
		case 61:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 5;
				break;
			}
		case 62:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 6;
				break;
			}
	 	case 71:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 1;
				break;
			}
		case 72:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 2;
				break;
			}
		case 73:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 3;
				break;
			}
		case 74:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 4;
				break;
			}
		case 21:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 9;
				break;
			}
		case 22:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 10;
				break;
			}
		case 23:
			{
                TempByte = 2*64 + (m_phase + 1)*16 + 11;
				break;
			}
		case 24:
			{
				TempByte = 2*64 + (m_phase + 1)*16 + 12;
				break;
			}
	
		}
        SendByteArray.Add(TempByte);            
		
		//����Э��,��ʱû����
		switch(m_protocol)
		{
		case 61:
			{
				TempByte =  5;
				break;
			}
		case 62:
			{
				TempByte =  6;
				break;
			}
	 	case 71:
			{
				TempByte =  1;
				break;
			}
		case 72:
			{
				TempByte =  2;
				break;
			}
		case 73:
			{
				TempByte =  3;
				break;
			}
		case 74:
			{
				TempByte =  4;
				break;
			}
		case 21:
			{
				TempByte =  9;
				break;
			}
		case 22:
			{
				TempByte = 10;
				break;
			}
		case 23:
			{
                TempByte =  11;
				break;
			}
		case 24:
			{
				TempByte = 12;
				break;
			}
	
		}

        SendByteArray.Add(TempByte);
		//���ͽǶ�
		SendByteArray.Add(m_angle);

		//����5-13
		if(m_protocol == 61 || m_protocol== 62)
		{
			ComeIntoBch60(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/,m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);
		}
		else if(m_protocol > 70)
		{
			ComeIntoBch70(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/,m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);
		}
		else
		{
			ComeIntoBch20(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/,m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);
		}
    
		TempByte = 0;
		
		//14 �����
		for(int i = 0; i < 14; i ++)
		{
			TempByte = TempByte + SendByteArray[i];
		}

		SendByteArray.Add(TempByte);      

		//15������
        SendByteArray.Add(0x16);

		//�򴮿ڷ���
		SendByteArrayToCom();
	
	}
	
}

void CTTTView::OnRealstop() 
{

	bClearOp    = TRUE;//���߳��˳�
	m_Stopping  = TRUE;
	Sleep(200);
	CWnd* pts   = GetDlgItem(IDC_REAL_START);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SEND);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SETTIMER);
	pts->EnableWindow(TRUE);
    pts = GetDlgItem(IDC_DECODE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_RADIO_REALTIME);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_COMSET);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SENDALLONE);
	pts->EnableWindow(TRUE);	
	pts = GetDlgItem(IDC_BUTTON_ANGLE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_REALSTOP);
	pts->EnableWindow(FALSE);
	KillTimer(1);
	KillTimer(2);
}

BOOL CTTTView::SendOrderToSCM(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/, BYTE ZeroDots/* ��ʱ��0����*/,BYTE Item/* Ҫʲô����,������*/,int status/*�ɷ�ʱ�����������*/)
{
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 ����Ϊģ���Ϊ16���Ϊ01
	AddrH = int((int(ModuleNum/100)%65536)/256);//��λ    ��Ӧ��Ϊ����1
    AddrM = (int(ModuleNum/100)%65536)%256;     //�м�λ  ��Ӧ��Ϊ����2
	AddrL = ModuleNum%100 - 1;                  //��4λ   �ָ����
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}
    
	
	StatusH = status/256;        //��λ    ��Ӧ��Ϊ����3�ĺ�2λ
	StatusL = status%256;        //��λ    ����4
	
	switch(Phase)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
            
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
		    
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// ��ʱ��0�����       
	//��� 
	
	//ORDER[5]��ORDER[10]�ɵ�Ƭ����Ƭ������ģ����

	if(m_protocol == 22)
	{
		
		//���Э��Ϊ22	
		if(!m_check4bit)
		{
			
			//����� 485��: 10(�ලλ) + 14(��ַ)+ 7(����)
			//����������: 10(�ලλ) + 14(��ַ)+ 4(�ֵ�ַ) + 3(����)
			
			//��ַǰ8λ
			ORDER[5]  = (ModuleNum/100)>>6; //��ַ��λ
			
			if(ModuleNum%100 == 15)
			{
				//485��  6λ��ַ + 2λ�����ֵĸ�λ(��7λ������)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + (Item>>5);
				//5λ������ + 3��0
				ORDER[7]  = (Item%32)*8;
			}
			else
			{
				//����� 6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
				//�ӱ��ַ2λ��λ(��4λ�ӱ��ַ) + 3λ������  + 3��0
				ORDER[7]  = ((ModuleNum%100-1)%4)*64  + ((Item%8)*8);
			}
			
		}
		else
		{
			//�����3λ�����
			//����� 485��: 10(�ලλ) + 3(�����) + 11(��ַ)  +  7(����)   
			//����������: 10(�ලλ) + 3(�����) + 11(��ַ)  +  4(�ӵ�ַ) + 3(����) 
			
			
			long      m_Modules       =      0;
			BYTE       m_data[18],m_checkvalue;	
			
			
			if(ModuleNum%100 >= 12)
			{
				//485  11(��ַ)  +  7(����)
				m_Modules = ((ModuleNum/100)<<7) + Item;
			}
			else
			{
				//     11(��ַ)  +  4(�ӵ�ַ) + 3(����)
				m_Modules = ((ModuleNum/100)<<7) + ((ModuleNum%100-1)>>3) + Item;
			}
			
			//3λУ���
			m_checkvalue              =     0 ;
			
			//18λ����
			for(int j = 0; j < 18; j ++)
			{
				m_data[17-j]       =       m_Modules%2;
				m_Modules          =       m_Modules/2;     
			}
			
			for( j = 0; j < 6; j ++)
			{
				m_checkvalue = m_checkvalue  + (m_data[3*j]*4+m_data[3*j+1]*2+m_data[3*j+2]*1);
			}
			
			m_checkvalue     = m_checkvalue%8;
			
			
			//3(�����) + ��ַǰ5λ
			ORDER[5]  =  (m_checkvalue<<5) +  ((ModuleNum/100)>>6);
			
			if(ModuleNum%100 >= 12)
			{
				//485��         6λ��ַ + 2λ�����ֵĸ�λ(��7λ������) 
				ORDER[6]        = (((ModuleNum/100)%64)<<2) + (Item>>5);
				//5λ������(��7λ������)  + 3��0
				ORDER[7]        = ((Item%32)<<3) + 0;
			}
			else
			{
				//�����        6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ) 
				ORDER[6]        = (((ModuleNum/100)%64)<<2) + ((ModuleNum%100-1)>>2);
				//              �ӱ��ַ��2λ(��4λ�ӱ��ַ) +  3λ������(��3λ������) + 3��0
				ORDER[7]        = (((ModuleNum%100-1)%4)<<6) + (Item<<3) + 0;
			}
			
			
		}
		
		ORDER[8]  =     0;
		ORDER[9]  =     0;

	}
	else if(m_protocol == 61 || m_protocol ==62)
	{

		//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������       + 6λ��־��
		//����� 485��: 18(�ලλ) + 14(��ַ) + "1"(485��־)           + 5(����) + 7λ������(0001000)
		//����������: 18(�ලλ) + 14(��ַ) + "0"(������ֵ�ַ)      + 2(����) + 7λ������(0001000)
			
		//��ַǰ8λ
		ORDER[5]  = (ModuleNum/100)>>6; //��ַ��λ
		
		if(ModuleNum%100 > 12)//>=
		{
			//485��  6λ��ַ  +  1λ(485��־) + 1λ������(��5λ������)
			ORDER[6]  = ((ModuleNum/100)%64)* 4 + 1*2 + (Item>>4);
			//4λ������(��5λ������) + 4λ������(0001)
			ORDER[7]  = (Item%16)*16 + 1;
			//3λ������(000) + 5��0
			ORDER[8]  =  0;
			
		}
		else
		{	
			
			//ͣ�͵�
			if(Item == 0x00 || Item==0x01)
			{
				//ʹ�ϵ�ͣ�粻���׳��֣�����7����ͣ�͵� 0111
				//����� 6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ)
				ORDER[6]  = ((ModuleNum/100)%64)* 4  +  1;
				//�ӱ��ַ2λ��λ(��4λ�ӱ��ַ)+2λ������+4λ������(0001)
				ORDER[7]  = 3*64+ (Item%4)*16        +  1;
				
			}
			else
			{
				//����� 6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ)
				ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
				//�ӱ��ַ2λ��λ(��4λ�ӱ��ַ)+2λ������+4λ������(0001)
				ORDER[7]  = ((ModuleNum%100-1)%4)*64+ (Item%4)*16     +    1;
				
			}
			
			//3λ������(000) + 5��0
			ORDER[8]  =   0;//00000000
		}	
		
		ORDER[9]  =     0;

		
	}
	else
	{
			
			//���Э��Ϊ31��32��71��72��
			ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //�����֣�Ҫʲô������ģ���ַ���λ
			ORDER[6]  = AddrH;//ģ��ߵ�ַ
			ORDER[7]  = AddrM;//ģ���е�ַ
			
			
			
			//��ʱ��
			/*	
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
			ORDER[9]  = StatusL;//פ��ʱ��
			if(status == 0)
			{
			ORDER[9] = 0x67;
			}
			*/
			
			//��ʱ��,�����ǹ㲥����
			if(Item == 0xF2)
			{
				ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
			}
			else
			{
				
				if(m_Is0Station)
				{
					//�����0վ
					ORDER[8]  = AddrL*16 + PhaseBit* 4 + 0;
				}
				else
				{
					//�����0վ
					ORDER[8]  = AddrL*16 + PhaseBit* 4 + 1;
				}
				
			}
			
			//�µ�ѡ��
			switch(Item)
			{
			case 0xF2://�����ǹ㲥����
				{
					ORDER[9]  = StatusL;//פ��ʱ��
					break;
				}
			case 0x02://���й����
				{	
					break;
				}
			case 0x3a://����ѹ
				{
					break;
				}
			case 0x3e://�����0
				{
					break;
				}
			case 0x40://����������0
				{
					break;
				}
			case 0xF7://�͵����
				{
					
					//�͵����  D3 = 0000****
					//	ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
					break;
					
				}
			case 0xf6://�ϵ����
				{	
					
					//�Ͽ�״̬ʱ D3 = 1111****
					//	ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
					break;
					
				}
			case 0x82://�������й����
				{
					
					//����Ϊ��������
					break;
					
				}
				
			default:
				{
					//����Ϊ��������
					ORDER[9]  =  0x67;                                 //���ֽں���λΪ��ʱ��0����
				}
				
			}
			
			
			
			//���������,��ORDER[9]��ֵ
			switch(ZeroDots)
			{
			case 3:
				{
					
					ORDER[9]  = 0x60 + 0x07;    //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 5:
				{
					
					ORDER[9]  = 0x60 + 0x07;    //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 20:
				{
					
					ORDER[9]  = 0x60 +  0x06;    //���ֽں���λΪ��ʱ��0����
					break;
					
				}	
			case 30:
				{
					
					ORDER[9]  = 0x60 +  0x05;     //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 60:
				{
					
					ORDER[9]  = 0x60 +  0x04;     //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 100:
				{
					
					ORDER[9]  = 0x60 +  0x03;      //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 160:
				{
					
					ORDER[9]  = 0x60 +  0x02;      //���ֽں���λΪ��ʱ��0����
					break;
					
				}	
			case 200:
				{
					
					ORDER[9]  = 0x60 +  0x01;      //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			case 240:
				{
					
					ORDER[9]  =  0x60 + 0x00;     //���ֽں���λΪ��ʱ��0����
					break;
					
				}
			}
			
	}

	
	//�����ֽ�
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��

	//status
	//��ʱ����
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//��Ƭ��������
	return PcSendToSCM(ORDER);
	Sleep(5);
}

BOOL CTTTView::DecodeBCH63394(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 6, n = 63 , length = 63, t = 4, k = 39, d = 9;
    int   alpha_to[64], index_of[64];
	CString str;
	    alpha_to[0]  = 1,index_of[0]   = -1,
		alpha_to[1]  = 2,index_of[1]   = 0,
		alpha_to[2]  = 4,index_of[2]   = 1,
		alpha_to[3]  = 8,index_of[3]   = 6,
		alpha_to[4]  = 16,index_of[4]  = 2,
		alpha_to[5]  = 32,index_of[5]  = 12,
		alpha_to[6]  = 3,index_of[6]   = 7,
		alpha_to[7]  = 6,index_of[7]   = 26,
		alpha_to[8]  = 12,index_of[8]  = 3,
		alpha_to[9]  = 24,index_of[9]  = 32,
		alpha_to[10] = 48,index_of[10] = 13,
		alpha_to[11] = 35,index_of[11] = 35,
		alpha_to[12] = 5,index_of[12]  = 8,
		alpha_to[13] = 10,index_of[13] = 48,
		alpha_to[14] = 20,index_of[14] = 27,
		alpha_to[15] = 40,index_of[15] = 18,
		alpha_to[16] = 19,index_of[16] = 4,
		alpha_to[17] = 38,index_of[17] = 24,
		alpha_to[18] = 15,index_of[18] = 33,
		alpha_to[19] = 30,index_of[19] = 16,
		alpha_to[20] = 60,index_of[20] = 14,
		alpha_to[21] = 59,index_of[21] = 52,
		alpha_to[22] = 53,index_of[22] = 36,
		alpha_to[23] = 41,index_of[23] = 54,
		alpha_to[24] = 17,index_of[24] = 9,
		alpha_to[25] = 34,index_of[25] = 45,
		alpha_to[26] = 7,index_of[26]  = 49,
		alpha_to[27] = 14,index_of[27] = 38,
		alpha_to[28] = 28,index_of[28] = 28,
		alpha_to[29] = 56,index_of[29] = 41,
		alpha_to[30] = 51,index_of[30] = 19,
		alpha_to[31] = 37,index_of[31] = 56,
		alpha_to[32] = 9,index_of[32]  = 5,
		alpha_to[33] = 18,index_of[33] = 62,
		alpha_to[34] = 36,index_of[34] = 25,
		alpha_to[35] = 11,index_of[35] = 11,
		alpha_to[36] = 22,index_of[36] = 34,
		alpha_to[37] = 44,index_of[37] = 31,
		alpha_to[38] = 27,index_of[38] = 17,
		alpha_to[39] = 54,index_of[39] = 47,
		alpha_to[40] = 47,index_of[40] = 15,
		alpha_to[41] = 29,index_of[41] = 23,
		alpha_to[42] = 58,index_of[42] = 53,
		alpha_to[43] = 55,index_of[43] = 51,
		alpha_to[44] = 45,index_of[44] = 37,
		alpha_to[45] = 25,index_of[45] = 44,
		alpha_to[46] = 50,index_of[46] = 55,
		alpha_to[47] = 39,index_of[47] = 40,
		alpha_to[48] = 13,index_of[48] = 10,
		alpha_to[49] = 26,index_of[49] = 61,
		alpha_to[50] = 52,index_of[50] = 46,
		alpha_to[51] = 43,index_of[51] = 30,
		alpha_to[52] = 21,index_of[52] = 50,
		alpha_to[53] = 42,index_of[53] = 22,
		alpha_to[54] = 23,index_of[54] = 39,
		alpha_to[55] = 46,index_of[55] = 43,
		alpha_to[56] = 31,index_of[56] = 29,
		alpha_to[57] = 62,index_of[57] = 60,
		alpha_to[58] = 63,index_of[58] = 42,
		alpha_to[59] = 61,index_of[59] = 21,
		alpha_to[60] = 57,index_of[60] = 20,
		alpha_to[61] = 49,index_of[61] = 59,
		alpha_to[62] = 33,index_of[62] = 57,
		alpha_to[63] = 0,index_of[63]  = 58;
	
	t2 = 2 * t;
	
	////�����ۺϲ�֢ 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//�޸� 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // ���ô����־
			// ת���ۺϲ�֢�Ӷ���ʽ��������ʽ
			s[i] = index_of[s[i]];
			
	}
	
	//�д���Ļ�
	if (syn_error) 
	{
		
		//��������λ�ö���ʽ��ŷ�������㷨��
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//����b(x)����ֵ
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// ��񻯴���λ�ö���ʽ
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// ��Chien search�ҵ������λ�� 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			}
			
			
			if (count == l[u])
			{
				//	// no. roots = degree of elp hence <= t errors 
				str.Format("������������� count = %d",count);
				WriteToLog(str);
				
				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					if( loc[i] < 24)
					{
						str.Format("��������λ�ã�%d",23 - loc[i]);
					}
					else
					{
						str.Format("��������λ�ã�%d",86 - loc[i]);
					}

				  //str.Format("��������λ�ã�%d",loc[i]);
					WriteToLog(str);

				}
				return TRUE;
				
			}
			else
			{
				//
				str.Format("�������Ϊ�� count = %d��l[%d] = %d",count,u,l[u]);
				WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> lengthΪ����ֵ 
		}
		else
		{
			//
			str.Format("�������Ϊ��%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//
		str = "t = 0,û�д���";
		WriteToLog(str);//
		return TRUE;
	}

}

void CTTTView::WriteToLog(CString Str)
{
	
	if(m_IfWriteToLog)
	{
		//д���ı��ļ�
		FILE *text;
		if((text = fopen("c:\\data.txt","a")) != NULL)
		{
			fputs(Str + "\r\n",text);
			fclose(text);
		}

	}
}

void CTTTView::ReadMeter()
{ 
	WriteToLog("[���Ƕ���]");

	//ѭ������   
	int     HalfCount  =     0;
	CString                str;
    BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
    U32                  count;
	DataLen            =     0; 
    memset(ReadBuff,0,1024);
	int         DataValues = 0;
	int         m_order    = 0;
	int i, j;
    CWnd* pt    =    GetDlgItem(IDC_ORDER);
    pt->GetWindowText(str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		pt    =    GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(TRUE);
		MessageBox("�����ֲ���Ϊ�գ�","",MB_OK|MB_ICONWARNING);
		return;
	}
    
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(FALSE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(FALSE);

	pt = GetDlgItem(IDC_REAL_START);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_DECODE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO_REALTIME);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_COMSET);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SENDALLONE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BUTTON_ANGLE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);

	//������
//	SendOrderToSCM(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/,m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);

		//��Ƭ����ָ��
	for(i=0; i<3; i++) {
		if(!SendOrderToSCM(1001+i*100/*ģ���*/,
							1/*�����ֵ�վ��*/,
							1/*ĸ��*/,
							1/*�ߺ�*/, 
							i/*��ѡ��0A 1B 2C*/,
							3, 
							0x02/* Ҫʲô����,������*/,
							0)) /*m_SendAngle*/
		{
			Beep(300,400);
			Beep(300,400);
		}
		Sleep(1000);
	}


	//������ͨ������,m_CollectChannels�ɼ�ͨ��
	//err = AI_ContReadChannel(card,m_CollectChannels, AD_B_10_V, ReadBuff, 1024, 
	//	(F64)100000, ASYNCH_OP);//1024
	//if (err!=0) 
	//{  
		//Beep(300,400); 
    //}    
	err = AI_ContScanChannels (card, 2, AD_B_10_V, ReadBuff,1024, CLKSRC_EXT_SampRate, ASYNCH_OP);
	if (err != 0) 
		return;

	//long m_rrr  = GetTickCount(); 

	int     m_Waves = 0;
	CString          ss;

    bClearOp        = FALSE;
	long begintimes = GetTickCount();
    BOOL     m_recording  = TRUE;

	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//���ʱ��Ƶ��
	dff = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);//��ó�ʼֵ
		
   	do
	{
	
	    long begintime1 = GetTickCount();
        qt1 = litmp.QuadPart;

		do
		{
			//����
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
		
			if(m_protocol == 22)
			{
				
				if(GetTickCount() - begintimes > 8000)
				{
				//	ss.Format("�ɼ�%d��,���ݳ���%d",(GetTickCount() - begintimes)/1000,DataLen);
				//	WriteToLog(ss);
					bClearOp = TRUE;
				}

			}
			else
			{
				
				if(GetTickCount() - begintimes > ((m_protocol%10)*12000))
				{
				//	ss.Format("�ɼ�%d��,���ݳ���%d",(GetTickCount() - begintimes)/1000,DataLen);
				//	WriteToLog(ss);
					bClearOp = TRUE;
				}

			}
				
		} while (!bHalfReady && !bClearOp);
		
		
		if (!bClearOp) 
		{
			
			//���Ͱ�������
			AI_AsyncDblBufferTransfer(card, ReadBuff);
			bHalfReady = FALSE;

			if(m_recording)
			{
				ss.Format("���굽��ʱ���:%d",GetTickCount()- begintimes);
				WriteToLog(ss);	
				
				m_recording = FALSE;
			}
			
			for(int i = 0; i < 512; i++)
			{	
				//���ֵ         m_maxDecimalVal      1��PCI-9111DR 4096     2��PCI-9111HR 65536 
		        //�ɵ���Ҫ����ֵ  m_DivideVal         1��PCI-9111DR   16     2��PCI-9111HR     1 
				DataValues = ReadBuff[i]/m_DivideVal;
				
				//��������,����m_maxDecimalVal/2Ϊ����
				if(DataValues > m_maxDecimalVal/2)
				{
					DataValues =  -(m_maxDecimalVal - DataValues);
				}
				
				TempDataBuf[DataLen++] = DataValues;
                

			//	U32 dig_inn;
			//	long m_time1 =  GetTickCount();
			//  DI_ReadPort(card, P9111_CHANNEL_EDI,&dig_inn); 
			//	long m_time2 =  GetTickCount();

			//	CString stddr;
			//	stddr.Format("ʱ�䳤�ȣ�%d,ֵ;%d",m_time2-m_time1,dig_inn);
	        //  WriteToLog(stddr);
			
			}

	//		eventWriteD.SetEvent();

			//m_Waves ++;
			m_Waves += 2;
			QueryPerformanceCounter(&litmp);//�����ֵֹ
			qt2 = litmp.QuadPart;
			dfm = (double)(qt2-qt1);
			dft = dfm/dff;//��ö�Ӧ��ʱ��ֵ

		    ss.Format("[��%3d������Ⱥ����%3d����ʱ����%.2f����]",m_Waves,m_Waves-1,dft*1000);
		    WriteToLog(ss);
			
		    long m_waittimes = 0;

			if(!m_quancai)
			{
			
				
				if(m_protocol == 22)
				{
					m_waittimes = 8000;
				}
				else
				{
					m_waittimes = m_protocol%10*12000;//8000
				}

				switch(m_protocol)
				{
				case 22:
					{
						
					}
				case 31:
					{
						
					}
				case 32:
					{
						
					}
				case 71:
					{
						
					}
				case 72:
					{
						
						
					}
				case 73:
					{
						//64*4
						if(DataLen >= 196608 /*131584*/)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 61:
					{
						// 1024 + 45*4*512  = 93184
						if(DataLen >= 93184)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 62:
					{
						//1024 + 4*45*2*512 = 185344
						if(DataLen >= 185344)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				}

				//��������
				if((GetTickCount() - begintimes > m_waittimes))// 115200���2004����  229
				{  
					bClearOp = TRUE;
					break;
				}
				
			}
			else
			{	
				if(m_protocol == 22)
				{
					m_waittimes = 8000;
				}
				else
				{
					m_waittimes = m_protocol%10*8000;
				}
                
				//ȫ����
				if(DataLen >= 263168 || (GetTickCount() - begintimes > m_waittimes))// 115200���2004����  229
				{  
					bClearOp = TRUE;
					break;
				}
				
			}
			
		}
		
	}while (!bClearOp && !bStopped);
	
    AI_AsyncClear(card, &count);
	
	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(TRUE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(TRUE);
	
	//ss.Format("\r\n\r\n===============ʱ���Ϊ��%d===============",m_times2 - m_times1);
	//WriteToLog(ss);
	long m_checklengths = 0;

	switch(m_protocol)
	{
	case 22:
		{
			
		}
	case 31:
		{
			
		}
	case 32:
		{
			
		}
	case 71:
		{
			
		}
	case 72:
		{
			
			
		}
	case 73:
		{
			//64*4
			m_checklengths = 131584;
			break;
		}
	case 61:
		{
			// 1024 + 45*4*512  = 93184
			m_checklengths = 93184;
			break;
		}
	case 62:
		{
			//1024 + 4*45*2*512 = 185344
			m_checklengths = 185344;
			break;
		}
	}

    ss.Format("���㣺%d",DataLen);
	WriteToLog(ss);
	DataLen = 131584;

	for(j=0; j<256*64*4; j++) {
		if(TempDataBuf[j] >= 2048)
			TempDataBuf[j] = TempDataBuf[j] - 4096;

		DataBuf[j*2] = TempDataBuf[j*3 + i + 207];
		DataBuf[j*2 + 1] = TempDataBuf[j*3 + i + 207];
	}


	if(DataLen >= m_checklengths)
	{
		double GetValue = Decode();

		if(GetValue >= 0)//����
		{
			m_SuccessTimes  = m_SuccessTimes + 1;
			m_data.Format("%f",GetValue);//.2
		}
		else
		{
			m_data = "NULL";
		}

	//	OnButtonUpdate();

	}
	else
	{
		Beep(300,400);
		m_ReceiveStr = "<<�ɼ����ݴ���>>";
		m_data       = "NULL";
		m_CollectErrors    ++;
	}
	
	m_TotalTimes  = m_TotalTimes  + 1;
	

	CEdit * ptt = (CEdit *)GetDlgItem(IDC_DATAVALUE);
	ptt->SetWindowText(m_data);
	ptt        =  (CEdit *)GetDlgItem(IDC_RECEIVE);
	ptt->SetWindowText(m_ReceiveStr);
	

	CWnd* pts   = GetDlgItem(IDC_REAL_START);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SEND);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SETTIMER);
	pts->EnableWindow(TRUE);
    pts = GetDlgItem(IDC_DECODE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_RADIO_REALTIME);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_COMSET);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_SENDALLONE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_BUTTON_ANGLE);
	pts->EnableWindow(TRUE);
	pts = GetDlgItem(IDC_REALSTOP);
	pts->EnableWindow(FALSE);
}

void CTTTView::OnButtonSave() 
{

    //�����ļ��Ի���
	char szFilter[]="�ı��ļ�(*.TXT)|*.TXT||";

   	CFileDialog dlg(FALSE,"TXT","*.TXT",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{
		
		CString  str;

		if(!file.Open(dlg.GetFileName(),CFile::modeWrite | CFile::modeCreate))
		{	
			MessageBox("д�ļ�����!","ȷ��",MB_OK);
			return;
		}
		
		file.Seek(0,CFile::begin);

		str.Format("%6d",DataBuf[0]);
		str = str + "\r\n";
		file.Write(str,8);
			
		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
	      
			//16λ�ɼ���
			str.Format("%6d",DataBuf[i]);

			str = str + "\r\n";
			file.Write(str,8);
		}

		file.Close();

		MessageBox("�����ļ��ѳɹ�����!","ȷ��",MB_OK);
	}

}


//long ModuleNo   ģ���
//int  times      �������
//int  mode       д��ģʽ //0 error,1 right
void CTTTView::WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode)
{
	
	CFile       file;
	CString filename;
	CString      str;

	filename.Format("%d%d",ModuleNo,times);
	
	if(mode == 0)
	{
		filename = filename + "ERROR.TXT";
	}
	else
	{
        filename = filename + "RIGHT.TXT";
	}
	
	if(file.Open(filename,CFile::modeWrite|CFile::modeCreate))
	{	
		
		file.Seek(0,CFile::begin);
		//str.Format("%4d",DataBuf[0]);
		str.Format("%5d",DataBuf[0]);
		str = str + "\r\n";
		//file.Write(str,6);
		file.Write(str,7);

		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
			//str.Format("%4d",DataBuf[i]);
			str.Format("%5d",DataBuf[i]);
			str = str + "\r\n";
		  //file.Write(str,6);
			file.Write(str,7);
		}
		file.Close();
	}
	
}


//���ýǶ�
//short generatrixno ĸ�߱��
//short phase        ��� 0 A�� 1 B�� 2 C��
//int   angles       �Ƕ�
//BYTE  kinds  ���� 0--�ź�ǿ�� 1���ӳٽǶ�
void CTTTView::SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds)
{
	
    	CString    str;
		
		BYTE ORDER[15];
		
		//�Ƕ����� 
		ORDER[0]  = 0x51;
		ORDER[1]  = 0x52;//ǰ����
		
	
		switch(kinds)
		{
		case 0:
			{
				ORDER[2]  = 0x5c + phase;//�Ƕ�����
				break;
			}
		case 1:
			{		
				ORDER[2]  = 0xC0 + phase;//�ӳٽǶ�
				break;
			}
		case 2:
			{
				ORDER[2]  = 0XC6 + phase;//�������
				break;
			}
		}

		ORDER[3]  = generatrixno-1;
		ORDER[4]  = (BYTE)angles;
		ORDER[5]  = 0;
		ORDER[6]  = 0;
		ORDER[7]  = 0;
		ORDER[8]  = 0;
		ORDER[9]  = 0;
		ORDER[10] = 0;
		ORDER[11] = 0;
		ORDER[12] = 0;
		ORDER[13] = 0;
		
		//��Ƭ��������
		if(PcSendToSCM(ORDER))
		{
			
			switch(phase)
			{
			case 0:
				{  
					switch(kinds)
					{
					case 0:
						{
							str = "A���ź�ǿ���������!";
							break;
						}
					case 1:
						{
							str = "A���ӳٽǶ��������!";
							break;
						}
					case 2:
						{
							str = "A�෢������������!";
							break;
						}
					}

					break;
					
				}
			case 1:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "B���ź�ǿ���������!";
							break;
						}
					case 1:
						{
							str = "B���ӳٽǶ��������!";
							break;
						}
					case 2:
						{
							str = "B�෢������������!";
							break;
						}
					}

					break;
					
				}
			case 2:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "C���ź�ǿ���������!";
							break;
						}
					case 1:
						{
							str = "C���ӳٽǶ��������!";
							break;
						}
					case 2:
						{
							str = "C�෢������������!";
							break;
						}
					}

					break;
					
				}
			
			}
		
		}
		else
		{	
			
			switch(phase)
			{
			case 0:
				{  
					
					switch(kinds)
					{
					case 0:
						{
							str = "A���ź�ǿ�����ô���!";
							break;
						}
					case 1:
						{
							str = "A���ӳٽǶ����ô���!";
							break;
						}
					case 2:
						{
							str = "A�෢��������ô���!";
							break;
						}
					}
					
					break;
					
				}
			case 1:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "B���ź�ǿ�����ô���!";
							break;
						}
					case 1:
						{
							str = "B���ӳٽǶ����ô���!";
							break;
						}
					case 2:
						{
							str = "B�෢��������ô���!";
							break;
						}
					}

					break;
					
				}
			case 2:
				{
					
					switch(kinds)
					{
					case 0:
						{
							str = "C���ź�ǿ�����ô���!";
							break;
						}
					case 1:
						{
							str = "C���ӳٽǶ����ô���!";
							break;
						}
					case 2:
						{
							str = "C�෢��������ô���!";
							break;
						}
					}

					break;
				}
			}

		}
		
		MessageBox(str," ",MB_OK|MB_ICONASTERISK);
}

//��ȡ�Ƕ�
//short generatrixno ĸ�߱��
//short phase  ��� 0 A�� 1 B�� 2 C��
//BYTE kinds        0  �ź�ǿ�� 1 �ӳٽǶ�
void CTTTView::ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds)
{
	
	BYTE ORDER[15];
	CString    str;
	//�Ƕ�����
	
	//ǰ����
	ORDER[0]  = 0x51;
	ORDER[1]  = 0x52;
	

	switch(kinds)
	{
	case 0:
		{
			ORDER[2]  = 0x58 + phase;//���źŽǶ�
			break;
		}
	case 1:
		{	
			ORDER[2]  = 0xC3 + phase;//���ӳٽǶ�
			break;
		}
	case 2:
		{	
			ORDER[2]  = 0XC9 + phase;//���������
			break;
		}
	case 3:
		{	
			ORDER[2]  = 0XC6 + phase;//����ģ�������ѹ
			break;
		}
	}
	
	ORDER[3]  = generatrixno-1;
	ORDER[4]  = 0;
	ORDER[5]  = 0;
	ORDER[6]  = 0;
	ORDER[7]  = 0;
	ORDER[8]  = 0;
	ORDER[9]  = 0;
	ORDER[10] = 0;
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	m_angles  = 0xff;
	
	//��Ƭ��������
	if(PcSendToSCM(ORDER))
	{
		
		Sleep(50);
		
		switch(phase)
		{
		case 0:
			{  
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("��ǰA�����õĽǶ�Ϊ%d�ȣ�",m_angles);//A����Ƕ�
						break;
					}
				case 1:
					{
						str.Format("��ǰA�����õ��ӳٽǶ�Ϊ%d�ȣ�",m_angles);//A����ӳٽǶ�
						break;
					}
				case 2:
					{
						str.Format("��ǰA�����õķ������Ϊ%d��",m_angles);//A����������
						break;
					}	
				case 3:
					{
						
						//����ģ�������ѹ
						if(m_angles == 0xff)
						{
							str = "������ģ��A�������ѹͨѶ���ϣ���";
						}
						else
						{
							//ǰ1λΪ��ѹ    0  ��  1��
							if(m_angles/128 > 0)
							{
								str.Format("����ģ��A�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("����ģ��A�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}

				}

				break;
				
			}
		case 1:
			{
				switch(kinds)
				{
				case 0:
					{
						str.Format("��ǰB�����õĽǶ�Ϊ%d�ȣ�",m_angles);//B����Ƕ�
						break;
					}
				case 1:
					{
						str.Format("��ǰB�����õ��ӳٽǶ�Ϊ%d�ȣ�",m_angles);//B����ӳٽǶ�
						break;
					}
				case 2:
					{
						str.Format("��ǰB�����õķ������Ϊ%d��",m_angles);//B����������
						break;
					}
				case 3:
					{
						
						//����ģ�������ѹ
						if(m_angles == 0xff)
						{
							str = "������ģ��B�������ѹͨѶ���ϣ���";
						}
						else
						{
							//ǰ1λΪ��ѹ    0  ��  1��
							if(m_angles/128 > 0)
							{
								str.Format("����ģ��B�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("����ģ��B�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}
				}

				break;
				
			}
		case 2:
			{
				switch(kinds)
				{
				case 0:
					{
						str.Format("��ǰC�����õĽǶ�Ϊ%d�ȣ�",m_angles);//C����Ƕ�
						break;
					}
				case 1:
					{
						str.Format("��ǰC�����õ��ӳٽǶ�Ϊ%d�ȣ�",m_angles);//C����ӳٽǶ�
						break;
					}
				case 2:
					{
						str.Format("��ǰC�����õķ������Ϊ%d��",m_angles);//C����������
						break;
					}
				case 3:
					{
						
						//����ģ�������ѹ
						if(m_angles == 0xff)
						{
							str = "������ģ��C�������ѹͨѶ���ϣ���";
						}
						else
						{
							//ǰ1λΪ��ѹ    0  ��  1��
							if(m_angles/128 > 0)
							{
								str.Format("����ģ��C�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							else
							{
								str.Format("����ģ��C�������ѹ(��ѹ:�� ����:%d)",ChangeIValue(m_angles%128));
							}
							
						}

						break;
					}
				}

				break;
				
			}
		case 3:
			{
				
				str.Format("��ǰ��·���Ϊ%d��",m_angles);       //��ȡֱ�ߺ�
				break;
				
			}
			
		}
		
		//	MessageBox(str,"",MB_OK|MB_ICONASTERISK);//��ʾ:
	}
	else
	{
		
		switch(phase)
		{
		case 0:
			{  
				switch(kinds)
				{
				case 0:
					{
						str.Format("A���ȡ�Ƕȴ���");
						break;
					}
				case 1:
					{
						str.Format("A���ȡ�ӳٽǶȴ���");
						break;
					}
				case 2:
					{
						str.Format("A���ȡ�����������");
						break;
					}	
				case 3:
					{
						str.Format("������ģ��A�������ѹ����");
						break;
					}
				}

				break;
				
			}
		case 1:
			{
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("B���ȡ�Ƕȴ���");
						break;
					}
				case 1:
					{
						str.Format("B���ȡ�ӳٽǶȴ���");
						break;
					}
				case 2:
					{
						str.Format("B���ȡ�����������");
						break;
					}
				case 3:
					{
						str.Format("������ģ��B�������ѹ����");
						break;
					}
				}

				break;
				
			}
		case 2:
			{
				
				switch(kinds)
				{
				case 0:
					{
						str.Format("C���ȡ�Ƕȴ���");
						break;
					}
				case 1:
					{
						str.Format("C���ȡ�ӳٽǶȴ���");
						break;
					}
				case 2:
					{
						str.Format("C���ȡ�����������");
						break;
					}
				case 3:
					{
						str.Format("������ģ��C�������ѹ����");
						break;
					}
				}

				break;
				
			}
		case 3:
			{
				
				str.Format("��ǰ��·��Ŷ�ȡ����");//��ȡֱ�ߺ�
				break;
				
			}
			
		}
		
	}
	
	MessageBox(str," ",MB_OK|MB_ICONASTERISK);
	
}

void CTTTView::OnButtonAngle() 
{
	CAngleSet  dlg;
	dlg.DoModal();		
}

UINT  ReadChannels(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());
	
	int  HalfCount                   = 0;
    BOOLEAN bHalfReady = 0, bStopped = 0;
    U32                           count1;
	DataLen                =           0;

	do{
	    do {
             AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
	    } while (!bHalfReady && !bStopped);

        AI_AsyncDblBufferTransfer(card, ReadBuff);
           	 for(int i = 0;i < 512; i++)
			 {
			 	 
				 DataBuf[DataLen++] = ReadBuff[i]/m_DivideVal;	
				 
				 if(DataLen > 1000000)
				 {
					 bClearOp = TRUE;
					 break;
				 }
					 
			 }
			 HalfCount++;

	}while (!bClearOp && !bStopped);
     AI_AsyncClear(card, &count1);

     pview->GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	 pview->GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	 return 0;

}


void CTTTView::OnRealRecord() 
{    
	//�������
	UpdateData(TRUE);

	short m_selectCh = 0;

	if(m_bCh0)
	{
		m_selectCh ++;	 
		m_Channels        =  0;//ͨ��
	}
	
	if(m_bCh1)
	{
		m_selectCh ++;	
		m_Channels        =  1;//ͨ��
	}
	
	if(m_bCh2)
	{
		m_selectCh ++;
		m_Channels        =  2;//ͨ��
	}
	
	if(m_bCh3)
	{
		m_selectCh ++;
		m_Channels        =  3;//ͨ��
	}
	
	if(m_bCh4)
	{
		m_selectCh ++;
		m_Channels        =  4;//ͨ��
	}
	
	if(m_bCh5)
	{
		m_selectCh ++;
		m_Channels        =  5;//ͨ��
	}

	if(m_bCh8)
	{
		m_selectCh ++;
		m_Channels        =  8;//ͨ��
	}
	
	if(m_bCh9)
	{
		m_selectCh ++;	
		m_Channels        =  9;//ͨ��
	}
	
	if(m_bCh10)
	{
		m_selectCh ++;
		m_Channels        =  10;//ͨ��
	}
	
	//�Դ���
    if(m_selectCh == 1)
	{
		m_ShowWave  = TRUE;
	}
	else 
	{
		MessageBox("�Բɲ���ʱ����ѡ��һ����Ψһһ��\r\n�ɼ�ͨ�����ɼ����ݣ���","",MB_OK|MB_ICONWARNING);
		return;
	}
	
	
	memset(ReadBuff,0,1024);
	memset(DataBuf,0,1000000);
	/*
    for(int i = 0; i < 1000000; i++)
	{
	   DataBuf[i] = 0;
	}
	*/
		
	err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err != 0) 
	{
	    Beep(300,400);
		return;
    }
	       
    err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
   
	//ͨ�� 
	err = AI_ContReadChannel(card,m_Channels, AD_B_10_V, ReadBuff, /*nReadCount*/1024, 
		    100000, ASYNCH_OP);
  	
	AfxBeginThread(ReadChannels,this);

	bClearOp = 0;
	
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(TRUE);
	
	/*
	DWORD ThreadID =         0;
	HANDLE m_handles = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReadChannels,(void *)this,0,&ThreadID);
	WaitForSingleObject(m_handles,INFINITE);
    CloseHandle(m_handles);

	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	*/

	AfxBeginThread(ReadChannels,this);
	bClearOp = 0;
}

void CTTTView::OnRealSend() 
{
	//�������
	BYTE   m_order = 0;
	CString        str;

	UpdateData(TRUE);
    m_nStartPoint = 0;
    UpdateData(FALSE);

	short m_selectCh = 0;

	if(m_bCh0)
	{
		m_selectCh ++;	 
		m_Channels        =  0;//ͨ��
	}
	
	if(m_bCh1)
	{
		m_selectCh ++;	
		m_Channels        =  1;//ͨ��
	}
	
	if(m_bCh2)
	{
		m_selectCh ++;
		m_Channels        =  2;//ͨ��
	}
	
	if(m_bCh3)
	{
		m_selectCh ++;
		m_Channels        =  3;//ͨ��
	}
	
	if(m_bCh4)
	{
		m_selectCh ++;
		m_Channels        =  4;//ͨ��
	}
	
	if(m_bCh5)
	{
		m_selectCh ++;
		m_Channels        =  5;//ͨ��
	}

	if(m_bCh8)
	{
		m_selectCh ++;
		m_Channels        =  8;//ͨ��
	}
	
	if(m_bCh9)
	{
		m_selectCh ++;	
		m_Channels        =  9;//ͨ��
	}
	
	if(m_bCh10)
	{
		m_selectCh ++;
		m_Channels        =  10;//ͨ��
	}
	
	//�Դ���
    if(m_selectCh == 1)
	{
		m_ShowWave  = TRUE;
	}
	else 
	{
		MessageBox("�Բɲ���ʱ����ѡ��һ����Ψһһ��\r\n�ɼ�ͨ�����ɼ����ݣ���","",MB_OK|MB_ICONWARNING);
		return;
	}
		
	CWnd* pt    =    GetDlgItem(IDC_ORDER);
	pt->GetWindowText(str);	
	
	str.TrimLeft();
	str.TrimRight();
	
	if(str.IsEmpty())
	{
		MessageBox("�����ֲ���Ϊ�գ�","",MB_OK|MB_ICONWARNING);
		return;
	}
	
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

    //������
	SendOrderToSCM(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/, m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* 0x02Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);
	
}

void CTTTView::OnButtonStoprec() 
{
	bClearOp =	TRUE;
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(TRUE);
	Sleep(100);
	OnButtonUpdate();
}

//��ȡ��·���
void CTTTView::OnReadline() 
{
	/*
	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//���ʱ��Ƶ��
	dff = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);//��ó�ʼֵ
	qt1 = litmp.QuadPart;
	for(int i = 0; i < 10000; i ++)
	{
	}
	QueryPerformanceCounter(&litmp);//�����ֵֹ
	qt2 = litmp.QuadPart;
	dfm = (double)(qt2-qt1);
	dft = dfm/dff;//��ö�Ӧ��ʱ��ֵ
	*/
	
	UpdateData(TRUE);
	ReadThreePhaseAngle(m_generatrix,3,0);
}


//����BCH��63��45��3
void CTTTView::Encode_Bch_63_45_3(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 63,k = 45;
	BYTE  bb[18];
	g[0]  = 1;
	g[1]  = 1;
	g[2]  = 1;
	g[3]  = 1;
	g[4]  = 0;
	g[5]  = 0;
	g[6]  = 1;
	g[7]  = 1;
	g[8]  = 0;
	g[9]  = 1;
	g[10] = 0;
	g[11] = 0;
	g[12] = 0;
	g[13] = 0;
	g[14] = 0;
	g[15] = 1;
	g[16] = 1;
	g[17] = 1;

	for (i = 0; i < length - k; i++)//length = 63, k = 45
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	//ǰ����ϵ��
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];
	}

	//����������
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
	}

		//ssgg debug
			//д���ı��ļ�
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<64; i++) {
				CString mystr;
				if(g[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
		//end ssgg debug
}

//����BCH��31��21��2
void CTTTView::Encode_Bch_31_21_2(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 31,k = 21;
	BYTE  bb[10];
    g[0]  =    1;
    g[1]  =    0;
    g[2]  =    0;
    g[3]  =    1;
    g[4]  =    0;
    g[5]  =    1;
    g[6]  =    1;
    g[7]  =    0;
    g[8]  =    1;
    g[9]  =    1;
    g[10] =    1;

	for (i = 0; i < length - k; i++)
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	CString str;
	
	//ǰ����ϵ��
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];	
		
		str.Format("g[%d]=%d",i,g[i]);
		WriteToLog(str);
	}



	//����������
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
		
		str.Format("g[%d]=%d",i + length - k,g[i + length - k]);
		WriteToLog(str);
	}
	
	g[31] = 0;

}


//����BCH��45��27��3
void CTTTView::Encode_Bch_45_27_3(BYTE g[],BYTE data[])
{
	int i,j,feedback,length = 45,k = 27;
	BYTE      bb[18];

   	g[0]   = 1;
	g[1]   = 1;
	g[2]   = 1;
	g[3]   = 1;
	g[4]   = 0;
	g[5]   = 0;
	g[6]   = 1;
	g[7]   = 1;
	g[8]   = 0;
	g[9]   = 1;
	g[10]  = 0;
	g[11]  = 0;
	g[12]  = 0;
	g[13]  = 0;
	g[14]  = 0;
	g[15]  = 1;
	g[16]  = 1;
	g[17]  = 1;

	for (i = 0; i < length - k; i++)
	{
		bb[i] = 0;
	}
	
	for (i = k - 1; i >= 0; i--) 
	{
		feedback = data[i] ^ bb[length - k - 1];
	
		if (feedback != 0)
		{
			for (j = length - k - 1; j > 0; j--)
			{

				if (g[j] != 0)
				{
					bb[j] = bb[j - 1] ^ feedback;
				}
				else
				{
					bb[j] = bb[j - 1];
				}

			}

			bb[0] = g[0] && feedback;
		} 
		else
		{

			for (j = length - k - 1; j > 0; j--)
			{
				bb[j] = bb[j - 1];
			}

			bb[0] = 0;
		}

	}

	CString str;
	
	//ǰ����ϵ��
	for (i = 0; i < length - k; i ++)
	{
		g[i] = bb[i];	
		
		str.Format("g[%d]=%d",i,g[i]);
		WriteToLog(str);
	}

	//����������
	for (i = 0; i < k; i++)
	{	
		g[i + length - k] = data[i];
		
		str.Format("g[%d]=%d",i + length - k,g[i + length - k]);
		WriteToLog(str);
	}
	
}

void CTTTView::OnEvent(WPARAM wParam, LPARAM lParam)
{
	
	switch(wParam)
	{
	case 1:
		{	
			UpdateData(TRUE);
			break;
		}
	case 2:
		{
		    UpdateData(FALSE);	
			break;
		}
	}
	
}

void CTTTView::OnSelchangeProtocols() 
{
	UpdateData(TRUE);	
	
	CString   str;

	if(m_ProtocolControl.GetCount() >= 0)
	{
		m_ProtocolControl.GetLBText(m_ProtocolControl.GetCurSel(),str);
	    m_protocol = atoi(str);

		CWnd* pt = GetDlgItem(IDC_CHECK4BIT);

		if(m_protocol == 22)
		{	
			UpdateData(FALSE);
			pt->EnableWindow(TRUE);
		}
		else
		{
			pt->EnableWindow(FALSE);
		}
		
		InitOrderCombo(m_protocol);
		
		OnSelchangeOrdercombo();

	}

}


BOOL CTTTView::DecodeBCH45273(BYTE recd[])
{
	
        register int i, j, u, q, t2, count = 0, syn_error = 0;
		short elp[8][32], l[1], s[6];
		short root[32], loc[32],reg[32];
		short qt[32], r[8][32];
		short b[8][32];
		short degr[32], degb[32];
		short temp, aux[32]; 
        CString         str;
		short m = 6, n = 63 , length = 45, t = 3, k = 27, d = 7;
	//	short m = 6, n = 63 , length = 56, t = 4, k = 32, d = 9;
     
		
		short alpha_to[64], index_of[64];
	    
		alpha_to[0]  = 1,index_of[0]   = -1,
		alpha_to[1]  = 2,index_of[1]   = 0,
		alpha_to[2]  = 4,index_of[2]   = 1,
		alpha_to[3]  = 8,index_of[3]   = 6,
		alpha_to[4]  = 16,index_of[4]  = 2,
		alpha_to[5]  = 32,index_of[5]  = 12,
		alpha_to[6]  = 3,index_of[6]   = 7,
		alpha_to[7]  = 6,index_of[7]   = 26,
		alpha_to[8]  = 12,index_of[8]  = 3,
		alpha_to[9]  = 24,index_of[9]  = 32,
		alpha_to[10] = 48,index_of[10] = 13,
		alpha_to[11] = 35,index_of[11] = 35,
		alpha_to[12] = 5,index_of[12]  = 8,
		alpha_to[13] = 10,index_of[13] = 48,
		alpha_to[14] = 20,index_of[14] = 27,
		alpha_to[15] = 40,index_of[15] = 18,
		alpha_to[16] = 19,index_of[16] = 4,
		alpha_to[17] = 38,index_of[17] = 24,
		alpha_to[18] = 15,index_of[18] = 33,
		alpha_to[19] = 30,index_of[19] = 16,
		alpha_to[20] = 60,index_of[20] = 14,
		alpha_to[21] = 59,index_of[21] = 52,
		alpha_to[22] = 53,index_of[22] = 36,
		alpha_to[23] = 41,index_of[23] = 54,
		alpha_to[24] = 17,index_of[24] = 9,
		alpha_to[25] = 34,index_of[25] = 45,
		alpha_to[26] = 7,index_of[26]  = 49,
		alpha_to[27] = 14,index_of[27] = 38,
		alpha_to[28] = 28,index_of[28] = 28,
		alpha_to[29] = 56,index_of[29] = 41,
		alpha_to[30] = 51,index_of[30] = 19,
		alpha_to[31] = 37,index_of[31] = 56,
		alpha_to[32] = 9,index_of[32]  = 5,
		alpha_to[33] = 18,index_of[33] = 62,
		alpha_to[34] = 36,index_of[34] = 25,
		alpha_to[35] = 11,index_of[35] = 11,
		alpha_to[36] = 22,index_of[36] = 34,
		alpha_to[37] = 44,index_of[37] = 31,
		alpha_to[38] = 27,index_of[38] = 17,
		alpha_to[39] = 54,index_of[39] = 47,
		alpha_to[40] = 47,index_of[40] = 15,
		alpha_to[41] = 29,index_of[41] = 23,
		alpha_to[42] = 58,index_of[42] = 53,
		alpha_to[43] = 55,index_of[43] = 51,
		alpha_to[44] = 45,index_of[44] = 37,
		alpha_to[45] = 25,index_of[45] = 44,
		alpha_to[46] = 50,index_of[46] = 55,
		alpha_to[47] = 39,index_of[47] = 40,
		alpha_to[48] = 13,index_of[48] = 10,
		alpha_to[49] = 26,index_of[49] = 61,
		alpha_to[50] = 52,index_of[50] = 46,
		alpha_to[51] = 43,index_of[51] = 30,
		alpha_to[52] = 21,index_of[52] = 50,
		alpha_to[53] = 42,index_of[53] = 22,
		alpha_to[54] = 23,index_of[54] = 39,
		alpha_to[55] = 46,index_of[55] = 43,
		alpha_to[56] = 31,index_of[56] = 29,
		alpha_to[57] = 62,index_of[57] = 60,
		alpha_to[58] = 63,index_of[58] = 42,
		alpha_to[59] = 61,index_of[59] = 21,
		alpha_to[60] = 57,index_of[60] = 20,
		alpha_to[61] = 49,index_of[61] = 59,
		alpha_to[62] = 33,index_of[62] = 57,
		alpha_to[63] = 0 ,index_of[63] = 58;
	
	t2 = 2 * t;
	
	////�����ۺϲ�֢ 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//�޸� 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // ���ô����־
			// ת���ۺϲ�֢�Ӷ���ʽ��������ʽ
			s[i] = index_of[s[i]];
			
	}
	
	//�д���Ļ�
	if (syn_error) 
	{
		
		//��������λ�ö���ʽ��ŷ�������㷨��
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//����b(x)����ֵ
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// ��񻯴���λ�ö���ʽ
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// ��Chien search�ҵ������λ�� 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			}
			
			
			if (count == l[u])
			{
                m_CollectNos = l[u];

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;
					str.Format("��������λ�ã�%d",loc[i]);
					WriteToLog(str);
				}
				return TRUE;
				
			}
			else
			{
				str.Format("�������Ϊ�� count = %d��l[%d] = %d",count,u,l[u]);
				WriteToLog(str);
				return FALSE;
			}
			
			//length - k -> lengthΪ����ֵ 
		}
		else
		{
			str.Format("�������Ϊ��%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		m_CollectNos = 0;
		str = "t = 0,û�д���";
		WriteToLog(str);
		return TRUE;
	}
	
}


UINT  ReadBchChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());	
    pview->ReadBCHMeter();
	return 0;
}


void CTTTView::OnSend() 
{
	UpdateData(TRUE);
	CWnd* pt  = GetDlgItem(IDC_RECEIVE);
	pt->SetWindowText(" ");
	m_ReceiveStr = "";
	
	m_SendOrder.TrimLeft();
	m_SendOrder.TrimRight();
	
	if(m_SendOrder.IsEmpty())
	{
		MessageBox("��������BCH���� ��","",MB_OK);
		return;
	}
	
	//��ɼ�������
	if(m_iModeSel == 1)
	{
	
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_BUTTON_ANGLE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);
		
		for(int i = 0; i < 270000; i++)
		{
			DataBuf[i] = 0;
		}
		//memset(DataBuf,0,300000);
		
		AfxBeginThread(ReadBchChannel,this);
		
		m_ShowWave  = TRUE;
	}
	else
	{
		//���ڷ���
		//�򴮿ڷ�������
		int         m_order      = 0;
		CString                  str;
		UpdateData(TRUE);
		CString TestStr = m_SendOrder;
		CString                 Temp1;
		int                         k;
		CString            str1,s;
		SendByteArray.RemoveAll();
		TestStr.TrimRight();
        TestStr.TrimLeft();
	
		GetDlgItem(IDC_RECEIVE)->SetWindowText("");
		GetDlgItem(IDC_SENDORDER)->SetWindowText("");

		while(TestStr.Find(' ') != -1)
		{
			
			k = TestStr.Find(' ');
			Temp1 = TestStr.Left(k);
			
			Temp1.TrimLeft();
			Temp1.TrimRight();
			
			Temp1 = Temp1.Right(Temp1.GetLength()-2);
			Temp1.MakeLower();
	
			SendByteArray.Add(GetHexValue(Temp1));
			TestStr  = TestStr.Right(TestStr.GetLength() - k - 1);
			TestStr.TrimLeft();
			TestStr.TrimRight();
			
		}

	
		
		TestStr = TestStr.Right(TestStr.GetLength() - 2);
		TestStr.MakeLower();

		SendByteArray.Add(GetHexValue(TestStr));
		
		if(SendByteArray.GetSize() < 16)
		{
			MessageBox("���������ݸ���С��16����","����",MB_OK|MB_ICONWARNING);
			SendByteArray.RemoveAll();
			return;
		}

		BYTE TempByte  = 0;
		//14 �����
		for(int i = 0; i < 14; i ++)
		{
			TempByte = TempByte + SendByteArray[i];
		}
		
		SendByteArray[14] = TempByte;      
		
		//15������
        SendByteArray[15] = 0x16;

		//�򴮿ڷ���
		SendByteArrayToCom();
	}

}

void CTTTView::ReadBCHMeter()
{	

	CString TestStr = m_SendOrder;
	CString           Temp1;
	int                   k;
	//ѭ������   
	int     HalfCount  =     0;
	BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
	U32                  count;
	DataLen            =     0; 
	memset(ReadBuff,0,1024);
	int          DataValues = 0;
	CByteArray      m_DataArray;
	U32               output[5];
	BYTE             Receive[5];
	CString  str1,str,s;

	while(TestStr.Find(' ') != -1)
	{
	 
		k = TestStr.Find(' ');
	    Temp1 = TestStr.Left(k);
		
		Temp1.TrimLeft();
		Temp1.TrimRight();

		Temp1 = Temp1.Right(Temp1.GetLength()-2);
		Temp1.MakeLower();
      	m_DataArray.Add(GetHexValue(Temp1));

		TestStr  = TestStr.Right(TestStr.GetLength() - k - 1);
		
		TestStr.TrimLeft();
		TestStr.TrimRight();

	}
	
	TestStr = TestStr.Right(TestStr.GetLength() - 2);
    TestStr.MakeLower();

	m_DataArray.Add(GetHexValue(TestStr));

	
	if(m_DataArray.GetSize() < 15)
	{
		MessageBox("BCH�������ݸ���������","",MB_OK);
		return;
	}
	else
	{
		
		BYTE ORDER[15];
		
		for(int i = 0; i < 14; i++)
		{
			ORDER[i] = m_DataArray[i];
		}	
				
		m_SendOrder = "";
		
		ORDER[14]    = 0;

		//��ǰ14λ
		for(int j = 0; j <= 13; j++)
		{

			WriteP9111_CHANNEL_DOPort(ORDER[j]); 
			
			if(j >= 2)
			{	
				//�����
				ORDER[14] = ORDER[14] + ORDER[j];
			}
			
			if(ORDER[j] > 15)
			{
				//Temp1.Format(" 0x%0x \r\n",ORDER[j]);
				Temp1.Format(" 0x%0x  ",ORDER[j]);
			}
			else
			{
				//Temp1.Format(" 0x0%0x \r\n",ORDER[j]);
				Temp1.Format(" 0x0%0x  ",ORDER[j]);
			}
			m_SendOrder = m_SendOrder + Temp1;
			
		}
		
		
		Temp1.Format(" 0x%0x ",ORDER[14]);
		m_SendOrder = m_SendOrder + Temp1;
		SendMessage(WM_EVENT,2,0);

		//���ͼ����
		WriteP9111_CHANNEL_DOPort(ORDER[14]);
        		
		//��һ����
		WriteP9111_CHANNEL_DOPort(0X01);
		
		
		//�߷�����
		for( j = 0; j < 5;j ++)
		{
			
			err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//ʱ��
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
			}
			
			//�ߵ�ʱ������,��Ҫ��ʱ
			err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
			}
			
			Sleep(1);
			
			err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//ʱ��
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
			}
			
			//�ߵ�ʱ������,��Ҫ��ʱ
			err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
			if(err != 0)
			{
				Beep(300,400);
				//MessageBox("д�˿�ʧ��!","���棺",MB_OK|MB_ICONWARNING);
			}
			Receive[j] = BYTE(output[j] & 0xff);
			Sleep(1);
			
			
		}
		
		/**/
		str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//���λ��λȥ��
		//AfxMessageBox(str1);
    
		CTime time = CTime::GetCurrentTime();
		CString s;
		s.Format("%4d-%2d-%2d %2d:%2d:%2d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //ת��ʱ���ʽ
		//WriteToLog("˫��ͨѶ���\r\n" + str + "\r\n" + str1 + s);
		
		
		if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
		{
			WriteToLog("˫��ͨѶʱ����Ͳ���!\r\n" + str + "\r\n" + str1);
			Beep(300,400);
		}
		
		switch(ORDER[2])
		{
		case 0x53://pc������
			{
				//Receive[1]������ĸ��  Receive[2]������ ��· Receive[3]������ ���
				if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
				{
					WriteToLog("˫��ͨѶʱ��������� 0x53!\r\n" + str + "\r\n" + str1);
					Beep(300,400); 
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5c://����A�ഥ���Ƕ�
			{
				if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5C!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5d://����B�ഥ���Ƕ�
			{
				if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5d!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x5e://����C�ഥ���Ƕ�
			{
				if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5e!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				break;
			}
		case 0x58://��ȡA�ഥ���Ƕ�
			{
				if(Receive[0] != 0x68)
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x58!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x59://��ȡB�ഥ���Ƕ�
			{
				if(Receive[0] != 0x69)
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x59!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x5a://��ȡC�ഥ���Ƕ�
			{
				if(Receive[0] != 0x6a)
				{
					WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5a!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		case 0x9c://��ȡֱ�ߺ�
			{
				if(Receive[0] != 0xac)
				{
					WriteToLog("˫��ͨѶʱ��ȡֱ�߱�Ų��� 0x5a!\r\n" + str + "\r\n" + str1);
					Beep(300,400);
					WriteToLog(s + "\r\n");
				}
				else
				{
					m_angles = Receive[2];//Receive[1];
				}
				break;
			}
		}
		
		CTime time0  = CTime::GetCurrentTime();

		
		//������ͨ������,m_CollectChannels�ɼ�ͨ��
		err = AI_ContReadChannel(card,m_CollectChannels, AD_B_10_V, ReadBuff, 1024, 
			(F64)100000, ASYNCH_OP);

		if (err!=0) 
		{  
			Beep(300,400); 
		}
		
		bClearOp  = FALSE;
		
		do
		{
			do
			{
				//����
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
				
			} while (!bHalfReady && !bClearOp);
			
			if (!bClearOp) 
			{
				
				//���Ͱ�������
				AI_AsyncDblBufferTransfer(card, ReadBuff);
				bHalfReady     =      FALSE;
				
				for(int i = 0; i < 512; i++)
				{	
					//���ֵ         m_maxDecimalVal      1��PCI-9111DR 4096     2��PCI-9111HR 65536 
    		        //�ɵ���Ҫ����ֵ m_DivideVal          1��PCI-9111DR   16     2��PCI-9111HR     1 
					DataValues = ReadBuff[i]/m_DivideVal;
					
					//��������,����m_maxDecimalVal/2Ϊ����
					if(DataValues > m_maxDecimalVal/2)
					{
						DataValues =  -(m_maxDecimalVal - DataValues);
					}
					
					DataBuf[DataLen++] = DataValues;
					
				}
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1     -       time0;
				
				if(m_protocol != 22)
				{
					
					//�������22Э��
					if(ts.GetTotalSeconds() > (m_protocol%10)*9)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				else
				{						
					//�����22Э��
					if(ts.GetTotalSeconds() > 9)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
				switch(m_protocol)
				{
				case 22:
					{
						
					}
				case 31:
					{
						
					}
				case 32:
					{
						
					}
				case 71:
					{
						
					}
				case 72:
					{
						
						
					}
				case 73:
					{
						//64*4
						if(DataLen >= 131584)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 61:
					{
						// 1024 + 45*4*512  = 93184
						if(DataLen >= 93184)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				case 62:
					{
						//1024 + 4*45*2*512 = 185344
						if(DataLen >= 185344)
						{	
							bClearOp = TRUE;
						}
						
						break;
					}
				
				}


			}
			
		}while (!bClearOp && !bStopped);
		
		AI_AsyncClear(card, &count);
		
		long m_checklengths = 0;
		
		switch(m_protocol)
		{
		case 22:
			{
				
			}
		case 31:
			{
				
			}
		case 32:
			{
				
			}
		case 71:
			{
				
			}
		case 72:
			{
				
				
			}
		case 73:
			{
				//64*4
				m_checklengths = 131584;
				break;
			}
		case 61:
			{
				// 1024 + 45*4*512  = 93184
				m_checklengths = 93184;
				break;
			}
		case 62:
			{
				//1024 + 4*45*2*512 = 185344
				m_checklengths = 185344;
				break;
			}
		}
		
		if(DataLen >= m_checklengths)
		{
			double GetValue = Decode();
			
			if(GetValue >= 0)//����
			{
				m_data.Format("%f",GetValue);//.2
			}
			else
			{
				m_data = "NULL";
			}
			
		}
		else
		{
			m_ReceiveStr = "<<�ɼ����ݴ���>>";
			m_data       = "NULL";
		}

		CEdit * pt =(CEdit *)GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText(m_data);

		CWnd* pts   = GetDlgItem(IDC_REAL_START);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SEND);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SETTIMER);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_DECODE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_RADIO_REALTIME);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_COMSET);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SENDALLONE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_BUTTON_ANGLE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_REALSTOP);
		pts->EnableWindow(FALSE);
		
	}
		
}

int CTTTView::GetHexValue(CString str)
{
    int iReturn = 0;

	int length = str.GetLength();
    for(int i = length - 1; i >= 0; i--)    
    {
		char cc =  str.GetAt(i);// str[i];

        if(cc >= '0' && cc <= '9')
            iReturn += int((cc - '0') * pow(16,length - i - 1));
        else if(cc >= 'a')
            iReturn += int((cc - 'a' + 10) * pow(16,length - i - 1));
        else 
            iReturn += int((cc - 'A' + 10) * pow(16,length - i - 1));
    }

    return iReturn ;
}

UINT  ContinueReadChannel(LPVOID lParam)
{   
	CMainFrame* pt = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CTTTView* pview = (CTTTView *)(pt->GetActiveView());	
    pview->ContinueRead();
	return 0;
}

void CTTTView::OnSettimer() 
{
	UpdateData(TRUE);
    m_nStartPoint = 0;
    UpdateData(FALSE);

   	CString         str;
    m_Stopping  = FALSE;

	CTIMEDLG        dlg;
	dlg.m_seconds  = m_TimeSeconds;
	
	if(dlg.DoModal() != IDOK)
	{
         return;
	}

	m_TimeSeconds = dlg.m_seconds;

	if(m_addone)
	{
		str = "������������ģ����𽥼�1��";
	}
	else
	{
		str = "������������ģ��Ų��䣿";
	}

	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{


		CWnd* pt = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText("  ");
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
    	pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);
        
		m_data            = "  ";
		m_SuccessTimes    = 0;
   	    m_TotalTimes      = 0;
		m_CollectErrors   = 0;//�ɼ�����

		AfxBeginThread(ContinueReadChannel,this);
		
	}


}



void CTTTView::ContinueRead()
{

	CWnd* pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);

	CString           Temp;
	
	bClearOp  = FALSE;//���߳��˳�
	
	while (1)
	{	
		
		if(m_Stopping)//���߳��˳�
		{	
            pt = GetDlgItem(IDC_REAL_START);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SEND);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SETTIMER);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_DECODE);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_RADIO_REALTIME);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_COMSET);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_SENDALLONE);
			pt->EnableWindow(TRUE);	
			pt = GetDlgItem(IDC_BUTTON_ANGLE);
			pt->EnableWindow(TRUE);
			pt = GetDlgItem(IDC_REALSTOP);
			pt->EnableWindow(FALSE);
			break;
		}
					
		SendMessage(WM_EVENT,1,0);
	
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		
		if (err != 0) 
		{
			//Beep(300,400);
		}
		
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);	
		
		for(int i = 0; i < 120000; i++)
		{
		   DataBuf[i] = 0;
		}

		m_ShowWave     =      TRUE;
	    DWORD ThreadID =         0;

		HANDLE m_handles = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReadChannel,(void *)this,0,&ThreadID);
		WaitForSingleObject(m_handles,INFINITE);
        CloseHandle(m_handles);

		if(m_TotalTimes > 0)
		{
		    Temp.Format("��%d��,�ɹ�%d��[%.1f%s],�ɼ�����%d��[%.5f%s],��������%d��",m_TotalTimes,m_SuccessTimes,m_SuccessTimes*100.00/m_TotalTimes,"%",m_CollectErrors,m_CollectErrors*100.00000/m_TotalTimes,"%",m_TimeSeconds);
		}
		else
		{		 
			Temp.Format("��%d��,�ɹ�%d��[%.1f%s],,�ɼ�����0��",0,0,0,"%");
		}
	    
		CWnd* ptt = GetDlgItem(IDC_STATICFILE);
        ptt->SetWindowText(Temp);

		//�ɼ�����
		if(m_TotalTimes > 0)
		{
			Temp.Format("��%d��,�ɹ�%d��[%.1f%s]",m_TotalTimes,m_SuccessTimes,m_SuccessTimes*100.00/m_TotalTimes,"%");
		}
		else
		{		 
			Temp.Format("��%d��,�ɹ�%d��[%.1f%s]",0,0,0,"%");
		}
		
		ptt = GetDlgItem(IDC_DATAVALUE);
        ptt->SetWindowText(Temp);
		
		ptt = GetDlgItem(IDC_REAL_START);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SEND);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SETTIMER);
		ptt->EnableWindow(FALSE);
    	ptt = GetDlgItem(IDC_DECODE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_RADIO_REALTIME);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_COMSET);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_SENDALLONE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_BUTTON_ANGLE);
		ptt->EnableWindow(FALSE);
		ptt = GetDlgItem(IDC_REALSTOP);
		ptt->EnableWindow(TRUE);

		m_data  =           Temp;

		if(!m_Stopping)
		{
			
			for( i = 0; i < 5*m_TimeSeconds; i ++)
			{

				MSG message;
				if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}

				if(m_Stopping)
				{
					pt = GetDlgItem(IDC_REAL_START);
			        pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SEND);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SETTIMER);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_DECODE);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_RADIO_REALTIME);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_COMSET);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_SENDALLONE);
					pt->EnableWindow(TRUE);	
					pt = GetDlgItem(IDC_BUTTON_ANGLE);
					pt->EnableWindow(TRUE);
					pt = GetDlgItem(IDC_REALSTOP);
					pt->EnableWindow(FALSE);
					break;
				}
				
				Sleep(200);
			}
			
		}
		
		if(m_addone)
		{
			pt = GetDlgItem(IDC_MODULE);
			pt->EnableWindow(FALSE);
			
			m_module = m_module + 1;
			
			if(m_module%100 > 15)
			{
				m_module = (m_module/100 + 1)*100 + 1;
			}
			
			if(m_module > 13107115)
			{
				pt = GetDlgItem(IDC_MODULE);
				pt->EnableWindow(TRUE);	
				pt = GetDlgItem(IDC_REALSTOP);
				pt->EnableWindow(FALSE);
				pt = GetDlgItem(IDC_REAL_START);
				pt->EnableWindow(TRUE);	
				pt = GetDlgItem(IDC_SEND);
				pt->EnableWindow(TRUE);
				MessageBox("������ϣ���"," ",MB_OK|MB_ICONWARNING);
				break;
			}
			
			SendMessage(WM_EVENT,2,0);

		}

	}
	
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(TRUE);
	pt = GetDlgItem(IDC_MODULE);
	pt->EnableWindow(TRUE);
}

void CTTTView::OnFileNew() 
{
	
	
}

void CTTTView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	if(m_iModeSel == 2)
	{
	  status(m_StatusStr);
	}
	else
	{
		status("");
	}
}

void CTTTView::OnFileOpen() 
{
	
	
}

void CTTTView::OnFileSave() 
{
	
	
}

void CTTTView::OnCheck10() 
{
   UpdateData(TRUE);
   OnButtonUpdate();
  
}

void CTTTView::OnZhongzhi() 
{
	UpdateData(TRUE);
	
	//��ֵ�˲�
	for(int i = 2; i < 120000 - 2 ; i++)
	{
		 DataBuf[i] = (DataBuf[i-2] + DataBuf[i-1] + DataBuf[i] + DataBuf[i+1] + DataBuf[i+2])/5;
	}

}

void CTTTView::OnDecode() 
{
	UpdateData(TRUE);
	CString       ss;
	
	m_ReceiveStr = "";	
 	
	m_startpoint = m_Spinstart.GetPos();
	m_wavepoints = m_SpinAverage.GetPos();

	long time1 = GetTickCount();
   	double m_GetValue =  0;
    m_GetValue =	Decode();
	long time2 = GetTickCount();

	ss.Format("����������ʱ�䣺%6d��\r\n",time2 - time1);
	WriteToLog(ss);
	
	m_data       = "NULL";
	
	if(m_GetValue >= 0)
	{
		m_data.Format("%.2f",(m_GetValue));
	}
	else
	{
		Beep(300,400);
	}

	UpdateData(FALSE);
	
	OnButtonUpdate();
}


void CTTTView::OnFft() 
{
    #define KK  1024
	//re ��ʵ�� ��im���鲿����ll=1�����任����ll=-1�����任��nn:2���ݣ�
	double *pr,*pi;
	pr = new double[KK];
	pi = new double[KK];

	for(int i = 0 ; i < 229; i ++)
	{
		for(int j = 0; j < KK; j++)
		{
		   pr[j]     = double(DataBuf[i*KK+j]);
		   pi[j]     = double(DataBuf[i*KK+j]);
     	}
		
		//�����ݽ���FFT 
		fftnew(pr, pi, KK, 1);
	
		//�����ݽ��з�FFT
		//fftnew(pr, pi, KK, -1);
		
		for( j = 0; j < KK; j++)
		{
		   DataBuf[i*KK+j] = short(pr[j]);
		}

	}
	delete[] pr;
	delete[] pi;

    OnButtonUpdate();
}

BOOL CTTTView::FFT(double * data, unsigned long nn[], int ndim, int isign)
{
    #define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
	int idim;
	unsigned long i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	unsigned long ibit,k1,k2,n,nprev,nrem,ntot;
	double tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	for (ntot=1,idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for(idim=ndim;idim>=1;idim--)
	{
		n = nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) 
		{
			if (i2 < i2rev)
			{
				for (i1=i2;i1<=i2+ip1-2;i1+=2) 
				{
					for (i3=i1;i3<=ip3;i3+=ip2) 
					{
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) 
			{
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2)
		{
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) 
			{
				for (i1=i3;i1<=i3+ip1-2;i1+=2) 
				{
					for (i2=i1;i2<=ip3;i2+=ifp2) 
					{
						k1=i2;
						k2=k1+ifp1;
						tempr       = wr*data[k2]-wi*data[k2+1];
						tempi       = wr*data[k2+1]+wi*data[k2];
						data[k2]    = data[k1]-tempr;
						data[k2+1]  = data[k1+1]-tempi;
						data[k1]   += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
	return true;
}



//pr[n]���������ʵ��
//pi[n]����������鲿
//n��k ��������n=2^k
//fr[n]���������ʵ��
//fi[n]����������鲿
//l����0 FFT��1 IFFT
//il����0 �����ʵ��/�鲿��1 �����ģ/����
void CTTTView::kkfft(double pr[],double pi[],int n,int k,double fr[],double fi[],int l,int il)
{
    int it,m,is,i,j,nv,l0;
    double p,q,s,vr,vi,poddr,poddi;
    for (it=0; it<=n-1; it++)
	{ 
		m  = it; 
		is =  0;
		
		for (i=0; i<=k-1; i++)
		{ 
			j  = m/2;
			is =2*is+(m-2*j);
			m  =   j;
		}
		
		fr[it]=pr[is]; fi[it]=pi[is];
		
	}
	
    pr[0] = 1.0; 
    pi[0] = 0.0;
    p     = 6.283185306/(1.0*n);
    pr[1] = cos(p);
	pi[1] = -sin(p);

    if (l!=0)
	{ 
		pi[1]=-pi[1];
	}
    
	for (i=2; i<=n-1; i++)
	{
		p=pr[i-1]*pr[1]; q=pi[i-1]*pi[1];
        s=(pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
        pr[i]=p-q; pi[i]=s-p-q;
	}
    
	for (it=0; it<=n-2; it=it+2)
	{
		vr=fr[it]; vi=fi[it];
        fr[it]=vr+fr[it+1]; fi[it]=vi+fi[it+1];
        fr[it+1]=vr-fr[it+1]; fi[it+1]=vi-fi[it+1];
	}
    m=n/2; 
	nv=2;
    
	for (l0=k-2; l0>=0; l0--)
	{
		m=m/2; 
		nv=2*nv;

        for (it=0; it<=(m-1)*nv; it=it+nv)
		{
			
			for (j=0; j<=(nv/2)-1; j++)
            { 
				p=pr[m*j]*fr[it+j+nv/2];
				q=pi[m*j]*fi[it+j+nv/2];
				s=pr[m*j]+pi[m*j];
				s=s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
				poddr = p-q; 
				poddi = s-p-q;
				fr[it+j+nv/2]=fr[it+j]-poddr;
				fi[it+j+nv/2]=fi[it+j]-poddi;
				fr[it+j]=fr[it+j]+poddr;
				fi[it+j]=fi[it+j]+poddi;
            }

		}
	}

    if (l!=0)
	{
		for (i=0; i<=n-1; i++)
		{
			fr[i]=fr[i]/(1.0*n);
			fi[i]=fi[i]/(1.0*n);
		}
	}

	if (il!=0)
	{
		for (i=0; i<=n-1; i++)
		{ 
			pr[i]=sqrt(fr[i]*fr[i]+fi[i]*fi[i]);
			
			if (fabs(fr[i])<0.000001*fabs(fi[i]))
			{
			
				if ((fi[i]*fr[i])>0)
				{ 
					pi[i]=90.0;
				}
				else
				{
					pi[i]=-90.0;
				}

			}
			else
			{
				pi[i]=atan(fi[i]/fr[i])*360.0/6.283185306;
			}
			
		}
	}
}


//re ��ʵ�� ��im���鲿����ll=1�����任����ll=-1�����任��nn:2���ݣ�
void CTTTView::fftnew(double *re, double *im, int nn, int ll)
{
    #define PI 3.1415926535

	int j, ij, m, l, istep;
	double sc, actep, bctep, bcarg, aw, bw;
	double atemp, btemp;
	j = 0;
	sc = sqrt(1.0 / nn);
	
	for (ij=0; ij<=nn-1; ij++) 
	{
		if (ij <= j) 
		{
			actep = re[j] * sc;
			bctep = im[j] * sc;
			re[j] = re[ij] * sc;
			im[j] = im[ij] * sc;
			re[ij] = actep;
			im[ij] = bctep;
		}
		m = nn/2;
		do 
		{
			if ((j+1)<=m) 
				break;
			j = j - m;
			m = m/2;
		}
		while (m>=1);
		j = j + m;
	}
	
	l = 1;
	do 
	{
		istep = 2 * l;
		for (m=1; m<=l; m++) 
		{
			bcarg = -(PI * ll * (m-1)) / l;
			aw = cos(bcarg); 
			bw = sin(bcarg);
			for (ij=m-1; ij<=nn-1; ij=ij+istep) 
			{
				atemp = aw * re[ij+l] - bw * im[ij+l];
				btemp = aw * im[ij+l] + bw * re[ij+l];
				re[ij+l] = re[ij] - atemp;
				im[ij+l] = im[ij] - btemp;
				re[ij] = re[ij] + atemp;
				im[ij] = im[ij] + btemp;
			}
		}
		l = istep;
	} 
	while( l < nn );
}



//�Ⱦ�ڵ��������ƽ��
//n-���ͱ���������ĵ�����Ҫ��n>=5
//y-����Ϊn�����飬���n���Ⱦ�۲���ϵĹ۲�����
//yy-����Ϊn�����飬����ʱ���ƽ�����
void CTTTView::kkspt(int n,double y[],double yy[])
{ 
	int i;
	if (n < 5)
	{ 
		for (i = 0; i <= n-1; i++)
		{
			yy[i]=y[i];
		}
	}
	else
	{ 
		yy[0]=69.0*y[0]+4.0*y[1]-6.0*y[2]+4.0*y[3]-y[4];
		yy[0]=yy[0]/70.0;
		yy[1]=2.0*y[0]+27.0*y[1]+12.0*y[2]-8.0*y[3];
		yy[1]=(yy[1]+2.0*y[4])/35.0;
		for (i=2; i<= n-3; i++)
		{ 
			yy[i]=-3.0*y[i-2]+12.0*y[i-1]+17.0*y[i];
			yy[i]=(yy[i]+12.0*y[i+1]-3.0*y[i+2])/35.0;
		}
		yy[n-2]=2.0*y[n-5]-8.0*y[n-4]+12.0*y[n-3];
		yy[n-2]=(yy[n-2]+27.0*y[n-2]+2.0*y[n-1])/35.0;
		yy[n-1]=-y[n-5]+4.0*y[n-4]-6.0*y[n-3];
		yy[n-1]=(yy[n-1]+4.0*y[n-2]+69.0*y[n-1])/70.0;
	}
}

//����Լ���
double CTTTView::CorrelationCheck(short SourceArray[], short DestArray[], int m,short m_places)
{

    double           A,B,C,Pxy,sums;
	double      DestArrayBak[2000];
	double     DestArrayBaks[2000];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	//ȥֱ��
	if(m_qzhikiu)
	{	
		
		for( i = 0; i < m;i ++)
		{
			sums = sums + double(DestArray[i]);
		}
		
		for( i = 0; i < m;i ++)
		{
			
			DestArrayBak[i]  = double(DestArray[i] - sums*1.000/m);
		}

	}
	else
	{
		for( i = 0; i < m;i ++)
		{
			DestArrayBak[i]  = double(DestArray[i]);
		}
		
	}

	//Ҫ�ƶ�λ��
	if(WM_NUMBERS > 0 && m_findpipeimax)
	{

		if(m_places + 1 <= WM_NUMBERS/2)
		{
		
			//��ֵǰ��
			for( i = 0; i < m;i ++)
			{
				
				//�ƶ�λ��ƥ��
				if(i + (WM_NUMBERS/2 - m_places)*1 < m)
				{
					//����ǰ��
					DestArrayBak[i] =  DestArrayBak[i + (WM_NUMBERS/2 - m_places)*1];
				}
				else
				{
					DestArrayBak[i] = 0;
				}
							
				//ǰ�����ݸ�Ϊ0
				if(i <= m - m_iBandPassPoints)
				{
					DestArrayBak[i]    =  0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}
				
			}
			
		}
		else if(m_places + 1 > WM_NUMBERS/2 + 1)
		{
			
			//��ֵ����
			for( i = 0; i < m;i ++)
			{
				
				if(i >= (m_places- WM_NUMBERS/2)*1)
				{
					//���ݺ���
					DestArrayBaks[i] =  DestArrayBak[i - (m_places- WM_NUMBERS/2)*1];
				}
				else
				{
					DestArrayBaks[i] = 0;
				}
				
				//ǰ�����ݸ�Ϊ0
				if(i <= m - m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}
				
			}
			
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i] = DestArrayBaks[i];
			}
			
		}
		else  if(m_places + 1 == WM_NUMBERS/2 + 1)
		{
         
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i]  = double(DestArray[i]);
				
				//ǰ�����ݸ�Ϊ0
				if(i <= m- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;

					if( i < 256 - m_iBandPassPoints)
					{
						SourceArray[i]  =   0;
					}

				}

			}

		}

	}


	for(i = 0; i < m_iBandPassPoints;i ++)
	{
		A += SourceArray[256-m_iBandPassPoints+i]*DestArrayBak[m -m_iBandPassPoints+i];
        B += SourceArray[256-m_iBandPassPoints+i]*SourceArray[256-m_iBandPassPoints+i];
        C += DestArrayBak[m -m_iBandPassPoints+i]*DestArrayBak[m -m_iBandPassPoints+i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
	/*
    double           A,B,C,Pxy,sums;
	double      DestArrayBak[256];
	double     DestArrayBaks[256];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	//ȥֱ��
	if(m_qzhikiu)
	{	
		
		for( i = 0; i < m;i ++)
		{
			sums = sums + double(DestArray[i]);
		}
		
		for( i = 0; i < m;i ++)
		{
			
			DestArrayBak[i]  = double(DestArray[i] - sums*1.000/m);
		}

	}
	else
	{
		for( i = 0; i < m;i ++)
		{
			DestArrayBak[i]  = double(DestArray[i]);
		}
		
	}

	//Ҫ�ƶ�λ��
	if(WM_NUMBERS > 0 && m_findpipeimax)
	{

		if(m_places + 1 <= WM_NUMBERS/2)
		{
		
			//��ֵǰ��
			for( i = 0; i < m;i ++)
			{
				
				//�ƶ�λ��ƥ��
				if(i + (WM_NUMBERS/2 - m_places)*1 < m)
				{
					//����ǰ��
					DestArrayBak[i] =  DestArrayBak[i + (WM_NUMBERS/2 - m_places)*1];
				}
				else
				{
					DestArrayBak[i] = 0;
				}
							
				//ǰ�����ݸ�Ϊ0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBak[i]    =  0;
					SourceArray[i]     =  0;
				}
				
			}
			
		}
		else if(m_places + 1 > WM_NUMBERS/2 + 1)
		{
			
			//��ֵ����
			for( i = 0; i < m;i ++)
			{
				
				if(i >= (m_places- WM_NUMBERS/2)*1)
				{
					//���ݺ���
					DestArrayBaks[i] =  DestArrayBak[i - (m_places- WM_NUMBERS/2)*1];
				}
				else
				{
					DestArrayBaks[i] = 0;
				}
				
				//ǰ�����ݸ�Ϊ0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;
					SourceArray[i]      =   0;
				}
				
			}
			
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i] = DestArrayBaks[i];
			}
			
		}
		else  if(m_places + 1 == WM_NUMBERS/2 + 1)
		{
         
			for( i = 0; i < m;i ++)
			{
				DestArrayBak[i]  = double(DestArray[i]);
				
				//ǰ�����ݸ�Ϊ0
				if(i <= 256- m_iBandPassPoints)
				{
					DestArrayBaks[i]    =   0;
					SourceArray[i]      =   0;
				}

			}

		}

	}


	for(i = 0; i < m;i ++)
	{
		A += SourceArray[i]*DestArrayBak[i];
        B += SourceArray[i]*SourceArray[i];
        C += DestArrayBak[i]*DestArrayBak[i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
	*/
}

void CTTTView::OnReadfilter() 
{
	//���ļ��Ի���
	char szFilter[]="ƥ�䲨�������ļ�(*.TXT)|*.TXT||";
   	CFileDialog dlg(TRUE,"TXT","*.TXT",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);

	if(dlg.DoModal() == IDOK)
	{
	
		char                 buf[7];
		CString                 str;
		short  GetSourceArray[2048];
	
		//�õ����������ļ��ĵ������ݳ���
	    short length = GetFileEveryDataLength(dlg.GetPathName());
	
		if(!file.Open(dlg.GetPathName( ),CFile::modeRead))
		{
			MessageBox("�ļ��򿪴���!","ȷ��",MB_OK); 
			return;
		}

		if(length != 4 && length != 5)
		{
			file.Close();
			MessageBox("�������ļ�����TTT���������ļ���","ȷ��",MB_OK|MB_ICONWARNING);
			return;
		}

		MaxPointsNum = (file.GetLength())/(length + 2);	//12λ�ɼ���length + 2Ϊ6 16λ�ɼ���length + 2Ϊ7
	
		if(MaxPointsNum != 2048)
		{
			MessageBox("ƥ�䲨�����ݴ�СӦΪ2048������!","ȷ��",MB_OK);
			file.Close();
			return;
		}

		CWnd* ptt = GetDlgItem(IDC_STATICFILE2);
		ptt->SetWindowText("ƥ���ļ���" + dlg.GetPathName());

		file.Seek(0,CFile::begin);
		
		for(UINT j = 0; j < MaxPointsNum; j++)
		{
			file.Read(buf,length+2);
			str   =      buf;
			str.TrimLeft();
			str.TrimRight();
			GetSourceArray[j] = atoi(str);
			file.Seek(0,CFile::current);
		}
		file.Close();

		//��3-1,4-2
		for(int i = 0;i < 512;i ++)   
		{ 
			//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
		    GetSourceArray[i]       = GetSourceArray[2 * 512 + i] - GetSourceArray[i];
			GetSourceArray[512 +i]  = GetSourceArray[3 * 512 + i] - GetSourceArray[512 + i];
		}
		
		//��������
		for( i = 0;i < 256;i ++)   
		{ 
			SourceArrays[i]  = GetSourceArray[i] + GetSourceArray[256+i] + GetSourceArray[512+i] + GetSourceArray[768+i];
			m_ppwave[i]      = SourceArrays[i];
			
			str.Format("%5d,",SourceArrays[i]);
			//WriteToLog(str);
			
			//д���ı��ļ�
			FILE *text;
			if((text = fopen("c:\\datas.txt","a")) != NULL)
			{
				fputs(str ,text);
			
				if((i+1)%16 == 0)
				{
					fputs("\r\n",text); 
				}
				
				fclose(text);
			}

		}

		UpdateData(FALSE);	
		
		OnButtonUpdate();

	}
	
}


void CTTTView::OnDeletefile() 
{
	if(::DeleteFile("C:\\data.txt") != 0)
	{
		MessageBox("��־�ļ��Ѿ�ɾ��!"," ",MB_OK);
	}
	else
	{
        MessageBox("�Բ����Ҳ�����־�ļ���"," ",MB_OK|MB_ICONWARNING);
	}
	
}

void CTTTView::OnOpenfile() 
{
	CString strFileName("C:\\data.txt");
	CFileFind  fFind;
	BOOL bExist = fFind.FindFile(strFileName);   //�ж��ļ��Ƿ����
	fFind.Close ();
	
	if(!bExist)   //����ļ��������򴴽�
	{
         MessageBox("�Բ����Ҳ�����־�ļ���","",MB_OK|MB_ICONWARNING);
	}
	else
	{
		//�򿪴��ı��ļ�
	    WinExec( "notepad.exe C:\\data.txt",SW_SHOWMAXIMIZED);
	}
	
}

//�õ���ֵ�˲�
short CTTTView::GetMedianNum(short bArray[], int iFilterLen)
{
	//ѭ������
	int		i;
	int		j;
	
	// �м����
	short    bTemp;
	
	// ��ð�ݷ��������������
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// ����
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// ������ֵ
	if ((iFilterLen & 1) > 0)
	{
		// ������������Ԫ�أ������м�һ��Ԫ��
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// ������ֵ
	return bTemp;
}

void CTTTView::OnBchtest() 
{   
  /* card: kortets ID. Gis her startverdi -1, verdi settes senere av funksjonen Register_Card.  
       I16 er en datatype som er definert i dask.h. 16 bit signed int. */ 
 

    /* cardNumber: nummer til kort i maskinen. Refererer til fysisk plass p? hovedkortet. */  
 //   I16 cardNumber = 0;  

    /* cardType: type kort som skal benyttes. Konstanter som svarer til de ulike kort som st?ttes av  
        biblioteket finnes i dask.h.  */ 
 //   int cardType=PCI_9111DG;  

    /* Variabel som skal motta verdi fra digital inngang */  
//  U32 dig_inn = 0;  

    /* Initierer kort og softwarebibliotek som benyttes. Returnerer ID til kortet, eller negativ feilkode   
       dersom feil oppst?r. */  
  //  card = Register_Card(cardType, cardNumber); 

    /* Avslutter om initsieringen ikke gikk bra. */  
   // if (card < 0) 
   // {  
   //     printf("Feil ved initsiering av kortet." ); 
   //     printf("\nFeilkode: %d", card); 
   //     exit(1); 
   // } 

    /* Skriver kortets ID til skjerm. */ 
  //  printf("Card ID= %d", card); 
//	long m_time1 =  GetTickCount();

    /* Henter verdi fra digital inngang og skriver denne til skjerm */  


//  DI_ReadPort(card, P9111_CHANNEL_EDI,&dig_inn); 
/*
    long m_time2 =  GetTickCount();
    BYTE m_temp  = dig_inn & 0xff;
	char                   t[32] ;
	
	itoa(dig_inn, t, 2);
	CString        stddr;

	stddr.Format("����ʱ�䣺%d����,������ֵ:%s",m_time2-m_time1,t);
	AfxMessageBox(stddr);

    printf("\nVerdi fra digital inngang: %d\n", dig_inn);  

  //Release_Card(card);  



	return;

	CString      sFolderPath;
	BROWSEINFO            bi;
	char    Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner      = NULL;
	bi.pidlRoot       = NULL;
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle      = "�޸Ľ���·��";
	bi.ulFlags        = 0;
	bi.lpfn           = NULL;
	bi.iImage         = NULL;
	
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//ȡ���ļ���·����Buffer��
		sFolderPath =                 Buffer;//��·��������һ��CString������
		AfxMessageBox(sFolderPath);
	}

	LPMALLOC       lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc)))
		return;
	//�ͷ��ڴ�
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	//д���ı��ļ�
	FILE *text;
	if((text = fopen(sFolderPath + "\\data.txt","a")) != NULL)
	{
		fputs("jfvgffg\r\n",text);
		fclose(text);
	}
	else
	{
        AfxMessageBox("�ļ��򿪴���");
	}

	return;
	
	COleDateTime dateTest;
   // dateTest value = midnight 30 December 1899
    dateTest = COleDateTime::GetCurrentTime();
    CString        strtime;
	strtime.Format("%4d-%02d-%02d %02d:%02d:%02d",dateTest.GetYear(),dateTest.GetMonth(),dateTest.GetDay(),dateTest.GetHour(),dateTest.GetMinute(),dateTest.GetSecond());
	
   	AfxMessageBox(strtime);
	return;


	CString        strtime;
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CTime dateTest(systime);
	strtime.Format("%4d-%02d-%02d %02d:%02d:%02d",dateTest.GetYear(),dateTest.GetMonth(),dateTest.GetDay(),dateTest.GetHour(),dateTest.GetMinute(),dateTest.GetSecond());

	AfxMessageBox(strtime);
    */
   /*
	
	int m_bitvalue =  255;
	CString m_ReadRangeStr;
	m_ReadRangeStr.Format("%03x",m_bitvalue);
	AfxMessageBox(m_ReadRangeStr);
	return;
	*/
	/*
	//61,62,Э��,�����ֽ�,BCHУ�� 45_27_3
	BYTE          data[27];
	//61,62,Э��,�����ֽ�,BCHУ�� 45_27_3
	BYTE             g[45];

    //27λ����
	for(int j = 0; j < 27; j ++)
	{
		if(j == 26)
		{
			data[j] = 1;
		}
		else
		{
			data[j] = 0;
		}
	}
	
	//ת��BCH��45_27_3
	Encode_Bch_45_27_3(g,data);
	return;
	*/

	/*
	BYTE gg[31];
	gg[ 0] =   0;
	gg[ 1] =   0;
	gg[ 2] =   1;
	gg[ 3] =   1;
	gg[ 4] =   0;	
	gg[ 5] =   0;
	gg[ 6] =   1;
	gg[ 7] =   1;
	gg[ 8] =   0;
	gg[ 9] =   1;
	gg[10] =   0;
	gg[11] =   1;
	gg[12] =   1;
	gg[13] =   0;
	gg[14] =   0;
	gg[15] =   0;
	gg[16] =   0;
	gg[17] =   0;
	gg[18] =   0;
	gg[19] =   0;	
	gg[20] =   0;
	gg[21] =   0;
	gg[22] =   0;
	gg[23] =   0;
	gg[24] =   0;
	gg[25] =   0;
	gg[26] =   0;
	gg[27] =   0;
	gg[28] =   0;
	gg[29] =   0;
    gg[30] =   1;


 	DecodeBCH31212(gg);
	return;
	*/
 
    int               m_kkkk  = 113;
	int                       i;
	CString            str,str1;

	read_p();               /* Read m */
	
	for(int re = 0; re <= m; re ++)
	{
		str.Format("p[%d] = %d",re,p[re]);
		WriteToLog(str);
	}

	BYTE   recdbak[1024];

	//����٤������GF(2**m)
	generate_gf();          
	
	str.Format("int alpha_to[%d] ={",length);

	for( re = 0; re < pow(2,m); re ++)
	{

		if(re < pow(2,m) - 1)
		{
		   str1.Format("%3d,",alpha_to[re]);
		}
		else
		{
			str1.Format("%3d};",alpha_to[re]);
		}

		//����
		if((re + 1)%8 == 0)
		{ 
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;
	  //.Format("alpha_to[%d] = %d,index_of[%d] = %d",re,alpha_to[re],re,index_of[re]);
	
	}

	WriteToLog(str);
	

	str.Format("int index_of[%d] ={",length);

	for( re = 0; re < pow(2,m); re ++)
	{
	    if(re < pow(2,m) - 1)
		{
		   str1.Format("%3d,",index_of[re]);
		}
		else
		{
			str1.Format("%3d};",index_of[re]);
		}

		//����
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	/*
	for( re = 0; re < pow(2,m); re ++)
	{
		str.Format("alpha_to[%d] = %d,index_of[%d] = %d",re,alpha_to[re],re,index_of[re]);
		WriteToLog(str);
	}
	*/
    
	//�������ʽ
	gen_poly(); 

	str.Format("int        g[%d] ={",GetNo + 1);

	for( re = 0; re <= GetNo; re ++)
	{
	    if(re <= GetNo - 1)
		{
		   str1.Format("%3d,",g[re]);
		}
		else
		{
			str1.Format("%3d};",g[re]);
		}

		//����
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	//�����������
	srand((unsigned)time(NULL));

	str.Format("int     data[%d] ={",k);

	for( re = 0; re < k; re ++)
	{
		data[re] =  rand()%2;
	    
		if(re <  k - 1)
		{
		   str1.Format("%3d,",data[re]);
		}
		else
		{
			str1.Format("%3d};",data[re]);
		}

		//����
		if((re + 1)%8 == 0)
		{
			str1 = str1 + "\r\n                   ";
		}

		str = str + str1;

	}

	WriteToLog(str);
	
	/*
	for (i = 0; i < k; i++)
	{
		//data[i] =  rand()%2;  
        if(i < k - 1)
		{
			data[i] = 0;
		}
		else
		{
			data[i] = 1;
		}

		str.Format("data[%d] = %d",i,data[i]);
		WriteToLog(str);
	}
	*/
	
    
	//����BCH��
	Encode_Bch();           
	
	//�����
	for (i = 0; i < length - k; i++)
	{
		str.Format("bb[%d] = %d",i,bb[i]);
		WriteToLog(str);
	}
    
	//ǰ����ϵ��
	for (i = 0; i < length - k; i++)
	{
		recd[i] = bb[i];
	}

	//����������
	for (i = 0; i < k; i++)
	{
		recd[i + length - k] = data[i];
	}

	//�������ʽ
	str = "�������ʽΪ:";
    WriteToLog(str);

	for (i = 0; i < length; i++) 
	{
		str.Format("recd[%d] = %d,",i,recd[i]);
		WriteToLog(str);
	}

//	return;
   	
	//����������
	numerr = 2;
   	
	//�������λ��
	errpos[0] = 27;
	errpos[1] = 38;
//	errpos[2] = 23;
       	
    //����BCH�Ƿ�����
	for(int hhhh = 0; hhhh < length; hhhh ++)
	{
		recdbak[hhhh] = recd[hhhh];
	}

	/*
	for(int kkk = 0; kkk < length; kkk ++)
	{
			
		for(int kkkj = 0; kkkj < length; kkkj ++)
		{
			
		//	for(int kkks = 0; kkks < length; kkks ++)
			{
				
				recd[kkkj]  ^=  1;
				recd[kkk]   ^=  1;
			//	recd[kkks]  ^=  1;

				//str.Format("����λ��1��%d������λ��2��%d,����λ��3��%d",kkkj,kkk,kkks);
				str.Format("����λ��1:%d,����λ��2:%d",kkkj,kkk);
				WriteToLog(str);
				
				//��������
				decode_bch();
				
				WriteToLog("\r\n");
			}
			
		}

	}
	*/    

	if(numerr > 0)
	{
		for(i = 0; i < length; i ++)
		{
			recd[i] = recdbak[i];
		}		
		
		for (i = 0; i < numerr; i++)
		{
			recd[errpos[i]] ^= 1;

			str.Format("�Ӵ���λ�õ�%dλ:%d",i+1,errpos[i]);
			WriteToLog(str);
		}
		
		for( i = 0; i < length; i ++)
		{
			recdbak[i] = recd[i];
		}	

		//��������
		decode_bch();
		
		WriteToLog("�ԱȽ������:");
		
		for (i = 0; i < length; i++) 
		{

			if(recdbak[i] == recd[i])
			{
				str.Format("��ǰ recd[%3d] = %3d,��� recd[%3d] = %2d",i,recdbak[i],i,recd[i]);
			}
			else
			{
				str.Format("��ǰ recd[%3d] = %3d,��� recd[%3d] = %2d  ������λ��",i,recdbak[i],i,recd[i]);
			}

			WriteToLog(str);
		}
		
	}

	/**/


	MessageBox("BCH���Խ�������","ȷ��",MB_OK);
    return;


}

short CTTTView::GetFileEveryDataLength(CString filename)
{ 
	FILE *text;
	CString str;
	char s[120];
	
	if((text  = fopen(filename,"r"))==NULL)
	{
		return  0;
	}
	else
	{
		fgets(s,120,text);
		str = s;
		str.TrimRight();
		fclose(text);
		return str.GetLength();
	}

}

void CTTTView::OnRadio1() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table10[i];
	}
	
	//��������
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}
	
	OnButtonUpdate();
	
	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("ƥ��Ƕȣ�10��");

}

void CTTTView::OnRadio2() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table20[i];
	}
	
	//��������
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}	
	
	OnButtonUpdate();

	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("ƥ��Ƕȣ�20��");
}

void CTTTView::OnCheckDiffi2() 
{
    OnButtonUpdate();	
}

void CTTTView::OnCheckDiffi3() 
{
	OnButtonUpdate();	
}

//��ƥ��ֵ�����Ǹ���
double CTTTView::Decode()
{	
	CString             str,signstr;
    short               Diffs[3000];
    BYTE  SignalBit[100],TempSignalBit[100],TempSignalBitbak[100],Signal[8],m_result;
	BYTE       m_PlaceDifferent[45];

	m_ReceiveStr               = "";
	BYTE                   Data[39];
	double dataValue       =      0;
	double dataValueValue  =     -1;
	double m_ppvalue       =      0;
	long   m_sums          =      0;
	double m_maxppvalue    =      0;
	short  m_pipeiplace    =      0;
  	long   m_maxpptimes    =      1;//ƥ�����
	long                Diffn[1024];
	BOOL               m_checkplace;
    BYTE     m_GetOverRecords  =  0;//����0.6�ĸ���
	double         m_ThreePipei[150];
    BYTE         m_ByteRecords =  0;//�յ��ֽ���

	switch(m_protocol)
	{
	case 31:
		{

		}
	case 32:
		{

		}
	case 71:
		{
			
		}
	case 72:
		{

		}
	case 73:
		{
			m_ByteRecords = 63;
			break;
		}
	case 61:
		{
			m_ByteRecords = 45;
			break;
		}
	case 62:
		{
			m_ByteRecords = 90;
			break;
		}
	}

	
	//��ƥ�����ֵ
	if(m_findpipeimax)
	{
		m_maxpptimes	= WM_NUMBERS;
	}
	
	signstr.Format("===========================�۽��룬��ʼ��Ϊ��%d�����===========================",m_startpoint);
	
	m_ppvalue    =    0;
	WriteToLog(signstr);
	
	long          time0     = GetTickCount();
	double*		 m_ppresult	= new double[m_maxpptimes * m_ByteRecords];
		
   	//ԭʼƥ�䲨
	if (m_radio < 3)
	{
		//���������λ
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			
			//��������㷨���,3-1,4-2
			for(int i = 0;i < m_wavepoints;i ++)   
			{ 
				//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
				Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
				Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
			}
			
			//��������
			for( i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//ƽ��ֵ
				Diffs[i]       = Diffs[i] + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
			}
		
			//ƥ��ֵ
			for(int jj = 0; jj < m_maxpptimes; jj ++)
			{
				
				m_ppresult[index*m_maxpptimes + jj]   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,jj);

			}
			
			
		}
    
	}
	else
	{
		
		long    Diffs_Sums[256];
		short   Diffs_All[25600];

		WriteToLog("���Լ�ѧϰ���롿");
		
		for(int t = 0; t < 256; t ++)
		{
              Diffs_Sums[t]  =  0;
		}

		//��ѧϰ,���������λ
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			
			//��������㷨���,3-1,4-2
			for(int i = 0;i < m_wavepoints;i ++)   
			{ 
				//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
				Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
				Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
			}
			
			//��������
			for( i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//ƽ��ֵ
				Diffs[i]                              = Diffs[i]      + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
			    //�ۼ�ֵ
				Diffs_Sums[i]                         = Diffs_Sums[i] + abs(Diffs[i]);
				//��ֵ����
				Diffs_All[index*(m_wavepoints/2) + i] = Diffs[i];
			}            
		
		}

		//���Ӳ���ƽ��ֵ
		for(int  i = 0;i < m_wavepoints/2;i ++)
		{
			//�ۼ�ֵ
			SourceArrays[i]                         = short(Diffs_Sums[i]/m_ByteRecords);
		}		

		//��ѧϰ,���������λ
		for( index = 0; index < m_ByteRecords ;index ++)
		{
			
			//��������㷨���,3-1,4-2
			for(int i = 0;i < m_wavepoints/2;i ++)   
			{ 
				//�õ��źż�
				Diffs[i]  = Diffs_All[index*(m_wavepoints/2) + i];
			}
			
			//ƥ��ֵ
			for(int jj = 0; jj < m_maxpptimes; jj ++)
			{				
				m_ppresult[index*m_maxpptimes + jj]   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,jj);
			}
			
			
		}

	}

	m_maxppvalue  =    0;//���ƥ��ֵ
	
	//�����ƥ��ֵ
	for(int jj = 0; jj < m_maxpptimes; jj ++)
	{
		
		m_ppvalue    =    0;//ƥ��ֵ��
		
		for(int index = 0; index < m_ByteRecords ;index ++)
		{
			m_ppvalue = fabs(m_ppresult[jj + m_maxpptimes * index]) + m_ppvalue;
		}	

		//ƥ��ֵ����ֵ��:
		if(m_findpipeimax)
		{
			if(jj + 1 <= m_maxpptimes/2)
			{
				signstr.Format("��ƥ�����ֵ��:%6.3f����������%02d�㡿",m_ppvalue,int(m_maxpptimes/2 - jj));			
			}
			else if(jj + 1 > m_maxpptimes/2 + 1)
			{
				signstr.Format("��ƥ�����ֵ��:%6.3f����������%02d�㡿",m_ppvalue,jj - m_maxpptimes/2);
			}
			else if(jj + 1 == m_maxpptimes/2 + 1)
			{
				signstr.Format("��ƥ�����ֵ��:%6.3f������û���ƶ���",m_ppvalue);
			}
			
		}
		else
		{
			signstr.Format("��ƥ�����ֵ�ͣ�%6.3f��",m_ppvalue);
		}
		
		WriteToLog(signstr);
		
		
		if(m_ppvalue > m_maxppvalue)
		{
			m_maxppvalue =  m_ppvalue;//���ƥ��ֵ
			m_pipeiplace =         jj;//��ס���ƥ��λ��
		}
		
	}
	
	//��ƥ�����ֵ
	if(m_findpipeimax)
	{

		//ƥ��������ֵ�����λ��
		if(m_pipeiplace + 1 <= m_maxpptimes/2)
		{
			signstr.Format("\r\n��ƥ����Ժ����ֵ��%6.3f����������%02d�㡿\r\n",m_maxppvalue,m_maxpptimes/2 - m_pipeiplace);			
		}
		else if(m_pipeiplace + 1 > m_maxpptimes/2 + 1)
		{
			signstr.Format("\r\n��ƥ����Ժ����ֵ��%6.3f����������%02d�㡿\r\n",m_maxppvalue,m_pipeiplace - m_maxpptimes/2);
		}
		else if(m_pipeiplace + 1 == m_maxpptimes/2)
		{
			signstr.Format("\r\n��ƥ����Ժ����ֵ��%6.3f������û���ƶ���\r\n",m_maxppvalue);
		}
		
		WriteToLog(signstr);

	}
	
	
    //���ƥ��λ�õ�����
	for(int index = 0; index < m_ByteRecords ;index ++)
	{
		//��ƥ��ϵͳ
		m_ThreePipei[index] = m_ppresult[m_pipeiplace + m_maxpptimes * index];

		//ƥ��ֵ��
		if(m_ppresult[m_pipeiplace + m_maxpptimes * index]  > 0)
		{
			SignalBit[index] = 0;
		}
		else 
		{
			SignalBit[index] = 1;
		}

		//ƥ��ֵ����0.6�ĸ���
		if(fabs(m_ppresult[m_pipeiplace + m_maxpptimes * index]) > 0.65)
		{
			m_GetOverRecords ++;
		}
		
		signstr.Format(" �յ�����Ϊ��SignalBit[%2d] = %0x [%.3f]",index,SignalBit[index],m_ppresult[m_pipeiplace + m_maxpptimes * index]);
		WriteToLog(signstr);
		
		//�س���
		if((index + 1) % 8 == 0 || index == m_ByteRecords - 1)
		{
			
			if((index + 1) % 8 == 0)
			{
				
				if(SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{	
					signstr.Format(" 0x%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				
			}
			else
			{	

				BYTE   m_addValue  =    0;
 
				if(index == m_ByteRecords - 1)
				{
					BYTE        m_ttts;
					m_ttts   =  m_ByteRecords- (m_ByteRecords/8)*8;


					for(int jjj = 0; jjj < m_ttts; jjj ++)
					{
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow(2,m_ttts-1-jjj));
					
					}
				
				}

				/*
				if(SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{
					signstr.Format(" 0x%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				*/

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\nʮ������Ϊ:"+ signstr + "\r\n");
			m_ReceiveStr = m_ReceiveStr + signstr;
			
		}
		
	}
	
	delete[]   m_ppresult;

	if(m_protocol == 22)
	{		
		
		//��ͬ������
		m_sums    =     0;
		dataValue =    -1;
		
		/*********˳������������22Э��Ļ�*/
		for(short i = 0; i <  31; i ++)
		{

			//�Ա����ν��յ�������
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{

				//��ס��ͬ��λ��
				if(m_sums <= m_derrors)
				{
					m_PlaceDifferent[m_sums] = i;
				}
							
				m_sums ++;
			}
			
		}
		
		str.Format("  ��λ��(%d)",m_sums);
		WriteToLog(str);

		//�����5��������ͬ�Ļ�
		if(m_sums > m_derrors)
		{	
			m_ReceiveStr = m_ReceiveStr + str;
			return -1;
		}
		else
		{
	        WriteToLog("22Э���������:\r\n");
		}
        
		str.Format("��λ���%d��",m_sums);
		m_ReceiveStr    =             str;

		//���ݵ����ٴ���,����10�Ⱥ�5�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
		BYTE              DJSignalBit[32];

		for(index = 0; index < 32 ;index ++)
		{

			if(index < 31)
			{
				
				//��������㷨���,3-1,4-2
				for(int i = 0;i < 512;i ++)   
				{ 
					//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
					Diffs[i]        = DataBuf[(2*index * 4 + 2) * 512 + i + 1024] - DataBuf[ 2*index * 4 *  512 + i  + 1024];
					Diffs[512 + i]  = DataBuf[(2*index * 4 + 3) * 512 + i + 1024] - DataBuf[(2*index * 4 + 1) * 512 + i + 1024];
					
					//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
					Diffn[i]        = DataBuf[((2*index + 1) * 4 + 2) * 512 + i + 1024] - DataBuf[(2*index + 1) * 4      *  512 + i  + 1024];
					Diffn[512 + i]  = DataBuf[((2*index + 1) * 4 + 3) * 512 + i + 1024] - DataBuf[((2*index +1) * 4 + 1) *  512 + i  + 1024];
				}
				
				//��������
				for( i = 0;i < 256;i ++)   
				{ 
					//0��31���ӣ�1��32����
					Diffs[i]   = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,m_pipeiplace);
				
				//��ƥ��ϵͳ
		        m_ThreePipei[62 + index] = m_ppvalue;

				if(m_ppvalue  > 0)
				{
					DJSignalBit[index] = 0;
				}
				else 
				{
					DJSignalBit[index] = 1;
				} 

			}
			else
			{

               DJSignalBit[31] = 0;
			
			}
			
			str.Format("DJSignalBit[%d] = %d [%.3f]",index,DJSignalBit[index],m_ppvalue);
			WriteToLog(str);
						
			if((index + 1) % 8 == 0)
			{
				
				m_result = DJSignalBit[index - 7] * 128 + DJSignalBit[index - 6] * 64 + DJSignalBit[index - 5]* 32 + DJSignalBit[index - 4] * 16  + DJSignalBit[index - 3] * 8 + DJSignalBit[index - 2] * 4 + DJSignalBit[index - 1] * 2  + DJSignalBit[index];

				if(m_result < 16)
				{
					signstr.Format(" 0x0%0x  ",m_result);
				}
				else
				{
					signstr.Format(" 0x%0x  ",m_result);
				}	
				
				WriteToLog("\r\nʮ������Ϊ:"+ signstr + "\r\n");

			    m_ReceiveStr = m_ReceiveStr + signstr;
				
			}
			
		}

		WriteToLog(" ���         ԭƥ��ֵ         �ط�ƥ��ֵ           ����ƥ��ֵ");

		for(index = 0; index < 31 ;index ++)
		{

			str.Format(" %2d      %12.3f      %12.3f         %12.3f ",index,m_ThreePipei[2*index],m_ThreePipei[2*index + 1],m_ThreePipei[62 + index]);
            WriteToLog(str);
		}
		
		WriteToLog("\r\n");

		//����
		for( i = 0; i <  31; i ++)
		{
			//31,21,2
			TempSignalBit[i]        = DJSignalBit[i];
			
			if( i < 10 )
			{
				TempSignalBit[i]    = DJSignalBit[9 - i];
			}
			else
			{
				TempSignalBit[i]    = DJSignalBit[30 - i + 10];
			}

		}
	
		
		//�������
		m_CollectNos    =   10;
			
		//31212����
		if(DecodeBCH31212(TempSignalBit))
		{
			   
			signstr.Format(" ����%d��ƥֵ>0.65��%d�ݸ�",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
			
			
			//��һ�¾���λ,����о����λ
			if(m_CollectNos > 0)
			{
				
				m_checkplace  =    FALSE;
				
				//��λ�㷨,�����λ�Ƿ����ڲ�ͬ��λ����
				for(int i = 0; i < m_CollectNos;i ++)
				{
					
					m_checkplace  = FALSE;
					
					//�м�����
					for(int j = 0; j < m_sums; j++)
					{
						
						if(m_PlaceDifferent[j] == m_CollectPlace[i])
						{
							m_checkplace = TRUE;
							break;
						}
						
					}

					
					if(!m_checkplace)
					{
						signstr.Format("  ��[%d]",m_CollectPlace[i]);
						m_ReceiveStr = m_ReceiveStr + signstr;
					}
					
				}
				
			}
			

			//��10-30Ϊ����λ��->�߷�չ���ص���Ϊ16����
			//����  0��30A
			//��ѹ  0��300V
		    //�͵�ɹ�0x33
			//������ 21ȫΪ1(111111111111111111111)�������������λΪ********************0
            //פ��û��פ����  (000000000000000000001)  20��0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;

			signstr.TrimLeft();
			signstr.TrimRight();
						
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}
		
			//16����
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(TempSignalBit[10 + i]*pow(2,i));
			}
			
			//��������ѹΪ
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{



				
			}
   	
		
		}
		else
		{
			
			signstr.Format("  �۾�������ƥֵ>0.65�У�%d�ݸ�",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
		}
		
		////////////////////////////////////////////////////////
		CString              Strtemp1,Strtemp2,Strtemp3,Strtemp4,Strtemp5;
		Strtemp1             =  Strtemp2   =   Strtemp3= Strtemp4 = Strtemp5     = "";
		BYTE     m_GetNumber1,m_GetNumber2,m_GetNumber3,m_GetNumber4,m_GetNumber5;
		m_GetNumber1 = m_GetNumber2 = m_GetNumber3  = m_GetNumber4 = m_GetNumber5 = 0;
	
        //������
		BYTE     JM[31]; 

		//�ֿ�ʼ��������
		for( i = 0; i <  31; i ++)
		{
			if( i < 10 )
			{
				JM[i]    = TempSignalBit[9 - i];
			}
			else
			{
				JM[i]    = TempSignalBit[30 - i + 10];
			}
			
		}
		
		//Strtemp1ǰ31����,Strtemp2��31����,Strtemp3Ϊ������31����
		Strtemp1  = "��һ��31����:";
		Strtemp2  = "�ط���31����:";
		Strtemp3  = "���Ӻ�31����:";				
		Strtemp4  = "�����31����:";

		//��ԭʼ���ݶԱ�
		for( i = 0; i <  31; i ++)
		{
			
			//��һ��31����
			if(SignalBit[2*i] == 0)
			{
				Strtemp1 = Strtemp1 + " 0";
			}
			else
			{
				Strtemp1 = Strtemp1 + " 1";
			}
			
			//�ط���31����
			if(SignalBit[2*i+1] == 0)
			{
				Strtemp2 = Strtemp2 + " 0";
			}
			else
			{
				Strtemp2 = Strtemp2 + " 1";
			}
			
			//���Ӻ�31����
			if(DJSignalBit[i] == 0)
			{
				Strtemp3 = Strtemp3 + " 0";
			}
			else
			{
				Strtemp3 = Strtemp3 + " 1";
			}
			
			//�����31����
			if( JM[i] == 0)
			{
				Strtemp4 = Strtemp4 + " 0";
			}
			else
			{
				Strtemp4 = Strtemp4 + " 1";
			}
			
			
			//�Ա����ν��յ�������
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{					
				m_GetNumber1 ++;
			}	
			
			//�Աȵ��Ӻ�͵�һ�ε�����	
			if(SignalBit[2*i]    != DJSignalBit[i])
			{
				m_GetNumber2++;
			}
			
			//�Աȵ��Ӻ�͵ڶ��ε�����	
			if(SignalBit[2*i + 1] != DJSignalBit[i])
			{
				m_GetNumber3++;
			}
			
			//�ԱȾ����͵�һ�ε�����	
			if(SignalBit[2*i]  != JM[i])
			{
				m_GetNumber4++;
			}
			
			//�ԱȾ����͵ڶ��ε�����	
			if(SignalBit[2*i + 1] != JM[i])
			{
				m_GetNumber5++;
			}
			
		}
		
		if(dataValue >= 0)
		{
			Strtemp5.Format("�ԱȽ�����£�\r\n���ν��յ������ݲ�ͬ����:%d\r\n���Ӻ�͵�һ�β�ͬ����:%d,���Ӻ�͵ڶ��β�ͬ����:%d\r\n�����͵�һ�β�ͬ����:%d,�����͵ڶ��β�ͬ����:%d,�������:%d",m_GetNumber1,m_GetNumber2,m_GetNumber3,m_GetNumber4,m_GetNumber5,m_CollectNos);
			WriteToLog(Strtemp1+ "\r\n" + Strtemp2 + "\r\n" + Strtemp3 + "\r\n" + Strtemp4 + "\r\n" + Strtemp5 + "\r\n" );
		}
		else
		{
			Strtemp5.Format("�ԱȽ�����£�\r\n���ν��յ������ݲ�ͬ����:%d\r\n���Ӻ�͵�һ�β�ͬ����:%d,���Ӻ�͵ڶ��β�ͬ����:%d\r\n",m_GetNumber1,m_GetNumber2,m_GetNumber3);
			WriteToLog(Strtemp1+ "\r\n" + Strtemp2 + "\r\n" + Strtemp3 + "\r\n" + Strtemp5 + "\r\n" );
		}

		
		////////////////////////////////////////////////////////
	
		//31212����
		if(dataValue >= 0)
		{
			//��ȷ�Ļ�
			Beep(5000,400); 
			return dataValue/10;
		}

	}
	else if(m_protocol == 61)
	{

		//61Э��,����
		for(int i = 0; i <  45; i ++)
		{
			
			//45,27,3
			if( i < 18 )
			{
				TempSignalBit[i]    = SignalBit[17 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[44 - i + 18];
			}
			
		}
		
		
		//�������
		m_CollectNos    =   10;
		
		//45273����
		if(DecodeBCH45273(TempSignalBit))
		{
			
			signstr.Format(" ����%d��ƥֵ>0.65��%d�ݸ�",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
				
			//61Э��,����ԭ������
			for(int i = 0; i <  45; i ++)
			{
				
				//45,27,3
				if( i < 18 )
				{
					SignalBit[i]    =  TempSignalBit[17 - i];
				}
				else
				{
					SignalBit[i]    =  TempSignalBit[44 - i + 18];
				}
				
			}

			//16����
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			}		
						
			m_sums     =      0;
			
			//7λһ�����
			for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			{
				
				//����λ����ֽ�,7λһ����� 
				for( i = 0;i < 7; i ++)
				{  	
					
					m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					
				}
				
			}
			
			//������Ƿ���ͬ
			if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			{
				
				//45273����
				if(dataValue >= 0)
				{
					//��ȷ�Ļ�
					Beep(5000,400); 
					return dataValue/10;
				}
				
			}
			else
			{
				//����Ͳ���
				str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				WriteToLog(str);
				return       -1;
			}
			
			//��10-30Ϊ����λ��->�߷�չ���ص���Ϊ16����
			//����  0��30A
			//��ѹ  0��300V
			//�͵�ɹ�0x33
			//������ 21ȫΪ1(111111111111111111111)�������������λΪ********************0
            //פ��û��פ����  (000000000000000000001)  20��0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;
			
			signstr.TrimLeft();
			signstr.TrimRight();
			
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}
			
			//��������ѹΪ
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{
				
				
				
				
			}
			
		}
		else
		{
			
			signstr.Format("  �۾�������ƥֵ>0.65�У�%d�ݸ�",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
			return -1;
		}
		
		
		
	}
	else if(m_protocol == 62)
	{	
		//62Э��,��ͬ������
		m_sums    =     0;
		dataValue =    -1;
		
		/*********˳������������22Э��Ļ�*/
		for(short i = 0; i <  45; i ++)
		{

			//�Ա����ν��յ�������
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{

				//��ס��ͬ��λ��
				if(m_sums <= m_derrors)
				{
					m_PlaceDifferent[m_sums] = i;
				}
							
				m_sums ++;
			}
			
		}
		
		str.Format("  ��λ���%d��",m_sums);
		WriteToLog(str);

		m_ReceiveStr    =             str;

		//���ݵ����ٴ���,����10�Ⱥ�5�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
		BYTE              DJSignalBit[48];

		for(index = 0; index < 48 ;index ++)
		{

			if(index < 45)
			{
				
				//��������㷨���,3-1,4-2
				for(int i = 0;i < 512;i ++)   
				{ 
					//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
					Diffs[i]        = DataBuf[(2*index * 4 + 2) * 512 + i + 1024] - DataBuf[ 2*index * 4 *  512 + i  + 1024];
					Diffs[512 + i]  = DataBuf[(2*index * 4 + 3) * 512 + i + 1024] - DataBuf[(2*index * 4 + 1) * 512 + i + 1024];
					
					//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
					Diffn[i]        = DataBuf[((2*index + 1) * 4 + 2) * 512 + i + 1024] - DataBuf[(2*index + 1) * 4      *  512 + i  + 1024];
					Diffn[512 + i]  = DataBuf[((2*index + 1) * 4 + 3) * 512 + i + 1024] - DataBuf[((2*index +1) * 4 + 1) *  512 + i  + 1024];
				}
				
				//��������
				for( i = 0;i < 256;i ++)   
				{ 
					//0��31���ӣ�1��32����
					Diffs[i]   = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,m_pipeiplace);
				
				//��ƥ��ϵͳ
		        m_ThreePipei[90 + index] = m_ppvalue;

				if(m_ppvalue  > 0)
				{
					DJSignalBit[index] = 0;
				}
				else 
				{
					DJSignalBit[index] = 1;
				} 
				
				str.Format("DJSignalBit[%d] = %d [%.3f]",index,DJSignalBit[index],m_ppvalue);
			    WriteToLog(str);

			}
			else
			{

               DJSignalBit[index] = 0;
			
			}
			
		
						
			if((index + 1) % 8 == 0)
			{
				
				m_result = DJSignalBit[index - 7] * 128 + DJSignalBit[index - 6] * 64 + DJSignalBit[index - 5]* 32 + DJSignalBit[index - 4] * 16  + DJSignalBit[index - 3] * 8 + DJSignalBit[index - 2] * 4 + DJSignalBit[index - 1] * 2  + DJSignalBit[index];

				if(m_result < 16)
				{
					signstr.Format(" 0x0%0x  ",m_result);
				}
				else
				{
					signstr.Format(" 0x%0x  ",m_result);
				}
				
				if((index + 1)/8 == 6)
				{

					if((m_result>>3) < 16)
					{
						signstr.Format(" 0x0%0x  ",(m_result>>3));
					}
					else
					{
						signstr.Format(" 0x%0x  ",(m_result>>3));
					}
					
				}
				
				WriteToLog("\r\nʮ������Ϊ:"+ signstr + "\r\n");

			    m_ReceiveStr = m_ReceiveStr + signstr;
				
			}
			
		}

		WriteToLog(" ���         ԭƥ��ֵ         �ط�ƥ��ֵ           ����ƥ��ֵ");

		for(index = 0; index < 45 ;index ++)
		{

			str.Format(" %2d      %12.3f      %12.3f         %12.3f ",index,m_ThreePipei[2*index],m_ThreePipei[2*index + 1],m_ThreePipei[90 + index]);
            WriteToLog(str);
		}
		
		WriteToLog("\r\n");

		//����
		for( i = 0; i <  45; i ++)
		{
			//45,27,3
			TempSignalBit[i]        = DJSignalBit[i];
			
			if( i < 18 )
			{
				TempSignalBit[i]    = DJSignalBit[17 - i];
			}
			else
			{
				TempSignalBit[i]    = DJSignalBit[44 - i + 18];
			}

		}
	
		
		//�������
		m_CollectNos    =   10;
			
		//45273����
		if(DecodeBCH45273(TempSignalBit))
		{
			   
			signstr.Format(" ����%d��ƥֵ>0.65��%d�ݸ�",m_CollectNos,m_GetOverRecords);
			
			m_ReceiveStr = m_ReceiveStr + signstr;
			
			//62Э��,����ԭ������
			for(int i = 0; i <  45; i ++)
			{
				
				//45,27,3
				if( i < 18 )
				{
					SignalBit[i]    =  TempSignalBit[17 - i];
				}
				else
				{
					SignalBit[i]    =  TempSignalBit[44 - i + 18];
				}
				
			}

			//16����
			dataValue = 0.00;
			
			for( i = 0; i < 21; i++)
			{
				dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			}		
						
			m_sums     =      0;
			
			//7λһ�����
			for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			{
				
				//����λ����ֽ�,7λһ����� 
				for( i = 0;i < 7; i ++)
				{  	
					
					m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					
				}
				
			}
			
			//������Ƿ���ͬ
			if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			{
				
				//45273����
				if(dataValue >= 0)
				{
					//��ȷ�Ļ�
					Beep(5000,400); 
					return dataValue/10;
				}
				
			}
			else
			{
				//����Ͳ���
				str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				WriteToLog(str);
				return       -1;
			}

			//��10-30Ϊ����λ��->�߷�չ���ص���Ϊ16����
			//����  0��30A
			//��ѹ  0��300V
		    //�͵�ɹ�0x33
			//������ 21ȫΪ1(111111111111111111111)�������������λΪ********************0
            //פ��û��פ����  (000000000000000000001)  20��0 + 1
			
			CWnd* pt    =    GetDlgItem(IDC_ORDER);
			pt->GetWindowText(signstr);	
			BYTE    m_order;

			signstr.TrimLeft();
			signstr.TrimRight();
						
			if(signstr.GetLength() > 1)
			{
				m_order = GetHexValue(signstr.GetAt(0))*16 + GetHexValue(signstr.GetAt(1));
			}
			else
			{
				m_order = GetHexValue(signstr.GetAt(0));
			}

			//��������ѹΪ
			if((m_order >= 0x62 && m_order<= 0x6f) || m_order==0x04)
			{



				
			}
		
		}
		else
		{
			
			signstr.Format("  �۾�������ƥֵ>0.65�У�%d�ݸ�",m_GetOverRecords);
			m_ReceiveStr = m_ReceiveStr + signstr;
			return -1;
		}
    
    }
	else
	{
		
		//˳�����
		for(int i = 0; i <  63; i ++)
		{
			
			if( i < 24)
			{
				TempSignalBit[i]    = SignalBit[23 - i];
				TempSignalBitbak[i] = SignalBit[23 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[62 - i + 24];
				TempSignalBitbak[i] = SignalBit[62 - i + 24];
			}
			
		}
		
		long time1 = GetTickCount();
		signstr.Format("��ƥ������ʱ�䣺%6d��",time1 - time0);
		WriteToLog(signstr);
		
		
		//���յ���������
		if(DecodeBCH63394(TempSignalBit))//����ԵĻ�
		{
			
			dataValue =    0;
			
			for( i = 0; i < 39; i++)
			{
				//�����ֵ�����
				Data[i] = TempSignalBit[62 - i];
			}	
			
			//�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û�����ã� "������1"
			//�ص�ֵΪAAAAAA.AA,��չģ��ı�û�����ã�           "������2"
			m_sums     =      0;
			
			//����λ����ֽ� 
			for( i = 0;i < 8; i ++)
			{  	
				//�������
				Signal[i] = Data[i * 4] * 8 + Data[i * 4 + 1] * 4 + Data[i * 4 + 2] * 2 + Data[i * 4 + 3] ;
				dataValue = dataValue + Signal[i] * 100000.0/pow(10,i);
				
				//��������
				if((i + 1)%2 != 0)
				{
					m_sums  = m_sums  + Signal[i]*16;
				}
				else
				{		
					m_sums  = m_sums  + Signal[i];
				}
				
			}
			
			if(m_sums%128 != Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			{
				CString                      str;
				str.Format("%0x,%0x",m_sums%128,Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38]);
				WriteToLog(str + "У��Ͳ��ԣ�");
			}
			
			//�½���
			if( Signal[0] == 0x0f && Signal[1] == 0x0e && Signal[2] == 0x0f && Signal[3] == 0x0e && Signal[4] == 0x0f && Signal[5] == 0x0e && Signal[6] == 0x0f && Signal[7] == 0x0e)
			{
				Beep(5000,400); 
				//������1
				WriteToLog("������1");
			}
			else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a)
			{
				Beep(5000,400); 
				//������2
				WriteToLog("������2");
			}
			else if( Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			{
				//��פ��ʱģ��û���յ���פ������ص���
				Beep(5000,400); 
				//ģ��û���յ���פ������
				WriteToLog("ģ��û���յ���פ������");
				
			}	
			else if(Signal[0] > 9 || Signal[1] > 9 || Signal[2] > 9 || Signal[3] > 9 || Signal[4] > 9 || Signal[5] > 9 || Signal[6] > 9 || Signal[7] > 9)
			{
				dataValue =   -1;
			}
			
			dataValueValue =    dataValue;
		}

	}
	
	if(dataValueValue > -1)
	{
		//��ȷ�Ļ�
		Beep(5000,400); 
	}

	return dataValueValue;
}

void CTTTView::OnRadio3() 
{

	for(int i = 0; i < 256; i ++)
	{
        SourceArrays[i] = Correlation_Table05[i];
	}
	
	//��������
	for( i = 0;i < 256;i ++)   
	{ 
		m_ppwave[i]  = SourceArrays[i];
	}
	
	OnButtonUpdate();

	CWnd* pt = GetDlgItem(IDC_STATICFILE2);
	pt->SetWindowText("ƥ��Ƕȣ�5��");
	
}


void CTTTView::OnCheck9() 
{
	UpdateData();
}

void CTTTView::OnTestdata() 
{
	CTestDlg DLG;
	DLG.DoModal();
}

void CTTTView::OnChangeStartpoint() 
{
//	UpdateData();
//	OnButtonUpdate();
}

void CTTTView::OnChangeWavepoints() 
{
	//g_Extend = DISPWINWIDTH/(float)PointsNum;
}

void CTTTView::OnCheck11() 
{
	UpdateData();
    
	if(m_quancai)
	{
		m_Spinstart.SetPos(1860);
		m_SpinAverage.SetPos(999);
	}
	else
	{
		m_Spinstart.SetPos(1024);
		m_SpinAverage.SetPos(512);
	}
	
	m_startpoint  =  m_Spinstart.GetPos();
	m_wavepoints  =  m_SpinAverage.GetPos();

	OnRadio1();
	
	if(m_wavepoints/2 > 256)
	{
		
		for(int  i = m_wavepoints/2 ; i >= 0; i --)   
		{ 
			if((255 - (m_wavepoints/2 - i)) >= 0)
			{
				m_ppwave[i]  = m_ppwave[255 - (m_wavepoints/2 - i)];
			}
			else
			{
				m_ppwave[i]  =  0;
			}
			
		}
		
	}

	UpdateData(FALSE);
    OnButtonUpdate();
	
}

void CTTTView::OnOutofmemorySpinstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//AfxMessageBox("error!");
	*pResult = 0;
}

void CTTTView::OnDeltaposSpinstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
    UpdateData();

	OnButtonUpdate();
	*pResult = 0;
}

void CTTTView::OnDeltaposSpinaverage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	UpdateData();

	OnRadio1();

	if(m_wavepoints/2 > 256)
	{
		
		for(int  i = m_wavepoints/2 ; i >= 0; i --)   
		{ 
		
			if((255 - (m_wavepoints/2 - i)) >= 0)
			{
				m_ppwave[i]  = m_ppwave[255 - (m_wavepoints/2 - i)];
			}
			else
			{
				m_ppwave[i]  =  0;
				
			}

		}
		
	}

	OnButtonUpdate();	
	
	*pResult = 0;
}


//�ҹ����
void CTTTView::OnFindzero() 
{
	
	short   m_BeginValue  =    10;//��10Ϊ����
	short   m_RangeValue  =    30;//��50��������
	short   m_rumbers     =     0;//
	CString                   str;
	BOOL    m_ready      =  FALSE;
    
	str.Format("DataLen = %d",DataLen);
	WriteToLog(str);

	for(int i = 0 ; i < DataLen - m_RangeValue; i ++)
	{
         
		
		if( DataBuf[i] <= m_BeginValue && DataBuf[i] >= 0)
		{
            
			//����С��
    		m_rumbers    =          0;	
			
			//�Һ�10����
			for(int j = i + 1; j < i + 11; j ++)
			{ 
				//����0���ǰһ����Ҫ��
				if(DataBuf[j] > DataBuf[i] || DataBuf[j] >= 0 )
				{		
					m_rumbers ++;
				}
				
			}	

			//���С��1��
			if(m_rumbers  < 1)
			{
				m_ready      =       TRUE;
				m_BeginValue = DataBuf[i];
			}
		
		}

		 //���׼������
		 if(m_ready)
		 {
		
			 m_rumbers = 0;
			 
			 for(int j = i + 1 ; j < i + m_RangeValue; j ++)
			 {
				 //������
				 if(DataBuf[j] < m_BeginValue)
				 {
					 m_rumbers ++;
				 }
				 
			 }
			 
			 //��80���ĵ�С����Ļ�
			 if(m_rumbers*1.000/m_RangeValue > 0.8)
			 {
				 str.Format("�����λ��Ϊ%d",i + 1);
				 WriteToLog(str);
				 i =  i + m_RangeValue;
			 }

			 m_ready      = FALSE;
			 m_BeginValue =    10;
		 }
	
	}

	MessageBox("����������ϣ�"," ",MB_OK);


	/*
	UINT CntPoint = 0,CntCycle =     0;
	UINT temp,CurZeroPoint     =     0;
	BOOL bReady                = FALSE;
	
    do{
       	temp = DataBuf[CntPoint++];

		if(temp > m_maxDecimalVal/2 - 1)
		{ 
			if(CntPoint > CurZeroPoint + 100)
			{
				bReady = TRUE; 
			}
		}
		else
		{			
			if(bReady)
			{
				
				if(DataBuf[CntPoint+100] < m_maxDecimalVal/2)
				{  
					CurZeroPoint= CntPoint;
					bReady      = FALSE; 
					CntCycle++;
				}

			}
			
		}
		
	}while(CntCycle < WaveNum + 1);
	
	return CntPoint-1;
	*/
}

//��1�Ĳ�������һ��,��0�Ĳ�������һ��
void CTTTView::AllWaveAdd()
{	
    short               Diffs[3000];
	double m_ppvalue       =      0;
	CString                     str;

	for(int i = 0; i < 10000; i++)
	{
		m_ppAllWave[i] = 0;
	}
	
	//���������λ
	for(int index = 0; index < 63 ;index ++)
	{
		
		//��������㷨���,3-1,4-2
		for(int i = 0;i < m_wavepoints;i ++)   
		{ 
			//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
			Diffs[i]                 = DataBuf[(index * 4 + 2) * m_wavepoints + i + m_startpoint] - DataBuf[index * 4 *  m_wavepoints + i  + m_startpoint];
			Diffs[m_wavepoints + i]  = DataBuf[(index * 4 + 3) * m_wavepoints + i + m_startpoint] - DataBuf[(index * 4 + 1) * m_wavepoints + i + m_startpoint];
		}
		
		//��������
		for( i = 0;i < m_wavepoints/2;i ++)   
		{ 
			//ƽ��ֵ
			Diffs[i]  = Diffs[i] + Diffs[m_wavepoints/2+i] + Diffs[m_wavepoints+i] + Diffs[3*m_wavepoints/2+i];
		}
	
		//ƥ��ֵ
		m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
		
		//pr[n]���������ʵ��
		//pi[n]����������鲿
		//n��k��������n=2^k
		//fr[n]���������ʵ��
		//fi[n]����������鲿
		//l����0 FFT��1 IFFT
		//il����0 �����ʵ��/�鲿��1 �����ģ/����		  
		//kkfft(double pr[],double pi[],int n,int k,double fr[],double fi[],int l,int il);
		
		// ��ڲ����� 
		// l: l = 0, ����Ҷ�任; l = 1, �渵��Ҷ�任
		// il: il = 0,�����㸵��Ҷ�任����任ģ�ͷ��ǣ�il = 1,����ģ�ͷ���
		// n: ����ĵ�����Ϊż����һ��Ϊ32��64��128��...,1024��
		// k: ����n=2^k(k>0),ʵ����k��n���������ݿ��Էֽ�Ϊż���ݺ�����ݵĴ���
		// pr[]: l=0ʱ�����N��������ݵ�ʵ��
		// l=1ʱ, ��Ÿ���Ҷ�任��N��ʵ��
		// pi[]: l=0ʱ�����N��������ݵ��鲿 
		// l=1ʱ, ��Ÿ���Ҷ�任��N���鲿
	
		// ���ڲ�����
		// fr[]: l=0, ���ظ���Ҷ�任��ʵ��
		// l=1, �����渵��Ҷ�任��ʵ��
		// fi[]: l=0, ���ظ���Ҷ�任���鲿

		// l=1, �����渵��Ҷ�任���鲿
		// pr[]: il = 1,i = 0 ʱ�����ظ���Ҷ�任��ģ
		// il = 1,i = 1 ʱ�������渵��Ҷ�任��ģ
		// pi[]: il = 1,i = 0 ʱ�����ظ���Ҷ�任�ķ���
		// il = 1,i = 1 ʱ�������渵��Ҷ�任�ķ���


		/*
		if(m_wavepoints == 512)
		{
			double pr[256],pi[256],fr[256],fi[256];
			
			for(i = 0; i <  256; i ++)
			{
				
				
				if( i < 256 - m_iBandPassPoints)
				{
					pr[i] =  0;
				}
				else
				{
					pr[i] = double(Diffs[i]);
				}

				pi[i] = 0;
				fr[i] = 0;
				fi[i] = 0;
			}

		    kkfft(pr,pi,256,8,fr,fi,0,1);
			
			for(i = 0; i <  256; i ++)
			{
				str.Format("pr[%3d]=%13.3f,pi[%3d]=%13.3f,fr[%3d]=%13.3f,fi[%3d]=%13.3f",i,pr[i],i,pi[i],i,fr[i],i,fi[i]);
				//str.Format("pr[%3d]=%13.3f, pi[%3d]=%13.3f",i,fr[i],i,fr[i]);
				//str.Format("fr[%3d]=%13.3f, fi[%3d]=%13.3f",i,fr[i],i,fi[i]);
				WriteToLog(str);
			}

		}
		*/

		for( i = 0; i < m_wavepoints/2; i ++)
		{
			if(m_ppvalue > 0)
			{
				m_ppAllWave[i] = m_ppAllWave[i] + Diffs[i];
			}
			else
			{
				m_ppAllWave[m_wavepoints/2 + i] = m_ppAllWave[m_wavepoints/2 + i] + Diffs[i];
			}
			
		}

		
	}
	
	/*
	//���Ӳ�����
	for( i = 0; i < m_wavepoints/2; i ++)
	{
		//���ϵĵ��Ӳ�
		Diffs[i] = m_ppAllWave[i];
	}
	
	//ƥ��ֵ
	m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
    str.Format("���ϵĵ��Ӳ�ƥ��ֵ:%.2f",m_ppvalue);
	WriteToLog(str);

	
	for( i = 0; i < m_wavepoints/2; i ++)
	{
		//���ϵĵ��Ӳ�
		Diffs[i] = m_ppAllWave[m_wavepoints/2 + i];
	}
	
	//ƥ��ֵ
	m_ppvalue   = CorrelationCheck(SourceArrays,Diffs,m_wavepoints/2,0);
    str.Format("���µĵ��Ӳ�ƥ��ֵ:%.2f",m_ppvalue);
    WriteToLog(str);


	CString   str;

	//���Ӳ���
	for( i = 0; i < m_wavepoints/2; i ++)
	{

		if(m_ppAllWave[i] > 0)
		{
            str.Format("%5d",m_ppAllWave[i]);
		}
		else
		{
			str.Format("%5d",0);
		}

	    WriteToLog(str);
	}
	*/

}




void CTTTView::OnAlladd() 
{
	UpdateData(TRUE);

	/*
	//���в�����
	if(m_AllAdd)
	{
		//��1�Ĳ�������һ��,��0�Ĳ�������һ��
		AllWaveAdd();
	}
	*/
	
	OnButtonUpdate();
	
}

void CTTTView::OnChangeAlltimes() 
{
	UpdateData();
	OnButtonUpdate();
	
}

void CTTTView::OnInitialize() 
{
	UpdateData(TRUE);
    CString    ComStr;
	int k      =    0;

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


	//����
	//��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
	//���ø��ֲ���m_comboport.GetCurSel()
	OptionClick(k-1,m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
	MessageBox("���ڳ�ʼ���ɹ���"," ",MB_OK|MB_ICONINFORMATION);
}


/***************************************************************
��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
����λ 0-��У��,1����У��,2��żУ��
����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
ֹͣλ 0-1     ,1-1.5    ,2-2
//�����Ʒ�ʽ����
**************************************************************/
void CTTTView::OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex)
{
    m_StatusStr = "";
	
	CString SpeedIndexstr;
    CString CheckIndexstr;
    CString  DataIndexstr;
	CString  StopIndexstr;
	CString  ParameterStr;
	
	//������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000
	switch(SpeedIndex)
	{
	case 0:
		{
			SpeedIndexstr = "600";
			break;
		}
	case 1:
		{
			SpeedIndexstr = "1200";
			break;
		}
	case 2:
		{
			SpeedIndexstr = "2400";
			break;
		}
	case 3:
		{
			SpeedIndexstr = "4800";
			break;
		}
	case 4:
		{
			SpeedIndexstr = "9600";
			break;
		}
	case 5:
		{
			SpeedIndexstr = "14400";
			break;
		}
	case 6:
		{
			SpeedIndexstr = "19200";
			break;
		}
	case 7:
		{
			SpeedIndexstr = "28800";
			break;
		}
	case 8:
		{
			SpeedIndexstr = "38400";
			break;
		}	
	case 9:
		{
			SpeedIndexstr = "56000";
			break;
		}
	case 10:
		{
			SpeedIndexstr = "128000";
			break;
		}
	case 11:
		{
			SpeedIndexstr = "256000";
			break;
		}	
		
	}
	
	//����λ 0-��У��,1����У��,2��żУ��
	switch(CheckIndex)
	{
	case 0:
		{
			//0-��У��
			CheckIndexstr = "N";
			break;
		}
	case 1:
		{
			//1����У��
			CheckIndexstr = "O";
			break;
		}
	case 2:
		{
			//2��żУ��
			CheckIndexstr = "E";
			break;
		}
	}
	
	//����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
	switch(DataIndex)
	{
	case 0:
		{
			DataIndexstr = "4";
			break;
		}
	case 1:
		{
			DataIndexstr = "5";
			break;
		}
	case 2:
		{
			DataIndexstr = "6";
			break;
		}
	case 3:
		{
			DataIndexstr = "7";
			break;
		}
	case 4:
		{
			DataIndexstr = "8";
			break;
		}
	}
    
	//StopIndexstr;ֹͣλ 0-1     ,1-1.5    ,2-2
	switch(StopIndex)
	{
	case 0:
		{
			StopIndexstr = "1";
			break;
		}
	case 1:
		{
			StopIndexstr = "1.5";//"1.5",ֻ������λΪ5ʱ��;
			break;
		}
	case 2:
		{
			StopIndexstr = "2";
			break;
		}
		
	}
	
	if(m_Com.GetPortOpen()) //�򿪴���   
	{
		m_Com.SetPortOpen(FALSE);
	}
	

	m_Com.SetCommPort(ComIndex + 1); //ѡ��COM,��0��ʼ
    m_Com.SetInBufferSize(1024);     //�������뻺�����Ĵ�С��Bytes
	m_Com.SetOutBufferSize(512);     //��������������Ĵ�С��Bytes
	
    //�򿪶˿�
	m_Com.SetPortOpen(TRUE);

	m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��

	m_Com.SetInputMode(1);//0 �ı���ʽ 1��������ʽ

    //���ò����� ������λ ������λ ��ֹͣλ	
	ParameterStr.Format("%s,%s,%s,%s",SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);
    
	m_Com.SetSettings(ParameterStr);//"600,n,8,1"
	m_Com.SetRThreshold(1);//ÿ����1���ַ��ʹ���1�ν����¼�
	m_Com.SetInputLen(0);  //ÿ�ζ�ȡһ���ַ�,��������ʽ
	m_Com.GetInput();      //���ԭ�е�����
		
	ParameterStr.Format("���ڳ�ʼ���ɹ���COM%d,%s,%s,%s,%s��",ComIndex+1,SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);
    m_StatusStr = ParameterStr;

	status(ParameterStr);
	
}


//����м����˿�����
void CTTTView::GetComPorts()
{
	HANDLE				m_hComm;
    CString             ComStr;
	m_comboport.ResetContent();

	for(int i = 0; i < 10; i ++)
	{
		
		ComStr.Format("COM%d",i + 1);
		
		// get a handle to the port
		m_hComm = CreateFile(ComStr,		// communication port string (COMX)
			GENERIC_READ | GENERIC_WRITE,	// read/write types
			0,								// comm devices must be opened with exclusive access
			NULL,							// no security attributes
			OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
			FILE_FLAG_OVERLAPPED,			// Async I/O
			0);							    // template must be 0 for comm devices
		
		if (m_hComm != INVALID_HANDLE_VALUE)
		{
			m_comboport.AddString(ComStr);
			CloseHandle(m_hComm);
		}
		
	}

	if(m_comboport.GetCount() > 0)
	{
		m_comboport.SetCurSel(0);
		m_combobit.SetCurSel(4);
		m_comcheck.SetCurSel(0);
		m_comdata.SetCurSel(4);
		m_comstop.SetCurSel(0);	
		
		//���ø��ֲ���m_comboport.GetCurSel()
	    OptionClick(m_comboport.GetCurSel(),m_combobit.GetCurSel(),m_comcheck.GetCurSel(),m_comdata.GetCurSel(),m_comstop.GetCurSel());
	
	}
	
}


//״̬������ʾ��Ϣ
void CTTTView::status(CString strname)
{
	CStatusBar*          pStatus;
	pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	
	if (pStatus)
	{
		pStatus->SetPaneText(0,strname);
	}
	
}

void CTTTView::OnComset() 
{
	m_TestPhase = FALSE;

	UpdateData();
	
	if(m_module > 1638415)
	{
		m_module = 1638301;
		UpdateData(FALSE);
	}
	
	GetDlgItem(IDC_STATIC50)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC51)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC52)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC53)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC54)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC55)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC56)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBOPORT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBOBIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECKCOMBOX)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATACOMBO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STOPCOMBO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_INITIALIZE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DELAY)->ShowWindow(SW_SHOW);	

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE); 
	GetDlgItem(IDC_READLINE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHIFTLEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTLEFT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SHIFTRIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ASHIFTRIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOAD)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_ANGLE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_SENDALLONE)->EnableWindow(FALSE); 
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);

	GetDlgItem(IDC_REAL_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_REAL_START)->SetWindowText("����");
	GetDlgItem(IDC_REALSTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
    GetDlgItem(IDC_SETTIMER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECODE)->EnableWindow(FALSE);

	GetDlgItem(IDC_REAL_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_REAL_RECORD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPREC)->EnableWindow(FALSE);
	GetDlgItem(IDC_READLINE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICFILE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATICFILE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANGLE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC57)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_ORDER)->SetWindowText("03");

	OnSelchangeProtocols(); 
}

//�򴮿ڷ�������
void CTTTView::SendByteArrayToCom()
{
	//��������ʱ��
	if(m_Com.GetPortOpen())
	{
		CString  str,str1;
		str      =     "";

		for(int i = 0; i < SendByteArray.GetSize(); i ++)
		{	
			
			
			if(SendByteArray[i] > 15)
			{
				str1.Format(" 0x%0x ",SendByteArray[i]);
			}
			else
			{
				str1.Format(" 0x0%0x ",SendByteArray[i]);
			}

			/*
			if(i == 0)
			{
				//AfxMessageBox(str);
				str1.TrimLeft();
				str1.TrimRight();
				str = str + str1;
			}
			else
			{*/
				
				if(i == 4 || i == 13)
				{
					str = str + str1 + "   ";
				}
				else
				{
					str = str + str1;
				}
		//	}
		
		}

		CWnd* pt = GetDlgItem(IDC_SENDORDER);
		pt->SetWindowText(str);
		
		UpdateData(TRUE);
        UpdateData(FALSE);

		m_Com.GetInput();
		m_Com.SetOutput(COleVariant(SendByteArray));
		m_Com.SetOutBufferCount(0);
		//��ʱm_delay,������ʱ��
		SetTimer(1,m_delay,NULL);
	}
	else
	{
		MessageBox("���ڴ򿪴���","����",MB_OK|MB_ICONWARNING);
	}

}

//��鴮���յ�������
void CTTTView::CheckComData()
{
	//�����Ʒ�ʽ
	COleVariant            varInput; 
	varInput.parray         =  NULL;
	long                     ix,l,u;
	BYTE                   TempByte;
	CString                     str;
	
	//ȡֵ����
	varInput     = m_Com.GetInput();
	m_ReceiveStr =               "";
	
	if(varInput.parray != NULL) 
	{ 
	
		m_ReceiveStr = "";
		//�õ���ȫ�����Ͻ�
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//�õ���ȫ�����½�
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//�õ�����������ֵ
		for(ix = l; ix <= u; ix ++)
		{
			SafeArrayGetElement(varInput.parray,&ix,&TempByte);
			str.Format("0x%0x ",TempByte);
			m_ReceiveStr = m_ReceiveStr + str;
		}
		
	}
	
	m_ReceiveStr.TrimLeft();
    m_ReceiveStr.TrimRight();

	if(m_ReceiveStr.IsEmpty())
	{
	   m_ReceiveStr = "<<���ճ�ʱ>>";
	}

	UpdateData(FALSE);

}

//����BCH��
//long ModuleNum   ģ���
//BYTE StationNo   �����ֵ�վ��
//BYTE MotherLine  ĸ��
//BYTE LineNo      �ߺ�
//BYTE Phase       ��ѡ��0A 1B 2C
//BYTE ZeroDots    ��ʱ��0����
//BYTE Item        Ҫʲô����,������
//int status       �ɷ�ʱ�����������
void CTTTView::ComeIntoBch20(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE          ORDER[9];
	BYTE          PhaseBit;
	long        m_PhaseBit;

	BYTE    data[21],g[32];
	memset(data,0,21);

	BYTE       AddrH,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 ����Ϊģ���Ϊ16���Ϊ01
	AddrH = (ModuleNum/100)>>13;//��λ    ��Ӧ��Ϊ����
   	AddrL = ModuleNum%100 - 1;  //��4λ   �����ӱ��ַ
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 8;i++)
	{
		ORDER[i] = 0;
	}
	
	StatusH = status/256;        //��λ    ��Ӧ��Ϊ����3�ĺ�2λ
	StatusL = status%256;        //��λ    ����4
	
	switch(Phase)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
            
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
		    
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[4]  = ZeroDots;// ��ʱ��0�����       
	//��� 
	
	//ORDER[5]��ORDER[10]�ɵ�Ƭ����Ƭ������ģ����
	ORDER[5]  = Item*32 + AddrL*2 + AddrH; //������(3) + ������ӱ��ַ(4) + ģ���ַ���λ(1);
		
	
	PhaseBit  = Item;

	for(int j = 0; j < 3; j ++)
	{
		data[2-j]  = Item%2;
		Item       = Item/2;
	}

	
    for( j = 0; j < 4; j ++)
	{
		data[6-j]   = AddrL%2;
		AddrL       = AddrL/2;
	}

	//��λ
	data[7]         =  AddrH;

	//ģ���
	m_PhaseBit       = ModuleNum/100;

	//ת��λ
	for(j = 0 ; j < 14; j ++)
	{
		data[20 - j]  = m_PhaseBit%2;
		m_PhaseBit    = m_PhaseBit/2;
	}

  	/*
	CString    str;

	for(j = 0; j < 21; j ++)
	{ 
	     str.Format("data[%d]=%d",j,data[j]);
		
		if((j + 1)%8 == 0)
		{
			WriteToLog(str + "\r\n");
		}
		else
		{
			WriteToLog(str);
		}
	}
	*/
    
	//////////////////////add 20060207
	/*
	for(j = 0; j < 21; j ++)
	{
		if(j == 20)
		{
			data[j] = 1;
		}
		else
		{
			data[j] = 0;
		}
		
	}
	*/
	
	/////////////////////////////add 20060207

	//ת��BCH��
	Encode_Bch_31_21_2(g,data);
	
 	/*
	for(j = 0; j < 32; j ++)
	{
		
        str.Format("g[%d]=%d",j,g[j]);

		if((j + 1)%8 == 0)
		{
			WriteToLog(str + "\r\n");
		}
		else
		{
			WriteToLog(str);
		}

	}

	DecodeBCH31212(g);
	*/

	//�����ָ���
	for( i = 5; i < 9; i ++)
	{
		
		ORDER[i]  = 0;
		
		for(int j = 0; j < 8;j ++)
		{
			//
			ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]<<(7-j));
		}

	//	str.Format("ORDER[%d]=%0x",i,ORDER[i]);
	//	WriteToLog(str);

	}

	for( i = 5; i <= 13; i ++)
	{
	
		if( i < 9)
		{
			SendByteArray.Add(ORDER[i]);
		}
		else
		{
			SendByteArray.Add(0x00);
		}

	}
}


//����BCH��
//long ModuleNum   ģ���
//BYTE StationNo   �����ֵ�վ��
//BYTE MotherLine  ĸ��
//BYTE LineNo      �ߺ�
//BYTE Phase       ��ѡ��0A 1B 2C
//BYTE ZeroDots    ��ʱ��0����
//BYTE Item        Ҫʲô����,������
//int status       �ɷ�ʱ�����������
void CTTTView::ComeIntoBch70(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 ����Ϊģ���Ϊ16���Ϊ01
	AddrH = int((int(ModuleNum/100)%65536)/256);//��λ    ��Ӧ��Ϊ����1
    AddrM = (int(ModuleNum/100)%65536)%256;     //�м�λ  ��Ӧ��Ϊ����2
	AddrL = ModuleNum%100 - 1;                  //��4λ   �ָ����
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}
    
	
	StatusH = status/256;        //��λ    ��Ӧ��Ϊ����3�ĺ�2λ
	StatusL = status%256;        //��λ    ����4
	
	switch(Phase)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
            
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
		    
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// ��ʱ��0�����       
	//��� 
	
	//ORDER[5]��ORDER[10]�ɵ�Ƭ����Ƭ������ģ����
	
	/*
	if(Item == 0xF7)//��������
	{
		ORDER[5]  = 0xF6 + int(int(ModuleNum/100)/65536); //�����֣�Ҫʲô������ģ���ַ���λ
		
	}
	else
	*/
	{
		
		ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //�����֣�Ҫʲô������ģ���ַ���λ
		
	}
	
	ORDER[6]  = AddrH;//ģ��ߵ�ַ
	ORDER[7]  = AddrM;//ģ���е�ַ
	ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
	
	//�µ�ѡ��
	switch(Item)
	{
	case 0xF2://�����ǹ㲥����
		{
			ORDER[9]  = StatusL;//פ��ʱ��
			break;
		}
    case 0x02://���й����
		{	
            break;
		}
	case 0x3a://����ѹ
		{
			break;
		}
	case 0x3e://�����0
		{
			break;
		}
	case 0x40://����������0
		{
            break;
		}
	case 0xF7://�͵����
		{
			
			//�͵����  D3 = 0000****
		//	ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
			break;
			
		}
	case 0xf6://�ϵ����
		{	
			
			//�Ͽ�״̬ʱ D3 = 1111****
			ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
			break;
			
		}
	case 0x82://�������й����
		{
			
			//����Ϊ��������
            break;
			
		}
		
	default:
		{
			//����Ϊ��������
			ORDER[9]  =  0x67;                                 //���ֽں���λΪ��ʱ��0����
		}
		
	}
	
	
	
	//���������,��ORDER[9]��ֵ
    switch(ZeroDots)
	{
	case 3:
		{
			
			ORDER[9]  = 0x60 + 0x07;    //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 5:
		{
			
			ORDER[9]  = 0x60 + 0x07;    //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 20:
		{
			
			ORDER[9]  = 0x60 +  0x06;    //���ֽں���λΪ��ʱ��0����
			break;
			
		}	
	case 30:
		{
			
			ORDER[9]  = 0x60 +  0x05;     //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 60:
		{
			
			ORDER[9]  = 0x60 +  0x04;     //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 100:
		{
			
			ORDER[9]  = 0x60 +  0x03;      //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 160:
		{
			
			ORDER[9]  = 0x60 +  0x02;      //���ֽں���λΪ��ʱ��0����
			break;
			
		}	
	case 200:
		{
			
			ORDER[9]  = 0x60 +  0x01;      //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	case 240:
		{
			
			ORDER[9]  =  0x60 + 0x00;     //���ֽں���λΪ��ʱ��0����
			break;
			
		}
	}
	
	//�����ֽ�
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��

	 /*
	 CString str;
	 for(int j = 0 ; j < 11; j++)
	 {
		str.Format("ORDER[%d]=%0X",j,ORDER[j]);
	    WriteToLog(str);
	 }
	*/
	
	//status
	//��ʱ����
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//BCH���
	//�����ֽ�,BCHУ��
	BYTE            g[64];
	BYTE         data[45];

	//	g[63] =             0;
	for( i = 5; i < 10; i ++)
	{
		
		//	str.Format("ORDER[%d]=0x%0x",i,ORDER[i]);
		//	WriteToLog(str);
		PhaseBit = ORDER[i];

		//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

		for(int j = 1; j <= 8; j ++)
		{
			
			//strtemp.Format("%d",PhaseBit%2);
			//WriteToLog(strtemp);
			//data[(i-5)*8+j-1] = TempVale%2;   //add 2004.12.28
			//ssgg 7-5
			//data[6 + (i-5)*8+j-1] = PhaseBit%2;//add 2004.12.28
			//PhaseBit              = PhaseBit/2;
			data[6 + (i - 5) * 8 + j - 1] = (PhaseBit & 0x80) == 0 ? 0 : 1;//add 2004.12.28
			PhaseBit                      = PhaseBit << 1;
			//end ssgg 7-5
		}
		
	}
	
	//  40-45��Ϊ0
	//	data[40] = data[41] = data[42] = data[43] = data[44] = 0;
	data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;

//ssgg debug
		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			int i;
			for(i=0; i<46; i++) {
				CString mystr;
				if(data[i] == 0)
					mystr='0';
				else
					mystr='1';
				fputs(mystr+" ",text);
				if((i+1) % 8 == 0)
					fputs(" ", text);
			}
			
			fputs("\r\n",text);
			fclose(text);
		}
//end ssgg debug

	//ת��BCH��
	Encode_Bch_63_45_3(g,data);
	
	//�����ָ���
	for( i = 5; i < 13; i ++)
	{
		
		ORDER[i] = 0;
		
		for(int j = 0; j < 8;j ++)
		{
			//ssgg 7-5
			//ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,j));
			ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow(2,j*(-1) + 7));
			//end ssgg 7-5
		}
		
	}
	
	ORDER[13] = 0;
		//ssgg debug
		//		FILE *text;
		if((text = fopen("f:\\ttt.txt","a")) != NULL)
		{
			char aaa[128];
			sprintf(aaa, "%x\n", ORDER[i]);
			fputs(aaa,text);
			fclose(text);
		}
		//end ssgg debug

	for( i = 5; i <= 13; i ++)
	{
		SendByteArray.Add(ORDER[i]);
	}
}

//����BCH��
//long ModuleNum   ģ���
//BYTE StationNo   �����ֵ�վ��
//BYTE MotherLine  ĸ��
//BYTE LineNo      �ߺ�
//BYTE Phase       ��ѡ��0A 1B 2C
//BYTE ZeroDots    ��ʱ��0����
//BYTE Item        Ҫʲô����,������
//int status       �ɷ�ʱ�����������
void CTTTView::ComeIntoBch60(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status)
{
	
	BYTE ORDER[15];
	BYTE  PhaseBit;
	
	BYTE AddrH,AddrM,AddrL;
	
	BYTE StatusH,StatusL;
	
	//1601 ����Ϊģ���Ϊ16���Ϊ01
	AddrH = int((int(ModuleNum/100)%65536)/256);//��λ    ��Ӧ��Ϊ����1
    AddrM = (int(ModuleNum/100)%65536)%256;     //�м�λ  ��Ӧ��Ϊ����2
	AddrL = ModuleNum%100 - 1;                  //��4λ   �ָ����
	
	// A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
		
	}    
	
	StatusH = status/256;        //��λ    ��Ӧ��Ϊ����3�ĺ�2λ
	StatusL = status%256;        //��λ    ����4
	
	switch(Phase)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
            
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 7;
			}
			else
			{
				m_CollectChannels = 0;
			}
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 8;
			}
			else
			{
				m_CollectChannels = 1;
			}

			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
		    
			//�����789����
			if(m_tong789)
			{
				m_CollectChannels = 9;
			}
			else
			{
				m_CollectChannels = 2;
			}

			break;
		}
	}
	
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	//ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo - 1) * 4 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo * 4) + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C

	ORDER[4]  = ZeroDots;// ��ʱ��0�����       
	
	//��� 
    //ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 20λ�������� + 7λ������(0001000)
	//����� 485��: 18(�ලλ) + 14(��ַ) + "1"(485��־)           + 5(����) + 7λ������(0001000)
	//����������: 18(�ලλ) + 14(��ַ) + "0"(������ֵ�ַ)      + 2(����) + 7λ������(0001000)
	
	//��ַǰ8λ
	ORDER[5]  = (ModuleNum/100)>>6; //��ַ��λ
	
	if(ModuleNum%100 >= 12)
	{
		//485��  6λ��ַ  +  1λ(485��־) + 1λ������(��5λ������)
		ORDER[6]  = ((ModuleNum/100)%64)* 4 + 1*2 + (Item>>4);
		//4λ������(��5λ������) + 4λ������(0001)
		ORDER[7]  = (Item%16)*16 + 1;
		//3λ������(000) + 5��0
		ORDER[8]  =  0x00;//00000000
		
	}
	else
	{	
		
		//ͣ�͵�
		if(Item == 0x00 || Item==0x01)
		{
			//ʹ�ϵ�ͣ�粻���׳��֣�����7����ͣ�͵� 0111
			//����� 6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ)
			ORDER[6]  = ((ModuleNum/100)%64)* 4  +  1;
			//�ӱ��ַ2λ��λ(��4λ�ӱ��ַ)+2λ������+4λ������(0001)
			ORDER[7]  = 3*64+ (Item%4)*16        +  1;
			
		}
		else
		{
			//����� 6λ��ַ + �ӱ��ַ2λ��λ(��4λ�ӱ��ַ)
			ORDER[6]  = ((ModuleNum/100)%64)* 4 + ((ModuleNum%100-1)>>2);
			//�ӱ��ַ2λ��λ(��4λ�ӱ��ַ)+2λ������+4λ������(0001)
			ORDER[7]  = ((ModuleNum%100-1)%4)*64+ (Item%4)*16     +    1;
			
		}
		
		//3λ������(000) + 5��0
		ORDER[8]  =  0x00;//00000000
	}
	
	//BCH���
	//�����ֽ�,BCHУ��
	//61,62,Э��,�����ֽ�,BCHУ�� 45_27_3
	BYTE             g[45];
	BYTE          data[27];
	
	//��27λ����ȡ��
	long         TempVale = (ORDER[5]<<19) + (ORDER[6]<<11) + (ORDER[7]<<3) +  (ORDER[8]>>5);
	
	//21λ����
	for(int j = 0; j < 27; j ++)
	{
		data[26-j]  = TempVale%2;
		TempVale    = TempVale/2;     
	}
		
	//ת��BCH��
	Encode_Bch_45_27_3(g,data);

	//�����ָ���
	for( i = 5; i < 13; i ++)
	{
		
		ORDER[i]     =   0;
		
		for(int j = 0; j < 8;j ++)
		{
			
			if(((i-5)*8 + j ) > 44)
			{
				ORDER[i] = ORDER[i] + 0;
			}
			else
			{
				ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow(2,7-j));
			}
			
		}	
		
	}
	
	ORDER[13] = 0;

	for( i = 5; i <= 13; i ++)
	{
		SendByteArray.Add(ORDER[i]);
	}
}

void CTTTView::OnChangeAngle() 
{
	UpdateData(TRUE);
	
	/*
	if(m_angle  < 5 || m_angle  > 50)
	{
		MessageBox("�Ƕȳ���[5,50]��","����",MB_OK|MB_ICONWARNING);
        m_angle  =     30;
		UpdateData(FALSE);
	}
	*/

}

//31-21-2
BOOL CTTTView::DecodeBCH31212(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 5, n = 31 , length = 31, t = 2, k = 21, d = 5;
   
	m_CollectPlace[0] = 0;
	m_CollectPlace[1] = 0;

	CString str;
	
	int alpha_to[] = {  1,  2,  4,  8, 16,  5, 10, 20, 
		                13, 26, 17,  7, 14, 28, 29, 31, 27, 19,  3,  6, 12, 24, 21, 15,30, 25, 23, 11, 22,  9, 18,  0};
  
	int index_of[] = { -1,  0,  1, 18,  2,  5, 19, 11,
                         3, 29,  6, 27, 20,  8, 12, 23,
                         4, 10, 30, 17,  7, 22, 28, 26,
                         21, 25,  9, 16, 13, 14, 24, 15};
	t2 = 2 * t;
	
	////�����ۺϲ�֢ 
    s[0] = 0;// add by hgm  2003.11.19
	for (i = 1; i <= t2; i++)
	{
		//�޸� 2004.1.11
		//for (i = 0; i <= t2; i++)
		s[i] = 0;
		for (j = 0; j < length; j++)
			if (recd[j] != 0)
				s[i] ^= alpha_to[(i * j) % n];
			if (s[i] != 0)
				syn_error = 1; // ���ô����־
			// ת���ۺϲ�֢�Ӷ���ʽ��������ʽ
			s[i] = index_of[s[i]];
			
	}
	
	//�д���Ļ�
	if (syn_error) 
	{
		
		//��������λ�ö���ʽ��ŷ�������㷨��
		for (i = 0; i <= d; i ++) 
		{
			r[0][i] = 0;
			r[1][i] = 0;
			b[0][i] = 0;
			b[1][i] = 0;
			qt[i]   = 0;
		}
		
		b[1][0] = 1; 
		degb[0] = 0;
		degb[1] = 0;
		
		r[0][d] = 1; // x^{2t+1}
		degr[0] = d;
		
		for (i = 0; i <= t2; i ++)
		{
			if (s[i] != -1)
			{
				r[1][i] = alpha_to[s[i]];
				degr[1] = i;
			}
			else
				r[1][i] = 0;
		}
		
		j = 1;
		
		if( (degr[0]-degr[1]) < t ) 
		{
			
			do {
				
				j++;
				
				for (i = 0; i <= d; i ++)
				{
					r[j][i] = 0;
				}
				
				for (i = 0;i <= degr[j-2];i ++) 
					r[j][i] = r[j-2][i]; 
				degr[j] = degr[j-2];
				
				temp = degr[j-2]-degr[j-1];
				for (i = temp; i >= 0; i --) 
				{
					u = degr[j-1]+i;
					if (degr[j] == u)
					{
						if ( r[j][degr[j]] && r[j-1][degr[j-1]])
							qt[i] = alpha_to[(index_of[r[j][degr[j]]] + n - index_of[r[j-1][degr[j-1]]])%n];
						
						
						for (u = 0; u <= d; u ++) aux[u] = 0;
						
						temp = degr[j-1];
						for (u = 0; u <= temp; u ++)
							if ( qt[i] && r[j - 1][u] )
								aux[u + i] = alpha_to[(index_of[qt[i]]+index_of[r[j-1][u]])%n];
							else
								aux[u + i] = 0;
							
							for (u = 0; u <= degr[j]; u ++)
								r[j][u] ^= aux[u];
							u = d;
							while ( !r[j][u] && (u > 0)) u--;
							degr[j] = u;
					}
					else
						qt[i] = 0;
					
				}
				
				temp = degr[j-2] - degr[j-1];
				
				//����b(x)����ֵ
				
				for (i = 0; i <= d; i ++) 
					aux[i] = 0; 
				
				temp = degr[j - 2] - degr[j - 1];
				for (i = 0; i <= temp; i ++)
					for (u = 0; u <= degb[j - 1]; u ++)
						if ( qt[i] && b[j - 1][u] )
							aux[i+u] ^= alpha_to[(index_of[qt[i]] + index_of[b[j-1][u]])%n];
						
						for (i = 0; i <= d; i ++) 
							b[j][i] = b[j-2][i] ^ aux[i];
						
						u = d;
						while ( !b[j][u] && (u > 0) ) u--;
						degb[j] = u;
						
						
			} while (degr[j] > t); 
			
		}
		
		u    =       1;
		temp = degb[j];
		
		// ��񻯴���λ�ö���ʽ
		for (i = 0;i <= temp;i ++) 
		{
			elp[u][i] = alpha_to[(index_of[b[j][i]] - index_of[b[j][0]] + n)%n];
		}
		l[u] = temp;
		
		if (l[u] <= t) 
		{
			// put elp into index form 
			for (i = 0; i <= l[u]; i++)
				elp[u][i] = index_of[elp[u][i]];
			
			// ��Chien search�ҵ������λ�� 
			for (i = 1; i <= l[u]; i++)
				reg[i] = elp[u][i];
			count = 0;
			for (i = 1; i <= n; i ++) 
			{
				q = 1;
				for (j = 1; j <= l[u]; j++)
					if (reg[j] != -1) 
					{
						reg[j] = (reg[j] + j) % n;
						q     ^= alpha_to[reg[j]];
					}
					if (!q)
					{
						root[count] = i;
						loc[count]  = n - i;
						count++;
						//printf("%3d ", n - i);
					}
			
			}
			
			
			if (count == l[u])
			{
				//	// no. roots = degree of elp hence <= t errors 
				str.Format("������������� count = %d",count);
				WriteToLog(str);
				
				//����ĸ���
				m_CollectNos = count;

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					/*
					if( loc[i] < 24)
					{
						str.Format("��������λ�ã�%d",23 - loc[i]);
					}
					else
					{
						str.Format("��������λ�ã�%d",86 - loc[i]);
					}
					*/
								
					if( loc[i] < 10)
					{
						m_CollectPlace[i] = 9 - loc[i];
						str.Format("��������λ�ã�%d",9 - loc[i]);
					}
					else
					{
						m_CollectPlace[i] = 40 - loc[i];
						str.Format("��������λ�ã�%d",40 - loc[i]);
					}
					                  
				    //str.Format("��������λ�ã�%d",loc[i]);
					
					WriteToLog(str);
					

				}
				return TRUE;
				
			}
			else
			{
				//
				str.Format("�������Ϊ�� count = %d��l[%d] = %d",count,u,l[u]);
				WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> lengthΪ����ֵ 
		}
		else
		{
			//
			str.Format("�������Ϊ��%d > 4 ",l[u]);
			WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//	
		m_CollectNos    =    0;
		str = "t = 0,û�д���";
		WriteToLog(str);//
		return TRUE;
	}

}

void CTTTView::OnCheck12() 
{
	UpdateData();
	
	if(m_xinjiaobian)
	{
		GetDlgItem(IDC_CHECK13)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CHECK13)->EnableWindow(FALSE);
	}
}

void CTTTView::OnChangeusedata() 
{
	CChangeFileDlg dlg;
	dlg.DoModal();
	
}

void CTTTView::OnSendallone() 
{
	CSendEveryTime  dlg;

	if(dlg.DoModal() == IDOK)
	{
		CWnd* pt = GetDlgItem(IDC_DATAVALUE);
		pt->SetWindowText("  ");
		pt = GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SEND);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SETTIMER);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_DECODE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_RADIO_REALTIME);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_COMSET);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_SENDALLONE);
		pt->EnableWindow(FALSE);
		pt = GetDlgItem(IDC_REALSTOP);
		pt->EnableWindow(TRUE);

        SetTimer(2,dlg.m_Seconds*1000,NULL);
		OnTimer(2);
	
	}
}

//ȫ��1
void CTTTView::SendAllOne()
{

	UpdateData(TRUE);
    BYTE           Receive[5];
	BYTE            ORDER[15];
	U32             output[5];
	CString        str,bakstr;
	
    // A 01 B 02  C 03
    for(int i =0 ;i < 15;i++)
	{
		ORDER[i] = 0;
	}
 
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	ORDER[3]  = (BYTE)(m_generatrix - 1) * 64 + (BYTE)((m_iChSelect + 1) * 4) + (m_phase + 1);//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[4]  = 3;    // ��ʱ��0�����       

	//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
	ORDER[2] = m_protocol/10*16 + m_protocol%10;
	
	if(m_protocol == 22)
	{
		//22Э�鵱71Э����
		ORDER[2] = 0x71;
	}
	else if(m_protocol == 31)
	{
		ORDER[2] = 0x53;
	}
	
	
	//�����ָ���
	for( i = 5; i <= 13; i ++)
	{
		ORDER[i] = 0xff;
	}			
		
 	//��ǰ14λ
	for(int j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//�����
			ORDER[14] = ORDER[14] + ORDER[j];
		}

	}

	//���ͼ����
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//��һ����
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//�߷�����
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//ʱ��
		if(err != 0)
		{
			Beep(300,400);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//ʱ��
		if(err != 0)
		{
			Beep(300,400);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			Beep(300,400);
		}

		Receive[j] = BYTE(output[j] & 0xff);

		Sleep(1);
	}
	
	/*
	str = "";
	for(j = 0; j <= 14; j ++)
	{
		bakstr.Format("ORDER[%d]=%0x \r\n",j,ORDER[j]);
		str = str + bakstr;
	}
	
	WriteToLog("����ָ�" + str);

	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		str.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//���λ��λȥ��
		WriteToLog("˫��ͨѶʱ����Ͳ���!\r\n" + str + "\r\n");
		Beep(300,400);
	}
	*/

}



//������λ
void CTTTView::OnButtonTestphase() 
{
	UpdateData(TRUE);
	BYTE         ORDER[15];
    BYTE  temp         = 0;
	BYTE  m_phaseValue = 0;

	//A��
	if(m_bCh8) 
	{
		temp         ++ ;
		m_phaseValue = 0;
	}
	
	//B��
	if(m_bCh9) 
	{
		temp         ++ ;	
		m_phaseValue = 1;

	}

	//C��
	if(m_bCh10) 
	{
		temp         ++ ;
		m_phaseValue = 2;
	}
	
	if(temp > 1)
	{
		MessageBox("����λ����ͬʱѡ��������ϵ�ѹ������ѡ��"," ",MB_OK|MB_ICONASTERISK);
		return;
	} 

	//��ʾ���ι���
	m_ShowWave     =   FALSE;
  	g_Extend       =      10;
	UpdateData(FALSE);

	unsigned short *ai_buf=NULL;
    I16                     err;
	
    err = AI_9111_Config(card, TRIG_INT_PACER, 0, 1024);
    if (err!=0) 
	{
	    Beep(300,400);
		return;
    }

	if(temp > 0)
	{
	
		//������,ORDER[0]��ORDER[4]������Ƭ����
		ORDER[0]  = 0x51;           //ǰ����
		ORDER[1]  = 0x52;           //ǰ����
		ORDER[2]  = 0x6c + m_phaseValue; //��������
		ORDER[3]  = (BYTE)(m_generatrix - 1) * 64 + (BYTE)((m_iChSelect + 1) * 4) + (m_phaseValue + 1);//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
		ORDER[4]  = 3;// ��ʱ��0����� 
		ORDER[5]  = 0;
		ORDER[6]  = 0;
		ORDER[7]  = 0;
		ORDER[8]  = 0;
		ORDER[9]  = 0;
		ORDER[10] = 0;
		ORDER[11] = 0;
		ORDER[12] = 0;
		ORDER[13] = 0;
		
		//��Ƭ��������
		if(!PcSendToSCM(ORDER))
		{
			MessageBox("�Է�û����Ӧָ��������ԣ���"," ",MB_OK|MB_ICONASTERISK);
			return;
		}
	
	}
    
	err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
  
	err = AI_ContScanChannels(card,LASTCHANNEL, AD_B_10_V, ai_buf, nReadCount,(SampleRate+1)*1000, ASYNCH_OP);
  	
	//����Ļ�
	m_TestPhase = TRUE;
	AfxBeginThread(ScanChannels,this);

	bClearOp = 0;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_SMPRATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_ANALYZE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_REALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TESTPHASE)->EnableWindow(FALSE);
	
}

void CTTTView::OnChangeEditCurrentgainsmpwin() 
{
	CString str;
	UpdateData();

	Invalidate();

	g_GainSampleWin        = m_fGainSampleWin;
	g_CurrentGainSampleWin = m_fCurrentGainSampleWin;	

	str.Format("+%3.2fV(+%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEP)->SetWindowText(str);
    str.Format("-%3.2fV(-%3.2fV)",10/m_fGainSampleWin,10/m_fCurrentGainSampleWin);
	GetDlgItem(IDC_STATIC_DISPSCALEN)->SetWindowText(str);

	if(m_iModeSel > 0)
	{
	    OnButtonUpdate();
	}
	
}

//�������ֵ
int CTTTView::ChangeIValue(BYTE m_Ivale)
{
	int m_ReturnValue = 0;

	if(m_Ivale <= 22)
	{
		m_ReturnValue = m_Ivale*1.000/22*400;
	}
	else if(m_Ivale > 22 && m_Ivale <= 38)
	{
		m_ReturnValue = 400 + (m_Ivale-22)*1.000/(38-22)*(720 - 400);
	}
	else if(m_Ivale > 38 && m_Ivale <= 53)
	{
		m_ReturnValue = 720 + (m_Ivale-38)*1.000/(53-38)*(800 -720);
	}
	else if(m_Ivale > 53 && m_Ivale <= 57)
	{
		m_ReturnValue = 800 + (m_Ivale-53)*1.000/(57-53)*(912 - 800);
	}
	else if(m_Ivale > 57 && m_Ivale <= 73)
	{
		m_ReturnValue = 912 + (m_Ivale-57)*1.000/(73-57)*(1200 -912);
	}
	else if(m_Ivale > 73 && m_Ivale <= 96)
	{
		m_ReturnValue = 1200 + (m_Ivale-73)*1.000/(96-73)*(1300 - 1200);
	}
	else
	{
		m_ReturnValue = 1500;
	}

	return int(m_ReturnValue);


}

//�ǽǱ�ȫ����ͨ������,��6�Σ�������������Э��
double CTTTView::DecodeSixChannel(long ModuleNum, BYTE Protocol, BYTE Item, BYTE m_phase)
{	
	CString               str,signstr;
	BYTE                     Data[39];
	double dataValue         =     -1;
	int   index              =      0;
    long                   Diffs[200];
	long         m_sums        =    0;
	int          m_StartPlace  =    0;
	double  m_maxppvalue       =    0;
	short   m_pipeiplace       =    0;
	int     m_maxpptimes       =    5;//���5����
	double  m_ppvalue          =    0;
    BYTE  SignalBit[100],TempSignalBit[100],Signal[10];
	double          m_ppresult[6000];//ƥ����
    int            m_ChaValue =    25;//25�����ƥ�䲨;
    short        m_PlaceDifferent[31];//22Э�鲻ͬ�ĶԱ�λ��
	BOOL         m_checkplace = FALSE;
	BYTE         m_ByteRecords =    0;//�յ��ֽ���
	int              m_ZeroPalce[1500];//�����λ��
	short             m_tempdata1[400];
    short             m_tempdata2[400];
	short             m_tempdata3[400];
    short             m_tempdata4[400];

	for(int i = 0; i < 6000;i ++)
	{
		m_ppresult[i] = 0;
	}

	//ʱ�����
	if(Protocol == 22)
	{
	    //(5 + 31*4*2)*2048 = 518144  ��ǰ�ɼ�
		if(DataLen < 518144)
		{	
			return -1;
		}
		
		m_ByteRecords = 62;

	}
	else if(Protocol == 31 || Protocol== 32 || Protocol == 71 || Protocol == 72 || Protocol == 73)
	{
		//(5 + 63*4)*2048 = 526336   ��ǰ�ɼ�
		if(DataLen < 526336)
		{	
			return -1;
		}
		
		m_ByteRecords = 63;

	}
	else if(Protocol == 61)
	{
		//(5 + 45*4)*2048 = 378880    ��ǰ�ɼ�
		if(DataLen < 378880)
		{	
			return -1;
		}
		
		m_ByteRecords = 45;
		
	}
	else if(Protocol == 62)
	{
		//(5 + 2*45*4)*2048 = 747520  ��ǰ�ɼ�
		if(DataLen < 747520)
		{	
			return -1;
		}	
		
		m_ByteRecords = 90;
		
	}

	//���������ѹ����,����������ƥ��ֵ���Ľ��
	for(int m_PhaseTest = 0; m_PhaseTest < 3; m_PhaseTest ++)
	{

		//��ʼ����0������
		for(int i = 0; i < 1500; i ++)
		{
			m_ZeroPalce[i]  =  0;
		}
		
		//�ɼ�������ת��
		for( i = 0;i < DataLen/6; i ++)
		{
			m_TestCurrent[i]  = DataBuf[i*6 + m_PhaseTest    ]; //m_phase���������
			m_TestVoltage[i]  = DataBuf[i*6 + m_PhaseTest + 3]; //m_phase���ѹ����

			/*
			if(m_PhaseTest == 2)
			{
				str.Format("%6d",m_TestVoltage[i]);
				WriteToLog(str);
			}
			*/
		}
		
		index   =     0;
		
		//�ҵ�ѹ��0��
		for( i = 0;i < DataLen/6; i ++)
		{
			
			m_StartPlace = FindZeroPoint(m_TestVoltage,i,30);
			
			if(m_StartPlace > m_ChaValue) // 20������ 20*2000/6/360 = 18.5
			{
				
				if(index < 1500)
				{
					m_ZeroPalce[2*index] = m_StartPlace;//��ѹ�����λ��
					//m_ZeroPalce[index] = m_StartPlace;//��ѹ�����λ��
					index                         ++ ;
				}
				
				//����һ�������
				i  = i + 300;	
			 // i  = i + 150;
			
			}	
			
		}

		
		//��0��
		for( i = 0;i < index - 1; i ++)
		{
            m_ZeroPalce[2*i + 1] = (m_ZeroPalce[2*i] + m_ZeroPalce[2*(i + 1)])/2;
		}
		
		
		//�����������Ч��
		for( i = 1; i < 1500 ; i ++)
		{
			
			if(m_ZeroPalce[i - 1] > 0 && m_ZeroPalce[i] > 0)
			{
				
			
				/**/
			//	if(m_PhaseTest == 2)
				{
				//	str.Format("m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,���:%d",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
				//	WriteToLog(str);
				}
				
				
				/*
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 33)
				{	
					
					str.Format("����ѹ�����������:m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,���:%d��",i - 1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
					WriteToLog(str);
					return           -1;		
					
				}
		    	*/
			
				
				//�������
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 15)
				{
				
					m_ZeroPalce[i] = m_ZeroPalce[i - 1] + 167;	
				
				}
				
			}
			
		}
		
		
		//��һ����������,���ư����
		index = 0;
		
		for( i = 0; i < 20; i ++)
		{
			
			if(m_TestVoltage[m_ZeroPalce[0] - i] >= 0)
			{
				
				index ++ ;
				
			}
			
		}
		
		//�����60%�Ǵ���0����
		if(index > 12)
		{
			//	signstr.Format("\r\n����һ�����������򲨡�\r\n");
			//	WriteToLog(signstr);
			
			for(int i = 0 ; i < 1499; i ++)
			{
				
				m_ZeroPalce[i]  = m_ZeroPalce[i + 1];
				
			}
			
		}/**/
		
				
		//��1����,�ҵ�һ����0��  m_frontdot �����ȵ�ѹ���ĵ���
		for(int hhh = 0; hhh < m_maxpptimes; hhh ++)
		{
			
			//����10�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
			for(index = 0; index < m_ByteRecords ;index ++)
			{
				
				
				for(int i = 0 ; i < 2*m_ChaValue; i ++)
				{	
					
					//��һ����,�����ǰ���ȡm_ChaValue����			
					m_tempdata1[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 1]  - m_ChaValue + i]; 
					m_tempdata1[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 2]  - m_ChaValue + i]; 
					
					//�ڶ�����	
					m_tempdata2[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 3]  - m_ChaValue + i]; 
					m_tempdata2[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 4]  - m_ChaValue + i]; 
					
					//��������
					m_tempdata3[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 5]  - m_ChaValue + i]; 
					m_tempdata3[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 6]  - m_ChaValue + i]; 
					
					//���ĸ���
					m_tempdata4[               i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 7]  - m_ChaValue + i]; 
					m_tempdata4[2*m_ChaValue + i] = m_TestCurrent[m_ZeroPalce[hhh*2 + index*8 + 8]  - m_ChaValue + i]; 
					
				}	
				
				//4�������
				for( i = 0; i < 4*m_ChaValue; i ++)
				{
					m_tempdata1[i] = m_tempdata3[i] - m_tempdata1[i]  +  m_tempdata4[i] - m_tempdata2[i]; 
				}
				
				//2���������
			    //WriteToLog("\r\n\r\n");
				//str.Format("���:%d,��%d����:",m_PhaseTest,hhh + 1);
				//WriteToLog(str);

				for( i = 0; i < m_ChaValue; i ++)
				{
					Diffs[i] = m_tempdata1[3*m_ChaValue/2 + i] + m_tempdata1[5*m_ChaValue/2 + i]; 

				    /*
					if( hhh == 2 || hhh == 3 || hhh == 4)
					{
						str.Format("Diffs[%4d] = %5d",i,Diffs[i]);
						WriteToLog(str);	
						
						if(i == (m_ChaValue - 1))
						{
							//2���������
							WriteToLog("\r\n\r\n");
						}

					}
					*/
				

				}
				
				//5��ƥ�䲨
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  +                                hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table05,Diffs,25);
				//10��ƥ�䲨
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  +   m_maxpptimes*m_ByteRecords + hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table10,Diffs,25);
				//20��ƥ�䲨
				m_ppresult[ m_PhaseTest*3*m_maxpptimes*m_ByteRecords  + 2*m_maxpptimes*m_ByteRecords + hhh*m_ByteRecords + index]   = CorrelationSixChannelCheck(CorrelationSix_Table20,Diffs,25);
			}
			
		}
		
	}
  
	/*	
	for(int j = 0; j  < 3*3*m_maxpptimes*m_ByteRecords; j ++)
	{
		
		if( ((j + 1)%m_ByteRecords) == 0)
		{
			str.Format("m_ppresult[%4d] = %8.2f\r\n\r\n\r\n\r\n",j%m_ByteRecords,m_ppresult[j]);
			
		}
		else
		{
			str.Format("m_ppresult[%4d] = %8.2f",j%m_ByteRecords,m_ppresult[j]);
		}
		
		WriteToLog(str);
	}
	*/

		
	//��5��10��20�����ҳ����ƥֵ
	m_maxppvalue  =    0;

	//�����ƥ��ֵ
	for(int jj = 0; jj < 3*3*m_maxpptimes; jj ++)//m_maxpptimes����
	{
		
		m_ppvalue    =    0;//ƥ��ֵ��
		
		for(index = 0; index < m_ByteRecords ;index ++)
		{
			
			m_ppvalue = fabs(m_ppresult[jj*m_ByteRecords + index]) + m_ppvalue;
			
		}
		
		if(m_ppvalue > m_maxppvalue)
		{
			m_maxppvalue  =  m_ppvalue;//���ƥ��ֵ
			m_pipeiplace  =         jj;//��ס���ƥ��λ��
		}

		signstr.Format("λ�ã�%d,ֵ��%.2f",jj + 1,m_ppvalue);
		WriteToLog(signstr);
	}

    signstr.Format("ģ��ţ�%d,���%d,��%d����,�Ƕȣ�%d��,ƥ��λ�ã�%d,ƥ���ֵ��%.2f����ֵ��%.2f",ModuleNum,m_pipeiplace/(3*m_maxpptimes),(m_pipeiplace%m_maxpptimes) + 1,5*int(pow(2,((m_pipeiplace%(3*m_maxpptimes))/m_maxpptimes))),m_pipeiplace+1,m_maxppvalue,float(m_maxppvalue/m_ByteRecords));
    WriteToLog(signstr);

	WriteToLog("���ƥ�������£�\r\n");

	//���ƥ��λ�õ�����
	for(index = 0; index < m_ByteRecords ;index ++)
	{
		
		//ƥ��ֵ��
		if(m_ppresult[m_pipeiplace*m_ByteRecords + index]  > 0)
		{
			SignalBit[index] = 0;
		}
		else 
		{
			SignalBit[index] = 1;
		}

		signstr.Format(" �յ�����Ϊ��SignalBit[%2d] = %0x [%.3f]",index,SignalBit[index],m_ppresult[m_pipeiplace*m_ByteRecords + index]);
		WriteToLog(signstr);
		
		//�س���
		if((index + 1) % 8 == 0 || index == m_ByteRecords - 1)
		{
			
			if((index + 1) % 8 == 0)
			{
				
				if(SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{	
					signstr.Format(" 0x%0x  ",SignalBit[index - 7] * 128 + SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				
			}
			else
			{	

				BYTE   m_addValue  =    0;
 
				if(index == m_ByteRecords - 1)
				{
					BYTE        m_ttts;
					m_ttts   =  m_ByteRecords- (m_ByteRecords/8)*8;


					for(int jjj = 0; jjj < m_ttts; jjj ++)
					{
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow(2,m_ttts-1-jjj));
					
					}
				
				}

				/*
				if(SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index] < 16)
				{
					signstr.Format(" 0x0%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				else
				{
					signstr.Format(" 0x%0x  ",SignalBit[index - 6] * 64 + SignalBit[index - 5]* 32 + SignalBit[index - 4] * 16  + SignalBit[index - 3] * 8 + SignalBit[index - 2] * 4 + SignalBit[index - 1] * 2  + SignalBit[index]);
				}
				*/

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\nʮ������Ϊ:"+ signstr + "\r\n");
			m_ReceiveStr = m_ReceiveStr + signstr;
			
		}
		
	}

	if(Protocol == 22)
	{
		
		//��ͬ������
		m_sums            =    0;
		
		//�����22Э��Ļ�,�Ա������յ�����
		for(short i = 0; i <  31; i ++)
		{
			
			//�Ա����ν��յ�������
			if(SignalBit[2*i] != SignalBit[2*i+1])
			{
				//��ס��ͬ��λ��
				m_PlaceDifferent[m_sums] = i;
				m_sums                    ++;
				
			}
			
		}
		
		//���ݵ����ٴ���,����10�Ⱥ�5�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
		for(index = 0; index < 31 ;index ++)
		{
			
			//��ƥ��ϵ�����
			m_ppvalue = m_ppresult[m_pipeiplace*m_ByteRecords + 2*index] + m_ppresult[m_pipeiplace*m_ByteRecords + 2*index + 1]; 
			
			//��0��1
			if(m_ppvalue  > 0)
			{
				SignalBit[index] = 0;
			}
			else 
			{
				SignalBit[index] = 1;
			} 
			
		}
		
		//����˳�����
		for( i = 0; i <  31; i ++)
		{
			//31,21,2
			if( i < 10 )
			{
				TempSignalBit[i]    = SignalBit[9 - i];
			}
			else
			{
				TempSignalBit[i]    = SignalBit[30 - i + 10];
			}
			
		}	
		
		//�������
		m_CollectNos    =   10;
		dataValue       =   -1;
		
		//WriteToLog("\r\n��ʼ����\r\n");	
		
		Sleep(100);	
		
		if(!(m_sums <= 6))
		{	
			//WriteToLog("��Χ����");
			return -1;
		}
		
		//31212����
		if(DecodeBCH31212(TempSignalBit))
		{
			
			//��һ�¾���λ,����о����λ
			if(m_CollectNos > 0)
			{
				m_checkplace  =    FALSE;
				
				//��λ�㷨,�����λ�Ƿ����ڲ�ͬ��λ����
				for(int i = 0; i < m_CollectNos;i ++)
				{
					
					m_checkplace  = FALSE;
					
					//�м�����
					for(int j = 0; j < m_sums; j++)
					{
						
						if(m_PlaceDifferent[j] == m_CollectPlace[i])
						{
							m_checkplace = TRUE;
							break;
						}
						
					}
					
					if(!m_checkplace)
					{
						break;
					}
					
				}
				
				//������λ��Ҫ�����鲻ͬ������λ����
				if(!m_checkplace)
				{
					return -1;
				}
				
			}
			
			//signstr.Format("��λ��m_CollectNos��%d",m_CollectNos);
			//WriteToLog("\r\n"+ signstr + "\r\n");
			
			// ���������λ�ڲ�ͬ��λ���л���û�д���
			if(m_checkplace || m_CollectNos == 0)
			{
				
				//��10-30Ϊ����λ��->�߷�չ���ص���Ϊ16����
				//����  0��30A
				//��ѹ  0��300V
				//�͵�ɹ�0x32
				//������ 21ȫΪ1(111111111111111111111)�������������λΪ********************0
				//פ��û��פ����  (000000000000000000001)  20��0 + 1
				
				//16���ƽ���
				dataValue   =     0.00;
				
				for( i = 0; i < 21; i++)
				{
					dataValue = dataValue + double(TempSignalBit[10 + i]*pow(2,i));
				}
				
				//str.Format("dataValue = %d",int(dataValue));
				//WriteToLog(str);
				
				if(TempSignalBit[10] == 1)
				{
					
					//���ͨѶ����,ֻ��485����е��ͨѶ����
					if(ModuleNum%100 >= 12 && long(dataValue)==2097151)
					{
						//���ͨѶ����
						return  -2;			
					}
					
					//פ��û��פ����,פ��ָ�����λΪ0
					if(long(dataValue)== 1 && (Item%2==0) )
					{
						//פ��û��פ����
						return  -4;			
					}	
					
					//���λΪ�����
					dataValue       =   -1;
					
				}
				else
				{
					//��������2λС��
					if(Item == 0x63 ||  Item == 0x62)
					{
						
						//���ֵΪ100*1000
						if(dataValue <= 100000)
						{
							return dataValue/1000;
						}
						else
						{
							dataValue =  -1;
						}
						
					}
					else
					{
						//����,���ֵΪ0��30
						if((Item>= 0x64 && Item<=0x69) || Item == 0x04)
						{
							//���ֵΪ300
							if(dataValue < 300)
							{
								return dataValue/10;
							}
							else
							{
								dataValue =  -1;
							}
							
						}
						
						//��ѹ,���ֵΪ0��300
						if((Item>= 0x6a && Item==0x6f) || Item==0x01)
						{
							//���ֵΪ300
							if(dataValue < 3000)
							{
								return dataValue/10;
							}
							else
							{
								dataValue =  -1;
							}
							
						}	
						
					}
					
					if(dataValue >=  0)
					{
						return dataValue/10;
					}
					
				}
				
			}
			
		 }
		 
		 //31212����
		 dataValue   =   -1;
		 
	 }
	 else if (Protocol == 61 || Protocol == 62)
	 {
		 
		 // WriteToLog("\r\n6162Э�鿪ʼ����\r\n");
		 
		 //61,62Э��
		 if (Protocol == 62)
		 {
			 
			 //62Э��,���ݵ����ٴ���,����10�Ⱥ�5�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
			 for(index = 0; index < 45 ;index ++)
			 {
				 
				 //��ƥ��ϵ�����
				 m_ppvalue = m_ppresult[m_pipeiplace*m_ByteRecords + 2*index] + m_ppresult[m_pipeiplace*m_ByteRecords + 2*index + 1]; 
				 
				 //��0��1
				 if(m_ppvalue  > 0)
				 {
					 SignalBit[index] = 0;
				 }
				 else 
				 {
					 SignalBit[index] = 1;
				 } 
				 
			 }
			 
		 }
		 
		 //����˳�����
		 for(int  i = 0; i <  45; i ++)
		 {
			 //45,27,3
			 if( i < 18 )
			 {
				 TempSignalBit[i]    = SignalBit[17 - i];
			 }
			 else
			 {
				 TempSignalBit[i]    = SignalBit[44 - i + 18];
			 }
			 
		 }	
		 
		 dataValue  =   -1;

		 
		 //���յ���������,45273
		 if(DecodeBCH45273(TempSignalBit))//����ԵĻ�
		 {
			 //��10-30Ϊ����λ��->�߷�չ���ص���Ϊ16����
			 //����  0��30A
			 //��ѹ  0��300V
			 //�͵�ɹ�0x32
			 //������ 21ȫΪ1(111111111111111111111)�������������λΪ********************0
			 //פ��û��פ����  (000000000000000000001)  20��0 + 1
			 //WriteToLog("����ɹ�");
			 
			 //6162Э��,����ԭ������
			 for(int i = 0; i <  45; i ++)
			 {
				 
				 //45,27,3
				 if( i < 18 )
				 {
					 SignalBit[i]    =  TempSignalBit[17 - i];
				 }
				 else
				 {
					 SignalBit[i]    =  TempSignalBit[44 - i + 18];
				 }
				 
			 }
			
			 //16����
			 dataValue = 0.00;
			 
			 for( i = 0; i < 21; i++)
			 {
				 dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
			 }		
			 
			 m_sums     =      0;
			 
			 //7λһ�����
			 for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			 {
				 
				 //����λ����ֽ�,7λһ����� 
				 for( i = 0;i < 7; i ++)
				 {  	
					 
					 m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow(2,6-i));
					 
				 }
				 
			 }
			 
			 //�������ͶԵĻ�
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
			
				 //45273����
				 if(dataValue >= 0)
				 {
					 //��ȷ�Ļ�
					 Beep(5000,400); 
					 return dataValue/10;
				 }
				 
			 }
			 else
			 {
				 //����Ͳ���
				 str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				 WriteToLog(str);
				 return       -1;
			 }

			 /*
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
				 
				 //���ֵ
				 for( i = 0; i < 21; i++)
				 {
					 dataValue = dataValue + double(SignalBit[18 + i]*pow(2,20-i));
				 }	
				 
				 if(SignalBit[38] == 1)
				 {
					 
					 //���ͨѶ����,ֻ��485����е��ͨѶ����
					 if(ModuleNum%100 >= 12 && long(dataValue)==2097151)
					 {
						 //��ȷ�Ļ�
                 		 Beep(5000,400); 
						 //���ͨѶ����
						 return  -2;			
					 }
					 
					 //פ��û��פ����,פ��ָ�����λΪ0
					 if(long(dataValue)== 1 && (Item%2==0) )
					 {
						 //פ��û��פ����
						 return  -4;			
					 }	
					 
					 //���λΪ�����
					 dataValue       =   -1;
					 
				 }
				 else
				 {
					 
					 //������ڵ���0
					 if(dataValue >= 0)
					 {
						 
						 //��������2λС��
						 if(Item==0x07 ||  Item==0x06 )
						 {
							 
							 //���ֵΪ100*1000
							 if(dataValue <= 1000)
							 {
								 return dataValue/1000;
							 }
							 else
							 {
								 dataValue  =      -1;
							 }
							 
						 }
						 else
						 {
							 //����,���ֵΪ0��30,��ѹ,���ֵΪ0��300,���������ѹ����һ���� ,ÿ��7���ֽڣ�ABC��7λ������*0.2����ѹ��*2
							 if(Item == 0x08 || Item == 0x09 || Item == 0x0B || Item == 0x0A) 
							 {								
								 return dataValue;
							 }
							 
						 }
						 
						 if(dataValue >= 0)
						 {
							 //����10
							 return dataValue/10;
						 }
						 
						 
					 }
					 
					 
				 }
				 
				 
			 }
			 */
			 
			 //����Ͳ���
			 dataValue =  -1;
			 
			 str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
			 WriteToLog(str);
		}
			
			
	 }
	 else
	 {
			 
		 //˳������������31��32��71��72Э��Ļ�
		 for(int i = 0; i <  63; i ++)
		 {
			 
			 if( i < 24 )
			 {
				 TempSignalBit[i]    =  SignalBit[23 - i];
			 }
			 else
			 {
				 TempSignalBit[i]    =  SignalBit[62 - i + 24];
			 }
			 
		 }	
		 
		 //	Sleep(100);
		 //	WriteToLog("���뿪ʼ");
		 dataValue = -1;
		 
		 //���յ���������,63394
		 if(DecodeBCH63394(TempSignalBit))
		 {
			 
			 dataValue    =  0;
			 
			 for( i = 0; i < 39; i++)
			 {
				 //�����ֵ�����
				 Data[i] = TempSignalBit[62 - i];
			 }	
			 
			 //�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û�����ã� "���ͨѶ����"
			 //�ص�ֵΪAAAAAA.AA,��չģ��ı�û�����ã�           "������2"
			 m_sums      =      0;
			 
			 //����λ����ֽ� 
			 for( i = 0;i < 8; i ++)
			 {
				 
				 Signal[i] = Data[i * 4] * 8 + Data[i * 4 + 1] * 4 + Data[i * 4 + 2] * 2 + Data[i * 4 + 3] ;
				 dataValue = dataValue + Signal[i] * 100000.00/pow(10,i);
				 
				 //�����
				 if((i + 1)%2 != 0)
				 {
					 m_sums  = m_sums  + Signal[i]*16;//��λ��ǰ
				 }
				 else
				 {		
					 m_sums = m_sums  + Signal[i];   //��λ�ں�
				 }
				 
			 }	
			 
			 if(Signal[0] == 0x0f && Signal[1] == 0x0e && Signal[2] == 0x0f && Signal[3] == 0x0e && Signal[4] == 0x0f && Signal[5] == 0x0e && Signal[6] == 0x0f && Signal[7] == 0x0e && (ModuleNum%100 >= 12))
			 {	 
				 //��ȷ�Ļ�
                 Beep(5000,400); 
				 //ֻ��485����е�����,485���ͨѶ����
				 return  -2;			
			 }
			 else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
			 {
				 //��ȷ�Ļ�
                 Beep(5000,400); 
				 //ֻ��485����е�����,������2
				 return  -3;
			 }
			 else if(Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			 {
				 //��ȷ�Ļ�
                 Beep(5000,400); 
				 //��פ��ʱģ��û���յ���פ������ص���
				 return  -4;
			 }	
			 else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			 {   
				 
				 //�����
				 if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
				 {
					 
					 //485��Ϊ0������
					 if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
					 {
						 return  -2;
					 }					 
					 
					 //��ȷ�Ļ�
                     Beep(5000,400);

					 return  dataValue;
					 
				 }
				 
				 return   -1;
				 
			 }
			 
			 return   -1;
			 
		 }
		 
	 }
	 
	 return dataValue;
}

//�ҹ�0���λ��,��10����,��һ��Ϊ���Ļ�,��5����,��5����,k����
int CTTTView::FindZeroPoint(short m_CollectData[], int m_StartPlace, int k)
{	
	/*
	int m_ZheSums    =  0;//���ĸ���
	int m_FuSums     =  0;//���ĸ���
	int m_dots       = -1;//ǰ���
	int m_Fvalue     =  0;
    int m_Zvalue     =  0;
	int m_AddByOrder =  0;
	m_ZheSums        =  0;//���ĸ���
	m_FuSums         =  0;//���ĸ���

	
	for(int i = m_StartPlace; i < m_StartPlace + k; i ++)
	{	
	
		//����,��-��+����		
		if(m_CollectData[i] < 0)
		{
			
			//�������
			m_FuSums ++;
			
			if(i < (m_StartPlace + k/2))
			{
				
				//����ֵ���
				m_Fvalue = m_Fvalue + m_CollectData[i];
				
			}
			
		}
		else
		{
			
			//�������
			m_ZheSums ++;
			
			if(i >= (m_StartPlace + k/2))
			{
				
				//����ֵ���
				m_Zvalue = m_Zvalue + m_CollectData[i];
				
			}
			
		}	
		
    }	

	//���������������
	if(((m_ZheSums == m_FuSums) || (m_ZheSums == (m_FuSums + 2)))  && (m_Zvalue*m_Fvalue) < 0  && (m_FuSums > 0))
	{
		m_dots = m_StartPlace + k/2 + 1;
	}
	*/


	int m_ZheSums     =  0;//���ĸ���
	int m_FuSums      =  0;//���ĸ���
	int m_dots        = -1;//ǰ���

	for(int i = m_StartPlace; i < m_StartPlace + k; i ++)
	{	
	
		//����,��-��+����		
		if(m_CollectData[i] < 0)
		{
			//�������
			m_FuSums ++;
		}
		else
		{
			//�������
			m_ZheSums ++;
		}		
    
	}	

	//���������������
	if((abs(m_ZheSums - m_FuSums) <= 2) && (m_ZheSums > 0))
	{
		m_dots = m_StartPlace + k/2 + 1;
	}

	return  m_dots;
}

//�ɼ���ͨ������Լ���
double CTTTView::CorrelationSixChannelCheck(long SourceArray[], long DestArray[], int K)
{
    double           A,B,C,Pxy,sums;
	int                           i;
   	A = B = C = Pxy = sums = 0.000;
	
	for(i = 0; i < K;i ++)
	{
		A += SourceArray[i]*DestArray[i];
        B += SourceArray[i]*SourceArray[i];
        C += DestArray[i]  *DestArray[i];
	}

	if(B*C == 0)
	{
		return 0;
	}

	Pxy = A/sqrt(B*C);
	return Pxy;
}


//ȫ�����������������,�ɼ���ͨ��
void CTTTView::ReadSixChannelMeter()
{
    WriteToLog("[�ǽǶ���]");

	//ѭ������   
	int     HalfCount  =     0;
	CString                str;
    BOOLEAN bHalfReady = FALSE;
	BOOLEAN   bStopped = FALSE;
    U32                  count;
	DataLen            =     0; 
    memset(ReadBuff,0,1024);
	int         DataValues = 0;
	int         m_order    = 0;	
	int m_YanShiMillSecond = 0;//��ʱ
    m_Stopping             = FALSE;
	CTime                timet;

    CWnd* pt    =    GetDlgItem(IDC_ORDER);
    pt->GetWindowText(str);

	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		pt    =    GetDlgItem(IDC_REAL_START);
		pt->EnableWindow(TRUE);
		MessageBox("�����ֲ���Ϊ�գ�","",MB_OK|MB_ICONWARNING);
		return;
	}
    
	if(str.GetLength() > 1)
	{
		m_order = GetHexValue(str.GetAt(0))*16 + GetHexValue(str.GetAt(1));
	}
	else
	{
		m_order = GetHexValue(str.GetAt(0));
	}

	pt= GetDlgItem(IDC_PROTOCOLS);
	pt->EnableWindow(FALSE);
	pt= GetDlgItem(IDC_ORDERCOMBO);
	pt->EnableWindow(FALSE);

	pt = GetDlgItem(IDC_REAL_START);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SEND);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SETTIMER);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_DECODE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_RADIO_REALTIME);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_COMSET);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_SENDALLONE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_BUTTON_ANGLE);
	pt->EnableWindow(FALSE);
	pt = GetDlgItem(IDC_REALSTOP);
	pt->EnableWindow(TRUE);
	
	//add 20061218
	long time11  = GetTickCount();

	//������
	SendOrderToSCM(m_module/*ģ���*/,0/*�����ֵ�վ��*/,m_generatrix/*ĸ��*/,m_iChSelect + 1/*�ߺ�*/,m_phase/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,m_order/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/);

	unsigned short *ai_buf=NULL;
	
	//��ʼ�ɼ�����
	memset(DataBuf,0,800000);
	memset(ReadBuff,0,1024);
	
	//˫����ģʽ
	err = AI_AsyncDblBufferMode(card, 1); 	
	
	if(err != 0)
	{
		//Beep(300,400);
		//Beep(300,400);
	}

	/*	
	err = AI_AsyncDblBufferMode(card, 0); 	

    //�ⴥ��״̬
	err = AI_9111_Config(card,TRIG_EXT_STROBE,0,0);//1024 512
	
	if (err !=  0) 
	{  
		//Beep(300,400);
		//Beep(300,400);
	}

	//�ɼ�8ͨ�������� 0-A����� 1��B����� 2��C����� 3-A���ѹ 4��B���ѹ 5��C���ѹ
	err = AI_ContScanChannels(card,5,AD_B_10_V,ai_buf,512,(F64)100000,SYNCH_OP);//ASYNCH_OP ASYNCH_OP SYNCH_OP

	//U16 analog_input[1];
	//AI_ReadChannel(card,0, AD_B_10_V, &analog_input[0]);

	long time22  = GetTickCount();
	str.Format("ʱ���:%d",time22 - time11);
	WriteToLog(str);
	//add 20061218
    */

	//�Բ�ģʽTRIG_INT_PACER
	err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		//Beep(300,400);
		//Beep(300,400);
	}
	

	//��Э�����ʱ����
	switch(m_protocol)
	{
	case 22:
		{
			m_YanShiMillSecond =  31*2*20*2;//2480  //��ʱ����  124
			break;
		}
	case 31:
		{
			
		}			
	case 71:
		{				
			m_YanShiMillSecond =  64*2*20;//2560  //��ʱ����   127
			break;
		}	
	case 32:
		{
			
		}
	case 72:
		{				
			m_YanShiMillSecond = 64*2*20*2;//5040  //��ʱ����  127*2 + 1
			break;
		}
	case 73:
		{				
			m_YanShiMillSecond = 64*2*20*3;//5040  //��ʱ����  127*3 + 1
			break;
		}
	case 33:
		{
			
		}
   case 61:
	   {
		   m_YanShiMillSecond =  45*2*20; //1800   //��ʱ����   89
		   break;
	   }
   case 62:
	   {
		   m_YanShiMillSecond =  45*2*20*2;//3600  //��ʱ����  89*2+1
		   break;
	   }
	}
	
	//��ʱ����
	m_YanShiMillSecond = m_YanShiMillSecond + m_millondseconds;

	timet = CTime::GetCurrentTime();	
	//str.Format("��ʼ���� "",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	//WriteToLog(str);

	str.Format("����Э��:%d,��ʱ:%d���� %4d-%02d-%02d %02d:%02d:%02d",m_protocol,m_YanShiMillSecond,timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	WriteToLog(str);

	bClearOp     =              FALSE;
	
	LARGE_INTEGER               litmp;
	LONGLONG                  qt1,qt2;
	double                dft,dff,dfm;
	QueryPerformanceFrequency(&litmp);//���ʱ��Ƶ��
	dff =      (double)litmp.QuadPart;

	QueryPerformanceCounter(&litmp);  //��ó�ʼֵ
	qt1 =              litmp.QuadPart;
	
	while(1)
	{	
		QueryPerformanceCounter(&litmp);//�����ֵֹ
		qt2 =      litmp.QuadPart;
		dfm = (double)(qt2 - qt1);
		dft =    dfm*1000.000/dff;//��ö�Ӧ��ʱ��ֵ
		
		if(m_Stopping)
		{
			break;
		}
		else
		{
			
			if((m_YanShiMillSecond - int(dft)) >= 200)
			{
				SurrenderWindowMessage();
				Sleep(200);
				SurrenderWindowMessage();
			}
			else
			{
				
				if((m_YanShiMillSecond - int(dft) - 20) <= 0)
				{
					break;
				}
				
			}
			
		}
		
	}	



	CTime time0  = CTime::GetCurrentTime();
	
	//�ɼ�ABC���������ѹ6��ͨ��
	err = AI_ContScanChannels(card,5, AD_B_10_V,ai_buf,2048,(F64)100000, ASYNCH_OP);

	if (err !=   0) 
	{  
		//	Beep(300,400);
		//	Beep(300,400);
	}

	do
	{
		do
		{
			//����
			AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
			
			
			CTimeSpan ts    = CTime::GetCurrentTime() - time0;
			
			if(m_protocol != 22)
			{
				
				//�������22Э��
				if(ts.GetTotalSeconds() > (m_protocol%10)*11 || m_Stopping)
				{
					
					bClearOp = TRUE;
					
				}
				
			}
			else
			{	
				//�����22Э��
				if(ts.GetTotalSeconds() > 10 || m_Stopping)
				{
					
					bClearOp = TRUE;
					
				}
				
			}
			
		} while (!bHalfReady && !bClearOp);
		
		if(m_Stopping)
		{
			bClearOp = TRUE;
		}
		
		if(!bClearOp) 
		{
			
			//���Ͱ�������
			AI_AsyncDblBufferTransfer(card, ReadBuff);
			
			bHalfReady = FALSE;
			
			for(int i = 0; i < 1024; i++)
			{	
				
				ReadBuff[i] = ReadBuff[i]/16;
				
				//����2048Ϊ����
				if(ReadBuff[i] >= 2048)
				{
					DataBuf[DataLen++] =  -(4096 - ReadBuff[i]);
				}
				else
				{
					DataBuf[DataLen++] =   ReadBuff[i];
				}
				
			}
			
			SurrenderWindowMessage();
			
			if(m_Stopping)
			{
				bClearOp = TRUE;
			}
			
			CTimeSpan ts    = CTime::GetCurrentTime() - time0;
			
			//ʱ�����
			switch(m_protocol)
			{
			case 22:
				{
					//(5 + 31*4*2)*2048 = 518144  ��ǰ�ɼ�
					if(DataLen >= 518144)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 31:
				{
					
				}
			case 32:
				{
					
				}
			case 71:
				{
					
				}
			case 72:
				{
					
					
				}
			case 73:
				{
					//(5 + 63*4)*2048 = 526336   ��ǰ�ɼ�
					if(DataLen >= 526336)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 61:
				{
					//(5 + 45*4)*2048 = 378880    ��ǰ�ɼ�
					if(DataLen >= 378880)
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			case 62:
				{
					//(5 + 2*45*4)*2048 = 747520   ��ǰ�ɼ�
					if(DataLen >= 747520 )
					{	
						bClearOp = TRUE;
					}
					
					break;
				}
			}				
			
			if(m_protocol != 22)
			{
				//�������22Э��
				if(ts.GetTotalSeconds() > (m_protocol%10)*11 || m_Stopping)
				{
					bClearOp = TRUE;
					break;
				}
			}
			else
			{	
				//�����22Э��
				if(ts.GetTotalSeconds() > 10 || m_Stopping)
				{
					bClearOp = TRUE;
					break;
				}
			}
			
		  }
			
			
        }while (!bClearOp && !bStopped);
		
		AI_AsyncClear(card, &count);
	
	  //  long time33  = GetTickCount();;
	  //  str.Format("ʱ���:%d",time33 - time22);
	  //  WriteToLog(str);

		//ʱ��
		timet = CTime::GetCurrentTime();	
		str.Format("��ʼ���� %4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	    WriteToLog(str);
		
		//����ֵ
		double GetValue  = DecodeSixChannel(m_module,m_protocol,m_phase,m_phase);
		
		if(GetValue >= 0)//����
		{	 
			//��ȷ�Ļ�
         //  Beep(5000,400); 
			m_SuccessTimes  = m_SuccessTimes + 1;
			m_data.Format("%.2f",GetValue);//
		}
		else
		{
			m_data = "NULL";
		}

		
		m_TotalTimes  = m_TotalTimes  + 1;
		
		CEdit * ptt = (CEdit *)GetDlgItem(IDC_DATAVALUE);
		ptt->SetWindowText(m_data);
		ptt        =  (CEdit *)GetDlgItem(IDC_RECEIVE);
		ptt->SetWindowText(m_ReceiveStr);
		
		CWnd* pts   = GetDlgItem(IDC_REAL_START);
		pts->EnableWindow(TRUE);
		pt= GetDlgItem(IDC_PROTOCOLS);
	    pt->EnableWindow(TRUE);	
		pt= GetDlgItem(IDC_ORDERCOMBO);
	    pt->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SEND);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SETTIMER);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_DECODE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_RADIO_REALTIME);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_COMSET);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_SENDALLONE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_BUTTON_ANGLE);
		pts->EnableWindow(TRUE);
		pts = GetDlgItem(IDC_REALSTOP);
		pts->EnableWindow(FALSE);
	
		//�Ļ��ⴥ��״̬
	    err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);

}

void CTTTView::SurrenderWindowMessage()
{	
	MSG message;
	
	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

}

//��ʼ��orderָ��
void CTTTView::InitOrderCombo(short m_protcols)
{

	CString                 str;
	m_ordercombo.ResetContent();
	
	if(m_protcols/10 == 3 || m_protcols/10 == 7)
	{
		m_ordercombo.AddString("02-���й����");
		m_ordercombo.AddString("06-���޹����");
		m_ordercombo.AddString("1C-A�����");
		m_ordercombo.AddString("1E-B�����");
		m_ordercombo.AddString("20-C�����");
		m_ordercombo.AddString("16-A���ѹ");
		m_ordercombo.AddString("18-B���ѹ");
		m_ordercombo.AddString("1A-C���ѹ");
		m_ordercombo.AddString("58-������");
		m_ordercombo.AddString("5A-�����");
		m_ordercombo.AddString("5C-ƽ����");
		m_ordercombo.AddString("5E-�ȵ���");
		m_ordercombo.AddString("38-��������");

		m_ordercombo.AddString("82-�������й����");
		m_ordercombo.AddString("86-�������޹����");	
		m_ordercombo.AddString("9C-����A�����");
		m_ordercombo.AddString("9E-����B�����");
		m_ordercombo.AddString("A0-����C�����");
		m_ordercombo.AddString("96-����A���ѹ");
		m_ordercombo.AddString("98-����B���ѹ");
		m_ordercombo.AddString("9A-����C���ѹ");	
		m_ordercombo.AddString("D8-���������");
		m_ordercombo.AddString("DA-��������");
		m_ordercombo.AddString("DC-����ƽ����");
		m_ordercombo.AddString("DE-����ȵ���");
		m_ordercombo.AddString("B8-���Ṧ������");		
		
	}
	else  if(m_protcols/10 == 6)
	{
		
		m_ordercombo.AddString("1F-���й����");
		m_ordercombo.AddString("1D-���޹����");
		m_ordercombo.AddString("09-�������");
		m_ordercombo.AddString("0B-�����ѹ");
		m_ordercombo.AddString("13-������");
		m_ordercombo.AddString("11-�����");
		m_ordercombo.AddString("0F-ƽ����");
		m_ordercombo.AddString("0D-�ȵ���");
		m_ordercombo.AddString("07-��������");
		m_ordercombo.AddString("02-ͣ�����");
		
		m_ordercombo.AddString("1E-�������й����");
		m_ordercombo.AddString("1C-�������޹����");
		m_ordercombo.AddString("08-�����������");
		m_ordercombo.AddString("0A-���������ѹ");
		m_ordercombo.AddString("12-���������");
		m_ordercombo.AddString("10-��������");	
		m_ordercombo.AddString("0E-����ƽ����");	
		m_ordercombo.AddString("0C-����ȵ���");		
		m_ordercombo.AddString("06-���Ṧ������");
		
		
	}
	else
	{
		
		m_ordercombo.AddString("5F-�й����");
		m_ordercombo.AddString("5D-�޹����");	
		m_ordercombo.AddString("69-A�����");
		m_ordercombo.AddString("67-B�����");
		m_ordercombo.AddString("65-C�����");	
		m_ordercombo.AddString("6F-A���ѹ");
		m_ordercombo.AddString("6D-B���ѹ");
		m_ordercombo.AddString("6B-C���ѹ");
		m_ordercombo.AddString("53-������");
		m_ordercombo.AddString("51-�����");
		m_ordercombo.AddString("4F-ƽ����");
		m_ordercombo.AddString("4D-�ȵ���");
		m_ordercombo.AddString("63-��������");

		m_ordercombo.AddString("5E-�������й����");	
		m_ordercombo.AddString("5C-�������޹����");
		m_ordercombo.AddString("68-����A�����");
		m_ordercombo.AddString("66-����B�����");
		m_ordercombo.AddString("64-����C�����");
		m_ordercombo.AddString("6E-����A���ѹ");
		m_ordercombo.AddString("6C-����B���ѹ");
		m_ordercombo.AddString("6A-����C���ѹ");	
		m_ordercombo.AddString("52-���������");
		m_ordercombo.AddString("50-��������");
		m_ordercombo.AddString("4E-����ƽ����");
	    m_ordercombo.AddString("4C-����ȵ���");	
	    m_ordercombo.AddString("62-���Ṧ������");
		
	}

	m_ordercombo.SetCurSel(0);

}

void CTTTView::OnSelchangeOrdercombo() 
{
	
	CString   str;

	if(m_ordercombo.GetCount() >= 0)
	{
		m_ordercombo.GetLBText(m_ordercombo.GetCurSel(),str);
		str = str.Left(2);

		GetDlgItem(IDC_ORDER)->SetWindowText(str);
	}
	
}

void CTTTView::OnButton1() 
{

	BOOL     m_AutoRecordAvi = FALSE;
	CString         m_parameter[95];
	CString  EightPlaceDirectionName[4];
	EightPlaceDirectionName[0] = "0";
	EightPlaceDirectionName[1] = "1";
	EightPlaceDirectionName[2] = "2";
	EightPlaceDirectionName[3] = "3";
	CString                  AVIFILE;
	AVIFILE = "1_H00_0105205128.264";
//	m_parameter[90] =  "F:\\������\\dvplay\\Ҫ�ĵ����ݿ��ʽ��Ҫ��\\Ҫ�ĵ����ݿ��ʽ��Ҫ��\\Police.mdb";
	m_parameter[90] =  "F:\\data";

	m_parameter[14] =  "��ӽ�1��";
	m_parameter[15] =  "��ӽ�2��";
//	AfxGetModuleState()->m_dwVersion   =   0x0601;//ָ���汾  

//	AfxGetModuleState()->m_dwVersion=0x0601;   
 // AfxDaoInit();   

	/*
 
	CDaoDatabase   db;   
	CString   strConnect(   _T(   ";pwd="   ));   
	strConnect   =   strConnect   +   szDBPws;   
	db.Open(   szDBFileName   ,   TRUE,   FALSE,strConnect);   
	AfxDaoTerm();//�ر����ݿ�ǰ����Ҫ�ú���   
	db.Close();
	*/

	int       m_channel      =        0;

	CString               m_filename;
	CFileFind                  fFind;
    CString               str,SqlCmd;
	long               m_Records = 0;
	BOOL         m_Successed = FALSE;
	CDaoDatabase                  db;//���ݿ�
	CDaoRecordset        RecSet(&db);//��¼��
	COleVariant                  var;//�ֶ�����
	var.ChangeType(VT_I4, NULL);
	CString               m_fangxian;
	CString          m_DataTableName;
	CTime m_StartTime  =  CTime::GetCurrentTime();
	BOOL  m_IsExist    =  FALSE;

	if(m_AutoRecordAvi)
	{
		m_DataTableName.Format("%4d%02d%02dBR",m_StartTime.GetYear(),m_StartTime.GetMonth(),m_StartTime.GetDay());
	}
	else
	{
		m_DataTableName.Format("%4d%02d%02dOT",m_StartTime.GetYear(),m_StartTime.GetMonth(),m_StartTime.GetDay());
	}

	//����ļ�Ŀ¼�ǿ�
	if(m_parameter[90].IsEmpty())
	{
		m_parameter[90] = "C:\\DATA";
	}
	
	/*
	//�����Ŀ¼������
	if(!FolderExist(m_parameter[90]))
	{
		//�����ھͽ������Ŀ¼
		if(!CreateFolder(m_parameter[90]))
		{
		//	SetResultStr(m_parameter[90] + "Ŀ¼����ʧ�ܣ�");
			//MessageBox(m_parameter[90] + "Ŀ¼����ʧ�ܣ�","",MB_OK|MB_ICONWARNING);
			return FALSE;
		}
		
	}
	*/

	//�����̵Ƶ����ݿ��¼
	m_filename.Format("%s\\%s",m_parameter[90],"Police.mdb");
	m_Successed         =  fFind.FindFile(m_filename);
	fFind.Close();
	
	if(!m_Successed)
	{
	//	SetResultStr("���̵������ļ�" + m_filename + "�Ҳ�����");
	//	return FALSE;
	}    
	
	m_Successed  = FALSE;


	try
	{

//		AfxMessageBox(m_filename);
		
		// ���Ѵ��������ݿ⼰��
		//db.Open(m_filename);
        db.Open(m_filename);//,FALSE,FALSE,_T("")
		
		//����Ӧ�ı��Ƿ����
		SqlCmd.Format("SELECT * FROM %s",m_DataTableName);
		
		TRY
		{
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,0);
			//�ر����ݿ�
			RecSet.Close( );
			m_IsExist = TRUE;
		}
		CATCH_ALL(e)
		{ 
			//�ر����ݿ�
			//RecSet.Close( );
			e->Delete();
			m_IsExist = FALSE;
		}
		END_CATCH_ALL;

        //�����ڴ˱�����
		if(!m_IsExist)
		{
			
			if(m_AutoRecordAvi)
			{
				SqlCmd.Format("SELECT * INTO %s FROM ����Ƽ�¼ WHERE 1<>1",m_DataTableName);
			}
			else
			{
				SqlCmd.Format("SELECT * INTO %s FROM ����Υ�¼�¼ WHERE 1<>1",m_DataTableName);
			}
			
			//����SQL���
			db.Execute(SqlCmd);
		}

		if(m_AutoRecordAvi)
		{
			SqlCmd.Format("SELECT COUNT(*)  FROM %s",m_DataTableName);
		}
		else
		{
			SqlCmd.Format("SELECT COUNT(*)  FROM %s",m_DataTableName);
		}

		if(RecSet.IsOpen())
		{
			RecSet.Close();
		}

		//���Ѵ��������ݱ�                                  
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd, 0);
		RecSet.GetFieldValue((int)0,var);  
		m_Records = var.lVal;
		RecSet.Close();
		
		COleDateTime m_Current = COleDateTime::GetCurrentTime();

		//���̵�
		if(m_AutoRecordAvi)
		{
			switch(atoi(EightPlaceDirectionName[m_channel]))
			{
			case 0:
				{
					m_fangxian="��";
					break;
				}
			case 1:
				{
					m_fangxian="��";
					break;
				}
			case 2:
				{
					m_fangxian="��";
					break;
				}
			case 3:
				{
					m_fangxian="��";
					break;
				}
			}

			//ԭ��û�м�¼
			SqlCmd.Format("INSERT INTO %s(���,ʱ��,·��,·��,����,[��ƺ�ʱ��(��)],¼��,��ע) VALUES (%d,'%s','%s','%d','%s',%d,'%s','%s')",m_DataTableName,m_Records + 1,m_Current.Format(),m_parameter[14 + 2*m_channel].Left(20),m_channel,m_fangxian,3,AVIFILE,"�����");
		}
		else
		{
			/*
			switch(m_RealDirection[m_channel])
			{
			case 0:
				{
					m_fangxian="��";
					break;
				}
			case 1:
				{
					m_fangxian="��";
					break;
				}
			case 2:
				{
					m_fangxian="��";
					break;
				}
			case 3:
				{
					m_fangxian="��";
					break;
				}
			}
			*/

			//ԭ��û�м�¼
			SqlCmd.Format("INSERT INTO %s(���,����,ʱ��,�ص�,Υ�����,¼��,��ע) VALUES (%d,'%s','%s','%s','%s','%s','%s')",m_DataTableName,m_Records + 1,m_Current.Format(),m_Current.Format(),m_parameter[14 + 2*m_channel].Left(20),"����Υ��",AVIFILE,"����Υ��");
		}
		
		try
		{
			AfxMessageBox(SqlCmd);

			//�����¼����SQL���,97�ֶ�
			db.Execute(SqlCmd);
			m_Successed = TRUE;
			
		}
		catch(CDaoException* e)
		{
			e->Delete();
			m_Successed = FALSE;
		}
		
		//�رռ�¼������
		db.Close();

	}
	catch(CDaoException* e)
	{
		db.Close();
		e->Delete();
		m_Successed = FALSE;
	}	
	
	if(!m_Successed)
	{
		
		if(m_AutoRecordAvi)
		{
			
			AfxMessageBox("����Ƽ�¼���ݱ���ʧ��!!");
			//	SetResultStr("<<����Ƽ�¼���ݱ���ʧ��>>");
		}
		else
		{
			AfxMessageBox("����Υ�����ݱ���ʧ��!!");
			//	SetResultStr("<<����Υ�����ݱ���ʧ��>>");
		}
		
	}
	else
	{
        if(m_AutoRecordAvi)
		{
			
			AfxMessageBox("����Ƽ�¼���ݱ���ɹ�!!");
		}
		else
		{
			AfxMessageBox("����Υ�����ݱ���ɹ�!!");
		}
		
	}

 //   return   m_Successed;
 //}	
}
