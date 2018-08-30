
// PowerBenchView.h : CPowerBenchView ��Ľӿ�
//

#pragma once

#include "resource.h"
class CPowerBenchDoc;

class CBaseForm;
class CPowerBenchView : public CFormView
{
public: // �������л�����
	CPowerBenchView();
protected:
	DECLARE_DYNCREATE(CPowerBenchView)

public:
	enum{ IDD = IDD_POWERBENCH_FORM };

// ����
public:
	CPowerBenchDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

	/////////////////////
	CBaseForm* m_pChildTransForm;

// ʵ��
public:
	virtual ~CPowerBenchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	void CenterChildTransForm();

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PostNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // PowerBenchView.cpp �еĵ��԰汾
inline CPowerBenchDoc* CPowerBenchView::GetDocument() const
   { return reinterpret_cast<CPowerBenchDoc*>(m_pDocument); }
#endif

