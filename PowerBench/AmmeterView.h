
#pragma once
#include "PowerBenchView.h"

//

//#include "AmmeterViewHoldDlg.h"

typedef CWinFormsDialog<PowerBenchSharpLib::AmmeterInfoControl> CAmmeterViewHoldDlg;

class CAmmeterView : public CDockablePane
{
// ����
public:
	CAmmeterView();

	
	void OnChangeVisualStyle();


	static CAmmeterView* GetCurrentInstance();
	

	PowerBenchSharpLib::AmmeterInfoControl^ GetHoldControl();

// ����
protected:
	CAmmeterViewHoldDlg m_dlg;

	
	

protected:
	

// ʵ��
public:
	virtual ~CAmmeterView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

