using System;

/*
14. Заполнить квадратную матрицу размером N x M по спирали. 
Число 1 ставится в центр матрицы, а затем массив заполняется по спирали против часовой стрелки значениями по возрастанию.
 */

namespace cs1_1
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

                if (numVal < 2 || numVal>9)
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
            Console.Title = "Example 1_1";
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
            int x = arSize / 2;
            int y = arSize / 2;

            int i = 1;
            numArray[x, y] = i;
            y--;
            x++;

            int step = 2;
            double angle = 0;

            while (y>=0)
            {
                for (int s = 0; s < step; ++s)
                {
                    y += (int)Math.Sin(angle);
                    x -= (int)Math.Cos(angle);
                    if (y >= arSize) return; //if last cell was filled and arSize is even
                    numArray[y, x] = ++i;
                }

                if (angle == 3*Math.PI / 2)
                {
                    step += 2;
                    angle = 0;
                    y--;
                    x++;
                }
                else
                    angle += Math.PI / 2;
            }
        }
    }
}


//int leftX = x - 1;
//int topY = y - 1;
//int rightX = x + 1;
//int bottomY = y + 1;

//while (leftX >= 0)
//{
//    for (int s = 1; s <= step; s++)
//    {
//        numArray[topY, rightX - s] = ++i;

//        if (topY + s >= arSize) continue;
//        numArray[topY + s, leftX] = i + step;

//        if (rightX >= arSize) continue;
//        numArray[bottomY, leftX + s] = i + 2 * step;
//        numArray[bottomY - s, rightX] = i + 3 * step;
//    }
//    i += 3 * step;
//    leftX--;
//    topY--;
//    rightX++;
//    bottomY++;
//    step += 2;
//}