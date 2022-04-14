Firewall.dll功能说明
接口功能说明：
1.bool AddApp_withName(char* strAppPath,char* strAppName) 
功能：使用该功能前需确保当前代码以管理员身份打开，将一个应用程序添加至防火墙例外
参数说明:
StrAppPath:该应用的路径，如C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe

strAppName:该应用的名称，如蓝鸽云网络智慧课堂

2.bool AddApp(char* strAppPath) 

功能：使用该功能前需确保当前代码以管理员身份打开，将一个应用程序添加至防火墙例外
参数说明:

StrAppPath:该应用的路径，如C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe


3.bool FwStatus(void)

功能:检查当前防火墙是否开启,若开启则返回 true,若未开启，则返回false;

Demo说明:

C++demo：

FwStatus():
检查当前防火墙是否开启

AddApp_withName：

将

 StrAppPath:D:\\Workshop\\云网络智慧教室V53\\Release\\LBD.CloudNetIntelClassroom.exe

 strAppName:蓝鸽云网络智慧课堂

添加到防火墙例外

AddApp：
将 
StrAppPath:C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe

添加到防火墙例外

C# demo：

可以直接输入strAppPath和strName

点击 检查防火墙状态 按钮，将调用FwStatus()接口，检查当前防火墙是否打开并弹窗反馈。

点击 设置防火墙例外(包含appname) 按钮，将 调用AddApp_withName接口:

 StrAppPath:C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe

 strAppName:蓝鸽云网络智慧课堂

 添加至防火墙例外

点击 设置防火墙例外(不包含和appname)按钮，将调用AddApp 接口:
 StrAppPath:C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe

添加至防火墙例外
