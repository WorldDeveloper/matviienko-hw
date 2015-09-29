using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Paint
{
    public class ConcreteRectangle : IFigure
    {
        private Rectangle mRectangle;
        private double mStartX;
        private double mStartY;

        public ConcreteRectangle()
        {
            mRectangle = new Rectangle();
        }

        public void SetAttributes(InkCanvas canvas)
        {
            mRectangle.Stroke = new SolidColorBrush(canvas.DefaultDrawingAttributes.Color);
            mRectangle.StrokeThickness = canvas.DefaultDrawingAttributes.Height;
            canvas.Children.Add(mRectangle);
        }

        public void StartPoint(double x, double y)
        {
            if (x < 0 || y < 0)
                throw new ArgumentOutOfRangeException();

            mStartX = x;
            mStartY = y;

            InkCanvas.SetLeft(mRectangle, mStartX);
            InkCanvas.SetTop(mRectangle, mStartY);
        }

        public void EndPoint(double x, double y)
        {
            if (x < 0 || y < 0)
                throw new ArgumentOutOfRangeException();

            double minX = Math.Min(x, mStartX);
            double minY = Math.Min(y, mStartY);

            double width = Math.Max(x, mStartX) - minX;
            double height = Math.Max(y, mStartY) - minY;

            mRectangle.Width = width;
            mRectangle.Height = height;

            InkCanvas.SetLeft(mRectangle, minX);
            InkCanvas.SetTop(mRectangle, minY);
        }
    }
}
