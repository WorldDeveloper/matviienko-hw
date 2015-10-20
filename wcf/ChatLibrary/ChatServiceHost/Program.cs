using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using ChatLibrary;

namespace ChatServiceHost
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ServiceHost serviceHost = new ServiceHost(typeof(ChatService)))
            {
                serviceHost.Open();
                DisplayHostInfo(serviceHost);
                Console.WriteLine("The chat is ready.\n");
                Console.WriteLine("Press the Enter key to exit...");
                Console.ReadLine();
            }
        }

        static void DisplayHostInfo(ServiceHost host)
        {
            foreach (System.ServiceModel.Description.ServiceEndpoint se in host.Description.Endpoints)
            {
                Console.WriteLine("Address: {0}", se.Address);
            }
        }
    }
}
