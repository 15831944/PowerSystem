// TAPILine.cpp: implementation of the CTAPILine class.
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"


#include "TAPILine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTAPILine* myTAPILine;

#define TAPI_SUCCESS 0

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//��ʼ�������ʱ����ҪЭ�̵���߰汾��Ϊ3.0����Ͱ汾��Ϊ1.3
CTAPILine::CTAPILine()
{
	m_lowAPIVersion = 0x00010003;
	m_highAPIVersion = 0x00030000;
	m_nCurLineID = 0;
	m_hLine = 0;
	m_nApplicationVersion = 0;
	myTAPILine = this;
}

//�ر���·
CTAPILine::~CTAPILine()
{
	if(m_hCall != 0)
	{
		lineDeallocateCall(m_hCall);
		m_hCall = 0;
	}
	
	if(m_hCall != 0)
		CloseLine();

	if(m_hLineApp != 0)
	{
		lineShutdown(m_hLineApp);
		m_hLineApp = 0;	
	}
}

//���ĸ������趨�ͻ�ȡ��߰汾�ź���Ͱ汾��
DWORD CTAPILine::GetLowAPI()
{
	return m_lowAPIVersion;
}

void CTAPILine::SetLowAPI(DWORD ver)
{
	m_lowAPIVersion = ver;
}

DWORD CTAPILine::GetHighAPI()
{
	return m_highAPIVersion;
}

void CTAPILine::SetHighAPI(DWORD ver)
{
	m_highAPIVersion = ver;
}

//��ȡ��ǰ��TAPI��·��ֵ�����ṩ������ģ��ʹ��
DWORD CTAPILine::GetNumLines()
{
	return m_nNumLines;
}

//��ȡ���趨��ǰTAPI��·
DWORD CTAPILine::GetCurrentLineID()
{
	return m_nCurLineID;
}

void CTAPILine::SetCurrentLineID(DWORD id)
{
	if(id >= 0 && id < m_nNumLines)
		m_nCurLineID = id;
	GetLineDevCaps();
}

//��ȡ��·��Ϣ�е�����
CString CTAPILine::GetLineName()
{
	return m_strLineName;	
}

CString CTAPILine::GetProviderInfo()
{
	return m_strProviderInfo;
}

CString CTAPILine::GetSwitchInfo()
{
	return m_strSwitchInfo;
}

DWORD CTAPILine::GetPermanentLineID()
{
	return m_nPermanentLineID;
}

DWORD CTAPILine::GetStringFormat()
{
	return m_nStringFormat;
}

DWORD CTAPILine::GetNumAddress()
{
	return m_numAddresses;
}

DWORD CTAPILine::GetmaxDataRate()
{
	return m_nMaxDataRate; 
}

LONG CTAPILine::GetBearerModes()
{
	return m_nBearerModes;
}

LONG CTAPILine::GetAddressModes()
{
	return m_nAddressModes;
}

LONG CTAPILine::GetMediaModes()
{
	return m_nMediaModes;
}

DWORD CTAPILine::GetGenerateToneMaxNumFreq()
{
	return m_nGenerateToneMaxNumFreq;
}

DWORD CTAPILine::GetGenerateToneModes()
{
	return m_nGenerateToneModes;
}

DWORD CTAPILine::GetNumTerminals()
{
	return m_nNumTerminals;
}

BOOL CTAPILine::GetLineSupportsVoice()
{
	BOOL bLineSupportsVoice = FALSE;
	if(m_nBearerModes & LINEBEARERMODE_VOICE)	
	{
		if(m_nMediaModes & LINEMEDIAMODE_INTERACTIVEVOICE)	
			bLineSupportsVoice = TRUE;
	}
	return bLineSupportsVoice;
}

DWORD CTAPILine::GetNegoAPIVersion()
{
	return m_nAPIVersions[m_nCurLineID];	
}

DWORD CTAPILine::GetExtAPIID0()
{
	return m_extAPIVersions[m_nCurLineID].dwExtensionID0;
}

DWORD CTAPILine::GetExtAPIID1()
{
	return m_extAPIVersions[m_nCurLineID].dwExtensionID1;
}

