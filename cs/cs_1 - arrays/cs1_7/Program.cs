using System;

/*
20. Реализовать сортировку пузырьком, вставками и выбором для двумерного массива произвольного размера.
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

                if (numVal < 3 || numVal > 19)
                {
                    Console.WriteLine(" *Enter number between 2 and 20.\n");
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
            Console.Title = "Example 1_7";
            int arSize = Input.Number("Enter the size of an array: ");

            int[,] numArray = new int[arSize, arSize];

            SelectSort(arSize, numArray);
            BubbleSort(arSize, numArray);
            InsertSort(arSize, numArray);

        }

        private static void InsertSort(int arSize, int[,] numArray)
        {
            InitArray(arSize, numArray);

            int itemsCount = arSize * arSize;

            for (int i = 0; i < arSize; ++i)
            {
                for (int j = 0; j < arSize; ++j)
                {
                    if (numArray[0, 0] > numArray[i, j])
                    {
                        int tmp = numArray[0, 0];
                        numArray[0, 0] = numArray[i, j];
                        numArray[i, j] = tmp;
                    }
                }
            }


            for (int k = 1; k < itemsCount; ++k)
            {
                int i = k / arSize;
                int j = k % arSize;
                int prevI = (k - 1) / arSize;
                int prevJ = (k - 1) % arSize;
                int min = numArray[i, j];

                for (int n = k; numArray[prevI, prevJ] > min; --n)
                {
                    i = n / arSize;
                    j = n % arSize;
                    prevI = (n - 1) / arSize;
                    prevJ = (n - 1) % arSize;

                    numArray[i, j] = numArray[prevI, prevJ];
                }
                numArray[i, j] = min;
            }

            ShowArray(arSize, numArray, "Insert sort");
        }

        private static void BubbleSort(int arSize, int[,] numArray)
        {
            InitArray(arSize, numArray);

            for (int lastIndex = arSize * arSize - 1; lastIndex > 0; --lastIndex)
            {
                for (int n = 0; n < lastIndex; ++n)
                {
                    int i = n / arSize;
                    int j = n % arSize;
                    int nextI = (n + 1) / arSize;
                    int nextJ = (n + 1) % arSize;

                    if (numArray[nextI, nextJ] < numArray[i, j])
                    {
                        int tmp = numArray[nextI, nextJ];
                        numArray[nextI, nextJ] = numArray[i, j];
                        numArray[i, j] = tmp;
                    }
                }
            }

            ShowArray(arSize, numArray, "Bubble sort");
        }

        private static void SelectSort(int arSize, int[,] numArray)
        {
            InitArray(arSize, numArray);

            int itemsCount = arSize * arSize;

            for (int k = 0; k < arSize; ++k)
            {
                for (int m = 0; m < arSize; ++m)
                {
                    int minI = k;
                    int minJ = m;
                    int min = numArray[minI, minJ];

                    for (int n = k * arSize + m + 1; n < itemsCount; ++n)
                    {
                        int i = n / arSize;
                        int j = n % arSize;

                        if (numArray[i, j] < min)
                        {
                            minI = i;
                            minJ = j;
                            min = numArray[i, j];
                        }
                    }
                    numArray[minI, minJ] = numArray[k, m];
                    numArray[k, m] = min;
                }
            }

            ShowArray(arSize, numArray, "Insert sort");
        }

        private static void ShowArray(int arSize, int[,] numArray, string title)
        {
            Console.WriteLine("\n{0}\n", title);
            for (int i = 0; i < arSize; ++i)
            {
                for (int j = 0; j < arSize; ++j)
                {
                    Console.Write("\t{0}", numArray[i, j]);
                }
                Console.Write("\n");
            }
        }

        private static void InitArray(int arSize, int[,] numArray)
        {
            Random r = new Random();
            for (int i = 0; i < arSize; ++i)
            {
                for (int j = 0; j < arSize; ++j)
                {
                    numArray[i, j] = r.Next(0, arSize * arSize);
                }
            }
            ShowArray(arSize, numArray, "\n\nInitial array");
        }

            


           
    }
}
