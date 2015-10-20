using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace ChatLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ChatService
    {
        Dictionary<string, IChatServiceCallback> mSubscribers;

        public ChatService()
        {
            mSubscribers = new Dictionary<string, IChatServiceCallback>();
        }
        public bool Join(string name)
        {
            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (mSubscribers.ContainsKey(name))
                return false;

            mSubscribers.Add(name, registeredUser);
            foreach (IChatServiceCallback callback in mSubscribers.Values)
            {
                callback.NewUserCallback(name);
            }

            Console.WriteLine(name + " has joined the conversation.");

            return true;
        }

        public void Leave(string name)
        {
            Console.WriteLine("Leave");
            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (!mSubscribers.ContainsKey(name))
                return;

            mSubscribers.Remove(name);
            foreach (IChatServiceCallback callback in mSubscribers.Values)
            {
                callback.UserUnjoinedCallBack(name);
            }
            Console.WriteLine(name + " has left the conversation.");
        }

        public void Send(string from, string message)
        {
            if (mSubscribers.Count == 0 || string.IsNullOrWhiteSpace(message))
                return;

            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (registeredUser != mSubscribers[from])
                return;

            foreach (IChatServiceCallback callback in mSubscribers.Values)
            {
                callback.NewMessageCallback(from, message, false);
            }

            Console.WriteLine(from + "has sent a message:" + message);
        }

        public void SendPrivate(string from, string to, string message)
        {
            if (!mSubscribers.ContainsKey(from) || !mSubscribers.ContainsKey(to) || string.IsNullOrWhiteSpace(message))
                return;

            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (registeredUser != mSubscribers[from])
                return;

            mSubscribers[to].NewMessageCallback(from, message, true);
            mSubscribers[from].NewMessageCallback(from, message, true);
            Console.WriteLine("{0} has sent a message to {1}: {2}", from, to, message);
        }
    }
}
