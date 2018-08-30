// IFRMView.h : interface of the CIFRMView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include <windows.h>                                       
#include <iostream> 
#include "afxmt.h"
#include "resource.h"
#include "mscomm.h"
#include "mswinsockcontrol.h"
//}}AFX_INCLUDES

#include "MyListCtrl.h"
#include "gridctrl.h"
#include "MutiTreeCtrl.h"
#include "memory"

#define WM_EVENT WM_USER+7

#if !defined(AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_)
#define AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIFRMCntrItem;

//�ܹ����ʹ���
#define   PASS_TIMES     35
#define   WM_NUMBERS     81

class CTransformRecordset    ;
class CAmetterRecordset      ;
class CUseInfoRecordSet      ;
class CGarrisonRecordSet     ;
class CDataInfoRecordSet     ;
class CPriceSet              ;
class CCHANGEAMMETERSet         ;//����ģ��
class CIFRMApp;

class CIFRMView : public CFormView
{
protected: // create from serialization only
	CIFRMView();
	DECLARE_DYNCREATE(CIFRMView)
	//CDataListCtrl	m_list;	
public:
	//{{AFX_DATA(CIFRMView)
	enum { IDD = IDD_IFRM_FORM };
	CListCtrl               m_lists;
	CMSComm	                  m_Com;
	CMSWinsockControl	m_WinSocket;
	CMSComm	            m_485MsComm;
	//}}AFX_DATA
	
	// Attributes
public:

	// m_pSelection holds the selection to the current CIFRMCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CIFRMCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.
	
	// TODO: replace this selection mechanism with one appropriate to your app.
	CIFRMCntrItem* m_pSelection;
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFRMView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL
	
	// Implementation
public:	
	BOOL m_CanQuickRead71485;
	BOOL                        m_QuickReading; //�������
	void DrFromAccessFile(CString  m_FileName);
    short                    m_WgLess;//�޹���ʱ���� 0---10���� 1---20���� 2---30����
	void WuGongDeal(CString   ConStr);
	void         CheckTongXunStatus();
	void                StartZhuLiu();
	BYTE      m_DateReadParameter[67];//��פ����������פ������ ��ʽ��62(31��*��*��)��1(������)��1(*��)��1(�Ժ󣪵�һ��)��1(������),1(�Ƿ��Զ�פ��) = 62 + 5 = 67
	CString m_DynaicCheckStrCondition;
	BOOL           m_CheckReading;
	BOOL WaitShiKedian(BYTE m_shikedian);
	BYTE	          m_shikedian;
	BYTE		     m_readRangle;
	BYTE	 	 m_readchecktimes;
	CEvent		TmpOnlyOneThreadRun;
	BOOL                  m_Pause;//�߳���ͣ��־
	CString        m_dbConnectStr;
	void           CheckLineRun();
	void DealOverTime(BYTE kinds);
	BYTE              m_saveyears;
	BOOL      m_DoubleConnected;
	short     m_PassErrortimes;
	BOOL      DeleteViewThread();
	void      ModifyDialInternetStatus();
	BOOL      m_IfChangeData;//����Զ�����ݵı�־
	BOOL      m_others;
	CString   DecodeParameter(BOOL m_ReadRanage);
	void      WriteToAllAmeterParameter();
	void      WriteToParameterByDate();//д�밴�������ò�����פ��
	short     m_parameter[110];
    void      ComingIntoBeing(CString SqlStr,CString m_begin, CString m_End, BOOL m_yg, BOOL m_wg, BOOL m_jz, BOOL m_fz, BOOL m_gz, BOOL m_pz,  BOOL m_dy, BOOL m_dl);
    void      ElectricityWarning(CString SqlStr,CString m_begin, CString m_End);//�õ�������
	void      BeginTotalLoss(CString m_Condtion,CString BeginTime,CString EndTime);
	void      EverySendInfo();
	BOOL      UpdateDataTable();
	int       m_GetErrors;
	int       m_CurrentPassPostions;
	int       m_PassDataRecords;
	CString   m_PassDataFileName;
	CString   m_GetDataTimeStr;
	BOOL      m_GetDataFromFile;
	CStringArray m_FileDataArray;
	COLORREF  m_BackRgbValue;
	int       m_SetRecycleTime;
	int       m_Recycles;
	short     m_AutoReadParameter[160];//��ʱ����Ĳ��� ǰ0��30Ϊ����� 31��61Ϊ���û�ѡ�� 62��92Ϊ���� 93��123Ϊ��·�� 124��154Ϊ��վ�� 155 ��ʾ������� 156�й���ֵ0��û��ѡ��ֵ 1��ѡ�񵥱��ۼ� 2��ѡ�񵥱��ۼӼ���ֵ��157�޹���ֵ0��û��ѡ��ֵ 1��ѡ�񵥱��ۼ� 2��ѡ�񵥱��ۼӼ���ֵ��158������0 û��ѡ 1ѡ�� 159��ѹ��0 û��ѡ 1ѡ��
	void      SetDataReadLabel(CString m_range);
	
