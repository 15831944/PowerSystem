//{{AFX_INCLUDES()
#include "sstabctl.h"
//}}AFX_INCLUDES
#if !defined(AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_)
#define AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AngleSet.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CAngleSet dialog
#include "Resource.h"
class CAngleSettingGlg : public CDialog
{
// Construction
public:
	BOOL m_WhichKind;
	CAngleSettingGlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAngleSet)
	enum { IDD = IDD_PARAMETERSET };
	CSpinButtonCtrl	m_spinhandno;
	CSpinButtonCtrl	m_SpinButton;
	int		m_Sangle;
	int		m_SangleB;
	int		m_SangleC;
	int		m_generatrixno;
	BYTE	m_handno;
	CString	m_handstationname;
	BOOL	m_status;
	CSSTabCtl	m_SstabCtrl;
	int		m_radio;
	BYTE	m_saveyears;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAngleSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAngleSet)
	afx_msg void OnAngleset();
	afx_msg void OnReadangle();
	afx_msg void OnAnglesetb();
	afx_msg void OnAnglesetc();
	afx_msg void OnReadangleb();
	afx_msg void OnReadanglec();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetparameter();
	afx_msg void OnClickSstab(short PreviousTab);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnSetyears();
	afx_msg void OnReadyears();
	afx_msg void OnCancelset();
	afx_msg void OnRadio49();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableWindows(int m_select);
	void GetHandNoInformation();//short generatrixno ĸ�߱��
    //short phase  ��� 0 A�� 1 B�� 2 C��
    //int   angles �Ƕ�
    //BYTE  kinds  ���� 0--�ź�ǿ�� 1���ӳٽǶ�
    void SetThreePhaseAngle(short generatrixno,short phase,int angles,BYTE kinds);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANGLESET_H__D596C165_0A1F_4DF7_943F_5A915F2D42E1__INCLUDED_)
