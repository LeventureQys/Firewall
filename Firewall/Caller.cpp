#include "Caller.h"
#include "stdafx.h"
//#include <string>
#include"Firewall.h"
//using namespace std;
#ifndef _DLL_FIREWALL
#define DLL_FIREWALL extern "C" _declspec (dllexport)
#define DLL_FIREWALL_PURE _declspec (dllexport)
#else
#define DLL_FIREWALL extern "C" _declspec (dllimport)
#define DLL_FIREWALL_PURE _declspec (dllimport)
#endif

//DLL_FIREWALL bool AddApp(const wchar_t* strAppPath, const wchar_t* strAppName)
//{
//	CFirewall cfer;
//
//	bool isok = cfer.AddApplication(strAppPath, strAppName);
//	if (isok) {
//		printf("应用已成功添加");
//	}
//	else {
//		printf("应用添加失败");
//	}
//	getchar();
//		return true;
//}

DLL_FIREWALL bool AddApp_withName(char* strAppPath, char* strAppName)
{
	String^ apppath = System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)strAppPath);
	String^ appname = System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)strAppName);

	CFirewall cfer;
	
	bool isok = cfer.AddApplication(apppath, appname);
	
	return isok;
}

DLL_FIREWALL bool AddApp(char* strAppPath)
{
	//char* strAppName 
	CFirewall cfer;

	char* strAppName = cfer.get_filename(strAppPath);

	String^ apppath = System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)strAppPath);
	String^ appname = System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)strAppName);
	
	

	bool isok = AddApp_withName(strAppPath,strAppName);

	return isok;

}


DLL_FIREWALL bool FwStatus(void)
{
	CFirewall cfer;
	bool isok = cfer.FirewallStatus(); //检查防火墙状态
	
	
	return isok;
}
