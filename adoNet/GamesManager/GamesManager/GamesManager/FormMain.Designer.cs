namespace GamesManager
{
    partial class FormMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip2 = new System.Windows.Forms.MenuStrip();
            this.leaguesToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.teamsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.checkBoxFinished = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.txt1TeamBidPercent = new System.Windows.Forms.TextBox();
            this.txtResult = new System.Windows.Forms.TextBox();
            this.txtNumber = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txt2TeamBidPercent = new System.Windows.Forms.TextBox();
            this.txtGuid = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbTeam2 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbTeam1 = new System.Windows.Forms.ComboBox();
            this.cbLeagues = new System.Windows.Forms.ComboBox();
            this.cbGames = new System.Windows.Forms.ComboBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnRemoveGame = new System.Windows.Forms.Button();
            this.btnUpdateGame = new System.Windows.Forms.Button();
            this.btnAddGame = new System.Windows.Forms.Button();
            this.menuStrip2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip2
            // 
            this.menuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.leaguesToolStripMenuItem1,
            this.teamsToolStripMenuItem});
            this.menuStrip2.Location = new System.Drawing.Point(0, 0);
            this.menuStrip2.Name = "menuStrip2";
            this.menuStrip2.Size = new System.Drawing.Size(384, 24);
            this.menuStrip2.TabIndex = 0;
            this.menuStrip2.Text = "menuStrip2";
            // 
            // leaguesToolStripMenuItem1
            // 
            this.leaguesToolStripMenuItem1.Name = "leaguesToolStripMenuItem1";
            this.leaguesToolStripMenuItem1.Size = new System.Drawing.Size(62, 20);
            this.leaguesToolStripMenuItem1.Text = "Leagues";
            this.leaguesToolStripMenuItem1.Click += new System.EventHandler(this.leaguesToolStripMenuItem_Click);
            // 
            // teamsToolStripMenuItem
            // 
            this.teamsToolStripMenuItem.Name = "teamsToolStripMenuItem";
            this.teamsToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.teamsToolStripMenuItem.Text = "Teams";
            this.teamsToolStripMenuItem.Click += new System.EventHandler(this.teamsToolStripMenuItem_Click);
            // 
            // checkBoxFinished
            // 
            this.checkBoxFinished.AutoSize = true;
            this.checkBoxFinished.Location = new System.Drawing.Point(110, 407);
            this.checkBoxFinished.Name = "checkBoxFinished";
            this.checkBoxFinished.Size = new System.Drawing.Size(65, 17);
            this.checkBoxFinished.TabIndex = 69;
            this.checkBoxFinished.Text = "Finished";
            this.checkBoxFinished.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(26, 373);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 13);
            this.label8.TabIndex = 68;
            this.label8.Text = "League:";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dateTimePicker1.CustomFormat = "dd.MM.yyyy   hh:mm";
            this.dateTimePicker1.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dateTimePicker1.Location = new System.Drawing.Point(110, 334);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(250, 20);
            this.dateTimePicker1.TabIndex = 67;
            // 
            // txt1TeamBidPercent
            // 
            this.txt1TeamBidPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txt1TeamBidPercent.Location = new System.Drawing.Point(110, 262);
            this.txt1TeamBidPercent.Name = "txt1TeamBidPercent";
            this.txt1TeamBidPercent.Size = new System.Drawing.Size(250, 20);
            this.txt1TeamBidPercent.TabIndex = 66;
            // 
            // txtResult
            // 
            this.txtResult.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtResult.Location = new System.Drawing.Point(110, 226);
            this.txtResult.Name = "txtResult";
            this.txtResult.Size = new System.Drawing.Size(250, 20);
            this.txtResult.TabIndex = 65;
            // 
            // txtNumber
            // 
            this.txtNumber.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtNumber.Location = new System.Drawing.Point(110, 116);
            this.txtNumber.Name = "txtNumber";
            this.txtNumber.Size = new System.Drawing.Size(250, 20);
            this.txtNumber.TabIndex = 64;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(26, 265);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 13);
            this.label6.TabIndex = 63;
            this.label6.Text = "1st Team bid:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(27, 229);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 62;
            this.label5.Text = "Result:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(27, 119);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 61;
            this.label4.Text = "Number:";
            // 
            // txt2TeamBidPercent
            // 
            this.txt2TeamBidPercent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txt2TeamBidPercent.Location = new System.Drawing.Point(110, 298);
            this.txt2TeamBidPercent.Name = "txt2TeamBidPercent";
            this.txt2TeamBidPercent.Size = new System.Drawing.Size(250, 20);
            this.txt2TeamBidPercent.TabIndex = 60;
            // 
            // txtGuid
            // 
            this.txtGuid.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtGuid.Enabled = false;
            this.txtGuid.Location = new System.Drawing.Point(110, 43);
            this.txtGuid.Name = "txtGuid";
            this.txtGuid.Size = new System.Drawing.Size(250, 20);
            this.txtGuid.TabIndex = 59;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(27, 340);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(33, 13);
            this.label7.TabIndex = 58;
            this.label7.Text = "Date:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(26, 301);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 13);
            this.label3.TabIndex = 57;
            this.label3.Text = "2nd Team bid:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(27, 192);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(58, 13);
            this.label10.TabIndex = 56;
            this.label10.Text = "2nd Team:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(26, 155);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 55;
            this.label9.Text = "1st Team:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 54;
            this.label2.Text = "Game:";
            // 
            // cbTeam2
            // 
            this.cbTeam2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbTeam2.FormattingEnabled = true;
            this.cbTeam2.Location = new System.Drawing.Point(110, 189);
            this.cbTeam2.Name = "cbTeam2";
            this.cbTeam2.Size = new System.Drawing.Size(250, 21);
            this.cbTeam2.TabIndex = 52;
            this.cbTeam2.DropDown += new System.EventHandler(this.cbTeam2_DropDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 53;
            this.label1.Text = "GUID:";
            // 
            // cbTeam1
            // 
            this.cbTeam1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbTeam1.FormattingEnabled = true;
            this.cbTeam1.Location = new System.Drawing.Point(110, 152);
            this.cbTeam1.Name = "cbTeam1";
            this.cbTeam1.Size = new System.Drawing.Size(250, 21);
            this.cbTeam1.TabIndex = 51;
            this.cbTeam1.DropDown += new System.EventHandler(this.cbTeam1_DropDown);
            this.cbTeam1.SelectedIndexChanged += new System.EventHandler(this.cbTeam1_SelectedIndexChanged);
            // 
            // cbLeagues
            // 
            this.cbLeagues.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbLeagues.FormattingEnabled = true;
            this.cbLeagues.Location = new System.Drawing.Point(110, 370);
            this.cbLeagues.Name = "cbLeagues";
            this.cbLeagues.Size = new System.Drawing.Size(250, 21);
            this.cbLeagues.TabIndex = 50;
            this.cbLeagues.DropDown += new System.EventHandler(this.cbLeagues_DropDown);
            // 
            // cbGames
            // 
            this.cbGames.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cbGames.FormattingEnabled = true;
            this.cbGames.Location = new System.Drawing.Point(110, 79);
            this.cbGames.Name = "cbGames";
            this.cbGames.Size = new System.Drawing.Size(250, 21);
            this.cbGames.TabIndex = 49;
            this.cbGames.SelectedIndexChanged += new System.EventHandler(this.cbGames_SelectedIndexChanged);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(272, 448);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 47;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnRemoveGame
            // 
            this.btnRemoveGame.Location = new System.Drawing.Point(191, 448);
            this.btnRemoveGame.Name = "btnRemoveGame";
            this.btnRemoveGame.Size = new System.Drawing.Size(75, 23);
            this.btnRemoveGame.TabIndex = 48;
            this.btnRemoveGame.Text = "Remove";
            this.btnRemoveGame.UseVisualStyleBackColor = true;
            // 
            // btnUpdateGame
            // 
            this.btnUpdateGame.Location = new System.Drawing.Point(110, 448);
            this.btnUpdateGame.Name = "btnUpdateGame";
            this.btnUpdateGame.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateGame.TabIndex = 46;
            this.btnUpdateGame.Text = "Update";
            this.btnUpdateGame.UseVisualStyleBackColor = true;
            // 
            // btnAddGame
            // 
            this.btnAddGame.Location = new System.Drawing.Point(29, 448);
            this.btnAddGame.Name = "btnAddGame";
            this.btnAddGame.Size = new System.Drawing.Size(75, 23);
            this.btnAddGame.TabIndex = 45;
            this.btnAddGame.Text = "Add";
            this.btnAddGame.UseVisualStyleBackColor = true;
            // 
            // FormMain
            // 
            this.ClientSize = new System.Drawing.Size(384, 511);
            this.Controls.Add(this.checkBoxFinished);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.txt1TeamBidPercent);
            this.Controls.Add(this.txtResult);
            this.Controls.Add(this.txtNumber);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txt2TeamBidPercent);
            this.Controls.Add(this.txtGuid);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cbTeam2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbTeam1);
            this.Controls.Add(this.cbLeagues);
            this.Controls.Add(this.cbGames);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnRemoveGame);
            this.Controls.Add(this.btnUpdateGame);
            this.Controls.Add(this.btnAddGame);
            this.Controls.Add(this.menuStrip2);
            this.MainMenuStrip = this.menuStrip2;
            this.MaximumSize = new System.Drawing.Size(1000, 550);
            this.MinimumSize = new System.Drawing.Size(400, 550);
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Games manager";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.menuStrip2.ResumeLayout(false);
            this.menuStrip2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem leaguesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip2;
        private System.Windows.Forms.ToolStripMenuItem leaguesToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem teamsToolStripMenuItem;
        private System.Windows.Forms.CheckBox checkBoxFinished;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.TextBox txt1TeamBidPercent;
        private System.Windows.Forms.TextBox txtResult;
        private System.Windows.Forms.TextBox txtNumber;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txt2TeamBidPercent;
        private System.Windows.Forms.TextBox txtGuid;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbTeam2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbTeam1;
        private System.Windows.Forms.ComboBox cbLeagues;
        private System.Windows.Forms.ComboBox cbGames;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnRemoveGame;
        private System.Windows.Forms.Button btnUpdateGame;
        private System.Windows.Forms.Button btnAddGame;
    }
}

