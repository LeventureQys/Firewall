// DemoFirewall.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Caller.h"
#pragma comment(lib,"Firewall.lib")
#include<iostream>
using namespace std;
int main()
{
	bool isok = FwStatus();



	
	const wchar_t* apppath = L"C:\Program Files (x86)\LgSoftWAN\LancooCNSC\Teacher\LBD.Frame.NetVoice.SIPServer.exe";
	const wchar_t* appname = L"LBD.Frame.NetVoice.SIPServer.exe";
	bool isadded = AddApp(apppath, appname);


	return 0;
}

