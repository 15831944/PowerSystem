#include "StdAfx.h"
#include "CtrlHistoryHoldDlg.h"
#include "afxdialogex.h"
#include "CtrlMessageHostDlg.h"

// CCtrlHistoryHoldDlg dialog

IMPLEMENT_DYNAMIC(CCtrlHistoryHoldDlg, CBaseForm)

CWinFormsControl<PowerBenchSharpLib::UCAmmeterUsage>& CCtrlHistoryHoldDlg::GetHoldCtrl()
{
	return m_ctrl;
}

static CCtrlHistoryHoldDlg* pinstance = NULL;
CCtrlHistoryHoldDlg* CCtrlHistoryHoldDlg::Instance()
{
	return pinstance;
}

CCtrlHistoryHoldDlg::CCtrlHistoryHoldDlg( CWnd* pParent /*= NULL*/ ) : CBaseForm(CCtrlHistoryHoldDlg::IDD, pParent)
{
	pinstance = this;
}


BOOL CCtrlHistoryHoldDlg::OnInitDialog()
{
	CBaseForm::OnInitDialog();
	//TO DO ����Ԫ�س�ʼ���ڴ�:��Ҫ��Combox�������
	CString title ;

	m_ctrl.GetWindowText(title);
	this->SetWindowText(title);

	

	return TRUE;
}




BEGIN_MESSAGE_MAP(CCtrlHistoryHoldDlg, CBaseForm)	
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCtrlHistoryHoldDlg message handlers



