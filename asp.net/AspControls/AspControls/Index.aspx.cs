using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace AspControls
{
    public partial class Index : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnSetStyles_Click(object sender, EventArgs e)
        {
            ListItem backColor = lstBackgroundColor.SelectedItem;
            if (backColor != null)
                lblSample.BackColor = Color.FromName(backColor.Text);

            ListItem foreColor = ddlForeColor.SelectedItem;
            if (foreColor != null)
                lblSample.ForeColor = Color.FromName(foreColor.Text);

            if (cbUpperCase.Checked)
                lblSample.Text = lblSample.Text.ToUpper();
            else
                lblSample.Text = lblSample.Text.ToLower();
        }
    }
}