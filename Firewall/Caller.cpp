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
//		printf("Ӧ���ѳɹ����");
//	}
//	else {
//		printf("Ӧ�����ʧ��");
//	}
//	getchar();
//		return true;
//}

DLL_FIREWALL bool AddApp(char* strAppPath, char* strAppName)
{
	System::String^ apppath = gcnew System::String(strAppPath);
	System::String^ appname = gcnew System::String(strAppName);

	CFirewall cfer;
	
	bool isok = cfer.AddApplication(apppath, appname);
	if (isok) {
		printf("Ӧ���ѳɹ����");
	}
	else {
		printf("Ӧ�����ʧ��");
	}
	getchar();
	
	return true;
}

DLL_FIREWALL bool FwStatus(void)
{
	CFirewall cfer;
	bool isok = cfer.FirewallStatus(); //������ǽ״̬
	if (isok) {
		printf("����ǽ�Ѵ�");
	}
	else {
		printf("����ǽ�ѹر�");
	}
	getchar();
	return isok;
}
