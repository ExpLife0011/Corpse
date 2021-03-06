#ifndef _DUIDIALOG_H_
#define _DUIDIALOG_H_

/**
  * 
*/

#include "DuiLib\UIlib.h"
#include "IrregularWindow.h"

using namespace DuiLib;

class CDUIDialog;

typedef void (CDUIDialog::*NotifyHandler)(TNotifyUI& msg);

struct stNotifyHandler
{
	CDuiString strNotifyName;

	NotifyHandler handler;

	stNotifyHandler(const TCHAR* pNotifyName,NotifyHandler pHandler)
		:strNotifyName(pNotifyName)
		,handler(pHandler)
	{
	}
};

#ifndef count_of
	#define count_of(x) ((x == NULL) ? 0 : (sizeof(x) / sizeof(x[0])))
#endif

class CDUIDialog : public CWindowWnd, public INotifyUI
{
public:

	/*
		gui文件名是 skin.xml 
		资源路径是 EXE文件路径 + "skin";
		BkImage 如果想实现异型窗体 则 设置一个png图片就可以了
	*/
	CDUIDialog(const CDuiString& strBKImage = _T(""));

	/*
		strGUI:文件名
		strPath: 资源路径 相对于 EXE文件路径,如:"skin"
	*/
	CDUIDialog(const CDuiString& strGUI,const CDuiString& strPath,const CDuiString& strBKImage = _T(""));

	/*
		bZipPath: 这个值其实 没用到 是为了与上面构造函数有个区分
		strPath:zip资源包的路径,如:"skin\\skin.zip"
		CDUIDialog(_T("skin.xml"),_T("skin\\skin.zip")
	*/
	CDUIDialog(const CDuiString& strGUI,const CDuiString& strZipPath, TCHAR bZipPath /*=true*/,const CDuiString& strBKImage = _T(""));

	bool Show(bool bCenter = true);

	~CDUIDialog();

protected:
    /**********事件处理***********/

	//设置窗口样式
	virtual void OnSetWindowStyle(LONG& dwStyle);

	//在显示之前
	virtual void PreShow();

	//显示之后
	virtual void AfterShow();

	//如果希望WM_CLOSE 使用默认处理(销毁窗口) 返回 0,否则返回非0
	virtual HRESULT OnClose();

	//按钮点击事件
	virtual void OnButtonClick(TNotifyUI& msg);

	//COptionUI 选中发生变化时
	virtual void OnOptionSelectChange(TNotifyUI& msg);

	//点击 CTextUI上面的链接
	virtual void OnLinkClick(TNotifyUI& msg);

	//Slider 值发生变化
	virtual void OnSliderValueChange(TNotifyUI& msg);

	//文本框 内容发生改变时
	virtual void OnEditTextChange(TNotifyUI& msg);

	//文本框中按下 return键
	virtual void OnEditReturn(TNotifyUI& msg);

	//子控件  定时器
	virtual void OnTimer(TNotifyUI& msg);

	//子控件 获得焦点
	virtual void OnFocusIn(TNotifyUI& msg);

	//子控件 失去焦点
	virtual void OnFocusOut(TNotifyUI& msg);

	virtual void OnMaxmize(TNotifyUI& msg);

	virtual void OnMinimize(TNotifyUI& msg);

protected:

	virtual LPCTSTR GetWindowClassName() const;

	virtual void Notify(TNotifyUI& msg);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	void __Init(const CDuiString& strGUI,const CDuiString& strPath,const CDuiString& strZip,const CDuiString& BkImage);

	//响应WM_CREATE消息 (不能是虚函数 没用,应为在构造函数的流程中调用的)
	HRESULT OnCreate();

private:

	static stNotifyHandler notifyMap[];

protected:

	 CPaintManagerUI m_pm;

	 CIrregularWindow* m_pBackWnd;

	 HRESULT m_hr;
};


#endif