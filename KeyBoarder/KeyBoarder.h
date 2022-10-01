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
	void		SoftWareList();						//应用列表
	void		OpenWare(TNotifyUI& msg);				//
	void		AddTrayIcon();
	int			KillProcess(TCHAR Kill_Name[]);
	void		WriteIniFile();						//读取ini文件
	void		VecInfoInit();							//初始化数组
	void		WriteIniSelect();					
	string		TCHAR2STRING(TCHAR *STR);//TCHAR转string
private:
	static DWORD WINAPI SoftWareList(LPVOID pParam);
public:
	CPaintManagerUI		m_PaintManager;
	CControlUI*			m_pHelloBtn;
	CControlUI*			m_pRoot;
	COptionUI*			m_pWareOpen;
	vector<listInfo>	m_vecInfo;
	HANDLE				m_handle;
	NOTIFYICONDATA		m_trayIcon;
	string				m_sFilePath;
	vector<string>      m_VecPath;		//exe路径
	vector<string>		m_VecIco;		//ico路径
	vector<string>		m_sExeName;		//exe名字
	vector<string>		m_sDynamAdd;	//动态添加缓存
	CReadIni*			m_pReadIni;
	CListUI*			m_pWareList;
	int					m_sCountPath;		//ini路径数量
	int					m_sCountIco;		//ini文件数量
};
