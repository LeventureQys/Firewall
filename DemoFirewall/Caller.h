#pragma once
#include "stdafx.h"


#ifndef _DLL_FIREWALL
#define DLL_FIREWALL extern "C" _declspec (dllexport)
#define DLL_FIREWALL_PURE _declspec (dllexport)
#else
#define DLL_FIREWALL extern "C" _declspec (dllimport)
#define DLL_FIREWALL_PURE _declspec (dllimport)
#endif

DLL_FIREWALL bool AddApp(const wchar_t* strAppPath, const wchar_t* strAppName);
DLL_FIREWALL bool FwStatus(void);
