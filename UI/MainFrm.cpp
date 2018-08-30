// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"



#include "AppInfo.h"
#include "MainFrm.h"

#include "IFRMView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const int CXABOUTBUTTON = 25;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGDATA, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGDATA, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SHOWDIALOGBAR, OnShowdialogbar)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_PROGRESS_PANE,
	ID_ANIMATE,
//	ID_SEPARATOR,         
// status line indicator
//	ID_SEPARATOR,
//	ID_INDICATOR_SCRL,  	
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,

};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bCreated           = FALSE;
	m_IsShowProgressCtrl = FALSE;
	m_pAnimate           =  NULL;
}

CMainFrame::~CMainFrame()
{

	m_pVicinity.DestroyMenu();    //���ز˵�����
    m_pLongDistance.DestroyMenu();//Զ�̲˵�����
	StopAnimation();

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}   
		
	//����ϵͳ������
	//����WINDOWSϵͳ������
	//::ShowWindow(::FindWindow("Shell_TrayWnd",NULL),SW_HIDE);//��ʾϵͳ������
	//�ָ�WINDOWSϵͳ������������ʾ
	//::ShowWindow (::FindWindow("Shell_TrayWnd",NULL),SW_SHOW);

	
	/*
	int *num, i, j = m_wndToolBar.GetToolBarCtrl().GetButtonCount();
	num = new int[j + 1];
	memset(num,0,(j + 1)*sizeof(int));
	num[0] = j;
	for(i = 0;i < j;i ++)
	{
		if(ID_SEPARATOR == m_wndToolBar.GetItemID( i ))
			num[i+1] = 1;
	}
	
	//�ָ�������һ����ť�������ԶΪ6
	//����õ��İ�ť������Զ�ȹ������༭�������趨�ĳ������7
	//���Ϊ������������λͼ����ť����״��Զֻ�봴��λͼ�б�ʱָ���Ĵ�Сһ�£��������ط��������޹�
	
	
	delete []num;
	*/
	
	//	m_wndToolBar.SetFullColorImage(IDR_MAINFRAME, RGB(255, 0, 255), num);




	if (!m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_bCreated = TRUE;

	m_pVicinity.LoadMenu(IDR_VICINITITYMENU);//���뱾�ز˵�
	HMENU hm=::GetMenu(this->m_hWnd);      //���Զ�̲˵�
	m_pLongDistance.Attach(hm);            //����Զ�̲˵���Դ
    
	//pt->m_WhichKind-------TRUE ���վ�汾  FALSE��ְ�
	CIFRMApp* pt = (CIFRMApp*)AfxGetApp();
	
	if(AppInfo::Instance().m_WhichKind)
	{
        SetMenu(&m_pVicinity);    //�Ѳ˵�����Ϊ���ز˵�
	}
	else
	{
		SetMenu(&m_pLongDistance);// �Ѳ˵�����ΪԶ�̲˵�
	}

//  TODO: Delete these three lines if you don't want the toolbar to
//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);
	 CRect     rt;                                                               
	 m_wndStatusBar.GetClientRect(&rt);
	
	 rt.left = rt.left + 358;//298
	 rt.top  = rt.top  +   2;
      
  	 m_progressBar.Create(WS_CHILD | WS_VISIBLE | WS_BORDER,rt,&m_wndStatusBar,ID_INDICATOR_PROGRESS_PANE);//ID_INDICATOR_PROGRESS_PANE);
     m_progressBar.ShowWindow(SW_SHOW);//SW_HIDE);//

	 CRect                rc;
	 VERIFY(m_wndAboutButton.Create(_T(""),WS_VISIBLE,rc,this,ID_APPEARDINGSHI));
 
	 // Create the Ok 256 colors button
     m_wndAboutButton.SubclassDlgItem(ID_APP_ABOUT, this);
 
//	 EnableDocking(CBRS_ALIGN_ANY);
//	 DockControlBar(&m_wndMyDialogData);
	 // Initialize dialog bar m_wndMyDialogData
	 if (!m_wndMyDialogData.Create(this, CG_IDD_MYDIALOGDATA,
		 CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		 CG_ID_VIEW_MYDIALOGDATA))
	 {
		 TRACE0("Failed to create dialog bar m_wndMyDialogData\n");
		 return -1;		// fail to create
	 }
	 
	 m_wndMyDialogData.EnableDocking(CBRS_ALIGN_BOTTOM);// | CBRS_ALIGN_TOP);

	 
	 if ( !m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR, CBRS_LEFT,CG_IDD_MYDIALOGBAR))//CBRS_LEFT CBRS_RIGHT
	 {
		 TRACE0("Failed to create dialog bar from CMyDialogBar class\n");
		 return -1;      // fail to create
	 }

	 //m_wndMyDialogBar.CalcDynamicLayout

	 CenterWindow();

	//m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndMyDialogBar);
//	DockControlBar(&m_wndMyDialogData);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
//  cs.x=-20;
//	cs.y=-30;

//	cs.style &= ~WS_THICKFRAME;// | ~WS_BORDER;
//	cs.style &= ~WS_DLGFRAME;
//	cs.style &= ~WS_BORDER;
//  cs.style &= FWS_ADDTOTITLE ;////~WS_EX_DLGMODALFRAME;
//  cs.hMenu = NULL;
//  the CREATESTRUCT cs
//	cs.style    &= ~WS_THICKFRAME;//����ı��С
//  cs.style     = cs.style &~ (WS_MAXIMIZEBOX);//// |WS_MINIMIZEBOX
//  cs.dwExStyle = WS_EX_TOPMOST;//���ڲ��ᱻ��ס
    cs.style    &=~ (LONG) FWS_ADDTOTITLE;//���ı����
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::StartAnimation( UINT id, int nPane /*=1*/ )
{
	StopAnimation();

	m_pAnimate = new CStatusbarAnimate;
	m_pAnimate->Create(id, nPane);
}

