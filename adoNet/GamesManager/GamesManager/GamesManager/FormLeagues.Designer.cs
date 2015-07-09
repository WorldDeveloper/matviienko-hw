namespace GamesManager
{
    partial class FormLeagues
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
            this.btnAddLeague = new System.Windows.Forms.Button();
            this.btnUpdateLeague = new System.Windows.Forms.Button();
            this.btnRemoveLeague = new System.Windows.Forms.Button();
            this.cbLeague = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtGuid = new System.Windows.Forms.TextBox();
            this.txtPictureUrl = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnAddLeague
            // 
            this.btnAddLeague.Location = new System.Drawing.Point(24, 136);
            this.btnAddLeague.Name = "btnAddLeague";
            this.btnAddLeague.Size = new System.Drawing.Size(75, 23);
            this.btnAddLeague.TabIndex = 0;
            this.btnAddLeague.Text = "Add";
            this.btnAddLeague.UseVisualStyleBackColor = true;
            this.btnAddLeague.Click += new System.EventHandler(this.btnAddLeague_Click);
            // 
            // btnUpdateLeague
            // 
            this.btnUpdateLeague.Location = new System.Drawing.Point(105, 136);
            this.btnUpdateLeague.Name = "btnUpdateLeague";
            this.btnUpdateLeague.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateLeague.TabIndex = 1;
            this.btnUpdateLeague.Text = "Update";
            this.btnUpdateLeague.UseVisualStyleBackColor = true;
            this.btnUpdateLeague.Click += new System.EventHandler(this.btnUpdateLeague_Click);
            // 
            // btnRemoveLeague
            // 
            this.btnRemoveLeague.Location = new System.Drawing.Point(186, 136);
            this.btnRemoveLeague.Name = "btnRemoveLeague";
            this.btnRemoveLeague.Size = new System.Drawing.Size(75, 23);
            this.btnRemoveLeague.TabIndex = 2;
            this.btnRemoveLeague.Text = "Remove";
            this.btnRemoveLeague.UseVisualStyleBackColor = true;
            this.btnRemoveLeague.Click += new System.EventHandler(this.btnRemoveLeague_Click);
            // 
            // cbLeague
            // 
            this.cbLeague.FormattingEnabled = true;
            this.cbLeague.Location = new System.Drawing.Point(91, 50);
            this.cbLeague.Name = "cbLeague";
            this.cbLeague.Size = new System.Drawing.Size(256, 21);
            this.cbLeague.TabIndex = 3;
            this.cbLeague.DropDown += new System.EventHandler(this.cbLeague_DropDown);
            this.cbLeague.SelectedIndexChanged += new System.EventHandler(this.cbLeaguesList_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "GUID:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Name:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(21, 85);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Picture url:";
            // 
            // txtGuid
            // 
            this.txtGuid.Enabled = false;
            this.txtGuid.Location = new System.Drawing.Point(91, 20);
            this.txtGuid.Name = "txtGuid";
            this.txtGuid.Size = new System.Drawing.Size(256, 20);
            this.txtGuid.TabIndex = 7;
            // 
            // txtPictureUrl
            // 
            this.txtPictureUrl.Location = new System.Drawing.Point(91, 82);
            this.txtPictureUrl.Name = "txtPictureUrl";
            this.txtPictureUrl.Size = new System.Drawing.Size(256, 20);
            this.txtPictureUrl.TabIndex = 8;
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(267, 136);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 2;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // FormLeagues
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(372, 192);
            this.Controls.Add(this.txtPictureUrl);
            this.Controls.Add(this.txtGuid);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbLeague);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnRemoveLeague);
            this.Controls.Add(this.btnUpdateLeague);
            this.Controls.Add(this.btnAddLeague);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "FormLeagues";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Leagues";
            this.Load += new System.EventHandler(this.Leagues_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAddLeague;
        private System.Windows.Forms.Button btnUpdateLeague;
        private System.Windows.Forms.Button btnRemoveLeague;
        private System.Windows.Forms.ComboBox cbLeague;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtGuid;
        private System.Windows.Forms.TextBox txtPictureUrl;
        private System.Windows.Forms.Button btnClose;
    }
}