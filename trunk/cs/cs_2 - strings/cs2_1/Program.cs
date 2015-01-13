using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//5. Определить, является ли строка палиндромом. 

namespace StringFunctions
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Write("Enter a string: ");
                string input = Console.ReadLine();
                StringBuilder testString = new StringBuilder("", input.Length);

                for (int i = 0; i < input.Length; ++i)
                {
                    if ((input[i] >= 'A' && input[i] <= 'z') ||
                        (input[i] >= 'А' && input[i] <= 'я'))
                        testString.Append(Char.ToLower(input[i]));
                }

                int halfString = testString.Length / 2;
                bool palindrome = true;
                if (halfString < 1) palindrome = false;

                for (int i = 0; i < halfString; ++i)
                {
                    if (testString[i] != testString[testString.Length - i - 1]) palindrome = false;
                }

                if (palindrome) Console.WriteLine("\nThis is a polindrome.\n");
                else Console.WriteLine("\nThis is not a polindrome.\n");

                Console.WriteLine("\nTry again? Y/N");
                string go = Console.ReadLine();
                if (go == "N" || go == "n")
                {
                    break;
                }
                Console.Clear();
            }
        }
    }
}
