#pragma once
#include "stdafx.h"


#ifndef _DLL_FIREWALL
#define DLL_FIREWALL extern "C" _declspec (dllexport)
#define DLL_FIREWALL_PURE _declspec (dllexport)
#else
#define DLL_FIREWALL extern "C" _declspec (dllimport)
#define DLL_FIREWALL_PURE _declspec (dllimport)
#endif

DLL_FIREWALL bool AddApp_withName(char* strAppPath, char* strAppName);
DLL_FIREWALL bool FwStatus(void);
DLL_FIREWALL bool AddApp(char* strAppPath);
