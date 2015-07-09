using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GamesManager
{
    public partial class FormTeams : Form
    {
        public FormTeams()
        {
            InitializeComponent();
        }

        private void Teams_Load(object sender, EventArgs e)
        {
            this.UpdateCBTeams();
        }

        private void UpdateCBTeams()
        {
            cbTeams.Items.Clear();
            DataLayer.Teams teams = new DataLayer.Teams();
            foreach (DataLayer.CbItem team in teams)
            {
                cbTeams.Items.Add(team);
            }
        }

        private void ClearForm()
        {
            txtGuid.Clear();
            cbTeams.Text = "";
            cbTeams.SelectedItem = null;
            cbTeams.SelectedIndex = -1;
            txtWins.Text = "";
            txtDraws.Text = "";
            txtLosses.Text = "";
            txtPictureUrl.Clear();
        }

        private void cbTeams_SelectedIndexChanged(object sender, EventArgs e)
        {
            DataLayer.CbItem curItem = (DataLayer.CbItem)cbTeams.SelectedItem;
            if (curItem == null)
                return;

            DataLayer.Team team = new DataLayer.Team(curItem.ID, curItem.Name, 0, 0, 0);
            team.GetFromDB();
            txtGuid.Text = team.ID.ToString();
            txtWins.Text = team.Wins.ToString();
            txtLosses.Text = team.Losses.ToString();
            txtDraws.Text = team.Draws.ToString();
            txtPictureUrl.Text = team.PictureUrl;
        }

        private void cbTeams_DropDown(object sender, EventArgs e)
        {
            this.UpdateCBTeams();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnRemoveTeam_Click(object sender, EventArgs e)
        {
            DataLayer.CbItem curItem = (DataLayer.CbItem)cbTeams.SelectedItem;
            if (curItem == null)
                return;

            DataLayer.Team team = new DataLayer.Team(curItem.ID, curItem.Name, 0, 0, 0);
            MessageBox.Show(team.RemoveFromDB().ToString() + " row was removed", "Teams removing");
            this.UpdateCBTeams();
            this.ClearForm();
        }

        private void btnUpdateTeam_Click(object sender, EventArgs e)
        {
            if (txtGuid.Text == "" || cbTeams.Text == ""||txtWins.Text==""||txtLosses.Text==""||txtDraws.Text=="")
                return;

            try
            {
                DataLayer.Team team = new DataLayer.Team(
                Guid.Parse(txtGuid.Text),
                cbTeams.Text,
                Int16.Parse(txtWins.Text),
                Int16.Parse(txtLosses.Text),
                Int16.Parse(txtDraws.Text),
                txtPictureUrl.Text); 
                
                MessageBox.Show(team.UpdateInDB().ToString() + " row was updated", "Teams updating");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }

           
        }

        private void btnAddTeam_Click(object sender, EventArgs e)
        {
            if (cbTeams.Text == "")
                return;

            try
            {
                Guid guid = Guid.NewGuid();
                DataLayer.Team team = new DataLayer.Team(
                         guid,
                         cbTeams.Text,
                         Int16.Parse(txtWins.Text),
                         Int16.Parse(txtLosses.Text),
                         Int16.Parse(txtDraws.Text),
                         txtPictureUrl.Text);

                MessageBox.Show(team.AddToDB().ToString() + " row was added", "Teams adding"); 
                this.ClearForm();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
          
        }
    }
}