DWORD CTAPILine::GetExtAPIID2()
{
	return m_extAPIVersions[m_nCurLineID].dwExtensionID2;
}

DWORD CTAPILine::GetExtAPIID3()
{
	return m_extAPIVersions[m_nCurLineID].dwExtensionID3;
}

//�Դ�������ṩ���ش�����Ϣ�ַ���
DWORD CTAPILine::GetLasterror()
{
	DWORD lastError;
	lastError = m_nLastTAPIError;
	//���ô����ʶ
	m_nLastTAPIError = 0;
	return lastError;
}

CString CTAPILine::ErrorString(DWORD errCode)
{
	CString strError;
	strError = GetLineErrString(errCode);
	return strError;
}

//��������
BOOL CTAPILine::Create()
{
	DWORD rc, line;
	LINEINITIALIZEEXPARAMS lip;
	LINEEXTENSIONID lxid;

	CString strTitle = _T("�绰API����");
	
	//��ʼ������
	lip.dwTotalSize = sizeof(lip);
	lip.dwOptions = LINEINITIALIZEEXOPTION_USEHIDDENWINDOW;
	
	//��ʼ��TAPI��·�Լ�����TAPI���
	rc = lineInitializeEx(&m_hLineApp, AfxGetApp()->m_hInstance, LineCallbackProc, 
		strTitle, &m_nNumLines, &m_highAPIVersion, &lip);

	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}
	else
	{
		//�������߼���·
		if(m_nNumLines > 0)
		{
			//Ϊÿһ��TAPI��·���а汾Э��
			for(line = 0; line < m_nNumLines; line++)
			{
				rc = lineNegotiateAPIVersion(m_hLineApp, line, m_lowAPIVersion, 
					m_highAPIVersion, &m_nAPIVersions[line], &lxid);

				//û�к���API�汾
				if(rc != TAPI_SUCCESS)
				{
					m_nAPIVersions[line] = 0;
					rc = 0;
				}
				else
				{
					m_extAPIVersions[line].dwExtensionID0 = lxid.dwExtensionID0;
					m_extAPIVersions[line].dwExtensionID1 = lxid.dwExtensionID1;
					m_extAPIVersions[line].dwExtensionID2 = lxid.dwExtensionID2;
					m_extAPIVersions[line].dwExtensionID3 = lxid.dwExtensionID3;
					
					if(m_nAPIVersions[line] > m_nApplicationVersion)
						m_nApplicationVersion = m_nAPIVersions[line];
				}
			}
		}
		else
			return FALSE;
	}

	rc = GetLineDevCaps();
	return TRUE;
}

//����·��Ϣ����
BOOL CTAPILine::OpenLine(DWORD nPrivileges, 
						 DWORD nMediaModes)
{
//���������Ч�����ش���·ʧ�ܺ���
	if(m_hLine != 0)
	{
		return FALSE;
	}

	DWORD rc;
	
//�򿪵�ǰ��·
	rc = lineOpen(m_hLineApp, 
		m_nCurLineID, 
		&m_hLine, 
		m_nAPIVersions[m_nCurLineID], 
		0,
		0, 
		nPrivileges, 
		nMediaModes, 
		NULL);

//�����·��ʧ�ܣ���������ʶ�����򣬷�����·�򿪳ɹ���־
	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}
	return TRUE;
}

//�����첽���еĺ���
BOOL CTAPILine::MakeCallAsynch(CString strPhoneNumbers)
{
	DWORD rc;
	
	if(m_hLine == 0)
		return FALSE;

	//������к���Ϊ�գ�ʵ���ϴ򿪺��о����������ʵ�ʵĺ���
	if(strPhoneNumbers == "")
		rc = lineMakeCall(m_hLine, &m_hCall, "", 0, NULL);
	//����һ������
	else
		rc = lineMakeCall(m_hLine, &m_hCall, strPhoneNumbers, 0, NULL);

	if(rc > 0)
	{
		//������н����������LINE_REPLY�н��ᷴӳ����
		//��¼��ǰ������ID
		m_nRequestingCall = rc;
	}
	else
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}

	return TRUE;
}