void CMainFrame::StopAnimation()
{
	delete m_pAnimate;
	m_pAnimate = NULL;
}

BOOL CMainFrame::IsAnimationActive()
{
	return (m_pAnimate != NULL);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	if(m_bCreated == TRUE)
	{
	
		CRect           rc;
		GetClientRect(&rc);
      //  m_wndMyDialogBar.GetWindowRect(&rc1);
	  //  m_wndMyDialogBar.SetWindowPos(&wndTop,rc1.left, rc1.top, rc1.Width(),600.top, SWP_SHOWWINDOW);

		m_wndStatusBar.GetClientRect(&rc);
		rc.left = rc.left + 298;//210;
		rc.top  = rc.top   +  2;

		if(m_IsShowProgressCtrl)
		{
			m_progressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,rc.bottom - rc.top, SWP_SHOWWINDOW);
		}
		else
		{	m_progressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,rc.bottom - rc.top, SWP_HIDEWINDOW);
		
		}
		
		CenterWindow();
    
//		DockControlBar(&m_wndMyDialogData,2,&rc);
		
		//���ؼ���С
	 	m_wndMyDialogData.ChangeSize();
	}
	
}

void CMainFrame::ShowProgressCtrl(BOOL m_IsShow)
{
	m_IsShowProgressCtrl = m_IsShow;
	if(m_IsShow)
	{
		m_progressBar.ShowWindow(SW_SHOW);
		
	}
	else
	{
		m_progressBar.ShowWindow(SW_HIDE);
		
	}
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	/***************/

	/*	
	//ȫ��Ļ��ʾ�Ĵ�����
	CRect rectDesktop;
	WINDOWPLACEMENT wpNew;
	::GetWindowRect(::GetDesktopWindow(), &rectDesktop );
//  rectDesktop.SetRect(315,0,1282,960);
//  rectDesktop.left = rectDesktop.left;
//  rectDesktop.top = rectDesktop.top;
//	rectDesktop.right = rectDesktop.right;
//	rectDesktop.bottom = rectDesktop.bottom;


	::AdjustWindowRectEx(&rectDesktop, GetStyle(),FALSE,GetExStyle());//TRUE
	wpNew.showCmd  = SW_SHOWNORMAL;//MAXIMIZED;
	wpNew.rcNormalPosition = rectDesktop;
    SetWindowPlacement (&wpNew ); //���ô�����ʾ״̬
  
	lpMMI->ptMaxSize.y = rectDesktop.Height()-9;
	lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y-9; 
	lpMMI->ptMaxSize.x = rectDesktop.Width(); 
	lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;


//	lpMMI->ptMinTrackSize.y = rectDesktop.Height();
//	lpMMI->ptMinTrackSize.x = rectDesktop.Width(); 
*/
	//������Сֵ
    lpMMI->ptMinTrackSize.y = 530;
    lpMMI->ptMinTrackSize.x = 720; 	

//	lpMMI->ptMinTrackSize.y = 0;
//	lpMMI->ptMinTrackSize.x = 0;
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnClose() 
{
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//	pview->DisConnect(pview->m_sendkind);
	
	if(!pview->DeleteViewThread())
	{
		return;
	}
		
	//ǿ���˳�
	if(MessageBox("�˳���ϵͳ��"," ",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{

		CFrameWnd::OnClose();
	}

}

void CMainFrame::OnShowdialogbar() 
{	
	CIFRMView* pview =  (CIFRMView *)((CFrameWnd*)AfxGetMainWnd())->GetActiveView();

	//���ڱ仯
	if(m_wndMyDialogBar.IsWindowVisible())
	{
		m_wndMyDialogBar.ShowWindow(SW_HIDE);
		m_wndMyDialogData.ShowWindow(SW_HIDE);

		pview->m_DialogBarVisible     = FALSE;
	}
	else
	{
		m_wndMyDialogBar.ShowWindow(SW_SHOW);
		m_wndMyDialogData.ShowWindow(SW_SHOW);
		RecalcLayout(TRUE);
		m_wndMyDialogData.ChangeSize();
		pview->m_DialogBarVisible     = TRUE;
	}

	//���²���
	RecalcLayout();
	
}


void CMainFrame::RecalcLayout(BOOL bNotify) 
{

	CFrameWnd::RecalcLayout(bNotify);
	CRect rc;
	
	if (m_wndStatusBar.m_hWnd)
	{
		m_wndStatusBar.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.left += CXABOUTBUTTON;
		m_wndStatusBar.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),
			SWP_NOZORDER);

		rc.left  = 0;
		rc.right = CXABOUTBUTTON;
		m_wndAboutButton.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),
				SWP_NOZORDER);	
		m_wndAboutButton.SetFlatFocus(TRUE,TRUE);
	}	
}

void CMainFrame::OnViewStatusBar() 
{
	// call base class handler
	OnBarCheck(AFX_IDW_STATUS_BAR);

	// now make button visible state same as status bar's
	BOOL bShow = m_wndStatusBar.GetStyle() & WS_VISIBLE;
	m_wndAboutButton.SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|
		(bShow ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));	
}
