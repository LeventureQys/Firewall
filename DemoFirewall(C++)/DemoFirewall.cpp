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
	
	char* apppath = "D:\\Workshop\\云网络智慧教室V53\\Release\\LBD.CloudNetIntelClassroom.exe";

	char* appname = "蓝鸽云网络智慧课堂23123";

	char* apppath2 = "C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe";

	bool isadded_withName = AddApp_withName(apppath, appname);

	bool isadd = AddApp(apppath2);

	if (isok) {
		printf("防火墙已开启\n\n\n");
	}
	else {
		printf("防火墙未开启\n\n");
	}

	if (isadded_withName) {
		printf(" 已将%s\n路径下的%s对象添加至例外\n\n",apppath,appname);
	}
	else {
		printf("添加至例外失败\n\n");
	}

	if (isadd) {
		printf("已将 %s 路径下的对象添加至例外", apppath2);
	}
	else {
		printf("添加至例外失败\n\n");
	}
	getchar();

	return 0;
}

