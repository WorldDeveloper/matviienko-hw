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

        private void Main_Load(object sender, EventArgs e)
        {

        }

        private void teamsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form teams = new FormTeams();
            teams.ShowDialog();
        }

        private void manageTeamsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void leaguesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form league = new FormLeagues();
            league.ShowDialog();
        }

        private void gamesToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            this.UpdateCBGames();
            //cbLeagues.Items.Clear();
            //cbLeagues.Items.Add(new DataLayer.CbItem(Guid.NewGuid(), "league"));
            //cbLeagues.SelectedIndex = 0;
        }

        private void UpdateCBGames()
        {
            cbGames.Items.Clear();
            DataLayer.Games games = new DataLayer.Games();

            foreach(DataLayer.CbItem game in games)
            {
                cbGames.Items.Add(game);
            }
        }

        private void cbTeam1_SelectedIndexChanged(object sender, EventArgs e)
        {

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
            DataLayer.CbItem gameItem=(DataLayer.CbItem)cbGames.SelectedItem;
            if ( gameItem== null)
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

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
