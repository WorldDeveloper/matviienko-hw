namespace GamesManager
{
    partial class FormTeams
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
            this.txtPictureUrl = new System.Windows.Forms.TextBox();
            this.txtGuid = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cbTeams = new System.Windows.Forms.ComboBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnRemoveTeam = new System.Windows.Forms.Button();
            this.btnUpdateTeam = new System.Windows.Forms.Button();
            this.btnAddTeam = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtWins = new System.Windows.Forms.TextBox();
            this.txtLosses = new System.Windows.Forms.TextBox();
            this.txtDraws = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // txtPictureUrl
            // 
            this.txtPictureUrl.Location = new System.Drawing.Point(82, 192);
            this.txtPictureUrl.Name = "txtPictureUrl";
            this.txtPictureUrl.Size = new System.Drawing.Size(256, 20);
            this.txtPictureUrl.TabIndex = 18;
            // 
            // txtGuid
            // 
            this.txtGuid.Enabled = false;
            this.txtGuid.Location = new System.Drawing.Point(82, 17);
            this.txtGuid.Name = "txtGuid";
            this.txtGuid.Size = new System.Drawing.Size(256, 20);
            this.txtGuid.TabIndex = 17;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 195);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "Picture url:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Name:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "GUID:";
            // 
            // cbTeams
            // 
            this.cbTeams.FormattingEnabled = true;
            this.cbTeams.Location = new System.Drawing.Point(82, 47);
            this.cbTeams.Name = "cbTeams";
            this.cbTeams.Size = new System.Drawing.Size(256, 21);
            this.cbTeams.TabIndex = 13;
            this.cbTeams.DropDown += new System.EventHandler(this.cbTeams_DropDown);
            this.cbTeams.SelectedIndexChanged += new System.EventHandler(this.cbTeams_SelectedIndexChanged);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(258, 253);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 11;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnRemoveTeam
            // 
            this.btnRemoveTeam.Location = new System.Drawing.Point(177, 253);
            this.btnRemoveTeam.Name = "btnRemoveTeam";
            this.btnRemoveTeam.Size = new System.Drawing.Size(75, 23);
            this.btnRemoveTeam.TabIndex = 12;
            this.btnRemoveTeam.Text = "Remove";
            this.btnRemoveTeam.UseVisualStyleBackColor = true;
            this.btnRemoveTeam.Click += new System.EventHandler(this.btnRemoveTeam_Click);
            // 
            // btnUpdateTeam
            // 
            this.btnUpdateTeam.Location = new System.Drawing.Point(96, 253);
            this.btnUpdateTeam.Name = "btnUpdateTeam";
            this.btnUpdateTeam.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateTeam.TabIndex = 10;
            this.btnUpdateTeam.Text = "Update";
            this.btnUpdateTeam.UseVisualStyleBackColor = true;
            this.btnUpdateTeam.Click += new System.EventHandler(this.btnUpdateTeam_Click);
            // 
            // btnAddTeam
            // 
            this.btnAddTeam.Location = new System.Drawing.Point(15, 253);
            this.btnAddTeam.Name = "btnAddTeam";
            this.btnAddTeam.Size = new System.Drawing.Size(75, 23);
            this.btnAddTeam.TabIndex = 9;
            this.btnAddTeam.Text = "Add";
            this.btnAddTeam.UseVisualStyleBackColor = true;
            this.btnAddTeam.Click += new System.EventHandler(this.btnAddTeam_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 90);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(34, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = "Wins:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 125);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 13);
            this.label5.TabIndex = 20;
            this.label5.Text = "Loses:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 160);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(40, 13);
            this.label6.TabIndex = 21;
            this.label6.Text = "Draws:";
            // 
            // txtWins
            // 
            this.txtWins.Location = new System.Drawing.Point(82, 87);
            this.txtWins.Name = "txtWins";
            this.txtWins.Size = new System.Drawing.Size(256, 20);
            this.txtWins.TabIndex = 22;
            // 
            // txtLosses
            // 
            this.txtLosses.Location = new System.Drawing.Point(82, 122);
            this.txtLosses.Name = "txtLosses";
            this.txtLosses.Size = new System.Drawing.Size(256, 20);
            this.txtLosses.TabIndex = 23;
            // 
            // txtDraws
            // 
            this.txtDraws.Location = new System.Drawing.Point(82, 157);
            this.txtDraws.Name = "txtDraws";
            this.txtDraws.Size = new System.Drawing.Size(256, 20);
            this.txtDraws.TabIndex = 24;
            // 
            // FormTeams
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(373, 299);
            this.Controls.Add(this.txtDraws);
            this.Controls.Add(this.txtLosses);
            this.Controls.Add(this.txtWins);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtPictureUrl);
            this.Controls.Add(this.txtGuid);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbTeams);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnRemoveTeam);
            this.Controls.Add(this.btnUpdateTeam);
            this.Controls.Add(this.btnAddTeam);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FormTeams";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Teams";
            this.Load += new System.EventHandler(this.Teams_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtPictureUrl;
        private System.Windows.Forms.TextBox txtGuid;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbTeams;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnRemoveTeam;
        private System.Windows.Forms.Button btnUpdateTeam;
        private System.Windows.Forms.Button btnAddTeam;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtWins;
        private System.Windows.Forms.TextBox txtLosses;
        private System.Windows.Forms.TextBox txtDraws;
    }
}