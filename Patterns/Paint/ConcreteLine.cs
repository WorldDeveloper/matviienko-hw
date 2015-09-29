using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Paint
{
    public class ConcreteLine : IFigure
    {
        private Line mLine;
        private double mStartX;
        private double mStartY;

        public ConcreteLine()
        {
            mLine = new Line();
        }

        public void SetAttributes(InkCanvas canvas)
        {
            mLine.Stroke = new SolidColorBrush(canvas.DefaultDrawingAttributes.Color);
            mLine.StrokeThickness = canvas.DefaultDrawingAttributes.Height;
            canvas.Children.Add(mLine);
        }

        public void StartPoint(double x, double y)
        {
            if (x < 0 || y < 0)
                throw new ArgumentOutOfRangeException();

            mStartX = x;
            mStartY = y;
            mLine.X1 = mStartX;
            mLine.Y1 = mStartY;
            mLine.X2 = mStartX;
            mLine.Y2 = mStartY;
            InkCanvas.SetLeft(mLine, mStartX);
            InkCanvas.SetTop(mLine, mStartY);
        }

        public void EndPoint(double x, double y)
        {
            if (x < 0 || y < 0)
                throw new ArgumentOutOfRangeException();

            double minX = Math.Min(x, mStartX);
            double minY = Math.Min(y, mStartY);

            mLine.X1 = mStartX;
            mLine.Y1 = mStartY;
            mLine.X2 = x;
            mLine.Y2 = y;
            mLine.SnapsToDevicePixels = true;



            InkCanvas.SetLeft(mLine, 0);
            InkCanvas.SetTop(mLine, 0);
        }
    }
}
