using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace DemoFirewallCS
{
    public partial class Form1 : Form
    {
        [DllImport("Firewall.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        private static extern bool AddApp([MarshalAs(UnmanagedType.LPStr)]string strAppPath);

        [DllImport("Firewall.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        private static extern bool FwStatus();

        [DllImport("Firewall.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        private static extern bool AddApp_withName([MarshalAs(UnmanagedType.LPStr)]string strAppPath, [MarshalAs(UnmanagedType.LPStr)]string strAppName);

        public Form1()
        {
            InitializeComponent();
        }

        private void btn_CheckFirewall_Click(object sender, EventArgs e)
        {
            if (FwStatus())
            {
                PublicMethod.smg("当前防火墙已开启", "防火墙状态");
            }
            else
            {
                PublicMethod.smg("当前防火墙已关闭", "防火墙状态");
            }
        }

        private void btn_AddApp_Click(object sender, EventArgs e)
        {
            string apppath = txt_apppath.Text.Trim().ToString();

            string appname = txt_appname.Text.Trim().ToString();

            //string apppath = "C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe";
            //string appname = "蓝鸽云网络智慧课堂233";


            bool isAdded = false;
            isAdded = AddApp_withName(apppath,appname);
            
            if (isAdded)
            {
                PublicMethod.smg("添加成功", "添加防火墙例外");
            }
            else
            {
                PublicMethod.smg("添加失败", "添加防火墙例外");
            }


        }

        private void txt_apppath_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string apppath = txt_apppath.Text.Trim().ToString();

            //string appname = txt_appname.Text.Trim().ToString();

            //string apppath = "C:\\Program Files (x86)\\LgSoftWAN\\LancooCNSC\\Teacher\\LBD.Frame.NetVoice.SIPServer.exe";
            //string appname = "蓝鸽云网络智慧课堂233";


            bool isAdded = false;
            isAdded = AddApp(apppath);

            if (isAdded)
            {
                PublicMethod.smg("添加成功", "添加防火墙例外");
            }
            else
            {
                PublicMethod.smg("添加失败", "添加防火墙例外");
            }
        }
    }
}