//�첽�Ҷϵ绰�ĺ���
BOOL CTAPILine::DropCallAsynch()
{
	DWORD rc;
	
	if(m_hCall == 0)
	{
		return FALSE;
	}

	rc = lineDrop(m_hCall, "", 0);

	if(rc > 0)
		m_nDroppingCall = rc;
	else
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}
	return TRUE;
}

//�ر���·�ĺ���
BOOL CTAPILine::CloseLine()
{
	DWORD rc;

	if(m_hLine == 0)
	{
		return FALSE;
	}
	
	//�ر���·
	rc = lineClose(m_hLine);

	//��·�����Ч
	m_hLine = 0;

	//��¼����
	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}
	return TRUE;
}
//��·���õĺ������ú���������·���öԻ���
BOOL CTAPILine::ConfigDialog(HWND hWnd, CString strDeviceClass)
{
	DWORD rc;

	if(strDeviceClass == "")
		rc = lineConfigDialog(m_nCurLineID, hWnd, "");
	else
		rc = lineConfigDialog(m_nCurLineID, hWnd, strDeviceClass);

	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}

	//��ʶ�ɹ�
	return TRUE;
}

//�������õĺ������ú������ò������öԻ���
BOOL CTAPILine::DialoingPropertiesDialog(HWND hWnd, CString strPhoneNumber)
{
	DWORD rc;

	if(strPhoneNumber == "")
		rc = lineTranslateDialog(m_hLineApp, m_nCurLineID, m_nApplicationVersion, hWnd, "");
	else
		rc = lineTranslateDialog(m_hLineApp, m_nCurLineID, m_nApplicationVersion, hWnd, strPhoneNumber);

	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}

	return TRUE;
}

//��ȡ��·��Ϣ
BOOL CTAPILine::GetLineDevCaps()	
{
	DWORD rc;
	CString strRef;
	LPBYTE buffer = new BYTE[1000];
	
	LPLINEDEVCAPS lpDevCaps = (LPLINEDEVCAPS)buffer;
	lpDevCaps->dwTotalSize = 1000 * sizeof(BYTE);

	rc = lineGetDevCaps(m_hLineApp, m_nCurLineID, m_nAPIVersions[m_nCurLineID],
		0, lpDevCaps);

	if(rc != TAPI_SUCCESS)
	{
		m_nLastTAPIError = rc;
		return FALSE;
	}

	//����Ϣ�����뵱ǰ���ж���ı���
	if(lpDevCaps->dwLineNameSize != 0)
		m_strLineName = (LPCSTR)(buffer + lpDevCaps->dwLineNameOffset);
	else
		m_strLineName = _T("");

	if(lpDevCaps->dwProviderInfoSize != 0)
		m_strProviderInfo = (LPCSTR)(buffer + lpDevCaps->dwProviderInfoOffset);
	else
		m_strProviderInfo = _T("");
	 
	if(lpDevCaps->dwSwitchInfoSize != 0)
		m_strSwitchInfo = (LPCSTR)(buffer + lpDevCaps->dwSwitchInfoOffset);
	else
		m_strSwitchInfo = _T("");
	 
	m_nPermanentLineID = lpDevCaps->dwPermanentLineID;
	m_nStringFormat = lpDevCaps->dwStringFormat;
	m_numAddresses = lpDevCaps->dwNumAddresses;
	m_nMaxDataRate = lpDevCaps->dwMaxRate;
	m_nBearerModes = lpDevCaps->dwBearerModes;
	m_nAddressModes = lpDevCaps->dwAddressModes;
	m_nMediaModes = lpDevCaps->dwMediaModes;	
	m_nGenerateToneMaxNumFreq = lpDevCaps->dwGenerateToneMaxNumFreq;
	m_nGenerateToneModes = lpDevCaps->dwGenerateToneModes;
	m_nNumTerminals = lpDevCaps->dwNumTerminals;

	return TRUE;
}

