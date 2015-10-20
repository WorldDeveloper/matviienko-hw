using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ChatLibrary;

namespace ConsoleApplication1
{
    class ChatServiceCallback : IChatServiceCallback
    {
        public void NewMessageCallback(string from, string message, bool isPrivate)
        {
            Console.WriteLine(from);
        }

        public void NewUserCallback(string name)
        {
            Console.WriteLine(name);
        }

        public void UserUnjoinedCallBack(string from)
        {
            Console.WriteLine(from);
        }
    }
}
