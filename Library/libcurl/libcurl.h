/*****************************************
*封装Libcurl下载库
*author：Jelin
*date：2016年2月24日		
*/

#pragma once

#ifdef LS_STATIC_LIB_CALL
#define LIB_CURL_API 
#elif defined  CURL_EXPORTS
#define LIB_CURL_API __declspec(dllexport)
#else
#define LIB_CURL_API __declspec(dllimport)
#endif

#include "libcurl/curl/curl.h"
#include "libcurl/curl/easy.h"

#include <atlstr.h>

class ILibcurlCallback
{
public:
	ILibcurlCallback(){};
	~ILibcurlCallback(){};
public:
	virtual void LibcurlNotify(DWORD dwEvent, CURLcode curlCode, LPVOID lpData)
	{
		return ;
	}
	virtual int Progress(DWORD dwEvent, LPVOID lpData, size_t size, size_t nmemb)
	{
		return size * nmemb;
	}
	virtual int ProcessFunc(DWORD dwEvent, LPVOID lpData, size_t size, size_t nmemb)
	{
		return size * nmemb;
	}
};

// class LIB_CURL_API ICallback : public ILibcurlCallback
// {
// public:
// 	virtual int Progress(DWORD dwEvent, LPVOID lpData, size_t size, size_t nmemb)
// 	{
// 		return size * nmemb;
// 	}
// };

class LIB_CURL_API CLibcurl
{
public:
    CLibcurl();
    virtual ~CLibcurl();

    BOOL Init();

protected:
    virtual int process(void* data, size_t size, size_t nmemb);

public:
	BOOL SetCallback(ILibcurlCallback* pCallback);
	BOOL SetUserAgent(LPCTSTR lpAgent);
    BOOL doHttpPost(DWORD dwEvent, LPCTSTR lpszUrl, LPCTSTR lpszData, DWORD dwTimeout = 10 , DWORD dwHeader = 0);
    BOOL doHttpGet(DWORD dwEvent, LPCTSTR lpszUrl, LPCTSTR lpszData = NULL, DWORD dwTimeout = 10 , DWORD dwHeader = 0);
	BOOL GetErrorInfo(CString& strErrorInfo) const;
public:
    //CURLcode setOpt( CURLoption option ); 
    void ResetOpt(); 
    
private:
    static size_t ProcessFunc(void* ptr, size_t size, size_t nmemb, void *usrptr);

private:
    CURL*					m_pCurl;				//libcurl指针
	CURLcode			m_curlCode;		//libcurl错误代码
	ILibcurlCallback* m_pCallback;
}; 