CString CTAPILine::GetLineErrString(DWORD lErrCode)
{
	CString strErrorMsg;
	switch(lErrCode)
	{
	case LINEERR_ALLOCATED: //( = &H80000001)
            strErrorMsg = _T("��Ҫ�����Դ���紮�пڣ��Ѿ��������һ��������");
			break;
	case LINEERR_BADDEVICEID: //(= &H80000002)
            strErrorMsg = _T("ָ�����豸ID������Χ");
			break;
	case LINEERR_BEARERMODEUNAVAIL: //(= &H80000003)
            strErrorMsg = _T("ָ����ģʽ������Χ");
			break;
	case LINEERR_CALLUNAVAIL: //(= &H80000005)
            strErrorMsg = _T("�������ַĿǰû�п��õĺ��г���");
			break;
	case LINEERR_COMPLETIONOVERRUN: //(= &H80000006)
            strErrorMsg = _T("Completion Overrun");
			break;
	case LINEERR_CONFERENCEFULL: //(= &H80000007)
            strErrorMsg = _T("Conference Full");
			break;
	case LINEERR_DIALBILLING: //(= &H80000008
            strErrorMsg = _T("�����ṩ�߲�֧�ֵȴ����ѵ���Ƶ$");
			break;
	case LINEERR_DIALDIALTONE: //(= &H80000009)
            strErrorMsg = _T("�����ṩ�߲�֧�ֵȴ����ŵ���ƵW");
			break;
	case LINEERR_DIALPROMPT: //(= &H8000000A)
            strErrorMsg = _T("�����ṩ�߲�֧�ֵȴ���ʾ����");
			break;
	case LINEERR_DIALQUIET: //(= &H8000000B)
            strErrorMsg = _T("�����ṩ�߲�֧�ֵȴ���Ĭ@");
			break;
	case LINEERR_INCOMPATIBLEAPIVERSION: //(= &H8000000C)
            strErrorMsg = _T("ָ���İ汾�Ų�����");
			break;
	case LINEERR_INCOMPATIBLEEXTVERSION: //(= &H8000000D
            strErrorMsg = _T("ָ������չ�Ų�����");
			break;
	case LINEERR_INIFILECORRUPT://(= &H8000000E)
            strErrorMsg = _T("��ʼ���ļ�����");
			break;
	case LINEERR_INUSE: //(= &H8000000F)
            strErrorMsg = _T("ָ������·����ʹ��");
			break;
	case LINEERR_INVALADDRESS: //(= &H80000010)
            strErrorMsg = _T("ָ���ĵ�ַ������Ч�ַ�");
			break;
	case LINEERR_INVALADDRESSID: //(= &H80000011)
            strErrorMsg = _T("ָ���ĵ�ַ������Χ");
			break;
	case LINEERR_INVALADDRESSMODE: //(= &H80000012)
            strErrorMsg = _T("��Ч�ĵ�ַģʽ");
			break;
    case LINEERR_INVALADDRESSSTATE: //(= &H80000013)
            strErrorMsg = _T("��Ч�ĵ�ַ״̬");
			break;
	case LINEERR_INVALAPPHANDLE: //(= &H80000014)
            strErrorMsg = _T("ָ����Ӧ�ó�����ʧ��Ч��");
			break;
	case LINEERR_INVALAPPNAME: //(= &H80000015)
            strErrorMsg = _T("Invalid App Name");
			break;
	case LINEERR_INVALBEARERMODE: //(= &H80000016)
            strErrorMsg = _T("Invalid Bearer Mode");
			break;
	case LINEERR_INVALCALLCOMPLMODE: //(= &H80000017)
            strErrorMsg = _T("Invalid Call Completion Mode");
			break;
	case LINEERR_INVALCALLHANDLE: //(= &H80000018)
            strErrorMsg = _T("Invalid Call Handle");
			break;
	case LINEERR_INVALCALLPARAMS: //(= &H80000019)
		     strErrorMsg = _T("Invalid Call Params");
			 break;
	case LINEERR_INVALCALLPRIVILEGE: //(= &H8000001A)
            strErrorMsg = _T("Invalid Call Privilege");
			break;
	case LINEERR_INVALCALLSELECT: //(= &H8000001B)
            strErrorMsg = _T("Invalid Call Select");
			break;
	case LINEERR_INVALCALLSTATE: //(= &H8000001C)
            strErrorMsg = _T("ָ���ĺ��ж���������˵δ������ȷ�غ���״̬");
			break;
	case LINEERR_INVALCALLSTATELIST: //(= &H8000001D)
            strErrorMsg = _T("Invalid Call State List");
			break;
	case LINEERR_INVALCARD: //(= &H8000001E)
            strErrorMsg = _T("Invalid Card");
			break;
	case LINEERR_INVALCOMPLETIONID: //(= &H8000001F)
            strErrorMsg = _T("Invalid Completion ID");
			break;
	case LINEERR_INVALCONFCALLHANDLE: //(= &H80000020)
            strErrorMsg = _T("Invalid Conf Call Handle");
			break;
	case LINEERR_INVALCONSULTCALLHANDLE: //(= &H80000021)
            strErrorMsg = _T("Invalid Consult Call Handle");
			break;
	case LINEERR_INVALCOUNTRYCODE: //(= &H80000022)
            strErrorMsg = _T("ָ���Ĺ��Ҵ�������Ч��");
			break;
	case LINEERR_INVALDEVICECLASS: //(= &H80000023)
            strErrorMsg = _T("Invalid Device Class");
			break;
	case LINEERR_INVALDEVICEHANDLE: //(= &H80000024)
            strErrorMsg = _T("Invalid Device Handle");
			break;
	case LINEERR_INVALDIGITLIST: //(= &H80000026)
            strErrorMsg = _T("Invalid Digit List");
			break;
	case LINEERR_INVALDIGITMODE: //(= &H80000027)
		    strErrorMsg = _T("Invalid Digit Mode");
			break;
	case LINEERR_INVALDIGITS: //(= &H80000028)
            strErrorMsg = _T("Invalid Digits");
			break;
	case LINEERR_INVALEXTVERSION: //(= &H80000029)
            strErrorMsg = _T("Invalid Ext Version");
			break;
	case LINEERR_INVALGROUPID: //(= &H8000002A)
            strErrorMsg = _T("Invalid Group ID");
			break;
	case LINEERR_INVALLINEHANDLE: //(= &H8000002B)
            strErrorMsg = _T("ָ������·�����Ч");
			break;
	case LINEERR_INVALLINESTATE: //(= &H8000002C)
            strErrorMsg = _T("Invalid Line State");
			break;
	case LINEERR_INVALLOCATION: //(= &H8000002D)
            strErrorMsg = _T("Invalid Location");
			break;
	case LINEERR_INVALMEDIALIST: //(= &H8000002E)
            strErrorMsg = _T("Invalid Media List");
			break;
	case LINEERR_INVALMEDIAMODE: //(= &H8000002F)
            strErrorMsg = _T("ָ����ý��ģʽ��Ч");
			break;
	case LINEERR_INVALMESSAGEID: //(= &H80000030)
            strErrorMsg = _T("Invalid Message ID");
			break;
	case LINEERR_INVALPARAM: //(= &H80000032)
            strErrorMsg = _T("��һ�������ѱ�ȷ��Ϊ��Ч��");
			break;
	case LINEERR_INVALPARKID: //(= &H80000033)
            strErrorMsg = _T("Invalid Park ID");
			break;
	case LINEERR_INVALPARKMODE: //(= &H80000034)
            strErrorMsg = _T("Invalid Park Mode");
			break;
	case LINEERR_INVALPOINTER: //(= &H80000035)
            strErrorMsg = _T("ָ��û������һ����Ч���ڴ�λ��");
			break;
	case LINEERR_INVALPRIVSELECT: //(= &H80000036)
            strErrorMsg = _T("Invalid Priv Select");
			break;
	case LINEERR_INVALRATE: //(= &H80000037)
            strErrorMsg = _T("Invalid Rate");
			break;
	case LINEERR_INVALREQUESTMODE: //(= &H80000038
            strErrorMsg = _T("Invalid Request Mode");
			break;
	case LINEERR_INVALTERMINALID: //(= &H80000039
            strErrorMsg = _T("Invalid Terminal ID");
			break;
	case LINEERR_INVALTERMINALMODE: //(= &H8000003A)
            strErrorMsg = _T("Invalid Terminal Mode");
			break;
	case LINEERR_INVALTIMEOUT: //(= &H8000003B)
            strErrorMsg = _T("Invalid Time Out");
			break;
	case LINEERR_INVALTONE: //(= &H8000003C)
            strErrorMsg = _T("Invalid Tone");
			break;
	case LINEERR_INVALTONELIST: //(= &H8000003D)
            strErrorMsg = _T("Invalid Tone List");
			break;
	case LINEERR_INVALTONEMODE: //(= &H8000003E)
            strErrorMsg = _T("Invalid Tone Mode");
			break;
	case LINEERR_INVALTRANSFERMODE: //(= &H8000003F)
            strErrorMsg = _T("Invalid Transfer Mode");
			break;
	case LINEERR_LINEMAPPERFAILED: //(= &H80000040)
            strErrorMsg = _T("Line Mapper Failed");
			break;
	case LINEERR_NOCONFERENCE: //(= &H80000041)
            strErrorMsg = _T("No Conference");
			break;
	case LINEERR_NODEVICE: //(= &H80000042)
            strErrorMsg = _T("No Device");
			break;
	case LINEERR_NODRIVER: //(= &H80000043)
            strErrorMsg = _T("�����ṩ�߷�������һ�������ʧ��");
			break;
	case LINEERR_NOMEM: //(= &H80000044)
            strErrorMsg = _T("û���㹻���ڴ�����������Ķ���");
			break;
	case LINEERR_NOREQUEST: //(= &H80000045)
            strErrorMsg = _T("No Request");
			break;
	case LINEERR_NOTOWNER: //(= &H80000046)
            strErrorMsg = _T("������Ķ������ܾ�����ΪӦ�ó��򲢲�ӵ���������");
			break;
	case LINEERR_NOTREGISTERED: //(= &H80000047)
            strErrorMsg = _T("Not Registered");
			break;
	case LINEERR_OPERATIONFAILED: //(= &H80000048)
            strErrorMsg = _T("����ԭ������ʧ��");
			break;
	case LINEERR_OPERATIONUNAVAIL: //(= &H80000049
            strErrorMsg = _T("�����ṩ�߲�֧�ִ�����");
			break;
	case LINEERR_RATEUNAVAIL: //(= &H8000004A)
            strErrorMsg = "Rate Unavailable";
			break;
	case LINEERR_RESOURCEUNAVAIL: //(= &H8000004B)
            strErrorMsg = _T("û���㹻����Դ��ɴ�����");
			break;
	case LINEERR_REQUESTOVERRUN: //(= &H8000004C)
            strErrorMsg = _T("Request Overrun");
			break;
	case LINEERR_STRUCTURETOOSMALL: //(= &H8000004D)
            strErrorMsg = _T("ָ���Ľṹ̫С�����ܰ�����������");
			break;
	case LINEERR_TARGETNOTFOUND: //(= &H8000004E)
            strErrorMsg = _T("Target Not found");
			break;
    case LINEERR_TARGETSELF: //(= &H8000004F)
            strErrorMsg = _T("Target Self");
			break;
	case LINEERR_UNINITIALIZED: //(= &H80000050)
            strErrorMsg = _T("Uninitialized");
			break;
	case LINEERR_USERUSERINFOTOOBIG: //(= &H80000051)
            strErrorMsg = _T("UserUser Info Too Big");
			break;
	case LINEERR_REINIT: //(= &H80000052)
            strErrorMsg = _T("Re-init");
			break;
	case LINEERR_ADDRESSBLOCKED: //(= &H80000053)
            strErrorMsg = _T("Address Blocked");
			break;
	case LINEERR_BILLINGREJECTED: //(= &H80000054)
            strErrorMsg = _T("Billing Rejected");
			break;
	case LINEERR_INVALFEATURE: //(= &H80000055)
            strErrorMsg = _T("Invalid Feature");
			break;
	case LINEERR_NOMULTIPLEINSTANCE: //(= &H80000056)
            strErrorMsg = _T("No Multiple Instance");
			break;
	default:
            strErrorMsg = _T("δ֪����"); // undefined
			break;
	}

	return strErrorMsg;
}

