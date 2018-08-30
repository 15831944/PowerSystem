// TAPILine.h: interface for the CTAPILine class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_)
#define AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "global.h"
#include "TAPI.h"


class CTAPILine  
{
	//��ʶ��·�ı���
	DWORD m_nNumLines;
	DWORD m_nCurLineID;

	//TAPI���
	HLINEAPP m_hLineApp;
	DWORD m_nAPIVersions[10];
	DWORD m_lowAPIVersion;
	DWORD m_highAPIVersion;
	LINEEXTENSIONID m_extAPIVersions[10];
	DWORD m_nApplicationVersion;
	DWORD m_nLastTAPIError;
	
//��ʾ�豸���豸���Եı���
	LINEDEVCAPS m_lineCaps;
	CString m_strLineName;
	CString m_strProviderInfo;
	CString m_strSwitchInfo;
	DWORD m_nPermanentLineID;
	DWORD m_nStringFormat;
	DWORD m_numAddresses;
	LONG m_nMediaModes;
	DWORD m_nAddress;
	DWORD m_nMaxDataRate;
	LONG m_nBearerModes;
	LONG m_nAddressModes;
	DWORD m_nGenerateToneMaxNumFreq;
	DWORD m_nGenerateToneModes;
	DWORD m_nNumTerminals;

//����״̬���첽��������״̬����
	HLINE m_hLine;
	HCALL m_hCall;
	DWORD m_nRequestingCall;
	DWORD m_nDroppingCall;
	DWORD m_nReqPrivileges;
	DWORD m_nReqMedialModes;
	
public:
	CTAPILine();
	virtual ~CTAPILine();

//��Ա����
//���ĸ������趨�ͻ�ȡ��߰汾�ź���Ͱ汾��
	void SetLowAPI(DWORD ver);
	DWORD GetLowAPI();
	void SetHighAPI(DWORD ver);
	DWORD GetHighAPI();	
//��ȡ��ǰ��TAPI��·��ֵ�����ṩ������ģ��ʹ��
	DWORD GetNumLines();
	
//��ȡ���趨��ǰTAPI��·
	DWORD GetCurrentLineID();
	void SetCurrentLineID(DWORD id);

//��ȡ��·��Ϣ�е�����
	CString GetLineName();
	CString GetProviderInfo();
	CString GetSwitchInfo();
	CString GetLineErrString(DWORD lErrCode);

	DWORD GetPermanentLineID();
	DWORD GetStringFormat();
	DWORD GetNumAddress();
	DWORD GetmaxDataRate();
	LONG GetBearerModes();
	LONG GetAddressModes();
	LONG GetMediaModes();
	DWORD GetGenerateToneMaxNumFreq();
	DWORD GetGenerateToneModes();
	DWORD GetNumTerminals();
	BOOL GetLineSupportsVoice();

	DWORD GetNegoAPIVersion();
	DWORD GetExtAPIID0();
	DWORD GetExtAPIID1();
	DWORD GetExtAPIID2();
	DWORD GetExtAPIID3();

//�Դ�������ṩ���ش�����Ϣ�ַ���	
	DWORD GetLasterror();
	CString ErrorString(DWORD errCode);

//��������
	BOOL Create();

//����·��Ϣ����
	BOOL OpenLine(DWORD nPrivileges = LINECALLPRIVILEGE_NONE, DWORD nMediaModes = LINEMEDIAMODE_INTERACTIVEVOICE);
//�����첽���еĺ���
	BOOL MakeCallAsynch(CString strPhoneNumbers = "");
//�첽�Ҷϵ绰�ĺ���
	BOOL DropCallAsynch();
//�ر���·�ĺ���
	BOOL CloseLine();
//��·���õĺ������ú���������·���öԻ���
	BOOL ConfigDialog(HWND hWnd = NULL, CString strDeviceClass = "");
//�������õĺ������ú������ò������öԻ���
	BOOL DialoingPropertiesDialog(HWND hWnd, CString strPhoneNumber);
//�ص�������������·��Ϣ��״̬�ı���Ϣ
	static void FAR PASCAL LineCallbackProc(DWORD dwDevice, DWORD dwMsg, DWORD dwCallbackInstance, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);
//�����·״̬�ַ���
	CString GetLineStateString(DWORD state);
	
//˽�г�Ա����
private:
//��ȡ��·��Ϣ
	BOOL GetLineDevCaps();	
};

#endif // !defined(AFX_TAPILINE_H__378FA136_FC63_4D63_87AE_CA6F56D70764__INCLUDED_)


