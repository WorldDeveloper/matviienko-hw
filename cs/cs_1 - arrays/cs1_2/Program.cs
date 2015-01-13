using System;

/*
15. Заполнить квадратную матрицу  по спирали. 
Число 1 ставится в угловой (например, верхний левый) элемент, и спираль закручивается к центру матрицы.
 */

namespace cs1_2
{
    static class Input
    {
        public static int Number(string mes)
        {
            int numVal = 0;

            while (true)
            {
                Console.Write(mes);
                string input = Console.ReadLine();

                try
                {
                    numVal = Convert.ToInt32(input);
                }
                catch (FormatException)
                {
                    Console.WriteLine("Input string is not a sequence of digits.\n");
                    continue;
                }
                catch (OverflowException)
                {
                    Console.WriteLine("The number cannot fit in an Int32.\n");
                    continue;
                }

                if (numVal < 2 || numVal > 9)
                {
                    Console.WriteLine(" *Enter number between 1 and 10.\n");
                    continue;
                }

                break;
            }

            return numVal;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Example 1_2";
            int arSize = Input.Number("Enter the size of an array: ");

            int[,] numArray = new int[arSize, arSize];

            CreateArray(arSize, numArray);

            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("\n");
            for (int m = 0; m < arSize; ++m)
            {
                Console.Write("\t");
                for (int n = 0; n < arSize; ++n)
                {
                    Console.Write("{0}\t", numArray[m, n]);
                }
                Console.WriteLine("\n\t");
            }
            Console.ResetColor();
        }

        private static void CreateArray(int arSize, int[,] numArray)
        {
            int x = 0;
            int y = 0;

            int i = 0;
            numArray[x, y] = i;

            int step = arSize-1;
            double angle = 0;

            while (i<arSize*arSize-1)
            {
                for (int s = 0; s < step; ++s)
                {
                    numArray[y, x] = ++i;
                    y += (int)Math.Sin(angle);
                    x += (int)Math.Cos(angle);                    
                }

                if (angle == 3*Math.PI/2)
                {
                    step -= 2;
                    angle = 0;
                    y++;
                    x++;
                }
                else 
                    angle += Math.PI / 2;
            }

            numArray[y, x] = arSize*arSize;
        }
    }
}