//�ص�������������·��Ϣ��״̬�ı���Ϣ
void CTAPILine::LineCallbackProc(DWORD dwDevice,
								 DWORD dwMsg, 
								 DWORD dwCallbackInstance,
								 DWORD dwParam1, 
DWORD dwParam2, DWORD dwParam3)
{
	int i = TAPI_MAKECALLRESULT;
	switch(dwMsg)
	{
	//�����첽�����Ϣ
	case LINE_REPLY:
		if(dwParam1 == myTAPILine->m_nRequestingCall)
		{
			myTAPILine->m_nRequestingCall = 0;
			//�������ȷ�Ϲر���·
			if(dwParam2 != 0)
				myTAPILine->CloseLine();
					
			OutputDebugString("TAPI_MAKECALLRESULT\n");
		}
		else if(dwParam1 == myTAPILine->m_nDroppingCall)
		{	
			//�첽����
			myTAPILine->m_nDroppingCall = 0;
			
			OutputDebugString("TAPI_DROPCALLRESULT\n");
		}
		break;
	//����״̬�ı���Ϣ
	case LINE_CALLSTATE:
		switch(dwParam1)
		{
		case LINECALLSTATE_DISCONNECTED:
			//Զ�˶Ͽ�����
			myTAPILine->DropCallAsynch();
			//�����Ͽ��¼�
			OutputDebugString("TAPI_DISCONNECTED \n");
			break;
		case LINECALLSTATE_IDLE:
			//�����ں��У�����״̬
			if(myTAPILine->m_hCall != 0)
			{
				lineDeallocateCall(myTAPILine->m_hCall);
				myTAPILine->CloseLine();
			}
			
			OutputDebugString("TAPI_IDLE \n");
			break;
		case LINECALLSTATE_CONNECTED:
			
			OutputDebugString("TAPI_CONNECTED \n");
			break;
		case LINECALLSTATE_BUSY:

			break;
		case LINECALLSTATE_DIALTONE:

			break;
		case LINECALLSTATE_RINGBACK:

			break;
		case LINECALLSTATE_DIALING:

			break;
		case LINECALLSTATE_PROCEEDING:

			break;
		case LINECALLSTATE_SPECIALINFO:
			break;

		default:
			break;
		}
		
		break;
	}	
}

