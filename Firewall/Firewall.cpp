#include "StdAfx.h"
#include "Firewall.h"

void CFirewall::WriteErrorMessage(System::String^ strErrorMessage)
{
	DirectoryInfo^ clsPath = gcnew DirectoryInfo(Path::GetDirectoryName(Application::ExecutablePath));
	DirectoryInfo^ clsSubPath = clsPath->CreateSubdirectory("Errlog");

	if (clsSubPath->Exists)
	{
		DateTime^ clsDate = DateTime::Now;
		String^ strPath = clsSubPath->FullName + "\\FireWall(" + String::Format("{0:yyyy-MM-dd}", clsDate) + ").log";
		StreamWriter^ clsWriter = gcnew StreamWriter(strPath, true);
		clsWriter->WriteLine(String::Format("{0:HH:mm:ss}", clsDate) + " " + strErrorMessage);
		clsWriter->Close();
	}
}
 
bool CFirewall::ServiceStatus(void)
{
	bool blnStatus = false;

	array<ServiceController^>^clsServices = ServiceController::GetServices();

	if (clsServices->Length)
	{
		for each (ServiceController^ clsService in clsServices)
		{
			if (clsService->ServiceName == "SharedAccess")
			{
				if (clsService->Status == ServiceControllerStatus::Running) blnStatus = true;
			}
			else if (clsService->ServiceName == "MpsSvc")
			{
				if (clsService->Status == ServiceControllerStatus::Running) blnStatus = true;
			}
		}
	}

	return blnStatus;
}

HRESULT CFirewall::WindowsFirewallInitialize(OUT INetFwProfile** fwProfile)
{
	HRESULT hr = S_OK;
	INetFwMgr* fwMgr = NULL;
	INetFwPolicy* fwPolicy = NULL;

	_ASSERT(fwProfile != NULL);

	*fwProfile = NULL;

	// Create an instance of the firewall settings manager.
	hr = CoCreateInstance(
		__uuidof(NetFwMgr),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwMgr),
		(void**)&fwMgr
	);
	if (FAILED(hr))
	{
		goto error;
	}

	// Retrieve the local firewall policy.
	hr = fwMgr->get_LocalPolicy(&fwPolicy);
	if (FAILED(hr))
	{
		goto error;
	}

	// Retrieve the firewall profile currently in effect.
	hr = fwPolicy->get_CurrentProfile(fwProfile);
	if (FAILED(hr))
	{
		goto error;
	}

	// Release the local firewall policy.
	if (fwPolicy != NULL)
	{
		fwPolicy->Release();
	}

	// Release the firewall settings manager.
	if (fwMgr != NULL)
	{
		fwMgr->Release();
	}

	return hr;

error:

	// Release the local firewall policy.
	if (fwPolicy != NULL)
	{
		fwPolicy->Release();
	}

	// Release the firewall settings manager.
	if (fwMgr != NULL)
	{
		fwMgr->Release();
	}

	WriteErrorMessage("WindowsFirewallInitialize:" + Convert::ToString(hr));

	return hr;
}


void CFirewall::WindowsFirewallCleanup(IN INetFwProfile* fwProfile)
{
	// Release the firewall profile.
	if (fwProfile != NULL)
	{
		fwProfile->Release();
	}
}


HRESULT CFirewall::WindowsFirewallIsOn(IN INetFwProfile* fwProfile, OUT BOOL* fwOn)
{
	HRESULT hr = S_OK;
	VARIANT_BOOL fwEnabled;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwOn != NULL);

	*fwOn = FALSE;

	// Get the current state of the firewall.
	hr = fwProfile->get_FirewallEnabled(&fwEnabled);
	if (FAILED(hr))
	{
		goto error;
	}

	// Check to see if the firewall is on.
	if (fwEnabled != VARIANT_FALSE)
	{
		*fwOn = TRUE;
	}
	else
	{
	}

	return hr;

