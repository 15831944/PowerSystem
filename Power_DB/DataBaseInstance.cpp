#include "stdafx.h"
#include "DataBaseInstance.h"


CDataBaseInstance::CDataBaseInstance(void)
{
}


CDataBaseInstance::~CDataBaseInstance(void)
{
}

CDatabase* CDataBaseInstance::GetDB()
{
	static CDatabase db;
	if(!db.IsOpen())
	{
		db.OpenEx( _T("DSN=ifrm"),CDatabase::openReadOnly |CDatabase::noOdbcDialog);
	}
	return &db;
}

void CDataBaseInstance::ExecuteDataBaseSQL( CString StrSql )
{
	//CDatabase dbs;
	//if(dbs.OpenEx( _T("DSN=ifrm"),CDatabase::noOdbcDialog))
	//{	

	TRY
	{
		GetDB()->ExecuteSQL(StrSql);

	}
	CATCH(CDBException, e)
	{

	}
	END_CATCH

		//dbs.Close();
		//}
}

long CDataBaseInstance::GetAllRecordsCount( CString Table, CString Condtion )
{
	//�����ݿ�

	CString strSql;
	//��CRecordset����
	CRecordset rs(GetDB());

	Condtion.TrimLeft();
	Condtion.TrimRight();

	if(Condtion == "ALL" || Condtion == "")
	{
		strSql.Format("SELECT count(*) FROM %s",Table);
	}
	else
	{
		strSql.Format("SELECT count(*) FROM %s  WHERE %s",Table,Condtion);
	}

	try
	{
		rs.Open(CRecordset::forwardOnly,strSql);
	}
	catch(CDBException* e) 
	{
		e->Delete();
		rs.Close();
		//�ر����ݿ�

		::MessageBox(NULL,"��ѯ�����������ݱ��ѯ���ִ���\r\n������ֶ�ֵΪ�ַ�������ϵ����ţ�"," ",MB_OK|MB_ICONWARNING);
		return  -1;
	}

	//�õ���¼����
	rs.GetFieldValue((short)0,strSql);
	rs.Close();
	//���ؼ�¼����
	return atol(strSql); 
}

//�õ�ģ�����
long CDataBaseInstance::Getmoduls( CString m_totalsql )
{
	//�����ݿ�
	
	CString      str = "";

	
		//��CRecordset����
		CRecordset   rs(GetDB());
		m_totalsql.TrimLeft();
		m_totalsql.TrimRight();


		if(m_totalsql == "ALL")
		{
			str = "Select COUNT(DISTINCT USER_MODULENO/100) from TB_USER";
		}
		else
		{
			str.Format("Select COUNT(DISTINCT USER_MODULENO/100) from TB_USER WHERE %s",m_totalsql);
		}

		/*
		str = "Select COUNT(DISTINCT  CAST(USER_MODULENO AS INT)/100) from TB_USER";
		*/

		rs.Open(CRecordset::forwardOnly,str);

		//�õ���¼����
		rs.GetFieldValue((short)0,str);
		rs.Close();

		//�ر����ݿ�
	//	dbs.Close();
	

	//���ؼ�¼����
	return atol(str);
}

