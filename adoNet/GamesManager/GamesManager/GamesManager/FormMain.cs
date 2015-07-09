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
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void teamsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form teams = new FormTeams();
            teams.ShowDialog();
            UpdateForm();
        }


        private void leaguesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form league = new FormLeagues();
            league.ShowDialog();
            UpdateForm();
        }


        private void FormMain_Load(object sender, EventArgs e)
        {
            this.UpdateCBGames();
        }

        private void UpdateCBGames()
        {
            cbGames.Items.Clear();
            DataLayer.Games games = new DataLayer.Games();

            foreach (DataLayer.CbItem game in games)
            {
                cbGames.Items.Add(game);
            }
        }

        private void cbTeam1_DropDown(object sender, EventArgs e)
        {
            cbTeam1.Items.Clear();
            DataLayer.Teams teams = new DataLayer.Teams();
            foreach (DataLayer.CbItem team in teams)
            {
                cbTeam1.Items.Add(team);
            }
        }

        private void cbTeam2_DropDown(object sender, EventArgs e)
        {
            cbTeam2.Items.Clear();
            DataLayer.Teams teams = new DataLayer.Teams();
            foreach (DataLayer.CbItem team in teams)
            {
                cbTeam2.Items.Add(team);
            }
        }

        private void cbLeagues_DropDown(object sender, EventArgs e)
        {
            cbLeagues.Items.Clear();
            DataLayer.Leagues leagues = new DataLayer.Leagues();
            foreach (DataLayer.CbItem league in leagues)
            {
                cbLeagues.Items.Add(league);
            }
        }

        private void cbGames_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.UpdateForm();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnRemoveGame_Click(object sender, EventArgs e)
        {
            DataLayer.CbItem curItem = (DataLayer.CbItem)cbGames.SelectedItem;
            if (curItem == null)
                return;

            DataLayer.Game game = new DataLayer.Game();
            game.ID = curItem.ID;
            MessageBox.Show(game.RemoveFromDB().ToString() + " row was removed", "Games removing");
            this.ClearForm();
        }

        private void ClearForm()
        {
            txtGuid.Text = "";
            cbGames.Text = "";
            cbGames.SelectedItem = null;
            cbGames.SelectedIndex = -1;
            txtNumber.Text = "";
            cbTeam1.Text = "";
            cbTeam1.SelectedItem = null;
            cbTeam1.SelectedIndex = -1;
            cbTeam2.Text = "";
            cbTeam2.SelectedItem = null;
            cbTeam2.SelectedIndex = -1;
            txtResult.Text = "";
            txt1TeamBidPercent.Text = "";
            txt2TeamBidPercent.Text = "";
            dateTimePicker1.Value = DateTime.Today;
            cbLeagues.Text = "";
            cbLeagues.SelectedItem = null;
            cbLeagues.SelectedIndex = -1;
            checkBoxFinished.Checked = false;
        }

        private void btnAddGame_Click(object sender, EventArgs e)
        {
            DataLayer.CbItem team1 = (DataLayer.CbItem)cbTeam1.SelectedItem;
            DataLayer.CbItem team2 = (DataLayer.CbItem)cbTeam2.SelectedItem;
            DataLayer.CbItem league = (DataLayer.CbItem)cbLeagues.SelectedItem;

            if (txtNumber.Text == "" || team1 == null || team2 == null || txtResult.Text == "")
                return;

            try
            {
                Guid guid = Guid.NewGuid();
                DataLayer.Game game = new DataLayer.Game(
                         guid,
                         Int32.Parse(txtNumber.Text),
                         team1,
                         team2,
                         Byte.Parse(txtResult.Text),
                         Byte.Parse(txt1TeamBidPercent.Text),
                         Byte.Parse(txt2TeamBidPercent.Text),
                         dateTimePicker1.Value,
                         league,
                         checkBoxFinished.Checked
                         );

                MessageBox.Show(game.AddToDB().ToString() + " row was added", "Games adding");
                this.ClearForm();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void cbGames_DropDown(object sender, EventArgs e)
        {
            this.UpdateCBGames();
        }

        private void btnUpdateGame_Click(object sender, EventArgs e)
        {
            DataLayer.CbItem team1 = (DataLayer.CbItem)cbTeam1.SelectedItem;
            DataLayer.CbItem team2 = (DataLayer.CbItem)cbTeam2.SelectedItem;
            DataLayer.CbItem league = (DataLayer.CbItem)cbLeagues.SelectedItem;

            if (txtNumber.Text == "" || team1 == null || team2 == null || txtResult.Text == "")
                return;

            try
            {
                DataLayer.Game game = new DataLayer.Game(
                         Guid.Parse(txtGuid.Text),
                         Int32.Parse(txtNumber.Text),
                         team1,
                         team2,
                         Byte.Parse(txtResult.Text),
                         Byte.Parse(txt1TeamBidPercent.Text),
                         Byte.Parse(txt2TeamBidPercent.Text),
                         dateTimePicker1.Value,
                         league,
                         checkBoxFinished.Checked
                         );

                MessageBox.Show(game.UpdateInDB().ToString() + " row was updated", "Games updating");
                UpdateCBGames();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
            }
        }

        private void UpdateForm()
        {
            DataLayer.CbItem gameItem = (DataLayer.CbItem)cbGames.SelectedItem;
            if (gameItem == null)
                return;

            DataLayer.Game game = new DataLayer.Game();
            game.GetFromDB(gameItem.ID);

            txtGuid.Text = game.ID.ToString();
            txtNumber.Text = game.Number.ToString();
            cbTeam1.Items.Clear();
            cbTeam1.Items.Add(game.Team1);
            cbTeam1.SelectedIndex = 0;
            cbTeam2.Items.Clear();
            cbTeam2.Items.Add(game.Team2);
            cbTeam2.SelectedIndex = 0;
            txtResult.Text = game.Result.ToString();
            txt1TeamBidPercent.Text = game.Team1BidPercent.ToString();
            txt2TeamBidPercent.Text = game.Team2BidPercent.ToString();
            dateTimePicker1.Value = game.Date;
            cbLeagues.Items.Clear();
            cbLeagues.Items.Add(game.League);
            cbLeagues.SelectedIndex = 0;
            checkBoxFinished.Checked = game.IsFinished;

        }
    }
}
