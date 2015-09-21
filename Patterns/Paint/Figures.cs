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
        //********************

        private Point startPoint;
        private Rectangle rect;

        private void icCanvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            startPoint = e.GetPosition(icCanvas);
            this.Title = "x: " + startPoint.X.ToString() + " Y:" + startPoint.Y.ToString();
            rect = new Rectangle
            {
                Stroke = new SolidColorBrush(icCanvas.DefaultDrawingAttributes.Color),
                StrokeThickness = icCanvas.DefaultDrawingAttributes.Height
            };

            icCanvas.Children.Add(rect);
            InkCanvas.SetLeft(rect, startPoint.X);
            InkCanvas.SetTop(rect, startPoint.Y);
        }

        private void icCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Released || rect == null)
                return;

            var pos = e.GetPosition(icCanvas);

            //this.Title = "x: "+pos.X.ToString() + " Y:" + pos.Y.ToString();
            var x = Math.Min(pos.X, startPoint.X);
            var y = Math.Min(pos.Y, startPoint.Y);

            var w = Math.Max(pos.X, startPoint.X) - x;
            var h = Math.Max(pos.Y, startPoint.Y) - y;

            rect.Width = w;
            rect.Height = h;

            InkCanvas.SetLeft(rect, x);
            InkCanvas.SetTop(rect, y);
        }

        private void icCanvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            rect = null;
        }
    }

   
}
