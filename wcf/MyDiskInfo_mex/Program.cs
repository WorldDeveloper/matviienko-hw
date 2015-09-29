using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace MyDiskInfo_mex
{
    class Program
    {
        [ServiceContract]
        public interface IMyDiskInfo
        {
            [OperationContract]
            string FreeSpace(string disk);
            [OperationContract]
            string TotalSpace(string disk);
        }

        public class MyDiskInfo : IMyDiskInfo
        {
            public string FreeSpace(string disk)
            {
                if (string.IsNullOrWhiteSpace(disk))
                    return "Wrong disk!";

                disk = disk.Substring(0, 1).ToUpper() + ":\\";
                DriveInfo[] drives = DriveInfo.GetDrives();
                foreach (DriveInfo drive in drives)
                {
                    if (drive.IsReady == true && drive.Name == disk)
                        return drive.TotalFreeSpace.ToString();
                }

                return "Wrong disk!";
            }

            public string TotalSpace(string disk)
            {
                if (string.IsNullOrWhiteSpace(disk))
                    return "Wrong disk!";

                disk = disk.Substring(0, 1).ToUpper() + ":\\";
                DriveInfo[] drives = DriveInfo.GetDrives();
                foreach (DriveInfo drive in drives)
                {
                    if (drive.IsReady == true && drive.Name == disk)
                        return drive.TotalSize.ToString();
                }

                return "Wrong disk!";
            }
        }

        static void Main(string[] args)
        {
            using (ServiceHost host = new ServiceHost(typeof(MyDiskInfo)))
            {
                host.Open();

                Console.WriteLine("Press Enter to exit");
                Console.ReadLine();
            }


        }
    }
}
