// IFRMView.cpp : implementation of the CIFRMView class
//

#include "stdafx.h"
#pragma warning(disable : 4244)
#pragma warning(disable : 4258)
#pragma warning(disable : 4995)
#pragma warning(disable : 4996)


#include "MainFrm.h"
#include "IFRMView.h"
#include "Dask.h"
#include "math.h"
#include <comdef.h>
#include "Winbase.h"
#include "CRC.H"
#include "DataBaseInstance.h"
#include "RuntimeAccount.h"
#include "AppInfo.h"

//#include "AmetterRecordset.h"
#include "AmetterRecordset.h"
#include "CHANGEAMMETERset.h"

#include "BreadSettingDlg.h"
#include "SearchDlg.h"
#include "TransformerDlg.h"
#include "AmetterDlg.h"
#include "UserInfoDlg.h"
#include "LineLossDlg.h"
#include "DataInformationDlg.h"
#include "PassWordDlg.h"
#include "GarrisonDlg.h"
#include "ChartDlg.h"
#include "StationCommunDlg.h"
#include "ELKindDlg.h"
#include "SelectTableDlg.h"
#include "AngleSettingDlg.h"
#include "CondtionsDlg.h"
#include "PhaseTestDlg.h"
#include "TimeCheckDlg.h"
#include "ShowInfoDlg.h"
#include "AutoDateReadModuleDlg.h"
#include "TimeSelectDlg.h"
#include "ELECTDEALDlg.h"
#include "ProgressDlg.h"
#include "ZHULIUTIMESELECTDlg.h"
#include "CHANGEAMMETERDLG.h"
#include "Protcoldlg.h"
#include "TestCommDlg.h"
#include "WuGongDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFRMView
//short           DataBuf[190000];
short           DataBuf[800000];
short       	m_TestCurrent[140000];//����
short           m_TestVoltage[140000];//��ѹ
int             m_TestParameter[6];
int                     DataLen;
I16                        card;
BOOL                   bClearOp;
unsigned short   ReadBuff[1024];
I16                         err;
BOOLEAN       bStopped =  FALSE;
CWinThread     *ReadMeterThread;

IMPLEMENT_DYNCREATE(CIFRMView, CFormView)

BEGIN_MESSAGE_MAP(CIFRMView, CFormView)
//{{AFX_MSG_MAP(CIFRMView)
ON_WM_DESTROY()
ON_WM_SETFOCUS()
ON_WM_SIZE()



ON_COMMAND(ID_TESTREADTABLE, OnTestreadtable)
ON_COMMAND(ID_BREADORDER, OnBreadorder)
ON_COMMAND(ID_TRANFORMER, OnTranformer)
ON_COMMAND(ID_USERINFO, OnUserinfo)
ON_COMMAND(ID_AMMETERINFO, OnAmmeterinfo)
ON_COMMAND(ID_COMMUNICATION, OnCommunication)
ON_COMMAND(ID_STOPRUN, OnStoprun)
ON_WM_TIMER()
ON_COMMAND(ID_OWEMONEY, OnOwemoney)


ON_COMMAND(ID_PRICE, OnPrice)
ON_COMMAND(ID_DATAPASS, OnDatapass)
ON_UPDATE_COMMAND_UI(ID_CONNECTSUCCESS, OnUpdateConnectsuccess)
ON_COMMAND(ID_STOPEXAM, OnStopexam)
ON_COMMAND(ID_ANGLESET, OnAngleset)
ON_WM_PAINT()
ON_COMMAND(ID_PHASETEST, OnPhasetest)
ON_COMMAND(ID_TIMECHECK, OnTimecheck)
	ON_UPDATE_COMMAND_UI(ID_LST_SAVE, OnUpdateLstSave)
	ON_COMMAND(ID_AUTOREADSET, OnAutoreadset)
	ON_COMMAND(ID_BREAkSOMEDAY, OnBREAkSOMEDAY)
	ON_UPDATE_COMMAND_UI(ID_OWEMONEY, OnUpdateOwemoney)
	ON_COMMAND(ID_PASSUSERDATA, OnPassuserdata)
	ON_UPDATE_COMMAND_UI(ID_PASSUSERDATA, OnUpdatePassuserdata)
	ON_UPDATE_COMMAND_UI(ID_SHOWDIALOGBAR, OnUpdateShowdialogbar)
	ON_UPDATE_COMMAND_UI(ID_PHASETEST, OnUpdatePhasetest)
	ON_UPDATE_COMMAND_UI(ID_TESTREADTABLE, OnUpdateTestreadtable)
	ON_NOTIFY(NM_RCLICK, IDC_LISTSS, OnRclickListss)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_HIDEDATA, OnUpdateHidedata)
	ON_COMMAND(ID_SAVEREPORTAS, OnSavereportas)
	ON_UPDATE_COMMAND_UI(ID_SAVEREPORTAS, OnUpdateSavereportas)
	ON_UPDATE_COMMAND_UI(ID_REMOTEMODIFY, OnUpdateRemotemodify)
	
	
	
	ON_COMMAND(ID_GETDATAFROMLONG, OnGetdatafromlong)
	ON_COMMAND(ID_LOCALMODIFY, OnLocalmodify)
	ON_UPDATE_COMMAND_UI(ID_LOCALMODIFY, OnUpdateLocalmodify)
	ON_UPDATE_COMMAND_UI(ID_APPEARSELECTDATA, OnUpdateAppearselectdata)
	
	ON_UPDATE_COMMAND_UI(ID_BREAkSOMEDAY, OnUpdateBREAkSOMEDAY)
	
	ON_UPDATE_COMMAND_UI(ID_DELETEMODULE, OnUpdateDeletemodule)
	ON_COMMAND(ID_DELETEMODULE, OnDeletemodule)
	ON_UPDATE_COMMAND_UI(ID_ANGLESET, OnUpdateAngleset)
	ON_UPDATE_COMMAND_UI(ID_COMMUNICATION, OnUpdateCommunication)
	ON_UPDATE_COMMAND_UI(ID_DATAPASS, OnUpdateDatapass)
	ON_UPDATE_COMMAND_UI(ID_AUTOREADSET, OnUpdateAutoreadset)
	ON_UPDATE_COMMAND_UI(ID_BREADORDER, OnUpdateBreadorder)
	ON_COMMAND(ID_CLOSEREPORT, OnClosereport)
	ON_UPDATE_COMMAND_UI(ID_CLOSEREPORT, OnUpdateClosereport)
	ON_COMMAND(ID_TIMESEARCH, OnTimesearch)
	ON_COMMAND(ID_ZHULIUMODIFY, OnZhuliumodify)
	ON_COMMAND(ID_ZHENSHIMODIFY, OnZhenshimodify)
	ON_UPDATE_COMMAND_UI(ID_TIMESEARCH, OnUpdateTimesearch)
	ON_COMMAND(ID_GETFILE, OnGetfile)
	ON_UPDATE_COMMAND_UI(ID_DISCONNECT, OnUpdateDisconnect)
	ON_COMMAND(ID_CONNECTSUCCESS, OnConnectsuccess)
	ON_COMMAND(ID_STOPORSEND, OnStoporsend)
	ON_UPDATE_COMMAND_UI(ID_STOPORSEND, OnUpdateStoporsend)
	ON_UPDATE_COMMAND_UI(ID_DATAAPPEAR, OnUpdateDataappear)
	ON_UPDATE_COMMAND_UI(ID_LISTSELECT, OnUpdateListselect)
	ON_COMMAND(ID_CHECKEQAUL, OnCheckeqaul)
	ON_UPDATE_COMMAND_UI(ID_CHECKEQAUL, OnUpdateCheckeqaul)
	ON_COMMAND(ID_XIANGCHANGE, OnXiangchange)
	ON_UPDATE_COMMAND_UI(ID_XIANGCHANGE, OnUpdateXiangchange)
	ON_COMMAND(ID_CHECKLINESTATUS, OnChecklinestatus)
	ON_UPDATE_COMMAND_UI(ID_CHECKLINESTATUS, OnUpdateChecklinestatus)
	ON_COMMAND(ID_FINDREPEATRECORDS, OnFindrepeatrecords)
	ON_COMMAND(ID_FAUTOREADSET, OnFautoreadset)
	ON_UPDATE_COMMAND_UI(ID_FAUTOREADSET, OnUpdateFautoreadset)
	ON_COMMAND(ID_CANCELAUTOZHULIU, OnCancelautozhuliu)
	ON_UPDATE_COMMAND_UI(ID_CANCELAUTOZHULIU, OnUpdateCancelautozhuliu)
	ON_COMMAND(ID_CHANGEAMMETER, OnChangeammeter)
	ON_COMMAND(ID_MODIFYPROTCOL, OnModifyprotcol)
	ON_COMMAND(ID_WXCHECKSTATUS, OnWxcheckstatus)
	ON_COMMAND(ID_WUGONGPARAMETER, OnWugongparameter)
	ON_COMMAND(ID_WUGONGDEAL, OnWugongdeal)
	ON_UPDATE_COMMAND_UI(ID_WUGONGDEAL, OnUpdateWugongdeal)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_CLOSE()
	ON_COMMAND(ID_DRFROMACCESS, OnDrfromaccess)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_MESSAGE(WM_EVENT, OnEvent)
ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFRMView construction/destruction


CIFRMView::CIFRMView()
: CFormView(CIFRMView::IDD)
{
	//{{AFX_DATA_INIT(CIFRMView)
	//}}AFX_DATA_INIT
    //�������ݴ������
	m_PassErrortimes       =     0;
	//�绰�κŵı�־
	m_IsDialConnectting    = FALSE;
	//�Ƿ�������ݱ�־
	m_ReceiveOk            = FALSE;
	//DialogBar�Ƿ���ڵ��ж�
	m_DialogBarVisible     =  TRUE;

	m_ModuleFindContionStr =    "";
	m_pSelection           =  NULL;
	m_strReceiveChar       =    "";
	m_iBandPassPoints      =    62;//70����Ч��ֵ
	m_ListRows             =     0;//���Զ����к�
	m_times                =     1;
	m_iChSelect            =     0;
	m_StartRead            = FALSE;//TRUE;
	m_ZhuLiuTime           =    "";
	m_angles               =     0;
	
    Apppt = (CIFRMApp*)AfxGetApp();
	
	//������ֵ����
	m_PassValue           =      0;
	
	//�����ļ�¼����
	m_PassRecords         =      0;

	//��ʱ�������
	//����Щ��

	TmpOnlyOneThreadRun.SetEvent();		//++

	for(int i = 0; i < 15; i++)
	{
		m_SetLabel[i]      = FALSE;//�����־
        m_TimeSetLabel[i]  = FALSE;//��ʱ�����־
		Ports[i]           = FALSE;//�����Ƿ��ܹ���TRUE  ����  FALSE ������
	}
	
	m_DayOrYear[0]         =  TRUE;//�����ñ��³�
	m_DayOrYear[1]         = FALSE;//�Ǿ����ñ��쳭
	m_sendkind       =           0;// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
    //���ӱ�־
	m_IsConnect      = FALSE;
	//��ǰ���ͺ��λ��
	m_LocalAddress   =     0;
	LowAddress       =     0;
    HighAddress      =     0;
	m_EveryUnit      =     0;
	
    ReadMeterThread   =  NULL;
	
	//�����ֱ���
	m_handno         =     0;
	//�Ƿ�ʱ�����ź�
	m_status         =  TRUE;
	//���ɵĿ���
//	m_ComeIntoDataName =  "";
	//��ʱ����
	m_TimeStrs       =    "";
	//�Ƿ��Զ�����Ϣ
	m_IsAutoSending  = FALSE;
	ReceiveByteArray.RemoveAll();
	//�Զ���������
	m_AutoReadCondtionStr = "";

	/*   Ӣ���ֶ�ת�ɺ����ֶ�*/
	/**********1��������ݱ����***************
	���	����	  �ֶ�Ӣ����
	1	   �õ���	    ELECTRICITY_NO
	2	   �õ�����	    ELECTRICITY_KIND
	3      ���	        ELECTRICITY_ PRICE
	4      ��ע	        ELECTRICITY_REMARK
	********************************************/
    TB_ELECTRICITYS.SetSize(8);	
	TB_ELECTRICITYS[0] = "ELECTRICITY_NO";
	TB_ELECTRICITYS[1] = "�õ���";
	TB_ELECTRICITYS[2] = "ELECTRICITY_KIND";
	TB_ELECTRICITYS[3] = "�õ�����";
	TB_ELECTRICITYS[4] = "ELECTRICITY_PRICE";
	TB_ELECTRICITYS[5] = "���";
	TB_ELECTRICITYS[6] = "ELECTRICITY_REMARK";
	TB_ELECTRICITYS[7] = "��ע";
	/**********2����̨��Ϣ���ݱ����*************
	���	����	     �ֶ�Ӣ����
	1   	��̨���	TRANSFORMER_NO
	2   	��̨�ͺ�	TRANSFORMER_TYPE
	3   	��̨����	TRANSFORMER_CAPACITY
	4	    ��װʱ��	TRANSFORMER_INSTALLTIME
	5	    λ��	    TRANSFORMER_POSITION
	6   	����Ȩ   	TRANSFORMER_OWNERSHIP
	7	    ������ʽ   	TRANSFORMER_CONNECTFORM
	********************************************/

	TB_TRANSFORMERS.SetSize(14);
	TB_TRANSFORMERS[0]  = "TRANSFORMER_NO";
	TB_TRANSFORMERS[1]  = "��̨����";
	TB_TRANSFORMERS[2]  = "TRANSFORMER_TYPE";
	TB_TRANSFORMERS[3]  = "��̨�ͺ�";
	TB_TRANSFORMERS[4]  = "TRANSFORMER_CAPACITY";
	TB_TRANSFORMERS[5]  = "��̨����";
    TB_TRANSFORMERS[6]  = "TRANSFORMER_INSTALLTIME";
	TB_TRANSFORMERS[7]  = "��װʱ��";
	TB_TRANSFORMERS[8]  = "TRANSFORMER_POSITION";
	TB_TRANSFORMERS[9]  = "λ��";
    TB_TRANSFORMERS[10] = "TRANSFORMER_OWNERSHIP";
	TB_TRANSFORMERS[11] = "����Ȩ";
	TB_TRANSFORMERS[12] = "TRANSFORMER_CONNECTFORM";
	TB_TRANSFORMERS[13] = "������ʽ";


	/**********3�������Ϣ���ݱ����*************
	���	����	   �ֶ�Ӣ����
	1	    ������	AMMETER_NO
	2	    ��������	AMMETER_MANUFACTURER
	3    	����ͺ�	AMMETER_TYPE
	4	    ������	    AMMETER_IMPULSE
	********************************************/

	TB_AMMETERS.SetSize(8);
	TB_AMMETERS[0] = "AMMETER_TYPE";
	TB_AMMETERS[1] = "����ͺ�";
	TB_AMMETERS[2] = "AMMETER_MANUFACTURER";
	TB_AMMETERS[3] = "��������";
	TB_AMMETERS[4] = "AMMETER_IMPULSE";
	TB_AMMETERS[5] = "������";
	TB_AMMETERS[6] = "AMMETER_REMARK";
	TB_AMMETERS[7] = "��ע";

	/**********4���û���Ϣ�����ݱ����*************
	���	����          	    �ֶ�Ӣ����
	1	  ��˾���򹩵������    USER_COMPANY
	2	  ��վ���             	USER_STATIONNO
	3	  ���վ��	            USER_STATIONNAME
	4	  ��·���            	USER_LINENO
	5     ��·����            	USER_LINENAME
	6	  ��̨����	            USER_TRANSFORMERNO
	7	  ģ���            	USER_MODULENO
	8     ģ�鰲װ���	        USER_PHASE
	9	  ����	                USER_NAME
	10	  �û����	            USER_NO
	11	  ԭ�û���	            USER_OLDNO
	12	  סַ	                USER_ADDRESS
	13	  �绰	                USER_PHONE
	14	  �õ�����	            USER_ELECTRICITYKIND
	15	  �����	            USER_AMMETERNO
	16	  ����ͺ�	            USER_AMMETERTYPE
	16	  �������	            USER_AMMETERKIND
	17	  ���緽ʽ          	USER_SUPPLYMODE
	18	  ��װʱ��          	USER_INSTALLTIME
	19	  ����ֵ	            USER_INITIALVALUE
	20	  ����	                USER_MULTIPLE
	21	  �õ�����	            USER_DESCRIBE
	22	  ������־	            USER_READLABEL
	23	  �õ�״̬	            USER_ETSTATUS
	********************************************/

	TB_USERS.SetSize(70);
	TB_USERS[0]  = "USER_COMPANY";
	TB_USERS[1]  = "���������";
	TB_USERS[2]  = "USER_STATIONNO";
	TB_USERS[3]  = "��վ���";
	TB_USERS[4]  = "USER_STATIONNAME";
	TB_USERS[5]  = "���վ��";
	TB_USERS[6]  = "USER_MOTHERLINE";
    TB_USERS[7]  = "ĸ�߱��";
	TB_USERS[8]  = "USER_BAKMOTHERLINE";
    TB_USERS[9]  = "����ĸ�߱��";
	TB_USERS[10] = "USER_LINENO";
	TB_USERS[11] = "���߱��";
	TB_USERS[12] = "USER_BAKLINENO";
	TB_USERS[13] = "���ó��߱��";
	TB_USERS[14] = "USER_LINENAME";
	TB_USERS[15] = "��·����";
	TB_USERS[16] = "USER_TRANSFORMERNO";
    TB_USERS[17] = "��̨����";
	TB_USERS[18] = "USER_MODULENO";
	TB_USERS[19] = "ģ���";
	TB_USERS[20] = "USER_PHASE";
	TB_USERS[21] = "��װ���";
	TB_USERS[22] = "USER_NAME";
	TB_USERS[23] = "����";
	TB_USERS[24] = "USER_NO";
	TB_USERS[25] = "�û����";
	TB_USERS[26] = "USER_OLDNO";
	TB_USERS[27] = "ԭ�û���";
	TB_USERS[28] = "USER_ADDRESS";
	TB_USERS[29] = "סַ";
	TB_USERS[30] = "USER_PHONE";
	TB_USERS[31] = "�绰";  
	TB_USERS[32] = "USER_ELECTRICITYKIND";
	TB_USERS[33] = "�õ���";
	TB_USERS[34] = "USER_AMMETERNO";
	TB_USERS[35] = "�����";
	TB_USERS[36] = "USER_AMMETERKIND";
	TB_USERS[37] = "�������";	
	TB_USERS[38] = "USER_INSTALLTIME";
	TB_USERS[39] = "��װʱ��";
	TB_USERS[40] = "USER_SUPPLYMODE";
	TB_USERS[41] = "���緽ʽ";
	TB_USERS[42] = "USER_INITIALVALUE";
	TB_USERS[43] = "����ֵ";
	TB_USERS[44] = "USER_MULTIPLE";
	TB_USERS[45] = "����";
	TB_USERS[46] = "USER_PROTOCOL";
	TB_USERS[47] = "����Э��";
	TB_USERS[48] = "USER_DESCRIBE";
	TB_USERS[49] = "�õ�����";
	TB_USERS[50] = "USER_READLABEL";
	TB_USERS[51] = "ϵͳ�ֶ�";
	TB_USERS[52] = "USER_TIMELABEL";
	TB_USERS[53] = "ϵͳ�ֶ�";
	TB_USERS[54] = "USER_ETSTATUS";
	TB_USERS[55] = "�õ�״̬";
	TB_USERS[56] = "USER_IDNO";
	TB_USERS[57] = "ģ������";
	TB_USERS[58] = "USER_AMMETERTYPE";
	TB_USERS[59] = "����ͺ�";
	TB_USERS[60] = "USER_SENDANGLE";
	TB_USERS[61] = "�ź�ǿ��";
	TB_USERS[62] = "USER_DOWNVALUE";
	TB_USERS[63] = "�±���������";	
	TB_USERS[64] = "USER_UPVALUE";
	TB_USERS[65] = "�±���������";
	TB_USERS[66] = "USER_RUNSTATUS";
	TB_USERS[67] = "����״̬";
	TB_USERS[68] = "USER_ZHULABEL";
	TB_USERS[69] = "ϵͳ�ֶ�";

	/**********5��פ�����ݱ����*************
	���	����          	    �ֶ�Ӣ����
	1   	ģ���      	GARRISON_MODULENO
	2   	�й����    	GARRISON_WORKDEGREE
	3   	�������й���	GARRISON_WORKDEGREETOTAL
	4	    �޹����    	GARRISON_LOSEDEGREE
	5	    �������޹���	GARRISON_LOSEDEGREETOTAL
	6	    A�����	        GARRISON_ACURRENT
	7    	B�����     	GARRISON_BCURRENT
	8	    C�����     	GARRISON_CCURRENT
	9	    A���ѹ     	GARRISON_AVOLTAGE
	10   	B���ѹ	        GARRISON_BVOLTAGE
	11	    C���ѹ	        GARRISON_CVOLTAGE
	12
	13
	14
	15
	16	    ����ʱ��	    GARRISON_TRANSCRIBETIME
	17   	��ӦЭ��	    GARRISON_PROTOCOL
	18	    פ��ʱ��	    GARRISON_HALTTIME
	********************************************/

	TB_GARRISONS.SetSize(38);
	TB_GARRISONS[0]  = "GARRISON_MODULENO";
	TB_GARRISONS[1]  = "ģ���";
	TB_GARRISONS[2]  = "GARRISON_WORKDEGREE";
	TB_GARRISONS[3]  = "�й����";
    TB_GARRISONS[4]  = "GARRISON_WORKDEGREETOTAL";
	TB_GARRISONS[5]  = "�������й���";
	TB_GARRISONS[6]  = "GARRISON_LOSEDEGREE";
	TB_GARRISONS[7]  = "�޹����";
    TB_GARRISONS[8]  = "GARRISON_LOSEDEGREETOTAL";
	TB_GARRISONS[9]  = "�������޹���";
	TB_GARRISONS[10] = "GARRISON_ACURRENT";
	TB_GARRISONS[11] = "A�����";
	TB_GARRISONS[12] = "GARRISON_BCURRENT";
	TB_GARRISONS[13] = "B�����" ;
    TB_GARRISONS[14] = "GARRISON_CCURRENT";
	TB_GARRISONS[15] = "C�����";
	TB_GARRISONS[16] = "GARRISON_AVOLTAGE";
	TB_GARRISONS[17] = "A���ѹ";
	TB_GARRISONS[18] = "GARRISON_BVOLTAGE";
	TB_GARRISONS[19] = "B���ѹ";
	TB_GARRISONS[20] = "GARRISON_CVOLTAGE";
	TB_GARRISONS[21] = "C���ѹ" ;
    TB_GARRISONS[22] = "GARRISON_JFDL";
    TB_GARRISONS[23] = "������";
	TB_GARRISONS[24] = "GARRISON_FDL";
    TB_GARRISONS[25] = "�����";
	TB_GARRISONS[26] = "GARRISON_PDL";
    TB_GARRISONS[27] = "ƽ����";				   
   	TB_GARRISONS[28] = "GARRISON_GDL";
    TB_GARRISONS[29] = "�ȵ���";
	TB_GARRISONS[30] = "GARRISON_GLYS";
    TB_GARRISONS[31] = "��������";
    TB_GARRISONS[32] = "GARRISON_TRANSCRIBETIME";
	TB_GARRISONS[33] = "����ʱ��";
    TB_GARRISONS[34] = "GARRISON_PROTOCOL";
	TB_GARRISONS[35] = "��ӦЭ��";
	TB_GARRISONS[36] = "GARRISON_HALTTIME";
	TB_GARRISONS[37] = "פ��ʱ��";

	/**********6�����ݱ����*************
	���	����          	    �ֶ�Ӣ����
	1   	ģ���      	REALTIME_MODULENO
	2   	�й����    	REALTIME_WORKDEGREE
	3   	�������й���	REALTIME_WORKDEGREETOTAL
	4	    �޹����    	REALTIME_LOSEDEGREE
	5	    �������޹���	REALTIME_LOSEDEGREETOTAL
	6	    A�����	        REALTIME_ACURRENT
	7    	B�����     	REALTIME_BCURRENT
	8	    C�����     	REALTIME_CCURRENT
	9	    A���ѹ     	REALTIME_AVOLTAGE
	10   	B���ѹ	        REALTIME_BVOLTAGE
	11	    C���ѹ	        REALTIME_CVOLTAGE
	12	    ����ʱ��	    REALTIME_TRANSCRIBETIME
	13   	��ӦЭ��	    REALTIME_PROTOCOL
	********************************************/

	TB_REALTIMES.SetSize(36); 	
	TB_REALTIMES[0]  = "REALTIME_MODULENO";
	TB_REALTIMES[1]  = "ģ���";
	TB_REALTIMES[2]  = "REALTIME_WORKDEGREE";
	TB_REALTIMES[3]  = "�й����";
    TB_REALTIMES[4]  = "REALTIME_WORKDEGREETOTAL";
	TB_REALTIMES[5]  = "�������й���";
	TB_REALTIMES[6]  = "REALTIME_LOSEDEGREE";
	TB_REALTIMES[7]  = "�޹����";
    TB_REALTIMES[8]  = "REALTIME_LOSEDEGREETOTAL";
	TB_REALTIMES[9]  = "�������޹���";
	TB_REALTIMES[10] = "REALTIME_ACURRENT";
	TB_REALTIMES[11] = "A�����";
	TB_REALTIMES[12] = "REALTIME_BCURRENT";
	TB_REALTIMES[13] = "B�����";
	TB_REALTIMES[14] = "REALTIME_CCURRENT";
	TB_REALTIMES[15] = "C�����";
	TB_REALTIMES[16] = "REALTIME_AVOLTAGE";
	TB_REALTIMES[17] = "A���ѹ";
	TB_REALTIMES[18] = "REALTIME_BVOLTAGE";
	TB_REALTIMES[19] = "B���ѹ";
	TB_REALTIMES[20] = "REALTIME_CVOLTAGE";
	TB_REALTIMES[21] = "C���ѹ";
	TB_REALTIMES[22] = "REALTIME_JFDL";
    TB_REALTIMES[23] = "������";
	TB_REALTIMES[24] = "REALTIME_FDL";
    TB_REALTIMES[25] = "�����";
	TB_REALTIMES[26] = "REALTIME_PDL";
    TB_REALTIMES[27] = "ƽ����";				   
   	TB_REALTIMES[28] = "REALTIME_GDL";
    TB_REALTIMES[29] = "�ȵ���";
    TB_REALTIMES[30] = "REALTIME_GLYS";
    TB_REALTIMES[31] = "��������";
	TB_REALTIMES[32] = "REALTIME_TRANSCRIBETIME";
	TB_REALTIMES[33] = "����ʱ��";
    TB_REALTIMES[34] = "REALTIME_PROTOCOL";
	TB_REALTIMES[35] = "��ӦЭ��";

	/*
	CREATE TABLE [dbo].[TB_CHANGEAMMETER] (
	[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,
	[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,
	[CHANGEAMMETER_WORKDEGREETOTAL] [float] NULL ,
	[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,
	[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NULL ,
	[CHANGEAMMETER_JFDL] [float] NULL ,
	[CHANGEAMMETER_FDL] [float] NULL ,
	[CHANGEAMMETER_PDL] [float] NULL ,
	[CHANGEAMMETER_GDL] [float] NULL ,
	[CHANGEAMMETER_GLYS] [float] NULL ,
	[CHANGEAMMETER_UPDATETIME] [datetime] NULL ,
	[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL 
    */

	//������Ϣ
	TB_CHANGEAMMETERS.SetSize(44);
	TB_CHANGEAMMETERS[0] = "CHANGEAMMETER_MODULENOOLD";
	TB_CHANGEAMMETERS[1] = "ԭ��ģ���";
	TB_CHANGEAMMETERS[2] = "CHANGEAMMETER_MODULENO";
	TB_CHANGEAMMETERS[3] = "�½�ģ���";
	TB_CHANGEAMMETERS[4] = "CHANGEAMMETER_NOOLD";
	TB_CHANGEAMMETERS[5] = "ԭ�ӵ����";
	TB_CHANGEAMMETERS[6] = "CHANGEAMMETER_NO";
	TB_CHANGEAMMETERS[7] = "�½ӵ����";
	TB_CHANGEAMMETERS[8] = "CHANGEAMMETER_WORKDEGREEOLD";
	TB_CHANGEAMMETERS[9] = "ԭ�й���Ȳ�ֵ";
	TB_CHANGEAMMETERS[10] = "CHANGEAMMETER_WORKDEGREE";
	TB_CHANGEAMMETERS[11] = "�й����ֵ";
	TB_CHANGEAMMETERS[12] = "CHANGEAMMETER_WORKDEGREETOTALOLD";
	TB_CHANGEAMMETERS[13] = "ԭ�������й���";	
	TB_CHANGEAMMETERS[14] = "CHANGEAMMETER_WORKDEGREETOTAL";
	TB_CHANGEAMMETERS[15] = "�������ܲ�ֵ";	
	TB_CHANGEAMMETERS[16] = "CHANGEAMMETER_LOSEDEGREEOLD";
	TB_CHANGEAMMETERS[17] = "ԭ�޹����ֵ";
	TB_CHANGEAMMETERS[18] = "CHANGEAMMETER_LOSEDEGREE";
	TB_CHANGEAMMETERS[19] = "�޹���Ȳ�ֵ";
	TB_CHANGEAMMETERS[20] = "CHANGEAMMETER_LOSEDEGREETOTALOLD";
	TB_CHANGEAMMETERS[21] = "ԭ�����޹���";
	TB_CHANGEAMMETERS[22] = "CHANGEAMMETER_LOSEDEGREETOTAL";
	TB_CHANGEAMMETERS[23] = "�������ܲ�ֵ";
	TB_CHANGEAMMETERS[24] = "CHANGEAMMETER_JFDLOLD";
	TB_CHANGEAMMETERS[25] = "ԭ������ֵ";
	TB_CHANGEAMMETERS[26] = "CHANGEAMMETER_JFDL";
	TB_CHANGEAMMETERS[27] = "��������ֵ";	
	TB_CHANGEAMMETERS[28] = "CHANGEAMMETER_FDLOLD";
	TB_CHANGEAMMETERS[29] = "ԭ�����ֵ";	
	TB_CHANGEAMMETERS[30] = "CHANGEAMMETER_FDL";
	TB_CHANGEAMMETERS[31] = "�������ֵ";
	TB_CHANGEAMMETERS[32] = "CHANGEAMMETER_PDLOLD";
	TB_CHANGEAMMETERS[33] = "ԭƽ����ֵ";
	TB_CHANGEAMMETERS[34] = "CHANGEAMMETER_PDL";
	TB_CHANGEAMMETERS[35] = "ƽ������ֵ";	
	TB_CHANGEAMMETERS[36] = "CHANGEAMMETER_GDLOLD";
	TB_CHANGEAMMETERS[37] = "ԭ�ȵ���ֵ";
	TB_CHANGEAMMETERS[38] = "CHANGEAMMETER_GDL";
	TB_CHANGEAMMETERS[39] = "�ȵ�����ֵ";
	TB_CHANGEAMMETERS[40] = "CHANGEAMMETER_UPDATETIME";
	TB_CHANGEAMMETERS[41] = "�����ʱ��";
	TB_CHANGEAMMETERS[42] = "CHANGEAMMETER_NAME";
	TB_CHANGEAMMETERS[43] = "����������";

    //��������ַ���û���������
	m_address        = "10.127.2.2";// 192.168.18.10
	m_loginname      = "yingkang";
	m_password       = "YingKang";
	m_FtpFileName    = "ykdocs.csv";
	m_QuickReading   =        FALSE;//�������
	m_QuickModuleAddress =         0;//���ٶ���ĵ�ַ
	m_QuickReadModuleValue =      -1;//���ٶ����ֵ
	/*
	m_address          =        "192.168.18.10";// 
	m_loginname        =        "yk";
	m_password         =        "yk";
    */

	m_port             =          21;
	//��ͷר�ñ�־

	Received           =           0;//�жν������ݵ�����	1 ��������Ľ��� 2������ϳ�ɳ����ͨѶ

	//ѭ������,Ĭ����1 ��
	m_Recycles         =     1;
	//��֮��ʱ����,Ĭ����30����
	m_SetRecycleTime   =    30;
	//��ʱ����Ĵ���
	m_ReadModuleTimes  =     0;
	//��פ������
	m_SendGarrisonTimes=     0;

	m_IsHistory        = FALSE;//�Ƿ���ʾ��ʷ����
	m_BackRgbValue     = RGB(255,255,255);//0xFF, 0xFF, 0xE0);
	m_GetDataFromFile  = FALSE;

	//�õ�����Ĵ���
	m_GetErrors        =     0;
	//ֹͣ��������
	m_StopPassing      = FALSE;

	//�������
	int ii;
	for(ii = 0; ii < 106; ii ++)
	{
		m_parameter[ii] = 0;
	}

	//FALSE ��������  TRUE  פ������
	m_others          =   FALSE;
	m_IfChangeData    =   FALSE;//����Զ�����ݵı�־ 
	m_DoubleConnected =    TRUE;
	m_SettimerValues  =  600000;//10����,��ʱ��פ���������ֵ���ʱ��
	m_saveyears       =       2;//���еĶ������ݱ���Ϊ2��
    m_Pause           =   FALSE;//�߳���ͣ��־
	m_CheckReading    =   FALSE;//���Ӷ���

	//��פ����������פ������
	for(ii = 0; ii < 67; ii ++)
	{
		m_DateReadParameter[ii] = 0;
	}

	m_zhuliukinds       =         0;//0 �����������פ�� 1 ��������פ��

   	for(ii = 0; ii < 128; ii ++)
	{
		m_AllLineThreeCurrent[ii] = 0;//��32����·4�ε���,����·�ĵ���ֵ���2*16=32 32*3 = 96 ÿ����·��3�ε���
	}	

	m_Thread_PRIORITY = (DWORD)THREAD_PRIORITY_ABOVE_NORMAL;//THREAD_PRIORITY_ABOVE_NORMAL;//�̼߳��� THREAD_PRIORITY_NORMAL THREAD_PRIORITY_ABOVE_NORMAL THREAD_PRIORITY_HIGHEST

	m_WgLess          =    0;//�޹������� 0 10���� 1 20����  2 30����

}


CIFRMView::~CIFRMView()
{ 
	
	//TRUE ���վ�汾  FALSE ��ְ�
	if(	AppInfo::Instance().m_WhichKind == TRUE)
	{

		//ɾ���ɼ���
		if(card == 0)
		{
			Release_Card(card);
		}

	}
    
	m_StartRead  = FALSE;

	//�õ��޸�״̬
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("�������޸�,���汨���ļ���?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{

             OnSavereportas(); 

		}

	}

}

void CIFRMView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFRMView)
	DDX_Control(pDX, IDC_MSCOMM, m_Com);
	DDX_Control(pDX, IDC_WINSOCK, m_WinSocket);
	DDX_Control(pDX, IDC_485MSCOMM, m_485MsComm);
	DDX_Control(pDX, IDC_PRINTREPORTS, m_Grid);
	//}}AFX_DATA_MAP
}

BOOL CIFRMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(WHITE_BRUSH),0);
	return CFormView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CIFRMView printing

BOOL CIFRMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;
	
	return TRUE;
}

void CIFRMView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{	
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;

	//�õ�ѡ����������
    if(pMainFrm->m_wndMyDialogBar.IsWindowVisible())
	{	
		
		//���û�м�¼
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0)
		{
			
			m_DialogBarVisible  = TRUE;
		    pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
			pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
			//���²���
         	pMainFrm->RecalcLayout();

		}
	
	}
    
	m_Grid.SetFixedBkColor(RGB(255,255,255));
	m_Grid.OnBeginPrinting(pDC, pInfo);

}

void CIFRMView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
	if(m_DialogBarVisible)
	{

		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		ASSERT_VALID(pMainFrm);
		//���û�м�¼
		if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0  && m_DialogBarVisible  == TRUE)
		{

		    //�õ�ѡ����������
		    pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
            pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			//���²���
         	pMainFrm->RecalcLayout();

		}
	

	}
	
	m_Grid.SetFixedBkColor(RGB(212,208,200));
    m_Grid.OnEndPrinting(pDC, pInfo);
}

void CIFRMView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	m_Grid.OnPrint(pDC, pInfo);

	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CIFRMView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	CFormView::OnDestroy();
	
    Sleep(100);
	
	//TRUE ���վ�汾  FALSE��ְ�
	if(	AppInfo::Instance().m_WhichKind == TRUE)
	{
		
		//���ټ�ʱ��
		for(int i = 1; i <= 3; i++)
		{

			KillTimer(i);
		
		}
		
	}
	else
	{
		//����ȡ����
		KillTimer(2);
		KillTimer(3);
	}
	
}




void CIFRMView::OnSize(UINT nType, int cx, int cy)
{
	
	//�ؼ���λ��
	CRect          rect;
    GetClientRect(rect);
	//�ؼ���λ��
    ::SetWindowPos(m_Grid,HWND_TOP,0,0,rect.Width(),rect.Height(),SWP_SHOWWINDOW);//SWP_DRAWFRAME);//

}

/////////////////////////////////////////////////////////////////////////////
// CIFRMView diagnostics

#ifdef _DEBUG
void CIFRMView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIFRMView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIFRMView message handlers

BEGIN_EVENTSINK_MAP(CIFRMView, CFormView)
//{{AFX_EVENTSINK_MAP(CIFRMView)
ON_EVENT(CIFRMView, IDC_MSCOMM,  1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 2 /* ConnectionRequest */, OnConnectionRequestWinsock, VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 0 /* DataArrival */, OnDataArrivalWinsock, VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 5 /* Close */, OnCloseWinsock, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 1 /* Connect */, OnConnectWinsock, VTS_NONE)
ON_EVENT(CIFRMView, IDC_WINSOCK, 6 /* Error */, OnErrorWinsock, VTS_I2 VTS_PBSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_PBOOL)
ON_EVENT(CIFRMView, IDC_WINSOCK, 3 /* SendProgress */, OnSendProgressWinsock, VTS_I4 VTS_I4)
ON_EVENT(CIFRMView, IDC_WINSOCK, 4 /* SendComplete */, OnSendCompleteWinsock, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


//�����߳�
UINT WorkerThread( LPVOID pParam )
{
	
	//����һ��������ָ�룬Ȼ�����ô��ڱ���
	int type =(int)pParam;
	CMainFrame* pts   = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CIFRMView* pview = (CIFRMView *)(pts->GetActiveView());

	pview->m_StartRead  = TRUE;

    //��ʼ����
	switch(type)
	{
	case 0:
		{   
			//���ö��ı�־
            pview->SetDataReadLabel(pview->SendContionStr);	//ѭ������,Ĭ����1 ��
			pview->FiveDataChuLi("���Զ���",pview->m_SetLabel,FALSE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 1:
		{	
			//���ö��ı�־
            pview->SetDataReadLabel(pview->SendContionStr);
			pview->FiveDataChuLi("��ʽ����",pview->m_SetLabel,TRUE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 2:
		{
			//���ö��ı�־
            pview->SetDataReadLabel(pview->SendContionStr);
			pview->FiveDataChuLi("פ������",pview->m_SetLabel,TRUE, 1, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 3://��������
		{
			
			//��д������Բ���,����������
			//CString title        �б���
			//CString Result       ����
			//CString ConStr       ������Χ
			//BYTE    orders       ����ؼ���
			//BOOL    OnlyReadNot  TRUE  ֻ��û�в��Գ����ģ��
			//                     FALSE ��֮
			//int     times        ��ÿ��ģ��Ĵ���
			//BOOL    OnlyOnce     TRUE  �ö����һ��ģ��ʱֻ����һ��   FALSE ÿ��������һ��
			//int     MaxIValue    ���ֵ(Ϊд����ʱ��)
			//int     MinIValue    ��Сֵ
			//int     intervals    ��  ��
			//(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals)
            //�ֽ�����
			int         k,l;
			k  =  l  =    0;
			CString str[10];

			while((k = pview->SendContionStr.Find(';')) != -1) 
			{
				
				//��";"����������
				str[l] = pview->SendContionStr.Left(k);
				pview->SendContionStr =	pview->SendContionStr.Right(pview->SendContionStr.GetLength()- k - 1);
				if(l > 9)
				{
					return 0;
				}
				l++;
				
				
			}

			str[9] = pview->SendContionStr;
			pview->DisposeModuleParameter(str[0],str[1],str[2],atoi(str[3]),atoi(str[4]),atoi(str[5]),atoi(str[6]),atoi(str[7]),atoi(str[8]),atoi(str[9]));
			break;
		}
	case 4:
		{
			//��פ��ֹͣ��,��ʼ��פ������
			pview->FiveDataChuLi("��ʱפ��",pview->m_TimeSetLabel,TRUE, 1, pview->m_AutoReadCondtionStr,1,1,1);
			break;
		}
	case 5:
		{   
			//�����·����״̬
			pview->SendMessage(WM_EVENT, 15, 0);
    		break;
		} 
	case 6:
		{    
			//����ʱפ����
			pview->SendBreadorder(pview->m_AutoReadTime,pview->m_SendGarrisonTimes);
			
			//�����·����״̬
			if(pview->m_StartRead)
			{
				CTime timet = CTime::GetCurrentTime();
				
				if(timet.GetMinute() < 30)
				{
					//�����·����
				//	pview->SendMessage(WM_EVENT, 15, 0);
					
					//�������ģ�������ѹ
				//	pview->SendMessage(WM_EVENT, 17, 0);
					
					//����޹����������
					pview->SendMessage(WM_EVENT, 18, 0);
					
				}

			}

    		break;
		}
	case 7:
		{    
			//���ڸ����û����ݱ�
			pview->GetDataFormMarketServer(pview->m_address,pview->m_loginname,pview->m_password,pview->m_FtpFileName,pview->m_port);
    		break;
		}
	case 8:
		{
			//פ��������,ֻ��û�ж����ļ�¼ 2004.11.2��
			pview->FiveDataChuLi("פ������",pview->m_SetLabel,TRUE, 1, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 9:
		{	
			//��ʽ������,ֻ��û�ж����ļ�¼ 2004.11.8��
			pview->FiveDataChuLi("��ʽ����",pview->m_SetLabel,TRUE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 10:
		{   
			//���Զ�����,ֻ��û�ж����ļ�¼ 2004.11.8��
    		pview->FiveDataChuLi("���Զ���",pview->m_SetLabel,FALSE, 0, pview->SendContionStr,pview->m_Recycles,pview->m_SetRecycleTime,0);
			break;
		}
	case 11:
		{
			//�ȼ����·����״̬����ʼ��פ������MsgWaitForMultipleObjects
			pview->SendMessage(WM_EVENT, 15, 0);
			pview->FiveDataChuLi("��ʱפ��",pview->m_TimeSetLabel,TRUE, 1, pview->m_AutoReadCondtionStr,1,1,1);
			break;
		}
	case 12:
		{
			//������ר��
			//30����һ��פ��
			pview->EverySendInfo();			
			//״̬������ʾ��Ϣ
			pview->StatusStr = " ";
			pview->SendMessage(WM_EVENT, 1, 0);
			break;
		}
	case 13:
		{
			//��ʱ�̵㵽
			if(pview->WaitShiKedian(pview->m_shikedian))
			{
				
				//�������ֹͣ��ť
				if(pview->m_StartRead)
				{	
					
					int m_waitfortimes     =                    0;
					CString                      m_CheckDaynicStr;
					m_CheckDaynicStr      = pview->m_DynaicCheckStrCondition;
				
					for( int yyyyyyy = 0 ; yyyyyyy < pview->m_readchecktimes; yyyyyyy ++)
					{
						
						//�������ֹͣ��ť
						if(!pview->m_StartRead)
						{	
							break;
						}

						//���ö��ı�־
						pview->SetDataReadLabel(m_CheckDaynicStr);	//ѭ������,Ĭ����1 ��
						pview->FiveDataChuLi("��̬���",pview->m_SetLabel,TRUE,0, m_CheckDaynicStr,1,1,0);
						
						//�������ֹͣ��ť
						if(!pview->m_StartRead)
						{	
							break;
						}
							
						while(1)
						{
							//�ȴ�ʱ��
							CTime timet = CTime::GetCurrentTime();
							
							//ʱ�������
							if(timet.GetMinute() < pview->m_shikedian)
							{
								m_waitfortimes = pview->m_shikedian*60 - timet.GetMinute()*60 - timet.GetSecond();
							}
							else
							{
								m_waitfortimes = pview->m_shikedian*60  + (3600 - timet.GetMinute()*60 - timet.GetSecond());	
							}

							if(m_waitfortimes <= 2)
							{
								break;
							}
							
							//��ʾ״̬����Ϣ
							pview->StatusStr.Format("���Ѷ�%d��,��%d��,���´μ��Ӷ���%4d��,���Ժ�...��",yyyyyyy+1,pview->m_readchecktimes,m_waitfortimes);
							pview->SendMessage(WM_EVENT, 1, 0);
						
							//��Զ�̷�����Ϣ
							pview->SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",pview->StatusStr);
							pview->SendMessage(WM_EVENT, 5, 0);
							
							Sleep(500);
							
							//�������ֹͣ��ť
							if(!pview->m_StartRead)
							{	
								break;
							}
							
							Sleep(500);
							
						}
						
					}
					
				}

			}
			
			pview->m_StartRead     = FALSE;
			pview->m_CheckReading  = FALSE;
			break;
		}
	case 14:
		{
			//�������ͨѶ
			pview->CheckTongXunStatus();
			break;
		}
	case 15:
		{
			//����޹�����
			pview->WuGongDeal(pview->SendContionStr);
			break;
		}
	
	
    }

	//�ر��߳�
//	pview->m_StartRead    =      FALSE;
    pview->PostMessage(WM_EVENT,16, 0);
	return                           0;   // ���ز��˳��߳�
}

//���ݶ���
void CIFRMView::OnTestreadtable() 
{  
	CString            str;
	CString  SelStr   = "";
	//��¼����
	long     m_records = 0;
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

    //�õ��Ի�������ѡ����
    if(!GetDialogBarStr())
	{
		return;
	}

	CCondtionsDlg        dlg;

	if(dlg.DoModal() == IDOK)
	{
	
		m_QuickReading = dlg.m_QuickReading;

	    //���վ�汾
		if(AppInfo::Instance().m_WhichKind == TRUE)//TRUE ���վ�汾  FALSE��ְ�
		{

			//��ͨ����
			if(dlg.m_readradiokinds == 0)
			{

				//פ��ʱ��
				m_ZhuLiuTime   =       dlg.m_GetTimeStr;
				m_StartRead    =                   TRUE;
				SendContionStr = m_ModuleFindContionStr;

				//������ϴ�פ��û�ж�������ģ��
				if(dlg.m_ReadLabel && dlg.m_NoReadingKinds > 0)
				{
					SendContionStr = "(" + SendContionStr + ")" + " AND USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					SetDataReadLabel(SendContionStr);	//���ö��ı�־

					//������Ϊ����
					if(dlg.m_PhaseNoKnown)
					{
						str.Format("Update TB_USER SET USER_PHASE=3 WHERE %s",SendContionStr);
	                    CDataBaseInstance::ExecuteDataBaseSQL(str);
					}

				}

				switch(dlg.m_radio1)
				{
				case 0:
					{  						
						if(dlg.m_ReadLabel)
						{ 
							//ֻ��û�ж�����ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)10,m_Thread_PRIORITY,0,0,NULL); // ���������� 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}
						else
						{ 
							//���˷�Χ��ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)0,m_Thread_PRIORITY,0,0,NULL); // ����������
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}
						
						break;
					}
				case 1:
					{ 
						//��ʽ����							
						if(dlg.m_ReadLabel)
						{ 
							//ֻ��û�ж�����ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)9,m_Thread_PRIORITY,0,0,NULL); // ����������
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}
						else
						{   
							//���˷�Χ��ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)1,m_Thread_PRIORITY,0,0,NULL); // ����������
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}

						break;
					}
				case 2:
					{ 
						
						if(m_IsAutoSending)
						{
							CString       MessageStr;
							m_StartRead  =        FALSE;
							MessageStr   = "��ʱפ���ڼ䲻��פ������";
							MessageBox(MessageStr," ",MB_OK|MB_ICONWARNING);
							return;
						}
						
						//פ������,ֻ���ϴζ���������ģ��						
						if(dlg.m_ReadLabel)
						{ 
							//ֻ��û�ж�����ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)8,m_Thread_PRIORITY,0,0,NULL); // ����������
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}
						else
						{
							//���˷�Χ��ģ��
							ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)2,m_Thread_PRIORITY,0,0,NULL); // ����������
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						}

						break;
					}
					
				}

			}
			else
			{
				//���Ƿ���Զ�פ����ͻ
				BOOL m_CanReading = TRUE;
				CString              str;
				BYTE        m_day  =   0;

				//�����פ���ڼ�
				if(m_IsAutoSending)
				{					
				
					CByteArray          m_TimeArray;//������������
				
					for(int i = 0; i < 31; i ++)
					{
						
						//�����������
						if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
						{
							m_TimeArray.Add(i+1);
						}
						
					}
					
					//���û�ж����������˳�
					if(m_TimeArray.GetSize() > 0)
					{	
						//������ʱ��	
						long m_seconds = (dlg.m_readRangle * dlg.m_readtimes)*3600;//���೤ʱ��
						CTimeSpan                                ts;//ʱ���϶//ʱ��
						ts                   =            m_seconds;
                    	CTime           timet = CTime::GetCurrentTime();
					    CTime            m_CurrentTime2 = timet + ts;//����ʱ�����
                        BYTE        m_day1 = timet.GetDay();
                        BYTE        m_day2 = m_CurrentTime2.GetDay();
                    
    					if(m_day2 >= m_day1)
						{

							for(int i = 0;i < m_TimeArray.GetSize();i ++)
							{

								if(m_TimeArray[i] >= m_day1 && m_TimeArray[i] <= m_day2)
								{
									//��¼��ͻ��
                                    m_day = m_TimeArray[i];
									m_CanReading  = FALSE;
									break;
								}
					
							}


						}
						else
						{
							//����
							for(int i = 0;i < m_TimeArray.GetSize();i ++)
							{

								if(m_TimeArray[i] <= m_day1 || m_TimeArray[i] >= m_day2)
								{
									//��¼��ͻ��
                                    m_day = m_TimeArray[i];
									m_CanReading  = FALSE;
									break;
								}
					
							}


						}
						
					}
					
				}

				if(m_CanReading)
				{
					m_CheckReading            =            TRUE;//���Ӷ���
					m_shikedian               = dlg.m_shikedian; //����ʱ���
					m_readRangle              = dlg.m_readRangle;//���೤ʱ��
					m_readchecktimes          = dlg.m_readtimes; //�������
					m_DynaicCheckStrCondition = m_ModuleFindContionStr;
					
					//���˷�Χ��ģ��
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					str.Format("�˲�����Ӱ��%d�ն�ʱפ������,����ִ���𣿣�\r\n���ִ���п��ܵ���%d��פ��������������",m_day,m_day);
					
					if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
					{

						m_CheckReading            =            TRUE;//���Ӷ���
						m_shikedian               = dlg.m_shikedian; //����ʱ���
						m_readRangle              = dlg.m_readRangle;//���೤ʱ��
						m_readchecktimes          = dlg.m_readtimes; //�������
						m_DynaicCheckStrCondition = m_ModuleFindContionStr;
						
						//���˷�Χ��ģ��
						ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // ����������
						ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						
					}

					
				}
				
			}
			
		}
		else
		{
			/*
			//��ְ�
			//SelStr---��ʽΪ��0��1��ɵ�ʮһλ����ʾ��:1111111111   
			//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
			//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
			//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
			//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
			//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
			//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
			//����λ��ʾ ������
            //�ڰ�λ��ʾ �����
            //�ھ�λ��ʾ �ȵ���
            //��ʮλ��ʾ ƽ����
            //��ʮһλ��ʾ ��������
			//�ϲ�����
			SelStr  =  "";
			
			//�õ����վ���
			//m_StationNo = GetStationNo();  
		
			//�ϲ�����
			for(int i = 0; i < 15; i ++)
			{
				
				//�ۻ��й���ȡ����������й���ȡ��ۻ��޹���ȡ����������޹���ȡ���������ѹ
				if( (i >= 0 && i <= 3) || i == 4 || i == 7  || (i >= 10 && i <= 14))
				{
					
					if(m_SetLabel[i] == TRUE)
					{
						SelStr = SelStr + "1";
					}
					else
					{
						SelStr = SelStr + "0";
					}
					
				}
				
			}


			//��ͨ����
			if(dlg.m_readradiokinds == 0)
			{
			
				//�½���
				switch(dlg.m_radio1)
				{
				case 0:
					{  
						
						//���Զ���
						m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
						
						//ֻ���ϴ�û�ж���������
						if(dlg.m_ReadLabel)
						{
							//����һ������������	//ѭ������,Ĭ����1 ��
							//��֮��ʱ����,Ĭ����30����
							str.Format("BEGINS;COMMAND:18:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						else
						{
							//����һ������������	
							str.Format("BEGINS;COMMAND:01:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						break;
					}
				case 1:
					{ 
						//��ʽ������¼����
						m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", m_ModuleFindContionStr);
						
						//ֻ���ϴ�û�ж���������
						if(dlg.m_ReadLabel)
						{
							//����һ������������
							str.Format("BEGINS;COMMAND:17:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						else
						{
							//����һ������������
							str.Format("BEGINS;COMMAND:02:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);
						}
						break;
					}
				case 2:
					{ 
						//פ������
						//ֻ���ϴζ���������ģ��
						if(dlg.m_ReadLabel)
						{
							//��¼����,ֻ���ϴ�û�ж�������ģ��
							m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
							str.Format("BEGINS;COMMAND:16:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);//פ������
						}
						else
						{	
							//��¼����
							m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
							str.Format("BEGINS;COMMAND:03:%s:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,m_Recycles,m_SetRecycleTime,SelStr);//פ������
						}
						break;
					}
					
				}

			}
			else
			{
				//��̬��ض�����¼����
				m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
				str.Format("BEGINS;COMMAND:37:%s:%d:%d:%d:%d:%s;ENDS",m_ModuleFindContionStr,m_records,dlg.m_shikedian,dlg.m_readRangle,dlg.m_readtimes,SelStr);//��̬��ض���
				
			}
		
			//Զ�̷��Ͳ��Զ�����ʽ����פ������ָ��
         	if(SelectSendString(m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
			{
				m_StartRead = TRUE;
			}
			else
			{
				m_StartRead = FALSE;
			}
			*/
			
		}
		
	}
	
}



//��פ��
void CIFRMView::OnBreadorder() 
{   
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CBreadSettingDlg dlg;
    dlg.DoModal();
	m_StartRead = FALSE;
}

void CIFRMView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	
	ResizeParentToFit();

	//��ִ���ļ�·��
	GetFileFolderPass =         GetFolder();

	//�������
	m_Grid.GetDefaultCell(FALSE,TRUE)->SetFormat(DT_CENTER|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS|DT_SINGLELINE);//
	m_Grid.SetEditable(FALSE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableDragAndDrop(TRUE);
    m_Grid.SetTextBkColor(m_BackRgbValue);//RGB(0xFF,0xFF,0xE0));
    m_Grid.SetBkColor(RGB(128,128,128));  //m_BackRgbValueRGB(255,255,255)
	m_Grid.SetHeaderSort(TRUE);
	m_Grid.SetSingleRowSelection(TRUE);	
	m_Grid.SetModified(FALSE,-1,-1);      //��δ�޸�״̬
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	

	//�������ݸ��ֱ�ṹ
	if(!UpdateDataTable())
	{
		MessageBox("���ݱ���������������ֲ������ܲ���\r\n����ִ�У���������Ӣ����˾��ϵ��"," ",MB_OK|MB_ICONWARNING);
		//�õ�DIALOGBAR�ϵı���,��ʼ�����ؼ�	
		//pMainFrm->SendMessage(WM_CLOSE);
	}

	m_WgLess          =    GetWGTimeEvery();//�޹������� 0 10���� 1 20����  2 30����//�õ��޹���ʱ����

	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
	{
		//��ʼ�����ؼ�
		pMainFrm->m_wndMyDialogBar.Treeinitialize();

		VARIANT        position;
		position.vt   =   VT_I4;
		position.lVal =       2;
		pMainFrm->m_wndMyDialogData.initializeFieldInfo("��������","ALL",3,position);
	}
	else
	{
		//���ߴ����ģ��
		CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_LINEERROR");

		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
	}

  	//�õ��˿ڸ���
	GetComPorts();

	//״̬��
	pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);// AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	//ָ�봫�����

	//��̨���ݿ�
	m_TransformpSet = std::shared_ptr<CTransformRecordset>(new CTransformRecordset);

    //��ȱ����ݿ�
	m_AmetterSet    = std::shared_ptr<CAmetterRecordset> (new CAmetterRecordset );

	//�û���Ϣ���ݿ�
	m_UseInfoset    = std::shared_ptr<CUseInfoRecordSet>(new CUseInfoRecordSet);

	//פ����Ϣ���ݿ�
	m_GarrisonSet   = std::shared_ptr<CGarrisonRecordSet> (new CGarrisonRecordSet);

	//������Ϣ���ݿ�
	m_DataInfoSet   =std::shared_ptr<CDataInfoRecordSet>(new CDataInfoRecordSet);

	//�۸����ݿ�
	m_PriceSet      = std::shared_ptr<CPriceSet> (new CPriceSet );

    //������Ϣ
	m_CCHANGEAMMETER = std::shared_ptr<CCHANGEAMMETERSet>(new  CCHANGEAMMETERSet);
	
	//����û���û������
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") <= 0)
	{
		
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		ASSERT_VALID(pMainFrm);

		//�õ�ѡ����������
		m_DialogBarVisible  = FALSE;
		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);

	}
	
	//�رմ���
	if(m_Com.GetPortOpen()) //�򿪴���   
	{
		m_Com.SetPortOpen(FALSE);
	}

	//��ʱ��ť��ΪFALSE
	ShowDingShiButton(FALSE);

	//���վ�汾
	if(	AppInfo::Instance().m_WhichKind)//TRUE ���վ�汾  FALSE��ְ�
	{	
		//��ʾ�汾
		if(!AppInfo::Instance().m_YanShi)
		{

			CString error;
			
			if ((card = Register_Card (PCI_9111DG, 0)) <0 ) 
			{	
				if(!AppInfo::Instance().m_AutoRunning)
				{
					MessageBox("�ɼ�����ʼ����������ɼ���\r\n��װ�Ƿ���ȷ��","����",MB_OK|MB_ICONWARNING);
				}
				else	
				{
					Beep(300,400);
				}
				
			}
			
			//˫������״̬
			err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
			if (err != 0)
			{
				//Beep(300,400); 
			}
			
			err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
			if (err != 0) 
			{
				//Beep(300,400);
			}

		}

	
			
		//�ڶ�����Ϊ�����ܱ��վվ�ܱ�ר�� 485
        if(Ports[1] == TRUE)
		{
			
			//����485�ڣ�485�ڳ�ʼ��
        	if(m_485MsComm.GetPortOpen()) //�򿪴���   
			{	
				//�رմ���485ͨѶ��
				m_485MsComm.SetPortOpen(FALSE);
			}
			
			m_485MsComm.SetCommPort(2);            //ѡ��COM2
			m_485MsComm.SetInBufferSize(1024);     //�������뻺�����Ĵ�С��Bytes
			m_485MsComm.SetOutBufferSize(512);     //��������������Ĵ�С��Bytes
			
			//�򿪶˿�
			m_485MsComm.SetPortOpen(TRUE);
			
			m_485MsComm.SetInputMode(1);           //0 �ı���ʽ 1��������ʽ
			
			//���ò�����,����λ,����λ,ֹͣλ	
			m_485MsComm.SetSettings("1200,E,8,1");//"600,n,8,1"
			//1200,E,8,1
			m_485MsComm.SetRThreshold(1);         //ÿ����1���ַ��ʹ���1�ν����¼�
			m_485MsComm.SetInputLen(0);           //ÿ�ζ�ȡһ���ַ�,��������ʽ
			m_485MsComm.GetInput();               //���ԭ�е�����
		}
		else
		{
			//MessageBox("COM2�ڴ򿪴���,���ܱ��վ�ܱ��޷�ͨ��485�ڶ�ȡ���ݣ�","����",MB_OK|MB_ICONWARNING);
		}
		
		//�õ���������Ϣ
		GetHandModuleInformation();
	
		//ÿ��10���ӷ�һ�ε����źţ���������
		if(m_status)
		{
			SetTimer(1,m_SettimerValues,NULL);
		}

		//�Ƿ��ǵ�һ�汾,���ǵ�һ�汾���⴮�ڻ������
		/*
		if(!AppInfo::Instance().m_SingleBB) 
		{
			//����ʱ�Զ�Ӧ��
			AutoAnswer(TRUE);
			
			//�Զ������Զ�Ӧ��
			SetLocalServer(m_WinSocket.GetLocalIP(),2500);
		}
		*/
		
		//���һ�������Զ�פ������ʱ��
		if(IsCurveTableExist("TB_Auto"))
		{
			AutoGarrisonTime();
		}
		
		//�Զ�����������פ��
		if(IsCurveTableExist("TB_DateAuto"))
		{
			ByDateAutoGarrisonTime();
		}

		//�����������
		CFileFind               finder;
		CString      m_RunnExeFileName;
        m_RunnExeFileName.Format("%s%s",GetFolder(),"TraySpy.exe");
		
		//������ڳ������
		if(finder.FindFile(m_RunnExeFileName) != 0) 
		{   
			LPCTSTR  m_pszAppName = "TraySpy";
			
			//�˳���ֻ������һ�Σ��û��������жϳ����Ƿ�������
			HANDLE m_hTrayWatchMutex = CreateMutex(NULL,TRUE, m_pszAppName); 
			
			if(GetLastError() != ERROR_ALREADY_EXISTS)
			{ 
				//���д����
				WinExec(m_RunnExeFileName,SW_SHOWDEFAULT);
			}
		
		}
			
		finder.Close();
	

	}
	else
	{	
		m_WinSocket.Close();
		//���ڸ����û����ݱ�
		//SetTimer(2,1*60000,NULL);//15
	}
	
    m_pSelection = NULL;    // initialize selection

}



//��̨���ݿ�
void CIFRMView::OnTranformer() 
{
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	//���ԭ�ȴ�����ر�
	if(m_TransformpSet->IsOpen())
	{
		m_TransformpSet->Close();
	}
	
	//���ݿ���Ƿ��
	if(m_TransformpSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CTransformerDlg	dlg(m_TransformpSet.get(),0);
		dlg.m_Enalbed  = TRUE;
		dlg.DoModal();
		
		//���ԭ�ȴ�����ر�
		if(m_TransformpSet->IsOpen())
		{
			m_TransformpSet->Close();
		}
		
		//��̨�޸Ļ������˼�¼
		if(dlg.m_IfAdding == TRUE)
		{
			//���ؼ�����ˢ��һ��
			RefreshTree();
		}
		
	}
	else
	{
		MessageBox("���ݿ��򿪴���"," ",MB_OK|MB_ICONWARNING);
	}
	
}

//������ݿ�
void CIFRMView::OnAmmeterinfo() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	if(m_AmetterSet->IsOpen())
	{
		m_AmetterSet->Close();
	}
	
    //���ݿ���Ƿ��
	if(m_AmetterSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		CAmetterDlg  dlg(m_AmetterSet.get(),0);
		dlg.m_Enalbed =   TRUE;
		dlg.DoModal();	
		
		if(m_AmetterSet->IsOpen())
		{
			m_AmetterSet->Close();
		}
	}
	else
	{
		MessageBox("���ݿ��򿪴���"," ",MB_OK|MB_ICONWARNING);
	}

}

//�û����ݿ�
void CIFRMView::OnUserinfo() 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	if(m_UseInfoset->IsOpen())
	{
		m_UseInfoset->Close();
	}
	
	//���ݿ���Ƿ��
	if(m_UseInfoset->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CUserInfoDlg dlg(m_UseInfoset.get(),0);
		dlg.m_filtercondtion = "";
		
		dlg.DoModal();	
		
		if(m_UseInfoset->IsOpen())
		{
			m_UseInfoset->Close();
		}
		
		//��̨�޸Ļ������˼�¼
		if(dlg.m_IfAdding == TRUE)
		{	
			//���ؼ�����ˢ��һ��
			RefreshTree();
			
		}
		
	}
	
}

//ͨѶ�Ի���
void CIFRMView::OnCommunication() 
{
	//DealOverTimeData(1);
	//return;
    //TRUE--���վ�汾  FALSE---��ְ�
	CStationCommunDlg    dlg;
	dlg.m_WhichKind = AppInfo::Instance().m_WhichKind;
	dlg.DoModal();
}

//״̬������ʾ��Ϣ
void CIFRMView::status(CString strname)
{
	if (pStatus)
	{
		pStatus->SetPaneText(0,strname);
	}
	
}

//��ʾ�����ع�����
void CIFRMView::ShowProgressCtrl(BOOL m_IsShow)
{
    CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->ShowProgressCtrl(m_IsShow);
}

//ֹͣ��ť
void CIFRMView::OnStoprun() 
{
	
	//����window����Ȩ
	SurrenderWindowMessage();
	
	m_StartRead       =   FALSE;

	//�����̼߳���
	if(ReadMeterThread != NULL)
	{
		//WaitForSingleObject(ReadMeterThread->m_hThread,INFINITE);
		ReadMeterThread->SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	}

	for(BYTE i = 0; i < 10; i ++)
	{

		m_StartRead       =   FALSE;
        bStopped          =    TRUE;
		//���Ӷ���
    	m_CheckReading    =   FALSE;	

		//����window����Ȩ
		SurrenderWindowMessage();
		Sleep(20);	
		
		if(ReadMeterThread == NULL)
		{	
			status("              ");
			break;
		}

	}
	//����߳���ͣ
	
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//�����߳��˳�
		ReadMeterThread->ResumeThread();
		m_Pause  =   FALSE;	
		
		//����window����Ȩ
		SurrenderWindowMessage();
		Sleep(500);
		//����window����Ȩ
		SurrenderWindowMessage();
		//����߳���ͣ
	}
	
    //ֹͣ��������
	m_StopPassing    = TRUE;

	KillTimer(2);
	KillTimer(3);

	//��ʾ�����ض���
	OperationAnimation(FALSE);
	//���ع�����
	ShowProgressCtrl(FALSE);

	//����window����Ȩ
	SurrenderWindowMessage();
 
	//SelectSendString(m_sendkind,"BEGINS;DATAS:3:StopData;ֹͣ;ENDS",TRUE,FALSE,FALSE);
	//����window����Ȩ
	//SurrenderWindowMessage();

	//�����Խ���������
	m_ReceiveOk    =   FALSE;

}


//�趨��������Χ,����
void CIFRMView::SetProgressCtrlRange(int ups, int downs,int steps)
{ 
	CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->m_progressBar.SetRange(ups , downs);
	pts->m_progressBar.SetStep(steps);
	pts->m_progressBar.SetPos( 0 );
	
}


//�趨�������»�
void CIFRMView::SetProgressCtrlSetIt()
{
	CMainFrame* pts = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pts->m_progressBar.StepIt();
	
}


//��������
double CIFRMView::ReadMeter(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/,BYTE Item/* Ҫʲô����*/,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/,CString m_AmmeterType/*������ͺ�*/)
{
//	WriteToLog("[���Ƕ���]");


	double  m_RetuenValue =     0;
	double  m_tempvalue   =     0;
	int     HalfCount     =     0;
	BOOLEAN bHalfReady    = FALSE;
	bStopped              = FALSE;
	U32                     count;
	DataLen               =     0;
	U16               overrunFlag;
	CString                   str;//��������ѹ
	BOOL m_changed        = FALSE;
	BYTE     k1  =  0,k2  =   1;

	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);

	//�ɿ��ٶ�485��
	m_CanQuickRead71485   = FALSE;

	if(!m_StartRead)
	{
		return -1;
	}

	for(int jj = 0 ; jj < 3; jj ++)
	{
        m_Quick71Value[jj] =   0;
	}
	
//	str.Format("ģ���:%d,���:%d\r\n",ModuleNum,Phase);
//	WriteToLog(str);
	
	//��ʾ�汾
	if(AppInfo::Instance().m_YanShi)
	{
		
		for(int jj = 0 ; jj < 7; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(1000);
			}
			else
			{
				break;
			}
			
		}
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		CTime time  = CTime::GetCurrentTime();
		
		if(Item == 0xf6 || Item==0xf8)
		{
			m_RetuenValue = 333333.33;
		}
		else if(Item == 0x38 || Item==0xB8)
		{
			m_RetuenValue = 0.98;
		}
		else
		{
			//����ֵModuleNum
			m_RetuenValue = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01 +  ModuleNum*0.001;
		}
		
	}
	else
	{	

		//����������,פ����������
		if(m_QuickReading)
		{  	
			
			//��61��62Э��485����ٶ���Ĺ�������
			if(((Protocol/10) == 6) && (Item==0x07 || Item==0x06) && ((ModuleNum%100) > 12))
			{
				
				if(ModuleNum/100 < 20000 )
				{

					//���ԭ�������˱��ֵ��
					if(m_QuickGlys[ModuleNum/100 - 1] >= 0)
					{

						return m_QuickGlys[ModuleNum/100 - 1];

					}
					
				}
				
			}		
		
			//��71��72Э��485����ٶ���Ĺ�������,�壬�ȣ�ƽ���й����޹�
			if(((Protocol/10) == 7) && (Item == 0x5A || Item == 0x5E || Item == 0x5C || Item == 0x02 || Item == 0x06 || Item == 0xDA || Item == 0xDE || Item == 0xDC || Item == 0x82 || Item == 0x86) && ((ModuleNum%100) >= 12))
			{
				
				CTime     timet    = CTime::GetCurrentTime();
				str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
				
				//��ģ���Ƿ��ܿ��ٶ���
				if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
				{
					
					if(!((ModuleNum/100) < 100000  && m_QuickGlys[ModuleNum/100] < 0))
					{
						
						//�ɿ��ٶ�485��
						m_CanQuickRead71485        = TRUE;
						m_QuickGlys[ModuleNum/100] =    0;
						
						//ʵʱ�壬�ȣ�ƽ
						if(Item == 0x5A || Item == 0x5E || Item == 0x5C)
						{
							//�壬�ȣ�ƽ
							Item = 0x64;
						}
						else if(Item == 0x02 || Item == 0x06)
						{
							//ʵʱ�й����޹�
							Item = 0x66;
						}
						else if(Item == 0xDA || Item == 0xDE || Item == 0xDC)
						{	
							//פ���壬�ȣ�ƽ
							Item = 0xF4;
						}
						else if(Item == 0x82 || Item == 0x86)
						{
							//פ��ʵʱ�й����޹�
							Item = 0xF6;
						}
						
					//	str.Format("Э�飺%d�����ٶ���ģ��ţ�%d��ָ��:%0x\r\n",Protocol,ModuleNum,Item);
					//	WriteToLog(str); 
					} 
					
				}
							
		  }
		  else
		  {	
				
				//71,72,73Э�������,һ������3��ģ������ݣ�32λ��ÿ��ģ��10λ�����999��ÿ������3��,61,62��485,�������غ��й����ʴ����һ��
				if((((ModuleNum%100) <= 8) && (Item==0x02 || Item==0x82) && ((Protocol/10) == 7)) || ((Protocol/10) == 6 && ((ModuleNum%100) > 12) && (Item==0x1F || Item==0x1E)))
				{
					
					CTime     timet    = CTime::GetCurrentTime();
					str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					
					//��ģ���Ƿ��ܿ��ٶ���
					if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
					{	   
						
						//�Ա�����ģ��,71,72,73Э��
						if((m_QuickModuleAddress/100 == ModuleNum/100) && ((Protocol/10) == 7))
						{
							
							//���ٶ���ģ���ӱ�ķ�Χ
							if((m_QuickModuleAddress%100) >= 1 &&  (m_QuickModuleAddress%100) <= 3)
							{
								k1 = 1;
							}
							else if((m_QuickModuleAddress%100) >= 4 &&  (m_QuickModuleAddress%100) <= 6)
							{
								k1 = 2;
							}
							else if((m_QuickModuleAddress%100) >= 7 &&  (m_QuickModuleAddress%100) <= 8)
							{
								k1 = 3;
							} 
							
							//��ʱ����ģ���ӱ�ķ�Χ
							if((ModuleNum%100) >= 1 &&  (ModuleNum%100) <= 3)
							{
								k2 = 1;
							}
							else if((ModuleNum%100) >= 4 &&  (ModuleNum%100) <= 6)
							{
								k2 = 2;
							}
							else if((ModuleNum%100) >= 7 &&  (ModuleNum%100) <= 8)
							{
								k2 = 3;
							}
							
							//������һ����
							if(k1 == k2) 
							{
								
								//m_QuickReadParameter[0] �����й���ȶ���ֵ
								//m_QuickReadParameter[1] �й���ȵ�ֵ
								//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ								   
								
								//���������������ֵ,ǰ10λ��һ�ӱ�ģ���ֵ���м�10λ�ڶ��ӱ�ģ���ֵ������10λΪ�����ӱ�ģ���ֵ
								if(m_QuickReadModuleValue >= 0)
								{
									
									switch((ModuleNum%10)%3)
									{
									case 1:
										{	  
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
											break;
										}
									case 2:
										{
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
											break;
										}
									case 0:
										{	
											m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
											break;
										}
									}
									
									//���������+���
									m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
									
								//	str.Format("ģ���:%d,ԭ����ֵ:%f,���:%f,����:%f,\r\n�������ֵ:%f,�ӱ��:%f,��һ�ӱ�:%d,�ڶ��ӱ�:%d,�����ӱ�:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
								//	WriteToLog(str);
									
									//����������ڻ���ں���Ļ�
									if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
									{
								//	    WriteToLog("�ӱ�״��ڵ���ԭ����");
										return  m_RetuenValue;
									}
									
								//	WriteToLog("�ӱ��С��ԭ����");
									
									
								}
								else
								{
									
									if(long(m_QuickReadModuleValue) < -1)
									{
										//û��פ��������
										return long(m_QuickReadModuleValue);
									}
									
								}									 
								
							}
							
						}
						else
						{
							
							m_changed              =  TRUE;
							
							if((Protocol/10) == 7)
							{
								m_QuickModuleAddress   =     0;//���ٶ���ĵ�ַ
								m_QuickReadModuleValue =    -1;
								
								if((ModuleNum%100 <= 3))
								{
									
									//��ǰ3��ģ��,�ӱ��ַΪ01,02,03
									if(Item == 0x02)
									{
										Item = 0x0E;
									}
									else
									{
										Item = 0x8E;
									}
									
								}
								else if((ModuleNum%100 >= 4) && (ModuleNum%100 <= 6))
								{
									
									//�м�3��ģ��,�ӱ��ַΪ04,05,06
									if(Item == 0x02)
									{
										Item = 0x10;
									}
									else
									{
										Item = 0x90;
									}					   
									
								}
								else 
								{
									//���2��ģ��,�ӱ��ַΪ07,08
									if(Item == 0x02)
									{
										Item = 0x12;
									}
									else
									{
										Item = 0x82;
									}					   
									
								}
								
								//   str.Format("Э�飺%d�����ٶ���ģ��ţ�%d��ָ��:%0x\r\n",Protocol,ModuleNum,Item);
								//   WriteToLog(str);
								
							}
							else
							{
								//61,62Э��
								if(Item == 0x1F)
								{
									Item = 0x01;
								}
								else
								{
									Item = 0x00;
								} 
								
								//   str.Format("Э�飺%d�����ٶ���ģ��ţ�%d��ָ��:%0x\r\n",Protocol,ModuleNum,Item);
								//   WriteToLog(str);
								
							}
							
						}
						
					}
					else
					{
							m_QuickReadModuleValue     =              -1;
							m_QuickModuleAddress       =       ModuleNum;//���ٶ���ĵ�ַ
					}
						
				}
				   
			}
			  
		}



		//˫������״̬
		err = AI_AsyncDblBufferMode(card, 1);  //double-buffer mode
		if (err !=   0) 
		{  
			return -1;
		}
		
		//�ⴥ��״̬
		err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);//1024 512
		if (err !=   0) 
		{  
			return -1;
		}


		//��Ƭ����ָ��
		if(!SendOrderToSCM(ModuleNum/*ģ���*/,StationNo/*�����ֵ�վ��*/,MotherLine/*ĸ��*/,LineNo/*�ߺ�*/, Phase/*��ѡ��0A 1B 2C*/,3, Item/* Ҫʲô����,������*/,0,Protocol,m_SendAngle))
		{
			Beep(300,400);
			Beep(300,400);
		}
		
		for(int jj = 0 ; jj < 8; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(150);
			}
			else
			{
				break;
			}
		}


		//��ʼ�ɼ�����

		memset(DataBuf,0,190000);
        memset(ReadBuff,0,1024);
		
		//������ͨ������
		err = AI_ContReadChannel(card,m_iChSelect, AD_B_10_V, ReadBuff,1024,(F64)100000, ASYNCH_OP);
		
		if (err !=   0) 
		{  
			return -1;
		}
		
		bClearOp     =                   FALSE;
		CTime time0  = CTime::GetCurrentTime();
		
		do
		{
			do
			{
				//����
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);
				
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1 - time0;
				
				if(Protocol != 22)
				{
					//�������22Э��
					if(ts.GetTotalSeconds() > (Protocol%10)*9 || !m_StartRead)
					{
						bClearOp = TRUE;
					}

				}
				else
				{	
					//�����22Э��
					if(ts.GetTotalSeconds() > 9 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				
			} while (!bHalfReady && !bClearOp);
			
			if(!m_StartRead)
			{
				bClearOp = TRUE;
			}

			if(!bClearOp) 
			{
				
				//���Ͱ�������
				AI_AsyncDblBufferTransfer(card, ReadBuff);
				
				bHalfReady = FALSE;
				
				for(int i = 0; i < 512; i++)
				{	
					DataBuf[DataLen++] = ReadBuff[i]/16;	
				}
				
				SurrenderWindowMessage();

				if(!m_StartRead)
				{
					bClearOp = TRUE;
				}
				
				CTime time1     = CTime::GetCurrentTime();
				CTimeSpan ts    = time1     -       time0;
				
				//ʱ�����
				switch(Protocol)
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
				
				
				if(Protocol != 22)
				{
					
					//�������22Э��
					if(ts.GetTotalSeconds() > (Protocol%10)*10 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				else
				{	
					
					//�����22Э��
					if(ts.GetTotalSeconds() > 9 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
			}
			
		
        }while (!bClearOp && !bStopped && m_StartRead);
	
		AI_AsyncClear(card, &count);
		
		AI_AsyncDblBufferOverrun(card,1,&overrunFlag);
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		//����ֵ
		m_RetuenValue = Decode(ModuleNum,Protocol,Item);

	}
	
//	str.Format("m_RetuenValue=%.2f\r\n",m_RetuenValue);
//	WriteToLog(str);

	//�ɿ��ٶ�485��
	if(m_CanQuickRead71485)
	{	
		

		//�������������Ƿ���Ч,������ݴ���0
		if(m_RetuenValue >= 0)
		{
			
			//CTime     timet    = CTime::GetCurrentTime();
			//str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

			//���71Э��485����ٶ����Ƿ�ɹ�
            Check_71485_Protcol(ModuleNum,Item);

			if(!m_CanQuickRead71485)
			{	
				
				if((ModuleNum/100) < 100000)
				{
					m_QuickGlys[ModuleNum/100] = -1;
				}

                m_RetuenValue = -1;
			}
		

		}
		else
		{

			if((ModuleNum/100) < 100000)
			{
				m_QuickGlys[ModuleNum/100] = -1;
			}
			
			m_CanQuickRead71485 = FALSE;

		}
		
	}
	else if(m_QuickReading && m_changed)
	{	

        //���ٶ���
		//������ݴ���0
		if(m_RetuenValue >= 0)
		{	
			
			//71,72,73Э��
			if((Protocol/10) == 7)
			{	
				//71,72,73�����
				m_QuickReadModuleValue =  long(m_RetuenValue);//����ģ������ݴ���һ��
				m_QuickModuleAddress   =            ModuleNum;//���ٶ���ĵ�ַ
				
				//m_QuickReadParameter[0] �����й���ȶ���ֵ
				//m_QuickReadParameter[1] �й���ȵ�ֵ
				//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ

				switch((ModuleNum%10)%3)
				{
				case 1:
					{	  
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
						break;
					}
				case 2:
					{
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
						break;
					}
				case 0:
					{	
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
						break;
					}
				}
				
				//���������,�ó��µ�����ֵ
				m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
				
		//		str.Format("ģ���:%d,ԭ����ֵ:%f,���:%f,����:%f,\r\n�������ֵ:%f,�ӱ��:%f,��һ�ӱ�:%d,�ڶ��ӱ�:%d,�����ӱ�:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
		//		WriteToLog(str);

				//�����������
				if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
				{
			//		WriteToLog("�ӱ�״��ڵ���ԭ����");
					return  m_RetuenValue;
				}
				
		//		WriteToLog("�ӱ��С��ԭ����");
		  	    
				m_RetuenValue          = - 1;
				m_QuickReadModuleValue = - 1;
				
			}
			else
			{
				//61,62,63Э��485�Ĳ��п��ٶ���,�����Ķ��������ֵ,ǰ7λΪ�������أ�����14λΪ�й����,61,62
				long  m_TmepQuickReadModuleValue =  long(m_RetuenValue*10);
				m_tempvalue                      =  (m_TmepQuickReadModuleValue%(int(pow((double)2,14)))) * 0.1;
				float m_TempGlys                 =  (m_TmepQuickReadModuleValue/(int(pow((double)2,14)))) * 0.01;
				
				if(m_tempvalue <= 999.8  &&  m_TempGlys <= 1)
				{
					
					//m_QuickReadParameter[0] �����й���ȶ���ֵ
					//m_QuickReadParameter[1] �й���ȵ�ֵ
					//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ

					m_RetuenValue = long(m_QuickReadParameter[0] + 0.001)/1000*1000 + m_tempvalue;
					
					//����������ڻ���ں���Ļ�
					if(m_RetuenValue  >= m_QuickReadParameter[0])
					{
						//��61��62Э��485����ٶ���Ĺ������� 
						if(ModuleNum/100 < 20000)
						{
							m_QuickGlys[ModuleNum/100 - 1] = m_TempGlys;
						}
						
						return  m_RetuenValue;
					}
					
				}
				
				m_RetuenValue          = - 1;
			}
			
		}
		else
		{
			//�����˱�ģ�鲻֧�ִ�ָ����
			m_QuickReadModuleValue     =   m_RetuenValue;
			m_QuickModuleAddress       =       ModuleNum;//���ٶ���ĵ�ַ
		}
		
		
	}
	else
	{

		//1-12Ϊ�����
		if(ModuleNum%100 <= 12 && m_RetuenValue > 0  && !m_AmmeterType.IsEmpty())
		{
			//Ĭ��������Ϊ3200��������ֵ
			m_RetuenValue = m_RetuenValue* 3200.00/GetAmmeterImpulse(m_AmmeterType);
		}
		
	}
  TmpOnlyOneThreadRun.SetEvent();


	return m_RetuenValue;
}


//���õ�������������
int CIFRMView::GetAmmeterImpulse(CString m_AmmeterType)
{
	CString       strValue;
	CDatabase           db;	

	strValue.Format("RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);

    //�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset    rs(&db );
		strValue.Format("SELECT AMMETER_TYPE,AMMETER_IMPULSE FROM TB_AMMETER  WHERE RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);
		rs.Open(CRecordset::dynaset,strValue);	
		
		if(rs.IsEOF())
		{
			rs.Close( );
			db.Close( );
			return 3200;
		}
		
		rs.GetFieldValue((short)1,strValue);

		rs.Close( );
		db.Close( );

		if(atoi(strValue) > 0)
		{
			return atoi(strValue);
		}

	}

	return 3200;
}

void CIFRMView::OnTimer(UINT nIDEvent) 
{
	CFormView::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
	case 1:
		{	
	
			
			//0 �����������פ�� 1 ��������פ��
			switch(m_zhuliukinds)
			{
			case 0:
				{
					//�����������פ��
					DingShiDeal();
					break;	
				}
			case 1:
				{
					//��������פ��
					ByDateDingShiDeal();
					break;
				}
			}
	


			break;
		
		}
	case 2:
		{  
		    //��ͷԶ�̰�ר�ã����ڸ����û����ݱ�����ڴ������ݻ����������Ļ����Ͳ�����	
			if(!(ReadMeterThread != NULL ||  m_StartRead == TRUE)) 
			{	
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)7,m_Thread_PRIORITY,0,0,NULL); // ����������
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
			}

			break;
		}
	case 3:
		{	  
			
			//�õ�����Ĵ���
			m_GetErrors ++;	
			BOOL m_connectings = TRUE;
		    
			//����״̬��ʾ
			switch(m_sendkind)
			{
			case 0:
				{
					m_connectings = m_Com.GetPortOpen();
					break;
				}
			case 1:
				{
					m_connectings = m_Com.GetCTSHolding();
					break;
				}
			case 2:
				{ 
					m_connectings = m_IsConnect;
					break;
				}
			}
		
		
			if(m_GetErrors  > 30  || m_StopPassing || !m_connectings)
			{	
				
				KillTimer(3);
				
				//��ʾ�����ض���
				OperationAnimation(FALSE);
				
				//���ع�����
				ShowProgressCtrl(FALSE);
				
				//�õ�����Ĵ���
				m_GetErrors     =     0;
				
				if(!AppInfo::Instance().m_WhichKind)
				{
					status("               ");
					
					//�����Զ�̶�,�����Ի���
					if(m_StopPassing)
					{
						MessageBox("���������ѱ���ֹ����","",MB_OK|MB_ICONWARNING);
					}
					else
					{
						MessageBox("������·�������⣬������·��","",MB_OK|MB_ICONWARNING);
					}

				}
				else
				{
				
					//�����վ,����״̬������ʾ��Ϣ
					if(m_StopPassing)
					{
						status("�����������ѱ���ֹ��");
						SendContionStr = "BEGINS;MESSAGE:0:Զ�̻�����ֹͣ���ն���!;ENDS";
                        SendMessage(WM_EVENT, 4, 0);
					}
					else
					{
						status("��������·��������,������·��");
					}

				}
				
			}
			else
			{
				//��ʽ��BEGINS;COMMAND:25:���ݱ���:Ҫ�ļ�¼��λ��;ENDS
				SendContionStr.Format("BEGINS;COMMAND:25:%s:%d;ENDS",m_PassDataFileName,m_CurrentPassPostions);
				//��������
				SendMessage(WM_EVENT, 5, 0);
			}

			break;
		}
	}
	
}


//����,��6�Σ�������������Э��
double CIFRMView::Decode(long ModuleNum,BYTE Protocol,BYTE Item)
{	
	CString               str,signstr;
	BYTE                     Data[39];
	double dataValue         =     -1;
	int   index              =      0;
    long                  Diffs[1024];
	long                  Diffn[1024];
	long         m_sums        =    0;
	double  m_maxppvalue       =    0;
	short   m_pipeiplace       =    0;
	int     m_maxpptimes = WM_NUMBERS;
	double  m_ppvalue          =    0;
    BYTE  SignalBit[100],TempSignalBit[100],Signal[10];
	double         m_ppresult10[7300];//10��ƥ����
	double         m_ppresult05[7300];// 5��ƥ����
	double           m_ppresult[7300];//    ƥ����
    short        m_PlaceDifferent[31];//22Э�鲻ͬ�ĶԱ�λ��
	BOOL         m_checkplace = FALSE;
	BYTE         m_ByteRecords =    0;//�յ��ֽ���
	int i;
	switch(Protocol)
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
			//���û�вɼ�����
			if(DataLen < 131584)
			{
				return -1;
			} 

			m_ByteRecords = 63;
			break;
		}
	case 61:
		{			
			if(DataLen < 93184)
			{
			//	str.Format("61�ɵ㲻��:%d,ӦΪ93184",DataLen);
			//	WriteToLog(str);
     			return -1;
			} 

			m_ByteRecords = 45;
			break;
		}
	case 62:
		{			
			if(DataLen < 185344)
			{	
				//str.Format("62�ɵ㲻��:%d,ӦΪ185344",DataLen);
				//WriteToLog(str);
				return -1;
			}
			
			m_ByteRecords = 90;
			break;
		}
	}
	
	//�ɼ�������ת��
	for( i = 0;i < DataLen; i ++)
	{
		//����2048Ϊ����
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
		
	}

    //����10�Ƚ�,�õ�����Э��,ǰ1024�����ǿյ�,���������λ
	for(index = 0; index < m_ByteRecords ;index ++)
	{
		
		//��������㷨���,3-1,4-2
		for( i = 0;i < 512;i ++)   
		{ 
			//�õ��źż�,��һ������ǰһ����,��3-1,4-2����,��4����
			Diffs[i]        = DataBuf[(index * 4 + 2) * 512 + i + 1024] - DataBuf[index * 4 *  512 + i  + 1024];
			Diffs[512 + i]  = DataBuf[(index * 4 + 3) * 512 + i + 1024] - DataBuf[(index * 4 + 1) * 512 + i + 1024];
		}
		
		//��������
		for( i = 0;i < 256;i ++)   
		{ 
			Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i];
		}
		
		//ƥ��ֵ
		for(int jj = 0; jj < m_maxpptimes; jj ++)
		{
			//10��ƥ�䲨
			m_ppresult10[index*m_maxpptimes + jj]   = CorrelationCheck(Correlation_Table10,Diffs,jj);
			//5��ƥ�䲨
			m_ppresult05[index*m_maxpptimes + jj]   = CorrelationCheck(Correlation_Table05,Diffs,jj);
		}
		
	}
	

	for(short yyy = 0 ; yyy < 2; yyy ++)
	{
		
		switch(yyy)
		{
		case 0:
			{	  
				//signstr.Format("��++++++++++10�Ƚ���++++++++++��");
				//WriteToLog(signstr);

				//10��
				for(int jj = 0 ; jj < m_ByteRecords*m_maxpptimes; jj ++)
				{
					m_ppresult[jj] = m_ppresult10[jj];
				}
				break;
			}
		case 1:
			{	
				//signstr.Format("��++++++++++05�Ƚ���++++++++++��");
				//WriteToLog(signstr);
				
				//5��
				for(int jj = 0 ; jj < m_ByteRecords*m_maxpptimes; jj ++)
				{
					m_ppresult[jj] = m_ppresult05[jj];
				}

				break;
			}
		}

		//���ƥ��ֵ
		m_maxppvalue  =    0;
		
		//�����ƥ��ֵ
		for(int jj = 0; jj < m_maxpptimes; jj ++)
		{
			
			m_ppvalue    =    0;//ƥ��ֵ��
			
			for(index = 0; index < m_ByteRecords ;index ++)
			{
				
				m_ppvalue = fabs(m_ppresult[jj + m_maxpptimes * index]) + m_ppvalue;
				
			}
			
		//	signstr.Format("ƥ��ϵͳֵ��m_ppresult[%d]=%.3f",jj,m_ppvalue);
		//	WriteToLog(signstr);	
			
			if(m_ppvalue > m_maxppvalue)
			{
				m_maxppvalue  =  m_ppvalue;//���ƥ��ֵ
				m_pipeiplace  =         jj;//��ס���ƥ��λ��
			}
			
		}
		
		//signstr.Format("m_pipeiplace=%d",m_pipeiplace);
		//WriteToLog(signstr);

	    //���ƥ��λ�õ�����
	    for(index = 0; index < m_ByteRecords ;index ++)
		{
			
	//	    signstr.Format("m_ppresult[%d] = %.3f",m_pipeiplace + m_maxpptimes * index,m_ppresult[m_pipeiplace + m_maxpptimes * index]);
	//	    WriteToLog(signstr);

			//ƥ��ֵ��
			if(m_ppresult[m_pipeiplace + m_maxpptimes * index]  > 0)
			{
				SignalBit[index] = 0;
			}
			else 
			{
				SignalBit[index] = 1;
			}

		 	//signstr.Format("m_ppresult[%d]=%.3f",index,m_ppresult[m_pipeiplace + m_maxpptimes * index]);
		    //WriteToLog("\r\n"+ signstr + "\r\n");
			
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
				
				//��������㷨���,3-1,4-2
				for( i = 0;i < 512;i ++)   
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
					Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
				}
				
				
				if(yyy == 0)
				{   
					//10��
					m_ppvalue = CorrelationCheck(Correlation_Table10,Diffs,m_pipeiplace);
				}
				else
				{
					// 5��
					m_ppvalue = CorrelationCheck(Correlation_Table05,Diffs,m_pipeiplace);
				}
				
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
			
		//	WriteToLog("\r\n��ʼ����\r\n");	
			Sleep(100);	
			
			if(!(m_sums <= 6 ))
			{	
				//WriteToLog("��Χ����");
				return -1;
			}
			
			//31212����
			if(DecodeBCH31212(TempSignalBit))
			{

			//	signstr.Format("ƥ��λ��:m_pipeiplace=%d,���0x%0x��ģ��ţ�%d,���룺m_CollectNos��%d����λ��m_sums=%d",m_pipeiplace,Item,ModuleNum,m_CollectNos,m_sums);
			//	WriteToLog("\r\n"+ signstr + "\r\n");

        		//��һ�¾���λ,����о����λ
				if(m_CollectNos > 0)
				{
					m_checkplace  =    FALSE;
					
					//��λ�㷨,�����λ�Ƿ����ڲ�ͬ��λ����
					for(i = 0; i < m_CollectNos;i ++)
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
						dataValue = dataValue + double(TempSignalBit[10 + i]*pow((double)2,i));
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
						if(Item== 0x63 ||  Item== 0x62 )
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
							if((Item>= 0x64 && Item<=0x69) || Item==0x04)
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
						 Diffs[i]       = Diffs[i] + Diffs[256+i] + Diffs[512+i] + Diffs[768+i] + Diffn[i] + Diffn[256+i] + Diffn[512+i] + Diffn[768+i];
					 }				
					 
					 if(yyy == 0)
					 {   
						 //10��
						 m_ppvalue = CorrelationCheck(Correlation_Table10,Diffs,m_pipeiplace);
					 }
					 else
					 {
						 // 5��
						 m_ppvalue = CorrelationCheck(Correlation_Table05,Diffs,m_pipeiplace);
					 }
					 
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
			 for(  i = 0; i <  45; i ++)
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
		//	 WriteToLog("���뿪ʼ");
			
			//���յ���������,45273
			if(DecodeBCH63394(TempSignalBit,FALSE))//����ԵĻ�
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

				//16���ƽ���
				dataValue   =     0.00;
				m_sums      =        0;
				
				//7λһ�����
				for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
				{
					
					//����λ����ֽ�,7λһ����� 
					for( i = 0;i < 7; i ++)
					{  	
						
						m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow((double)2,6-i));
						
					}
					
				}
				
				//�������ͶԵĻ�
			    if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
				{
					
					//���ֵ
					for( i = 0; i < 21; i++)
					{
						dataValue = dataValue + double(SignalBit[18 + i]*pow((double)2,20-i));
					}	
					
		//			str.Format("dataValue = %d",int(dataValue));
		//			AfxMessageBox(str);
		//			WriteToLog(str);
					
					if(SignalBit[38] == 1)
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
								if(Item==0x08 || Item==0x09 || Item==0x0B || Item==0x0A) 
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
				else
				{
					//����Ͳ���
					dataValue =  -1;
					
				}

    			//str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
				//WriteToLog(str);
			
			}

			//45273����
			dataValue   =   -1;
			 
		 }
	     else
		 {
			
			//˳������������31��32��71��72Э��Ļ�
			for( i = 0; i <  63; i ++)
			{
				
				if( i < 24 )
				{
					TempSignalBit[i]    = SignalBit[23 - i];
				}
				else
				{
					TempSignalBit[i]    = SignalBit[62 - i + 24];
				}
				
			}	
			
		//	Sleep(100);

			//���յ���������,63394
			if(DecodeBCH63394(TempSignalBit,TRUE))//����ԵĻ�
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
					dataValue = dataValue + Signal[i] * 100000.00/pow((double)10,i);
					
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
					//ֻ��485����е�����,485���ͨѶ����
					return  -2;			
				}
				else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
				{
					
					//ֻ��485����е�����,������2
					return  -3;
				}
				else if( Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
				{
					
					//��פ��ʱģ��û���յ���פ������ص���
					return  -4;
					
				}	
				else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
				{  	

					//�������3��ѹA����BC�������������޹����ʡ�
					if(m_QuickReading && ((Protocol/10)== 7)  && ((ModuleNum%100) >= 12) && (Item==0x60 || Item==0xF0 || Item==0x62 || Item==0xF2 || Item==0x64 || Item==0x66 || Item==0xf4 || Item==0xf6))
					{
                       
					    //71,72�Ŀ��ٶ���
						if(Item==0x60 || Item==0xF0 || Item==0x62 || Item==0xF2)
						{																
							 
							 //3��ѹA����,BC����,��������,�޹�����
							 for(int iiiii = 0 ; iiiii < 4; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 8 ; jjjjj ++)
								 {
                                      m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*8 + jjjjj]*int(pow((double)2,7-jjjjj));
                                 }

                             }

							 if(Item==0x60 || Item==0xF0)
							 {
								 //3��ѹA����
								 m_Quick71Value[0] = m_Quick71Value[0]*2;
								 m_Quick71Value[1] = m_Quick71Value[1]*2;
								 m_Quick71Value[2] = m_Quick71Value[2]*2;
								 m_Quick71Value[3] = m_Quick71Value[3]*0.2;
							 }
							 else
							 {
								 //BC����,��������,�޹�����
								 m_Quick71Value[0] = m_Quick71Value[0]*0.2;
								 m_Quick71Value[1] = m_Quick71Value[1]*0.2;
								 m_Quick71Value[2] = m_Quick71Value[2]*0.01;
								 m_Quick71Value[3] = m_Quick71Value[3]*0.01;
							 }


						}
						else if (Item == 0x64 || Item == 0xF4)
						{											
							
							 //�壬ƽ���ȿ��ٶ���
							 for(int iiiii = 0 ; iiiii < 3; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 10 ; jjjjj ++)
								 {
                                     
									   m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*10 + jjjjj]*int(pow((double)2,9-jjjjj));
                                 
								 }

                             }
						
						}
						else if(Item == 0x66 || Item == 0xF6)
						{
							
							//�й����޹�
							for(int iiiii = 0 ; iiiii < 2; iiiii ++)
							 {
								 m_Quick71Value[iiiii] = 0;

								 for(int jjjjj = 0; jjjjj < 16 ; jjjjj ++)
								 {
                                     
									   m_Quick71Value[iiiii] = m_Quick71Value[iiiii] + Data[iiiii*16 + jjjjj]*int(pow((double)2,15-jjjjj));
                                 
								 }

                             }
							
						//	WriteToLog(strValue);

						}

    					/*
						dataValue =   0; 

						//�����Ƶ���
						for(int jjj = 0; jjj < 32; jjj ++)
						{
                            dataValue = dataValue + Data[jjj]*int(pow((double)2,31-jjj));
							
							str.Format("���ٶ���ֵ:%.2f",dataValue);
					  	    WriteToLog(str);

						}
						*/

					//	str.Format("���ٶ���ֵ:%.2f",dataValue);
					//	WriteToLog(str);

						return 1;//(dataValue + 0.001);
					}
					
					//���ٶ���,�������ݴ���һ��
					if(ModuleNum%100 <= 8 && (Item==0x0E || Item==0x8e || Item==0x10 || Item==0x90 || Item==0x12 || Item==0x92) && m_QuickReading)
					{
                        dataValue =   0;

						//�����Ƶ���
						for(int jjj = 0; jjj < 30; jjj ++)
						{
                            dataValue = dataValue + Data[jjj]*int(pow((double)2,29-jjj));
						}

					//	str.Format("���ٶ���ֵ:%d",long(dataValue));
					//	WriteToLog(str); 

						return  long(dataValue + 0.001);
					}

					//�����
					if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
					{
						//WriteToLog("����Ͷ�!");
						
						//0�Ĵ���,485����0�Ļ���������,�й�Ϊ0������
						if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
						{
							return  -2;
						}
						
						return  dataValue;
						
					}
					
					//WriteToLog("����Ͳ���!");
					
					dataValue = -1;
				}

				

				dataValue =  -1;

			}

			/*********˳������������31��71��72Э��Ļ�*/
			dataValue =  -1;
			
		}

    }
		
	return dataValue;
}


void CIFRMView::WriteP9111_CHANNEL_DOPort(int value)
{
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


/****************************  ִ������   **********************************
COMMAND  ִ������
��ʽΪ:
1��BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  ����1---ĸ��,����2---���,����3---���͵�ʱ�䵥λ��(8�ı���),����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������
2��BEGINS;COMMAND:01:����1;ENDS              ����1---���ݷ�Χ                       ִ�в��Զ������
3��BEGINS;COMMAND:02:����1;ENDS              ����1---���ݷ�Χ                       ִ����ʽ�������
4��BEGINS;COMMAND:03:����1;ENDS              ����1---���ݷ�Χ                       ִ��פ���������
5��BEGINS;COMMAND:04:����1;ENDS              ����1---���ݷ�Χ                       ִ���͵����
6��BEGINS;COMMAND:05:����1;ENDS              ����1---���ݷ�Χ                       ִ��ͣ�����
****************************************************************************/
//ͼ����ʾ
void CIFRMView::OnOwemoney() 
{  
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
    CChartDlg     dlg;
	dlg.DoModal();

}


/************************************************************************
**    �ܸ�ʽ:������BEGINS;������ѡ��;*;*;*;*;*;*;ENDS 
**
**     MESSAGE    ��ʾ��Ϣ�Ի���
**          ��ʽΪ:
**               a��BEGINS;MESSAGE:0:����;ENDS ��ʾ��ʾ�Ի���
**               b��BEGINS;MESSAGE:1:����;ENDS ��ʾ����Ի���
**
**     DATAS      ���ݴ���
**         �յ��ĸ�ʽ������:
**         a��BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
**         b��BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
**         c��BEGINS;DATAS:2:����;�������;ENDS      ���ݴ��ͽ�����־
**         d��BEGINS;DATAS:3:StopData;ֹͣ;ENDS      ����ֹͣ��ť���
** 
**                                      
**     SEND       ��������(���б�����ʾ)
**          ��ʽΪ:
**                   BEGINS;SEND:����:��ѯ����;ENDS Ҫ�䴫����������������
** 												 
** 
**    COMMAND  ִ������
**    ��ʽΪ:
**    1��BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  ����1---ĸ��,����2---���,����3---���͵�ʱ�䵥λ��(8�ı���),����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������
**    2��BEGINS;COMMAND:01:����1;ENDS              ����1---���ݷ�Χ                       ִ�в��Զ������
**    3��BEGINS;COMMAND:02:����1;ENDS              ����1---���ݷ�Χ                       ִ����ʽ�������
**    4��BEGINS;COMMAND:03:����1;ENDS              ����1---���ݷ�Χ                       ִ��פ���������
**    5��BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
**                         ����1---����         ����2---���                   ����3---������Χ
**    	                   ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
**    	                   ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
**    	                   ����10--���         ��д������Բ���,����������
****************************************************************************/
void CIFRMView::OnOnCommMscomm() 
{
	
	switch(m_Com.GetCommEvent()) 
	{ 
	case 1: 
		{
		
			break; 
		}
	case 2: 
		{   
		    //���ն��������ݷ�ʽ,�������ܵ����� 
			BinarySystemReceive();
			break; 
		}
	default: 
		{
			// �����¼�����,��������� 
			m_Com.SetOutBufferCount(0);  
			break; 
		}

	}

}

/***************************************************************
��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
����λ 0-��У��,1����У��,2��żУ��
����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
ֹͣλ 0-1     ,1-1.5    ,2-2
//�����Ʒ�ʽ����
**************************************************************/
void CIFRMView::OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex)
{

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
    
	//ֹͣλ 0-1,1-1.5,2-2
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
	m_Com.SetPortOpen(TRUE);         //�򿪶˿�
	m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��
	m_Com.SetInputMode(1);           //0 �ı���ʽ 1��������ʽ
    
	ParameterStr.Format("%s,%s,%s,%s",SpeedIndexstr,CheckIndexstr,DataIndexstr,StopIndexstr);//���ò����� ������λ ������λ ��ֹͣλ	
	m_Com.SetSettings(ParameterStr); //"600,n,8,1"
	m_Com.SetRThreshold(1);          //ÿ����1���ַ��ʹ���1�ν����¼�
	m_Com.SetInputLen(0);            //ÿ�ζ�ȡһ���ַ�,��������ʽ
	m_Com.GetInput();                //���ԭ�е�����
	
}

//�κ�
void CIFRMView::Dial(CString m_strPhoneNumber,BOOL IfVoice)
{
	
	StatusStr = "";
	CString          strTemp;
	m_Com.SetDTREnable(TRUE);//Open DTR
	m_Com.SetRTSEnable(TRUE);//Open RTS ������--->moden������
		
	SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM��λ��Reset�������¶�ȡԤ���0����趨����ֵ��
	Sleep(500);

	if(IfVoice)
	{
		//����
		strTemp = "ATM1\r\n";//
	}
	else
	{
		//����
		strTemp = "ATM0\r\n";//
	}

	//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
	//Str             �����ַ�
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	SelectSendString(1,strTemp,FALSE,FALSE,FALSE);
  	Sleep(500);

	//strTemp = "ATDT" + m_strPhoneNumber + "\r\n"; ATDT �����κ�
	strTemp = "ATD" + m_strPhoneNumber + "\r\n";
	//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
	//Str             �����ַ�
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	SelectSendString(1,strTemp,FALSE,FALSE,FALSE);

	Sleep(300);

	//�绰�κŵı�־
	m_IsDialConnectting    = FALSE;


}

//�Ͽ�����
void CIFRMView::DisConnect(short kinds)
{	
	switch(kinds)
	{
	case 0:
		{   
			//�򿪴���
			if(m_Com.GetPortOpen())    
			{
				m_Com.SetPortOpen(FALSE);
			}
			break;
		}
	case 1:
		{
			if(m_Com.GetCDHolding())
			{
				//�����Զ�̰�Ļ�
				if(!AppInfo::Instance().m_WhichKind)
				{	
					SelectSendString(1, "BEGINS;COMMAND:28:^CLOSED^MODEM?^OK!;ENDS", FALSE,FALSE,TRUE);
				}
								
				SelectSendString(1,"+++",FALSE,FALSE,FALSE);     //�����յ���������+++, ֮��3������û���κ�����, Modem�ͽ�������ģʽ, ��������AT�����������
				Sleep(3200);

				SelectSendString(1,"ATH0\r\n",FALSE,FALSE,FALSE);//�Ͽ��绰����
				Sleep(500);
				
				SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM��λ��Reset�������¶�ȡԤ���0����趨����ֵ��
				Sleep(500);

				//����Ǳ��ذ�
				if(AppInfo::Instance().m_WhichKind)
				{
					//�Զ�Ӧ��״̬
					AutoAnswer(FALSE);
				}

				status("���κ������ѶϿ���");
				
			}
			break;
		}
	case 2:
		{
			if(m_IsConnect)
			{
				//�����Զ�̰�Ļ�
				if(!AppInfo::Instance().m_WhichKind)
				{			
		            SelectSendString(2, "BEGINS;COMMAND:28:^CLOSED^INTERNET?^OK!;ENDS", FALSE,FALSE,TRUE);
					Sleep(100);
				}
				
				OnCloseWinsock();
			}
   			break;
		}

	}

	//TRUE ���վ�汾  FALSE��ְ�
	if(!AppInfo::Instance().m_WhichKind)
	{
		//�����Զ�̰�Ļ�
		m_StartRead = FALSE;
		status("                     ");
	}

}

/******************************************************************
**         �յ��ĸ�ʽ������:
**         a��BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
**         b��BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
**         c��BEGINS;DATAS:2:����;�������;ENDS      ���ݴ��ͽ�����־
**         d��BEGINS;DATAS:3:StopData;ֹͣ;ENDS      ����ֹͣ��ť���
*******************************************************************/
//ʵʱ������ʾ����
void CIFRMView::RealTimeReceiveData(CString str)
{	
	CString  data,GetStr,StrTemp;
	CString    FileName,DataName;
	CString         TempStr[27];		
	CFileFind            finder; 
    int           k =         0;

	BOOL   m_IfRepeat =   FALSE;//�ϵ�ʱ�Ƿ���д�б�
	
	//�Ѿ�ȥ����"BEGINS;"�� ";ENDS",ֻʣ���м�Ķ�����
	switch(atoi(str.Mid(6,1)))
	{
	case 0:
		{
			//BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
			k   =  str.Find(';');
			status("�����ڽ������ݣ����Ժ�...��");
			
			//��ʾ�����ض���
			OperationAnimation(TRUE);

			if(k != -1)
			{
				data             =    str.Right(str.GetLength() - k - 1);
				m_PassRecords    =    0;
				StrTemp = str.Left(k);
				//�õ����͵����ݱ���
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
    			//////////////////////////////////
				//dataΪ����+";0"��"0;"
				//;0 Ϊ���Ƕϵ㴫�� ;1�Ƕϵ㴫��
				k = atoi(data.Right(1));

				//����
				data = data.Left(data.GetLength() - 1);//-2);
                //////////////////////////////////////////////
				
				//�ļ���	
                FileName.Format("%s%s.txt",GetFolder(),DataName);
                
				//���Ƕϵ㴫��
				if(k == 0)
				{
					//�������������������
					if(finder.FindFile(FileName) != 0) 
					{ 
						//���ڴ��ļ��Ļ���ɾ�����ļ�
						::DeleteFile(FileName);
					}

				}
				else
				{
					
					//�Ƕϵ㴫��
					m_IfRepeat = TRUE;
					
					//�������д�б�Ļ�
					if(!m_IfRepeat)
					{
						//������Ϊԭ�����ļ�¼����
						m_PassRecords = m_Grid.GetColumnCount();
					}
					else
					{
						//���ļ���ȡ������
						m_PassRecords = GetDataLines(FileName);
					}
	
				}

				//����ǲ�֧�ֶϵ��֧�ֶϵ㵫Ҫ��д�б���
				if(k == 0 || (k== 1 && m_IfRepeat))
				{
					//��ʾ�б�ͷ
                    ShowGridHead(data);
					SurrenderWindowMessage();
				}
						
				m_StartRead  =  TRUE;

				//���Խ���������
				m_ReceiveOk  =  TRUE;

			}
			break;
		}
    case 1:
		{
			//BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
			//���ܽ�������
			if(!m_ReceiveOk)
			{
				return;
			}

	        //��ʾ�����ض���
			OperationAnimation(TRUE);

			m_PassRecords++;
			CString     strValue;
			CString m_FieldNames;//�ֶ�����
			long        ModuleNo;//ģ���

			k   =  str.Find(';');
			
			if(k != -1)
			{
				
				data    = str.Right(str.GetLength() - k - 1);
				StrTemp = str.Left(k);
				//�õ����͵����ݱ���
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
				
				//�ļ���	
				FileName.Format("%s%s.txt",GetFolder(),DataName);
			    int    colum     = 0;
				
				while(data.Find(';') != -1)
				{
					
					k   =  data.Find(';');
					
					if(k != -1)
					{
						
                        TempStr[colum] =  data.Left(k);
						//��,�ֿ�
						GetStr = GetStr + TempStr[colum] + ",";
						
						TempStr[colum] = " " + TempStr[colum];
						
						data  = data.Right(data.GetLength() - k - 1);
						
						colum++;
					}
					
				}
				
				
				TempStr[colum] = data;
				
				GetStr = GetStr + TempStr[colum];
				
				//д���ı��ļ�
				FILE *text;
				if((text = fopen(FileName,"a")) != NULL)
				{
					fputs(GetStr + "\r\n",text);
					fclose(text);
				}
				
				//���������
				if(colum > 0)
				{	

					//add 2004.10.13if(colum + 1 == m_list.GetColumns() && m_list.GetColumns()>0)
					if(colum + 1 == m_Grid.GetColumnCount() && m_Grid.GetColumnCount() > 0)
					{
						//��ʾ����б�
						AddlistItem(TempStr,colum + 1);
					}
                    
				    //IfWriteData     �Ƿ�д�����ݿ� FALSE---��д TRUE---д
                    //WhichTable      �ĸ��� 0----���ݱ� 1----פ����
					if(DataName == "ZSDB_DATA")
					{
						//��ʽ���� 
						if(TempStr[11].Find("������") != -1)
						{
							return;
						}
						
						//ģ���
						ModuleNo = atol(TempStr[5]);
						
						//ʱ��ȥ�ո�
						TempStr[12].TrimLeft();
						TempStr[12].TrimRight();
						
    					TempStr[10].TrimLeft();
						TempStr[10].TrimRight();
						
						//���ݴ�����ֵ���ж���ʲôֵ 
						if(TempStr[10] == "�й����")
						{
							m_FieldNames = "REALTIME_WORKDEGREE";
						}
						else if(TempStr[10] == "�ۻ��й����")
						{
							m_FieldNames = "REALTIME_WORKDEGREETOTAL";
						}
						else if(TempStr[10] == "�޹����")
						{
							m_FieldNames = "REALTIME_LOSEDEGREE";
						}
						else if(TempStr[10] == "�ۻ��޹����")
						{
							m_FieldNames = "REALTIME_LOSEDEGREETOTAL";
						}
						else if(TempStr[10] == "A�����")
						{
							m_FieldNames = "REALTIME_ACURRENT";
						}
						else if(TempStr[10] == "B�����")
						{
							m_FieldNames = "REALTIME_BCURRENT";
						}
						else if(TempStr[10] == "C�����")
						{
							m_FieldNames = "REALTIME_CCURRENT";
						}
						else if(TempStr[10] == "A���ѹ")
						{
							m_FieldNames = "REALTIME_AVOLTAGE";
						}
						else if(TempStr[10] == "B���ѹ")
						{
							m_FieldNames = "REALTIME_BVOLTAGE";
						}
						else if(TempStr[10] == "C���ѹ")
						{
							m_FieldNames = "REALTIME_CVOLTAGE";
						}
						else if(TempStr[10] == "��ѹ")
						{
							
							//������һ���ģ��
							if(TempStr[8].Find('A') != -1)
							{
								m_FieldNames = "REALTIME_AVOLTAGE";
							}
							else if(TempStr[8].Find('B') != -1)
							{
								m_FieldNames = "REALTIME_BVOLTAGE";
							}
							else
							{
								m_FieldNames = "REALTIME_CVOLTAGE";
							}
							
						}
						
						//������ʽ�������
						//REALTIME_MODULENO ģ��� , REALTIME_PROTOCOL ��ӦЭ��   
						strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_TRANSCRIBETIME,REALTIME_PROTOCOL) VALUES (%d,%.2f,'%s',%d)",m_FieldNames,ModuleNo,atof(TempStr[11]),TempStr[12],0);
					
						//����SQL���
						CDataBaseInstance::ExecuteDataBaseSQL(strValue);

						
					}
					else if(DataName == "ZLDB_DATA")
					{	

						//פ������,�й��ϵ�ģ��д�����
						if(TempStr[11].Find("������") != -1)
						{
							return;
						}
						
						//ģ���
						ModuleNo = atol(TempStr[5]);
						
						//ʱ��ȥ�ո�
						TempStr[12].TrimLeft();
						TempStr[12].TrimRight();
						
						//פ�����ݱ�,פ������Ļ�,����TB_GARRISON����
						strValue.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",ModuleNo,TempStr[12]/*פ��ʱ��*/);
						
						TempStr[10].TrimLeft();
						TempStr[10].TrimRight();
						
						
						//���ݴ�����ֵ���ж���ʲôֵ 
						if(TempStr[10] == "�й����")
						{
							m_FieldNames = "GARRISON_WORKDEGREE";
						}
						else if(TempStr[10] == "�ۻ��й����")
						{
							m_FieldNames = "GARRISON_WORKDEGREETOTAL";
						}
						else if(TempStr[10] == "�޹����")
						{
							m_FieldNames = "GARRISON_LOSEDEGREE";
						}
						else if(TempStr[10] == "�ۻ��޹����")
						{
							m_FieldNames = "GARRISON_LOSEDEGREETOTAL";
						}
						else if(TempStr[10] == "A�����")
						{
							m_FieldNames = "GARRISON_ACURRENT";
						}
						else if(TempStr[10] == "B�����")
						{
							m_FieldNames = "GARRISON_BCURRENT";
						}
						else if(TempStr[10] == "C�����")
						{
							m_FieldNames = "GARRISON_CCURRENT";
						}
						else if(TempStr[10] == "A���ѹ")
						{
							m_FieldNames = "GARRISON_AVOLTAGE";
						}
						else if(TempStr[10] == "B���ѹ")
						{
							m_FieldNames = "GARRISON_BVOLTAGE";
						}
						else if(TempStr[10] == "C���ѹ")
						{
							m_FieldNames = "GARRISON_CVOLTAGE";
						}
						else if(TempStr[10] == "��ѹ")
						{
							
							//������һ���ģ��
							if(TempStr[8].Find('A') != -1)
							{
								m_FieldNames = "GARRISON_AVOLTAGE";
							}
							else if(TempStr[8].Find('B') != -1)
							{
								m_FieldNames = "GARRISON_BVOLTAGE";
							}
							else
							{
								m_FieldNames = "GARRISON_CVOLTAGE";
							}
							
						}
						
						//ԭ��פ������û�д�פ��ʱ�������
						if(CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", strValue) < 1)
						{
							//GARRISON_MODULENO ģ��� , GARRISON_PROTOCOL ��ӦЭ��  , GARRISON_HALTTIME פ��ʱ��
							strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,%s,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s','%s')",m_FieldNames,ModuleNo,atof(TempStr[11]),0,TempStr[12],TempStr[12]);
						}
						else
						{   
							//ԭ��פ�������д�פ��ʱ�������,���滻ԭ������
							//����Ƕ��й���Ȼ򶳽���,�����ԭ���ı��
							strValue.Format("UPDATE TB_GARRISON SET %s = %.2f,GARRISON_HALTTIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_FieldNames,atof(TempStr[11]),TempStr[12],ModuleNo,TempStr[12]);
						}
				
						//����SQL���
						CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										
						
					}
				    
					m_StartRead =  TRUE;
				
                 }
				
			}
			m_StartRead =	TRUE;			
			break;
		}
	case 2:
		{
			
			//���ܽ�������
			if(!m_ReceiveOk)
			{
				return;
			}

			BOOL  m_IsOk = FALSE;
			m_StartRead         =        FALSE;
			m_ReceiveOk         =        FALSE;
			//BEGINS;DATAS:2:����;�������;ENDS      ���ݴ��ͽ�����־
			k   =  str.Find(';');
			
			if(k != -1)
			{
				
				data  = str.Right(str.GetLength() - k - 1);
				StrTemp = str.Left(k);
				//�õ����͵����ݱ���
				DataName = StrTemp.Right(StrTemp.GetLength() - 8);
				//�ļ���	
				FileName.Format("%s%s.txt",GetFolder(),DataName);
				//��ʾ�ж�������¼��������
				data.Format("�����������,��¼%d��,�ļ�:��װĿ¼+%s.TXT",m_PassRecords,DataName);
				status(data);

				//��ʾ�����ض���
			    OperationAnimation(FALSE);
				
				//�������������������
				if(finder.FindFile(FileName) != 0) 
				{ 
	
					if(DataName != "ZSDB_DATA" && DataName != "ZLDB_DATA" && DataName != "TB_HISTORYDATAS")
					{
						
                        //���ذ棬Զ�̴���������
						if(	AppInfo::Instance().m_WhichKind == TRUE)
						{
						 
							//�����ظ����ݼ�¼ m_DataName   ����,TxtFileName  �����ı��ļ�
							DealRepeatRecord(DataName,FileName);
							
							//������Ϣ
							SendContionStr.Format("����������ϣ���Ӽ�¼%d����ע���ظ���¼��ɾ�����",m_PassRecords);
							status(SendContionStr);

                    		//������Ϣ
							SendContionStr.Format("BEGINS;MESSAGE:0:Զ�̻��������������,��������ݼ�¼%d����\r\nע�������ظ���¼ʱ��ɾ���ظ���¼����ӣ�;ENDS",m_PassRecords);
							SendMessage(WM_EVENT, 4, 0);
							
							//������û����ݱ���̨��
							if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
							{
								//���ؼ�����ˢ��һ��
								RefreshTree();
							}

								
						}
						else
						{

							data.Format("���ݴ�����ϣ������Զ�̴����Ĺ���%d�����ݼ�¼��\r\n���뱾�ض�Ӧ�Ŀ������?",m_PassRecords);
													
							if(MessageBox(data,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
							{
								//�����ظ����ݼ�¼ m_DataName   ����,TxtFileName  �����ı��ļ�
							    DealRepeatRecord(DataName,FileName);

								//������û����ݱ���̨��
								if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
								{
									//���ؼ�����ˢ��һ��
									RefreshTree();
								}

							}
											
						}
							
						
					}
					//���Ƕ�ģ�����ɵ����Ļ�
							
				}
				//������������ݴ����ļ��еĻ�
				
			}

			break;
			//�ܽ�������
		}
		
	}
	
}


//��ʼ�����ݿ�
void CIFRMView::InitGrid(CString table,CString BeginTime,CString EndTime)
{

	//�����ݿ�
	CDatabase               db;
	CString    strSql,strValue;
	
	//��ʼʱ��
	short m_year,m_month,m_day,m_hour,m_minuter,m_second;
    m_year       =         atoi(BeginTime.Mid( 0,4));
    m_month      =         atoi(BeginTime.Mid( 5,2));
    m_day        =         atoi(BeginTime.Mid( 8,2));
    m_hour       =         atoi(BeginTime.Mid(11,2));
	m_minuter    =         atoi(BeginTime.Mid(14,2));
    m_second     =         atoi(BeginTime.Mid(17,2));

	if(m_minuter == 0 && m_second == 0)
	{
       BeginTime.Format("%d-%d-%d %dʱ",m_year,m_month,m_day,m_hour);
	}
	else
	{   
		if(m_second == 0)
		{
		   BeginTime.Format("%d-%d-%d %d:%d",m_year,m_month,m_day,m_hour,m_minuter);
		}
		else
		{
            BeginTime.Format("%d-%d-%d %d:%d:%d",m_year,m_month,m_day,m_hour,m_minuter,m_second);
		}
	} 
	
	//��ֹʱ��
	m_year       =         atoi(EndTime.Mid( 0,4));
    m_month      =         atoi(EndTime.Mid( 5,2));
    m_day        =         atoi(EndTime.Mid( 8,2));
    m_hour       =         atoi(EndTime.Mid(11,2));
	m_minuter    =         atoi(EndTime.Mid(14,2));
    m_second     =         atoi(EndTime.Mid(17,2));

	if(m_minuter == 0 && m_second == 0)
	{
       EndTime.Format("%d-%d-%d %dʱ",m_year,m_month,m_day,m_hour);
	}
	else
	{   
		if(m_second == 0)
		{
			EndTime.Format("%d-%d-%d %d:%d",m_year,m_month,m_day,m_hour,m_minuter);
		}
		else
		{
            EndTime.Format("%d-%d-%d %d:%d:%d",m_year,m_month,m_day,m_hour,m_minuter,m_second);
		}
	}

	//�õ��޸�״̬
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("ԭ���������޸�,���汨���ļ���?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			OnSavereportas(); 
		}

	}
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		
		//�õ���¼����
		long fields = CDataBaseInstance::GetAllRecordsCount(table,"ALL"); 
		
		//���û�м�¼
		if(fields < 1)
		{	
			//�ر����ݿ�
			db.Close();
			MessageBox("û�����ݿ����ɱ�����"," ",MB_OK|MB_ICONWARNING);
			return;
		}
		
		strSql.Format("SELECT * FROM %s",table);
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
		
		//ɾ�����е�����
	    m_Grid.DeleteAllItems();
		
		m_IsHistory    =  FALSE;//�Ƿ���ʾ��ʷ����
		
		//���
		m_Grid.GetDefaultCell(FALSE,TRUE)->SetFormat(DT_CENTER|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS|DT_SINGLELINE);
        m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(fields + 1);	        //��
		m_Grid.SetColumnCount(nFields + 1);     //��
		m_Grid.SetGridLineColor(RGB(212,208,200));    //RGB(0,0,0)����ɫ
		m_Grid.SetColumnWidth(0, 80);
		m_Grid.SetBkColor(RGB(255,255,255));

		for(int i = 0;i < nFields + 1; i++)
		{

			if(i == 0)
			{
				//���������
				m_Grid.SetItemTextFmt(0, i, "���");
			}
			else
			{
				//������
				rs.GetODBCFieldInfo(i - 1,fieldinfo);
				
				fieldinfo.m_strName.TrimLeft();
				fieldinfo.m_strName.TrimRight();
				
				if(fieldinfo.m_strName.Find("����") != -1 || fieldinfo.m_strName.Find("����") != -1 )
				{
					fieldinfo.m_strName.Replace("����",EndTime);
					fieldinfo.m_strName.Replace("����",EndTime);
				}
				else
				{
					
					if(fieldinfo.m_strName.Find("�ϴ�") != -1 || fieldinfo.m_strName.Find("����") != -1 )
					{
						fieldinfo.m_strName.Replace("�ϴ�",BeginTime);
						fieldinfo.m_strName.Replace("����",BeginTime);
					}

				}
				
				if(fieldinfo.m_strName.Find("����") != -1)
				{
					fieldinfo.m_strName.Replace("����","");
				}

				m_Grid.SetItemTextFmt(0, i, fieldinfo.m_strName);
			}
		
		}
		
		status("�������ɴ�ӡ�������Ժ�...");
		ShowProgressCtrl(TRUE);
		
		//��Χ
		SetProgressCtrlRange(0, fields,1);

		
		//��������Ϣ
		for(int j = 0;j < fields; j++)
		{
			//�ֶ���
			SurrenderWindowMessage();//����window����Ȩ
		
			for(int i = 0; i < nFields + 1; i++)
			{
				
				if(i == 0)
				{
					strValue.Format("%6d",j + 1);
				}
				else
				{	
					rs.GetFieldValue(int(i - 1),strValue);
					
					strValue.TrimLeft();
					strValue.TrimRight();

					//���ֵΪ�յĻ�
					if(strValue.IsEmpty())
					{
						strValue.Format(" ");
					}
					else
					{
						//�е�Ϊ����
						if(strValue.Find(".") != -1)
						{
							strValue.Format("%.2f",atof(strValue));
						}

						//�����0.00�Ļ�,��0��
						if(strValue == "0.00")
						{
                            strValue = " 0";
						}
						
					}
								
				}
				
				//��ʾ����
				m_Grid.SetItemTextFmt(j + 1,i,strValue);
				
			}
			
			//���»�һ����¼
			rs.MoveNext();
            
			//����������
			SetProgressCtrlSetIt();
			
		}

		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	
        m_Grid.ShowWindow(SW_SHOW);
		ShowProgressCtrl(FALSE);//��������
		status("                   ");
    	m_Grid.SetModified(TRUE,-1,-1);	//�����޸�״̬
	}
	
}

//�κ�����
BOOL CIFRMView::Connect(BOOL  ShowMessage,BOOL IfVoice)
{
	SurrenderWindowMessage();
	
	SelectSendString(1,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM��λ��Reset�������¶�ȡԤ���0����趨����ֵ��
	Sleep(500);
	SurrenderWindowMessage();

	if(IfVoice)
	{
		//����	
    	SelectSendString(1,"ATM1\r\n",FALSE,FALSE,FALSE);
	}
	else
	{
		//����
		SelectSendString(1,"ATM0\r\n",FALSE,FALSE,FALSE);
	}

	Sleep(500);
	SurrenderWindowMessage();

	//״̬����ʾ��Ϣ
	StatusStr   =         "";

	//Modem�Զ��ȴ�����	
	SelectSendString(1,"ATS0=1\r\n",FALSE,FALSE,FALSE);

	Sleep(500);
    SurrenderWindowMessage();
   	
	if(ShowMessage)
	{
		//ȫ����Ϊ��д
	    StatusStr.MakeUpper();
		
		//���û�з���ֵOK
		if(StatusStr.Find("OK") == -1)
		{
			MessageBox("�Զ�Ӧ������ʧ��,����MODEM�Ƿ�\r\n�������ҵ�Դ�Ƿ��Ѵ򿪣�","����",MB_OK|MB_ICONWARNING);
			return FALSE;
		}

	}
	else
	{
		//ȫ����Ϊ��д
	    StatusStr.MakeUpper();

		//���û�з���ֵOK
		if(StatusStr.Find("OK") == -1)
		{	
			//��ʾ״̬����Ϣ
		    StatusStr = "���Զ�Ӧ��ʧ�ܡ�";
			SendMessage(WM_EVENT, 1, 0);

	    	//WriteToLog(StatusStr);
			return FALSE;
		} 
		
		StatusStr = "���Զ�Ӧ��ɹ���";
		SendMessage(WM_EVENT, 1, 0);

		//WriteToLog(StatusStr);
	
	}

    //�Զ�Ӧ�����
	SelectSendString(1,"AT&W\r\n",FALSE,FALSE,FALSE);
	Sleep(500);
	SurrenderWindowMessage();

	m_Com.SetDTREnable(TRUE);//Open DTR
	return TRUE;
	
}

//���ݿ��ת���ı��ļ�
BOOL CIFRMView::WriteDataToTextFile(CString dataname,CString Sqlstr,long records,CString filename)
{
	//�����ı�ָ��	
	FILE*     text;
	CString GetStr;
	
	//�����ݿ�
	CDatabase   db;
	
	if((text = fopen(filename,"w"))==NULL)
	{
		return  FALSE;
	}
	
	status("���ڱ����" + dataname + "���ݳ��ı��ļ�" + filename + "�����Ժ�...");
	ShowProgressCtrl(TRUE);
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset   rs(&db);
		SetProgressCtrlRange(0, records,1);
		rs.Open(CRecordset::forwardOnly,Sqlstr);
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();
		
		//���û���Ϣ
		for(int  j = 0;j < records; j++)
		{
			
			GetStr  = "";
			
			//�ֶ���
			for(int i = 0; i < nFields; i++)
			{
				
				rs.GetFieldValue(int(i),Sqlstr);
				
				Sqlstr.TrimRight();
				
				if(Sqlstr.GetLength() < 18)
				{
					
					if(Sqlstr.Find('.') != -1)
					{
						Sqlstr.Format("%.2f",atof(Sqlstr));
					}
					
				}
				
				//���һ���ֶ�
				if(i == nFields - 1)
				{
					GetStr = GetStr + Sqlstr;
				}
				else
				{
					GetStr = GetStr + Sqlstr + ",";
				}
				
			}
            
			GetStr.TrimLeft();
            GetStr.TrimRight();

			int k = GetStr.GetLength();

			for(int ii = 0; ii < 300 - k;ii ++)
			{
				GetStr = GetStr + " ";
			}

			fputs(GetStr + "\r\n",text);
			
			SetProgressCtrlSetIt();
			
			//�»�һ����¼
			rs.MoveNext();
		}
		
		
		//�ر����ݿ�
		rs.Close();
		
		db.Close();
		
		fclose(text);
		//����״̬��
		status("                            ");
		ShowProgressCtrl(FALSE);
		return TRUE;

	}

	return FALSE;
}


//�۸����ݱ����
void CIFRMView::OnPrice() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	//������ݿ��Ƿ��
	if(m_PriceSet->IsOpen())
	{
		m_PriceSet->Close();
	}
	
	//���ݱ���Ƿ���ȷ
	if(m_PriceSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		CELKindDlg  dlg(m_PriceSet.get(),0);
		dlg.DoModal();	
		
		//������ݿ��Ƿ��
		if(m_PriceSet->IsOpen())
		{
			m_PriceSet->Close();
		}

	}
	else
	{
		MessageBox("���ݿ��򿪴���"," ",MB_OK|MB_ICONWARNING);
	}
	
}

//���ɳ����嵥
void CIFRMView::FormChaoBiaoData(CString SqlStr,CString BeginTime,CString EndTime)
{
	CString                                     Str;
	status("�������ɳ������嵥ͳ�Ʊ����Ժ�...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
    
	BeginTime.TrimLeft();
    EndTime.TrimRight();

	//����
	if(IsCurveTableExist("TB_EXCERPTION"))
	{
		//ɾ��ԭ���Ŀ��
		Str.Format("DROP TABLE TB_EXCERPTION");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	SetProgressCtrlSetIt();
	
	Str = "CREATE TABLE [dbo].[TB_EXCERPTION] (\
		[��̨����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
		[�û����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
		[ԭ����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[ģ���] [bigint] NULL ,\
		[��������] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
		[�õ����] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
		[����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		[�ϴζ���] [float] NULL ,\
		[���ζ���] [float] NULL ,\
		[����] [int] NULL ,\
		[����] [float] NULL,\
		[���] [float] NULL ,\
		[���] [float] NULL \
    	) ON [PRIMARY]";
		
	//�������ݱ�
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
//	WriteToLog(Str);
	SetProgressCtrlSetIt();
	
    //�˴ζ�������SQL����õ����
	Str.Format("INSERT TB_EXCERPTION(��̨����,�û����,����,ԭ����,ģ���,��������,�õ����,����,�ϴζ���,���ζ���,����,����,���,���)\
		        SELECT  USER_TRANSFORMERNO AS ��̨����,RTRIM(LTRIM(a.USER_NO)) AS �û����,RTRIM(LTRIM(a.USER_NAME)) AS ����,RTRIM(LTRIM(a.USER_OLDNO)) AS ԭ����,a.USER_MODULENO,a.USER_AMMETERNO,f.ELECTRICITY_KIND,'%s',\
				d.GARRISON_WORKDEGREE,e.GARRISON_WORKDEGREE,a.USER_MULTIPLE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2),f.ELECTRICITY_PRICE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2)*f.ELECTRICITY_PRICE\
					   FROM TB_USER a ,TB_GARRISONBAK d,TB_GARRISONBAK e,TB_ELECTRICITY f WHERE (%s) AND f.ELECTRICITY_NO=a.USER_ELECTRICITYKIND AND d.GARRISON_MODULENO=a.USER_MODULENO AND e.GARRISON_MODULENO=a.USER_MODULENO  AND d.GARRISON_HALTTIME='%s' AND e.GARRISON_HALTTIME='%s'","�й����",SqlStr,BeginTime,EndTime);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

//	WriteToLog(Str);
    SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  

}

//�������ݱ�����
void CIFRMView::OnDatapass() 
{
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
    CString      str;
	
	CSelectTableDlg dlg;
	
	if(dlg.DoModal() == IDOK)
	{
		
		switch(dlg.m_selects)
		{
		case 0:
			{
				
              	//��ʽ: BEGINS;SEND:0:����:��ѯ����;ENDS   ��������,��֧�ֶϵ㴫��
				str.Format("BEGINS;SEND:0:%s:%s;ENDS",dlg.StrTable,dlg.Sqlstr);
			    
				//Զ�̷�����ȡ����Ϣָ��
				if(SelectSendString(m_sendkind, str,TRUE,TRUE,TRUE) == TRUE)
				{ 
					//ֹͣ��������
	                m_StopPassing = FALSE;
					m_GetErrors = 0;
				}
				
				m_StartRead = FALSE;
				break;

			}
		case 1:
			{
			
				if(m_Com.GetPortOpen() || m_Com.GetCDHolding() || m_IsConnect)
				{
					m_GetErrors   =   0;
					//������������ļ�¼
					CString m_filename,m_SqlStr;
					m_filename.Format("%s%s%s",GetFolder(),dlg.StrTable,".TXT");
					
					long fields = CDataBaseInstance::GetAllRecordsCount(dlg.StrTable,dlg.Sqlstr);
					
					if(dlg.Sqlstr == "ALL")
					{
						m_SqlStr.Format("SELECT * FROM %s",dlg.StrTable);
					}
					else
					{
						m_SqlStr.Format("SELECT * FROM %s WHERE %s",dlg.StrTable,dlg.Sqlstr);
					}
					
					if(fields > 0)
					{	
						//ֹͣ��������
	                    m_StopPassing = FALSE;
						//���߶Է��ж�������
						WriteDataToTextFile(dlg.StrTable,m_SqlStr,fields,m_filename);	
						//���߶Է�û������
						SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS",dlg.StrTable,fields);
						SendMessage(WM_EVENT, 4, 0);
					}
					else
					{
						m_StartRead = FALSE;
						//���߶Է�û������
						MessageBox("�Բ��𣬴˱���û�������������������Ϣ!","����",MB_OK|MB_ICONWARNING);
						return;
					}
					
				}
				else
				{
					MessageBox("�˿ڴ򿪴���!","����",MB_OK|MB_ICONWARNING);
					return;
				}
				break;
			}
		case 2:
			{
				//Զ�����
				if(	AppInfo::Instance().m_WhichKind == FALSE)//TRUE ���վ�汾  FALSE��ְ�
				{	
					
					//��ʽ: BEGINS;SEND:0:����:��ѯ����;ENDS   ��������,���б�����ʾ���� 
					//str.Format("BEGINS;SEND:0:%s:%s;ENDS",dlg.StrTable,dlg.Sqlstr);
					if(dlg.Sqlstr == "ALL")
					{
					   str.Format("BEGINS;COMMAND:12:DELETE FROM %s ;ENDS",dlg.StrTable);
					}
					else
					{
					   str.Format("BEGINS;COMMAND:12:DELETE FROM %s WHERE %s;ENDS",dlg.StrTable,dlg.Sqlstr);
					}
					
				    //Զ�̷�������Է����ָ��
					if(SelectSendString(m_sendkind, str, TRUE,TRUE,TRUE) == TRUE)
					{
						//m_StartRead = TRUE;
					}
					else
					{
						m_StartRead = FALSE;
					}
					
				}

				break;
			}
		}

	}
	
}


void CIFRMView::OnUpdateConnectsuccess(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(FALSE);
	return;

	CString      TimeStr; 
	
	//TRUE-���վ�汾  FALSE-��ְ�
	if(AppInfo::Instance().m_WhichKind)
	{

		//�������״̬��ͨ�������
		if(m_IsConnect && m_Com.GetCDHolding())
		{	
		
			if(m_DoubleConnected)
			{
				
				m_sendkind        =     1;
				m_DoubleConnected = FALSE;

		    	//�ر�Զ��è
				SelectSendString(1, "BEGINS;COMMAND:32:�����ذ����������Զ�̰�������(æ)���κ����ӽ��Ͽ���;ENDS",TRUE,FALSE,TRUE);
				Sleep(200);

				DisConnect(1);
				Sleep(200);
				
				//����Զ�Ӧ��ģʽ
				AutoAnswer(FALSE);
				m_sendkind = 2;
          
				return;

			}
		
		}
		else if(m_Com.GetCDHolding())
		{  
			//��è������״̬
			m_DoubleConnected = TRUE;
			m_sendkind        =    1;

		}
		else if(m_IsConnect)
		{
			//�Ǿ�����������
            m_DoubleConnected = TRUE;
			m_sendkind        =    2;

		}

	} 


	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{
		 	pCmdUI->Enable(m_Com.GetPortOpen());
			break;
		}
	case 1:
		{	//�绰�κŵı�־,���ǵ�ְ��ʱ��
	        pCmdUI->Enable(m_Com.GetCDHolding());
        
			if(m_Com.GetCDHolding() && !m_IsDialConnectting)
			{
		        
				if(ReadMeterThread != NULL)
				{	
					//��ͨʱֹͣԭ���Ĺ���
				    m_StartRead    =   FALSE;
                    SurrenderWindowMessage();
					Sleep(1000);
				    SurrenderWindowMessage();
				}
				
				m_others         =            FALSE;//				
			    status("���κ����ӳɹ���");
				ReceiveByteArray.RemoveAll();

				m_IsDialConnectting =   TRUE;	
			    m_IfChangeData      =   TRUE;//�޸Ľ������ݱ�־	
			    m_PassErrortimes    =      0;//���������Ϊ0
			
			}
			else
			{
               
				if(!m_Com.GetCDHolding() && m_IsDialConnectting)
				{
					
			        m_PassErrortimes    =           0;//���������Ϊ0
					m_IsDialConnectting =       FALSE;
					m_IfChangeData      =       FALSE; //�޸Ľ������ݱ�־

					ReceiveByteArray.RemoveAll();
					OperationAnimation(FALSE);        //����״̬������
    				StatusStr    =         "";
					Received     =          0;        //����ͳ�ɳ��ͨѶ
					
					//���ذ�ʱ
					if(AppInfo::Instance().m_WhichKind)   
					{
						AutoAnswer(FALSE);	          //�Զ�Ӧ��
					}
					
					status("���κŶϿ����ӡ�");

				}

			}

			break;
		}
	case 2:
		{   
			//���ӱ�־
			pCmdUI->Enable(m_IsConnect);

			if(m_IsConnect && !m_IsDialConnectting)
			{
			   	
				if(ReadMeterThread != NULL)
				{	
					//��ͨʱֹͣԭ���Ĺ���
				    m_StartRead    =   FALSE;
                    SurrenderWindowMessage();
					Sleep(1000);
				    SurrenderWindowMessage();
				}
			
				m_others         =            FALSE;//
				m_IfChangeData   =             TRUE;//�޸Ľ������ݱ�־
				status("�����ӳɹ�,����:" + m_WinSocket.GetLocalIP() + ",����:" + m_WinSocket.GetRemoteHostIP()+ "��");
				
				m_IsDialConnectting =       TRUE;
			    m_PassErrortimes    =          0;//���������Ϊ0

			}
			else
			{

				if(!m_IsConnect && m_IsDialConnectting)
				{
					
					//��������������
					if(AppInfo::Instance().m_WhichKind)
					{
						SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
					}

					status("��TCP/IP�����ѶϿ���");
					m_IsDialConnectting =          FALSE;
					m_IfChangeData      =          FALSE;          //�޸Ľ������ݱ�־
					
				}
				
			}

			break;
		}

	}

}

//д���ռ��ļ�
void CIFRMView::WriteToLog(CString Str)
{
	CString  YearLog;
	CTime time  = CTime::GetCurrentTime();
	YearLog.Format("%sifrm%dlog.txt",GetFileFolderPass,time.GetYear());

	FILE *text;
	if((text = fopen(YearLog,"a")) != NULL)
	{
		fputs(Str + "\r\n",text);
		fclose(text);
	}
	
}

void CIFRMView::OnStopexam() 
{
	m_StartRead = FALSE;	
}


void CIFRMView::SurrenderWindowMessage()
{
	
	MSG message;
	
	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

	}
	
}

//long ModuleNo  ģ���
//int times      �������
//int mode       д��ģʽ 0 error,1 right
void CIFRMView::WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode)
{
	
	CFile       file;
	CString      str;
	CString filename;
	filename.Format("%d%d",ModuleNo,times);
	if(mode == 0)
	{
		filename = filename + "ERROR.TXT";
	}
	else
	{
        filename = filename + "RIGHT.TXT";
	}
	
	if(file.Open(filename,CFile::modeWrite | CFile::modeCreate))
	{	
		file.Seek(0,CFile::begin);
		str.Format("%4d",DataBuf[0]);
		str = str + "\r\n";
		file.Write(str,6);

		for(int i = 1; i < DataLen; i++)
		{
			file.Seek(0,CFile::current);
			str.Format("%4d",DataBuf[i]);
			str = str + "\r\n";
			file.Write(str,6);
		}

		file.Close();
	}
	
}

//˫��ͨѶ
BOOL CIFRMView::PcSendToSCM(BYTE ORDER[],BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/)
{
	
	CString        str;	
	CString       str1;
	U32      output[5];
	BYTE    Receive[5];

	ORDER[14]     =  0;

	if(ORDER[2] == 0x53)
	{

		//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]				
		//ʮ�����Ƶ�Э��
		ORDER[2] = Protocol/10*16 + Protocol%10;
		
		//�����22Э��
		if(Protocol == 22)
		{
			//��71Э����
			ORDER[2] = 0x71;
		}
		else if(Protocol == 31)
		{
			ORDER[2] = 0x53;
		}	

		//71,72Э��
		if(Protocol >= 71 && Protocol <= 73)
		{
			
			//�����ֽ�,BCHУ��
			BYTE            g[64];
			BYTE         data[45];
			//	CString   str,strtemp;
			BYTE         TempVale;
			
			//0-5��Ϊ0,ǰ6����Ϊ0
			data[0] = data[1] = data[2] = data[3] = data[4] = data[5] = 0;
			
			//40����
			int i;
			for(i = 5; i < 10; i ++)
			{
				
				//str.Format("�ϳ�ǰ:ORDER[%d]=0x%0x \r\n",i,ORDER[i]);
				//WriteToLog(str);
				
				TempVale = ORDER[i];
				
				//�۳�λ
				for(int j = 1; j <= 8; j ++)
				{
					data[6 + (i - 5) * 8 + j - 1] = TempVale%2;//add 2004.12.28
					TempVale                      = TempVale/2;
				}
				
			}
			
			//ת��BCH��
			//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
            Encode_Bch(g,data,0);
			
			//�����ָ��� 5-----13
			for( i = 5; i < 13; i ++)
			{
				
				ORDER[i] = 0;
				
				//λ�ֺϳ�������
				for(int j = 0; j < 8;j ++)
				{
					ORDER[i] = ORDER[i] + BYTE(g[(i-5) * 8 + j]*pow((double)2,j));
				}
				
				//str.Format("�ϳɺ�:ORDER[%d]=0x%0x \r\n",i,ORDER[i]);
				//WriteToLog(str);
				
			}
			
			ORDER[13] = 0;
		}
		else if(Protocol== 22)
		{
		
			//22Э��,�����ֽ�,BCHУ��
			BYTE             g[31];
			BYTE            gg[62];
			BYTE          data[21];
			long         TempVale = (ORDER[5]<<13) + (ORDER[6]<<5) + (ORDER[7]>>3);
			
			//21����
			for(int j = 0; j < 21; j ++)
			{
				//21λ����
				data[20-j] = TempVale%2;
				TempVale     = TempVale/2;     
			}
			
			//ת��BCH��
			Encode_Bch(g,data,2);
			
			//22��˫��Э��,1��10,0����01
			int i = 0;
			for(i = 0; i < 31; i ++)
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
			
			//�����ָ��� 5-----13
			for( i = 5; i < 13; i ++)
			{
				ORDER[i]  = 0;
				
				for(int j = 0; j < 8;j ++)
				{
					
					if((i-5)*8+j < 62)
					{
						ORDER[i] = ORDER[i] + BYTE(gg[(i-5)*8+j]<<(7-j));
					}
					else
					{	
						if((i-5)*8+j == 62)
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
						}
						else
						{
							ORDER[i] = ORDER[i] + BYTE(0<<(7-j));
						}
						
					}
					
				}
			}
			
			ORDER[13] = 0;
			
		}
		else if(Protocol == 61 || Protocol == 62)
		{

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

			//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
			//ת��BCH��45_27_3
			Encode_Bch(g,data,1);

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
						ORDER[i] = ORDER[i] + BYTE(g[(i-5)*8+j]*pow((double)2,7-j));
					}
					
				}	
							
			}

			ORDER[13] = 0;
			
		}

	}
	
	ORDER[13]  = m_SendAngle;//����Ƕ�
	
	//long begintimes = GetTickCount();
	
	//��ǰ14λ
	int j;
	for(j = 0; j <= 13; j++)
	{
		WriteP9111_CHANNEL_DOPort(ORDER[j]); 
		
		if(j >= 2)
		{	
			//�����
			ORDER[14] = ORDER[14] + ORDER[j];
		}
	
		//str.Format("���ͽ��:ORDER[%d]=0x%0x \r\n",j,ORDER[j]);
		//WriteToLog(str);
	//	str1.Format(" %0x \r\n",ORDER[j]);
    //  str = str + str1;
	}	
	

	
	//str.Format("���ͽ��:ORDER[14]=0x%0x \r\n",ORDER[14]);
	//WriteToLog(str);
	
	//str.Format("ORDER[%d]= %0x \r\n",j,ORDER[j]);
	//WriteToLog(str);
	
	//str1.Format(" %0x ",ORDER[14]);
	//str = str + str1;
    
	//ORDER[14] = ORDER[14]%256;
	//WriteToLog("˫��ͨѶ���\r\n" + str);	
	
	//���ͼ����
	WriteP9111_CHANNEL_DOPort(ORDER[14]);
	
	//str.Format("������ʱ%d����",GetTickCount()-begintimes);
	//WriteToLog(str);
	
	//��һ����
	WriteP9111_CHANNEL_DOPort(0X01);
	
	
	//�߷�����
	for( j = 0; j < 5;j ++)
	{
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0100);//ʱ��
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		Sleep(1);
		
		err = DO_WritePort(card,P9111_CHANNEL_DO,0X0000);//ʱ��
		if(err != 0)
		{
			//Beep(300,400);
		}
		
		//�ߵ�ʱ������,��Ҫ��ʱ
		err = DI_ReadPort(card,P9111_CHANNEL_DI,&output[j]);
		if(err != 0)
		{
			//Beep(300,400);
		}

		Receive[j] = BYTE(output[j] & 0xff);
		Sleep(1);
	}
	
    /**/
	str1.Format(" %0x  %0x  %0x  %0x  %0x ",Receive[0],Receive[1],Receive[2],Receive[3],Receive[4]);//���λ��λȥ��
    CTime time = CTime::GetCurrentTime();
	CString s;
	s.Format("%4d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond()); //ת��ʱ���ʽ
//	WriteToLog("˫��ͨѶ���\r\n" + str + "\r\n" + str1 + s);
	
	
//	if(Receive[4] != (Receive[0] + Receive[1] + Receive[2] + Receive[3])%256)
	{
		//AfxMessageBox("˫��ͨѶ��������벻�ԣ�\r\n" + str + "\r\n" + str1 + s);
		
		//WriteToLog("˫��ͨѶ��������벻�ԣ�\r\n" + str + "\r\n" + str1 + s);
		//Beep(300,400);
//		return FALSE;
	}
	
	switch(ORDER[2])
	{
	case 0x53://pc������
		{
			//Receive[1]������ĸ��  Receive[2]������ ��· Receive[3]������ ���
			if(Receive[0] != 0x63 || ORDER[3] != Receive[1] * 64 + Receive[2] * 4 + Receive[3])
			{
//	    		WriteToLog("˫��ͨѶʱ��������� 0x53!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5c://����A�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6c || ORDER[4] != Receive[2])
			{
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5C!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0x5d://����B�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6d || ORDER[4] != Receive[2])
			{
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5d!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0x5e://����C�ഥ���Ƕ�
		{
			if(Receive[0] != 0x6e || ORDER[4] != Receive[2])
			{
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5e!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0x58://��ȡA�ഥ���Ƕ�
		{
			if(Receive[0] != 0x68)
			{
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x58!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
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
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x59!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
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
//				WriteToLog("˫��ͨѶʱ���ô����ǶȲ��� 0x5a!\r\n" + str + "\r\n" + str1);
//				WriteToLog(s + "\r\n");
				return FALSE;
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
			//	WriteToLog("˫��ͨѶʱ��ȡֱ�߱�Ų��� 0x5a!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("˫��ͨѶʱ����A���ӳٽǶȲ��� 0xD0!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC1://����B���ӳٽǶ�
		{
			if(Receive[0] != 0xD1)
			{
			//	WriteToLog("˫��ͨѶʱ����B���ӳٽǶȲ��� 0xD1!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}

			break;
		}
	case 0xC2://����C���ӳٽǶ�
		{
			if(Receive[0] != 0xD2)
			{
			//	WriteToLog("˫��ͨѶʱ����C���ӳٽǶȲ��� 0xD2!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			break;
		}
	case 0xC3://��ȡA���ӳٽǶ�
		{
			if(Receive[0] != 0xD3)
			{
			//	WriteToLog("˫��ͨѶʱ��ȡA���ӳٽǶȲ��� 0xD3!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("˫��ͨѶʱ��ȡB���ӳٽǶȲ��� 0xD4!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
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
			//	WriteToLog("˫��ͨѶʱ��ȡC���ӳٽǶȲ��� 0xD5!\r\n" + str + "\r\n" + str1);
			//	WriteToLog(s + "\r\n");
				return FALSE;
			}
			else
			{
				m_angles = Receive[2];
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

	}


	return TRUE;
}


void CIFRMView::OnAngleset() 
{
 
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{      
		return;
	}
	
	CAngleSettingGlg  dlg;
	dlg.m_WhichKind = AppInfo::Instance().m_WhichKind;
	dlg.DoModal();	
	
}

//��������·�巢ָ��
BOOL CIFRMView::SendOrderToSCM(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/, BYTE ZeroDots/* ��ʱ��0����*/,BYTE Item/* Ҫʲô����,������*/,int status/*�ɷ�ʱ�����������*/,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/)
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
    for(int i = 0 ;i < 15;i ++)
	{
		ORDER[i] = 0;
	}
    
	
	StatusH = status/256;                       //��λ    ��Ӧ��Ϊ����3�ĺ�2λ
	StatusL = status%256;                       //��λ    ����4
	 
	switch(Phase)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
			m_iChSelect = 0;
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			m_iChSelect = 1;
			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
			m_iChSelect = 2;
			break;
		}
	}
	
	//������,ORDER[0]��ORDER[4]������Ƭ����
	ORDER[0]  = 0x51;    //ǰ����
	ORDER[1]  = 0x52;    //ǰ����
	ORDER[2]  = 0x53;    //��������
 	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[4]  = ZeroDots;// ��ʱ��0�����       

	//���Э��Ϊ22
	if(Protocol == 22)
	{
		
		//ģ��Ŵ���0�Ļ�Ϊ��������ͣ��
		if(ModuleNum > 0)
		{
			//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������  
			//����� 485��: 10(�ලλ) + 14(��ַ)+ 7(����)
			//����������: 10(�ලλ) + 14(��ַ)+ 4(�ֵ�ַ) + 3(����)
			
			//��ַǰ8λ
			ORDER[5]  = (ModuleNum/100)>>6; //��ַ��λ
			
			if(ModuleNum%100 >= 12)
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
			//��վ��Ϣ
			if(m_handno == 0)
			{
				//o��վ ��ȫ0��21��0
				ORDER[5]  = 0x0; 
				ORDER[6]  = 0x0;
				ORDER[7]  = 0x0;
			}
			else
			{
				//1��վ ��14��0��7��1	
				ORDER[5]  = 0x0;  //8��0
				ORDER[6]  = 0x03; //6��0 + 2��1
				ORDER[7]  = 0xf8; //5��1 ��3��0
			}
			
		}
		
		ORDER[8]  =     0;
		ORDER[9]  =     0;


	}
	else  if(Protocol == 61 || Protocol == 62)
	{
		
		//ģ��Ŵ���0�Ļ�Ϊ��������ͣ��
		if(ModuleNum > 0)
		{
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
			
		}
		else
		{
			//��վ��Ϣ
			if(m_handno == 0)
			{
				//o��վ ��ȫ0��20��0 �� 7λ������(0001000)
				ORDER[5]  = 0x00; //8��0
				ORDER[6]  = 0x00; //8��0
				ORDER[7]  = 0x01; //4��0 �� 0001
				ORDER[8]  = 0x00;
			}
			else
			{
				//1��վ       20��1�� 7λ������(0001000)	
				ORDER[5]  = 0xff;  //8��1
				ORDER[6]  = 0xff;  //8��1
				ORDER[7]  = 0xf1;  //4��1 ��0001
				ORDER[8]  = 0x00;
			}
			
		}
	
		ORDER[9]  =     0;
		
	}
	else
	{	
		//���Э��Ϊ31��32��71��72��
		//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ����
		ORDER[5]  = Item + int(int(ModuleNum/100)/65536); //�����֣�Ҫʲô������ģ���ַ���λ
		ORDER[6]  = AddrH;//ģ��ߵ�ַ
		ORDER[7]  = AddrM;//ģ���е�ַ
		
		//�����ǹ㲥����
		if(Item == 0xF2)
		{
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
		}
		else
		{
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StationNo;  //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
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
		case 0xF6://�͵����
			{
				
				//�͵����  D3 = 0000****
				//ORDER[8]  = 0*16  + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
				break;
			}
		case 0xf8://�ϵ����
			{	
				//�Ͽ�״̬ʱ D3 = 1111****
				//ORDER[8]  = 15*16 + PhaseBit* 4 + StationNo;    //�ϳ��ֽ�,ǰ1-4λΪģ��͵�ַ,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λΪ������վ��
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
				ORDER[9]  =  0x67;                             //���ֽں���λΪ��ʱ��0����
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
		
		//0x46  д����ֵ
		//0x4A  д �� ��
		//0x4e  д������
		//0x52  д��̨����//��Ҫ��
		if(Item == 0x46 || Item == 0x4A || Item == 0x4e)
		{
			ORDER[9]  =	m_PassValue;   
		}
		
		//д����ʱ�л����,ConversionCurrentValue
		if(Item == 0x46)
		{
			ORDER[9]  =	ConversionCurrentValue(m_PassValue);
		}
		
		
    }
	
	//�����ֽ�,��У��
	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��
	//��ʱ����
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//��Ƭ��������
	return PcSendToSCM(ORDER,Protocol/*����Э��*/,m_SendAngle/*���͵ĽǶ�*/);
	Sleep(5);
}

//��������63394
BOOL CIFRMView::DecodeBCH63394(BYTE recd[],BOOL m_Is63394)
{
    int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
	int        alpha_to[64], index_of[64];
	CString                           str;
    int   m = 6, n = 63,length,t,k,d;

	if(m_Is63394)
	{
		//63394
		length           =            63;
		t                =             4;
		k                =            39;
		d                =             9;
	}
	else
	{	
		//45273
		length           =            45;
		t                =             3;
		k                =            27;
		d                =             7;
	}

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
	
	t2 = 2 * t;//short
	
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
				//	no. roots = degree of elp hence <= t errors 
				//	str.Format("������������� count = %d",count);
				//	WriteToLog(str);
				
				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;	
					
					if(loc[i] >= 24)
					{
						//32-47λΪ******.**ǰ4�����ֽڵ������ܾ�,�ܹ�16λ
						if((86 - loc[i]) >= 32 && (86 - loc[i]) <= 55)
						{

						}
					
					}
					
				//	str.Format("��������λ�ã�%d",loc[i]);
				//	WriteToLog(str);
				}
				return TRUE;
				
			}
			else
			{
		//		str.Format("�������Ϊ�� count = %d��l[%d] = %d",count,u,l[u]);
		//		WriteToLog(str);
				return FALSE;
			}
			//length - k -> lengthΪ����ֵ 
		}
		else
		{
		//	str.Format("�������Ϊ��%d > 4 ",l[u]);
		//	WriteToLog(str);
			return FALSE;
		}
		
   	}
	else
	{
	//	str = "t = 0,û�д���";
	//	WriteToLog(str);
		return TRUE;
	}
	
}

BOOL CIFRMView::DecodeBCH31212(BYTE recd[])
{
    register int i, j, u, q, t2, count = 0, syn_error = 0;
	int   elp[100][100], l[1], s[1025];
	int   root[200], loc[200], reg[201];
	int   qt[513], r[129][513],b[12][513];
	int   degr[129], degb[129],temp, aux[513];
    int   m = 5, n = 31 , length = 31, t = 2, k = 21, d = 5;
   	
	m_CollectPlace[0]       =       0;
	m_CollectPlace[1]       =       0;

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
			//	str.Format("������������� count = %d",count);
			//	WriteToLog(str);
				
				//����ĸ���
				m_CollectNos = count;

				for (i = 0; i < l[u]; i ++)
				{
					recd[loc[i]] ^= 1;

					if( loc[i] < 10)
					{
						m_CollectPlace[i] = 9 - loc[i];
						//str.Format("��������λ�ã�%d",9 - loc[i]);
					}
					else
					{
						m_CollectPlace[i] = 40 - loc[i];
					    //str.Format("��������λ�ã�%d",41 - loc[i]);
					}
					                  
				    //str.Format("��������λ�ã�%d",loc[i]);
					//WriteToLog(str);
					

				}
				return TRUE;
				
			}
			else
			{
				//
				//str.Format("�������Ϊ�� count = %d��l[%d] = %d",count,u,l[u]);
				//WriteToLog(str);//
				return FALSE;
			}
			
			//length - k -> lengthΪ����ֵ 
		}
		else
		{
			//
			//str.Format("�������Ϊ��%d > 4 ",l[u]);
			//WriteToLog(str);//
			return FALSE;
		}
		
   	}
	else
	{
		//	
		m_CollectNos    =    0;
		//str = "t = 0,û�д���";
		//WriteToLog(str);//
		return TRUE;
	}

}

//��פ������,ÿ�ζ���
void CIFRMView::SendBreadorder(CTime  m_iBroadTime,int times)
{


	CString            str;
	long         broadTime;
	BYTE         ORDER[15];
	BYTE          PhaseBit;
    CTime            time0;
	
	//1601 ģ���Ϊ16���Ϊ01
	BYTE AddrH,AddrM,AddrL;
	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	StatusStrRead = StatusStr;


	//���Զ�פ��״̬
	if(m_IsAutoSending)
	{
		m_others  =   TRUE;
	}

    //��ʾ״̬����Ϣ
	if(times == 1)
	{
		StatusStr.Format("�����ڷ�פ��%4d-%02d-%02d %02d:%02d:%02d������Ժ�...��",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond()); 
	}
	else
	{
		StatusStr.Format("�����ڵ�%d�η�פ��%4d-%02d-%02d %02d:%02d:%02d������Ժ�...��",times,m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond()); 
	}

	SendMessage(WM_EVENT, 1, 0);
	
	//״̬����ʾ��Ϣ
	//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",str);
	//SendMessage(WM_EVENT, 5, 0);

	m_StartRead  =         TRUE;//�ܹ����ı�־

	//�õ���פ����Ϣ��ĸ�ߺ�Э������
    SendMessage(WM_EVENT, 20, 0);
	
	if(m_MotherLineArray.GetSize() <= 0 || m_ProtColArray.GetSize() <= 0)
	{
		//��ʾ״̬����Ϣ
		StatusStr.Format("���û����ݱ������û����ݣ�����פ��ֹͣ��"); 
		SendMessage(WM_EVENT, 1, 0);
		return;
	}

	//�ö���Э�飬ÿһ�ֶ���һ��
	for(int kk = 0; kk < m_ProtColArray.GetSize(); kk ++)
	{
		
		SurrenderWindowMessage();
		
		if(!m_StartRead)
		{
			break;
		}

		Sleep(200);
		
		//��ĸ��
		for(int j = 0; j < 2; j++)
		{

			BOOL m_CanContinue = FALSE;

			for(int hhh = 0; hhh < m_MotherLineArray.GetSize(); hhh ++)
			{

                if(m_MotherLineArray[hhh] == (j + 1))
				{
                   m_CanContinue = TRUE;
				   break;
				}

			}

			if(!m_CanContinue)
			{
				continue;
			}

			SurrenderWindowMessage();
			Sleep(200); 

			if(!m_StartRead)
			{
				break;
			}
			
			//����
	    	for(int i = 0; i < 3; i++)
			{

				SurrenderWindowMessage();
				
				if(!m_StartRead)
				{
					break;
				}

				//���������ʱ��
				time0           = CTime::GetCurrentTime();
				CTimeSpan ts    = m_iBroadTime  -   time0;

				if(m_ProtColArray[kk] == 22 || m_ProtColArray[kk] == 61 || m_ProtColArray[kk] == 62)
				{
					//22Э�龫��Ϊ30���ӣ�����Ϊ30���ӵı���,4���ӷ�Χ��
					broadTime       = (ts.GetTotalSeconds() + 240)/1800;//����ʱ
				}
				else
				{
					//31��32��33��71��72��73����Ϊ8�����
					broadTime       = ts.GetTotalSeconds()/8;//����ʱ
				}
				
				if(broadTime <= 0 || !m_StartRead)       //�������ֹͣ���жϷ�פ��
				{
					break;
				}
				
				BYTE StatusH,StatusL;
				
				//�㲥��ַ
				AddrH = 0;                                  //��λ    ��Ӧ��Ϊ����1
				AddrM = 0;                                  //�м�λ  ��Ӧ��Ϊ����2
				AddrL = (broadTime>>10)&0x0f;               //��4λ   ����ʱ��ĸ�4λ
				// A 01 B 02  C 03
				
				StatusH = (broadTime>>8); 
				StatusH = StatusH & 0x03;                   //��2λ   ����ʱ��ĸ�2λ
				StatusL = broadTime%256;                    //��8λ   ����ʱ��ĵ�8λ
				
				switch(i)
				{ 
				case  0://A��
					{
						PhaseBit    = 0x01;
						break;
					}
				case  1://B��
					{
						PhaseBit    = 0x02; 
						break;
					}
				case 2://C��
					{  
						PhaseBit    = 0x03;
						break;
					}
				}
				
				//��ORDER[0]��ORDER[4]��Ƭ����
				//������
				ORDER[0]  = 0x51; //ǰ����
				ORDER[1]  = 0x52; //ǰ����
				ORDER[2]  = 0x53; //��������
				ORDER[3]  = j*64  + 0 + PhaseBit;//�ϳ��ֽ� ǰ2λΪ(j 0��1����ĸ��)ĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
				ORDER[4]  =    3; // ��ʱ��0����   
						
				if(m_ProtColArray[kk] == 22)
				{
					//���Э��Ϊ22	
					//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������  
					//��ʽ��10λ�ල��+7(7��1)+ 7(7λפ��ʱ��)+ 7(7��0)
					//��ַǰ8λ
					ORDER[5]  = 254   + (broadTime>>6); //ʱ���1λ	
					//ʱ���6λ + 2λ0
					ORDER[6]  = (broadTime%64)*4 + 0;
					ORDER[7]  =                    0;
					ORDER[8]  =                    0;
					ORDER[9]  =                    0;
				}
				else
				{
					
					if(m_ProtColArray[kk] == 61 || m_ProtColArray[kk] == 62)
					{
						//61,62Э��
						//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������  
						//��ʽ��18λ�ල��+ ��ַ��8λȫ1 +  ��ַ��6λ(6λפ��ʱ��) + 6(6��0) + 0001000
						//��ַǰ8λ
						ORDER[5]  =                 0xff; //��ַ��8λȫ1	
						ORDER[6]  =       (broadTime<<2); //��ַ��6λ(6λפ��ʱ��) + 2��0
						ORDER[7]  =                    1; //4��0  +  0001
						ORDER[8]  =                    0; //000   +  5��0
						ORDER[9]  =                    0;
					}
					else
					{
						//31,32,33,71,72,72Э��
						//����ģ����
						ORDER[5]  = 0xf2; //�����֣�Ҫʲô����
						ORDER[6]  = 0;    //ģ��ߵ�ַ
						ORDER[7]  = 0;    //ģ���е�ַ
						ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4��Ϊפ��ʱ��,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
						ORDER[9]  = StatusL;//פ��ʱ��
					}
					
				}			

				ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��
				
				//��ʱ����
				ORDER[11] = 0;
				ORDER[12] = 0;
				ORDER[13] = 0;
			
				//��ʾ�汾
				if(!AppInfo::Instance().m_YanShi)
				{
					//62Э��
					//��Ƭ��������
					if(!PcSendToSCM(ORDER,m_ProtColArray[kk]/*����Э��*/,0))
					{
						Beep(300,400);
					}

				}
				
				if(times == 1)
				{	
					str.Format("��פ��%4d-%02d-%02d %02d:%02d:%02d,ĸ��%dЭ��%d,",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond(),j + 1,m_ProtColArray[kk]); 
				}
				else
				{
					str.Format("פ��%4d-%02d-%02d %02d:%02d:%02d,��%d��ĸ��%dЭ��%d",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond(),times,j + 1,m_ProtColArray[kk]); 
				}
				
				switch(i)
				{
				case 0:
					{	
						//��ʾ״̬����Ϣ
						StatusStr = "��" + str + "A��ɹ���";
						break;
					}
				case 1:
					{
						//��ʾ״̬����Ϣ
						StatusStr = "��" + str + "B��ɹ���";
						break;
					}
				case 2:
					{
						//��ʾ״̬����Ϣ
						StatusStr = "��" + str + "C��ɹ���";
						break;
					}
					
				}	
				
				SendMessage(WM_EVENT, 1, 0);
				
				//���͵��ַ�BEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
				//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
				//SendMessage(WM_EVENT, 5, 0);
				
				SurrenderWindowMessage();

				//��פ��ʱ�����
				m_AutoReadTime = m_iBroadTime;
				SendMessage(WM_EVENT, 11, 0);
				  
				//�ȴ�ʱ��
				BYTE  m_SendTimers  =    0;

				if(m_ProtColArray[kk] == 22)
				{
					//22Э��ȴ�ʱ��
					m_SendTimers =  8;
				}
				else
				{
					m_SendTimers = (m_ProtColArray[kk]%10)*9;
				}
				
                for(BYTE jj = 0 ; jj < m_SendTimers; jj ++)
				{
					SurrenderWindowMessage();
					
					if(m_StartRead)
					{
						Sleep(1000);
					}
					else
					{
						break;
					}
					
				}				
				
				SurrenderWindowMessage();
				Sleep(1000);

				//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
				//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS","");
				//SendMessage(WM_EVENT, 5, 0);	
							
           }

		 
       }

	  
	}	
	
	if(times == 1)
	{
		StatusStr.Format("����פ��ʱ��%4d-%02d-%02d %02d:%02d:%02d������ϡ�",m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
	}
	else
	{
		StatusStr.Format("����%d�η�פ��ʱ��%4d-%02d-%02d %02d:%02d:%02d������ϡ�",times,m_iBroadTime.GetYear(),m_iBroadTime.GetMonth(),m_iBroadTime.GetDay(),m_iBroadTime.GetHour(),m_iBroadTime.GetMinute(),m_iBroadTime.GetSecond());
	}

	SendMessage(WM_EVENT, 1, 0);
	m_times                 ++;

	StatusStr = StatusStrRead;
	
	//������Զ�פ��״̬
	if(m_IsAutoSending)
	{
		m_others       =    FALSE;
	}

   TmpOnlyOneThreadRun.SetEvent();

}

void CIFRMView::OnPaint() 
{
	CPaintDC dc(this); 

    CBrush brush(m_BackRgbValue);//RGB(128,128,128));
    CRect                   rect;
    GetClientRect(rect);
    dc.FillRect(&rect,&brush);
	
    
	
  	/*
    CDC dcImage;
    if (!dcImage.CreateCompatibleDC(&dc))
		return;
	
	CRect m_Rect;
	GetClientRect(&m_Rect);
	
	CBitmap m_bitmap;
	
    if (!m_bitmap.LoadBitmap(IDB_GRIDBACK))
	  return;
  
    BITMAP bm;
    m_bitmap.GetBitmap( &bm );
    CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
    dc.StretchBlt(0,0,m_Rect.Width(),m_Rect.Height(),&dcImage,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);	
    dcImage.SelectObject(pOldBitmap);
    */
		
	// Do not call CFormView::OnPaint() for painting messages
}

//title           �Ի������
//IfWriteData     �Ƿ�д�����ݿ� FALSE---��  д   TRUE---д
//WhichTable      �ĸ���            0----���ݱ�   1----פ����
//constr          ����              ALL--��  ��
//recycles        ѭ������
//Settimes        ÿ����ʱ����
//m_ReadKinds     0---�ֹ���   1----��ʱ���� 
void CIFRMView::FiveDataChuLi(CString title,BOOL  SELECT[],BOOL IfWriteData, int WhichTable, CString constr,int recycles,int Settimes,BYTE m_ReadKinds)
{
    int     READTIMES        =        0;//�������
	BYTE    MotherLine       =        0;//ĸ�߱��
	BYTE    LineNo           =        0;//��  ��
	BYTE    BakMotherLine    =        0;//����ĸ�߱��
	BYTE    BakLineNo        =        0;//�����ߺ�
	BYTE    PhaseNo          =        0;//��  ��
    long    ModuleNo         =        0;//ģ���
	BYTE    StationNo        =        0;//�����ֱ��վ����
	BYTE    tempvalue,value  =        0;//ָ�����
    BYTE    m_AMMETERKIND    =        0;//�������
	BYTE    m_SUPPLYMODED    =        0;//���緽ʽ 0-���߹��� 1��վ������ 2���������ֹ���
	BYTE    m_PROTOCOL       =        0;//����Э��
	BYTE    m_SendAngle      =        0;//���͵ĽǶ� 
	float   m_BeginValue     =        0;//����ֵ 
	double  CurrentValue     =        0;//��ʼ��ģ������
	long                         fields;//��¼����
	short                       nFields;//�ֶθ���
	long    m_OldModule       =    - 10;
	double  m_OldCurrentValue =   -10.0;
	BOOL    m_UseOldValue     =   FALSE;
	BYTE    m_OldReadHour     =      24;
	BYTE    m_OldReadMinute   =      60;
	BOOL    m_StillRunning    =   FALSE;
	short   m_CheckTimes      =       0;
	long    m_PhaseModule     =       0;
	BYTE    m_PhaseBak        =       3;
	CTime        m_CheckreadModuleTimes;//����ʱ��
	CString 	 m_ReadAmmeterType,m_ReadMeterLabel;//��������
	CString      strValue,m_FieldNames,m_ReadTime;
	CString       strSql,HisStrSql,DataStr  = "";
	CDatabase                         db;
    CTimeSpan                       ttts;

	constr.TrimLeft();
	constr.TrimRight();
	int i;
	for( i = 0; i < 31; i ++)
	{
		m_All_Line_Current[i] = 2;//û�м��״̬
	}

	//��61��62Э��485����ٶ���Ĺ������� 
	for(i = 0; i < 20000; i ++)
	{
       m_QuickGlys[i] =  -1;
	}	
	
	m_QuickModuleAddress =         0;//���ٶ���ĵ�ַ
	m_QuickReadModuleValue =      -1;//���ٶ����ֵ

	//�������û�����
	constr = "(" + constr + ") AND USER_RUNSTATUS<=2";

	//ɾ��ԭ������
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);                      //13��

	m_StartRead              =              TRUE;//��ͣ��־
	m_ZhuLiuTime             =   GetZhuLiuTime();//פ��ʱ��    
	
	//��ʾ״̬����Ϣ
	StatusStr = "����" + title + "�����Ժ�...";
	SendMessage(WM_EVENT, 1, 0);

	//���DIALOGBAR�ɼ��Ļ�������
	SendMessage(WM_EVENT, 6, 0);
	memset(m_QuickGlys,0,100000);
  
	//���Ƕ�ʱ����
	if(WhichTable < 2)
	{   
		//�кŴ�0��ʼ
		m_ListRows              =    1;
	}
	
    if(m_ReadKinds == 0)
	{

		if(WhichTable == 1)//      �ĸ���            0----���ݱ�   1----פ����
		{
		   m_QuickReading   =         FALSE;//ע��:פ���������ÿ��ٶ���
		}
			
		m_ReadMeterLabel = "USER_READLABEL";//��ͨ����
		m_others         =            FALSE;//FALSE ��������  TRUE  פ������
		READTIMES        =                5;//5��
	}
	else
	{
		m_QuickReading   =            FALSE;//ע��:פ���������ÿ��ٶ���
		m_ReadMeterLabel = "USER_TIMELABEL";//��ʱ�Զ�����
		m_others         =             TRUE;//FALSE ��������  TRUE  פ������
		READTIMES        =                1;//1��

		//פ���������һ�Σ����5��
		if(m_IsAutoSending)
		{	

            
			if(m_zhuliukinds == 0)
			{

				//������������
				if(m_ReadModuleTimes == m_parameter[106])
				{
					//���һ�ζ���5��
					READTIMES  =   5;
					
				}
				
			}
			else
			{
				
				if(m_ReadModuleTimes == m_DateReadParameter[63])
				{
					
					//���һ�ζ���5��
					READTIMES  =   5;
					
				}
				
			}

		}

	}
	
	//��������Ķ�����ʼ,����������Ļ�����,15�����͵����� 0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14����������
	for(int hhh = 1; hhh < 15; hhh ++)
	{
		
		if(hhh == 7 || hhh == 8 || hhh == 9)
        {
			//�����ֻ�ж������ѹ
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s%d",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_MODULENO%100<=12 AND USER_PHASE<>",hhh - 7);
		}
		else
		{
			//�����ֻ���й����
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_MODULENO%100<=12");
		}

		CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		
		//61��62Э��û��BC�������ѹ�ɶ�A��ʱ������ͬʱ������
		if(hhh == 5 || hhh == 6 || hhh == 8 || hhh == 9)
		{
			//�����ִ����������·���վ�ܱ�û��������
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"USER_PROTOCOL=61 OR USER_PROTOCOL=62");
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		}
		
		if(hhh == 1 || hhh == 3)
		{
			//�����ִ����������·���վ�ܱ�û��������
			strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,%d,1,'Y') WHERE %s",m_ReadMeterLabel,m_ReadMeterLabel,hhh + 1,"(USER_MODULENO%100>12 AND USER_SUPPLYMODE=0) OR (USER_AMMETERKIND>3)");
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
		}
	
	}
	
	//�����Ĳ��ܶ���
	strSql = "UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY',USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_RUNSTATUS>2";	
	CDataBaseInstance::ExecuteDataBaseSQL(strSql);

	//61,62Э�����Լ���ѹ��	
	strSql.Format("UPDATE TB_USER SET %s=STUFF(%s,2,14,'YYYYYYYYYYYYYY') WHERE %s AND (USER_PROTOCOL=61 OR USER_PROTOCOL=62)",m_ReadMeterLabel,m_ReadMeterLabel,"USER_MODULENO%100<=12");
    CDataBaseInstance::ExecuteDataBaseSQL(strSql);
	//��������Ķ�������

	//���ݿ��
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
		
		if(WhichTable < 2 || (WhichTable >= 2 && m_times <= 1))
		{
			//д�б����
			SendMessage(WM_EVENT, 2, 0);
		}
		
		//��������
        for(int www = 0; www < recycles; www++)
		{
			
			//���Ӷ���
			if(m_CheckReading)
			{
				m_CheckreadModuleTimes = CTime::GetCurrentTime();//��̬��ض���ʱ��
			}			

			SurrenderWindowMessage();
			
			//�������ֹͣ��ť
			if(!m_StartRead)
			{	
				break;
			}		

			ShowProgressCtrl(TRUE);//��ʾ������
	
    	    //��ʼɨһ��,15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
			for(int a = 0 ; a < 15 ; a ++)
			{
				
				SurrenderWindowMessage();

				//�������ֹͣ��ť
				if(!m_StartRead)
				{	
					break;
				}

				//��̬��ض���ʱ��
				if(m_CheckReading)
				{

					ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

					//1����ǰֹͣ
					if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
					{
						break;
					}

				}			


				//���ѡ���˴���      
				if(SELECT[a] == TRUE)
				{
				
					//ÿ�������
					for(int m_ReadTimes = 0;m_ReadTimes < READTIMES;m_ReadTimes ++)
					{
						
						SurrenderWindowMessage();

						//�������ֹͣ��ť
						if(!m_StartRead)
						{	
							break;
						}

					    //��̬��ض���ʱ��
						if(m_CheckReading)
						{

							ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

							//1����ǰֹͣ
							if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
							{
								break;
							}

						}
						
						//�ҳ�ԭ���б�ǵĵط�
						strSql.Format("(%s) AND SUBSTRING(%s,%d,1)='N'",constr,m_ReadMeterLabel,a + 1);
					
						if(rs.IsOpen())
						{
							rs.Close();
						}
						
						//�����������ĸ���
						strValue.Format("SELECT COUNT(*) FROM TB_USER WHERE %s",strSql);
						rs.Open(CRecordset::forwardOnly,strValue);
						rs.GetFieldValue(short(0),strValue);
						rs.Close();
						
						fields = atoi(strValue);
					
						if(fields <= 0)	
						{
							m_ReadTimes = READTIMES;//û�����������ļ�¼�Ļ�������
							continue;
						}

						strSql.Format("SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE (%s) AND SUBSTRING(%s,%d,1)='N' ORDER BY USER_AMMETERKIND DESC,USER_MODULENO ASC",constr,m_ReadMeterLabel,a + 1);
				
						rs.Open(CRecordset::forwardOnly,strSql);
						nFields = rs.GetODBCFieldCount();//�õ��ֶθ���
						rs.Close();
						
						SetProgressCtrlRange(0, fields,1);
						
						//�����ݿ�����
						rs.Open(CRecordset::forwardOnly,strSql);
						
						//���û���Ϣ
						for(int j = 0;j < fields; j ++)
						{
							
							SurrenderWindowMessage();

							//�������ֹͣ��ť
							if(!m_StartRead)
							{	
								break;
							}
							
							//��̬��ض���ʱ��
							if(m_CheckReading)
							{

								ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

								//1����ǰֹͣ
								if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
								{
									break;
								}

							}			

							//���
							m_StrArray[0].Format("%6d",m_ListRows);
							m_StrArray[1]   = title;
																			
							///////////////////////////////////�õ��ֶ���Ϣ/////////////////////////
							for(int i = 0; i < nFields; i ++)
							{
								rs.GetFieldValue(int(i),strValue);
								strValue.TrimRight();

								switch(i)
								{
								case 0:
									{
										//��   ��
										m_StrArray[2] = strValue;
										break;
									}
								case 1:
									{ 
										//�û����  
										m_StrArray[3] = strValue;
										break;
									}
    						   case 2:
									{ 
										//ס   ַ  
										m_StrArray[4] = strValue;
										break;
									}
								case 3:
									{  
										//ģ���
										m_StrArray[5].Format("%8s",strValue);
										ModuleNo = atol(strValue);
										break;
									}
								case 4:
									{  
										//����
										m_StrArray[6].Format("%8s",strValue);
										break;
									}
								case 5:
									{  
										//ĸ�߱��
										MotherLine = atoi(strValue); 
										
										if(MotherLine > 2)
										{
											MotherLine = 2;
										}
										
										if(MotherLine < 1)
										{
											MotherLine = 1;
										}

										break;
									}
								case 6:
									{	
										//��·����
										m_StrArray[7] = strValue;
     									break;
									}
								case 7:
									{
										//��·���
										strValue.TrimLeft();
										strValue.TrimRight();
										LineNo = atoi(strValue);

										if(LineNo > 15)
										{
											LineNo = 15;
										}
										
										if(LineNo < 1)
										{
											LineNo = 1;
										}

										break;
									}
								case 8:
									{
										//��
                                        PhaseNo       = atoi(strValue);	
																			
										if(PhaseNo >= 3)
										{											
										//	strValue.Format("�����ݱ���ģ���:%d,���:%d,m_PhaseBak=%d\r\n",ModuleNo,PhaseNo,m_PhaseBak);
										//	WriteToLog(strValue);

											//ԭ���Ƿ���������
											if((m_PhaseModule/100) == (ModuleNo/100))
											{
												PhaseNo = m_PhaseBak;
											}
											else
											{
												PhaseNo = 3;
											}

										}

										break;
									}
							   case 9:
									{
										//��̨����
										m_StrArray[9] = strValue;
						     			break;
									}
								case 10:
									{
										//�����ֵ�վ��,����ֵ
										StationNo    = m_handno;
										m_BeginValue = float(atof(strValue));
										break;
									}
								case 11:
									{
										//�������
										m_AMMETERKIND = atoi(strValue);
										break;
									}
								case 12:
									{
										//���緽ʽ
										m_SUPPLYMODED = atoi(strValue);
										break;
									}
								case 13:
									{
										//����Э��71-73 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
										m_PROTOCOL = atoi(strValue);
										
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A��",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B��",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C��",m_PROTOCOL);
												break;
											}
										default:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"δ֪",m_PROTOCOL);
												break;
											}
										}

										//61,62Э���A�������ѹʱͬʱ��ABC��������
										if((a==4 || a==7)  && (m_PROTOCOL==61 || m_PROTOCOL==62)  && PhaseNo<3)
										{	
											m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"3��",m_PROTOCOL);
										}

										break;
									}
								case 14:
									{
										//����ĽǶ�,�Ƿ����ǽ�����,ƫ�ƽǶ�,�ǽ�Ϊ30��
										if(IsDyConnect(m_StrArray[9]))
										{
											m_SendAngle   =                        6;//5��һ������
											m_StrArray[9] = m_StrArray[9] + "(�ǽ�)";
										}
										else
										{
											m_SendAngle = 0;
										}

										break;
									}
								case 15:
									{
										//�������
										strValue.TrimLeft();
                                        strValue.TrimRight();
										m_ReadAmmeterType = strValue;

										//����������Ļ�
										if(a > 2)
										{
                                           m_ReadAmmeterType  = "";
										}

										break;
									}
								case 16:
									{
										//����ĸ�߱��
										BakMotherLine = atoi(strValue);

										if(m_SUPPLYMODED == 2)
										{
											
											if(BakMotherLine > 2)
											{
												BakMotherLine = 2;
											}	
											
											if(BakMotherLine < 1)
											{
												BakMotherLine = 1;

											}

										}

										break;
									}	
								case 17:
									{
										//���ó��ߺ�
										BakLineNo     = atoi(strValue);
                                        
										if(m_SUPPLYMODED == 2)
										{
											
											if(BakLineNo > 15)
											{
												BakLineNo = 15;
											}
											
											if(BakLineNo < 1)
											{
												BakLineNo = 1;
											}
											
										}

										break;
									}
									
								}
								
							 }
							 
							 ///////////////////////////////////�õ��ֶ����/////////////////////////
							 
							 
							 ///////////////////////////////////ѡ��ʼ//////////////////////////////
							 switch(a)
							 {
							 case 0:
								 {
									 //WhichTable  �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {  
										 //�����վ�����ֹ���Ļ�
										 if(m_SUPPLYMODED == 1)
										 {
										
											 //���Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 {
												 
												 //������ʽ���������ַ�ʽ,���й����-�����ۼ�ֵ
												 if(m_handno == 0)
												 {
													 value  = 0x57;
												 }
												 else
												 {  
													 value  = 0x5B;
												 }
												 
											 }
											 else
											 {

												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
												     //������ʽ���������ַ�ʽ,���й����-�����ۼ�ֵ
													 if(m_handno == 0)
													 {
														 value  = 0x17;
													 }
													 else
													 {  
														 value  = 0x1B;
													 }
													 
												 }
												 else
												 {													 
													 //������ʽ���������ַ�ʽ,���й����-�����ۼ�ֵ
													 if(m_handno == 0)
													 {
														 value  = 0x50;
													 }
													 else
													 {  
														 value  = 0x54;
													 }

												 }

											 }
											
											 m_StrArray[10].Format("%dվ�й�",m_handno);
										 
										 }
										 else
										 {
											
											 //��������,���й����-����ֵ,���Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 { 
												 
												 if(ModuleNo%100 < 12)
												 {
													 value = 0x07;
												 }
												 else
												 {
													 value = 0x5F;
												 }
												 
											 }
											 else
											 {
												 
												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(ModuleNo%100 < 12)
													 {
														 value = 0x03;
													 }
													 else
													 {
														 value = 0x1F;
													 }
													 
												 }
												 else
												 {
												    value = 0x02;

												 }

											 }
											 
											 m_StrArray[10] = "�й����";

										 }
										 m_FieldNames       = "REALTIME_WORKDEGREE";
										 
									 }
									 else
									 {
										 //פ������,�����ַ�ʽ
										 if(m_SUPPLYMODED == 1)
										 {
											 
											 //�����ַ�ʽ�����Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 {
												 
												 //�������й����-�����ۼ�ֵ
												 if(m_handno == 0)
												 {
													 value  = 0x56;
												 } 
												 else
												 {   
													 value  = 0x5A;
												 }
												 
											 }
											 else
											 {

												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 { 
													 //�������й����-�����ۼ�ֵ
													 if(m_handno == 0)
													 {
														 value  = 0x16;
													 } 
													 else
													 {   
														 value  = 0x1A;
													 }
													 
												 }
												 else
												 {
													 //�������й����-�����ۼ�ֵ
													 if(m_handno == 0)
													 {
														 value  = 0xD0;
													 }
													 else
													 {   
														 value  = 0xD4;
													 }
												 }


											 }

											 m_StrArray[10].Format("%dվ�й�",m_handno);
										 }
										 else
										 {

											 //��������,�������й����-����ֵ�����Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 {
												 
												 if(ModuleNo%100 < 12)
												 {
													 value = 0x06;
												 }
												 else
												 {
													 value = 0x5E;
												 }

											 }
											 else
											 {
												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(ModuleNo%100 < 12)
													 {
														 value = 0x02;
													 }
													 else
													 {
														 value = 0x1E;
													 }

												 }
												 else
												 {
													 value     = 0x82;
												 }

											 }

											 m_StrArray[10]  = "�й����";
										 }

										 m_FieldNames        = "GARRISON_WORKDEGREE";
									 }

									 break;
								 }	 
							 case 1:
								 {
									 //1��3Ϊ�����ֹ���ר��,WhichTable  �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ����,���й����-����ֵ
										 if(m_PROTOCOL == 22)
										 {
											 value        = 0x5F;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value        = 0x1F;
											 }
											 else
											 {
												 value        = 0x02;
											 }

										 }

										 m_FieldNames = "REALTIME_WORKDEGREETOTAL";
									 }
									 else
									 {
										 //פ������,�������й����-����ֵ
										 if(m_PROTOCOL == 22)
										 {
											 value        = 0x5E;
										 }
										 else
										 { 
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value        = 0x1E;
											 }
											 else
											 {
												 value        = 0x82;
											 }

										 }

										 m_FieldNames = "GARRISON_WORKDEGREETOTAL";
									 }

									 m_StrArray[10]   = "���й�";
									 break;
								 }
							 case 2:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {  
										 //�����ַ�ʽ
										 if(m_SUPPLYMODED == 1)
										 {
											 
											 //���Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 {
												 
												 //�����ַ�ʽ
												 if(m_handno == 0)
												 {
													 //���޹����-�����ۼ�ֵ
													 value = 0x55;
												 }
												 else
												 {  
													 //���޹����-�����ۼ�ֵ
													 value = 0x59;
												 }
												 
											 }
											 else
											 {
												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 { 
													 //�����ַ�ʽ
													 if(m_handno == 0)
													 {
														 //���޹����-�����ۼ�ֵ
														 value = 0x15;
													 }
													 else
													 {  
														 //���޹����-�����ۼ�ֵ
														 value = 0x19;
													 }
													 
												 }
												 else
												 {
													 //�����ַ�ʽ
													 if(m_handno == 0)
													 {
														 //���޹����-�����ۼ�ֵ
														 value = 0x52;
													 }
													 else
													 {  
														 //���޹����-�����ۼ�ֵ
														 value = 0x56;
													 }

												 }

											 }

											 m_StrArray[10].Format("%dվ�޹�",m_handno);
											 
										 }
										 else
										 {   
											 //��������,���޹����-����ֵ
											 if(m_PROTOCOL == 22)
											 {
												 value = 0x5D;            
											 }
											 else
											 { 
												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 value = 0x1D;  
												 }
												 else
												 {
													 value = 0x06; 
												 }

											 }

											 m_StrArray[10] = "�޹����";
										 }

										 m_FieldNames       = "REALTIME_LOSEDEGREE";//���޹����

									 }
									 else
									 {
										 //פ������,�����ַ�ʽ
										 if(m_SUPPLYMODED == 1)
										 {
                                             
											 //���Ϊ22Э��
											 if(m_PROTOCOL == 22)
											 {

												 if(m_handno == 0)
												 {
													 //�������޹����-0վ�����ۼ�ֵ
													 value  = 0x54;
												 }
												 else
												 {
													 //�������޹����-1վ�����ۼ�ֵ
													 value  = 0x58;
												 }
												 
											 }
											 else
											 {
												  //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 
													 if(m_handno == 0)
													 {
														 //�������޹����-0վ�����ۼ�ֵ
														 value  = 0x14;
													 }
													 else
													 {
														 //�������޹����-1վ�����ۼ�ֵ
														 value  = 0x18;
													 }

												 }
												 else
												 {
													 if(m_handno == 0)
													 {
														 //�������޹����-�����ۼ�ֵ
														 value   = 0xD2;
													 }
													 else
													 {
														 //�������޹����-�����ۼ�ֵ
														 value   = 0xD6;
													 }
												 }

											 }

											 m_StrArray[10].Format("%dվ�޹�",m_handno);
											 
										 }
										 else
										 {
											 //��������,�������޹����-����ֵ
											 if(m_PROTOCOL == 22)
											 {
												 value = 0x5C;
											 }
											 else
											 {
												 //61��62Э��
												 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
												 {
													 value = 0x1C;
												 }
												 else
												 {
													 value = 0x86;
												 }

											 }

											 m_StrArray[10]    = "�޹����";
										 }

										 m_FieldNames = "GARRISON_LOSEDEGREE";
										 
									 }

									 break;
								 }	 
							 case 3:
								 {
									 //1��3 Ϊ�����ֹ�����ܱ�ʱר��,WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {  
										 //���Զ��޹����-����ֵ,���Ϊ22Э��
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x5D;
										 }
										 else
										 { 
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x1D;
											 }
											 else
											 {
												 value  = 0x06;
											 }

										 }

										 m_FieldNames = "REALTIME_LOSEDEGREETOTAL";//���޹����
									 }
									 else
									 {
										 //פ������,�������޹����-����ֵ
                                         if(m_PROTOCOL == 22)
										 {
											 value   = 0x5C;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value   = 0x1C;
											 }
											 else
											 {
												 value   = 0x86;
											 }
											 
										 }

										 m_FieldNames = "GARRISON_LOSEDEGREETOTAL";
									 
									 }
									 
									 m_StrArray[10]   = "���޹�";

									 break;
								 }
							 case 4:
								 {   
									 //WhichTable  �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ����,A�����
										 if(m_PROTOCOL == 22)
										 {
											 value  =  0x69;
										 }
										 else
										 {
											 //61��62Э��
											 if((m_PROTOCOL/10) == 6)
											 {
												 value  =  0x09;
											 }
											 else 
											 { 
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  =  0x1C;  
												 }

											 }
											 
										 }

										 m_FieldNames = "REALTIME_ACURRENT";
									 }
									 else
									 {
										 //פ������,A�����,���Ϊ22Э��
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x68;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x08;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0xF0; 
												 }
												 else
												 {
													 value  = 0x9C;
												 }

											 }

										 }				   
										 
										 m_FieldNames = "GARRISON_ACURRENT";
									 }

									 //61��62Э��
									 if((ModuleNo%100) >=12)
									 {

										 if(int(m_PROTOCOL/10) == 6) 
										 {

                                             m_StrArray[10]   = "�������";
										 
										 }
										 else
										 { 
											 //71��72��73Э����ٶ�
											 if((m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
									              m_StrArray[10]   = "3��ѹA����";
											 }
											 else
											 {
												 m_StrArray[10]    = "�������";
											 }

										 }
									 }
									 else
									 {
										 m_StrArray[10]   = " A�����";
									 }

									 break;
								 } 
							 case 5:
								 {  
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ��B�����,���Ϊ22Э��
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x67;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x09;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0x62; 
												 }
												 else
												 {
												    value   =  0x1E;  
												 }
											 }

										 }

										 m_FieldNames = "REALTIME_BCURRENT";
										 
									 }
									 else
									 {
										 //פ����B�����
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x66;	 
										 }
										 else
										 {
											 //61��62Э��
											 if((m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x08;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0xF2; 
												 }
												 else
												 {
												    value   =  0x9E;  
												 }

											 }

										 }
     									
										 m_FieldNames = "GARRISON_BCURRENT";
									 }

									  //61��62Э��
									 if((ModuleNo%100) >=12)
									 {

										 if((m_PROTOCOL/10) == 6)
										 {
										      m_StrArray[10]   = "�������";
										 }
										 else
										 {
											 //71��72��73Э����ٶ�
											 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
												 m_StrArray[10]   = "BC�����������޹���";
												 
											 }
											 else
											 {
												 m_StrArray[10]   = "�������";
											 }

										 }

									 }
									 else
									 {
										 m_StrArray[10]   = " B�����";
									 }

									 break;
								 }
							 case 6:
								 {   
									 //WhichTable�ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ��C����� 
										 if(m_PROTOCOL == 22)
										 {
											  value   = 0x65;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x09;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0x62; 
												 }
												 else
												 {
												     value  = 0x20;  
												 }

											 }
										 
										 }

										 m_FieldNames = "REALTIME_CCURRENT";
									 }
									 else
									 {
										 //פ����C�����
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x64;
										 }
										 else
										 { 
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 { 
												 value  = 0x08;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0xF2; 
												 }
												 else
												 {
												    value  =  0xA0;  
												 }

											 }

										 }

										 m_FieldNames = "GARRISON_CCURRENT";
									 }
                                     
									 //61��62Э��
									 if((ModuleNo%100) >=12)
									 {
										 
										 if(int(m_PROTOCOL/10) == 6)
										 {											 
											 m_StrArray[10]   = "�������";
										 }
										 else
										 {
											 //71��72��73Э����ٶ�
											 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
											 {
												 m_StrArray[10]   = "BC�����������޹���";
											 }
											 else
											 {
												 m_StrArray[10]   = "�������";
											 }
										 
										 }

									 }
									 else
									 {
										 m_StrArray[10]   = " C�����";
									 }

									 break;
								 }
							 case 7:
								 {   
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ��A���ѹ
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x6F;
										 }
										 else
										 { 
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  = 0x16;
												 }
												 
											 }
											 
										 }

										 m_FieldNames = "REALTIME_AVOLTAGE";
										 
									 }
									 else
									 {
										 //פ����A���ѹ
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x6E;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0A;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0xF0; 
												 }
												 else
												 {
												    value  = 0x96;
												 }

											 }

										 }

										 m_FieldNames = "GARRISON_AVOLTAGE";
									 }
									 
									 //ģ���<��12�ģ����Բɵ�ѹ
									 if(ModuleNo%100 <= 12)
									 {
										 
										 //ģ���Բɵ�ѹ,���Ϊ22Э��
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  =   0x01;
										 }
										 else
										 {
											 value  =   0x3A;
										 }

										 m_StrArray[10] = "��ѹ";

									 }
									 else
									 {
									
										 //61��62Э��
										 if((ModuleNo%100) >=12)
										 {
											
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "�����ѹ";
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC��ѹA����";
												 }
												 else
												 {
													 m_StrArray[10] = "�����ѹ";
												 }

											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " A���ѹ";
										 }
									 
									 }

									 break;
								 }  
							 case 8:
								 {	
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ����B���ѹ 
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6D;
										 }
										 else
										 {	 
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value   =  0x18;
												 }
												 
											 }

										 }

										 m_FieldNames = "REALTIME_BVOLTAGE";
									 }
									 else
									 {
										 //פ����B���ѹ
										 if(m_PROTOCOL == 22)
										 {
											  value   =  0x6C;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0A;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0xF0; 
												 }
												 else
												 {
												    value  = 0x98;
												 }

											 }

										 }
										 
										 m_FieldNames = "GARRISON_BVOLTAGE";
									 }
									 
									 //ģ���<��12�ģ����Բɵ�ѹ
									 if(ModuleNo%100 <= 12)
									 {
										 //ģ���Բɵ�ѹ
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  = 0x01;
										 }
										 else
										 {
											 value  = 0x3A;
										 }

										 m_StrArray[10] = "��ѹ";
									 }
									 else
									 { 
										 //61��62Э��
										 if((ModuleNo%100) >=12)
										 {
											 
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "�����ѹ";
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC��ѹA����";
												 }
												 else
												 {
													 m_StrArray[10] = "�����ѹ";
												 }
												 
											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " B���ѹ";
										 }

									 }

									 break;
								 }
							 case 9:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ��C���ѹ
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6B;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x0B;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0x60; 
												 }
												 else
												 {
													 value  = 0x1A;
												 }
												 
											 }

										 }

										 m_FieldNames = "REALTIME_CVOLTAGE";
									 }
									 else
									 {
										 //פ����C���ѹ 
										 if(m_PROTOCOL == 22)
										 {
											 value   =  0x6A;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value   =  0x0A;
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,ABC�������ѹ+A�����
                                                     value  =  0xF0; 
												 }
												 else
												 {
													 value   =  0x9A;
												 }
											 }
										
										 }

										 m_FieldNames = "GARRISON_CVOLTAGE";
									 }
                         
									 //ģ���<��12�ģ����Բɵ�ѹ
									 if(ModuleNo%100 <= 12)
									 {
										//ģ���Բɵ�ѹ
										 if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
										 {
											 value  = 0x01;
										 }
										 else
										 {
											 value  = 0x3A;
										 }

										 m_StrArray[10] = "��ѹ";

									 }
									 else
									 {
										 //61��62Э��
										 if((ModuleNo%100) >=12)
										 {
											 
											 if((m_PROTOCOL/10) == 6)
											 {
												 m_StrArray[10] = "�����ѹ";
											 }
											 else
											 {
												 //71��72��73Э����ٶ�
												 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 m_StrArray[10]   = "ABC��ѹA����";
												 }
												 else
												 {
													 m_StrArray[10]   = "�����ѹ";
												 }
												 
											 }
											 
										 }
										 else
										 {
											 m_StrArray[10] = " C���ѹ";
										 }
										 
									 }

									 break;
								 }
							 case 10:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ��������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x53;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x13;
											 }
											 else
											 {
												 value  = 0x58;
											 }

										 }

										 m_FieldNames = "REALTIME_JFDL";
									 }
									 else
									 {
										 //פ����������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x52;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x12;
											 }
											 else
											 {
												 value  = 0xD8;
											 }

										 }

										 m_FieldNames = "GARRISON_JFDL";
										 
									 }
                         			
									 m_StrArray[10]   = "������";

									 break;
								 }	 
							 case 11:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ�������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x51;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x11;
											 }
											 else
											 {
												 value  = 0x5A;
											 }

										 }

										 m_FieldNames = "REALTIME_FDL";
									 }
									 else
									 {
										 //פ����������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x50;
										 }
										 else
										 { 
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x10;
											 }
											 else
											 {
												 value  = 0xDA;
											 }

										 }
										 m_FieldNames = "GARRISON_FDL";
									 }
                         			
									 m_StrArray[10] = "�����";
									 break;
								 }	 
							 case 12:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   

										 //������ʽ��ƽ����
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4F;
										 }
										 else
										 { 
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x0f;
											 }
											 else
											 {
												 value  = 0x5C;
											 }
											 
										 }

										 m_FieldNames = "REALTIME_PDL";
									 }
									 else
									 {
										 //פ����ƽ����
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4E;
										 }
										 else
										 {	
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 {
												 value  = 0x0e;
											 }
											 else
											 {
												 value  = 0xDC;
											 }

										 }

										 m_FieldNames = "GARRISON_PDL";
									 }
                         			
									 m_StrArray[10]   = "ƽ����";
									 break;
								 }	
							 case 13:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ���ȵ���
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4D;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 { 
												 value  = 0x0D;
												 
											 }
											 else
											 {
												 value  = 0x5E;
											 }

										 }
										 
										 m_FieldNames = "REALTIME_GDL";
									 }
									 else
									 {
										 //פ�����ȵ���
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x4C;
										 }
										 else
										 {
											 //61��62Э��
											 if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
											 { 
												 value  = 0x0C;
											 }
											 else
											 {
												 value  = 0xDE;
											 }
										 }

										 m_FieldNames = "GARRISON_GDL";
									 }
                         			
									 m_StrArray[10]   = "�ȵ���";
									 break;
								 }	
							 case 14:
								 {
									 //WhichTable �ĸ��� 0----���ݱ� 1----פ����
									 if(WhichTable != 1)
									 {   
										 //������ʽ����������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x63;
										 }
										 else
										 {
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x07;
											 }
											 else
											 { 
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0x62; 
												 }
												 else
												 {
												     value  = 0x38;
												 }

											 }

										 }

										 m_FieldNames = "REALTIME_GLYS";
									 
									 }
									 else
									 {

										 //פ������������
										 if(m_PROTOCOL == 22)
										 {
											 value  = 0x62;
										 }
										 else
										 { 
											 //61��62Э��
											 if(int(m_PROTOCOL/10) == 6)
											 {
												 value  = 0x06;
											 }
											 else
											 {	 
												 //71��72��73Э����ٶ�
												 if((m_PROTOCOL/10) == 7  && m_QuickReading)
												 {
													 //һ��������4����,BC�����+��������+�޹�����
                                                     value  =  0xF2; 
												 }
												 else
												 {
													 value  = 0xB8;
												 }

											 }
											 
										 }

										 m_FieldNames = "GARRISON_GLYS";
									 }

									 //71��72��73Э����ٶ�
									 if(int(m_PROTOCOL/10) == 7  && m_QuickReading)
									 {
										 m_StrArray[10]   = "BC�����������޹���";
									 }
									 else
									 {
                               			 m_StrArray[10]   = "��������";
									 }

									 break;
								 }
								 
							}
							
							/////////////////////////////ѡ�����////////////////////////
					
							//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
							StatusStr.Format("%s[%d-%d-%d][%s%d-%d][%d],���%.2f��,���Ժ�...",title,www + 1,recycles,Settimes,m_StrArray[10],fields,j + 1,ModuleNo,float(j)*100/fields);
							SendMessage(WM_EVENT,1,0);

    						///////////////////////////////////��ʼ����/////////////////////////
							//����ʼֵ
							CurrentValue = -1;
	                        
							//������߱��վ�ܱ�����ֱ�Ӷ���,�����·������
							if(m_AMMETERKIND <= 5)
							{	

								//��ʱפ������,��Сʱ�����
								if(m_ReadKinds > 0)
								{
								
									CTime  EveryHourtimet= CTime::GetCurrentTime();
									
									//��Сʱ��������С�������е���
									if(m_OldReadHour != EveryHourtimet.GetHour() && EveryHourtimet.GetMinute() < 10)
									{
										EveryHourCheckLine();
										m_OldReadHour = EveryHourtimet.GetHour();
										StatusStr.Format("%s[%d-%d-%d][%s%d-%d][%d],���%.2f��,���Ժ�...",title,www + 1,recycles,Settimes,m_StrArray[10],fields,j + 1,ModuleNo,float(j)*100/fields);
										SendMessage(WM_EVENT,1,0);
									}
									
									BOOL  m_ChuWG = FALSE;

									switch(m_WgLess)
									{
										
									case 0:
										{
											//10����,�޹����������
											if(EveryHourtimet.GetMinute()/10 != m_OldReadMinute)
											{
                                               m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/10;
											}

											break;
										}
									case 1:
										{
											//20����
											if(((EveryHourtimet.GetMinute()/10)%2) == 0  && (EveryHourtimet.GetMinute()/20)!= m_OldReadMinute)
											{
											   m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/20;
											}
											
											break;
										}
									case 2:
										{
											//30����
											if(((EveryHourtimet.GetMinute()/10)%3) == 0  && (EveryHourtimet.GetMinute()/30)!= m_OldReadMinute)
											{
											   m_ChuWG         = TRUE;
											   m_OldReadMinute =  EveryHourtimet.GetMinute()/30;
											}

											break;
										}

									}
								
											
									if(m_ChuWG)
									{
										strValue =  StatusStr;
										
										//���е��޹�����һ��
										ALLWuGongDeal();

										StatusStr = strValue;
										SendMessage(WM_EVENT,1,0);
									}
								
								}

								//��������û�ж�����
								if(PhaseNo > 2)
								{
									
									//���඼Ҫ����һ��
									for(int m_TestReadtimes = 0; m_TestReadtimes < 3; m_TestReadtimes ++)
									{
										
										if(m_StartRead)
										{
							
											//���û�м��
											if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
											{
												
												//����е���
												if(CheckIfHaveCurrentValue(MotherLine,LineNo))
												{
													
													m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
													
												}
												
											}										
										
											
											//����е���
											if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
											{	

												if(m_SendAngle == 0)
												{
													//�·��������
													CurrentValue =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//�ǽǱ����,�·��������
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo, m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}

											}
											else
											{
                                                CurrentValue =  -6;//û�е���
											}
																				
										}
                                        
										//һ�첻����300��
										SurrenderWindowMessage();
											
										//������������֣��ٶ�һ������
										if((int(CurrentValue) == -1 || int(CurrentValue) == -6) && m_SUPPLYMODED == 2 && m_StartRead)
										{
										
											
											//���û�м��
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] > 1)
											{
												
												//����е���
												if(CheckIfHaveCurrentValue(BakMotherLine,BakLineNo))
												{
													
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  0;
													
												}
												
											}									
											
											//������������е���
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] == 1 )
											{
												
												if(m_SendAngle == 0)
												{
													//�·��������
												     CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//�ǽǱ����,�·��������
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,m_TestReadtimes,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												
												//����ڱ���ĸ�ߺͱ��ó����϶�����
												if(int(CurrentValue) != -1)
												{
													
													MotherLine =   BakMotherLine;
													LineNo     =       BakLineNo;
													PhaseNo    = m_TestReadtimes;
													
												}
											
											}
									

										}
										
										SurrenderWindowMessage();

										//�������ֹͣ��ť
										if(!m_StartRead)
										{	
											break;
										}

									    //��̬��ض���ʱ��
										if(m_CheckReading)
										{

											ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

											//1����ǰֹͣ
											if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
											{
												break;
											}

										}			

										SurrenderWindowMessage();

										//����ҳ�����λ
										if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
										{	
										
											//��
											switch(m_TestReadtimes)
											{
											case 0:
												{
												    m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A��",m_PROTOCOL);
													break;
												}
											case 1:
												{
													m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B��",m_PROTOCOL);
													break;
												}
											case 2:
												{
													m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C��",m_PROTOCOL);
													break;
												}
										
											}

											//�޸����ֵ
											strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",m_TestReadtimes,ModuleNo - 16,ModuleNo + 16);//�޸����ֵ
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
																					
                                            //�������ֵ
											PhaseNo         = m_TestReadtimes;
											m_PhaseBak      = PhaseNo;
											m_PhaseModule   = ModuleNo;                							
											break;
										}

										SurrenderWindowMessage();

										//Sleep(300);

										//�������ֹͣ��ť
										if(!m_StartRead)
										{	
											break;
										}
							
									}

								}
								else
								{
									
									SurrenderWindowMessage();
									//Sleep(200);

									//�ඨ�Ļ�,��ԭ���ı��¼����
									if(m_OldModule > 0 && m_OldCurrentValue >= 0 && a >= 7 && a <= 9 && m_OldModule/100 == ModuleNo/100 && ModuleNo%100 <= 12)
									{	
										CurrentValue      =   m_OldCurrentValue;
										m_OldModule       =            ModuleNo;
										m_UseOldValue     =                TRUE;
									}
									else
									{	
										
										//���û�м��
										if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
										{
											
											//����е���
											if(CheckIfHaveCurrentValue(MotherLine,LineNo))
											{
												
												m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
											}
											else
											{
												m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
												
											}
											
										}									
										
										//����е���
										if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
										{
											
											//�·��������
											if(m_SendAngle == 0)
											{
												//�·��������
												CurrentValue      =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
											}
											else
											{
												//�ǽǱ����,�·��������
												CurrentValue      =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
											}

											m_UseOldValue     =  FALSE;

										}
										else
										{
											CurrentValue =  -6;//û�е���
										}
									    
										SurrenderWindowMessage();

										//������������֣��ٶ�һ������
										if((int(CurrentValue) == -1 || int(CurrentValue) == -6)  &&  m_SUPPLYMODED == 2 && m_StartRead)
										{
											
											//���û�м��
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] > 1)
											{
												
												//����е���
												if(CheckIfHaveCurrentValue(BakMotherLine,BakLineNo))
												{
													
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  1;
												}
												else
												{
													m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] =  0;
													
												}
												
											}									
											
											//����е���
											if(m_All_Line_Current[(BakMotherLine-1)*15 + BakLineNo - 1] == 1 )
											{

												//�·��������
												if(m_SendAngle == 0)
												{
													//�·��������
													CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												else
												{
													//�ǽǱ����,�·��������
													CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,value,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
												}
												
												//����ڱ���ĸ�ߺͱ��ó����϶�����
												if(int(CurrentValue) != -1)
												{
													switch(PhaseNo)
													{
													case 0:
														{
															m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A��",m_PROTOCOL);
															break;
														}
													case 1:
														{
															m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B��",m_PROTOCOL);
															break;
														}
													case 2:
														{
															m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C��",m_PROTOCOL);
															break;
														}
													}
													
													MotherLine = BakMotherLine;
													LineNo     =     BakLineNo;
												}

											}

										}

										SurrenderWindowMessage();

										//�������ֹͣ��ť
										if(!m_StartRead)
										{	
											break;
										}

									    //��̬��ض���ʱ��
										if(m_CheckReading)
										{

											ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

											//1����ǰֹͣ
											if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
											{
												break;
											}

										}			

										if(a >= 7 && a <= 9 && (ModuleNo%100 <= 12))
										{
											m_OldModule       =      ModuleNo;
											m_OldCurrentValue =  CurrentValue;
										}

									}

									/*
									if(m_ReadTimes > 3  &&  m_GetDataFromFile)
									{
										//ʱ��
										CTime timet = CTime::GetCurrentTime();	
										strValue.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
										CurrentValue  =	GetTestData(ModuleNo,strValue);	
									}
									*/
								}

								SurrenderWindowMessage();
								
								//����������,���й���Ȼ򶳽���,�����ԭ���ı��
    							if((a < 1) && (ModuleNo%100 < 12) && (CurrentValue >= 0))
								{
									//���ϵ���ֵ
									CurrentValue =  CurrentValue + m_BeginValue;
								}							
						

								//�ر������,����Ƕ�פ���Ļ������������ֵ���ϴ�һ�������ٶ�һ��ʵʱֵ����
								if((WhichTable == 1  && (CurrentValue >= 0 || int(CurrentValue) == -4)) && !m_CanQuickRead71485)
								{
                                    
									//�ͷ�CPUʱ��
									SurrenderWindowMessage();									
	                                
									//������ڶ�
									if(m_StartRead)
									{
									
										//����������ѹ������������һ��Ӧ�ñ�һ�δ�,���û��פ�������߻����ϴε�פ��
										if(((a < 4 || (a > 9 && a < 13)) && CurrentValue >= 0) || (int(CurrentValue)==-4))
										{ 

											m_StillRunning = FALSE;

											if(CurrentValue >= 0)
											{
												//���������
												if(!CheckReadValueValid(ModuleNo,m_FieldNames,CurrentValue,m_ZhuLiuTime,1))
												{												   
												   //WriteToLog("���פ����ԭ��С���,�����");                                                    
													m_StillRunning = TRUE;
													CurrentValue   =   -1;
												}
												
											}										

											//���������Ч�Խ���
											if(m_StillRunning || (int(CurrentValue) == -4))
											{

												//��Ч�Ļ�,��ʵʱ��ֵ
												if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
												{
													//22         Э�������� ��ʽ����=פ������+1
													tempvalue     =  value + 0x01;
												}
												else
												{
													//31,32,71,72Э�������� ��ʽ����=פ������-0x80
													tempvalue     =  value - 0x80;
												}
													
												//������ڶ�
												if(m_StartRead)
												{

													//���û�м��
													if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] > 1)
													{
														
														//����е���
														if(CheckIfHaveCurrentValue(MotherLine,LineNo))
														{
															
															m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
														}
														else
														{
															m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
															
														}
														
													}									
													
													//����е���
													if(m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] == 1 )
													{
														
														m_CheckTimes =  0;

														//��������2��
														for(int m_qqq = 0; m_qqq < 3; m_qqq++)
														{	
															//�ͷ�CPUʱ��
															SurrenderWindowMessage();
															
															//�·��������
															if(m_SendAngle == 0)
															{
																//�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��
																CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,tempvalue,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
															}
															else
															{
																//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��
																CurrentValue  =  ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,tempvalue,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
															}
															
															SurrenderWindowMessage();

														    if(CurrentValue >= 0  && m_StartRead)
															{
															
																//����������,���й���Ȼ򶳽���,�����ԭ���ı��
																if((a < 1) && (ModuleNo%100 < 12) && (CurrentValue >= 0))
																{
																	//���ϵ���ֵ
																	CurrentValue =  CurrentValue + m_BeginValue;
																}		

																//���������Ч�Խ���
																if(!CheckReadValueValid(ModuleNo,m_FieldNames,CurrentValue,m_ZhuLiuTime,0))
																{
																	m_CheckTimes ++;
																//	WriteToLog("<<���פ����ԭ��С,�����>>");
                                                                    CurrentValue = -1;
																}
																else
																{
																	break;
																}
																
																if(!m_StartRead)
																{
																	CurrentValue = -1;
																	break;
																}

															}
															
															//�ͷ�CPUʱ��
															SurrenderWindowMessage();
															
														}

														SurrenderWindowMessage();

														//������2�����ϣ�����ʵ��ֵ��ԭ����С�Ļ����´β���
														if(m_CheckTimes > 1 && CurrentValue < 0)
														{															
															strValue.Format("UPDATE TB_USER SET %s = STUFF(%s,%d,1,'Y') WHERE USER_MODULENO=%d",m_ReadMeterLabel,m_ReadMeterLabel,a+1,ModuleNo);
															CDataBaseInstance::ExecuteDataBaseSQL(strValue);
														}

													}
													else
													{
														CurrentValue  =  -6;//û�е���
													}

												}


											}
										
										}

									
									}

									//�ͷ�CPUʱ��
									SurrenderWindowMessage();
								
									if(!m_StartRead)
									{	
										break;
									}

								    //��̬��ض���ʱ��
									if(m_CheckReading)
									{

										ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;

										//1����ǰֹͣ
										if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
										{
											break;
										}

									}			
									
								}
								//�ر������
												
							}
							else
							{
								//long  m_address ���ַ
								//short kinds     ��  ��  0---�й� 2---�޹� 4---A����� 5---B����� 6---C����� 7---A���ѹ 8---B���ѹ 9---C���ѹ
								//ֱ�Ӵ�485�ڶ�����
								if(a != 1 || a != 3)//1,3Ϊ�����ֶ����й������޹�
								{
									//m_StrArray[9]��̨����  485���ϵĵ���6λ�ڱ�̨������
									m_StrArray[9].TrimLeft();
									m_StrArray[9].TrimRight();

									//���ڱ�12λ��ַ
									strValue.Format("%6d%6d",atol(m_StrArray[9]),int(ModuleNo/100)); 
									strValue.Replace(' ', '0');
					
									CurrentValue =  ReadDataFrom485Com2(strValue,a);

									m_StrArray[9] = "���ڶ���";
								}
								else
								{
									continue;
								}
								
							}
							
							///////////////////////////////////���ݶ���ֵ�½���/////////////////////////
							//���б�����ʾ�����
							if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3 || int(CurrentValue) == -6)
							{

								if(!m_UseOldValue)
								{
									
									if(!m_IsAutoSending)
									{
										//��ʱפ��������
										Beep(5000,400);  //2004.12.13��
									}

								}
															
								//���ö��ɹ���־
								if(int(CurrentValue) != -6)
								{
									strValue.Format("UPDATE TB_USER SET %s = STUFF(%s,%d,1,'Y') WHERE USER_MODULENO=%d",m_ReadMeterLabel,m_ReadMeterLabel,a+1,ModuleNo);
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								}
								
								//ʱ��
								CTime timet = CTime::GetCurrentTime();
								
								//��פ������Ļ�
								if(	WhichTable == 1)
								{

									m_StrArray[12] = m_ZhuLiuTime;//פ��ʱ��
									m_ReadTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

								}
								else
								{	
									
									//��̬��ض���ʱ��
									if(m_CheckReading)
									{
										m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),m_shikedian,0);
									}
									else
									{
										m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
									}

								}

								/********************ѡ�����**************/
								if(CurrentValue >= 0)
								{
								
									if(m_PROTOCOL == 61 || m_PROTOCOL == 62)
									{
										//61,62Э��С����Ϊ1λ
								    	strValue.Format("%.1f",CurrentValue);
									}
									else
									{
										strValue.Format("%.2f",CurrentValue);

									}

									m_StrArray[11].Format("%12s",strValue);
									
									//61��62Э���485��ĵ�����ѹ����
									if(int(m_PROTOCOL/10) == 6 && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
									{
										//6162Э��
										if(value==0x08 || value==0x09)
										{
										   //�ֿ��������
										   m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2);
										}
										else if(value==0x0B || value==0x0A)
										{
										   //�ֿ������ѹ
										   m_StrArray[11].Format("%3d,%3d,%3d",(int(CurrentValue)/16384)*2,((int(CurrentValue)%16384)/128)*2,(int(CurrentValue)%128)*2);
										}

									}

									//71,72�Ŀ��ٶ���
									if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0xF0 || value==0x62 || value==0xF2))
									{
										
										if(value==0x60 || value==0xF0)
										{											
											//3��ѹA���� 
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3]);//(long(CurrentValue)/long(pow((double)2,24)))*2.0,((long(CurrentValue)%long(pow((double)2,24)))/long(pow((double)2,16)))*2.0,((long(CurrentValue)%long(pow((double)2,16)))/long(pow((double)2,8)))*2.0,(long(CurrentValue)%long(pow((double)2,8)))*0.2);
											m_StrArray[10]   = "3��ѹA����";
											//3��ѹA���� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 4)+'Y'+SUBSTRING(%s,6,2)+'YYY'+SUBSTRING(%s, 11, 5)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);									

										}
										else
										{
											//BC����,��������,�޹�����
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3]);//(long(CurrentValue)/long(pow((double)2,24)))*0.2,((long(CurrentValue)%long(pow((double)2,24)))/long(pow((double)2,16)))*0.2,((long(CurrentValue)%long(pow((double)2,16)))/long(pow((double)2,8)))*0.01,(long(CurrentValue)%long(pow((double)2,8)))*0.01);
											m_StrArray[10]   = "BC���������޹���";
											//BC�������������ء��޹����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
										    strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 5)+'YY'+SUBSTRING(%s,8,6)+'Y'", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
											
										}	
										
									//	WriteToLog(strValue);								
										
									}

									/////////////////////////////////////////////////
									//71,72�Ŀ��ٶ���,
									if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
									{

                                        if(value==0x5A || value==0x5E || value==0x5C)
										{											
											//ʵʱ�壬�ȣ�ƽ���ٶ���
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
											m_StrArray[10]   = "��ƽ�ȿ��";
											//ʵʱ�壬�ȣ�ƽ���ٶ��� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 11) + 'YYY' +SUBSTRING(%s, 15, 1)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
  										    CDataBaseInstance::ExecuteDataBaseSQL(strValue);
									
										}
										else if(value==0x02 || value==0x06)
										{
											//ʵʱ�й����޹�%f
											m_StrArray[11].Format("%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1]);
											m_StrArray[10]   = "�й��޹����";
											//ʵʱ�й����޹� .a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
											strValue.Format("UPDATE TB_USER SET %s = 'Y' +  SUBSTRING(%s, 2, 1) + 'Y' + SUBSTRING(%s , 4, 11)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										}
										else if(value == 0xDA || value == 0xDE || value == 0xDC)
										{
                                            //פ���壬ƽ����
											m_StrArray[11].Format("%5.1f,%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
											m_StrArray[10]   = "��ƽ�ȿ��";
											//פ���壬�ȣ�ƽ���ٶ��� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
											strValue.Format("UPDATE TB_USER SET %s =  SUBSTRING(%s, 1, 11) + 'YYY' +SUBSTRING(%s, 15, 1)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);	
                                        } 
										else if(value == 0x82 || value == 0x86)
									    { 	 
											//פ��ʵʱ�й����޹�
											m_StrArray[11].Format("%5.1f,%5.1f",m_Quick71Value[0],m_Quick71Value[1]);
											m_StrArray[10]   = "�й��޹����";
											//פ���й����޹� .a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������														
											strValue.Format("UPDATE TB_USER SET %s = 'Y' +  SUBSTRING(%s, 2, 1) + 'Y' + SUBSTRING(%s , 4, 11)", m_ReadMeterLabel,m_ReadMeterLabel,m_ReadMeterLabel);
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);									       
                                        }	
										
									//	WriteToLog(strValue);

									}
														
									////////////////////////////////////////////////////////

									
									//�������������ݿ���,����������ӦС��999999.99
									switch(WhichTable)
									{
									case 0:
										{
											//��������ݱ�,��ʽ����Ļ�,����TB_REALTIME����
											if(IfWriteData)
											{
												
												//��̬��ض���ʱ��
												if(m_CheckReading)
												{
													//��̬��ض���,����TB_REALTIME����,����Э��100,ר��
													strValue.Format("REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",ModuleNo,m_StrArray[12]);
													
													if(CDataBaseInstance::GetAllRecordsCount("TB_REALTIME", strValue) < 1)
													{
														
														//ԭ�ȱ���û�д�����,���¼�	
														if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
														{

															//61��62Э���485��ĵ�����ѹ����
															if(value==0x08 || value==0x09)
															{
																//�ֿ��������
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,100,m_StrArray[12]);
															}
															else if(value==0x0B || value==0x0A)
															{
																//�ֿ������ѹ
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,100,m_StrArray[12]);
															}

														
														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
														{
																								                       
															//71��72Э���485��ĵ�����ѹ����
															if(value==0x60)
															{ 															
																//3��ѹA����
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_ACURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],100,m_StrArray[12]);
															}
															else
															{															
																//BC�������������ء��޹�����
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_GLYS,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],100,m_StrArray[12]);
															}

															
														}														
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
														{
														
															//71,72�Ŀ��ٶ���,
															if(value == 0x5A || value == 0x5E || value == 0x5C)
															{	
															
																//ʵʱ�壬ƽ���ȿ��ٶ���
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL) VALUES (%d,%.1f,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
															}
															else if(value == 0x02 || value == 0x06)
															{
															
																//ʵʱ�й����޹�
																strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_WORKDEGREETOTAL,REALTIME_LOSEDEGREETOTAL) VALUES (%d,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1]);
															}
																												
														}
														else
														{															
														
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s')",m_FieldNames,ModuleNo,CurrentValue,100,m_StrArray[12]);
														
														}


													}
													else
													{
														
														//ԭ��ʵʱ�����д�����,���滻ԭ������
														if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
														{
															
															//61��62Э���485��ĵ�����ѹ����
															if(value==0x08 || value==0x09)
															{
																//�ֿ��������
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_ACURRENT=%.1f,REALTIME_BCURRENT=%.1f,REALTIME_CCURRENT=%.1f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,ModuleNo,m_StrArray[12]);
															}
															else if(value==0x0B || value==0x0A)
															{
																//�ֿ������ѹ
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_AVOLTAGE=%.1f,REALTIME_BVOLTAGE=%.1f,REALTIME_CVOLTAGE=%.1f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,ModuleNo,m_StrArray[12]);
															}


														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
														{
															
															//71��72Э���485��ĵ�����ѹ����
															if(value==0x60)
															{
																//3��ѹA����
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_AVOLTAGE=%.2f,REALTIME_BVOLTAGE=%.2f,REALTIME_CVOLTAGE=%.2f,REALTIME_ACURRENT=%.2f,REALTIME_TRANSCRIBETIME='%s' WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],ModuleNo,m_StrArray[12]);
															}
															else
															{	
																//BC�������������ء��޹�����
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_BCURRENT=%.2f,REALTIME_CCURRENT=%.2f,REALTIME_GLYS=%.2f,REALTIME_TRANSCRIBETIME='%s' WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],ModuleNo,m_StrArray[12]);
															}
															
														}
														else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
														{
															
															//71,72�Ŀ��ٶ���,
															if(value == 0x5A || value == 0x5E || value == 0x5C)
															{	
																//ʵʱ�壬ƽ���ȿ��ٶ���
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_FDL=%.2f,REALTIME_PDL=%.2f,REALTIME_GDL=%.2f WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],ModuleNo,m_StrArray[12]);
															}
															else if(value == 0x02 || value == 0x06)
															{
															
																//ʵʱ�й����޹�
																strValue.Format("UPDATE TB_REALTIME SET REALTIME_WORKDEGREETOTAL=%.2f,REALTIME_LOSEDEGREETOTAL=%.2f WHERE REALTIME_MODULENO=%d AND REALTIME_HALTTIME='%s' AND REALTIME_PROTOCOL=100",m_Quick71Value[0],m_Quick71Value[1],ModuleNo,m_StrArray[12]);
															}
																													
														}
														else
														{
															strValue.Format("UPDATE TB_REALTIME SET %s = %.2f WHERE REALTIME_MODULENO=%d AND REALTIME_TRANSCRIBETIME='%s' AND REALTIME_PROTOCOL=100",m_FieldNames,CurrentValue,ModuleNo,m_StrArray[12]);
														}

													}
																								
												
												}
												else
												{
												
													
													if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
													{
														
														//61��62Э���485��ĵ�����ѹ����
														if(value==0x08 || value==0x09)
														{
															//�ֿ��������
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_ACURRENT,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_PROTOCOL,m_StrArray[12]);
														}
														else if(value==0x0B || value==0x0A)
														{
															//�ֿ������ѹ
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_PROTOCOL,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_PROTOCOL,m_StrArray[12]);
														}
														
													}
													else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0x60 || value==0x62))
													{

														//71��72Э���485��ĵ�����ѹ����
														if(value==0x60)
														{
															//3��ѹA����
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_AVOLTAGE,REALTIME_BVOLTAGE,REALTIME_CVOLTAGE,REALTIME_ACURRENT,REALTIME_PROTOCOL,REALTIME_HALTTIME,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
														}
														else
														{	
															//BC�������������ء��޹�����
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_BCURRENT,REALTIME_CCURRENT,REALTIME_GLYS,REALTIME_PROTOCOL,REALTIME_HALTTIME,REALTIME_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0]*0.2,m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
														}
													
													}
													else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
													{
														
														//71,72�Ŀ��ٶ���,
														if(value == 0x5A || value == 0x5E || value == 0x5C)
														{	
															//ʵʱ�壬ƽ���ȿ��ٶ���
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_FDL,REALTIME_PDL,REALTIME_GDL) VALUES (%d,%.1f,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2]);
														}
														else if(value == 0x02 || value == 0x06)
														{	
														    //ʵʱ�й����޹�
															strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,REALTIME_WORKDEGREETOTAL,REALTIME_LOSEDEGREETOTAL) VALUES (%d,%.1f,%.1f)",ModuleNo,m_Quick71Value[0],m_Quick71Value[1]);
														}
																										
													}
													else
													{
														
														//��ͨ�������¼�
														strValue.Format("INSERT INTO TB_REALTIME(REALTIME_MODULENO,%s,REALTIME_TRANSCRIBETIME,REALTIME_PROTOCOL) VALUES (%d,%.2f,'%s',%d)",m_FieldNames,ModuleNo,CurrentValue,m_StrArray[12],m_PROTOCOL);
													}
																						
												}
												
												//����SQL���
												CDataBaseInstance::ExecuteDataBaseSQL(strValue);

											}
											
											break;
										}
									case 1:
										{
											//פ�����ݱ�,פ������Ļ�,����TB_GARRISON����
											strValue.Format("GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",ModuleNo,m_ZhuLiuTime/*פ��ʱ��*/);
											
											//ԭ��פ������û�д�פ��ʱ�������
											if(CDataBaseInstance::GetAllRecordsCount("TB_GARRISON", strValue) < 1)
											{
												
												//ԭ�ȱ���û�д�����,���¼�
												if((int(m_PROTOCOL/10) == 6) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
												{
												
													//61��62Э���485��ĵ�����ѹ����
													if(value==0x08 || value==0x09)
													{
														//�ֿ��������
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_ACURRENT,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													else if(value==0x0B || value==0x0A)
													{
														//�ֿ������ѹ
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													
												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0xF0 || value==0xF2))
												{
	                                                
													//71��72Э���485��ĵ�����ѹ����
													if(value==0xF0)
													{
														//3��ѹA����
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_AVOLTAGE,GARRISON_BVOLTAGE,GARRISON_CVOLTAGE,GARRISON_ACURRENT,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													else
													{
														//BC�������������ء��޹�����
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_BCURRENT,GARRISON_CCURRENT,GARRISON_GLYS,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}

												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
												{
													
													//71,72�Ŀ��ٶ���,
													if(value == 0xDA || value == 0xDE || value == 0xDC)
													{
														//פ���壬ƽ����
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_FDL,GARRISON_PDL,GARRISON_GDL,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													} 
													else if(value == 0x82 || value == 0x86)
													{ 
														//פ��ʵʱ�й����޹�
														strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,GARRISON_WORKDEGREETOTAL,GARRISON_LOSEDEGREETOTAL,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.1f,%.1f,%d,'%s','%s')",ModuleNo,m_Quick71Value[0],m_Quick71Value[1],m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
													}
													
												}
												else
												{
													strValue.Format("INSERT INTO TB_GARRISON(GARRISON_MODULENO,%s,GARRISON_PROTOCOL,GARRISON_HALTTIME,GARRISON_TRANSCRIBETIME) VALUES (%d,%.2f,%d,'%s','%s')",m_FieldNames,ModuleNo,CurrentValue,m_PROTOCOL,m_ZhuLiuTime,m_ReadTime);
												}

											}
											else
											{   
												
												
												if((m_PROTOCOL == 61 || m_PROTOCOL == 62) && ((ModuleNo%100)>=12 && (ModuleNo%100)<=15) && a>=4 && a<=9)
												{
													
													//61��62Э���485��ĵ�����ѹ����
													if(value==0x08 || value==0x09)
													{
														//�ֿ��������
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_ACURRENT=%.2f,GARRISON_BCURRENT=%.2f,GARRISON_CCURRENT=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",(int(CurrentValue)/16384)*0.2,((int(CurrentValue)%16384)/128)*0.2,(int(CurrentValue)%128)*0.2,m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													else if(value==0x0B || value==0x0A)
													{
														//�ֿ������ѹ
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_AVOLTAGE=%.2f,GARRISON_BVOLTAGE=%.2f,GARRISON_CVOLTAGE=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",(int(CurrentValue)/16384)*2.0,((int(CurrentValue)%16384)/128)*2.0,(int(CurrentValue)%128)*2.0,m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													
												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && (value==0xF0 || value==0xF2))
												{
	                                                
													//71��72Э���485��ĵ�����ѹ����
													if(value==0xF0)
													{
														//3��ѹA����
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_AVOLTAGE=%.2f,GARRISON_BVOLTAGE=%.2f,GARRISON_CVOLTAGE=%.2f,GARRISON_ACURRENT=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}
													else
													{
														//BC�������������ء��޹�����
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_BCURRENT=%.2f,GARRISON_CCURRENT=%.2f,GARRISON_GLYS=%.2f,GARRISON_TRANSCRIBETIME='%s' WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],m_Quick71Value[3],m_ReadTime,ModuleNo,m_ZhuLiuTime);
													}

												}
												else if(m_QuickReading && int(m_PROTOCOL/10) == 7 && ((ModuleNo%100)>=12) && m_CanQuickRead71485)
												{
													
													//71,72�Ŀ��ٶ���,
													if(value == 0xDA || value == 0xDE || value == 0xDC)
													{
														//פ���壬ƽ����
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_FDL=%.2f,GARRISON_PDL=%.2f,GARRISON_GDL=%.2f WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],m_Quick71Value[2],ModuleNo,m_ZhuLiuTime);
													} 
													else if(value == 0x82 || value == 0x86)
													{ 	
														//פ��ʵʱ�й����޹�
														strValue.Format("UPDATE TB_GARRISON SET GARRISON_WORKDEGREETOTAL=%.2f,GARRISON_LOSEDEGREETOTAL=%.2f WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_Quick71Value[0],m_Quick71Value[1],ModuleNo,m_ZhuLiuTime);
													}
													
												}
												else
												{
													//ԭ��פ�������д�פ��ʱ�������,���滻ԭ������
													strValue.Format("UPDATE TB_GARRISON SET %s = %.2f,GARRISON_TRANSCRIBETIME='%s',GARRISON_PROTOCOL=%d WHERE GARRISON_MODULENO=%d AND GARRISON_HALTTIME='%s'",m_FieldNames,CurrentValue,m_ReadTime,m_PROTOCOL,ModuleNo,m_ZhuLiuTime);
												}


											}
											
											//����SQL���
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);

											break;
										}
										
									}

									
								}
								else
								{

									if(int(CurrentValue) == -2)
									{	
										//�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û������
										m_StrArray[11] = "��ͨѶ����";
									}
									else if(int(CurrentValue) == -3)
									{
										//�ص�ֵΪAAAAAA.AA,��չģ��ı�û������
										m_StrArray[11] = "��չ�����";
									}
									else if(int(CurrentValue) == -6)
									{
										//��·ͣ��
										m_StrArray[11] = "��·ͣ��";
									}
									
									m_ReadTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
									
									if(int(CurrentValue) == -2 || int(CurrentValue) == -3)
									{
										//�н��ߴ����д�����ݱ�
										if(	WhichTable == 1)
										{
											//��פ������Ļ�
											strValue.Format("INSERT INTO TB_LINEERROR(LINEERROR_MODULE,LINEERROR_READTIME,LINEERROR_HALTTIME,LINEERROR_KINDS) VALUES (%d,'%s','%s',%d)",ModuleNo,m_ReadTime,m_StrArray[12],2);
											//����SQL���
											CDataBaseInstance::ExecuteDataBaseSQL(strValue);
										}
										else
										{
											
											if(IfWriteData)
											{
												strValue.Format("INSERT INTO TB_LINEERROR(LINEERROR_MODULE,LINEERROR_READTIME,LINEERROR_HALTTIME,LINEERROR_KINDS) VALUES (%d,'%s','%s',%d)",ModuleNo,m_StrArray[12],"",1);
												//����SQL���
												CDataBaseInstance::ExecuteDataBaseSQL(strValue);
											}
											
										}

									}

								}
					
    							//��ʾ����б�
								for(i = 0; i < 13; i++)
								{	
                        
									//����ǵ�һ��
									if(i == 1)
									{
										//������߱��վ�ܱ�
										if(m_AMMETERKIND > 4)
										{
											m_StrArray[i] = m_StrArray[i] + "[��2]";
										}
										
									}
									
     								m_StrArray[i] = " " + m_StrArray[i];
									
								}
								
								//��ʾ�б�����
								SendMessage(WM_EVENT, 3, 0);
							
								//�к��Լ�
								m_ListRows++;
								
							  }
							  
							  //���б�����ʾ�����
							  if(CurrentValue <  0)
							  {
								  //ʱ��
								  CTime timet = CTime::GetCurrentTime();
								  m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
								  
								  //�����һ��û�ж�����Ļ�,��¼����,���߻ص����ݲ���Ҫ��,�����פ������
								  if((m_ReadTimes == READTIMES -1 || int(CurrentValue) == -2 || int(CurrentValue) == -3) && WhichTable== 1) 
								  {  
									  //ȥ���ո��ַ�
									  for(int i = 0; i <= 12; i ++)
									  {
                               			  m_StrArray[i].TrimLeft(); 
							    		  m_StrArray[i].TrimRight(); 
									  }
											  
								  }
					  
							  }
							  
							  ///////////////////////////////////���ݶ���ֵ������/////////////////////////
							  
							  //�û����»�һ����¼
							  rs.MoveNext();
							  SetProgressCtrlSetIt();
							  
							}
							//�ر����ݿ�
							
							if(rs.IsOpen())
							{
								rs.Close();
							}

							//�������ֹͣ��ť
							if(!m_StartRead)
							{	
								break;
							}

							//��̬��ض���ʱ��
							if(m_CheckReading)
							{
								
								ttts = CTime::GetCurrentTime() - m_CheckreadModuleTimes;
								
								//1����ǰֹͣ
								if(ttts.GetTotalSeconds() >= (m_readRangle*60 - 1)*60)
								{
									break;
								}
								
							}			

					  }

				}
				 
			}
			//ɨ��һ�ֽ���
			
			//���ع�����
			ShowProgressCtrl(FALSE);

	    	CTime RecycleTime1 = CTime::GetCurrentTime();
			CTime RecycleTime2 = CTime::GetCurrentTime();

			CTimeSpan       ts;	
	
			//recycles        ѭ������
			//Settimes        ÿ����ʱ����,����
			//��ʱ�ù��ػ���Ϣ
			if(www  < (recycles - 1) && m_StartRead)//�пɶ���¼��־��ѭ������û�е�
			{	
				
				//��ԭ���������,���ʼ����־
				strSql.Format("(%s) AND (%s<>'YYYYYYYYYYYYYY')",constr,m_ReadMeterLabel);
				
				//�õ���¼����
				fields     = CDataBaseInstance::GetAllRecordsCount("TB_USER",strSql);  
				
				if(fields  > 0)
				{
					
					while(1)
					{
						
						RecycleTime2 = CTime::GetCurrentTime();
						ts = RecycleTime2 - RecycleTime1;
						
						if(ts.GetTotalSeconds() >=  Settimes * 60 || !m_StartRead)
						{
							break;
						}
						
						//��ʱһ��
						Sleep(1000);

						//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
						StatusStr.Format("����%d�֣��Ѷ�%d�֣������ֻ���%d��%d�룬���Ժ�...��",recycles,www + 1,(Settimes * 60 - ts.GetTotalSeconds())/60,(Settimes * 60 - ts.GetTotalSeconds())%60);
						SendMessage(WM_EVENT,1,0);

						//�ų�windows��Ϣ
						SurrenderWindowMessage();
					}

				}
				
			}
				        
        }
        
		//�������ֹͣ��ť
		if(!m_StartRead)
		{
			
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			if(db.IsOpen())
			{
				db.Close();
			}
			
			//��ʾ״̬����Ϣ
			StatusStr = "��������;��ֹͣ��";
			SendMessage(WM_EVENT, 1, 0);
			
			//���ع�����
			ShowProgressCtrl(FALSE);
		    return;
		}
		
		//������ɨ��
		if(rs.IsOpen())
		{
			rs.Close();
		}
	
		if(db.IsOpen())
		{
			db.Close();
		}

	}

	//������ɨ��
	if(db.IsOpen())
	{
		db.Close();
	}

    //������ʾ״̬����ʾ
	StatusStr = "�����������";
	SendMessage(WM_EVENT, 1, 0);
	
   	//�����б��������
	SendMessage(WM_EVENT, 13, 0);
	
	//���ع�����
	ShowProgressCtrl(FALSE);
	
	m_times           ++;
	
	//��̬��ض���ʱ��
	if(!m_CheckReading)
	{
		m_StartRead  = FALSE;
	}

	m_others         = FALSE;

}

void CIFRMView::OnPhasetest() 
{
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CPhaseTestDlg        dlg;
	CString       PassStr;
	
	//��¼�ܸ���
	long    m_records = 0;

	//�õ��Ի�������ѡ����
    if(!GetDialogBarStr())
	{
		return;
	}

	dlg.m_StrSql = m_ModuleFindContionStr;
	
	if(dlg.DoModal() == IDOK)
	{
		
		//�Ƿ��಻��,��¼����
		if(dlg.m_nook == TRUE)
		{
            m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", dlg.m_StrSql + " AND USER_PHASE=3");
		}
		else
		{
            m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", dlg.m_StrSql);
		}

		switch(dlg.m_radio)
		{
		case 0:
			{  
				//���������
				//CString title        �б���
				//CString Result       ����
				//CString ConStr       ������Χ
				//BYTE    orders       ����ؼ���
				//BOOL    OnlyReadNot  TRUE  ֻ��û�в��Գ����ģ��,FALSE ��֮
				//int     times        ��ÿ��ģ��Ĵ���
				//BOOL    OnlyOnce     TRUE  �ö����һ��ģ��ʱֻ����һ��,FALSE ÿ��������һ��
				//int     MaxIValue    ���ֵ(Ϊд����ʱ��)
				//int     MinIValue    ��Сֵ
				//int     intervals    ��  ��
				//��ְ汾
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//Ҫ������   
					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					//                  ����11               ����������¼����
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","ģ�����ⶨ","�ⶨ�ɹ�",dlg.m_StrSql,0x02,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","ģ�����ⶨ","�ⶨ�ɹ�",dlg.m_StrSql,0x02,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}

				break;
			}
		case 1:
			{
				//��DSP����ֵ
				//CString title        �б���
				//CString Result       ����
				//CString ConStr       ������Χ
				//BYTE    orders       ����ؼ���
				//BOOL    OnlyReadNot  TRUE  ֻ��û�в��Գ����ģ��,FALSE ��֮
				//int     times        ��ÿ��ģ��Ĵ���
				//BOOL    OnlyOnce     TRUE  �ö����һ��ģ��ʱֻ����һ��,FALSE ÿ��������һ��
				//int     MaxIValue    ���ֵ(Ϊд����ʱ��)
				//int     MinIValue    ��Сֵ
				//int     intervals    ��  ��
				
				//��ְ汾
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//Ҫ������   
					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","��DSP����","��ֵ�ɹ�",dlg.m_StrSql, 0x48,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","��DSP����","��ֵ�ɹ�",dlg.m_StrSql, 0x48,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				
				break;
			}
		case 2:
			{
				//������ֵ
				//CString title        �б���
				//CString Result       ����
				//CString ConStr       ������Χ
				//BYTE    orders       ����ؼ���
				//BOOL    OnlyReadNot  TRUE  ֻ��û�в��Գ����ģ��,FALSE ��֮
				//int     times        ��ÿ��ģ��Ĵ���
				//BOOL    OnlyOnce     TRUE  �ö����һ��ģ��ʱֻ����һ��,FALSE ÿ��������һ��
				//int     MaxIValue    ���ֵ(Ϊд����ʱ��)
				//int     MinIValue    ��Сֵ
				//int     intervals    ��  ��
				
				//��ְ汾
				if(AppInfo::Instance().m_WhichKind == FALSE)
				{
					//Ҫ������   
					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","������ֵ","��ֵ�ɹ�",dlg.m_StrSql,0x44,dlg.m_nook,dlg.m_times,1,1,1,1,m_records);
					
				}
				else
				{
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","������ֵ","��ֵ�ɹ�",dlg.m_StrSql,0x44,dlg.m_nook,dlg.m_times,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}

				break;
			}
			
				
		}
	 
		//��ְ汾,�½���
		if(AppInfo::Instance().m_WhichKind == FALSE)
		{
			
			//Զ�̷��͵��Բ�����ָ��
			if(SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE) == TRUE)
			{
				
				m_StartRead = TRUE;
				
			}
			else
			{
				m_StartRead = FALSE;
			}
			
		}
		
     }
	 
}


//�õ�פ��ʱ��
CString CIFRMView::GetZhuLiuTime()
{
	
	CString         str;
	//�����ݿ�
	CDatabase        db;
	CString      strSql;
	CString    strValue;
	str        =     "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
        
		//�õ���¼����
		long fields = CDataBaseInstance::GetAllRecordsCount("TB_HALTTIME", "ALL");
		
		if(fields > 0)
		{
			
			strSql = "SELECT * FROM TB_HALTTIME";
			
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//���û���Ϣ
			for(int j = 0;j < fields; j++)
			{
				//�õ�ֵ
				rs.GetFieldValue((short)0,str);
				str.TrimRight();
				
				//���»�һ����¼
				rs.MoveNext();
			}
			
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}
	return str;
	
}

void CIFRMView::SendOfficeBreadorder(int generatrix,int times,int m_iBroadTime,BYTE m_Potocol,CString NewTime)
{
	
	CString         StrSql;
	
	BYTE         ORDER[15];
	BYTE          PhaseBit;
	
	//1601 ģ���Ϊ16���Ϊ01
	BYTE AddrH,AddrM,AddrL;
	
	//����window����Ȩ
	SurrenderWindowMessage();
	
	//�㲥��ַ
	AddrH = 0;          //��λ    ��Ӧ��Ϊ����1
	AddrM = 0;          //�м�λ  ��Ӧ��Ϊ����2


	AddrL = m_iBroadTime/int(pow((double)2,10));     //��4λ,����ʱ��ĸ�4λ
	// A 01 B 02  C 03
	
    m_StartRead = TRUE;
	
	BYTE StatusH,StatusL;
	StatusH    = (m_iBroadTime%(int(pow((double)2,10))))/256; //��λ,��Ӧ��Ϊ����3�ĺ�2λ
	StatusL    =  m_iBroadTime%256;                   //��λ    ����4
	switch(times)
	{ 
	case  0://A��
		{
			PhaseBit    = 0x01;
			//	ORDER[4]    = 0x40;  
			break;
		}
	case  1://B��
		{
			PhaseBit    = 0x02; 
			//	ORDER[4]    = 0x80;  
			break;
		}
	case 2://C��
		{  
			PhaseBit    = 0x03;
			//	ORDER[4]    = 0xC0;   
			break;
		}
	}
	
	//������
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x53; //��������
	
	ORDER[3]  = generatrix*64  + 0 + PhaseBit;//�ϳ��ֽ� ǰ2λΪ(j 0��1����ĸ��)ĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
//	ORDER[3]  = 0 + PhaseBit;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[4]  = 3;// ��ʱ��0���� 
	
	//ORDER[0]��ORDER[4]��Ƭ����  
	
	/*
	//����ģ����
	ORDER[5]  = 0xf2; //�����֣�Ҫʲô����
	ORDER[6]  = 0;//ģ��ߵ�ַ
	ORDER[7]  = 0;//ģ���е�ַ
	ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4��Ϊפ��ʱ��,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
	ORDER[9]  = StatusL;//פ��ʱ��
	*/

	if(m_Potocol == 22)
	{
		//���Э��Ϊ22	
		//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������  
		//��ʽ��10λ�ල��+7(7��1)+ 7(7λפ��ʱ��)+ 7(7��0)
		//��ַǰ8λ
		ORDER[5]  = 254   + (m_iBroadTime>>6); //ʱ���1λ	
		//ʱ���6λ + 2λ0
		ORDER[6]  = (m_iBroadTime%64)*4 + 0;
		ORDER[7]  =                    0;
		ORDER[8]  =                    0;
		ORDER[9]  =                    0;
	}
	else
	{
					
		if(m_Potocol == 61 || m_Potocol == 62)
		{
			//61,62Э��
			//ORDER[5]��ORDER[10]�ɵ�Ƭ������ģ���� 21λ��������  
			//��ʽ��18λ�ල��+ ��ַ��8λȫ1 +  ��ַ��6λ(6λפ��ʱ��) + 6(6��0) + 0001000
			//��ַǰ8λ
			ORDER[5]  =                 0xff; //��ַ��8λȫ1	
			ORDER[6]  =    (m_iBroadTime<<2); //��ַ��6λ(6λפ��ʱ��) + 2��0
			ORDER[7]  =                    1; //4��0 �� 0001
			ORDER[8]  =                    0; //000 + 5��0
			ORDER[9]  =                    0;
		}
		else
		{
			//31,32,33,71,72,72Э��
			//����ģ����
			ORDER[5]  = 0xf2; //�����֣�Ҫʲô����
			ORDER[6]  = 0;    //ģ��ߵ�ַ
			ORDER[7]  = 0;    //ģ���е�ַ
			ORDER[8]  = AddrL*16 + PhaseBit* 4 + StatusH;    //�ϳ��ֽ�,ǰ1-4��Ϊפ��ʱ��,5-6Ϊ��λ���(01 A 10 B 11 C),7-8λ��פ��ʱ����
			ORDER[9]  = StatusL;//פ��ʱ��
		}

					
	}			

	ORDER[10] = ORDER[5] + ORDER[6] + ORDER[7] + ORDER[8] + ORDER[9];//����� ORDER[5]��ORDER[9]֮��

	//��ʱ����
	ORDER[11] = 0;
	ORDER[12] = 0;
	ORDER[13] = 0;
	
	//��Ƭ��������
	if(PcSendToSCM(ORDER,m_Potocol/*����Э��*/,0))
	{
		
		switch(times)
		{
		case 0:
			{
				StrSql.Format("��%d��ĸ�ߣ�פ��A��ɹ���ʱ��%s,Э��[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
		case 1:
			{
				StrSql.Format("��%d��ĸ�ߣ�פ��B��ɹ���פ��ʱ��%s,Э��[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
		case 2:
			{
				StrSql.Format("��%d��ĸ�ߣ�פ��C��ɹ���פ��ʱ��%s,Э��[%d]",generatrix + 1,NewTime,m_Potocol);
				status(StrSql);
				break;
			}
			
		}
		
	}
	
    //ɾ��פ��ʱ��
	StrSql = "DELETE FROM TB_HALTTIME";
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
	
	//����פ��ʱ��
	StrSql.Format("INSERT INTO TB_HALTTIME(HALTTIME_TIME) VALUES ('%s')",NewTime);
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

	m_StartRead = FALSE;

}

void CIFRMView::WriteListHeading()
{
	//ɾ�����е�����
	m_Grid.DeleteAllItems();
    m_Grid.ShowWindow(SW_SHOW);		
	
	//�Ƿ���ʾ��ʷ����
	m_IsHistory     =    FALSE;

	TRY { 
		m_Grid.SetFixedRowCount(1);
	    m_Grid.SetRowCount(1);     //��
    	m_Grid.SetColumnCount(13); //��
    	//������ݺ��к�
	    CStringArray m_StrArrays;
		short         m_wide[13];
		m_StrArrays.SetSize(13);
        m_StrArrays[0]  = "���";
		m_wide[0]       =  36;
		m_StrArrays[1]  = "��������";
		m_wide[1]       =  75;
		m_StrArrays[2]  = "�û�����";
		m_wide[2]       =  75;
		m_StrArrays[3]  = "�û����";
		m_wide[3]       =  60;
		m_StrArrays[4]  = "��ַ";
        m_wide[4]       =  105;
		m_StrArrays[5]  = "ģ���";
		m_wide[5]       =  60;
		m_StrArrays[6]  = "����";
		m_wide[6]       =  60;
		m_StrArrays[7]  = "��·����";
		m_wide[7]       =  60;
		m_StrArrays[8]  = "��·����";
		m_wide[8]       =  86;
		m_StrArrays[9]  = "��̨����";
		m_wide[9]       =  90;
		m_StrArrays[10]  = "����";
		m_wide[10]       =  80;
		m_StrArrays[11] = "����ֵ";
		m_wide[11]       =  110;
		m_StrArrays[12] = "ʱ��";
	    m_wide[12]       =  115;
	    
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
		#ifndef _WIN32_WCE
		   dwTextStyle |= DT_END_ELLIPSIS;
		#endif

	   for (int col = 0; col < m_Grid.GetColumnCount(); col++)
	   { 
		   
		   GV_ITEM        Item;
		   Item.mask = GVIF_TEXT|GVIF_FORMAT;
		   Item.row      =   0;
		   Item.col      = col;
		   Item.nFormat = dwTextStyle;
		   Item.strText.Format("%s",(m_StrArrays[col]));
		   m_Grid.SetItem(&Item);
		   m_Grid.SetColumnWidth(col,m_wide[col]); 
		   
	   }
        
		//ֻ��״̬
		m_Grid.SetModified(FALSE,-1,-1);
		//����
		m_Grid.m_title  = "";

		m_Grid.SetBkColor(RGB(255,255,255));

		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	END_CATCH

	/******************************************************************
	**         �յ��ĸ�ʽ������:
	**         a��BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
	**         b��BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
	**         c��BEGINS;DATAS:2:����;�������;ENDS      ���ݴ��ͽ�����־
	*******************************************************************/
	SurrenderWindowMessage();//����window����Ȩ
   
	/*
	//������ӺõĻ�
	//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
	//Str             �����ַ�
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	if(SelectSendString(m_sendkind,"BEGINS;DATAS:0:" + m_ComeIntoDataName + ";���,36;��������,85;�û�����,95;�û����,60;��ַ,125;ģ���,60;����,80;��·����,60;ĸ��-��-��-Э��,96;��̨����,65;����,60;����ֵ,75;ʱ��,115;0;ENDS",TRUE,FALSE,FALSE))
	{
		SurrenderWindowMessage();//����window����Ȩ
		Sleep(500);
	}
    
	SurrenderWindowMessage();//����window����Ȩ
	*/
  
}




BOOL CIFRMView::StopRunning()
{
	//�������ֹͣ��ť
	if(m_StartRead == FALSE)
	{	
		ShowProgressCtrl(FALSE);
		status("��������;��ֹͣ��");//��ʾ:
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	
}

//��ʾ�б�����
void CIFRMView::AddlistItem(CString m_StrArray[], int n)
{
	//����һ������
   	m_Grid.InsertRow(_T(" "), -1);
	m_Grid.Invalidate();

	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	#ifndef _WIN32_WCE
	   dwTextStyle |= DT_END_ELLIPSIS;
	#endif

	for (int col = 0; col < n; col++)
	{ 
		
		GV_ITEM  Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     = m_Grid.GetRowCount() - 1;
		Item.col     = col;
		Item.nFormat = dwTextStyle;
		Item.strText.Format("%s",(m_StrArray[col]));
		m_Grid.SetItem(&Item);
	}
	
	m_Grid.SetModified(FALSE,-1,-1);
	m_Grid.Invalidate();
	
}

/****************************  ִ������   **********************************
**    COMMAND  ִ������
**    ��ʽΪ:

1�������Ҫ���վִ�з�פ��ʱ������, ���վ���㲥��Ϣ��������ģ��פ��ͬһʱ�̵�����,���й���ȵȡ�
��ʽ��BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  
����1---ĸ��
����2---���
����3---���͵�ʱ�䵥λ��(8�ı���)
����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������

2�������Ҫ���վִ�в��Զ����������,ֻ��ʵʱ����,�������������
��ʽ��BEGINS;���վ���;COMMAND:01:����1:����2;ENDS 
����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
����2---��ʽΪ��0��1��ɵ���λ����ʾ��:1111   
��һλ��ʾ �й���� 1 �� Ҫ���й���� 0 - �����й����
�ڶ�λ��ʾ �޹���� 1 �� Ҫ���޹���� 0 - �����޹����
����λ��ʾ     ���� 1 �� Ҫ������     0 - ��������
����λ��ʾ     ��ѹ 1 �� Ҫ����ѹ     0 - ������ѹ

3�������Ҫ���վִ����ʽ�����������,��ʽ����,���ݱ�������ʽ�������ݱ���,  
��ʽ��BEGINS;���վ���;COMMAND:02:����1:����2;ENDS 
����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
����2---��ʽΪ��0��1��ɵ���λ����ʾ��:1111   
��һλ��ʾ �й���� 1 �� Ҫ���й���� 0 - �����й����
�ڶ�λ��ʾ �޹���� 1 �� Ҫ���޹���� 0 - �����޹����
����λ��ʾ     ���� 1 �� Ҫ������     0 - ��������
����λ��ʾ     ��ѹ 1 �� Ҫ����ѹ     0 - ������ѹ

4�������Ҫ���վִ��פ���������������ص�פ�����ݴ����TB_GARRISON��
��ʽ��BEGINS;���վ���;COMMAND:03:����1:����2;ENDS 
����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���) 
����2---��ʽΪ��0��1��ɵ���λ����ʾ��:1111   
��һλ��ʾ �й���� 1 �� Ҫ���й���� 0 - �����й����
�ڶ�λ��ʾ �޹���� 1 �� Ҫ���޹���� 0 - �����޹����
����λ��ʾ     ���� 1 �� Ҫ������     0 - ��������
����λ��ʾ     ��ѹ 1 �� Ҫ����ѹ     0 - ������ѹ

5�������Ҫ���վִ��ͣ���������
��ʽ��BEGINS;���վ���;COMMAND:04:����1;ENDS
����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)  ��
  
6�������Ҫ���վִ���͵��������
��ʽ��BEGINS;���վ���;COMMAND:05:����1;ENDS
����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)      

7�������Ҫ���վִ�ж�ʱ��������
//��ʽ��BEGINS;���վ���;COMMAND:06:����1;����2;����3;����4;����5;����6;����7;����8;����9;ENDS 
//����1---פ��ʱ�� ��ʽ���㣺�֣����磺0��00��00 
//����2---��פ������,�ܹ������ٴ�
//����3---������೤ʱ�䷢һ��פ��ʱ������,�Ա�ÿһ��ģ�鶼�յ�
//����4---�����ñ�ѡ��   0 ÿ��һ��          N��һ�� N>=1 
//����5---���û���       0 ÿ��һ��          N��һ�� N>=1
//����6---��̨�ܱ�       0 ÿ��һ��          N��һ�� N>=1
//����7---��·�ܱ�       0 ÿ��һ��          N��һ�� N>=1
//����8---��վ�ܱ�       0 ÿ��һ��          N��һ�� N>=1
//����9---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
//��һλ��ʾ �й����    0 - �����й����    1 �� Ҫ���й����     
//�ڶ�λ��ʾ �й��������0 ��ֻ�������ۼ�ֵ  1 -  �������ۼ�ֵ�����й���ֵ
//����λ��ʾ �޹����    0 - �����޹����    1 �� Ҫ���޹����
//����λ��ʾ �޹��������0 ��ֻ�������ۼ�ֵ  1 -  �������ۼ�ֵ�����޹���ֵ
//����λ��ʾ ����        0 - ��������        1 �� Ҫ������      
//����λ��ʾ ��ѹ        0 - ������ѹ        1 �� Ҫ����ѹ
//�ֽ����

8����������ñ��վ�������ýǶȴ�С
��ʽ��BEGINS;COMMAND:07:����1:����2;ENDS   
����1---��һ�� 0��A 1��B 2��C��  
����2---�Ƕȴ�С

9������ֶ����վ�����Ƕȴ�С
BEGINS;COMMAND:08:����1:����2;ENDS 
����1---ĸ�߱��  
����2---��һ�� 0��A 1��B 2��C��   

12�����������վ������ָ��, ��:��д������Բ���,����������
��ʽ: BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
����1---����  ��" ����̨����"
����2---���  ��" ����̨�����ɹ�"
����3---������Χ,���ݷ�Χ
����4---������   ����ؼ���
����5---�Ƿ�ֻ���಻��   TRUE  ֻ��û�в��Գ����ģ��, FALSE ��֮ȫ����   
����6---����        ��ÿ��ģ��Ĵ���
����7---�Ƿ�ֻ��һ��,�ö����һ��ģ��ʱֻ����һ��   FALSE ÿ��������һ��,���������һ��ģ���кö��,��ģ��ֻҪ��һ���͹���,�ò���ÿ��������
����8---��Сֵ(Ҳ������ʱ����)
����9---���ֵ��(Ϊд����ʱ��)
����10--���        
********************************************************************/
void CIFRMView::CarryOutOrders(CString Str)
{

	CString             KeyStr;
	CString         Conditions;
	int    colum          =  0;
	
	int    k          =  Str.Find("COMMAND:");
	
	if(k != -1)
	{
		KeyStr  =   Str.Mid(8,2); 
		CString       TempStr[4];
		
		//��ʼ����������
		for(int j = 0; j < 15; j ++)
		{
			m_SetLabel[j] = FALSE;
		}
		
		//���ݹؼ����ж�����������
		switch(atoi(KeyStr))
		{
		case 0:  
			{
				
				//��פ������ 
			    //BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  ����1---ĸ��,����2---���,����3---���͵�ʱ�䵥λ��(8�ı���),����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������				//str.Format("BEGINS;COMMAND:00:%d:%d:%d:%s;ENDS",i,broadTime,Э��,s);
				Str = Str.Right(Str.GetLength() - 11);
				CString              strs[5];
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{

					//ĸ��
                    strs[0] = Str.Left(k);
                    Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					//���
					strs[1] = Str.Left(k);
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//���͵�ʱ�䵥λ��(8�ı���)
						strs[2] = Str.Left(k);	
						Str = Str.Right(Str.GetLength() - k -1);
						k    =  Str.Find(':');
						
						//���͵�Э��
                        strs[3] = Str.Left(k);
						
						//���͵�ʱ��(�ַ���ʽ)
						strs[4] = Str.Right(Str.GetLength() - k - 1);
						
						//�ش�ִ��������ȷ
						SendErrorMessage(2);
						
						SendOfficeBreadorder(atoi(strs[0]),atoi(strs[1]),atoi(strs[2]),atoi(strs[3]),strs[4]);
						
					}
					
				}
				break;
				
			}
		case 1:
			{
				
				//�����Ҫ���վִ�в��Զ����������,ֻ��ʵʱ����,�������������
				//BEGINS;���վ���;COMMAND:01:����1:����2:����3:����4:����5;ENDS  
				//����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}

					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
	                
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					SendContionStr = Conditions;
           			ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)0,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
				break;
				
			}
		case 2:
			{
				//�����Ҫ���վִ����ʽ�����������,ֻ��ʵʱ����,�������������
				//BEGINS;���վ���;COMMAND:02:����1:����2:����3:����4:����5;ENDS 
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					SendContionStr = Conditions;
              	    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)1,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
				break;
				
			}
		case 3:
			{
				//�����Ҫ���վִ��פ�������������,�����������
				//BEGINS;���վ���;COMMAND:03:����1:����2:����3:����4:����5;ENDS 
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				if(m_IsAutoSending)
				{
					SendContionStr = "BEGINS;MESSAGE:0: ��ʱפ���ڼ䲻��פ������;ENDS";
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}
					
					m_times   =  0;
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					SendContionStr = Conditions;
           		    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)2,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
				break;
				
			} 
		case 4:
			{   
				//�����Ҫ���վִ��ͣ���������
				//��ʽ��BEGINS;���վ���;COMMAND:04:����1:����2;ENDS
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---���������ļ�¼����
  
				Str = Str.Right(Str.GetLength() - 11);
				k    =  Str.Find(':');
				if(k !=  -1)
				{	
					
					
					//������߼�¼�ļ�¼���Ƿ�һ��
					if(atol(Str.Right(Str.GetLength() - k - 1)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Str.Left(k)))
					{
						//0 --- ���ݲ�һ��  1------����������� 
                        SendErrorMessage(0);
						return;
					}


					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","ͣ�����","ͣ��ɹ�",Str.Left(k), 0xf8,FALSE,5,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
                    SendErrorMessage(1);
					return;

				}
				break;
				
			}
		case 5:
			{   
				//�����Ҫ���վִ���͵��������
				//��ʽ��BEGINS;���վ���;COMMAND:05:����1;ENDS
				//����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---���������ļ�¼����
				
				Str = Str.Right(Str.GetLength() - 11);
				k    =  Str.Find(':');
				if(k !=  -1)
				{	
					
					
					//������߼�¼�ļ�¼���Ƿ�һ��
					if(atol(Str.Right(Str.GetLength() - k - 1)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Str.Left(k)))
					{
						//0 --- ���ݲ�һ��  1------����������� 
                        SendErrorMessage(0);
						return;
					}

					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					//SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","�͵����","�͵�ɹ�",Str.Left(k), 0xF7,FALSE,5,TRUE,1,1,1);
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","�͵����","�͵�ɹ�",Str.Left(k), 0xF6,FALSE,5,TRUE,1,1,1);
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
                    SendErrorMessage(1);
					return;

				}
				break;
				
			}
		case 6:
			{   
				//�����ӳٽǶȴ�С 
				//��ʽ��BEGINS;COMMAND:06:����1:����2:����3;ENDS
				//����1---ĸ�߱��  
				//����2---��һ�� 0��A 1��B 2��C��  
				//����3---�Ƕȴ�С
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0;
				BYTE m_Angle      = 0;
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					m_phase      = atoi(Str.Left(k));                      //��    ��
					m_Angle      = atoi(Str.Right(Str.GetLength() - k -1));//�Ƕȴ�С
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);
					
					//���ýǶ�
					//short phase  ��� 0 A�� 1 B�� 2 C��
					//int   angles �Ƕ�
					SetPhaseAngle(m_generatrix,m_phase,m_Angle,1);
					
				}
				break;
							
			}
		case 7:
			{   
				
				//���ô����Ƕȴ�С 
				//��ʽ��BEGINS;COMMAND:07:����1:����2:����3;ENDS
				//����1---ĸ�߱��  
				//����2---��һ�� 0��A 1��B 2��C��  
				//����3---�Ƕȴ�С
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0;
				BYTE m_Angle      = 0;
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
			
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					Str = Str.Right(Str.GetLength() - k -1);
					k    =  Str.Find(':');
					m_phase      = atoi(Str.Left(k));                      //��    ��
					m_Angle      = atoi(Str.Right(Str.GetLength() - k -1));//�Ƕȴ�С
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					//���ýǶ�
					//short phase  ��� 0 A�� 1 B�� 2 C��
					//int   angles �Ƕ�
					SetPhaseAngle(m_generatrix,m_phase,m_Angle,0);
					
				}
				break;
				
			}
		case 8:
			{   
				
				//�������Ƕȴ�С
				//BEGINS;COMMAND:08:����1:����2;ENDS 
				//����1---ĸ�߱��  
				//����2---��һ�� 0��A 1��B 2��C�� 
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0; 
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					//���
					m_phase      = atoi(Str.Right(Str.GetLength() - k -1));//�Ƕȴ�С

					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					//��ȡ�Ƕ�
					//short phase  ��� 0 A�� 1 B�� 2 C��
					ReadThreePhaseAngle(m_generatrix,m_phase,0);
				}
				break;
				
			}
		case 9:
			{  
		    	//���ӳٽǶȴ�С
				//BEGINS;COMMAND:08:����1:����2;ENDS 
				//����1---ĸ�߱��  
				//����2---��һ�� 0��A 1��B 2��C�� 
				BYTE m_generatrix = 0;
				BYTE m_phase      = 0; 
				Str = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				if(k != -1)
				{
					
					m_generatrix = atoi(Str.Left(k));
					//���
					m_phase      = atoi(Str.Right(Str.GetLength() - k -1));//�Ƕȴ�С

					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					//��ȡ�Ƕ�
					//short phase  ��� 0 A�� 1 B�� 2 C��
					ReadThreePhaseAngle(m_generatrix,m_phase,1);
				}
				break;
			}
		case 10:
			{   
				//�ش�ִ��������ȷ
				SendErrorMessage(2);

                ReadRemoteTime();				
				break;
			}
		case 11:
			{
				//Ҫ������   
				//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
				//                  ����1---����         ����2---���            ����3---������Χ
				//                  ����4---������       ����5---�Ƿ�ֻ���಻��  ����6---����        
				//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ����������ʱ��)   ����9--- ���ֵ 
				//                  ����10--���         ��д������Բ���,����������
				//                  ����11--��¼����
			    //CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals
				BOOL    OnlyReadNot;
				BOOL       OnlyOnce;
				long  m_records = 0;
				
				Str = Str.Right(Str.GetLength() - 11);
				CString  TempStr[11];
				
				int    colum     = 0;
				
				while(Str.Find(':') != -1)
				{
					
					k   =  Str.Find(':');
					
					if(k != -1)
					{
						
						if(colum < 10)
						{
							
							TempStr[colum] =  Str.Left(k);

						}
						
						Str  = Str.Right(Str.GetLength() - k - 1);
						
						SurrenderWindowMessage();//����window����Ȩ
						colum++;
						
					}
					
				}
				
				TempStr[10] = Str;
				
				//�������߼�¼�ĸ����Ƿ����
				if(atoi(TempStr[4]) == 1)
				{
					//ֻ�����಻����ģ��
					m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", TempStr[2] + " AND USER_PHASE=3");
				}
				else
				{
					//���е�ģ�鶼����
					m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", TempStr[2]);
				}

				if(m_records != atol(TempStr[10]))
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(0);
					return;
				}

				if(atoi(TempStr[4]) == 0)
				{   
					//��������0����OnlyReadNotΪFALSE
					OnlyReadNot = FALSE;
				}
				else
				{   
					//��������1����OnlyReadNotΪTRUE
					OnlyReadNot = TRUE;
				}
				
				if(atoi(TempStr[6]) == 0)
				{   
					//��������0����OnlyOnceΪFALSE
					OnlyOnce = FALSE;
				}
				else
				{   
					//��������1����OnlyOnceΪTRUE
					OnlyOnce = TRUE;
				}
				
				//�ش�ִ��������ȷ
				SendErrorMessage(2);

				SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d",TempStr[0],TempStr[1],TempStr[2],atoi(TempStr[3]),OnlyReadNot,atoi(TempStr[5]),OnlyOnce,atoi(TempStr[7]),atoi(TempStr[8]),atoi(TempStr[9]));
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				break;
				
			}
		case 12:
			{
				//ִ�����ϴ�����SQL���  
				//BEGINS;COMMAND:12:����1;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
				CDataBaseInstance::ExecuteDataBaseSQL(Str);
				
				//�ش�ִ��������ȷ
				SendErrorMessage(2);

				if(Str.Find("DELETE") != -1 && Str.Find("TB_HALTTIME") == -1)
				{
					//������Ϣ
					SendContionStr = "BEGINS;MESSAGE:0:Զ�̻���ɾ���������!;ENDS";
					SendMessage(WM_EVENT, 4, 0);
					
					m_StartRead    = FALSE;
				    
					status("��ɾ��������ϡ�");

					if(Str.Find("TB_USER") != -1)
					{
						//���ؼ�����ˢ��һ��
						RefreshTree();
					}

				}	
				break;
			} 
		case 13:
			{
				//Уʱ����  
				//BEGINS;COMMAND:13:��-��-��-ʱ-��-��;ENDS   
				Str = Str.Right(Str.GetLength() - 11);

				//�ش�ִ��������ȷ
				SendErrorMessage(2);

				//����ϵͳʱ��
				SetLocalTimes(Str);
				break;
			}
		case 14:
			{
				//Уʱ����  
				//BEGINS;COMMAND:15:��-��-��-ʱ-��-��;ENDS   
				CString  TimeStr;
				CTime time = CTime::GetCurrentTime();
				TimeStr.Format("BEGINS;COMMAND:15:%d-%d-%d-%d-%d-%d;ENDS",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				
				//�ش�ִ��������ȷ
				SendErrorMessage(2);

				SetRemoteTime(TimeStr);
				break;
			}  
		case 15:
			{
				//Уʱ����  
				//BEGINS;COMMAND:15:��-��-��-ʱ-��-��;ENDS  
				m_TimeStrs = Str.Right(Str.GetLength() - 11);

				//�ش�ִ��������ȷ
				SendErrorMessage(2);

				break;
			}
		case 16:
			{
				//ֻ��û�ж�������ģ���פ������
				//BEGINS;���վ���;COMMAND:16:����1:����2:����3:����4:����5;ENDS 
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				if(m_IsAutoSending)
				{
					SendContionStr = "BEGINS;MESSAGE:0: ��ʱפ���ڼ䲻��פ������;ENDS";
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					SendContionStr = Conditions;
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

                    //ֻ��û�ж�������ģ���פ������
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)8,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
				break;
			}
		case 17:
			{
				//ֻ��û�ж�������ģ�����ʽ��������
                //BEGINS;���վ���;COMMAND:17:����1:����2:����3:����4:����5;ENDS 
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}
					
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					SendContionStr = Conditions;

                    //ֻ��û�ж�������ģ�����ʽ��������
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)9,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
				break;
			}
		case 18:
			{
				//ֻ��û�ж�������ģ��Ĳ��Զ�������
                //BEGINS;���վ���;COMMAND:18:����1:����2:����3:����4:����5;ENDS 
                //����1---�û����ݷ�Χ(�û����ݷ�Χ�������ַ���)
				//����2---��¼����
				//����3---ѭ������
				//����4---ʱ����
				//����5---��ʽΪ��0��1��ɵ���λ����ʾ��:111111   
				//��һλ��ʾ �ۻ��й����     1 �� Ҫ���ۻ��й����     0 - �����ۻ��й����
				//�ڶ�λ��ʾ ���������й���� 1 �� Ҫ�����������й���� 0 - �������������й����
				//����λ��ʾ �ۻ��޹����     1 �� Ҫ���ۻ��޹����     0 - �����ۻ��޹����
				//����λ��ʾ ���������޹���� 1 �� Ҫ�����������޹���� 0 - �������������޹����
				//����λ��ʾ ����             1 �� Ҫ������             0 - ��������
				//����λ��ʾ ��ѹ             1 �� Ҫ����ѹ             0 - ������ѹ
				Str         = Str.Right(Str.GetLength() - 11);
				int    k    =  Str.Find(':');
				
				if(k != -1)
				{
					Conditions = Str.Left(k);
					Str  = Str.Right(Str.GetLength() - k - 1);

					k    =  Str.Find(':');
					
					if(k != -1)
					{
						//������߼�¼�ļ�¼���Ƿ�һ��
						if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", Conditions))
						{
							//0 --- ���ݲ�һ��  1------����������� 
							SendErrorMessage(0);
							return;
						}		
						
						Str  =  Str.Right(Str.GetLength() - k - 1);
						k    =  Str.Find(':');
						
						if(k != -1)
						{  
							m_Recycles       =     atol(Str.Left(k));//��֮��ʱ����,Ĭ����30����
							
							Str  =  Str.Right(Str.GetLength() - k - 1);
							k    =  Str.Find(':');
							
							if(k != -1)
							{  
								m_SetRecycleTime =  atol(Str.Left(k));
								Str  =  Str.Right(Str.GetLength() - k - 1);
							}
							
						}

					}
					else
					{
					
						//0 --- ���ݲ�һ��  1------����������� 
						SendErrorMessage(1);
						return;
					}
				
					
					//�ۻ��й����
					if(atoi(Str.Left(1)) == 1)
					{
						m_SetLabel[0] = TRUE;
					}
					
					//���������й����
					if(atoi(Str.Mid(1,1)) == 1)
					{
						m_SetLabel[1] = TRUE;
					}
					
					//�ۻ��޹����
					if(atoi(Str.Mid(2,1)) == 1)
					{
						m_SetLabel[2] = TRUE;
					}
					
					//���������޹����
					if(atoi(Str.Mid(3,1)) == 1)
					{
						m_SetLabel[3] = TRUE;
					}
					
					//����
					if(atoi(Str.Mid(4,1)) == 1)
					{
						m_SetLabel[4] = TRUE;
						m_SetLabel[5] = TRUE;
						m_SetLabel[6] = TRUE;
					}
					
					//��ѹ
					if(atoi(Str.Mid(5,1)) == 1)
					{
						m_SetLabel[7] = TRUE;
						m_SetLabel[8] = TRUE;
						m_SetLabel[9] = TRUE;
					}
					
					//������
					if(atoi(Str.Mid(6,1)) == 1)
					{
						m_SetLabel[10] = TRUE;
					}

	                //�����
					if(atoi(Str.Mid(7,1)) == 1)
					{
						m_SetLabel[11] = TRUE;
					} 
					
					//ƽ����
					if(atoi(Str.Mid(8,1)) == 1)
					{
						m_SetLabel[12] = TRUE;
					}
					
					//�ȵ���
					if(atoi(Str.Mid(9,1)) == 1)
					{
						m_SetLabel[13] = TRUE;
					}	
					
					//��������
					if(atoi(Str.Mid(10,1)) == 1)
					{
						m_SetLabel[14] = TRUE;
					}

					m_times   =  0;
					
					//�ش�ִ��������ȷ
					SendErrorMessage(2);

					SendContionStr = Conditions;
                    //ֻ��û�ж�������ģ��Ĳ��Զ�������
				    ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)10,m_Thread_PRIORITY,0,0,NULL); // ����������
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				else
				{
					//0 --- ���ݲ�һ��  1------����������� 
					SendErrorMessage(1);
					return;
				}
       			break;
			}
		case 19:
			{
				//ִ�����ϴ�����SQL���,��������Ϣ  
				//BEGINS;COMMAND:19:����1;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
				CDataBaseInstance::ExecuteDataBaseSQL(Str);
				break;
			} 
         case 20:
			 {
			   //Զ�����������ֵ�����Ϣ	
				CDatabase                     dbs;
				int    colum     =              0;
			 	CString  TempStr[5],SqlStr,StrSql;
    			//�����ŵ�������
				Str = Str.Right(Str.GetLength() - 11);	
				
				while(Str.Find(':') != -1)
				{
					
					k   =  Str.Find(':');
					
					if(k != -1)
					{
						
						if(colum < 2)
						{
							TempStr[colum] =  Str.Left(k);
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//����window����Ȩ
						    colum++;
						}
						else
						{
                            break;

						}
				

					}
					
				}
				
				TempStr[2] = Str;
		
				if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
				{	
					//������վ����
					m_handno        =  atoi(TempStr[0]);
					//�Ƿ��͵����ź�
					m_status        =  atoi(TempStr[2]);

	    			StrSql = "DELETE FROM TB_HAND";
					dbs.ExecuteSQL(StrSql);
					StrSql.Format("INSERT INTO TB_HAND(HAND_NO,HAND_STATIONNAME,HAND_STATUS) VALUES (%d,'%s',%d)",m_handno,TempStr[1],m_status);
					dbs.ExecuteSQL(StrSql);
					dbs.Close();
									
					//���ö�ʱ��Ϣ
					SetTimersign();
					StrSql = "�����ֹ��������ϢԶ�����óɹ���";
					status(StrSql);
                    //���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
					SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StrSql);
					//��������
					SendMessage(WM_EVENT, 5, 0);
				
				}
		    	 break;
			 }
		 case 21:
			 {
   
			    break;
			 }
		 case 22:
			 {
				//ִ��ģ��ŵ�Զ���޸�  
				//BEGINS;COMMAND:22:ԭģ���;ԭ���;��ģ���;�����;ENDS   
				Str = Str.Right(Str.GetLength() - 11);
                CString    TempStr[4];
				BYTE    colum    =  0;
			    
				while(Str.Find(';') != -1)
				{
					k   =  Str.Find(';');
					if(k != -1)
					{
						if(colum < 3)
						{
							TempStr[colum] =  Str.Left(k);
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//����window����Ȩ
						    colum++;
						}
						else
						{
                            break;
						}

					}

				}
 				
				TempStr[3] = Str;

				//�õ��ɼ�¼����
				Str.Format("USER_MODULENO=%s",TempStr[0]);
				long  oldfields =  CDataBaseInstance::GetAllRecordsCount("TB_USER", Str);
			    
				//�õ��¼�¼����
				Str.Format("USER_MODULENO=%s",TempStr[2]);
				long  newfields =  CDataBaseInstance::GetAllRecordsCount("TB_USER", Str);

				if(oldfields < 1 || (newfields > 0 && TempStr[0] != TempStr[2]))
				{ 
				                   
					if(oldfields < 1)
					{
						Str.Format("���վ������Ҫ�޸ĵ�ģ���%s��Զ���޸�ʧ�ܣ�",TempStr[0]);
						//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
						SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS",Str);
						status(Str);
					}
					else
					{
                        Str.Format("���վ�Ѿ�����Ҫ�޸ĺ��ģ���%s��Զ���޸�ʧ�ܣ�",TempStr[2]);
						//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
						SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS",Str);
						status(Str);
					}

				}
				else
				{
	                Str.Format("UPDATE TB_USER SET USER_MODULENO=%s,USER_PHASE=%d WHERE USER_MODULENO=%s",TempStr[2],atoi(TempStr[3]),TempStr[0]);
                 	CDataBaseInstance::ExecuteDataBaseSQL(Str);
					Str.Format("Զ��ģ���%s�ɹ��޸ĳ�%s��",TempStr[0],TempStr[2]);
					status(Str);
					//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
					SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",Str);
				}
				//��������
				SendMessage(WM_EVENT, 5, 0);
     			break;
			 }
		 case 23:
			 {	
				 //�õ�DIALOGBAR�ϵı���,��ʼ�����ؼ�	
				 CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
				 ASSERT_VALID(pMainFrm);	
				 //��ʼ�����ؼ�
				 pMainFrm->m_wndMyDialogBar.Treeinitialize();
				 break;
			 }	
		 case 24:
			 {	
				 //�õ�Զ�̻����ϵļ�¼����	
				 //��ʽ��BEGINS;COMMAND:24:���ݱ���:��¼����;ENDS
				 Str     = Str.Right(Str.GetLength() - 11);
				 int k   =  Str.Find(':');
				 CString       m_fileName;

				 if(k != -1)
				 {
					 //ֹͣ��������
	                 m_StopPassing      = FALSE;

					 m_PassDataFileName =  Str.Left(k);//���ݱ���
					 m_PassDataRecords  = atoi(Str.Right(Str.GetLength() - k - 1));//��¼����
                     
					 if(m_PassDataRecords > 0)
					 {
						 Str.Format("����Զ�̱�" + m_PassDataFileName + "�����ݣ���¼��%d��,���Ժ�...",m_PassDataRecords);
						 //��ʼ��������
						 status(Str);

						 ShowProgressCtrl(TRUE);
						 SetProgressCtrlRange(0,m_PassDataRecords,1);
						 m_CurrentPassPostions =  1;
				         m_fileName.Format("%s%s%s",GetFolder(),m_PassDataFileName,".TXT");
                         
						 CFileFind    finder;
						 if(finder.FindFile(m_fileName) != 0) 
						 { 
							//���ڴ��ļ��Ļ���ɾ�����ļ�
							::DeleteFile(m_fileName);
						 }

						 //���ʱ��ȡ��
						 SetTimer(3,1000,NULL);
					 }

				 }
				 break;
			 }
		 case 25:
			 {
				 //��ʽ��BEGINS;COMMAND:25:���ݱ���:Ҫ�ļ�¼��λ��;ENDS
				 CString   m_fileName;
				 int      m_positions;

				 Str = Str.Right(Str.GetLength() - 11);
				 int k   =  Str.Find(':');
				 
				 if(k != -1)
				 {
				     m_fileName          = Str.Left(k);                             //���ݱ���
					 m_positions         = atoi(Str.Right(Str.GetLength() - k - 1));//Ҫ�ļ�¼λ��

					 m_fileName          = GetFolder() + m_fileName + ".TXT";
					 CString   m_InfoStr = GetDataLineCString(m_fileName,m_positions);
		
					 //���ı��ļ���ȡ��
					 if(m_InfoStr.IsEmpty())
					 {	
						 //��ʽ��BEGINS;COMMAND:26:������Ϣ;ENDS
			             SendContionStr.Format("BEGINS;COMMAND:26:%s;ENDS","NOFINDDATA?OK!");
					 }
					 else
					 {	
						 //��ʽ��BEGINS;COMMAND:26:������Ϣ;ENDS
			             SendContionStr.Format("BEGINS;COMMAND:26:%s;ENDS",m_InfoStr);
					 } 

					 //��������
			         SendMessage(WM_EVENT, 5, 0); 
					 
					 //����ǰκŵĻ�
				//	 if(m_sendkind == 1)
				//	 {
				//		 Sleep(500);
				//	 }
					
					 Str.Format("���ͱ�%s��%d����¼���...",Str.Left(k),m_positions);
					 status(Str);
					 
				 }
         		 break;
			 }
	   case 26:
		   {    
				 //��ʽ��BEGINS;COMMAND:26:������Ϣ;ENDS
				 Str = Str.Right(Str.GetLength() - 11);
				 
				 //����Ĵ�����Ϊ0
	             m_GetErrors    =   0;

				 if(Str.Find("NOFINDDATA?OK!") != -1)
				 {	

					 m_StartRead = FALSE;
					 status("                            ");
					 ShowProgressCtrl(FALSE);//û������
					 KillTimer(3);

				 }
				 else
				 {	 
					
					 CString             m_fileName;
					 m_fileName.Format("%s%s%s",GetFolder(),m_PassDataFileName,".TXT");
					
				     //�ƶ�������
					 SetProgressCtrlSetIt();	
						 
					 //д���ı��ļ�
					 FILE *text;
					 if((text = fopen(m_fileName,"a")) != NULL)
					 {
						 fputs(Str + "\r\n",text);
						 fclose(text);
					 }
						 
					 //��ʾ״̬����Ϣ
					 Str.Format("����Զ�̱�" + m_PassDataFileName + "���ݣ�%d��%d��,���Ժ�...",m_CurrentPassPostions,m_PassDataRecords);
					 status(Str);
					 
					 m_CurrentPassPostions ++;
					 KillTimer(3);
					 OnTimer(3);
													
					 //����������˵Ļ�
					 if(m_CurrentPassPostions > m_PassDataRecords)
					 { 	
						 //ֹͣ��������
	                     m_StopPassing = FALSE;
						 KillTimer(3);	
					    
						 status("             ");
						 ShowProgressCtrl(FALSE);
						 
						 SurrenderWindowMessage();

						 m_StartRead  =  FALSE; 
						 
						 if(!AppInfo::Instance().m_WhichKind)
						 {
							 
							 if(MessageBox("��ʾԶ�̽�����������������","ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
							 {
								 //��ʾ������������
								 AppearAccept(m_PassDataFileName);
							 }

						 }
                        
						 //ѯ���Ƿ�Ҫ�ؼ�������
						 AskIfAddData(m_PassDataFileName,m_fileName);
                        
					 }
					 else
					 {

						 if(!m_StopPassing)
						 {
							 //���ʱ��ȡ��
							 SetTimer(3,1000,NULL);
						 }
						 else
						 {
							 status("�����������ѱ���ֹ��");
						 }

					 }

				 }
         		 break;
			 }
	   case 27:
		   {
			   //Զ�̲�ѯ�Է���פ������
			   if(!m_IsAutoSending)
			   {
				   SendContionStr = "BEGINS;MESSAGE:0:�Է�������û�����ö�ʱ��פ������!;ENDS";
			   }
			   else
			   {  
				   SendContionStr.Format("BEGINS;MESSAGE:0:�Է�������ʱ��פ����������%s��;ENDS",m_DingShiString);
			   }
			   
			   //������Ϣ
			   SendMessage(WM_EVENT, 4, 0);
               break;
		   }
	   case 28:
		   {
			   //����Զ�̻��Ͽ� 
			   //��ʽ��BEGINS;COMMAND:28:������Ϣ;ENDS			 
			   Str = Str.Right(Str.GetLength() - 11);
			   Str.TrimLeft();
			   Str.TrimRight();
			   
			   //�Ͽ��ˣ��������ݱ�־��ΪFALSE
			   if(ReadMeterThread == NULL)
			   {
				   m_IfChangeData = FALSE;
			   }
			   
			   switch(m_sendkind)
			   {
			   case 0:
				   {
					   
					   break;
				   }
			   case 1:
				   {
					   //�ر�è
					   if(Str.Find("^CLOSED^MODEM?^OK!") != -1)
					   {
						   
						   m_IsDialConnectting =       FALSE;
											   
						   if(AppInfo::Instance().m_WhichKind)//  -TRUE   ���վ�汾 -FALSE  ��ְ�
						   {
							   
							   SelectSendString(m_sendkind,"+++",FALSE,FALSE,FALSE);     //�����յ���������+++, ֮��3������û���κ�����, Modem�ͽ�������ģʽ, ��������AT�����������
							   Sleep(3200);
							   SelectSendString(m_sendkind,"ATH0\r\n",FALSE,FALSE,FALSE);//�Ͽ��绰����
							   Sleep(500);	
							   SelectSendString(m_sendkind,"ATZ\r\n",FALSE,FALSE,FALSE);//Z0 MODEM��λ��Reset�������¶�ȡԤ���0����趨����ֵ��
							   Sleep(500);
							   
							   AutoAnswer(FALSE);	//ADD 20041221�Զ�Ӧ��
							   
						   }
						   
						   status("���κ������ѶϿ���");
						   ReceiveByteArray.RemoveAll();
						   m_Com.GetInput();
					   }
					   break;
				   }
			   case 2:
				   {
			
					   if(Str.Find("^CLOSED^INTERNET?^OK!")!= -1)
					   {	
						   m_IsConnect   =    FALSE;
						   SendContionStr = "BEGINS;MESSAGE:0:�Է�����TCP��IP���������Ѿ��Ͽ���;ENDS";
						   SendMessage(WM_EVENT, 4, 0);
						   Sleep(100);
						   OnCloseWinsock();
					   }
					   break;
				   }  
				   
				   //��������
				   OperationAnimation(FALSE);
				   StatusStr           =          "";
				   //����ͳ�ɳ��ͨѶ
				   Received            =           0;	
				   SurrenderWindowMessage();
			   }
			   
			   break;
	  
		   }
	   case 29:
		   {
  			    //��һ����ʱ����פ����
				if(m_IsAutoSending)
				{
					//��ʾ״̬����Ϣ
					SendContionStr.Format("BEGINS;MESSAGE:0: Զ��פ��ԭ���趨��\r\n����ȡ������������פ����;ENDS");
					SendMessage(WM_EVENT,4,0);
					Sleep(200);
					return;
				}

				//�ֽ����
                int    colum  =      0;
			 	CString  SqlStr,StrSql,str;
    			//�����ŵ�������
				Str = Str.Right(Str.GetLength() - 11);	
						
				while(Str.Find(';') != -1)
				{
					
					k   =  Str.Find(';');
					
					if(k != -1)
					{
						
						if(colum < 109)
						{
							m_parameter[colum] =  atoi(Str.Left(k));
							Str  = Str.Right(Str.GetLength() - k - 1);
							SurrenderWindowMessage();//����window����Ȩ
						    colum++;
						}
						else
						{
                            break;

						}
				

					}
					
				}
				
				m_parameter[109]  = atoi(Str);

				//д���������û�����̨��ȱ�Ĳ���
				WriteToAllAmeterParameter();

				//14�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ
			    //��ʱ��פ��,��ʱ�����־
				for(int i = 0; i < 15; i++)
				{
					m_TimeSetLabel[i]  = FALSE;  
				}
	
				//�й����
				if(m_parameter[93] > 0)
				{
					if(m_parameter[93] > 0  && m_parameter[94] > 0)
					{
						m_TimeSetLabel[0] = TRUE;
						m_TimeSetLabel[1] = TRUE;    //0���й����-�����ۼ�ֵ
					}
					else
					{
						m_TimeSetLabel[0] = TRUE;
					}
				}	
	
				//�޹����
				if(m_parameter[95] > 0)
				{
					if(m_parameter[95] > 0  && m_parameter[96] > 0)
					{
						m_TimeSetLabel[2] = TRUE;
						m_TimeSetLabel[3] = TRUE;    //0���޹����-�����ۼ�ֵ
					}
					else
					{
						m_TimeSetLabel[2] = TRUE;   
					}
				}	
					
				//4��A����� 5��B����� 6��C�����
				if(m_parameter[97] > 0)
				{
					m_TimeSetLabel[4] = TRUE;
					m_TimeSetLabel[5] = TRUE;
					m_TimeSetLabel[6] = TRUE;
				}

				//7��A���ѹ 8��B���ѹ 9��C���ѹ
				if(m_parameter[98] > 0)
				{
					m_TimeSetLabel[7] = TRUE;
					m_TimeSetLabel[8] = TRUE;
					m_TimeSetLabel[9] = TRUE;
				}

				//������
				if(m_parameter[99] > 0)
				{
					m_TimeSetLabel[10] = TRUE;
				}
				
				//�����
				if(m_parameter[100] > 0)
				{
					m_TimeSetLabel[11] = TRUE;
				}
				
				//ƽ����
				if(m_parameter[101] > 0)
				{
					m_TimeSetLabel[12] = TRUE;
				}
				
				//�ȵ���
				if(m_parameter[102] > 0)
				{
					m_TimeSetLabel[13] = TRUE;
				}
				
				//��������	
				if(m_parameter[103] > 0)
				{
					m_TimeSetLabel[14] = TRUE;
				}
					
				//Ȼ�������Զ���פ���Զ�������
				//�к���ʼΪ0
				m_ListRows      =      0;
				//����Ϊ0
				m_times         =      1;
				//�Զ�����Ϣ 
				m_IsAutoSending =   TRUE;	
				//��ʾ��Ϣ
				SendContionStr.Format("BEGINS;MESSAGE:0:Զ���Զ���פ���Զ����������óɹ�!\r\n%s;ENDS",m_statusstr);
				//���ͷ�����Ϣ
				SendMessage(WM_EVENT, 4, 0);
				//ִֹͣ�д˲���
				m_StartRead     = FALSE;  
				
				//�õ�����Э�������
	            SendMessage(WM_EVENT, 10, 0);

    			//ʱ��
				CTime timet = CTime::GetCurrentTime();
				str.Format("��%4d-%02d-%02d %02d:%02d:%02d�����ö�ʱפ������:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
			   	WriteToLog(str);

				//ȡ��10���Ӽ��һ�μ��
				KillTimer(1);
				ShowDingShiButton(TRUE);                   //��ʱ��ť��ΪTRUE	
	            
				m_ReadModuleTimes = 0;//���������Ϊ0	
				//��פ������
	            m_SendGarrisonTimes=     0;
				m_parameter[105]  =     30;//���ǿ�����ó�30����
                str.Format("����%dʱפ��,���%d����,����%d��,�Ժ�%dʱ����%d�졿",m_parameter[104],m_parameter[105],m_parameter[106],m_parameter[107],m_parameter[108]);
			    status(str);
				
				//Ϊ22Э��ӵģ���������ſ���,10���Ӽ��һ��
				//10���Ӽ��һ��
				m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
				
				SetTimer(1,m_SettimerValues,NULL);//���ö�ʱ��,10���Ӽ��һ��
				break;
								
			}
	   case 30:
		   {
			   //Զ�̲�ѯ�Է���פ������
			   if(!m_IsAutoSending)
			   {
				   SendContionStr = "BEGINS;MESSAGE:0:�Է�������û�����ö�ʱ��פ������!;ENDS";
				   //������Ϣ
				   SendMessage(WM_EVENT, 4, 0);
			   }
			   else
			   {
				   
				   CString ConStr,str;
				   ConStr  = "BEGINS;COMMAND:31:";
				   
				   for(int i = 0; i < 110; i ++)
				   {	
					   //��ʼ����פ�������õ�110������
					   str.Format("%d",m_parameter[i]);
					   ConStr = ConStr + str + ";";
				   }
				   
				   //��������
				   ConStr = ConStr + "ENDS";
				   SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE); 
			   }
			   break;
		   } 
	   case 31:
		   {
			   //�ֽ����
			   int    colum  =      0;
			   CString  SqlStr,StrSql,str;
			   //�����ŵ�������
			   Str = Str.Right(Str.GetLength() - 11);	
			   
			   while(Str.Find(';') != -1)
			   {
				   
				   k   =  Str.Find(';');
				   
				   if(k != -1)
				   {
					   
					   if(colum < 109)
					   {
						   m_parameter[colum] =  atoi(Str.Left(k));
						   Str  = Str.Right(Str.GetLength() - k - 1);
						   SurrenderWindowMessage();//����window����Ȩ
						   colum++;
					   }
					   else
					   {
						   break;
						   
					   }
					   
					   
				   }
				   
			   }
			   
			   m_parameter[109] = atoi(Str);
			   
			   //д���������û�����̨��ȱ�Ĳ���
			   WriteToAllAmeterParameter(); 
			   m_zhuliukinds       =     0;//0 �����������פ�� 1 ��������פ��

			   if(!AppInfo::Instance().m_WhichKind)
			   {
					MessageBox(DecodeParameter(TRUE),"�Է���ʱ���������������:");
			   }
			   break;
		   }
	   case 32:
		   { 
			   //�����ŵ�������
			   Str = Str.Right(Str.GetLength() - 11);
			   MessageBox(Str," ",MB_OK|MB_ICONWARNING);
			   //�Ͽ��κ�����
			   DisConnect(1);  
			   break;
		   } 
	   case 33:
		   { 
			   //����פ��ʱ��,�����ŵ�������
			   Str = Str.Right(Str.GetLength() - 11);
			   m_saveyears = atoi(Str);
			   SendContionStr.Format("BEGINS;MESSAGE:0:�Է������������ݱ���ʱ��Ϊ%d��!;ENDS",m_saveyears);
			   SendMessage(WM_EVENT, 4, 0);
			   break;
		   } 
	   case 34:
		   { 
			   //��ѯפ��ʱ��
			   SendContionStr.Format("BEGINS;MESSAGE:0:�Է������������ݱ���ʱ��Ϊ%d��!;ENDS",m_saveyears);
			   SendMessage(WM_EVENT, 4, 0);
			   break;
		   }
	   case 35:
		   {
			   //ִ�����ϴ�����SQL���  
			   //BEGINS;COMMAND:35:����1;ENDS   
			   Str = Str.Right(Str.GetLength() - 11);
               Str = "UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE " + Str;
			   CDataBaseInstance::ExecuteDataBaseSQL(Str);
			   SendContionStr = "BEGINS;MESSAGE:0:Զ�̻��������ɹ���;ENDS";
			   SendMessage(WM_EVENT, 4, 0);
			   m_StartRead    = FALSE;
			   status("�������ɹ���");
			   break;
		   }
       case 36:
		   {
			   //ִ�����ϴ�����SQL���  
			   //BEGINS;COMMAND:36:����1;ENDS   
			   Str = Str.Right(Str.GetLength() - 11);
               Str = "UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE " + Str;
			   CDataBaseInstance::ExecuteDataBaseSQL(Str);
			   SendContionStr =  "BEGINS;MESSAGE:0:Զ�̻���ȡ�������ɹ���;ENDS";
			   SendMessage(WM_EVENT, 4, 0);
			   m_StartRead    =  FALSE;
			   status("��ȡ�������ɹ���");
			   break;
		   }  
	   case 37:
		   {
			   //ִ�ж�̬���������Ƿ���Զ�פ����ͻ
			   BOOL m_CanReading  =        TRUE;
			   BYTE        m_day  =           0;
			   
			   Str         = Str.Right(Str.GetLength() - 11);
			   int    k    =  Str.Find(':');
			   
			   if(k != -1)
			   {	
				  
				   //��Χ
				   m_DynaicCheckStrCondition = Str.Left(k); 
				
				   Str  = Str.Right(Str.GetLength() - k - 1);
     			   
				   //��¼����
				   k    =  Str.Find(':');
				   
				   if(k != -1)
				   {
					   //������߼�¼�ļ�¼���Ƿ�һ��
					   if(atol(Str.Left(k)) != CDataBaseInstance::GetAllRecordsCount("TB_USER", m_DynaicCheckStrCondition))
					   {
						   //0 --- ���ݲ�һ��  1------����������� 
						   SendErrorMessage(0);
						   return;
					   }		
					   
					   Str  =  Str.Right(Str.GetLength() - k - 1);
					   k    =  Str.Find(':');
					   
					   if(k != -1)
					   {
                           //����ʱ���
						   m_shikedian = atoi(Str.Left(k));
						   
						   Str  =  Str.Right(Str.GetLength() - k - 1);
						   k    =  Str.Find(':');
						   
						   if(k != -1)
						   {
							   //���೤ʱ��
							   m_readRangle = atoi(Str.Left(k));

							    Str  =  Str.Right(Str.GetLength() - k - 1);
						        k    =  Str.Find(':');

								if(k != -1)
								{
									//�������
									m_readchecktimes   =  atoi(Str.Left(k));
									Str                =  Str.Right(Str.GetLength() - k - 1);
                                    
									//�ۻ��й����
									if(atoi(Str.Left(1)) == 1)
									{
										m_SetLabel[0] = TRUE;
									}
									
									//���������й����
									if(atoi(Str.Mid(1,1)) == 1)
									{
										m_SetLabel[1] = TRUE;
									}
									
									//�ۻ��޹����
									if(atoi(Str.Mid(2,1)) == 1)
									{
										m_SetLabel[2] = TRUE;
									}
									
									//���������޹����
									if(atoi(Str.Mid(3,1)) == 1)
									{
										m_SetLabel[3] = TRUE;
									}
									
									//����
									if(atoi(Str.Mid(4,1)) == 1)
									{
										m_SetLabel[4] = TRUE;
										m_SetLabel[5] = TRUE;
										m_SetLabel[6] = TRUE;
									}
									
									//��ѹ
									if(atoi(Str.Mid(5,1)) == 1)
									{
										m_SetLabel[7] = TRUE;
										m_SetLabel[8] = TRUE;
										m_SetLabel[9] = TRUE;
									}
									
									//������
									if(atoi(Str.Mid(6,1)) == 1)
									{
										m_SetLabel[10] = TRUE;
									}
									
									//�����
									if(atoi(Str.Mid(7,1)) == 1)
									{
										m_SetLabel[11] = TRUE;
									} 
									
									//ƽ����
									if(atoi(Str.Mid(8,1)) == 1)
									{
										m_SetLabel[12] = TRUE;
									}
									
									//�ȵ���
									if(atoi(Str.Mid(9,1)) == 1)
									{
										m_SetLabel[13] = TRUE;
									}
									
									//��������
									if(atoi(Str.Mid(10,1)) == 1)
									{
										m_SetLabel[14] = TRUE;
									}
									
									m_CheckReading     =        TRUE;//���Ӷ���
								}

						   }
						   
					   }


				   }

			   }

			   if(!m_CheckReading)
			   {
				   SendContionStr =  "BEGINS;MESSAGE:0:Զ�̻�������ָ�����;ENDS";
				   SendMessage(WM_EVENT, 4, 0);
				   return;
			   }
			 

			   //�����פ���ڼ�
			   if(m_IsAutoSending)
			   {					
				   
				   CByteArray          m_TimeArray;//������������
				   
				   for(int i = 0; i < 31; i ++)
				   {
					   
					   //�����������
					   if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
					   {
						   m_TimeArray.Add(i+1);
					   }
					   
				   }
				   
				   //���û�ж����������˳�
				   if(m_TimeArray.GetSize() > 0)
				   {	
					   //������ʱ��	
					   long m_seconds = (m_readRangle * m_readchecktimes)*3600;//���೤ʱ��
					   CTimeSpan                                ts;//ʱ���϶//ʱ��
					   ts                   =            m_seconds;
					   CTime           timet = CTime::GetCurrentTime();
					   CTime            m_CurrentTime2 = timet + ts;//����ʱ�����
					   BYTE        m_day1 = timet.GetDay();
					   BYTE        m_day2 = m_CurrentTime2.GetDay();
					   
					   if(m_day2 >= m_day1)
					   {
						   
						   for(int i = 0;i < m_TimeArray.GetSize();i ++)
						   {
							   
							   if(m_TimeArray[i] >= m_day1 && m_TimeArray[i] <= m_day2)
							   {
								   //��¼��ͻ��
								   m_day = m_TimeArray[i];
								   m_CanReading  = FALSE;
								   break;
							   }
							   
						   }
						   
						   
					   }
					   else
					   {
						   //����
						   for(int i = 0;i < m_TimeArray.GetSize();i ++)
						   {
							   
							   if(m_TimeArray[i] <= m_day1 || m_TimeArray[i] >= m_day2)
							   {
								   //��¼��ͻ��
								   m_day = m_TimeArray[i];
								   m_CanReading  = FALSE;
								   break;
							   }
							   
						   }
						   
						   
					   }
					   
				   }
				   
			   }
			   
			   if(!m_CanReading)
			   {
				   //��פ��������Ӱ��
				   SendContionStr.Format("Զ�̻�����̬���Ӷ���ɹ������˲�����Ӱ��%d�ն�ʱפ��������\r\n���ִ���п��ܵ���%d��פ����������������STOP��ťֹͣ��",m_day,m_day);
			   }
			   else
			   {
				   SendContionStr =  "BEGINS;MESSAGE:0:Զ�̻�����̬���Ӷ���ɹ���;ENDS";
			   }  

			   SendMessage(WM_EVENT, 4, 0);
			 		 
			   //���˷�Χ��ģ��
			   ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)13,m_Thread_PRIORITY,0,0,NULL); // ����������
			   ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
			   break;
		   
		   }

	   }
   
    }

}


//��д������Բ���,����������
//CString title          �б���
//CString Result         ����
//CString ConStr         ������Χ
//BYTE    orders         ����ؼ���
//BOOL    OnlyReadNot    TRUE  ֻ��û�в��Գ����ģ��
//                       FALSE ��֮
//int     times          ��ÿ��ģ��Ĵ���
//BOOL    OnlyOnce TRUE  �ö����һ��ģ��ʱֻ����һ��   FALSE ÿ��������һ��
//int     MaxIValue      ���ֵ(Ϊд����ʱ��)
//int     MinIValue      ��Сֵ
//int     intervals      ��  ��
void CIFRMView::DisposeModuleParameter(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals)
{
	
	BYTE    LineNo           =        0;//��  ��
	BYTE    PhaseNo          =        0;//��  ��
	BYTE    StationNo        =        0;//�����ֱ��վ����
	BYTE    MotherLine       =        0;//ĸ�߱��
	long    ModuleNo         =        0;//ģ���
	long    Records          =        0;//�Ǳ�����
	double  CurrentValue     =        0;//��ʼ��ģ������
	long    GetModuleNo      =        0;//�м����
	long    fields           =        0;//��¼��
	BYTE    m_AMMETERKIND    =        0;//�������
	BYTE    m_SUPPLYMODED    =        0;//���緽ʽ 0-���߹��� 1��վ������ 2-�������ֹ���
	BYTE    m_PROTOCOL       =        0;//����Э�� 71-73 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
    BYTE    m_SendAngle      =        0;//���͵ĽǶ� 2005-04-07�� 
	float   m_BeginValue     =        0;//����ֵ 
	BYTE    BakMotherLine    =        0;//����ĸ�߱��
	BYTE    BakLineNo        =        0;//������  ��

	CString           m_ReadAmmeterType;//��������
 	
	m_StartRead              =     TRUE;//��ͣ��־  
	
	CString   strSql,strValue,PhaseInfo;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	m_ListRows               =        0; 
	CString  m_ReadErrorStr,CondtionStr;
	
	//������Χ
	ConStr.TrimLeft();
	ConStr.TrimRight();
	
	//ɾ��ԭ������
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13��
	
	StatusStr.Format("����%s�����Ժ�...",Title);
    SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(TRUE);

	//���DIALOGBAR�ɼ��Ļ�������
	SendMessage(WM_EVENT, 6, 0);	
	
	//�����ݿ�
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
		
		//д�б����
		SendMessage(WM_EVENT, 2, 0);
		
		//��������ȫ������
		if(ConStr == "ALL")
		{
            //ֻ��û�в������
			if(OnlyReadNot)
			{
				//��Χ����
				CondtionStr = " USER_PHASE=3 AND USER_AMMETERKIND<=5";
				//��¼����
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//��ѯ���
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE USER_PHASE=3  AND USER_AMMETERKIND<=5";
			}
			else
			{
				//��Χ����
				CondtionStr = " USER_AMMETERKIND<=5";
				//��¼����
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//��ѯ���
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE USER_AMMETERKIND<=5";
			}

		}
		else
		{
            
			//ֻ����������
			if(OnlyReadNot)//ֻ��û�в������
			{
				//��Χ����
				CondtionStr = "(" + ConStr + ")  AND USER_PHASE=3  AND USER_AMMETERKIND<=5";
				//��¼����
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);  
				//��ѯ���       ���,��������,�û�����,�û����,��ַ,ģ���,����,��·����,ĸ��-�ߺ�-���,��̨��,����,����ֵ,����ʱ��
    			strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE " + CondtionStr;
			}
			else
			{	
				//��Χ����
				CondtionStr = "(" + ConStr + ") AND USER_AMMETERKIND<=5";
				//��¼����
				fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr);
				//��ѯ���
				strSql = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO FROM TB_USER WHERE " + CondtionStr;
			}

		}

		//δ�������ݲ�ѯ���
		m_ReadErrorStr = strSql   + " AND USER_READLABEL='NNNNNNNNNNNNNNN'";//15��N��ʾû�ж���

		rs.Open(CRecordset::forwardOnly,strSql);
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();
		rs.Close();
		
		//���û�м�¼�Ļ�
		if(fields < 1)
		{
            db.Close();
		
			//�������
		//	SendContionStr = "BEGINS;MESSAGE:0:û���������������ݻ��ߡ�վ�ܱ�ֱ�Ӵ�485�ڶ���,���ܴ���!!!;ENDS";
		//	SendMessage(WM_EVENT, 4, 0);
			
			//״̬����Ϣ
			StatusStr = "û���������������ݻ��ߡ�վ�ܱ�ֱ�Ӵ�485�ڶ���,���ܴ���!!!";
            SendMessage(WM_EVENT, 1, 0);
	
            //���ع�����
			ShowProgressCtrl(FALSE);
			m_StartRead   =   FALSE;
	
			return;
		}
		
		//���������ĸ�ֵΪ-1,����SQL���,��ԭ���������,���ó�ʼ����־
		strSql.Format("UPDATE TB_USER SET USER_READLABEL='NNNNNNNNNNNNNNN' WHERE %s",CondtionStr);
		CDataBaseInstance::ExecuteDataBaseSQL(strSql);

		//��������Χ
		SetProgressCtrlRange(0, fields,1);
			
		//ѭ������
		for(int m_Current = MinIValue;m_Current <= MaxIValue;m_Current = m_Current + intervals)
		{
			
			//���͵�ֵ
			m_PassValue         = m_Current;
			
			//ÿ����times��
			for(int m_ReadTimes = 0;m_ReadTimes < times;m_ReadTimes ++)
			{
			
				//�õ�û�ж������ݱ�־�ļ�¼��
				fields     = CDataBaseInstance::GetAllRecordsCount("TB_USER",CondtionStr + " AND USER_READLABEL='NNNNNNNNNNNNNNN'");  
				
				if(fields <= 0)
				{
					//û�пɶ��ļ�¼��
					m_ReadTimes = times;
				    //û�����������ļ�¼�Ļ�
					continue;
				}
				
			    //�����ݿ�����
				rs.Open(CRecordset::forwardOnly,m_ReadErrorStr);

				//���û���Ϣ
				for(int j = 0;j < fields; j ++)
				{
					
					//��ԭʼֵ
					CurrentValue = -1;
					
					//�������ֹͣ��ť
					if(!m_StartRead)
					{	
						
						if(rs.IsOpen())
						{
							rs.Close();
						}
						
						if(db.IsOpen())
						{
							db.Close();
						}
											
						//�������
						//SendContionStr = "BEGINS;MESSAGE:0:������;��ֹͣ!;ENDS";
						//SendMessage(WM_EVENT, 4, 0);
						
						//��ʾ״̬����Ϣ
						StatusStr = "��������;��ֹͣ��";
						SendMessage(WM_EVENT, 1, 0);
					    
						//���ع�����
						ShowProgressCtrl(FALSE);
						return;
					}
					
					//���
					strValue.Format("%d",m_ListRows + 1);
					m_StrArray[0].Format("%5s",strValue);
					
					//��ʾָ��
					m_StrArray[1] =  Title;
					
					//�ֶ���
					int i;
					for( i = 0; i < nFields; i++)
					{
						rs.GetFieldValue(int(i),strValue);
						strValue.TrimLeft();
						strValue.TrimRight();
						
						switch(i)
						{
						case 0:
							{
								//����
								m_StrArray[2] = strValue;
								break;
							}
						case 1:
							{ 
								//�û����  
								m_StrArray[3] = strValue;
								break;
							}
						case 2:
							{ 
								//סַ  
								m_StrArray[4] = strValue;
								break;
							}
						case 3:
							{  
								//ģ���
								m_StrArray[5].Format("%8s",strValue);
								ModuleNo = atol(strValue);
								break;
							}
						case 4:
							{  
								//����
								m_StrArray[6].Format("%8s",strValue);
								break;
							}
						case 5:
							{  
								//ĸ�ߺ�
								MotherLine = atoi(strValue); //add by 2004.10.21
								break;
							}
						case 6:
							{	
								//��·����
								m_StrArray[7] = strValue;
								break;
							}
						case 7:
							{
								//��·���
								LineNo = atoi(strValue);
								break;
							}
						case 8:
							{
								CString PhaseStr;
								//��
								switch(atoi(strValue))
								{
								case 0:
									{
										PhaseStr = "A��";
										PhaseNo = 0;
										break;
									}
								case 1:
									{
										PhaseStr = "B��";
										PhaseNo = 1;
										break;
									}
								case 2:
									{
										PhaseStr = "C��";
										PhaseNo = 2;
										break;
									}
								default:
									{
										PhaseStr = "δ֪";
										PhaseNo = atoi(strValue);
										break;
									}
								}
								m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
							
								//��������Ϣ
								if(PhaseNo < 3)
								{
								   PhaseInfo = m_StrArray[8];
								}
								break;
							}
						case 9:
							{
								//��̨����
								m_StrArray[9].Format("%s",strValue);
								break;
							}
						case 10:
							{
								//�����ֵ�վ��
								StationNo    = m_handno;
								//����ֵ
								m_BeginValue = float(atof(strValue));
								break;
							}
						case 11:
							{
								//�������
								m_AMMETERKIND = atoi(strValue);
								break;
							}
						case 12:
							{
								//���緽ʽ
								m_SUPPLYMODED = atoi(strValue);
								break;
							}	
						case 13:
							{
								//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
								m_PROTOCOL = atoi(strValue);

								if(m_PROTOCOL == 22 || m_PROTOCOL == 61 || m_PROTOCOL == 62)
								{
									//ת��ָ��
									switch(orders)
									{
									case 0xf4:
										{
											//�õ�״̬
											if(ModuleNo%100 < 12)
											{
												//�����
											}
											else
											{
												//485��
											}
											
											continue;
											break;
										}
									case 0x3c:
										{
										

											//ͣ�����
											if(ModuleNo%100 < 12)
											{
												//�����	
												if(m_PROTOCOL == 22)
												{
													orders = 0x02;
												}
											
											}
											else
											{
												//485��
												if(m_PROTOCOL == 22)
												{
													orders = 0x79;
												}
												else
												{
													orders = 0x02;
												}
												
											}
											
											break;
										}
									case 0xf6:
										{
											//�͵�
											if(ModuleNo%100 < 12)
											{
												//�����
												if(m_PROTOCOL == 22)
												{
													orders = 0x05;
												}
												else
												{
													orders = 0x01;
												}
											}
											else
											{
												//485��
												if(m_PROTOCOL == 22)
												{
													orders = 0x73;
												}
												else
												{
													orders = 0x04;
												}

											}
											
											break;
										}
									case 0xf8:
										{
											//ͣ��
											if(ModuleNo%100 < 12)
											{
												
												if(m_PROTOCOL == 22)
												{
													//�����
													orders = 0x03;
												}
												else
												{
													orders = 0x00;
												}

											}
											else
											{
												//485��	
												if(m_PROTOCOL == 22)
												{
													orders = 0x70;
												}
												else
												{
													orders = 0x05;
												}
												
											}
											
                                            break;
										} 
									case 0x02:
										{
											//������й�
											if(ModuleNo%100 < 12)
											{
												//�����
												if(m_PROTOCOL == 22)
												{
													orders = 0x07;
												}
												else
												{
													orders = 0x03;
												}

											}
											else
											{
												//485��	
												if(m_PROTOCOL == 22)
												{
													orders = 0x5f;
												}
												else
												{
													orders = 0x1f;
												}

											}
											
											break;
										}
									case 0x48:
										{
											//DSP����
											if(ModuleNo%100 < 12)
											{
												//�����
												
											}
											else
											{
												//485��
												
											}
											continue;
											
											break;
										}
									case 0x44:
										{
											//������ֵ
											if(ModuleNo%100 < 12)
											{
												//�����
												
											}
											else
											{
												//485��
												
											}

											continue;
											
											break;
										}
									}
									
								}

								m_StrArray[8] = m_StrArray[8] + strValue + "]";
								break;
							}	
						case 14:
							{
								//����ĽǶ�
								//m_SendAngle = atoi(strValue);
								//�Ƿ����ǽ�����,ƫ�ƽǶ�,�ǽ�Ϊ30��
								if(IsDyConnect(m_StrArray[9]))
								{
									m_SendAngle = 6;//atoi(strValue); 5��һ������
								}
								else
								{
									m_SendAngle = 0;
								}							
								break;
							}
						case 15:
							{
								//���������
								strValue.TrimLeft();
								strValue.TrimRight();
								m_ReadAmmeterType = strValue;
								break;
							}	
						case 16:
							{
								//����ĸ�߱��
								BakMotherLine = atoi(strValue);
								break;
							}	
						case 17:
							{
								//���ó��ߺ�
								BakLineNo     = atoi(strValue);
								break;
							}
							
						 }
							
					   }
						
						//�ö����һ��ģ��ʱ��ֻ����һ��ʱ
						if(OnlyOnce == TRUE && abs(ModuleNo-GetModuleNo)<=16 &&  GetModuleNo > 0)
						{
							//�ö����һ��ģ��ʱ��ֻ����һ��ʱ
							GetModuleNo    = ModuleNo;
							//��ȡ��·������Ϣ
							m_StrArray[8]  = PhaseInfo;
							m_StrArray[11] = "";
						}
						
						//��ʾ״̬����Ϣ
						StatusStr.Format("����%s[%d-%d],[%d],���%.2f��,���Ժ�...",Title,fields,m_ListRows + 1,ModuleNo,float(m_ListRows)*100/fields);
						SendMessage(WM_EVENT, 1, 0);
						
						//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
						//SendMessage(WM_EVENT, 4, 0);//��������
						
						//ģ��Ų���ȵĻ�
						if(GetModuleNo != ModuleNo)
						{
							
							//��֪��������Ļ�,ÿ���඼����һ��
							if(PhaseNo > 2)
							{
								
								//��ѭ��
								for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
								{
									
									//�������ֹͣ��ť
									if(m_StartRead == FALSE)
									{
										break;
									}
									
									switch(PhaseNo)
									{
									case 0:
										{	
											strValue.Format("����%s,����ģ���(%d)A��,���Ժ�...",m_StrArray[1],ModuleNo);
											break;
										}
									case 1:
										{
											strValue.Format("����%s,����ģ���(%d)B��,���Ժ�...",m_StrArray[1],ModuleNo);
											break;
										}
									case 2:
										{
											strValue.Format("����%s,����ģ���(%d)C��,���Ժ�...",m_StrArray[1],ModuleNo);
											break;
										}
									}
									
									//��ʾ״̬����Ϣ
									StatusStr =        strValue;
									SendMessage(WM_EVENT, 1, 0);
									
									if(m_SendAngle == 0)
									{
										CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine/*ĸ��*/,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									else
									{
										//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
										CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine/*ĸ��*/,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}

									if(m_PROTOCOL != 22)
									{
										//ͣ����͵�,31,32,71,72Э��ص���ӦΪ333333.33
										if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
										{
											CurrentValue = -1;
										}										
									}
									else
									{
										//22Э��ص���Ϊ3.2
										if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
										{
											CurrentValue = -1;
										}
									}

									//������������֣��ٶ�һ������
									if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
									{

										if(m_SendAngle == 0)
										{
											CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
										}
										else
										{
											//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
											CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
										}
										
										if(m_PROTOCOL != 22)
										{

											//ͣ����͵�,31,32,71,72Э��ص���ӦΪ333333.33
											if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
											{
												
												CurrentValue = -1;

											}	
											
										}
										else
										{
											//22Э��ص���Ϊ3.2
											if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
											{
												
												CurrentValue = -1;
											
											}

										}
										
										//����ڱ���ĸ�ߺͱ��ó����϶�����
										if(int(CurrentValue) != -1)
										{
											MotherLine =   BakMotherLine;
											LineNo     =       BakLineNo;
										}
										
									}
									
									//���������ֵ���ڻ����0		//if(CurrentValue >= 0)
									if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
									{
										
										//��
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A��",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B��",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C��",m_PROTOCOL);
												break;
											}
										}

										//��������Ϣ
										PhaseInfo = m_StrArray[8];
										
										//���������ݿ�
										strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",PhaseNo,ModuleNo - 16,ModuleNo + 16);
										//����SQL���
										CDataBaseInstance::ExecuteDataBaseSQL(strValue); 

										//����SQL���,д��Զ�̻���
									    //SendContionStr.Format("BEGINS;COMMAND:12:%s;ENDS",strValue);
									    //SendMessage(WM_EVENT, 4, 0);
										break;
									}
									
								}
								
								
							}
							else
							{
								//֪������Ͷ�����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*ĸ��*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
								
								SurrenderWindowMessage();
							
								if(m_PROTOCOL != 22)
								{
									//ͣ����͵�,31,32,71,72Э��ص���ӦΪ333333.33
									if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
									{
										CurrentValue = -1;
									}										
								}
								else
								{
									//22Э��ص���Ϊ3.2
									if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
									{
										CurrentValue = -1;
									}
								}
								
								//������������֣��ٶ�һ������
								if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
								{

									if(m_SendAngle == 0)
									{
										CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									else
									{
										//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
										CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
									}
									
									if(m_PROTOCOL == 22)
									{
										//22Э��ص���Ϊ3.2
										if((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && int(CurrentValue*10)!=32)
										{
											CurrentValue = -1;
										}
																	
									}
									else if(m_PROTOCOL == 61 || m_PROTOCOL == 62 )
									{
										//ͣ����͵�,31,32,71,72Э��ص���ӦΪ333333.33
										if((orders == 0x04 || orders == 0x05 || orders == 0x01 || orders == 0x00)  && int(CurrentValue*100)!=32)
										{
											CurrentValue = -1;
										}		
									
									}
									else
									{
										//ͣ����͵�,31,32,71,72Э��ص���ӦΪ333333.33
										if((orders == 0xf6 || orders == 0xf8)  && int(CurrentValue*100)!=33333333)
										{
											CurrentValue = -1;
										}	


									}

									//����ڱ���ĸ�ߺͱ��ó����϶�����
									if(int(CurrentValue) != -1)
									{
										switch(PhaseNo)
										{
										case 0:
											{
												m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A��",m_PROTOCOL);
												break;
											}
										case 1:
											{
												m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B��",m_PROTOCOL);
												break;
											}
										case 2:
											{
												m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C��",m_PROTOCOL);
												break;
											}
										}
										
										MotherLine = BakMotherLine;
										LineNo     =     BakLineNo;
									}
									
								}
								
							}
								
							//���ݵõ���ֵ�½���
							if(int(CurrentValue) == -1)
							{	
								//�û����»�һ����¼
								rs.MoveNext();
								//��������ִ��
								continue;
							}
							else
							{	
								
								//ģ�鼸����ֻ��ֻ��һ���͹���
								if(OnlyOnce)
								{
									//���ɹ��ı�־
									strValue.Format("UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d",ModuleNo - 16,ModuleNo + 16);
									//����SQL���
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);	//���ɹ��ı�־
								}
								else
								{   
									//���ɹ��ı�־
									strValue.Format("UPDATE TB_USER SET USER_READLABEL='YYYYYYYYYYYYYYY' WHERE USER_MODULENO=%d",ModuleNo);
									//����SQL���
									CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								}

							}
								
						}

							
						//���ݵõ���ֵ�½���
						if(CurrentValue >= 0 )
						{	
							
							//��ȷ�Ļ�
		                    Beep(5000,400); 

    						//�յ���ֵת���ɶ�Ӧ�ĵ���ֵ
							if(orders == 0x44 && m_PROTOCOL!=22) 
							{
								CurrentValue = double(SwitchCurrentValue(float(CurrentValue)));
							}
							else if((orders == 0xf6 && m_PROTOCOL!=22) || ((orders == 0x05 || orders == 0x73) && m_PROTOCOL==22))
							{
								//�͵�,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_ETSTATUS = '%s' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d","�͵�״̬",ModuleNo - 16,ModuleNo + 16);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
							}
							else if((orders == 0xf8 && m_PROTOCOL!=22) || ((orders == 0x03 || orders == 0x70) && m_PROTOCOL == 22))
							{
								//ͣ��,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_ETSTATUS = '%s' WHERE USER_MODULENO>= %d AND USER_MODULENO<= %d","ͣ��״̬",ModuleNo - 16,ModuleNo + 16);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
							}
							
							//ģ��Ÿ���
							GetModuleNo = ModuleNo;
							strValue.Format("%.2f",CurrentValue);
							
							//д���ɹ���ķ���ֵ
							if(((orders == 0x3e || orders == 0x40 || orders == 0x46 || orders == 0x4A || orders == 0x4e || orders == 0x50 || orders == 0xf6 || orders == 0xf8) && m_PROTOCOL!=22) || ((orders == 0x03 || orders == 0x70 || orders == 0x05 || orders == 0x73) && m_PROTOCOL == 22))
							{
								m_StrArray[11] = "0x33";	   
							}
							else
							{	
								m_StrArray[11].Format("%12s",strValue);
							}
							
							//����
							m_StrArray[10] = " " + Result;
							
							//����̨����
							if(orders == 0x50)
							{
								
								strValue.TrimLeft();
								strValue.TrimRight();
								
								switch(atoi(strValue.Left(1)))
								{
								case 1:
									{
										m_StrArray[10] = "[30,49]kVA";
										break;
									}
								case 2:
									{
										m_StrArray[10] = "[50-99]kVA";
										break;
									}
								case 3:
									{
										m_StrArray[10] = "[100-199]kVA";
										break;
									}
								case 4:
									{
										m_StrArray[10] = "[200-299]kVA";
										break;
									}
								case 5:
									{
										m_StrArray[10] = "[300-399]kVA";
										break;
									}
								case 6:
									{
										m_StrArray[10] = "[400-599]kVA";
										break;
									}
								case 7:
									{
										m_StrArray[10] = "[600-9000]kVA";
										break;
									}
								}
								
							}
							
						}
						else
						{
							
							//�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û������
							if(int(CurrentValue) == -2)
							{	
								
								//��ȷ�Ļ�
		                        Beep(5000,400); 
								m_StrArray[11] = "����1 ";
							}
							else
							{

								if(int(CurrentValue) == -3)
								{
								
									//��ȷ�Ļ�
                        		    Beep(5000,400); 
 									m_StrArray[11] = "����2 ";
								
								}

							}
							
							//����
							m_StrArray[10] = Result;
						}
							
						//ʱ��
						CTime timet = CTime::GetCurrentTime();	
						m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
						
//						DataStr.Format("BEGINS;DATAS:1:%s",m_ComeIntoDataName);
						
						//��ʾ����б�
						for(i = 0; i < 13; i++)
						{		
							m_StrArray[i].TrimLeft();
							m_StrArray[i].TrimRight();
							
							//���ݸ�ʽ����
							if(i == 0)
							{
								//���
								if(m_StrArray[i].GetLength() < 5)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%5s",strValue);
								}
								
							}
							else if( i == 5)
							{   
								//ģ��� 
								if(m_StrArray[i].GetLength() < 8)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%8s",strValue);
								}
								
							}
							else if( i == 11)
							{   
								//������ֵ
								if(m_StrArray[i].GetLength() < 12)
								{
									strValue = m_StrArray[i];
									m_StrArray[i].Format("%12s",strValue);
								}
								
							}
							
							DataStr = DataStr + ";" + m_StrArray[i];
							
						}
						
						//��ʾ�б�����
						SendMessage(WM_EVENT, 3, 0);
					//	DataStr = DataStr +  ";" + "ENDS";
						
						SetProgressCtrlSetIt();
						//�к��Լ�
						m_ListRows++;
						
						//��������
					//	SendContionStr = DataStr;
					//	SendMessage(WM_EVENT, 4, 0);
				
						//�û����»�һ����¼
						rs.MoveNext();
							
                     }
					
					 //�ر����ݿ�
					 if(rs.IsOpen())
					 {
						 rs.Close();
					 }
									 
				}
				//ÿ����times�ν���
				
        }
		//ѭ���������� 
		
		if(db.IsOpen())
		{
			db.Close();
		}
      		
    }
  
	//״̬����ϢΪ��
	StatusStr = "                            ";
    SendMessage(WM_EVENT, 1, 0);
	
	//��ʾDialogBar
    //SendMessage(WM_EVENT, 7, 0);
	ShowProgressCtrl(FALSE);
	m_StartRead    =  FALSE;

}

//���ýǶ�
//short generatrixno ĸ�߱��
//short phase        ��� 0 A�� 1 B�� 2 C��
//int   angles       �Ƕ�
//BYTE  kinds  ���� 0--�ź�ǿ�� 1���ӳٽǶ�
void CIFRMView::SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds)
{
	
	CString    PassStr;

    //��ְ汾//TRUE ���վ�汾  FALSE��ְ�
	if(AppInfo::Instance().m_WhichKind == FALSE)
	{
	   	//  BEGINS;COMMAND:07:����1:����2;ENDS  07 �����ź�ǿ��   06 �����ӳٽǶ�
		//                    ����1---��һ�� 0��A 1��B 2��C��  
		//                    ����2---�Ƕȴ�С   
		if(kinds == 0)
		{
			PassStr.Format("BEGINS;COMMAND:07:%d:%d:%d;ENDS",generatrixno,phase,angles);	//������ӺõĻ�
		}
		else
		{
			PassStr.Format("BEGINS;COMMAND:06:%d:%d:%d;ENDS",generatrixno,phase,angles);	//������ӺõĻ�
		}
		
		//���ýǶȴ�С
		if(SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE) == TRUE)
		{
			SurrenderWindowMessage();//����window����Ȩ
		//	Sleep(1000);
		}
		
		
	}
	else
	{
		
	   	CString    str;
		BYTE ORDER[15];
		
		//�Ƕ����� 
		ORDER[0]  = 0x51;
		ORDER[1]  = 0x52;//ǰ����
		
		switch(phase)
		{
		case 0:
			{  
				if(kinds == 0)
				{
					ORDER[2]  = 0x5c;//A��Ƕ�����
				}
				else
				{		
					ORDER[2]  = 0xC0;//A���ӳٽǶ�
				}
				break;
				
			}
		case 1:
			{
				if(kinds == 0)
				{
					ORDER[2]  = 0x5d;//B��Ƕ�����
				}
				else
				{
					ORDER[2]  = 0xC1;//B���ӳٽǶ�
				}
				break;
				
			}
		case 2:
			{
				if(kinds == 0)
				{
					ORDER[2]  = 0x5e;//c��Ƕ�����
				}
				else
				{	
					ORDER[2]  = 0xC2;//c���ӳٽǶ�
				}
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
		if(PcSendToSCM(ORDER,31,0))
		{
			
			switch(phase)
			{
			case 0:
				{  
					if(kinds == 0)
					{
						str = "A���ź�ǿ���������!";
					}
					else
					{
						str = "A���ӳٽǶ��������!";
					}

					break;
					
				}
			case 1:
				{
					
					if(kinds == 0)
					{
						str = "B���ź�ǿ���������!";
					}
					else
					{
						str = "B���ӳٽǶ��������!";
					}

					break;
					
				}
			case 2:
				{
					
					if(kinds == 0)
					{
						str = "C���ź�ǿ���������!";
					}
					else
					{
						str = "C���ӳٽǶ��������!";
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
					if(kinds == 0)
					{
						str = "A���ź�ǿ�����ô���!";
					}
					else
					{
						str = "A���ӳٽǶ����ô���!";
					}

					break;
					
				}
			case 1:
				{
					
					if(kinds == 0)
					{
						str = "B���ź�ǿ�����ô���!";
					}
					else
					{
						str = "B���ӳٽǶ����ô���!";
					}

					break;
					
				}
			case 2:
				{
					
					if(kinds == 0)
					{
						str = "C���ź�ǿ�����ô���!";
					}
					else
					{
						str = "C���ӳٽǶ����ô���!";
					}

					break;
				}

			}
		
		}
			
		//MESSAGE    ��ʾ��Ϣ�Ի���
		//��ʽΪ:
		//    a��BEGINS;MESSAGE:0:����;ENDS ��ʾ��ʾ�Ի���
		//    b��BEGINS;MESSAGE:1:����;ENDS ��ʾ����Ի���
		PassStr.Format("BEGINS;MESSAGE:0:%s;ENDS",str);		
		
		//������ʾ��Ϣ
		if(SelectSendString(m_sendkind,PassStr,TRUE,FALSE,TRUE) == TRUE)
		{
			status(str);
		}
		else
		{
			MessageBox(str," ",MB_OK|MB_ICONASTERISK);
		}
	
     }

}


//��ȡ�Ƕ�
//short generatrixno ĸ�߱��
//short phase  ��� 0 A�� 1 B�� 2 C��
void CIFRMView::ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds)
{
	
	CString             PassStr;
	
    //��ְ汾//TRUE ���վ�汾  FALSE��ְ�
	if(AppInfo::Instance().m_WhichKind == FALSE)
	{
		
		//���Ƕȴ�С
		//BEGINS;COMMAND:08:����1:����2;ENDS 
		//����1---ĸ�߱��  
		//����2---��һ�� 0��A 1��B 2��C��      
		//  BEGINS;COMMAND:08:����1:����2;ENDS  08 ��ȡ�ź�ǿ��   09 ��ȡ�ӳٽǶ�
		//                    ����1---��һ�� 0��A 1��B 2��C��  
		//                    ����2---�Ƕȴ�С   

		if(kinds == 0)
		{
			PassStr.Format("BEGINS;COMMAND:08:%d:%d;ENDS",generatrixno,phase);//������ӺõĻ�
		}
		else
		{
			PassStr.Format("BEGINS;COMMAND:09:%d:%d;ENDS",generatrixno,phase);//������ӺõĻ�
		}

	    SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
		
	}
	else
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
		if(PcSendToSCM(ORDER,31,0))
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
						str.Format("������ģ��C�������ѹ����");
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
						str.Format("������ģ��C�������ѹ����");
						break;
					}
				}
				
				break;
				
			}
				
		}
		
	}
	
	MessageBox(str," ",MB_OK|MB_ICONASTERISK);
	}
}

//��鵱ǰ�Ƿ��г��������
BOOL CIFRMView::CheckRunning()
{   
	//����ڴ������ݻ����������Ļ�
	if(ReadMeterThread != NULL || m_StartRead == TRUE) 
	{
		MessageBox("����ִ����������,�˴�ָ�����,�밴\r\nSTOP��ťֹͣ��������������������!"," ",MB_OK|MB_ICONWARNING);
		return TRUE;
	}
	
	return FALSE;
	
}

//TCP ������,���ö˿�
void CIFRMView::SetLocalServer(CString LocalHostAddress, int LocalPort)
{ 
	//IP ��ַ�磺121.111.1.1
    VARIANT LocalHostPort_VT,LocalHostIP_VT;
	m_WinSocket.Close();
    	
	LocalHostPort_VT.vt    = VT_I2;//����Ϊ����
    LocalHostPort_VT.lVal  = LocalPort;
	
    LocalHostIP_VT.vt      = VT_BSTR;//����Ϊ�ַ���
    LocalHostIP_VT.bstrVal = LocalHostAddress.AllocSysString();
	
	//TCP���ӵ� LocalPort �� LocalIP��
	m_WinSocket.Bind(LocalHostPort_VT, LocalHostIP_VT);
	
	//��ʼ����
	m_WinSocket.Listen();
	
	status("����������״̬��");
	
}

/*
GetState()ֵ
����                  ֵ      ���� 
sckClosed             0       ȱʡ�ġ��ر� 
sckOpen               1       �� 
sckListening          2       ���� 
sckConnectionPending  3       ���ӹ��� 
sckResolvingHost      4       ʶ������ 
sckHostResolved       5       ��ʶ������ 
sckConnecting         6       �������� 
sckConnected          7       ������ 
sckClosing            8       ͬ����Ա���ڹر����� 
sckError              9       ���� 
*/

//���������ӵ���ʱ����(��������)
void CIFRMView::OnConnectionRequestWinsock(long requestID) 
{	

	//���ؼ��� State �����Ƿ�Ϊ�رյ�,�������,�ڽ����µ�����֮ǰ�ȹرմ����ӡ�
	if(m_WinSocket.GetState() != 0)
	{
		m_WinSocket.Close();
	}
	
	//	����           ֵ     ���� 
	//sckTCPProtocol   0      ȱʡ�ġ�TCP Э�顣 
	//sckUDPProtocol   1      UDP Э�顣 
    m_WinSocket.SetProtocol(0); 
	
	//���ܾ��� requestID ����������
	m_WinSocket.Accept(requestID);
	
	//���ӱ�־
	m_IsConnect      = TRUE;

	//�����ԭ�κųɹ�״̬��
	if(m_Com.GetCDHolding())
	{	
		 //�ر�Զ��è
		 SelectSendString(2, "BEGINS;COMMAND:32:�����ذ���ͨ���绰����Զ�̰�������(æ)���������ӶϿ���;ENDS",TRUE,FALSE,TRUE);
		
		 //TRUE ���վ�汾  FALSE��ְ�
	     OnCloseWinsock();

		 status("����ͼ���������ӣ����绰ռ�ã�����������ʧ�ܡ�");
		 return;

	}

}

//���� TCP �ͻ���
void CIFRMView::SettcpClient(CString RemoteHostAddress, int RemotePort)
{
	
	//  if(m_WinSocket.GetState() != 0)
	{
		m_WinSocket.Close();
	}
	
	//IP ��ַ�磺121.111.1.1
	VARIANT RemoteHostPort_VT,RemoteHostIP_VT;
	
	RemoteHostPort_VT.vt    = VT_I2;//����Ϊ����
	RemoteHostPort_VT.lVal  = RemotePort;
	
	RemoteHostIP_VT.vt      = VT_BSTR;//����Ϊ�ַ���
	RemoteHostIP_VT.bstrVal = RemoteHostAddress.AllocSysString();
	
	m_WinSocket.SetRemoteHost(RemoteHostAddress);
	m_WinSocket.SetRemotePort(RemotePort);
	
	//����Connect����,��ʼ�����ӡ�
	m_WinSocket.Connect(RemoteHostIP_VT,RemoteHostPort_VT);
	
}

//�����ݵ���ʱ�����¼�
void CIFRMView::OnDataArrivalWinsock(long bytesTotal) 
{
	long                  ix;
	int                  k,l;
	BYTE                 bit;
	CString   str,ReceiveStr;
	//�����ֽ�����
	COleVariant     recv_var;
	
	ReceiveByteArray.RemoveAll();
	
	//����
	VARIANT            Vtype;
	Vtype.vt    =   VT_ERROR;
	
	//����
	VARIANT           Maxlen;
	Maxlen.vt   =      VT_I4;
	Maxlen.lVal = bytesTotal;
	
	m_WinSocket.GetData(&recv_var, Vtype, Maxlen);//�������ݰ�
	
	if(recv_var.parray != NULL) 
	{
		
		for( ix = 0; ix < bytesTotal; ix ++)
		{
			
			SafeArrayGetElement(recv_var.parray,&ix,&bit);
			char a=*(char*)(&bit); 
			str.Format("%c",a); 
			ReceiveStr+=str;   
		
		}
				
		k = ReceiveStr.Find("ENDS");
		l = ReceiveStr.Find("BEGINS");

   		//������Ҫ������
		if(k != -1 && l != -1)
		{	
			/****************ȥ��ͷ��β�������ַ�*********/
			ReceiveStr = ReceiveStr.Mid(l+7,k - l - 8);
			ReceiveStr.TrimLeft();
			ReceiveStr.TrimRight();
			AnalyseOrder(ReceiveStr);//��������������,�Խ��յ�����������Ҫ����
	
		}
		
	} 
	
}

BOOL CIFRMView::DestroyWindow() 
{	
    //m_WinSocket.Close();	
	return CFormView::DestroyWindow();
}

void CIFRMView::OnCloseWinsock() 
{   

	if(AppInfo::Instance().m_WhichKind )
	{
	   
		//����Ƿ�������,�ڱ��վ��
		m_WinSocket.Close();
		
		Sleep(200);
		
		//��������������
		SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
	}
	else
	{
		m_WinSocket.Close();
	}
	
	//���ӱ�־
	m_IsConnect   =    FALSE;

}




/************************************************************************
**    �ܸ�ʽ:������BEGINS;������ѡ��;*;*;*;*;*;*;ENDS 
**
**     MESSAGE    ��ʾ��Ϣ�Ի���
**          ��ʽΪ:
**               a��BEGINS;MESSAGE:0:����;ENDS ��ʾ��ʾ�Ի���
**               b��BEGINS;MESSAGE:1:����;ENDS ��ʾ����Ի���
**
**     DATAS      ���ݴ���
**         �յ��ĸ�ʽ������:
**         a��BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
**         b��BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
**         c��BEGINS;DATAS:2:����;�������;ENDS      ���ݴ��ͽ�����־
**         d��BEGINS;DATAS:3:StopData;ֹͣ;ENDS      ����ֹͣ��ť���
** 
**                                      
**     SEND       ��������(���б�����ʾ)
**          ��ʽΪ:
**                   BEGINS;SEND:����:��ѯ����;ENDS Ҫ�䴫����������������
** 												 
** 
**    COMMAND  ִ������
**    ��ʽΪ:
**    1��BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  ����1---ĸ��,����2---���,����3---���͵�ʱ�䵥λ��(8�ı���),����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������     
**    2��BEGINS;COMMAND:01:����1;ENDS              ����1---���ݷ�Χ                       ִ�в��Զ������
**    3��BEGINS;COMMAND:02:����1;ENDS              ����1---���ݷ�Χ                       ִ����ʽ�������
**    4��BEGINS;COMMAND:03:����1;ENDS              ����1---���ݷ�Χ                       ִ��פ���������
**    5��BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
**                         ����1---����         ����2---���                   ����3---������Χ
**    	                   ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
**    	                   ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
**    	                   ����10--���         ��д������Բ���,����������
****************************************************************************/

//���������ָ��Խ��յ�����������Ҫ���� 
void CIFRMView::AnalyseOrder(CString OrderStr)
{
	
	int                k,l;
	CString            str;
	m_IfChangeData  = TRUE;//����Զ�����ݵı�־
	
    //Զ��Ҫ��ֹͣ
	if(OrderStr.Find("DATAS:3:StopData") != -1)
	{ 
		//����Ĵ�����Ϊ0
		m_GetErrors   =       0;
		
		for(BYTE i = 0; i < 10; i ++)
		{
			
			m_StartRead       =   FALSE;
			bStopped          =    TRUE;
			//���Ӷ���
			m_CheckReading    =   FALSE;	
			
			//����window����Ȩ
			SurrenderWindowMessage();
			Sleep(250);
			
			if(ReadMeterThread == NULL)
			{
				break;
			}
			
		}
		//����߳���ͣ
		
		if(ReadMeterThread != NULL  && m_Pause)
		{
			//�����߳��˳�
			ReadMeterThread->ResumeThread();
			m_Pause  =   FALSE;	
			
			//����window����Ȩ
			SurrenderWindowMessage();
			Sleep(500);
			//����window����Ȩ
			SurrenderWindowMessage();
			//����߳���ͣ
		}
		
		//ֹͣ��������
		m_StopPassing    = TRUE;
		
		KillTimer(2);
		KillTimer(3);
		
		//��ʾ�����ض���
		OperationAnimation(FALSE);
		//���ع�����
		ShowProgressCtrl(FALSE);
		
		//����window����Ȩ
		SurrenderWindowMessage();
		//�����Խ���������
		m_ReceiveOk    =   FALSE;
		status("              ");
		
	   /*
		//����Ĵ�����Ϊ0
	    m_GetErrors   =       0;
		m_StartRead   =   FALSE;
		m_others      =   FALSE;

		//ֹͣ��������
	    m_StopPassing =    TRUE;
		//����window����Ȩ
		SurrenderWindowMessage();
		//ֹͣ��ʱ����
		KillTimer(2);
		//ֹͣ��ʱ����
		KillTimer(3);
		//��ʾ�����ض���
		OperationAnimation(FALSE);
		Sleep(1000);
		*/
		return;
	}
	
	//Զ��Ҫ��ֹͣ�Զ���פ���Զ�����
	if(OrderStr.Find("DATAS:4:StopData") != -1)
	{ 	
		
		//�ж���Ļ����˳�
		m_StartRead   =   FALSE;
        m_others      =   FALSE;

		KillTimer(1);
		KillTimer(2);
		KillTimer(3);

		//�����������±������Ϊ0
		m_statusstr     =       "";
		status("                         ");

		if(m_IsAutoSending)
		{
			m_IsAutoSending =    FALSE;
			SendContionStr  =    "BEGINS;MESSAGE:0:�Զ���פ���Զ�������ȡ��!;ENDS";
			SendMessage(WM_EVENT, 4, 0);
			status("���Զ���פ��������ȡ����");
			//����window����Ȩ
			SurrenderWindowMessage();

			//д����ʷ��¼��,ʱ��
			CString strs;
			CTime timet = CTime::GetCurrentTime();
			strs.Format("��%4d-%02d-%02d %02d:%02d:%02d��Զ��ȡ������ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			WriteToLog(strs);
			
			//��ʱ��ť��ΪFALSE
			ShowDingShiButton(FALSE);
		}
		else
		{
			//Զ�̲�ѯ�Է���פ������
			SendContionStr = "BEGINS;MESSAGE:0:�Է�������ʱפ������Ϊ�գ�;ENDS";
			SendMessage(WM_EVENT, 4, 0);
		}
		return;

	}		
	
	//MESSAGE    ��ʾ��Ϣ�Ի���
	//��ʽΪ:
	//a��BEGINS;MESSAGE:0:����;ENDS   ��ʾ��ʾ�Ի���
	//b��BEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
	k = OrderStr.Find("MESSAGE:");
	
	if(k != -1)
	{
		k = OrderStr.Find("MESSAGE:0");
		
		if(k != -1)
		{	  
			//��ʾ��Ϣ�ַ�
			str         = OrderStr.Right(OrderStr.GetLength() -10);
			
			//����ǵ�ְ�,�����Ի��򣬱��վ�汾����״̬������ʾ��Ϣ
			if(!AppInfo::Instance().m_WhichKind)
			{
				status("                     ");
				MessageBox( str," ",MB_OK|MB_ICONWARNING);
				m_StartRead          =    FALSE;
			}
			else
			{
				status(str);
			}
			
		}
		else
		{
			str = OrderStr.Right(OrderStr.GetLength() - 10);
			//״̬����ʾ��Ϣ
			status(str);
		}
		
	}
	
	//TRUE-���վ�汾 FALSE-��ְ�,����������������ڴ�����
	if(AppInfo::Instance().m_WhichKind)
	{

		//������վ������פ������1���ڷ�פ������ 2�������ݶ��� 
		if(ReadMeterThread != NULL)
		{
			//����window����Ȩ
		    SendContionStr.Format("BEGINS;MESSAGE:0:%s;ENDS","��Զ�̻��������ڶ���������ֵ���״̬��æ��");
			SendMessage(WM_EVENT,4,0);
        	return;

		}

	}

	
	/***********���͵�������,���б�����ʾ����***********/
	//��ʽΪ:
	//    a��BEGINS;DATAS:0:����;��ṹ;ENDS        ���ݿ������ݽṹ
	//    b��BEGINS;DATAS:1:����;*;*;*;*;*;*;*;ENDS ���ݿ�������
	//    c��BEGINS;DATAS:2:����;�������;ENDS      ���ͱ����
	//    d��BEGINS;DATAS:3:StopData;ֹͣ;ENDS      ֹͣ����
	
	k = OrderStr.Find("DATAS:");
	
	if( k != -1)
	{	
		//��ʾʵʱ����
		RealTimeReceiveData(OrderStr);
	}
	else 
	{
		
		/***********��Ҫ������������������***********/
		//��ʽΪ:
		//��ʽ: BEGINS;SEND:0:����:��ѯ����;ENDS   ��������,���б�����ʾ����,���Ƕϵ����� 
	
		k = OrderStr.Find("SEND:");
		
		if(k != -1)
		{
			
			k = OrderStr.Find(':');
			
			if( k != -1)
			{
				
				//ȥ��"SEND:"
				OrderStr = OrderStr.Right(OrderStr.GetLength()- k - 1);
				
				k = OrderStr.Find(':');
				
				if( k != -1)
				{
					
					l = atoi(OrderStr.Left(k));
					
					//ȥ��"0:"��"1:"
					OrderStr = OrderStr.Right(OrderStr.GetLength()- k - 1); 
					
					k = OrderStr.Find(':');
					if( k != -1)
					{
						
						//�õ�Ҫ���ı���, �õ�����������
						//���͸�����Ҫ�������,���б�����ʾ����
						if(l == 0)
						{

							//������������ļ�¼
							CString m_DataName,m_Condtion,m_filename,m_SqlStr;
                            m_DataName = OrderStr.Left(k);
							m_Condtion = OrderStr.Right(OrderStr.GetLength()- k - 1);
                            m_filename.Format("%s%s%s",GetFolder(),m_DataName,".TXT");
							
							long fields = CDataBaseInstance::GetAllRecordsCount(m_DataName,m_Condtion);
							
							m_Condtion.TrimLeft();
                            m_Condtion.TrimRight();

							if(m_Condtion == "ALL")
							{
								m_SqlStr.Format("SELECT * FROM %s",m_DataName);
							}
							else
							{
								m_SqlStr.Format("SELECT * FROM %s WHERE %s",m_DataName,m_Condtion);
							}
							
							if(fields > 0)
							{
								//���߶Է��ж�������
								WriteDataToTextFile(m_DataName,m_SqlStr,fields,m_filename);	
								//���߶Է�û������
								SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS",m_DataName,fields);
					            SendMessage(WM_EVENT, 4, 0);
							}
							else
							{
								//���߶Է�û������
								SendContionStr = "BEGINS;MESSAGE:0:�Բ��𣬶Է�����û�������������������Ϣ!;ENDS";
								SendMessage(WM_EVENT, 4, 0);
							}

							//ֹͣ��������
	                        m_StopPassing = FALSE;
  							
						}

					}
					
				}
				
			}
			
		}
		else
		{
			
			/****************************  ִ������   **********************************
			COMMAND  ִ������
			��ʽΪ:
			1��BEGINS;���վ���;COMMAND:00:����1:����2:����3:����4;ENDS  ����1---ĸ��,����2---���,����3---���͵�ʱ�䵥λ��(8�ı���),����4---���͵�ʱ��(�ַ���ʽ) ִ�з�פ������    
			2��BEGINS;COMMAND:01:����1;ENDS              ����1---���ݷ�Χ                       ִ�в��Զ������
			3��BEGINS;COMMAND:02:����1;ENDS              ����1---���ݷ�Χ                       ִ����ʽ�������
			4��BEGINS;COMMAND:03:����1;ENDS              ����1---���ݷ�Χ                       ִ��פ���������
			5��BEGINS;COMMAND:11:����1;ENDS              ����1---���ݷ�Χ                       ִ���͵����
			6��BEGINS;COMMAND:05:����1;ENDS              ����1---���ݷ�Χ                       ִ��ͣ�����
			****************************************************************************/
			
			k = OrderStr.Find("COMMAND:");
			
			if(k != -1)
			{
				//ִ������
				CarryOutOrders(OrderStr);
			}
			
		}
		
	}
}


//�����κŲ�������ʾ
void CIFRMView::AnalyseDial(CString str)
{
	CStringArray m_StrArray;
    m_StrArray.Add("RING");
	m_StrArray.Add("��⵽�κ������ź�...           ");
	m_StrArray.Add("ERROR");
	m_StrArray.Add("��Ч��������д���...         "); 
	m_StrArray.Add("CONNECT");
    m_StrArray.Add("�κ����ӳɹ�������               ");
    m_StrArray.Add("NO DIALTONE");
	m_StrArray.Add("û�м�⵽�κ������κ�ʧ��...   ");
    m_StrArray.Add("BUSY");
	m_StrArray.Add("��⵽æ��,�Է���·æ���κ�ʧ��...");
    m_StrArray.Add("NO ANSWER");
	m_StrArray.Add("�εĵ绰�����ź������κ�ʧ��... ");	
	
	for(int i = 0; i < m_StrArray.GetSize(); i = i + 2)
	{
        str.MakeUpper( );

		//������Ӧ�ķ���ֵ
		if(str.Find(m_StrArray[i]) != -1)
		{	

			if(!AppInfo::Instance().m_WhichKind)
			{
				MessageBox(m_StrArray[i + 1]," ",MB_OK|MB_ICONASTERISK);
			}
			else
			{	
				CTime time = CTime::GetCurrentTime();	
				str.Format(" %d-%d-%d %d:%d:%d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				status(m_StrArray[i + 1] + str);
			}
			ReceiveByteArray.RemoveAll();
		}
		
	}

			
}

//���ӽ����ã����Խ���ͨ��ʱ����(�ͻ���)
void CIFRMView::OnConnectWinsock() 
{
    //���ӱ�־
	m_IsConnect      = TRUE;
}

//��������ʱ����
void CIFRMView::OnErrorWinsock(short Number, BSTR FAR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL FAR* CancelDisplay) 
{
	return;
}

//�ڷ��������ڼ����
void CIFRMView::OnSendProgressWinsock(long bytesSent, long bytesRemaining) 
{
	// TODO: Add your control notification handler code here
	
}

//�����һ�����Ͳ���ʱ���֡�
void CIFRMView::OnSendCompleteWinsock() 
{
	
}


//�����Ʒ�ʽ�����ַ���
//kinds           ����         0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP���� m_sendkind
//Str             �����ַ�
//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
//BOOL m_CheckReturnValue �Ƿ��ⷵ��ֵ,֤���յ���
BOOL CIFRMView::SelectSendString(int kinds, CString Str, BOOL CheckConnected,BOOL AppearPrompt,BOOL m_CheckReturnValue)
{	
	return TRUE;
	

	switch(kinds)
	{
	case 0://���ڷ���
		{
			
			//Ҫ���Ӻ���ܷ���
			if(CheckConnected)
			{
				
				if(m_Com.GetPortOpen())
				{
					
					//��פ���ڼ��פ������ʱ������Ϣ
					if(m_IsAutoSending && m_others)
					{
						
						//ֻ�д�Щ��Ϣ�ſ��Է���
						if(Str.Find("��Զ�̻��������ڶ���������ֵ���״̬��æ��") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("�����ذ����������Զ�̰�������(æ)���κ����ӽ��Ͽ���") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("�����ذ���ͨ���绰����Զ�̰�������(æ)���������ӶϿ���") == -1 )
						{
							return FALSE;
						}
						
					}
                    
					BYTE                     bits;
					int            m_length   = 0;  //����
					CString                  strs;
					//CRC����ֵ
					unsigned int  crc  =   0xffff;
					Str = Str.Mid(7,Str.GetLength() - 12);
					
					int Count   = Str.GetLength();
					
					//ɾ����������
					SendByteArray.RemoveAll();
					//��һλ������ʼ��־ 0x68
					SendByteArray.Add(0x68);
					//�ڶ�λ��������L���ֽ�
					SendByteArray.Add(0x00); 
					//����λ��������L���ֽ�
					SendByteArray.Add(0x00); 
					//����λ��, 0x68
					SendByteArray.Add(0x68);
					
					//�����鸳ֵ
					for(int i  = 0; i < Count; i ++)
					{
						//ÿ���ֽڵ�ֵ
						if(Str.GetAt(i) == ' ')
						{
							bits =  '*';
						}
						else
						{
							bits =  Str.GetAt(i);
						}
						
						SendByteArray.Add(bits);
						//����CRC����
                        crc = Crc16( crc , bits );            
						
					}
					
					//����,ǰ�ĸ���������
					m_length = SendByteArray.GetSize() - 4; 
					//����L���ֽ� 
					SendByteArray[1] = m_length%256;
					//����L���ֽ�
					SendByteArray[2] = m_length/256;; 
					//��CRC�����λ
					SendByteArray.Add(crc%256);	
					//��CRC�����λ
					SendByteArray.Add(crc/256);
					//��β��־
					SendByteArray.Add(0x16);
					
					SurrenderWindowMessage();
					//��������ʱ��
					m_Com.SetOutput(COleVariant(SendByteArray));
					m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��
					
					SurrenderWindowMessage();
					
					//����Ǵ������ݵĻ�,��Ҫ����ʱ
					if(Str.Find("COMMAND:26")== -1 && Str.Find("COMMAND:25")== -1 && Str.Find("DATAS:3:")== -1)
					{
						
						//�ӳ�ʱ��
						for(int iii = 0; iii <= 20; iii++)
						{
							SurrenderWindowMessage();
							Sleep(10);
							SurrenderWindowMessage();
						}
						
					}

					return TRUE;
					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("��Զ�̻�������ʧ�ܣ������Ӻ����ԣ�"," ",MB_OK|MB_ICONWARNING);
						//�ֿ��Խ���ָ��
						m_StartRead = FALSE;
					}
					
					return FALSE;
					
				}
				
				
			}
			else
			{	
				//�����Ʒ�ʽ����
				m_Com.SetOutput(COleVariant(Str));//��������,����ASCII�ַ�����
			//	m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��
			}

			break;
			
           
		}
	case 1://�绰�κŷ���
		{   
			if(CheckConnected)
			{

				//Ҫ���Ӻ���ܷ���
				if(m_Com.GetCDHolding())
				{
				
					//�����������PASS_TIMES��������
					if(m_PassErrortimes > PASS_TIMES)
					{
						return FALSE;
					}

					//��פ���ڼ��פ������ʱ������Ϣ
					if(m_IsAutoSending && m_others)
					{
						
						//ֻ�д�Щ��Ϣ�ſ��Է���
						if(Str.Find("��Զ�̻��������ڶ���������ֵ���״̬��æ��") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("�����ذ����������Զ�̰�������(æ)���κ����ӽ��Ͽ���") == -1 )
						{
							return FALSE;
						}
						
						if(Str.Find("�����ذ���ͨ���绰����Զ�̰�������(æ)���������ӶϿ���") == -1 )
						{
							return FALSE;
						}
						
					}
		
					BYTE                     bits;
					int            m_length   = 0;  //����
					CString                  strs;
					//CRC����ֵ
					unsigned int  crc  =   0xffff;
					Str = Str.Mid(7,Str.GetLength() - 12);
					
					int Count   = Str.GetLength();
            					
					//ɾ����������
					SendByteArray.RemoveAll();
					//��һλ������ʼ��־ 0x68
					SendByteArray.Add(0x68);
					//�ڶ�λ��������L���ֽ�
					SendByteArray.Add(0x00); 
					//����λ��������L���ֽ�
					SendByteArray.Add(0x00); 
					//����λ��, 0x68
					SendByteArray.Add(0x68);
					
					//�����鸳ֵ
					for(int i  = 0; i < Count; i ++)
					{
						//ÿ���ֽڵ�ֵ
						if(Str.GetAt(i) == ' ')
						{
							bits =  '*';
						}
						else
						{
							bits =  Str.GetAt(i);
						}
						
						SendByteArray.Add(bits);
						//����CRC����
                        crc = Crc16( crc , bits );            
						
					}
					
					//����,ǰ�ĸ���������
					m_length = SendByteArray.GetSize() - 4; 
					//����L���ֽ� 
					SendByteArray[1] = m_length%256;
					//����L���ֽ�
					SendByteArray[2] = m_length/256;; 
					//��CRC�����λ
					SendByteArray.Add(crc%256);	
					//��CRC�����λ
					SendByteArray.Add(crc/256);
					//��β��־
					SendByteArray.Add(0x16);
             
					for(int ii = 0 ; ii < 10; ii ++)
					{

						//��CTS�߼�CD��Ϊ�ߵ�ƽʱ�ſɷ��ͣ�������ȴ��� 
						if(m_Com.GetCTSHolding() &&  m_Com.GetCDHolding())
						{
							
							SurrenderWindowMessage();
							//��������ʱ��
							m_Com.SetOutput(COleVariant(SendByteArray));
						    m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��
							
							SurrenderWindowMessage();

							//����Ǵ������ݵĻ�,��Ҫ����ʱ
							if(Str.Find("COMMAND:26")== -1 && Str.Find("COMMAND:25")== -1 && Str.Find("DATAS:3:")== -1)
							{
								
								//�ӳ�ʱ��
								for(int iii = 0; iii <= 30; iii ++)
								{
									SurrenderWindowMessage();
									Sleep(10);
									SurrenderWindowMessage();
								}


							}

							//�ɹ�������������Ϊ0
							m_PassErrortimes = 0;

							return TRUE;

						}

						Sleep(100);
					
					}
					
					//����������
					m_PassErrortimes ++;
					
					StatusStr = "�������ݷ��ʹ���";
					SendMessage(WM_EVENT, 1, 0);

					return FALSE;
           					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("��Զ�̻�������ʧ�ܣ������Ӻ����ԣ�"," ",MB_OK|MB_ICONWARNING);
						//�ֿ��Խ���ָ��
						m_StartRead = FALSE;
					}
					
					return FALSE;
					
				}
				
				
			}
			else
			{	
				//�����Ʒ�ʽ����
				m_Com.SetOutput(COleVariant(Str));//��������,����ASCII�ַ�����
			//	m_Com.SetOutBufferCount(0);      //�建���������� 2005-10-11��
			}
			break;
		}
	case 2://TCP/IP����
		{   
			
			if(m_IsConnect)
			{

				//��פ���ڼ��פ������ʱ������Ϣ
				if(m_IsAutoSending && m_others)
				{
					
					//ֻ�д�Щ��Ϣ�ſ��Է���
					if(Str.Find("��Զ�̻��������ڶ���������ֵ���״̬��æ��") == -1 )
					{
						return FALSE;
					}
					
					if(Str.Find("�����ذ����������Զ�̰�������(æ)���κ����ӽ��Ͽ���") == -1 )
					{
						return FALSE;
					}
					
					if(Str.Find("�����ذ���ͨ���绰����Զ�̰�������(æ)���������ӶϿ���") == -1 )
					{
						return FALSE;
					}
					
				}
				
				//Ҫ���Ӻ���ܷ���
				m_WinSocket.SendData(COleVariant(Str));//�������� 
				SurrenderWindowMessage();//����window����Ȩ 
				
				//Ҫ��ʱʱ��
				if(m_CheckReturnValue)
				{			
					//��ʱ500����
					Sleep(200);	
				}
		        SurrenderWindowMessage();
			}
			else
			{
				
                if(AppearPrompt)
				{
					MessageBox("��Զ�̻�������ʧ�ܣ������Ӻ����ԣ�"," ",MB_OK|MB_ICONWARNING);
					//�ֿ��Խ���ָ��
					m_StartRead = FALSE;
				}
				return FALSE;
				
			}
			break;
		}
		
	}
	
	SurrenderWindowMessage();//����window����Ȩ
   
	return TRUE;
}

//�����Ʒ�ʽ����
//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
BOOL CIFRMView::SelectSendCByteArray(int kinds,BOOL CheckConnected,BOOL AppearPrompt)
{
	switch(kinds)
	{
	case 0://���ڷ���
		{
			if(CheckConnected)
			{
				//Ҫ���Ӻ���ܷ���
				if(m_Com.GetPortOpen())
				{
					
					m_Com.SetOutput(COleVariant(SendByteArray));
					
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("����û�д򿪣��������úô��ڲ�������!"," ",MB_OK|MB_ICONWARNING);
					}
					return FALSE;
					
				}
				
			}
			else
			{
				
				m_Com.SetOutput(COleVariant(SendByteArray));
				
			}
			break;
		}
	case 1://�绰�κŷ���
		{   
			if(CheckConnected)
			{
				
				//Ҫ���Ӻ���ܷ���
				if(m_Com.GetCDHolding())
				{	
					//if(m_IsDialConnectting)
					m_Com.SetOutput(COleVariant(SendByteArray));
						
				}
				else
				{
					
					if(AppearPrompt)
					{
						MessageBox("Զ������ʧ�ܣ��������Ӻñ��ض˺�Զ�̶�����!"," ",MB_OK|MB_ICONWARNING);
					}
					return FALSE;
				}
				
			}
			else
			{	
				
				m_Com.SetOutput(COleVariant(SendByteArray));
				
			}
			break;
		}
	case 2://TCP/IP����
		{   
			
			if(CheckConnected)
			{
				
				//���ӱ�־
	            if(m_IsConnect)
				{
				    //Ҫ���Ӻ���ܷ���
				    m_WinSocket.SendData(COleVariant(SendByteArray));//����������Ϣ
				}
				
			}
			else
			{
				
                if(AppearPrompt)
				{
					MessageBox("��������ʧ�ܣ��������Ӻ�����!"," ",MB_OK|MB_ICONWARNING);
				}
				return FALSE;
				
			}
			break;
		}
		
	}
	
	return TRUE;
	
}

//�볤ɳ��Զͨ������
void CIFRMView::AnalyseReceivedByteArray()
{
	
    //������������,�Ҽ�������
    if(!WipeOffSpilthData())
	{
		return;
	}
	
	//��0x10��ͷ��Ϊ�̶�֡��ʽ����Ϊ6
	switch(ReceiveByteArray[0])
	{
	case 0x10://����̶�֡��ʽ
		{   
			
			//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
			switch(ReceiveByteArray[1])
			{
		    case 0x48://��վ�ٻ��ն�ϵͳʱ��
				{
					
					//���ͻ�����Ϣ
					BYTE  SendByte[21];
					CString        STR;
					SendByte[19]   = 0;
					//ϵͳʱ�䴦��
					SYSTEMTIME   systime;
					::GetLocalTime(&systime);
					
					SendByte[0]  = 0x68;
					SendByte[1]  = 0x0F;
					SendByte[2]  = 0x00;
					SendByte[3]  = 0x68;
					SendByte[4]  = 0x88;
					SendByte[5]  = 0xFF;
					SendByte[6]  = 0x48;
					SendByte[7]  = 0x01; 
					SendByte[8]  = 0x05;
					SendByte[9]  = ReceiveByteArray[2];
					SendByte[10] = ReceiveByteArray[3];
					SendByte[11] = 0x30;
					
					SendByte[12] = systime.wYear%100;                  //��
					SendByte[13] = BYTE(systime.wMonth);               //��
					SendByte[14] = BYTE(systime.wDay);                 //��
					SendByte[15] = BYTE(systime.wHour);                //ʱ
					SendByte[16] = BYTE(systime.wMinute);              //��
					SendByte[17] = BYTE(systime.wSecond);              //��
					SendByte[18] = BYTE(systime.wMilliseconds/10);    //����
					STR.Format("%d��%d��%d��-%d:%d:%d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
				
					//ʱ��ת��BCD��
					int i;
					for( i = 12; i <= 18; i++)
					{
						SendByte[i] = SendByte[i]/10*16 + SendByte[i]%10;
					}
					
					SendByte[20] = 0x16;                               //������־
					//������ֵ
					SendByteArray.RemoveAll();
					
					for( i = 0; i < 21; i ++)
					{
						if(i >= 4 && i < 19)
						{
							//У����
							SendByte[19] = SendByte[19] + SendByte[i];
						}
						SendByteArray.Add(SendByte[i]);
						
					}
					
					//�����Ʒ�ʽ����
					//kinds           ����  0-���ڷ���  1-�绰�κŷ���  2-TCP/IP����m_sendkind
					//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
					//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
					SelectSendCByteArray(m_sendkind,TRUE,FALSE);
					status("��վ�ٻ��ն�ϵͳʱ�ӣ�" + STR);
					break;
				}
			case 0x49:
				{
					//�ظ��ٻ��ն˵�ǰһ֡������
					m_LocalAddress = m_LocalAddress - m_EveryUnit;
				
					if(m_LocalAddress < 0 )
					{
						m_LocalAddress = 0;
					} 

				    //CString Datatime  ����>��Datatime������
					//BYTE    Kinds     ����  0x11 ����  0x13������ѹ
					//int     Start     ��ʼλ
					//int     N         �ն����ݿ�ṹ��˲ʱ���ʵ�ѹ����
					if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
					{
						status("�ظ��ٻ��ն˵�ǰһ֡�����ݳɹ�!");
					}
					else
					{
                       status("�ظ��ٻ��ն˵�ǰһ֡������û���ҵ�!");
					}
					//��ǰ��¼λ��
					m_LocalAddress = m_LocalAddress + m_EveryUnit;
				
					break;
				}
			case 0x4A:
				{
					//��վ�ٻ��ն˵ĺ�������
					//CString Datatime  ����>��Datatime������
					//BYTE    Kinds     ����  0x11 ����  0x13������ѹ
					//int     Start     ��ʼλ
					//int     N         �ն����ݿ�ṹ��˲ʱ���ʵ�ѹ����
	                if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
					{
						status("��վ�ٻ��ն˵ĺ������ݳɹ�!");
					}
					else
					{
                       status("��վ�ٻ��ն˵ĺ�������û���ҵ�!");
					}					//��ǰ��¼λ��
					m_LocalAddress = m_LocalAddress + m_EveryUnit;
					break;
				}
				
			}
			//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
			//��0x10��ͷ��Ϊ�̶�֡��ʽ
			break;
		}
	case 0x68://����ɱ�֡��ʽ
		{
			
			
			switch(ReceiveByteArray[4])
			{
		    case 0x46://��վ�����ն�ϵͳʱ��
				 {
					 /********************************************************/
					 //�յ�����ΪBCD��,ת��ʮ���Ƶ���
					 SYSTEMTIME systime;
					 CString       strs;
					 systime.wYear          = ReceiveByteArray[12]/16*10 + ReceiveByteArray[12]%16 + 2000;//��
					 systime.wMonth         = ReceiveByteArray[13]/16*10 + ReceiveByteArray[13]%16;       //��
					 systime.wDayOfWeek     = 0;
					 systime.wDay           = ReceiveByteArray[14]/16*10 + ReceiveByteArray[14]%16;       //�� 
					 systime.wHour          = ReceiveByteArray[15]/16*10 + ReceiveByteArray[15]%16;       //ʱ
					 systime.wMinute        = ReceiveByteArray[16]/16*10 + ReceiveByteArray[16]%16;       //��
                     systime.wSecond        = ReceiveByteArray[17]/16*10 + ReceiveByteArray[17]%16;       //��
					 systime.wMilliseconds  = (ReceiveByteArray[18]/16*10 + ReceiveByteArray[18]%16)*100; //����
                   
					 if(::SetLocalTime(&systime))
					 {
						 strs.Format("��վ�����ն�ϵͳʱ�ӳɹ�: %d-%d-%d %d:%d:%d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
						 status(strs);
					     //���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
                         SendMessageToElectricOffice(0);
					 }
					 else
					 {
						 status("��վ�����ն�ϵͳʱ��ʧ��!");
						//WriteToLog("��վ�����ն�ϵͳʱ��ʧ��!");
					 }
					 break;
					 /********************************************************/
					 
				 }
			 case 0x4b://��վ�ٻ��ն˵�����
				 {   
					 CString      str;

				     //0x11Ϊ����  0x13Ϊ������ѹ
				     if(ReceiveByteArray[11] == 0x11 || ReceiveByteArray[11] == 0x13)
					 {
						
						 m_EveryUnit = ReceiveByteArray[12]/16*10 + ReceiveByteArray[12]%16;//��Ϣ�������
						 //����ʱ�� >�� �����ڵ�����
                         HuNanZhaoHuanTime.Format("%4d-%02d-%02d %02d:%02d:%02d",ReceiveByteArray[13]/16*10 +ReceiveByteArray[13]%16 + 2000,ReceiveByteArray[14]/16*10+ReceiveByteArray[14]%16,ReceiveByteArray[15]/16*10+ReceiveByteArray[15]%16,ReceiveByteArray[16]/16*10+ReceiveByteArray[16]%16,ReceiveByteArray[17]/16*10+ReceiveByteArray[17]%16,0);
						 HuNanZhaoHuanOrder  = ReceiveByteArray[11];
						 
						 //��ǰ���ͺ��λ��
						 m_LocalAddress     =          0;
						 //CString Datatime  ����>��Datatime������
						 //BYTE    Kinds     ����  0x11 ����  0x13������ѹ
						 //int     Start     ��ʼλ
						 //int     N         �ն����ݿ�ṹ��˲ʱ���ʵ�ѹ����
						 if(SendHunNanHexData(HuNanZhaoHuanTime,HuNanZhaoHuanOrder, m_LocalAddress, m_EveryUnit))
						 {
							 
							 if(ReceiveByteArray[11] == 0x11)
							 {
								 str.Format("��վ�ٷ�ʱ��������:ʱ��>=%s[%d��,�ɹ�]",HuNanZhaoHuanTime,m_EveryUnit);
							 }
							 else
							 {	
								 str.Format("��վ��˲ʱ������ѹ:ʱ��>=%s[%d��,�ɹ�]",HuNanZhaoHuanTime,m_EveryUnit);
							 }

						 }
						 else
						 {   
							 if(ReceiveByteArray[11] == 0x11)
							 {
								 str.Format("��վ�ٷ�ʱ����:ʱ��>=%s[%d��,û���ҵ�]",HuNanZhaoHuanTime,m_EveryUnit);
							 }
							 else
							 {	
								 str.Format("��վ��˲ʱ������ѹ:ʱ��>=%s[%d��,û���ҵ�]",HuNanZhaoHuanTime,m_EveryUnit);
							 }

						 }

						 status(str);
						 //��ǰλ��
						 m_LocalAddress = m_LocalAddress + m_EveryUnit;
						 
					 }
					 break;
					 
				 }  
			 case 0x4E://������֤
				 {
					 /*
                     if(ReceiveByteArray.GetSize() > 11)
					 {

						 if(ReceiveByteArray[11] == 0x70)
						 {
                              //���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					          SendMessageToElectricOffice(0);
							  status("������֤�ɹ�!");
						 }
						 else
						 {
						      //���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					          SendMessageToElectricOffice(1);
							  status("������֤ʧ��!");
						 }

					 }
					 else
					 {
						 //���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					     SendMessageToElectricOffice(1);
						 status("������֤ʧ��!");
					 }
					 */
					 //���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					 SendMessageToElectricOffice(0);
					 status("������֤�ɹ�!");
     				 break;
				 }
				 
				 
			 }
			 //��0x68��ͷ��Ϊ�ɱ�֡��ʽ
			 break;
			 
		  }
		  
    }
	
    //ɾ���ֽ�����
    ReceiveByteArray.RemoveAll();
	
}

LRESULT CIFRMView::OnEvent(WPARAM wParam, LPARAM lParam)
{
	
	switch(wParam)
	{
	case 1:
		{
			//��ʾ״̬��
			status(StatusStr);
			break;
		}
	case 2:
		{
			//��ʾ�б���
			WriteListHeading();		
			break;
			
		}
	case 3:
		{
			//��ʾ����
		   	m_Grid.InsertRow(_T(" "), -1);
			m_Grid.Invalidate(); 
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
			#ifndef _WIN32_WCE
			   dwTextStyle |= DT_END_ELLIPSIS;
			#endif
		
			for (int col = 0; col < m_Grid.GetColumnCount(); col++)
			{ 

				GV_ITEM  Item;
				Item.mask    = GVIF_TEXT|GVIF_FORMAT;
				Item.row     = m_Grid.GetRowCount() - 1;//m_ListRows;
				Item.col     = col;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%s",(m_StrArray[col]));
				m_Grid.SetItem(&Item);
			}

			m_Grid.SetModified(FALSE,-1,-1);
			m_Grid.Invalidate();
		//	m_Grid.Refresh();
		//	SurrenderWindowMessage();
			break;
		}
	case 4:
		{
			//������ӺõĻ�
			//SelectSendString(m_sendkind,SendContionStr,TRUE,FALSE,TRUE);
			break;
		}
	case 5:
		{
			//������ӺõĻ�
			//SelectSendString(m_sendkind,SendContionStr,TRUE,FALSE,FALSE); 
			break;
		}
	case 6:
		{
			//����DIALOGBAR
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);

			if(pMainFrm->m_wndMyDialogBar.IsWindowVisible())
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
			}
			m_DialogBarVisible     = FALSE;//TRUE;

			//���²���
			pMainFrm->RecalcLayout();
			break;
		}
	case 7:
		{
			//��ʾDIALOGBAR
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);

			if(!pMainFrm->m_wndMyDialogBar.IsWindowVisible())
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			}	
			
			//���²���
			pMainFrm->RecalcLayout();
			
			break;
		}
	case 8:
		{
			//��������߳�
			if(ReadMeterThread != NULL)
			{
				delete ReadMeterThread;
				ReadMeterThread = NULL;
			}
			break;
		}
	case 9:
		{
			//���²���
		    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			ASSERT_VALID(pMainFrm);
			pMainFrm->m_wndMyDialogBar.Treeinitialize();
			pMainFrm->RecalcLayout();
			break;
		}
	case 10:
		{
		    break;
		}
	case 11:
		{
            CString        StrSql;
			StrSql = "DELETE FROM TB_HALTTIME";
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql); //ɾ��פ��ʱ��
			StrSql.Format("INSERT INTO TB_HALTTIME(HALTTIME_TIME) VALUES ('%4d-%02d-%02d %02d:%02d:%02d')",m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql); //����פ��ʱ��
			break;
		}
	case 12:
		{
           	//ɾ�����е�����
			m_Grid.DeleteAllItems();
			m_Grid.ShowWindow(SW_SHOW);		
			
			//�Ƿ���ʾ��ʷ����
			m_IsHistory     =    FALSE;
			
			TRY { 
				m_Grid.SetFixedRowCount(1);
				m_Grid.SetRowCount(1);     //��
				m_Grid.SetColumnCount(13); //��
				//������ݺ��к�
				CStringArray m_StrArrays;
				short         m_wide[13];
				m_StrArrays.SetSize(13);
				m_StrArrays[0]  = "���";
				m_wide[0]       =  36;
				m_StrArrays[1]  = "��������";
				m_wide[1]       =  85;
				m_StrArrays[2]  = "�û�����";
				m_wide[2]       =  95;
				m_StrArrays[3]  = "�û����";
				m_wide[3]       =  60;
				m_StrArrays[4]  = "��ַ";
				m_wide[4]       =  125;
				m_StrArrays[5]  = "ģ���";
				m_wide[5]       =  60;
				m_StrArrays[6]  = "����";
				m_wide[6]       =  80;
				m_StrArrays[7]  = "��·����";
				m_wide[7]       =  60;
				m_StrArrays[8]  = "ĸ��-��-��-Э��";
				m_wide[8]       =  96;
				m_StrArrays[9]  = "��̨����";
				m_wide[9]       =  65;
				m_StrArrays[10]  = "����";
				m_wide[10]       =  60;
				m_StrArrays[11] = "����ֵ";
				m_wide[11]       =  75;
				m_StrArrays[12] = "ʱ��";
				m_wide[12]       =  115;
				
				DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
               #ifndef _WIN32_WCE
				dwTextStyle |= DT_END_ELLIPSIS;
               #endif
				
				for (int col = 0; col < m_Grid.GetColumnCount(); col++)
				{ 
					GV_ITEM Item;
					Item.mask = GVIF_TEXT|GVIF_FORMAT;
					Item.row = 0;
					Item.col = col;
					Item.nFormat = dwTextStyle;
					Item.strText.Format("%s",(m_StrArrays[col]));
					m_Grid.SetItem(&Item);
					m_Grid.SetColumnWidth(col,m_wide[col]); 
				}
				
				//ֻ��״̬
				m_Grid.SetModified(FALSE,-1,-1);
				//����
				m_Grid.m_title  = "";
				
				m_Grid.SetBkColor(RGB(255,255,255));
				
				m_Grid.Invalidate();
				m_Grid.Refresh();
			}
			CATCH (CMemoryException, e)
			{
				e->ReportError();
				e->Delete();
				return 0;
			}
			END_CATCH
	
			SurrenderWindowMessage();//����window����Ȩ
			break;
		}
	case 13:
		{
			CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			
			//������������
			if(m_saveyears < 1)
			{
				DealOverTimeData(1);
			}
			else
			{
				DealOverTimeData(m_saveyears);
			}
			
			pMainFrm->m_wndMyDialogBar.InitializeCombo();
			break;
		}
	case 14:
		{
			//���������״̬ʱ,ǿ���˳��߳�
			if(m_IsConnect || m_Com.GetCDHolding())
			{
				
				if(ReadMeterThread != NULL)
				{
					//��פ��ʱ�䵽��,���ԭ���ڶ�����˳�����
					m_StartRead    =   FALSE;
					//�ͷ�CPUʱ��
					SurrenderWindowMessage();
					Sleep(2000);
					//�ͷ�CPUʱ��
					SurrenderWindowMessage();
				}
				
			}
			
			//����߳�û������
			if(ReadMeterThread == NULL)
			{	
				//�޸İκŻ��Զ�����״̬
				ModifyDialInternetStatus();
				
			}
			break;
		}
	case 15:
		{
			//�����·������״̬,���ڱ�������־
			CheckLineRun();
			break;
		}
	case 16:
		{
		         
			DWORD            dwStatus;

			if(ReadMeterThread != NULL)
			{
				
				VERIFY(::GetExitCodeThread(ReadMeterThread->m_hThread,&dwStatus));
				
				if(dwStatus == STILL_ACTIVE)
				{
					//���Ϊ����״̬,����ֹ
					m_StartRead    =      FALSE;
					PostMessage(WM_EVENT,16, 0);
				}
				else
				{	
					//����Ѿ���ֹ,��ɾ�����߳�
					delete ReadMeterThread;
					ReadMeterThread = NULL;
				}				
				
			}

			break;
		}
	case 17:
		{
			//��������ģ�������ѹ
			CheckWireLess();
			break;
		}
	case 18:
		{
		    //�����޹�������������
            WuGongDeal("ALL");
			break;
		}
	case 19:
		{
		    //�����޹������������
           	m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 1, m_StrArray[1]);	
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 10, m_StrArray[10]);
			m_Grid.Invalidate();
			m_Grid.Refresh();	
			
			//ֻ��״̬
			m_Grid.SetModified(FALSE,-1,-1);
            break;
		}
	case 20:
		{
			//�õ���פ����Ϣ��ĸ�ߺ�Э������
			GetSendZhuLiuInformation();
			break;
		}
	}
	return 0;
	
}

//������������
BOOL CIFRMView::WipeOffSpilthData()
{
	//�����ַ�
	CString  Condtion,str;
	
	//���վ���
	int         StationNo;
	
	long Size         =  ReceiveByteArray.GetSize();
	
   //��0x10��ͷ��Ϊ�̶�֡��ʽ����Ϊ6
	switch(ReceiveByteArray[0])
	{
	case 0x10://����̶�֡��ʽ
		{   
			
			//���Ȳ��ԵĻ�
			if(ReceiveByteArray.GetSize() != 6)
			{
				//ɾ���ֽ�����
				ReceiveByteArray.RemoveAll();
				return  FALSE;
			}
			
			//���±��վ��
			LowAddress     =  ReceiveByteArray[2];
			HighAddress    =  ReceiveByteArray[3];
			
			//���վ���
			StationNo = ReceiveByteArray[2] + ReceiveByteArray[3] * 256;
			Condtion.Format("atoi(USER_STATIONNO)=%d",StationNo);
			
			//д����־
//			WriteToLog(Condtion);
			
			//�ж��ǲ��Ǳ�վ����Ϣ
			//	if(CDataBaseInstance::GetAllRecordsCount("TB_USER",Condtion) < 1)
			{
				
				//У��Ͳ��ԵĻ�
				if((ReceiveByteArray[1] + ReceiveByteArray[2] + ReceiveByteArray[3])%256 != ReceiveByteArray[4])
				{
					//���ͼ��������
					//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					SendMessageToElectricOffice(1);
					//ɾ���ֽ�����
					ReceiveByteArray.RemoveAll();
					return  FALSE;
				}
				
			}
			
			//��0x10��ͷ��Ϊ�̶�֡��ʽ
			break;
		}
	case 0x68://����ɱ�֡��ʽ
		{
			
			//����У����,����
			int length = ReceiveByteArray[1] + ReceiveByteArray[2] * 256;
			
			//���ȴ���Ļ�
            if( length + 6 != ReceiveByteArray.GetSize())
			{
				//ɾ���ֽ�����
				ReceiveByteArray.RemoveAll();
				return  FALSE;
				
			}
			
			//���±��վ��
			LowAddress     =   ReceiveByteArray[9];
			HighAddress    =  ReceiveByteArray[10];
			
			//���վ���
			StationNo = ReceiveByteArray[9] + ReceiveByteArray[10] * 256;
			Condtion.Format("atoi(USER_STATIONNO)=%d",StationNo);
			
			//д����־
//			WriteToLog(Condtion);
			
			//�ж��ǲ��Ǳ�վ����Ϣ
			//if(CDataBaseInstance::GetAllRecordsCount("TB_USER",Condtion) < 1)
			{
				//У����
				BYTE  CheckSum = 0;
				
				for(int i = 4; i < Size - 2; i++)
				{
                    CheckSum = CheckSum + ReceiveByteArray[i];
				}
				
				//У��Ͳ��ԵĻ�
				if(CheckSum != ReceiveByteArray[Size - 2])
				{
					
					//���ͼ��������
					//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
					SendMessageToElectricOffice(1);
					
					//ɾ���ֽ�����
					ReceiveByteArray.RemoveAll();
					return  FALSE;
					
				}
				
			}
			break;
			
		}
		
	}
	return TRUE;
}


//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
void CIFRMView::SendMessageToElectricOffice(short kinds)
{
	SendByteArray.RemoveAll();
	SendByteArray.Add(0x10);
	switch(kinds)
	{
	case 0:
		{  
			//�ɹ�ִ��
			SendByteArray.Add(0x8b);
			break;
		}
	case 1:
		{
			//�����벻��
			SendByteArray.Add(0x85);
			break;
		}
	case 2:
		{
			//������
			SendByteArray.Add(0x89);
			break;
		}
		
	}
	SendByteArray.Add(LowAddress); //��ַ
	SendByteArray.Add(HighAddress);//��ַ
	
	SendByteArray.Add((SendByteArray[1] + LowAddress + HighAddress)%256);//У����
	SendByteArray.Add(0x16);       //������־
	
	//�����Ʒ�ʽ����
	//kinds           ����  0-���ڷ���  1-�绰�κŷ���  2-TCP/IP����m_sendkind
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	SelectSendCByteArray(m_sendkind,TRUE,FALSE);
}


//CString  m_address 12λ��ַ
//short kinds     	//14�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10�������� 11������� 12���ȵ��� 13��ƽ���� 14-��������
float CIFRMView::ReadDataFrom485Com2(CString m_address,short kinds)
{
	
	//�����Ʒ�ʽ
	COleVariant            varInput; 
	long                     ix,l,u;
	BYTE                   TempByte;
	CString                StrValue;
	float        GetValue   =    -1;
    BOOL     m_StartAdd     = FALSE;
	StrValue.Format("%s",m_address);
	int Length = StrValue.GetLength();
	
	//�ڶ�����Ϊ�����ܱ��վ�ܱ�ר��485
	if(Ports[1] == FALSE || kinds == 1 || kinds == 3 || kinds > 15)
	{
		return -1;
	}
	
	//��ʾ�汾
	if(AppInfo::Instance().m_YanShi)
	{ 
		CTime time = CTime::GetCurrentTime();
		GetValue   = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01;//����
		Sleep(500);
		return  GetValue;
	}
	
	//��ַ���Ȳ���
	if(Length < 12)
	{

		for(int i = 0; i < 12 - Length; i ++)
		{
			StrValue = "0" + StrValue;
		}
	}
	
    SendByteArray.RemoveAll();
	//�Ի��ѽ��շ���������״̬
	SendByteArray.Add(0xFE);
	SendByteArray.Add(0xFE);
	
	//ָ�ʼ
	SendByteArray.Add(0x68);
	
	//��ַ����ǰ�����ں�
	int i;
	for( i = 0; i < 6; i++)
	{
		TempByte = atoi(StrValue.Right(2));
		SendByteArray.Add(TempByte/10*16 + TempByte%10);
		StrValue = StrValue.Left(StrValue.GetLength() - 2);
	}
	/*
	0x9010 -�����й� + 0x33 �ͣ�����
	9020   - �����й�
	9110   - �����޹�
	9120   - �����޹�
	B611   - A��ѹ  �����ֽ�
	B612   - B��ѹ
	B613   - C��ѹ
	B621   - A���� �����ֽ���λС��
	B622   - B����
	B623   - C����
	*/
	//�й�      FE FE 68 16 66 17 00 00 00 68 01 02 43 C3 6C 16
	//�޹�      FE FE 68 16 66 17 00 00 00 68 01 02 43 C4 6D 16
	//����:     68 AA AA AA AA AA AA 68 01 02 54 E9 0C 16 
	//�ص���Rx: 68 59 00 00 00 00 00 68 81 04 54 E9 33 33 51 16 
	//��ѹTx:   68 AA AA AA AA AA AA 68 01 02 44 E9 FC 16 
    //�ص���Rx: 68 59 00 00 00 00 00 68 81 04 44 E9 63 35 73 16 
	SendByteArray.Add(0x68);
	SendByteArray.Add(0x01);
	SendByteArray.Add(0x02);
	
	
	switch(kinds)
	{
	case 0:
		{   
			//0�������й� 
			SendByteArray.Add(0x43);
			SendByteArray.Add(0xC3);
			break;
		}
	case 2:
		{   
			//2�������޹� 
			SendByteArray.Add(0x43);
			SendByteArray.Add(0xC4);
			break;
		}
	case 4:
		{   
			/*
			B621   - A���� �����ֽ���λС��
			B622   - B����
			B623   - C����
			*/
			//4������A����� 
			SendByteArray.Add(0x54);
			SendByteArray.Add(0xE9);
			break;
		}	
	case 5:
		{   
			//5������B����� 
			SendByteArray.Add(0x55);
			SendByteArray.Add(0xE9);
			break;
		}	
	case 6:
		{   
			//6������C�����
			SendByteArray.Add(0x56);
			SendByteArray.Add(0xE9);
			break;
		}
	case 7:
		{   
		/*
		B611   - A��ѹ  �����ֽ�
		B612   - B��ѹ
		B613   - C��ѹ
			*/
			//7������A���ѹ
			SendByteArray.Add(0x44);
			SendByteArray.Add(0xE9);
			break;
		}
	case 8:
		{   
			//8������B���ѹ 
			SendByteArray.Add(0x45);
			SendByteArray.Add(0xE9);
			break;
		}
	case 9:
		{   
			//9������C���ѹ  
			SendByteArray.Add(0x46);
			SendByteArray.Add(0xE9);
			break;
		}
	case 10:
		{   
			//10��������  
			SendByteArray.Add(0x44);
			SendByteArray.Add(0xC3);
			break;
		}	
	case 11:
		{   
			//11��������  
			SendByteArray.Add(0x45);
			SendByteArray.Add(0xC3);
			break;
		}
	case 12:
		{   
			//12������ƽ  
			SendByteArray.Add(0x46);
			SendByteArray.Add(0xC3);
			break;
		}
	case 13:
		{   
			//13��������  
			SendByteArray.Add(0x47);
			SendByteArray.Add(0xC3);
			break;
		}
	case 14:
		{   
			//14��������������  
			SendByteArray.Add(0x83);
			SendByteArray.Add(0xE9);
			break;
		}
		
	}
	
	//������
	int Size    =  SendByteArray.GetSize();
	TempByte    =                        0;
	
	for( i = 2; i < Size; i ++)
	{
		TempByte = TempByte + SendByteArray[i];
	}
    SendByteArray.Add(TempByte);
	
	//������־
    SendByteArray.Add(0x16);
	
    Size    =  SendByteArray.GetSize();
	
	
	for( i = 0; i < Size; i ++)
	{
		StrValue.Format("SendByteArray[%d]=%0x",i,SendByteArray[i]);
		//	WriteToLog(StrValue);
	}
	
	
	//�����Ʒ�ʽ����
    m_485MsComm.SetOutput(COleVariant(SendByteArray));
	
	Sleep(600);
	
	ReceiveByteArray.RemoveAll();
	
	//ȡֵ����
	varInput = m_485MsComm.GetInput();
	
	if(varInput.parray != NULL) 
	{ 
		
		//�õ���ȫ�����Ͻ�
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//�õ���ȫ�����½�
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//�õ�����������ֵ
		for(ix = l; ix <= u; ix ++)
		{
			
			SafeArrayGetElement(varInput.parray,&ix,&TempByte);
			
			if(TempByte == 0x68)
			{
				m_StartAdd = TRUE;
			}
			
			if(m_StartAdd)
			{
				ReceiveByteArray.Add(TempByte);
			}
			//StrValue.Format("%0x",TempByte);
			//WriteToLog(StrValue);
			
		}
		
	}
	
	//��������ֵ
    Size    =  ReceiveByteArray.GetSize();
	if(Size > 0)
	{
        
		//��0x16��β��λ��
		for(ix = Size - 1; ix <= 0; ix--)
		{
			
			if(ReceiveByteArray[ix] == 0x16)
			{
				break;
			}
			
		}
		
		
		//������
		TempByte = 0;
		
		for(i = 0; i < Size - 2; i++)
		{
			TempByte = TempByte + ReceiveByteArray[i];
		}
		
		//�������ȵĻ�
		if(TempByte == ReceiveByteArray[Size - 2])
		{
			
			if(ix > 4)
			{
				if(kinds >= 4 && kinds <= 6)
				{
					//����
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16) + ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16) * 0.01);
				}
				else if(kinds >= 7 && kinds <= 9)
				{  
					//��ѹ	
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16)*100 +  ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16));
				}	
				else if(kinds == 14)
				{
					//��������
					GetValue = float(int(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16)*100 +  ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16))/10)*0.01;
				}
				else
				{
					//�й��޹�
					GetValue = float(((ReceiveByteArray[ix - 2] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 2] - 0x33)%16) * 10000 + ((ReceiveByteArray[ix - 3] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 3] - 0x33)%16) * 100 + ((ReceiveByteArray[ix - 4] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 4] - 0x33)%16) + ((ReceiveByteArray[ix - 5] - 0x33)/16 * 10 + (ReceiveByteArray[ix - 5] - 0x33)%16) * 0.01);
				}
			
			//	Beep(5000,400); 
			//	Beep(5000,400);	
				
			}
			
		}
		
	}
	
	/*
	//�رմ��ж˿�
	if(m_485MsComm.GetPortOpen()) //�򿪴���   
	{
	m_485MsComm.SetPortOpen(FALSE);
	}
	*/
	return GetValue;
}

//����ת���ɶ�Ӧ��ֵ����
BYTE CIFRMView::ConversionCurrentValue(BYTE Source)
{   
	
	BYTE GetValue    =   0;
	int Current[6]   = {20,30 ,40 ,50 ,60 ,70 };
	int DataValue[6] = {0xc8,0x12c,0x1a8,0x204,0x230,0x273};
	int i;
	//�������20A�Ļ�����������Ϊ0xc8
	for( i = 0; i < 6; i ++)
	{
		
		if(Source <= Current[i])
		{
			if(i == 0)
			{
                GetValue = BYTE(DataValue[0]/10);
			}
			else if(i == 5)
			{
				GetValue = BYTE(DataValue[5]/10);
			}
			else
			{
                GetValue = BYTE((DataValue[i-1] + (Source - Current[i-1])*1.00/(Current[i] - Current[i -1])*(DataValue[i]-DataValue[i-1]))/10);
			}
			break;
		}
		
	}
	
	if(i > 5)
	{
		GetValue = BYTE(DataValue[0]/10);
	}
	
	return GetValue;
}

//�յ���ֵת���ɶ�Ӧ�ĵ���ֵ
float CIFRMView::SwitchCurrentValue(float DeValue)
{
	float m_Current  =   0;
	int   Current[6] = {20 ,30 ,40 ,50 ,60 ,70 };
	int DataValue[6] = {0xc8,0x12c,0x1a8,0x204,0x230,0x273};
	int i ;
	for( i = 0; i < 6; i ++)
	{
		
		if(DeValue <= DataValue[i])
		{
			
			if(i == 0)
			{
                m_Current  = float(Current[0]);
			}
			else if(i == 5)
			{
				m_Current  = float(Current[5]);
			}
			else
			{
                m_Current  = float(Current[i-1] + (DeValue - DataValue[i-1])*1.00/(DataValue[i] - DataValue[i -1])*(Current[i]-Current[i-1]));
			}
			break;
			
		}
		
	}
	
	if(i > 5)
	{
		m_Current = float(Current[5]);
	}
	return m_Current;
}

//�õ���������Ϣ
void CIFRMView::GetHandModuleInformation()
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
			
			//�����ֱ���
			rs.GetFieldValue((short)0,strValue);
			m_handno = atoi(strValue);
            
			//�����ֵ�վ����
            rs.GetFieldValue((short)1,strValue);
			
			//�Ƿ�ʱ�����ź�
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

//����м����˿�����
void CIFRMView::GetComPorts()
{
	HANDLE				m_hComm;
    CString             ComStr;
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
		
		if (m_hComm == INVALID_HANDLE_VALUE)
		{
			Ports[i] = FALSE;
		}
		else
		{
			Ports[i] = TRUE;
			CloseHandle(m_hComm);
		}
		
	}
	
}

//���ö�ʱ������
void CIFRMView::SetTimersign()
{

	KillTimer(1);

	if(m_status)
	{

		//�����Զ�����״̬
		if(!m_IsAutoSending)
		{
			//����10����һ��
			SetTimer(1,m_SettimerValues,NULL);
    		OnTimer(1);
		}

	}
	else
	{

	    //�����Զ�����״̬
		if(!m_IsAutoSending)
		{
			//����10����һ��
			KillTimer(1);
   		}

	}

}


void CIFRMView::OnTimecheck() 
{ 
    //�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

    m_StartRead = TRUE;
	
	CTimeCheckDlg dlg;
	dlg.DoModal();

	m_StartRead = FALSE;
}

//����ʱ��
//��ʽ: ��-��-��-ʱ-��-��
void CIFRMView::SetLocalTimes(CString times)
{	
	
    //�������
	CString       str[6];
	int    colum     = 0;
	int    k         = 0;
	
	//ȥ�ո�
	times.TrimLeft();
	times.TrimRight();
	
	//��-Ϊ�ָ���
	while(times.Find('-') != -1)
	{
		k   =  times.Find('-');
		if(k != -1)
		{
            str[colum] =  times.Left(k);
			times  = times.Right(times.GetLength() - k - 1);
			
			if(colum > 4)
			{
				break;
			}
			colum++;
		}
	}
	
	//��
	str[5] = times;
	
	SYSTEMTIME systime;
	systime.wYear          = atoi(str[0]);      //��
	systime.wMonth         = atoi(str[1]);      //��
	systime.wDayOfWeek     =            0;
	systime.wDay           = atoi(str[2]);      //�� 
	systime.wHour          = atoi(str[3]);      //ʱ
	systime.wMinute        = atoi(str[4]);      //��
	systime.wSecond        = atoi(str[5]);      //��
	systime.wMilliseconds  = 700;               //����
	
	if(::SetLocalTime(&systime))
	{
		//AppInfo::Instance().m_WhichKind  -TRUE   ���վ�汾 -FALSE  ��ְ�
		if(AppInfo::Instance().m_WhichKind)
		{
			//������Ϣ
		//	SendContionStr = "BEGINS;MESSAGE:1:Զ������ʱ�����!;ENDS";
		//	SendMessage(WM_EVENT, 4, 0);
			return;
		}
		
	}
	
}

BOOL CIFRMView::SetRemoteTime(CString Str)
{
	//������ӺõĻ�
	return SelectSendString(m_sendkind,Str,TRUE,FALSE,TRUE);
}

void CIFRMView::KillAotoReadMeter()
{
	CString   ConStr;
	
	if(MessageBox("����ȡ����ʱ��פ��������","ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//���վ��
		if(AppInfo::Instance().m_WhichKind == TRUE)
		{

			//�ж���Ļ����˳�
			m_StartRead = FALSE;
			
			//���û��������
			if(!m_status)
			{
				KillTimer(1);
			}

			KillTimer(2);
			KillTimer(3);
		
			//�����������±������Ϊ0
			m_statusstr     =    "";
			status("                         ");
			m_IsAutoSending =    FALSE;
			SendContionStr  =    "BEGINS;MESSAGE:0:�Զ���פ���Զ�������ȡ��!;ENDS";
			SendMessage(WM_EVENT, 4, 0);
			status("���Զ���פ���Զ�������ȡ����");
			
			//д����־�ļ�
			CString str;
			//ʱ��
			CTime timet = CTime::GetCurrentTime();
			str.Format("��%4d-%02d-%02d %02d:%02d:%02d��ȡ������ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			WriteToLog(str);
			//��ʱ��ť��ΪFALSE
	        ShowDingShiButton(FALSE);
		
		}
		else
		{
		    
			//��ְ�
			ConStr = "BEGINS;DATAS:4:StopData;ֹͣ;ENDS";
			
			if(SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE) == TRUE)
			{	
				
				//״̬����Ϣȡ��
				m_StartRead      =   FALSE;	
				m_statusstr      =      "";
				status("                         ");
				m_IsAutoSending  = FALSE;
				Sleep(1000);
				//��ʱ��ť��ΪFALSE
				ShowDingShiButton(FALSE);
				
			}
		
			m_StartRead = FALSE;
			
			
		}
	
	}

}


//������ģʽ��������
void CIFRMView::BinarySystemReceive()
{

	BYTE                      bit; 
	COleVariant          varInput; 
	long                 ix,k,l,u; 
	short       Received     =  0; //�жν������ݵ�����	1 ��������Ľ��� 2������ϳ�ɳ����ͨѶ
	int i = 0, Size  = 0,m_length;
	CString                   str;
    //CRCֵ
    unsigned         crc = 0xffff;
	
	varInput  =  m_Com.GetInput();
	
	if(varInput.parray != NULL) 
	{ 
		
		//�õ���ȫ�����Ͻ�
		SafeArrayGetLBound(varInput.parray,1,&l);
		
		//�õ���ȫ�����½�
		SafeArrayGetUBound(varInput.parray,1,&u);
		
		//�õ�����������ֵ
		for(ix = l; ix <= u; ix ++)
		{
			
			SafeArrayGetElement(varInput.parray,&ix,&bit);
			
			//����window����Ȩ
			//SurrenderWindowMessage();
			
			//Ҫ���Ӻ���ܷ���	//������ӳɹ��˵Ļ�short  m_sendkind;// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_Com.GetCDHolding()
			if((m_Com.GetCDHolding() && m_sendkind == 1) || (m_Com.GetPortOpen() && m_sendkind == 0 ))//
			{
				
				ReceiveByteArray.Add(bit);
				
				//ĩλ0x16���,��������������Ƿ���������
				if(bit == 0x16)
				{	
					
					//�����Ƿ�������ȫ��������
					Size         =  ReceiveByteArray.GetSize();
					
					//����Ƿ��ж������
					for( i = 0; i < Size; i ++)
					{
						
						//��λ��0x68�ж�
						if(ReceiveByteArray[i] == 0x68)
						{
							
							//λ�����Ļ�
							if(Size - i > 3)
							{
								//����Ҫ��
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 7 == Size - i))
								{
									Received = 1; //�Ǳ�������غ�Զ��֮���ͨѶ
									break;
								}

                                //����Ҫ��
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 6 == Size - i))
								{
									Received = 2; //�Ǳ�����ͺ��ϳ�ɳ֮���ͨѶ
									break;
								}

							}
							//λ�����Ļ�
							
						}
						//��λ��0x68�ж�
						
						//��λ��0x10�ж�,���ͳɹ��ı�־
						if(ReceiveByteArray[i] == 0x10)
						{
							
							//λ�����Ļ�
							if(Size - i >= 5 )
							{
								
								//�յ�Զ�̻����´��ֹͣ��Ϣ
								if(ReceiveByteArray[i+1] == 0x8b && ReceiveByteArray[i+2] == 0x44 && ReceiveByteArray[i+3] == 0x44 && (ReceiveByteArray[i] + ReceiveByteArray[i+1] + ReceiveByteArray[i+2] + ReceiveByteArray[i+3])%256 == ReceiveByteArray[i+4] )
								{
                                	//�����ֽ����
									ReceiveByteArray.RemoveAll();
									m_StartRead = FALSE;
									
									//ֹͣ��ʱ����
									KillTimer(1);	
									//��ʾ�����ض���
			                        OperationAnimation(FALSE);
									return;
								}

								//�յ�������ʤ���ź�
								if((ReceiveByteArray[i+1] + ReceiveByteArray[i+2] + ReceiveByteArray[i+3])%256 == ReceiveByteArray[i+4] )//255
								{
								    Received        =          2; //�Ǳ�����ͺ��ϳ�ɳ֮���ͨѶ
									break;
								}
								
							}
							//λ�����Ļ�
							
						}
						//��λ��0x10�ж�,���ͳɹ��ı�־
						
					}
					//����Ƿ��ж������
					
					
				}
			
				//ĩλ0x16���,�����������Ƿ������������
				
			}
			else
			{
				//û�а�ͨʱ,���ֽ�ת��ΪCString�ͱ���
				char a = *(char*)(&bit);      
				str.Format("%c",a);	
				//��������ӳɹ�֮ǰ��ֵ
				StatusStr = StatusStr + str;
				status(StatusStr);
				//�����κŲ�������ʾ
				AnalyseDial(StatusStr); 
				
			}
		
		}
		//ȡ������
	}

	//���ݴ���������,������ָ��
	if(Received == 1) //�Ǳ�������غ�Զ��֮���ͨѶ
	{	
		//�ҳ�0x68��0x10��λ��
		if(i + 6 <= Size)
		{
			//ɾ��0x68ǰ��������ݣ�ǰ��λҲɾ������ʱ��������Ҫ�����ݡ�CRC�����λ��CRC�����λ����β0X16
			for( k = 0; k < i + 4; k ++)
			{
				
				ReceiveByteArray.RemoveAt(0,1);
			}
			
		}
	
		bit      =     0;

  	    m_length = ReceiveByteArray.GetSize();
		
		//�������ݼ����,��������֡���������ݡ�CRC�����λ��CRC�����λ����β0X16
		for( k = 0; k < m_length - 1 ; k ++)
		{	
			//����ʱ��
			//����CRC����
            crc = Crc16( crc , ReceiveByteArray[k]) ; 
		}
		
		//���crcֵ��Ϊ0�Ļ�
		if(crc != 0)
		{
			//��һ֡�Ǵ����
			ReceiveByteArray.RemoveAll();
			return;
		}
	
		//����������ȷ�Ļ�������ַ�
		m_strReceiveChar  = "";
		
		//ƴ���ַ�����ʽ
		for(ix = 0; ix < ReceiveByteArray.GetSize() - 3; ix ++)
		{
			
			bit = ReceiveByteArray[ix];
			
			
			//���ֽ�ת��ΪCString�ͱ��� 
			char a = *(char*)(&bit);       
            
			//�����*��,��ת�ɿո�
			if( a == '*')
			{
				str = " ";
			}
			else
			{
				str.Format("%c",a);
			}
		
			//�ۼ�ֵ 
			m_strReceiveChar += str;
			
		}
	  
		ReceiveByteArray.RemoveAll();

     	//��������,�Խ��յ���������Ҫ����
		m_strReceiveChar.TrimLeft();
		m_strReceiveChar.TrimRight();
		str   =     m_strReceiveChar;
		m_strReceiveChar    =     "";
        
		AnalyseOrder(str);

	}
	else if(Received  == 2)
	{
	
		//�Ǳ�����ͺ��ϳ�ɳ֮���ͨѶ
		//ɾ��0x68ǰ���������
		for( k = 0; k < i ; k ++)
		{
			ReceiveByteArray.RemoveAt(0,1);
		}
		
		//�볤ɳ��Զͨ������
        AnalyseReceivedByteArray();
	}

}


//������ʤ���ճ���
void CIFRMView::HuNanWeiYuanReceive()
{

	BYTE                    bit; 
	COleVariant        varInput; 
	long                 ix,l,u; 
	BOOL       Received	= FALSE;	
	
	//Ҫ���Ӻ���ܷ���
	if(m_Com.GetCDHolding() || m_Com.GetPortOpen())
	{
		
		varInput = m_Com.GetInput();
		
		if(varInput.parray != NULL) 
		{ 
		
			//�õ���ȫ�����Ͻ�
			SafeArrayGetLBound(varInput.parray,1,&l);
			
			//�õ���ȫ�����½�
			SafeArrayGetUBound(varInput.parray,1,&u);
			
			//�õ�����������ֵ
			for(ix = l; ix <= u; ix ++)
			{
				SafeArrayGetElement(varInput.parray,&ix,&bit);
				
				//���̫��Ļ���������ɾ���ֽ�����
				if(ReceiveByteArray.GetSize() > 65536)
				{
					ReceiveByteArray.RemoveAll();
					
				}
				
				ReceiveByteArray.Add(bit);
				
				//ĩλ0x16���,��������������Ƿ���������
				/***************************************/
				if(bit == 0x16)
				{	
					
					//�����Ƿ�������ȫ��������
					long Size         =  ReceiveByteArray.GetSize();
					
					//����Ƿ��ж������
					int i;
					for( i = 0; i < Size; i ++)
					{
						
						//��λ��0x68�ж�
						if(ReceiveByteArray[i] == 0x68)
						{
							
							//λ�����Ļ�
							if(Size - i >= 3)
							{
								//����Ҫ��
								if(ReceiveByteArray[i+3] == 0x68 && (ReceiveByteArray[i+1] + ReceiveByteArray[i+2]*256 + 6 == Size - i))
								{
									Received = TRUE;
									break;
								}
								
							}
							
						}
						
						//��λ��0x10�ж�
						if(ReceiveByteArray[i] == 0x10)
						{
							//��6λ���Ļ�
							if(Size - i == 6)
							{
								Received = TRUE;
								break;
							}
							
						}
						
					}
					
					
					//����������ϣ�
					if(Received)
					{
						//�ҳ�0x68��0x10��λ��
						if(i + 6 <= Size)
						{
							//ɾ��0x68��0x10ǰ���������
							for(int k = 0; k < i; k ++)
							{
								
								ReceiveByteArray.RemoveAt(0,1);
								
							}

							break;
						}
						
					}
					
					
				}
				/***************************************/
				//ĩλ0x16���,�����������Ƿ������������
				
			}
			
		}
		
		//���ݴ���������,������ָ��
		if(Received)
		{	
			AnalyseReceivedByteArray();
		}
		
	}
	else
	{
		//��ջ�����
		m_Com.GetInput();
	}
	
}

void CIFRMView::OnUpdateLstSave(CCmdUI* pCmdUI) 
{
   // pCmdUI->Enable(m_lists.IsWindowVisible() && m_lists.GetSelectedCount() > 0);
}


//0 --- ���ݲ�һ��  1------�����������  2
void CIFRMView::SendErrorMessage(short kinds)
{
	switch(kinds)
	{
	case 0:
		{	
			//��ʾ��Ϣ
            SendContionStr = "BEGINS;MESSAGE:0:���ȸ����������ݣ�����һ���ٲ���!;ENDS";
			break;
		}
	case 1:
		{
			//��ʾ��Ϣ
			SendContionStr = "BEGINS;MESSAGE:0:�����������,�������ٴ�!;ENDS";
			break;
		}
	case 2:
		{
			return;
    //      SendContionStr = "BEGINS;MESSAGE:1:���������ȷ������ִ�����ָ��!;ENDS";
			break;
		}
	}
	
	//���ͷ�����Ϣ
	SendMessage(WM_EVENT, 4, 0);

}

CString CIFRMView::GetStationNo()
{
	
	CDatabase            db;
	CString     Str = "";
	
	//��¼����
	long m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL");

	if(m_records <= 0)
	{
		return "";
	}

    //-USER_STATIONNO
	//�����ݿ�

	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset        rs(&db);
		Str = "SELECT USER_STATIONNO FROM TB_USER ORDER BY USER_STATIONNO";
		rs.Open(CRecordset::forwardOnly,Str);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,Str);

		//ȥ���ո�
        Str.TrimLeft();
		Str.TrimRight();

		//�ر����ݿ�
		rs.Close( );
		db.Close( );				
	}

	return Str;

}


//���������
void CIFRMView::OnAutoreadset() 
{ 
  

	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}	
	
	CString      ConStr,str;
	CAutoDateReadModuleDlg dlg;

	if(dlg.DoModal()== IDOK)
	{
		//���վ
		if(AppInfo::Instance().m_WhichKind)
		{
	
			//��ʱ��פ����ʱ����
			m_StartRead     =  TRUE;
			//�к���ʼΪ0
			m_ListRows      =     0;
			//����Ϊ0
			m_times         =     1;
			//��ʾ��Ϣ
			SendContionStr.Format("BEGINS;MESSAGE:0:Զ���Զ���פ���Զ����������óɹ�!\r\n%s;ENDS",m_statusstr);
			//���ͷ�����Ϣ
			SendMessage(WM_EVENT, 4, 0);

			//ִֹͣ�д˲���
			m_StartRead     = FALSE;
			//ʱ��
			CTime timet = CTime::GetCurrentTime();
			str.Format("��%4d-%02d-%02d %02d:%02d:%02d�����ö�ʱפ������:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
			WriteToLog(str);
		
			//ȡ��10���Ӽ��һ�μ��
			KillTimer(1);
			ShowDingShiButton(TRUE);//��ʱ��ť��ΪTRUE	
			
			m_IsAutoSending   =  TRUE;//פ��״̬��־
			
			//��ʼ������
            InitializeCurrent();

			StatusStr.Format("����%dʱפ��,�ȼ����Сʱ��%d��,������Сʱ��%d�Ρ�",m_parameter[104],m_parameter[106],m_parameter[108]);
			status(StatusStr);

			//Ϊ22Э��ӵģ���������ſ���, ��10�ı������ӿ���
			m_SettimerValues = ((10 - (timet.GetMinute()%10))*60 - timet.GetSecond())*1000;
			m_ReadModuleTimes   =     0;//���������Ϊ0
			//��פ������
	        m_SendGarrisonTimes =     0;	
			m_zhuliukinds       =     0;//0 �����������פ�� 1 ��������פ��
        	SetTimer(1,m_SettimerValues,NULL); //���ö�ʱ��,10���Ӽ��һ��
		}
		else
        { 
			
			ConStr  = "BEGINS;COMMAND:29:";
					 
			for(int i = 0; i < 110; i ++)
			{	
				//��ʼ����פ�������õ�110������
				str.Format("%d",m_parameter[i]);
				ConStr = ConStr + str + ";";
			}
			
			//��������
			ConStr = ConStr + "ENDS";
			
			if(SelectSendString(m_sendkind, ConStr,TRUE,TRUE,TRUE) == TRUE)
			{				
    			//��û�з�פ������
				m_IsAutoSending =  TRUE;
				//��ʱ��ť��ΪTRUE
	            ShowDingShiButton(TRUE);
			}
			
    		m_StartRead     = FALSE;

		}
		
	}
}

void CIFRMView::OnBREAkSOMEDAY() 
{
    //ȡ�����췢פ������
	KillAotoReadMeter();
}

void CIFRMView::OnUpdateOwemoney(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}


//�����û����ݿ�
void CIFRMView::OnPassuserdata() 
{
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

	BOOL  m_connectting = FALSE;

	switch(m_sendkind)
	{
	case 0:
		{
			m_connectting = m_Com.GetPortOpen();
			break;
		}
	case 1:	
		{
			m_connectting = m_Com.GetCDHolding();
			break;
		}
	case 2:	
		{
			m_connectting = m_IsConnect;
			break;
		}
	}

	if(m_connectting)
	{

		//�õ��Ի�������ѡ����
		if(!GetDialogBarStr())
		{
			return;
		}
	
		SurrenderWindowMessage();
		
		//�����û����ݴӵ��->���վ
		if(MessageBox("����Զ�̴������ݵ����վ��"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
		
			//�����վ�ĸ���
			if(!CheckStations(m_ModuleFindContionStr))
			{
				return;
			}
				
			m_StartRead =  TRUE;

			//������������ļ�¼
			CString m_filename,m_SqlStr;
			m_filename.Format("%s%s%s",GetFolder(),"TB_USER",".TXT");
			
			long fields = CDataBaseInstance::GetAllRecordsCount("TB_USER",m_ModuleFindContionStr);
			
			if(m_ModuleFindContionStr == "ALL")
			{
				m_SqlStr.Format("SELECT * FROM %s","TB_USER");
			}
			else
			{
				m_SqlStr.Format("SELECT * FROM %s WHERE %s","TB_USER",m_ModuleFindContionStr);
			}
			
			if(fields > 0)
			{
				
				//���߶Է��ж�������
				WriteDataToTextFile("TB_USER",m_SqlStr,fields,m_filename);
				
				//���߶Է�û������
				SendContionStr.Format("BEGINS;COMMAND:24:%s:%d;ENDS","TB_USER",fields);
				SendMessage(WM_EVENT, 4, 0);
			}
			else
			{
				m_StartRead = FALSE;
				MessageBox("�Բ��𣬴˱���û�������������������Ϣ!","����",MB_OK|MB_ICONWARNING);
				return;
			}
		}

	}
	else
	{
		MessageBox("�˿ڴ򿪴���!","",MB_OK|MB_ICONWARNING);
		return;
	}
	
}

BOOL CIFRMView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	
	if (wParam == (WPARAM)m_Grid.GetDlgCtrlID())
    {
        *pResult = 1;
        GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;
        if (GVN_GETDISPINFO  == pDispInfo->hdr.code)
        {
			SetGridItem(pDispInfo);
			return TRUE;
        }
    }
	
	return CFormView::OnNotify(wParam, lParam, pResult);
}

void CIFRMView::SetGridItem(GV_DISPINFO *pDispInfo)
{
	
	//m_pMapFile->SetGridText(pDispInfo);
	if((pDispInfo->item.col ==0) && (pDispInfo->item.row != 0))
	{
	  //pDispInfo->item.iImage = rand()%m_ImageList.GetImageCount();
		pDispInfo->item.mask  |= (GVIF_IMAGE);
	}

	if((pDispInfo->item.col == 6) && (atoi(pDispInfo->item.strText) > 2000))
	{
		COLORREF clr = RGB( 128, 128,  128);
		pDispInfo->item.crBkClr = clr;             // or - m_Grid.SetItemBkColour(row, col, clr);
		pDispInfo->item.crFgClr = RGB(255,0,0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
		pDispInfo->item.mask |= (GVIF_BKCLR|GVIF_FGCLR);
	}
	
}

//�õ��Ի�������ѡ����
BOOL CIFRMView::GetDialogBarStr()
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//�õ�ѡ����������
	m_ModuleFindContionStr = pMainFrm->m_wndMyDialogBar.SelectCondition();

	m_ModuleFindContionStr.TrimLeft();
	m_ModuleFindContionStr.TrimRight();
	
	if(m_ModuleFindContionStr.IsEmpty())
	{
		MessageBox("��ѡ�����ݷ�Χ,������!!"," ",MB_OK|MB_ICONWARNING);
		return  FALSE;
	}
	return TRUE;
}

void CIFRMView::OnUpdatePassuserdata(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}

void CIFRMView::OnUpdateShowdialogbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_DialogBarVisible == TRUE);
	pCmdUI->Enable(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") > 0);
}

void CIFRMView::OnUpdatePhasetest(CCmdUI* pCmdUI) 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//�õ�ѡ����������
   	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty()  && CRuntimeAccount::GetCurrentPrivilege() < 1);
	
}

void CIFRMView::OnUpdateTestreadtable(CCmdUI* pCmdUI) 
{	
	/*pCmdUI->Enable(FALSE);*/
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//ѡ������
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}
	
}

void CIFRMView::OnRclickListss(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_POPUP); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_lists.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
		pPopupMenu->EnableMenuItem(ID_LST_SAVE  , MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
		pPopupMenu->EnableMenuItem(ID_LST_SAVE  , MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);		
	*pResult = 0;
}


//���ؼ�����ˢ��һ��
void CIFRMView::RefreshTree()
{
	//���ؼ�����ˢ��һ��
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	//���û�м�¼
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL") <=  0)
	{
		pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
		pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
		m_DialogBarVisible = FALSE;

	}
	else
	{
	
		pMainFrm->m_wndMyDialogBar.Treeinitialize();
		
		//DIALOGBAR�Ƿ�ɼ�
		if(m_DialogBarVisible)
		{

			pMainFrm->m_wndMyDialogBar.ShowWindow(SW_SHOW);
			pMainFrm->m_wndMyDialogData.ShowWindow(SW_SHOW);
			pMainFrm->RecalcLayout(TRUE);

		}

	}

	//���²���
	pMainFrm->RecalcLayout();

}

void CIFRMView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);
	
}

void CIFRMView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	//�����Զ�פ���ڼ��ӡ
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);
}

void CIFRMView::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	//�����Զ�פ���ڼ��ӡ
	pCmdUI->Enable(m_Grid.IsWindowVisible() && !m_IsAutoSending);	
}


void CIFRMView::OnUpdateHidedata(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(m_lists.IsWindowVisible());	
}

void CIFRMView::OnSavereportas() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	char szFilter[]	=	"��Ƶ����Զ�̳���EXCEL�����ļ�(*.CSV)|*.CSV|";
   	CFileDialog dlg(FALSE,"CSV","*.CSV",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);

	dlg.m_ofn.lpstrTitle="����Ϊ:";
	
	if(dlg.DoModal() == IDOK)
	{
		//��Ƶ����Զ�̳������ļ�
		if(m_Grid.Save(dlg.GetPathName( ), ','/*���ݷָ���*/))
		{	
			//��û���޸�״̬
			m_Grid.SetModified(FALSE,-1,-1);
		}
		status("�ɹ��������...");
		
	}
	
}

void CIFRMView::OnUpdateSavereportas(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(m_Grid.GetRowCount() > 0 && m_Grid.IsWindowVisible());	
}

//�õ�EXE�ļ�Ŀ¼
CString CIFRMView::GetFolder()
{
	CString Folder,filename;
	char   ExeFilePath[256];               //�����ļ�·��������  
   
	strcpy(ExeFilePath,__argv[0]);         //��ȡ�ļ�·��
	filename = AfxGetApp()->m_pszExeName;  //��ȡEXE��������

	Folder = ExeFilePath;                  //�ļ�Ŀ¼
	Folder = Folder.Left(Folder.GetLength() - filename.GetLength() - 4);//ȥ�ļ���.EXE
	return Folder;
}


//�õ��ı��ļ�����
int CIFRMView::GetDataLines(CString FileName)
{
	char      s[300];
	FILE         *fp;
	int    lines = 0;
	if((fp=fopen(FileName,"r"))==NULL)
	{
		return  0;
	}
	else
	{
		while(!feof(fp))
		{
			fgets(s,300,fp);
			lines++;
		}
		fclose(fp);	
		return lines;
	}
}


//�õ��ı��ļ���*�е�����
CString CIFRMView::GetDataLineCString(CString FileName,int m_lines)
{
	CString  str = " ";	
	CFile         file;
	char        s[303];

	int          k = 0;

	if(file.Open(FileName,CFile::modeRead))
	{
		
		//һ��������150������
		if(file.GetLength() >= m_lines * 303 && file.GetLength()%303 == 0)
		{
			file.Seek((m_lines - 1)*303,CFile::begin);	
			file.Read(s,303);
			
			str  =  s;
			k    =  str.Find("\r\n");
		
			if(k != -1)
			{
				str = str.Left(k);
			}

		}
		file.Close();
	}	
	

	str.TrimLeft();
	str.TrimRight();
	return str;

}

//�����ظ����ݼ�¼
//CString  m_DataName   ����
//CString  TxtFileName  �����ı��ļ�
void CIFRMView::DealRepeatRecord(CString  m_DataName,CString TxtFileName)
{

	CString       m_DataNameTemp,SqlStr,Str;
    m_DataNameTemp     = m_DataName + "TMP";
	short   m_fileds   =                  0;

	//ɾ��ԭ�����е���ʱ��,����ɾ��ԭ������ʱ��
	//�жϱ��Ƿ����
	if(IsCurveTableExist(m_DataNameTemp))
	{
		SqlStr.Format("DROP TABLE %s",m_DataNameTemp);
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	}

	//������ʱ��
    SqlStr.Format("SELECT * INTO %s FROM %s ",m_DataNameTemp,m_DataName);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	if(m_DataName == "TB_USER")
	{
		//������û����ݿ�
		SqlStr.Format("DELETE FROM %s","TB_USERTMP");
		CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	}

	//�ı��ļ�������ʱ��
	SqlStr.Format("BULK INSERT IFRM..%s FROM '%s' WITH (DATAFILETYPE = 'char', FIELDTERMINATOR = ',', ROWTERMINATOR = '\n')",m_DataNameTemp,TxtFileName);
    CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	//����ʱ����ԭ��������
	if(m_DataName == "TB_USER")
	{
		
		//�ظ���¼д����־
		CDatabase     db;
		int   i    =   0;
		
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			CDaoDatabase* m_pDatabase = new CDaoDatabase();
			m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
			db.Close( );
			
			//��˾����ʼ
			CDaoRecordset m_CompanySet(m_pDatabase);
			m_CompanySet.Open(dbOpenSnapshot,_T("Select a.USER_LINENAME,a.USER_TRANSFORMERNO,a.USER_MODULENO FROM TB_USER AS a,TB_USERTMP AS b WHERE a.USER_MODULENO=b.USER_MODULENO"));
			
			//Ѱ�����������ļ�¼
			while (!m_CompanySet.IsEOF())
			{
				i ++;

				if(i == 1)
				{
					WriteToLog("----------------------�û���Ϣ��������ģ����ظ���ɾ��-----------------------");
					WriteToLog("    ���   ��·����                 ��̨��                             ģ���");
				}

				SqlStr.Format("%6d      %16.16s        %16.16s         %16.16s",i,(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0)),(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1)),(LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2)));
				WriteToLog(SqlStr);

				m_CompanySet.MoveNext();
			}
			m_CompanySet.Close();	
		
			if(i > 0)
			{
				 WriteToLog("---------------------------------------------------------------------------------");
			}
			
			delete m_pDatabase;
			m_pDatabase = NULL; 
	
		}

	 	//ɾ���ظ�������
		SqlStr.Format("DELETE TB_USER FROM TB_USER AS a,TB_USERTMP AS b WHERE a.USER_MODULENO=b.USER_MODULENO");
	}	
	else
	{
		//ɾ��ԭ��������
		SqlStr.Format("DELETE FROM %s",m_DataName);
	}

	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

	SqlStr.Format("INSERT %s SELECT DISTINCT * FROM %s",m_DataName,m_DataNameTemp);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);
	
	//ɾ����ʱ��
	SqlStr.Format("DROP TABLE %s",m_DataNameTemp);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);

}



void CIFRMView::OnUpdateRemotemodify(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
}

//CString m_CondtionString  ����Ҫ���������
//CString m_TableName       ����Ҫ����ı���
//int     Start             ��ʼλ��
BOOL CIFRMView::SendRemoteData(CString m_CondtionString, CString m_TableName, int Start)
{
	
	CString   strSql,strValue;
    long        fields   =  0;
	BYTE                 bits;
	int       m_length    = 0;//����
	unsigned int crc = 0xffff;//CRC����ֵ

	//�����ݿ�
	CDatabase             db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db);

		//���ʺ������ĸ���
		if(m_CondtionString == "ALL")
		{
		     strSql.Format("SELECT COUNT(*) FROM %s", m_TableName);
		}
		else
		{
			strSql.Format("SELECT COUNT(*) FROM %s WHERE %s", m_TableName,m_CondtionString);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		//��¼����
		fields = atol(strValue);   
		rs.Close();
		
		if(fields < 1 || Start >= fields || Start < 0)
		{	
			//�ر����ݿ�
			db.Close( );

			//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
            SendMessageToElectricOffice(2);
			strSql.Format("%s���������ݿ�ȡ...",m_TableName);
			status(strSql);
			return  FALSE;
		}
		
    	//���ʺ������ĸ���
		if(m_CondtionString == "ALL")
		{
		     strSql.Format("SELECT * FROM %s", m_TableName);
		}
		else
		{
			strSql.Format("SELECT * FROM %s WHERE %s", m_TableName,m_CondtionString);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();

	//	status("������ȡ��Ӧ�ļ�¼�����Ժ�...");
	//	ShowProgressCtrl(TRUE);
	//	SetProgressCtrlRange(0, fields,1);
		
		//�Ƶ���һ����¼
		rs.MoveFirst();

		rs.Move(Start, SQL_FETCH_ABSOLUTE);
        
		strSql = "";
		
		//�ֶ���
		int i;
		for( i = 0; i < nFields; i++)
		{
			rs.GetFieldValue(int(i),strValue);
			strValue.TrimRight();

			if(i == nFields  - 1)
			{
				strSql = strSql + strValue;
			}
			else
			{
				strSql = strSql + strValue + ",";
			}
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
		
		int Count   = strSql.GetLength();

		//ɾ����������
		SendByteArray.RemoveAll();
		//��һλ������ʼ��־ 0x68
		SendByteArray.Add(0x68);
		//�ڶ�λ��������L���ֽ�
		SendByteArray.Add(0x00); 
        //����λ��������L���ֽ�
		SendByteArray.Add(0x00); 
		//����λ��, 0x68
		SendByteArray.Add(0x68);
					
		//�����鸳ֵ
		for( i  = 0; i < Count; i ++)
		{
			//ÿ���ֽڵ�ֵ
			if(strSql.GetAt(i) == ' ')
			{
				bits =  '*';
			}
			else
			{
				bits =  strSql.GetAt(i);
			}
		
			SendByteArray.Add(bits);
			
			//����CRC����
            crc = Crc16( crc , bits );            
		}
		
		//����,ǰ�ĸ���������
		m_length = SendByteArray.GetSize() - 4; 
		//����L���ֽ� 
		SendByteArray[1] = m_length%256;
     	//����L���ֽ�
		SendByteArray[2] = m_length/256;; 
     	//��CRC�����λ
		SendByteArray.Add(crc%256);	
	    //��CRC�����λ
		SendByteArray.Add(crc/256);
		//��β��־
		SendByteArray.Add(0x16);
		//��������ʱ��
		m_Com.SetOutput(COleVariant(SendByteArray));
		strSql.Format("Զ����ȡ���ر�%s��%d����¼�ɹ�...",m_TableName,Start);
		status(strSql);
	//	ShowProgressCtrl(FALSE);
	}
	return   TRUE;
}

//CString Datatime  ����>��Datatime������
//BYTE    Kinds     ����  0x11 ��ʱ����  0x13������ѹ
//int     Start     ��ʼλ
//int     N         �ն����ݿ�ṹ��˲ʱ���ʵ�ѹ�������ݽṹ�����
BOOL CIFRMView::SendHunNanHexData(CString Datatime, BYTE Kinds, int Start, int N)
{ 
	
	CString           strSql;
	CString         strValue;
    long        fields  =  0;
	BYTE               bytes;
	CString    DataAppear[9];     
	
	//�����ݿ�
	CDatabase             db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		Datatime.TrimLeft();
		Datatime.TrimRight();
		//��CRecordset����
		CRecordset rs(&db);
		//���ʺ������ĸ���
		strSql = "SELECT COUNT(*) FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISON.GARRISON_HALTTIME >= '" + Datatime + "'";
		rs.Open(CRecordset::forwardOnly,strSql);
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		//��¼����
		fields = atol(strValue);   
		rs.Close();
		
		if(Kinds == 0x11)
		{   
			//������ʱ����
			ShowGridHead("ģ�����,160;ʱ��,160;�й�,160;�޹�,160;ģ���,160;");
		}
        else if(Kinds == 0x13)
		{  
			//0x13˲ʱ������ѹ
			ShowGridHead("ģ�����,120;ʱ��,120;A�����,70;B�����,70;C�����,70;A���ѹ,70;B���ѹ,70;C���ѹ,70;ģ���,160;");
		}

		if(fields < 1 || Start >= fields)
		{	
			//�ر����ݿ�
			db.Close( );
			//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
            SendMessageToElectricOffice(2);
			return  FALSE; 
		}
		
		//���͵��ֽ���0
		SendByteArray.RemoveAll();
		
		//ģ����롢פ��ʱ�䡢�й����޹���A�������B�������C�������A���ѹ��B���ѹ��C���ѹ��ģ���
		strSql = "SELECT TB_USER.USER_IDNO,TB_GARRISON.GARRISON_HALTTIME,TB_GARRISON.GARRISON_WORKDEGREE,TB_GARRISON.GARRISON_LOSEDEGREE,TB_GARRISON.GARRISON_ACURRENT,TB_GARRISON.GARRISON_BCURRENT,TB_GARRISON.GARRISON_CCURRENT,TB_GARRISON.GARRISON_AVOLTAGE,TB_GARRISON.GARRISON_BVOLTAGE,TB_GARRISON.GARRISON_CVOLTAGE,TB_USER.USER_MODULENO FROM TB_GARRISON,TB_USER WHERE TB_GARRISON.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISON.GARRISON_HALTTIME >= '" + Datatime + "' ORDER BY TB_GARRISON.GARRISON_MODULENO";
		rs.Open(CRecordset::forwardOnly,strSql);
		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();
		status("������ȡ��Ӧ�ļ�¼�����Ժ�...");
		ShowProgressCtrl(TRUE);
		SetProgressCtrlRange(0, fields,1);
		
		//���������ֽ�
		SendByteArray.Add(0x68);  //��ʼ��־
      
		if(Kinds == 0x11)
		{   
			//������ʱ����
			SendByteArray.Add((8+N*(9+80))%256);//���ȵĵ��ֽ�λ//255
			SendByteArray.Add((8+N*(9+80))/256);//���ȵĸ��ֽ�λ//255
		}
        else if(Kinds == 0x13)
		{  
			//0x13˲ʱ������ѹ
			SendByteArray.Add((8+N*(9+40))%256);//���ȵĵ��ֽ�λ//255
			SendByteArray.Add((8+N*(9+40))/256);//���ȵĸ��ֽ�λ//255
		}
		
		SurrenderWindowMessage();//����window����Ȩ

        SendByteArray.Add(0x68);            //�м��ֽ�
        SendByteArray.Add(0x88);            //�м��ֽ�
        SendByteArray.Add(0xff);            //�м��ֽ�
        SendByteArray.Add(0x01);            //�м��ֽ�
        SendByteArray.Add(N);               //���ݽṹ����
        SendByteArray.Add(0x05);            //�м��ֽ�
        SendByteArray.Add(0x00);            //�ն˵͵�ַ
        SendByteArray.Add(0x00);            //�ն˸ߵ�ַ
        SendByteArray.Add(Kinds);           //�ؼ���0x11 ��0x13
		
		//���û���Ϣ
		for(int j = 0;j < fields; j ++)
		{
			
			if(j >= Start && j < Start + N)
			{
				
				SendByteArray.Add(0xA1);//��Ч��־	
				
				//�ֶ���
				for(int i = 0; i < nFields; i++)
				{
					rs.GetFieldValue(int(i),strValue);
					strValue.TrimRight();
					//0x11 ����  0x13������ѹ
					switch(i)
					{
					case 0:
						{
							//ģ�����,2���ֽ�
							DataAppear[0] = strValue;

							//add 2004.9.17
							bytes =  atoi(strValue)%100;
							bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
							SendByteArray.Add(bytes);
	                        bytes =  atoi(strValue)/100;
							bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
							SendByteArray.Add(bytes);
							break;
						}
					case 1:
						{  
							//פ��ʱ�䣬6���ֽ�
							//2004- 1- 1 16: 0: 0
							DataAppear[1] = strValue;
							int k = strValue.Find('-');
							if(k != -1)
							{
								//��
								bytes = atoi(strValue.Left(k)) - 2000;
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //������
								
								//��
								k = strValue.Find('-');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								strValue.TrimLeft();
								strValue.TrimRight();
								SendByteArray.Add(bytes);        //������
								
								//��
								k = strValue.Find(' ');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //������
								
								//ʱ
								k = strValue.Find(':');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //����ʱ
								
								//��
								k = strValue.Find(':');
								bytes = atoi(strValue.Left(k));
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								strValue  = strValue.Right(strValue.GetLength() - k - 1);
								SendByteArray.Add(bytes);        //�����
								
								//��
								bytes = atoi(strValue);
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //������
								
							}
							break;
						}
					case 2:
						{
							//������ʱ����
							if(Kinds == 0x11)
							{
								DataAppear[2].Format(" %.2f",atof(strValue));
								//�й�,4���ֽڣ��ӵ͵���,��ת��BCD��
								long DataValue = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�
								
								bytes        = (DataValue%1000000)/10000;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //���������ֽ�
								
								bytes       = (DataValue%100000000)/1000000;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //���������ֽ�
							}
							break;
						}
					case 3:
						{
							//������ʱ����
							if(Kinds == 0x11)
							{   
								DataAppear[3].Format(" %.2f",atof(strValue));

                                //�޹�,4���ֽ�,��ת��BCD��
								//ǰ��4���������й��塢�����й�ƽ�������й��ȡ������й���� 4*4=16�ֽ�Ϊ0
								for(int jjj = 0; jjj < 16; jjj ++)
								{
									SendByteArray.Add(0x00);        //��16�����ֽ�
								}
								
								//�й�,4���ֽڣ��ӵ͵���,��ת��BCD��
								long DataValue = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�
								
								bytes        = (DataValue%1000000)/10000;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //���������ֽ�
								
								bytes       = (DataValue%100000000)/1000000;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //���������ֽ�
								
								//����14����������޹��ܡ������޹����14����Ϊ���ֽ� 4*14=56�ֽ�Ϊ0
								for( int jjj = 0; jjj < 56; jjj ++)
								{
									SendByteArray.Add(0x00);        //��16�����ֽ�
								}
							}		
							break;
						}
					case 4:
						{
							//0x13˲ʱ������ѹ 
							if(Kinds == 0x13)
							{  
								DataAppear[2].Format(" %.2f",atof(strValue));

								//ǰ��12�����й����ʡ�A���й����ʡ�B���й����ʡ�C���й����ʵ�12��Ϊ�� ���ֽ���Ϊ40��12��28��
								for(int jjj = 0; jjj < 28; jjj ++)
								{
									SendByteArray.Add(0x00);        //��28�����ֽ�
								}
								
								//A�����
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�
							}
							break;
						}
					case 5:
						{
							//0x13˲ʱ������ѹ
							if(Kinds == 0x13)
							{  
								
								DataAppear[3].Format(" %.2f",atof(strValue));
								//B�����
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�

							}
							break;
						}
					case 6:
						{   
							//0x13˲ʱ������ѹ
							if(Kinds == 0x13)
							{  
								
								DataAppear[4].Format(" %.2f",atof(strValue));
								//C�����
								long DataValue  = long(atof(strValue)*100+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�

							}
							break;
						} 
					case 7:
						{
							
							//0x13˲ʱ������ѹ
							if(Kinds == 0x13)
							{  
								DataAppear[5].Format(" %.1f",atof(strValue));//.2f
								//A���ѹ
								long DataValue  = long(atof(strValue)*10+0.5);//*10  
								bytes           =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�
							}
							break;
						}
					case 8:
						{
							//0x13˲ʱ������ѹ
							if(Kinds == 0x13)
							{  
								
								DataAppear[6].Format(" %.1f",atof(strValue));
								//B���ѹ
								long DataValue  = long(atof(strValue)*10+0.5);
								bytes           =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�

							}
							break;
						}
					case 9:
						{
							//0x13˲ʱ������ѹ
							if(Kinds == 0x13)
							{ 
								DataAppear[7].Format(" %.1f",atof(strValue));

								//C���ѹ
								long DataValue  = long(atof(strValue)*10+0.5);
								bytes        =  DataValue%100;
                                bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //��һ�����ֽ�
								
								bytes        = (DataValue%10000)/100;
								bytes = (bytes/10)*16 + bytes%10;//ת��BCD��
								SendByteArray.Add(bytes);        //�ڶ������ֽ�
							}
							break;
						}
					case 10:
						{
							//ģ���
							if(Kinds == 0x11)
							{ 
								DataAppear[4]  = strValue;
                            }
							else if(Kinds == 0x13)
							{
                                DataAppear[8]  = strValue;
							}
							break;
						}
						
				   }
				   
			 }

			 //��ʾ�б�����
			 if(Kinds == 0x11)
			 {   
				 //������ʱ����
				 AddlistItem(DataAppear, 5);
			 }
			 else if(Kinds == 0x13)
			 {	
				 //˲ʱ������ѹ
				 AddlistItem(DataAppear, 9);
			 }
			 
		  }
		
		  //��ʾ��Ϣ
		  strValue.Format("������ȡ���ݼ�¼,���%.2f��,���Ժ�...",float(j)*100/fields);
		  status(strValue);
		  //��¼�»�
		  SetProgressCtrlSetIt();
		  //�û����»�һ����¼
		  rs.MoveNext();

		  if(j > Start + N)
		  {
		     break;
		  }
	
		}
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
      
		/*
		//�Ƿ���,����������
		if(Start + N - fields > 0)
		{
			
			for(int ll = 0; ll < Start + N - fields; ll ++)
			{
				
				SendByteArray.Add(0xE1);//��Ч����

				//0x11    ����
				if(Kinds == 0x11)
				{
					for(int jjj = 0 ; jjj < 88; jjj ++)
					{
						SendByteArray.Add(0x00);//��Ч����
					}

				} 
				
				//0x13˲ʱ������ѹ
				if(Kinds == 0x13)
				{
                   	for(int jjj = 0 ; jjj < 48; jjj ++)
					{
						SendByteArray.Add(0x00);//��Ч����
					}

				}

			}

		}
		*/

		//add 2004.9.17
		if(Start + N - fields > 0)
		{
			
			if(Kinds == 0x11)
			{   
				//������ʱ����
				SendByteArray[1] = ((8+(fields-Start)*(9+80))%256);//���ȵĵ��ֽ�λ//255
				SendByteArray[2] = ((8+(fields-Start)*(9+80))/256);//���ȵĸ��ֽ�λ//255
		        SendByteArray[7] =  fields-Start;
			}
			else if(Kinds == 0x13)
			{  
				//0x13˲ʱ������ѹ
				SendByteArray[1] = ((8+(fields-Start)*(9+40))%256);//���ȵĵ��ֽ�λ//255
				SendByteArray[2] = ((8+(fields-Start)*(9+40))/256);//���ȵĸ��ֽ�λ//255
				//���ݽṹ��
				SendByteArray[7] =  fields-Start;
			}

		}
		//add 2004.9.17
    
		bytes = 0;

		//������
		for(int jjj = 0; jjj < SendByteArray.GetSize(); jjj ++)
		{
			if( jjj >= 4)
			{
			  
				bytes  = (bytes + SendByteArray[jjj])%256;//255

			}
		}
		
		SendByteArray.Add(bytes);//������
		SendByteArray.Add(0x16); //������
        SelectSendCByteArray(m_sendkind,TRUE,FALSE);//��������
		SendByteArray.RemoveAll();

	}
	status("                            ");
	ShowProgressCtrl(FALSE);
	return   TRUE;
}

//����ʤ����ȡ��ԭʼ������
void CIFRMView::GetPriveteDataFromWs(CString  m_CsvFileName)
{

    CString                SqlStr,Strs;
	
	//��ʾ״̬����Ϣ
	StatusStr = "���ڸ���ԭʼ�׿�����ݣ����Ե�...";
	SendMessage(WM_EVENT, 1, 0);

	//ɾ����ʤ��ʱ������
	CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USERTEMPWS");

	//���ı��ļ�������ʤ����
	SqlStr.Format("BULK INSERT IFRM..TB_USERTEMPWS FROM '%s' WITH (DATAFILETYPE = 'char', FIELDTERMINATOR = ',', ROWTERMINATOR = '\n')",m_CsvFileName);
	CDataBaseInstance::ExecuteDataBaseSQL(SqlStr);	

	
	//����з�Χ�Ļ�,ɾ�����ڴ˷�Χ������,
	if(CDataBaseInstance::GetAllRecordsCount("TB_MANAGERANGE","ALL") > 0)
	{
	   CDataBaseInstance::ExecuteDataBaseSQL("DELETE TB_USERTEMPWS WHERE USER_MANAGENO NOT IN (SELECT USER_MANAGENO FROM TB_MANAGERANGE)");
	}
	
	//������¼ӵĶ���
	if(CDataBaseInstance::GetAllRecordsCount("TB_USERTEMPWS","ALL") > 0)
	{
		//������ʤ�Ŀ�,ͳһ����
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USERTEMPWS SET USER_AMMETERNO=LEFT(USER_AMMETERNO,14)");
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USERTEMPWS SET USER_TRANSFORMERNO=REPLACE(USER_TRANSFORMERNO,'��̨����','')");//ȥ�ַ�����̨������
		//ɾ���û�����е�����
		CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USER");
		//����ʤ����ȡ����
		//����з�Χ�Ļ�
		CDataBaseInstance::ExecuteDataBaseSQL("INSERT TB_USER(USER_STATIONNO,USER_STATIONNAME,USER_MOTHERLINE,USER_LINENO,USER_LINENAME,USER_TRANSFORMERNO,USER_AMMETERNO,USER_MODULENO,USER_SUPPLYMODE,USER_IDNO,USER_MULTIPLE,USER_SENDANGLE,USER_PROTOCOL) SELECT DISTINCT USER_STATIONNO,USER_STATIONNAME,USER_MOTHERLINE,USER_LINENO,USER_LINENAME,USER_TRANSFORMERNO,USER_AMMETERNO,USER_MODULENO,USER_SUPPLYMODE,USER_IDNO,USER_MULTIPLE,USER_SENDANGLE,USER_PROTOCOL FROM TB_USERTEMPWS");
		//������ּ�������,��𲻶�
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USER SET USER_COMPANY='��ͷ�����',USER_PHASE=3,USER_AMMETERKIND=2,USER_INITIALVALUE=0.00 WHERE USER_COMPANY IS NULL");
		//����̨����Ϊ��
		CDataBaseInstance::ExecuteDataBaseSQL("Update TB_USER SET USER_TRANSFORMERNO='ĩ������̨' WHERE ltrim(RTrim(USER_TRANSFORMERNO))='<null>'");
	
	}

   //ɾ����ʤ��ʱ������
	CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_USERTEMPWS");
    
	//�������ؼ�
	SendMessage(WM_EVENT, 9, 0);
  
	//��ʾ״̬����Ϣ
	StatusStr = "����ԭʼ�׿��������...";
	SendMessage(WM_EVENT, 1, 0);
}

void CIFRMView::ReplaceUserModuleID(int startNo)
{	
	//�õ���¼����
	long fields = CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL"); 
				
	//���û����������������,����
	if(fields <= 0)
	{					
		return;
	}
	
	//�����ݿ�
	CDatabase          db;
	CString        strSql;
	CString      strValue;	
	CString     fieldname;

    if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
    
		strSql = "SELECT USER_MODULENO FROM TB_USER";

		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j++)
		{
           
			rs.GetFieldValue((short)0,strValue);

	     	strSql.Format("Update TB_USER SET USER_IDNO=%d WHERE  USER_MODULENO=%d",startNo + j,atol(strValue));
			CDataBaseInstance::ExecuteDataBaseSQL(strSql);
			//���»�һ����¼
			rs.MoveNext();
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}


}


//�ӷ�������ȡ����
void CIFRMView::GetDataFormMarketServer(CString m_address, CString m_loginname, CString m_password,CString m_StrFileName,int m_port)
{

	CInternetSession           ses;	
	CString   str,FileName,strtime;
	FILETIME       RemoteLastWrite;
    SYSTEMTIME          systemTime;
	
	//�û���
	m_loginname.TrimLeft();
    m_loginname.TrimRight();
    
	//����
	m_password.TrimLeft();
    m_password.TrimRight();

	//��������ַ
    m_address.TrimLeft();
    m_address.TrimRight();

	CFtpConnection* pFTP;
	try
	{
		//��ʾ״̬����Ϣ
		StatusStr = "������ȡ����������...";
		SendMessage(WM_EVENT, 1, 0);
	
		//���û���������
		pFTP = ses.GetFtpConnection(m_address,m_loginname,m_password,m_port,FALSE);
		

		if (pFTP) 
		{	
			//��ʾ״̬����Ϣ
		    StatusStr = "���������ӳɹ�...";
		    SendMessage(WM_EVENT, 1, 0);

			CFtpFileFind pFileFind(pFTP);
		
			//�����ļ�
			if(pFileFind.FindFile("/data/pub/" + m_StrFileName))//ykdocs.csv"))
			{	
			 
				pFileFind.FindNextFile();
				
				//����GetLastWriteTimeǰ�ȵ���FindNextFile()һ��
				pFileFind.GetLastWriteTime(&RemoteLastWrite);
				
				//ת�ļ�ʱ��Ϊϵͳʱ��
				::FileTimeToSystemTime(&RemoteLastWrite,&systemTime);
				
				strtime.Format("%d-%d-%d %d:%d:%d",systemTime.wYear,systemTime.wMonth,systemTime.wDay,systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
			
				//��ʾ״̬����Ϣ
		        StatusStr = "�ɹ��ҵ�" + m_StrFileName + "�ļ�������:" + strtime;
		        SendMessage(WM_EVENT, 1, 0);
			
				pFileFind.Close();

				//���ʱ�䲻ͬ�Ļ�
				if(strtime != GetRefreshTime())
				{
					
					CFileFind  finder;
					FileName.Format("%s%s",GetFolder(),m_StrFileName);//"ykdocs.csv");
					
					//�������������������
					if(finder.FindFile(FileName) != 0) 
					{ 
						//���ڴ��ļ��Ļ���ɾ�����ļ�
						::DeleteFile(FileName);
					}
					
					//�����ļ�����ǰĿ¼
					if (pFTP->GetFile("/data/pub/" + m_StrFileName,FileName))//ykdocs.csv"
					{
						delete pFTP;

						//��ʾ״̬����Ϣ
						StatusStr = "�ӷ�������ȡ�����ļ��ɹ�...";
						SendMessage(WM_EVENT, 1, 0);
					
						//��������
						GetPriveteDataFromWs(FileName);
					    //ɾ��ԭ�����ʱ��
						CDataBaseInstance::ExecuteDataBaseSQL("DELETE FROM TB_REFRESHTIME");
	                    //ʱ�����ʱ����¿�
						str.Format("INSERT INTO TB_REFRESHTIME(USER_REFRESHTIME) VALUES ('%s')",strtime);
                        CDataBaseInstance::ExecuteDataBaseSQL(str); 
						
						//��������ݸ�����Ϣ���´���
						CWnd* pt = CWnd::FindWindow(NULL,"���ݸ�����Ϣ");
						if(pt)
						{
							pt->SendMessage(WM_CLOSE,0,0);
						}
						
						//�����FTPԶ��������ȡ
						pt = CWnd::FindWindow(NULL,"FTPԶ��������ȡ");
						if(pt)
						{
							pt->SendMessage(WM_CLOSE,0,0);
						}

						//��ʾ���
						CShowInfoDlg    dlg;
						dlg.DoModal();

					} 
					else
					{
						//��ʾ״̬����Ϣ
						StatusStr = "�ӷ�������ȡ�����ļ�ʧ��...";
						SendMessage(WM_EVENT, 1, 0);
					}

				}
				else
				{
					//��ʾ״̬����Ϣ
					StatusStr = "�ϴθ��µ��û�������Ϣ�Ѿ�����������...";
					SendMessage(WM_EVENT, 1, 0);
				}

			}
			else
			{
				//��ʾ״̬����Ϣ
				StatusStr = "FTP���������Ҳ���" + m_StrFileName + "�ļ�...";
				SendMessage(WM_EVENT, 1, 0);
			}

		}

	}
	catch(CInternetException *pEx)
	{
		char m_szStatus[1024];
		pEx->GetErrorMessage(m_szStatus, sizeof(m_szStatus));
		//��ʾ״̬����Ϣ
		StatusStr = m_szStatus;
		SendMessage(WM_EVENT, 1, 0);
	    //status(m_szStatus);
		pEx->Delete();
	}

}


//�õ����ݸ��µ�ʱ��
CString CIFRMView::GetRefreshTime()
{  
	//�����ݿ�
	CDatabase         dbs;	
	CString      str = "";
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_REFRESHTIME","ALL") > 0)
	{
		
		if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//��CRecordset����
			CRecordset   rs(&dbs);
				
			str = "SELECT * FROM TB_REFRESHTIME";
			
			rs.Open(CRecordset::forwardOnly,str);
		
			//�õ���¼����
			rs.GetFieldValue((short)0,str);
			rs.Close();
			
			//�ر����ݿ�
			dbs.Close();
		}

	}

	str.TrimLeft();
	str.TrimRight();
	
	//���ؼ�¼ʱ��
	return str;   

}

//��ͷר�ã��� 2004.10.8 ������
void CIFRMView::OnUpdateNewreport(CCmdUI* pCmdUI) 
{	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
    //pCmdUI->Enable(!m_BaoTouUse);	
}


void CIFRMView::OnGetdatafromlong() 
{
	//CFTPGetDataDlg                dlg;
	//dlg.m_port      =       m_port;
	//dlg.m_loginname =  m_loginname;
	//dlg.m_password  =   m_password;
	//dlg.m_FileName  = m_FtpFileName;//FTP�ļ���
	//dlg.DoModal();	
}

void CIFRMView::OnLocalmodify() 
{

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm); 
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

	if(m_UseInfoset->IsOpen())
	{
		m_UseInfoset->Close();
	}
	
	//���ݿ���Ƿ��
	if(m_UseInfoset->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{

		CUserInfoDlg dlg(m_UseInfoset.get(),0);
		dlg.m_filtercondtion = pMainFrm->m_wndMyDialogBar.SelectCondition();
	    dlg.m_IfAdding       = FALSE;
		dlg.DoModal();	
		
		//��̨�޸Ļ������˼�¼
		if(dlg.m_IfAdding == TRUE)
		{	
			//���ؼ�����ˢ��һ��
			RefreshTree();
		}
		
	}

}

void CIFRMView::OnUpdateLocalmodify(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege()< 2);

}

void CIFRMView::OnUpdateAppearselectdata(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������
   	pCmdUI->Enable(AppInfo::Instance().m_WhichKind == FALSE && !pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
}


//�����վ�ĸ���
BOOL CIFRMView::CheckStations(CString m_strsql)
{

	CDatabase          dbs;
	CString         StrSql;
	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset rs(&dbs);
		//�õ�ѡ��ı��վ�ĸ���
		StrSql.Format("SELECT COUNT(DISTINCT USER_STATIONNO) FROM TB_USER WHERE %s",m_strsql);
		rs.Open(CRecordset::forwardOnly,StrSql);
		//�õ���¼����
		rs.GetFieldValue((short)0,StrSql);
		rs.Close();
		//�ر����ݿ�
		dbs.Close();
		
		if(atoi(StrSql) > 1)
		{	
			MessageBox("��ѡ���˶�����վ�����ݣ���ѡ�񵥸����վ�����ݷ��ͣ�","����",MB_OK|MB_ICONWARNING);
			return  FALSE;
		}
		
	}

	return TRUE;

}

//ȡ����ʱ��פ����ʱ����
void CIFRMView::OnUpdateBREAkSOMEDAY(CCmdUI* pCmdUI) 
{
	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{
			//����
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	
			//�绰
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//�绰
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			else
			{
				//���ӱ�־
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}
}

//���ö��ı�־
void CIFRMView::SetDataReadLabel(CString m_range)
{
	
	CString StrSql,str = "";//�ȸ������־,Y �Ѷ��ɹ����ö�  N û�ж����ı�־
	
	//14�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10�������� 11������� 12���ȵ��� 13��ƽ����
	for(int i = 0; i < 15; i++)
	{
		
		if(m_SetLabel[i])
		{
			str = str + "N";
		}
		else
		{
			str = str + "Y";
		}
		
	}
	
	if(m_range == "ALL")
	{
        //���ö����־
		StrSql.Format("UPDATE TB_USER SET USER_READLABEL='%s'",str);
	}
	else
	{
		//���ö����־
		StrSql.Format("UPDATE TB_USER SET USER_READLABEL='%s' WHERE %s",str,m_range);
	}

	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
}



//��ʾ��ʱ����İ�ť
void CIFRMView::ShowDingShiButton(BOOL  IsShowWindows)
{	
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	if(IsShowWindows)
	{    
	
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHI);

	}
	else
	{		
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHINULL);
	}

}

//����ʱ�Զ�Ӧ��
void CIFRMView::AutoAnswer(BOOL  ShowMessage)
{

	CString       str;
	CDatabase      db;
	str         =  "";
	short parameter[6];
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
       	str = "SELECT count(*) FROM TB_COMINFORMATION";
		rs.Open(CRecordset::forwardOnly,str);
		//�õ���¼����
		rs.GetFieldValue((short)0,str);
		//��¼����
		long fields = atol(str); 
		rs.Close();
		
		if(fields <= 0)
		{
			db.Close( );
			return;
		}
		else
		{
			str = "SELECT * FROM TB_COMINFORMATION";
			
			rs.Open(CRecordset::forwardOnly,str);
			
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
					    parameter[0] = atoi(str);
						break;
					}
				case 1:
					{
						//������
						parameter[1] = atoi(str);
						break;
					}
				case 2:
					{
						//����λ
						parameter[2] = atoi(str);
						break;
					}
				case 3:
					{
						//����λ
						parameter[3] = atoi(str);
						break;
					}
				case 4:
					{
						//ֹͣλ
						parameter[4] = atoi(str);
						break;
					}
				case 5:
					{
						//�Զ�Ӧ��
						parameter[5] = atoi(str);
						break;
					}
					
				}
				
			}
			
			//�ر����ݿ�
			rs.Close( );
			db.Close( );


			//�Զ�Ӧ��
			if(parameter[5] > 0)
			{

				/***************************************************************
				��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
				������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000 10-128000 11-256000
				����λ 0-��У��,1����У��,2��żУ��
				����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
				ֹͣλ 0-1     ,1-1.5    ,2-2
				**************************************************************/
		
				OptionClick(parameter[0],parameter[1],parameter[2],parameter[3],parameter[4]);
				m_sendkind   =    1;
			
				//�Զ�Ӧ��,���û������ͨ�򷵻�TRUE
				//Connect(ShowMessage,TRUE);
			    Connect(ShowMessage,FALSE);
			}

		}
		
	}

}

//��ʾ�б�ͷ
void CIFRMView::ShowGridHead(CString HeadStr)
{

	CString             Str;
	int               k = 0;
	CStringArray    ColName;
	CByteArray      ColWide;
	
	while(HeadStr.Find(';') != -1)
	{
		
		k   =  HeadStr.Find(';');
		
		if(k != -1)
		{
			Str =  HeadStr.Left(k);
			HeadStr  = HeadStr.Right(HeadStr.GetLength() - k - 1);

			k   =  Str.Find(',');
			
			if(k != -1)
			{
				
				ColName.Add(Str.Left(k));
				ColWide.Add(atoi(Str.Right(Str.GetLength() - k - 1)));
			}
			
		}
		
	}
	
	//ɾ�����е�����
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);

	TRY { 

		m_IsHistory    =     FALSE;//�Ƿ���ʾ��ʷ����
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);                    //��
		m_Grid.SetColumnCount(ColName.GetSize()); //��
		
		//�б�����
		for (int col = 0; col < ColName.GetSize(); col++)
		{ 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = 0;
			Item.col = col;
			Item.nFormat = DT_LEFT|DT_WORDBREAK;
			Item.strText.Format("%s",(ColName[col]));
			m_Grid.SetItem(&Item);
			m_Grid.SetColumnWidth(col,ColWide[col]); 
		}
		
		m_Grid.SetModified(FALSE,-1,-1);
		
		m_Grid.SetBkColor(RGB(255,255,255));

		m_Grid.Invalidate();
		m_Grid.Refresh();

	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
	END_CATCH
		
}


//��ʾ�����ض���
void CIFRMView::OperationAnimation(BOOL m_starting)
{ 
	//�õ���ѡ��ģ���
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	if(m_starting)
	{

		if (!pMainFrm->IsAnimationActive())
		{
			pMainFrm->StartAnimation(IDR_AVITEST);
		}

	}
	else
	{

		if (pMainFrm->IsAnimationActive())
		{
			pMainFrm->StopAnimation();
		}

	}

}


//����ɾ��ģ��
void CIFRMView::OnUpdateDeletemodule(CCmdUI* pCmdUI) 
{
    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
}

void CIFRMView::OnDeletemodule() 
{	
	CString            StrSql;

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

    StrSql.Format("����ɾ����ѡ���ģ���û���Ϣ����[%d��]��",CDataBaseInstance::GetAllRecordsCount("TB_USER",pMainFrm->m_wndMyDialogBar.SelectCondition()));

	if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{	
		
		StrSql = "ȷ��ɾ����ѡ���ģ���û���Ϣ������\r\n���棺ɾ�����û���Ϣ���ݲ��ָܻ�����";
		
		if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			
			StrSql = "ͬʱɾ����ѡ���ģ�����������ʽ��פ��������\r\n���棺ɾ�������ݲ��ָܻ�����";
            
			if(MessageBox(StrSql,"",MB_YESNO|MB_ICONQUESTION) == IDYES)
			{

				//ɾ�����פ������
				StrSql.Format("DELETE FROM TB_GARRISON WHERE GARRISON_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
				//ɾ�������ʽ��������	
				StrSql.Format("DELETE FROM TB_REALTIME WHERE REALTIME_MODULENO IN (SELECT USER_MODULENO FROM TB_USER  WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);	
				//���ߴ����ģ��
				StrSql.Format("DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE IN (SELECT USER_MODULENO FROM TB_USER WHERE %s)",pMainFrm->m_wndMyDialogBar.SelectCondition());
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);	
				//ɾ�������޹�������
				StrSql.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)");
				CDataBaseInstance::ExecuteDataBaseSQL(StrSql);

			}		
			
			//ɾ���û���Ϣ
			StrSql.Format("DELETE FROM TB_USER WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
				
			if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") < 1)
			{
				pMainFrm->m_wndMyDialogBar.ShowWindow(SW_HIDE);
				pMainFrm->m_wndMyDialogData.ShowWindow(SW_HIDE);
				GetParentFrame()->RecalcLayout();
			}
			else
			{
				pMainFrm->m_wndMyDialogBar.Treeinitialize();
			}
		}
		//���ؼ�����ˢ��һ��
	}

}

//��������Ա����
void CIFRMView::OnUpdateAngleset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 1);
}

//�߼��û�����
void CIFRMView::OnUpdateCommunication(CCmdUI* pCmdUI) 
{
 	
	pCmdUI->Enable(FALSE);
	return;

   	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(!m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 1:
		{	//�绰�κŵı�־,���ǵ�ְ��ʱ��
	        pCmdUI->Enable(!m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 2:
		{   
			//���ӱ�־
			pCmdUI->Enable(!m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	}
}

//�߼��û�����CRegKey
void CIFRMView::OnUpdateDatapass(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(FALSE);
	return;

	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 1:
		{	
			//�绰
			pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	case 2:
		{   
			//���ӱ�־
			pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 3);
			break;
		}
	}

}

//��ͨ����Ա���ϲ���
void CIFRMView::OnUpdateAutoreadset(CCmdUI* pCmdUI) 
{
   	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{				
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	//�绰�κ�
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//���ӱ�־
			if(AppInfo::Instance().m_WhichKind)
			{
			    pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);
			}
			else
			{
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}

}

void CIFRMView::OnUpdateBreadorder(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 1  && !m_IsAutoSending);	
}

//����BCH��
//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
void CIFRMView::Encode_Bch(BYTE g[],BYTE data[],BYTE m_kinds)
{
	int i,j,feedback,length = 63,k = 45;
	BYTE  bb[18];
	switch(m_kinds)
	{
	case 0:
		{	
			//0  Bch63_45_3
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
			length = 63;
			k      = 45;
			break;
		}
	case 1:
		{
			//1  Bch45_27_3
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
			length = 45;
			k      = 27;
			break;
		}
	case 2:
		{
			//2 BCH31_21_2
			g[0]   =    1;
			g[1]   =    0;
			g[2]   =    0;
			g[3]   =    1;
			g[4]   =    0;
			g[5]   =    1;
			g[6]   =    1;
			g[7]   =    0;
			g[8]   =    1;
			g[9]   =    1;
			g[10]  =    1;
			length =   31;
			k      =   21;
			break;
		}
	}



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

	//BUG ��һλû�вμ�BCH����
	g[63] = data[45];

}


void CIFRMView::OnClosereport() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{      
		return;
	}
	
	//��ʾ�����ض���
	OperationAnimation(FALSE);
	//���ع�����
	ShowProgressCtrl(FALSE);

    //�õ��޸�״̬
	if(m_Grid.GetModified(-1,-1))
	{
		
		if(MessageBox("�������޸�,���汨���ļ���?"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
             
			OnSavereportas(); 
			m_Grid.SetModified(FALSE,-1,-1);
		}
	
	}
	
	//ɾ�����е�����
	m_Grid.DeleteAllItems();
	m_Grid.SetModified(FALSE,-1,-1);
	
	m_Grid.SetBkColor(RGB(128,128,128));

	m_Grid.Refresh();
	status("     ");

}

void CIFRMView::OnUpdateClosereport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.GetRowCount() > 0); 
	
}

void CIFRMView::OnTimesearch() 
{
   
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
		
	CString       PassStr;
	if(	AppInfo::Instance().m_WhichKind)
	{
		
		if(m_zhuliukinds == 0)
		{			
			//0 �����������פ�� 1 ��������פ��
			MessageBox(DecodeParameter(TRUE),"�����������פ����������:");
		}
		else
		{
			//�����ڽ�������
			MessageBox(ByDateDecodeParameter(),"�����ڲ�ͬ��פ����������:");
			
		}

		
	}
	else
	{
		//Զ�̲�ѯ�Է���פ������
		PassStr    = "BEGINS;COMMAND:30:HALT;ENDS";
		m_TimeStrs = "";
		
		//������ӺõĻ�
		//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP���� m_sendkind
		//Str             �����ַ�
		//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
		//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
		SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
	}

}

//����Լ���
double CIFRMView::CorrelationCheck(long SourceArray[], long DestArray[],int m_places)
{
    double           A,B,C,Pxy,sums;
	double        DestArrayBak[256];
	double       DestArrayBaks[256];
    int                           i;
   	A = B = C = Pxy = sums = 0.000;

	for( i = 0; i < 256;i ++)
	{
		DestArrayBak[i]  = double(DestArray[i]);
	}

	//Ҫ�ƶ�λ��
	if(m_places + 1 <= WM_NUMBERS/2)
	{
		
		//��ֵǰ��
		for( i = 0; i < 256;i ++)
		{
			
			//�ƶ�λ��ƥ��
			if(i + (WM_NUMBERS/2 - m_places)*1 < 256)
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
		for( i = 0; i < 256;i ++)
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
		
		for( i = 0; i < 256;i ++)
		{
			DestArrayBak[i] = DestArrayBaks[i];
		}
		
	}
	else  if(m_places + 1 == WM_NUMBERS/2 + 1)
	{
		
		for( i = 0; i < 256;i ++)
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

	for(i = 0; i < 256;i ++)
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
}


//��ʼʱ��ͽ���ʱ��
//long     m_Module     ģ���
//CString  m_RightTime  ��ʱʱ��
double CIFRMView::GetTestData(long m_Module,CString m_RightTime)
{	
	
	m_GetDataTimeStr.TrimLeft();
    m_GetDataTimeStr.TrimRight();

	if(m_GetDataTimeStr.IsEmpty())
	{
		return -1;
	}
	int i;

	for( i = 0 ; i < m_FileDataArray.GetSize(); i = i + 3)
	{

		if(atol(m_FileDataArray[i]) == m_Module)
		{
			break;
		}
	}

	if(i + 2 > m_FileDataArray.GetSize())
	{
		return -1;
	}


	short m_year,m_month,m_day,m_hour,m_minuter,m_second;
	long                                          kk1;
    m_year       =         atoi(m_GetDataTimeStr.Mid( 0,4));
    m_month      =         atoi(m_GetDataTimeStr.Mid( 5,2));
    m_day        =         atoi(m_GetDataTimeStr.Mid( 8,2));
    m_hour       =         atoi(m_GetDataTimeStr.Mid(11,2));
	m_minuter    =         atoi(m_GetDataTimeStr.Mid(14,2));
    m_second     =         atoi(m_GetDataTimeStr.Mid(17,2));
    CTime    time1(m_year,m_month,m_day,m_hour,m_minuter,m_second);
   
	m_year       =         atoi(m_RightTime.Mid( 0,4));
    m_month      =         atoi(m_RightTime.Mid( 5,2));
    m_day        =         atoi(m_RightTime.Mid( 8,2));
    m_hour       =         atoi(m_RightTime.Mid(11,2));
	m_minuter    =         atoi(m_RightTime.Mid(14,2));
    m_second     =         atoi(m_RightTime.Mid(17,2));
    CTime    time2(m_year,m_month,m_day,m_hour,m_minuter,m_second);
  
	//�������Ϊ0�Ļ�
	if(atof(m_FileDataArray[i + 2]) == 0)
	{
		return atof(m_FileDataArray[i + 1]);
	}
	
	CTimeSpan      ts1;
	if(time2 >=  time1)
	{
		ts1 = time2  -  time1;
		kk1 = ts1.GetTotalSeconds();
		return atof(m_FileDataArray[i + 1]) + kk1*atof(m_FileDataArray[i + 2])/(24*3600);
	}
	else
	{
		ts1 = time1  -  time2;
		kk1 = ts1.GetTotalSeconds();
		return atof(m_FileDataArray[i + 1]) - kk1*atof(m_FileDataArray[i + 2])/(24*3600);
	}

}


void CIFRMView::OnZhuliumodify() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}	
	
	// פ����
	if(m_GarrisonSet->IsOpen())
	{
		m_GarrisonSet->Close();
	}
	m_GarrisonSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks);
	
	CGarrisonDlg  dlg(m_GarrisonSet.get(),0);
	dlg.DoModal();
}

void CIFRMView::OnZhenshimodify() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}	
	
	// ���ݱ�
	if(m_DataInfoSet->IsOpen())
	{
		m_DataInfoSet->Close();
	}
	m_DataInfoSet->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks);
	
	CDataInformationDlg  dlg(m_DataInfoSet.get(),0);
	dlg.DoModal();	
}


//�жϱ��Ƿ����
BOOL CIFRMView::IsCurveTableExist(CString strTableName)
{ 
	//�����ݿ�
	CDatabase          db;
	CString        strSql;
    
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		
		strSql.Format("SELECT * FROM %s",strTableName);
		
		TRY
		{
			rs.Open(CRecordset::forwardOnly,strSql);
			//�ر����ݿ�
			rs.Close( );
			db.Close( );
			return TRUE;
		}
		CATCH_ALL(e)
		{ 
			rs.Close( );
			db.Close( );
			e->Delete();
		}
		END_CATCH_ALL;
	}
    return FALSE;
}


//��Զ��פ��ʱ�������
void CIFRMView::ReadRemoteTime()
{
	CString strValue,strSql;
    CDatabase            db;
	short     parameter[38];

    //û�м�¼�򷵻�
	if(CDataBaseInstance::GetAllRecordsCount("TB_AUTOINFO","ALL") <= 0)
	{	
		return;
	}
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		
		strSql = "SELECT * FROM TB_AUTOINFO";
		rs.Open(CRecordset::forwardOnly,strSql);
		int j;
		//��¼����
		for( j = 0; j < 38; j ++)
		{
			//8���ֶ�,���������
			rs.GetFieldValue((short)j,strValue);
			
			//��ʼ����פ�������õ�38������
			parameter[j] = atoi(strValue);
		}
		
		rs.Close( );
		//�ر����ݿ�
		db.Close( );		
		
		//���վ��פ����ʱ�䵽�����
		//��ʽ��BEGINS;COMMAND:21:����1;����2;...����38;ENDS 
		strSql  = "BEGINS;COMMAND:21:";
		
		//��������
		for( j = 0; j < 38; j ++)
		{
			//��ʼ����פ�������õ�38������
			strValue.Format("%d",parameter[j]);
			strSql = strSql + strValue + ";";
		}
		
		strSql = strSql + "ENDS";
		
		//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
		//Str             �����ַ�
		//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
		//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
		SelectSendString(m_sendkind, strSql,TRUE,TRUE,TRUE); 

	}

}

void CIFRMView::OnUpdateTimesearch(CCmdUI* pCmdUI) 
{

	// 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	switch(m_sendkind)
	{ 
	case 0:
		{				
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && m_IsAutoSending);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetPortOpen() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 1:
		{	//�绰�κ�
			if(AppInfo::Instance().m_WhichKind)
			{
				//���ذ�
				pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2  && m_IsAutoSending);
			}
			else
			{
				//Զ�̰�
				pCmdUI->Enable(m_Com.GetCDHolding() && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	case 2:
		{   
			//���ӱ�־
			if(AppInfo::Instance().m_WhichKind)
			{
			    pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2  && m_IsAutoSending);
			}
			else
			{
				pCmdUI->Enable(m_IsConnect && CRuntimeAccount::GetCurrentPrivilege() < 2);
			}
			break;
		}
	}

}

void CIFRMView::OnGetfile() 
{
	UpdateDataTable();
	//CConectStatus  dlg;
	//dlg.DoModal();

	/*
	CDataInto  dlg;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

		
	if(dlg.DoModal() == IDOK)
	{

	}
	
	if(m_GetDataFromFile)
	{
		pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGCHECK);
		pMainFrm->m_wndAboutButton.ShowWindow(SW_SHOW);
	}
	else
	{
        pMainFrm->m_wndAboutButton.SetIcon(IDI_DINGSHINULL);
		pMainFrm->m_wndAboutButton.ShowWindow(SW_SHOW);
	}	
	*/
}

//ѯ���Ƿ�Ҫ�ؼ�������
void CIFRMView::AskIfAddData(CString DataName,CString FileName)
{	
	
	CFileFind            finder; 

	//�������������������
	if(finder.FindFile(FileName) != 0) 
	{ 
		
		if(DataName != "ZSDB_DATA" && DataName != "ZLDB_DATA" && DataName != "TB_HISTORYDATAS")
		{
			
            //���ذ棬Զ�̴���������
			if(	AppInfo::Instance().m_WhichKind == TRUE)
			{
				
				//�����ظ����ݼ�¼ m_DataName  ����,TxtFileName  �����ı��ļ�
				DealRepeatRecord(DataName,FileName);
				
				//������û����ݱ���̨��
				if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
				{
					//���ؼ�����ˢ��һ��
					RefreshTree();
				}
				
				 //������Ϣ
				 SendContionStr.Format("BEGINS;MESSAGE:0:Զ�̻��������������,��������ݼ�¼%d����\r\nע�������ظ���¼ʱ��ɾ���ظ���¼����ӣ�;ENDS",m_PassDataRecords);
			     SendMessage(WM_EVENT, 4, 0);
				
			}
			else
			{
				
				CString      data;
				data.Format("���ݽ�����ϣ������Զ�̴����Ĺ���%d�����ݼ�¼��\r\n���뱾�ض�Ӧ�Ŀ������?",m_PassDataRecords);
				
				if(MessageBox(data,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
				{
					
					//�����ظ����ݼ�¼ m_DataName   ����,TxtFileName  �����ı��ļ�
					DealRepeatRecord(DataName,FileName);
                  
					//������û����ݱ���̨��
					if(DataName == "TB_USER")// || DataName == "TB_TRANSFORMER")
					{
						//���ؼ�����ˢ��һ��
						RefreshTree();
					}  
					
					MessageBox("Զ�̴������ݴ��뱾�����ݱ���ϣ�"," ",MB_OK);
					
				}
				
			}
			
		}
		//���Ƕ�ģ�����ɵ����Ļ�
	
	}

}

//��ʾ������������
void CIFRMView::AppearAccept(CString m_dataname)
{
	
	CString      StrSql,m_filename;
	CDatabase                   db;
	CStringArray         m_ColName;
	int            m_positions = 1;
	char                    s[300];

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
		StrSql.Format("SELECT * FROM %s",m_dataname);
		rs.Open(CRecordset::forwardOnly,StrSql);
		
		//�õ��ֶθ���
		short m_fileds = rs.GetODBCFieldCount();
		
		if(m_dataname ==  "TB_ELECTRICITY")
		{
			//�õ�����͵�۱�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_ELECTRICITYS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_TRANSFORMER")
		{
			
			//��̨��Ϣ���ݱ�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_TRANSFORMERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_AMMETER")
		{
			
			//�����Ϣ���ݱ�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_AMMETERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_USER")
		{
			
			//�û���Ϣ�����ݱ�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_USERS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_GARRISON")
		{
			
			//פ�����ݱ�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_GARRISONS[i + 1]);
			}
			
		}
		else if(m_dataname == "TB_REALTIME")
		{
			//��ʽ�������ݱ�
			for(int i = 0; i < 2 * m_fileds; i = i + 2)
			{
				m_ColName.Add(TB_REALTIMES[i + 1]);
			}
			
		}
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
		
		//ɾ�����е�����
		m_Grid.DeleteAllItems();
		m_Grid.ShowWindow(SW_SHOW);		
		
		TRY { 

			m_Grid.SetFixedRowCount(1);
			m_Grid.SetRowCount(1);           //��
			m_Grid.SetColumnCount(m_fileds); //��
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
            
            #ifndef _WIN32_WCE
			   dwTextStyle |= DT_END_ELLIPSIS;
            #endif
			int col;
			for ( col = 0; col < m_Grid.GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = 0;
				Item.col = col;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%s",m_ColName[col]);
				m_Grid.SetItem(&Item);
				m_Grid.SetColumnWidth(col,80); 
			}
			
			//��ȡ�ı��ļ�����
			m_filename   =  GetFolder() + m_dataname + ".TXT";
		      
			int m_lines  =  GetDataLines(m_filename);
			
			if(m_lines < 0)
			{
				return;
			}
            
			ShowProgressCtrl(TRUE);

			status("������ʾ�������ݣ����Ժ�... ");
            SetProgressCtrlRange(0, m_lines,1);
	        
			FILE   *fp;
			if((fp=fopen(m_filename,"r"))!=NULL)
			{
				
				while(!feof(fp))
				{
					//���Ϊ�����˳�
					if(fgets(s,300,fp) == NULL)
					{
						break;
					}
					
					StrSql =   s;
					StrSql.TrimRight();
					StrSql.TrimLeft();

					//���ı��ļ���ȡ��
					if(!StrSql.IsEmpty())
					{
						
						col  = 0;
						
						//��,Ϊ�ָ���,�ֽ��ַ���
						while(StrSql.Find(',') != -1)
						{				
							
							int 	k   =  StrSql.Find(',');
							
							if(k != -1)
							{
								
								m_ColName[col]  =  StrSql.Left(k);
								m_ColName[col].TrimLeft();
								m_ColName[col].TrimRight();
								
								if(m_ColName[col].GetLength() == 23 && m_ColName[col].Find("-")!=-1 && m_ColName[col].Find(":")!= -1)
								{
									m_ColName[col] = m_ColName[col].Left(19);
								}
								
								StrSql          =  StrSql.Right(StrSql.GetLength() - k - 1);
								
								if(col > m_fileds - 2)
								{
									break;
								}
								col++;
							}
							
						}
						
						m_ColName[col] =  StrSql;
						
						m_ColName[col].TrimLeft();
						m_ColName[col].TrimRight();
						
						if(m_ColName[col].GetLength() == 23 && m_ColName[col].Find("-")!=-1 && m_ColName[col].Find(":")!= -1)
						{
							m_ColName[col] = m_ColName[col].Left(19);
						}
						
						m_Grid.InsertRow(_T(" "), -1);
						m_Grid.Invalidate(); 
						
						for ( col = 0; col < m_Grid.GetColumnCount(); col++)
						{ 
							GV_ITEM  Item;
							Item.mask    = GVIF_TEXT|GVIF_FORMAT;
							Item.row     = m_Grid.GetRowCount() - 1;
							Item.col     = col;
							Item.nFormat = dwTextStyle;
							Item.strText.Format("%s",(m_ColName[col]));
							m_Grid.SetItem(&Item);
						}
						
						m_Grid.Invalidate();
						
						m_Grid.SetBkColor(RGB(255,255,255));

						m_Grid.Refresh();
						SurrenderWindowMessage();
						
					}	
					SetProgressCtrlSetIt();
				}
				
				//�ر��ļ�ָ��
				fclose(fp);	

				m_Grid.SetModified(FALSE,-1,-1);
				m_Grid.AutoSize();
				status("��ʾ�����������... ");
				ShowProgressCtrl(FALSE);
			}

		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
		END_CATCH
   }

}


void CIFRMView::OnUpdateDisconnect(CCmdUI* pCmdUI) 
{

	switch(m_sendkind)
	{ 
	case 0:
		{
			pCmdUI->Enable(m_Com.GetPortOpen());
			break;
		}
	case 1:
		{	//�绰�κŵı�־,���ǵ�ְ��ʱ��
			pCmdUI->Enable(m_Com.GetCDHolding());
			break;
		}
	case 2:
		{   
			//���ӱ�־
			pCmdUI->Enable(m_IsConnect);
			break;
		}
	}
	
}

//�Ͽ�����
void CIFRMView::OnConnectsuccess() 
{
    DisConnect(m_sendkind);	
	
	if(!AppInfo::Instance().m_WhichKind)
	{
		KillTimer(3);
		//��ʾ�����ض���
		OperationAnimation(FALSE);
		//���ع�����
		ShowProgressCtrl(FALSE);
		//�õ�����Ĵ���
		m_GetErrors     =     0;
	
	}
				
}

//�������ݸ��ֱ�ṹ
BOOL CIFRMView::UpdateDataTable()
{	
	//д�Ϲس���ʱ��
	CString      m_Sqlstr,str;
	CTime timet = CTime::GetCurrentTime();	    
	str.Format("��%4d-%02d-%02d %02d:%02d:%02d���������",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	WriteToLog(str);

	//�Ƿ���ڴ˱�
	BOOL  m_IsExisting  = FALSE; 
	BOOL  m_Updateing   = FALSE;

	/*
	//�޸��û����ݱ�
	m_Sqlstr= "ALTER TABLE TB_USER ALTER COLUMN USER_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//��������
	m_Sqlstr= "ALTER TABLE TB_USER ADD PRIMARY KEY (USER_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	

	//�޸�פ�����ݱ�
	m_Sqlstr= "ALTER TABLE TB_GARRISON ALTER COLUMN GARRISON_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//��������
	m_Sqlstr= "ALTER TABLE TB_GARRISON ADD PRIMARY KEY (GARRISON_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	
	//�޸���ʽ��������
	m_Sqlstr= "ALTER TABLE TB_REALTIME ALTER COLUMN REALTIME_MODULENO bigint NOT NULL";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	//��������
	m_Sqlstr= "ALTER TABLE TB_REALTIME ADD PRIMARY KEY (REALTIME_MODULENO)";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	*/

	//�޸�ԭ����פ��ʱ���ַ���
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,6,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,6,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
    m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,9,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,9,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,12,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,12,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,15,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,15,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	m_Sqlstr = "UPDATE TB_GARRISON SET GARRISON_HALTTIME=STUFF(GARRISON_HALTTIME,18,1,'0') WHERE SUBSTRING(GARRISON_HALTTIME,18,1)=' '";
	CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

	//��ͷ���м��

	{
		//������ǰ�ͷ������,��ɾ��
        if(IsCurveTableExist("TB_MANAGERANGE"))
		{
			m_Sqlstr.Format("DROP TABLE TB_MANAGERANGE");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		} 
		
		if(IsCurveTableExist("TB_USERTEMPWS"))
		{
			m_Sqlstr.Format("DROP TABLE TB_USERTEMPWS");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}
		
		//���û���޹�������
        if(!IsCurveTableExist("TB_WUGONG"))
		{

			m_Sqlstr.Format("CREATE TABLE [dbo].[TB_WUGONG] (\
				          [WUGONG_MODULE] [bigint] NOT NULL ,\
				          [WUGONG_SPACE]  [int]    NOT NULL \
				                            ) ON [PRIMARY]");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		
		}
		
		//���û���޹�������
        if(!IsCurveTableExist("TB_WGUPDOWN"))
		{
			m_Sqlstr.Format("CREATE TABLE [dbo].[TB_WGUPDOWN] (\
								[WGUPDOWN_UP] [int] NOT NULL ,\
								[WGUPDOWN_DOWN] [int] NOT NULL ,\
								[WGUPDOWN_EVERYTIME] [smallint] NULL\
								) ON [PRIMARY]");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		} 
		
	}

	//���û�н��ߴ����
    if(!IsCurveTableExist("TB_LINEERROR"))
	{
	   m_Sqlstr= "CREATE TABLE   [dbo].[TB_LINEERROR] (\
							[LINEERROR_MODULE]   [bigint]  NULL ,\
							[LINEERROR_READTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
							[LINEERROR_HALTTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
							[LINEERROR_KINDS]    [tinyint]  NULL \
							) ON [PRIMARY]";

		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	} 
	
	//���û�л�����Ϣ��
    if(!IsCurveTableExist("TB_CHANGEAMMETER"))
	{
	   m_Sqlstr= "CREATE TABLE   [dbo].[TB_CHANGEAMMETER] (\
						[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,\
						[CHANGEAMMETER_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTAL] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NOT NULL ,\
						[CHANGEAMMETER_JFDL] [float] NOT NULL ,\
						[CHANGEAMMETER_FDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_PDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_GDL] [float] NOT  NULL ,\
						[CHANGEAMMETER_UPDATETIME] [datetime] NOT NULL ,\
						[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL \
							) ON [PRIMARY]";

		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		//��������
		m_Sqlstr= "ALTER TABLE TB_CHANGEAMMETER ADD PRIMARY KEY (CHANGEAMMETER_MODULENO)";
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
	}  
	
	//ɾ��ԭ����ʷ�����¼
	if(IsCurveTableExist("TB_HISTORYDATA"))
	{
		str.Format("Drop TABLE  %s","TB_HISTORYDATA");
		CDataBaseInstance::ExecuteDataBaseSQL(str);
	}

    //����л�����Ϣ
	if(IsCurveTableExist("TB_CHANGEAMMETER"))
	{
		
		if(GetFieldNumbers("TB_CHANGEAMMETER") != 22)
		{
			//ɾ��ԭ���ı�
			m_Sqlstr.Format("DROP TABLE TB_CHANGEAMMETER");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

			//�����ɱ�
			m_Sqlstr = "CREATE TABLE [dbo].[TB_CHANGEAMMETER] (\
						[CHANGEAMMETER_MODULENOOLD] [bigint] NOT NULL ,\
						[CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,\
						[CHANGEAMMETER_NOOLD] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
						[CHANGEAMMETER_WORKDEGREEOLD] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTALOLD] [float] NULL ,\
						[CHANGEAMMETER_WORKDEGREETOTAL] [float] NULL ,\
						[CHANGEAMMETER_LOSEDEGREEOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTALOLD] [float] NULL ,\
						[CHANGEAMMETER_LOSEDEGREETOTAL] [float] NULL ,\
						[CHANGEAMMETER_JFDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_JFDL] [float] NOT NULL ,\
						[CHANGEAMMETER_FDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_FDL] [float] NOT NULL ,\
						[CHANGEAMMETER_PDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_PDL] [float] NOT NULL ,\
						[CHANGEAMMETER_GDLOLD] [float] NOT NULL ,\
						[CHANGEAMMETER_GDL] [float] NOT NULL ,\
						[CHANGEAMMETER_UPDATETIME] [datetime] NOT NULL ,\
						[CHANGEAMMETER_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NOT NULL\
						) ON [PRIMARY]";

			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		
		}

	}

	//���û����ֶθ���
	short m_fields = GetFieldNumbers("TB_USER");
	
	//���С��34������
	if(m_fields < 35)
	{
		
		CProgressDlg pDialog(ID_PROGRESSDLGUPDATE);
		pDialog.Create(NULL);
		pDialog.SetRange(1,20);
		pDialog.SetStep(1);
		pDialog.SetPos(1);	 

		////////////////////1���û���Ϣ//////////////////////////////
        m_Sqlstr = " 	CREATE TABLE [dbo].[TB_USER] (\
			[USER_COMPANY] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNO] [char] (5) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MOTHERLINE] [int] NULL ,\
			[USER_BAKMOTHERLINE] [int] NULL ,\
			[USER_LINENO] [int] NULL ,\
			[USER_BAKLINENO] [int] NULL ,\
			[USER_LINENAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TRANSFORMERNO] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MODULENO] [bigint] NULL ,\
			[USER_PHASE] [tinyint] NULL ,\
			[USER_NAME] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_NO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_OLDNO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ADDRESS] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_PHONE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ELECTRICITYKIND] [tinyint] NULL ,\
			[USER_AMMETERNO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_AMMETERKIND] [tinyint] NULL ,\
			[USER_INSTALLTIME] [datetime] NULL ,\
			[USER_SUPPLYMODE] [tinyint] NULL ,\
			[USER_INITIALVALUE] [float] NULL ,\
			[USER_MULTIPLE] [int] NULL ,\
			[USER_PROTOCOL] [tinyint] NULL ,\
			[USER_DESCRIBE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_READLABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TIMELABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ETSTATUS] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_IDNO] [int] NULL ,\
			[USER_AMMETERTYPE] [varchar] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_SENDANGLE] [tinyint] NULL ,\
			[USER_DOWNVALUE] [int] NULL ,\
        	[USER_UPVALUE]   [int] NULL, \
			[USER_RUNSTATUS] [tinyint] NULL,\
			[USER_ZHULABEL] [char] (93) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
        
		
		//�û���Ϣ
		if(ModifyDataTable("TB_USER",m_Sqlstr,1))
		{
           m_Sqlstr = "UPDATE TB_USER SET USER_RUNSTATUS=0";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   pDialog.StepIt();
		}
		else
		{
			pDialog.CheckCancelButton();
			MessageBox("ģ���û���Ϣ���������󣡣�"," ",MB_OK|MB_ICONWARNING);
            return FALSE;
		}
	    
		///////////////////2��פ������Ϣ/////////////////////
	    m_IsExisting  = IsCurveTableExist("TB_GARRISON");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_GARRISON") != 19)
			{
				m_Updateing = TRUE;
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{

		   m_Sqlstr = "  CREATE TABLE [dbo].[TB_GARRISON] (\
			  [GARRISON_MODULENO] [bigint] NOT NULL ,\
			  [GARRISON_WORKDEGREE] [float] NULL ,\
			  [GARRISON_WORKDEGREETOTAL] [float] NULL ,\
			  [GARRISON_LOSEDEGREE] [float] NULL ,\
			  [GARRISON_LOSEDEGREETOTAL] [float] NULL ,\
			  [GARRISON_ACURRENT] [float] NULL ,\
			  [GARRISON_BCURRENT] [float] NULL ,\
			  [GARRISON_CCURRENT] [float] NULL ,\
			  [GARRISON_AVOLTAGE] [float] NULL ,\
			  [GARRISON_BVOLTAGE] [float] NULL ,\
			  [GARRISON_CVOLTAGE] [float] NULL ,\
			  [GARRISON_JFDL] [float] NULL ,\
			  [GARRISON_FDL] [float] NULL ,\
			  [GARRISON_PDL] [float] NULL ,\
			  [GARRISON_GDL] [float] NULL ,\
			  [GARRISON_GLYS] [float] NULL ,\
			  [GARRISON_TRANSCRIBETIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [GARRISON_PROTOCOL] [smallint] NOT NULL ,\
			  [GARRISON_HALTTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL \
			  ) ON [PRIMARY]";
	
			 //�޸ĺ��µ����ݱ�һ��
			 if(ModifyDataTable("TB_GARRISON",m_Sqlstr,1))
			 {
				 pDialog.StepIt();
			 }
			 else
			 {
				 pDialog.CheckCancelButton();
				 MessageBox("פ�����ݱ��������󣡣�"," ",MB_OK|MB_ICONWARNING);
				 return FALSE;
			 }
	
		}
		else
		{
			pDialog.StepIt();
		}
		
		////////////////////3��ʵʱ����////////////////////////
        m_IsExisting  = IsCurveTableExist("TB_REALTIME");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_REALTIME") != 18)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 		CREATE TABLE [dbo].[TB_REALTIME] (\
				[REALTIME_MODULENO] [bigint] NOT NULL ,\
				[REALTIME_WORKDEGREE] [float] NULL ,\
				[REALTIME_WORKDEGREETOTAL] [float] NULL ,\
				[REALTIME_LOSEDEGREE] [float] NULL ,\
				[REALTIME_LOSEDEGREETOTAL] [float] NULL ,\
				[REALTIME_ACURRENT] [float] NULL ,\
				[REALTIME_BCURRENT] [float] NULL ,\
				[REALTIME_CCURRENT] [float] NULL ,\
				[REALTIME_AVOLTAGE] [float] NULL ,\
				[REALTIME_BVOLTAGE] [float] NULL ,\
				[REALTIME_CVOLTAGE] [float] NULL ,\
				[REALTIME_JFDL] [float] NULL ,\
				[REALTIME_FDL] [float] NULL ,\
				[REALTIME_PDL] [float] NULL ,\
				[REALTIME_GDL] [float] NULL ,\
				[REALTIME_GLYS] [float] NULL ,\
				[REALTIME_TRANSCRIBETIME] [char] (19) COLLATE Chinese_PRC_CI_AS NULL ,\
				[REALTIME_PROTOCOL] [smallint] NOT NULL \
				) ON [PRIMARY]";
			
			if(ModifyDataTable("TB_REALTIME",m_Sqlstr,1))
			{
				pDialog.StepIt();
			}
			else
			{
				pDialog.CheckCancelButton();
				MessageBox("ʵʱ�������ݱ��������󣡣�"," ",MB_OK|MB_ICONWARNING);
				return FALSE;
			}
		}
		else
		{
			pDialog.StepIt();
			
		}

		////////////////////4�����������Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_AMMETER");  //�Ƿ���ڴ˱�
        m_Updateing   =                           FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_AMMETER") != 4)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "CREATE TABLE [dbo].[TB_AMMETER] (\
		    [AMMETER_TYPE]         [char] (10) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
		    [AMMETER_MANUFACTURER] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		    [AMMETER_IMPULSE]      [int] NOT NULL ,\
		    [AMMETER_REMARK]       [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
		    ) ON [PRIMARY]";
			
			//�޸ĺ��µ����ݱ�һ��
			if(ModifyDataTable("TB_AMMETER",m_Sqlstr,1))
			{
				pDialog.StepIt();	
			}
			else
			{
				pDialog.CheckCancelButton();
				MessageBox("���������Ϣ���������󣡣�"," ",MB_OK|MB_ICONWARNING);
				return FALSE;
			}
			
			//��������
			m_Sqlstr= "ALTER TABLE TB_AMMETER ADD PRIMARY KEY (AMMETER_TYPE)";
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
			
			pDialog.StepIt();
		}
		else
		{
			pDialog.StepIt();
			pDialog.StepIt();
		}	

		///////////////////5��פ��ʱ��/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_HALTTIME");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_HALTTIME") != 1)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_HALTTIME] (\
			[HALTTIME_TIME] [char] (19) COLLATE Chinese_PRC_CI_AS NOT NULL \
			) ON [PRIMARY] ";
			
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_HALTTIME",m_Sqlstr,0);
		}
	
		pDialog.StepIt();
		

		///////////////////6����������Ϣ/////////////////////

		m_IsExisting  = IsCurveTableExist("TB_HAND");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_HAND") != 3)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_HAND] (\
				[HAND_NO] [tinyint] NULL ,\
				[HAND_STATIONNAME] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[HAND_STATUS] [tinyint] NULL \
				) ON [PRIMARY]";
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_HAND",m_Sqlstr,0);
		}

		pDialog.StepIt();

		//////////////////////7���Զ�������Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_Auto");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_Auto") != 110)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{

            m_Sqlstr = "CREATE TABLE [dbo].[TB_Auto] (";
			
			for(int i = 1; i <= 110; i ++)
			{
				if(i < 110)
				{
					str.Format("[Auto_Parameter%d] [tinyint] NULL,",i);
					m_Sqlstr = m_Sqlstr  + str;
				}
				else
				{
					str.Format("[Auto_Parameter%d] [tinyint] NULL",i);
					m_Sqlstr = m_Sqlstr  + str;
				}
				
			}
			
			m_Sqlstr = m_Sqlstr + ") ON [PRIMARY]";
			
					
			str.Format("Drop TABLE  %s","TB_Auto");
			CDataBaseInstance::ExecuteDataBaseSQL(str);//ɾ���ϱ�

			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);//�����±�
		
		}
	
		pDialog.StepIt();


        //////////////////////8��������Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_COMINFORMATION");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_COMINFORMATION") != 6)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "CREATE TABLE [dbo].[TB_COMINFORMATION] (\
					  [COMINFORMATION_COM] [smallint] NULL ,\
					  [COMINFORMATION_BITS] [smallint] NULL ,\
					  [COMINFORMATION_CHECKBIT] [smallint] NULL ,\
					  [COMINFORMATION_DATABIT] [smallint] NULL ,\
					  [COMINFORMATION_STOPBIT] [smallint] NULL ,\
					  [COMINFORMATION_AUTOREPLY] [tinyint] NULL \
					  ) ON [PRIMARY]";
		
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_COMINFORMATION",m_Sqlstr,0);
		}
		pDialog.StepIt();
	  
	   //////////////////////9�����������Ϣ/////////////////////

		m_IsExisting  = IsCurveTableExist("TB_DWELLERACCOUNT");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_DWELLERACCOUNT") != 10)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "	    CREATE TABLE [dbo].[TB_DWELLERACCOUNT] (\
			  [�û���] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [�û���] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [���] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			  [����ָ��] [float] NULL ,\
			  [����ָ��] [float] NULL ,\
			  [����] [float] NULL ,\
			  [�Ŵ�����] [float] NULL ,\
			  [�Ŵ����] [float] NULL ,\
			  [���] [float] NULL ,\
			  [�ϼ�] [float] NULL \
			  ) ON [PRIMARY]";
			
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_DWELLERACCOUNT",m_Sqlstr,0);
		}

		pDialog.StepIt();

	    //////////////////////10���õ�������Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITY");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITY") != 4)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "	CREATE TABLE [dbo].[TB_ELECTRICITY] (\
				[ELECTRICITY_NO] [tinyint] NOT NULL ,\
				[ELECTRICITY_KIND] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[ELECTRICITY_PRICE] [float] NOT NULL ,\
				[ELECTRICITY_REMARK] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";
				
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_ELECTRICITY",m_Sqlstr,0);
			
			// ��������
			m_Sqlstr= "ALTER TABLE TB_ELECTRICITY ADD PRIMARY KEY (ELECTRICITY_NO)";
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}

		pDialog.StepIt();
		
		//////////////////////11���õ�������Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITYLOSS");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITYLOSS") != 7)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "		CREATE TABLE [dbo].[TB_ELECTRICITYLOSS] (\
				[��̨����] [char] (26) COLLATE Chinese_PRC_CI_AS NULL ,\
				[����] [int] NULL ,\
				[����] [int] NULL ,\
				[���¹�����] [float] NULL ,\
				[�����۵���] [float] NULL ,\
				[��ʧ����] [float] NULL ,\
				[������] [float] NULL \
				) ON [PRIMARY]";
				
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_ELECTRICITYLOSS",m_Sqlstr,0);
		}

		pDialog.StepIt();
			
		///////////////////12���õ�ͳ����Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ELECTRICITYTOTAL");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ELECTRICITYTOTAL") != 6)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}

         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "		CREATE TABLE [dbo].[TB_ELECTRICITYTOTAL] (\
				[��̨����] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
				[���ܱ���] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[���¶���] [float] NULL ,\
				[���¶���] [float] NULL ,\
				[����] [int] NULL ,\
				[����] [float] NULL \
				) ON [PRIMARY]";
				
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_ELECTRICITYTOTAL",m_Sqlstr,0);
		}

        pDialog.StepIt();

        ///////////////////13�������嵥��Ϣ/////////////////////
		m_IsExisting  = IsCurveTableExist("TB_EXCERPTION");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_EXCERPTION") != 9)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = "	CREATE TABLE [dbo].[TB_EXCERPTION] (\
				[�û����������ơ�ԭ����] [char] (70) COLLATE Chinese_PRC_CI_AS NULL ,\
				[��������] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[����] [int] NULL ,\
				[�õ����] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[�ϴζ���] [float] NULL ,\
				[���ζ���] [float] NULL ,\
				[���] [float] NULL ,\
				[����] [float] NULL \
				) ON [PRIMARY]";
			 
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_EXCERPTION",m_Sqlstr,0);
		}

		pDialog.StepIt();
	
		////////////////////14��IP��ַ////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_IP");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_IP") != 2)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_IP] (\
				[IP_ADDRESS] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
				[IP_COMPUTER] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]	";
			//�޸ĺ��µ����ݱ�һ��
			ModifyDataTable("TB_IP",m_Sqlstr,0);
		}
		pDialog.StepIt();

   		
		////////////////////15���绰����////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_PHONE");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_PHONE") != 3)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_PHONE] (\
				[PHONE_NO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
				[PHONE_NAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
				[PHONE_PASSWORD] [varchar] (8) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_PHONE",m_Sqlstr,0);
		}
		pDialog.StepIt();
        
		////////////////////16��TB_REFRESHTIME////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_REFRESHTIME");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_REFRESHTIME") != 1)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " 	CREATE TABLE [dbo].[TB_REFRESHTIME] (\
				[USER_REFRESHTIME] [char] (19) COLLATE Chinese_PRC_CI_AS NOT NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_REFRESHTIME",m_Sqlstr,0);
		}

		pDialog.StepIt();

        ////////////////////17����̨��Ϣ//////////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_TRANSFORMER");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_TRANSFORMER") != 7)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			m_Sqlstr = " CREATE TABLE [dbo].[TB_TRANSFORMER] (\
				[TRANSFORMER_NO] [char] (40) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[TRANSFORMER_TYPE] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CAPACITY] [int] NULL ,\
				[TRANSFORMER_INSTALLTIME] [datetime] NULL ,\
				[TRANSFORMER_POSITION] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_OWNERSHIP] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CONNECTFORM] [tinyint] NULL \
				) ON [PRIMARY]";
			ModifyDataTable("TB_TRANSFORMER",m_Sqlstr,0);
		}
		pDialog.StepIt();
        

	  ////////////////////18��TB_ZXACCOUNT//////////////////////////////
		m_IsExisting  = IsCurveTableExist("TB_ZXACCOUNT");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_ZXACCOUNT") != 17)
			{
				m_Updateing = TRUE;
				
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			  m_Sqlstr = " 	CREATE TABLE [dbo].[TB_ZXACCOUNT] (\
					[�û���] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[�û���] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
					[�����ϼ�] [float] NULL ,\
					[��Ѻϼ�] [float] NULL ,\
					[��ƺ�] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[��װ����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[������] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
					[��Ʊ���] [int] NULL ,\
					[���±���] [float] NULL ,\
					[���±���] [float] NULL ,\
					[��Ƶ���] [float] NULL ,\
					[������Ŀ] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
					[����] [float] NULL ,\
					[���] [float] NULL ,\
					[���] [float] NULL ,\
					[˰��] [float] NULL ,\
					[�ϼ�] [float] NULL \
					) ON [PRIMARY]";
			  ModifyDataTable("TB_ZXACCOUNT",m_Sqlstr,0);
		}

	    pDialog.StepIt();

        ////////////////////19��TB_DateAuto��פ�����������Զ�פ��///////
 		m_IsExisting  = IsCurveTableExist("TB_DateAuto");  //�Ƿ���ڴ˱�
        m_Updateing   =      FALSE;

		if(m_IsExisting)
		{
			
			if(GetFieldNumbers("TB_DateAuto") != 67)
			{
				m_Updateing = TRUE;
				m_Sqlstr.Format("DROP TABLE TB_DateAuto");//ɾ��ԭ���ı�
				CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
			}
			
		}
		else
		{
			m_Updateing = TRUE;
		}
         
		//���Ҫ����
		if(m_Updateing)
		{
			  m_Sqlstr = "CREATE TABLE [dbo].[TB_DateAuto] (";
   
			   for(int i = 1; i <= 67; i ++)
			   {

				   if(i < 67)
				   {
					   str.Format("[Auto_Parameter%d] [tinyint] NULL,",i);
					   m_Sqlstr = m_Sqlstr  + str;
				   }
				   else
				   {
					   str.Format("[Auto_Parameter%d] [tinyint] NULL",i);
					   m_Sqlstr = m_Sqlstr  + str;
				   }
				   
			   }
   
			   m_Sqlstr = m_Sqlstr + ") ON [PRIMARY]";	
			   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);//�����±�
		}

        pDialog.StepIt();
	
		//ɾ��ԭ����ʱ����ı�
		if(IsCurveTableExist("TB_AUTOINFO"))
		{
			 str.Format("Drop TABLE  %s","TB_AUTOINFO");
			 CDataBaseInstance::ExecuteDataBaseSQL(str);//ɾ���ϱ�
		}  
    
   }
   else
   {
	

   }
 
   //�޸��û����ݱ�
   m_Sqlstr= "ALTER TABLE TB_USER ALTER COLUMN USER_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
  
   m_Sqlstr= "ALTER TABLE TB_USER DROP PRIMARY KEY (USER_MODULENO) ";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

   //��������
   m_Sqlstr= "CREATE INDEX TB_USERINDEX ON TB_USER (USER_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //�޸�פ�����ݱ�
   m_Sqlstr= "ALTER TABLE TB_GARRISON ALTER COLUMN GARRISON_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   //��������
   m_Sqlstr= "CREATE INDEX TB_GARRISONINDEX ON TB_GARRISON (GARRISON_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //�޸���ʽ����
   m_Sqlstr= "ALTER TABLE TB_REALTIME ALTER COLUMN REALTIME_MODULENO bigint NOT NULL";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   //��������
   m_Sqlstr= "CREATE INDEX TB_REALTIMEINDEX ON TB_REALTIME (REALTIME_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //�����������
   m_Sqlstr= "CREATE INDEX TB_AMMETERINDEX ON TB_AMMETER (AMMETER_TYPE)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //�����Զ�פ������
   m_Sqlstr= "CREATE INDEX TB_AutoINDEX ON TB_Auto (Auto_Parameter1)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //��������ģ������
   m_Sqlstr= "CREATE INDEX TB_CHANGEAMMETERINDEX ON TB_CHANGEAMMETER (CHANGEAMMETER_MODULENO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //�����Զ�פ������
   m_Sqlstr= "CREATE INDEX TB_DateAutoINDEX ON TB_DateAuto (Auto_Parameter1)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //��������������
   m_Sqlstr= "CREATE INDEX TB_HANDINDEX ON TB_HAND (HAND_NO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //����פ����������
   m_Sqlstr= "CREATE INDEX TB_REFRESHTIMEINDEX ON TB_REFRESHTIME (USER_REFRESHTIME)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //����פ��ʱ������
   m_Sqlstr= "CREATE INDEX TB_HALTTIMEINDEX ON TB_HALTTIME (HALTTIME_TIME)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
   
   //������̨����
   m_Sqlstr= "CREATE INDEX TB_TRANSFORMERINDEX ON TB_TRANSFORMER (TRANSFORMER_NO)";
   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

   return TRUE;

}


//�õ����ֶεĸ���
short CIFRMView::GetFieldNumbers(CString m_DataName)
{	
	CDatabase              db;
	CString          m_Sqlstr;	
    short         nFields = 0;

    //�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db);
		//����û����ݱ�
		m_Sqlstr.Format("SELECT * FROM %s",m_DataName);
		rs.Open(CRecordset::forwardOnly,m_Sqlstr);
		//�õ��ֶθ���
		nFields = rs.GetODBCFieldCount( );
		rs.Close();
		db.Close();
	}
	
	return nFields;
}

//ͣ����͵紦��
void CIFRMView::OnStoporsend() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CELECTDEALDlg          DLG;
	CString         PassStr;
	int   m_records   =   0;
	
	if(DLG.DoModal() == IDOK)
	{
		
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		
		//��¼����
		m_records = CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition());
	
		switch(DLG.m_radio)
		{
		case 0:
			{	
				PassStr.Format("�����ѯ��ѡ���û���%d���ݵ��õ�״̬��",m_records);
				break;
			}
		case 1:
			{
				PassStr.Format("��ѯ��ѡ���û���%d���ݵ�ͣ�������",m_records);
				break;
			}
		case 2:
			{
				PassStr.Format("����ѡ���û���%d���ݵ��õ���",m_records);
				break;
			}
		case 3:
			{
				PassStr.Format("ͣ��ѡ���û���%d���ݵ��õ���",m_records);
				break;
			}
		case 4:
			{
				PassStr.Format("��ѡ���û���%d����������",m_records);
				break;
			}
		case 5:
			{
				PassStr.Format("��ѡ���û���%d����ȡ��������",m_records);
				break;
			}
		}
		
		if(MessageBox(PassStr," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	
		//����ѡ�໧��,��ְ汾 TRUE ���վ�汾  FALSE��ְ�
		if(AppInfo::Instance().m_WhichKind == FALSE)
		{	
			//ͣ�����
			//CString title        �б���
			//CString Result       ����
			//CString ConStr       ������Χ
			//BYTE    orders       ����ؼ���
			//BOOL    OnlyReadNot  TRUE  ֻ��û�в��Գ����ģ��
			//                     FALSE ��֮
			//int  times        ��ÿ��ģ��Ĵ���
			//BOOL OnlyOnce TRUE  �ö����һ��ģ��ʱֻ����һ��   FALSE ÿ��������һ��
			//int  MaxIValue    ���ֵ(Ϊд����ʱ��)
			//int  MinIValue    ��Сֵ
			//int  intervals    ��  ��
			
			//�����Ҫ���վִ��ͣ���������
			//��ʽ��BEGINS;���վ���;COMMAND:04:����1:����2;ENDS
			switch(DLG.m_radio)
			{
			case 0:
				{
					//�õ�״̬   
					//BEGINS;COMMAND:11:����1:����2:����3:����4:����5:����6:����7:����8:����9:����10;ENDS 
					//                  ����1---����         ����2---���                   ����3---������Χ
					//                  ����4---������       ����5---�Ƿ�ֻ���಻��         ����6---����        
					//                  ����7---�Ƿ�ֻ��һ�� ����8---��Сֵ(Ҳ������ʱ����) ����9---���ֵ  
					//                  ����10--���         ��д������Բ���,����������
					//                  ����11               ����������¼����
				    PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","�õ�״̬","��ѯ�ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(),0xf4,FALSE,5,1,1,1,1,m_records);
					break;
				}
			case 1:
				{
					//ģ��ͣ�����
				    PassStr.Format("BEGINS;COMMAND:11:%s:%s:%s:%d:%d:%d:%d:%d:%d:%d:%d;ENDS","ͣ�����","��ѯ�ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(),0x3C,FALSE,5,1,1,1,1,m_records);
					break;
				}
			case 2:
				{
					//�͵�
					PassStr.Format("BEGINS;COMMAND:05:%s:%d;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition(),m_records);
					break;
				}
			case 3:
				{
					//ͣ��
					PassStr.Format("BEGINS;COMMAND:04:%s:%d;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition(),m_records);
					break;
				}
			case 4:
				{
					//����
					PassStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			        CDataBaseInstance::ExecuteDataBaseSQL(PassStr);
					PassStr.Format("BEGINS;COMMAND:35:%s;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition());
					break;
				}
			case 5:
				{
					//ȡ������
					PassStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
			        CDataBaseInstance::ExecuteDataBaseSQL(PassStr);
					PassStr.Format("BEGINS;COMMAND:36:%s;ENDS",pMainFrm->m_wndMyDialogBar.SelectCondition());
					break;
				}

			}	
			
			//Զ�̷���ͣ���͵��ָ��
			SelectSendString(m_sendkind, PassStr, TRUE,TRUE,TRUE);
					
		}
		else
		{
			//ͣ���͵����  TRUE ���վ��  FALSE ��ְ�
			switch(DLG.m_radio)
			{
			case 0:
				{
					//
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","�õ�״̬","��ѯ�ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf4,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 1:
				{
					//
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","ͣ�����","��ѯ�ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0x3C,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 2:
				{
					//�͵����
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","�͵����","�͵�ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf6,FALSE,5,TRUE,1,1,1);
					break;
				}
			case 3:
				{
					//ͣ�����
					SendContionStr.Format("%s;%s;%s;%d;%d;%d;%d;%d;%d;%d","ͣ�����","ͣ��ɹ�",pMainFrm->m_wndMyDialogBar.SelectCondition(), 0xf8,FALSE,5,TRUE,1,1,1);
					break;
				}

			}
			
			if(DLG.m_radio <= 3)
			{
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)3,m_Thread_PRIORITY,0,0,NULL); // ����������
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
			}
			else
			{
				
				switch(DLG.m_radio)
				{
				case 4:
					{
						//����
						SendContionStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
						CDataBaseInstance::ExecuteDataBaseSQL(SendContionStr);
						MessageBox("��ѡ�û������ɹ���","  ",MB_OK|MB_ICONASTERISK);
						break;
					}
				case 5:
					{	
						//ȡ������
						SendContionStr.Format("UPDATE TB_USER SET USER_RUNSTATUS=0 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
						CDataBaseInstance::ExecuteDataBaseSQL(SendContionStr);
						MessageBox("��ѡ�û�ȡ�������ɹ���","  ",MB_OK|MB_ICONASTERISK);
						break;
					}
				}
				
			}
			
		}
		
	}
	
}


void CIFRMView::OnUpdateStoporsend(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
	
}

void CIFRMView::EverySendInfo()
{
   WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	
	//����������ֵĻ�	
	if(m_status)
	{
		
		CByteArray  m_ByteSendOnce;	
		m_ByteSendOnce.Add(62);
		m_ByteSendOnce.Add(62);
		m_ByteSendOnce.Add(71);
		m_ByteSendOnce.Add(72);
		m_ByteSendOnce.Add(32);
		m_ByteSendOnce.Add(22);
		
		//�ܹ����ı�־
		m_StartRead    =  TRUE;
		
		//�ö���Э�飬ÿһ�ֶ���һ��
		for(int kk = 0; kk < m_ByteSendOnce.GetSize(); kk ++)
		{
			
			//ĸ�߶���
			for(int j = 0; j < 2; j++)
			{
				
				
				//����� ABC
				for(int i = 0; i < 3; i++)
				{
					
					if(!m_StartRead)
					{
						break;
					}
					
					//ABC���෢ָ��,һ��ģ���Ϊ0���ź�
					switch(i)
					{
					case 0:
						{   
							StatusStr.Format("���������ֵ���[%d]վ��[%d]��ĸ��A�࣬Э��[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					case 1:
						{   
							StatusStr.Format("���������ֵ���[%d]վ��[%d]��ĸ��B�࣬Э��[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					case 2:
						{
							StatusStr.Format("���������ֵ���[%d]վ��[%d]��ĸ��C�࣬Э��[%d]...",m_handno,j + 1,m_ByteSendOnce[kk]);
							break;
						}
					}
					
					//״̬������ʾ��Ϣ
					SendMessage(WM_EVENT, 1, 0);
					
					//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
					//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
					//SendMessage(WM_EVENT, 5, 0);
					
					if(!(SendOrderToSCM(0/*ģ���*/,m_handno/*�����ֵ�վ��*/,j + 1/*ĸ��*/,1/*�ߺ�*/, i/*��ѡ��0A 1B 2C*/, 3/* ��ʱ��0����*/,0xC0/* Ҫʲô����,������*/,0/*�ɷ�ʱ�����������*/,m_ByteSendOnce[kk],0)))
					{
						Beep(300,400);
						Beep(300,400);
					}
					
					//�ȴ�ʱ��
					BYTE  m_SendTimers  =    0;
					
					if(m_ByteSendOnce[kk] == 22)
					{
						m_SendTimers =  8;
					}
					else
					{
						m_SendTimers = (m_ByteSendOnce[kk]%10)*8;
					}
					
					for(BYTE jj = 0 ; jj < m_SendTimers; jj ++)
					{
						SurrenderWindowMessage();
						
						if(m_StartRead)
						{
							Sleep(1000);
						}
						else
						{
							break;
						}
						
					}	
					
					//���͵��ַ���Զ�̻�������ʾBEGINS;MESSAGE:1:����;ENDS   ״̬����ʾ��Ϣ
					//SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS","");
					//SendMessage(WM_EVENT, 5, 0);	
					
				}
				
			}
			
		}
	
    }
		
		
	//���Ҫ��·������
	CTime timet = CTime::GetCurrentTime();
	
	if(timet.GetMinute() < 30)
	{
		//��·������
		SendMessage(WM_EVENT, 15, 0);

		//����ģ��������ѹ���
//		SendMessage(WM_EVENT, 17, 0);	
		
		//����޹����������
		SendMessage(WM_EVENT, 18, 0);

	}
	
//	m_StartRead = FALSE;

   TmpOnlyOneThreadRun.SetEvent();


}

void CIFRMView::OnUpdateDataappear(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());	
	
}

//������ͳ��
void CIFRMView::BeginTotalLoss(CString m_Condtion,CString BeginTime,CString EndTime)
{	
	
	CDatabase                db;
	CString  m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,strsql;
	double         supplys,sales;
	int    doors       =       0;//����
	int    m_records   =       0;//��¼��
   
	//�жϱ��Ƿ����
	if(IsCurveTableExist("TB_TOTLE"))
	{
		//ɾ��ԭ���ı�
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
	}
	
	//������ʱ��
    strsql.Format("SELECT * INTO TB_TOTLE FROM TB_USER WHERE %s",m_Condtion);
    CDataBaseInstance::ExecuteDataBaseSQL(strsql);

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		CDaoDatabase* m_pDatabase = new CDaoDatabase();
        m_pDatabase->Open(NULL,FALSE,FALSE,db.GetConnect());
		db.Close( );
		
		//��˾����ʼ
		CDaoRecordset m_CompanySet(m_pDatabase);
		strsql = "SELECT count(*)  FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
		m_CompanySet.Open(dbOpenSnapshot,strsql);
		
		m_records = V_I4(&m_CompanySet.GetFieldValue(0));
        m_CompanySet.Close();
	
		strsql = "SELECT USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO FROM TB_TOTLE  GROUP BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO ORDER BY USER_COMPANY,USER_STATIONNAME,USER_LINENAME,USER_TRANSFORMERNO";
        m_CompanySet.Open(dbOpenSnapshot,strsql);

	    ShowProgressCtrl(TRUE);
        SetProgressCtrlRange(0, m_records,1);
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			m_CompanyName    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(0));
            m_STATIONNAME    = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(1));
            m_LINENAME       = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(2));
            m_TRANSFORMERNO  = (LPTSTR)(LPCTSTR)V_I4(&m_CompanySet.GetFieldValue(3));
			
			status("���ڼ����̨����:" + m_TRANSFORMERNO);
			//������
			supplys = GetSubElc("SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE*TB_USER.USER_MULTIPLE)",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,0,BeginTime,EndTime);
			//�۵���
			sales   = GetSubElc("SUM(TB_GARRISONBAK.GARRISON_WORKDEGREE*TB_USER.USER_MULTIPLE)",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO,1,BeginTime,EndTime);
			//��̨�µĻ���ĳ
			strsql.Format("USER_COMPANY='%s' AND USER_STATIONNAME='%s' AND USER_LINENAME='%s' AND USER_TRANSFORMERNO='%s' AND USER_AMMETERKIND<2 ",m_CompanyName,m_STATIONNAME,m_LINENAME,m_TRANSFORMERNO);
			//����
			doors   = CDataBaseInstance::GetAllRecordsCount("TB_TOTLE",strsql);
			
			//��������û���ר��������û�
			if(doors > 0)
			{
				
				//�������������0
				if(supplys > 0)
				{
					strsql.Format("INSERT INTO TB_ELECTRICITYLOSS(����,��̨����,����,���¹�����,�����۵���,��ʧ����,������) VALUES (%d,'%s',%d,%.2f,%.2f,%.2f,%.2f)",doors,m_TRANSFORMERNO,SubCapability(m_TRANSFORMERNO),supplys,sales,supplys-sales,(supplys-sales)*100.0000/supplys);
				}
				else
				{	
					strsql.Format("INSERT INTO TB_ELECTRICITYLOSS(����,��̨����,����,���¹�����,�����۵���,��ʧ����) VALUES (%d,'%s',%d,%.2f,%.2f,%.2f)",doors,m_TRANSFORMERNO,SubCapability(m_TRANSFORMERNO),supplys,sales,supplys-sales);
				}
				
				CDataBaseInstance::ExecuteDataBaseSQL(strsql);

			}
		
			m_CompanySet.MoveNext();
            SetProgressCtrlSetIt();

		}

		m_CompanySet.Close();
		delete m_pDatabase;	
		
		//ɾ��ԭ���ı�
		strsql.Format("DROP TABLE %s","TB_TOTLE");
		CDataBaseInstance::ExecuteDataBaseSQL(strsql);
		ShowProgressCtrl(FALSE);
	}

}


//�õ�ĳ��̨������ܱ�ֵ�������о����ʹ��û���ĺ�
//CString FieldName       �����ֶ��� TB_GARRISON.GARRISON_WORKDEGREE
//CString CompanyName     ��˾��
//CString SubstationName  ���վ��
//int     SubNo           ��̨��  
//CString LineName        ��·����
//CString SubNo           ��̨��
//short   kinds           ���� 0����������ı�ֵ 1�����������о�������û���ı�� 
double CIFRMView::GetSubElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,CString SubNo,short kinds,CString BeginTime,CString EndTime)
{
    //�����ݿ�
	CString   strValue;
	CDatabase       db;	
	CString     strSql;
	double   sum1,sum2;
    sum1 = sum2    = 0;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{	
		
		//��CRecordset����
		CRecordset rs(&db);
	
		if(kinds == 0)
		{
			//ĳ��̨����ı�ֵ
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4) ",Order,CompanyName,SubstationName,LineName,SubNo,BeginTime);
		}
		else
		{	
			//ͳ���������о�������û���ı��
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND TB_USER.USER_AMMETERKIND<2 ",Order,CompanyName,SubstationName,LineName,SubNo,BeginTime);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		rs.GetFieldValue((short)0,strValue);
		sum1 = atof(strValue);
		rs.Close( );

		
		if(kinds == 0)
		{
			//ĳ��̨����ı�ֵ
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND (TB_USER.USER_AMMETERKIND=2 OR TB_USER.USER_AMMETERKIND=4) ",Order,CompanyName,SubstationName,LineName,SubNo,EndTime);
		}
		else
		{	
			//ͳ���������о�������û���ı��
			strSql.Format("SELECT %s FROM TB_USER,TB_GARRISONBAK WHERE TB_USER.USER_COMPANY='%s' AND TB_USER.USER_STATIONNAME='%s' AND TB_USER.USER_LINENAME='%s' AND TB_USER.USER_TRANSFORMERNO='%s' AND TB_GARRISONBAK.GARRISON_MODULENO=TB_USER.USER_MODULENO AND TB_GARRISONBAK.GARRISON_HALTTIME='%s'  AND TB_USER.USER_AMMETERKIND<2 ",Order,CompanyName,SubstationName,LineName,SubNo,EndTime);
		}

		rs.Open(CRecordset::forwardOnly,strSql);
		
		rs.GetFieldValue((short)0,strValue);
		sum2 = atof(strValue);
		rs.Close( );
		

		db.Close( );

		return sum2-sum1;
	}

	return 0;
}


//�õ�ĳһ��̨������
long CIFRMView::SubCapability(CString SubNo)
{   //�����ݿ�
	CDatabase         db;
	CString       strSql;
	CString     strValue = "";
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		if(SubNo.IsEmpty())
		{
       	    strSql = "SELECT count(*) FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT count(*) FROM TB_TRANSFORMER WHERE TRANSFORMER_NO='%s'",SubNo);
			
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		
		//��¼����
		long fields = atol(strValue); 
		rs.Close();
		
		if(SubNo.IsEmpty())
		{
       	    strSql = "SELECT TRANSFORMER_CAPACITY FROM TB_TRANSFORMER";
		}
		else
		{
			strSql.Format("SELECT TRANSFORMER_CAPACITY FROM TB_TRANSFORMER WHERE TRANSFORMER_NO='%s'",SubNo);
		}
		
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j++)
		{
			rs.GetFieldValue((short)0,strValue);
			strValue.TrimLeft();
			strValue.TrimRight();
			
			//���»�һ����¼
			rs.MoveNext();
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
	}

	return atol(strValue);
}


//�޸ı������
BOOL CIFRMView::ModifyDataTable(CString m_TableName,CString m_TableSql,BOOL m_CheckRecords)
{

	//�����ݿ�
	CDatabase                             db;
	CString             m_Sqlstr,m_FieldName;
	int                             k,j,kkkk;
	CStringArray               TableColTitle;
    CStringArray     TableColTitleTempupdate;
    CStringArray               EqualColTitle;
	CString                              str;
	int                                    i;
	long     m_BeforeRecords, m_AfterRecords;
	m_BeforeRecords = m_AfterRecords    =  0;
	
	//////////////////////���������Ϣ/////////////////////
	//�жϱ��Ƿ����
	if(!IsCurveTableExist(m_TableName))
	{
		//�����ڵĻ�,����
		CDataBaseInstance::ExecuteDataBaseSQL(m_TableSql);
		return TRUE;
		
	}
	else
	{
		
		if(IsCurveTableExist("TEMPUPDAE"))
		{
			m_Sqlstr.Format("DROP FROM TEMPUPDAE");
			CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		}

		//֮ǰ�ļ�¼��
		m_BeforeRecords = CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL");
		//m_AfterRecords
		
		m_Sqlstr.Format("SELECT *  INTO TEMPUPDAE FROM %s",m_TableName);
	
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		m_Sqlstr.Format("Drop TABLE  %s",m_TableName);
		CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);

		//�����µı�
		CDataBaseInstance::ExecuteDataBaseSQL(m_TableSql);
	
		if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
		{
			//��CRecordset����
			CRecordset rs(&db );
			m_Sqlstr.Format("SELECT DISTINCT * FROM %s",m_TableName);
			rs.Open(CRecordset::forwardOnly,m_Sqlstr);
			
			//�õ��ֶθ���
			short nFields = rs.GetODBCFieldCount( );
			CODBCFieldInfo fieldinfo;
			
			for(int i = 0;i < nFields; i++)
			{
				//�ֶ���
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_FieldName = fieldinfo.m_strName;
				m_FieldName.TrimLeft();
				m_FieldName.TrimRight();
				
				if(m_FieldName.Find("��") != -1  || m_FieldName.Find("-") != -1)
				{
					
					m_FieldName = "[" + m_FieldName + "]";
					
				}
				
				TableColTitle.Add(m_FieldName);
			}
			rs.Close( );
			
			//ԭ���ı�
			m_Sqlstr.Format("SELECT DISTINCT * FROM %s","TEMPUPDAE");
			rs.Open(CRecordset::forwardOnly,m_Sqlstr);
			
			//�õ��ֶθ���
			nFields = rs.GetODBCFieldCount( );
			
			for( i = 0;i < nFields; i++)
			{
				//�ֶ���
				rs.GetODBCFieldInfo(i,fieldinfo);
				m_FieldName = fieldinfo.m_strName;
				m_FieldName.TrimLeft();
				m_FieldName.TrimRight();
				
				if(m_FieldName.Find("��") != -1  || m_FieldName.Find("-") != -1)
				{
					
					m_FieldName = "[" + m_FieldName + "]";
					
				}
				
				TableColTitleTempupdate.Add(m_FieldName);
			}
			rs.Close( );
			db.Close( );
			
			//�±���ֶ���
			k  =  TableColTitle.GetSize();
			//�ϱ���ֶ���
			j  =  TableColTitleTempupdate.GetSize();
			
			for(i = 0;i < j ;i ++)
			{
				
				for(int l = 0;l < k ;l ++)
				{
					
					//�����ȵĻ�
					if(TableColTitle[l] == TableColTitleTempupdate[i])
					{
						
						//������ͬ���ֶ���
						EqualColTitle.Add(TableColTitle[l]);
						
						if(TableColTitle[l].Find("��") != -1  || TableColTitle[l].Find("-") != -1)
						{
							m_FieldName = TableColTitle[l];
						}
						else
						{
							m_FieldName = "[" + TableColTitle[l] + "]";
						}
						
						kkkk = m_TableSql.Find(m_FieldName);
						
						
						//����д��ַ�
						if(kkkk != -1)
						{
							str  = m_TableSql.Right(m_TableSql.GetLength() - kkkk - m_FieldName.GetLength());
							kkkk = str.Find("NULL");
							
							//����д��ַ�
							if(kkkk != -1)
							{
								
								// �޸��ֶΣ�
								// ALTER TABLE [����] ALTER COLUMN [�ֶ���] NVARCHAR (50) NULL
								str = str.Left(kkkk + 4);
								//WriteToLog("�ֶ���:" + TableColTitle[l]);
								m_FieldName.Format("ALTER TABLE TEMPUPDAE ALTER COLUMN %s %s",TableColTitle[l],str);
								
								//WriteToLog(m_FieldName);
								//�����µı�
								CDataBaseInstance::ExecuteDataBaseSQL(m_FieldName);
								
							}
							
						}
						
					}
					
				}
				
			}
			
	   }
	
	   //����ͬ���ֶ�
	   if(EqualColTitle.GetSize() > 0)
	   {
		   
		   str = "";
		   k   = EqualColTitle.GetSize();
		   
		   for(i = 0; i < k;i ++)
		   {
			   
			   if(i == k -1)
			   {
				   str = str + EqualColTitle[i];
			   }
			   else
			   {
				   str = str + EqualColTitle[i] + ",";
			   }
			   
		   }	
		   
		   //������������
		   m_Sqlstr.Format("INSERT %s(%s) SELECT DISTINCT %s FROM TEMPUPDAE",m_TableName,str,str);
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
	   }
	   
	   //Ҫ�������ǰ�������
	   if(!m_CheckRecords)
	   {  
		   //ɾ����ʱ��
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   return TRUE;
	   }

	   //֮ǰ�ļ�¼��
	   m_AfterRecords = CDataBaseInstance::GetAllRecordsCount("TB_USER", "ALL");
		
	   //������ּ�¼����ȵĻ�
	   if(m_BeforeRecords == m_AfterRecords)
	   { 
		   //ɾ����ʱ��
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   //�ɹ��޸�
		   return  TRUE;
	   }
	   else
	   {
		   //���ɹ��Ļ���ԭ��ԭ�������ݿ�
		   if(IsCurveTableExist(m_TableName))
		   {
			   m_Sqlstr.Format("DROP TABLE  %s",m_TableName);
			   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr); 
		   }
		   
		   //��ԭ���ݿ�
		   m_Sqlstr.Format("SELECT *  INTO %s FROM TEMPUPDAE",m_TableName);
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
		   //ɾ����ʱ��
		   m_Sqlstr = "Drop TABLE  TEMPUPDAE";
		   CDataBaseInstance::ExecuteDataBaseSQL(m_Sqlstr);
		   
		   //�޸�ʧ��
		   return FALSE;
	   }

	}
}

void CIFRMView::OnUpdateListselect(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
	
}

//���ɸ��ֲ���ͳ�Ʊ�
void CIFRMView::ComingIntoBeing(CString SqlStr,CString m_begin, CString m_End, BOOL m_yg, BOOL m_wg, BOOL m_jz, BOOL m_fz, BOOL m_gz, BOOL m_pz,  BOOL m_dy, BOOL m_dl)
{
	CString           Str;
	status("�������ɸ�������ͳ�Ʊ����Ժ�...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
	
	if(IsCurveTableExist("TB_TOTAL"))
	{
		//ɾ��ԭ���Ŀ��
		Str.Format("DROP TABLE TB_TOTAL");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	Str = "CREATE TABLE [dbo].[TB_TOTAL] (\
											[��̨����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
											[�û����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
											[�û�����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
											[ԭ�û����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
											[ģ���]   [bigint] NULL ,\
											[����]     [int] NULL ,\
											[�õ�����] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
											[�ϴ��й�] [float] NULL ,\
											[�����й�] [float] NULL ,\
											[�й���ֵ] [float] NULL ,\
											[�ϴ��޹�] [float] NULL ,\
											[�����޹�] [float] NULL ,\
											[�޹���ֵ] [float] NULL ,\
											[�ϴη�ֵ] [float] NULL ,\
											[���η�ֵ] [float] NULL ,\
											[��ֵ��]   [float] NULL ,\
											[�ϴι�ֵ] [float] NULL ,\
											[���ι�ֵ] [float] NULL ,\
											[�Ȳ�ֵ]   [float] NULL ,\
											[�ϴ�ƽֵ] [float] NULL ,\
											[����ƽֵ] [float] NULL ,\
											[ƽֵ��]   [float] NULL ,\
											[���μ�ֵ] [float] NULL ,\
											[�ϴμ�ֵ] [float] NULL ,\
											[��ֵ��]   [float] NULL ,\
											[A���ѹ]  [float] NULL ,\
											[B���ѹ]  [float] NULL ,\
											[C���ѹ]  [float] NULL ,\
											[A�����]  [float] NULL ,\
											[B�����]  [float] NULL ,\
											[C�����]  [float] NULL \
											) ON [PRIMARY]";
	
	//�������ݱ�
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	SetProgressCtrlSetIt();
	

	//�˴ζ�������SQL����õ����
	Str.Format("INSERT TB_TOTAL(��̨����,�û����,�û�����,ԭ�û����,\
								ģ���,����,�õ�����,\
							   �ϴ��й�,�����й�,�й���ֵ,\
							   �ϴ��޹�,�����޹�,�޹���ֵ,\
							   �ϴη�ֵ,���η�ֵ, ��ֵ��,\
							   �ϴι�ֵ,���ι�ֵ,�Ȳ�ֵ,\
							   �ϴ�ƽֵ,����ƽֵ,ƽֵ��,\
							   ���μ�ֵ,�ϴμ�ֵ,��ֵ��,\
							   A���ѹ,B���ѹ,C���ѹ,\
							   A�����,B�����,C�����)\
		               SELECT  RTRIM(LTRIM(a.USER_TRANSFORMERNO)),RTRIM(LTRIM(a.USER_NO)),RTRIM(LTRIM(a.USER_NAME)),RTRIM(LTRIM(a.USER_OLDNO)),a.USER_MODULENO,a.USER_MULTIPLE,f.ELECTRICITY_KIND,\
					           d.GARRISON_WORKDEGREE,e.GARRISON_WORKDEGREE,ROUND((e.GARRISON_WORKDEGREE-d.GARRISON_WORKDEGREE)*a.USER_MULTIPLE,2),\
							   d.GARRISON_LOSEDEGREE,e.GARRISON_LOSEDEGREE,ROUND((e.GARRISON_LOSEDEGREE-d.GARRISON_LOSEDEGREE)*a.USER_MULTIPLE,2),\
							   d.GARRISON_FDL       ,e.GARRISON_FDL       ,ROUND((e.GARRISON_FDL       -d.GARRISON_FDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_GDL       ,e.GARRISON_GDL       ,ROUND((e.GARRISON_GDL       -d.GARRISON_GDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_PDL       ,e.GARRISON_PDL       ,ROUND((e.GARRISON_PDL       -d.GARRISON_PDL)*a.USER_MULTIPLE,2),\
		                       d.GARRISON_JFDL      ,e.GARRISON_JFDL      ,ROUND((e.GARRISON_JFDL      -d.GARRISON_JFDL)*a.USER_MULTIPLE,2),\
                               e.GARRISON_AVOLTAGE  ,e.GARRISON_BVOLTAGE  ,e.GARRISON_CVOLTAGE,\
                               e.GARRISON_ACURRENT  ,e.GARRISON_BCURRENT  ,e.GARRISON_CCURRENT\
							   FROM TB_USER a ,TB_GARRISONBAK d,TB_GARRISONBAK e,TB_ELECTRICITY f WHERE (%s) AND f.ELECTRICITY_NO=a.USER_ELECTRICITYKIND AND d.GARRISON_MODULENO=a.USER_MODULENO AND e.GARRISON_MODULENO=a.USER_MODULENO  AND d.GARRISON_HALTTIME='%s' AND e.GARRISON_HALTTIME='%s'",SqlStr,m_begin,m_End);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

	//WriteToLog(Str);
    SetProgressCtrlSetIt();
	
	//�й�
	if(!m_yg)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN �ϴ��й�,�����й�,�й���ֵ";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//�޹�
	if(!m_wg)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN �ϴ��޹�,�����޹�,�޹���ֵ";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//��
	if(!m_fz)
	{	
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN �ϴη�ֵ,���η�ֵ,��ֵ��";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//��
	if(!m_gz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN �ϴι�ֵ,���ι�ֵ,�Ȳ�ֵ";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//ƽ
	if(!m_pz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN �ϴ�ƽֵ,����ƽֵ,ƽֵ��";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//��
	if(!m_jz)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN ���μ�ֵ,�ϴμ�ֵ,��ֵ��";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//��ѹ
	if(!m_dy)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN A���ѹ,B���ѹ,C���ѹ";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	//����
	if(!m_dl)
	{
		Str= "ALTER TABLE TB_TOTAL DROP COLUMN A�����,B�����,C�����";
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  
}


//�õ�������
void CIFRMView::ElectricityWarning(CString SqlStr,CString m_begin, CString m_End)
{
	CString        Str,strValue;
	status("���������õ籨��ͳ�Ʊ����Ժ�...");
	ShowProgressCtrl(TRUE);
	SetProgressCtrlRange(0, 3,1);
    
	m_begin.TrimLeft();
    m_End.TrimRight();

	int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
    CTimeSpan                     ts; 
	long       m_TotalSeconds  =   0;
    double     m_kx            =   0;//�·���

	//ʱ�䴦��
	strValue  = m_begin;
	int k     = strValue.Find('-');
	//��
	m_years   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
    strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k         = strValue.Find('-');
	m_months  = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
    strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k         = strValue.Find(' ');
	m_days    = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//ʱ
	k         = strValue.Find(':');
	m_hours   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k = strValue.Find(':');
	m_minutes = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	m_seconds = atoi(strValue);
    
	CTime m_begintime(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);//�ϴ�ʱ��
   
	strValue  = m_End;
	k     = strValue.Find('-');
	//��
	m_years   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k         = strValue.Find('-');
	m_months  = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k         = strValue.Find(' ');
	m_days    = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//ʱ
	k         = strValue.Find(':');
	m_hours   = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	k = strValue.Find(':');
	m_minutes = atoi(strValue.Left(k));
	strValue  = strValue.Right(strValue.GetLength() - k - 1);
	strValue.TrimLeft();
    strValue.TrimRight();

	//��
	m_seconds = atoi(strValue);

	CTime m_endtime(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);//����ʱ��
    
	//ʱ���
	ts              =  m_endtime - m_begintime;
	m_TotalSeconds  =  ts.GetTotalSeconds();//ʱ���(��)

	//��������
	m_kx            =  m_TotalSeconds*1.0000/(24*3600*30);
 
	if(m_kx <= 0)
	{
        return;
	}

	//����
	if(IsCurveTableExist("TB_WARN"))
	{
		//ɾ��ԭ���Ŀ��
		Str.Format("DROP TABLE TB_WARN");
		CDataBaseInstance::ExecuteDataBaseSQL(Str);
	}
	
	Str = "CREATE TABLE [dbo].[TB_WARN] (\
			[���վ����] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[��·����] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[��̨����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[ģ���] [bigint] NULL ,\
			[�û����] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[ԭ�û���] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[�û�����] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[�û���ַ] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[�ϴ��õ�] [float] NULL ,\
			[�����õ�] [float] NULL ,\
			[�õ��] [float] NULL ,\
			[�±�������] [int] NULL ,\
			[�±�������] [int] NULL ,\
			[����ԭ��] [char] (16) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
		
	//�������ݱ�
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	SetProgressCtrlSetIt();
	
	//�˴ζ�������SQL���
	Str.Format("INSERT TB_WARN(���վ����,��·����,��̨����,ģ���,�û����,ԭ�û���,�û�����,�û���ַ,�ϴ��õ�,�����õ�,�õ��,�±�������,�±�������)\
		        SELECT a.USER_STATIONNAME,a.USER_LINENAME,a.USER_TRANSFORMERNO,\
					   a.USER_MODULENO,a.USER_NO,a.USER_OLDNO,a.USER_NAME,a.USER_ADDRESS,b.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE,a.USER_DOWNVALUE,a.USER_UPVALUE\
					   FROM TB_USER a ,TB_GARRISONBAK b,TB_GARRISONBAK c WHERE (%s) AND b.GARRISON_MODULENO=a.USER_MODULENO AND c.GARRISON_MODULENO=a.USER_MODULENO  AND b.GARRISON_HALTTIME='%s' AND c.GARRISON_HALTTIME='%s' AND a.USER_DOWNVALUE>=0 AND a.USER_UPVALUE>=0 AND ((c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)>(a.USER_UPVALUE*%f) OR (c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<(a.USER_DOWNVALUE*%f))",SqlStr,m_begin,m_End,m_kx,m_kx);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);
	
	SetProgressCtrlSetIt();
	Str.Format("UPDATE  TB_WARN SET ����ԭ�� = '���������趨����' WHERE  (�����õ�-�ϴ��õ�)>(�±�������*%f)",m_kx);
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	Str.Format("UPDATE  TB_WARN SET ����ԭ�� = '����С���趨����' WHERE  (�����õ�-�ϴ��õ�)<(�±�������*%f)",m_kx);
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	//������޺����޶��ǿ�
	Str.Format("INSERT TB_WARN(���վ����,��·����,��̨����,ģ���,�û����,ԭ�û���,�û�����,�û���ַ,�ϴ��õ�,�����õ�,�õ��,�±�������,�±�������)\
		        SELECT a.USER_STATIONNAME,a.USER_LINENAME,a.USER_TRANSFORMERNO,\
					   a.USER_MODULENO,a.USER_NO,a.USER_OLDNO,a.USER_NAME,a.USER_ADDRESS,b.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE,c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE,a.USER_DOWNVALUE,a.USER_UPVALUE\
					   FROM TB_USER a ,TB_GARRISONBAK b,TB_GARRISONBAK c WHERE (%s) AND b.GARRISON_MODULENO=a.USER_MODULENO AND c.GARRISON_MODULENO=a.USER_MODULENO  AND b.GARRISON_HALTTIME='%s' AND c.GARRISON_HALTTIME='%s' AND a.USER_DOWNVALUE IS NULL AND a.USER_UPVALUE IS NULL AND ((c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<0.001 OR (c.GARRISON_WORKDEGREE-b.GARRISON_WORKDEGREE)<0.001)",SqlStr,m_begin,m_End);
	CDataBaseInstance::ExecuteDataBaseSQL(Str);

	Str = "UPDATE TB_WARN SET ����ԭ�� = 'ģ����û������' WHERE  (�����õ�-�ϴ��õ�)<0.001";
    CDataBaseInstance::ExecuteDataBaseSQL(Str);

	SetProgressCtrlSetIt();
	ShowProgressCtrl(FALSE);  
}


//��鵱ǰ��ʱ����ȷ����ʱ����ĸ���״̬
//����0 - ����30  Ϊ�����Ĳ�����������
//����31- ����61  Ϊ���û��Ĳ����������� 
//����62- ����92  Ϊ���û��Ĳ�����������
//����93- ����102 Ϊ��������
//����103         Ϊ����ʱ�̵�
//��鶨ʱ��״̬
//����ֵ 0-----û��  1----��פ����ʱ��  2-----�����ʱ��  3-�޹���������
short CIFRMView::CheckCurrentTime()
{   
//	CString                        m_SqlStr,str;
//	CTime m_CurrentTimes = CTime::GetCurrentTime();	 	
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��ʼ���״̬0",m_CurrentTimes.GetYear(),m_CurrentTimes.GetMonth(),m_CurrentTimes.GetDay(),m_CurrentTimes.GetHour(),m_CurrentTimes.GetMinute(),m_CurrentTimes.GetSecond());
//	WriteToLog(str);

	if(!m_IsAutoSending)
	{
		return 0;
	}	
	
/*	if(ReadMeterThread != NULL)
	{
		//����
		if(ReadMeterThread->SuspendThread() != 0xFFFFFFFF)
		{
			m_Pause  = TRUE;
		}
		else
		{
			m_Pause  = FALSE;
		}
		
	}
*/
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��ʼ���״̬1",m_CurrentTimes.GetYear(),m_CurrentTimes.GetMonth(),m_CurrentTimes.GetDay(),m_CurrentTimes.GetHour(),m_CurrentTimes.GetMinute(),m_CurrentTimes.GetSecond());
//	WriteToLog(str);
	
	//������ʱ��
	CTime                         m_CurrentTime;//����ʱ�����
    CTimeSpan                                ts;//ʱ���϶
	CByteArray          m_TimeArray,m_TempArray;//������������
	int                        m_years,m_months;
	BYTE m_LastMonths,m_ThisMonths,m_NextMonths;
	int i;
	for( i = 0; i < 31; i ++)
	{
		
		//�����������
		if(m_parameter[i] || m_parameter[31 + i] || m_parameter[62 + i] )
		{

			m_TimeArray.Add(i+1);

		}

	}
	
	//���û�ж����������˳�
    if(m_TimeArray.GetSize() <= 0)
	{

		if(ReadMeterThread != NULL  && m_Pause)
		{
			//�����߳�
			ReadMeterThread->ResumeThread();
			m_Pause    =              FALSE;
		}

		return  0;
	}
	
	//��ȡ��ǰʱ��
	m_CurrentTime  = CTime::GetCurrentTime(); 

	//�õ������������
	m_LastMonths = GetMaxDays(0);

	//�õ������������
	m_ThisMonths = GetMaxDays(1);

	//�õ������������
	m_NextMonths = GetMaxDays(2);
	
  //m_SqlStr.Format("�����������:%d,�����������:%d,�����������:%d",m_LastMonths,m_ThisMonths,m_NextMonths);
  //WriteToLog(m_SqlStr);
 
	//  �� 1  4  28����� ����28 ����1  ����4  ����28 ����1��������ʱ���� 
	//���������һ������
	if(m_TimeArray[m_TimeArray.GetSize()-1] <= m_LastMonths)
	{
	    m_TempArray.Add(m_TimeArray[m_TimeArray.GetSize()-1]);
	}
	else
	{
		m_TempArray.Add(m_LastMonths);
	}

	//���µ�����
	for(i = 0; i < m_TimeArray.GetSize(); i ++)
	{	
		
		//�������ֻ��28��29��
		if(m_TimeArray[i] < m_ThisMonths)
		{
			m_TempArray.Add(m_TimeArray[i]);
		}
		else
		{
			m_TempArray.Add(m_ThisMonths);
			break;
		}
		
	}
	
	//�����µ���ǰһ�������
	if(m_TimeArray[0] <= m_NextMonths)
	{
	   m_TempArray.Add(m_TimeArray[0]);
	}
	else
	{
		m_TempArray.Add(m_NextMonths);
	}

	//����פ�������־
	SetGarrionLabel();
	
	//����Ƿ���Ӧ�÷�פ��
	for(i = 0 ; i < m_TempArray.GetSize() - 1; i ++)
	{	
		
		//��ʱ������·�
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//�ϸ��µ�ʱ��
		if(i == 0)
		{	
			
			if(m_months > 1)
			{
				//�·ݼ�1
				m_months = m_months - 1;
			}
			else
			{
				//���Ϊ1 �·ݣ�����
				m_years  = m_years - 1;
				m_months =          12;
			}

		}
		
		//��ʼʱ��
		CTime    m_Time1(m_years,m_months,m_TempArray[i],m_parameter[104],0,0);
		
		//��ʱ������·�
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//��һ���µ����� 
		if(i + 1 == m_TempArray.GetSize() - 1)
		{
           	
			if(m_months < 12)
			{
				//�·ݼ�1
				m_months = m_months + 1;
			}
			else
			{
				//���Ϊ12 �·ݣ�����
				m_years  = m_years + 1;
				m_months =           1;
			}

		}
		
		//����ʱ�� 
		CTime  m_Time2(m_years,m_months,m_TempArray[i+1],m_parameter[104],0,0);
		
		//�м�ʱ��	
		ts = m_Time2  -     m_Time1;
		ts = ts.GetTotalSeconds()/3*2;
		
		//�м�ʱ��
		CTime  m_MiddleTime = m_Time1 + ts;		
			
		//פ��m_Time2��ʱ�䷶Χ[�м�ʱ��-----����ʱ��],פ��ʱ������
		if((m_CurrentTime >= m_MiddleTime  && m_CurrentTime <= m_Time2))
		{
			//ʱ��2��ʱ��1��ʱ���
			ts  = m_Time2  - m_CurrentTime;
			
			if(ts.GetTotalSeconds() <= 86400 &&  ts.GetTotalSeconds() > 0)
			{	
				
				//��������
				if(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0)
				{
					//��פ��ʱ�䵽��,ȡ��פ��ʱ��
					m_AutoReadTime = m_Time2;
					
					if(ReadMeterThread != NULL  && m_Pause)
					{	
						//��פ��ʱ�䵽��,���ԭ���ڶ�����˳�����
						m_StartRead       =      FALSE;
						//�����߳�
						ReadMeterThread->ResumeThread();
						m_Pause  =                FALSE;
						
					}
					
					return   1;
				}
				else
				{
					switch(m_WgLess)
					{
						
					case 0:
						{
							//10����
							//�޹����������
							return     3;
							break;
						}
					case 1:
						{
							//20����
							if(((m_CurrentTime.GetMinute()/10)%2) == 0)
							{
								//�޹����������
								return     3;
							}
							
							break;
						}
				
					}

				}
				
			}
		
		}	
		
	}
 
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//����
		ReadMeterThread->ResumeThread();
		m_Pause      =            FALSE;
	}
    
	if(ReadMeterThread == NULL && !(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0))
	{
		//�޹����������
		switch(m_WgLess)
		{
			
		case 0:
			{
				//10����
				//�޹����������
				return     3;
				break;
			}
		case 1:
			{
				//20����
				if(((m_CurrentTime.GetMinute()/10)%2) == 0)
				{
					//�޹����������
					return     3;
				}
				
				break;
			}
		}
	
	}
	
	//��Сʱһ��������
	return 2;
}



//��鵱ǰ��ʱ����ȷ����ʱ����ĸ���״̬
//����ֵ 0-----û��  1----��פ����ʱ��  2-----�����ʱ��
short CIFRMView::ByDateCheckCurrentTime()
{
	
	if(!m_IsAutoSending)
	{
		return 0;
	}	
	
/*	if(ReadMeterThread != NULL)
	{
		//����ɹ�
		if(ReadMeterThread->SuspendThread() != 0xffffffff)
		{
			m_Pause  = TRUE;
		}
		else
		{
			m_Pause = FALSE;
		}

	}
*/
	//������ʱ��
	CTime                         m_CurrentTime;//����ʱ�����
    CTimeSpan                                ts;//ʱ���϶
	CByteArray          m_TimeArray,m_TempArray;//������������
    CString                        m_SqlStr,str;
	int                        m_years,m_months;
	BYTE m_LastMonths,m_ThisMonths,m_NextMonths;
	int i;
	for( i = 0; i < 31; i ++)
	{

		//�����������
		if(m_DateReadParameter[2*i] > 0)
		{

			m_TimeArray.Add(i+1);

		}

	}
	
	//���û�ж����������˳�
    if(m_TimeArray.GetSize() <= 0)
	{

		if(ReadMeterThread != NULL && m_Pause)
		{
			//�����߳�
			ReadMeterThread->ResumeThread();
			m_Pause    =              FALSE;
		}

		return  0;
	}
	
	//��ȡ��ǰʱ��
	m_CurrentTime  = CTime::GetCurrentTime(); 

	//�õ������������
	m_LastMonths = GetMaxDays(0);

	//�õ������������
	m_ThisMonths = GetMaxDays(1);

	//�õ������������
	m_NextMonths = GetMaxDays(2);
	
  //m_SqlStr.Format("�����������:%d,�����������:%d,�����������:%d",m_LastMonths,m_ThisMonths,m_NextMonths);
  //WriteToLog(m_SqlStr);
 
	//  �� 1  4  28����� ����28 ����1  ����4  ����28 ����1��������ʱ���� 
	//���������һ������
	if(m_TimeArray[m_TimeArray.GetSize()-1] <= m_LastMonths)
	{
	    m_TempArray.Add(m_TimeArray[m_TimeArray.GetSize()-1]);
	}
	else
	{
		m_TempArray.Add(m_LastMonths);
	}

	//���µ�����
	for(i = 0; i < m_TimeArray.GetSize(); i ++)
	{	
		
		//�������ֻ��28��29��
		if(m_TimeArray[i] < m_ThisMonths)
		{
			m_TempArray.Add(m_TimeArray[i]);
		}
		else
		{
			m_TempArray.Add(m_ThisMonths);
			break;
		}
		
	}
	
	//�����µ���ǰһ�������
	if(m_TimeArray[0] <= m_NextMonths)
	{
	   m_TempArray.Add(m_TimeArray[0]);
	}
	else
	{
		m_TempArray.Add(m_NextMonths);
	}

	//����Ƿ���Ӧ�÷�פ��
	for(i = 0 ; i < m_TempArray.GetSize() - 1; i ++)
	{	
		
		//��ʱ������·�
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//�ϸ��µ�ʱ��
		if(i == 0)
		{	
			
			if(m_months > 1)
			{
				//�·ݼ�1
				m_months = m_months - 1;
			}
			else
			{
				//���Ϊ1 �·ݣ�����
				m_years  = m_years - 1;
				m_months =          12;
			}

		}
		
		//��ʼʱ��
		CTime    m_Time1(m_years,m_months,m_TempArray[i],m_DateReadParameter[2*(m_TempArray[i]-1) + 1],0,0);
		
		//��ʱ������·�
        m_years   =   m_CurrentTime.GetYear();
		m_months  =   m_CurrentTime.GetMonth();
		
		//��һ���µ����� 
		if(i + 1 == m_TempArray.GetSize() - 1)
		{
           	
			if(m_months < 12)
			{
				//�·ݼ�1
				m_months = m_months + 1;
			}
			else
			{
				//���Ϊ12 �·ݣ�����
				m_years  = m_years + 1;
				m_months =           1;
			}

		}
		
		//����ʱ�� 
		CTime  m_Time2(m_years,m_months,m_TempArray[i+1],m_DateReadParameter[2*(m_TempArray[i+1]-1) + 1],0,0);
	
		//�м�ʱ��	
		ts = m_Time2  -     m_Time1;
		ts = ts.GetTotalSeconds()/3*2;
		
		//�м�ʱ��
		CTime  m_MiddleTime = m_Time1 + ts;		
			
		//פ��m_Time2��ʱ�䷶Χ[�м�ʱ��-----����ʱ��],פ��ʱ������
		if((m_CurrentTime >= m_MiddleTime  && m_CurrentTime <= m_Time2))
		{
			//ʱ��2��ʱ��1��ʱ���
			ts  = m_Time2  - m_CurrentTime;
			
			if(ts.GetTotalSeconds() <= 86400 &&  ts.GetTotalSeconds() > 0)
			{	

				//��������
				if(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0)
				{
					//��פ��ʱ�䵽��,ȡ��פ��ʱ��
					m_AutoReadTime = m_Time2;
					
					if(ReadMeterThread != NULL  && m_Pause)
					{	
						//��פ��ʱ�䵽��,���ԭ���ڶ�����˳�����
						m_StartRead       =      FALSE;
						//�����߳�
						ReadMeterThread->ResumeThread();
						m_Pause           =      FALSE;
						
					}	
					
					//�ͷ�CPUʱ��
					SurrenderWindowMessage();
					Sleep(2000);
					//�ͷ�CPUʱ��
					SurrenderWindowMessage();
					
					//����߳��˳���
					if(ReadMeterThread == NULL)
					{
						//��д��ʱ�����־
						ByDateSetGarrisonRange(m_TempArray[i+1]);
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���ֵΪ1,��פ��(%4d-%02d-%02d %02d:%02d:%02d)",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
					WriteToLog(str);
					
					return   1;
				}
				else
				{
					switch(m_WgLess)
					{
						
					case 0:
						{
							//10����
							//�޹����������
							return     3;
							break;
						}
					case 1:
						{
							//20����
							if(((m_CurrentTime.GetMinute()/10)%2) == 0)
							{
								//�޹����������
								return     3;
							}
							
							break;
						}
				
					}

				}

			}
		
		}	
		
	}
 
	//����߳�����ͣ��
	if(ReadMeterThread != NULL  && m_Pause)
	{
		//����
		ReadMeterThread->ResumeThread();
		m_Pause      =            FALSE;
	}
   
	if(ReadMeterThread == NULL && !(m_CurrentTime.GetMinute()/10 == 0 || ((m_CurrentTime.GetMinute()/10)%3) == 0))
	{
		//�޹����������
		switch(m_WgLess)
		{
			
		case 0:
			{
				//10����
				//�޹����������
				return     3;
				break;
			}
		case 1:
			{
				//20����
				if(((m_CurrentTime.GetMinute()/10)%2) == 0)
				{
					//�޹����������
					return     3;
				}
				
				break;
			}
		}
		
	}

	str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���ֵΪ2,��פ��",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	WriteToLog(str);

	return 2;
}


//д���������û�����̨��ȱ�Ĳ���
void CIFRMView::WriteToAllAmeterParameter()
{
	CString m_SqlStr,str;

	//ɾ��ԭ��������
	m_SqlStr = "DELETE FROM TB_Auto";
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);

	//�������
	m_SqlStr = "INSERT INTO TB_Auto(";
	int i;
	for( i = 1; i <= 110; i++)
	{
		if(i < 110)
		{
		   str.Format("Auto_Parameter%d,",i);
		}
		else
		{		   
			str.Format("Auto_Parameter%d",i);
		}
		m_SqlStr = m_SqlStr + str;
	}

	m_SqlStr = m_SqlStr + ")  VALUES("; 
	
	for( i = 0; i < 109; i++)
	{
		str.Format("%d,",m_parameter[i]);
		m_SqlStr = m_SqlStr + str;
	}
	
	str.Format("%d",m_parameter[109]);
	m_SqlStr = m_SqlStr + str + ")";
  
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
}

//д�밴�������ò�����פ��
void CIFRMView::WriteToParameterByDate()
{
	CString m_SqlStr,str;

	//ɾ��ԭ��������
	m_SqlStr = "DELETE FROM TB_DateAuto";
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);

	//�������
	m_SqlStr = "INSERT INTO TB_DateAuto(";
	int i;
	for( i = 1; i <= 67; i++)
	{
		if(i < 67)
		{
		   str.Format("Auto_Parameter%d,",i);
		}
		else
		{		   
			str.Format("Auto_Parameter%d",i);
		}
		m_SqlStr = m_SqlStr + str;
	}

	m_SqlStr = m_SqlStr + ")  VALUES("; 
	
	for( i = 0; i < 66; i++)
	{
		str.Format("%d,",m_DateReadParameter[i]);
		m_SqlStr = m_SqlStr + str;
	}
	
	str.Format("%d",m_DateReadParameter[66]);
	m_SqlStr = m_SqlStr + str + ")";
  
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
}

//��������  m_ReadRanage  FALSE ֻ������������  TRUE ��������������
CString CIFRMView::DecodeParameter(BOOL m_ReadRanage)
{
	
	CString    Str,m_GetDataStr,m_ReadData,m_timeevery;
	CString                    m_String[3];
	
	for(int j = 0; j < 3; j ++)
	{
		
		Str    =  m_GetDataStr = m_ReadData = "";
		
		for(int i = 0; i < 31; i ++)
		{
			
			if(m_parameter[j*31 + i] > 0)
			{
				Str.Format("%d",i + 1);
				m_GetDataStr = m_GetDataStr + Str + "   ";
			}
			
		}	
		
		//��������
		m_GetDataStr.TrimLeft();
		m_GetDataStr.TrimRight();
		
		switch(j)
		{
		case 0:
			{
                if(m_GetDataStr.IsEmpty())
				{
					m_String[0] = "���� �� �� \r\n  �������ڣ�<��> \r\n";
					
				}
				else
				{
					m_String[0].Format("���� �� �� \r\n  �������ڣ�[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		case 1:
			{	
				if(m_GetDataStr.IsEmpty())
				{
					m_String[1] = "�����û��� \r\n  �������ڣ�<��> \r\n";
					
				}
				else
				{
					m_String[1].Format("�����û��� \r\n  �������ڣ�[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		case 2:
			{	
				if(m_GetDataStr.IsEmpty())
				{
					m_String[2] = "��̨��ȱ� \r\n  �������ڣ�<��> \r\n";
				}
				else
				{
					m_String[2].Format("��̨��ȱ� \r\n  �������ڣ�[%s] \r\n",m_GetDataStr);
				}
				break;
			}
		}
		
	}

	if(!m_ReadRanage)
	{
	   return m_String[0] + m_String[1] + m_String[2];
	}
    
	//��������
	Str   =  "���������ݡ�\r\n";
	
	//�й����
	if(m_parameter[93] > 0)
	{

		if(m_parameter[93] > 0  && m_parameter[94] > 0)
		{
			Str = Str +  "  ��ǰվ�й������й���� ";
		}
		else
		{
			Str = Str +  "  �й���� ";
		}

	}	
	
	//�޹����
	if(m_parameter[95] > 0)
	{

		if(m_parameter[95] > 0  && m_parameter[96] > 0)
		{
			Str = Str + "  ��ǰվ�޹������޹����";	
		}
		else
		{
			Str = Str +  "  �޹���� ";	
		}

	}	
		
	//4��A����� 5��B����� 6��C�����
	if(m_parameter[97] > 0)
	{
        Str = Str + "  A�ࡢB�ࡢC�����ֵ  ";
	}

	//7��A���ѹ 8��B���ѹ 9��C���ѹ
	if(m_parameter[98] > 0)
	{
        Str = Str + "  A�ࡢB�ࡢC���ѹֵ  ";
	}

	//������
	if(m_parameter[99] > 0)
	{
        Str = Str + "  ������  ";
	}
	
	//�����
	if(m_parameter[100] > 0)
	{
        Str = Str + "  �����  ";
	}
	
    //ƽ����
	if(m_parameter[101] > 0)
	{
        Str = Str + "  ƽ����  ";
	}
	
	//�ȵ���
	if(m_parameter[102] > 0)
	{
        Str = Str + "  �ȵ���  ";
	}
	
	//��������
	if(m_parameter[103] > 0)
	{
        Str = Str + "  ��������  ";
	}

	//פ��ʱ��
    m_GetDataStr.Format("��פ��ʱ�̡�\r\n  %dʱ",m_parameter[104]);

	//ɨ����,ɨ�����
	if(m_parameter[109] > 0)
	{
		m_timeevery.Format("�����������\r\n  �ȼ����Сʱ����%d��,����8Сʱ��%d��\r\n���Զ����С�\r\n  �������ʱ�Զ��������������פ������",m_parameter[106],m_parameter[108]);
	}
	else
	{
		m_timeevery.Format("�����������\r\n  �ȼ����Сʱ����%d��,����8Сʱ��%d��\r\n���Զ����С�\r\n  �������ʱ���Զ��������������פ������",m_parameter[106],m_parameter[108]);
	}
   
	return  m_String[0] + m_String[1] + m_String[2] + Str + "\r\n" + m_GetDataStr+ "\r\n" + m_timeevery;

}


//�õ�һ���µ����������  m_select= 0 ���� 1 ���� 2 ����
BYTE CIFRMView::GetMaxDays(BYTE m_select)
{
	CTime                 m_CurrentTime;//����ʱ�����
    CTimeSpan                        ts;//ʱ���϶
	short              m_years,m_months;
	BYTE               m_days      =  0;
	
	//��ȡ��ǰʱ��
	m_CurrentTime  = CTime::GetCurrentTime(); 

	m_years   =   m_CurrentTime.GetYear();
	m_months  =   m_CurrentTime.GetMonth();
	
	switch(m_select)
	{
	case 0:
		{
			//����
			if(m_months > 1)
			{
				//�·ݼ�1
				m_months = m_months - 1;
			}
			else
			{
				//���Ϊ1 �·ݣ�����
				m_years  = m_years - 1;
				m_months =          12;
			}
			
			break;
		}
	case 1:
		{
			//����
			break;
		}
	case 2:
		{
			//����
			if(m_months < 12)
			{
				//�·ݼ�1
				m_months = m_months + 1;
			}
			else
			{
				//���Ϊ12 �·ݣ�����
				m_years  = m_years + 1;
				m_months =           1;
			}

			break;
		}
	}

	CTime    m_start(m_years,m_months,1,0,0,0);
  
	for(int i = 28; i <= 31; i ++)
	{
         ts             = i*86400;
		 CTime    m_end = m_start + ts;

		 if(m_end.GetMonth() != m_months)
		 {
			 //�µ��������
			 m_days = i;
			 break;
		 }
	}

	return m_days;
}

//���һ�������Զ�פ������ʱ��
void CIFRMView::AutoGarrisonTime()
{
	
    CString               str;
	CDatabase              db;	
	int i;
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset   rs(&db );
		str = "SELECT * FROM TB_Auto";
		rs.Open(CRecordset::dynaset,str);
		
		if(rs.IsEOF())
		{
			//�ر����ݿ�
		    rs.Close( );
		    db.Close( );
			return;
		}
		
		//���Զ�������Ϣ
		for(int i = 0; i < 110; i++)
		{
			rs.GetFieldValue((short)i,str);
			m_parameter[i] = atoi(str);
		}

		//�ر����ݿ�
		rs.Close( );
		db.Close( );

		if(m_parameter[109] <= 0)
		{

	        for( i = 0; i < 110; i++)
			{
				m_parameter[i] = 0;
			}

			return;
		}
		
		//15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
		//��ʱ��פ��,��ʱ�����־
		for( i = 0; i < 15; i++)
		{
			m_TimeSetLabel[i]  = FALSE;  
		}
		
		//�й����
		if(m_parameter[93] > 0)
		{
			
			if(m_parameter[93] > 0  && m_parameter[94] > 0)
			{
				m_TimeSetLabel[0] = TRUE;
				m_TimeSetLabel[1] = TRUE;    //0���й����-�����ۼ�ֵ
			}
			else
			{
				m_TimeSetLabel[0] = TRUE;
			}
		
		}	
		
		//�޹����
		if(m_parameter[95] > 0)
		{
			
			if(m_parameter[95] > 0  && m_parameter[96] > 0)
			{
				m_TimeSetLabel[2] = TRUE;
				m_TimeSetLabel[3] = TRUE;    //0���޹����-�����ۼ�ֵ
			}
			else
			{
				m_TimeSetLabel[2] = TRUE;   
			}

		}	
		
		//4��A����� 5��B����� 6��C�����
		if(m_parameter[97] > 0)
		{
			m_TimeSetLabel[4] = TRUE;
			m_TimeSetLabel[5] = TRUE;
			m_TimeSetLabel[6] = TRUE;
		}
		
		//7��A���ѹ 8��B���ѹ 9��C���ѹ
		if(m_parameter[98] > 0)
		{
			m_TimeSetLabel[7] = TRUE;
			m_TimeSetLabel[8] = TRUE;
			m_TimeSetLabel[9] = TRUE;
		}
		
		//������
		if(m_parameter[99] > 0)
		{
			m_TimeSetLabel[10] = TRUE;
		}
		
		//�����
		if(m_parameter[100] > 0)
		{
			m_TimeSetLabel[11] = TRUE;
		}
		
		//ƽ����
		if(m_parameter[101] > 0)
		{
			m_TimeSetLabel[12] = TRUE;
		}
		
		//�ȵ���
		if(m_parameter[102] > 0)
		{
			m_TimeSetLabel[13] = TRUE;
		}
		
		//��������	
		if(m_parameter[103] > 0)
		{
			m_TimeSetLabel[14] = TRUE;
		}
	
		//ִֹͣ�д˲���
		m_StartRead      =  FALSE;
		//ʱ��
		CTime timet = CTime::GetCurrentTime();
		str.Format("��%4d-%02d-%02d %02d:%02d:%02d�����ö�ʱפ������:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),DecodeParameter(TRUE));
		WriteToLog(str);
		
		//ȡ��10���Ӽ��һ�μ��
		KillTimer(1);

		ShowDingShiButton(TRUE);//��ʱ��ť��ΪTRUE
		m_IsAutoSending    =          TRUE;//פ��״̬��־
		m_ReadModuleTimes  =             0;//���������Ϊ0
		m_SendGarrisonTimes=             0;//��פ������
	    m_IfChangeData     =          FALSE;             //�޸Ľ������ݱ�־
		m_parameter[105]   =             30;//���ǿ�����ó�30����
		m_zhuliukinds      =              0;//פ������ 0 ��������� 1 ����������

		StatusStr.Format("����%dʱפ��,�ȼ����Сʱ��%d��,������Сʱ��%d�Ρ�",m_parameter[104],m_parameter[106],m_parameter[108]);
		status(StatusStr);
	
        //��ʼ������
        InitializeCurrent();

		//Ϊ22Э��ӵģ���������ſ���,10����һ���
		m_SettimerValues = ((10 - (timet.GetMinute()%10))*60 - timet.GetSecond())*1000;
		SetTimer(1,m_SettimerValues,NULL);//���ö�ʱ��,10���Ӽ��һ��
	
	}

}


//����פ�������־
void CIFRMView::SetGarrionLabel()
{
	//��ʱ��פ��,15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
	for(int i = 0; i < 15; i++)
	{
		m_TimeSetLabel[i]  = FALSE;  
	}
	
	//�й����
	if(m_parameter[93] > 0)
	{

		if(m_parameter[93] > 0  && m_parameter[94] > 0)
		{
			m_TimeSetLabel[0] = TRUE;
			m_TimeSetLabel[1] = TRUE;    //0���й����-�����ۼ�ֵ
		}
		else
		{
			m_TimeSetLabel[0] = TRUE;
		}

	}	
	
	//�޹����
	if(m_parameter[95] > 0)
	{
		
		if(m_parameter[95] > 0  && m_parameter[96] > 0)
		{
			m_TimeSetLabel[2] = TRUE;
			m_TimeSetLabel[3] = TRUE;    //0���޹����-�����ۼ�ֵ
		}
		else
		{
			m_TimeSetLabel[2] = TRUE;   
		}
		
	}	
	
	//4��A����� 5��B����� 6��C�����
	if(m_parameter[97] > 0)
	{
		m_TimeSetLabel[4] = TRUE;
		m_TimeSetLabel[5] = TRUE;
		m_TimeSetLabel[6] = TRUE;
	}
	
	//7��A���ѹ 8��B���ѹ 9��C���ѹ
	if(m_parameter[98] > 0)
	{
		m_TimeSetLabel[7] = TRUE;
		m_TimeSetLabel[8] = TRUE;
		m_TimeSetLabel[9] = TRUE;
	}
	
	//������
	if(m_parameter[99] > 0)
	{
		m_TimeSetLabel[10] = TRUE;
	}
	
	//�����
	if(m_parameter[100] > 0)
	{
		m_TimeSetLabel[11] = TRUE;
	}
	
	//ƽ����
	if(m_parameter[101] > 0)
	{
		m_TimeSetLabel[12] = TRUE;
	}
	
	//�ȵ���
	if(m_parameter[102] > 0)
	{
		m_TimeSetLabel[13] = TRUE;
	}

	//��������	
	if(m_parameter[103] > 0)
	{
		m_TimeSetLabel[14] = TRUE;
	}

}

//��ʼ������Χ
void CIFRMView::InitializeGarrionReadRange()
{
	//����ѡ��, ���ı�����
	CString        str,m_SqlStr;
	m_AutoReadCondtionStr  = "";
	int j;			
	//��������������о����
	for( j = 0; j < 3; j ++)
	{
		
		//����ж�������
		if(m_parameter[j * 31 + m_AutoReadTime.GetDay() - 1] > 0)
		{
			//j = 0 �����  1 ���û���  2 ̨��ȱ�
			if( j == 2)
			{
				str.Format("USER_AMMETERKIND>=%d",j);
			}
			else
			{
				str.Format("USER_AMMETERKIND=%d",j);
			}
			
			m_AutoReadCondtionStr.TrimRight();
			m_AutoReadCondtionStr.TrimRight();
			
			if(m_AutoReadCondtionStr.IsEmpty())
			{
				m_AutoReadCondtionStr = m_AutoReadCondtionStr + str;
			}
			else
			{
				m_AutoReadCondtionStr = m_AutoReadCondtionStr + " OR " + str;
			}
			
		}
		
	}
	
	//WriteToLog("��������:" + m_AutoReadCondtionStr + "\r\n");
	//str.Format("GARRISON_HALTTIME='%4d-%02d-%02d %02d:%02d:%02d'",m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
    //WriteToLog("פ��ʱ��:" + str + "\r\n");
	
	str = "";
	
	//15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
	for(j = 0; j < 15; j ++)
	{
		
		if(m_TimeSetLabel[j])
		{
			str = str + "N";
		}
		else
		{
			str = str + "Y";
		}
		
	}
	
	//����ģ�鶨ʱ�����־ȫ��ΪY
	m_SqlStr.Format("UPDATE TB_USER SET USER_TIMELABEL='%s'","YYYYYYYYYYYYYYY");
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
	
	//�������������ñ�־
	m_SqlStr.Format("UPDATE TB_USER SET USER_TIMELABEL='%s' WHERE %s",str,m_AutoReadCondtionStr);
	CDataBaseInstance::ExecuteDataBaseSQL(m_SqlStr);
	m_times  = 1;
}


//�޸İκŻ���������״̬
void CIFRMView::ModifyDialInternetStatus()
{	
	//���Է���ʾ
	SelectSendString(m_sendkind, "BEGINS;COMMAND:32:�����30������û��Զ�̻����κ�ָ����ذ��Զ��Ͽ�����ʼפ��������;ENDS",TRUE,FALSE,TRUE);
	Sleep(300);

	//�Ͽ���������
	DisConnect(2);
	
	if(!m_IsConnect)
	{
		SetLocalServer(m_WinSocket.GetLocalIP(),m_WinSocket.GetLocalPort());
	}
	
	//�Ҷϰκ�
	DisConnect(1);
	
	//�κ�����
	if(!m_Com.GetCDHolding())
	{
		
		//������ù��Զ�Ӧ��
		if(CDataBaseInstance::GetAllRecordsCount("TB_COMINFORMATION","COMINFORMATION_AUTOREPLY=1") > 0)
		{  
			//�Զ�Ӧ��
			AutoAnswer(FALSE);	          
		}
		
	}
	
}

//ɾ�������פ���߳�
BOOL CIFRMView::DeleteViewThread()
{
	
	if(ReadMeterThread != NULL)
	{
		MessageBox("����ֹͣ����Ȼ�����˳���"," ",MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	else
	{
	    m_StartRead  =     FALSE;
		//����window����Ȩ
	//	SurrenderWindowMessage();
	
		//д�Ϲس���ʱ��
		CString       str;
		CTime timet = CTime::GetCurrentTime();	    
		str.Format("��%4d-%02d-%02d %02d:%02d:%02d������˳�",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
	    WriteToLog(str);
	}

	return TRUE;
	
}


//����������ݣ�פ�����У���֮ǰ�����ݣ���ʽ���е�����
void CIFRMView::DealOverTimeData(int m_Years)
{
	
	CString            m_SqlStr,m_sql,m_filename;
	CTime     m_time   = CTime::GetCurrentTime();
	m_filename.Format("%s%s%4d_%02d_%02d_%02d%s",GetFolder(),"GARRISON_BAK_",m_time.GetYear(),m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),".TXT");
	
    m_SqlStr.Format("GARRISON_HALTTIME < '%4d-%02d-%02d %02d:%02d:%02d'",m_time.GetYear()-m_Years,m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),m_time.GetMinute(),m_time.GetSecond());

    long fields        =  CDataBaseInstance::GetAllRecordsCount("TB_GARRISON",m_SqlStr);
	m_sql              =  "SELECT * FROM TB_GARRISON WHERE " + m_SqlStr;
	
	if(fields  > 0)
	{
		//����פ��������
		WriteDataToTextFile("TB_GARRISON",m_sql,fields,m_filename);
		
		//ɾ��פ��������
		m_sql.Format("DELETE FROM TB_GARRISON WHERE %s",m_SqlStr);
		CDataBaseInstance::ExecuteDataBaseSQL(m_sql);
       
		//ɾ����ʽ������
		m_SqlStr.Format("REALTIME_TRANSCRIBETIME < '%4d-%02d-%02d %02d:%02d:%02d'",m_time.GetYear()-m_Years,m_time.GetMonth(),m_time.GetDay(),m_time.GetHour(),m_time.GetMinute(),m_time.GetSecond());
	    m_sql.Format("DELETE FROM TB_REALTIME WHERE %s",m_SqlStr);
		CDataBaseInstance::ExecuteDataBaseSQL(m_sql);
	}

}

//kinds  0 ����פ��ʱ��  1 ��ѯפ��ʱ��
void CIFRMView::DealOverTime(BYTE kinds)
{
	//��ְ汾
	CString       PassStr;

	if(!AppInfo::Instance().m_WhichKind)
	{
		
		if(kinds == 0)
		{
			//����פ��ʱ��
			PassStr.Format("BEGINS;COMMAND:33:%d;ENDS",m_saveyears);
		}
		else
		{
			//��ѯפ��ʱ��
			PassStr = "BEGINS;COMMAND:34;ENDS";
		}	
			
		//Զ�̷��͵��Բ�����ָ��
		SelectSendString(m_sendkind,PassStr,TRUE,TRUE,TRUE);
	
	}
	else
	{	
		PassStr.Format("���ж������ݱ���ʱ��Ϊ%d�꣡",m_saveyears);
		MessageBox(PassStr," ",MB_OK|MB_ICONINFORMATION);
	}

}


void CIFRMView::OnCheckeqaul() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}	

	CString      str;
	str = "ɾ�����ڻ����ԭ������ĸ��û�����ص�ģ�����ʽ��פ��\r\n��ʷ���ݣ���Щ���ݱ�ɾ�������ָܻ���ɾ����Щ��¼��";

	if(MessageBox(str,"ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
	
		//פ������
		str = "DELETE TB_GARRISON WHERE GARRISON_MODULENO NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER) AND GARRISON_MODULENO NOT IN (SELECT DISTINCT CHANGEAMMETER_MODULENOOLD FROM TB_CHANGEAMMETER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);

		//��ʽ��������
		str = "DELETE TB_REALTIME WHERE REALTIME_MODULENO NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);
	
		//���ߴ����ģ��
    	str = "DELETE FROM TB_LINEERROR WHERE LINEERROR_MODULE NOT IN (SELECT USER_MODULENO FROM TB_USER)";
		CDataBaseInstance::ExecuteDataBaseSQL(str);
		
		//ɾ���޹�������
		str.Format("DELETE FROM TB_WUGONG WHERE WUGONG_MODULE NOT IN (SELECT DISTINCT USER_MODULENO FROM TB_USER)");
		CDataBaseInstance::ExecuteDataBaseSQL(str);
      
		CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		pMainFrm->m_wndMyDialogBar.InitializeCombo();
		
		MessageBox("����ɾ��������"," ",MB_OK|MB_ICONASTERISK);
	}
	
}

//���ݼ���һ����
void CIFRMView::OnUpdateCheckeqaul(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);	
}

//����Ϊ������
void CIFRMView::OnXiangchange() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CString         StrSql,str;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	StrSql.Format("��ѡ�û�ģ��[%d��]�඼��Ϊ��������",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()));
	
	if(MessageBox(StrSql," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
	{
		return;
	}	
	
	StrSql.Format("Update TB_USER SET USER_PHASE=3 WHERE %s",pMainFrm->m_wndMyDialogBar.SelectCondition());
	CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
		
	//Զ�̰淢�͸ı�����ָ��
	if(!AppInfo::Instance().m_WhichKind)//TRUE ���վ�汾  FALSE��ְ�
	{
	   str.Format("BEGINS;COMMAND:19:%s;ENDS",StrSql);
	   SelectSendString(m_sendkind,str,TRUE,TRUE,TRUE);
	}

	MessageBox("��ѡģ������޸���ϣ�","  ",MB_OK|MB_ICONASTERISK);
}

void CIFRMView::OnUpdateXiangchange(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	//�õ�ѡ����������pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
    pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty() && CRuntimeAccount::GetCurrentPrivilege() < 2);
	
}

//��⵱ǰĸ�߳����Ƿ��е���
//BYTE MotherLine ĸ�߱��
//BYTE LineNo     ��·���
//BYTE Phase      ���
//m_SendInfo    TRUE ���͵���ָ��  FALSE ����·
CString CIFRMView::CheckCurrentValue(BYTE MotherLine, BYTE LineNo,BOOL m_SendInfo)
{

	double m_ACurrentSum,m_BCurrentSum,m_CCurrentSum;
	double m_ACurrentAvgSum,m_BCurrentAvgSum,m_CCurrentAvgSum;
	m_ACurrentSum    = m_BCurrentSum    = m_CCurrentSum    = 0;
	m_ACurrentAvgSum = m_BCurrentAvgSum = m_CCurrentAvgSum = 0;

	CString                        str;
	str.Format("%10d|%10d|%10d",0,0,0);

	BYTE   ORDER[15];

	if(m_SendInfo)
	{
		//���͵���ָ��

		//��Ƭ����ָ��
		if(!SendOrderToSCM(13107115/*ģ���*/,0/*�����ֵ�վ��*/,MotherLine/*ĸ��*/,LineNo/*�ߺ�*/, 1/*��ѡ��0A 1B 2C*/,3, 0x02/* Ҫʲô����,������*/,0,71,0))
		{
			Beep(300,400);
			Beep(300,400);
		
		}
	
	}
	else
	{
		//�л���·
		//�����ִ�ORDER[0]��ORDER[4]��Ƭ����
		ORDER[0]  = 0x51; //ǰ����
		ORDER[1]  = 0x52; //ǰ����
		ORDER[2]  = 0x5B; //�������� ������·
		ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + 01;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
		ORDER[4]  =  3;
		// ��ʱ��0����   
		
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
		PcSendToSCM(ORDER,31,0);
	}

    SurrenderWindowMessage();

	//��ʱ10����
	Sleep(500);
    SurrenderWindowMessage();
	DataLen     =          0;

	//�ɼ�ͬ�������ź�
	//unsigned short  *ai_buf = new unsigned short[15360];
	unsigned short  ai_buf[15360];
	memset(ai_buf,0,15360);

	//�Բ�ģʽ
    err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		return str;
	}
	
	//˫����ģʽ
    err = AI_AsyncDblBufferMode(card, 0); 	
	
	if(err != 0)
	{
		return str;
	}

	//�ɼ�8ͨ�������� 0-A����� 1��B����� 2��C����� 3-A���ѹ 4��B���ѹ 5��C���ѹ
	err = AI_ContScanChannels(card,2,AD_B_10_V,ai_buf,15360,(F64)100000,SYNCH_OP);
	
	if(err != 0)
	{
		return str;
	}

	//˫������״̬
	err = AI_AsyncDblBufferMode(card, 1);
	
	if(err != 0)
	{
		return str;
	}

	//�Ļ��ⴥ��״̬
	err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
	
	if(err != 0)
	{
		return str;
	}
	int i;
	//�����ɼ�������
	for( i = 0; i < 12000; i++)
	{   	
 
		DataBuf[i] = ai_buf[i]/16;
		
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
	
		switch(i%3)
		{
		case 0:
			{
				//A������ۼ�ֵ
				m_ACurrentSum = m_ACurrentSum + DataBuf[i];
				break;
			}
		case 1:
			{
				//B������ۼ�ֵ
				m_BCurrentSum = m_BCurrentSum + DataBuf[i];
				break;
			}
		case 2:
			{
               //C������ۼ�ֵ
				m_CCurrentSum = m_CCurrentSum + DataBuf[i];
				break;
			}
			//��Ʈ��
		}
	}

	//ƽ��ֵ  A
	m_ACurrentAvgSum = (m_ACurrentSum*1.00)/4000;
	m_BCurrentAvgSum = (m_BCurrentSum*1.00)/4000;
	m_CCurrentAvgSum = (m_CCurrentSum*1.00)/4000;
	
    m_ACurrentSum = m_BCurrentSum = m_CCurrentSum = 0;
	
	//�����ɼ�������
	for( i = 0; i < 12000; i++)
	{   	
		
		switch(i%3)
		{
		case 0:
			{
				//A������ۼ�ֵ
				m_ACurrentSum = m_ACurrentSum + fabs(DataBuf[i] - m_ACurrentAvgSum);
				break;
			}
		case 1:
			{
				//B������ۼ�ֵ
				m_BCurrentSum = m_BCurrentSum + fabs(DataBuf[i] - m_BCurrentAvgSum);
				break;
			}
		case 2:
			{
				//C������ۼ�ֵ
				m_CCurrentSum = m_CCurrentSum + fabs(DataBuf[i] - m_CCurrentAvgSum);
				break;
			}
		}
		
	}

	str.Format("%10d|%10d|%10d",int(m_ACurrentSum/2),int(m_BCurrentSum/2),int(m_CCurrentSum/2));
	return str;

}


//��⵱ǰĸ�߳����Ƿ��е���
//BYTE MotherLine ĸ�߱��
//BYTE LineNo     ��·���
BOOL CIFRMView::CheckIfHaveCurrentValue(BYTE MotherLine, BYTE LineNo)
{

	//��ʾ��
	if(AppInfo::Instance().m_YanShi)
	{
		return TRUE;
	}
	int i;
	double m_ACurrentSum,m_BCurrentSum,m_CCurrentSum;
	double m_ACurrentAvgSum,m_BCurrentAvgSum,m_CCurrentAvgSum;
	m_ACurrentSum    = m_BCurrentSum    = m_CCurrentSum    = 0;
	m_ACurrentAvgSum = m_BCurrentAvgSum = m_CCurrentAvgSum = 0;
    BOOL m_IfHaving  = FALSE;

	BYTE   ORDER[15];

	//�л���·
	//�����ִ�ORDER[0]��ORDER[4]��Ƭ����
	ORDER[0]  = 0x51; //ǰ����
	ORDER[1]  = 0x52; //ǰ����
	ORDER[2]  = 0x5B; //�������� ������·
	ORDER[3]  = (BYTE)(MotherLine - 1) * 64 + (BYTE)(LineNo) * 4 + 01;//�ϳ��ֽ� ǰ2λΪĸ��, �м�4λΪ��·�ţ���2λΪ��λֵ 01 A 02 B 03 C
	ORDER[4]  =  3;
	// ��ʱ��0����   
	
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
	PcSendToSCM(ORDER,31,0);

    SurrenderWindowMessage();

	//��ʱ10����
	Sleep(200);
    SurrenderWindowMessage();
	DataLen    =   0;

	//�ɼ�ͬ�������ź�
	unsigned short  ai_buf[15360];
	memset(ai_buf,0,15360);

	//�Բ�ģʽ
    err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
	
	if(err != 0)
	{
		return m_IfHaving;
	}
	
	//˫����ģʽ
    err = AI_AsyncDblBufferMode(card, 0); 	
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//�ɼ�8ͨ�������� 0-A����� 1��B����� 2��C����� 3-A���ѹ 4��B���ѹ 5��C���ѹ
	err = AI_ContScanChannels(card,2,AD_B_10_V,ai_buf,15360,(F64)100000,SYNCH_OP);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//˫������״̬
	err = AI_AsyncDblBufferMode(card, 1);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//�Ļ��ⴥ��״̬
	err = AI_9111_Config(card, TRIG_EXT_STROBE,0,0);
	
	if(err != 0)
	{
		return m_IfHaving;
	}

	//�����ɼ�������
	for( i = 0; i < 12000; i++)
	{   	
 
		DataBuf[i] = ai_buf[i]/16;
		
		if(DataBuf[i] >= 2048)
		{
			DataBuf[i] =  -(4096 - DataBuf[i]);
		}
	
		switch(i%3)
		{
		case 0:
			{
				//A������ۼ�ֵ
				m_ACurrentSum = m_ACurrentSum + DataBuf[i];
				break;
			}
		case 1:
			{
				//B������ۼ�ֵ
				m_BCurrentSum = m_BCurrentSum + DataBuf[i];
				break;
			}
		case 2:
			{
               //C������ۼ�ֵ
				m_CCurrentSum = m_CCurrentSum + DataBuf[i];
				break;
			}
			//��Ʈ��
		}
	}

	//ƽ��ֵ  A
	m_ACurrentAvgSum = (m_ACurrentSum*1.00)/4000;
	m_BCurrentAvgSum = (m_BCurrentSum*1.00)/4000;
	m_CCurrentAvgSum = (m_CCurrentSum*1.00)/4000;
	
    m_ACurrentSum = m_BCurrentSum = m_CCurrentSum = 0;
		
	
	//�����ɼ�������
	for( i = 0; i < 12000; i++)
	{   	
		switch(i%3)
		{
		case 0:
			{
				//A������ۼ�ֵ
				m_ACurrentSum = m_ACurrentSum + fabs(DataBuf[i] - m_ACurrentAvgSum);
				break;
			}
		case 1:
			{
				//B������ۼ�ֵ
				m_BCurrentSum = m_BCurrentSum + fabs(DataBuf[i] - m_BCurrentAvgSum);
				break;
			}
		case 2:
			{
				//C������ۼ�ֵ
				m_CCurrentSum = m_CCurrentSum + fabs(DataBuf[i] - m_CCurrentAvgSum);
				break;
			}
		}
		
	}
  
	if(int(m_ACurrentSum/2) > 1000 || int(m_BCurrentSum/2) > 1000 || int(m_CCurrentSum/2) > 1000)//2000
	{
		m_IfHaving = TRUE;
	}
	
	return m_IfHaving;

}

//������·����״̬
void CIFRMView::OnChecklinestatus() 
{  
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	if(CDataBaseInstance::GetAllRecordsCount("TB_USER","ALL") > 0)
	{
		//��������״̬���
		ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)5,m_Thread_PRIORITY,0,0,NULL); // ����������
		ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
	}
	else
	{
		MessageBox("���ݱ���û����·�ɼ�⣡"," ",MB_OK|MB_ICONWARNING);
	}

}

void CIFRMView::OnUpdateChecklinestatus(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2);
}

//�����·������״̬
void CIFRMView::CheckLineRun()
{

	CDatabase                   db;
	CString        str,MsgStr,str1;
    BYTE         MotherLine,LineNo;
	int                i    =  1,k;
    int      m_LineNumbers  =     0;
	BOOL     m_IfHaveElc    = FALSE;
	m_StartRead             =  TRUE;//��ͣ��־
	CString           m_GetValue[3];
	float      m_addlinecurrent = 0;
		
	//ɾ�����е�����
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);		
	
	TRY { 
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);     //��
		m_Grid.SetColumnCount(8);  //��
		
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
       #ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
       #endif
		
		GV_ITEM       Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     =   0;
		Item.col     =   0;
		
		Item.nFormat = dwTextStyle;
		Item.strText.Format("%s","���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(0,80); 
		
		Item.col     =   1;
		Item.strText.Format("%s","ĸ�߱��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(1,80); 
		
		Item.col     =   2;
		Item.strText.Format("%s","���߱��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(2,80); 
		
		Item.col     =   3;
		Item.strText.Format("%s","���Զ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(3,80);
		
		Item.col     =   4;
		Item.strText.Format("%s","A�����");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(4,120);
		
		Item.col     =   5;
		Item.strText.Format("%s","B�����");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(5,120);
		
		Item.col     =   6;
		Item.strText.Format("%s","C�����");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(6,120);
		
		Item.col     =   7;
		Item.strText.Format("%s","����ʱ��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(7,180);
		m_Grid.SetModified(FALSE,-1,-1);//ֻ��״̬
		m_Grid.m_title  = "";	//����
		m_Grid.SetBkColor(RGB(255,255,255));
		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->Delete();
		return;
	}
	END_CATCH
		
	SurrenderWindowMessage();
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		SurrenderWindowMessage();
		
		//��ʾ״̬����Ϣ
		StatusStr = "���ڲ�����·����״̬�����Ժ�...";
		SendMessage(WM_EVENT, 1, 0);
		
		//��CRecordset����
		CRecordset  m_CompanySet(&db);	
		str.Format("SELECT USER_LINENAME,USER_MOTHERLINE,USER_LINENO FROM TB_USER GROUP BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO ORDER BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO");
		m_CompanySet.Open(CRecordset::dynaset,str);
		
		while(!m_CompanySet.IsEOF())
		{
			m_CompanySet.MoveNext();
		}
		
		//�õ���¼����
		m_LineNumbers = m_CompanySet.GetRecordCount();
		
		if(m_LineNumbers < 1)
		{
			m_CompanySet.Close();
			db.Close();
			m_StartRead =   FALSE;	
			ShowProgressCtrl(FALSE);	//���ع�����
			return;
		}
		
		//��ʾ������
		ShowProgressCtrl(TRUE);
		
		SetProgressCtrlRange(0, m_LineNumbers,1);
		
		if(!m_CompanySet.IsBOF())
		{
			m_CompanySet.MoveFirst();
		}

		//ǰ3�ε�����ǰ��һ��
		for(int i = 0; i < 96; i ++)
		{
			m_AllLineThreeCurrent[i] = m_AllLineThreeCurrent[32 + i];
		}

		i =   1;
		
		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{
			
			SurrenderWindowMessage();
			SetProgressCtrlSetIt();
			SurrenderWindowMessage();
			
			if(	!m_StartRead)
			{
				break;
			}
			
			//��·����
			m_CompanySet.GetFieldValue(short(0),str1);
			str1.TrimRight();
			str1 = str1 + "��·";
			
			//��ʾ״̬����Ϣ
			StatusStr = "���ڼ����·" + str1 + "�����Ժ�...";
			SendMessage(WM_EVENT, 1, 0);
			m_CompanySet.GetFieldValue(int(1),str);
			MotherLine  =  atoi(str);
			m_CompanySet.GetFieldValue(int(2),str);
			LineNo      =  atoi(str);;
			
			//��ʾ�汾
			if(AppInfo::Instance().m_YanShi)
			{
				//����Ƿ���ͣ��״̬
				Sleep(1000);
				MsgStr.Format("%.2f|%.2f|%.2f",float(rand()/440000),float(rand()/440000),float(rand()/440000));//11000
			}
			else
			{
				//����Ƿ���ͣ��״̬
				MsgStr =  CheckCurrentValue(MotherLine,LineNo,FALSE);
			}
			
			m_GetValue[0] =     "";
			m_GetValue[1] =     "";
			m_GetValue[2] =     "";
			m_IfHaveElc   =  FALSE;
			
			//�ֽ�MsgStr�ַ���
			k = MsgStr.Find("|");
			
			if( k != -1)
			{
				m_GetValue[0] = MsgStr.Left(k);
				MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
				
				k = MsgStr.Find("|");
				
				if( k != -1)
				{
					m_GetValue[1] = MsgStr.Left(k);
					MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
					m_GetValue[2] = MsgStr;
				}
				
			}
			
			for(int ll = 0; ll < 3; ll ++)
			{
				
				if(atol(m_GetValue[ll]) > 1000)
				{
					
					m_IfHaveElc  = TRUE;
					
				}				
				
			}

			//�����浵 MotherLine,LineNo
			m_addlinecurrent = atof(m_GetValue[0])/440000 + atof(m_GetValue[1])/440000 + atof(m_GetValue[2])/440000;//����������
	
			//��32����·3�ε���,����·�ĵ���ֵ���2*16=32 32*3 = 96 ÿ����·��4�ε���
			m_AllLineThreeCurrent[3*32 + (MotherLine-1)*16 + (LineNo - 1)]	= 	m_addlinecurrent;
					
			CTime time    = CTime::GetCurrentTime();
			str.Format("%sifrm_%d_%02d_Three_Current_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
			k             =                  0;
			CFileFind                   finder;//�Ƿ��д��ļ�
			
			//�������������������
			if(finder.FindFile(str) != 0) 
			{ 
				k  = 1;
			}
			
			finder.Close();
			
			FILE *text;
			if((text = fopen(str,"a")) != NULL)
			{	
				
				if(k == 0)
				{
					//���Զ���,A�����,B�����,C�����,����ʱ��
					str.Format("���Զ���,A�����,B�����,C�����,����ʱ��\n");
					fputs(str,text);
				}
				
				str.Format("%s,%.2f,%.2f,%.2f,%4d-%02d-%02d %02d:%02d:%02d\n",str1,atof(m_GetValue[0])/440000,atof(m_GetValue[1])/440000,atof(m_GetValue[2])/440000,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				fputs(str,text);		
				fclose(text);
			}
			
			//��ʾ����
			m_Grid.InsertRow(_T(" "), -1);
			m_Grid.Invalidate(); 
			
			DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
			dwTextStyle |= DT_END_ELLIPSIS;
#endif
			
			GV_ITEM  Item;
			Item.mask    = GVIF_TEXT|GVIF_FORMAT;
			Item.row     = m_Grid.GetRowCount() - 1;
			
			//���
			Item.col     = 0;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",i);
			m_Grid.SetItem(&Item);
			
			//ĸ�߱��
			Item.col     = 1;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",MotherLine);
			m_Grid.SetItem(&Item);
			
			//���߱��
			Item.col     = 2;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%4d",LineNo);
			m_Grid.SetItem(&Item); 
			
			//��·����
			Item.col     = 3;
			Item.nFormat = dwTextStyle;
			Item.strText.Format("%s",str1);
			m_Grid.SetItem(&Item);
			
			//A��B��C������� 
			for(int ll = 4; ll <= 6; ll ++)
			{
				Item.col     = ll;
				Item.nFormat = dwTextStyle;
				Item.strText.Format("%.2f",atof(m_GetValue[ll-4])/440000.00);
				m_Grid.SetItem(&Item);
			}
			
			//ʱ��
			Item.col     =           7;
			Item.nFormat = dwTextStyle;
			
			Item.strText.Format("%4d-%02d-%02d %02d:%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
			m_Grid.SetItem(&Item);
			
			if(!m_IfHaveElc)
			{	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��·����:%16s[%2d-%2d]  ���ͣ��",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),str1,MotherLine,LineNo);
				WriteToLog(str);
			}
			
			m_Grid.SetModified(FALSE,-1,-1);
			m_Grid.Invalidate();
			
			i ++;			
			m_CompanySet.MoveNext();
	}
	
	m_CompanySet.Close();
	db.Close();
	
	if(m_StartRead)
	{ 
		StatusStr = "����������";
	}
	else
	{
		StatusStr = "������жϡ�";
	}	
	
	SendMessage(WM_EVENT, 1, 0);
	
	//���ع�����
	ShowProgressCtrl(FALSE);
	
   }
	
//	m_StartRead  =   FALSE;

}

void CIFRMView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	//	SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
	CFormView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

//��ʱ����פ����פ��
void CIFRMView::DingShiDeal()
{

	CString       str,strhalt;
	
	//���ʱ���Ƿ��˷�פ��ʱ��,10���Ӽ��һ��	,��������ʱ����Զ������
	if(Received == 2 )
	{
	    //����ͳ�ɳ��ͨѶ����û��פ���ϵĻ�
		return;
	}
	
	//��������д��ڴ���ر�
	CWnd* pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}

	pt = CWnd::FindWindow(NULL,"��̨������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�û���Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"פ������������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"��ʽ����������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�õ����߷�������");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	//������ڲ��Զ������ʽ���� m_others  FALSE ��������  TRUE  פ������
//	if(ReadMeterThread != NULL)
/*	if(ReadMeterThread != NULL)

	{	
		
		//������ڲ��Զ������ʽ����
		while(!m_others)
		{
		SurrenderWindowMessage();
		Sleep(180);
//			return;
		}
		
	}
*/
/*	int HaveThreadRun = 0;
    MessageBox("���:���߳�������","  ",MB_OK);	
	while (ReadMeterThread != NULL)
	{ 
		Sleep(1000);
		HaveThreadRun++;
		if(HaveThreadRun > 60) 
		{
			HaveThreadRun = 0;
			MessageBox("Ŀǰ���߳�����","  ",MB_OK);	
		}
	}
	HaveThreadRun = 0;
	MessageBox("CPU����","  ",MB_OK);
*/
//�Ƿ��ǵ�һ�汾,���ǵ�һ�汾���⴮�ڻ������
	/*
	if(!AppInfo::Instance().m_SingleBB) 
	{
		
		//���������״̬
		if(!m_IfChangeData)
		{
			//���������״̬ʱ,ǿ���˳��߳�
			SendMessage(WM_EVENT,14, 0);
		}
		else
		{
			//�޸Ľ������ݱ�־
			m_IfChangeData = FALSE;
			return;
		}
		
	}
	*/
	
	KillTimer(1);
	SetTimer(1,600000,NULL);         //���ö�ʱ��,10���Ӽ��һ��
	
	int k_status        = CheckCurrentTime();

//	CTime m_CurrentTime = CTime::GetCurrentTime();	 	
//	str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���״̬���:%d",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),k_status);
//	WriteToLog(str);

	//���״̬

	switch(k_status)
	{
	case 0:
		{
			//����ʱ��,����������ֵĻ�	
			//if(ReadMeterThread == NULL)
			//{
				/*
				CTime m_CurrentTime = CTime::GetCurrentTime();	 	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���0",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	            WriteToLog(str);
				*/

				//�����źŻ�����·����
/*				while (ReadMeterThread != NULL)
				{ 
				SurrenderWindowMessage();
					Sleep(180);
				}
*/
//	MessageBox("פ��0","  ",MB_OK);
//				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
			//}
			
			break;
		}
	case 1:
		{
			/*
             CTime m_CurrentTime = CTime::GetCurrentTime();	 	
			 str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���1��פ��",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	         WriteToLog(str);
			 */

			//��פ��ʱ�䵽��,���ԭ���ڶ�����˳�����
/*			m_StartRead    =   FALSE;
	           
			//�ͷ�CPUʱ��
			SurrenderWindowMessage();
			Sleep(2000);
			//�ͷ�CPUʱ��
			SurrenderWindowMessage();
*/			
			//��פ������,ÿ�ζ���
//			if(ReadMeterThread == NULL)
//			{
/*			while (ReadMeterThread != NULL)
			{ 
				SurrenderWindowMessage();
				Sleep(180);
			}
*/
//	MessageBox("פ��1","  ",MB_OK);
			
				//дפ��ʱ����־ʱ��
				CTime timet = CTime::GetCurrentTime();
				
				/*
				//פ��ʱ��
				CTimeSpan                           ts;
				ts   =  m_AutoReadTime    -      timet;
				
				//����������ʱ��,�����(0,10)����֮��Ļ�,������
				if(ts.GetTotalSeconds() < 600)
				{
					KillTimer(1);
					SetTimer(1,ts.GetTotalSeconds()*1000,NULL); //���ö�ʱ��,ts.GetTotalSeconds()�������
				}
				*/
					
				//��ʼ������Χ
				InitializeGarrionReadRange();

				//���������Ϊ0
				m_ReadModuleTimes =  0;	
				//��פ������
				m_SendGarrisonTimes ++;
				
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��%4d�η�[%4d-%02d-%02d %02d:%02d:%02d]��ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_SendGarrisonTimes,m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
				WriteToLog(str);
				
				//������פ���߳�
				ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)6,m_Thread_PRIORITY+1,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				
//			}

			break;
		}
	case 2:
		{	 
			/*
			CTime m_CurrentTime = CTime::GetCurrentTime();	 	
			str.Format("%4d-%02d-%02d %02d:%02d:%02d   ���2����",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond());
	        WriteToLog(str);
			 */

			//����ʱ�䵽��,�������,��Ҫ����פ���ſ���
//			if(ReadMeterThread == NULL)
//			{
/*			while (ReadMeterThread != NULL)
			{ 
				SurrenderWindowMessage();
				Sleep(180);
			}
*/
//	MessageBox("פ��2","  ",MB_OK);
			//++
    			int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
				CTime  m_CurrentTime     =      CTime::GetCurrentTime();
				str                      =              GetZhuLiuTime();
				float             m_temp =                            0;
				CString                                    m_bakstrline;
			
				str.TrimLeft();
				str.TrimRight();
				
				//פ��ʱ��Ϊ��,������������
				if(str.IsEmpty() || m_ReadModuleTimes > (m_parameter[106] + m_parameter[108]) || CDataBaseInstance::GetAllRecordsCount("TB_USER", "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'") == 0)
				{
					//�����źŻ�����·����
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
					return;
				}
				
				//פ��ʱ��
				strhalt   = str;
				
				//ʱ�䴦��
				int k     = str.Find('-');
				
				//��
				m_years   = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();

				//��
				k         = str.Find('-');
				m_months  = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				k         = str.Find(' ');
				m_days    = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//ʱ
				k         = str.Find(':');
				m_hours   = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				k         = str.Find(':');
				m_minutes = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
			
				//��
				m_seconds      = atoi(str);
				
				CTime            timebakks(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);
				m_AutoReadTime = timebakks;
				
				//ʱ���϶
				CTimeSpan                           ts;
				ts   =  m_CurrentTime - m_AutoReadTime;

				if(ts.GetTotalSeconds() < 0)
				{
					//�����źŻ�����·����
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
					return;
				}
				else  if(ts.GetTotalSeconds() < 180)
				{

				
					//�ȶ��ؿڱ�,�պõ�פ��ʱ���,ǰ3�����ڶ���
					if(m_ReadModuleTimes == 0)
					{
						
						//���ؿڱ�
						m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY' AND USER_AMMETERKIND>5";
						
						//��פ������
						m_SendGarrisonTimes   =   0;	
						str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��[%s]��ʱפ���ؿڱ�",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),strhalt);
						WriteToLog(str);
						
						KillTimer(1);
						SetTimer(1,5*60000,NULL); 
						
						//�������
						m_ReadModuleTimes = 0;
						
						//��פ���ؿڱ�
						ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL); 
						ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						
					}
					
					
				}
				else							
				{	
					
					//���������������,ʱ�����Ļ�,��ǰʱ��
					CTime timet = CTime::GetCurrentTime();
					
					//��������ſ���,10���Ӽ��һ��
	                m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
					
					KillTimer(1);
					SetTimer(1,m_SettimerValues,NULL); 	
					
					//����פ�������־
					SetGarrionLabel();
					
					//�ؿڱ��ٶ���
					CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_AMMETERKIND>4");
					
					m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					//��פ������
					m_SendGarrisonTimes   =   0;	
					
					if(m_ReadModuleTimes < m_parameter[106] - 1)
					{
						//�����Сʱһ��û�ж���
						m_ReadModuleTimes        ++;    
					}
					else if(m_ReadModuleTimes == m_parameter[106] - 1)
					{
						//�����Сʱһ�θպö���
						m_ReadModuleTimes        ++; 
						
						//�����Ȱ�Сʱһ�������ʱ��
						m_FirstReadOkTime = CTime::GetCurrentTime();

					}
					else 
					{
						
						//�������������һ���Ѿ�����,Ҫ��8Сʱһ�εĶ���
						ts   =  timet  - m_FirstReadOkTime ;
						
						//4Сʱ��������8Сʱ�ض� /4 �������Ļ�
						k = (ts.GetTotalSeconds()+ 60)/14400;
						
						if(k > 0 && ((ts.GetTotalSeconds() + 60)%14400) < 1800)
						{
							
							if(k%2 == 1)
							{
								
								//4Сʱ,���������
								str         =      "";
								
								//���32����·�ĵ���
								for(k = 0 ; k < 32; k ++)
								{	
									
                        			m_temp = m_AllLineThreeCurrent[k] + m_AllLineThreeCurrent[32 + k] + m_AllLineThreeCurrent[64 + k];
																	
									//4Сʱһ����������10%����·�Ŷ�
									if((m_AllLineThreeCurrent[96 + k] >= (1.1*m_temp/3.0)) && (m_temp > 0.01))
									{
										
										m_bakstrline.Format("%4d-%02d-%02d %02d:%02d:%02d   4Сʱһ��⣬ĸ��%d����%d��ԭ����0.1������(��%.2f-ԭ%.2f)",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),(k/16) + 1,(k%16) + 1,m_AllLineThreeCurrent[96 + k],m_temp/3.0);
					                    WriteToLog(m_bakstrline);

										m_bakstrline.Format(" (USER_MOTHERLINE=%d AND USER_LINENO=%d) ", (k/16) + 1,(k%16) + 1);
										
										if(str.IsEmpty())
										{
											str = str  +  m_bakstrline;
										}
										else
										{
											str = str  + " OR " + m_bakstrline;
											
										}

										
									}
									
								}
								
								str.TrimLeft();
								str.TrimRight();

								if( !str.IsEmpty() )
								{
									
									//����е���
								//	m_ReadModuleTimes ++;    //4Сʱһ�Ĳ���������
									m_AutoReadCondtionStr = m_AutoReadCondtionStr + "AND  (" + str + ")";

								}
								else
								{
									
									str.Format("%4d-%02d-%02d %02d:%02d:%02d   4Сʱһ��⣬û�м�������·����ǰ����10���ĵ���",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					                WriteToLog(str);
									
									//�����źŻ�����·����
									ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
									ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
									return;
								}
								
								
							}
							else
							{
								//8Сʱֱ�Ӷ���
								m_ReadModuleTimes  ++;    //�������
							}
							
							
						}
						else
						{			
							
							//�����źŻ�����·����
							ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
							return;
							
						}
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��%4d�ζ�[%s]��ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_ReadModuleTimes,strhalt);
					WriteToLog(str);
					
					//פ������,ͬʱ��·�������
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				}
				
//			}
			
			break;
		}
	case 3:
		{
//			if(ReadMeterThread == NULL)
//			{
/*	while (ReadMeterThread != NULL)
	{ 
		SurrenderWindowMessage();
		Sleep(180);
	}
*/	
//			MessageBox("פ��3","  ",MB_OK);
				//�޹����������
				SendContionStr       =  "ALL";
				ReadMeterThread      =  AfxBeginThread(WorkerThread,(LPVOID)15,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
//			}

			break;
		}
		
	}
			
}

//�����ظ���¼
void CIFRMView::OnFindrepeatrecords() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm); 
	//�����ݿ�
	CDatabase           db;
	CString         strSql;
	CString       strValue;
    int         fields = 0;
	
    if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset rs(&db );
		
		strSql.Format("SELECT * FROM TB_USER WHERE USER_MODULENO in (select USER_MODULENO from TB_USER group by USER_MODULENO  having count(*)>1) AND %s order by USER_MODULENO",pMainFrm->m_wndMyDialogBar.SelectCondition());
		rs.Open(CRecordset::dynaset,strSql);//CRecordset::forwardOnly
		
		if(rs.IsEOF())
		{
			//�ر����ݿ�
			rs.Close( );
			db.Close( );
			MessageBox("û���ҵ��ظ���¼��"," ",MB_OK|MB_ICONWARNING);
			return;
		}
		else
		{
			while (!rs.IsEOF())
			{
				rs.MoveNext();
			}
		
			fields = rs.GetRecordCount();//ֻ��ͳ�Ƶ�ǰ�Ѿ�������ļ�¼
		}	 
		
		rs.MoveFirst();
	    ShowProgressCtrl(TRUE);
		//��Χ
	    SetProgressCtrlRange(0, fields,1);

		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount( );
		CODBCFieldInfo fieldinfo;
		
		//ɾ�����е�����
		m_Grid.DeleteAllItems();
		
		TRY { 
			m_Grid.SetHeaderSort(TRUE);
			m_Grid.SetFixedRowCount(1);
			m_Grid.SetRowCount(fields + 1);	//��
			m_Grid.SetColumnCount(nFields); //��
			m_Grid.SetBkColor(RGB(255,255,255));
		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
		END_CATCH
			
	
		for(int i = 0;i < nFields; i++)
		{
			//�ֶ���
			m_Grid.SetItemTextFmt(0, i, TB_USERS[2*i + 1]);//fieldinfo.m_strName
			m_Grid.SetColumnWidth(i,120);
		}
		
		status("���ڶ�ȡ�ظ���¼�����Ժ�...");
	
		//��������Ϣ 
		for(int j = 0; j < fields; j ++)
	   	{
			//�ֶ���
			SurrenderWindowMessage();//����window����Ȩ
			
			for(int i = 0; i < nFields; i++)
			{
				
				rs.GetFieldValue(int(i),strValue);
				
				strValue.TrimLeft();
				strValue.TrimRight();
				
				//��ʾ����
				m_Grid.SetItemTextFmt(j + 1,i,strValue);
				
			}
			
			//���»�һ����¼
			rs.MoveNext();

			//����������
	        SetProgressCtrlSetIt();
		}
		
		//�ر����ݿ�
		rs.Close( );
		db.Close( );
		
		m_Grid.ShowWindow(SW_SHOW);
		m_Grid.Invalidate();

		//��������
	    ShowProgressCtrl(FALSE);
		//�����޸�״̬
		m_Grid.SetModified(FALSE,-1,-1);
		status("                   ");

	}
	
}


void CIFRMView::OnUpdateFindrepeatrecords(CCmdUI* pCmdUI) 
{

	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//ѡ������
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}	
}

//�ȴ�ʱ���
BOOL CIFRMView::WaitShiKedian(BYTE m_shikedian)
{
	m_StartRead         = TRUE;
	int  m_waitfortimes =    0;
	
	while(1)
	{
		//ʱ��
		CTime timet = CTime::GetCurrentTime();
		
		//ʱ�������
		if(timet.GetMinute() < m_shikedian)
		{
			m_waitfortimes = m_shikedian*60 - timet.GetMinute()*60 - timet.GetSecond();
		}
		else
		{
			m_waitfortimes = m_shikedian*60  + (3600 - timet.GetMinute()*60 - timet.GetSecond());	
		}
		
		if(m_waitfortimes <= 2)
		{
			break;
		}

		//��ʾ״̬����Ϣ
		StatusStr.Format("���Ѷ�0��,��%d��,���´μ��Ӷ���%4d��,���Ժ�...��",m_readchecktimes,m_waitfortimes);
		SendMessage(WM_EVENT, 1, 0);
		
		//��Զ�̷�����Ϣ
		SendContionStr.Format("BEGINS;MESSAGE:1:%s;ENDS",StatusStr);
		SendMessage(WM_EVENT, 5, 0);
		
		//�������ֹͣ��ť
		if(!m_StartRead)
		{	
			return FALSE;
			break;
		}
		
		Sleep(500);
		
		//�������ֹͣ��ť
		if(!m_StartRead)
		{	
			return FALSE;
			break;
		}
		
		Sleep(500);
		
	}

	return TRUE;

}


//�Ƿ����ǽ�����
BOOL CIFRMView::IsDyConnect(CString m_StationName)
{

	CString       strValue;
	CDatabase           db;
	
	m_StationName.TrimLeft();
    m_StationName.TrimRight();

    //�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset    rs(&db );
		strValue.Format("SELECT TRANSFORMER_NO  FROM TB_TRANSFORMER WHERE RTRIM(LTRIM(TRANSFORMER_NO))='%s' AND TRANSFORMER_CONNECTFORM=1",m_StationName);
		rs.Open(CRecordset::dynaset,strValue);	
		
		if(rs.IsEOF())
		{	
			//�ر����ݿ�
			rs.Close( );
			db.Close( );
			return FALSE;
		}
		
	   	//�ر����ݿ�
		rs.Close( );
		db.Close( );
		return TRUE;

	}

	return  FALSE;

}

void CIFRMView::OnFautoreadset() 
{
    CZHULIUTIMESELECTDlg dlgs;
	dlgs.DoModal();
}

//����������פ������
void CIFRMView::ByDateDingShiDeal()
{

	CString       str,strhalt;
	
	/*
	//���ʱ���Ƿ��˷�פ��ʱ��,10���Ӽ��һ��	,��������ʱ����Զ������
	if(Received == 2 )
	{
	    //����ͳ�ɳ��ͨѶ����û��פ���ϵĻ�
		return;
	}
	*/
	
	//��������д��ڴ���ر�
	CWnd* pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}

	pt = CWnd::FindWindow(NULL,"��̨������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�û���Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"פ������������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"��ʽ����������Ϣ");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�����Ϣ�ǼǱ�");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	pt = CWnd::FindWindow(NULL,"�õ����߷�������");
	if(pt)
	{
		pt->SendMessage(WM_CLOSE,0,0);
	}
	
	//������ڲ��Զ������ʽ���� m_others  FALSE ��������  TRUE  פ������
/*	if(ReadMeterThread != NULL)
	{
		//������ڲ��Զ������ʽ����
		if(!m_others)
		{	
			return;
		}
		
	}
*/
/*		while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}
*/
	//�Ƿ��ǵ�һ�汾,���ǵ�һ�汾���⴮�ڻ������
	/*
	if(!AppInfo::Instance().m_SingleBB) 
	{
		
		//���������״̬
		if(!m_IfChangeData)
		{
			//���������״̬ʱ,ǿ���˳��߳�
			SendMessage(WM_EVENT,14, 0);
		}
		else
		{
			//�޸Ľ������ݱ�־
			m_IfChangeData = FALSE;
			return;
		}
		
	}
	*/
	
	KillTimer(1);
    SetTimer(1,600000,NULL);         //���ö�ʱ��,10���Ӽ��һ��

	//��פ�����ڼ���Ƿ���פ��
	switch(ByDateCheckCurrentTime())
	{
	case 0:
		{
			//����ʱ��,����������ֵĻ�	
//			if(ReadMeterThread == NULL)
//			{	
/*	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}
	*/			//�����źŻ�����·����
				ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
//			}
			
			break;
		}
	case 1:
		{
//			m_StartRead    =   FALSE;
	           
			//�ͷ�CPUʱ��
			SurrenderWindowMessage();
			Sleep(2000);
			//�ͷ�CPUʱ��
			SurrenderWindowMessage();
						
			//��פ������,ÿ�ζ���
//			if(ReadMeterThread == NULL)
//			{
/*	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}			
*/				CTime timet = CTime::GetCurrentTime();
				
				/*
				CTimeSpan                          ts;
				ts   =  m_AutoReadTime    -     timet;
				
				if(ts.GetTotalSeconds() < 1800)
				{
					KillTimer(1);
					SetTimer(1,ts.GetTotalSeconds()*1000,NULL); //���ö�ʱ��,10���Ӽ��һ��
				}
				*/
				
				//��פ������
				m_SendGarrisonTimes ++;	
				
				//���������Ϊ0
				m_ReadModuleTimes  = 0;
				
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��%4d�η�[%4d-%02d-%02d %02d:%02d:%02d]��ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_SendGarrisonTimes,m_AutoReadTime.GetYear(),m_AutoReadTime.GetMonth(),m_AutoReadTime.GetDay(),m_AutoReadTime.GetHour(),m_AutoReadTime.GetMinute(),m_AutoReadTime.GetSecond());
				WriteToLog(str);
				
				//������פ���߳�
				ReadMeterThread                 =  AfxBeginThread(WorkerThread,(LPVOID)6,m_Thread_PRIORITY,0,0,NULL); 
				ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
				
//			}

			break;
		}
	case 2:
		{	
			//����ʱ�䵽��,�������,��Ҫ����פ���ſ���
//			if(ReadMeterThread == NULL)
//			{
/*
	while (ReadMeterThread != NULL)
	{ 
		Sleep(500);
	}				
*/				//��ȡ��ǰʱ��
				int m_years,m_months,m_days,m_hours,m_minutes,m_seconds;
				CTime  m_CurrentTime    =  CTime::GetCurrentTime();
				str                     =          GetZhuLiuTime();
				float            m_temp =                        0;
				CString                               m_bakstrline;
								
				str.TrimLeft();
				str.TrimRight();
				
				//פ��ʱ��Ϊ��, ע������Ҫע��=
				if(str.IsEmpty() || m_ReadModuleTimes > (m_DateReadParameter[63] + m_DateReadParameter[65]) || CDataBaseInstance::GetAllRecordsCount("TB_USER", "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'") == 0)
				{
					//�����źŻ�����·����
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
					return;
				}
				
				//פ��ʱ��
				strhalt = str;
				
				//ʱ�䴦��
				int k     = str.Find('-');
				
				//��
				m_years   = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				k         = str.Find('-');
				m_months  = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				k         = str.Find(' ');
				m_days    = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//ʱ
				k         = str.Find(':');
				m_hours   = atoi(str.Left(k));
				str       = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				k = str.Find(':');
				m_minutes = atoi(str.Left(k));
				str  = str.Right(str.GetLength() - k - 1);
				str.TrimLeft();
				str.TrimRight();
				
				//��
				m_seconds = atoi(str);
				
				CTime timebakkss(m_years,m_months,m_days,m_hours,m_minutes,m_seconds);
				m_AutoReadTime = timebakkss;
				
				//ʱ���϶
				CTimeSpan                           ts;
				ts   =  m_CurrentTime - m_AutoReadTime;
				
				if(ts.GetTotalSeconds() < 0)
				{
					
					//�����źŻ�����·����
					ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
					return;
					
				}
				else  if(ts.GetTotalSeconds() < 180)
				{
					
					if(m_ReadModuleTimes == 0)
					{
						
						//���ؿڱ�
						m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY' AND USER_AMMETERKIND>5";
						
						//��פ������
						m_SendGarrisonTimes   =   0;	
						str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��[%s]��ʱפ���ؿڱ�",m_CurrentTime.GetYear(),m_CurrentTime.GetMonth(),m_CurrentTime.GetDay(),m_CurrentTime.GetHour(),m_CurrentTime.GetMinute(),m_CurrentTime.GetSecond(),strhalt);
						WriteToLog(str);
						
						KillTimer(1);
						SetTimer(1,5*60000,NULL); 
						
						//�������
						m_ReadModuleTimes = 0;
						
						//��פ���ؿڱ�
						ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL); // ����������
						ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
						
					}
					
					
				}
				else							
				{	
					
					//���������������,ʱ�����Ļ�
					CTime timet = CTime::GetCurrentTime();
					
					//��������ſ���,10���Ӽ��һ��
	                m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
					
					KillTimer(1);
					SetTimer(1,m_SettimerValues,NULL); 			
					
					//���еĶ�����
					for(int i = 0; i < 15; i ++)
					{
						m_TimeSetLabel[i]  = TRUE;  
					}
					
					//�ؿڱ��ٶ���
					CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY' WHERE USER_AMMETERKIND>4");
					
					m_AutoReadCondtionStr = "USER_TIMELABEL<>'YYYYYYYYYYYYYYY'";
					m_SendGarrisonTimes   =   0;	//��פ������
									
					if(m_ReadModuleTimes < m_DateReadParameter[63] - 1)
					{
						//�����Сʱһ��û�ж���
						m_ReadModuleTimes        ++;    
					}
					else if(m_ReadModuleTimes == m_DateReadParameter[63] - 1)
					{
						//�����Сʱһ�θպö���
						m_ReadModuleTimes        ++; 
						
						//�����Ȱ�Сʱһ�������ʱ��
						m_FirstReadOkTime = CTime::GetCurrentTime();
					}
					else 
					{
						
						//�������������һ���Ѿ�����,Ҫ��8Сʱһ�εĶ���
						ts   =  timet  - m_FirstReadOkTime ;
						
						//4Сʱ��������8Сʱ�ض� /4 �������Ļ�
						k = (ts.GetTotalSeconds()+ 60)/14400;
						
						if(k > 0 && ((ts.GetTotalSeconds() + 60)%14400) < 1800)
						{
							
							if(k%2 == 1)
							{
									
								//4Сʱ,���������
								//m_AllLineThreeCurrent[128],��32����·4�ε���
								str         =      "";
								
								//���32����·�ĵ���
								for(k = 0 ; k < 32; k ++)
								{	
									
							        m_temp = m_AllLineThreeCurrent[k] + m_AllLineThreeCurrent[32 + k] + m_AllLineThreeCurrent[64 + k];
									
									//4Сʱһ����������10%����·�Ŷ�
									if((m_AllLineThreeCurrent[96 + k] >= 1.1*m_temp/3.0) && (m_temp > 0.01))
									{
										
										m_bakstrline.Format("%4d-%02d-%02d %02d:%02d:%02d   4Сʱһ��⣬ĸ��%d����%d��ԭ����10������(��%.2f-ԭ%.2f)",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),(k/16) + 1,(k%16) + 1,m_AllLineThreeCurrent[96 + k],m_temp/3.0);
					                    WriteToLog(m_bakstrline);

										m_bakstrline.Format(" (USER_MOTHERLINE=%d AND USER_LINENO=%d) ", (k/16) + 1,(k%16) + 1);
										
										if(str.IsEmpty())
										{
											str = str   +  m_bakstrline;
										}
										else
										{
											str =  str  + " OR "  + m_bakstrline;
										}
										
									}
									
								}
								
								if(!str.IsEmpty())
								{
									
									//����е���
								//	m_ReadModuleTimes ++;    //4Сʱһ�Ĳ���������
									m_AutoReadCondtionStr = m_AutoReadCondtionStr + "AND  (" + str + ")";

								}
								else
								{
									
									str.Format("%4d-%02d-%02d %02d:%02d:%02d   4Сʱһ��⣬û����·����ǰ����10����������·",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
					                WriteToLog(str);
									
									//�����źŻ�����·����
									ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
									ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
									return;
								}
								
								
							}
							else
							{
								//8Сʱֱ�Ӷ���
								m_ReadModuleTimes  ++;    //�������
							}
							
							
						}
						else
						{			
							
							//�����źŻ�����·����
							ReadMeterThread                 = AfxBeginThread(WorkerThread,(LPVOID)12,m_Thread_PRIORITY,0,0,NULL); 
							ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
							return;
							
						}
						
					}
					
					str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��%4d�ζ�[%s]��ʱפ��",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),m_ReadModuleTimes,strhalt);
					WriteToLog(str);
					
					//פ������,ͬʱ��·�������
					ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)4,m_Thread_PRIORITY,0,0,NULL);
					ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
								
				}				
				
//			}
			
			break;
		}
		 
	}
}


//����פ��
void CIFRMView::StartZhuLiu()
{
	CString            str;
	m_StartRead     =  TRUE;  //��ʱ��פ����ʱ����
	m_ListRows      =     0;  //�к���ʼΪ0
	m_times         =     1;  //����Ϊ0	
//	m_StartRead     = FALSE;  //ִֹͣ�д˲���

	KillTimer(1);             //ȡ��10���Ӽ��һ�μ��
	ShowDingShiButton(TRUE);  //��ʱ��ť��ΪTRUE	
	m_IsAutoSending   =  TRUE;//פ��״̬��־

	StatusStr.Format("����������פ��,�ȼ����Сʱ��%d��,������Сʱ��%d�Ρ�",m_DateReadParameter[63],m_DateReadParameter[65]);
	status(StatusStr);
    //ʱ��
	CTime timet = CTime::GetCurrentTime();
  
	//��ʼ������
    InitializeCurrent();

	//10���Ӽ��һ��
	m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;

	m_ReadModuleTimes      =     0;    //���������Ϊ0
	m_SendGarrisonTimes    =     0;    //��פ������
	m_zhuliukinds          =     1;//0 �����������פ�� 1 ��������פ��
	
	//��ʱ�������,����Щ��
	for(int i = 0; i < 15; i++)
	{
	    m_TimeSetLabel[i]  = TRUE;//��ʱ�����־
	}

	KillTimer(1);
	SetTimer(1,m_SettimerValues,NULL); //���ö�ʱ��,10���Ӽ��һ��
	
}

void CIFRMView::OnUpdateFautoreadset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CRuntimeAccount::GetCurrentPrivilege() < 2 && !m_IsAutoSending);	
}


//�����ڽ�������
CString CIFRMView::ByDateDecodeParameter()
{
	CString        str,strbak;
	str       =     "��פ��ʱ�䡿";
	int    j  =                      1;

	for(int ii = 0; ii < 31; ii ++)
	{

		if(m_DateReadParameter[2*ii] > 0)
		{
			if(j > 1)
			{
				strbak.Format("\r\n\r\n%2d��%2d��%2d��",j,ii+1,m_DateReadParameter[2*ii+1]);
			}
			else
			{
				strbak.Format("\r\n%2d��%2d��%2d��",j,ii+1,m_DateReadParameter[2*ii+1]);
			}

			str = str + strbak;
			str = str + "\r\n" + GetZhuLiuRanage(ii + 1);
			
			j ++;
		
		}

	}

	//ɨ�����(3-7��)
	strbak.Format("\r\n��ɨ�������\r\n��ÿ����Сʱɨ��%d��",m_DateReadParameter[63]);
    str = str + strbak;
	//�Ժ�ɨ�����(0-3��)
	strbak.Format("\r\n����ɨ������\r\n��ÿ����Сʱɨ��%d��",m_DateReadParameter[65]);
    str = str + strbak;
    //�Ƿ�һ�������Զ�פ��
	//pview->m_DateReadParameter[66] = m_autorun;

	if(m_DateReadParameter[66] == 1)
	{
	    strbak.Format("\r\n���Զ�������\r\n�������ʱ����פ���Զ�����");
	}
	else
	{
	    strbak.Format("\r\n���Զ�������\r\n�������ʱ����פ��������");
	}
    
	str = str + strbak;
	
	return str;


}

//�õ�һפ���յ�����
CString CIFRMView::GetZhuLiuRanage(short m_date)
{
	CString          str,strsql,StrTemp,str1,str2,str3;
	str           =               "";
    CDatabase                     db;
	long             m_subs      = 0;
	BYTE             m_AmmerAter = 0;
	int                m_GetData = 0;

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
	   
		//��CRecordset����
		CRecordset  m_CompanySet(&db);
    	strsql.Format("SELECT SUBSTRING(USER_ZHULABEL,%d,3) FROM TB_USER GROUP BY SUBSTRING(USER_ZHULABEL,%d,3) ORDER BY SUBSTRING(USER_ZHULABEL,%d,3)",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);//,(m_date-1)*15+1,(m_date-1)*15+1,(m_date-1)*15+1);	
		m_CompanySet.Open(CRecordset::forwardOnly,strsql);

		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{ 
			m_CompanySet.GetFieldValue(short(0),strsql);
			m_CompanySet.MoveNext();
			m_subs ++;
			
			if(m_subs > 1)
			{
				break;
			}			
		}

		//��¼����
		if(m_subs == 1)
		{

			strsql.TrimLeft();
			strsql.TrimRight();
            
			//ת����
			m_GetData = GetHexValue(strsql);
			m_GetData =      m_GetData%2048;
			
		    str       = "������Χ��\r\nȫ����\r\n";
			StrTemp   = "���������ݡ�\r\n";
			str       =   str   +  StrTemp;

			//�й����
			StrTemp = "";

			if((m_GetData>>9) == 3)//11
			{
               StrTemp = "�й������й����";
			}
			else if((m_GetData>>9) == 2)//10
			{
               StrTemp = "�й����";
			}

			//�޹����
			if(((m_GetData>>7)%4) == 3)//11
			{

				if(StrTemp.IsEmpty())
				{
                    StrTemp = "�޹������޹����";
				}
				else
				{
					StrTemp = StrTemp + "���޹������޹����";
				}

			}
			else if(((m_GetData>>7)%4) == 2)
			{

				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "�޹����";
				}
				else
				{
					StrTemp = StrTemp + "���޹����";

				}

			}

			//�������
            if(((m_GetData>>6)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "ABC�������";
				}
				else
				{
					StrTemp = StrTemp + "��ABC�������";
				}
				
			}

			//�����ѹ
            if(((m_GetData>>5)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "ABC�����ѹ";
				}
				else
				{
					StrTemp = StrTemp + "��ABC�����ѹ";
				}
				
			}
			
			//������
            if(((m_GetData>>4)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "������";
				}
				else
				{
					StrTemp = StrTemp + "��������";
				}
				
			}
			
			//�����
            if(((m_GetData>>3)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "�����";
				}
				else
				{
					StrTemp = StrTemp + "�������";
				}
				
			}
			
			//ƽ����
            if(((m_GetData>>2)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "ƽ����";
				}
				else
				{
					StrTemp = StrTemp + "��ƽ����";
				}
				
			}

		    //�ȵ���
            if(((m_GetData>>1)%2) == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "�ȵ���";
				}
				else
				{
					StrTemp = StrTemp + "���ȵ���";
				}
				
			}
			
			//��������
            if(m_GetData%2 == 1)
			{
				
				if(StrTemp.IsEmpty())
				{
                    StrTemp =   "��������";
				}
				else
				{
					StrTemp = StrTemp + "����������";
				}
				
			}
			
			str = str +  StrTemp;

			
		}
		else
		{				
			m_CompanySet.Close();

			strsql.Format("SELECT USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND FROM TB_USER WHERE SUBSTRING(USER_ZHULABEL,%d,3)<>'000' GROUP BY USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND ORDER BY USER_LINENAME,USER_TRANSFORMERNO,SUBSTRING(USER_ZHULABEL,%d,3),USER_AMMETERKIND",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);	
			m_CompanySet.Open(CRecordset::forwardOnly,strsql);

			str     = "������Χ��\r\n��·����                       ��̨����               ��������      �������";

			//Ѱ�����������ļ�¼
			while (!m_CompanySet.IsEOF())
			{
				
				m_CompanySet.GetFieldValue(short(0),str1);
				m_CompanySet.GetFieldValue(short(1),str2);
				str2.TrimLeft();
				str2.TrimRight();

				m_CompanySet.GetFieldValue(short(2),strsql);
                strsql.TrimLeft();
				strsql.TrimRight();
				
				StrTemp   = "";
				
				//ת����
				m_GetData = GetHexValue(strsql);
				m_GetData =      m_GetData%2048;
						
				//�й����
				StrTemp = "";
				
				if((m_GetData>>9) == 3)//11
				{
					StrTemp = "�й������й����";
				}
				else if((m_GetData>>9) == 2)//10
				{
					StrTemp = "�й����";
				}
				
				
				//�޹����
				if(((m_GetData>>7)%4) == 3)//11
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp = "�޹������޹����";
					}
					else
					{
						StrTemp = StrTemp + "���޹������޹����";
					}
					
				}
				else if(((m_GetData>>7)%4) == 2)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "�޹����";
					}
					else
					{
						StrTemp = StrTemp + "���޹����";
						
					}
					
				}
				
				//�������
				if(((m_GetData>>6)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "ABC�������";
					}
					else
					{
						StrTemp = StrTemp + "��ABC�������";
					}
					
				}
				
				//�����ѹ
				if(((m_GetData>>5)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "ABC�����ѹ";
					}
					else
					{
						StrTemp = StrTemp + "��ABC�����ѹ";
					}
					
				}
				
				//������
				if(((m_GetData>>4)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "������";
					}
					else
					{
						StrTemp = StrTemp + "��������";
					}
					
				}
				
				//�����
				if(((m_GetData>>3)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "�����";
					}
					else
					{
						StrTemp = StrTemp + "�������";
					}
					
				}
				
				//ƽ����
				if(((m_GetData>>2)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "ƽ����";
					}
					else
					{
						StrTemp = StrTemp + "��ƽ����";
					}
					
				}
				
				//�ȵ���
				if(((m_GetData>>1)%2) == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "�ȵ���";
					}
					else
					{
						StrTemp = StrTemp + "���ȵ���";
					}
					
				}
				
				//��������
				if(m_GetData%2 == 1)
				{
					
					if(StrTemp.IsEmpty())
					{
						StrTemp =   "��������";
					}
					else
					{
						StrTemp = StrTemp + "����������";
					}
					
				}
				
				m_CompanySet.GetFieldValue(int(3),strsql);
				m_AmmerAter = atoi(strsql);
				
				if(m_AmmerAter == 0)
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"�����");
				}
				else  if(m_AmmerAter == 1)
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"���û���");
				}
				else
				{
					str3.Format("%14s  %20s  %16s  %12s",str1,str2,StrTemp,"̨����");
				}
				
				str = str + "\r\n" + str3;
				

				m_CompanySet.MoveNext();
			
			}
			

		}

    	m_CompanySet.Close();
		db.Close();

    }

	return str;
}

//ʮ�����ַ�ת����
int CIFRMView::GetHexValue(CString str)
{
    int iReturn = 0;

	int length = str.GetLength();
    for(int i = length - 1; i >= 0; i--)    
    {
		char cc =  str.GetAt(i);// str[i];

        if(cc >= '0' && cc <= '9')
            iReturn += int((cc - '0') * pow((double)16,length - i - 1));
        else if(cc >= 'a')
            iReturn += int((cc - 'a' + 10) * pow((double)16,length - i - 1));
        else 
            iReturn += int((cc - 'A' + 10) * pow((double)16,length - i - 1));
    }

    return iReturn ;
}

//�Զ�����������פ��
void CIFRMView::ByDateAutoGarrisonTime()
{
    CString               str;
	CDatabase              db;	
	int i;
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset   rs(&db );
		str = "SELECT * FROM TB_DateAuto";
		rs.Open(CRecordset::dynaset,str);
		
		if(rs.IsEOF())
		{
			//�ر����ݿ�
		    rs.Close( );
		    db.Close( );
			return;
		}
		
		//���Զ�������Ϣ
		for( i = 0; i < 67; i++)
		{
			rs.GetFieldValue((short)i,str);
			m_DateReadParameter[i] = atoi(str);
		}

		//�ر����ݿ�
		rs.Close( );
		db.Close( );

        if(m_DateReadParameter[66] > 0)
		{

			//15�����͵����� a��ֵ��0���й����-�����ۼ�ֵ 1���й����-����ֵ 2���޹����-�����ۼ�ֵ 3���޹����-����ֵ 4��A����� 5��B����� 6��C����� 7��A���ѹ 8��B���ѹ 9��C���ѹ 10-������ 11-����� 12-�ȵ��� 13��ƽ���� 14-��������
			for( i = 0; i < 15; i++)
			{
				m_TimeSetLabel[i]  = TRUE;  
			}	
			
			//ִֹͣ�д˲���
			m_StartRead      =  FALSE;
			
			//ʱ��
			CTime timet = CTime::GetCurrentTime();//ʱ��
			str.Format("��%4d-%02d-%02d %02d:%02d:%02d����������פ��:\r\n%s ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ByDateDecodeParameter());
			WriteToLog(str);
			
			//ȡ��10���Ӽ��һ�μ��
			KillTimer(1);
			
			ShowDingShiButton(TRUE);//��ʱ��ť��ΪTRUE
			m_IsAutoSending     =           TRUE;//פ��״̬��־
			m_ReadModuleTimes   =              0;//���������Ϊ0
			m_SendGarrisonTimes =              0;//��פ������
			m_IfChangeData      =          FALSE;             //�޸Ľ������ݱ�־
			m_zhuliukinds       =               1;//פ������ 0 ��������� 1 ����������

			StatusStr.Format("����������פ��,�ȼ����Сʱ��%d��,������Сʱ��%d�Ρ�",m_DateReadParameter[63],m_DateReadParameter[65]);
			status(StatusStr);
			
			//10���Ӽ��һ��
	        m_SettimerValues = ((10 - timet.GetMinute()%10)*60 - timet.GetSecond())*1000;
			
			SetTimer(1,m_SettimerValues,NULL);//���ö�ʱ��,10���Ӽ��һ��

		}
	
	}
}

//���ð��������ò���
void CIFRMView::ByDateSetGarrisonRange(BYTE m_date)
{
	CString          strsql,StrRange,str;
    CDatabase                         db;
	int                        m_GetData;
	
	//�Ȱ���ǰ��ȫ�ĳɶ���״̬
	CDataBaseInstance::ExecuteDataBaseSQL("UPDATE TB_USER SET USER_TIMELABEL='YYYYYYYYYYYYYYY'");
	
	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
	   
		//��CRecordset����
		CRecordset  m_CompanySet(&db);
    	strsql.Format("SELECT SUBSTRING(USER_ZHULABEL,%d,3) FROM TB_USER GROUP BY SUBSTRING(USER_ZHULABEL,%d,3) ORDER BY SUBSTRING(USER_ZHULABEL,%d,3)",(m_date-1)*3+1,(m_date-1)*3+1,(m_date-1)*3+1);	
		m_CompanySet.Open(CRecordset::forwardOnly,strsql);

		//Ѱ�����������ļ�¼
		while (!m_CompanySet.IsEOF())
		{ 
			m_CompanySet.GetFieldValue(short(0),str);
			str.TrimLeft();
			str.TrimRight();

			//����ת����
			m_GetData   = GetHexValue(str);
			m_GetData   =   m_GetData%2048;
    	    StrRange    =               "";

			if((m_GetData>>9) == 3)//11
			{
				StrRange = StrRange + "NN";
			}
			else if((m_GetData>>9) == 2)//10
			{
				StrRange = StrRange + "NY";
			}
			else
			{
				StrRange = StrRange + "YY";
			}

			//�޹����
			if(((m_GetData>>7)%4) == 3)//11
			{
				StrRange = StrRange + "NN";
			}
			else if(((m_GetData>>7)%4) == 2)
			{
				StrRange = StrRange + "NY";
			}
			else
			{
				StrRange = StrRange + "YY";
			}

			//�������
            if(((m_GetData>>6)%2) == 1)
			{
				StrRange = StrRange + "NNN";
			}
			else
			{
				StrRange = StrRange + "YYY";
			}

			//�����ѹ
            if(((m_GetData>>5)%2) == 1)
			{
				StrRange = StrRange + "NNN";
			}
			else
			{
				StrRange = StrRange + "YYY";
			}
			
			//������
            if(((m_GetData>>4)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
			
			//�����
            if(((m_GetData>>3)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
			
			//ƽ����
            if(((m_GetData>>2)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
	
		    //�ȵ���
            if(((m_GetData>>1)%2) == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
		
			
			//��������
            if(m_GetData%2 == 1)
			{
				StrRange = StrRange + "N";
			}
			else
			{
				StrRange = StrRange + "Y";
			}
		
	        //�滻	
			strsql.Format("UPDATE TB_USER SET USER_TIMELABEL='%s' WHERE SUBSTRING(USER_ZHULABEL,%d,3)='%s'",StrRange,(m_date-1)*3+1,str);
			CDataBaseInstance::ExecuteDataBaseSQL(strsql);

			m_CompanySet.MoveNext();
	
		}

		m_CompanySet.Close();
		db.Close();
	}

}

void CIFRMView::OnCancelautozhuliu() 
{
	CString     str;

	//ȡ���Զ�פ��
	if(MessageBox("����ȡ���������ʱ���Զ�����פ���˹�����","ѯ��",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		
		//ȥ����������Զ�פ��
		if(IsCurveTableExist("TB_Auto"))
		{
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_Auto","ALL") > 0)
			{
				
				str.Format("UPDATE TB_Auto SET Auto_Parameter110=%d",0);
				CDataBaseInstance::ExecuteDataBaseSQL(str);
				
			}
			
		}

		//ȥ�������Զ�פ��
		if(IsCurveTableExist("TB_DateAuto"))
		{
			
			if(CDataBaseInstance::GetAllRecordsCount("TB_DateAuto","ALL") > 0)
			{
				
				str.Format("UPDATE TB_DateAuto SET Auto_Parameter67=%d",0);
				CDataBaseInstance::ExecuteDataBaseSQL(str);
				
			}
			
		}


		m_parameter[109]        = 0;
		m_DateReadParameter[66] = 0;

		MessageBox("�������ʱ����פ���˹�����ȡ����"," ",MB_OK|MB_ICONASTERISK);

		
	}
	
}

//�Զ�פ��
void CIFRMView::OnUpdateCancelautozhuliu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_IsAutoSending  && CRuntimeAccount::GetCurrentPrivilege() < 2 && (m_parameter[109]>0 || m_DateReadParameter[66]>0));	
}

//��Сʱ��������С�������е���
void CIFRMView::EveryHourCheckLine()
{
	if(!m_StartRead)
	{
        return;
	}
	
	//��ʾ��
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	CDatabase                   db;
	CString        str,MsgStr,str1;
    BYTE         MotherLine,LineNo;
	int                          k;
	BOOL     m_IfHaveElc    = FALSE;
	CString           m_GetValue[3];

	//�����ݿ�
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		SurrenderWindowMessage();
		
		//��ʾ״̬����Ϣ
		StatusStr = "���ڲ�����·����״̬�����Ժ�...";
		SendMessage(WM_EVENT, 1, 0);

		//��CRecordset����
		CRecordset  m_CompanySet(&db);	
		str.Format("SELECT USER_LINENAME,USER_MOTHERLINE,USER_LINENO FROM TB_USER GROUP BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO ORDER BY USER_LINENAME,USER_MOTHERLINE,USER_LINENO");
		m_CompanySet.Open(CRecordset::dynaset,str);
		
		//Ѱ�����������ļ�¼
      	while (!m_CompanySet.IsEOF())
		{
			
			SurrenderWindowMessage();

			if(	!m_StartRead)
			{
				break;
			}
			
			//��·����
			m_CompanySet.GetFieldValue(short(0),str1);
			str1.TrimRight();
			str1 = str1 + "��·";
			
			//��ʾ״̬����Ϣ
		    StatusStr = "���ڼ����·" + str1 + "�����Ժ�...";
		    SendMessage(WM_EVENT, 1, 0);

          	m_CompanySet.GetFieldValue(int(1),str);
			MotherLine  =  atoi(str);

			m_CompanySet.GetFieldValue(int(2),str);
            LineNo      =  atoi(str);;
			
			//��ʾ�汾
			if(AppInfo::Instance().m_YanShi)
			{
				//����Ƿ���ͣ��״̬
				Sleep(1000);
				MsgStr.Format("%.2f|%.2f|%.2f",float(rand()/440000),float(rand()/440000),float(rand()/440000));
			}
			else
			{
				//����Ƿ���ͣ��״̬
				MsgStr =  CheckCurrentValue(MotherLine,LineNo,FALSE);
			}

			m_GetValue[0] =     "";
            m_GetValue[1] =     "";
            m_GetValue[2] =     "";
            m_IfHaveElc   =  FALSE;

			//�ֽ�MsgStr�ַ���
			k = MsgStr.Find("|");
			
			if( k != -1)
			{
				m_GetValue[0] = MsgStr.Left(k);
				MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);

				k = MsgStr.Find("|");
	            
				if( k != -1)
				{
					m_GetValue[1] = MsgStr.Left(k);
					MsgStr        = MsgStr.Right(MsgStr.GetLength()-k-1);
					m_GetValue[2] = MsgStr;
				}
				
			}

			for(int ll = 0; ll < 3; ll ++)
			{
				
				if(atol(m_GetValue[ll]) > 1000)
				{
					m_IfHaveElc  = TRUE;
				}				
				
			}
			
			//��������е���
            if(((MotherLine-1)*15 + LineNo - 1) < 32)
			{

				//����е���
				if(m_IfHaveElc)
				{
					m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  1;
				}
				else
				{
					m_All_Line_Current[(MotherLine-1)*15 + LineNo - 1] =  0;
				}

			}
		
			CTime time    = CTime::GetCurrentTime();
			str.Format("%sifrm_%d_%02d_Three_Current_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
			k             =                  0;
			CFileFind                   finder;//�Ƿ��д��ļ�
			
			//�������������������
			if(finder.FindFile(str) != 0) 
			{ 
				k  = 1;
			}

			finder.Close();
								
			FILE *text;
			if((text = fopen(str,"a")) != NULL)
			{	
				
				if(k == 0)
				{
					//���Զ���,A�����,B�����,C�����,����ʱ��
					str.Format("���Զ���,A�����,B�����,C�����,����ʱ��\n");
                    fputs(str,text);
				}
				
				str.Format("%s,%.2f,%.2f,%.2f,%4d-%02d-%02d %02d:%02d:%02d\n",str1,atof(m_GetValue[0])/440000,atof(m_GetValue[1])/440000,atof(m_GetValue[2])/440000,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
				fputs(str,text);

				fclose(text);
			}

			if(!m_IfHaveElc)
			{	
				str.Format("%4d-%02d-%02d %02d:%02d:%02d   ��·����:%16s[%2d-%2d]  ���ͣ��",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond(),str1,MotherLine,LineNo);
				WriteToLog(str);
			}
			
			m_CompanySet.MoveNext();

		}
		
		m_CompanySet.Close();
		db.Close();
		
		StatusStr = "��������������";
		SendMessage(WM_EVENT, 1, 0);	
		
		//�������ģ�������ѹ
//		SendMessage(WM_EVENT, 17, 0);
    }

}

void CIFRMView::OnChangeammeter() 
{
    CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);

	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	if(m_CCHANGEAMMETER->IsOpen())
	{
		m_CCHANGEAMMETER->Close();
	}
	
	//���ݿ���Ƿ��
	if(m_CCHANGEAMMETER->Open(AFX_DB_USE_DEFAULT_TYPE,NULL,CRecordset::useBookmarks))
	{
		
		CCHANGEAMMETERDlg dlg(m_CCHANGEAMMETER.get(),0);
		dlg.m_filtercondtion = "";
		
		dlg.DoModal();
		
		if(m_CCHANGEAMMETER->IsOpen())
		{
			m_CCHANGEAMMETER->Close();
		}
		
	}	
}

//��ʼ������
void CIFRMView::InitializeCurrent()
{

	for(int ii = 0; ii < 128; ii ++)
	{
		m_AllLineThreeCurrent[ii] = 0;//��32����·3�ε���,����·�ĵ���ֵ���2*16=32 32*3 = 96 ÿ����·��3�ε���
	}	
	
}

void CIFRMView::OnModifyprotcol() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	CString         StrSql;
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
    
	 CProtcoldlg   dlg;
	
	 if(dlg.DoModal() == IDOK)
	 {
		 
		 switch(dlg.m_kinds)
		 {
		 case 0:
			 {
				 //����Э��
				 StrSql.Format("��ѡ�û�ģ��[%d��]����Э�鶼��Ϊ%dЭ����\r\n���棺�޸Ĵ˲�������Ӱ�����ݳ��������أ�",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 case 1:
			 {
				 //ģ��ĸ��
 				 StrSql.Format("��ѡ�û�ģ��[%d��]ĸ�߱�Ŷ���Ϊ%d��\r\n���棺�޸Ĵ˲�������Ӱ�����ݳ��������أ�",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 case 2:
			 {
				 //ģ�����
  				 StrSql.Format("��ѡ�û�ģ��[%d��]���߱�Ŷ���Ϊ%d��\r\n���棺�޸Ĵ˲�������Ӱ�����ݳ��������أ�",CDataBaseInstance::GetAllRecordsCount("TB_USER", pMainFrm->m_wndMyDialogBar.SelectCondition()),dlg.m_protcol);
				 break;
			 }
		 }

		 if(MessageBox(StrSql," ",MB_YESNO|MB_ICONQUESTION) != IDYES)
		 {
			 return;
		 }	
		 
		 switch(dlg.m_kinds)
		 {
		 case 0:
			 {
				 //����Э��
				 StrSql.Format("Update TB_USER SET USER_PROTOCOL=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 case 1:
			 {
				 //ģ��ĸ��
				 StrSql.Format("Update TB_USER SET USER_MOTHERLINE=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 case 2:
			 {
				 //ģ�����
				 StrSql.Format("Update TB_USER SET USER_LINENO=%d WHERE %s",dlg.m_protcol,pMainFrm->m_wndMyDialogBar.SelectCondition());
				 break;
			 }
		 }

		 CDataBaseInstance::ExecuteDataBaseSQL(StrSql);
		 		 		 
		 MessageBox("��ѡģ�鳭������޸���ϣ�","  ",MB_OK|MB_ICONASTERISK);

	 }

}

//����ģ��ͨ��״̬���
void CIFRMView::OnWxcheckstatus() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	for(int i = 0; i < 6; i ++)
	{
	    m_TestParameter[i] = 0;
	}

	CTestCommDlg  dlg;

	if(dlg.DoModal() == IDOK)
	{	
		//���DIALOGBAR�ɼ��Ļ�������
    	SendMessage(WM_EVENT, 6, 0);

		m_TestParameter[0] = dlg.m_test1;
		m_TestParameter[1] = dlg.m_test2;
		m_TestParameter[2] = dlg.m_test3;
		m_TestParameter[3] = dlg.m_test4;
		m_TestParameter[4] = dlg.m_test5;
		m_TestParameter[5] = dlg.m_testtimes;
		//��������״̬���
		ReadMeterThread = AfxBeginThread(WorkerThread,(LPVOID)14,m_Thread_PRIORITY,0,0,NULL); // ����������
		ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
	}

}

//���ͨ��״̬,��A���Ƿ�ɹ�
void CIFRMView::CheckTongXunStatus()
{
	//��ʾ��
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE     ORDER[15];
	int m_SuccessTimes[4] = {0};
	int m_NoAnswers[4]    = {0};
	CString                 str;
  	m_StartRead             =  TRUE;//��ͣ��־
    int     m_connecttimes  =     0;	


	//ɾ�����е�����
	m_Grid.DeleteAllItems();
	m_Grid.ShowWindow(SW_SHOW);		
	
	TRY { 
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetRowCount(1);     //��
		m_Grid.SetColumnCount(15);  //��
		
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
       #ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
       #endif
		
		GV_ITEM       Item;
		Item.mask    = GVIF_TEXT|GVIF_FORMAT;
		Item.row     =   0;
		Item.col     =   0;
		
		Item.nFormat = dwTextStyle;
		Item.col     =   0;
		Item.strText.Format("%s","1�γɹ�");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(0,70); 

		Item.col     =   1;
		Item.strText.Format("%s","1��ĩ��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(1,70); 
		
		Item.col     =   2;
		Item.strText.Format("%s","1�γɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(2,70); 
		
	
		Item.col     =   3;
		Item.strText.Format("%s","2�γɹ�");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(3,70); 

		Item.col     =   4;
		Item.strText.Format("%s","2��ĩ��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(4,70); 

		Item.col     =   5;
		Item.strText.Format("%s","2�γɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(5,70);

		Item.col     =   6;
		Item.strText.Format("%s","3�γɹ�");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(6,70); 

		Item.col     =   7;
		Item.strText.Format("%s","3��ĩ��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(7,70); 

		Item.col     =   8;
		Item.strText.Format("%s","3�γɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(8,70);

		Item.col     =   9;
		Item.strText.Format("%s","4�γɹ�");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(9,70); 

		Item.col     =   10;
		Item.strText.Format("%s","4��ĩ��");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(10,70); 

		Item.col     =   11;
		Item.strText.Format("%s","4�γɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(11,70);

		
		Item.col     =   12;
		Item.strText.Format("%s","�ܳɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(12,70); 
		
		Item.col     =   13;
		Item.strText.Format("%s","��ĩ�ش�");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(13,70); 
		
		Item.col     =   14;
		Item.strText.Format("%s","�ܳɹ���");
		m_Grid.SetItem(&Item);
		m_Grid.SetColumnWidth(14,70);
		
		m_Grid.SetModified(FALSE,-1,-1);//ֻ��״̬
		m_Grid.m_title  = "";	//����
		m_Grid.SetBkColor(RGB(255,255,255));
		m_Grid.Invalidate();
		m_Grid.Refresh();
	}
	CATCH (CMemoryException, e)
	{
		e->Delete();
		return;
	}
	END_CATCH
		
	SurrenderWindowMessage();
			
	//��ʾ������
	ShowProgressCtrl(TRUE);
	//��ʾ����
	m_Grid.InsertRow(_T(" "), -1);
	m_Grid.Invalidate(); 
	
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
	dwTextStyle |= DT_END_ELLIPSIS;
#endif
	
	GV_ITEM  Item;
	Item.mask    = GVIF_TEXT|GVIF_FORMAT;
	Item.row     = m_Grid.GetRowCount() - 1;

	SetProgressCtrlRange(0,m_TestParameter[5],1);
	
	for(int i = 0; i < m_TestParameter[5]; i ++)
	{
		
		if(!m_StartRead)
		{
			break;
		}
		
		//4��ĸ��
		for(int ii  = 0; ii < 4; ii ++)
		{
			

			if(m_TestParameter[0] == 0 && ii == 0)
			{
				continue;
			}

			if(m_TestParameter[1] == 0 && ii == 1)
			{
				continue;
			}

			
			if(m_TestParameter[2] == 0 && ii == 2)
			{
				continue;
			}

			if(m_TestParameter[3] == 0 && ii == 3)
			{
				continue;
			}

			m_connecttimes ++;

			//��ʾ״̬����Ϣ
			StatusStr.Format("���ڲ��%d(%d)��,��%d��ĸ��,���%d������ͨѶ���Ժ�...",i + 1,m_TestParameter[5],ii + 1,m_TestParameter[4]);
			SendMessage(WM_EVENT, 1, 0);

			ORDER[0]    = 0x51;//ǰ����
			ORDER[1]    = 0x52;
			ORDER[2]    = 0x58;//A����źŽǶ�
			ORDER[3]    = ii;  //ĸ��
			ORDER[4]    = 0;
			ORDER[5]    = 0;
			ORDER[6]    = 0;
			ORDER[7]    = 0;
			ORDER[8]    = 0;
			ORDER[9]    = 0;
			ORDER[10]   = 0;
			ORDER[11]   = 0;
			ORDER[12]   = 0;
			ORDER[13]   = 0;

			SurrenderWindowMessage();
			m_angles  =         0xff;
			
			//��Ƭ��������
			if(PcSendToSCM(ORDER,31,0))
			{
				
				Sleep(1000);
				
				if((m_angles != 0xff) && (m_angles > 0))
				{
					
					switch(ii)
					{
					case 0:
						{
					       m_SuccessTimes[0] ++;
						   break;
						}
					case 1:
						{
					       m_SuccessTimes[1] ++;
						   break;
						}
					case 2:
						{
					       m_SuccessTimes[2] ++;
						   break;
						}
					case 3:
						{
					       m_SuccessTimes[3] ++;
						   break;
						}
					}
					
				}
				
				if(m_angles == 0xff) 
				{

					switch(ii)
					{
					case 0:
						{
					       m_NoAnswers[0] ++;
						   break;
						}
					case 1:
						{
					       m_NoAnswers[1] ++;
						   break;
						}
					case 2:
						{
					       m_NoAnswers[2] ++;
						   break;
						}
					case 3:
						{
					       m_NoAnswers[3] ++;
						   break;
						}
					}
					
				}
				
			}	
			
			
			switch(ii)
			{
			case 0:
				{
					//1�γɹ�����
					str.Format("%7d",m_SuccessTimes[0]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 0, str);
					//1��ĩ�ش���
					str.Format("%7d",m_NoAnswers[0]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 1, str);

					//1��ͨѶ�ɹ���	
					if((i + 1 - m_NoAnswers[0]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[0]*1.00/(i + 1 - m_NoAnswers[0])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 2, str);
 					break;
				}
			case 1:
				{
					//2�γɹ�����
					str.Format("%7d",m_SuccessTimes[1]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 3, str);
					//2��ĩ�ش���
					str.Format("%7d",m_NoAnswers[1]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 4, str);

					//2��ͨѶ�ɹ���	
					if((i + 1 - m_NoAnswers[1]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[1]*1.00/(i + 1 - m_NoAnswers[1])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 5, str);
					break;
				}
			case 2:
				{
					//3�γɹ�����
					str.Format("%7d",m_SuccessTimes[2]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 6, str);
					//2��ĩ�ش���
					str.Format("%7d",m_NoAnswers[2]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 7, str);

					//2��ͨѶ�ɹ���	
					if((i + 1 - m_NoAnswers[2]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[2]*1.00/(i + 1 - m_NoAnswers[2])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 8, str);
					break;
				}
			case 3:
				{
					//4�γɹ�����
					str.Format("%7d",m_SuccessTimes[3]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 9, str);
					//4��ĩ�ش���
					str.Format("%7d",m_NoAnswers[3]);
					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 10, str);
				
					//4��ͨѶ�ɹ���	
					if((i + 1 - m_NoAnswers[3]) > 0)
					{
						str.Format("%.2f%s",m_SuccessTimes[3]*1.00/(i + 1 - m_NoAnswers[3])*100,"%");
					}
					else
					{
						str = "";
					}

					m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 11, str);
					break;
				}

			}
						
			//�ܳɹ�����
			str.Format("%7d",m_SuccessTimes[0] + m_SuccessTimes[1] + m_SuccessTimes[2] + m_SuccessTimes[3]);
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 12, str);
			
			//��ĩ�ش���
			str.Format("%7d",m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3]);
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 13, str); 
			
			//��ͨѶ�ɹ���
			if((m_connecttimes - (m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3])) > 0)
			{
				str.Format("%.3f",(m_SuccessTimes[0] + m_SuccessTimes[1] + m_SuccessTimes[2] + m_SuccessTimes[3])*100.00/(m_connecttimes - (m_NoAnswers[0] + m_NoAnswers[1] + m_NoAnswers[2] + m_NoAnswers[3])));
			}
			else
			{
				str = "";
			}
			
			m_Grid.SetItemText(m_Grid.GetRowCount() - 1, 14, str); 
				
			m_Grid.Invalidate();
			m_Grid.Refresh();
			
			SurrenderWindowMessage();
					
			if(m_TestParameter[4]  > 0)
			{

				for(int j = 0; j < 4*(m_TestParameter[4] -1); j ++)
				{
					
					Sleep(250);	
					SurrenderWindowMessage();
					
					if(!m_StartRead)
					{
						break;
					}
					
				}

			}
			
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}

		}

		if(!m_StartRead)
		{
			break;
		}

		SetProgressCtrlSetIt();
		SurrenderWindowMessage();
		
	}

	m_Grid.SetModified(FALSE,-1,-1);//ֻ��״̬

	if(m_StartRead)
	{ 
		StatusStr = "����������";
	}
	else
	{
		StatusStr = "������жϡ�";
	}	
	
	SendMessage(WM_EVENT, 1, 0);
	
	//���ع�����
	ShowProgressCtrl(FALSE);
	
    m_StartRead  =   FALSE;

}


//�������ֵ
int CIFRMView::ChangeIValue(BYTE m_Ivale)
{
	int m_ReturnValue = 0;

	if(m_Ivale <= 22)
	{
		m_ReturnValue =  m_Ivale*1.000/22*400;
	}
	else if(m_Ivale > 22 && m_Ivale <= 38)
	{
		m_ReturnValue =  400 + (m_Ivale-22)*1.000/(38-22)*(720  - 400);
	}
	else if(m_Ivale > 38 && m_Ivale <= 53)
	{
		m_ReturnValue =  720 + (m_Ivale-38)*1.000/(53-38)*(800  - 720);
	}
	else if(m_Ivale > 53 && m_Ivale <= 57)
	{
		m_ReturnValue =  800 + (m_Ivale-53)*1.000/(57-53)*(912  - 800);
	}
	else if(m_Ivale > 57 && m_Ivale <= 73)
	{
		m_ReturnValue =  912 + (m_Ivale-57)*1.000/(73-57)*(1200 - 912);
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

//��������ģ�������ѹ
void CIFRMView::CheckWireLess()
{

	//��ʾ��
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE             ORDER[15];
	int m_SuccessTimes =     0;
	CString           str,str1;
	CString             newstr;

	newstr          =   "";
		
	if(!m_StartRead)
	{
		return;
	}

	for(int jjj = 0; jjj < 6;  jjj ++)
	{
		
		if(!m_StartRead)
		{
			break;
		}
		
		//��ʾ״̬����Ϣ
		StatusStr.Format("���ڲ��Ե�%d������ͨѶ״̬�����Ժ�...",jjj + 1);
		SendMessage(WM_EVENT, 1, 0);
		int j;
		for( j = 0; j < 4; j ++)
		{
			
			Sleep(250);	
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}
			
		}
		
		SurrenderWindowMessage();
		
		ORDER[0]    = 0x51;//ǰ����
		ORDER[1]    = 0x52;
		
		switch(jjj)
		{
		case 0:
			{
				ORDER[2]    = 0xc6;//A������ģģ��
				ORDER[3]    =    0;//ĸ��
				break;
			}
		case 1:
			{
				ORDER[2]    = 0xc7;//B������ģģ��	
				ORDER[3]    =    0;//ĸ��
				break;
			}
		case 2:
			{
				ORDER[2]    = 0xc8;//C������ģģ��	
				ORDER[3]    =    0;//ĸ��
				break;
			}
		case 3:
			{
				ORDER[2]    = 0xc6;//A������ģģ��
				ORDER[3]    =    1;//ĸ��
				break;
			}
		case 4:
			{
				ORDER[2]    = 0xc7;//B������ģģ��	
				ORDER[3]    =    1;//ĸ��
				break;
			}
		case 5:
			{
				ORDER[2]    = 0xc8;//C������ģģ��	
				ORDER[3]    =    1;//ĸ��
				break;
			}
		}
		
		ORDER[4]    = 0;
		ORDER[5]    = 0;
		ORDER[6]    = 0;
		ORDER[7]    = 0;
		ORDER[8]    = 0;
		ORDER[9]    = 0;
		ORDER[10]   = 0;
		ORDER[11]   = 0;
		ORDER[12]   = 0;
		ORDER[13]   = 0;
		m_angles    = 0xff;
		
		//��Ƭ��������
		if(PcSendToSCM(ORDER,31,0))
		{
			
			Sleep(50);
			
			if(m_angles != 0xff)
			{
				
				m_SuccessTimes ++;
				
			}
			
		}
		
		for( j = 0; j < 4; j ++)
		{
			
			Sleep(250);	
			
			SurrenderWindowMessage();
			
			if(!m_StartRead)
			{
				break;
			}
			
		}
		
		//ͨѶ�ɹ�����
		if(m_angles == 0xff)
		{
			str = "ͨѶ����";
		}
		else
		{
			//ǰ1λΪ��ѹ    0  ��  1��
			if(m_angles/128 > 0)
			{
				str.Format("�� %d",ChangeIValue(m_angles%128));
			}
			else
			{
				str.Format("�� %d",ChangeIValue(m_angles%128));
			}
			
		}	
		
		newstr = newstr + str + ",";
		
		SurrenderWindowMessage();
	}	
	
	//ͨѶ�ɹ�����
	str.Format("%d",m_SuccessTimes);
	newstr = newstr + str + ",";
		
	//��ͨѶ����
	str.Format("%d",6);
	newstr = newstr + str + ",";
		
	//ͨѶ�ɹ���
	str.Format("%.2f%s",m_SuccessTimes*1.00/6*100,"%");
	newstr = newstr + str + ",";
	
	CTime time    = CTime::GetCurrentTime();
	str.Format("%sifrm_%d_%02d_Wireless_Info_log.csv",GetFileFolderPass,time.GetYear(),time.GetMonth());
	BYTE   k         =               0;
	CFileFind                   finder;//�Ƿ��д��ļ�
	
	//�������������������
	if(finder.FindFile(str) != 0) 
	{ 
		k  = 1;
	}
	
	finder.Close();
	
	FILE *text;
	if((text = fopen(str,"a")) != NULL)
	{	
		
		if(k == 0)
		{
			fputs("1��A���ѹ����,1��B���ѹ����,1��C���ѹ����,2��A���ѹ����,2��B���ѹ����,2��C���ѹ����,ͨѶ�ɹ�����,��ͨѶ����,ͨѶ�ɹ���,����ʱ��\n",text);
		}
		
		str1.Format("%4d-%02d-%02d %02d:%02d:%02d\n",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		
		fputs(newstr + str1,text);		
		fclose(text);
	}
	
	SurrenderWindowMessage();
}

//���鵱ǰ�������Ƿ���Ч m_kinds 0 ���Ժ��ϴε�����ȣ�1����=
BOOL CIFRMView::CheckReadValueValid(long m_module,CString m_FieldName,double Currentvalue,CString m_zhutimeValue,BYTE m_kinds)
{
	CDatabase                    dbs;	
	CString                   strSql;
	double       m_tempvalue  =    0;
	int          m_days       =    0;
	BOOL         m_Successing = FALSE;

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset             rs(&dbs);
		strSql.Format("SELECT  count(*) FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d AND %s>= 0.01", m_module,m_module,m_FieldName);
//		strSql.Format("SELECT count(*) FROM TB_GARRISON WHERE GARRISON_MODULENO=%d AND %s>= 0.01",m_module,m_FieldName); //IS NOT  NULL
//      WriteToLog(strSql);
		
		rs.Open(CRecordset::forwardOnly,strSql);
		rs.GetFieldValue((short)0,strSql);
		rs.Close();

		if(atol(strSql) > 0)
		{			

			//GARRISON_WORKDEGREE
			strSql.Format("SELECT  %s,DATEDIFF(day,GARRISON_HALTTIME, '%s'),GARRISON_HALTTIME FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d", m_FieldName,m_zhutimeValue,m_module,m_module);
	        rs.Open(CRecordset::forwardOnly,strSql);

			//��ֵ
			rs.GetFieldValue((short)0,strSql);
        //	WriteToLog(strSql);
    	//	WriteToLog("��ֵ:" + strSql);			
			m_tempvalue = atof(strSql);
			
			//ʱ�������
			rs.GetFieldValue((short)1,strSql);
			
		//	WriteToLog("ʱ�������:" + strSql);

			m_days     = atoi(strSql);
			rs.Close();

		//	strSql.Format("��ֵ:%f",Currentvalue - m_tempvalue);
		//	WriteToLog(strSql);
			if(m_days == 0)
			{
				m_days  =  1;
			}

			//���Ե�
			if(m_kinds == 0 || (m_days == 1 &&  m_kinds > 0))
			{
				//һ����0~200��
				if(((Currentvalue - m_tempvalue) <= m_days*200) && ((Currentvalue - m_tempvalue) >= 0))
				{
					m_Successing = TRUE;
				}
			}
			else
			{
				//һ����0~200��
				if(((Currentvalue - m_tempvalue) <= m_days*200) && ((Currentvalue - m_tempvalue) > 0))
				{
					m_Successing = TRUE;
				}
				
			}
			
		}
		else
		{
			m_Successing = TRUE;
		}

		//�ر����ݿ�
		dbs.Close();	

	}
	
	return m_Successing; 

}


//ȫ�����������������,�ɼ���ͨ��
double CIFRMView::ReadSixChannelMeter(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/,BYTE Item/* Ҫʲô����*/,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/,CString m_AmmeterType/*������ͺ�*/)
{
//	WriteToLog("[�ǽǶ���]");

	double  m_RetuenValue =  0;
	double  m_tempvalue   =  0;
	int     HalfCount  =     0;
	BOOLEAN bHalfReady = FALSE;
	bStopped           = FALSE;
	U32                  count;
	DataLen            =     0;
//	U16            overrunFlag;
	int     m_YanShiMillSecond;//��ʱ
	//��������ѹ
	CString                str;
	BOOL m_changed     = FALSE;
	BYTE     k1  =  0,k2 =   1;

	WaitForSingleObject(TmpOnlyOneThreadRun.m_hObject,INFINITE);
	
	if(!m_StartRead)
	{
		return -1;
	}
	
	//��ʾ�汾
	if(AppInfo::Instance().m_YanShi)
	{
		
		for(int jj = 0 ; jj < 7; jj ++)
		{
			SurrenderWindowMessage();
			
			if(m_StartRead)
			{
				Sleep(1000);
			}
			else
			{
				break;
			}
			
		}
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		CTime time  = CTime::GetCurrentTime();
		
		if(Item == 0xf6 || Item==0xf8)
		{
			m_RetuenValue = 333333.33;
		}
		else if(Item == 0x38 || Item==0xB8)
		{
			m_RetuenValue = 0.98;
		}
		else
		{
			//����ֵModuleNum
			m_RetuenValue = time.GetYear() + time.GetMonth() + time.GetDay() + time.GetHour() + time.GetMinute()*0.1 + time.GetSecond()*0.01 +  ModuleNum*0.001;
		}
		
	}
	else
	{
		unsigned short *ai_buf=NULL;
	    
		//��ʼ�ɼ�����
		memset(DataBuf,0,800000);
        memset(ReadBuff,0,1024);
		
		//����������
		if(m_QuickReading)
		{  	
			
			//��61��62Э��485����ٶ���Ĺ�������
			if(((Protocol/10) == 6) && (Item==0x07 || Item==0x06) && ((ModuleNum%100) > 12))
			{
				
				if(ModuleNum/100 < 20000)
				{

					//���ԭ�������˱��ֵ��
					if(m_QuickGlys[ModuleNum/100 - 1] >= 0)
					{

						return m_QuickGlys[ModuleNum/100 - 1];

					}
					
				}
				
			}
			
        	//71,72,73Э�������,һ������3��ģ������ݣ�32λ��ÿ��ģ��10λ�����999��ÿ������3��,61,62��485,�������غ��й����ʴ����һ��
			if((((ModuleNum%100) <= 8) && (Item==0x02 || Item==0x82) && ((Protocol/10) == 7)) || ((Protocol/10) == 6 && ((ModuleNum%100) > 12) && (Item==0x1F || Item==0x1E)))
			{
				
				CTime     timet    = CTime::GetCurrentTime();
				str.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
				
				//��ģ���Ƿ��ܿ��ٶ���
				if(TestIfCanQuickReadAmmeter(ModuleNum,str,m_AmmeterType,Protocol)) 
				{	   
					
					//�Ա�����ģ��,71,72,73Э��
					if((m_QuickModuleAddress/100 == ModuleNum/100) && ((Protocol/10) == 7))
					{
						
						//���ٶ���ģ���ӱ�ķ�Χ
						if((m_QuickModuleAddress%100) >= 1 &&  (m_QuickModuleAddress%100) <= 3)
						{
							k1 = 1;
						}
						else if((m_QuickModuleAddress%100) >= 4 &&  (m_QuickModuleAddress%100) <= 6)
						{
							k1 = 2;
						}
						else if((m_QuickModuleAddress%100) >= 7 &&  (m_QuickModuleAddress%100) <= 8)
						{
							k1 = 3;
						} 
						
						//��ʱ����ģ���ӱ�ķ�Χ
						if((ModuleNum%100) >= 1 &&  (ModuleNum%100) <= 3)
						{
							k2 = 1;
						}
						else if((ModuleNum%100) >= 4 &&  (ModuleNum%100) <= 6)
						{
							k2 = 2;
						}
						else if((ModuleNum%100) >= 7 &&  (ModuleNum%100) <= 8)
						{
							k2 = 3;
						}
						
						//������һ����
						if(k1 == k2) 
						{
							//AfxMessageBox("1");
							//m_QuickReadParameter[0] �����й���ȶ���ֵ
							//m_QuickReadParameter[1] �й���ȵ�ֵ
							//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ								   
							
							//���������������ֵ,ǰ10λ��һ�ӱ�ģ���ֵ���м�10λ�ڶ��ӱ�ģ���ֵ������10λΪ�����ӱ�ģ���ֵ
							if(m_QuickReadModuleValue >= 0)
							{
								
								switch((ModuleNum%10)%3)
								{
								case 1:
									{	  
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
										break;
									}
								case 2:
									{
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024 + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;
										break;
									}
								case 0:
									{	
										m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024) + (long(((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)*100)%100)/100.00;	
										break;
									}
								}
								
								//���������+���
								m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
								
							//	str.Format("ģ���:%d,ԭ����ֵ:%f,���:%f,����:%f,\r\n�������ֵ:%f,�ӱ��:%f,��һ�ӱ�:%d,�ڶ��ӱ�:%d,�����ӱ�:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
				            //  WriteToLog(str);
																						
								//����������ڻ���ں���Ļ�
								if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
								{
							//		WriteToLog("�ӱ�״��ڵ���ԭ����");
									return  m_RetuenValue;
								}
								
							//	WriteToLog("�ӱ��С��ԭ����");
								
								
							}
							else
							{
								
								if(long(m_QuickReadModuleValue) < -1)
								{
									//û��פ��������
									return long(m_QuickReadModuleValue);
								}
								
							}									 
							
						}

					}
					else
					{
						  
						   m_changed              =  TRUE;
						   
						   if((Protocol/10) == 7)
						   {
							   m_QuickModuleAddress   =     0;//���ٶ���ĵ�ַ
						       m_QuickReadModuleValue =    -1;
							  
							   if((ModuleNum%100 <= 3))
							   {
								   
								   //��ǰ3��ģ��,�ӱ��ַΪ01,02,03
								   if(Item == 0x02)
								   {
									   Item = 0x0E;
								   }
								   else
								   {
									   Item = 0x8E;
								   }
								   
							   }
							   else if((ModuleNum%100 >= 4) && (ModuleNum%100 <= 6))
							   {
								   
								   //�м�3��ģ��,�ӱ��ַΪ04,05,06
								   if(Item == 0x02)
								   {
									   Item = 0x10;
								   }
								   else
								   {
									   Item = 0x90;
								   }					   
								   
							   }
							   else 
							   {
								   //���2��ģ��,�ӱ��ַΪ07,08
								   if(Item == 0x02)
								   {
									   Item = 0x12;
								   }
								   else
								   {
									   Item = 0x82;
								   }					   
								   
							   }
							   
							//   str.Format("Э�飺%d�����ٶ���ģ��ţ�%d��ָ��:%0x\r\n",Protocol,ModuleNum,Item);
							//   WriteToLog(str);
							   
						   }
						   else
						   {
							   //61,62Э��
							   if(Item == 0x1F)
							   {
								   Item = 0x01;
							   }
							   else
							   {
								   Item = 0x00;
							   } 
							   
							//   str.Format("Э�飺%d�����ٶ���ģ��ţ�%d��ָ��:%0x\r\n",Protocol,ModuleNum,Item);
							//   WriteToLog(str);
							   
						   }
						   
					}
					   
				}
			    else
				{
				   m_QuickReadModuleValue     =              -1;
				   m_QuickModuleAddress       =       ModuleNum;//���ٶ���ĵ�ַ
				}
			   
		   }		
			   
		}
		
		//��Ƭ����ָ��
		if(!SendOrderToSCM(ModuleNum/*ģ���*/,StationNo/*�����ֵ�վ��*/,MotherLine/*ĸ��*/,LineNo/*�ߺ�*/, Phase/*��ѡ��0A 1B 2C*/,3, Item/* Ҫʲô����,������*/,0,Protocol,m_SendAngle))
		{
		//	Beep(300,400);
		//	Beep(300,400);
		}
	
		//�Բ�ģʽ
		err = AI_9111_Config(card,TRIG_INT_PACER, 0, 1024);
		
		if(err != 0)
		{
			return -1;
		}
		
		//˫����ģʽ
		err = AI_AsyncDblBufferMode(card, 1); 	
		
		if(err != 0)
		{
			return -1;
		}
		
		//��Э�����ʱ����
		switch(Protocol)
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

//		str.Format("����Э��:%d,��ʱ:%d����",Protocol,m_YanShiMillSecond);
//		WriteToLog(str);

		//������ʱ 1230���� ��485��ʱ610����
		//��ʱ����
		m_YanShiMillSecond = m_YanShiMillSecond + 610;


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

			if(!m_StartRead)
			{
				return -1;
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
			return -1;
		}
		
		do
		{
			do
			{
				//����
				AI_AsyncDblBufferHalfReady(card, &bHalfReady, &bStopped);				
					
				CTimeSpan ts    = CTime::GetCurrentTime() - time0;
				
				if(Protocol != 22)
				{

					//�������22Э��AI_ContStatus
					if(ts.GetTotalSeconds() > (Protocol%10)*11 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				else
				{	
					//�����22Э��
					if(ts.GetTotalSeconds() > 10 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						
					}
					
				}
				
			} while (!bHalfReady && !bClearOp);
			
			if(!m_StartRead)
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

				if(!m_StartRead)
				{
					bClearOp = TRUE;
				}
				
				CTimeSpan ts    = CTime::GetCurrentTime() - time0;
				
				//ʱ�����
				switch(Protocol)
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
				
				if(Protocol != 22)
				{
					
					//�������22Э��
					if(ts.GetTotalSeconds() > (Protocol%10)*11 || !m_StartRead)
					{
						
						bClearOp = TRUE;
						break;
					
					}
					
				}
				else
				{	
					
					//�����22Э��
					if(ts.GetTotalSeconds() > 10 || !m_StartRead)
					{
						bClearOp = TRUE;
						break;
					}
					
				}
				
			}
			
		
        }while (!bClearOp && !bStopped && m_StartRead);
	
		AI_AsyncClear(card, &count);
		
		if(!m_StartRead)
		{
			return -1;
		}
		
		//����ֵ
		m_RetuenValue = DecodeSixChannel(ModuleNum,Protocol,Item,Phase);//����

	}
	
	//���ٶ���
	if(m_QuickReading && m_changed)
	{	

		//������ݴ���0
		if(m_RetuenValue >= 0)
		{	
			
			//71,72,73Э��
			if((Protocol/10) == 7)
			{	
				//71,72,73�����
				m_QuickReadModuleValue =  long(m_RetuenValue);//����ģ������ݴ���һ��
				m_QuickModuleAddress   =            ModuleNum;//���ٶ���ĵ�ַ
				
				//m_QuickReadParameter[0] �����й���ȶ���ֵ
				//m_QuickReadParameter[1] �й���ȵ�ֵ
				//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ

				switch((ModuleNum%10)%3)
				{
				case 1:
					{	  
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + m_QuickReadModuleValue/1024/1024;
						break;
					}
				case 2:
					{
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%(1024*1024))/1024;
						break;
					}
				case 0:
					{	
						m_RetuenValue = long((m_QuickReadParameter[0] - m_QuickReadParameter[1])*m_QuickReadParameter[2] + 0.001)/1000*1000 + (m_QuickReadModuleValue%1024);	
						break;
					}
				}
				
				//���������,�ó��µ�����ֵ
				m_RetuenValue	=	m_RetuenValue/m_QuickReadParameter[2];
				
			//	str.Format("ģ���:%d,ԭ����ֵ:%f,���:%f,����:%f,\r\n�������ֵ:%f,�ӱ��:%f,��һ�ӱ�:%d,�ڶ��ӱ�:%d,�����ӱ�:%d\r\n",ModuleNum,m_QuickReadParameter[0],m_QuickReadParameter[1],m_QuickReadParameter[2],m_RetuenValue,m_RetuenValue + m_QuickReadParameter[1],m_QuickReadModuleValue/1024/1024,(m_QuickReadModuleValue%(1024*1024))/1024,(m_QuickReadModuleValue%1024));
			//	WriteToLog(str);

				//�����������
				if((m_RetuenValue  + m_QuickReadParameter[1]) >= m_QuickReadParameter[0])
				{
			//		WriteToLog("�ӱ�״��ڵ���ԭ����");
					return  m_RetuenValue;
				}
				
			//	WriteToLog("�ӱ��С��ԭ����");
		  	    
				m_RetuenValue          = - 1;
				m_QuickReadModuleValue = - 1;
				
			}
			else
			{
				//61,62,63Э��485�Ĳ��п��ٶ���,�����Ķ��������ֵ,ǰ7λΪ�������أ�����14λΪ�й����,61,62
				long  m_TmepQuickReadModuleValue =  long(m_RetuenValue*10);
				m_tempvalue                      =  (m_TmepQuickReadModuleValue%(int(pow((double)2,14)))) * 0.1;
				float m_TempGlys                 =  (m_TmepQuickReadModuleValue/(int(pow((double)2,14)))) * 0.01;
				
				if(m_tempvalue <= 999.8  &&  m_TempGlys <= 1)
				{
					
					//m_QuickReadParameter[0] �����й���ȶ���ֵ
					//m_QuickReadParameter[1] �й���ȵ�ֵ
					//m_QuickReadParameter[2] 3200�ı���,ֱ�����ֵ

					m_RetuenValue = long(m_QuickReadParameter[0] + 0.001)/1000*1000 + m_tempvalue;
					
					//����������ڻ���ں���Ļ�
					if(m_RetuenValue  >= m_QuickReadParameter[0])
					{
						//��61��62Э��485����ٶ���Ĺ������� 
						if(ModuleNum/100 < 20000)
						{
							m_QuickGlys[ModuleNum/100 - 1] = m_TempGlys;
						}
						
						return  m_RetuenValue;
					}
					
				}
				
				m_RetuenValue          = - 1;
			}
			
		}
		else
		{
			//�����˱�ģ�鲻֧�ִ�ָ����
			m_QuickReadModuleValue     =   m_RetuenValue;
			m_QuickModuleAddress       =       ModuleNum;//���ٶ���ĵ�ַ
		}
		
		
	}
	else
	{

		//1-12Ϊ�����
		if(ModuleNum%100 <= 12 && m_RetuenValue > 0  && !m_AmmeterType.IsEmpty())
		{
			//Ĭ��������Ϊ3200��������ֵ
			m_RetuenValue = m_RetuenValue* 3200.00/GetAmmeterImpulse(m_AmmeterType);
		}

	}
	
	//�Ļ��ⴥ��״̬
	AI_9111_Config(card,TRIG_EXT_STROBE,0,0);

    TmpOnlyOneThreadRun.SetEvent();

	return m_RetuenValue;
}


//�ǽǱ�ȫ����ͨ������,��6�Σ�������������Э��
double CIFRMView::DecodeSixChannel(long ModuleNum,BYTE Protocol,BYTE Item,BYTE m_phase)
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
	int i;
	for( i = 0; i < 6000;i ++)
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

	//������
	/*
	CFile   file;
	
	if(file.Open("c:\\tdata.txt",CFile::modeWrite | CFile::modeCreate))
	{			
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
	}
	*/
	//������

	//���������ѹ����,����������ƥ��ֵ���Ľ��
	for(int m_PhaseTest = 0; m_PhaseTest < 3; m_PhaseTest ++)
	{
		int i;
		//��ʼ����0������
		for( i = 0; i < 1500; i ++)
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
				
				/*
				if(m_PhaseTest == 2)
				{
					str.Format("m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,���:%d",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
					WriteToLog(str);
				}
				*/
				
				/*
				if(abs(m_ZeroPalce[i] - m_ZeroPalce[i - 1] - 167) > 10)
				{	
				
					str.Format("����ѹ�����������:m_ZeroPalce[%d]=%d,m_ZeroPalce[%d]=%d,���:%d��",i-1,m_ZeroPalce[i -1],i,m_ZeroPalce[i],m_ZeroPalce[i]-m_ZeroPalce[i-1]);
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
		
		/**/
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
			
		}
	
	
				
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

	//	signstr.Format("λ�ã�%d,ֵ��%.2f",jj + 1,m_ppvalue);
	//	WriteToLog(signstr);
	}


//  signstr.Format("ģ��ţ�%d,���%d,��%d����,�Ƕȣ�%d��,ƥ��λ�ã�%d,ƥ���ֵ��%.2f����ֵ��%.2f",ModuleNum,m_pipeiplace/(3*m_maxpptimes),(m_pipeiplace%m_maxpptimes) + 1,5*int(pow((double)2,((m_pipeiplace%(3*m_maxpptimes))/m_maxpptimes))),m_pipeiplace,m_maxppvalue,float(m_maxppvalue/m_ByteRecords));
//  WriteToLog(signstr);
//	AfxMessageBox(signstr);


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

		/*
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
					
						m_addValue = m_addValue + SignalBit[m_ttts*8 + jjj]*BYTE(pow((double)2,m_ttts-1-jjj));
					
					}
				
				}

				signstr.Format(" 0x%0x  ",m_addValue);
				
			}
			
			
			WriteToLog("\r\nʮ������Ϊ:"+ signstr + "\r\n");
		
				
		}
		*/
		
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
					dataValue = dataValue + double(TempSignalBit[10 + i]*pow((double)2,i));
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
		 if(DecodeBCH63394(TempSignalBit,FALSE))//����ԵĻ�
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
			 
			 //16���ƽ���
			 dataValue   =     0.00;
			 m_sums      =        0;
			 
			 //7λһ�����
			 for(int kkkkk = 0; kkkkk < 3; kkkkk ++)
			 {
				 
				 //����λ����ֽ�,7λһ����� 
				 for( i = 0;i < 7; i ++)
				 {  	
					 
					 m_sums  = m_sums  + SignalBit[18 + kkkkk*7 + i] * BYTE(pow((double)2,6-i));
					 
				 }
				 
			 }
			 
			 //�������ͶԵĻ�
			 if((m_sums%64) == (SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 ))
			 {
				 
				 //���ֵ
				 for( i = 0; i < 21; i++)
				 {
					 dataValue = dataValue + double(SignalBit[18 + i]*pow((double)2,20-i));
				 }	
				 
				 if(SignalBit[38] == 1)
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
							 
						//	 CString ssss;
						//	 ssss.Format("����ֵ = %f",dataValue/10);
						//	 WriteToLog(ssss);

							 //����10
							 return dataValue/10;
						 }
						 
						 
					 }
					 
					 
				 }
				 
				 
			 }
			 
			 //����Ͳ���
			 dataValue =  -1;
			 
			 //str.Format("ǰУ���(0x)%0x,��У���(0x)%0x,У��Ͳ��ԣ�",m_sums%64,SignalBit[39]*32 + SignalBit[40]*16 + SignalBit[41]*8 + SignalBit[42]*4 + SignalBit[43]*2 + SignalBit[44]*1 );
			 //WriteToLog(str);
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
		 if(DecodeBCH63394(TempSignalBit,TRUE))
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
				 dataValue = dataValue + Signal[i] * 100000.00/pow((double)10,i);
				 
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
				 //ֻ��485����е�����,485���ͨѶ����
				 return  -2;			
			 }
			 else if(Signal[0] == 0x0a && Signal[1] == 0x0a && Signal[2] == 0x0a && Signal[3] == 0x0a && Signal[4] == 0x0a && Signal[5] == 0x0a && Signal[6] == 0x0a && Signal[7] == 0x0a && (ModuleNum%100 >= 12))
			 {
				 //ֻ��485����е�����,������2
				 return  -3;
			 }
			 else if(Signal[0] == 0x0f && Signal[1] == 0x0f && Signal[2] == 0x0f && Signal[3] == 0x0f && Signal[4] == 0x0f && Signal[5] == 0x0f && Signal[6] == 0x0f && Signal[7] == 0x0f)
			 {
				 //��פ��ʱģ��û���յ���פ������ص���
				 return  -4;
			 }	
			 else if(m_sums%128 == Data[32]*64 + Data[33]*32 + Data[34]*16 + Data[35]*8 + Data[36]*4 + Data[37]*2 + Data[38])
			 {   
				 
				 //�����
				 if(Signal[0] <= 9 && Signal[1] <= 9 && Signal[2] <= 9 && Signal[3] <= 9 && Signal[4] <= 9 && Signal[5] <= 9 && Signal[6] <= 9 && Signal[7] <= 9)
				 {
					
				//	 WriteToLog("[����Ͷ�]");

					 //485��Ϊ0������
					 if((ModuleNum%100 >= 12) && (Item==0x02 || Item==0x82) && int(dataValue*100) == 0)
					 {	
						
					//	 CString                         ssss;
					//	 ssss.Format("����ֵ = %f",dataValue);
					//	 WriteToLog(ssss);

						 return  -2;
					 }					 
					 
					 return  dataValue;
					 
				 }
				 
			//	 WriteToLog("[����Ͳ���]");
				 
				 return   -1;
				 
			 }
			 
			 return   -1;
			 
		 }
		 
	 }
	 
	 return dataValue;
}


//�ɼ���ͨ������Լ���
double CIFRMView::CorrelationSixChannelCheck(long SourceArray[], long DestArray[],int K)
{
    double           A,B,C,Pxy,sums;
	int                           i;
   	A = B = C = Pxy = sums =  0.000;
	
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


//�ҹ�0���λ��,��10����,��һ��Ϊ���Ļ�,��5����,��5����,k����
int CIFRMView::FindZeroPoint(short m_CollectData[],int m_StartPlace,int k)
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

	return  m_dots;
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

void CIFRMView::OnWugongparameter() 
{
	CWuGongDlg  dlg;
	dlg.DoModal();	
}


//�����޹�������������
void CIFRMView::WuGongDeal(CString ConStr)
{
	BYTE    LineNo           =        0;//��  ��
	BYTE    PhaseNo          =        0;//��  ��
	BYTE    StationNo        =        0;//�����ֱ��վ����
	BYTE    MotherLine       =        0;//ĸ�߱��
	long    ModuleNo         =        0;//ģ���
	long    Records          =        0;//�Ǳ�����
	double  CurrentValue     =        0;//��ʼ��ģ������
	long    GetModuleNo      =        0;//�м����
	long    fields           =        0;//��¼��
	BYTE    m_AMMETERKIND    =        0;//�������
	BYTE    m_SUPPLYMODED    =        0;//���緽ʽ 0-���߹��� 1��վ������ 2-�������ֹ���
	BYTE    m_PROTOCOL       =        0;//����Э�� 71-73 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
    BYTE    m_SendAngle      =        0;//���͵ĽǶ� 2005-04-07�� 
	float   m_BeginValue     =        0;//����ֵ 
	BYTE    BakMotherLine    =        0;//����ĸ�߱��
	BYTE    BakLineNo        =        0;//������  ��
	CString           m_ReadAmmeterType;//�������� 	
	m_StartRead              =     TRUE;//��ͣ��־  
	BYTE                         orders;//�޹�����ָ��
	CString             strSql,str,strValue;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	m_ListRows               =        0; 
	CString                 CondtionStr;
	int                   READTIMES = 3;
	float                    m_Q,m_WGGL;//m_Q �������أ��޹�����
	int                     m_QSUMS = 0;//����������
	double         m_UpValue,m_DownValue;
    m_UpValue                =      0.8;
    m_DownValue              =      0.3;
	short           m_dokind =        0;//0 ���� 1 Ͷ  2��
    double   	    m_Bvalue =        0;//(�޹�����*����)/����������; 
	double          m_Multiple =      0;//����
	short           m_RunStatus  =    0;//����״̬ 

	StatusStrRead = StatusStr;
    CString                  WGFileName;
	//������Χ
	ConStr.TrimLeft();
	ConStr.TrimRight();
	
	//ɾ��ԭ������
	//m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13��
	
	StatusStr.Format("���ڽ����޹���������������Ժ�...");
    SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(TRUE);
	
	//���DIALOGBAR�ɼ��Ļ�������
	SendMessage(WM_EVENT, 6, 0);
	
	//��������ȫ������
	if(ConStr == "ALL")
	{
		CondtionStr = " USER_AMMETERKIND=5";
	}
	else
	{
		CondtionStr = "(" + ConStr + ") AND USER_AMMETERKIND=5";
	}
	
   	//�����ݿ�
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);
		int i;
		//д�б����
//		SendMessage(WM_EVENT, 2, 0);

		strSql      = "SELECT COUNT(*)  FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		fields   =  atoi(strValue);
		rs.Close();

		//���û�м�¼�Ļ�
		if(fields < 1)
		{
            db.Close();
			//״̬����Ϣ
			StatusStr = "���޹���������������";
            SendMessage(WM_EVENT, 1, 0);
            //���ع�����
//			ShowProgressCtrl(FALSE);
//			m_StartRead   =   FALSE;
			return;
		}
		
		CTime timet = CTime::GetCurrentTime();
		WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
		str.Format("��%4d-%02d-%02d %02d:%02d:%02d���޹��������\r\n",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
		FILE *text;
		if((text = fopen(WGFileName,"a")) != NULL)
		{	
			fputs(str,text);		
			fclose(text);
		}
		
		strSql      = "SELECT WGUPDOWN_UP,WGUPDOWN_DOWN FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);
			m_UpValue       =     atof(strValue)/100.00;
			rs.GetFieldValue((short)1,strValue);
			m_DownValue     =     atof(strValue)/100.00;
		}	
		
		rs.Close();

		strSql      = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO,USER_MULTIPLE,USER_RUNSTATUS,b.WUGONG_SPACE FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);

		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();
		rs.Close();	
		
		//��������Χ
		SetProgressCtrlRange(0, fields,1);
		//�����ݿ�����
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j ++)
		{
			
			//��ԭʼֵ
			CurrentValue = -1;
			
			//�������ֹͣ��ť
			if(!m_StartRead)
			{	
				
				if(rs.IsOpen())
				{
					rs.Close();
				}
				
				if(db.IsOpen())
				{
					db.Close();
				}
				
				//��ʾ״̬����Ϣ
				StatusStr = "��������;��ֹͣ��";
				SendMessage(WM_EVENT, 1, 0);
				
				//���ع�����
				ShowProgressCtrl(FALSE);
				return;
			}
			
			//���
			strValue.Format("%d",m_ListRows + 1);
			m_StrArray[0].Format("%5s",strValue);
			
			//��ʾָ��
			m_StrArray[1] =  "�޹�����";
			
			//�����ֶε����ƿ�ʼ
			for( i = 0; i < nFields; i++)
			{
				rs.GetFieldValue(int(i),strValue);

				strValue.TrimLeft();
				strValue.TrimRight();

				switch(i)
				{
				case 0:
					{
						//����
						m_StrArray[2] = strValue;
						break;
					}
				case 1:
					{ 
						//�û����  
						m_StrArray[3] = strValue;
						break;
					}
				case 2:
					{ 
						//סַ  
						m_StrArray[4] = strValue;
						break;
					}
				case 3:
					{  
						//ģ���
						m_StrArray[5].Format("%8s",strValue);
						ModuleNo = atol(strValue);
						break;
					}
				case 4:
					{  
						//����
						m_StrArray[6].Format("%8s",strValue);
						break;
					}
				case 5:
					{  
						//ĸ�ߺ�
						MotherLine = atoi(strValue); //add by 2004.10.21
						break;
					}
				case 6:
					{	
						//��·����
						m_StrArray[7] = strValue;
						break;
					}
				case 7:
					{
						//��·���
						LineNo = atoi(strValue);
						break;
					}
				case 8:
					{
						CString         PhaseStr;
						//��
						switch(atoi(strValue))
						{
						case 0:
							{
								PhaseStr = "A��";
								PhaseNo = 0;
								break;
							}
						case 1:
							{
								PhaseStr = "B��";
								PhaseNo = 1;
								break;
							}
						case 2:
							{
								PhaseStr = "C��";
								PhaseNo = 2;
								break;
							}
						default:
							{
								PhaseStr = "δ֪";
								PhaseNo = atoi(strValue);
								break;
							}
						}

						m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
						break;
					}
				case 9:
					{
						//��̨����
						m_StrArray[9].Format("%s",strValue);
						break;
					}
				case 10:
					{
						//�����ֵ�վ��
						StationNo    = m_handno;
						//����ֵ
						m_BeginValue = float(atof(strValue));
						break;
					}
				case 11:
					{
						//�������
						m_AMMETERKIND = atoi(strValue);
						break;
					}
				case 12:
					{
						//���緽ʽ
						m_SUPPLYMODED = atoi(strValue);
						break;
					}	
				case 13:
					{
						//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
						m_PROTOCOL    = atoi(strValue);
						orders        =           0x48;
						
						switch(m_PROTOCOL)
						{
						case 61:
							{
								
							}
						case 62:
							{
								orders = 0x03;
								break;
							}
						case 71:
							{
								
							}
						case 72:
							{
								
							}
						case 73:
							{
								orders = 0x48;
								break;
							}
						}
						
						m_StrArray[8] = m_StrArray[8] + strValue + "]";
						break;
					}	
				case 14:
					{
						//����ĽǶ�,�Ƿ����ǽ�����,ƫ�ƽǶ�,�ǽ�Ϊ30��
						if(IsDyConnect(m_StrArray[9]))
						{
							m_SendAngle = 6;
						}
						else
						{
							m_SendAngle = 0;
						}
						
						break;
					}
				case 15:
					{
						//���������
						m_ReadAmmeterType = strValue;
						break;
					}	
				case 16:
					{
						//����ĸ�߱��
						BakMotherLine = atoi(strValue);
						break;
					}	
				case 17:
					{
						//���ó��ߺ�
						BakLineNo     = atoi(strValue);
						break;
					}
				case 18:
					{
						//����
						m_Multiple     = atof(strValue);
						break;
					}	
				case 19:
					{
						//Ͷ��״̬
						m_RunStatus    = atoi(strValue);
						break;
					}
				case 20:
					{
						//����������
						m_QSUMS       = atoi(strValue);
						break;
					}
					
				 }
				 
              }			 
			  //�����ֶε����ƽ���
			
			  CurrentValue =   -1;

			  //����READTIMES��
			  for(int m_readtimes = 0; m_readtimes < READTIMES; m_readtimes ++)
			  {

				  if(int(CurrentValue) != -1)
				  {
					  break;
				  }

				  //��ʾ״̬����Ϣ
				  StatusStr.Format("���ڵ�[%d]�β����޹�����[%d(%d-%d)]���%.2f��,�Ժ�...",m_readtimes + 1,ModuleNo,fields,m_ListRows + 1,float(m_ListRows)*100/fields);
				  SendMessage(WM_EVENT, 1, 0);	


				  //��֪��������Ļ�,ÿ���඼����һ��
				  if(PhaseNo > 2)
				  {				  
					  SurrenderWindowMessage();

					  //��ѭ��
					  for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
					  { 
						  
						  if(int(CurrentValue) != -1)
						  {
							  break;
						  }

						  SurrenderWindowMessage();

						  //�������ֹͣ��ť
						  if(m_StartRead == FALSE)
						  {
							  break;
						  }
						  
						  switch(PhaseNo)
						  {
						  case 0:
							  {	
								  strValue.Format("����%s,����ģ���(%d)A��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 1:
							  {
								  strValue.Format("����%s,����ģ���(%d)B��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 2:
							  {
								  strValue.Format("����%s,����ģ���(%d)C��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  }
						  
						  //��ʾ״̬����Ϣ
						  StatusStr =        strValue;
						  SendMessage(WM_EVENT, 1, 0);
						  
						  if(m_SendAngle == 0)
						  {
							  CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  else
						  {
							  //�ǽǱ����,�·��������,�·��������,��һ��ʵʱ����
							  CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  
						  //��������Ƿ����
						  if(CurrentValue >= 0)
						  {
							  
							  if((m_PROTOCOL/10) == 6)
							  {
								  //61,62��Э��
								  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
								  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
									  
							  }
							  else  if((m_PROTOCOL/10) == 7)
							  {
								  
								  //71,72��Э��
								  m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //��������
								  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //�޹�����
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
								  
							  }
							  
						  }
						  
						  SurrenderWindowMessage();
						  
						  //������������֣��ٶ�һ������
						  if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
						  {
							  
							  if(m_SendAngle == 0)
							  {
								  CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
							  else
							  {
								  //�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
								  CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
													  
							  //��������Ƿ����
							  if(CurrentValue >= 0)
							  {
								  
								  if((m_PROTOCOL/10) == 6)
								  {
									  //61,62��Э��
									  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
									  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }
										  
								  }
								  else  if((m_PROTOCOL/10) == 7)
								  {
									  
									  //71,72��Э��
									  m_Q     =   (int(CurrentValue*100)/10000)*0.001;   //��������
									  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;   //�޹�����
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }

								  }
								  
							  }

						  }
							  
						  SurrenderWindowMessage();
						  
						  //���������ֵ���ڻ����0	
						  if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
						  {
							  
							  //��
							  switch(PhaseNo)
							  {
							  case 0:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A��",m_PROTOCOL);
									  break;
								  }
							  case 1:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B��",m_PROTOCOL);
									  break;
								  }
							  case 2:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C��",m_PROTOCOL);
									  break;
								  }
							  }
							  
							  //���������ݿ�
							  strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO= %d",PhaseNo,ModuleNo);
							  //����SQL���
							  CDataBaseInstance::ExecuteDataBaseSQL(strValue); 
							  break;
							  
						  }
							  

                     }
			 					  
					  
				}
				else
				{
					//֪������Ͷ�����
					CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*ĸ��*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						
					//��������Ƿ����
					if(CurrentValue >= 0)
					{
						
						if((m_PROTOCOL/10) == 6)
						{
							//61,62��Э��
							m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
							m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						else  if((m_PROTOCOL/10) == 7)
						{
							
							//71,72��Э��
							m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //��������
							m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //�޹�����
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						
					}
					
					SurrenderWindowMessage();
									
					//������������֣��ٶ�һ������
					if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
					{
						
						if(m_SendAngle == 0)
						{
							CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						else
						{
							//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
							CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						
						//��������Ƿ����
						if(CurrentValue >= 0)
						{
							
							if((m_PROTOCOL/10) == 6)
							{
								//61,62��Э��
								m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
								m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{	
									MotherLine  =  BakMotherLine;//����ĸ�߱��
	                                LineNo      =   BakLineNo;   //�����ߺ�
									break;
								}
								
							}
							else  if((m_PROTOCOL/10) == 7)
							{
								
								//71,72��Э��
								m_Q     =   (int(CurrentValue*100)/10000)*0.001;         //��������
								m_WGGL  =   (int(CurrentValue*100)%10000)*0.01;          //�޹�����
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{
									MotherLine  =  BakMotherLine;//����ĸ�߱��
	                                LineNo      =   BakLineNo;   //�����ߺ�
									break;
								}
								
							}
							
						}
						
						SurrenderWindowMessage();

						//����ڱ���ĸ�ߺͱ��ó����϶�����
						if(int(CurrentValue) != -1)
						{
							switch(PhaseNo)
							{
							case 0:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A��",m_PROTOCOL);
									break;
								}
							case 1:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B��",m_PROTOCOL);
									break;
								}
							case 2:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C��",m_PROTOCOL);
									break;
								}
							}
							
						}
						
					}
					
				}
			
            }
				
			//���ݵõ���ֵ�½���
			if(int(CurrentValue) == -1)
			{	
				//�û����»�һ����¼
				rs.MoveNext();
				//��������ִ��
				continue;
			}
				
			Beep(5000,400); 
			
			//���ݵõ���ֵ�½���
			if(CurrentValue >= 0 )
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("�ɹ�");
				strValue.Format("Q(%.2f),QG(%.2f)",m_Q,m_WGGL);
				m_StrArray[11]  =  strValue;
			}
			else
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("δ�ɹ�");
				
				//�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û������
				if(int(CurrentValue) == -2)
				{	
					//��ȷ�Ļ�
					m_StrArray[11] = "����1 ";
				}

				if(int(CurrentValue) == -3)
				{
					//��ȷ�Ļ�
					m_StrArray[11] = "����2 ";
				}					
				
			}
			
			//ʱ��
			CTime timet = CTime::GetCurrentTime();	
			m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			
			//��ʾ����б�
			for( i = 0; i < 13; i++)
			{		
				m_StrArray[i].TrimLeft();
				m_StrArray[i].TrimRight();
				
				//���ݸ�ʽ����
				if(i == 0)
				{
					//���
					if(m_StrArray[i].GetLength() < 5)
					{
						
						strValue = m_StrArray[i];
						m_StrArray[i].Format("%5s",strValue);

					}
					
				}
				else if( i == 5)
				{   
					//ģ��� 
					if(m_StrArray[i].GetLength() < 8)
					{

						strValue = m_StrArray[i];
						m_StrArray[i].Format("%8s",strValue);

					}
					
				}
				else if( i == 11)
				{   
					//������ֵ
					if(m_StrArray[i].GetLength() < 12)
					{

						strValue = m_StrArray[i];
						m_StrArray[i].Format("%12s",strValue);

					}
					
				}
				
				DataStr = DataStr + ";" + m_StrArray[i];
			}
			
			//��ʾ�б�����
			SendMessage(WM_EVENT, 3, 0);

			SurrenderWindowMessage();			
		
			//���ֵΪ��
			if(CurrentValue >= 0 && m_StartRead)
			{
				//m_dokind   0 ���� 1 Ͷ  2 ��
				//61,62 �͵� 0x04  ͣ��  0x05
                //71,72 �͵� 0xf6  ͣ��  0xf8
                m_dokind =   0;
				
                if(m_QSUMS > 0)
				{
					
					m_Bvalue  = (m_WGGL*m_Multiple)/m_QSUMS;//(m_WGGL*����)/m_QSUMS; 
					
					//�������� 1 Ͷ
					if(m_Bvalue >= m_UpValue)
					{
                        m_dokind =   1;
					}
					
					//С������ 2 ��
					if(m_Bvalue <= m_DownValue)
					{
                        m_dokind =   2;
					}
					
                }

				//Ҫ�Ͳ����͵�״̬,Ҫͣ����ͣ��״̬	 m_RunStatus  0 ����  1  ͣ��
				if(((m_dokind == 1  && m_RunStatus != 0)  || (m_dokind == 2 && m_RunStatus != 1)) && (m_dokind > 0))
				{
					
					//�����Ƿ�Ͷ��,	Ͷ3��
					for(int yyy = 0; yyy < READTIMES; yyy ++)
					{
						
						SurrenderWindowMessage();
						
						if(m_dokind == 1)
						{
							//��ʾ״̬����Ϣ
							StatusStr.Format("���ڵ�[%d]�ζ��޹�����ģ��[%d]Ͷ�������,�Ժ�...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);	
							
							if(m_PROTOCOL/10 == 6  && m_StartRead)
							{
								//�͵����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x04,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//�͵����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf6,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						else
						{
							//��ʾ״̬����Ϣ
							StatusStr.Format("���ڵ�[%d]�ζ��޹�����ģ��[%d]�в������,�Ժ�...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);
							
							if(m_PROTOCOL/10 == 6  &&  m_StartRead)
							{
								//ͣ�����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x05,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//ͣ�����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf8,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						
						//������سɹ�
						if(int(CurrentValue) > 0)
						{
						
						 	CTime timet = CTime::GetCurrentTime();

							//�޸��͵硢ͣ��״̬
							if(m_dokind == 1)
							{
								m_StrArray[1]  =  "�޹�Ͷ����";	
								m_StrArray[10] =  "Ͷ�ɹ�";
								//�͵�,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_DESCRIBE = '%s' WHERE USER_MODULENO= %d","�޹������͵�",ModuleNo);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("��%4d-%02d-%02d %02d:%02d:%02d��ģ�飺%d    ����:�޹������͵�\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
															
							}
							else
							{
								m_StrArray[1]  =  "�޹��в���";
								m_StrArray[10] =  "�гɹ�";
								//ͣ��,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_DESCRIBE = '%s' WHERE USER_MODULENO=%d","�޹�����ͣ��",ModuleNo);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("��%4d-%02d-%02d %02d:%02d:%02d��ģ�飺%d    ����:�޹�����ͣ��\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}	
							
							
							WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
						
							FILE *text;
							if((text = fopen(WGFileName,"a")) != NULL)
							{	
								fputs(str,text);		
								fclose(text);
							}

							SendMessage(WM_EVENT, 19, 0);
							Beep(5000,400);						
							break;

						}
						
					}
					
				}
				////////////////

			}

			SetProgressCtrlSetIt();

			//�к��Լ�
			m_ListRows++;
			
			//�û����»�һ����¼
			rs.MoveNext();
			
		}
		  
	    //�ر����ݿ�
	    if(rs.IsOpen())
		{
		   rs.Close();
		}
	  
	    //ѭ���������� 
	    if(db.IsOpen())
		{
		   db.Close();
		}
		  
    }
	  
	//״̬����ϢΪ��
	StatusStr = StatusStrRead;
	SendMessage(WM_EVENT, 1, 0);
	
	ShowProgressCtrl(FALSE);
//	m_StartRead    =  FALSE;
	  
}

//���е��޹�����һ��
void CIFRMView::ALLWuGongDeal()
{	
	//��ʾ��
	if(AppInfo::Instance().m_YanShi)
	{
		return;
	}

	BYTE    LineNo           =        0;//��  ��
	BYTE    PhaseNo          =        0;//��  ��
	BYTE    StationNo        =        0;//�����ֱ��վ����
	BYTE    MotherLine       =        0;//ĸ�߱��
	long    ModuleNo         =        0;//ģ���
	long    Records          =        0;//�Ǳ�����
	double  CurrentValue     =        0;//��ʼ��ģ������
	long    GetModuleNo      =        0;//�м����
	long    fields           =        0;//��¼��
	BYTE    m_AMMETERKIND    =        0;//�������
	BYTE    m_SUPPLYMODED    =        0;//���緽ʽ 0-���߹��� 1��վ������ 2-�������ֹ���
	BYTE    m_PROTOCOL       =        0;//����Э�� 71-73 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
    BYTE    m_SendAngle      =        0;//���͵ĽǶ� 2005-04-07�� 
	float   m_BeginValue     =        0;//����ֵ 
	BYTE    BakMotherLine    =        0;//����ĸ�߱��
	BYTE    BakLineNo        =        0;//������  ��
	CString           m_ReadAmmeterType;//�������� 	
	m_StartRead              =     TRUE;//��ͣ��־  
	BYTE                         orders;//�޹�����ָ��
	CString         strSql,strValue,str;
	CString DataStr          =       "";
	m_StartRead              =     TRUE;
	CString                 CondtionStr;
	int                   READTIMES = 3;
	float                    m_Q,m_WGGL;//m_Q �������أ��޹�����
	int                     m_QSUMS = 0;//����������
	double         m_UpValue,m_DownValue;
    m_UpValue                =      0.8;
    m_DownValue              =      0.3;
	short           m_dokind =        0;//0 ���� 1 Ͷ  2��
    double   	    m_Bvalue =        0;//(�޹�����*����)/����������; 
	double          m_Multiple =      0;//����
	short           m_RunStatus  =    0;//����״̬ 
	CString                  WGFileName;
		
	//ɾ��ԭ������
	m_StrArray.RemoveAll();
	m_StrArray.SetSize(13);            //13��
	
	StatusStr.Format("���ڽ����޹���������������Ժ�...");
    SendMessage(WM_EVENT, 1, 0);
	
	//���DIALOGBAR�ɼ��Ļ�������
	SendMessage(WM_EVENT, 6, 0);
	
	//��������ȫ������
	CondtionStr = " USER_AMMETERKIND=5";
	
   	//�����ݿ�
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);


		strSql      = "SELECT COUNT(*)  FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//�õ���¼����
		rs.GetFieldValue((short)0,strValue);
		fields   =  atoi(strValue);
		rs.Close();

		//���û�м�¼�Ļ�
		if(fields < 1)
		{
            db.Close();
			//״̬����Ϣ
			StatusStr = "  ";
            SendMessage(WM_EVENT, 1, 0);
           	return;
		}
		
		CTime timet = CTime::GetCurrentTime();
		str.Format("��%4d-%02d-%02d %02d:%02d:%02d���޹��������\r\n",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
		WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
		
		FILE *text;
		if((text = fopen(WGFileName,"a")) != NULL)
		{	
			fputs(str,text);		
			fclose(text);
		}

		strSql      = "SELECT WGUPDOWN_UP,WGUPDOWN_DOWN FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);
			m_UpValue       =     atof(strValue)/100.00;
			rs.GetFieldValue((short)1,strValue);
			m_DownValue     =     atof(strValue)/100.00;
		}	
		
		rs.Close();

		strSql      = "SELECT USER_NAME,USER_NO,USER_ADDRESS,USER_MODULENO,USER_AMMETERNO,USER_MOTHERLINE,USER_LINENAME,USER_LINENO,USER_PHASE,USER_TRANSFORMERNO,USER_INITIALVALUE,USER_AMMETERKIND,USER_SUPPLYMODE,USER_PROTOCOL,USER_SENDANGLE,USER_AMMETERTYPE,USER_BAKMOTHERLINE,USER_BAKLINENO,USER_MULTIPLE,USER_RUNSTATUS,b.WUGONG_SPACE FROM TB_USER a,TB_WUGONG b WHERE USER_MODULENO=b.WUGONG_MODULE AND " + CondtionStr;
		rs.Open(CRecordset::forwardOnly,strSql);

		//�õ��ֶθ���
		short nFields = rs.GetODBCFieldCount();
		rs.Close();	

		//�����ݿ�����
		rs.Open(CRecordset::forwardOnly,strSql);
		
		//���û���Ϣ
		for(int j = 0;j < fields; j ++)
		{
			
			//��ԭʼֵ
			CurrentValue = -1;
			
			//�������ֹͣ��ť
			if(!m_StartRead)
			{	
				
				if(rs.IsOpen())
				{
					rs.Close();
				}
				
				if(db.IsOpen())
				{
					db.Close();
				}
				
				//��ʾ״̬����Ϣ
				StatusStr = "��������;��ֹͣ��";
				SendMessage(WM_EVENT, 1, 0);
				return;
			}
			
			//���
			m_StrArray[0].Format(" ");
			
			//��ʾָ��
			m_StrArray[1] =  "�޹�����";
			
			//�����ֶε����ƿ�ʼ
			for(int i = 0; i < nFields; i++)
			{
				rs.GetFieldValue(int(i),strValue);

				strValue.TrimLeft();
				strValue.TrimRight();

				switch(i)
				{
				case 0:
					{
						//����
						m_StrArray[2] = strValue;
						break;
					}
				case 1:
					{ 
						//�û����  
						m_StrArray[3] = strValue;
						break;
					}
				case 2:
					{ 
						//סַ  
						m_StrArray[4] = strValue;
						break;
					}
				case 3:
					{  
						//ģ���
						m_StrArray[5].Format("%8s",strValue);
						ModuleNo = atol(strValue);
						break;
					}
				case 4:
					{  
						//����
						m_StrArray[6].Format("%8s",strValue);
						break;
					}
				case 5:
					{  
						//ĸ�ߺ�
						MotherLine = atoi(strValue); //add by 2004.10.21
						break;
					}
				case 6:
					{	
						//��·����
						m_StrArray[7] = strValue;
						break;
					}
				case 7:
					{
						//��·���
						LineNo = atoi(strValue);
						break;
					}
				case 8:
					{
						CString         PhaseStr;
						//��
						switch(atoi(strValue))
						{
						case 0:
							{
								PhaseStr = "A��";
								PhaseNo = 0;
								break;
							}
						case 1:
							{
								PhaseStr = "B��";
								PhaseNo = 1;
								break;
							}
						case 2:
							{
								PhaseStr = "C��";
								PhaseNo = 2;
								break;
							}
						default:
							{
								PhaseStr = "δ֪";
								PhaseNo = atoi(strValue);
								break;
							}
						}

						m_StrArray[8].Format("[%d-%d-%s",MotherLine,LineNo,PhaseStr);
						break;
					}
				case 9:
					{
						//��̨����
						m_StrArray[9].Format("%s",strValue);
						break;
					}
				case 10:
					{
						//�����ֵ�վ��
						StationNo    = m_handno;
						//����ֵ
						m_BeginValue = float(atof(strValue));
						break;
					}
				case 11:
					{
						//�������
						m_AMMETERKIND = atoi(strValue);
						break;
					}
				case 12:
					{
						//���緽ʽ
						m_SUPPLYMODED = atoi(strValue);
						break;
					}	
				case 13:
					{
						//����Э�� 31-39��71-79 ����[ʮλ:3-��У�� 7-BCHУ�� ��λ:���Ӵ���]
						m_PROTOCOL    = atoi(strValue);
						orders        =           0x48;
						
						switch(m_PROTOCOL)
						{
						case 61:
							{
								
							}
						case 62:
							{
								orders = 0x03;
								break;
							}
						case 71:
							{
								
							}
						case 72:
							{
								
							}
						case 73:
							{
								orders = 0x48;
								break;
							}
						}
						
						m_StrArray[8] = m_StrArray[8] + strValue + "]";
						break;
					}	
				case 14:
					{
						//����ĽǶ�,�Ƿ����ǽ�����,ƫ�ƽǶ�,�ǽ�Ϊ30��
						if(IsDyConnect(m_StrArray[9]))
						{
							m_SendAngle = 6;
						}
						else
						{
							m_SendAngle = 0;
						}
						
						break;
					}
				case 15:
					{
						//���������
						m_ReadAmmeterType = strValue;
						break;
					}	
				case 16:
					{
						//����ĸ�߱��
						BakMotherLine = atoi(strValue);
						break;
					}	
				case 17:
					{
						//���ó��ߺ�
						BakLineNo     = atoi(strValue);
						break;
					}
				case 18:
					{
						//����
						m_Multiple     = atof(strValue);
						break;
					}	
				case 19:
					{
						//Ͷ��״̬
						m_RunStatus    = atoi(strValue);
						break;
					}
				case 20:
					{
						//����������
						m_QSUMS       = atoi(strValue);
						break;
					}
					
				 }
				 
              }			 
			  //�����ֶε����ƽ���
			
			  CurrentValue =   -1;

			  //����READTIMES��
			  for(int m_readtimes = 0; m_readtimes < READTIMES; m_readtimes ++)
			  {

				  if(int(CurrentValue) != -1)
				  {
					  break;
				  }

				  //��ʾ״̬����Ϣ
				  StatusStr.Format("���ڵ�[%d]�β����޹�����[%d],���Ժ�...",m_readtimes + 1,ModuleNo);
				  SendMessage(WM_EVENT, 1, 0);	


				  //��֪��������Ļ�,ÿ���඼����һ��
				  if(PhaseNo > 2)
				  {				  
					  SurrenderWindowMessage();

					  //��ѭ��
					  for(PhaseNo = 0; PhaseNo <= 2; PhaseNo++)
					  { 
						  
						  if(int(CurrentValue) != -1)
						  {
							  break;
						  }

						  SurrenderWindowMessage();

						  //�������ֹͣ��ť
						  if(m_StartRead == FALSE)
						  {
							  break;
						  }
						  
						  switch(PhaseNo)
						  {
						  case 0:
							  {	
								  strValue.Format("����%s,����ģ���(%d)A��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 1:
							  {
								  strValue.Format("����%s,����ģ���(%d)B��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  case 2:
							  {
								  strValue.Format("����%s,����ģ���(%d)C��,���Ժ�...",m_StrArray[1],ModuleNo);
								  break;
							  }
						  }
						  
						  //��ʾ״̬����Ϣ
						  StatusStr =        strValue;
						  SendMessage(WM_EVENT, 1, 0);
						  
						  if(m_SendAngle == 0)
						  {
							  CurrentValue    =   ReadMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  else
						  {
							  //�ǽǱ����,�·��������,�·��������,��һ��ʵʱ����
							  CurrentValue    =   ReadSixChannelMeter(ModuleNo,StationNo,MotherLine,LineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						  }
						  
						  //��������Ƿ����
						  if(CurrentValue >= 0)
						  {
							  
							  if((m_PROTOCOL/10) == 6)
							  {
								  //61,62��Э��
								  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
								  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
									  
							  }
							  else  if((m_PROTOCOL/10) == 7)
							  {
								  
								  //71,72��Э��
								  m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //��������
								  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //�޹�����
								  
								  if(m_Q > 1 || m_WGGL > 100)
								  {
                                      CurrentValue  = -1;
								  }
								  
							  }
							  
						  }
						  
						  SurrenderWindowMessage();
						  
						  //������������֣��ٶ�һ������
						  if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
						  {
							  
							  if(m_SendAngle == 0)
							  {
								  CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
							  else
							  {
								  //�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
								  CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							  }
													  
							  //��������Ƿ����
							  if(CurrentValue >= 0)
							  {
								  
								  if((m_PROTOCOL/10) == 6)
								  {
									  //61,62��Э��
									  m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
									  m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }
										  
								  }
								  else  if((m_PROTOCOL/10) == 7)
								  {
									  
									  //71,72��Э��
									  m_Q     =   (int(CurrentValue*100)/10000)*0.001;   //��������
									  m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;   //�޹�����
									  
									  if(m_Q > 1 || m_WGGL > 100)
									  {
										  CurrentValue  = -1;
									  }

								  }
								  
							  }

						  }
							  
						  SurrenderWindowMessage();
						  
						  //���������ֵ���ڻ����0	
						  if(CurrentValue >= 0 || int(CurrentValue) == -2  || int(CurrentValue) == -3)
						  {
							  
							  //��
							  switch(PhaseNo)
							  {
							  case 0:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"A��",m_PROTOCOL);
									  break;
								  }
							  case 1:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"B��",m_PROTOCOL);
									  break;
								  }
							  case 2:
								  {
									  m_StrArray[8].Format("[%d-%d-%s-%d]",MotherLine,LineNo,"C��",m_PROTOCOL);
									  break;
								  }
							  }
							  
							  //���������ݿ�
							  strValue.Format("UPDATE TB_USER SET USER_PHASE = %d WHERE USER_MODULENO= %d",PhaseNo,ModuleNo);
							  //����SQL���
							  CDataBaseInstance::ExecuteDataBaseSQL(strValue); 
							  break;
							  
						  }
							  

                     }
			 					  
					  
				}
				else
				{
					//֪������Ͷ�����
					CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine/*ĸ��*/,LineNo, PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						
					//��������Ƿ����
					if(CurrentValue >= 0)
					{
						
						if((m_PROTOCOL/10) == 6)
						{
							//61,62��Э��
							m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
							m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						else  if((m_PROTOCOL/10) == 7)
						{
							
							//71,72��Э��
							m_Q     =   (int(CurrentValue*100)/10000)*0.001;  //��������
							m_WGGL  =   (int(CurrentValue*100)%10000)* 0.01;  //�޹�����
							
							if(m_Q > 1 || m_WGGL > 100)
							{
								CurrentValue  = -1;
							}
							else
							{
								break;
							}
							
						}
						
					}
					
					SurrenderWindowMessage();
									
					//������������֣��ٶ�һ������
					if(int(CurrentValue) == -1 &&  m_SUPPLYMODED == 2 && m_StartRead)
					{
						
						if(m_SendAngle == 0)
						{
							CurrentValue =  ReadMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						else
						{
							//�ǽǱ����,�·��������,�·��������,��һ��ʵʱ������ֵΪ��4û���յ���פ��,�ٶ�һ��
							CurrentValue =  ReadSixChannelMeter(ModuleNo,StationNo,BakMotherLine,BakLineNo,PhaseNo,orders,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
						}
						
						//��������Ƿ����
						if(CurrentValue >= 0)
						{
							
							if((m_PROTOCOL/10) == 6)
							{
								//61,62��Э��
								m_Q     =  (int(CurrentValue*10)/256)*1.000/1000;//��������
								m_WGGL  =  (int(CurrentValue*10)%256)*1.000;     //�޹�����
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{	
									MotherLine  =  BakMotherLine;//����ĸ�߱��
	                                LineNo      =   BakLineNo;   //�����ߺ�
									break;
								}
								
							}
							else  if((m_PROTOCOL/10) == 7)
							{
								
								//71,72��Э��
								m_Q     =   (int(CurrentValue*100)/10000)*0.001;         //��������
								m_WGGL  =   (int(CurrentValue*100)%10000)*0.01;          //�޹�����
								
								if(m_Q > 1 || m_WGGL > 100)
								{
									CurrentValue  = -1;
								}
								else
								{
									MotherLine  =  BakMotherLine;//����ĸ�߱��
	                                LineNo      =   BakLineNo;   //�����ߺ�
									break;
								}
								
							}
							
						}
						
						SurrenderWindowMessage();

						//����ڱ���ĸ�ߺͱ��ó����϶�����
						if(int(CurrentValue) != -1)
						{
							switch(PhaseNo)
							{
							case 0:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"A��",m_PROTOCOL);
									break;
								}
							case 1:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"B��",m_PROTOCOL);
									break;
								}
							case 2:
								{
									m_StrArray[8].Format("[��%d-%d-%s-%d]",BakMotherLine,BakLineNo,"C��",m_PROTOCOL);
									break;
								}
							}
							
						}
						
					}
					
				}
			
            }
				
			//���ݵõ���ֵ�½���
			if(int(CurrentValue) == -1)
			{	
				//�û����»�һ����¼
				rs.MoveNext();
				//��������ִ��
				continue;
			}
				
			Beep(5000,400); 
			
			//���ݵõ���ֵ�½���
			if(CurrentValue >= 0 )
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("�ɹ�");
				strValue.Format("Q(%.2f),QG(%.2f)",m_Q,m_WGGL);
				m_StrArray[11]  =  strValue;
			}
			else
			{	
				strValue.Format("(%d,%.2f,%.2f)",m_QSUMS,m_UpValue,m_DownValue);
				m_StrArray[4] = m_StrArray[4] + strValue;
				m_StrArray[10].Format("δ�ɹ�");
				
				//�ص�ֵΪFEFEFE.FE,����ģ�������ͨѶ��û������
				if(int(CurrentValue) == -2)
				{	
					//��ȷ�Ļ�
					m_StrArray[11] = "����1 ";
				}

				if(int(CurrentValue) == -3)
				{
					//��ȷ�Ļ�
					m_StrArray[11] = "����2 ";
				}					
				
			}
			
			//ʱ��
			CTime timet = CTime::GetCurrentTime();	
			m_StrArray[12].Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());
			
			SurrenderWindowMessage();			
		
			//���ֵΪ��
			if(CurrentValue >= 0 )
			{
				//m_dokind   0 ���� 1 Ͷ  2 ��
				//61,62 �͵� 0x04  ͣ��  0x05
                //71,72 �͵� 0xf6  ͣ��  0xf8
                m_dokind =   0;
				
                if(m_QSUMS > 0)
				{
					
					m_Bvalue  = (m_WGGL*m_Multiple)/m_QSUMS;//(m_WGGL*����)/m_QSUMS; 
					
					//�������� 1 Ͷ
					if(m_Bvalue >= m_UpValue)
					{
                        m_dokind =   1;
					}
					
					//С������ 2 ��
					if(m_Bvalue <= m_DownValue)
					{
                        m_dokind =   2;
					}
					
                }

				//Ҫ�Ͳ����͵�״̬,Ҫͣ����ͣ��״̬	 m_RunStatus  0 ����  1  ͣ��
				if(((m_dokind == 1  && m_RunStatus != 0)  || (m_dokind == 2 && m_RunStatus != 1)) && (m_dokind > 0))
				{
					
					//�����Ƿ�Ͷ��,	Ͷ3��
					for(int yyy = 0; yyy < READTIMES; yyy ++)
					{
						
						SurrenderWindowMessage();
						
						if(m_dokind == 1)
						{
							//��ʾ״̬����Ϣ
							StatusStr.Format("���ڵ�[%d]�ζ��޹�����ģ��[%d]Ͷ�������,�Ժ�...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);	
							
							if(m_PROTOCOL/10 == 6  && m_StartRead)
							{
								//�͵����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x04,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//�͵����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf6,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						else
						{
							//��ʾ״̬����Ϣ
							StatusStr.Format("���ڵ�[%d]�ζ��޹�����ģ��[%d]�в������,�Ժ�...",yyy + 1,ModuleNo);
							SendMessage(WM_EVENT, 1, 0);
							
							if(m_PROTOCOL/10 == 6  &&  m_StartRead)
							{
								//ͣ�����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0x05,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							else
							{
								//ͣ�����
								CurrentValue  =  ReadMeter(ModuleNo,StationNo,MotherLine,LineNo, PhaseNo,0xf8,m_PROTOCOL,m_SendAngle,m_ReadAmmeterType);
							}
							
						}
						
						//������سɹ�
						if(int(CurrentValue) > 0)
						{
							
							CTime timet = CTime::GetCurrentTime();

							//�޸��͵硢ͣ��״̬
							if(m_dokind == 1)
							{
								//�͵�,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=0,USER_DESCRIBE = '%s' WHERE USER_MODULENO= %d","�޹������͵�",ModuleNo);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("��%4d-%02d-%02d %02d:%02d:%02d��ģ�飺%d    ����:�޹������͵�\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}
							else
							{
								//ͣ��,���������ݿ�
								strValue.Format("UPDATE TB_USER SET USER_RUNSTATUS=1,USER_DESCRIBE = '%s' WHERE USER_MODULENO=%d","�޹�����ͣ��",ModuleNo);
								//����SQL���
								CDataBaseInstance::ExecuteDataBaseSQL(strValue);
								str.Format("��%4d-%02d-%02d %02d:%02d:%02d��ģ�飺%d    ����:�޹�����ͣ��\r\n ",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond(),ModuleNo);
							}

							WGFileName.Format("%sifrm_%d_%02d_WG_log.TXT",GetFileFolderPass,timet.GetYear(),timet.GetMonth());
							
							FILE *text;
							if((text = fopen(WGFileName,"a")) != NULL)
							{	
								fputs(str,text);		
								fclose(text);
							}

							Beep(5000,400);						
							break;

						}
						
					}
					
				}
				////////////////

			}

			//�û����»�һ����¼
			rs.MoveNext();
			
		}
		  
	    //�ر����ݿ�
	    if(rs.IsOpen())
		{
		   rs.Close();
		}
	  
	    //ѭ���������� 
	    if(db.IsOpen())
		{
		   db.Close();
		}
		  
    }
	  
	//״̬����ϢΪ��
	StatusStr = "             ";
	SendMessage(WM_EVENT, 1, 0);  
}


void CIFRMView::OnWugongdeal() 
{
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}

    //�õ��Ի�������ѡ����
    if(!GetDialogBarStr())
	{
		return;
	}
	
	CMainFrame* pMainFrm =  (CMainFrame*) AfxGetApp()->m_pMainWnd;
	SendContionStr       =  pMainFrm->m_wndMyDialogBar.SelectCondition();
	ReadMeterThread      =  AfxBeginThread(WorkerThread,(LPVOID)15,m_Thread_PRIORITY,0,0,NULL); // ����������
	ReadMeterThread->m_bAutoDelete  =  FALSE;//�߳�Ϊ�ֶ�ɾ��
}

void CIFRMView::OnUpdateWugongdeal(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pMainFrm);
	pCmdUI->Enable(!pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty());
	
	//ѡ������
	if(pMainFrm->m_wndMyDialogBar.SelectCondition().IsEmpty())
	{
		pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,FALSE);
	}
	else
	{
        pMainFrm->m_wndMyDialogBar.m_SSTabData.SetTabEnabled(2,TRUE);
	}	
}

//�õ��޹���ʱ����
short CIFRMView::GetWGTimeEvery()
{
	CString  strSql,strValue;
	short      m_Result = 0;
	
   	//�����ݿ�
	CDatabase           db;
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		//��CRecordset����
		CRecordset  rs(&db);

		strSql      = "SELECT WGUPDOWN_EVERYTIME FROM TB_WGUPDOWN";
		rs.Open(CRecordset::forwardOnly,strSql);
		
		if(!rs.IsEOF())
		{	
			rs.GetFieldValue((short)0,strValue);	
			m_Result        =  atoi(strValue);//�޹�ʱ����
		}	
		
		rs.Close();
		db.Close();
	}

	return m_Result;

}



void CIFRMView::OnDrfromaccess() 
{	
	//�ж��Ƿ��г���������
	if(CheckRunning())
	{
		return;
	}
	
	char szFilter[]="��Ƶ����Զ�̳������ļ�EXCEL�ļ�(*.mdb)|*.mdb|";//USER.mdb
   	CFileDialog dlg(TRUE,"MDB","*.MDB",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
	
	if(dlg.DoModal() == IDOK)
	{	

		DrFromAccessFile(dlg.GetPathName());
	
	}	
}


//���ⲿACCESS�������ݵ������
void CIFRMView::DrFromAccessFile(CString m_FileName)
{
	CDaoDatabase             db;	    //���ݿ�
	CDaoTableDefInfo  tableinfo;
	BOOL               bSuccess;
	CFileFind             fFind;
	CDaoRecordset   RecSet(&db);		//��¼��
	CString                 str;
	CString              SqlCmd;
	int    index      =       0;
	CStringArray     m_DataName;
    BOOL      m_finding = FALSE;
	int k        =            0;
	
	//�����Ƿ���ڴ����ݿ��ļ�USER.mdb
	bSuccess         =  fFind.FindFile(m_FileName);
	fFind.Close();
	
	if(bSuccess)
	{
		
		db.Open(m_FileName, TRUE, FALSE,_T(""));

		//�õ��������
		while(index < db.GetTableDefCount())
		{
			db.GetTableDefInfo(index,tableinfo,AFX_DAO_ALL_INFO);

			if(!(tableinfo.m_lAttributes & dbSystemObject) && !(tableinfo.m_lAttributes & dbHiddenObject))
			{

				m_DataName.Add(tableinfo.m_strName);
			
			}

			index++;
		}
		
        //���Ƿ���4����
		for(int index = 0; index < m_DataName.GetSize(); index ++)
		{
		
			if(m_DataName[index].Find("TB_AMMETER") != -1 || m_DataName[index].Find("TB_ELECTRICITY") != -1 ||  m_DataName[index].Find("TB_TRANSFORMER") != -1 ||  m_DataName[index].Find("TB_USER") != -1)
			{
			
				m_finding = TRUE;
			
			}

		}
		
		if(!m_finding)
		{
			db.Close();
			MessageBox("��ACCESS���ݱ��ǹ�Ƶ���䳭�����ݣ���","����",MB_OK|MB_ICONWARNING);
			return;
		}

		//�½�4����ʱ��
		//1����TB_AMMETERBAK���ݱ�
		if(IsCurveTableExist("TB_AMMETERBAK"))  //�Ƿ���ڴ˱�
		{
            SqlCmd.Format("DROP TABLE TB_AMMETERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

	
		SqlCmd = "CREATE TABLE [dbo].[TB_AMMETERBAK] (\
		    [AMMETER_TYPE]         [char] (10) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
		    [AMMETER_MANUFACTURER] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
		    [AMMETER_IMPULSE]      [int] NOT NULL ,\
		    [AMMETER_REMARK]       [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
		    ) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		 
		 //2����TB_ELECTRICITYBAK���ݱ�
		if(IsCurveTableExist("TB_ELECTRICITYBAK"))  //�Ƿ���ڴ˱�
		{               
            SqlCmd.Format("DROP TABLE TB_ELECTRICITYBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = "	CREATE TABLE [dbo].[TB_ELECTRICITYBAK] (\
				[ELECTRICITY_NO] [tinyint] NOT NULL ,\
				[ELECTRICITY_KIND] [char] (16) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[ELECTRICITY_PRICE] [float] NOT NULL ,\
				[ELECTRICITY_REMARK] [char] (30) COLLATE Chinese_PRC_CI_AS NULL \
				) ON [PRIMARY]";

         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);

        //3����TB_TRANSFORMERBAK���ݱ�
		if(IsCurveTableExist("TB_TRANSFORMERBAK"))  //�Ƿ���ڴ˱�
		{               
            SqlCmd.Format("DROP TABLE TB_TRANSFORMERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = " CREATE TABLE [dbo].[TB_TRANSFORMERBAK] (\
				[TRANSFORMER_NO] [char] (40) COLLATE Chinese_PRC_CI_AS NOT NULL ,\
				[TRANSFORMER_TYPE] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CAPACITY] [int] NULL ,\
				[TRANSFORMER_INSTALLTIME] [datetime] NULL ,\
				[TRANSFORMER_POSITION] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_OWNERSHIP] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
				[TRANSFORMER_CONNECTFORM] [tinyint] NULL \
				) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		 
		//4����TB_USERBAK���ݱ�
		if(IsCurveTableExist("TB_USERBAK"))  //�Ƿ���ڴ˱�
		{               
            SqlCmd.Format("DROP TABLE TB_USERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

		SqlCmd = " 	CREATE TABLE [dbo].[TB_USERBAK] (\
			[USER_COMPANY] [char] (30) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNO] [char] (5) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_STATIONNAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MOTHERLINE] [int] NULL ,\
			[USER_BAKMOTHERLINE] [int] NULL ,\
			[USER_LINENO] [int] NULL ,\
			[USER_BAKLINENO] [int] NULL ,\
			[USER_LINENAME] [char] (20) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TRANSFORMERNO] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_MODULENO] [bigint] NULL ,\
			[USER_PHASE] [tinyint] NULL ,\
			[USER_NAME] [char] (40) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_NO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_OLDNO] [char] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ADDRESS] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_PHONE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ELECTRICITYKIND] [tinyint] NULL ,\
			[USER_AMMETERNO] [char] (16) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_AMMETERKIND] [tinyint] NULL ,\
			[USER_INSTALLTIME] [datetime] NULL ,\
			[USER_SUPPLYMODE] [tinyint] NULL ,\
			[USER_INITIALVALUE] [float] NULL ,\
			[USER_MULTIPLE] [int] NULL ,\
			[USER_PROTOCOL] [tinyint] NULL ,\
			[USER_DESCRIBE] [char] (60) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_READLABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_TIMELABEL] [char] (15) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_ETSTATUS] [char] (12) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_IDNO] [int] NULL ,\
			[USER_AMMETERTYPE] [varchar] (10) COLLATE Chinese_PRC_CI_AS NULL ,\
			[USER_SENDANGLE] [tinyint] NULL ,\
			[USER_DOWNVALUE] [int] NULL ,\
        	[USER_UPVALUE]   [int] NULL, \
			[USER_RUNSTATUS] [tinyint] NULL,\
			[USER_ZHULABEL] [char] (93) COLLATE Chinese_PRC_CI_AS NULL\
			) ON [PRIMARY]";
         CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);

		COleVariant          vars;	
		vars.ChangeType(VT_I4, 0);
		
		//����TB_AMMETER����,�����Ϣ
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_AMMETER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//��ʾ״̬����Ϣ
			StatusStr.Format("���ڴ�%s���е�������Ϣ���ݣ����Ժ�...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//��ʾ������
			SetProgressCtrlRange(0, index,1);

			//������ TB_AMMETER
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_AMMETER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
				StatusStr.Format("��������Ϣ�������%.2f��,���Ժ�...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);
              	
				SqlCmd = "INSERT INTO TB_AMMETERBAK(AMMETER_TYPE,AMMETER_MANUFACTURER,AMMETER_IMPULSE,AMMETER_REMARK) VALUES (";

				for(int i = 0; i < 4; i ++)
				{	
					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();
					
					if(i == 2)
					{	
						
						if(str.IsEmpty())
						{
							SqlCmd = SqlCmd      + "0,";
						}
						else
						{
							SqlCmd = SqlCmd + str + ",";
						}
						
					}
					else
					{
						
						if(i < 3)
						{
							SqlCmd = SqlCmd + "'" + str + "',";
						}
						else
						{
							SqlCmd = SqlCmd + "'" + str + "')";
						}
						
					}

				}
				
		//		WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//д���
				k                       ++;
				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("��������Ϣ�������...");//,m_FileName);
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//��ʾ������

		}
	
		vars.ChangeType(VT_I4, 0);
		
		//����TB_ELECTRICITYBAK���ݱ�,�����Ϣ
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_ELECTRICITY",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		index = vars.lVal;

		if(index > 0)
		{
			
			//��ʾ״̬����Ϣ
			StatusStr.Format("���ڴ�%s���е�������Ϣ���ݣ����Ժ�...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//��ʾ������
			SetProgressCtrlRange(0, index,1);

			//������ TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_ELECTRICITY",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
				StatusStr.Format("���뵼�����������%.2f��,���Ժ�...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);

            	SqlCmd = "INSERT INTO TB_ELECTRICITYBAK(ELECTRICITY_NO,ELECTRICITY_KIND,ELECTRICITY_PRICE,ELECTRICITY_REMARK) VALUES (";
            
				for(int i = 0; i < 4; i ++)
				{
					SetProgressCtrlSetIt();

					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
					str.TrimRight();
					str.TrimLeft();

					switch(i)
					{
					case 0:
						{
						//	SqlCmd = SqlCmd  +  str + ",";
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}

							break;
						}
					case 1:
						{
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 2:
						{
							//SqlCmd = SqlCmd   + str + ",";
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}
							
							break;
						}
					case 3:
						{
							SqlCmd = SqlCmd + "'" + str + "')";
							break;
						}
						
					}
				
				}
			
			//	WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//д���
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("��������Ϣ�������...");
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//��ʾ������

		}

        vars.ChangeType(VT_I4, 0);

		//����TB_TRANSFORMERBAK���ݱ�,��̨��Ϣ����
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_TRANSFORMER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//��ʾ״̬����Ϣ
			StatusStr.Format("���ڴ�%s���е����̨��Ϣ���ݣ����Ժ�...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//��ʾ������
			SetProgressCtrlRange(0, index,1);

			//������ TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_TRANSFORMER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
				StatusStr.Format("���뵼���̨��Ϣ�������%.2f��,���Ժ�...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);

				//(TRANSFORMER_NO VARCHAR(40),TRANSFORMER_TYPE VARCHAR(10),TRANSFORMER_CAPACITY VARCHAR(4),TRANSFORMER_INSTALLTIME VARCHAR(8),TRANSFORMER_POSITION  VARCHAR(30),TRANSFORMER_OWNERSHIP VARCHAR(10),TRANSFORMER_CONNECTFORM  VARCHAR(1)
            	SqlCmd = "INSERT INTO TB_TRANSFORMERBAK(TRANSFORMER_NO,TRANSFORMER_TYPE,TRANSFORMER_CAPACITY,TRANSFORMER_INSTALLTIME,TRANSFORMER_POSITION,TRANSFORMER_OWNERSHIP,TRANSFORMER_CONNECTFORM) VALUES (";
            
				for(int i = 0; i < 7; i ++)
				{
					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();

					switch(i)
					{
					case 0:
						{
							//TRANSFORMER_NO
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 1:
						{
							//TRANSFORMER_TYPE
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 2:
						{
							//TRANSFORMER_CAPACITY	
							if(str.IsEmpty())
							{
								SqlCmd = SqlCmd      + "0,";
							}
							else
							{
								SqlCmd = SqlCmd + str + ",";
							}

							//SqlCmd = SqlCmd   + str + ",";
							break;
						}
					case 3:
						{
							//TRANSFORMER_INSTALLTIME,ʱ�䴦��
							CTime              m_BakTime(atoi(str.Mid(0,4)),atoi(str.Mid(4,2)),atoi(str.Mid(6,2)),0,0,0);
							str.Format("%4d-%02d-%02d %02d:%02d:%02d",m_BakTime.GetYear(),m_BakTime.GetMonth(),m_BakTime.GetDay(),m_BakTime.GetHour(),m_BakTime.GetMinute(),m_BakTime.GetSecond());
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 4:
						{
							//TRANSFORMER_POSITION
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 5:
						{
							//TRANSFORMER_OWNERSHIP
							SqlCmd = SqlCmd + "'" + str + "',";
							break;
						}
					case 6:
						{
							//TRANSFORMER_CONNECTFORM
							SqlCmd = SqlCmd  + str +  ")";
							break;
						}
						
					}
				
				}
				
				//WriteToLog(SqlCmd);
                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//д���
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("�����̨��Ϣ�������...");
			SendMessage(WM_EVENT, 1, 0);
			ShowProgressCtrl(FALSE);//��ʾ������

		}
		
        vars.ChangeType(VT_I4, 0);
		//����TB_USERBAK���ݱ�,��̨��Ϣ����
		RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT COUNT(*) FROM TB_USER",NULL);
		RecSet.GetFieldValue((short)0,vars);  
		RecSet.Close();
		
		index = vars.lVal;

		if(index > 0)
		{
			
			//��ʾ״̬����Ϣ
			StatusStr.Format("���ڴ�%s���е����û���Ϣ���ݣ����Ժ�...",m_FileName);
			SendMessage(WM_EVENT, 1, 0);

           	k        =            0;
			ShowProgressCtrl(TRUE);//��ʾ������
			SetProgressCtrlRange(0, index,1);

			//������ TB_ELECTRICITY
			RecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TB_USER",NULL);
					
			while(!RecSet.IsEOF())	
			{		
			
				//��ʾ״̬����Ϣ,������ʾ״̬����ʾ	
				StatusStr.Format("���뵼���û���Ϣ�������%.2f��,���Ժ�...",k*100.0/index);
				SendMessage(WM_EVENT,1,0);
			
             	SqlCmd = "INSERT INTO TB_USERBAK(USER_COMPANY     ,USER_STATIONNO    ,USER_STATIONNAME    ,USER_MOTHERLINE  ,USER_BAKMOTHERLINE ,USER_LINENO     ,USER_BAKLINENO ,\
												 USER_LINENAME    ,USER_TRANSFORMERNO,USER_MODULENO       ,USER_PHASE       ,USER_NAME          ,USER_NO         ,USER_OLDNO     ,\
												 USER_ADDRESS     ,USER_PHONE        ,USER_ELECTRICITYKIND,USER_AMMETERNO   ,USER_AMMETERKIND   ,USER_INSTALLTIME,USER_SUPPLYMODE,\
												 USER_INITIALVALUE,USER_MULTIPLE     ,USER_PROTOCOL       ,USER_DESCRIBE    ,USER_READLABEL     ,USER_TIMELABEL  ,USER_ETSTATUS  ,\
												 USER_IDNO        ,USER_AMMETERTYPE  ,USER_SENDANGLE      ,USER_DOWNVALUE   ,USER_UPVALUE       ,USER_RUNSTATUS  ,USER_ZHULABEL  ) VALUES (";
				for(int i = 0; i < 35; i ++)
				{					
					COleVariant               var;	
		            var.ChangeType(VT_BSTR, NULL);
					
					SetProgressCtrlSetIt();
					RecSet.GetFieldValue((short)i,var);
					
					str = (LPCSTR)var.pbstrVal;
                   	
					str.TrimRight();
					str.TrimLeft();

					//��ֵ��
					if((i >= 3 && i <= 6) || (i==9) ||  (i==10) || (i==16) || (i==18) || (i==20) || (i==21) || (i==22) || (i==23) || (i>=30 && i<=33))
					{

						if(str.IsEmpty())
						{
							SqlCmd = SqlCmd      + "0,";
						}
						else
						{
							SqlCmd = SqlCmd + str + ",";
						}

					}
					else if(i == 19)
					{
						//USER_INSTALLTIME
						CTime              m_BakTime(atoi(str.Mid(0,4)),atoi(str.Mid(4,2)),atoi(str.Mid(6,2)),0,0,0);
						str.Format("%4d-%02d-%02d %02d:%02d:%02d",m_BakTime.GetYear(),m_BakTime.GetMonth(),m_BakTime.GetDay(),m_BakTime.GetHour(),m_BakTime.GetMinute(),m_BakTime.GetSecond());
						SqlCmd = SqlCmd + "'" + str + "',";
						
					}
					else if(i == 34)
					{
						SqlCmd = SqlCmd + "'" + str + "')";
					}
					else
					{
                        SqlCmd = SqlCmd + "'" + str + "',";
					}

				}

		//		WriteToLog(SqlCmd);
		//		AfxMessageBox(SqlCmd);

                CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	//д���
				k                       ++;

				RecSet.MoveNext();
			}
			
			RecSet.Close();

			StatusStr.Format("�����û���Ϣ�������...");
			SendMessage(WM_EVENT, 1, 0);

			ShowProgressCtrl(FALSE);//��ʾ������
		}

		//����ʱ���е�������
		StatusStr.Format("������ʱ���е������ݣ����Ժ�...");
		SendMessage(WM_EVENT, 1, 0);

	    ShowProgressCtrl(TRUE);//��ʾ������
		SetProgressCtrlRange(0, 4,1);

		
		//ɾ��TB_AMMETERBAK���ݱ�
		if(IsCurveTableExist("TB_AMMETERBAK"))  //�Ƿ���ڴ˱�
		{
			//����������
			SqlCmd = "INSERT INTO TB_AMMETER SELECT DISTINCT * FROM TB_AMMETERBAK WHERE AMMETER_TYPE NOT IN (SELECT AMMETER_TYPE FROM TB_AMMETER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
			SqlCmd.Format("DROP TABLE TB_AMMETERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}
	

		SetProgressCtrlSetIt();	
		
		//ɾ��TB_ELECTRICITYBAK���ݱ�
		if(IsCurveTableExist("TB_ELECTRICITYBAK"))  //�Ƿ���ڴ˱�
		{       
			//����������
			SqlCmd = "INSERT INTO TB_ELECTRICITY SELECT DISTINCT * FROM TB_ELECTRICITYBAK WHERE ELECTRICITY_NO NOT IN (SELECT ELECTRICITY_NO FROM TB_ELECTRICITY)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
            SqlCmd.Format("DROP TABLE TB_ELECTRICITYBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}

	
		SetProgressCtrlSetIt();
	
		//ɾ��TB_TRANSFORMERBAK���ݱ�
		if(IsCurveTableExist("TB_TRANSFORMERBAK"))  //�Ƿ���ڴ˱�
		{    
			//�����̨����
			SqlCmd = "INSERT INTO TB_TRANSFORMER SELECT DISTINCT * FROM TB_TRANSFORMERBAK WHERE TRANSFORMER_NO NOT IN (SELECT TRANSFORMER_NO FROM TB_TRANSFORMER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);	           
            SqlCmd.Format("DROP TABLE TB_TRANSFORMERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
		}
	

		SetProgressCtrlSetIt();
		
		//ɾ��TB_USERBAK���ݱ�
		if(IsCurveTableExist("TB_USERBAK"))  //�Ƿ���ڴ˱�
		{  
			//�����û�����
			SqlCmd = "INSERT INTO TB_USER SELECT DISTINCT * FROM TB_USERBAK WHERE USER_MODULENO NOT IN (SELECT USER_MODULENO FROM TB_USER)"; 
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);           
            SqlCmd.Format("DROP TABLE TB_USERBAK");
			CDataBaseInstance::ExecuteDataBaseSQL(SqlCmd);
			
			//���ؼ�����ˢ��һ��
			RefreshTree();
		}	
		
		SetProgressCtrlSetIt();

		StatusStr.Format("����ACCESS���ݿ��е�������������ϡ�");
		SendMessage(WM_EVENT, 1, 0);
	    db.Close();

		ShowProgressCtrl(FALSE);//��ʾ������
	
	}
	
}

//���ٶ���ʱ���ó���ǰ��ģ�������������ֵ��ʱ��,61,62Э��Ϊ485��,71,72Э��Ϊ�����
BOOL CIFRMView::TestIfCanQuickReadAmmeter(long module,CString  m_CurrentTime,CString  m_AmmeterType,BYTE m_protcol)
{	
	CDatabase                   dbs;	
	CString              strSql,str;
	int       m_days        =     0;
	int       k             =  3200;
	BOOL      m_CheckValue  = FALSE;
	double  m_tempvalue,m_InitValue;
	m_tempvalue  = m_InitValue =  0;

	//m_QuickReadParameter[0] �����й���ȶ���ֵ
	//m_QuickReadParameter[1] �й���ȵ�ֵ
	//m_QuickReadParameter[2] 3200�ı���

	for(int i = 0; i < 3; i ++)
	{
		m_QuickReadParameter[i] = 0;
	}

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset             rs(&dbs);
		//strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,module,module);
		strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s'),b.USER_INITIALVALUE FROM TB_GARRISON a,TB_USER b WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d AND b.USER_MODULENO=a.GARRISON_MODULENO",m_CurrentTime,module,module);
		rs.Open(CRecordset::forwardOnly,strSql);

		if(!rs.IsEOF())
		{
			//�й���ȵ�ֵ
			rs.GetFieldValue((short)0,strSql);			
			m_QuickReadParameter[0]   = atof(strSql);
			
			//�����ڵ�ʱ���
			rs.GetFieldValue((short)1,strSql);
			m_days     =  atoi(strSql);
			
			//��ʼֵ
			rs.GetFieldValue((short)2,strSql);
			m_QuickReadParameter[1]   = atof(strSql);
		}

		rs.Close();
		
	    if(!m_AmmeterType.IsEmpty())
		{
			strSql.Format("SELECT AMMETER_IMPULSE FROM TB_AMMETER  WHERE RTRIM(AMMETER_TYPE)='%s'",m_AmmeterType);
			rs.Open(CRecordset::dynaset,strSql);	
			
			if(!rs.IsEOF())
			{
	    		rs.GetFieldValue((short)0,strSql);
				k =  atoi(strSql);
			}
			
			if(k == 0)
			{
				k = 3200;
			}
			
			rs.Close( );

		}	

		dbs.Close();
		
	}   
	
	if(BYTE(m_protcol/10) == 6)
	{
		//61,62Э��Ϊ485��
		if(m_days < 20 && m_QuickReadParameter[0] > 0.01)
		{
			m_CheckValue = TRUE;
		}
		
	}
	else
	{
		//71,72Э��Ϊ�����
		m_QuickReadParameter[2] = k*1.00/3200;
		
		if(m_days/m_QuickReadParameter[2] < 20  && m_QuickReadParameter[0] > 0.01)
		{
			m_CheckValue = TRUE;
		}

	}
	
	return m_CheckValue;
}

//�õ���פ����Ϣ��ĸ�ߺ�Э������
void CIFRMView::GetSendZhuLiuInformation()
{	

	m_MotherLineArray.RemoveAll();
	m_ProtColArray.RemoveAll();

	CDatabase            db;
	CString             Str;
	
	if(db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
		
		//��CRecordset����
		CRecordset        rs(&db);
		
		//ĸ��
		//SELECT DISTINCT USER_MOTHERLINE,USER_PROTOCOL FROM TB_USER ORDER BY USER_MOTHERLINE ASC,USER_PROTOCOL DESC
		Str = "SELECT DISTINCT USER_MOTHERLINE FROM TB_USER";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //�õ���¼����
		    rs.GetFieldValue((short)0,Str);
			m_MotherLineArray.Add(atoi(Str));
			rs.MoveNext();
		}

		rs.Close();

		//����
		Str = "SELECT DISTINCT USER_BAKMOTHERLINE FROM TB_USER";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //�õ���¼����
		    rs.GetFieldValue((short)0,Str);
			m_MotherLineArray.Add(atoi(Str));
			rs.MoveNext();
		}

		rs.Close();

		//Э��SELECT DISTINCT a.USER_BAKMOTHERLINE,a.USER_PROTOCOL FROM TB_USER a, TB_USER b WHERE a.USER_BAKMOTHERLINE=b.USER_BAKMOTHERLINE AND b.USER_BAKMOTHERLINE> 0 ORDER BY a.USER_BAKMOTHERLINE ASC,a.USER_PROTOCOL DESC 
		Str = "SELECT DISTINCT USER_PROTOCOL FROM TB_USER ORDER BY USER_PROTOCOL DESC";
		rs.Open(CRecordset::forwardOnly,Str);
		
		while(!rs.IsEOF())
		{
		    //�õ���¼����
		    rs.GetFieldValue((short)0,Str);
			m_ProtColArray.Add(atoi(Str));
			rs.MoveNext();
		}

    	rs.Close();
		db.Close( );				
	}


}

//���71Э��485����ٶ����Ƿ�ɹ�
void CIFRMView::Check_71485_Protcol(long ModuleNum,BYTE m_order)
{
  	CDatabase                                    dbs;	
	CString                               strSql,str;
	int                 m_days         =           0;
	double    m_tempvalue1,m_tempvalue2,m_tempvalue3;
	m_tempvalue1 =  m_tempvalue2 = m_tempvalue3  = 0;
	CString                            m_CurrentTime;
	CTime  timet  =          CTime::GetCurrentTime();
    m_CurrentTime.Format("%4d-%02d-%02d %02d:%02d:%02d",timet.GetYear(),timet.GetMonth(),timet.GetDay(),timet.GetHour(),timet.GetMinute(),timet.GetSecond());

	if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog))
	{
    	CRecordset   rs(&dbs);

		//��CRecordset����
		if(m_order == 0x64 || m_order == 0xF4)
		{	
			//�壬ƽ���ȿ��ٶ���
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_FDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			//פ����
			if(!rs.IsEOF())
			{
				//��ֵ
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue1 = atof(strSql);
				
				//ʱ�������
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[0] = m_tempvalue1 - (long(m_tempvalue1)%1000) + m_Quick71Value[0];

				//���Ե�
				if(m_days == 1)
				{					
					
					//һ����0~200��,�����Ƿ����
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{	
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{
					
					//һ����0~200��
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//�ɿ��ٶ�485��
				m_CanQuickRead71485   = FALSE;	
				
			}
			
			//פ����
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_PDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
				//ƽ,��ֵ
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue2 = atof(strSql);
				
				//ʱ�������
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[1] = m_tempvalue2 - (long(m_tempvalue2)%1000) + m_Quick71Value[1];

				//���Ե�
				if(m_days == 1)
				{					
					
					//һ����0~200��,�����Ƿ����
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{	
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;
					
					}
					
				}
				else
				{
					//һ����0~200��
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//�ɿ��ٶ�485��
				m_CanQuickRead71485   = FALSE;	
				
			}
			
			//פ����
			if(rs.IsOpen())
			{
				rs.Close();
			}
			
			strSql.Format("SELECT  GARRISON_GDL,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
				//��ֵ
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue3 = atof(strSql);
				
				//ʱ�������
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[2] = m_tempvalue3 - (long(m_tempvalue3)%1000) + m_Quick71Value[2];

				//���Ե�
				if(m_days == 1)
				{	
					
					//һ����0~200��,�����Ƿ����
					if(!(((m_Quick71Value[2] - m_tempvalue3) <= m_days*200) && ((m_Quick71Value[2] - m_tempvalue3) >= 0)))
					{	
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{

					//һ����0~200��
					if(!(((m_Quick71Value[2] - m_tempvalue3) <= m_days*200) && ((m_Quick71Value[2] - m_tempvalue3) >= 0)))
					{
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//�ɿ��ٶ�485��
				m_CanQuickRead71485   = FALSE;	
				
			}
		
		
		}
		else if(m_order == 0x66 || m_order == 0xF6)
		{
			//ʵʱ�й����޹�,פ���й����޹�
			if(rs.IsOpen())
			{
				rs.Close();
			}

			strSql.Format("SELECT  GARRISON_WORKDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
			rs.Open(CRecordset::forwardOnly,strSql);

			if(!rs.IsEOF())
			{
				//פ���й�
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue1 = atof(strSql);
				
				//ʱ�������
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[0] = m_tempvalue1 - (long(m_tempvalue1)%10000) + m_Quick71Value[0];

				//���Ե�
				if(m_days == 1)
				{					
					//һ����0~200��,�����Ƿ����
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{	
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{
					//һ����0~200��
					if(!(((m_Quick71Value[0] - m_tempvalue1) <= m_days*200) && ((m_Quick71Value[0] - m_tempvalue1) >= 0)))
					{
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//�ɿ��ٶ�485��
				m_CanQuickRead71485   = FALSE;	
				
			}

		    //פ���޹�
			if(rs.IsOpen())
			{
				rs.Close();
			}

			strSql.Format("SELECT  GARRISON_LOSEDEGREE,DATEDIFF(day,GARRISON_HALTTIME,'%s') FROM TB_GARRISON  WHERE GARRISON_HALTTIME = (SELECT MAX(GARRISON_HALTTIME) FROM  TB_GARRISON WHERE GARRISON_MODULENO=%d) AND GARRISON_MODULENO=%d",m_CurrentTime,ModuleNum,ModuleNum);
            rs.Open(CRecordset::forwardOnly,strSql);
			
			if(!rs.IsEOF())
			{
			
				rs.GetFieldValue((short)0,strSql);
				m_tempvalue2 = atof(strSql);
				
				//ʱ�������
				rs.GetFieldValue((short)1,strSql);
				m_days     = atoi(strSql);
				rs.Close();
		
				if(m_days == 0)
				{
					m_days  =  1;
				}

				m_Quick71Value[1] = m_tempvalue2 - (long(m_tempvalue2)%10000) + m_Quick71Value[1];

				if(m_days == 1)
				{	
					
					//һ����0~200��,�����Ƿ����
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{	
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;
					}
					
				}
				else
				{

					//һ����0~200��
					if(!(((m_Quick71Value[1] - m_tempvalue2) <= m_days*200) && ((m_Quick71Value[1] - m_tempvalue2) >= 0)))
					{
						//�ɿ��ٶ�485��
						m_CanQuickRead71485   = FALSE;	
					}
					
				}
				
			}
			else
			{				
				//�ɿ��ٶ�485��
				m_CanQuickRead71485   = FALSE;	
				
			}
		
        }
		
	//	str.Format("����(0x%0x),m_CanQuickRead71485=%d(1�ܿ��,0����)�����:%.2f(���m_Quick71Value[0]=%.2f),���:%.2f(m_Quick71Value[1]=%.2f),���:%.2f(m_Quick71Value[2]=%.2f)",m_order,m_CanQuickRead71485,m_tempvalue1,m_Quick71Value[0],m_tempvalue2,m_Quick71Value[1],m_tempvalue3,m_Quick71Value[2]);
	//	WriteToLog(str);
	  
		if(rs.IsOpen())
		{
			rs.Close();
		}
	
		if(dbs.IsOpen())
		{
			dbs.Close();
		}


	}

}
