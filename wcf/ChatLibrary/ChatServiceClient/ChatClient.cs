using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ChatLibrary;
using System.ServiceModel;
using System.Threading;
using System.Windows.Documents;
using System.Windows.Media;

namespace ChatServiceClient
{
    class ChatClient : IChatServiceCallback
    {
        private InstanceContext mContext;
        private IChatService mClient;
        private string mCurrentUser;
        private MainWindow mWindow;

        public ChatClient()
        {
            mContext = null;
            mClient = null;
            mCurrentUser = null;
            mWindow = null;
        }

        public void Start(ChatClient callback, string name, MainWindow window)
        {
            mWindow = window;
            mContext = new InstanceContext(callback);
            DuplexChannelFactory<IChatService> factory = new DuplexChannelFactory<IChatService>(mContext, "ChatClientEndPoint");
            mClient = factory.CreateChannel();
            mCurrentUser = name;

            mClient.Join(name);
        }

        public void SendMessage(string from, string message)
        {
            mClient.Send(from, message);
        }

        public void SendPrivateMessage(string from, string to, string message)
        {
            mClient.SendPrivate(from, to, message);
        }

        public void Leave(string name)
        {
            mClient.Leave(name);
        }

        public void NewMessageCallback(string from, string message)
        {
            if (from == mCurrentUser)
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run("-> "+message+"\n") { Foreground = Brushes.Green, FontWeight = FontWeights.Bold });
            }
            else
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Bold(new Run(from + ": ")));
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n"));
            }
            mWindow.svReceivedMessages.ScrollToBottom();

            if (from == mCurrentUser)
                mWindow.txtNewMessage.Text = "";
        }

        public void NewPrivateMessageCallback(string from, string to, string message)
        {
            if (from == mCurrentUser)
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run(from+" -> " + to + ": ") { Foreground = Brushes.Red, FontWeight = FontWeights.Bold });
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n") { Foreground=Brushes.Green, FontWeight = FontWeights.Bold });
            }
            else
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run(from+ ": ") { Foreground = Brushes.Red, FontWeight = FontWeights.Bold });
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n"));
            }
            mWindow.svReceivedMessages.ScrollToBottom();

            if (from == mCurrentUser)
                mWindow.txtNewMessage.Text = "";
        }

        public void NewUserCallback(string name)
        {
            mWindow.lblReceivedMesages.Inlines.Add(new Italic(new Run(name + " has joined the conversation\n")));
            mWindow.svReceivedMessages.ScrollToBottom();

            if (name == mCurrentUser)
            {
                mWindow.btnJoin.Content = "Leave";
                mWindow.txtUserName.IsEnabled = false;
                mWindow.btnSend.IsEnabled = true;
                mWindow.txtNewMessage.IsEnabled = true;
                mWindow.txtNewMessage.Focus();
            }
            else
            {
                mWindow.mUsers.Add(name);
            }
        }

        public void UserUnjoinedCallBack(string name)
        {
            mWindow.lblReceivedMesages.Inlines.Add(new Italic(new Run(name + " has left the conversation\n")));
            mWindow.svReceivedMessages.ScrollToBottom();

            if (name == mCurrentUser)
            {
                mWindow.btnJoin.Content = "Join";
                mWindow.txtUserName.IsEnabled = true;
                mWindow.btnSend.IsEnabled = false;
                mWindow.txtNewMessage.IsEnabled = false;
                mWindow.mUsers.Clear();
            }
            else
            {
                mWindow.mUsers.Remove(name);
            }
        }

        public void ConnectedUsersCallback(List<string> users)
        {
            mWindow.mUsers.Clear();
            users.ForEach(mWindow.mUsers.Add);
        }

    }
}