error:

	WriteErrorMessage("WindowsFirewallIsOn:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallTurnOn(IN INetFwProfile* fwProfile)
{
	HRESULT hr = S_OK;
	BOOL fwOn;

	_ASSERT(fwProfile != NULL);

	// Check to see if the firewall is off.
	hr = WindowsFirewallIsOn(fwProfile, &fwOn);
	if (FAILED(hr))
	{
		goto error;
	}

	// If it is, turn it on.
	if (!fwOn)
	{
		// Turn the firewall on.
		hr = fwProfile->put_FirewallEnabled(VARIANT_TRUE);
		if (FAILED(hr))
		{
			goto error;
		}
	}

	return hr;

error:
	WriteErrorMessage("WindowsFirewallTurnOn:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallTurnOff(IN INetFwProfile* fwProfile)
{
	HRESULT hr = S_OK;
	BOOL fwOn;

	_ASSERT(fwProfile != NULL);

	// Check to see if the firewall is on.
	hr = WindowsFirewallIsOn(fwProfile, &fwOn);
	if (FAILED(hr))
	{
		goto error;
	}

	// If it is, turn it off.
	if (fwOn)
	{
		// Turn the firewall off.
		hr = fwProfile->put_FirewallEnabled(VARIANT_FALSE);
		if (FAILED(hr))
		{
			goto error;
		}
	}

	return hr;

error:
	WriteErrorMessage("WindowsFirewallTurnOff:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallAppIsEnabled(
	IN INetFwProfile* fwProfile,
	IN const wchar_t* fwProcessImageFileName,
	OUT BOOL* fwAppEnabled
)
{
	HRESULT hr = S_OK;
	BSTR fwBstrProcessImageFileName = NULL;
	VARIANT_BOOL fwEnabled;
	INetFwAuthorizedApplication* fwApp = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);
	_ASSERT(fwAppEnabled != NULL);

	*fwAppEnabled = FALSE;

	// Retrieve the authorized application collection.
	hr = fwProfile->get_AuthorizedApplications(&fwApps);
	if (FAILED(hr))
	{
		goto error;
	}

	// Allocate a BSTR for the process image file name.
	fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
	if (fwBstrProcessImageFileName == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto error;
	}

	// Attempt to retrieve the authorized application.
	hr = fwApps->Item(fwBstrProcessImageFileName, &fwApp);
	if (SUCCEEDED(hr))
	{
		// Find out if the authorized application is enabled.
		hr = fwApp->get_Enabled(&fwEnabled);
		if (FAILED(hr))
		{
			goto error;
		}

		if (fwEnabled != VARIANT_FALSE)
		{
			// The authorized application is enabled.
			*fwAppEnabled = TRUE;
		}
		else
		{
		}
	}
	else
	{
		// The authorized application was not in the collection.
		hr = S_OK;
	}

	// Free the BSTR.
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	return hr;

error:

	// Free the BSTR.
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	WriteErrorMessage("WindowsFirewallAppIsEnabled:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallAddApp(
	IN INetFwProfile* fwProfile,
	IN const wchar_t* fwProcessImageFileName,
	IN const wchar_t* fwName
)
{
	HRESULT hr = S_OK;
	BOOL fwAppEnabled;
	BSTR fwBstrName = NULL;
	BSTR fwBstrProcessImageFileName = NULL;
	INetFwAuthorizedApplication* fwApp = NULL;
	INetFwAuthorizedApplications* fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);
	_ASSERT(fwName != NULL);

	// First check to see if the application is already authorized.
	hr = WindowsFirewallAppIsEnabled(
		fwProfile,
		fwProcessImageFileName,
		&fwAppEnabled
	);
	if (FAILED(hr))
	{
		goto error;
	}

	// Only add the application if it isn't already authorized.
	if (!fwAppEnabled)
	{
		// Retrieve the authorized application collection.
		hr = fwProfile->get_AuthorizedApplications(&fwApps);
		if (FAILED(hr))
		{
			goto error;
		}

		// Create an instance of an authorized application.
		hr = CoCreateInstance(
			__uuidof(NetFwAuthorizedApplication),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(INetFwAuthorizedApplication),
			(void**)&fwApp
		);
		if (FAILED(hr))
		{
			goto error;
		}

		// Allocate a BSTR for the process image file name.
		fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
		if (fwBstrProcessImageFileName == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto error;
		}

		// Set the process image file name.
		hr = fwApp->put_ProcessImageFileName(fwBstrProcessImageFileName);
		if (FAILED(hr))
		{
			goto error;
		}

		// Allocate a BSTR for the application friendly name.
		fwBstrName = SysAllocString(fwName);
		if (SysStringLen(fwBstrName) == 0)
		{
			hr = E_OUTOFMEMORY;
			goto error;
		}

		// Set the application friendly name.
		hr = fwApp->put_Name(fwBstrName);
		if (FAILED(hr))
		{
			goto error;
		}

		// Add the application to the collection.
		hr = fwApps->Add(fwApp);
		if (FAILED(hr))
		{
			goto error;
		}
	}

	// Free the BSTRs.
	SysFreeString(fwBstrName);
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	return hr;

error:

	// Free the BSTRs.
	SysFreeString(fwBstrName);
	SysFreeString(fwBstrProcessImageFileName);

	// Release the authorized application instance.
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	// Release the authorized application collection.
	if (fwApps != NULL)
	{
		fwApps->Release();
	}

	WriteErrorMessage("WindowsFirewallAddApp:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallPortIsEnabled(
	IN INetFwProfile* fwProfile,
	IN LONG portNumber,
	IN NET_FW_IP_PROTOCOL ipProtocol,
	OUT BOOL* fwPortEnabled
)
{
	HRESULT hr = S_OK;
	VARIANT_BOOL fwEnabled;
	INetFwOpenPort* fwOpenPort = NULL;
	INetFwOpenPorts* fwOpenPorts = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwPortEnabled != NULL);

	*fwPortEnabled = FALSE;

	// Retrieve the globally open ports collection.
	hr = fwProfile->get_GloballyOpenPorts(&fwOpenPorts);
	if (FAILED(hr))
	{
		goto error;
	}

	// Attempt to retrieve the globally open port.
	hr = fwOpenPorts->Item(portNumber, ipProtocol, &fwOpenPort);
	if (SUCCEEDED(hr))
	{
		// Find out if the globally open port is enabled.
		hr = fwOpenPort->get_Enabled(&fwEnabled);
		if (FAILED(hr))
		{
			goto error;
		}

		if (fwEnabled != VARIANT_FALSE)
		{
			// The globally open port is enabled.
			*fwPortEnabled = TRUE;
		}
		else
		{
		}
	}
	else
	{
		// The globally open port was not in the collection.
		hr = S_OK;
	}

	// Release the globally open port.
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}

	// Release the globally open ports collection.
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}

	return hr;

error:

	// Release the globally open port.
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}

	// Release the globally open ports collection.
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}

	WriteErrorMessage("WindowsFirewallPortIsEnabled:" + Convert::ToString(hr));

	return hr;
}


