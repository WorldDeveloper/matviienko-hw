using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace chess
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }

    class ChessBoard
    {
        public ChessBoard(Form parent, PaintEventArgs e)
        {
            int cellSize = 40;
            int padding = 20; // min 10
            int side = 8 * cellSize + padding * 2;
            Size clientSize = new Size(side, side);
            parent.ClientSize = clientSize;

            Graphics g = e.Graphics;
            Rectangle board = parent.ClientRectangle;
            SolidBrush brush = new SolidBrush(Color.BurlyWood);
            g.FillRectangle(brush, board);

            Rectangle[,] cell = new Rectangle[8, 8];
            Font font = new Font("Verdana", Math.Min(padding, cellSize) / 3, FontStyle.Bold);

            for (int i = 0; i < 8; ++i)
            {
                Point numberPosition = new Point(i * cellSize + cellSize / 2 + padding, padding / 3);
                g.DrawString(((char)('A' + i)).ToString(), font, Brushes.White, numberPosition);
            }
            for (int i = 0; i < 8; ++i)
            {
                Point numberPosition = new Point(padding / 3, i * cellSize + cellSize / 2 + padding);
                g.DrawString((8 - i).ToString(), font, Brushes.White, numberPosition);
                for (int j = 0; j < 8; ++j)
                {
                    cell[i, j] = new Rectangle(padding + i * cellSize, padding + j * cellSize, cellSize, cellSize);

                    if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
                        g.FillRectangle(Brushes.White, cell[i, j]);
                    else
                        g.FillRectangle(brush, cell[i, j]);
                }
            }

            int penSize = 2;
            int frameTop = padding - penSize / 2;
            Rectangle cellsFrame = new Rectangle(frameTop, frameTop, 8 * cellSize + penSize, 8 * cellSize + penSize);
            Pen pen = new Pen(Brushes.White, penSize);
            g.DrawRectangle(pen, cellsFrame);
        }
    }

}