	BOOL      m_IsDialConnectting;    //�κ����ӵı�־
	CString   m_FtpFileName;
	void      GetDataFormMarketServer(CString m_address, CString m_loginname, CString m_password,CString m_StrFileName,int m_port);
    //CString  m_DataName  ����,CString  TxtFileName  �����ı��ļ�
	void      DealRepeatRecord(CString  m_DataName,CString TxtFileName);
	void      SetGridItem(GV_DISPINFO *pDispInfo);
	BOOL      m_DialogBarVisible;
	CGridCtrl m_Grid;
	//��ʼ���б�
	void      InitGrid(CString table,CString BeginTime,CString EndTime);
	
    
	CString   m_ModuleFindContionStr;
	//1��������ݱ����
	CStringArray TB_ELECTRICITYS;
	//2����̨��Ϣ���ݱ����
	CStringArray TB_TRANSFORMERS;
	//3�������Ϣ���ݱ����
	CStringArray TB_AMMETERS;
	//4���û���Ϣ�����ݱ����
	CStringArray TB_USERS;
	//5��פ�����ݱ����
	CStringArray  TB_GARRISONS;
	//6�����ݱ����
	CStringArray  TB_REALTIMES;
    //7��������Ϣ
	CStringArray  TB_CHANGEAMMETERS;
	//��������ַ���û���������
	CString          m_address;
	CString        m_loginname;
	CString         m_password;
	int                 m_port;

	BOOL     m_IsAutoSending;
	void     SurrenderWindowMessage();
	void     KillAotoReadMeter();
	CString  m_TimeStrs;
	BOOL     SetRemoteTime(CString    Str);
	void     SetLocalTimes(CString  times);
	void     SetTimersign();
	CString  m_AutoReadCondtionStr;
	//�Ƿ�ʱ�����ź�
	BOOL     m_status;
	//���ӱ�־
	BOOL     m_IsConnect; //�������ӵı�־
	BOOL     Ports[15];
	//�õ����ݸ��µ�ʱ��
    CString GetRefreshTime();

	//�������»�
	void   SetProgressCtrlSetIt();
	void   ShowProgressCtrl(BOOL m_IsShow);
	void   status(CString strname);

