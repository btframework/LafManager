using System;
using System.Collections.Generic;
using System.Windows.Forms;

using wclLaf;
using wclCommon;

namespace LafManager
{
    public partial class fmMain : Form
    {
        private wclLafManager FLaf;

        public fmMain()
        {
            InitializeComponent();
        }

        private void fmMain_Load(object sender, EventArgs e)
        {
            FLaf = new wclLafManager();

            Int32 Res = FLaf.Open();
            if (Res != wclErrors.WCL_E_SUCCESS)
                lbLog.Items.Add("Open LAF Manager failed: 0x" + Res.ToString("X8"));

            else
            {
                lbLog.Items.Add("LAF Manager opened");

                String Pfn;
                String AppName;
                String Publisher;
                Res = FLaf.GetIdentity(out Pfn, out AppName, out Publisher);
                if (Res != wclErrors.WCL_E_SUCCESS)
                    lbLog.Items.Add("Get identity failed: 0x" + Res.ToString("X8"));
                else
                {
                    lbLog.Items.Add("PFN: " + Pfn);
                    lbLog.Items.Add("AppName: " + AppName);
                    lbLog.Items.Add("Publisher: " + Publisher);

                    List<String> Laf = new List<String>();

                    Res = FLaf.Enum(Laf);
                    if (Res != wclErrors.WCL_E_SUCCESS)
                        lbLog.Items.Add("Enum LAF failed: 0x" + Res.ToString("X8"));
                    else
                    {
                        if (Laf.Count > 0)
                        {
                            foreach (String s in Laf)
                                cbLaf.Items.Add(s);

                            cbLaf.SelectedIndex = 0;
                        }
                    }
                }
            }
        }

        private void btUnlock_Click(object sender, EventArgs e)
        {
            if (cbLaf.SelectedIndex == -1)
                lbLog.Items.Add("No LAF found");
            else
            {
                String Laf = cbLaf.Text;
                Int32 Res = FLaf.Unlock(Laf);
                if (Res != wclErrors.WCL_E_SUCCESS)
                    lbLog.Items.Add("Unlock " + Laf + " failed: 0x" + Res.ToString("X8"));
                else
                    lbLog.Items.Add("LAF " + Laf + " unlocked");
            }
        }

        private void fmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            FLaf.Close();
        }
    }
}
