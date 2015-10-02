using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace LoginForm
{
    public partial class LoginForm : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("First name: ").Append(txtFirstName.Text);
            sb.Append("<br />Last name: ").Append(txtLastName.Text);
            sb.Append("<br />Login: ").Append(txtLogin.Text);
            sb.Append("<br />Password: ").Append(txtPassword.Text);
            sb.Append("<br />E-mail: ").Append(txtEmail.Text);
            sb.Append("<br />Age: ").Append(txtAge.Text);
            sb.Append("<br />Gender: ");
            foreach (ListItem li in rbGender.Items)
            {
                if (li.Selected)
                {
                    sb.Append(li.Text);
                    break;
                }
            }
            sb.Append("<br />Subscribe: ").Append(cbSubscribe.Checked.ToString());

            lblResult.Text = sb.ToString();

        }
    }
}