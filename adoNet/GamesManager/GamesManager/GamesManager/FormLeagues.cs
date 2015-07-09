using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;



namespace GamesManager
{
    public partial class FormLeagues : Form
    {
        public FormLeagues()
        {
            InitializeComponent();
        }

        private void Leagues_Load(object sender, EventArgs e)
        {
            this.UpdateCBLeague();
        }

        private void cbLeaguesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            DataLayer.CbItem curItem=(DataLayer.CbItem)cbLeague.SelectedItem;
            if (curItem == null)
                return;

            txtGuid.Text = curItem.ID.ToString();

            DataLayer.League league = new DataLayer.League(curItem.ID, curItem.Name);
            league.GetFromDB();
            txtPictureUrl.Text = league.PictureUrl;
        }

        private void cbLeague_DropDown(object sender, EventArgs e)
        {
            this.UpdateCBLeague();         
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnRemoveLeague_Click(object sender, EventArgs e)
        {
            DataLayer.CbItem curItem = (DataLayer.CbItem)cbLeague.SelectedItem;
            if (curItem == null)
                return;

            DataLayer.League league = new DataLayer.League(curItem.ID, curItem.Name);
            MessageBox.Show(league.RemoveFromDB().ToString()+" row was removed", "Leagues removing");
            this.ClearForm();            
        }

        private void UpdateCBLeague()
        {
            cbLeague.Items.Clear();
            DataLayer.Leagues leagues = new DataLayer.Leagues();
            foreach (DataLayer.CbItem league in leagues)
            {
                cbLeague.Items.Add(league);
            }
        }

        private void ClearForm()
        {
            txtGuid.Clear();
            cbLeague.Text = "";
            cbLeague.SelectedItem = null;
            cbLeague.SelectedIndex = -1;
            txtPictureUrl.Clear();
        }

        private void btnUpdateLeague_Click(object sender, EventArgs e)
        {            
            if (txtGuid.Text == "" || cbLeague.Text=="" )
                return;
            
            DataLayer.League league = new DataLayer.League(Guid.Parse(txtGuid.Text), cbLeague.Text, txtPictureUrl.Text);

            MessageBox.Show(league.UpdateInDB().ToString() + " row was updated", "Leagues updating");
        }

        private void btnAddLeague_Click(object sender, EventArgs e)
        {
            if (cbLeague.Text == "")
                return;
            Guid guid = Guid.NewGuid();
            DataLayer.League league = new DataLayer.League(guid, cbLeague.Text, txtPictureUrl.Text);

            MessageBox.Show(league.AddToDB().ToString() + " row was added", "Leagues adding");
            this.ClearForm();
        }
    }
}
