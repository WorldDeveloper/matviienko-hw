using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ChatLibrary;
using System.Threading;

namespace ChatServiceClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    //[CallbackBehavior(UseSynchronizationContext = false, ConcurrencyMode = ConcurrencyMode.Reentrant)]
    public partial class MainWindow : Window
    {
        public IChatService chat;
        private ChatServiceCallback callback;
        public DuplexChannelFactory<IChatService> factory;
        public InstanceContext context;
        public MainWindow()
        {
            InitializeComponent();

            //callback = new ChatServiceCallback(this);
            //context = new InstanceContext(callback);
            //factory = new DuplexChannelFactory<IChatService>(context, "ChatClientEndPoint");
            //chat = factory.CreateChannel();     
           
        }

        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            callback = new ChatServiceCallback();// 
            callback.Start(callback, txtUserName.Text, this);
            callback.ReceiveMsg += new ReceviedMessage(Callback_ReceiveMsg);    

            //chat.Send("user", "test");
            //ThreadPool.QueueUserWorkItem(new WaitCallback(ThreadProc));

        }


        private void Callback_ReceiveMsg(string sender, string message)
        {
            lblReceivedMesages.Content = lblReceivedMesages.Content + "\n" + sender + " -> " + message;
           
        }

        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            callback.SendMessage(txtUserName.Text, txtNewMessage.Text, true);

            //ChatServiceCallback cb = new ChatServiceCallback(this);
            //cb.NewMessageCallback(null, null, true);
        }

        #region callbacks
        public void NewMessageCallback(string from, string message, bool isPrivate)
        {
            MessageBox.Show(message+"2");
        }

        public void NewUserCallback(string name)
        {
            MessageBox.Show(name);// txtNewMessage.Text = name;
        }

        public void UserUnjoinedCallBack(string from)
        {
            MessageBox.Show(from);// txtNewMessage.Text = from;
        }
        #endregion
    }
}
