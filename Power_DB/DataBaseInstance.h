#pragma once
#include "Power_DBDefinition.h"
class POWERDBAPI CDataBaseInstance
{
public:
	static CDatabase* GetDB();
	static void ExecuteDataBaseSQL(CString StrSql);

	//�õ�ĳһ������м�¼��
	static long GetAllRecordsCount(CString Table, CString Condtion = "");


	//�õ�ģ�����
	static long Getmoduls(CString  m_totalsql);





private:
	CDataBaseInstance(void);
	~CDataBaseInstance(void);
};