HRESULT CFirewall::WindowsFirewallPortAdd(
	IN INetFwProfile* fwProfile,
	IN LONG portNumber,
	IN NET_FW_IP_PROTOCOL ipProtocol,
	IN const wchar_t* name
)
{
	HRESULT hr = S_OK;
	BOOL fwPortEnabled;
	BSTR fwBstrName = NULL;
	INetFwOpenPort* fwOpenPort = NULL;
	INetFwOpenPorts* fwOpenPorts = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(name != NULL);

	// First check to see if the port is already added.
	hr = WindowsFirewallPortIsEnabled(
		fwProfile,
		portNumber,
		ipProtocol,
		&fwPortEnabled
	);
	if (FAILED(hr))
	{
		goto error;
	}

	// Only add the port if it isn't already added.
	if (!fwPortEnabled)
	{
		// Retrieve the collection of globally open ports.
		hr = fwProfile->get_GloballyOpenPorts(&fwOpenPorts);
		if (FAILED(hr))
		{
			goto error;
		}

		// Create an instance of an open port.
		hr = CoCreateInstance(
			__uuidof(NetFwOpenPort),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(INetFwOpenPort),
			(void**)&fwOpenPort
		);
		if (FAILED(hr))
		{
			goto error;
		}

		// Set the port number.
		hr = fwOpenPort->put_Port(portNumber);
		if (FAILED(hr))
		{
			goto error;
		}

		// Set the IP protocol.
		hr = fwOpenPort->put_Protocol(ipProtocol);
		if (FAILED(hr))
		{
			goto error;
		}

		// Allocate a BSTR for the friendly name of the port.
		fwBstrName = SysAllocString(name);
		if (SysStringLen(fwBstrName) == 0)
		{
			hr = E_OUTOFMEMORY;
			goto error;
		}

		// Set the friendly name of the port.
		hr = fwOpenPort->put_Name(fwBstrName);
		if (FAILED(hr))
		{
			goto error;
		}

		// Opens the port and adds it to the collection.
		hr = fwOpenPorts->Add(fwOpenPort);
		if (FAILED(hr))
		{
			goto error;
		}
	}

	// Free the BSTR.
	SysFreeString(fwBstrName);

	// Release the open port instance.
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}

	// Release the globally open ports collection.
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}

	return hr;

