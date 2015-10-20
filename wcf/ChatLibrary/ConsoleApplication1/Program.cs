using ChatLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            InstanceContext context = new InstanceContext(new ChatServiceCallback());
            using (DuplexChannelFactory<IChatService> factory = new DuplexChannelFactory<IChatService>(context, "ChatClientEndPoint"))
            {
                IChatService chat = factory.CreateChannel();
                string user = Console.ReadLine();
                chat.Send(user, null);

                Console.ReadLine();
            }

        }
    }
}