//�����·״̬�ַ���
CString CTAPILine::GetLineStateString(DWORD state)
{
	CString strMsg;

	switch(state)
	{
	case LINECALLSTATE_IDLE:
		strMsg = _T("���б�Ϊ����");
		break;
	case LINECALLSTATE_ACCEPTED:
		strMsg = _T("�µĺ��б�����");
		break;
	case LINECALLSTATE_DIALTONE:
		strMsg = _T("��⵽һ��������Ƶ");
		break;
	case LINECALLSTATE_DIALING:
		strMsg = _T("���ݸ��绰�������ĵ�ַ��Ϣ");
		break;
	case LINECALLSTATE_RINGBACK:
		strMsg = _T("��⵽�����ź�");
		break;
	case LINECALLSTATE_BUSY:
		strMsg = _T("����δ�����");
		break;
	case LINECALLSTATE_CONNECTED:
		strMsg = _T("�����ѳɹ�����");
		break;
	case LINECALLSTATE_PROCEEDING:
		strMsg = _T("���н��������ڽ��н�������");
		break;
	case LINECALLSTATE_ONHOLD:
		strMsg = _T("������������");
		break;
	case LINECALLSTATE_CONFERENCED:
		strMsg = _T("�����Ƕ෽�����һ��");
		break;
	case LINECALLSTATE_ONHOLDPENDCONF:
		strMsg = _T("���ӵ��෽����");
		break;
	case LINECALLSTATE_DISCONNECTED:
		strMsg = _T("�����Ѿ���������ж�");
		break;
	case LINECALLSTATE_UNKNOWN:
		strMsg = _T("δ֪�ĺ���״̬");
		break;
	default:
		strMsg = _T("����δ֪״̬");
		break;
	}

	return strMsg;
}
