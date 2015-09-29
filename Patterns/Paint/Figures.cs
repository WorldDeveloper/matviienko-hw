using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Ink;
using Microsoft.Win32;

namespace Paint
{
    public partial class MainWindow
    {
        private IFigure mFigure;
        private string mFigureType;

        private void icCanvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (icCanvas.EditingMode == InkCanvasEditingMode.Ink)
                return;

            Point startPoint = e.GetPosition(icCanvas);

            mFigure = FigureFactory.GetFigure(mFigureType);
            mFigure.SetAttributes(icCanvas);
            mFigure.StartPoint(startPoint.X, startPoint.Y);
        }

        private void icCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Released || mFigure == null)
                return;

            var pos = e.GetPosition(icCanvas);

            mFigure.EndPoint(pos.X, pos.Y);
        }

        private void icCanvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            mFigure = null;
        }
    }   
}
