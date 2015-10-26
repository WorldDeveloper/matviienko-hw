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
using System.Media;

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
            try
            {
                mWindow = window;
                mContext = new InstanceContext(callback);
                DuplexChannelFactory<IChatService> factory = new DuplexChannelFactory<IChatService>(mContext, "ChatClientEndPoint");
                mClient = factory.CreateChannel();
                mCurrentUser = name;

                mClient.Join(name);
            }
            catch
            {
                MessageBox.Show("Can't connect to the server", "Chat", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public void SendMessage(string from, string message)
        {
            try
            {
                mClient.Send(from, message);
            }
            catch
            {
                MessageBox.Show("Can't send a message", "Chat", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public void SendPrivateMessage(string from, string to, string message)
        {
            try
            {
                mClient.SendPrivate(from, to, message);
            }
            catch
            {
                MessageBox.Show("Can't send a message", "Chat", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public void Leave(string name)
        {
            try
            {
                mClient.Leave(name);
            }
            catch
            {
                UserUnjoinedCallBack(mCurrentUser);
            }
        }

        public void NewMessageCallback(string from, string message)
        {
            if (from == mCurrentUser)
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run("-> " + message + "\n") { Foreground = Brushes.Green, FontWeight = FontWeights.Bold });
            }
            else
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Bold(new Run(from + ": ")));
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n"));

                using (var soundPlayer = new SoundPlayer(@"c:\Windows\Media\chimes.wav"))
                {
                    soundPlayer.Play();
                }
            }
            mWindow.svReceivedMessages.ScrollToBottom();

            if (from == mCurrentUser)
                mWindow.txtNewMessage.Text = "";
        }

        public void NewPrivateMessageCallback(string from, string to, string message)
        {
            if (from == mCurrentUser)
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run(" -> " + to + ": ") { Foreground = Brushes.Red, FontWeight = FontWeights.Bold });
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n") { Foreground = Brushes.Green, FontWeight = FontWeights.Bold });
            }
            else
            {
                mWindow.lblReceivedMesages.Inlines.Add(new Run(from + ": ") { Foreground = Brushes.Red, FontWeight = FontWeights.Bold });
                mWindow.lblReceivedMesages.Inlines.Add(new Run(message + "\n"));

                using (var soundPlayer = new SoundPlayer(@"c:\Windows\Media\chimes.wav"))
                {
                    soundPlayer.Play();
                }
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
