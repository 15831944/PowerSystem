#pragma once
class AppInfo
{
public:
	BOOL          m_WhichKind;  //ѡ��汾     TRUE ���վ�汾           FALSE ��ְ�
	BOOL          m_2000Users;  //2000�û�     TRUE 2000�û�             FALSE �û�����������
	BOOL          m_AutoRunning;//�Ƿ�һ�������Զ�����
	BOOL          m_SingleBB;   //�Ƿ��ǵ�һ�汾
	BOOL            m_YanShi;   //�Ƿ�����ʾ�汾
	static AppInfo& Instance()
	{
		static AppInfo intance;
		return intance;
	}

};