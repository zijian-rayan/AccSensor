
// ChildView.h : interface de la classe CChildView
//


#pragma once

#define MAX_ECH 2000
#define val 30

// fen¨ºtre CChildView

class CChildView : public CWnd, public AccManager
{
// Construction
	void init();
public:
	CChildView();

// Attributs
public:
  int zoom;
  bool start;
  int nb;
  bool connected;
  POINTF points[3][MAX_ECH];//or point???? not sure
  AccSensor* sensor;
  int counter;

// Op¨¦rations
public:
	void show(CDC &dc);

// Substitutions
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Impl¨¦mentation
public:
	virtual ~CChildView();

	// Fonctions g¨¦n¨¦r¨¦es de la table des messages
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFichierSave();
	afx_msg void OnFichierRead();
	afx_msg void OnViewStart();
	afx_msg void OnAffichageZoomin();
	afx_msg void OnAffichageZoomout();
	afx_msg void OnUpdateViewStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAffichageZoomin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAffichageZoomout(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

