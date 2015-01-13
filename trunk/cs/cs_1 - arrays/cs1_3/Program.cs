using System;

/*
16. Заполнить массив N x M следующим образом:
 * 1    2   3   4   5   6
 * 7    8   9   10  11  12
 * 13   14  15  16  17  18
 * 19   20  21  22  23  24
 * 25   26  27  28  29  30
 */

namespace cs1_3
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
            Console.Title = "Example 1_3";
            int row = Input.Number("Enter the number of array's rows: ");
            int col = Input.Number("Enter the number of array's cols: ");

            int[,] numArray = new int[row, col];

            CreateArray(row, col, numArray);

            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine("\n");
            for (int i = 0; i < row; ++i)
            {
                Console.Write("\t");
                for (int j = 0; j < col; ++j)
                {
                    Console.Write("{0}\t", numArray[i, j]);
                }
                Console.WriteLine("\n\t");
            }
            Console.ResetColor();
        }

        private static void CreateArray(int row, int col, int[,] numArray)
        {
            for (int i = 0; i < row; ++i)
            {
                for (int j = 0; j < col; ++j)
                {
                    numArray[i, j] = i * col + j;
                }
            }
        }
    }
}
