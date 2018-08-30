// TTTView.h : interface of the CTTTView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_TTTVIEW_H__393422BA_FA7C_426F_9691_DA615699BFAB__INCLUDED_)
#define AFX_TTTVIEW_H__393422BA_FA7C_426F_9691_DA615699BFAB__INCLUDED_

#include <math.h>
#include <direct.h>

#include "DisplayWaveWin.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dask.h"
//#include "MainFrm.h"
#include "TTTDoc.h"

#define WM_EVENT WM_USER+7
#define WM_NUMBERS   81


class CTTTView : public CFormView
{
protected: // create from serialization only
	CTTTView();
	DECLARE_DYNCREATE(CTTTView)

public:
	//{{AFX_DATA(CTTTView)
	enum { IDD = IDD_TTT_FORM };
	CComboBox	m_ordercombo;
	CComboBox	m_SmprateComb;
	CComboBox	m_ProtocolControl;
	CComboBox	m_comcheck;
	CComboBox	m_comdata;
	CComboBox	m_comstop;
	CComboBox	m_combobit;
	CComboBox	m_comboport;
	CSpinButtonCtrl	m_SpinAverage;
	CSpinButtonCtrl	m_Spinstart;
	CSpinButtonCtrl	m_spin4;
	CSpinButtonCtrl	m_spin3;
	int		m_iSampleRate;
	BOOL	m_bCh0;
	BOOL	m_bCh1;
	BOOL	m_bCh2;
	BOOL	m_bCh3;
	BOOL	m_bCh4;
	BOOL	m_bCh5;	
	BOOL	m_bCh8;
	BOOL	m_bCh9;
	BOOL	m_bCh10;
	int  	m_nStartPoint;
	UINT	m_nCycleNum;
	int		m_iCycleNum;
	int		m_iModeSel;
	float	m_fGain;
	float	m_fGainSampleWin;
	int		m_iChSelect;
	BOOL	m_bDiff2;
	BOOL	m_bAver4;
	BOOL	m_bDiffI;
	BOOL	m_bBandPass;
	BYTE	m_generatrix;
	BYTE	m_phase;
	long	m_module;
	CString	m_data;
	BOOL	m_tong789;
	CString	m_SendOrder;
	CString	m_ReceiveStr;
	BOOL	m_addone;
	BOOL	m_IfWriteToLog;
	BOOL	m_qzhikiu;
	BOOL	m_bDiff3;
	BOOL	m_findpipeimax;
	int		m_radio;
	BOOL	m_quancai;
	BOOL	m_AllAdd;
	int		m_alltimes;
	CMSComm	m_Com;
	int		m_delay;
	int		m_angle;
	BYTE	m_derrors;
	BOOL	m_check4bit;
	BOOL	m_xinjiaobian;
	BOOL	m_Is0Station;
	float	m_fCurrentGainSampleWin;
	BOOL	m_equal;
	int		m_millondseconds;
	//}}AFX_DATA

// Attributes
public:
	CTTTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTTView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SurrenderWindowMessage();
	//ȫ�����������������,�ɼ���ͨ��
    void ReadSixChannelMeter();
	double CorrelationSixChannelCheck(long SourceArray[], long DestArray[],int K);
	int FindZeroPoint(short m_CollectData[],int m_StartPlace,int k);
	double DecodeSixChannel(long ModuleNum,BYTE Protocol,BYTE Item,BYTE m_phase);
	float       g_Extend;
	int        PointsNum;
	float         g_Gain;
	int    BandPassAngle;
	int   	m_startpoint;
	int     m_wavepoints;
	short m_ppwave[2048];
	short m_ppAllWave[10000];
	int  m_maxDecimalVal;//���ֵ        1��PCI-9111DR 4096     2��PCI-9111HR 65536 
	BOOL m_Stopping;
	void ContinueRead();
	void ReadBCHMeter();
	void ReadMeter();
	BOOL DecodeBCH45273(BYTE recd[]);
	//����BCH��63��45��3
    void Encode_Bch_63_45_3(BYTE g[],BYTE data[]);
	//����BCH��31��21��2
    void Encode_Bch_31_21_2(BYTE g[],BYTE data[]);
	//����BCH��45��27��3
    void Encode_Bch_45_27_3(BYTE g[],BYTE data[]);
	void WriteToTxtFile(CString FileName,unsigned short DataBuf[],int length);
	void Delay();
	int  FindZeroPointCao(UINT WaveNum);
	int  FindCyclePointsNum(int WaveNum);
    BOOL SendOrderToSCM(long ModuleNum/*ģ���*/,BYTE StationNo/*�����ֵ�վ��*/,BYTE MotherLine/*ĸ��*/,BYTE LineNo/*�ߺ�*/, BYTE Phase/*��ѡ��0A 1B 2C*/, BYTE ZeroDots/* ��ʱ��0����*/,BYTE Item/* Ҫʲô����,������*/,int status/*�ɷ�ʱ�����������*/);
	BOOL DecodeBCH63394(BYTE recd[]);
	void WriteToLog(CString Str);
	BOOL bFlash,bRight,bError,bRight1,bError1;
	int  Channel;
	int  m_iBandPassPoints;
	//��ȡ�Ƕ�
	//short generatrixno ĸ�߱��
	//short phase  ��� 0 A�� 1 B�� 2 C��
	void ReadThreePhaseAngle(short generatrixno,int phase,BYTE kinds);
	//���ýǶ�
	//short generatrixno ĸ�߱��
	//short phase        ��� 0 A�� 1 B�� 2 C��
	//int   angles       �Ƕ�
	//BYTE  kinds  ���� 0--�ź�ǿ�� 1��ƫ�ƽǶ�
    void SetPhaseAngle(short generatrixno,short phase, int angles,BYTE  kinds);
	//long ModuleNo  ģ���
	//int times      �������
	//int mode       д��ģʽ //0 error,1 right
	void WriteDataToModuleNoTxtFile(long ModuleNo,int times,int mode);
    BYTE CycleNum,SendVal;
	int MaxCycleNum,MaxPointsNum;
	int MinSum;
	int Line;
	UINT m_nTimer;
	CFile file;
	short m_angles;
	BOOL m_ShowWave;
	void   WriteP9111_CHANNEL_DOPort(int value);
	BOOL   PcSendToSCM(BYTE ORDER[]);
   	virtual ~CTTTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTTTView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnSelchangeComboSmprate();
	afx_msg void OnCheckCh3();
	afx_msg void OnCheckCh0();
	afx_msg void OnCheckCh1();
	afx_msg void OnCheckCh2();
	afx_msg void OnCheckCh4();
	afx_msg void OnCheckCh5();
	afx_msg void OnButtonUpdate();
	afx_msg void OnChangeEditStartpoint();
	afx_msg void OnSelchangeComboCyclenum();
	afx_msg void OnChangeEditGain();
	afx_msg void OnRadioRealtime();
	afx_msg void OnRadioAnalyze();
	afx_msg void OnButtonShiftleft();
	afx_msg void OnButtonShiftright();
	afx_msg void OnButtonAshiftleft();
	afx_msg void OnButtonAshiftright();
	afx_msg void OnChangeEditGainsmpwin();
	afx_msg void OnSelchangeComboChselect();
	afx_msg void OnButtonLoad();
	afx_msg void OnCheckDiff();
	afx_msg void OnCheckAver4();
	afx_msg void OnCheckDiffi();
	afx_msg void OnChangeEditAngle();
	afx_msg void OnChangeEditThreshold();
	afx_msg void OnChangeEditSendcode();
	afx_msg void OnCheckCh10();
	afx_msg void OnCheckCh9();
	afx_msg void OnCheckCh8();
	afx_msg void OnCheckBandPass();
	afx_msg void OnChangeEditBandpassangle();
	afx_msg void OnCheckDvdt();
	afx_msg void OnLoad();
	afx_msg void OnRealStart();
	afx_msg void OnRealstop();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonAngle();
	afx_msg void OnRealRecord();
	afx_msg void OnRealSend();
	afx_msg void OnButtonStoprec();
	afx_msg void OnReadline();
	afx_msg void OnSelchangeProtocols();
	afx_msg void OnSend();
	afx_msg void OnSettimer();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnCheck10();
	afx_msg void OnZhongzhi();
	afx_msg void OnDecode();
	afx_msg void OnFft();
	afx_msg void OnReadfilter();
	afx_msg void OnDeletefile();
	afx_msg void OnOpenfile();
	afx_msg void OnBchtest();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnCheckDiffi2();
	afx_msg void OnCheckDiffi3();
	afx_msg void OnRadio3();
	afx_msg void OnCheck9();
	afx_msg void OnTestdata();
	afx_msg void OnChangeStartpoint();
	afx_msg void OnChangeWavepoints();
	afx_msg void OnCheck11();
	afx_msg void OnOutofmemorySpinstart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinstart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinaverage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFindzero();
	afx_msg void OnAlladd();
	afx_msg void OnChangeAlltimes();
	afx_msg void OnInitialize();
	afx_msg void OnComset();
	afx_msg void OnChangeAngle();
	afx_msg void OnCheck12();
	afx_msg void OnChangeusedata();
	afx_msg void OnSendallone();
	afx_msg void OnButtonTestphase();
	afx_msg void OnChangeEditCurrentgainsmpwin();
	afx_msg void OnSelchangeOrdercombo();
	afx_msg void OnButton1();
	//}}AFX_MSG
    afx_msg void OnEvent(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	void InitOrderCombo(short m_protcols);
	int m_TimeSeconds;
	int ChangeIValue(BYTE  m_Ivale);
	void SendAllOne();
	BYTE      m_CollectNos;
	BYTE m_CollectPlace[2];
	//31-21-2
    BOOL DecodeBCH31212(BYTE recd[]);
	//����BCH��
	//long ModuleNum   ģ���
	//BYTE StationNo   �����ֵ�վ��
	//BYTE MotherLine  ĸ��
	//BYTE LineNo      �ߺ�
	//BYTE Phase       ��ѡ��0A 1B 2C
	//BYTE ZeroDots    ��ʱ��0����
	//BYTE Item        Ҫʲô����,������
	//int status       �ɷ�ʱ�����������
	void ComeIntoBch70(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status);
		//����BCH��
	//long ModuleNum   ģ���
	//BYTE StationNo   �����ֵ�վ��
	//BYTE MotherLine  ĸ��
	//BYTE LineNo      �ߺ�
	//BYTE Phase       ��ѡ��0A 1B 2C
	//BYTE ZeroDots    ��ʱ��0����
	//BYTE Item        Ҫʲô����,������
	//int status       �ɷ�ʱ�����������
	void ComeIntoBch60(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status);

	//����BCH��
	//long ModuleNum   ģ���
	//BYTE StationNo   �����ֵ�վ��
	//BYTE MotherLine  ĸ��
	//BYTE LineNo      �ߺ�
	//BYTE Phase       ��ѡ��0A 1B 2C
	//BYTE ZeroDots    ��ʱ��0����
	//BYTE Item        Ҫʲô����,������
	//int status       �ɷ�ʱ�����������
	void ComeIntoBch20(long ModuleNum,BYTE StationNo,BYTE MotherLine,BYTE LineNo, BYTE Phase,BYTE ZeroDots,BYTE Item,int status);
	void CheckComData();
	CByteArray     SendByteArray;//�����ֽ����飬�����ֽ�����
	void SendByteArrayToCom();
	CString m_StatusStr;
	//״̬������ʾ��Ϣ
    void  status(CString strname);
    //����м����˿�����
    void GetComPorts();
	/***************************************************************
	��  �� 0-COM1  ,1-COM2   ,2-COM3   ,3-COM4 ,4-COM5 ,5-COM6
	������ 0-600   ,1-1200   ,2-2400   ,3-4800 ,4-9600 ,5-14400,6-19200,7-28800,8-38400,9-56000
	����λ 0-��У��,1����У��,2��żУ��
	����λ 0-4     ,1-5      ,2-6      ,3-7    ,4-8
	ֹͣλ 0-1     ,1-1.5    ,2-2
	//HexSend  TRUE  �����Ʒ�ʽ���� FALSE �ı���ʽ����
	****************************************************************/
    void   OptionClick(int ComIndex,int SpeedIndex,int CheckIndex,int DataIndex,int StopIndex);
	void AllWaveAdd();
	double Decode();
	short GetFileEveryDataLength(CString filename);
	short  GetMedianNum(short bArray[], int iFilterLen);
	double CorrelationCheck(short SourceArray[],short DestArray[],int m,short m_places);
	//pr[n]���������ʵ��
	//pi[n]����������鲿
	//n��k��������n=2^k
	//fr[n]���������ʵ��
	//fi[n]����������鲿
	//l����0 FFT��1 IFFT
	//il����0 �����ʵ��/�鲿��1 �����ģ/����
	void  kkfft(double pr[],double pi[],int n,int k,double fr[],double fi[],int l,int il);
	//re ��ʵ�� ��im���鲿����ll=1�����任����ll=-1�����任��nn:2���ݣ�
    void  fftnew(double *re, double *im, int nn, int ll);
	BOOL  FFT(double * data, unsigned long nn[], int ndim, int isign);
	long  m_SuccessTimes;
   	long  m_TotalTimes;
	long  m_CollectErrors;
	int   GetHexValue(CString str);
	short m_CollectChannels;
	short m_Channels;
	int	  m_protocol;
	
	//�Ⱦ�ڵ��������ƽ��
    //n-���ͱ���������ĵ�����Ҫ��n>=5
    //y-����Ϊn�����飬���n���Ⱦ�۲���ϵĹ۲�����
    //yy-����Ϊn�����飬����ʱ���ƽ�����
    void kkspt(int n,double y[],double yy[]);
};

#ifndef _DEBUG  // debug version in TTTView.cpp
inline CTTTDoc* CTTTView::GetDocument()
   { return (CTTTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTTVIEW_H__393422BA_FA7C_426F_9691_DA615699BFAB__INCLUDED_)
