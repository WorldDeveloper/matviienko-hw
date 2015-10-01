using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace PowerCalc
{
    public partial class Index : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnCalc_Click(object sender, EventArgs e)
        {
            double number;
            if (!double.TryParse(txtNumber.Text, out number))
            {
                lblResult.Text= "Error: Incorrect number";
                return;
            }

            double power;
            if (!double.TryParse(txtPower.Text, out power))
            {
                lblResult.Text = "Error: Incorrect power";
            }

            try
            {

                double result = checked(Math.Pow(number, power));
                lblResult.Text = txtNumber.Text+"^"+txtPower.Text+"="+result.ToString();
            }
            catch (OverflowException)
            {
                lblResult.Text = "Error: Overflow";
            }
        }
    }
}