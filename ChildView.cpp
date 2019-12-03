
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "AccSensor.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	zoom=1;
	nb=0;
	start=false;
	init();
	connected=false;
	counter=0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FICHIER_SAVE, &CChildView::OnFichierSave)
	ON_COMMAND(ID_FICHIER_READ, &CChildView::OnFichierRead)
	ON_COMMAND(ID_VIEW_START, &CChildView::OnViewStart)
	ON_COMMAND(ID_AFFICHAGE_ZOOMIN, &CChildView::OnAffichageZoomin)
	ON_COMMAND(ID_AFFICHAGE_ZOOMOUT, &CChildView::OnAffichageZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_START, &CChildView::OnUpdateViewStart)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_ZOOMIN, &CChildView::OnUpdateAffichageZoomin)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_ZOOMOUT, &CChildView::OnUpdateAffichageZoomout)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// gestionnaires de messages pour CChildView


void CChildView::init()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<MAX_ECH;j++)
		{
			points[i][j].x=j;
			points[i][j].y=0;
		}
}
//show

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // contexte de périphérique pour la peinture
	
	// TODO : ajoutez ici le code de votre gestionnaire de messages
	dc.SetBkMode(TRANSPARENT);
	RECT r; ::GetClientRect(m_hWnd,&r);
//******line1******
	CPen p1(PS_SOLID,1,0x0000FF);//r
	CPen pp1(PS_DOT,1,0x0000FF);
	CPen *p1pold1=dc.SelectObject(&pp1);
  dc.MoveTo(0,r.bottom/4);//pos=1/4
	dc.LineTo(MAX_ECH-1,r.bottom/4);//line r
	CPen *ppold1=dc.SelectObject(&p1);
	for(size_t i=0;i<MAX_ECH;i++)
	{
		dc.MoveTo(i,r.bottom/4-points[0][i].y*zoom/8);
		dc.LineTo(i+1,r.bottom/4-points[0][i+1].y*zoom/8);
	}

	dc.SelectObject(&pp1);
	dc.MoveTo(0,r.bottom/4-val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom/4-val*zoom);
	dc.MoveTo(0,r.bottom/4+val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom/4+val*zoom);
//******line2******
	CPen p2(PS_DOT,1,0x00FF00);
	CPen pp2(PS_SOLID,1,0x00FF00);
  CPen *ppold2=dc.SelectObject(&p2);
	dc.MoveTo(0,r.bottom*2/4);
	dc.LineTo(MAX_ECH-1,r.bottom*2/4);

  CPen *p2pold2=dc.SelectObject(&pp2);
  for(size_t i=0;i<MAX_ECH;i++)
	{
		dc.MoveTo(i,r.bottom*2/4-points[1][i].y*zoom/8);
		dc.LineTo(i+1,r.bottom*2/4-points[1][i+1].y*zoom/8);
	}
  dc.SelectObject(&p2);
	dc.MoveTo(0,r.bottom*2/4-val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom*2/4-val*zoom);
	dc.MoveTo(0,r.bottom*2/4+val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom*2/4+val*zoom);

//******line3******

	CPen p3(PS_DOT,1,0xFF0000);
	CPen pp3(PS_SOLID,1,0xFF0000);
	CPen *ppold3=dc.SelectObject(&p3);
	dc.MoveTo(0,r.bottom*3/4);
	dc.LineTo(MAX_ECH-1,r.bottom*3/4);
	CPen *p3pold3=dc.SelectObject(&pp3);
 for(size_t i=0;i<MAX_ECH;i++)
	{
		dc.MoveTo(i,r.bottom*3/4-points[2][i].y*zoom/8);
		dc.LineTo(i+1,r.bottom*3/4-points[2][i+1].y*zoom/8);
	}
	dc.SelectObject(&p3);
	dc.MoveTo(0,r.bottom*3/4-val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom*3/4-val*zoom);
	dc.MoveTo(0,r.bottom*3/4+val*zoom);
	dc.LineTo(MAX_ECH-1,r.bottom*3/4+val*zoom);

	dc.SelectObject(ppold1);
	dc.SelectObject(ppold2);
	dc.SelectObject(ppold3);
	// Ne pas appeler CWnd::OnPaint() pour la peinture des messages
}


void CChildView::OnFichierSave()
{
	// TODO: 在此添加命令处理程序代码
}

void CChildView::OnFichierRead()
{
	// TODO: 在此添加命令处理程序代码
}

void CChildView::OnViewStart()
{
	if(start)
	{
		KillTimer(1);
		start = false;
	}
	else
	{
		if(GetNbSensors()!=0)
		{ 
			start=true;
			sensor=GetSensor(0);
			SetTimer(1,100,0);
		} 
		else{
			PlaySound("erreur",NULL,SND_FILENAME|SND_ASYNC);
			MessageBox(_T("pas de capteur disponible"),_T("Erreur!")); 
		}
		init();//tout (re)démarrage
		nb=0;
		Invalidate();
	}
	// TODO: 在此添加命令处理程序代码
}

void CChildView::OnUpdateViewStart(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(start ? _T("&Stop") : _T("&Start"));
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CChildView::OnAffichageZoomin()
{
	if(zoom<8)
		zoom++;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

void CChildView::OnUpdateAffichageZoomin(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(zoom<7);
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CChildView::OnAffichageZoomout()
{
	
	if(zoom>0)
		zoom--;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

void CChildView::OnUpdateAffichageZoomout(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(zoom>1);
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
	{
    short tabshort[3];
    if(sensor->ReadAcc(tabshort)){
      //MessageBox("marche");
			points[0][nb].y=tabshort[0];
			points[1][nb].y=tabshort[1];
			points[2][nb].y=tabshort[2];
			nb++;
			CRect rect;
			GetClientRect(&rect);
			CRect r(nb-2,0,nb+1,rect.bottom);
			InvalidateRect(&r);
    }
    else
      KillTimer(1);
	}
  else
    KillTimer(1);
	__super::OnTimer(nIDEvent);
}
