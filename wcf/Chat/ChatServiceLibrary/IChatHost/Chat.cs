using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace ChatHost
{
     [ServiceBehavior(InstanceContextMode= InstanceContextMode.PerCall)]
    public class Chat : IChat
    {
        Dictionary<string, IChatCallback> mSubscribers;
        public Chat()
        {
            mSubscribers = new Dictionary<string, IChatCallback>();
        }
        public bool Join(string name)
        {
            IChatCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            if (mSubscribers.ContainsKey(name))
                return false;

            mSubscribers.Add(name, registeredUser);
            foreach (IChatCallback callback in mSubscribers.Values)
            {
                callback.NewUserCallback(name);
            }

            Console.WriteLine(name+" has joined.");

            return true;
        }

        public void Leave(string name)
        {
            Console.WriteLine("Leave");
            IChatCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            if (!mSubscribers.ContainsKey(name))
                return;

            mSubscribers.Remove(name);
            foreach (IChatCallback callback in mSubscribers.Values)
            {
                callback.UserUnjoinedCallBack(name);
            }
            Console.WriteLine(name + " has left.");
        }

        public void Send(string from, string message)
        {
            if (mSubscribers.Count == 0 || string.IsNullOrWhiteSpace(message))
                return;

            IChatCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            if (registeredUser != mSubscribers[from])
                return;

            foreach (IChatCallback callback in mSubscribers.Values)
            {
                callback.NewMessageCallback(from, message, false);
            }

            Console.WriteLine(from+" message :" + message);
        }

        public void SendPrivate(string from, string to, string message)
        {
            if (!mSubscribers.ContainsKey(to) || string.IsNullOrWhiteSpace(message))
                return;

            IChatCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatCallback>();
            if (registeredUser != mSubscribers[from])
                return;

            mSubscribers[to].NewMessageCallback(from, message, true);
            mSubscribers[from].NewMessageCallback(from, message, true);
            Console.WriteLine(from+" to "+to + " has sent a message :" + message);
        }
    }
}
