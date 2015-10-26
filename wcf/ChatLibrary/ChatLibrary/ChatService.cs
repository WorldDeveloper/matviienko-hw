using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;

namespace ChatLibrary
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ChatService : IChatService
    {
        private Dictionary<string, IChatServiceCallback> mSubscribers;

        public ChatService()
        {
            mSubscribers = new Dictionary<string, IChatServiceCallback>();
        }
        public void Join(string name)
        {
            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (mSubscribers.ContainsKey(name))
                return;

            if (mSubscribers != null)
                registeredUser.ConnectedUsersCallback(mSubscribers.Keys.ToList<string>());

            mSubscribers.Add(name, registeredUser);
            List<string> disconnectedUsers = new List<string>();
            foreach (var subscriber in mSubscribers)
            {
                try
                {
                    subscriber.Value.NewUserCallback(name);
                }
                catch
                {
                    disconnectedUsers.Add(subscriber.Key);
                }
            }

            RemoveDisconnectedUsers(disconnectedUsers);
            Console.WriteLine(name + " has joined the conversation.");
        }

        public void Leave(string name)
        {
            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (!mSubscribers.ContainsKey(name))
                return;

            List<string> disconnectedUsers = new List<string>();
            foreach (var subscriber in mSubscribers)
            {
                try
                {
                    subscriber.Value.UserUnjoinedCallBack(name);
                }
                catch
                {
                    disconnectedUsers.Add(subscriber.Key);
                }
            }
            mSubscribers.Remove(name);
            RemoveDisconnectedUsers(disconnectedUsers);
            Console.WriteLine(name + " has left the conversation.");
        }

        public void Send(string from, string message)
        {
            if (mSubscribers.Count == 0 || string.IsNullOrWhiteSpace(message))
                return;

            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (registeredUser != mSubscribers[from])
                return;

            List<string> disconnectedUsers = new List<string>();
            foreach (var subscriber in mSubscribers)
            {
                try
                {
                    subscriber.Value.NewMessageCallback(from, message);
                }
                catch
                {
                    disconnectedUsers.Add(subscriber.Key);
                }
            }
            RemoveDisconnectedUsers(disconnectedUsers);
            Console.WriteLine(from + " has sent a message: " + message);
        }

        public void SendPrivate(string from, string to, string message)
        {
            if (!mSubscribers.ContainsKey(from) || !mSubscribers.ContainsKey(to) || string.IsNullOrWhiteSpace(message))
                return;

            IChatServiceCallback registeredUser = OperationContext.Current.GetCallbackChannel<IChatServiceCallback>();
            if (registeredUser != mSubscribers[from])
                return;
            List<string> disconnectedUsers = new List<string>();
            try
            {
                mSubscribers[to].NewPrivateMessageCallback(from, to, message);
            }
            catch
            {
                disconnectedUsers.Add(to);
            }

            try
            {
                mSubscribers[from].NewPrivateMessageCallback(from, to, message);
                Console.WriteLine("{0} has sent a private message to {1}: {2}", from, to, message);
            }
            catch
            {
                disconnectedUsers.Add(from);
            }
            RemoveDisconnectedUsers(disconnectedUsers);
        }

        private void RemoveDisconnectedUsers(List<string> disconnectedUsers)
        {

            foreach (string user in disconnectedUsers)
            {
                try
                {
                    mSubscribers.Remove(user);
                    foreach (IChatServiceCallback callback in mSubscribers.Values)
                        callback.UserUnjoinedCallBack(user);
                }
                catch
                { }
            }
        }
    }
}
