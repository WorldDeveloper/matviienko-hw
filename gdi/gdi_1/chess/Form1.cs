using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace chess
{
    
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
             ChessBoard chessBoard = new ChessBoard(this, e);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
