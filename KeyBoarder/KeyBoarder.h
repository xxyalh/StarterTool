#pragma once

#include "resource.h"
#include <Windows.h>
#include <atlstr.h>
#include  "shellapi.h "
#include <Tlhelp32.h>
#include "ReadIni.h"
struct listInfo
{
	string ico;
	string text;
};
class MainWnd :public WindowImplBase, public CWebBrowserEventHandler
{
public:
	MainWnd();
	virtual LPCTSTR GetWindowClassName() const { return _T("MainWnd"); }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	virtual void OnFinalMessage(HWND /*hWnd*/) { delete this; };
	virtual LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void  Notify(TNotifyUI & msg);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void		InitWindow();
	void		SoftWareList();						//Ӧ���б�
	void		OpenWare(TNotifyUI& msg, int sel);				//
	void		AddTrayIcon();
	int			KillProcess(TCHAR Kill_Name[]);
	void		WriteIniFile(string path, string ico, int count);						//��ȡini�ļ�
	void		VecInfoInit(int count);							//��ʼ������
	void		WriteIniSelect();					
	string		TCHAR2STRING(TCHAR *STR);//TCHARתstring
private:
	void SoftWareList(CListUI* pList);
public:
	CPaintManagerUI		m_PaintManager;
	CControlUI*			m_pHelloBtn;
	CControlUI*			m_pRoot;
	COptionUI*			m_pWareOpen;
	vector<listInfo>	m_vecInfo;
	CButtonUI*			m_pSelect1;
	CButtonUI*			m_pSelect2;
	CButtonUI*			m_pSelect3;
	CEditUI*			m_pRolledmux;
	HANDLE				m_handle;
	NOTIFYICONDATA		m_trayIcon;
	string				m_sFilePath;
	vector<string>      m_VecPath1;		//exe·��
	vector<string>		m_VecIco1;		//ico·��
	vector<string>      m_VecPath2;		//exe·��
	vector<string>		m_VecIco2;		//ico·��
	vector<string>      m_VecPath3;		//exe·��
	vector<string>		m_VecIco3;		//ico·��
	vector<string>		m_sGameName;		//exe����
	vector<string>		m_sCommonName;		//exe����
	vector<string>		m_sFileName;		//exe����
	vector<string>		m_sDynamAdd;	//��̬��ӻ���
	CReadIni*			m_pReadIni;
	CListUI*			m_pGameList;	//��Ϸ�б�
	CListUI*			m_pCommuncList; //ͨ���б�
	CListUI*			m_pFileList;	//�ļ��б�
	CTabLayoutUI*		m_pTablay;			//��ҳ
	int					m_sCountPath;		//ini·������
	int					m_sCountIco;		//ini�ļ�����
	int					m_sInfo;			//���ݵ��б�����
	int					m_pCount;			//�򿪴���
};
