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
	void		OpenWare(TNotifyUI& msg, int sel);				//
	void		AddTrayIcon();
	int			KillProcess(TCHAR Kill_Name[]);
	void		WriteIniFile(string path, string ico, int count);						//读取ini文件
	void		VecInfoInit(int count);							//初始化数组
	void		WriteIniSelect();					
	string		TCHAR2STRING(TCHAR *STR);//TCHAR转string
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
	vector<string>      m_VecPath1;		//exe路径
	vector<string>		m_VecIco1;		//ico路径
	vector<string>      m_VecPath2;		//exe路径
	vector<string>		m_VecIco2;		//ico路径
	vector<string>      m_VecPath3;		//exe路径
	vector<string>		m_VecIco3;		//ico路径
	vector<string>		m_sGameName;		//exe名字
	vector<string>		m_sCommonName;		//exe名字
	vector<string>		m_sFileName;		//exe名字
	vector<string>		m_sDynamAdd;	//动态添加缓存
	CReadIni*			m_pReadIni;
	CListUI*			m_pGameList;	//游戏列表
	CListUI*			m_pCommuncList; //通信列表
	CListUI*			m_pFileList;	//文件列表
	CTabLayoutUI*		m_pTablay;			//翻页
	int					m_sCountPath;		//ini路径数量
	int					m_sCountIco;		//ini文件数量
	int					m_sInfo;			//创捷的列表索引
	int					m_pCount;			//打开次数
};
