#include "stdafx.h"
#include "RuntimeAccount.h"


CRuntimeAccount::CRuntimeAccount(void)
{
}


CRuntimeAccount::~CRuntimeAccount(void)
{
}

CString CRuntimeAccount::GetType( AccountPrivilege privilege )
{
	CString UseName;
	switch(privilege)
	{
	case 0:
		{
			UseName = "�߼�����Ա";
			break;
		}
	case 1:
		{
			UseName = "��ͨ����Ա";
			break;
		}
	case 2:
		{
			UseName = "�߼��û�";
			break;
		}
	case 3:
		{
			UseName = "��ͨ�û�";
			break;
		}
	}
	return UseName;
}

CRuntimeAccount::AccountPrivilege CRuntimeAccount::GetCurrentPrivilege()
{
	static AccountPrivilege val = AccountPrivilege::AdvancedAdministrator;
	return val;
}
