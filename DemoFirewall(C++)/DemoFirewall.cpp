// DemoFirewall.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Caller.h"
#pragma comment(lib,"Firewall.lib")
#include<iostream>
using namespace std;
int main()
{
	bool isok = FwStatus();
	
	char* apppath = "D:\\Workshop\\�������ǻ۽���V53\\Release\\LBD.CloudNetIntelClassroom.exe";

	char* appname = "�����������ǻۿ���23123";

	char* apppath2 = "C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe";

	bool isadded_withName = AddApp_withName(apppath, appname);

	bool isadd = AddApp(apppath2);

	if (isok) {
		printf("����ǽ�ѿ���\n\n\n");
	}
	else {
		printf("����ǽδ����\n\n");
	}

	if (isadded_withName) {
		printf(" �ѽ�%s\n·���µ�%s�������������\n\n",apppath,appname);
	}
	else {
		printf("���������ʧ��\n\n");
	}

	if (isadd) {
		printf("�ѽ� %s ·���µĶ������������", apppath2);
	}
	else {
		printf("���������ʧ��\n\n");
	}
	getchar();

	return 0;
}