	BYTE   m_handno;
	//�õ������ֱ���
    void   GetHandModuleInformation();
	void   SettcpClient(CString RemoteHostAddress,int RemotePort);
	void   SetLocalServer(CString LocalHostAddress, int LocalPort);
	BOOL   m_SetLabel[15];     //����Щ��
    BOOL   m_TimeSetLabel[15]; //��ʱ�����־
   	short  m_sendkind;         //0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����
	BOOL   m_StartRead;
	BOOL   m_DayOrYear[2];     //ÿ��һ������ÿ��һ��
	//���ýǶ�
	//short generatrixno ĸ�߱��
	//short phase        ��� 0 A�� 1 B�� 2 C��
	//int   angles       �Ƕ�
	//BYTE  kinds  ���� 0--�ź�ǿ�� 1���ӳٽǶ�
	void SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds);

	//��ȡ�Ƕ�
	//short generatrixno ĸ�߱��
    //short phase        ���   0 A�� 1 B�� 2 C��
    void   ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds);
	
	
	//title           �Ի������
    //IfWriteData     �Ƿ�д�����ݿ� FALSE---��д TRUE---д
    //WhichTable      �ĸ���         0----���ݱ�  1----פ����
    //constr          ���� ALL ����
	//recycles        ѭ������
	//Settimes        ÿ����ʱ����
	//m_ReadKinds     0---��ͨ����   1----�ֹ��� 
    void   FiveDataChuLi(CString title,BOOL  SELECT[],BOOL IfWriteData, int WhichTable, CString constr,int recycles,int Settimes,BYTE m_ReadKinds);
	
	//�������
    void   DisposeModuleParameter(CString Title,CString Result,CString ConStr, BYTE orders,BOOL OnlyReadNot,int times,BOOL OnlyOnce,int MinIValue,int MaxIValue,int intervals);

    //����SQL���
	

	//���ɳ�������
	void   FormChaoBiaoData(CString SqlStr,CString BeginTime,CString EndTime);
    
	//��פ��ʱ������
	void   SendBreadorder(CTime  m_iBroadTime,int times);
	void   WriteDataToExcelFile(CString dataname,CString Sqlstr,long records,CString filename);
	BOOL   PcSendToSCM(BYTE ORDER[],BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/);
	int    m_iBandPassPoints;
	void   WriteToLog(CString Str);
	BOOL   WriteDataToTextFile(CString dataname,CString Sqlstr,long records,CString filename);
	void   DisConnect(short kinds);
	BOOL   Connect(BOOL  ShowMessage,BOOL IfVoice);
	void   Dial(CString m_strPhoneNumber,BOOL IfVoice);
	CString m_strReceiveChar;
	/***************************************************************
	��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
	������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000
	����λ 0-��У��,1����У��,2��żУ��
	����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
	ֹͣλ 0-1     ,1-1.5    ,2-2
	//HexSend  TRUE  �����Ʒ�ʽ���� FALSE �ı���ʽ����
	****************************************************************/
    void   OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex);
	double ReadMeter(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/,BYTE Item/* Ҫʲô����*/,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/,CString m_AmmeterType/*������ͺ�*/);
	//ȫ�����������������,�ɼ���ͨ��
    double ReadSixChannelMeter(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/,BYTE Item/* Ҫʲô����*/,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/,CString m_AmmeterType/*������ͺ�*/);

	void   WriteP9111_CHANNEL_DOPort(int value);
	void   SetProgressCtrlRange(int ups,int downs,int steps);

	std::shared_ptr<CTransformRecordset>    m_TransformpSet;
	std::shared_ptr<CAmetterRecordset>      m_AmetterSet;
	std::shared_ptr<CUseInfoRecordSet>      m_UseInfoset;
	std::shared_ptr<CGarrisonRecordSet>     m_GarrisonSet;
	std::shared_ptr<CDataInfoRecordSet>     m_DataInfoSet;
	std::shared_ptr<CPriceSet>              m_PriceSet;
	std::shared_ptr<CCHANGEAMMETERSet>         m_CCHANGEAMMETER;//����ģ��

	//���̵߳�����
	CString                 SendContionStr;
	BOOL    SendOrderToSCM(long ModuleNum,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo,BYTE Phase,BYTE ZeroDots,BYTE Item,int status,BYTE Protocol/*����Э��*/,BYTE m_SendAngle/*���͵ĽǶ�*/);
	CString                 StatusStr;
	CString                 StatusStrRead;
	
	//�жϱ��Ƿ����
    BOOL   IsCurveTableExist(CString strTableName);

	//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
	//Str             �����ַ�
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	//BOOL m_CheckReturnValue �Ƿ��ⷵ��ֵ,֤���յ���
	BOOL  SelectSendString(int kinds, CString Str, BOOL CheckConnected,BOOL AppearPrompt,BOOL m_CheckReturnValue);

	//�Զ�������ʱ��
	CTime             m_AutoReadTime;
	int          m_SendGarrisonTimes;

	CIFRMApp*                  Apppt;
	BOOL              CheckRunning();

	//����
	int                      m_times;
	virtual ~CIFRMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CIFRMView)
	afx_msg void OnDestroy();
	
    afx_msg void OnSize(UINT nType, int cx, int cy);
	
	
	
	afx_msg void OnTestreadtable();
	afx_msg void OnBreadorder();
	afx_msg void OnTranformer();
	afx_msg void OnUserinfo();
	afx_msg void OnAmmeterinfo();
	afx_msg void OnCommunication();
	afx_msg void OnStoprun();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOwemoney();
	afx_msg void OnOnCommMscomm();
	
	afx_msg void OnOpenreportfile();
	afx_msg void OnPrice();
	afx_msg void OnDatapass();
	afx_msg void OnUpdateConnectsuccess(CCmdUI* pCmdUI);
	afx_msg void OnStopexam();
	afx_msg void OnAngleset();
	afx_msg void OnPaint();
	afx_msg void OnPhasetest();
	afx_msg void OnConnectionRequestWinsock(long requestID);
	afx_msg void OnDataArrivalWinsock(long bytesTotal);
	afx_msg void OnCloseWinsock();
	afx_msg void OnConnectWinsock();
	afx_msg void OnErrorWinsock(short Number, BSTR FAR* Description, long Scode, LPCTSTR Source, LPCTSTR HelpFile, long HelpContext, BOOL FAR* CancelDisplay);
	afx_msg void OnSendProgressWinsock(long bytesSent, long bytesRemaining);
	afx_msg void OnSendCompleteWinsock();
	afx_msg void OnTimecheck();
	afx_msg void OnUpdateLstSave(CCmdUI* pCmdUI);
	afx_msg void OnAutoreadset();
	afx_msg void OnBREAkSOMEDAY();
	afx_msg void OnUpdateOwemoney(CCmdUI* pCmdUI);
	afx_msg void OnPassuserdata();
	afx_msg void OnUpdatePassuserdata(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowdialogbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePhasetest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTestreadtable(CCmdUI* pCmdUI);
	afx_msg void OnRclickListss(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHidedata(CCmdUI* pCmdUI);
	afx_msg void OnSavereportas();
	afx_msg void OnUpdateSavereportas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemotemodify(CCmdUI* pCmdUI);
	
	
	
	afx_msg void OnUpdateNewreport(CCmdUI* pCmdUI);
	
	afx_msg void OnGetdatafromlong();
	afx_msg void OnLocalmodify();
	afx_msg void OnUpdateLocalmodify(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppearselectdata(CCmdUI* pCmdUI);
	
	afx_msg void OnUpdateBREAkSOMEDAY(CCmdUI* pCmdUI);
	afx_msg void OnReportfont();
	afx_msg void OnUpdateDeletemodule(CCmdUI* pCmdUI);
	afx_msg void OnDeletemodule();
	afx_msg void OnUpdateAngleset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommunication(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDatapass(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAutoreadset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBreadorder(CCmdUI* pCmdUI);
	afx_msg void OnClosereport();
	afx_msg void OnUpdateClosereport(CCmdUI* pCmdUI);
	afx_msg void OnTimesearch();
	afx_msg void OnZhuliumodify();
	afx_msg void OnZhenshimodify();
	afx_msg void OnUpdateTimesearch(CCmdUI* pCmdUI);
	afx_msg void OnGetfile();
	afx_msg void OnUpdateDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnConnectsuccess();
	afx_msg void OnStoporsend();
	afx_msg void OnUpdateStoporsend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDataappear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateListselect(CCmdUI* pCmdUI);
	afx_msg void OnCheckeqaul();
	afx_msg void OnUpdateCheckeqaul(CCmdUI* pCmdUI);
	afx_msg void OnXiangchange();
	afx_msg void OnUpdateXiangchange(CCmdUI* pCmdUI);
	afx_msg void OnChecklinestatus();
	afx_msg void OnUpdateChecklinestatus(CCmdUI* pCmdUI);
	afx_msg void OnFindrepeatrecords();
	afx_msg void OnUpdateFindrepeatrecords(CCmdUI* pCmdUI);
	afx_msg void OnFautoreadset();
	afx_msg void OnUpdateFautoreadset(CCmdUI* pCmdUI);
	afx_msg void OnCancelautozhuliu();
	afx_msg void OnUpdateCancelautozhuliu(CCmdUI* pCmdUI);
	afx_msg void OnChangeammeter();
	afx_msg void OnModifyprotcol();
	afx_msg void OnWxcheckstatus();
	afx_msg void OnWugongparameter();
	afx_msg void OnWugongdeal();
	afx_msg void OnUpdateWugongdeal(CCmdUI* pCmdUI);
	afx_msg void OnDrfromaccess();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
    afx_msg LRESULT OnEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void Check_71485_Protcol(long ModuleNum,BYTE m_order);
	double m_Quick71Value[4];
	CByteArray      m_MotherLineArray;
	CByteArray      m_ProtColArray;
	void  GetSendZhuLiuInformation();

	float         m_QuickGlys[100000];
	long        m_QuickModuleAddress;//���ٶ���ĵ�ַ
	long      m_QuickReadModuleValue;//���ٶ����ֵ
	double   m_QuickReadParameter[3];
	BOOL  TestIfCanQuickReadAmmeter(long module,CString  m_CurrentTime,CString  m_AmmeterType,BYTE m_protcol);
	short GetWGTimeEvery();
	//���е��޹�����һ��
    void ALLWuGongDeal();

	//�ҹ�0���λ��,��10����,��һ��Ϊ���Ļ�,��5����,��5����,k����
    int FindZeroPoint(short m_CollectData[],int m_StartPlace,int k);
    //�ɼ���ͨ������Լ���
    double CorrelationSixChannelCheck(long SourceArray[], long DestArray[],int K);
    //���鵱ǰ�������Ƿ���Ч m_kinds 0 ���Ժ��ϴε�����ȣ�1����=
    BOOL CheckReadValueValid(long m_module,CString m_FieldName,double Currentvalue,CString m_zhutimeValue,BYTE m_kinds);
	//�������ֵ
    int ChangeIValue(BYTE m_Ivale);
	void CheckWireLess();
	CTime m_FirstReadOkTime;
	void InitializeCurrent();
	float  m_AllLineThreeCurrent[128];//��32����·4�ε���
	BYTE   m_All_Line_Current[32];//����·�Ƿ��е�����ֵ 0 û�е��� 1 �е���  2 û�м��
	void   EveryHourCheckLine();
	//��⵱ǰĸ�߳����Ƿ��е���
	//BYTE MotherLine ĸ�߱��
	//BYTE LineNo     ��·���
	BOOL CheckIfHaveCurrentValue(BYTE MotherLine, BYTE LineNo);
	void ByDateSetGarrisonRange(BYTE m_date);
	DWORD         m_Thread_PRIORITY;//�̵߳ļ���
	//ʮ�����ַ�ת����
    int GetHexValue(CString str);
	void ByDateAutoGarrisonTime();
	CString GetZhuLiuRanage(short m_date);
	CString ByDateDecodeParameter();
	BYTE m_zhuliukinds;
	short ByDateCheckCurrentTime();//�����ڼ���Ƿ��Ƿ�פ��
	void  ByDateDingShiDeal();
	BOOL IsDyConnect(CString m_StationName);
	void DingShiDeal();
	BYTE         m_CollectNos;//�������
	BYTE    m_CollectPlace[2];//����λ��
	CString CheckCurrentValue(BYTE MotherLine,BYTE LineNo,BOOL m_SendInfo);
	CString GetFileFolderPass;
	BYTE    m_ReadModuleTimes;
    void DealOverTimeData(int m_Years); //����������ݣ�פ�����У���֮ǰ�����ݣ���ʽ���е�����
	long m_SettimerValues;
	void InitializeGarrionReadRange();
	void SetGarrionLabel();
	void AutoGarrisonTime();
	BYTE GetMaxDays(BYTE m_select);
	short       CheckCurrentTime();
	BOOL ModifyDataTable(CString m_TableName,CString m_TableSql,BOOL m_CheckRecords);
	long    SubCapability(CString SubNo);
	//�õ�ĳ��̨������ܱ�ֵ�������о����ʹ��û���ĺ�
	//CString FieldName       �����ֶ��� TB_Garrison.�й����
	//CString CompanyName     ��˾��
	//CString SubstationName  ���վ��
	//int     SubNo           ��̨��  
	//CString LineName        ��·����
	//CString     SubNo           ��̨��
	//short   kinds           ���� 0����������ı�ֵ 1�����������о�������û���ı��
	double GetSubElc(CString Order,CString CompanyName, CString SubstationName,CString LineName,CString SubNo,short kinds,CString BeginTime,CString EndTime);

	CString m_DingShiString;
	//���õ�������������
    int GetAmmeterImpulse(CString m_AmmeterType);
	//�õ����ֶεĸ���
    short GetFieldNumbers(CString m_DataName);
	BOOL m_StopPassing;
	void AppearAccept(CString m_dataname);
	void AskIfAddData(CString DataName,CString FileName);
	//�õ��ı��ļ���*�е�����
    CString GetDataLineCString(CString FileName,int m_lines);
	//CString m_CondtionString  ����Ҫ���������
	//CString m_TableName       ����Ҫ����ı���
	//int  Start     ��ʼλ
	BOOL   SendRemoteData(CString m_CondtionString, CString m_TableName, int Start);
	void   ReadRemoteTime();
	//����Լ���
    double CorrelationCheck(long SourceArray[], long DestArray[],int m_places);
	//����BCH��
	//m_kinds   0  Bch63_45_3  1 Bch45_27_3  2  Bch31_21_2
    void    Encode_Bch(BYTE g[],BYTE data[],BYTE m_kinds);
	BOOL    m_IsHistory;
	void    OperationAnimation(BOOL m_starting);
	void    ShowGridHead(CString  HeadStr);
	void    AutoAnswer(BOOL  ShowMessage);
	void    ShowDingShiButton(BOOL  IsShowWindows);
	short   Received;//�жν������ݵ�����	1 ��������Ľ��� 2������ϳ�ɳ����ͨѶ
	BOOL    CheckStations(CString m_strsql);
	void    ReplaceUserModuleID(int startNo);
	void    GetPriveteDataFromWs(CString  m_CsvFileName);
	BYTE    HuNanZhaoHuanOrder;
	CString HuNanZhaoHuanTime;
	BOOL    SendHunNanHexData(CString Datatime,BYTE Kinds,int Start,int N);
	//�õ��ı��ļ�����
    int    GetDataLines(CString FileName);
	CString         GetFolder();
//	CString  m_ComeIntoDataName;
	void          RefreshTree();
	BOOL            m_ReceiveOk;
	BOOL      GetDialogBarStr();
	CString      GetStationNo();
	void SendErrorMessage(short kinds);
	CString         m_statusstr;
	void  BinarySystemReceive();//�����Ʒ�ʽ����,ת���ַ���
    void  HuNanWeiYuanReceive();//������Զ�Ľ��ճ���
	void  GetComPorts();
	float SwitchCurrentValue(float DeValue);
	BYTE  ConversionCurrentValue(BYTE Source);
	float ReadDataFrom485Com2(CString m_address,short kinds);
    void  SendMessageToElectricOffice(short kinds);//���ͻ�����Ϣ 0-�ɹ�ִ��,1-�����벻��,2-������
    BOOL  WipeOffSpilthData();                     //������������
	int   m_LocalAddress;
	void  AnalyseReceivedByteArray();              //���͵���ʼλ�ú͸���

	//kinds           ���� 0 ���ڷ��� 1 �绰�κŷ��� 2 TCP/IP����m_sendkind
	//CheckConnected  �Ƿ�Ҫ����   TRUE Ҫ���Ӻ���ܷ��� FALSE ��Ҫ��
	//AppearPrompt    �Ƿ���ʾ��ʾ TRUE ��ʾ��ʾ         FALSE ����ʾ��ʾ
	BOOL  SelectSendCByteArray(int kinds,BOOL CheckConnected,BOOL AppearPrompt);
	void  AnalyseDial(CString str);
	void  AnalyseOrder(CString OrderStr);

    short          m_EveryUnit;
	BYTE            LowAddress; //���վ�͵�ַ
    BYTE           HighAddress; //���վ�ߵ�ַ
    CByteArray     SendByteArray;//�����ֽ����飬�����ֽ�����
	CByteArray  ReceiveByteArray;
	long           m_PassRecords;
	CStatusBar*          pStatus;
	CStringArray      m_StrArray; 
	int                 m_angles;//�Ƕ�ֵ
	void    CarryOutOrders(CString Str);
	void    AddlistItem(CString m_StrArray[], int n);
	BOOL    StopRunning();
	void    WriteListHeading();
	void    SendOfficeBreadorder(int generatrix,int times,int m_iBroadTime,BYTE m_Potocol,CString NewTime);
	CString m_ZhuLiuTime;
	CString GetZhuLiuTime();
	BOOL    DecodeBCH63394(BYTE recd[],BOOL m_Is63394);
	BOOL    DecodeBCH31212(BYTE recd[]);
	int     m_iChSelect;
	BYTE    m_PassValue;
	//long ModuleNo  ģ���
    //int times      �������
    //int mode       д��ģʽ //0 error,1 right
    void    WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode);
	long    m_ListRows;
	CString ReceiveStr;
	BOOL    IsFirstReceived;
	void    RealTimeReceiveData(CString str);
    double  Decode(long ModuleNum,BYTE Protocol,BYTE Item);  //����
	//ȫ����ͨ������,��6�Σ�������������Э��
    double DecodeSixChannel(long ModuleNum,BYTE Protocol,BYTE Item,BYTE m_phase);
	double  GetTestData(long m_Module,CString m_RightTime);//CString m_RightTime ��ʱʱ��
};

#ifndef _DEBUG  // debug version in IFRMView.cpp
inline CIFRMDoc* CIFRMView::GetDocument()
{ return (CIFRMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFRMVIEW_H__20A8C007_F40B_4627_8B95_7233F7C56AE9__INCLUDED_)
