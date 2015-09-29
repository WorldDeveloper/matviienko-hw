using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace DiskInfoClient_CF
{
    class Program
    {

        static void Main(string[] args)
        {
            ChannelFactory<IMyDiskInfo> factory = new ChannelFactory<IMyDiskInfo>(new BasicHttpBinding(), new EndpointAddress("http://localhost:8080/MyDiskInfo/ep1"));
            IMyDiskInfo channel = factory.CreateChannel();

            string diskName = "c";
            Console.WriteLine("Disk {0}:\\", diskName.ToUpper());

            Console.WriteLine("\n\tTotal size: {0}", channel.TotalSpace(diskName).ToString());
            Console.WriteLine("\n\tFree space: {0}", channel.FreeSpace(diskName).ToString());

            Console.WriteLine("\n\nPress Enter to exit");
            Console.ReadLine();
        }

        [ServiceContract]
        public interface IMyDiskInfo
        {
            [OperationContract]
            string FreeSpace(string disk);
            [OperationContract]
            string TotalSpace(string disk);
        }
    }
}
