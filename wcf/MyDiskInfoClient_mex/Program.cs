using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyDiskInfoClient_mex
{
    class Program
    {
        static void Main(string[] args)
        {
            localhost.MyDiskInfoClient proxy = new localhost.MyDiskInfoClient();

            string diskName = "d";
            Console.WriteLine("Disk {0}:\\", diskName.ToUpper());

            Console.WriteLine("\n\tTotal size: {0}", proxy.TotalSpace(diskName).ToString());
            Console.WriteLine("\n\tFree space: {0}", proxy.FreeSpace(diskName).ToString());

            Console.WriteLine("\n\nPress Enter to exit");
            Console.ReadLine();
        }
    }
}
