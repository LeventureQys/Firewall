#pragma once

//#include <windows.h>
//#include <crtdbg.h>
//#include <netfw.h>
//#include <objbase.h>
//#include <oleauto.h>
//#include <stdio.h>

//#import "netfw.tlb"

using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::ServiceProcess;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

class CFirewall
{
private:
	void WriteErrorMessage(System::String^ strErrorMessage);
	bool ServiceStatus(void);

	HRESULT WindowsFirewallInitialize(OUT INetFwProfile** fwProfile);
	void WindowsFirewallCleanup(IN INetFwProfile* fwProfile);
	HRESULT WindowsFirewallIsOn(IN INetFwProfile* fwProfile, OUT BOOL* fwOn);
	HRESULT WindowsFirewallTurnOn(IN INetFwProfile* fwProfile);
	HRESULT WindowsFirewallTurnOff(IN INetFwProfile* fwProfile);
	HRESULT WindowsFirewallAppIsEnabled(IN INetFwProfile* fwProfile, IN const wchar_t* fwProcessImageFileName, OUT BOOL* fwAppEnabled);
	HRESULT WindowsFirewallAddApp(IN INetFwProfile* fwProfile, IN const wchar_t* fwProcessImageFileName, IN const wchar_t* fwName);
	HRESULT WindowsFirewallPortIsEnabled(IN INetFwProfile* fwProfile, IN LONG portNumber, IN NET_FW_IP_PROTOCOL ipProtocol, OUT BOOL* fwPortEnabled);
	HRESULT WindowsFirewallPortAdd(IN INetFwProfile* fwProfile, IN LONG portNumber, IN NET_FW_IP_PROTOCOL ipProtocol, IN const wchar_t* name);
	
public:
	CFirewall(void);
	~CFirewall(void);
	bool FirewallStatus(void);
	bool AddApplication(const wchar_t* strAppPath, const wchar_t* strAppName);
	bool AddApplication(System::String^ strAppPath, System::String^ strAppName);
	char *get_filename(char *fullpath);
	
};
