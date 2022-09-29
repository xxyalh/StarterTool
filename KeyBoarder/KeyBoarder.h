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
	void InitWindow();
	void SoftWareList();					//应用列表
	void OpenWare(TNotifyUI& msg);						//
	void AddTrayIcon();
	int KillProcess(TCHAR Kill_Name[]);
	void ReadIniFile();						//读取ini文件
	string TCHAR2STRING(TCHAR *STR);//TCHAR转string
public:
	CPaintManagerUI		m_PaintManager;
	CControlUI*			m_pHelloBtn;
	CControlUI*			m_pRoot;
	COptionUI*			m_pWareOpen;
	vector<listInfo>	m_vecInfo;
	HANDLE				m_handle;
	HANDLE				m_hList;
	NOTIFYICONDATA		m_trayIcon;
	string				m_sFilePath;
	vector<string>      m_VecPath;
};
