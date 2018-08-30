#if !defined(AFX_MYLISTCTRL_H__2CBBF377_59A4_11D3_860E_C141D5317B49__INCLUDED_)
#define AFX_MYLISTCTRL_H__2CBBF377_59A4_11D3_860E_C141D5317B49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//
///////////////////////////////////////////////////////////////////

// CDataListCtrl window

class CDataListCtrl : public CListCtrl
{
public:
   CDataListCtrl();
   virtual ~CDataListCtrl();

 	BOOL AddColumn(
		LPCTSTR strItem,int nItem,int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT);//���б�������һ��
	//���б�������һ��
	BOOL AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);

public:
   BOOL   IsItem(int nItem) const;//��ѡ���Ƿ����
   BOOL   IsColumn(int nCol) const;//��ѡ���Ƿ����
   int    GetSelectedItem(int nStartItem = -1) const;//�õ���ѡ��
   BOOL   SelectItem(int nItem);//ѡ��ָ����
   BOOL   SelectAll();//ѡ��������

public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDataListCtrl)
	//}}AFX_VIRTUAL

   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//���غ���,�����б��������

// Generated message map functions
protected:
   //{{AFX_MSG(CDataListCtrl)
	//}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__2CBBF377_59A4_11D3_860E_C141D5317B49__INCLUDED_)
