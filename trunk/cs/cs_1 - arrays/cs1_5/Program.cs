using System;

/*
18. Заполнить массив следующим образом:
 * 1    57  19  45  29  36  25  52  11  60
 * 58   2   46  20  35  26  37  12  53  10
 * 18   47  3   34  21  44  13  38  9   54
 * 48   17  33  4   51  14  43  8   39  24 
 * 28   32  16  50  5   56  7   42  23  40
 * 31   27  49  15  59  6   55  22  41  30
 */

namespace cs1_5
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

                if (numVal < 2 || numVal > 10)
                {
                    Console.WriteLine(" *Enter number between 1 and 11.\n");
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
            Console.Title = "Example 1_5";
            int row = Input.Number("Enter the number of array's rows: ");
            int col = Input.Number("Enter the number of array's cols: ");


            int[,] numArray = new int[row, col];

            CreateArray(row, col, numArray);

            Show(row, col, numArray);
        }

        private static void Show(int row, int col, int[,] numArray)
        {
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("\n");
            for (int i = 0; i < row; ++i)
            {
                for (int j = 0; j < col; ++j)
                {
                    Console.Write("{0}\t", numArray[i, j]);
                }
                Console.WriteLine("\n");
            }
            Console.ResetColor();
        }

        private static void CreateArray(int row, int col, int[,] numArray)
        {
            int x = -1;
            int y = -1;
            int i = 0;
            double angle = Math.PI / 4;
            double newAngle = Math.PI / 2;

            int end = row * col;
            while (true)
            {
                bool cycle = true;
                while (true)
                {
                    y += (int)Math.Round(Math.Cos(angle));
                    x += (int)Math.Round(Math.Sin(angle));

                    if (x < 0 || x >= col || y < 0 || y >= row)
                    {
                        y -= (int)Math.Round(Math.Cos(angle));
                        x -= (int)Math.Round(Math.Sin(angle));
                        break;
                    }

                    if (numArray[y, x] == 0)
                    {
                        numArray[y, x] = ++i;
                        cycle = false;
                    }
                }

                if (cycle)
                {
                    for (x = -1; x < col - 1 && numArray[row - 1, x + 1] != 0; ++x) ;
                    y = row;
                    angle = 3 * Math.PI / 4;
                    continue;
                }

                if (x == col - 1 && y == row - 1)
                {
                    x = -1;
                    y = row;
                    angle = 3 * Math.PI / 4;
                }
                else if ((x == 0 && y == row - 1) || (x == col - 1 && y == 0))
                {
                    x = col;
                    y = row;
                    angle = 5 * Math.PI / 4;
                }
                else
                {
                    angle += newAngle;

                    int tryY = y + (int)Math.Round(Math.Cos(angle));
                    int tryX = x + (int)Math.Round(Math.Sin(angle));

                    if (tryX < 0 || tryX >= col || tryY < 0 || tryY >= row)
                    {
                        newAngle = -newAngle;
                        angle += Math.PI;
                    }
                }

                if (i >= end) return;
            }
        }
    }
}