error:

	// Free the BSTR.
	SysFreeString(fwBstrName);

	// Release the open port instance.
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}

	// Release the globally open ports collection.
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}

	WriteErrorMessage("WindowsFirewallPortAdd:" + Convert::ToString(hr));

	return hr;
}

CFirewall::CFirewall(void)
{
}

CFirewall::~CFirewall(void)
{
}

bool CFirewall::FirewallStatus(void)
{
	HRESULT hr = S_OK;
	HRESULT comInit = E_FAIL;
	INetFwProfile* fwProfile = NULL;

	bool blnResult = false;
	BOOL blnReturn = FALSE;

	if (!ServiceStatus()) return false;

	// Initialize COM.
	comInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (comInit != RPC_E_CHANGED_MODE)
	{
		hr = comInit;
		if (FAILED(hr))
		{
			goto error;
		}
	}

	// Retrieve the firewall profile currently in effect.
	hr = WindowsFirewallInitialize(&fwProfile);
	if (FAILED(hr))
	{
		goto error;
	}

	hr = WindowsFirewallIsOn(fwProfile, &blnReturn);
	if (FAILED(hr))
	{
		goto error;
	}

	// Release the firewall profile.
	WindowsFirewallCleanup(fwProfile);

	// Uninitialize COM.
	if (SUCCEEDED(comInit))
	{
		CoUninitialize();
	}

	if (blnReturn == TRUE)
		return true;
	else
		return false;

error:

	// Release the firewall profile.
	WindowsFirewallCleanup(fwProfile);

	// Uninitialize COM.
	if (SUCCEEDED(comInit))
	{
		CoUninitialize();
	}

	WriteErrorMessage("FirewallStatus");

	return false;
}

bool CFirewall::AddApplication(const wchar_t* strAppPath, const wchar_t* strAppName)
{
	HRESULT hr = S_OK;
	HRESULT comInit = E_FAIL;
	INetFwProfile* fwProfile = NULL;

	if (!ServiceStatus()) return false;

	// Initialize COM.
	comInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
	);

	// Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
	// initialized with a different mode. Since we don't care what the mode is,
	// we'll just use the existing mode.
	if (comInit != RPC_E_CHANGED_MODE)
	{
		hr = comInit;
		if (FAILED(hr))
		{
			goto error;
		}
	}

	// Retrieve the firewall profile currently in effect.
	hr = WindowsFirewallInitialize(&fwProfile);
	if (FAILED(hr))
	{
		goto error;
	}

	// Add Windows Messenger to the authorized application collection.
	hr = WindowsFirewallAddApp(fwProfile, strAppPath, strAppName);
	if (FAILED(hr))
	{
		goto error;
	}

	// Release the firewall profile.
	WindowsFirewallCleanup(fwProfile);

	// Uninitialize COM.
	if (SUCCEEDED(comInit))
	{
		CoUninitialize();
	}

	return true;

error:

	// Release the firewall profile.
	WindowsFirewallCleanup(fwProfile);

	// Uninitialize COM.
	if (SUCCEEDED(comInit))
	{
		CoUninitialize();
	}

	WriteErrorMessage("AddApplication");

	return false;
}

bool CFirewall::AddApplication(System::String^ strAppPath, System::String^ strAppName)
{
	bool blnReturn = false;

	//const wchar_t* chrAppPath = (const wchar_t*)(Marshal::StringToHGlobalUni(strAppPath)).ToPointer();
	//const wchar_t* chrAppName = (const wchar_t*)(Marshal::StringToHGlobalUni(strAppName)).ToPointer();

	wchar_t* chrAppPath = (wchar_t*)(Marshal::StringToHGlobalUni(strAppPath)).ToPointer();
	wchar_t* chrAppName = (wchar_t*)(Marshal::StringToHGlobalUni(strAppName)).ToPointer();

	blnReturn = AddApplication(chrAppPath, chrAppName);

	Marshal::FreeHGlobal((IntPtr)chrAppPath);
	Marshal::FreeHGlobal((IntPtr)chrAppName);

	return blnReturn;
}