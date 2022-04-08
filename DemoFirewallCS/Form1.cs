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

namespace DemoFirewallCS
{
    public partial class Form1 : Form
    {
        [DllImport("Firewall.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        private static extern bool AddApp(String strAppPath, String strAppName);

        [DllImport("Firewall.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        private static extern bool FwStatus();
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
            bool isAdded = false;
            //bool isAdded = AddApp();
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
