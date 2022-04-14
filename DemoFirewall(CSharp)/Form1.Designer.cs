namespace DemoFirewallCS
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_apppath = new System.Windows.Forms.TextBox();
            this.txt_appname = new System.Windows.Forms.TextBox();
            this.btn_CheckFirewall = new System.Windows.Forms.Button();
            this.btn_AddApp = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 55);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "apppath";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(145, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "appname";
            // 
            // txt_apppath
            // 
            this.txt_apppath.Location = new System.Drawing.Point(12, 82);
            this.txt_apppath.Name = "txt_apppath";
            this.txt_apppath.Size = new System.Drawing.Size(100, 21);
            this.txt_apppath.TabIndex = 2;
            this.txt_apppath.Text = "D:\\\\Workshop\\\\云网络智慧教室V53\\\\Release\\\\LBD.CloudNetIntelClassroom.exe";
            this.txt_apppath.TextChanged += new System.EventHandler(this.txt_apppath_TextChanged);
            // 
            // txt_appname
            // 
            this.txt_appname.Location = new System.Drawing.Point(147, 82);
            this.txt_appname.Name = "txt_appname";
            this.txt_appname.Size = new System.Drawing.Size(100, 21);
            this.txt_appname.TabIndex = 3;
            this.txt_appname.Text = "蓝鸽云网络智慧课堂233";
            // 
            // btn_CheckFirewall
            // 
            this.btn_CheckFirewall.Location = new System.Drawing.Point(27, 142);
            this.btn_CheckFirewall.Name = "btn_CheckFirewall";
            this.btn_CheckFirewall.Size = new System.Drawing.Size(205, 23);
            this.btn_CheckFirewall.TabIndex = 4;
            this.btn_CheckFirewall.Text = "检查防火墙状态 ";
            this.btn_CheckFirewall.UseVisualStyleBackColor = true;
            this.btn_CheckFirewall.Click += new System.EventHandler(this.btn_CheckFirewall_Click);
            // 
            // btn_AddApp
            // 
            this.btn_AddApp.Location = new System.Drawing.Point(27, 171);
            this.btn_AddApp.Name = "btn_AddApp";
            this.btn_AddApp.Size = new System.Drawing.Size(205, 23);
            this.btn_AddApp.TabIndex = 5;
            this.btn_AddApp.Text = "设置防火墙例外(包含appname)";
            this.btn_AddApp.UseVisualStyleBackColor = true;
            this.btn_AddApp.Click += new System.EventHandler(this.btn_AddApp_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(27, 200);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(205, 23);
            this.button1.TabIndex = 6;
            this.button1.Text = "设置防火墙例外(不包含appname)";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btn_AddApp);
            this.Controls.Add(this.btn_CheckFirewall);
            this.Controls.Add(this.txt_appname);
            this.Controls.Add(this.txt_apppath);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_apppath;
        private System.Windows.Forms.TextBox txt_appname;
        private System.Windows.Forms.Button btn_CheckFirewall;
        private System.Windows.Forms.Button btn_AddApp;
        private System.Windows.Forms.Button button1;
    }
}

