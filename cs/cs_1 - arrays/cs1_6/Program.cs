using System;

/*
19. Заполнить трёхмерный массив N x N x N нулями.
 * В получившийся куб вписать шар, состоящий из единиц.
 * После чего, разрезать куб на N слоёв, и показать каждый слой в виде двумерного массива N x N на экране консоли.
 */

namespace cs1_6
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

                if (numVal < 5 || numVal > 79)
                {
                    Console.WriteLine(" *Enter number between 4 and 80.\n");
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
            Console.Title = "Example 1_6";
            int arSize = Input.Number("Enter the size of an array: ");
            int[,,] numArray= new int[arSize, arSize, arSize];
            double standardRadius = arSize / 2;
            if (arSize % 2 == 0) standardRadius-=0.5;

            for (int z = 0; z < arSize; ++z)
            {
                for (int y = 0; y < arSize; ++y)
                {
                    for (int x = 0; x < arSize; ++x)
                    {
                        double curRadius = Math.Sqrt(Math.Pow(z - standardRadius, 2) + Math.Pow(x - standardRadius, 2) + Math.Pow(y - standardRadius, 2));
                        if (standardRadius >= curRadius) numArray[z, y, x] = 1;
                    }                    
                }               
            } 
            
            
            for (int z = 0; z < arSize; ++z)
            {
                Console.Clear();
                Console.WriteLine("Layer# {0} out of {1}\t\tPress the Enter key to continue\n", z+1, arSize);
                for (int y = 0; y < arSize; ++y)
                {
                    for (int x = 0; x < arSize; ++x)
                    {
                        Console.Write(numArray[z, y, x]);
                    }
                    Console.Write("\n");
                }
                Console.ReadLine();
            }
        }
    }
}
