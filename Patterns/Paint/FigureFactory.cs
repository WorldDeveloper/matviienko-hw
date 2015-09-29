using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace Paint
{
    class FigureFactory
    {
        public static IFigure GetFigure(string figureType)
        {
            switch (figureType)
            {
                case "Rectangle":
                    return  new ConcreteRectangle();
                case "Line":
                    return new ConcreteLine();

            }

            return null;
        }
    }
}
