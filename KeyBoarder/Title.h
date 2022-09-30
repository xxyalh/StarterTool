#pragma once
#include<Windows.h>
class Title : public WindowImplBase 
{
public:
	HWND m_hwnds;
public:
	Title(){};
	~Title(){};

	virtual LPCTSTR GetWindowClassName() const { return _T("Title"); }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	virtual void OnFinalMessage(HWND /*hWnd*/) { delete this; };
	
	virtual CDuiString GetSkinFile(){ return _T("Title.xml"); }
	virtual CDuiString GetSkinFolder(){ return _T("Title"); }
	virtual void  Notify(TNotifyUI & msg)
	{
		if (msg.sType == _T("click"))
		{
			if (msg.pSender->GetName() == _T("configBtn"))
			{
				::PostMessage(m_hwnds, WM_TITLESELECTEDCONFIG, 1, 0);
			}
			else if (msg.pSender->GetName() == _T("exitBtn"))
			{
				Close();
			}
		}
	}
	
};

