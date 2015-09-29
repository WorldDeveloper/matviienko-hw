using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Paint
{
    interface IFigure
    {
        void StartPoint(double x, double y);
        void EndPoint(double x, double y);
        void SetAttributes(InkCanvas canvas);
    }
}
