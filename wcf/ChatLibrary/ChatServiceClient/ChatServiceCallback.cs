using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ChatLibrary;
using System.ServiceModel;
using System.Threading;

namespace ChatServiceClient
{
    public delegate void ReceviedMessage(string sender, string message);

    //[CallbackBehavior(UseSynchronizationContext = false, ConcurrencyMode = ConcurrencyMode.Multiple)] // ConcurrencyMode = ConcurrencyMode.Reentrant
    class ChatServiceCallback:IChatServiceCallback
    {

        InstanceContext context = null;
        IChatService client = null;
        string mName;
     
        public event ReceviedMessage ReceiveMsg;
        private MainWindow mWindow;
        public  ChatServiceCallback()//(ChatServiceCallback callback, string name, MainWindow window)
        {
            //mWindow = window;
            //context = new InstanceContext(callback);
            //DuplexChannelFactory<IChatService> factory = new DuplexChannelFactory<IChatService>(context, "ChatClientEndPoint");
            //client = factory.CreateChannel();
            //client.Join(name);
        }

        public void Start(ChatServiceCallback callback, string name, MainWindow window)
        {
            mWindow = window;
            context = new InstanceContext(callback);
            DuplexChannelFactory<IChatService> factory = new DuplexChannelFactory<IChatService>(context, "ChatClientEndPoint");
            client = factory.CreateChannel();
            mName = name;
            client.Join(name);
        }

        public void SendMessage(string from, string message, bool isPrivate)
        {
            client.Send(from, message);
        }

        public void NewMessageCallback(string from, string message, bool isPrivate)
        {
            if (ReceiveMsg != null)
                ReceiveMsg(from, message);

            //MessageBox.Show(message, mName);
            //mWindow.txtUserName.Text = message;          

        }

        public void NewUserCallback(string name)
        {
            MessageBox.Show(name);
        }

        public void UserUnjoinedCallBack(string from)
        {
            MessageBox.Show("Hello");
        }
    }
}
