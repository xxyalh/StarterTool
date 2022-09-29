#pragma once
class Listmenu :public WindowImplBase, public CWebBrowserEventHandler
{
public:
	Listmenu();
	~Listmenu();

	virtual LPCTSTR GetWindowClassName() const { return _T("MainWnd"); }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	virtual void OnFinalMessage(HWND /*hWnd*/) { delete this; };
	virtual void  Notify(TNotifyUI & msg);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return 0; };
	virtual void Init(POINT pt);

	void PopupPosition(POINT pt);
public:
	HWND s_handle;//主窗口句柄
	bool bIsLock;//锁定标志
};

